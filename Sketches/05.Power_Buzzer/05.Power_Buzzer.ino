#include "External_Devices.h"

void setup() {
  Serial.begin(9600);
  Power_Setup();  //Battery pin initialization
  Buzzer_Setup(); //Buzzer pin initialization
  delay(1000);
  Buzzer_Alarm(); //Buzzer control function
}

void loop() {
  //Get the battery voltage every 3s and print it out
  Power_Get_Data();
}
