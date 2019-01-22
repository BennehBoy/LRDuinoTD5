#ifndef _LRDuinoTD5_Macros
#define _LRDuinoTD5_Macros

#ifdef USE_SSD1306
#define SCREEN_TYPE           Adafruit_SSD1306
#define SCREEN_CLEAR()       display1.clearDisplay()
#define SCREEN_DISPLAY()      display1.display()
#define BLUE WHITE
#define RED WHITE
#define GREEN WHITE
#define CYAN WHITE
#define MAGENTA WHITE
#define YELLOW WHITE

#define SCREENWIDTH 128
#define SCREENHEIGHT 64
#endif

#ifdef USE_SSD1331
#define SCREEN_TYPE           Adafruit_SSD1331
#define SCREEN_CLEAR()     display1.fillScreen(BLACK);
#define SCREEN_DISPLAY()    { }
#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF

#define SCREENWIDTH 96
#define SCREENHEIGHT 64
#endif

#ifdef USE_SSD1351
#define SCREEN_TYPE           Adafruit_SSD1351
#define SCREEN_CLEAR()     display1.fillScreen(BLACK);
#define SCREEN_DISPLAY()    { }
#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF

#define SCREENWIDTH 128
#define SCREENHEIGHT 128
#endif

#endif // End of Macros
