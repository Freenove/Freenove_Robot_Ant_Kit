/**********************************************************************
  Product     : Freenove Robot Ant Kit
  Description : Test ultrasonic module
  Auther      : www.freenove.com
  Modification: 2021/04/20
**********************************************************************/
#include "Ultrasonic.h"

void setup() {
  Serial.begin(9600);
  Ultrasonic_Setup();//Ultrasonic initialization
}

void loop() {
  Ultrasonic_Get_Data();//Ultrasonic get distance value
}
