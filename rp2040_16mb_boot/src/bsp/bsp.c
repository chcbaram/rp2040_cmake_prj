#include "bsp.h"






bool bspInit(void)
{
  // overclock the rp2040 to 250mhz
  //set_sys_clock_khz(250000, true);

  stdio_init_all();
  
  __enable_irq();

  return true;
}

void bspDeInit(void)
{
   __disable_irq();

  // Disable Interrupts
  //
  for (int i=0; i<1; i++)
  {
    NVIC->ICER[i] = 0xFFFFFFFF;
    __DSB();
    __ISB();
  }
  SysTick->CTRL = 0;
}

void delay(uint32_t time_ms)
{
  sleep_ms(time_ms);
}

uint32_t millis(void)
{  
  return to_ms_since_boot(get_absolute_time());
}