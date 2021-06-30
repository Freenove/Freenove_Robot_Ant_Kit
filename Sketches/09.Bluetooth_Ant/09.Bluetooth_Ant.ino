/**********************************************************************
  Product     : Freenove Robot Ant Kit
  Description : Bluetooth module remote control ant robot
  Auther      : www.freenove.com
  Modification: 2021/04/20
**********************************************************************/
#include "BluetoothOrders.h"
#include "myServo.h"

int Ant_Move_Direction = 0; //Direction of ant movement
int Ant_Move_Speed = 0;     //Ant speed

void setup() {
  Bluetooth_Setup();
  Ant_Setup();
  
  //NOTE：The ant robot is adjusted by modifying the parameters.
  Ant_Correct_Angle(-1,4,1); //Calibrate ant Servo(Each robot is different, depending on your installation process)
}

void loop() {
  if (stringComplete){//Get the Bluetooth command
    Deal_Serial_Data();
    char commandChar = inputCommandArray[0].charAt(0);//Gets the first character of the inputCommandArray[0]
    if(commandChar==ACTION_MOVE){
        Ant_Move_Direction = paramters[1];
        Ant_Move_Speed = paramters[2];
    } 
    inputCommandArray[0] = "";
  }
  else{
    if (Ant_Move_Direction == 0)//Restore initial state
      ant_reset_angle();
    else if (Ant_Move_Direction == 1)//Forward
      ant_move_forth(2, 5+2*Ant_Move_Speed);
    else if (Ant_Move_Direction == 2)//Backwards
      ant_move_back(2, 5+2*Ant_Move_Speed);
    else if (Ant_Move_Direction == 3)//Forward to the left
      ant_move_left(4, 5+2*Ant_Move_Speed);
    else if (Ant_Move_Direction == 4)//Forward to the right
      ant_move_right(4, 5+2*Ant_Move_Speed);
    else if (Ant_Move_Direction == 5)//Turn left in situ
      ant_situ_left(2, 5+2*Ant_Move_Speed);
    else if (Ant_Move_Direction == 6)//Turn right in situ
      ant_situ_right(2, 5+2*Ant_Move_Speed);
  }
}
