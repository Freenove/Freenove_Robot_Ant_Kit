#include "myIRremote.h"

void setup() {
  Serial.begin(9600);
  IRremote_Setup();//Initialize the infrared receiving pin
}

void loop() {
  IRremote_Read();//Read the infrared key value
  if(IRremote_flag==1)//If the infrared key value is received,IRremote_flag=1
  {
     IRremote_flag = 0;
     Serial.println(IRremote_value, HEX); 
  }
  else if (IRremote_flag == 2)//If you press the button long enough,IRremote_flag=2
  {
    IRremote_flag = 0;
    Serial.println(IRremote_value, HEX);
  }
}
