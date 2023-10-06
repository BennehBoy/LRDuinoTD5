## LRDuinoTD5 - ISO14230-1
In car multi gauge system -  STM32, OLED Display (SSD1306, SSD1331, SSD1351), MAX31856 (EGT)

I started this project so that I could monitor some parts on my tuned Land Rover Discovery TD5 that are not covered by the stock ECU.  This does not mean that LRDuino is limited to use in any way on Land Rovers alone, even if they are the best 4x4 by far.

Latest release no longer supports Roger Clarke's STM32 core -> https://github.com/rogerclarkmelbourne/Arduino_STM32 and no longer supports ESP32 (but it should be trivial to port it)

The project has been simplified to remove some bloat, data loggins, menus, roll meter & animations, etc.

I'm currently working on a fuel consumption gauge - this is WIP in the moment but should provide litres per 100k or MPG output - trip based only.

You can use buttons or a rotary encoder for input, only 1 button is really requried, but with 2 you can go forward or backward through the sensors.  #define ENCODER to use a rotary encoder.  Place a copy of the supplied encoder folder and contents in your arduino libraries folder.

### Requirements
* Adafruit_GFX
* Adafruit library matching your OLED
* MAX31856 & K-type thermocouple - will function without this (you can disable EGT in td5sensors.h by setting the sensor first parameter to false (see the Sensors array)
* L9637D or ECU Emulator wired up appropriately - will function without either
* supported microcontroller, see below.

### Latest version (0.19) can be used with
* Maple Mini (or clone)
* Blue Pill
* Black Pill
* Black Pill F303
* Black 407VET6
* Black 407ZET6
* Black 407ZGT6
* DIYMROE_F407VGT 
* FK407M1 
* almost any reasonably powerful STM32 microcontroller, but you will need to update the code to cater for pinout differences & the board definitio name

### Sensor types currently supported:
  *NTC based coolant sensor - Bosch 0 280 130 026 / Land Rover ERR2081
  *MAX31856 Digital Thermocouple(this is connected via SPI2)
  *Generic linear output MAP sensors - for vehicle boost
  *Generic linear output pressure sensors - eg for oil
  *OBD sensors via the TD5 ECU connector (schematics for interfacing via an L9637D to follow.  You can also interface directly with the TD5 ECU Emulator also available in my github - note that you will have to comment out echo suppression in td5comm.cpp, look for read_byte(&fluff); and comment this out.

### Display types supported:
    *SSD1306 - Monochrome 128 * 96 OLED
    *SSD1331 - Full colour 96 * 64 OLED
    *SSD1351 - Full colour 128 * 128 OLED
    Adding additional displays (which have Adafruit libraries) should be as simple as adding a section to Macros.h and an ifdef section in LRDuinoTD5.ino


## License

      The source code of this project are released under "THE BEER-WARE" license.

I would, however, consider it a great courtesy if you could email me and tell me about your project and how this code was used, just for my own continued personal gratification :)

## Contribution

        Contributions in all forms(including documentation) are welcomed. If you would like to contribute to this project, then just fork it in github and send a pull request.

## References

*STM32Duino - http ://www.stm32duino.com
* Adafruint Graphics Library - https : //github.com/adafruit/Adafruit-GFX-Library
* Custom Max31586 code - https : //forum.arduino.cc/index.php?topic=390824.0
* ArduinoMenu - https : //github.com/neu-rah/ArduinoMenu

## Limitations

* Many
