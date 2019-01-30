//Black407VET6

#ifndef LRDuinoDefs407VE_h
#define LRDuinoDefs407VE_h

#define NUM_DISPLAYS 1
#define INTERVAL 	250
#define OBDFAST		400
#define OBDSLOW		600
#define BUT_DELAY 	100
#define MAX_DEPTH 	3
#define DIVISOR     4095
#define MENUTIMEOUT 10000
#define _FAULT_CODES_STRINGS_

#define PIEZO       PE14	// PWM for piezo
// HW SPI
#define OLED_MOSI   PB5		// SPI1_MOSI - connect to D1 on SSD1306
#define SD_MISO     PB4		// SPI1 MISO 
#define OLED_CLK    PB3		// SPI1_SCK - connect to D0 on SSD1306
#define OLEDCS_1    PE10
#define OLED_RESET  PE12
#define OLED_DC     PE8
#define MAX_MOSI    PB15  // SPI2 MOSI
#define MAX_MISO    PB14  // SPI2 MISO
#define MAX_CLK     PB13  // SPI2 SCK
#define MAX_CS      PB12  // SPI2 SS
#define SD_CS       PE13

// Analogue inputs
#define COOL        A4		// Coolant Level - PA4
#define OILT        A3		// Oil Temp - PA3
#define OILP        A2		// Oil pressure - PA2
#define TBXT        A1		// tbox temp  - PA1
#define BOST        A5		// boost - PA5

// user input
#define UPBUT       PE8		// **TBD**
#define DOWNBUT     PA0		// builtin K_UP
#define LEFTBUT     PE6		// **TBD**
#define RIGHTBUT    PE3		// built in K1
#define SELBUT      PE4		// built in K2

//K-Line - Serial3
#define K_OUT       PB10  //TX3
#define K_IN        PB11  //RX3

// MAX31856 registers
#define NumRegisters 10
#define ARRAY_SIZE(x) (sizeof(x) / sizeof(*(x)))

// For CDC serial
#define Serial SerialUSB

#endif
