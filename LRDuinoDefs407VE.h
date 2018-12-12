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

// Following pinout details are for Maple Mini
// 1 - TX for Bluetooth
// 2 - RX for Bluetooth
#define PIEZO       PE14 //PB0		//3 // PWM for piezo
// HW SPI
#define OLED_MOSI   PB5 //PA7		//4 // SPI_MOSI
#define MAX_MISO    PB4 //PA6		//5 // SPI MISO
#define OLED_CLK    PB3 //PA5		//6 // SPI_SCK
// Analogue inputs
#define A4          PA4		//7  // Coolant Level
#define A3          PA3		//8  // Oil Temp
#define A2          PA2		//9  // Oil pressure
#define A1          PA1		//10 // tbox temp
#define A0          PA5		//11 // boost
// user input
#define UPBUT		PE8 // PC15	//12
#define DOWNBUT		PA0 //PC14	//13
// SPI stuff
#define MAX_CS      PE11 //PC13	//14
// PB7 //15 is I2C SDA
// PB6 //16 is I2C SCL
//#define SD_CS		PA13     // 22
// PA12 - 23 is USB
// PA11 - 24 is USB
#define OLEDCS_1	PE10 //PB5 //17


#define OLED_RESET  PE12 //PA8		//27
#define OLED_DC     PE8 //PB15	//28
// user input
#define LEFTBUT		PE6 //PB14	//29
#define RIGHTBUT	PE3 //PB13	//30
#define SELBUT    PE4 //  PB12	//31 

#define K_OUT       PA9 // PB10  //26   //TX1
#define K_IN        PA10 //PB11  //25	  //RX1

// MAX31856 registers
#define NumRegisters 10

#define ARRAY_SIZE(x) (sizeof(x) / sizeof(*(x)))

#endif
