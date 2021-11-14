#include "ap.h"





void apInit(void)
{
  cliOpen(_DEF_UART1, 115200);

  lcdDrawFillRect(0, 0, LCD_WIDTH, LCD_HEIGHT, black);
  lcdPrintfResize(0, 0, green, 16, "Test 테스트");
  lcdPrintfResize(0, 2+16, green, 20, "폰트 크기 20");
  lcdPrintfResize(0, 2+16+20, green, 24, "폰트 크기 24");
  lcdPrintfResize(0, 2+16+20+24, green, 28, "폰트 크기 28");
  lcdPrintfResize(0, 2+16+20+24+28, green, 32, "폰트 크기 32");
  lcdPrintfResize(0, 2+16+20+24+28+32, green, 36, "폰트 크기 36");
  lcdUpdateDraw();
}

void apMain(void)
{
  uint32_t pre_time;


  while(1)
  {
    if (millis()-pre_time >= 500)
    {
      pre_time = millis();
      ledToggle(_DEF_LED1);
    }

    cliMain();
  }
}

