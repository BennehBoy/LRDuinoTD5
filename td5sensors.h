#pragma once

// This is all the parameters and variables for our sensors
// define sensor types so we can switch on these for sensor reading
#define ERR2081       1
#define KTYPE         2
#define BOOST3BAR     3
#define CH100PSI      4
#define EARTHSW       5
#define OBD           6
// OBD PIDS
#define OBDRPM        1
#define OBDSPD        2
#define OBDECT        3
#define OBDBTV        4
#define OBDINT        5
#define OBDFLT        6
#define OBDAAP        7

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
 //active  master slaveID     senseorder	warnstatus    sensefault senseglyphs sensevals  senselastvals   units maxvals minvals peakvals warnhivals warnlovals  sensename       sensetype     PIN/PID     hidden
  {true,   true,  MASTER,     0,			    false,        0,         trbBMP,     0,         1,              1,    32,     0,      0,       29,        NOLOWARN,	  "Boost",        BOOST3BAR,    BOST,       false}, // Boost
  {true,   true,  MASTER,     0,			    false,        0,         tboxBMP,    0,         1,              0,    150,    -40,    -40,     140,       NOLOWARN,	  "Tbox Temp",    ERR2081,      TBXT,       false}, // Transfer Box Temp
  {true,   true,  MASTER,     0,			    false,        0,         egtBMP,     0,         1,              0,    900,    -40,    -40,     750,       NOLOWARN,	  "EGT",          KTYPE,        0,          false}, // EGT
  {true,   true,  4,          0,			    false,        0,         eopBMP,     0,         1,              1,    72,     0,      0,       60,        20,	        "Oil Pressure", CH100PSI,     OILP,       false}, // Oil Pressure
  {true,   false, MASTER,     0,			    false,        0,         eotBMP,     0,         1,              0,    150,    -40,    -40,     100,       NOLOWARN,	  "Oil Temp",     ERR2081,      OILT,       false}, // Oil Temp
  {true,   true,  MASTER,     0,			    false,        0,         coollev,    0,         1,              2,    1,      0,      1,       NOHIWARN,  1,	        "Coolant Lvl",  EARTHSW,      COOL,       false}, // Coolant Level
  {true,   true,  MASTER,     0,			    false,        0,         Gauge,      0,         1,              4,    4500,   0,      0,       4500,      600,	      "RPM (OBD)",    OBD,          OBDRPM,     false}, // RPM
  {true,   true,  MASTER,     0,			    false,        0,         Gauge,      0,         1,              5,    100,    -30,    0,       100,       -30,	      "Speed (OBD)",  OBD,          OBDSPD,     false}, // Roadspeed
  {true,   true,  MASTER,     0,			    false,        0,         cooltmp,    0,         1,              0,    130,    -30,    0,       100,       NOLOWARN,	  "ECT (OBD)",    OBD,          OBDECT,     false}, // Coolant
  {true,   true,  MASTER,     0,			    false,        0,         OBDII,   	 0,         1,              7,    16,     0,	    0,       15,        11,	        "BtV (OBD)",    OBD,          OBDBTV,     false}, // Battery Voltage
  {false,  true,  MASTER,     0,			    true,         0,         OBDII,   	 0,         1,              0,    100,    -40,	  0,       50,        NOLOWARN,	  "InT (OBD)",    OBD,          OBDINT,     false}, // Inlet Temperature
  {false,  true,  MASTER,     0,			    true,         0,         OBDII,   	 0,         1,              0,    100,    -40,	  0,       75,        NOLOWARN,	  "FlT (OBD)",    OBD,          OBDFLT,     false}, // Fuel Temperature
  {false,  true,  MASTER,     0,			    true,         0,         OBDII,   	 0,         1,              1,    20,     0,	    0,       16,        12,	        "AAP (OBD)",    OBD,          OBDAAP,     false}  // Ambient Pressure
};

const uint8_t totalsensors = 13; //this is the actual number of definitions above
