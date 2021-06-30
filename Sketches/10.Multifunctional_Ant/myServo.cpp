#include <Arduino.h>
#include <Servo.h>

#include "myServo.h"

Servo myservo1;
Servo myservo2;
Servo myservo3;

int ant_move_time = 0;
int forth_angle  = 90 ;      //Forth servo value
int middle_angle = 90 ;      //Middle servo value
int back_angle   = 90 ;      //Back servo value

int ant_move_ai = 0;
int ant_move_bi = 0;
int ant_move_now = 0;
int ant_move_before = 0;
int ant_move_state = 0;

//Initialize the servo
void Ant_Setup(void)
{
  myservo1.attach(2);
  myservo2.attach(3);
  myservo3.attach(4);
  ant_reset_angle();
}

//Calibrate the servo value
void Ant_Correct_Angle(int angle1, int angle2, int angle3)
{
  forth_angle  = 90 + angle1;
  middle_angle = 90 + angle2;
  back_angle   = 90 + angle3;
}

//Set the movement pattern of the ant
void Ant_Servo_Mode(int mode, int speed, bool state)
{
  mode = constrain(mode, 0, 6);
  speed = constrain(speed, 0, 2);
  switch (mode)
  {
    case 0:
      ant_reset_angle();                   //Restore initial state
      break;
    case 1:
      ant_move_forth(2, 5+speed*2, state); //Forward
      break;
    case 2:
      ant_move_back(2, 5+speed*2, state);  //Backwards
      break;
    case 3:
      ant_move_left(4, 5+speed*2, state);  //Forward to the left
      break;
    case 4:
      ant_move_right(4, 5+speed*2, state); //Forward to the right
      break;
    case 5:
      ant_situ_left(2, 5+speed*2, state);  //Turn left in situ
      break;
    case 6:
      ant_situ_right(2, 5+speed*2, state); //Turn right in situ
      break;
    default:
      break;
  }
}



//Restore initial state
void ant_reset_angle(void)
{
  ant_move_now = millis();
  if (ant_move_now - ant_move_before >= 100)
  {
    ant_move_before = ant_move_now;
    myservo1.write(forth_angle);
    myservo2.write(middle_angle);
    myservo3.write(back_angle);
    ant_move_time = 0;
    ant_move_ai = 0;
    ant_move_bi = 0;
    ant_move_state = 0;
  }
}

//Forward
bool ant_move_forth(int times, int mdelayms, int state)
{
  ant_move_now = millis();
  if (ant_move_now - ant_move_before >= mdelayms)
  {
    ant_move_before = millis();
    ant_move_state=constrain(ant_move_state,0,6);
    if (ant_move_time < times)
    {
      if (ant_move_state == 0)
      {
        if (ant_move_ai >= -ANT_UPLIFT_HEIGHT)
        {
          ant_move_ai--;
          myservo2.write(middle_angle + ant_move_ai);
        }
        else
          ant_move_state = 1;
      }
      else if (ant_move_state == 1)
      {
        if (ant_move_bi <= ANT_ROTATE_ANGLE)
        {
          ant_move_bi++;
          myservo1.write(forth_angle + ant_move_bi);
          myservo3.write(back_angle + ant_move_bi);
        }
        else
          ant_move_state = 2;
      }
      else if (ant_move_state == 2)
      {
        if (ant_move_ai <= ANT_UPLIFT_HEIGHT)
        {
          ant_move_ai++;
          myservo2.write(middle_angle + ant_move_ai);
        }
        else
          ant_move_state = 3;
      }
      else if (ant_move_state == 3)
      {
        if (ant_move_bi >= -ANT_ROTATE_ANGLE)
        {
          ant_move_bi--;
          myservo1.write(forth_angle + ant_move_bi);
          myservo3.write(back_angle + ant_move_bi);
        }
        else
          ant_move_state = 4;
      }
      else if (ant_move_state == 4)
      {
        if (ant_move_ai >= -ANT_UPLIFT_HEIGHT)
        {
          ant_move_ai--;
          myservo2.write(middle_angle + ant_move_ai);
        }
        else
          ant_move_state = 5;
      }
      else if (ant_move_state == 5)
      {
        if (ant_move_bi <= 0)
        {
          ant_move_bi++;
          myservo1.write(forth_angle + ant_move_bi);
          myservo3.write(back_angle + ant_move_bi);
        }
        else
          ant_move_state = 6;
      }
      else if (ant_move_state == 6)
      {
        ant_move_time++;
        ant_move_state = 0;
      }
      return 0;
    }
    else
    {
      if (state == 1)
      {
        ant_move_time = 0;
        return 1;
      }
      else if (state == 0)
      {
        return 1;
      }
    }
  }
}

