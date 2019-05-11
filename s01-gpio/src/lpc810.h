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

#define FLASHCFG (*(__IO uint32*)0x40040010)

#define PINENABLE0 (*(__IO uint32*)0x4000C1C0)

#define GPIO_DIR0 (*(__IO uint32*)0xA0002000)
#define GPIO_SET0 (*(__IO uint32*)0xA0002200)
#define GPIO_CLR0 (*(__IO uint32*)0xA0002280)
#define GPIO_NOT0 (*(__IO uint32*)0xA0002300)
