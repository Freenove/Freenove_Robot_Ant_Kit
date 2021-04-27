#include <Arduino.h>
#include "Freenove_WS2812B_RGBLED_Controller.h"
#include "WS2812.h"

Freenove_WS2812B_Controller ws2812_strip(I2C_ADDRESS, LEDS_COUNT, TYPE_GRB);

int ws2812_task_mode = 0;
int ws2812_strip_time_now;
int ws2812_strip_time_next;
unsigned char ws2812_strip_color[LEDS_COUNT][3];

//WS2812 initialization function
void WS2812_Setup(void)
{
  ws2812_strip.begin();
  WS2812_Set_Color(0, 0, 100);
  ws2812_strip_time_now = millis();
}

//WS2812 set mode
void WS2812_SetMode(int mode)
{
  mode = constrain(mode, 0, 5);
  ws2812_task_mode = mode;
}

//WS2812 non-blocking display function
void WS2812_Show(void)
{
  switch (ws2812_task_mode)
  {
    case 0://Close the WS2812
      ws2812_close();
      break;
    case 1:
      ws2812_rgb();
      break;
    case 2:
      ws2812_flowing();
      break;
    case 3:
      ws2812_blink();
      break;
    case 4:
      ws2812_breathe();
      break;
    case 5:
      ws2812_rainbow();
      break;
    default:
      break;
  }
}

//Set the display color1 for WS2812
void WS2812_Set_Color(unsigned char color_1, unsigned char color_2, unsigned char color_3)  //Set the display color1 for WS2812
{
  for (int i = 0; i < LEDS_COUNT; i++)
  {
    ws2812_strip_color[i][0] = map(constrain(color_1, 0, 255),0,255,0,100);
    ws2812_strip_color[i][1] = map(constrain(color_2, 0, 255),0,255,0,100);
    ws2812_strip_color[i][2] = map(constrain(color_3, 0, 255),0,255,0,100);
  }
}

static int ws2812_led_state = 0;
static bool ws2812_led_red = 0;
static bool ws2812_led_green = 0;
static bool ws2812_led_blue = 0;

//Set the display color for WS2812
void WS2812_Set_LED(bool red, bool green, bool blue, int brightness)
{
  if (red == 1)
  {
    if (ws2812_led_red == 1)
      ws2812_led_red = 0;
    else
      ws2812_led_red = 1;
  }
  if (green == 1)
  {
    if (ws2812_led_green == 1)
      ws2812_led_green = 0;
    else
      ws2812_led_green = 1;
  }
  if (blue == 1)
  {
    if (ws2812_led_blue == 1)
      ws2812_led_blue = 0;
    else
      ws2812_led_blue = 1;
  }

  ws2812_led_state = (ws2812_led_red << 2 | ws2812_led_green << 1 | ws2812_led_blue);
  switch (ws2812_led_state)
  {
    case 0://000
      WS2812_Set_Color(0, 0, 0);
      break;
    case 1://001
      WS2812_Set_Color(0, 0, brightness);
      break;
    case 2://010
      WS2812_Set_Color(0, brightness, 0);
      break;
    case 3://011
      WS2812_Set_Color(0, brightness, brightness);
      break;
    case 4://100
      WS2812_Set_Color(brightness, 0, 0);
      break;
    case 5://101
      WS2812_Set_Color(brightness, 0, brightness);
      break;
    case 6://110
      WS2812_Set_Color(brightness, brightness, 0);
      break;
    case 7://111
      WS2812_Set_Color(brightness, brightness, brightness);
      break;
  }
}

//Close the display WS2812
void ws2812_close(void)
{
  ws2812_strip_time_next = millis();
  if (ws2812_strip_time_next - ws2812_strip_time_now > 500)
  {
    ws2812_strip_time_now = ws2812_strip_time_next;
    for (int i = 0; i < LEDS_COUNT; i++)
      ws2812_strip.setLedColorData(i, 0, 0, 0);
    ws2812_strip.show();
  }
}

