// LRDuino by Ben Anderson
// Version 0.014
// Please select your display type below by uncommenting ONLY your display type (lines 57-59)

#include <SPI.h>

#if defined ARDUINO_BLACK_F407VE || defined ARDUINO_BLACK_F407ZE || defined ARDUINO_BLACK_F407ZG || defined ARDUINO_FK407M1// STM Core & SDIO
#include "LRDuinoDefs407VE.h"
  #define HAS_SDIO
  SPIClass SPI_2(PB15,PB14,PB13); // Max31856 on MOSI, MISO, CLK - SPI2 on F4,  STM Core
  #define ARCH_DEFINED
#endif

#if defined ARDUINO_DIYMROE_F407VGT // STM Core SPI SD
  #include "LRDuinoDefs407VE.h"
  #define ARCH_DEFINED
  SPIClass SPI_2(PB15,PB14,PB13); // Max31856  on MOSI, MISO, CLK - SPI2 on F4,  STM Core
#endif

#if defined BOARD_maple_mini || defined BOARD_generic_stm32f103c // Roger's Maple core SPI SD
  #include "LRDuinoDefsMM.h"
  SPIClass SPI_2(2); // Max31856  on SPI2
  #define ARCH_DEFINED
#endif

#if defined ARDUINO_MAPLEMINI_F103CB || defined ARDUINO_BLUEPILL_F103C8 || defined ARDUINO_BLACKPILL_F103C8 // STM Core SPI SD
  #include "LRDuinoDefsMM.h"
  SPIClass SPI_2(PB15,PB14,PB13); // Max31856  on MOSI, MISO, CLK - SPI2 on F1,  STM Core
  #define ARCH_DEFINED
#endif

#if defined ARDUINO_ARCH_ESP32 // Espressif Core
  #include "LRDuinoDefsESP.h"
  static const int spiClk = 8000000; // 8 MHz
  SPIClass * vspi = NULL;
  // TODO Break MAX out onto 2nd SPI peripheral
  #define ARCH_DEFINED
#endif

#if defined HAS_SDIO // Setup SD
  #include <STM32SD.h>
  #ifndef SD_DETECT_PIN
    #define SD_DETECT_PIN SD_DETECT_NONE
  #endif
  File sdLogFile;
#else
  #include <SdFat.h>
  SdFat sd;
  SdFile sdLogFile;
#endif

#ifndef ARCH_DEFINED
#error Unsupported core \ board combination
#endif

// uncommment the define that matches your diaplsy type
#define USE_SSD1306
//#define USE_SSD1331
//#define USE_SSD1351

#include <Adafruit_GFX.h>

#if defined USE_SSD1306
  #include <Adafruit_SSD1306.h>
  #define SCREEN_CHOSEN
  Adafruit_SSD1306 display1(OLED_DC, OLED_RESET, OLEDCS_1);
#endif

#if defined USE_SSD1331
  #include <Adafruit_SSD1331.h>
  #define SCREEN_CHOSEN
  Adafruit_SSD1331 display1(OLEDCS_1, OLED_DC, OLED_RESET);
#endif

#if defined USE_SSD1351
  #include <Adafruit_SSD1351.h>
  #define SCREEN_CHOSEN
  Adafruit_SSD1351 display1(128, 128, &SPI, OLEDCS_1, OLED_DC, OLED_RESET);
#endif

#ifndef SCREEN_CHOSEN
#error Please choose a screen type by uncommenting one choice only eg "#define USE_SSD1306"
#endif

#include "Macros.h"
#include "LRDuinoGFX.h"
#include <Fonts/FreeSansBoldOblique9pt7b.h>
#include <Fonts/FreeSansBoldOblique12pt7b.h>
#include <Fonts/FreeSansBoldOblique18pt7b.h>
#include <Fonts/FreeSansBoldOblique24pt7b.h>
#include <menu.h>
#include <menuIO/chainStream.h>
#include <menuIO/adafruitGfxOut.h>
#include <menuIO/serialIn.h>
#include <Buttons.h>
#include "td5comm.h"


using namespace Menu;

byte RegisterValues[] =    {0x90,  0x03,   0xFC,   0x7F,   0xC0,   0x7F,     0xFF,     0x80,     0x00,     0x00 };
String RegisterNames[] =   {"CR0", "CR1", "MASK", "CJHF", "CHLF", "LTHFTH", "LTHFTL", "LTLFTH", "LTLFTL", "CJTO"};
byte RegisterAddresses[] = {0x00,  0x01,   0x02,   0x03,   0x04,   0x05,     0x06,     0x07,     0x08,     0x09 };

Td5Comm td5; // setup ODBC object

