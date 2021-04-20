#ifndef _ULTRASONIC_H
#define _ULTRASONIC_H

#define Ultrasonic_Trig 8
#define Ultrasonic_Echo 7
#define Temperature_Compensation 25

extern int Ultrasonic_Value;               //Ultrasonic distance

void Ultrasonic_Setup(void);               //Ultrasonic initialization
int Ultrasonic_Get_Data(int delayms=1000); //Ultrasonic get distance value
void Ultrasonic_Bluetooth_Data(void);      //Ultrasonic send distance value








#endif
