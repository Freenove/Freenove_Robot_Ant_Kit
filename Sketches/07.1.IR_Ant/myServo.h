#ifndef _MYSERVO_H
#define _MYSERVO_H

#define ANT_UPLIFT_HEIGHT 10
#define ANT_ROTATE_ANGLE 25

void Ant_Setup(void);                                        //Initialize the servo
void Ant_Correct_Angle(int angle1, int angle2, int angle3);  //Calibrate the servo value
void Ant_Servo_Mode(int mode, int speed=1, bool state=1);    //Set the movement pattern of the ant


void ant_reset_angle(void);                                  //Restore initial state
bool ant_move_forth(int times, int mdelayms, int state = 1); //Forward
bool ant_move_back(int times, int mdelayms, int state = 1);  //Backwards
bool ant_move_left(int times, int mdelayms, int state = 1);  //Forward to the left
bool ant_move_right(int times, int mdelayms, int state = 1); //Forward to the right
bool ant_situ_left(int times, int mdelayms, int state = 1);  //Turn left in situ
bool ant_situ_right(int times, int mdelayms, int state = 1); //Turn right in situ

void ant_run_forth(int times, int mdelayms);                 //Forward
void ant_run_back(int times, int mdelayms);                  //Backwards
void ant_run_left(int times, int mdelayms);                  //Forward to the left
void ant_run_right(int times, int mdelayms);                 //Forward to the right
void ant_run_situ_left(int times, int mdelayms);             //Turn left in situ
void ant_run_situ_right(int times, int mdelayms);            //Turn right in situ





#endif
