#include "bsp.h"






bool bspInit(void)
{
  stdio_init_all();
  
  return true;
}

void delay(uint32_t time_ms)
{
  sleep_ms(time_ms);
}

uint32_t millis(void)
{  
  return to_ms_since_boot(get_absolute_time());
}