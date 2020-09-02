#pragma once

// This is all the parameters and variables for our sensors
// define sensor types so we can switch on these for sensor reading
#define ERR2081       1
#define KTYPE         2
#define BOOST3BAR     3
#define CH100PSI      4
#define EARTHSW       5

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

SingleSensor Sensors[9] = {
 //active  master slaveID  senseorder  warnstatus  sensefault senseglyphs sensevals  senselastvals  units maxvals minvals peakvals warnhivals warnlovals  sensename       sensetype  PIN/PID  hidden
  {true,   true,  MASTER,  0,			     false,      0,         trbBMP,     0,         1,             1,    32,     0,      0,       29,        NOLOWARN,	  "Boost",        BOOST3BAR, BOST,    false}, // Boost
  {true,   true,  MASTER,  0,			     false,      0,         egtBMP,     0,         1,             0,    900,    -40,    -40,     750,       NOLOWARN,	  "EGT",          KTYPE,     0,       false}, // EGT
  {true,   true,  MASTER,  0,          false,      0,         tboxBMP,    0,         1,             0,    150,    -40,    -40,     140,       NOLOWARN,   "Tbox Temp",    ERR2081,   TBXT,    false}, // TBox Temp
  {true,   true,  MASTER,  0,          false,      0,         Gauge,      0,         1,             1,    72,     0,      0,       65,        40,         "Fuel Pressre", CH100PSI,  FULP,    false}, // Fuel Pressure  
  {true,   true,  5,       0,          false,      0,         gopBMP,     0,         1,             1,    72,     0,      0,       60,        20,         "Gbx Pressure", CH100PSI,  GBOP,    false}, // Gearbox Pressure
  {true,   false, MASTER,  0,          false,      0,         tboxBMP,    0,         1,             0,    150,    -40,    -40,     100,       NOLOWARN,   "Gbx Temp",     ERR2081,   GBOT,    false}, // Gearbox Temp
  {true,   true,  7,       0,			     false,      0,         eopBMP,     0,         1,             1,    72,     0,      0,       60,        20,	        "Oil Pressure", CH100PSI,  OILP,    false}, // Oil Pressure
  {true,   false, MASTER,  0,			     false,      0,         eotBMP,     0,         1,             0,    150,    -40,    -40,     100,       NOLOWARN,	  "Oil Temp",     ERR2081,   OILT,    false}, // Oil Temp
  {true,   true,  MASTER,  0,			     false,      0,         coollev,    0,         1,             2,    1,      0,      1,       NOHIWARN,  1,	        "Coolant Lvl",  EARTHSW,   COOL,    false}  // Coolant Level
};

const uint8_t totalsensors = 9; //this is the actual number of definitions above
