#include "bsp.h"






bool bspInit(void)
{
  // overclock the rp2040 to 250mhz
  //set_sys_clock_khz(250000, true);

  
  stdio_init_all();
  
  __enable_irq();
  
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