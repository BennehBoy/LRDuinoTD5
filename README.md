## LRDuinoTD5 - ISO14230-1
In car multi gauge system -  STM32, ESP32, SSD1306, SSD1331, SSD1351, MAX31856, L9637D, TD5 ECU

I started this project so that I could monitor some parts on my tuned Land Rover Discovery TD5 that are not covered by the stock ECU.  This does not mean that LRDuino is limited to use in any way on Land Rovers alone, even if they are the best 4x4 by far.

### Latest version (0.13) can be used with
* Maple Mini (or chinese copy) using core: https://github.com/rogerclarkmelbourne/Arduino_STM32
* Blue Pill using core: https://github.com/rogerclarkmelbourne/Arduino_STM32
* Black Pill  using core: https://github.com/rogerclarkmelbourne/Arduino_STM32
* Black 407VET6 using core: https://github.com/stm32duino/Arduino_Core_STM32
* Black 407ZET6 using core: https://github.com/stm32duino/Arduino_Core_STM32
* Black 407ZGT6 using core: https://github.com/stm32duino/Arduino_Core_STM32
* DIYMROE_F407VGT using core: https://github.com/stm32duino/Arduino_Core_STM32
* FK407M1 using core: https://github.com/stm32duino/Arduino_Core_STM32
* NodeMCU-32S ESP32 using Espressif Core: https://github.com/espressif/arduino-esp32

### Sensor types currently supported:  
* NTC based coolant sensor - Bosch 0 280 130 026 / Land Rover ERR2081  
* MAX31856 Digital Thermocouple  (this is connected via SPI2)
* Generic linear output MAP sensors - for vehicle boost
* Generic linear output pressure sensors - eg for oil
* TD5 Ecu PID's via K-Line/Serial Emulator - https://github.com/BennehBoy/TD5EcuEmulatorMM

### Display types supported:
* SSD1306 - Monochrome 128*96 OLED
* SSD1331 - Full colour 96*64 OLED
* SSD1351 - Full colour 128*128 OLED
Adding additional diaplsy (which have Adafruit libraries) should be as simple as adding a section to Macros.h and an ifdef section in LRDuinoTD5.ino

### Datalogging to micro SD card
* Micro SD 3.3v shields
* SDIO on board micro SD

## License

The source code of this project are released under "THE BEER-WARE" license.

I would, however, consider it a great courtesy if you could email me and tell me about your project and how this code was used, just for my own continued personal gratification :)

## Contribution

Contributions in all forms (including documentation) are welcomed. If you would like to contribute to this project, then just fork it in github and send a pull request.

## References

* STM32Duino - http://www.stm32duino.com
* Adafruint Graphics Library - https://github.com/adafruit/Adafruit-GFX-Library
* Custom Max31586 code - https://forum.arduino.cc/index.php?topic=390824.0
* ArduinoMenu - https://github.com/neu-rah/ArduinoMenu
* TD5 Open Com (by Luca72) - http://luca72.xoom.it/td5mapsuiteweb/archive/td5opencom/
* TD5 KeyGen - https://github.com/pajacobson/td5keygen

## Limitations

* ESP32 support is only in the inital stages - ADC & MAX31586 not yet tested.
* Hardware setup for serial to K-line conversion not yet documented