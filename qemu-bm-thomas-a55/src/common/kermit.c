/*
 * Kermit client implemention.
 * Ported from u-boot.
 *
 * Maintainer: Liuwei <Wei.Liu@verisilicon.com>
 *
 * Copyright (C) 2021 VeriSilicon Microelectronics (Shanghai) Co., Ltd.
 *
 */

#include "common.h"
#include "console.h"
#include <string.h>
#include <ctype.h>
#include <stdarg.h>

/*
 * loadb command (load binary) included
 */
#define XON_CHAR        17
#define XOFF_CHAR       19
#define START_CHAR      0x01
#define ETX_CHAR	0x03
#define END_CHAR        0x0D
#define SPACE           0x20
#define K_ESCAPE        0x23
#define SEND_TYPE       'S'
#define DATA_TYPE       'D'
#define ACK_TYPE        'Y'
#define NACK_TYPE       'N'
#define BREAK_TYPE      'B'
#define tochar(x) ((char) (((x) + SPACE) & 0xff))
#define untochar(x) ((int) (((x) - SPACE) & 0xff))

static void set_kerm_bin_mode(void *addr);
static int k_recv(void);

static char his_eol;        /* character he needs at end of packet */
static int  his_pad_count;  /* number of pad chars he needs */
static char his_pad_char;   /* pad chars he needs */
static char his_quote;      /* quote chars he'll use */

static void send_pad(void)
{
	int count = his_pad_count;

	while (count-- > 0)
		console_putc(his_pad_char);
}

/* converts escaped kermit char to binary char */
static char ktrans(char in)
{
	if ((in & 0x60) == 0x40)
		return (char) (in & ~0x40);
	else if ((in & 0x7f) == 0x3f)
		return (char) (in | 0x40);
	else
		return in;
}

static int chk1(char *buffer)
{
	int total = 0;

	while (*buffer) {
		total += *buffer++;
	}
	return (int) ((total + ((total >> 6) & 0x03)) & 0x3f);
}

static void s1_sendpacket(char *packet)
{
	send_pad();
	while (*packet) {
		console_putc(*packet++);
	}
}

static char a_b[24];
static void send_ack(int n)
{
	a_b[0] = START_CHAR;
	a_b[1] = tochar(3);
	a_b[2] = tochar(n);
	a_b[3] = ACK_TYPE;
	a_b[4] = '\0';
	a_b[4] = tochar(chk1(&a_b[1]));
	a_b[5] = his_eol;
	a_b[6] = '\0';
	s1_sendpacket(a_b);
}

static void send_nack(int n)
{
	a_b[0] = START_CHAR;
	a_b[1] = tochar(3);
	a_b[2] = tochar(n);
	a_b[3] = NACK_TYPE;
	a_b[4] = '\0';
	a_b[4] = tochar(chk1(&a_b[1]));
	a_b[5] = his_eol;
	a_b[6] = '\0';
	s1_sendpacket(a_b);
}


static void (*os_data_init)(void);
static void (*os_data_char)(char new_char);
static int os_data_state, os_data_state_saved;
static char *os_data_addr, *os_data_addr_saved;
static char *bin_start_address;

static void bin_data_init(void)
{
	os_data_state = 0;
	os_data_addr = bin_start_address;
}

static void os_data_save(void)
{
	os_data_state_saved = os_data_state;
	os_data_addr_saved = os_data_addr;
}

static void os_data_restore(void)
{
	os_data_state = os_data_state_saved;
	os_data_addr = os_data_addr_saved;
}

static void bin_data_char(char new_char)
{
	switch (os_data_state) {
	case 0:					/* data */
		*os_data_addr++ = new_char;
		break;
	default:
		break;
	}
}

static void set_kerm_bin_mode(void *addr)
{
	bin_start_address = (char *) addr;
	os_data_init = bin_data_init;
	os_data_char = bin_data_char;
}


/* k_data_* simply handles the kermit escape translations */
static int k_data_escape, k_data_escape_saved;
static void k_data_init(void)
{
	k_data_escape = 0;
	os_data_init();
}

static void k_data_save(void)
{
	k_data_escape_saved = k_data_escape;
	os_data_save();
}

static void k_data_restore(void)
{
	k_data_escape = k_data_escape_saved;
	os_data_restore();
}

static void k_data_char(char new_char)
{
	if (k_data_escape) {
		/* last char was escape - translate this character */
		os_data_char(ktrans(new_char));
		k_data_escape = 0;
	} else {
		if (new_char == his_quote)
			/* this char is escape - remember */
			k_data_escape = 1;
		else
			/* otherwise send this char as-is */
			os_data_char(new_char);
	}
}

