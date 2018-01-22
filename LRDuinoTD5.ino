// LRDuino by Ben Anderson
// Version 0.06  (STM32 Only)

#include "LRDuinoDefs.h"
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <SdFat.h>
#include "LRDuinoGFX.h"
#include <Fonts/FreeSansBoldOblique12pt7b.h>
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
byte RegisterAddresses[] = {0x00,  0x01,   0x02,   0x03,   0x04,   0x04,     0x06,     0x07,     0x08,     0x09 };

Td5Comm td5;

SdFat sd;
SdFile sdLogFile;

//HARDWARE SPI
Adafruit_SSD1306 display1(OLED_DC, OLED_RESET, OLEDCS_1);

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

// Button initialisation
Button btn_up(UPBUT, LOW);
Button btn_down(DOWNBUT, LOW);
Button btn_left(LEFTBUT, LOW);
Button btn_right(RIGHTBUT, LOW);
Button btn_enter(SELBUT, LOW);

// This is all the parameters and variables for our sensors

typedef struct
{
  bool senseactive;
  bool master;
  uint8_t slaveID;
  uint8_t senseorder;
  bool warnstatus;
  uint8_t sensefault;
  const unsigned char* senseglyphs;
  int sensevals;
  const uint8_t senseunits;
  const int sensemaxvals;
  const int8_t senseminvals;
  int sensepeakvals;
  int sensewarnhivals;
  int sensewarnlowvals;
  const char sensename[13];
} SingleSensor;

SingleSensor Sensors[16] = {
 //active  master slaveID senseorder	warnstatus    sensefault senseglyphs sensevals  units maxvals minvals peakvals warnhivals warnlovals
  {true,   true,  99,     0,			false,        0,         trbBMP,     0,         1,    32,     0,      0,       29,        -999,	"Boost"}, 		// Boost
  {true,   true,  99,     0,			false,        0,         tboxBMP,    0,         0,    150,    -40,    -40,     140,       -999,	"Tbox Temp"}, 	// Transfer Box Temp
  {true,   true,  99,     0,			false,        0,         egtBMP,     0,         0,    900,    -40,    -40,     750,       -999,	"EGT"}, 		// EGT
  {true,   true,  4,      0,			false,        0,         eopBMP,     0,         1,    72,     0,      0,       60,        20,	"Oil Pressure"},// Oil Pressure
  {true,   false, 99,     0,			false,        0,         eotBMP,     0,         0,    150,    -40,    -40,     100,       -999,	"Oil Temp"}, 	// Oil Temp
  {true,   true,  11,     0,			false,        0,         coollev,    0,         2,    1,      0,      1,       999,       1,	"Coolant Lvl"}, // Coolant Level
  {false,   true,  7,      0,			false,        0,         D2a0,       0,         3,    45,     -45,    0,       30,        -30,	"Roll"},  		// Vehicle Roll
  {false,   false, 99,     0,			false,        0,         D2p0,       0,         3,    60,     -60,    0,       45,        -45,	"Pitch"},  		// Vehicle Pitch
  {false,   true,  99,     0,			false,        0,         compass,    0,         3,    360,    0,      0,       999,       -999,	"Compass"}, 	// Magnetometer
  {true,   true,  99,     0,			false,        0,         Gauge,      0,         4,    4500,   0,      0,       4500,      600,	"RPM (OBD)"},  	// RPM
  {true,   true,  99,     0,			false,        0,         Gauge,      0,         5,    100,    -30,    0,       100,       -30,	"Speed (OBD)"}, // Roadspeed
  {true,   false,  99,     0,			false,        0,         cooltmp,    0,         0,    130,    -30,    0,       100,       -999,	"ECT (OBD)"},   // Coolant
  {true,   true,  99,     0,			false,        0,         OBDII,   	 0,         7,    16,     0,	  0,       15,        11,	"BtV (OBD)"},   // Battery Voltage
  {false,   true,  99,     0,			true,        0,         OBDII,   	 0,         0,    100,    -40,	  0,       50,        -999,	"InT (OBD)"},   // Inlet Temperature
  {false,   true,  99,     0,			true,        0,         OBDII,   	 0,         0,    100,    -40,	  0,       75,        -999,	"FlT (OBD)"},   // Fuel Temperature
  {false,   true,  99,     0,			true,        0,         OBDII,   	 0,         1,    20,     0,	  0,       16,        12,	"AAP (OBD)"}    // Ambient Pressure
};

uint8_t sensecount = 0;
const uint8_t totalsensors = 16; //this is the actual number of definitions above
uint8_t rotation = 0; // incremented by 1 with each button press - it's used to tell the drawdisplay functions which sensor data they should output.

// the follow variable is a long because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
unsigned long previousMillis = 0;        // will store last time the displays were updated
unsigned long OBDslowMillis = 0;
unsigned long OBDfastMillis = 0;
unsigned long menuMillis = 0;
unsigned long inptimeoutMillis = 0;

//int atmos = 215;                //somewhere to store our startup atmospheric pressure - unused at present

// MENUS
#define textScale 1
#define fontX 5
#define fontY 9

