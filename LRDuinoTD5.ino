#include <SPI.h>

#if defined ARDUINO_BLACK_F407VE || defined ARDUINO_BLACK_F407ZE || defined ARDUINO_BLACK_F407ZG || defined ARDUINO_FK407M1 || defined ARDUINO_GENERIC_F407VE || defined ARDUINO_DIYMORE_F407VGT // STM Core & SDIO
#include "LRDuinoDefs407VE.h"
SPIClass SPI_2(PB15, PB14, PB13); // Max31856 on MOSI, MISO, CLK - SPI2 on F4,  STM Core
#define ARCH_DEFINED
#endif

#if defined ARDUINO_MAPLEMINI_F103CB || defined ARDUINO_BLUEPILL_F103CB || defined ARDUINO_BLUEPILL_F103C8 || defined ARDUINO_BLACKPILL_F303CC // STM Core SPI SD
#include "LRDuinoDefsMM.h"
SPIClass SPI_2(PB15, PB14, PB13); // Max31856  on MOSI, MISO, CLK - SPI2 on F1,  STM Core
#define Serial SerialUSB
#define ARCH_DEFINED
#endif

//#define ENCODER

#ifndef ARCH_DEFINED
#error Unsupported core \ board combination
#endif

// uncommment the define that matches your display type
#define USE_SSD1306
//#define USE_SSD1331
//#define USE_SSD1351

#include <Adafruit_GFX.h>
#include "Macros.h"

#if defined USE_SSD1306
#include <Adafruit_SSD1306.h>
#define SCREEN_CHOSEN
Adafruit_SSD1306 display1(SCREENWIDTH, SCREENHEIGHT, &SPI, OLED_DC, OLED_RESET, OLEDCS_1);
#endif

#if defined USE_SSD1331
#include <Adafruit_SSD1331.h>
#define SCREEN_CHOSEN
Adafruit_SSD1331 display1(OLEDCS_1, OLED_DC, OLED_RESET);
#endif

#if defined USE_SSD1351
#include <Adafruit_SSD1351.h>
#define SCREEN_CHOSEN
Adafruit_SSD1351 display1(SCREENWIDTH, SCREENHEIGHT, &SPI, OLEDCS_1, OLED_DC, OLED_RESET);
#endif

#ifndef SCREEN_CHOSEN
#error Please choose a screen type by uncommenting one choice only eg "#define USE_SSD1306"
#endif

#include "LRDuinoGFX.h"
#include <Fonts/FreeSansBoldOblique9pt7b.h>
#include <Fonts/FreeSansBoldOblique12pt7b.h>
#include <Fonts/FreeSansBoldOblique18pt7b.h>
#include <Fonts/FreeSansBoldOblique24pt7b.h>
#include "td5comm.h"

#if defined ENCODER
#include <ClickEncoder.h>
#else
#include <Buttons.h>
#endif

byte RegisterValues[] =    {0x90,  0x03,   0xFC,   0x7F,   0xC0,   0x7F,     0xFF,     0x80,     0x00,     0x00 };
String RegisterNames[] =   {"CR0", "CR1", "MASK", "CJHF", "CHLF", "LTHFTH", "LTHFTL", "LTLFTH", "LTLFTL", "CJTO"};
byte RegisterAddresses[] = {0x00,  0x01,   0x02,   0x03,   0x04,   0x05,     0x06,     0x07,     0x08,     0x09 };

Td5Comm td5; // setup ODBC object

int oldPos;
int pos;
bool rotated = 1;

#if defined ENCODER
// Encoder initialisation
ClickEncoder *clickEncoder;
// Timer STM32 - timer to use & callback function for the clickencoder.
#define TIMER_ENC  TIM4

void checkenc(void)
{
  clickEncoder->service();
}
#else
Button btn_left(LEFTBUT, LOW);
Button btn_right(RIGHTBUT, LOW);
Button btn_enter(SELBUT, LOW);
#endif

#include "td5sensors.h"

// Insert code to read settings in here, and also set default states of sensors to hidden if hw is not present
// end settings reading section

uint8_t sensecount = 0;
uint8_t rotation = 0; // incremented by 1 with each button press - it's used to tell the drawdisplay functions which sensor data they should output.

// the follow variable is a long because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
unsigned long previousMillis = 0;        // will store last time the displays were updated
unsigned long menuMillis = 0;
unsigned long inptimeoutMillis = 0;

#define textScale 1
#define fontX 5
#define fontY 9