#define SEND_DATA_SIZE  20
static char send_parms[SEND_DATA_SIZE];
static char *send_ptr;

/* handle_send_packet interprits the protocol info and builds and
   sends an appropriate ack for what we can do */
static void handle_send_packet(int n)
{
	int length = 3;
	int bytes;

	/* initialize some protocol parameters */
	his_eol = END_CHAR;		/* default end of line character */
	his_pad_count = 0;
	his_pad_char = '\0';
	his_quote = K_ESCAPE;

	/* ignore last character if it filled the buffer */
	if (send_ptr == &send_parms[SEND_DATA_SIZE - 1])
		--send_ptr;
	bytes = send_ptr - send_parms;	/* how many bytes we'll process */
	do {
		if (bytes-- <= 0)
			break;
		/* handle MAXL - max length */
		/* ignore what he says - most I'll take (here) is 94 */
		a_b[++length] = tochar(94);
		if (bytes-- <= 0)
			break;
		/* handle TIME - time you should wait for my packets */
		/* ignore what he says - don't wait for my ack longer than 1 second */
		a_b[++length] = tochar(1);
		if (bytes-- <= 0)
			break;
		/* handle NPAD - number of pad chars I need */
		/* remember what he says - I need none */
		his_pad_count = untochar(send_parms[2]);
		a_b[++length] = tochar(0);
		if (bytes-- <= 0)
			break;
		/* handle PADC - pad chars I need */
		/* remember what he says - I need none */
		his_pad_char = ktrans(send_parms[3]);
		a_b[++length] = 0x40;	/* He should ignore this */
		if (bytes-- <= 0)
			break;
		/* handle EOL - end of line he needs */
		/* remember what he says - I need CR */
		his_eol = untochar(send_parms[4]);
		a_b[++length] = tochar(END_CHAR);
		if (bytes-- <= 0)
			break;
		/* handle QCTL - quote control char he'll use */
		/* remember what he says - I'll use '#' */
		his_quote = send_parms[5];
		a_b[++length] = '#';
		if (bytes-- <= 0)
			break;
		/* handle QBIN - 8-th bit prefixing */
		/* ignore what he says - I refuse */
		a_b[++length] = 'N';
		if (bytes-- <= 0)
			break;
		/* handle CHKT - the clock check type */
		/* ignore what he says - I do type 1 (for now) */
		a_b[++length] = '1';
		if (bytes-- <= 0)
			break;
		/* handle REPT - the repeat prefix */
		/* ignore what he says - I refuse (for now) */
		a_b[++length] = 'N';
		if (bytes-- <= 0)
			break;
		/* handle CAPAS - the capabilities mask */
		/* ignore what he says - I only do long packets - I don't do windows */
		a_b[++length] = tochar(2);	/* only long packets */
		a_b[++length] = tochar(0);	/* no windows */
		a_b[++length] = tochar(94);	/* large packet msb */
		a_b[++length] = tochar(94);	/* large packet lsb */
	} while (0);

	a_b[0] = START_CHAR;
	a_b[1] = tochar(length);
	a_b[2] = tochar(n);
	a_b[3] = ACK_TYPE;
	a_b[++length] = '\0';
	a_b[length] = tochar(chk1(&a_b[1]));
	a_b[++length] = his_eol;
	a_b[++length] = '\0';
	s1_sendpacket(a_b);
}

