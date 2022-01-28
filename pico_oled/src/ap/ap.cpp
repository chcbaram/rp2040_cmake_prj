#include "ap.h"





void apInit(void)
{
  cliOpen(_DEF_UART1, 115200);

  for (int i=0; i<32; i+=2)
  {
    lcdDrawFillRect(0, 0, LCD_WIDTH, LCD_HEIGHT, black);
    lcdPrintfResize(0, 31-i, green, 16, "   >>> 시작 <<<");  
    lcdUpdateDraw();
    delay(10);
  }
  delay(1000);
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

    if (lcdDrawAvailable() > 0)
    {
      lcdClearBuffer(black);  

      lcdPrintfResize(0, 0, green, 16, "테스트 Test");  
      lcdPrintfResize(0,16, green, 16, "%d", millis());  

      lcdRequestDraw();
    }
  }
}

