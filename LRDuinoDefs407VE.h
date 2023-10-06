//Black407VET6

#ifndef LRDuinoDefs407VE_h
#define LRDuinoDefs407VE_h

#define NUM_DISPLAYS 1
#define INTERVAL  250
#define BUT_DELAY   100
#define MAX_DEPTH   3
#define DIVISOR     4095
#define MENUTIMEOUT 10000

#define PIEZO       PE14  // PWM for piezo
// HW SPI
#define OLED_MOSI   PB5   // SPI1_MOSI - connect to D1 on SSD1306
#define SD_MISO     PB4   // SPI1 MISO 
#define OLED_CLK    PB3   // SPI1_SCK - connect to D0 on SSD1306
#define OLEDCS_1    PE10
#define OLED_RESET  PE12
#define OLED_DC     PE8
#define MAX_MOSI    PB15  // SPI2 MOSI
#define MAX_MISO    PB14  // SPI2 MISO
#define MAX_CLK     PB13  // SPI2 SCK
#define MAX_CS      PB12  // SPI2 SS
#define SD_CS       PE13

// Analogue inputs
#define COOL        PA4    // Coolant Level - PA4
#define OILT        PA3    // Oil Temp - PA3
#define OILP        PA2    // Oil pressure - PA2
#define TBXT        PA1    // tbox temp  - PA1
#define BOST        PA5    // boost - PA5
#define GBOP        PA6    // Gearbox Pressure
#define GBOT        PA7    // Gearbox Temp
#define FULP        PB0    // Fuel Pressure

// user input OPTICAL ENCODER
#define LEFTBUT     PB6
#define RIGHTBUT    PB7
#define SELBUT      PB8

//K-Line - Serial3
#define K_OUT       PB10  //TX3
#define K_IN        PB11  //RX3

// MAX31856 registers
#define NumRegisters 10
#define ARRAY_SIZE(x) (sizeof(x) / sizeof(*(x)))

// For CDC serial
#define Serial SerialUSB

#endif