/* k_recv receives a OS Open image file over kermit line */
static int k_recv(void)
{
	char new_char;
	char k_state, k_state_saved;
	int sum;
	int done;
	int length;
	int n, last_n;
	int len_lo, len_hi;

	/* initialize some protocol parameters */
	his_eol = END_CHAR;		/* default end of line character */
	his_pad_count = 0;
	his_pad_char = '\0';
	his_quote = K_ESCAPE;

	/* initialize the k_recv and k_data state machine */
	done = 0;
	k_state = 0;
	k_data_init();
	k_state_saved = k_state;
	k_data_save();
	n = 0;				/* just to get rid of a warning */
	last_n = -1;

	/* expect this "type" sequence (but don't check):
	   S: send initiate
	   F: file header
	   D: data (multiple)
	   Z: end of file
	   B: break transmission
	 */

	/* enter main loop */
	while (!done) {
		/* set the send packet pointer to begining of send packet parms */
		send_ptr = send_parms;

		/* With each packet, start summing the bytes starting with the length.
		   Save the current sequence number.
		   Note the type of the packet.
		   If a character less than SPACE (0x20) is received - error.
		 */

		/* get a packet */
		/* wait for the starting character or ^C */
		for (;;) {
			switch (console_getc ()) {
			case START_CHAR:	/* start packet */
				goto START;
			case ETX_CHAR:		/* ^C waiting for packet */
				return (0);
			default:
				;
			}
		}
START:
		/* get length of packet */
		sum = 0;
		new_char = console_getc();
		if ((new_char & 0xE0) == 0)
			goto packet_error;
		sum += new_char & 0xff;
		length = untochar(new_char);
		/* get sequence number */
		new_char = console_getc();
		if ((new_char & 0xE0) == 0)
			goto packet_error;
		sum += new_char & 0xff;
		n = untochar(new_char);
		--length;

		/* NEW CODE - check sequence numbers for retried packets */
		/* Note - this new code assumes that the sequence number is correctly
		 * received.  Handling an invalid sequence number adds another layer
		 * of complexity that may not be needed - yet!  At this time, I'm hoping
		 * that I don't need to buffer the incoming data packets and can write
		 * the data into memory in real time.
		 */
		if (n == last_n) {
			/* same sequence number, restore the previous state */
			k_state = k_state_saved;
			k_data_restore();
		} else {
			/* new sequence number, checkpoint the download */
			last_n = n;
			k_state_saved = k_state;
			k_data_save();
		}
		/* END NEW CODE */

		/* get packet type */
		new_char = console_getc();
		if ((new_char & 0xE0) == 0)
			goto packet_error;
		sum += new_char & 0xff;
		k_state = new_char;
		--length;
		/* check for extended length */
		if (length == -2) {
			/* (length byte was 0, decremented twice) */
			/* get the two length bytes */
			new_char = console_getc();
			if ((new_char & 0xE0) == 0)
				goto packet_error;
			sum += new_char & 0xff;
			len_hi = untochar(new_char);
			new_char = console_getc();
			if ((new_char & 0xE0) == 0)
				goto packet_error;
			sum += new_char & 0xff;
			len_lo = untochar(new_char);
			length = len_hi * 95 + len_lo;
			/* check header checksum */
			new_char = console_getc();
			if ((new_char & 0xE0) == 0)
				goto packet_error;
			if (new_char != tochar((sum + ((sum >> 6) & 0x03)) & 0x3f))
				goto packet_error;
			sum += new_char & 0xff;
/* --length; */ /* new length includes only data and block check to come */
		}
		/* bring in rest of packet */
		while (length > 1) {
			new_char = console_getc();
			if ((new_char & 0xE0) == 0)
				goto packet_error;
			sum += new_char & 0xff;
			--length;
			if (k_state == DATA_TYPE) {
				/* pass on the data if this is a data packet */
				k_data_char (new_char);
			} else if (k_state == SEND_TYPE) {
				/* save send pack in buffer as is */
				*send_ptr++ = new_char;
				/* if too much data, back off the pointer */
				if (send_ptr >= &send_parms[SEND_DATA_SIZE])
					--send_ptr;
			}
		}
		/* get and validate checksum character */
		new_char = console_getc();
		if ((new_char & 0xE0) == 0)
			goto packet_error;
		if (new_char != tochar((sum + ((sum >> 6) & 0x03)) & 0x3f))
			goto packet_error;
		/* get END_CHAR */
		new_char = console_getc();
		if (new_char != END_CHAR) {
		  packet_error:
			/* restore state machines */
			k_state = k_state_saved;
			k_data_restore();
			/* send a negative acknowledge packet in */
			send_nack(n);
		} else if (k_state == SEND_TYPE) {
			/* crack the protocol parms, build an appropriate ack packet */
			handle_send_packet(n);
		} else {
			/* send simple acknowledge packet in */
			send_ack(n);
			/* quit if end of transmission */
			if (k_state == BREAK_TYPE)
				done = 1;
		}
	}
	return ((unsigned long) os_data_addr - (unsigned long)bin_start_address);
}

void kermit_load(unsigned long offset, unsigned int baudrate)
{
	int size;

	console_printf("## Ready for (kermit) download to 0x%lx at %d bps\n",
							offset, baudrate);

	set_kerm_bin_mode((void *)offset);

	size = k_recv();

	console_printf("## Total Size      = 0x%08x = %d Bytes\n", size, size);
}