int ws2812_following_number = 0;
//WS2812 flow display
void ws2812_flowing(void)
{
  ws2812_strip_time_next = millis();
  if (ws2812_strip_time_next - ws2812_strip_time_now > 100)
  {
    ws2812_strip_time_now = ws2812_strip_time_next;
    for (int i = 0; i < ws2812_following_number; i++)
      ws2812_strip.setLedColorData(i, ws2812_strip_color[i][0], ws2812_strip_color[i][1], ws2812_strip_color[i][2]);
    for (int i = ws2812_following_number; i < LEDS_COUNT; i++)
      ws2812_strip.setLedColorData(i, 0, 0, 0);
    ws2812_strip.show();
    ws2812_following_number++;
    if (ws2812_following_number == LEDS_COUNT + 1)
      ws2812_following_number = 0;
  }
}
//WS2812 static display
void ws2812_rgb(void)
{
  ws2812_strip_time_next = millis();
  if (ws2812_strip_time_next - ws2812_strip_time_now > 100)
  {
    ws2812_strip_time_now = ws2812_strip_time_next;
    for (int i = 0; i < LEDS_COUNT; i++)
      ws2812_strip.setLedColorData(i, ws2812_strip_color[i][0], ws2812_strip_color[i][1], ws2812_strip_color[i][2]);
    ws2812_strip.show();
  }
}

int ws2812_blink_flag = 0;
//WS2812 blink display
void ws2812_blink(void)
{
  ws2812_strip_time_next = millis();
  if (ws2812_strip_time_next - ws2812_strip_time_now > 500 && ws2812_blink_flag == 0)
  {
    ws2812_blink_flag = 1;
    ws2812_strip_time_now = ws2812_strip_time_next;
    for (int i = 0; i < LEDS_COUNT; i++)
      ws2812_strip.setLedColorData(i, ws2812_strip_color[i][0], ws2812_strip_color[i][1], ws2812_strip_color[i][2]);
    ws2812_strip.show();
  }
  else if (ws2812_strip_time_next - ws2812_strip_time_now > 500 && ws2812_blink_flag == 1)
  {
    ws2812_blink_flag = 0;
    ws2812_strip_time_now = ws2812_strip_time_next;
    for (int i = 0; i < LEDS_COUNT; i++)
      ws2812_strip.setLedColorData(i, 0, 0, 0);
    ws2812_strip.show();
  }
}

int ws2812_breathe_flag = 0;
int breathe_brightness = 0;
//WS2812 breathe display
void ws2812_breathe(void)
{
  ws2812_strip_time_next = millis();
  if ((ws2812_strip_time_next - ws2812_strip_time_now > 50) && (ws2812_breathe_flag == 0))
  {
    ws2812_strip_time_now = ws2812_strip_time_next;
    breathe_brightness = breathe_brightness + 10;
    for (int i = 0; i < LEDS_COUNT; i++)
      ws2812_strip.setLedColorData(i, ws2812_strip_color[i][0]*breathe_brightness / 255, ws2812_strip_color[i][1]*breathe_brightness / 255, ws2812_strip_color[i][2]*breathe_brightness / 255);
    ws2812_strip.show();
    if (breathe_brightness >= 250)
      ws2812_breathe_flag = 1;
  }
  else if ((ws2812_strip_time_next - ws2812_strip_time_now > 50) && (ws2812_breathe_flag == 1))
  {
    ws2812_strip_time_now = ws2812_strip_time_next;
    breathe_brightness = breathe_brightness - 10;
    for (int i = 0; i < LEDS_COUNT; i++)
      ws2812_strip.setLedColorData(i, ws2812_strip_color[i][0]*breathe_brightness / 255, ws2812_strip_color[i][1]*breathe_brightness / 255, ws2812_strip_color[i][2]*breathe_brightness / 255);
    ws2812_strip.show();
    if (breathe_brightness <= 0)
      ws2812_breathe_flag = 0;
  }
}

int rainbow_count = 0;
//WS2812 rainbow display
void ws2812_rainbow(void)
{
  ws2812_strip_time_next = millis();
  if (ws2812_strip_time_next - ws2812_strip_time_now > 40)
  {
    ws2812_strip_time_now = ws2812_strip_time_next;
    rainbow_count = rainbow_count + 3;
    for (int i = 0; i < LEDS_COUNT; i++)
      ws2812_strip.setLedColorData(LEDS_COUNT - 1 - i, ws2812_strip.Wheel((i * 256 / LEDS_COUNT + rainbow_count) & 255));
    ws2812_strip.show();
    if (rainbow_count > 255)
      rainbow_count = 0;
  }
}








//