//Backwards
bool ant_move_back(int times, int mdelayms, int state)
{
  ant_move_now = millis();
  if (ant_move_now - ant_move_before >= mdelayms)
  {
    ant_move_before = millis();
    ant_move_state=constrain(ant_move_state,0,6);
    if (ant_move_time < times)
    {
      if (ant_move_state == 0)
      {
        if (ant_move_ai >= -ANT_UPLIFT_HEIGHT)
        {
          ant_move_ai--;
          myservo2.write(middle_angle + ant_move_ai);
        }
        else
          ant_move_state = 1;
      }
      else if (ant_move_state == 1)
      {
        if (ant_move_bi >= -ANT_ROTATE_ANGLE)
        {
          ant_move_bi--;
          myservo1.write(forth_angle + ant_move_bi);
          myservo3.write(back_angle + ant_move_bi);
        }
        else
          ant_move_state = 2;
      }
      else if (ant_move_state == 2)
      {
        if (ant_move_ai <= ANT_UPLIFT_HEIGHT)
        {
          ant_move_ai++;
          myservo2.write(middle_angle + ant_move_ai);
        }
        else
          ant_move_state = 3;
      }
      else if (ant_move_state == 3)
      {
        if (ant_move_bi <= ANT_ROTATE_ANGLE)
        {
          ant_move_bi++;
          myservo1.write(forth_angle + ant_move_bi);
          myservo3.write(back_angle + ant_move_bi);
        }
        else
          ant_move_state = 4;
      }
      else if (ant_move_state == 4)
      {
        if (ant_move_ai >= -ANT_UPLIFT_HEIGHT)
        {
          ant_move_ai--;
          myservo2.write(middle_angle + ant_move_ai);
        }
        else
          ant_move_state = 5;
      }
      else if (ant_move_state == 5)
      {
        if (ant_move_bi >= 0)
        {
          ant_move_bi--;
          myservo1.write(forth_angle + ant_move_bi);
          myservo3.write(back_angle + ant_move_bi);
        }
        else
          ant_move_state = 6;
      }
      else if (ant_move_state == 6)
      {
        ant_move_time++;
        ant_move_state = 0;
      }
      return 0;
    }
    else
    {
      if (state == 1)
      {
        ant_move_time = 0;
        return 1;
      }
      else if (state == 0)
      {
        return 1;
      }
    }
  }
}

