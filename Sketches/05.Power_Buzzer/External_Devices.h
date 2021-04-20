#ifndef _EXTERNAL_DEVICES_H
#define _EXTERNAL_DEVICES_H

#define POWER_PIN        A0                                           //Power pin
#define POWER_AREF_PIN   A1                                           //Aref pin
#define BUZZER_PIN       5                                            //Buzzer pin

void Power_Setup(void);                                               //Battery pin initialization
void Power_Correct(float value);                                      //Calibration of power supply reference voltage
void Power_Bluetooth_Data(void);                                      //Get battery voltage
void Power_Get_Data(void);                                            //Get battery voltage


void Buzzer_Setup(void);                                              //Buzzer pin initialization
void Buzzer_Alarm(int frequency=1000, int msdelay=100, int times=1);  //Buzzer control function
void Buzzer_Alert(int frequency);                                     //Buzzer control function

















#endif