// Button initialisation
Button btn_up(UPBUT, LOW);
Button btn_down(DOWNBUT, LOW);
Button btn_left(LEFTBUT, LOW);
Button btn_right(RIGHTBUT, LOW);
Button btn_enter(SELBUT, LOW);

#include "td5sensors.h"

// Insert code to read settings in here, and also set default states of sensors to hidden if hw is not present
// end settings reading section

uint8_t sensecount = 0;
uint8_t rotation = 3; // incremented by 1 with each button press - it's used to tell the drawdisplay functions which sensor data they should output.

// the follow variable is a long because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
unsigned long previousMillis = 0;        // will store last time the displays were updated
unsigned long OBDslowMillis = 0;
unsigned long OBDfastMillis = 0;
unsigned long menuMillis = 0;
unsigned long inptimeoutMillis = 0;

// MENUS
#define textScale 1
#define fontX 5
#define fontY 9

bool inMenu = false;   // if true then the menu should be output on display1
bool exitMenu = false;
bool dataLog = false;  // if true then we are writing data to SD
bool sd_present = false; // changes to false if an SD card is inserted at startup

result quitMenu() {
  inMenu = false;
  exitMenu = true;
  inptimeoutMillis = inptimeoutMillis - MENUTIMEOUT;
  return proceed;
}

MENU(setMenu,"Settings",doNothing,anyEvent,wrapStyle
  ,OP("Save Settings",doNothing,enterEvent)
  ,OP("Read Settings",doNothing,enterEvent)
  ,OP("Reset to Defaults",doNothing,enterEvent)
  ,EXIT("<Back")
);

MENU(ecuMenu,"ECU",doNothing,anyEvent,wrapStyle
  ,OP("Connect to ECU",initOBD,enterEvent)
  ,OP("Read Faults",doNothing,enterEvent)
  ,OP("Clear Faults",doNothing,enterEvent)
  ,EXIT("<Back")
);

TOGGLE(Sensors[0].hidden,sensor0Toggle, "Boost: ",getSensecount,enterEvent,wrapStyle//,doExit,enterEvent,noStyle
  ,VALUE("On",false,doNothing,noEvent)
  ,VALUE("Off",true,doNothing,noEvent)
);
TOGGLE(Sensors[1].hidden,sensor1Toggle, "Tbox Temp: ",getSensecount,enterEvent,wrapStyle//,doExit,enterEvent,noStyle
  ,VALUE("On",false,doNothing,noEvent)
  ,VALUE("Off",true,doNothing,noEvent)
);
TOGGLE(Sensors[2].hidden,sensor2Toggle, "EGT: ",getSensecount,enterEvent,wrapStyle//,doExit,enterEvent,noStyle
  ,VALUE("On",false,doNothing,noEvent)
  ,VALUE("Off",true,doNothing,noEvent)
);
TOGGLE(Sensors[3].hidden,sensor3Toggle, "Oil Press/Tmp: ",getSensecount,enterEvent,wrapStyle//,doExit,enterEvent,noStyle
  ,VALUE("On",false,doNothing,noEvent)
  ,VALUE("Off",true,doNothing,noEvent)
);
TOGGLE(Sensors[5].hidden,sensor5Toggle, "Coolent Lev: ",getSensecount,enterEvent,wrapStyle//,doExit,enterEvent,noStyle
  ,VALUE("On",false,doNothing,noEvent)
  ,VALUE("Off",true,doNothing,noEvent)
);
TOGGLE(Sensors[6].hidden,sensor6Toggle, "RPM (OBD): ",getSensecount,enterEvent,wrapStyle//,doExit,enterEvent,noStyle
  ,VALUE("On",false,doNothing,noEvent)
  ,VALUE("Off",true,doNothing,noEvent)
);
TOGGLE(Sensors[7].hidden,sensor7Toggle, "Speed (OBD): ",getSensecount,enterEvent,wrapStyle//,doExit,enterEvent,noStyle
  ,VALUE("On",false,doNothing,noEvent)
  ,VALUE("Off",true,doNothing,noEvent)
);
TOGGLE(Sensors[8].hidden,sensor8Toggle, "ECT (OBD): ",getSensecount,enterEvent,wrapStyle//,doExit,enterEvent,noStyle
  ,VALUE("On",false,doNothing,noEvent)
  ,VALUE("Off",true,doNothing,noEvent)
);
TOGGLE(Sensors[9].hidden,sensor9Toggle, "BtV (OBD): ",getSensecount,enterEvent,wrapStyle//,doExit,enterEvent,noStyle
  ,VALUE("On",false,doNothing,noEvent)
  ,VALUE("Off",true,doNothing,noEvent)
);
TOGGLE(Sensors[10].hidden,sensor10Toggle, "InT (OBD): ",getSensecount,enterEvent,wrapStyle//,doExit,enterEvent,noStyle
  ,VALUE("On",false,doNothing,noEvent)
  ,VALUE("Off",true,doNothing,noEvent)
);
TOGGLE(Sensors[11].hidden,sensor11Toggle, "FlT (OBD): ",getSensecount,enterEvent,wrapStyle//,doExit,enterEvent,noStyle
  ,VALUE("On",false,doNothing,noEvent)
  ,VALUE("Off",true,doNothing,noEvent)
);
TOGGLE(Sensors[12].hidden,sensor12Toggle, "AAP (OBD): ",getSensecount,enterEvent,wrapStyle//,doExit,enterEvent,noStyle
  ,VALUE("On",false,doNothing,noEvent)
  ,VALUE("Off",true,doNothing,noEvent)
);
MENU(togsensMenu,"En/Dis(able) Sensors",doNothing,anyEvent,wrapStyle
  ,SUBMENU(sensor0Toggle)
  ,SUBMENU(sensor1Toggle)
  ,SUBMENU(sensor2Toggle)
  ,SUBMENU(sensor3Toggle)
  // No sensor4 because this is paired with 3
  ,SUBMENU(sensor5Toggle)
  ,SUBMENU(sensor6Toggle)
  ,SUBMENU(sensor7Toggle)
  ,SUBMENU(sensor8Toggle)
  ,SUBMENU(sensor9Toggle)
  ,SUBMENU(sensor10Toggle)
  ,SUBMENU(sensor11Toggle) 
  ,EXIT("<Back")
);