//Forward to the left
bool ant_move_left(int times, int mdelayms, int state)
{
  ant_move_now = millis();
  if (ant_move_now - ant_move_before >= mdelayms)
  {
    ant_move_before = millis();
    ant_move_state=constrain(ant_move_state,0,6);
    if (ant_move_time < times)
    {
      if (ant_move_state == 0)
      {
        if (ant_move_ai >= -ANT_UPLIFT_HEIGHT)
        {
          ant_move_ai--;
          myservo2.write(middle_angle + ant_move_ai);
        }
        else
          ant_move_state = 1;
      }
      else if (ant_move_state == 1)
      {
        if (ant_move_bi <= ANT_ROTATE_ANGLE)
        {
          ant_move_bi++;
          myservo1.write(forth_angle + ant_move_bi);
          myservo3.write(back_angle + ant_move_bi);
        }
        else
          ant_move_state = 2;
      }
      else if (ant_move_state == 2)
      {
        if (ant_move_ai <= 0)
        {
          ant_move_ai++;
          myservo2.write(middle_angle + ant_move_ai);
        }
        else
          ant_move_state = 3;
      }
      else if (ant_move_state == 3)
      {
        if (ant_move_bi >= -ANT_ROTATE_ANGLE)
        {
          ant_move_bi--;
          myservo1.write(forth_angle + ant_move_bi);
          myservo3.write(back_angle + ant_move_bi);
        }
        else
          ant_move_state = 4;
      }
      else if (ant_move_state == 4)
      {
        if (ant_move_ai >= -ANT_UPLIFT_HEIGHT)
        {
          ant_move_ai--;
          myservo2.write(middle_angle + ant_move_ai);
        }
        else
          ant_move_state = 5;
      }
      else if (ant_move_state == 5)
      {
        if (ant_move_bi <= 0)
        {
          ant_move_bi++;
          myservo1.write(forth_angle + ant_move_bi);
          myservo3.write(back_angle + ant_move_bi);
        }
        else
          ant_move_state = 6;
      }
      else if (ant_move_state == 6)
      {
        ant_move_time++;
        ant_move_state = 0;
      }
      return 0;
    }
    else
    {
      if (state == 1)
      {
        ant_move_time = 0;
        return 1;
      }
      else if (state == 0)
      {
        return 1;
      }
    }
  }
}

//Forward to the right
bool ant_move_right(int times, int mdelayms, int state)
{
  ant_move_now = millis();
  if (ant_move_now - ant_move_before >= mdelayms)
  {
    ant_move_before = millis();
    ant_move_state=constrain(ant_move_state,0,6);
    if (ant_move_time < times)
    {
      if (ant_move_state == 0)
      {
        if (ant_move_ai <= ANT_UPLIFT_HEIGHT)
        {
          ant_move_ai++;
          myservo2.write(middle_angle + ant_move_ai);
        }
        else
          ant_move_state = 1;
      }
      else if (ant_move_state == 1)
      {
        if (ant_move_bi >= -ANT_ROTATE_ANGLE)
        {
          ant_move_bi--;
          myservo1.write(forth_angle + ant_move_bi);
          myservo3.write(back_angle + ant_move_bi);
        }
        else
          ant_move_state = 2;
      }
      else if (ant_move_state == 2)
      {
        if (ant_move_ai >= 0)
        {
          ant_move_ai--;
          myservo2.write(middle_angle + ant_move_ai);
        }
        else
          ant_move_state = 3;
      }
      else if (ant_move_state == 3)
      {
        if (ant_move_bi <= ANT_ROTATE_ANGLE)
        {
          ant_move_bi++;
          myservo1.write(forth_angle + ant_move_bi);
          myservo3.write(back_angle + ant_move_bi);
        }
        else
          ant_move_state = 4;
      }
      else if (ant_move_state == 4)
      {
        if (ant_move_ai <= ANT_UPLIFT_HEIGHT)
        {
          ant_move_ai++;
          myservo2.write(middle_angle + ant_move_ai);
        }
        else
          ant_move_state = 5;
      }
      else if (ant_move_state == 5)
      {
        if (ant_move_bi >= 0)
        {
          ant_move_bi--;
          myservo1.write(forth_angle + ant_move_bi);
          myservo3.write(back_angle + ant_move_bi);
        }
        else
          ant_move_state = 6;
      }
      else if (ant_move_state == 6)
      {
        ant_move_time++;
        ant_move_state = 0;
      }
      return 0;
    }
    else
    {
      if (state == 1)
      {
        ant_move_time = 0;
        return 1;
      }
      else if (state == 0)
      {
        return 1;
      }
    }
  }
}

