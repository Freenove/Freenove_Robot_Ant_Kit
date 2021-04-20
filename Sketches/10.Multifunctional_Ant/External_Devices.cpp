#include <Arduino.h>
#include "External_Devices.h"

int power_before = 0;          //Record the last time
float power_correction = 2.5; //Power correction factor

//Battery pin initialization
void Power_Setup(void) {
  analogReference(DEFAULT);
  pinMode(POWER_PIN, INPUT);
  pinMode(POWER_AREF_PIN, INPUT);
  delay(100);
  float a=analogRead(POWER_AREF_PIN);
  Serial.println(a);
  power_correction=float(analogRead(POWER_AREF_PIN))/1023*5*32/(32+1);
  analogReference(EXTERNAL);
  power_before = millis();
}

//Get battery voltage
void Power_Get_Data(void) {
  int power_next = millis();
  if (power_next - power_before > 3000) {
    power_before = power_next;
    float adc_value = analogRead(POWER_PIN);
    adc_value = adc_value / 1024 * power_correction * 4;
    Serial.print("I#");
    Serial.println(int(adc_value * 1000));
    Serial.println(power_correction);
  }
}

//Get battery voltage
void Power_Bluetooth_Data(void) {
  float adc_value = analogRead(POWER_PIN);
  adc_value = adc_value / 1024 * power_correction * 4;
  Serial.print("I#");
  Serial.println(int(adc_value * 1000));
}

//Calibration of power supply reference voltage
void Power_Correct(float value) {
  power_correction = value;
}


//Buzzer pin initialization
void Buzzer_Setup(void) {
  pinMode(BUZZER_PIN, OUTPUT);
  Buzzer_Alarm();
}

//Buzzer control function
void Buzzer_Alarm(int frequency, int msdelay, int times) {
  for (int i = 0; i < times; i++)
  {
    tone(BUZZER_PIN, frequency);
    delay(msdelay / 2);
    noTone(BUZZER_PIN);
    delay(msdelay / 2);
  }
}

//Buzzer control function
void Buzzer_Alert(int frequency)
{
  tone(BUZZER_PIN, frequency);
  if (frequency == 0)
    noTone(BUZZER_PIN);
}










//
