// Sensor reading code.

int readERR2081(uint8_t sensor, uint8_t index)
{
  int raw = 0;     // variable to store the raw ADC input value
  float Vin = 3.3; // variable to store the measured VCC voltage
  float Vout = 0;  // variable to store the output voltage
  int R2 = 1000;   // variable to store the R2 value
  float Rth = 0;   // variable to store the thermistor value

  raw = analogRead(sensor);      // Reads the Input PIN
  Vout = (Vin / DIVISOR) * raw;     // Calculates the Voltage on the Input PIN
  Rth = ((R2 * Vin) / Vout) - R2;   // Calculates the Resistance of the Thermistor
  float steinhart;                  // This next stage calculates the temp from the resistance
  steinhart = Rth / 2012.2;         // (R/Ro)  therm @ 25C = 1986
  steinhart = log(steinhart);       // ln(R/Ro)
  steinhart /= 3502;                // 1/B * ln(R/Ro) b coefficient = 3344
  steinhart += 1.0 / (25 + 273.15); // + (1/To) nominal temp is 25c
  steinhart = 1.0 / steinhart;      // Invert
  steinhart -= 273.15;              // convert to C
  // FAULT checking
  // Sensors should be connected with a 1K pulldown resistor - if there's is a connection fault a low raw read will indicate this.
  return (processConstraints(DIVISOR / 100, raw, int(steinhart), index));
}

int readBoost(uint8_t sensor, uint8_t index)
{
  int rawval;
  float kpaval;
  float boost;
  //Sensor slope = MaxV - MinV / MaxP - MinP    ==   2640 - 0 / 4000 - 0   === 0.66 mv per millibar  -1bar = 1v 0bar = 2v 1 bar =3v  (2640 is equivalent of 3bar at 4v when using 2.3v logic)
  //mv per ADC = 3300mv/4095 = 0.80586
  //mb per ADC = 0.80586/0.66   == 1.221
  //offset = 330/0.80586 = 409 ADC's
  rawval = analogRead(sensor);    // Read MAP sensor raw value on analog port 0
  kpaval = (rawval * 1.221)/10;  // convert to kpa
  boost = (kpaval * 0.145038) - 14.5038;  // Convert to psi and subtract atmospheric (sensor is absolute pressure)
  
  // process any faults
  // Sensors should be connected with a 10K / 20K pulldown dividor to map the 5v output to 3.3v
  Serial.println(rawval);
  return (processConstraints(DIVISOR / 100, rawval, int(boost), index));
}

int readMAX(uint8_t index)
{
  int t = int(MAXReadTemperature(MAX_CS));
  // process any faults
  return (processConstraints(MAXreadFault(MAX_CS), 0, t, index));
}

int readPress(uint8_t sensor, uint8_t index)
{
  int rawval;
  long kpaval;
  long oilpress;
  //100 psi Chinese Transducer
  //Sensor slope = MaxV - MinV / MaxP - MinP    ==   3000 - 333 / 6894 - 0   === 0.386 mv per millibar  0.5v @ 0psi 4.5v @100psi
  //mv per ADC = 3300mv/4095 = 0.80586
  //mb per ADC = 0.80586/0.386   == 2.0877
  //offset = 330/0.80586 = 409 ADC's
  rawval = analogRead(sensor);       // Read MAP sensor raw value on analog port 0
  kpaval = ((rawval - 409) * 2.0877) / 10;         // convert to kpa
  oilpress = (kpaval * 0.145038); //Convert to psi - sensor is already relative to atmospheric
  // process any faults
  // Sensors should be connected with a 10K / 20K pulldown dividor to map the 5v output to 3.3v
  return (processConstraints(DIVISOR / 100, rawval, int(oilpress), index));
}

bool readCoolantLevel(uint8_t sensor, uint8_t index)
{
  // sensor is normally closed
  // use a pulldown resistor to enable fault monitoring
  int CoolantLevel;
  CoolantLevel = analogRead(sensor);
  // process any faults
  return ((bool)processConstraints(DIVISOR / 2, CoolantLevel, CoolantLevel, index));
}

// MAX31856 SPI CODE

void MAXInitializeChannel(int Pin)
{
  for (int i = 0; i < NumRegisters; i++) {
    MAXWriteRegister(Pin, i, RegisterValues[i]);
  }
}

uint8_t MAXreadFault(int Pin)
{
  return MAXReadSingleRegister(Pin, 0x0F);
}

byte MAXReadSingleRegister(int Pin, byte Register)
{
  SPI_2.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE3));
  digitalWrite(Pin, LOW);
  delayMicroseconds(1);
  SPI_2.transfer(Register & 0x7F); //set bit 7 to 0 to ensure a read command
  delayMicroseconds(1);
  byte data = SPI_2.transfer(0);
  digitalWrite(Pin, HIGH);
  SPI_2.endTransaction();
  return data;
}

unsigned long MAXReadMultipleRegisters(int Pin, byte StartRegister, int count)
{
  //reads up to 4 sequential registers
  SPI_2.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE3));
  digitalWrite(Pin, LOW);
  unsigned  long data = 0;
  SPI_2.transfer(StartRegister & 0x7F); //force bit 7 to 0 to ensure a read command
  delayMicroseconds(1);

  for (int i = 0; i < count; i++) {
    data = (data << 8) | SPI_2.transfer(0); //bitshift left 8 bits, then add the next register
  }
  digitalWrite(Pin, HIGH);
  SPI_2.endTransaction();
  return data;
}

void MAXWriteRegister(int Pin, byte Register, byte Value)
{
  byte Address = Register | 0x80; //Set bit 7 high for a write command
  SPI_2.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE3));
  digitalWrite(Pin, LOW);
  delayMicroseconds(1); // required by the MAX docs
  SPI_2.transfer(Address);
  delayMicroseconds(1);
  SPI_2.transfer(Value);
  digitalWrite(Pin, HIGH);
  SPI_2.endTransaction();
}

double MAXReadTemperature(int Pin)
{
  double temperature;
  long data;
  data = MAXReadMultipleRegisters(Pin, 0x0C, 4);
  // Strip the unused bits and the Fault Status Register
  data = data >> 13;
  // Negative temperatures have been automagically handled by the shift above :-)
  // Convert to Celsius
  temperature = (double) data * 0.0078125;
  // Return the temperature
  return (temperature);
}