//Turn left in situ
bool ant_situ_left(int times, int mdelayms, int state)
{
  ant_move_now = millis();
  if (ant_move_now - ant_move_before >= mdelayms)
  {
    ant_move_before = millis();
    ant_move_state=constrain(ant_move_state,0,10);
    if (ant_move_time < times)
    {
      if (ant_move_state == 0)
      {
        if (ant_move_ai >= -ANT_UPLIFT_HEIGHT)
        {
          ant_move_ai--;
          myservo2.write(middle_angle + ant_move_ai);
        }
        else
          ant_move_state = 1;
      }
      else if (ant_move_state == 1)
      {
        if (ant_move_bi <= ANT_ROTATE_ANGLE)
        {
          ant_move_bi++;
          myservo1.write(forth_angle + ant_move_bi);
          myservo3.write(back_angle + ant_move_bi);
        }
        else
          ant_move_state = 2;
      }
      else if (ant_move_state == 2)
      {
        if (ant_move_ai <= 0)
        {
          ant_move_ai++;
          myservo2.write(middle_angle + ant_move_ai);
        }
        else
          ant_move_state = 3;
      }
      else if (ant_move_state == 3)
      {
        if (ant_move_bi >= -ANT_ROTATE_ANGLE)
        {
          ant_move_bi--;
          myservo1.write(forth_angle + ant_move_bi);
          myservo3.write(back_angle + ant_move_bi);
        }
        else
          ant_move_state = 4;
      }
      else if (ant_move_state == 4)
      {
        if (ant_move_ai <= ANT_UPLIFT_HEIGHT)
        {
          ant_move_ai++;
          myservo2.write(middle_angle + ant_move_ai);
        }
        else
          ant_move_state = 5;
      }
      else if (ant_move_state == 5)
      {
        if (ant_move_bi <= ANT_ROTATE_ANGLE)
        {
          ant_move_bi++;
          myservo1.write(forth_angle + ant_move_bi);
          myservo3.write(back_angle + ant_move_bi);
        }
        else
          ant_move_state = 6;
      }
      else if (ant_move_state == 6)
      {
        if (ant_move_ai >= 0)
        {
          ant_move_ai--;
          myservo2.write(middle_angle + ant_move_ai);
        }
        else
          ant_move_state = 7;
      }
      else if (ant_move_state == 7)
      {
        if (ant_move_bi >= -ANT_ROTATE_ANGLE)
        {
          ant_move_bi--;
          myservo1.write(forth_angle + ant_move_bi);
          myservo3.write(back_angle + ant_move_bi);
        }
        else
          ant_move_state = 8;
      }
      else if (ant_move_state == 8)
      {
        if (ant_move_ai >= -ANT_UPLIFT_HEIGHT)
        {
          ant_move_ai--;
          myservo2.write(middle_angle + ant_move_ai);
        }
        else
          ant_move_state = 9;
      }
      else if (ant_move_state == 9)
      {
        if (ant_move_bi <= 0)
        {
          ant_move_bi++;
          myservo1.write(forth_angle + ant_move_bi);
          myservo3.write(back_angle + ant_move_bi);
        }
        else
          ant_move_state = 10;
      }
      else if (ant_move_state == 10)
      {
        ant_move_time++;
        ant_move_state = 0;
      }
      return 0;
    }
    else
    {
      if (state == 1)
      {
        ant_move_time = 0;
        return 1;
      }
      else if (state == 0)
      {
        return 1;
      }
    }
  }
}

