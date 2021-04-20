#include "Ultrasonic.h"

void setup() {
  Serial.begin(9600);
  Ultrasonic_Setup();//Ultrasonic initialization
}

void loop() {
  Ultrasonic_Get_Data();//Ultrasonic get distance value
}
