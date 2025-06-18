#include <Wire.h>
//  init ADS1015
void ADS1015_init() {
  //  init i2c as a master
  Wire.begin();
}
#define ADS1015_ADDR 0x48
//  triger conversion on An
void ADS1015_trigger(int n) {
  //  trigger conversion
  Wire.beginTransmission(ADS1015_ADDR);
  Wire.write(0x01);               //  to "config"
  Wire.write(0xc3 | (n << 4));    //  OS=1,MUX=1nn,PGA=001(x1),MODE=1(single)
  Wire.write(0xe3);               //  DR=111(3300SPS),00011(no comparator)
  Wire.endTransmission();
}
//  read conversion result
int ADS1015_read() {
  short int value;
  //  read out the result
  Wire.beginTransmission(ADS1015_ADDR);
  Wire.write(0x00);               //  to "conversion"
  Wire.endTransmission();
  Wire.requestFrom(ADS1015_ADDR, 2);  //  read out 2 bytes
  value = Wire.read() << 8;  value |= Wire.read();
  //  return -2048..+2047
  return value / 16;              //  0V=0, 4.096V=2047, 3.3V=1649
}
//  main program
int chan;
int values[4];
void setup() {
  //  serial for debugging
  Serial.begin(115200);
  Serial.println("*** started");
  //  trigger first conversion (on A0)
  chan = 0;
  ADS1015_init();
  ADS1015_trigger(chan);
}
void loop() {
  //  read out the result
  values[chan] = ADS1015_read();
  //  trigger next conversion
  chan = (chan + 1) % 4;    //  0,1,2,3,0,1,2,3...
  ADS1015_trigger(chan);
  //  delay (minimum 0.3ms)
  delay(10);
  //  output to monitor
  if (chan == 0) {
      Serial.print("  "); Serial.print(values[0]);
      Serial.print(", "); Serial.print(values[1]);
      Serial.print(", "); Serial.print(values[2]);
      Serial.print(", "); Serial.print(values[3]);
      Serial.println("");
  }
}