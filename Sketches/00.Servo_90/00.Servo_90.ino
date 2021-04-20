/**********************************************************************
  Product     : Freenove Robot Ant Kit
  Description : Calibrate the Servo's Angle
  Auther      : www.freenove.com
  Modification: 2021/04/20
**********************************************************************/
#include <Servo.h>

Servo myservo1;
Servo myservo2;
Servo myservo3;

int forth_angle  = 90 ;      //Forth servo value
int middle_angle = 90 ;      //Middle servo value
int back_angle   = 90 ;      //Back servo value

void setup() {
  ant_setup();               //Initialize the servo
  ant_correct_angle(0,0,0);  //Calibrate the servo value
  ant_reset_angle();         //Restore initial state
}

void loop() {

}

//Initialize the servo
void ant_setup() {
  myservo1.attach(2);
  myservo2.attach(3);
  myservo3.attach(4);
}

//Calibrate the servo value
void ant_correct_angle(int angle1, int angle2, int angle3) {
  forth_angle  = 90 + angle1;
  middle_angle = 90 + angle2;
  back_angle   = 90 + angle3;
}

//Restore initial state
void ant_reset_angle() {
  myservo1.write(forth_angle);
  myservo2.write(middle_angle);
  myservo3.write(back_angle);
}







//
