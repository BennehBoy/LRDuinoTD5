//Maple Mini & BluePill

#ifndef LRDuinoDefsMM_h
#define LRDuinoDefsMM_h

#define NUM_DISPLAYS 1
#define INTERVAL 	250
#define OBDFAST		400
#define OBDSLOW		600
#define BUT_DELAY 	100
#define MAX_DEPTH 	3
#define DIVISOR     4095
#define MENUTIMEOUT 10000
#define _FAULT_CODES_STRINGS_

#define PIEZO       PB0		// PWM for piezo
// HW SPI
#define OLED_MOSI   PA7		// SPI1_MOSI - connect to D1 on SSD1306
#define MAX_MISO    PA6		// SPI1 MISO
#define OLED_CLK    PA5		// SPI1_SCK - connect to D0 on SSD1306
// SPI Device pins
#define MAX_CS      PC13
#define SD_CS		PA13
#define OLEDCS_1	PB5
#define OLED_RESET  PA8
#define OLED_DC     PB15

// Analogue inputs
#define A4          PA4		// Coolant Level
#define A3          PA3		// Oil Temp
#define A2          PA2		// Oil pressure
#define A1          PA1		// tbox temp
#define A0          PA0		// boost

// user input
#define UPBUT		PC15	//12
#define DOWNBUT		PC14	//13
#define LEFTBUT		PB14	//29
#define RIGHTBUT	PB13	//30
#define SELBUT      PB12	//31 

//K-Line - Serial3
#define K_OUT       PB10	//TX3
#define K_IN        PB11	//RX3

// MAX31856 registers
#define NumRegisters 10
#define ARRAY_SIZE(x) (sizeof(x) / sizeof(*(x)))

#endif
