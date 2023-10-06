// 4 screens - use index values like this to rotate around the displays
// 1 2
// 4 3

// 6 screens - use index values like this to rotate around the displays
// 1 2 3
// 6 5 4

// 8 screens - use index values like this to rotate around the displays
// 1 2 3 4
// 8 7 6 5

void drawDISPLAY(SCREEN_TYPE &refDisp, uint8_t index)   // DISPLAY 1 is our Main guage display
{
  // we only draw things when vlaues have changed
  int8_t sensor0 = processRotation(index);  //this gets us the id of the current sensor

  if (sensor0 == -1) { // don't draw anything because there are less sensors than displays
  } else if (Sensors[sensor0].slaveID == OBDCON) { // Fuel consumption output - where we combine sensors and do calculations)
    if ((Sensors[sensor0].sensevals != Sensors[sensor0].senselastvals) || rotated == 1) {
      drawSensor(0, 0, refDisp, sensor0, true); // 12 = our fake storage sensor (see td5sensors.h)
      drawBarGraph(refDisp, sensor0);
    }
  } else if (Sensors[sensor0].slaveID != MASTER) { // draw paired sensors
    if ((Sensors[sensor0].sensevals != Sensors[sensor0].senselastvals) || rotated == 1) {
      drawSensor(0, 0, refDisp, sensor0, true);
      drawSensor(0, SCREENHEIGHT/2, refDisp, Sensors[sensor0].slaveID, true);
    }
    drawWarnings(SCREENWIDTH - 24, 0, sensor0, refDisp);
    drawWarnings(SCREENWIDTH - 24, SCREENHEIGHT/2, Sensors[sensor0].slaveID, refDisp);
  } else if (Sensors[sensor0].sensetype == KTYPE) { // draw a bargraph
    if ((Sensors[sensor0].sensevals != Sensors[sensor0].senselastvals) || rotated == 1) {
      drawSensor(0, 0, refDisp, sensor0, true);
      drawBarGraph(refDisp, sensor0);
    }
    drawWarnings(SCREENWIDTH - 24, 0, sensor0, refDisp);
  } else if (Sensors[sensor0].sensetype == BOOST3BAR) { // draw a vertical bargraph
    if ((Sensors[sensor0].sensevals != Sensors[sensor0].senselastvals) || rotated == 1) {
      drawSensor(32, (SCREENHEIGHT/2)-16, refDisp, sensor0, true);
      drawVBarGraph(refDisp, sensor0);
    }
    drawWarnings(SCREENWIDTH - 24, 0, sensor0, refDisp);
  } else { // default
    if ((Sensors[sensor0].sensevals != Sensors[sensor0].senselastvals) || rotated == 1) drawBIG(refDisp, sensor0);
    drawWarnings(0, SCREENHEIGHT - 2 - 24, sensor0, refDisp);
  }
  SCREEN_DISPLAY();
}

void drawSensor(uint8_t x, uint8_t y, SCREEN_TYPE &refDisp, uint8_t sensor, bool icons)
{
  uint16_t w, h, wU, hU, wL, hL;
  int16_t  x1, y1, xU, yU, xL, yL;
  uint8_t leftpad = 0; // width of sensor glyph +2
  uint8_t charpad;
  if (icons) {
     leftpad = 34;
  }

  refDisp.setTextWrap(false);

  if (SCREENWIDTH < 128) { // we have to set the font now otherwisw getTextBounds will calculate using the wrong font
    refDisp.setFont(&FreeSansBoldOblique9pt7b); //switch to a nice ttf font 9x7
    charpad = 13;
  } else {
    refDisp.setFont(&FreeSansBoldOblique12pt7b); //switch to a nice ttf font 12x7
    charpad = 16;
  }

  refDisp.getTextBounds(getValIfNoErr(sensor, true), leftpad + x, y + 9 + charpad, &x1, &y1, &w, &h);  //find out what area we need to clear that contained previous text
  refDisp.fillRect(x1-1, y1-1, w+2 , h+2 , BLACK); //clear previous text
  //drawItem(leftpad + x, y + 9 + charpad, getValIfNoErr(sensor, false), 1, refDisp); // output the value

  refDisp.getTextBounds(getValIfNoErr(sensor, false), leftpad + x, y + 9 + charpad, &x1, &y1, &w, &h); // figure out where to draw our new units
  refDisp.getTextBounds(getValIfNoErr(sensor, true), leftpad + x, y + 9 + charpad, &xL, &yL, &wL, &hL); // figure out where we drew our previous units
  
  refDisp.setFont(); // switch to small standard font

  refDisp.getTextBounds(getUnits(sensor), xL+wL+2, y + 9, &xU, &yU, &wU, &hU); // figure out where to erase the previous units
  refDisp.fillRect(xU-1, yU-1, wU+2, hU+2, BLACK); // and erase them
  drawItem(x1+w+2, y + 9, getUnits(sensor), 1, refDisp); // draw the units symbol

  if (SCREENWIDTH < 128) {
    refDisp.setFont(&FreeSansBoldOblique9pt7b); //switch to a nice ttf font 9x7
    charpad = 13;
  } else {
    refDisp.setFont(&FreeSansBoldOblique12pt7b); //switch to a nice ttf font 12x7
    charpad = 16;
  }
  
  drawItem(leftpad + x, y + 9 + charpad, getValIfNoErr(sensor, false), 1, refDisp); // output the value - we do this over the unit to prevent edge cases where the unit erasure overwrites our new value
  
  if (icons) {
    refDisp.drawBitmap(x, y, Sensors[sensor].senseglyphs, 32, 32, GREEN);
  }
  refDisp.setFont(); //reset to basic font
}

