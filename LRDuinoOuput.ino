// 4 screens - use index values like this to rotate around the displays
// 1 2
// 4 3

// 6 screens - use index values like this to rotate around the displays
// 1 2 3
// 6 5 4

// 8 screens - use index values like this to rotate around the displays
// 1 2 3 4
// 8 7 6 5

void drawDISPLAY(SCREEN_TYPE &refDisp, uint8_t index) { // DISPLAY 1 is our Main guage display

  int8_t sensor0 = processRotation(index);
  
  if (sensor0 == -1) {
  // don't draw anything because there are less sensors than displays
  } else if (Sensors[sensor0].slaveID != MASTER) { // draw paired sensors
    drawSensor(0, 0, refDisp, sensor0, true);
    drawSensor(33, 0, refDisp, Sensors[sensor0].slaveID, true);
  } else if (Sensors[sensor0].sensetype == KTYPE) { // draw a bargraph
    drawSensor(0, 0, refDisp, sensor0, true); 
    drawBarGraph(refDisp, sensor0);
  } else {
	drawBIG(refDisp, sensor0);  
  }
  SCREEN_DISPLAY();
}

void drawSensor(uint8_t y, uint8_t x, SCREEN_TYPE &refDisp, uint8_t sensor, bool icons) {
  uint8_t unitoffset = 0;
  uint16_t w, h;
  int16_t  x1, y1;
  uint8_t leftpad = 34; // width of sensor glyph +2
  uint8_t charpad;
  
  refDisp.setTextWrap(false);

  // DO sensor visual warnings
  if (processHiLo(sensor, true) && icons) {
    refDisp.fillRect(SCREENWIDTH-24, y + 4, 24, 24, BLACK);
    refDisp.drawBitmap(SCREENWIDTH-24, y + 4, triBMP, 24, 24, RED); //outut the warning triangle
  } else if (processFaultIfSet(sensor) == 1 && icons){
    refDisp.fillRect(SCREENWIDTH-24, y + 4, 24, 24, BLACK);
    refDisp.drawBitmap(SCREENWIDTH-24, y + 4, NoConn, 24, 24, YELLOW); //output the disconnected sensor icon
  } else {
    refDisp.fillRect(SCREENWIDTH-24, y + 4, 24, 24, BLACK); // clear the same area
  }

  if (SCREENWIDTH < 128) {
    refDisp.setFont(&FreeSansBoldOblique9pt7b); //switch to a nice ttf font 12x7
    charpad = 13;
  } else {
    refDisp.setFont(&FreeSansBoldOblique12pt7b); //switch to a nice ttf font 12x7
    charpad = 16;
  }
  if (Sensors[sensor].senselastvals != Sensors[sensor].sensevals) {  // only clear our textbox if the value has changed - reduces flicker
    refDisp.getTextBounds(getValIfNoErr(sensor, true), leftpad + x, y + 9 + charpad, &x1, &y1, &w, &h);  //find out what area we need to clear that contained previous text
    refDisp.fillRect(x1, y1-1, w+6, h+2, BLACK); //clear to screen edge to also erase the units
  }
  drawItem(leftpad + x, y + 9 + charpad, getValIfNoErr(sensor, false), 1, refDisp); // output the value 

  refDisp.getTextBounds(getValIfNoErr(sensor, false), leftpad + x, y + 9 + charpad, &x1, &y1, &w, &h); // figure out where to draw our units 
  unitoffset = (w+5);
  refDisp.setFont(); // switch to small standard font
  drawItem(leftpad + x + unitoffset, y + 9, getUnits(sensor), 1, refDisp); // draw the units symbol

  if (icons) {
    refDisp.drawBitmap(0, y, Sensors[sensor].senseglyphs, 32, 32, GREEN);
  }
  refDisp.setFont(); //reset to basic font
}

