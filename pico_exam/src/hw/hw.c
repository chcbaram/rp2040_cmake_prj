/*
 * hw.c
 *
 *  Created on: Jun 13, 2021
 *      Author: baram
 */

#include "hw.h"





bool hwInit(void)
{  
  bspInit();

  cliInit();
  ledInit();
  uartInit();
  uartOpen(_DEF_UART1, 57600);

  return true;
}