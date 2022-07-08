#include "ap.h"
#include "boot/boot.h"


#ifdef _USE_AP_BOOT
cmd_t cmd_boot;
#else
void cliInfo(cli_args_t *args);
void cliBoot(cli_args_t *args);
#endif








void apInit(void)
{
  #ifdef _USE_AP_BOOT
  cmdInit(&cmd_boot);
  cmdOpen(&cmd_boot, _DEF_UART1, 115200);
  #else
  cliOpen(_DEF_UART1, 115200);

  cliAdd("info", cliInfo);
  cliAdd("boot", cliBoot);
  #endif
}

void apMain(void)
{
  uint32_t pre_time;

  while(1)
  {
    if (millis()-pre_time >= 100)
    {
      pre_time = millis();
      ledToggle(_DEF_LED1);
    }

    #ifdef _USE_AP_BOOT
    if (cmdReceivePacket(&cmd_boot) == true)
    {
      bootProcessCmd(&cmd_boot);
    }
    #else
    cliMain();
    #endif
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

  if (args->argc == 1 && args->isStr(0, "jump"))
  {
    cliPrintf("JumpToFw()\n");
    delay(50);

    jumpToFw();
    ret = true;
  }


  if (ret != true)
  {
    cliPrintf("info flash\n");
  }
}

void cliBoot(cli_args_t *args)
{
  bool ret = false;

  if (args->argc == 1 && args->isStr(0, "jump"))
  {
    cliPrintf("jump to fw\n");
    delay(50);

    jumpToFw();
    ret = true;
  }


  if (ret != true)
  {
    cliPrintf("boot jump\n");
  }
}