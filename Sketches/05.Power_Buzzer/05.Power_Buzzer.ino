/**********************************************************************
  Product     : Freenove Robot Ant Kit
  Description : Test the battery level and the buzzer
  Auther      : www.freenove.com
  Modification: 2021/04/20
**********************************************************************/
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
