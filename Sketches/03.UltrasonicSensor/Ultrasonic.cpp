#include <Arduino.h>
#include <UltrasonicSensor.h>
#include "Ultrasonic.h"

UltrasonicSensor ultrasonic(Ultrasonic_Trig, Ultrasonic_Echo);

int Ultrasonic_Value = 0;

int ultrasonic_before = 0;
int ultrasonic_next = 0;

//Ultrasonic initialization
void Ultrasonic_Setup(void)
{
  ultrasonic.setTemperature(Temperature_Compensation);
  ultrasonic_before = millis();
}

//Ultrasonic get distance value
int Ultrasonic_Get_Data(int delayms)
{
  ultrasonic_next = millis();
  delayms=constrain(delayms,0,32767);
  if (ultrasonic_next - ultrasonic_before >= delayms){
    ultrasonic_before = ultrasonic_next;
    Ultrasonic_Value = ultrasonic.distanceInCentimeters();
    Serial.print("E#");
    Serial.println(Ultrasonic_Value);
    return Ultrasonic_Value;
  }
}

//Ultrasonic send distance value
void Ultrasonic_Bluetooth_Data(void)
{
  int Sonic_Value = ultrasonic.distanceInCentimeters();
  Serial.print("E#");
  Serial.println(Sonic_Value);
}
