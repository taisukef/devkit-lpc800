#define __MAIN_CLOCK 12000000

#define SRAM_LOC 0x10000000
#define SRAM_LEN 0x400

#define __I  volatile const // read only
#define __O  volatile       // write only
#define __IO volatile       // read / write

#define SYSAHBCLKCTRL (*(__IO uint32*)(0x40048080))
#define SYSAHBCLKCTRL_SYS (1 << 0) // default:1
#define SYSAHBCLKCTRL_ROM (1 << 1) // 1
#define SYSAHBCLKCTRL_RAM (1 << 2) // 1
#define SYSAHBCLKCTRL_FLASHREG (1 << 3) // 1
#define SYSAHBCLKCTRL_FLASH (1 << 4) // 1
#define SYSAHBCLKCTRL_I2C (1 << 5) // 0
#define SYSAHBCLKCTRL_GPIO (1 << 6) // 0
#define SYSAHBCLKCTRL_SWM (1 << 7) // 0
#define SYSAHBCLKCTRL_SCT (1 << 8) // 0
#define SYSAHBCLKCTRL_WKT (1 << 9) // 0
#define SYSAHBCLKCTRL_MRT (1 << 10) // 0
#define SYSAHBCLKCTRL_SPI0 (1 << 11) // 0
#define SYSAHBCLKCTRL_SPI1 (1 << 12) // 0
#define SYSAHBCLKCTRL_CRC (1 << 13) // 0
#define SYSAHBCLKCTRL_UART0 (1 << 14) // 0
#define SYSAHBCLKCTRL_UART1 (1 << 15) // 0
#define SYSAHBCLKCTRL_UART2 (1 << 16) // 0
#define SYSAHBCLKCTRL_WWDT (1 << 17) // 0
#define SYSAHBCLKCTRL_IOCON (1 << 18) // 0
#define SYSAHBCLKCTRL_ACMP (1 << 19) // 0

#define PRESETCTRL (*(__IO uint32*)0x40048004)
#define PRESETCTRL_SPI0 (1UL << 0)
#define PRESETCTRL_SPI1 (1UL << 1)
#define PRESETCTRL_UARTFRG (1UL << 2)
#define PRESETCTRL_UART0 (1UL << 3)
#define PRESETCTRL_UART1 (1UL << 4)
#define PRESETCTRL_UART2 (1UL << 5)
#define PRESETCTRL_I2C (1UL << 6)
#define PRESETCTRL_MRT (1UL << 7)
#define PRESETCTRL_SCT (1UL << 8)
#define PRESETCTRL_WKT (1UL << 9)
#define PRESETCTRL_GPIO (1UL << 10)
#define PRESETCTRL_FLASH (1UL << 11)
#define PRESETCTRL_ACMP (1UL << 12)

#define FLASHCFG (*(__IO uint32*)0x40040010)

#define PINENABLE0 (*(__IO uint32*)0x4000C1C0)

#define GPIO_PBYTE0	((__IO   uint8*)0xA0000000) // 17byte
#define GPIO_PWORD0	((__IO  uint16*)0xA0001000) // 17byte * 2
#define GPIO_DIR0	(*(__IO uint32*)0xA0002000)
#define GPIO_MASK0	(*(__IO uint32*)0xA0002080)
#define GPIO_PIN0	(*(__IO uint32*)0xA0002100)
#define GPIO_MPIN0	(*(__IO uint32*)0xA0002180)
#define GPIO_SET0	(*(__IO uint32*)0xA0002200)
#define GPIO_CLR0	(*(__O  uint32*)0xA0002280)
#define GPIO_NOT0	(*(__O  uint32*)0xA0002300)

#define PINASSIGN0 (*(__IO uint32*)0x4000C000)
#define PINASSIGN1 (*(__IO uint32*)0x4000C004)