void drawBIG(SCREEN_TYPE &refDisp, uint8_t sensor)
{
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
  refDisp.drawBitmap(SCREENWIDTH - 32, (SCREENHEIGHT - 30), Sensors[sensor].senseglyphs, 32, 32, GREEN); //draw the sensor icon
  xposition = (SCREENWIDTH / 2) - (((getUnits(sensor).length()) * charpad) / 2); // work out our drawing location
  drawItem(xposition, (SCREENHEIGHT - 6), getUnits(sensor), 1, refDisp); // and draw the units, 6 is custom font baseline adjustment
  if (SCREENWIDTH < 128) {
    refDisp.setFont(&FreeSansBoldOblique18pt7b); //switch to a nice ttf font 12x7
    charpad = 22;
  } else {
    refDisp.setFont(&FreeSansBoldOblique24pt7b); //switch to a nice ttf font 12x7
    charpad = 28;
  }

  if (Sensors[sensor].senselastvals != Sensors[sensor].sensevals) {  // only clear our textbox if the value has changed - reduces flicker
    xposition = (SCREENWIDTH / 2) - (((getValIfNoErr(sensor, true).length()) * charpad) / 2); // work out the drawing location
    refDisp.getTextBounds(getValIfNoErr(sensor, true), xposition, 34, &x1, &y1, &w, &h);  //find out what area we need to clear that contained previous text
    refDisp.fillRect(x1, y1, w, h, BLACK); //clear it
  }
  xposition = (SCREENWIDTH / 2) - (((getValIfNoErr(sensor, false).length()) * charpad) / 2); // work out the drawing location
  drawItem(xposition, 34, getValIfNoErr(sensor, false), 1, refDisp); // draw the value

  refDisp.setFont(); //reset to basic font
}

void drawBarGraph(SCREEN_TYPE &refDisp, uint8_t sensor)
{
  int padding = 0;
  float scalerange = 0;
  int scaleposmin = 0;

  refDisp.drawLine(11, 52, 11, 54, WHITE); // draw our gauge and scale markings
  refDisp.drawLine(SCREENWIDTH / 2, 52, SCREENWIDTH / 2, 54, WHITE);
  refDisp.drawLine(SCREENWIDTH - 12, 52, SCREENWIDTH - 12, 54, WHITE);
  refDisp.drawRect(11, 42, SCREENWIDTH - 22, 10, WHITE); //Border of the bar chart
  if (Sensors[sensor].senseminvals < 0) { // Work out a positive range of values that we need to plot
    scaleposmin = Sensors[sensor].senseminvals * -1;
    scalerange = scaleposmin + Sensors[sensor].sensemaxvals;
  } else {
    scaleposmin = Sensors[sensor].senseminvals;
    scalerange = Sensors[sensor].sensemaxvals - scaleposmin;
  }
  refDisp.fillRect(13, 43, SCREENWIDTH - 26, 8, BLACK);
  refDisp.fillRect(14, 44, ((SCREENWIDTH - 28) / scalerange * (Sensors[sensor].sensevals + scaleposmin)), 6, WHITE); //Draws the bar depending on the sensor value
  refDisp.drawLine(13 + ((SCREENWIDTH - 28) / scalerange * (Sensors[sensor].sensepeakvals + scaleposmin)), 41, 13 + ((SCREENWIDTH - 28) / scalerange * (Sensors[sensor].sensepeakvals + scaleposmin)), 50, WHITE); // draw the peak value line;
  if (Sensors[sensor].sensevals < 100) { // adjust padding for the low value so it looks nice
    padding = 0;
  } else {
    padding = -4;
  }
  refDisp.fillRect(0, 32, SCREENWIDTH, 10, BLACK);
  drawItem(8 + padding + ((SCREENWIDTH - 28) / scalerange * (Sensors[sensor].sensepeakvals + scaleposmin)), 33, String(Sensors[sensor].sensepeakvals), 1, refDisp); // set cursor with padding & write the peak val

  drawItem(8, 57, String(Sensors[sensor].senseminvals), 1, refDisp); // draw the low scale
  refDisp.setCursor((SCREENWIDTH / 2) - 6, 57);
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
  drawItem(SCREENWIDTH - 28 + padding, 57, String(Sensors[sensor].sensemaxvals), 1, refDisp); // draw the high scale
}


