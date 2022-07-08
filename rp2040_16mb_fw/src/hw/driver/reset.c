/*
 * reset.c
 *
 *  Created on: 2021. 2. 23.
 *      Author: baram
 */






#include "reset.h"
#include "cli.h"


#ifdef _USE_HW_RESET


#define RESET_BOOT_RAM_ADDR         0x20000000
#define BOOT_MSG_STR(x)             #x
#define RESET_COUNT_DELAY           500


typedef struct
{
  uint32_t magic_number;
  uint32_t boot_mode;
  uint32_t boot_mode_xor;

  uint32_t reset_src;
  uint32_t reset_src_xor;

  uint32_t reset_count;
  uint32_t reset_count_xor;
} reset_boot_mode_t;


static void cliReset(cli_args_t *args);
static uint32_t resetUpdateBootMode(void);
static uint32_t resetUpdateCount(void);

static reset_boot_mode_t *p_boot_mode = (reset_boot_mode_t *)RESET_BOOT_RAM_ADDR;
static uint32_t run_timeout_count = 0;
static uint32_t reset_boot_mode = RESET_MODE_FW;
static uint32_t reset_count = 0;





void resetISR(void)
{
  if (run_timeout_count > 0)
  {
    run_timeout_count--;

    if (run_timeout_count == 0)
    {
      resetToRunBoot();
    }
  }
}






void resetInit(void)
{
  /*
  p_boot_mode->magic_number = MAGIC_NUMBER;

  reset_count = resetUpdateCount();
  reset_boot_mode = resetUpdateBootMode();
  */
  resetSetBootMode(RESET_MODE_FW);

  cliAdd("reset", cliReset);
}

void resetSetBootMode(uint32_t mode)
{
  p_boot_mode->boot_mode = mode;
  p_boot_mode->boot_mode_xor = mode ^ 0xFFFFFFFF;
}

uint32_t resetUpdateBootMode(void)
{
  uint32_t boot_mode;

  boot_mode = p_boot_mode->boot_mode_xor ^ 0xFFFFFFFF;

  if (p_boot_mode->magic_number == MAGIC_NUMBER && 
      p_boot_mode->boot_mode != boot_mode)
  {
    resetSetBootMode(RESET_MODE_FW);
  }

  return p_boot_mode->boot_mode;
}

uint32_t resetUpdateCount(void)
{
  uint32_t ret;

  if (p_boot_mode->reset_count != (p_boot_mode->reset_count_xor ^ 0xFFFFFFFF))
  {
    p_boot_mode->reset_count = 0;
    p_boot_mode->reset_count_xor = p_boot_mode->reset_count ^ 0xFFFFFFFF;
  }
  p_boot_mode->reset_count++;
  p_boot_mode->reset_count_xor = p_boot_mode->reset_count ^ 0xFFFFFFFF;
  delay(RESET_COUNT_DELAY);
  ret = p_boot_mode->reset_count;
  
  p_boot_mode->reset_count = 0;
  p_boot_mode->reset_count_xor = 0;

  return ret;  
}

uint32_t resetGetBootMode(void)
{
  return reset_boot_mode;
}

uint32_t resetGetCount(void)
{
  return reset_count;
}

void resetToBoot(uint32_t timeout)
{
  if (timeout == 0)
  {
    resetToRunBoot();
  }
  else
  {
    run_timeout_count = timeout;
  }
}

void resetToRunBoot(void)
{
  resetSetBootMode(RESET_MODE_BOOT);
  NVIC_SystemReset();
}

void resetToRunFw(void)
{
  resetSetBootMode(RESET_MODE_FW);
  NVIC_SystemReset();
}

const char *resetGetBootModeMsg(void)
{
  const char *ret_str = "NONE";
  uint32_t reset_mode;


  reset_mode = resetGetBootMode();

  switch(reset_mode)
  {
    case RESET_MODE_BOOT:
      ret_str = BOOT_MSG_STR(RESET_MODE_BOOT);
      break;

    case RESET_MODE_FW:
      ret_str = BOOT_MSG_STR(RESET_MODE_FW);
      break;
  }

  return ret_str;
}

void cliReset(cli_args_t *args)
{
  bool ret = false;


  if (args->argc == 1 && args->isStr(0, "info"))
  {
    cliPrintf("magic         : 0x%X\n", p_boot_mode->magic_number);
    cliPrintf("boot mode     : 0x%X\n", p_boot_mode->boot_mode);
    cliPrintf("boot mode xor : 0x%X\n", p_boot_mode->boot_mode_xor);    
    cliPrintf("get mode      : %d\n", resetGetBootMode());
    cliPrintf("get mode str  : %s\n", resetGetBootModeMsg());
    cliPrintf("reset count   : %d\n", reset_count);
    ret = true;
  }
  
  if (args->argc == 1 && args->isStr(0, "run_boot"))
  {
    cliPrintf("run boot\n");
    delay(50);
    resetToRunBoot();
    ret = true;
  }

  if (args->argc == 1 && args->isStr(0, "run_fw"))
  {
    cliPrintf("run fw\n");
    delay(50);
    resetToRunFw();
    ret = true;
  }


  if (ret != true)
  {
    cliPrintf("reset info\n");
    cliPrintf("reset run_boot\n");
    cliPrintf("reset run_fw\n");
  }
}
#endif