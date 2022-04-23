#ifndef PPC_H
#define PPC_H

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

/* SPCTRL memory mapped register access structure */
struct spctrl_def {
    volatile uint32_t reserved[4];
    volatile uint32_t secrespcfg;
    volatile uint32_t nsccfg;
    volatile uint32_t reserved2;
    volatile uint32_t secmpcintstatus;
    volatile uint32_t secppcintstat;
    volatile uint32_t secppcintclr;
    volatile uint32_t secppcinten;
    volatile uint32_t reserved3;
    volatile uint32_t secmscintstat;
    volatile uint32_t secmscintclr;
    volatile uint32_t secmscinten;
    volatile uint32_t reserved4;
    volatile uint32_t brgintstat;
    volatile uint32_t brgintclr;
    volatile uint32_t brginten;
    volatile uint32_t reserved5;
    volatile uint32_t ahbnsppc0;
    volatile uint32_t reserved6[3];
    volatile uint32_t ahbnsppcexp0;
    volatile uint32_t ahbnsppcexp1;
    volatile uint32_t ahbnsppcexp2;
    volatile uint32_t ahbnsppcexp3;
    volatile uint32_t apbnsppc0;
    volatile uint32_t apbnsppc1;
    volatile uint32_t reserved7[2];
    volatile uint32_t apbnsppcexp0;
    volatile uint32_t apbnsppcexp1;
    volatile uint32_t apbnsppcexp2;
    volatile uint32_t apbnsppcexp3;
    volatile uint32_t ahbspppc0;
    volatile uint32_t reserved8[3];
    volatile uint32_t ahbspppcexp0;
    volatile uint32_t ahbspppcexp1;
    volatile uint32_t ahbspppcexp2;
    volatile uint32_t ahbspppcexp3;
    volatile uint32_t apbspppc0;
    volatile uint32_t apbspppc1;
    volatile uint32_t reserved9[2];
    volatile uint32_t apbspppcexp0;
    volatile uint32_t apbspppcexp1;
    volatile uint32_t apbspppcexp2;
    volatile uint32_t apbspppcexp3;
    volatile uint32_t nsmscexp;
    volatile uint32_t reserved10[959];
    volatile uint32_t pid4;
    volatile uint32_t pid5;
    volatile uint32_t pid6;
    volatile uint32_t pid7;
    volatile uint32_t pid0;
    volatile uint32_t pid1;
    volatile uint32_t pid2;
    volatile uint32_t pid3;
    volatile uint32_t cid0;
    volatile uint32_t cid1;
    volatile uint32_t cid2;
    volatile uint32_t cid3;
};


/* Secure Privilege Control */
#define CMSDK_SPCTRL_BASE_S  0x50080000
#define CMSDK_SPCTRL  ((struct spctrl_def*)CMSDK_SPCTRL_BASE_S)

void ppc_init(void);
#endif