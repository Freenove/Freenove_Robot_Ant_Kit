/**********************************************************************
  Product     : Freenove Robot Ant Kit
  Description : Test the crawling of an ant robot
  Auther      : www.freenove.com
  Modification: 2021/04/20
**********************************************************************/
#include "myServo.h"

void setup() {
  Ant_Setup();
  delay(2000);
}

void loop() {
  Ant_Servo_Mode(0);//Restore initial state
//  Ant_Servo_Mode(1);//Forward
//  Ant_Servo_Mode(2);//Backwards
//  Ant_Servo_Mode(3);//Forward to the left
//  Ant_Servo_Mode(4);//Forward to the right
//  Ant_Servo_Mode(5);//Turn left in situ
//  Ant_Servo_Mode(6);//Turn right in situ
}
