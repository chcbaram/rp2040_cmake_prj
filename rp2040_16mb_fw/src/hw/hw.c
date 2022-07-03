/*
 * hw.c
 *
 *  Created on: Jun 13, 2021
 *      Author: baram
 */

#include "hw.h"



volatile const firm_ver_t boot_ver __attribute__((section(".version"))) = 
{
  .magic_number = VERSION_MAGIC_NUMBER,
  .version_str  = _DEF_FIRMWATRE_VERSION,
  .name_str     = _DEF_BOARD_NAME,
};





bool hwInit(void)
{  
  bspInit();  

  cliInit();
  resetInit();
  logInit();
  ledInit();
  uartInit();
  uartOpen(_DEF_UART1, 115200);
  logOpen(_DEF_UART1, 115200);
  
  flashInit();

  logPrintf("[ Firmware Begin... ]\r\n");
  logPrintf("Booting..Name \t\t: %s\r\n", _DEF_BOARD_NAME);
  logPrintf("Booting..Ver  \t\t: %s\r\n", _DEF_FIRMWATRE_VERSION);
  logPrintf("Clk sys  \t\t: %d\r\n", clock_get_hz(clk_sys));
  logPrintf("Clk peri \t\t: %d\r\n", clock_get_hz(clk_peri));
  logPrintf("Clk usb  \t\t: %d\r\n", clock_get_hz(clk_usb));
  logPrintf("Clk adc  \t\t: %d\r\n", clock_get_hz(clk_adc));
  logPrintf("Clk rtc  \t\t: %d\r\n", clock_get_hz(clk_rtc));
  logPrintf("Clk timer\t\t: %d\r\n", clock_get_hz(clk_ref));
  logPrintf("\n");
  logPrintf("Reset Mode\t\t: %s\r\n", resetGetBootModeMsg());
  logPrintf("Reset Count\t\t: %d\r\n", resetGetCount());
  logPrintf("Version Addr\t\t: 0x%X\r\n", (int)&boot_ver);


  logBoot(false);

  return true;
}