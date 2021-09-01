/**********************************************************************
  Product     : Freenove Robot Ant Kit
  Description : Integrate all the functions of Ant Robot
  Auther      : www.freenove.com
  Modification: 2021/04/20
**********************************************************************/
#include "BluetoothOrders.h"
#include "Emotion.h"
#include "External_Devices.h"
#include "Ultrasonic.h"
#include "WS2812.h"
#include "myIRremote.h"
#include "myServo.h"

bool Sonic_Mode = 0;        //Ultrasonic mode
int Ant_Move_Direction = 0; //Direction of ant movement
int Ant_Move_Speed = 0;     //Ant speed

void setup() {
  Buzzer_Setup();           //Buzzer pin initialization
  Emotion_Setup();          //Initializes the Led Matrix
  Power_Setup();            //Battery pin initialization
  Ultrasonic_Setup();       //Ultrasonic initialization
  WS2812_Setup();           //WS2812 initialization function
  IRremote_Setup();         //IR initialisation
  Ant_Setup();              //Initialize the servo
  Bluetooth_Setup();        //Test whether the Bluetooth is connected
  
  Ant_Correct_Angle(1,1,1); //Change the patament of Ant_Correct_Angle(x1, x2, x3) tp calibrate ant Servo
  delay(100);

}

void loop() {
  if (Sonic_Mode == 1){//Ultrasonic obstacle avoidance mode
    //Get the distance value every 1s and store it in the Ultrasonic_Value
    Ultrasonic_Get_Data();
    if (Ultrasonic_Value >= 40)
      Ant_Move_Direction = 1;//Forward
    else if (Ultrasonic_Value >= 20 && Ultrasonic_Value < 40)
      Ant_Move_Direction = 3;//Forward to the left
    else if (Ultrasonic_Value >= 10 && Ultrasonic_Value < 20)
      Ant_Move_Direction = 5;//Turn right in situ
    else
      Ant_Move_Direction = 2;//Backwards
  }
  if (IRremote_flag != 0){//Get the infrared command
    IRremote_flag = 0;
    switch (IRremote_value){
      case 0xFFA25D://Restore initial state
        Ant_Move_Direction = 0;
        break;
      case 0xFF02FD://Forward
        Ant_Move_Direction = 1;
        break;
      case 0xFF9867://Backwards
        Ant_Move_Direction = 2;
        break;
      case 0xFFE01F://Forward to the left
        Ant_Move_Direction = 3;
        break;
      case 0xFF906F://Forward to the right
        Ant_Move_Direction = 4;
        break;
      case 0xFF22DD://Turn left in situ
        Ant_Move_Direction = 5;
        break;
      case 0xFFC23D://Turn right in situ
        Ant_Move_Direction = 6;
        break;
      case 0xFFE21D://Buzzer 100ms
        Buzzer_Alarm();
        break;
      case 0xFFA857://Move speed control
        Ant_Move_Speed--;
        if (Ant_Move_Speed < 0)
          Ant_Move_Speed = 2;
        break;
      case 0xFF6897://Ultrasonic mode on
        Sonic_Mode = 1;
        Buzzer_Alarm();
        break;
      case 0xFFB04F://Ultrasonic mode off
        Sonic_Mode = 0;
        Ant_Move_Direction = 0;
        Buzzer_Alarm();
        break;
      case 0xFF30CF://WS2812 RED On/Off
        WS2812_Set_LED(1, 0, 0);
        break;
      case 0xFF18E7://WS2812 GREEN On/Off
        WS2812_Set_LED(0, 1, 0);
        break;
      case 0xFF7A85://WS2812 BLUE On/Off
        WS2812_Set_LED(0, 0, 1);
        break;
      case 0xFF10EF://WS2812 set mode
        ws2812_task_mode++;
        if (ws2812_task_mode > 5)
          ws2812_task_mode = 0;
        break;
      case 0xFF38C7://Display animated emoticons
        emotion_count = 0;
        emotion_task_mode++;
        if (emotion_task_mode > 6)
          emotion_task_mode = 0;
        break;
      case 0xFF5AA5://Display static emotions
        Emotion_SetMode(7);
        break;
      default:
        break;
    }
  }
  if (stringComplete){//Get the Bluetooth command
    Deal_Serial_Data();
    char commandChar = inputCommandArray[0].charAt(0);
    if (commandChar == ACTION_MOVE){//Control ant movement
      if (Sonic_Mode != 0){
        Sonic_Mode = 0;
        Buzzer_Alarm();
      }
      Ant_Move_Direction = paramters[1];
      Ant_Move_Speed = paramters[2];
    }
    if (commandChar == ACTION_EMOTION){//Control expression module display
      if (paramters[1] <= 7)
        Emotion_SetMode(paramters[1]);
      else if (paramters[1] > 7)
        Emotion_SetMode(paramters[1], paramters[2]);
    }
    if (commandChar == ACTION_RGB){//Control WS2812 display
      WS2812_SetMode(paramters[1]);
      WS2812_Set_Color(paramters[2], paramters[3], paramters[4]);
    }
    if (commandChar == ACTION_BUZZER)//Control the buzzer sound
      Buzzer_Alert(paramters[1]);
    if (commandChar == ACTION_ULTRASONIC)//Get ultrasonic distance value
      Ultrasonic_Bluetooth_Data();
    if (commandChar == ACTION_CAR_MODE){//Ultrasonic mode
      int cmd_mode = constrain(paramters[1], 0, 1);
      Sonic_Mode = cmd_mode;
      if (Sonic_Mode == 0)
        Ant_Move_Direction = 0;
      Buzzer_Alarm();
    }
    if (commandChar == ACTION_GET_VOLTAGE)//Get battery voltage
      Power_Bluetooth_Data();
    inputCommandArray[0] = "";
  }
  else{//Execute code without blocking
    IRremote_Read();//Non - blocking access to infrared commands
    Ant_Servo_Mode(Ant_Move_Direction, Ant_Move_Speed);//Non-blocking ant motion function
    Emotion_Show();//Non-blocking expression module display function
    WS2812_Show();//Non-blocking color light display function
  }
}