MENU(lowarnMenu,"Low Warnings",doNothing,anyEvent,wrapStyle
    ,FIELD(Sensors[3].sensewarnlowvals,"Oil Pressure","psi",Sensors[3].senseminvals,Sensors[3].sensemaxvals,10,1,doNothing,noEvent,wrapStyle)
  ,EXIT("<Back")
);

MENU(hiwarnMenu,"High Warnings",doNothing,anyEvent,wrapStyle
    ,FIELD(Sensors[0].sensewarnhivals,"Boost","psi",Sensors[0].senseminvals,Sensors[0].sensemaxvals,10,1,doNothing,noEvent,wrapStyle)
    ,FIELD(Sensors[1].sensewarnhivals,"Tbox Temp","C",Sensors[1].senseminvals,Sensors[1].sensemaxvals,10,1,doNothing,noEvent,wrapStyle)
    ,FIELD(Sensors[2].sensewarnhivals,"EGT","C",Sensors[2].senseminvals,Sensors[2].sensemaxvals,50,10,doNothing,noEvent,wrapStyle)
    ,FIELD(Sensors[3].sensewarnhivals,"Oil Pressure","psi",Sensors[3].senseminvals,Sensors[3].sensemaxvals,10,1,doNothing,noEvent,wrapStyle)
    ,FIELD(Sensors[4].sensewarnhivals,"Oil Temp","C",Sensors[4].senseminvals,Sensors[4].sensemaxvals,10,1,doNothing,noEvent,wrapStyle)
    ,FIELD(Sensors[8].sensewarnhivals,"Coolant Temp","C",Sensors[8].senseminvals,Sensors[8].sensemaxvals,10,1,doNothing,noEvent,wrapStyle) 
  ,EXIT("<Back")
);

MENU(sensorMenu,"Sensors",doNothing,anyEvent,wrapStyle
  ,SUBMENU(togsensMenu)
  ,OP("Change Order",doNothing,enterEvent)
  ,SUBMENU(lowarnMenu)
  ,SUBMENU(hiwarnMenu)
  ,EXIT("<Back")
);

TOGGLE(dataLog, dataLogging, "Datalogging: ",toggleDatalog,enterEvent,wrapStyle//,doExit,enterEvent,noStyle
  ,VALUE("On",true,doNothing,noEvent)
  ,VALUE("Off",false,doNothing,noEvent)
);

MENU(mainMenu,"Main menu",doNothing,noEvent,wrapStyle
  ,SUBMENU(sensorMenu)
  ,SUBMENU(dataLogging)
  ,SUBMENU(ecuMenu)
  ,SUBMENU(setMenu)
  ,OP("<Quit Menu",quitMenu,enterEvent)
  //,EXIT("<Quit Menu")
);

