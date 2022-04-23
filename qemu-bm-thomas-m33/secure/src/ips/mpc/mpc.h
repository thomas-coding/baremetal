#ifndef MPC_H
#define MPC_H

/* following defines should be used for structure members */
#define     __IM     volatile const      /*! Defines 'read only' structure member permissions */
#define     __OM     volatile            /*! Defines 'write only' structure member permissions */
#define     __IOM    volatile            /*! Defines 'read / write' structure member permissions */

#ifndef uint32_t
typedef unsigned int uint32_t;
#endif

#ifndef uint8_t
typedef unsigned char uint8_t;
#endif


typedef struct {
	unsigned int CTRL;                     /* Offset: 0x000 (R/W) Control Register */
	unsigned int RESERVED0[3];
	unsigned int BLK_MAX;                  /* Offset: 0x010 (R/ ) Block Maximum Register */
	unsigned int BLK_CFG;                  /* Offset: 0x014 (R/ ) Block Configuration Register */
	unsigned int BLK_IDX;                  /* Offset: 0x018 (R/W) Block Index Register */
	unsigned int BLK_LUT;                  /* Offset: 0x01C (R/W) Block Lookup Table Register */
	unsigned int INT_STAT;                 /* Offset: 0x020 (R/ ) Interrupt Status Register */
	unsigned int INT_CLEAR;                /* Offset: 0x024 ( /W) Interrupt Clear Register */
	unsigned int INT_EN;                   /* Offset: 0x028 (R/W) Interrupt Enable Register */
	unsigned int INT_INFO1;                /* Offset: 0x02C (R/ ) Interrupt Info1 Register */
	unsigned int INT_INFO2;                /* Offset: 0x030 (R/ ) Interrupt Info2 Register */
	unsigned int INT_SET;                  /* Offset: 0x034 ( /W) Interrupt Set Register */
} MPC_TypeDef;


/* 0x0000_0000 - 0x0040_0000 
 * 0x1000_0000 - 0x1040_0000
 */
#define SRAM0_MPC               ((MPC_TypeDef       *) 0x58007000UL) /*!< SRAM0 MPC */

void mpc_init(void);
#endif