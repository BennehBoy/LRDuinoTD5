//Maple Mini & BluePill

#ifndef LRDuinoDefsMM_h
#define LRDuinoDefsMM_h

#define NUM_DISPLAYS 1
#define INTERVAL    500
#define BUT_DELAY   100
#define MAX_DEPTH   3
#define DIVISOR     4095
#define MENUTIMEOUT 10000

#define PIEZO       PB0   // PWM for piezo
// HW SPI
#define OLED_MOSI   PA7   // SPI1_MOSI - connect to D1 on SSD1306
#define SD_MISO     PA6   // SPI1_MISO
#define OLED_CLK    PA5   // SPI1_SCK - connect to D0 on SSD1306
#define OLEDCS_1    PB5
#define OLED_RESET  PB3
#define OLED_DC     PA15
#define MAX_MOSI    PB15  // SPI2 MOSI
#define MAX_MISO    PB14  // SPI2 MISO
#define MAX_CLK     PB13  // SPI2 SCK
#define MAX_CS      PB12  // SPI2 SS
#define SD_CS       PA8

// Analogue inputs
#define COOL        PA4   // Coolant Level
#define OILT        PA3   // Oil Temp
#define OILP        PA2   // Oil pressure
#define TBXT        PA1   // tbox temp
#define BOST        PA0   // boost
#define GBOP        PA2   // Gearbox Pressure  - PLACEHOLDER PINS (not enough ADC on MM)
#define GBOT        PA3   // Gearbox Temp  - PLACEHOLDER PINS (not enough ADC on MM)
#define FULP        PA2   // Fuel Pressure  - PLACEHOLDER PINS (not enough ADC on MM)

// user input
#define LEFTBUT     PC14
#define RIGHTBUT    PC15
#define SELBUT      PC13

//K-Line - Serial3
#define K_OUT       PB10  //TX3
#define K_IN        PB11  //RX3

// MAX31856 registers
#define NumRegisters 10
#define ARRAY_SIZE(x) (sizeof(x) / sizeof(*(x)))

#endif
