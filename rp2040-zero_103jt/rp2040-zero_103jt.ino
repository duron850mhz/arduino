#include <math.h>

#define THERMISTOR_PIN1 26
#define THERMISTOR_PIN2 27

const float DIVIDER = 10000.0; // 分圧抵抗10kΩ

const float T0 = 273.15;
const float R0 = 27700.0;
const float B = 3435.0;

float calcTemp(float Rt) {
  float T_bar = 1/T0 + 1/B * log(Rt/R0);
  return 1.0/T_bar - 273.15;
}

void setup() {
  Serial.begin(9600);
  pinMode(THERMISTOR_PIN1, INPUT);
  pinMode(THERMISTOR_PIN2, INPUT);
}

void loop() {
  float Aout1 =  float(analogRead(THERMISTOR_PIN1));
  float Rt1 = DIVIDER * Aout1 / (1024.0 - Aout1);
  float temp1 = calcTemp(Rt1);
  
  float Aout2 =  float(analogRead(THERMISTOR_PIN2));
  float Rt2 = DIVIDER * Aout2 / (1024.0 - Aout2);
  float temp2 = calcTemp(Rt2);
  
  Serial.print("Temp1:");
  Serial.print(temp1);
  Serial.print(" Temp2:");
  Serial.println(temp2);
  delay(1000);
}