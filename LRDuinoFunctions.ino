
void initOBD(void) {
  td5.init();
  if(!td5.connectToEcu(false)) {  
    disableOBDSensors();
  } else {
    enableOBDSensors();
    getSensecount();
  }
}

void enableOBDSensors(void) {
  for(uint8_t i=0; i < totalsensors; i++ )  {
    if (Sensors[i].sensetype == OBD ) {
      if (Sensors[i].warnstatus == true) { // already disabled so set warnstatus to true - we'll use this as temp storage so we don't re-enable if OBD gets re-initialised
        Sensors[i].senseactive = false; // should already be false but no harm in making sure
        Sensors[i].warnstatus = false;
      } else {
        Sensors[i].senseactive = true;
        Sensors[i].warnstatus = false;
      }
    }
  }
}

void disableOBDSensors(void) {
  for(uint8_t i=0; i < totalsensors; i++ )  {
    if (Sensors[i].sensetype == OBD ) {
      if (Sensors[i].senseactive == false) { // already disabled so set warnstatus to true - we'll use this as temp storage so we don't re-enable if OBD gets re-initialised
        Sensors[i].senseactive = false;
        Sensors[i].warnstatus = true;
      } else {
        Sensors[i].senseactive = false;
        Sensors[i].warnstatus = false;
      }
    }
  }
getSensecount();
}

void getSensecount(void)
{
  sensecount = 0;
  for (uint8_t thisSensor = 0; thisSensor < totalsensors; thisSensor++) {
    if (Sensors[thisSensor].senseactive == true && Sensors[thisSensor].master == true && Sensors[thisSensor].hidden == false) { // don't count slaves
      sensecount++;
    }
  }
}

