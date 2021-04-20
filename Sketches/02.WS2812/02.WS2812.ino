#include "WS2812.h"

void setup() {
  WS2812_Setup();
//  WS2812_SetMode(0);//close ws2812
//  WS2812_SetMode(1);//rgb mode
//  WS2812_SetMode(2);//flow mode
//  WS2812_SetMode(3);//blink mode
  WS2812_SetMode(4);//breathe mode
//  WS2812_SetMode(5);//rainbow mode
}

void loop() {
  WS2812_Show();
}
