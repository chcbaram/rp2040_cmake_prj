#include "ap.h"
#include "boot/boot.h"



bool is_boot_mode = true;

cmd_t cmd_boot;

void cliInfo(cli_args_t *args);
void cliBoot(cli_args_t *args);









void apInit(void)
{

  if (resetGetBootMode() == RESET_MODE_FW)
  {
    switch(resetGetCount())
    {
      case 2:
        is_boot_mode = true;
        break;

      case 3:
        is_boot_mode = false;
        break;

      default:
        bootJumpToFw();
        break;
    }
  }

  if (is_boot_mode == true)
  {
    cmdInit(&cmd_boot);
    cmdOpen(&cmd_boot, _DEF_UART1, 115200);
  }
  else
  {
    cliOpen(_DEF_UART1, 115200);

    cliAdd("info", cliInfo);
    cliAdd("boot", cliBoot);
  }
}

void apMain(void)
{
  uint32_t pre_time;
  uint32_t led_time = 100;

  if (is_boot_mode != true)
  {
    led_time = 50;
  }

  while(1)
  {
    if (millis()-pre_time >= led_time)
    {
      pre_time = millis();
      ledToggle(_DEF_LED1);
    }

    if (is_boot_mode == true)
    {
      if (cmdReceivePacket(&cmd_boot) == true)
      {
        bootProcessCmd(&cmd_boot);
      }
    }
    else
    {
      cliMain();
    }
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