#ifndef _MYIRREMOTE_H
#define _MYIRREMOTE_H

#define IR_PIN 9             //Infrared receiving pin

extern unsigned long IRremote_value;
extern unsigned int IRremote_flag;

void IRremote_Setup(void);    //Infrared initialization
void IRremote_Read(void);     //Read infrared value







#endif
