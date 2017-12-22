#ifndef LRDuinoDefs_h
#define LRDuinoDefs_h

#define NUM_DISPLAYS 8
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
#define PIEZO       PB0		//3 // PWM for piezo
// HW SPI
#define OLED_MOSI   PA7		//4 // SPI_MOSI
#define MAX_MISO    PA6		//5 // SPI MISO
#define OLED_CLK    PA5		//6 // SPI_SCK
// Analogue inputs
#define A4          PA4		//7  // Coolant Level
#define A3          PA3		//8  // Oil Temp
#define A2          PA2		//9  // Oil pressure
#define A1          PA1		//10 // tbox temp
#define A0          PA0		//11 // boost
// user input
#define UPBUT		PC15	//12
#define DOWNBUT		PC14	//13
// SPI stuff
#define MAX_CS      PC13	//14
// PB7 //15 is I2C SDA
// PB6 //16 is I2C SCL
#define SD_CS		PA13     // 22
// PA12 - 23 is USB
// PA11 - 24 is USB
#define MUX_OLEDCS_1 0
#define MUX_OLEDCS_2 1
#define MUX_OLEDCS_3 2
#define MUX_OLEDCS_4 3
#define MUX_OLEDCS_5 4
#define MUX_OLEDCS_6 5
#define MUX_OLEDCS_7 6
#define MUX_OLEDCS_8 7
#define MUX_A0	PB5 //17
#define MUX_A1	PB4 //18
#define MUX_A2	PB3 //19
#define MUX_A3	PA15 //20
#define MUX_E1	PA14 //21

#define OLED_RESET  PA8		//27
#define OLED_DC     PB15	//28
// user input
#define LEFTBUT		PB14	//29
#define RIGHTBUT	PB13	//30
#define SELBUT      PB12	//31 

#define K_OUT       PB10  //26   //TX1
#define K_IN        PB11  //25	  //RX1

// MAX31856 registers
#define NumRegisters 10

#define ARRAY_SIZE(x) (sizeof(x) / sizeof(*(x)))

#endif