typedef enum IRQn {
/******  Cortex-M0 Processor Exceptions Numbers ***************************************************/
  Reset_IRQn                    = -15,    /*!< 1 Reset Vector, invoked on Power up and warm reset*/  
  NonMaskableInt_IRQn           = -14,    /*!< 2 Non Maskable Interrupt                           */
  HardFault_IRQn                = -13,    /*!< 3 Cortex-M0 Hard Fault Interrupt                   */
  SVCall_IRQn                   = -5,     /*!< 11 Cortex-M0 SV Call Interrupt                     */
  PendSV_IRQn                   = -2,     /*!< 14 Cortex-M0 Pend SV Interrupt                     */
  SysTick_IRQn                  = -1,     /*!< 15 Cortex-M0 System Tick Interrupt                 */

/******  LPC8xx Specific Interrupt Numbers ********************************************************/
  SPI0_IRQn                     = 0,        /*!< SPI0                                             */
  SPI1_IRQn                     = 1,        /*!< SPI1                                             */
  Reserved0_IRQn                = 2,        /*!< Reserved Interrupt                               */	
  UART0_IRQn                    = 3,        /*!< USART0                                            */
  UART1_IRQn                    = 4,        /*!< USART1                                            */
  UART2_IRQn                    = 5,        /*!< USART2                                            */
  Reserved1_IRQn                = 6,        /*!< Reserved Interrupt                               */    
  Reserved2_IRQn                = 7,        /*!< Reserved Interrupt                               */
  I2C_IRQn                      = 8,        /*!< I2C                                              */
  SCT_IRQn                      = 9,        /*!< SCT                                              */
  MRT_IRQn                      = 10,       /*!< MRT                                              */ 
  CMP_IRQn                      = 11,       /*!< CMP                                              */
  WDT_IRQn                      = 12,       /*!< WDT                                              */
  BOD_IRQn                      = 13,       /*!< BOD                                              */
  Reserved3_IRQn                = 14,       /*!< Reserved Interrupt                               */
  WKT_IRQn                      = 15,       /*!< WKT Interrupt                                    */
  Reserved4_IRQn                = 16,       /*!< Reserved Interrupt                               */    
  Reserved5_IRQn                = 17,       /*!< Reserved Interrupt                               */
  Reserved6_IRQn                = 18,       /*!< Reserved Interrupt                               */    
  Reserved7_IRQn                = 19,       /*!< Reserved Interrupt                               */
  Reserved8_IRQn                = 20,       /*!< Reserved Interrupt                               */    
  Reserved9_IRQn                = 21,       /*!< Reserved Interrupt                               */
  Reserved10_IRQn               = 22,       /*!< Reserved Interrupt                               */    
  Reserved11_IRQn               = 23,       /*!< Reserved Interrupt                               */
  PININT0_IRQn               	= 24,       /*!< External Interrupt 0                             */
  PININT1_IRQn                  = 25,       /*!< External Interrupt 1                             */  
  PININT2_IRQn                  = 26,       /*!< External Interrupt 2                             */
  PININT3_IRQn                  = 27,       /*!< External Interrupt 3                             */
  PININT4_IRQn                  = 28,       /*!< External Interrupt 4                             */
  PININT5_IRQn                  = 29,       /*!< External Interrupt 5                             */
  PININT6_IRQn                  = 30,       /*!< External Interrupt 6                             */
  PININT7_IRQn                  = 31,       /*!< External Interrupt 7                             */
} IRQn_Type;

typedef struct {
  __IO uint32 ISER[1];                      /*!< (Offset: 0x000) Interrupt Set Enable Register            */
       uint32 RESERVED0[31];
  __IO uint32 ICER[1];                      /*!< (Offset: 0x080) Interrupt Clear Enable Register          */
       uint32 RSERVED1[31];
  __IO uint32 ISPR[1];                      /*!< (Offset: 0x100) Interrupt Set Pending Register           */
       uint32 RESERVED2[31];
  __IO uint32 ICPR[1];                      /*!< (Offset: 0x180) Interrupt Clear Pending Register         */
       uint32 RESERVED3[31];
       uint32 RESERVED4[64];
  __IO uint32 IPR[8];                       /*!< (Offset: 0x3EC) Interrupt Priority Register              */
}  NVIC_Type;

#define SCS_BASE (0xE000E000)
#define NVIC_BASE (SCS_BASE + 0x0100)
#define NVIC ((NVIC_Type*)NVIC_BASE)

static inline void NVIC_EnableIRQ(IRQn_Type IRQn) {
	NVIC->ISER[0] = (1 << ((uint32)(IRQn) & 0x1F)); // enable interrupt
}
static inline void NVIC_DisableIRQ(IRQn_Type IRQn) {
	NVIC->ICER[0] = (1 << ((uint32)(IRQn) & 0x1F)); // disable interrupt
}