bool processHiLo(uint8_t sensor, bool toggle)
{
  // this function toggles a an error flag if the current sensor is above it's high warning parameter or below it's low warning paramater - since the display is redrawn every 250ms it appears to flash
  if (Sensors[sensor].sensefault > 0 && Sensors[sensor].sensetype == EARTHSW) { // we don't want to display a high or low warning if there's a sensor fault on an earth switched device (ie wiring issue etc).
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

void audibleWARN(uint8_t sensor)
{
  // sound the buzzer if their's a warning condition
  if (processHiLo(sensor, false)) {
    if (PIEZO > 0) {
      //tone(PIEZO, 2000, 200);
    }
  }
}

uint8_t processFaultIfSet(uint8_t sensor)
{
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

void processFault(uint8_t sensor)
{
  // toggles the fault state of a sensor (to make our fault symbols flash)
  if (Sensors[sensor].sensefault == 2) {
    Sensors[sensor].sensefault = 2; // 2 is animation off
  } else {
    Sensors[sensor].sensefault = 1; // 1 is animation on
  }
}

void processPeak(uint8_t sensor)
{
  // stores the current value of a sensor if it is above the previously stored high value
  if (Sensors[sensor].sensevals >= Sensors[sensor].senseminvals) { // only do this if the value is above the min
    if (Sensors[sensor].sensevals <= Sensors[sensor].sensemaxvals) { // only do this if the value is below the max
      if (Sensors[sensor].sensevals > Sensors[sensor].sensepeakvals) {
        Sensors[sensor].sensepeakvals = int(Sensors[sensor].sensevals); //if we have a new max then store it
      }
    }
  }
}

String getUnits(uint8_t sensor)   // returns the units associated with the sensor
{
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
      return ("mgh");
    case 6:
      return ("kph");
    case 7:
      return ("lpC");
  }
  return ("");
}

String getValIfNoErr(uint8_t sensor, bool prev)   //prevents values being displayed if we are in fault state OR this is a boolean sensor (coolant level)
{
  //String text = String(Sensors[sensor].sensevals);
  // if a fault is set return an empty string

  if ((Sensors[sensor].sensetype == EARTHSW) && (Sensors[sensor].sensefault == 0)) {
    return ("ok");
  }
  if (Sensors[sensor].sensefault > 0) {
    return ("Er");
  }
  if (!prev) {
    return (String(Sensors[sensor].sensevals));
  } else {
    return (String(Sensors[sensor].senselastvals));
  }
}

int8_t processRotation(uint8_t location)   // this is used to shift our array of data around the screens
{
  if (sensecount == 0) { // all screens will be blank in this case so just return -1
    return (-1);
  }
  uint8_t count = 0;
  uint8_t dimension = 0;
  if (sensecount < NUM_DISPLAYS) {
    dimension = NUM_DISPLAYS;
  } else {
    dimension = sensecount;
  }
  int8_t pos[dimension];
  // now we populate the array with the active sensors
  for (uint8_t locthisSensor = 0; locthisSensor < totalsensors; locthisSensor++) {
    if (Sensors[locthisSensor].senseactive == true && Sensors[locthisSensor].master == true && Sensors[locthisSensor].hidden == false) {
      pos[count] = locthisSensor;
      count++;
    }
  }
  // if there are less sensors than screens then we need to insert some -1 values so that an empty screen is drawn
  if (sensecount < NUM_DISPLAYS) {
    for (uint8_t emptyScreens = NUM_DISPLAYS - 1; emptyScreens > count - 1; emptyScreens--) {
      pos[emptyScreens] = -1;
    }
    count = NUM_DISPLAYS;
  }
  // return the correct sensor for the current location (or -1 to display nothing)
  location = location - 1 + rotation;
  if (location > count - 1) {
    location = location % count;
  }
  return (pos[location]);
}

int processConstraints(int constraint, int checkval, int retval, uint8_t index)   //
{
  if (checkval < constraint) {
    processFault(index); //fault!
    Sensors[index].sensepeakvals = Sensors[index].senseminvals; //set the peak value to minimum (tidies the display)
    retval = Sensors[index].senseminvals; //return minimum value
  } else {
    Sensors[index].sensefault = 0; // no fault
  }
  return (retval);
}

void readSensor(int currentsensor)
{
  Sensors[currentsensor].senselastvals = Sensors[currentsensor].sensevals; // stash the previous value
  switch (Sensors[currentsensor].sensetype) { // switch based upon the sensor type
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
          case OBDINJ  :
            if(td5.getPid(&pidFuelling) > 0) {
              Sensors[currentsensor].sensevals = pidFuelling.getfValue(6); // Injection Quantity
          }
          break;
          case OBDSPD  :
            if(td5.getPid(&pidVehicleSpeed) > 0) {
              Sensors[currentsensor].sensevals = pidVehicleSpeed.getbValue(0); // Speed
          }
          break;
          case OBDCON  :
            int spd=0;
            float inj=0;
            int rpm=0;
            if(td5.getPid(&pidVehicleSpeed) > 0) {
              spd = pidVehicleSpeed.getbValue(0); // Speed
            } 

            delay(55);

            if (td5.getPid(&pidRPM) > 0) {
              rpm = pidRPM.getlValue();
            }

            delay(55);

            if (td5.getPid(&pidFuelling) > 0) {
              inj = pidFuelling.getfValue(6);
            }

            delay(55);
            
            float kgh = (inj * rpm * (5/2) * 60) / 1000000;   //injq*rpm*(5/2)*60/1000000
            float lphk;
            if (spd != 0) { // avoid divide by zero condition
              lphk = (100/spd) * (kgh * 0.85); 
            } else {
              lphk = 0;
            }
            Sensors[currentsensor].sensevals = int(lphk); //stash the computed value
          
          break;
        } // OBD PID switch
      } // if ECU is connected
    break; //optional
    } // Sensor type switch
    processPeak(currentsensor);  // update the highest value if it's been exceeded - useful for graphs.
    audibleWARN(currentsensor);  // issue tones if there's an issue
}
