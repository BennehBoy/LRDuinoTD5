#pragma once

// This is all the parameters and variables for our sensors
// define sensor types so we can switch on these for sensor reading
#define ERR2081       1
#define KTYPE         2
#define BOOST3BAR     3
#define CH100PSI      4
#define EARTHSW       5
#define BMP280        6
#define OBD           7
#define FAKE          8
// OBD PIDS
#define OBDRPM        9
#define OBDINJ        10
#define OBDSPD        11
#define OBDCON        12

// when multiple sensors displayed on one screen the master sensor has this ID
#define MASTER        99

// Definitions for out of bounds warning values
#define NOLOWARN      -9999
#define NOHIWARN      9999

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
  int senselastvals;
  const uint8_t senseunits;
  const int sensemaxvals;
  const int8_t senseminvals;
  int sensepeakvals;
  int sensewarnhivals;
  int sensewarnlowvals;
  const char sensename[13];
  uint8_t sensetype;
  uint8_t sensepin;
  bool hidden;
} SingleSensor;

SingleSensor Sensors[13] = {
 //active  master slaveID  senseorder  warnstatus  sensefault senseglyphs sensevals  senselastvals  units maxvals minvals peakvals warnhivals warnlovals  sensename       sensetype  PIN/PID  hidden
  {true,  true,  MASTER,  0,			     false,      0,         trbBMP,     0,         -999,             1,    32,     0,      0,       29,        NOLOWARN,	 "Boost",        BOOST3BAR, BOST,    false}, // Boost
  {true,   true,  MASTER,  0,			     false,      0,         egtBMP,     0,         -999,             0,    900,    -40,    -40,     750,       NOLOWARN,	 "EGT",          KTYPE,     0,       false}, // EGT
  {false,  true,  MASTER,  0,          false,      0,         tboxBMP,    0,         -999,             0,    150,    -40,    -40,     140,       NOLOWARN,   "Tbox Temp",    ERR2081,   TBXT,    false}, // TBox Temp
  {false,  true,  MASTER,  0,          false,      0,         Gauge,      0,         -999,             1,    72,     0,      0,       65,        40,         "Fuel Pressre", CH100PSI,  FULP,    false}, // Fuel Pressure  
  {false,  true,  5,       0,          false,      0,         gopBMP,     0,         -999,             1,    72,     0,      0,       60,        20,         "Gbx Pressure", CH100PSI,  GBOP,    false}, // Gearbox Pressure
  {false,  false, MASTER,  0,          false,      0,         tboxBMP,    0,         -999,             0,    150,    -40,    -40,     100,       NOLOWARN,   "Gbx Temp",     ERR2081,   GBOT,    false}, // Gearbox Temp
  {true,   true,  7,       0,			     false,      0,         eopBMP,     0,         -999,             1,    72,     0,      0,       60,        20,	       "Oil Pressure", CH100PSI,  OILP,    false}, // Oil Pressure
  {true,   false, MASTER,  0,			     false,      0,         eotBMP,     0,         -999,             0,    150,    -40,    -40,     100,       NOLOWARN,	 "Oil Temp",     ERR2081,   OILT,    false}, // Oil Temp
  {false,  true,  MASTER,  0,			     false,      0,         coollev,    0,         -999,             2,    1,      0,      1,       NOHIWARN,  1,	         "Coolant Lvl",  EARTHSW,   COOL,    false}, // Coolant Level
  {false,  true,  MASTER,  0,          false,      0,         Gauge,      0,         -999,             7,    50,     0,      0,       NOHIWARN,  NOLOWARN,   "l/100km",      OBD,       OBDCON,  false}, // Fule Consumption (composite PID)
  {false,   true, MASTER,  0,          false,      0,         Gauge,      0,         -999,             4,    4500,   0,      0,       NOHIWARN,  NOLOWARN,   "RPM (OBD)",    OBD,       OBDRPM,  false}, // RPM
  {false,   true, MASTER,  0,          false,      0,         Gauge,      0,         -999,             5,    100,    0,      0,       NOHIWARN,  NOLOWARN,   "Inj mg/s",     OBD,       OBDINJ,  false}, // Injection Quantity
  {false,   true, MASTER,  0,          false,      0,         Gauge,      0,         -999,             6,    200,    -30,    0,       NOHIWARN,  NOLOWARN,   "Speed (OBD)",  OBD,       OBDSPD,  false}  // Roadspeed 
};

const uint8_t totalsensors = 13; //this is the actual number of definitions above
