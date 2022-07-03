#include "ap.h"



void cliInfo(cli_args_t *args);





void apInit(void)
{
  cliOpen(_DEF_UART1, 115200);

  cliAdd("info", cliInfo);  
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

void cliInfo(cli_args_t *args)
{
  bool ret = false;

  if (args->argc == 1 && args->isStr(0, "flash"))
  {
    extern const uint32_t __flash_binary_start;
    extern const uint32_t __flash_binary_end;

    cliPrintf("Flash FW Start : 0x%X\n", &__flash_binary_start);
    cliPrintf("Flash FW End   : 0x%X\n", &__flash_binary_end);
    cliPrintf("Flash FW Size  : %d KB\n", ((uint32_t)&__flash_binary_end - (uint32_t)&__flash_binary_start)/1024);

    ret = true;
  }


  if (ret != true)
  {
    cliPrintf("info flash\n");
  }
}