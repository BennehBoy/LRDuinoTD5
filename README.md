# LRDuinoTD5 - ISO14230-1
In car multi gauge system -  STM32, SSD1306, MAX31856, ADXL345, L9637D, TD5 ECU

This is a fork of my other project LRDuino.  This version is for direct k-line interface to a Land Rover TD5 ECU.  The other version utilises a bluetooth linked ELM327.

I started this project so that I could monitor some parts on my tuned Land Rover Discovery TD5 that are not covered by the stock ECU.  This does not mean that LRDuino is limited to use in any way on Land Rovers alone, even if they are the best 4x4 by far.

Video of bench test system running (version 0.94)  
[![Version 0.94 Video](https://img.youtube.com/vi/KDIy4PNw3LQ/0.jpg)](https://www.youtube.com/watch?v=KDIy4PNw3LQ)

Sensor types currently supported:  
NTC based coolant sensor - Bosch 0 280 130 026 / Land Rover ERR2081  
MAX31856 Digital Thermocouple  
ADXL345 Accelerometer (for vehicle roll when off roading)  
Generic linear output MAP sensors - for vehicle boost
Generic linear output pressure sensors - eg for oil
TD5 Ecu PID's via K-Line

# License

The source code of this project are released under "THE BEER-WARE" license.

I would, however, consider it a great courtesy if you could email me and tell me about your project and how this code was used, just for my own continued personal gratification :)

# Contribution

Contributions in all forms (including documentation) are welcomed. If you would like to contribute to this project, then just fork it in github and send a pull request.

# References

STM32Duino - http://www.stm32duino.com

Adafruint Graphics Library - https://github.com/adafruit/Adafruit-GFX-Library

ELM327 Library - https://github.com/irvined1982/arduino-ELM327

Custom Max31586 code - https://forum.arduino.cc/index.php?topic=390824.0

Fabo ADXL345 library - https://github.com/FaBoPlatform/FaBo3Axis-ADXL345-Library

ArduinoMenu - https://github.com/neu-rah/ArduinoMenu

TD5 Open Com (by Luca72) - http://luca72.xoom.it/td5mapsuiteweb/archive/td5opencom/

TD5 KeyGen - https://github.com/pajacobson/td5keygen