const colorDef<uint16_t> colors[] MEMMODE={
  {{BLACK,WHITE},{BLACK,WHITE,WHITE}},//bgColor
  {{WHITE,BLACK},{WHITE,BLACK,BLACK}},//fgColor
  {{WHITE,BLACK},{WHITE,BLACK,BLACK}},//valColor
  {{WHITE,BLACK},{WHITE,BLACK,BLACK}},//unitColor
  {{WHITE,BLACK},{BLACK,BLACK,BLACK}},//cursorColor
  {{WHITE,BLACK},{BLACK,WHITE,WHITE}},//titleColor
};

MENU_OUTPUTS(out,MAX_DEPTH
//  ,SERIAL_OUT(Serial)
  ,ADAGFX_OUT(display1,colors,fontX,fontY,{0,0,128/fontX,64/fontY})
  ,NONE//must have 2 items at least
);

serialIn in(Serial);
NAVROOT(nav,mainMenu,MAX_DEPTH,in,out);
// END MENUS

void setup()   {
  //start serial connection
  //Serial.begin(57600);  //uncomment to send serial debug info

  #if defined ARDUINO_ARCH_ESP32
    vspi = new SPIClass(VSPI);
    vspi->begin();
    analogReadResolution(12); //12 bits
    analogSetAttenuation(ADC_11db);  //For all pins  = 0-3.3v
  #endif

  #if defined ARDUINO_ARCH_STM32
    #if defined BOARD_maple_mini || defined BOARD_generic_stm32f103c
    // do nothing
    #else
    analogReadResolution(12); //12 bits
    #endif
  #endif

  // Pin setup
  pinMode (OLEDCS_1, OUTPUT);
  digitalWrite(OLEDCS_1, HIGH);
  pinMode (MAX_CS, OUTPUT);
  digitalWrite(MAX_CS, HIGH);
  pinMode (SD_CS, OUTPUT);
  digitalWrite(SD_CS, HIGH);

  #if defined ARDUINO_BLACK_F407VE || defined ARDUINO_BLACK_F407ZE || defined ARDUINO_BLACK_F407ZG
    pinMode (PA0, INPUT_PULLDOWN); //Button K_UP
  #endif

  MAXInitializeChannel(MAX_CS); // Init the MAX31856 
  display1.begin(8000000); //construct our displays
  SCREEN_CLEAR();   // clears the screen and buffer
  SCREEN_DISPLAY(); //output to the screen to avoid adafruit logo

  // Ensure #define ENABLE_SPI_TRANSACTIONS 1 is set in SdFatConfig.h
  #if defined HAS_SDIO
    if (!SD.begin(SD_DETECT_PIN))        
  #else
    if (!sd.begin(SD_CS, SD_SCK_MHZ(8)))
  #endif
  {
    display1.fillScreen(BLACK);
    display1.setTextColor(RED);
    display1.setTextSize(1);
    display1.setCursor(0, 0);
    display1.println("SD init failed.");
    SCREEN_DISPLAY();
    delay(200);
    display1.fillScreen(BLACK);
    sd_present = false;
  }
  else
  {
    sd_present = true;    
  }
  initOBD(); // this also fires getSensecount()

} // End Setup