//Turn right in situ
bool ant_situ_right(int times, int mdelayms, int state)
{
  ant_move_now = millis();
  if (ant_move_now - ant_move_before >= mdelayms)
  {
    ant_move_before = millis();
    ant_move_state=constrain(ant_move_state,0,10);
    if (ant_move_time < times)
    {
      if (ant_move_state == 0)
      {
        if (ant_move_ai <= ANT_UPLIFT_HEIGHT)
        {
          ant_move_ai++;
          myservo2.write(middle_angle + ant_move_ai);
        }
        else
          ant_move_state = 1;
      }
      else if (ant_move_state == 1)
      {
        if (ant_move_bi >= -ANT_ROTATE_ANGLE)
        {
          ant_move_bi--;
          myservo1.write(forth_angle + ant_move_bi);
          myservo3.write(back_angle + ant_move_bi);
        }
        else
          ant_move_state = 2;
      }
      else if (ant_move_state == 2)
      {
        if (ant_move_ai >= 0)
        {
          ant_move_ai--;
          myservo2.write(middle_angle + ant_move_ai);
        }
        else
          ant_move_state = 3;
      }
      else if (ant_move_state == 3)
      {
        if (ant_move_bi <= ANT_ROTATE_ANGLE)
        {
          ant_move_bi++;
          myservo1.write(forth_angle + ant_move_bi);
          myservo3.write(back_angle + ant_move_bi);
        }
        else
          ant_move_state = 4;
      }
      else if (ant_move_state == 4)
      {
        if (ant_move_ai >= -ANT_UPLIFT_HEIGHT)
        {
          ant_move_ai--;
          myservo2.write(middle_angle + ant_move_ai);
        }
        else
          ant_move_state = 5;
      }
      else if (ant_move_state == 5)
      {
        if (ant_move_bi >= -ANT_ROTATE_ANGLE)
        {
          ant_move_bi--;
          myservo1.write(forth_angle + ant_move_bi);
          myservo3.write(back_angle + ant_move_bi);
        }
        else
          ant_move_state = 6;
      }
      else if (ant_move_state == 6)
      {
        if (ant_move_ai <= 0)
        {
          ant_move_ai++;
          myservo2.write(middle_angle + ant_move_ai);
        }
        else
          ant_move_state = 7;
      }
      else if (ant_move_state == 7)
      {
        if (ant_move_bi <= ANT_ROTATE_ANGLE)
        {
          ant_move_bi++;
          myservo1.write(forth_angle + ant_move_bi);
          myservo3.write(back_angle + ant_move_bi);
        }
        else
          ant_move_state = 8;
      }
      else if (ant_move_state == 8)
      {
        if (ant_move_ai <= ANT_UPLIFT_HEIGHT)
        {
          ant_move_ai++;
          myservo2.write(middle_angle + ant_move_ai);
        }
        else
          ant_move_state = 9;
      }
      else if (ant_move_state == 9)
      {
        if (ant_move_bi >= 0)
        {
          ant_move_bi--;
          myservo1.write(forth_angle + ant_move_bi);
          myservo3.write(back_angle + ant_move_bi);
        }
        else
          ant_move_state = 10;
      }
      else if (ant_move_state == 10)
      {
        ant_move_time++;
        ant_move_state = 0;
      }
      return 0;
    }
    else
    {
      if (state == 1)
      {
        ant_move_time = 0;
        return 1;
      }
      else if (state == 0)
      {
        return 1;
      }
    }
  }
}


//Forward
void ant_run_forth(int times, int mdelayms) {
  for (int i = 0; i < times; i++) {
    myservo2.write(middle_angle - ANT_UPLIFT_HEIGHT);   
    for (int bi = 0; bi <= ANT_ROTATE_ANGLE; bi++) {
      myservo1.write(forth_angle + bi);  
      myservo3.write(back_angle + bi);   
      delay(mdelayms);
    }
    for (int ai = -ANT_UPLIFT_HEIGHT; ai <= ANT_UPLIFT_HEIGHT; ai++) {
      myservo2.write(middle_angle + ai); 
      delay(mdelayms);
    }
    for (int bi = ANT_ROTATE_ANGLE; bi >= -ANT_ROTATE_ANGLE; bi--) {
      myservo1.write(forth_angle + bi); 
      myservo3.write(back_angle + bi);   
      delay(mdelayms);
    }
    for (int ai = ANT_UPLIFT_HEIGHT; ai >= -ANT_UPLIFT_HEIGHT; ai--) {
      myservo2.write(middle_angle + ai);
      delay(mdelayms);
    }
    for (int bi = -ANT_ROTATE_ANGLE; bi < 0; bi++) {
      myservo1.write(forth_angle + bi);
      myservo3.write(back_angle + bi);
      delay(mdelayms);
    }
  }
}

