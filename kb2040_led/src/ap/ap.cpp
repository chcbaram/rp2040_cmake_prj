#include "ap.h"
#include "neopixel.hpp"


NeoPixel pixels(1, 17, NEO_GRB + NEO_KHZ400);


void apInit(void)
{
  cliOpen(_DEF_UART1, 115200);
  
  pixels.begin();
}

void apMain(void)
{
  uint32_t pre_time;
  uint8_t led_i = 0;

  while(1)
  {
    if (millis()-pre_time >= 500)
    {
      pre_time = millis();

      switch(led_i)
      {
        case 0:
          pixels.setPixelColor(0, pixels.Color(255, 0, 0));
          break;
        case 2:
          pixels.setPixelColor(0, pixels.Color(0, 255, 0));
          break;
        case 4:
          pixels.setPixelColor(0, pixels.Color(0, 0, 255));
          break;
        default:
          pixels.setPixelColor(0, pixels.Color(0, 0, 0));
          break;   
      }
      pixels.show();
      led_i = (led_i + 1) % 6;
    }

    cliMain();
  }
}

