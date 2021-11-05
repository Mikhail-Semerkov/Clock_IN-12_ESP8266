#include <Arduino.h>
#include <WS2812FX.h>
#include "GyverButton.h"
#include "GyverTimer.h"

bool Auto_Brightness_LED_FRONT;
bool Auto_Brightness_LED_BASIC;

int Max_Brightness_ws2812 = 30; //Максимальная яркость ws2812

#define BTN_PIN_BOTTON 0
#define BTN_PIN_UP 2
GButton BUTTON_BOTTON(BTN_PIN_BOTTON);
GButton BUTTON_UP(BTN_PIN_UP);

GTimer Timer_Brightness_ws2812(MS);
GTimer Timer_Count_ws2812_Color(MS);

#define LED_COUNT_1 16
#define LED_COUNT_2 4
#define LED_PIN_1 12
#define LED_PIN_2 10

uint32_t Color_ws2812[] = {0xFF0000, 0x00FF00, 0x0000FF, 0xFFFFFF, 0xFFFF00, 0x00FFFF, 0xFF00FF};

WS2812FX ws2812fx_BASIC = WS2812FX(LED_COUNT_1, LED_PIN_1, NEO_RGB + NEO_KHZ800);

WS2812FX ws2812fx_FRONT = WS2812FX(LED_COUNT_2, LED_PIN_2, NEO_RGB + NEO_KHZ800);

int Mode_Effect_Basic;
int Mode_Effect_Up;
bool Flag_Start_WS2812_Basic;
bool Flag_Start_WS2812_Front;

void setup_ws2812()
{
  ws2812fx_BASIC.init();
  ws2812fx_BASIC.setBrightness(settings.int_bright_led_basic);
  ws2812fx_BASIC.setSpeed(settings.int_speed_led_basic * 50);

  String Color_Basic = settings.string_color_basic;

  String R_Basic = getValue(Color_Basic, ',', 0);
  String G_Basic = getValue(Color_Basic, ',', 1);
  String B_Basic = getValue(Color_Basic, ',', 2);

  ws2812fx_BASIC.setColor(R_Basic.toInt(), G_Basic.toInt(), B_Basic.toInt());

  ws2812fx_BASIC.setMode(settings.int_effects_led_basic);
  ws2812fx_BASIC.start();

  ws2812fx_FRONT.init();
  ws2812fx_FRONT.setBrightness(settings.int_bright_led_front);
  ws2812fx_FRONT.setSpeed(settings.int_speed_led_front * 50);

  String Color_Front = settings.string_color_front;

  String R_Front = getValue(Color_Front, ',', 0);
  String G_Front = getValue(Color_Front, ',', 1);
  String B_Front = getValue(Color_Front, ',', 2);

  ws2812fx_FRONT.setColor(R_Front.toInt(), G_Front.toInt(), B_Front.toInt());

  ws2812fx_FRONT.setMode(settings.int_effects_led_basic);
  ws2812fx_FRONT.start();

  BUTTON_BOTTON.setDebounce(50);      // настройка антидребезга (по умолчанию 80 мс)
  BUTTON_BOTTON.setTimeout(1000);     // настройка таймаута на удержание (по умолчанию 500 мс)
  BUTTON_BOTTON.setClickTimeout(600); // настройка таймаута между кликами (по умолчанию 300 мс)
  BUTTON_BOTTON.setType(HIGH_PULL);
  BUTTON_BOTTON.setDirection(NORM_OPEN);

  BUTTON_UP.setDebounce(50);      // настройка антидребезга (по умолчанию 80 мс)
  BUTTON_UP.setTimeout(1000);     // настройка таймаута на удержание (по умолчанию 500 мс)
  BUTTON_UP.setClickTimeout(600); // настройка таймаута между кликами (по умолчанию 300 мс)
  BUTTON_UP.setType(HIGH_PULL);
  BUTTON_UP.setDirection(NORM_OPEN);

  //Timer_Brightness_ws2812.setInterval(500);
  Timer_Count_ws2812_Color.setInterval(60000 * 5);

  Mode_Effect_Basic = 1;
  Mode_Effect_Up = 0;

  Flag_Start_WS2812_Basic = true;
  Flag_Start_WS2812_Front = true;

  Auto_Brightness_LED_BASIC = false;
}

void loop_ws2812()
{

  // if (Timer_Brightness_ws2812.isReady())
  // {
  //   if (Auto_Brightness_LED_FRONT == true)
  //   {
  //     Brightness_ws2812 = map(analogRead(A0), 0, 1024, 3, Max_Brightness_ws2812);
  //     ws2812fx_FRONT.setBrightness(Brightness_ws2812);
  //   }
  //   else if (Auto_Brightness_LED_BASIC == true)
  //   {

  //     Brightness_ws2812 = map(analogRead(A0), 0, 1024, 3, Max_Brightness_ws2812);
  //     ws2812fx_BASIC.setBrightness(Brightness_ws2812);
  //   }
  // }

  BUTTON_BOTTON.tick();
  BUTTON_UP.tick();

  ws2812fx_BASIC.service();
  ws2812fx_FRONT.service();

  if (BUTTON_BOTTON.hasClicks())
  {
    if (BUTTON_BOTTON.getClicks() == 1)
    {
      if (Flag_Start_WS2812_Basic == false)
      {
        ws2812fx_BASIC.start();
        Mode_Effect_Basic--;
        Flag_Start_WS2812_Basic = true;
      }
      if (Flag_Start_WS2812_Basic == true)
      {
        Mode_Effect_Basic++;
        ws2812fx_BASIC.setMode(Mode_Effect_Basic);
        Flag_Start_WS2812_Basic = true;
      }
    }

    if (BUTTON_BOTTON.getClicks() == 2)
    {
      if (Flag_Start_WS2812_Basic == false)
      {
        ws2812fx_BASIC.start();
        Mode_Effect_Basic++;
        Flag_Start_WS2812_Basic = true;
      }
      if (Flag_Start_WS2812_Basic == true)
      {
        Mode_Effect_Basic--;
        ws2812fx_BASIC.setMode(Mode_Effect_Basic);
        Flag_Start_WS2812_Basic = true;
      }
    }
  }

  if (BUTTON_BOTTON.isHolded())
  {
    ws2812fx_BASIC.stop();
    Flag_Start_WS2812_Basic = false;
  }

  if (BUTTON_UP.hasClicks())
  {
    if (BUTTON_UP.getClicks() == 1)
    {
      if (Flag_Start_WS2812_Front == false)
      {
        ws2812fx_FRONT.start();
        Mode_Effect_Up--;
        Flag_Start_WS2812_Front = true;
      }
      if (Flag_Start_WS2812_Front == true)
      {
        Mode_Effect_Up++;
        ws2812fx_FRONT.setMode(Mode_Effect_Up);
        Flag_Start_WS2812_Front = true;
      }
    }

    if (BUTTON_UP.getClicks() == 2)
    {
      if (Flag_Start_WS2812_Front == false)
      {
        ws2812fx_FRONT.start();
        Mode_Effect_Up++;
        Flag_Start_WS2812_Front = true;
      }
      if (Flag_Start_WS2812_Front == true)
      {
        Mode_Effect_Up--;
        ws2812fx_FRONT.setMode(Mode_Effect_Up);
        Flag_Start_WS2812_Front = true;
      }
    }
  }

  if (BUTTON_UP.isHolded())
  {
    ws2812fx_FRONT.stop();
    Flag_Start_WS2812_Front = false;
  }
}
