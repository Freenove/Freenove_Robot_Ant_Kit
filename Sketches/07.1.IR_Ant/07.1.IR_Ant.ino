/**********************************************************************
  Product     : Freenove Robot Ant Kit
  Description : Infrared remote control ant robot
  Auther      : www.freenove.com
  Modification: 2021/04/20
**********************************************************************/
#include "myIRremote.h"
#include "myServo.h"

int Ant_State = 0;//Stores received instructions

void setup() {
  Serial.begin(9600);
  IRremote_Setup(); //Initialize the infrared receiver pin
  Ant_Setup();      //Initialize Servo
  
  //NOTE：The ant robot is adjusted by modifying the parameters.
  Ant_Correct_Angle(-1,4,1); //Calibrate ant Servo(Each robot is different, depending on your installation process)
}

void loop() {
  IRremote_Read();//Read the infrared key value
  if (IRremote_flag == 1){
    IRremote_flag = 0;
    Serial.println(IRremote_value, HEX);
    if (IRremote_value == 0xFFA25D)      //Restore initial state
      Ant_State = 0;
    else if (IRremote_value == 0xFF02FD) //Forward
      Ant_State = 1;
    else if (IRremote_value == 0xFF9867) //Backwards
      Ant_State = 2;
    else if (IRremote_value == 0xFFE01F) //Forward to the left
      Ant_State = 3;
    else if (IRremote_value == 0xFF906F) //Forward to the right
      Ant_State = 4;
    else if (IRremote_value == 0xFF22DD) //Turn left in situ
      Ant_State = 5;
    else if (IRremote_value == 0xFFC23D) //Turn right in situ
      Ant_State = 6;
  }
  else if (IRremote_flag == 2){
    IRremote_flag = 0;
    Serial.println(IRremote_value, HEX);
  }
  else{
    if (Ant_State == 0)//Restore initial state
      ant_reset_angle();
    if (Ant_State == 1)//Forward
      ant_move_forth(2, 5);
    else if (Ant_State == 2)//Backwards
      ant_move_back(2, 5);
    else if (Ant_State == 3)//Forward to the left
      ant_move_left(4, 7);
    else if (Ant_State == 4)//Forward to the right
      ant_move_right(4, 7);
    else if (Ant_State == 5)//Turn left in situ
      ant_situ_left(2, 7);
    else if (Ant_State == 6)//Turn right in situ
      ant_situ_right(2, 7);
  }
}