bool inMenu = false;   // if true then the menu should be output on display1
bool dataLog = false;  // if true then we are writing data to SD
bool sd_present = false; // changes to false if an SD card is inserted at startup

result quitMenu() {
  inMenu = false;
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

TOGGLE(Sensors[0].senseactive,sensor0Toggle, "Boost: ",getSensecount,enterEvent,wrapStyle//,doExit,enterEvent,noStyle
  ,VALUE("On",true,doNothing,noEvent)
  ,VALUE("Off",false,doNothing,noEvent)
);
TOGGLE(Sensors[1].senseactive,sensor1Toggle, "Tbox Temp: ",getSensecount,enterEvent,wrapStyle//,doExit,enterEvent,noStyle
  ,VALUE("On",true,doNothing,noEvent)
  ,VALUE("Off",false,doNothing,noEvent)
);
TOGGLE(Sensors[2].senseactive,sensor2Toggle, "EGT: ",getSensecount,enterEvent,wrapStyle//,doExit,enterEvent,noStyle
  ,VALUE("On",true,doNothing,noEvent)
  ,VALUE("Off",false,doNothing,noEvent)
);
TOGGLE(Sensors[3].senseactive,sensor3Toggle, "Oil Press/Tmp: ",getSensecount,enterEvent,wrapStyle//,doExit,enterEvent,noStyle
  ,VALUE("On",true,doNothing,noEvent)
  ,VALUE("Off",false,doNothing,noEvent)
);
TOGGLE(Sensors[5].senseactive,sensor5Toggle, "Coolent Lev: ",getSensecount,enterEvent,wrapStyle//,doExit,enterEvent,noStyle
  ,VALUE("On",true,doNothing,noEvent)
  ,VALUE("Off",false,doNothing,noEvent)
);
TOGGLE(Sensors[6].senseactive,sensor6Toggle, "Pitch/Roll: ",getSensecount,enterEvent,wrapStyle//,doExit,enterEvent,noStyle
  ,VALUE("On",true,doNothing,noEvent)
  ,VALUE("Off",false,doNothing,noEvent)
);
TOGGLE(Sensors[8].senseactive,sensor8Toggle, "Compass: ",getSensecount,enterEvent,wrapStyle//,doExit,enterEvent,noStyle
  ,VALUE("On",true,doNothing,noEvent)
  ,VALUE("Off",false,doNothing,noEvent)
);
TOGGLE(Sensors[9].senseactive,sensor9Toggle, "RPM (OBD): ",getSensecount,enterEvent,wrapStyle//,doExit,enterEvent,noStyle
  ,VALUE("On",true,doNothing,noEvent)
  ,VALUE("Off",false,doNothing,noEvent)
);
TOGGLE(Sensors[10].senseactive,sensor10Toggle, "Speed (OBD): ",getSensecount,enterEvent,wrapStyle//,doExit,enterEvent,noStyle
  ,VALUE("On",true,doNothing,noEvent)
  ,VALUE("Off",false,doNothing,noEvent)
);
TOGGLE(Sensors[11].senseactive,sensor11Toggle, "ECT (OBD): ",getSensecount,enterEvent,wrapStyle//,doExit,enterEvent,noStyle
  ,VALUE("On",true,doNothing,noEvent)
  ,VALUE("Off",false,doNothing,noEvent)
);
TOGGLE(Sensors[12].senseactive,sensor12Toggle, "BtV (OBD): ",getSensecount,enterEvent,wrapStyle//,doExit,enterEvent,noStyle
  ,VALUE("On",true,doNothing,noEvent)
  ,VALUE("Off",false,doNothing,noEvent)
);
TOGGLE(Sensors[13].senseactive,sensor13Toggle, "InT (OBD): ",getSensecount,enterEvent,wrapStyle//,doExit,enterEvent,noStyle
  ,VALUE("On",true,doNothing,noEvent)
  ,VALUE("Off",false,doNothing,noEvent)
);
TOGGLE(Sensors[14].senseactive,sensor14Toggle, "FlT (OBD): ",getSensecount,enterEvent,wrapStyle//,doExit,enterEvent,noStyle
  ,VALUE("On",true,doNothing,noEvent)
  ,VALUE("Off",false,doNothing,noEvent)
);
TOGGLE(Sensors[15].senseactive,sensor15Toggle, "AAP (OBD): ",getSensecount,enterEvent,wrapStyle//,doExit,enterEvent,noStyle
  ,VALUE("On",true,doNothing,noEvent)
  ,VALUE("Off",false,doNothing,noEvent)
);
MENU(togsensMenu,"En/Dis(able) Sensors",doNothing,anyEvent,wrapStyle
	,SUBMENU(sensor0Toggle)
	,SUBMENU(sensor1Toggle)
	,SUBMENU(sensor2Toggle)
	,SUBMENU(sensor3Toggle)
	,SUBMENU(sensor5Toggle)
	,SUBMENU(sensor6Toggle)
	,SUBMENU(sensor8Toggle)
	,SUBMENU(sensor9Toggle)
	,SUBMENU(sensor10Toggle)
	,SUBMENU(sensor11Toggle)
	,SUBMENU(sensor12Toggle)
	,SUBMENU(sensor13Toggle)
	,SUBMENU(sensor14Toggle)
	,SUBMENU(sensor15Toggle)	
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
    ,FIELD(Sensors[11].sensewarnhivals,"Coolant Temp","C",Sensors[11].senseminvals,Sensors[11].sensemaxvals,10,1,doNothing,noEvent,wrapStyle)	
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
  //Serial.begin(9600);  //uncomment to send serial debug info

  // Pin setup
  pinMode (OLEDCS_1, OUTPUT);
  digitalWrite(OLEDCS_1, HIGH);
  pinMode (MAX_CS, OUTPUT);
  digitalWrite(MAX_CS, HIGH);
  pinMode (SD_CS, OUTPUT);
  digitalWrite(SD_CS, HIGH);
  
  MAXInitializeChannel(MAX_CS); // Init the MAX31856 

  display1.begin(SSD1306_SWITCHCAPVCC, SSD1306_I2C_ADDRESS, true); //construct our displays

  display1.clearDisplay();   // clears the screen and buffer

  display1.display(); //output to the screen to avoid adafruit logo

  // Ensure #define ENABLE_SPI_TRANSACTIONS 1 is set in SdFatConfig.h
  if (!sd.begin(SD_CS, SD_SCK_MHZ(8)))
  {
	  
	display1.setTextColor(WHITE);
	display1.setTextSize(1);
    display1.setCursor(0, 0); 
    display1.println("SD init failed...   ");
	display1.display();
	delay(1000);
    sd_present = false;
  }
  else
  {
    sd_present = true;    
  }
  
  // read our boost sensor rawADC value since at this point it should be atmospheric pressure...
  //atmos = readBoost(0,0);  // not actually used at this point so could be rmeoved

  initOBD(); // this also fires getSensecount()
  
  // set up our analogue inputs on STM32
  for (int x = 7; x < 11; x++) {
    //pinMode(x, INPUT_ANALOG);
  }
}

void initOBD(void) {
	td5.init();
	if(!td5.connectToEcu(false)) {	
		disableOBDSensors();
	} else {
 		for (uint8_t i=9; i < totalsensors; i++) {
			if (Sensors[i].warnstatus == true) { // already disabled so set warnstatus to true - we'll use this as temp storage so we don't re-enable if OBD gets re-initialised
				Sensors[i].senseactive = false; // should already be false but no harm in making sure
				Sensors[i].warnstatus = false;
			} else {
				Sensors[i].senseactive = true;
				Sensors[i].warnstatus = false;
			}
		}
		getSensecount();
	}
	
}

void disableOBDSensors(void) {
		for (uint8_t i=9; i < totalsensors; i++) {
			if (Sensors[i].senseactive == false) { // already disabled so set warnstatus to true - we'll use this as temp storage so we don't re-enable if OBD gets re-initialised
				Sensors[i].senseactive = false;
				Sensors[i].warnstatus = true;
			} else {
				Sensors[i].senseactive = false;
				Sensors[i].warnstatus = false;
			}
		}
	getSensecount();
}

void getSensecount(void) {
	sensecount=0;
	for (uint8_t thisSensor = 0; thisSensor < totalsensors; thisSensor++) {
		if (Sensors[thisSensor].senseactive == true && Sensors[thisSensor].master == true) { // don't count slaves
			sensecount++;
		}
	}
}

void toggleDatalog(void) {
	// do some SD stuff.
	if(sd_present && dataLog) {
		

		if(sd_present) {	
			char file_name[] = "data_00.csv";
			// if name exists, create new filename
			for (int i=0; i<100; i++) {
				file_name[5] = i/10 + '0';
				file_name[6] = i%10 + '0';
				if (sdLogFile.open(file_name, O_CREAT | O_EXCL | O_WRITE)) {
					break;
				}
			}

			if (sdLogFile.isOpen()) {
				sdLogFile.println("LRDuino data Log file");sdLogFile.println();
				sdLogFile.print(Sensors[0].sensename);sdLogFile.print(";");			
				sdLogFile.print(Sensors[1].sensename);sdLogFile.print(";");
				sdLogFile.print(Sensors[2].sensename);sdLogFile.print(";");
				sdLogFile.print(Sensors[3].sensename);sdLogFile.print(";");
				sdLogFile.print(Sensors[4].sensename);sdLogFile.print(";");
				sdLogFile.print(Sensors[5].sensename);sdLogFile.print(";");
				sdLogFile.print(Sensors[6].sensename);sdLogFile.print(";");
				sdLogFile.print(Sensors[7].sensename);sdLogFile.print(";");
				sdLogFile.print(Sensors[8].sensename);sdLogFile.print(";");
				sdLogFile.print(Sensors[9].sensename);sdLogFile.print(";");
				sdLogFile.print(Sensors[10].sensename);sdLogFile.print(";");
				sdLogFile.print(Sensors[11].sensename);sdLogFile.println(";");
//				sdLogFile.print(Sensors[12].sensename);sdLogFile.print(";");
//				sdLogFile.print(Sensors[13].sensename);sdLogFile.println(";");
			} else { //file open failed
				dataLog = false;
				Serial.println("failed to open file");
			}
		}
	
	// open the file and write the header
	} else if (sd_present && !dataLog) {
	// close the file
		if (sdLogFile.isOpen())	{ 
			sdLogFile.close();
		}
	}
}

void writeDatalogline(void) {
	// write a line to the datalog
	if (sdLogFile.isOpen()) { 
		sdLogFile.print(Sensors[0].sensevals);sdLogFile.print(";");			
		sdLogFile.print(Sensors[1].sensevals);sdLogFile.print(";");
		sdLogFile.print(Sensors[2].sensevals);sdLogFile.print(";");
		sdLogFile.print(Sensors[3].sensevals);sdLogFile.print(";");
		sdLogFile.print(Sensors[4].sensevals);sdLogFile.print(";");
		sdLogFile.print(Sensors[5].sensevals);sdLogFile.print(";");
		sdLogFile.print(Sensors[6].sensevals);sdLogFile.print(";");
		sdLogFile.print(Sensors[7].sensevals);sdLogFile.print(";");
		sdLogFile.print(Sensors[8].sensevals);sdLogFile.print(";");
		sdLogFile.print(Sensors[9].sensevals);sdLogFile.print(";");
		sdLogFile.print(Sensors[10].sensevals);sdLogFile.print(";");
		sdLogFile.print(Sensors[11].sensevals);sdLogFile.println(";");
//		sdLogFile.print(Sensors[12].sensevals);sdLogFile.print(";");
//		sdLogFile.print(Sensors[13].sensevals);sdLogFile.println(";");
	} 
}

void loop() {
  unsigned long currentMillis = millis(); //store the time

  // USER INTERACTION
 
	if(currentMillis - inptimeoutMillis > MENUTIMEOUT) {  //timeout the menu 
		inMenu=false;
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
			nav.active().dirty=true;//for a menu
			nav.navFocus->dirty=true;//should invalidate also full screen fields assert(nav.navFocus!=NULL)
			//nav.poll();//do serial input
			nav.doOutput(); //need to use this as .poll also processes input (using the fake Serial stream == compilation failure)
			display1.display();
			display1.clearDisplay();	
		}
	}
  // left rotation requested
  if (btn_left.sense() == buttons_debounce) { 
    
	if (currentMillis - previousMillis > BUT_DELAY) {
	
		rotation = rotation + 1; // rotate the screens if the button was pressed
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
    // save the last time we updated
    previousMillis = currentMillis;

  if(td5.ecuIsConnected())
  {
    // keep ecu alive
    if(td5.getLastReceivedPidElapsedTime() > KEEP_ALIVE_TIME)
    {
      td5.getPid(&pidKeepAlive);  
    }

    // shutdown in case of too many frames lost
    if (td5.getConsecutiveLostFrames() > 3)
    {
		disableOBDSensors();
		td5.disconnectFromEcu();
    }
  }
	
    // SENSOR READING

    if (Sensors[0].senseactive) {
      Sensors[0].sensevals = readBoost(A0, 0); // read boost off A0 and store at index 0
      processPeak(0); // TURBO
      audibleWARN(0);
    }

    if (Sensors[1].senseactive) {
      Sensors[1].sensevals = readERR2081(A1, 1); // read A1, currently the Gearbox oil temp sensor
      processPeak(1); // TBOX OIL TEMP
      audibleWARN(1);
    }

    if (Sensors[2].senseactive) {
      Sensors[2].sensevals = readMAX(2); //read EGT from the Max31856
      processPeak(2); // EGT
      audibleWARN(2);
    }

    if (Sensors[3].senseactive) {
      Sensors[3].sensevals = readPress(A2, 3); // placeholder at the moment but should be very similar to the boost reading if a cheap pressure sensor is used (ie one which returns a linear voltage 0-5v based on presure)
      processPeak(3); // OIL PRESSURE
      audibleWARN(3);
    }

    if (Sensors[4].senseactive) {
      Sensors[4].sensevals = readERR2081(A3, 4); // read A7, store at index 4 currently the Engine oil temp sensor
      processPeak(4); // OIL TEMP
      audibleWARN(4);
    }

    if (Sensors[5].senseactive) {
      Sensors[5].sensevals = readCoolantLevel(A4, 5); // read A6, to check if coolant level is low
      audibleWARN(5);
      //processPeak(5); // Coolant Level - no need to set a max as this is boolean
    }

    if (Sensors[6].senseactive) {

    }

    if (Sensors[7].senseactive) {

    }

    if (Sensors[8].senseactive) {

    }

    if (Sensors[9].senseactive) {
		if (td5.ecuIsConnected()) {
			if(td5.getPid(&pidRPM) > 0) {
				Sensors[9].sensevals = pidRPM.getlValue(); // RPM
			}
		}
    }
  
   	if (Sensors[10].senseactive) {
		if (td5.ecuIsConnected()) {
			if(td5.getPid(&pidVehicleSpeed) > 0) {			
				Sensors[10].sensevals = pidVehicleSpeed.getbValue(0); // Speed
			}
		}
	} 
		
  	if (Sensors[11].senseactive) {
		if (td5.ecuIsConnected()) {
			if(td5.getPid(&pidTemperatures) > 0) {
				Sensors[11].sensevals = pidTemperatures.getfValue(0); // Coolant Temp
			}
		}
	audibleWARN(11);
	} 	

  	if (Sensors[12].senseactive) {
		if (td5.ecuIsConnected()) {
			if(td5.getPid(&pidBatteryVoltage) > 0) {
				Sensors[12].sensevals = pidBatteryVoltage.getfValue(); // Battery Voltage
			}
		}
	audibleWARN(12);
	} 	

  	if (Sensors[13].senseactive) {
		if (td5.ecuIsConnected()) {
			if(td5.getPid(&pidTemperatures) > 0) {
				Sensors[13].sensevals = pidTemperatures.getfValue(1); // Inlet Temp
			}
		}
	audibleWARN(13);
	} 
	
  	if (Sensors[14].senseactive) {
		if (td5.ecuIsConnected()) {
			if(td5.getPid(&pidTemperatures) > 0) {
				Sensors[14].sensevals = pidTemperatures.getfValue(3); // Fuel Temp
			}
		}
	audibleWARN(14);
	}
	
  	if (Sensors[15].senseactive) {
		if (td5.ecuIsConnected()) {
			if(td5.getPid(&pidAmbientPressure) > 0) {
				Sensors[15].sensevals = pidAmbientPressure.getfValue(1); // AAP
			}
		}
	audibleWARN(15);
	} 

	if(dataLog == true) {
		writeDatalogline();  // write out the last readings if we're logging
	}
	
    // DRAW DISPLAYS
  
	if (!inMenu) {
		drawDISPLAY(display1, 1);
	}
  }
  
	// 500 millis interval
 	if (currentMillis - OBDfastMillis > OBDFAST) { // only read these sensors if 400 millis have passed
		// save the last time we updated
		OBDfastMillis = currentMillis;
		 

	}

	// 1000 Millis interval
	if (currentMillis - OBDslowMillis > OBDSLOW) { // only read these sensors if 600 millis have passed
		// save the last time we updated
		OBDslowMillis = currentMillis;

	}
  }

// 4 screens - use index values like this to rotate around the displays
// 1 2
// 4 3

// 6 screens - use index values like this to rotate around the displays
// 1 2 3
// 6 5 4

// 8 screens - use index values like this to rotate around the displays
// 1 2 3 4
// 8 7 6 5

void drawDISPLAY(Adafruit_SSD1306 &refDisp, uint8_t index) { // DISPLAY 1 is our Main guage display

  int8_t sensor0 = processRotation(index);
  
  if (sensor0 == -1) {
  // don't draw anything because there are less sensors than displays
  } else if (Sensors[sensor0].slaveID != 99) { // draw paired sensors
    drawSensor(0, 0, refDisp, sensor0, true);
    drawSensor(33, 0, refDisp, Sensors[sensor0].slaveID, true);
  } else if ((sensor0 == 20)) { // draw a bargraph
    drawSensor(0, 0, refDisp, sensor0, true); 
    drawBarGraph(refDisp, sensor0);
  } else {
	drawBIG(refDisp, sensor0);  
  }
refDisp.display();
refDisp.clearDisplay();
}

void drawSensor(uint8_t y, uint8_t x, Adafruit_SSD1306 &refDisp, uint8_t sensor, bool icons) {
  uint8_t xoffset = 0;
  String temp;
  int8_t rolltemp = 0;

  refDisp.setTextWrap(false);

  refDisp.setFont(&FreeSansBoldOblique12pt7b); //switch to a nice ttf font 12x7
  drawItem(46 + x, y + 9 + 15, getValIfNoErr(sensor), 1, refDisp); // x should only be given a value if we are not showing icons (eg for the compass display)

  temp = getValIfNoErr(sensor);
  xoffset = (temp.length() * 13) + 5 ; // work out width of the characters so we can move the cursor to the correct position to display our units symbol

  refDisp.setFont(); // switch to small standard font
  drawItem(46 + x + xoffset, y + 9, getUnits(sensor), 1, refDisp);

  if (sensor == 6) { // INCLINOMETER ONLY (ANIMATED)

  } else {
    //ALL OTHER SENSORS
    if (icons) {
      refDisp.drawBitmap(0, y, Sensors[sensor].senseglyphs, 32, 32, WHITE);
    }
  }
  // DO sensor visual warnings
  if (processHiLo(sensor, true) && icons) {
    refDisp.drawBitmap(100, y + 4, triBMP, 24, 24, WHITE); //outut the warning triangle
  }
  if (processFaultIfSet(sensor) == 1 && icons) {
    refDisp.drawBitmap(100, y + 4, NoConn, 24, 24, WHITE); //output the disconnected sensor icon
  }
  refDisp.setFont(); //reset to basic font
}

void drawBIG(Adafruit_SSD1306 &refDisp, uint8_t sensor) {
  int xposition = 0;

  refDisp.setTextWrap(false);

  refDisp.setFont(&FreeSansBoldOblique12pt7b); //switch to a nice ttf font 12x7
  
  refDisp.drawBitmap(95, 34, Sensors[sensor].senseglyphs, 32, 32, WHITE); //draw the sensor icon
  
  xposition = 64-(((getUnits(sensor).length())*16)/2);  // work out our drawing location
  
  drawItem(xposition, 60, getUnits(sensor), 1, refDisp); // and draw the units
  
  refDisp.setFont(&FreeSansBoldOblique24pt7b); // change to large font
  
  xposition = 64-(((getValIfNoErr(sensor).length())*28)/2); // work out the drawing location
  
  drawItem(xposition, 34, getValIfNoErr(sensor), 1, refDisp); // draw the value

  refDisp.setFont(); //reset to basic font
  
  if (processHiLo(sensor, true)) {
    refDisp.drawBitmap(0, 38, triBMP, 24, 24, WHITE); //outut the warning triangle
  }
  if (processFaultIfSet(sensor) == 1) {
    refDisp.drawBitmap(0, 38, NoConn, 24, 24, WHITE); //output the disconnected sensor icon
  }
  
  
}

void drawBarGraph(Adafruit_SSD1306 &refDisp, uint8_t sensor) {
  int padding = 0;
  float scalerange = 0;
  int scaleposmin = 0;

  refDisp.drawLine(11, 52, 11, 54, WHITE); // draw our gauge and scale markings
  refDisp.drawLine(64, 52, 64, 54, WHITE);
  refDisp.drawLine(116, 52, 116, 54, WHITE);
  refDisp.drawRect(11, 42, 106, 10, WHITE); //Border of the bar chart
  if (Sensors[sensor].senseminvals < 0) { // Work out a positive range of values that we need to plot
    scaleposmin = Sensors[sensor].senseminvals * -1;
    scalerange = scaleposmin + Sensors[sensor].sensemaxvals;
  } else {
    scaleposmin = Sensors[sensor].senseminvals;
    scalerange = Sensors[sensor].sensemaxvals - scaleposmin;
  }
  refDisp.fillRect(14, 44, (100 / scalerange * (Sensors[sensor].sensevals + scaleposmin)), 6, WHITE); //Draws the bar depending on the sensor value
  refDisp.drawLine(13 + (100 / scalerange * (Sensors[sensor].sensepeakvals + scaleposmin)), 41, 13 + (100 / scalerange * (Sensors[sensor].sensepeakvals + scaleposmin)), 50, WHITE); // draw the peak value line;
  if (Sensors[sensor].sensevals < 100) { // adjust padding for the low value so it looks nice
    padding = 0;
  } else {
    padding = -4;
  }
  drawItem(8 + padding + (100 / scalerange * (Sensors[sensor].sensepeakvals + scaleposmin)), 33, String(Sensors[sensor].sensepeakvals), 1, refDisp); // set cursor with padding & write the peak val
  drawItem(8, 57, String(Sensors[sensor].senseminvals), 1, refDisp); // draw the minumum value
  refDisp.setCursor(58, 57);
  if (Sensors[sensor].senseminvals < 100) { // adjust padding for the low value so it looks nice
    padding = 8;
  } else {
    padding = 0;
  }
  refDisp.println(String(static_cast<int>(((Sensors[sensor].sensemaxvals - Sensors[sensor].senseminvals) / 2) - scaleposmin))); // draw the midpoint value
  if (Sensors[sensor].sensemaxvals < 100) { // adjust padding for the high value so it looks nice/doesnt wrap off screen
    padding = 10;
  } else {
    padding = 5;
  }
  drawItem(100 + padding, 57, String(Sensors[sensor].sensemaxvals), 1, refDisp);
}

void drawItem(int x, int y, String token, int txt_size, Adafruit_SSD1306 &refDisp) {
  refDisp.setCursor(x, y);
  refDisp.setTextColor(WHITE);
  refDisp.setTextSize(txt_size);
  refDisp.print(token);
  refDisp.setTextSize(1); // Back to default text size
}


bool processHiLo(uint8_t sensor, bool toggle) {
  // this function toggles a an error flag if the current sensor is above it's high warning parameter or below it's low warning paramater - since the display is redrawn every 250ms it appears to flash
  if (Sensors[sensor].sensefault > 0 && sensor != 5) { // we don't want to display a high or low warning if there's a sensor fault (ie wiring issue etc).
    return (false);
  }
  if (Sensors[sensor].sensevals > Sensors[sensor].sensewarnhivals || Sensors[sensor].sensevals < Sensors[sensor].sensewarnlowvals) { // if we're under the min or over the max then warn!
    if (Sensors[sensor].warnstatus == true) { // if we're already in a wanring state
      if (toggle) { // only used when being called from inside the display because we use this to flash the warning icons - tones are dealt with outside the display loop (eg if we have more sensors than we can draw at once)
        Sensors[sensor].warnstatus = false; // we toggle the value so that the warning triangle flashes based on the interval we are looping at in loop()
      }
      return (false);
    } else {
      if (toggle) {
        Sensors[sensor].warnstatus = true;
      }
      return (true);
    }
  } else { // otherwise return false
    if (toggle) {
      Sensors[sensor].warnstatus = false;
    }
    return false;
  }
  return (Sensors[sensor].warnstatus); // return the current value in the case that there's a connection issue
}

void audibleWARN(uint8_t sensor) {
  // sound the buzzer if their's a warning condition
  if (processHiLo(sensor, false)) {
    if (PIEZO > 0) {
      //tone(PIEZO, 2000, 200);
    }
  }
}

uint8_t processFaultIfSet(uint8_t sensor) {
  // this function alternates a flag between 1 & 2 if it is set - since the display is redrawn every 250ms it appears to flash
  if (Sensors[sensor].sensefault > 0) {
    if (Sensors[sensor].sensefault == 1) {
      Sensors[sensor].sensefault = 2; // we toggle the value so that the fault icon flashes based on the interval we are looping at in loop()
    } else {
      Sensors[sensor].sensefault = 1;
    }
  }
  return (Sensors[sensor].sensefault);
}

void processFault(uint8_t sensor) {
  // toggles the fault state of a sensor (to make our fault symbols flash)
  if (Sensors[sensor].sensefault == 2) {
    Sensors[sensor].sensefault = 2; // 2 is animation off
  } else {
    Sensors[sensor].sensefault = 1; // 1 is animation on
  }
}

void processPeak(uint8_t sensor) {
  // stores the current value of a sensor if it is above the previously stored high value
  if (Sensors[sensor].sensevals >= Sensors[sensor].senseminvals) { // only do this if the value is above the min
    if (Sensors[sensor].sensevals <= Sensors[sensor].sensemaxvals) { // only do this if the value is below the max
      if (Sensors[sensor].sensevals > Sensors[sensor].sensepeakvals) {
        Sensors[sensor].sensepeakvals = int(Sensors[sensor].sensevals); //if we have a new max then store it
      }
    }
  }
}

String getUnits(uint8_t sensor) { // returns the units associated with the sensor
  switch (Sensors[sensor].senseunits) {
    case 0:
      return ("C");
    case 1:
      return ("psi");
    case 2:
      return ("lvl");
    case 3:
      return ("o");
    case 4:
      return ("rpm");
    case 5:
      return ("mph");
	case 6:
	  return ("g/m");
	case 7:
	  return ("V");  
  }
}

String getValIfNoErr(uint8_t sensor) { //prevents values being displayed if we are in fault state OR this is a boolean sensor (coolant level)
  //String text = String(Sensors[sensor].sensevals);
  // if a fault is set return an empty string

  if (sensor == 5 && Sensors[sensor].sensefault == 0) {
    return ("ok");
  }
  if (Sensors[sensor].sensefault > 0) {
    return ("Err");
  }
  return (String(Sensors[sensor].sensevals));
}

int8_t processRotation(uint8_t location) { // this is used to shift our array of data around the screens
  
  if (sensecount == 0) { // all screens will be blank in this case so just return -1
	  return(-1);
  }
  
  uint8_t count = 0;
  uint8_t dimension = 0;
  if (sensecount < NUM_DISPLAYS) {
	dimension=NUM_DISPLAYS;
  } else {
	  dimension=sensecount;
  }
	int8_t pos[dimension];
  
  // now we populate the array with the active sensors
  for (uint8_t locthisSensor = 0; locthisSensor < totalsensors; locthisSensor++) {
    if (Sensors[locthisSensor].senseactive == true && Sensors[locthisSensor].master == true) {
      pos[count] = locthisSensor;
      count++;
    }
  }
  
  // if there are less sensors than screens then we need to insert some -1 values so that an empty screen is drawn
  if (sensecount < NUM_DISPLAYS) {
	for(uint8_t emptyScreens = NUM_DISPLAYS-1; emptyScreens > count-1; emptyScreens--) {
		pos[emptyScreens] = -1;
	}
	count=NUM_DISPLAYS;
  }
  
  // return the correct sensor for the current location (or -1 to display nothing)
  location = location - 1 + rotation;
  if (location > count - 1) {
    location = location % count;
  }
  return (pos[location]);
}

int processConstraints(int constraint, int checkval, int retval, uint8_t index) { //
  if (checkval < constraint) {
    processFault(index); //fault!
    Sensors[index].sensepeakvals = Sensors[index].senseminvals; //set the peak value to minimum (tidies the display)
    retval = Sensors[index].senseminvals; //return minimum value
  } else {
    Sensors[index].sensefault = 0; // no fault
  }
  return (retval);
}

// Sensor reading code.

int readERR2081(uint8_t sensor, uint8_t index) {
  int raw = 0;     // variable to store the raw ADC input value
  float Vin = 3.3; // variable to store the measured VCC voltage
  float Vout = 0;  // variable to store the output voltage
  int R2 = 1000;   // variable to store the R2 value
  float Rth = 0;   // variable to store the thermistor value

  // THERMISTOR CODE
  raw = analogRead(sensor);      // Reads the Input PIN
  Vout = (Vin / DIVISOR) * raw;     // Calculates the Voltage on the Input PIN
  Rth = ((R2 * Vin) / Vout) - R2;   // Calculates the Resistance of the Thermistor
  float steinhart;                  // This next stage calculates the temp from the resistance
  steinhart = Rth / 2012.2;         // (R/Ro)  therm @ 25C = 1986
  steinhart = log(steinhart);       // ln(R/Ro)
  steinhart /= 3502;                // 1/B * ln(R/Ro) b coefficient = 3344
  steinhart += 1.0 / (25 + 273.15); // + (1/To) nominal temp is 25c
  steinhart = 1.0 / steinhart;      // Invert
  steinhart -= 273.15;              // convert to C
  // END THERMISTOR CODE

  // FAULT checking
  // Sensors should be connected with a 1K pulldown resistor - if there's is a connection fault a low raw read will indicate this.
  return (processConstraints(DIVISOR / 100, raw, int(steinhart), index));
}

int readBoost(uint8_t sensor, uint8_t index) {
  int rawval;
  float kpaval;
  float boost;
  //mV per mB = 2640mv/6894.76mb  = 0.3828  (this is for 3.3v STM32)
  //mv per ADC = 3300mv/4095 = 0.80586
  //mb per ADC = 2.1052
  rawval = analogRead(sensor);       // Read MAP sensor raw value on analog port 0
  kpaval = rawval * 0.4878;             // convert to kpa
  boost = kpaval * 0.145038 - 14.5038;  // Convert to psi and subtract atmospheric (sensor is absolute pressure)
  // process any faults
  return (processConstraints(DIVISOR / 100, rawval, int(boost), index));
}

int readMAX(uint8_t index) {
  int t = int(MAXReadTemperature(MAX_CS));
  // process any faults
  return (processConstraints(MAXreadFault(MAX_CS), 0, t, index));
}

int readPress(uint8_t sensor, uint8_t index) {
  //just a dummy at present
  int rawval;
  long kpaval;
  long oilpress;
  
  //mV per mB = 2640mv/6894mb  = 0.383  (this is for 3.3v STM32)
  //mv per ADC = 3300mv/4096 = 0.8056
  //mb per ADC = 2.1034
  rawval = analogRead(sensor);       // Read MAP sensor raw value on analog port 0
  kpaval = (rawval * 2.1034)/10;             // convert to kpa
  oilpress = kpaval * 0.145038 - 12.5;  // Convert to psi & subtract atmospheric 12psi (sesnor appears to have ~2.5spi offset from reality)
  // process any faults
  return (processConstraints(DIVISOR / 100, rawval, int(oilpress), index));
}

bool readCoolantLevel(uint8_t sensor, uint8_t index) {
  // sensor is normally closed
  // use a pulldown resistor to enable fault monitoring
  int CoolantLevel;
  CoolantLevel = analogRead(sensor);
  // process any faults
  return ((bool)processConstraints(DIVISOR / 2, CoolantLevel, CoolantLevel, index));
}



// MAX31856 SPI CODE

void MAXInitializeChannel(int Pin) {
  for (int i = 0; i < NumRegisters; i++) {
    MAXWriteRegister(Pin, i, RegisterValues[i]);
  }
}

uint8_t MAXreadFault(int Pin) {
  return MAXReadSingleRegister(Pin, 0x0F);
}

byte MAXReadSingleRegister(int Pin, byte Register) {
  SPI.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE3));
  digitalWrite(Pin, LOW);
  delayMicroseconds(1);
  SPI.transfer(Register & 0x7F); //set bit 7 to 0 to ensure a read command
  delayMicroseconds(1);
  byte data = SPI.transfer(0);
  digitalWrite(Pin, HIGH);
  SPI.endTransaction();
  return data;
}