void setup()
{
  //start serial connection
  //Serial.begin(57600);  //uncomment to send serial debug info
  
#if defined ENCODER
  clickEncoder = new ClickEncoder(LEFTBUT, RIGHTBUT, SELBUT, 2);
#endif

#if defined ARDUINO_ARCH_STM32
#if defined BOARD_maple_mini || defined BOARD_generic_stm32f103c
  // do nothing
#else
  analogReadResolution(12); //12 bits
#endif
#endif

  pinMode(LEFTBUT, INPUT_PULLUP);
  pinMode(RIGHTBUT, INPUT_PULLUP);
  pinMode(SELBUT, INPUT_PULLUP);
  // Pin setup
  pinMode(OLEDCS_1, OUTPUT);
  digitalWrite(OLEDCS_1, HIGH);
  pinMode(MAX_CS, OUTPUT);
  digitalWrite(MAX_CS, HIGH);
  pinMode(SD_CS, OUTPUT);
  digitalWrite(SD_CS, HIGH);

#if defined ARDUINO_BLACK_F407VE || defined ARDUINO_BLACK_F407ZE || defined ARDUINO_BLACK_F407ZG
  pinMode(PA0, INPUT_PULLDOWN);  //Button K_UP
#endif

#if defined ARDUINO_GENERIC_F407VE
    SPI.setMISO(PB4);
    SPI.setMOSI(PB5); 
    SPI.setSCLK(PB3);
#endif

  MAXInitializeChannel(MAX_CS); // Init the MAX31856
  display1.begin(8000000); //construct our displays
  SCREEN_CLEAR();   // clears the screen and buffer
  SCREEN_DISPLAY(); //output to the screen to avoid adafruit logo
 
  getSensecount(); //check how many sensors we have (in case any are programatically disabled

#if defined ENCODER
  /* Timer code for the click encoder */
  TIM_TypeDef *Instance = TIMER_ENC;
  HardwareTimer *stimer_t = new HardwareTimer(Instance);
  stimer_t->setMode(2, TIMER_OUTPUT_COMPARE); // Will not be required post 1.8.0 stm32 release
  stimer_t->setOverflow(1000, HERTZ_FORMAT); // 1000 Hz
  stimer_t->attachInterrupt(checkenc);
  stimer_t->resume();
#endif  

  oldPos = -1;

  initOBD(); // this also fires getSensecount()

} // End Setup

void loop()
{
  unsigned long currentMillis = millis(); //store the time
  #if defined ENCODER
  pos += clickEncoder->getValue();
  #endif

  // USER INPUT


  // left rotation requested
#if defined ENCODER
  if (pos - oldPos < 0) {
#else
  if (btn_left.sense() == buttons_debounce) {
  if (currentMillis - previousMillis > BUT_DELAY) { 
#endif
    oldPos = pos;
    rotation = rotation + 1; // rotate the screens if the button was pressed
    rotated = 1;
    display1.fillScreen(BLACK);
    previousMillis = previousMillis - (INTERVAL + 1); // force an update of the screens.
    if (sensecount < NUM_DISPLAYS) {
      if (rotation == NUM_DISPLAYS) { // if we have less sensors than displays, keep rotating until we hit the screen count
        rotation = 0;
      }
    } else {
      if (rotation == sensecount) { // otherwise rotate until we hit the last sensor
        rotation = 0;
      }
    }
#ifndef ENCODER
  }
#endif
    
  }

  // right rotation requested
#if defined ENCODER
  if (pos - oldPos > 0) {
#else
  if (btn_right.sense() == buttons_debounce) {
  if (currentMillis - previousMillis > BUT_DELAY) { 
#endif
    oldPos = pos;
    rotation = rotation - 1; // rotate the screens if the button was pressed
    rotated = 1;
    display1.fillScreen(BLACK);
    previousMillis = previousMillis - (INTERVAL + 1); // force an update of the screens.
    if (sensecount < NUM_DISPLAYS) {
      if (rotation == 0) { // if we have less sensors than displays, keep rotating until we hit the screen count
        rotation = NUM_DISPLAYS;
      }
    } else {
      if (rotation == 0) { // otherwise rotate until we hit the last sensor
        rotation = sensecount;
      }
    }
#ifndef ENCODER
  }
#endif
  }

  if (currentMillis - previousMillis > INTERVAL) { // only read the sensors and draw the screen if 250 millis have passed
    previousMillis = currentMillis; // save the last time we updated

    if(td5.ecuIsConnected())  {       // keep ecu alive
      if(td5.getLastReceivedPidElapsedTime() > KEEP_ALIVE_TIME) {
        td5.getPid(&pidKeepAlive);  
      }     
      if (td5.getConsecutiveLostFrames() > 3) { // shutdown in case of too many frames lost
        disableOBDSensors();
        td5.disconnectFromEcu();
        SCREEN_CLEAR();
      }
    }

  // update sensors for display 1
  // first work out which sensors will be on that display
  int mainsense = processRotation(1);
  int pairsense = Sensors[mainsense].slaveID;
  // now read the sensors
  readSensor(mainsense);
  if (pairsense != MASTER){ // read the paired sensor if it has one.
    readSensor(pairsense);
  }
  
  // now draw the first display
  drawDISPLAY(display1, 1);
  rotated = 0;
  // repeat the above for each extra display incrementing the index by 1 each time)
  }
} // Void Loop()