void drawVBarGraph(SCREEN_TYPE &refDisp, uint8_t sensor)
{
  float scalerange = 0;
  int scaleposmin = 0;
    
  refDisp.fillRect(10, 0, 17, SCREENHEIGHT, BLACK); //blank out peak info
  refDisp.drawLine(10, SCREENHEIGHT-1, 12, SCREENHEIGHT-1, WHITE); // low scale line
//  refDisp.drawLine(10, SCREENHEIGHT / 2, 12, SCREENHEIGHT / 2, WHITE); // mid scale line
  refDisp.drawLine(10, 0, 12, 0, WHITE); // high scale line
  refDisp.drawRect(0, 0, 10, SCREENHEIGHT, WHITE); //Border of the bar chart
 
  if (Sensors[sensor].senseminvals < 0) { // Work out a positive range of values that we need to plot
    scaleposmin = Sensors[sensor].senseminvals * -1;
    scalerange = scaleposmin + Sensors[sensor].sensemaxvals;
  } else {
    scaleposmin = Sensors[sensor].senseminvals;
    scalerange = Sensors[sensor].sensemaxvals - scaleposmin;
  }
  refDisp.fillRect(1, 1, 8, SCREENHEIGHT - 2, BLACK); // blank out the bargraph
  refDisp.fillRect(2, ((SCREENHEIGHT - 1) - ((SCREENHEIGHT - 2) / scalerange * (Sensors[sensor].sensevals + scaleposmin))), 6, ((SCREENHEIGHT - 2) / scalerange * (Sensors[sensor].sensevals + scaleposmin)), WHITE); //Draws the bar depending on the sensor value
  
  refDisp.drawLine(0, ((SCREENHEIGHT - 1) - ((SCREENHEIGHT - 2) / scalerange * (Sensors[sensor].sensepeakvals + scaleposmin))), 12, ((SCREENHEIGHT - 1) - ((SCREENHEIGHT - 2) / scalerange * (Sensors[sensor].sensepeakvals + scaleposmin))), WHITE); // draw the peak value line;
  if (((SCREENHEIGHT - 1) - ((SCREENHEIGHT - 1) - ((SCREENHEIGHT - 2) / scalerange * (Sensors[sensor].sensepeakvals + scaleposmin)))) < 8) { //this works out if we're within 8 pixels of the screen botom
     drawItem(14, SCREENHEIGHT - 8, String(Sensors[sensor].sensepeakvals), 1, refDisp); // and if so prints the value at 8 pixels below screen bottom
  } else {
     drawItem(14, ((SCREENHEIGHT - 1) - ((SCREENHEIGHT - 2) / scalerange * (Sensors[sensor].sensepeakvals + scaleposmin))), String(Sensors[sensor].sensepeakvals), 1, refDisp); // otherwise it writes it at the calculated position
  }
}


void drawItem(int x, int y, String token, int txt_size, SCREEN_TYPE &refDisp)
{
  refDisp.setCursor(x, y);
  refDisp.setTextColor(WHITE, BLACK);
  refDisp.setTextSize(txt_size);
  refDisp.print(token);
  refDisp.setTextSize(1); // Back to default text size
}

void drawWarnings(int x, int y, uint8_t sensor, SCREEN_TYPE &refDisp)
{
  if (processHiLo(sensor, true)) {
    refDisp.fillRect(x,y, 24, 24, BLACK);
    refDisp.drawBitmap(x, y, triBMP, 24, 24, RED); //outut the warning triangle
  } else if (processFaultIfSet(sensor) == 1) {
    refDisp.fillRect(x, y, 24, 24, BLACK);
    refDisp.drawBitmap(x, y, NoConn, 24, 24, YELLOW); //output the disconnected sensor icon
  } else {
    refDisp.fillRect(x, y, 24, 24, BLACK); // clear the same area
  }
}