unsigned long MAXReadMultipleRegisters(int Pin, byte StartRegister, int count) {
  //reads up to 4 sequential registers
  SPI.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE3));
  digitalWrite(Pin, LOW);
  unsigned  long data = 0;
  SPI.transfer(StartRegister & 0x7F); //force bit 7 to 0 to ensure a read command
  delayMicroseconds(1);

  for (int i = 0; i < count; i++) {
    data = (data << 8) | SPI.transfer(0); //bitshift left 8 bits, then add the next register
  }
  digitalWrite(Pin, HIGH);
  SPI.endTransaction();
  return data;
}

void MAXWriteRegister(int Pin, byte Register, byte Value) {
  byte Address = Register | 0x80; //Set bit 7 high for a write command
  SPI.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE3));
  digitalWrite(Pin, LOW);
  delayMicroseconds(1);
  SPI.transfer(Address);
  delayMicroseconds(1);
  SPI.transfer(Value);
  digitalWrite(Pin, HIGH);
  SPI.endTransaction();
}

double MAXReadTemperature(int Pin) {
  double temperature;
  long data;
  data = MAXReadMultipleRegisters(Pin, 0x0C, 4);
  // Strip the unused bits and the Fault Status Register
  data = data >> 13;
  // Negative temperatures have been automagically handled by the shift above :-)
  // Convert to Celsius
  temperature = (double) data * 0.0078125;
  // Return the temperature
  return (temperature);
}