//Backwards
void ant_run_back(int times, int mdelayms) {
  for (int i = 0; i < times; i++) {
    myservo2.write(middle_angle - ANT_UPLIFT_HEIGHT);
    for (int bi = 0; bi >= -ANT_ROTATE_ANGLE; bi--) {
      myservo1.write(forth_angle + bi);
      myservo3.write(back_angle + bi);
      delay(mdelayms);
    }
    for (int ai = -ANT_UPLIFT_HEIGHT; ai <= ANT_UPLIFT_HEIGHT; ai++) {
      myservo2.write(middle_angle + ai);
      delay(mdelayms);
    }
    for (int bi = -ANT_ROTATE_ANGLE; bi <= ANT_ROTATE_ANGLE; bi++) {
      myservo1.write(forth_angle + bi);
      myservo3.write(back_angle + bi);
      delay(mdelayms);
    }
    for (int ai = ANT_UPLIFT_HEIGHT; ai >= -ANT_UPLIFT_HEIGHT; ai--) {
      myservo2.write(middle_angle + ai);
      delay(mdelayms);
    }
    for (int bi = ANT_ROTATE_ANGLE; bi > 0; bi--) {
      myservo1.write(forth_angle + bi);
      myservo3.write(back_angle + bi);
      delay(mdelayms);
    }
  }
}

//Forward to the left
void ant_run_left(int times, int mdelayms) {
  for (int i = 0; i < times; i++) {
    myservo2.write(middle_angle - ANT_UPLIFT_HEIGHT);    
    for (int bi = 0; bi <= ANT_ROTATE_ANGLE; bi++) {     
      myservo1.write(forth_angle + bi);
      myservo3.write(back_angle + bi);
      delay(mdelayms);
    }
    for (int ai = -ANT_UPLIFT_HEIGHT; ai <= 0; ai++) {    
      myservo2.write(middle_angle + ai);
      delay(mdelayms);
    }
    for (int bi = ANT_ROTATE_ANGLE; bi >= -ANT_ROTATE_ANGLE; bi--) {    
      myservo3.write(back_angle + bi);
      myservo1.write(forth_angle + bi);
      delay(mdelayms);
    }

    for (int ai = 0; ai >= -ANT_UPLIFT_HEIGHT; ai--) {   
      myservo2.write(middle_angle + ai);
      delay(mdelayms);
    }
    for (int bi = -ANT_ROTATE_ANGLE; bi <= 0; bi++) {  
      myservo1.write(forth_angle + bi);
      myservo3.write(back_angle + bi);
      delay(mdelayms);
    }
  }
}

//Forward to the right
void ant_run_right(int times, int mdelayms) {
  for (int i = 0; i < times; i++) {
    myservo2.write(middle_angle + ANT_UPLIFT_HEIGHT);    
    for (int bi = 0; bi >= -ANT_ROTATE_ANGLE; bi--) {   
      myservo1.write(forth_angle + bi);
      myservo3.write(back_angle + bi);
      delay(mdelayms);
    }
    for (int ai = ANT_UPLIFT_HEIGHT; ai >= 0; ai--)  {   
      myservo2.write(middle_angle + ai);
      delay(mdelayms);
    }
    for (int bi = -ANT_ROTATE_ANGLE; bi <= ANT_ROTATE_ANGLE; bi++) {    
      myservo1.write(forth_angle + bi);
      myservo3.write(back_angle + bi);
      delay(mdelayms);
    }
    for (int ai = 0; ai <= ANT_UPLIFT_HEIGHT; ai++)  {    
      myservo2.write(middle_angle + ai);
      delay(mdelayms);
    }
    for (int bi = ANT_ROTATE_ANGLE; bi > 0; bi--)   {   
      myservo1.write(forth_angle + bi);
      myservo3.write(back_angle + bi);
      delay(mdelayms);
    }
  }
}

