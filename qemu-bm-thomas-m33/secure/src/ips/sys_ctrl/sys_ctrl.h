#ifndef SYS_CTRL_H
#define SYS_CTRL_H

/* following defines should be used for structure members */
#define     __IM     volatile const      /*! Defines 'read only' structure member permissions */
#define     __OM     volatile            /*! Defines 'write only' structure member permissions */
#define     __IOM    volatile            /*! Defines 'read / write' structure member permissions */

/**
  \brief  Structure type to access the System Control Block (SCB).
 */
typedef struct
{
  __IM  unsigned int  CPUID;                  /*!< Offset: 0x000 (R/ )  CPUID Base Register */
  __IOM unsigned int  ICSR;                   /*!< Offset: 0x004 (R/W)  Interrupt Control and State Register */
  __IOM unsigned int  VTOR;                   /*!< Offset: 0x008 (R/W)  Vector Table Offset Register */
  __IOM unsigned int  AIRCR;                  /*!< Offset: 0x00C (R/W)  Application Interrupt and Reset Control Register */
  __IOM unsigned int  SCR;                    /*!< Offset: 0x010 (R/W)  System Control Register */
  __IOM unsigned int  CCR;                    /*!< Offset: 0x014 (R/W)  Configuration Control Register */
  __IOM unsigned char SHP[12U];               /*!< Offset: 0x018 (R/W)  System Handlers Priority Registers (4-7, 8-11, 12-15) */
  __IOM unsigned int  SHCSR;                  /*!< Offset: 0x024 (R/W)  System Handler Control and State Register */
  __IOM unsigned int  CFSR;                   /*!< Offset: 0x028 (R/W)  Configurable Fault Status Register */
  __IOM unsigned int  HFSR;                   /*!< Offset: 0x02C (R/W)  HardFault Status Register */
  __IOM unsigned int  DFSR;                   /*!< Offset: 0x030 (R/W)  Debug Fault Status Register */
  __IOM unsigned int  MMFAR;                  /*!< Offset: 0x034 (R/W)  MemManage Fault Address Register */
  __IOM unsigned int  BFAR;                   /*!< Offset: 0x038 (R/W)  BusFault Address Register */
  __IOM unsigned int  AFSR;                   /*!< Offset: 0x03C (R/W)  Auxiliary Fault Status Register */
  __IM  unsigned int  PFR[2U];                /*!< Offset: 0x040 (R/ )  Processor Feature Register */
  __IM  unsigned int  DFR;                    /*!< Offset: 0x048 (R/ )  Debug Feature Register */
  __IM  unsigned int  ADR;                    /*!< Offset: 0x04C (R/ )  Auxiliary Feature Register */
  __IM  unsigned int  MMFR[4U];               /*!< Offset: 0x050 (R/ )  Memory Model Feature Register */
  __IM  unsigned int  ISAR[5U];               /*!< Offset: 0x060 (R/ )  Instruction Set Attributes Register */
        unsigned int  RESERVED0[5U];
  __IOM unsigned int  CPACR;                  /*!< Offset: 0x088 (R/W)  Coprocessor Access Control Register */
} SCB_Type;

/* Memory mapping of Core Hardware */
#define SCS_BASE            (0xE000E000UL)                             /*!< System Control Space Base Address */
#define SCB_BASE            (SCS_BASE +  0x0D00UL)                     /*!< System Control Block Base Address */

#define SCB                 ((SCB_Type       *)     SCB_BASE         ) /*!< SCB configuration struct */

void sys_ctrl_init(void);
#endif