#ifndef _WS2812_H
#define _WS2812_H

#define I2C_ADDRESS  0x20
#define LEDS_COUNT   8

extern int ws2812_task_mode;

void WS2812_Setup(void);                                                                  //WS2812 initialization function
void WS2812_Show(void);                                                                   //WS2812 non-blocking display function
void WS2812_Set_Color(unsigned char color_1,unsigned char color_2,unsigned char color_3); //Set the display color for WS2812
void WS2812_Set_LED(bool red=0,bool green=0,bool blue=0,int brightness=20);               //Set the display color for WS2812
void WS2812_SetMode(int mode);                                                            //WS2812 set mode


void ws2812_close(void);    //Close the display WS2812
void ws2812_flowing(void);  //WS2812 flow display
void ws2812_rgb(void);      //WS2812 static display 
void ws2812_blink(void);    //WS2812 blink display
void ws2812_breathe(void);  //WS2812 breathe display
void ws2812_rainbow(void);  //WS2812 rainbow display
 

#endif













//