//Turn left in situ
void ant_run_situ_left(int times, int mdelayms) {
  for (int i = 0; i < times; i++) {
    myservo2.write(middle_angle - ANT_UPLIFT_HEIGHT);     
    for (int bi = 0; bi <= ANT_ROTATE_ANGLE; bi++)  {   
      myservo1.write(forth_angle + bi);
      myservo3.write(back_angle + bi);
      delay(mdelayms);
    }
    for (int ai = -ANT_UPLIFT_HEIGHT; ai <= 0; ai++) {    
      myservo2.write(middle_angle + ai);
      delay(mdelayms);
    }
    for (int bi = ANT_ROTATE_ANGLE; bi >= -ANT_ROTATE_ANGLE; bi--) {    
      myservo3.write(back_angle + bi);
      myservo1.write(forth_angle + bi);
      delay(mdelayms);
    }
    for (int ai = 0; ai <= ANT_UPLIFT_HEIGHT; ai++)  {    
      myservo2.write(middle_angle + ai);
      delay(mdelayms);
    }
    for (int bi = -ANT_ROTATE_ANGLE; bi < ANT_ROTATE_ANGLE; bi++)  {   
      myservo3.write(back_angle + bi);
      myservo1.write(forth_angle + bi);
      delay(mdelayms);
    }
    for (int ai = ANT_UPLIFT_HEIGHT; ai >= 0; ai--)  {    
      myservo2.write(middle_angle + ai);
      delay(mdelayms);
    }
    for (int bi = ANT_ROTATE_ANGLE; bi >= -ANT_ROTATE_ANGLE; bi--) {   
      myservo3.write(back_angle + bi);
      myservo1.write(forth_angle + bi);
      delay(mdelayms);
    }
    for (int ai = 0; ai >= -ANT_UPLIFT_HEIGHT; ai--) {    
      myservo2.write(middle_angle + ai);
      delay(mdelayms);
    }
    for (int bi = -ANT_ROTATE_ANGLE; bi <= 0; bi++) {   
      myservo1.write(forth_angle + bi);
      myservo3.write(back_angle + bi);
      delay(mdelayms);
    }
  }
}

//Turn right in situ
void ant_run_situ_right(int times, int mdelayms) {
  for (int i = 0; i < times; i++) {
    myservo2.write(middle_angle + ANT_UPLIFT_HEIGHT);   
    for (int bi = 0; bi >= -ANT_ROTATE_ANGLE; bi--) {    
      myservo1.write(forth_angle + bi);
      myservo3.write(back_angle + bi);
      delay(mdelayms);
    }
    for (int ai = ANT_UPLIFT_HEIGHT; ai >= 0; ai--)  {   
      myservo2.write(middle_angle + ai);
      delay(mdelayms);
    }
    for (int bi = -ANT_ROTATE_ANGLE; bi <= ANT_ROTATE_ANGLE; bi++) {   
      myservo1.write(forth_angle + bi);
      myservo3.write(back_angle + bi);
      delay(mdelayms);
    }
    for (int ai = 0; ai >= -ANT_UPLIFT_HEIGHT; ai--) {    
      myservo2.write(middle_angle + ai);
      delay(mdelayms);
    }
    for (int bi = ANT_ROTATE_ANGLE; bi >= -ANT_ROTATE_ANGLE; bi--) {    
      myservo3.write(back_angle + bi);
      myservo1.write(forth_angle + bi);
      delay(mdelayms);
    }
    for (int ai = -ANT_UPLIFT_HEIGHT; ai < 0; ai++)  {    
      myservo2.write(middle_angle + ai);
      delay(mdelayms);
    }
    for (int bi = -ANT_ROTATE_ANGLE; bi <= ANT_ROTATE_ANGLE; bi++) {   
      myservo3.write(back_angle + bi);
      myservo1.write(forth_angle + bi);
      delay(mdelayms);
    }
    for (int ai = 0; ai <= ANT_UPLIFT_HEIGHT; ai++)  {    
      myservo2.write(middle_angle + ai);
      delay(mdelayms);
    }
    for (int bi = ANT_ROTATE_ANGLE; bi > 0; bi--)   { 
      myservo1.write(forth_angle + bi);
      myservo3.write(back_angle + bi);
      delay(mdelayms);
    }
  }
}




//
