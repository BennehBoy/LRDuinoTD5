
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
		for (uint8_t i=6; i < totalsensors; i++) {
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
		if (Sensors[thisSensor].senseactive == true && Sensors[thisSensor].master == true && Sensors[thisSensor].hidden == false) { // don't count slaves
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
        
        #if defined HAS_SDIO
        if (SD.open(file_name)) {
        #else
        if (sdLogFile.open(file_name, O_CREAT | O_EXCL | O_WRITE)) {
        #endif
					break;
				}
			}

      #if defined HAS_SDIO
      if (sdLogFile == SD.open(file_name, FILE_WRITE)) {
      #else
      if (sdLogFile.isOpen()) {
      #endif
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
				sdLogFile.print(Sensors[11].sensename);sdLogFile.print(";");
				sdLogFile.print(Sensors[12].sensename);sdLogFile.println(";");
			} else { //file open failed
				dataLog = false;
				//Serial.println("failed to open file");
			}
		}
	
	// open the file and write the header
	} else if (sd_present && !dataLog) {
	// close the file
      #if defined HAS_SDIO
      if (sdLogFile) {        
      #else
      if (sdLogFile.isOpen()) { 
      #endif
			sdLogFile.close();
		}
	}
}

void writeDatalogline(void) {
	// write a line to the datalog
  #if defined HAS_SDIO
  if (sdLogFile) {
      // TODO - fix conversion of int to char for STM32SD.h   
  }
  #else
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
		sdLogFile.print(Sensors[11].sensevals);sdLogFile.print(";");
		sdLogFile.print(Sensors[12].sensevals);sdLogFile.println(";");
	}
  #endif
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
  return ("");
}

String getValIfNoErr(uint8_t sensor, bool prev) { //prevents values being displayed if we are in fault state OR this is a boolean sensor (coolant level)
  //String text = String(Sensors[sensor].sensevals);
  // if a fault is set return an empty string

  if (sensor == 5 && Sensors[sensor].sensefault == 0) {
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
    if (Sensors[locthisSensor].senseactive == true && Sensors[locthisSensor].master == true && Sensors[locthisSensor].hidden == false) {
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