void loop() {
  unsigned long currentMillis = millis(); //store the time

  // USER INTERACTION
  if((currentMillis - inptimeoutMillis > MENUTIMEOUT) && (inMenu==true)) {  //timeout the menu 
  inMenu=false;
    SCREEN_CLEAR();
  }
  
  if(exitMenu == true) {  //clear the menu if we exited
    exitMenu=false;
    SCREEN_CLEAR();
  }
 
  if ((!inMenu) && (btn_enter.sense() == buttons_held)) {
    inMenu=true; // turn the menu on if we have a long press on the enter button
    inptimeoutMillis = currentMillis;
  }
  if (inMenu) {
    if (currentMillis - menuMillis > BUT_DELAY) {
      menuMillis = currentMillis;
      if (btn_up.sense() == buttons_debounce) {
        nav.doNav(upCmd); // navigate up
        inptimeoutMillis = currentMillis;
      } else if (btn_down.sense() == buttons_debounce) {
        nav.doNav(downCmd); // navigate down
        inptimeoutMillis = currentMillis;
      } else if (btn_enter.sense() == buttons_debounce) {
        nav.doNav(enterCmd); // do current command
        inptimeoutMillis = currentMillis;
      }
      //nav.active().dirty=true;//for a menu
      //nav.navFocus->dirty=true;//should invalidate also full screen fields assert(nav.navFocus!=NULL)
      nav.doOutput(); //need to use this as .poll also processes input
      SCREEN_DISPLAY();
    }
  }
  // left rotation requested
  if (btn_left.sense() == buttons_debounce) { 
    if (currentMillis - previousMillis > BUT_DELAY) {
      rotation = rotation + 1; // rotate the screens if the button was pressed
      display1.fillScreen(BLACK);
      previousMillis = previousMillis - (INTERVAL + 1); // force an update of the screens.
      if (sensecount < NUM_DISPLAYS) {
        if (rotation == NUM_DISPLAYS) { // if we have less than 8 sensors, keep rotating until we hit the screen count
          rotation = 0;
        }
      } else {
        if (rotation == sensecount) { // otherwise rotate until we hit the last sensor
          rotation = 0;
        }
      }
    }
  }
  
  // right rotation requested
  if (btn_right.sense() == buttons_debounce) { 
    if (currentMillis - previousMillis > BUT_DELAY) {
      rotation = rotation - 1; // rotate the screens if the button was pressed
      display1.fillScreen(BLACK);
      previousMillis = previousMillis - (INTERVAL + 1); // force an update of the screens.
      if (sensecount < NUM_DISPLAYS) {
        if (rotation == 0) { // if we have less than 8 sensors, keep rotating until we hit the screen count
          rotation = NUM_DISPLAYS;
        }
      } else {
        if (rotation == 0) { // otherwise rotate until we hit the last sensor
          rotation = sensecount;
        }
      }
    }
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
      }
    }
    
    // ********NEW*********
  for(uint8_t currentsensor=0; currentsensor < totalsensors; currentsensor++ ){
      if (Sensors[currentsensor].senseactive) {
        Sensors[currentsensor].senselastvals = Sensors[currentsensor].sensevals; // stash the previous value
        switch(Sensors[currentsensor].sensetype) { // switch based upon the sensor type
          case ERR2081  :
            Sensors[currentsensor].sensevals = readERR2081(Sensors[currentsensor].sensepin, currentsensor);
            break; //optional
          case KTYPE  :
            Sensors[currentsensor].sensevals = readMAX(currentsensor); // no pin supplied since this is over SPI
            break; //optional
          case BOOST3BAR  :
            Sensors[currentsensor].sensevals = readBoost(Sensors[currentsensor].sensepin, currentsensor);
            break; //optional
          case CH100PSI  :
            Sensors[currentsensor].sensevals = readPress(Sensors[currentsensor].sensepin, currentsensor);
            break; //optional
          case EARTHSW  :
            Sensors[currentsensor].sensevals = readCoolantLevel(Sensors[currentsensor].sensepin, currentsensor);
            break; //optional
          case OBD  :
            if (td5.ecuIsConnected()) {
              switch(Sensors[currentsensor].sensepin) { // if it's OBD switch based upon the PID
                case OBDRPM  :
                  if(td5.getPid(&pidRPM) > 0) {
                  Sensors[currentsensor].sensevals = pidRPM.getlValue(); // RPM
                  }
                  break;
                case OBDSPD  :
                  if(td5.getPid(&pidVehicleSpeed) > 0) {
                    Sensors[currentsensor].sensevals = pidVehicleSpeed.getbValue(0); // Speed
                  }
                  break;
                case OBDECT  :
                  if(td5.getPid(&pidTemperatures) > 0) {
                    Sensors[currentsensor].sensevals = pidTemperatures.getfValue(0); // Coolant Temp
                  }
                  break;
                case OBDBTV  :
                  if(td5.getPid(&pidBatteryVoltage) > 0) {
                    Sensors[currentsensor].sensevals = pidBatteryVoltage.getfValue(); // Battery Voltage
                  }
                  break;
                case OBDINT  :
                  if(td5.getPid(&pidTemperatures) > 0) {
                    Sensors[currentsensor].sensevals = pidTemperatures.getfValue(1); // Inlet Temp
                  }
                  break;
                case OBDFLT  :
                  if(td5.getPid(&pidTemperatures) > 0) {
                    Sensors[currentsensor].sensevals = pidTemperatures.getfValue(3); // Fuel Temp
                  }
                  break;
                case OBDAAP  :
                  if(td5.getPid(&pidAmbientPressure) > 0) {
                    Sensors[currentsensor].sensevals = pidAmbientPressure.getfValue(1); // AAP
                  }
                  break;
              } // OBD PID switch
            } // if ECU is connected
            break; //optional
        } // Sensor type switch
        processPeak(currentsensor);  // update the highest value if it's been exceeded - useful for graphs.
        audibleWARN(currentsensor);  // issue tones if there's an issue
      }
  }

    if(dataLog == true) {
      writeDatalogline();  // write out the last readings if we're logging
    }
  
    // DRAW DISPLAYS
    if (!inMenu) {
      drawDISPLAY(display1, 1);
    }
  }
} // Void Loop()