void drawBIG(SCREEN_TYPE &refDisp, uint8_t sensor) {
  uint8_t xposition = 0;
  uint16_t w, h;
  int16_t  x1, y1;
  uint8_t charpad; 
  
  refDisp.setTextWrap(false);

  if (SCREENWIDTH < 128) {
    refDisp.setFont(&FreeSansBoldOblique9pt7b); //switch to a nice ttf font 12x7
    charpad = 13;
  } else {
    refDisp.setFont(&FreeSansBoldOblique12pt7b); //switch to a nice ttf font 12x7
    charpad = 16;
  }
  refDisp.drawBitmap(SCREENWIDTH-32, 34, Sensors[sensor].senseglyphs, 32, 32, GREEN); //draw the sensor icon
  xposition = (SCREENWIDTH/2)-(((getUnits(sensor).length())*charpad)/2);  // work out our drawing location
  drawItem(xposition, (SCREENHEIGHT-6), getUnits(sensor), 1, refDisp); // and draw the units, 6 is custom font baseline adjustment
  if (SCREENWIDTH < 128) {
    refDisp.setFont(&FreeSansBoldOblique18pt7b); //switch to a nice ttf font 12x7
    charpad=22;
  } else {
    refDisp.setFont(&FreeSansBoldOblique24pt7b); //switch to a nice ttf font 12x7
    charpad=28;
  }

  if (Sensors[sensor].senselastvals != Sensors[sensor].sensevals) {  // only clear our textbox if the value has changed - reduces flicker
    xposition = (SCREENWIDTH/2)-(((getValIfNoErr(sensor, true).length())*charpad)/2); // work out the drawing location
    refDisp.getTextBounds(getValIfNoErr(sensor, true), xposition, 34, &x1, &y1, &w, &h);  //find out what area we need to clear that contained previous text
    refDisp.fillRect(x1, y1, w, h, BLACK); //clear it
  }
  xposition = (SCREENWIDTH/2)-(((getValIfNoErr(sensor, false).length())*charpad)/2); // work out the drawing location
  drawItem(xposition, 34, getValIfNoErr(sensor, false), 1, refDisp); // draw the value
      
  if (processHiLo(sensor, true)) {
    refDisp.fillRect(0, SCREENHEIGHT-2-24, 24, 24, BLACK);
    refDisp.drawBitmap(0, SCREENHEIGHT-2-24, triBMP, 24, 24, RED); //outut the warning triangle
  } else if (processFaultIfSet(sensor) == 1) {
    refDisp.fillRect(0, SCREENHEIGHT-2-24, 24, 24, BLACK);
    refDisp.drawBitmap(0, SCREENHEIGHT-2-24, NoConn, 24, 24, YELLOW); //output the disconnected sensor icon
  } else {
    refDisp.fillRect(0, SCREENHEIGHT-2-24, 24, 24, BLACK); // clear the same area
  }
  refDisp.setFont(); //reset to basic font
}

void drawBarGraph(SCREEN_TYPE &refDisp, uint8_t sensor) {
  int padding = 0;
  float scalerange = 0;
  int scaleposmin = 0;

  refDisp.drawLine(11, 52, 11, 54, WHITE); // draw our gauge and scale markings
  refDisp.drawLine(SCREENWIDTH/2, 52, SCREENWIDTH/2, 54, WHITE);
  refDisp.drawLine(SCREENWIDTH-12, 52, SCREENWIDTH-12, 54, WHITE);
  refDisp.drawRect(11, 42, SCREENWIDTH-22, 10, WHITE); //Border of the bar chart
  if (Sensors[sensor].senseminvals < 0) { // Work out a positive range of values that we need to plot
    scaleposmin = Sensors[sensor].senseminvals * -1;
    scalerange = scaleposmin + Sensors[sensor].sensemaxvals;
  } else {
    scaleposmin = Sensors[sensor].senseminvals;
    scalerange = Sensors[sensor].sensemaxvals - scaleposmin;
  }
  refDisp.fillRect(13, 43, SCREENWIDTH-26, 8, BLACK);
  refDisp.fillRect(14, 44, ((SCREENWIDTH-28) / scalerange * (Sensors[sensor].sensevals + scaleposmin)), 6, WHITE); //Draws the bar depending on the sensor value
  refDisp.drawLine(13 + ((SCREENWIDTH-28) / scalerange * (Sensors[sensor].sensepeakvals + scaleposmin)), 41, 13 + ((SCREENWIDTH-28) / scalerange * (Sensors[sensor].sensepeakvals + scaleposmin)), 50, WHITE); // draw the peak value line;
  if (Sensors[sensor].sensevals < 100) { // adjust padding for the low value so it looks nice
    padding = 0;
  } else {
    padding = -4;
  }
  refDisp.fillRect(0,32,SCREENWIDTH,10, BLACK);
  drawItem(8 + padding + ((SCREENWIDTH-28) / scalerange * (Sensors[sensor].sensepeakvals + scaleposmin)), 33, String(Sensors[sensor].sensepeakvals), 1, refDisp); // set cursor with padding & write the peak val
  
  drawItem(8, 57, String(Sensors[sensor].senseminvals), 1, refDisp); // draw the low scale
  refDisp.setCursor((SCREENWIDTH/2)-6, 57);
  if (Sensors[sensor].senseminvals < 100) { // set padding for the mid
    padding = 8;
  } else {
    padding = 0;
  }
  refDisp.println(String(static_cast<int>(((Sensors[sensor].sensemaxvals - Sensors[sensor].senseminvals) / 2) - scaleposmin))); // draw the mid scale
  if (Sensors[sensor].sensemaxvals < 100) { // adjust padding for the high value so it looks nice/doesnt wrap off screen
    padding = 10;
  } else {
    padding = 5;
  }
  drawItem(SCREENWIDTH-28 + padding, 57, String(Sensors[sensor].sensemaxvals), 1, refDisp); // draw the high scale
}

void drawItem(int x, int y, String token, int txt_size, SCREEN_TYPE &refDisp) {
  refDisp.setCursor(x, y);
  refDisp.setTextColor(WHITE, BLACK);
  refDisp.setTextSize(txt_size);
  refDisp.print(token);
  refDisp.setTextSize(1); // Back to default text size
}
