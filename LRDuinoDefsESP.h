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

#define PIEZO       0		// PWM for piezo
// HW SPI
#define OLED_MOSI   23		// SPI1_MOSI - connect to D1 on SSD1306
#define MAX_MISO    19		// SPI1 MISO
#define OLED_CLK    18		// SPI1_SCK - connect to D0 on SSD1306
// SPI Device pins
#define MAX_CS      21
#define SD_CS		4
#define OLEDCS_1	5
#define OLED_RESET  17
#define OLED_DC     16

// Analogue inputs
#define COOL          32		// Coolant Level
#define OILT          35		// Oil Temp
#define OILP          34		// Oil pressure
#define TBXT          39		// tbox temp
#define BOST          36		// boost

// user input
#define UPBUT		33	//12
#define DOWNBUT		25	//13
#define LEFTBUT		26	//29
#define RIGHTBUT	27	//30
#define SELBUT      14	//31 

//K-Line - Serial3
#define K_OUT       10	//TX3
#define K_IN        9	//RX3

// MAX31856 registers
#define NumRegisters 10
#define ARRAY_SIZE(x) (sizeof(x) / sizeof(*(x)))

#endif
