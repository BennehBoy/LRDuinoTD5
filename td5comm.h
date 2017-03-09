/*
Td5Comm.h -
 
 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.
 
 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 
 */

#ifndef Td5Comm_h
#define Td5Comm_h

#include <Arduino.h>

#define _FAULT_CODES_STRINGS_

#define Td5RequestByteDelay       5
#define Td5RequestDelay           55
#define Td5KeepAliveDelay         4000L

#define READ_ATTEMPTS             7
#define FRAME_READ_ATTEMPT_TIME   300
#define INIT_FIRST_DELAY_TIME     300
#define MAX_FAULT_CODE            280
#define MAX_FUELLING_PARAMS       22
#define KEEP_ALIVE_TIME           4500

#define INIT_FRAME      0x00
#define START_DIAG      0x01
#define REQ_SEED        0x02
#define SEND_KEY        0x03
#define START_FUELLING  0x04
#define ENGINE_RPM      0x05
#define TEMPERATURES    0x06
#define INLET_PRES_MAF  0x07
#define BATTERY_VOLT    0x08
#define AMBIENT_PRES    0x09
#define VEHICLE_SPEED   0x0A
#define THROTTLE_POS    0x0B
#define IO_CONTROL      0x0C
#define INJ_BALANCE     0x0D
#define RPM_ERROR       0x0E
#define EGR_MOD         0x0F
#define ILT_MOD         0x10
#define TWG_MOD         0x11
#define KEEP_ALIVE      0x12
#define FAULT_CODES     0x13
#define CLEAR_FAULTS    0x14

class Td5Pid;

// Class Td5Comm
class Td5Comm
{
public:
  Td5Comm();
  void init();
  void initComm();
  int8_t getPid(Td5Pid* pid);
  boolean ecuIsConnected();
  boolean newDataIsAvailable();
  unsigned long getLastReceivedPidTime();
  unsigned long getLastReceivedPidElapsedTime();
  void setInitStep(byte init_step);
  byte getInitStep();
  int getLostFrames();
  int getConsecutiveLostFrames();

  boolean connectToEcu(boolean showBar = true);
  void disconnectFromEcu();
  void instrumentCycle();
  void fuellingCycle();
  int getFaultCodes();
  int getFaultCode(int index);
  int getFaultCodesCount(){return faultCodesCount;};
  int8_t resetFaults();
  
private:  
  byte checksum(byte *data, byte len);
  boolean read_byte(byte * b);
  void write_byte(byte b);

protected:
  unsigned long lastReceivedPidTime;
  unsigned long initTime;
  byte initStep;  // Init is multistage, this is the counter
  boolean ecuConnection;  // Have we connected to the ECU or not
  boolean newDataAvailable;
  int lostFrames;
  int8_t consLostFrames;
  int faultCodesCount;
};

// Class Td5Pid
class Td5Pid
{
public:
  Td5Pid(byte ID, byte reqlen, byte resplen, long cycletime = 0);
  void setCycleTime(long time){ cycleTime = time; };
  boolean getValue(float *fvalue, byte index = 0);
  boolean getValue(uint16_t *value, byte index = 0);
  boolean getValue(int *value, byte index = 0);
  float getfValue(byte index = 0);
  uint16_t getulValue(byte index = 0);
  int16_t getlValue(byte index = 0);
  byte getbValue(byte index = 0);
  
  void setRequestByte(byte value, byte pos);
  byte getResponseByte(byte pos);

  byte *requestFrame;
  byte *responseFrame;
  
  byte id;
  long cycleTime;
  long lastSeenTime;
  byte responseLength;  
};

// Generic functions
void remote_log_byte(byte b);
void remote_log_frame(byte *datasent, byte sentlen, byte *datarecv, byte recvlen);
void retrieve_keys_from_eeprom(uint8_t *seed, uint8_t *key);

uint8_t td5_get_next_fault_code();
uint8_t td5_get_previous_fault_code();
   

// Declare pids
extern Td5Pid pidInitFrame;
extern Td5Pid pidStartDiag;
extern Td5Pid pidRequestSeed;
extern Td5Pid pidSendKey;
extern Td5Pid pidRPM;
extern Td5Pid pidTurboPressureMaf;
extern Td5Pid pidTemperatures;
extern Td5Pid pidBatteryVoltage;
extern Td5Pid pidAmbientPressure;
extern Td5Pid pidStartFuelling;
extern Td5Pid pidKeepAlive;
extern Td5Pid pidFaultCodes;
extern Td5Pid pidResetFaults;
extern Td5Pid pidInjectorsBalance;
extern Td5Pid pidVehicleSpeed;
extern Td5Pid pidThrottlePosition;
extern Td5Pid pidRPMError;
extern Td5Pid pidEGR;
extern Td5Pid pidILT;
extern Td5Pid pidTWG;


#define PID_NOT_READY        0
#define PID_LOST_FRAME      -1
#define PID_NEGATIVE_ANSWER -2

#endif

