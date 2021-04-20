/**********************************************************************
  Product     : Freenove Robot Ant Kit
  Description : Ultrasonic obstacle avoidance ant robot
  Auther      : www.freenove.com
  Modification: 2021/04/20
**********************************************************************/
#include "Ultrasonic.h"
#include "myServo.h"

void setup() {
  Ultrasonic_Setup();
  Ant_Setup();
  delay(2000);
}

void loop() {
  Ultrasonic_Get_Data(100);
  if (Ultrasonic_Value >= 40)
    ant_run_forth(2, 5); //Forward      //Forward
  else if (Ultrasonic_Value >= 20 && Ultrasonic_Value < 40)
    ant_run_left(2, 5);       //Forward to the left
//  ant_run_right(2, 5);      //Forward to the right
  else if (Ultrasonic_Value >= 10 && Ultrasonic_Value < 20)
    ant_run_situ_left(2, 5);  //Turn left in situ
//  ant_run_situ_right(2, 5); //Turn right in situ
  else
    ant_run_back(2, 5);       //Backwards
}
