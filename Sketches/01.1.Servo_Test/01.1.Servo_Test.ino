/**********************************************************************
  Product     : Freenove Robot Ant Kit
  Description : Test the crawling of an ant robot
  Auther      : www.freenove.com
  Modification: 2021/04/20
**********************************************************************/
#include "myServo.h"

void setup() {
  Ant_Setup();
  
  //NOTE：The ant robot is adjusted by modifying the parameters.
  Ant_Correct_Angle(-1,4,1); //Calibrate ant Servo(Each robot is different, depending on your installation process)
  delay(2000);
}

void loop() {
  ant_run_forth(2,7);//Forward
  delay(1000);
  ant_run_back(2,7);//Backwards
  delay(1000);
  ant_run_left(4,7);//Forward to the left
  delay(1000);
  ant_run_right(4,7);//Forward to the right
  delay(1000);
  ant_run_situ_left(2,7);//Turn left in situ
  delay(1000);
  ant_run_situ_right(2,7);//Turn right in situ
  delay(1000);
}
