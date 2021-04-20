#include <Arduino.h>
#include "myIRremote.h"

unsigned long IRremote_value = 0;
unsigned int IRremote_flag = 0;

unsigned int irremote_state = 0;
unsigned int irremote_time = 0;
unsigned int irremote_before = 0;
unsigned int irremote_next = 0;
unsigned long verify_value = 0;

void IRremote_Setup()
{
  pinMode(IR_PIN, INPUT);
  irremote_before = micros();
}

void IRremote_Read() {
  irremote_next = micros();
  if (irremote_next - irremote_before >= 100)
  {
    irremote_before = micros();
    if (digitalRead(IR_PIN) == LOW && irremote_state == 0)
    {
      irremote_state = 1;
      irremote_time = 0;
    }
    if (digitalRead(IR_PIN) == LOW && irremote_state == 1)
    {
      irremote_time++;
      if (irremote_time >= 100)
      {
        return ;
      }
    }
    if (digitalRead(IR_PIN) == HIGH && irremote_state == 1)
    {
      irremote_state = 2;
      irremote_time = 0;
    }
    if (digitalRead(IR_PIN) == HIGH && irremote_state == 2)
    {
      irremote_time++;
      if (irremote_time >= 100)
      {
        return ;
      }
    }
    if (digitalRead(IR_PIN) == LOW && irremote_state == 2)
    {
      if (irremote_time <= 25)
      {
        irremote_state = 10;
        IRremote_value = 0xffffffff;
      }
      else
        irremote_state = 3;
      irremote_time = 0;
    }
    if (irremote_state == 3)
    {
      unsigned long IRCOM[4];
      for (int j = 0; j < 4; j++)
      {
        IRCOM[j] = 0;
        for (int k = 0; k < 8; k++)
        {
          while (!digitalRead(IR_PIN));
          irremote_time = 0;
          while (digitalRead(IR_PIN))
          {
            delayMicroseconds(100);
            irremote_time++;
            if (irremote_time >= 30)
            {
              return ;
            }
          }
          IRCOM[j] = IRCOM[j] << 1;
          if (irremote_time >= 8)
          {
            IRCOM[j] = IRCOM[j] | 0x01;
          }
          irremote_time = 0;
        }
      }
      IRremote_value = (IRCOM[0] << 24) | (IRCOM[1] << 16) | (IRCOM[2] << 8) | (IRCOM[3]);
      verify_value = IRremote_value & 0xffff0000;
      if (verify_value == 0x00ff0000)
        irremote_state = 9;
      else
        irremote_state = 8;
    }
    if (digitalRead(IR_PIN) == HIGH && irremote_state == 8)
    {
      irremote_time++;
      if (irremote_time >= 1000)
      {
        irremote_time = 0;
        IRremote_value = 0;
        verify_value = 0;
        irremote_state = 0;
        irremote_time = 0;
        IRremote_flag = 0;
      }
    }
    if (irremote_state == 9)
    {
      irremote_time++;
      if (irremote_time >= 240)
      {
        irremote_state = 0;
        irremote_time = 0;
        IRremote_flag = 1;
      }
    }
    if (irremote_state == 10)
    {
      irremote_time++;
      if (irremote_time >= 1000)
      {
        irremote_state = 0;
        irremote_time = 0;
        IRremote_flag = 2;
      }
    }
  }
}
