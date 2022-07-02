/*
 * bsp.h
 *
 *  Created on: Jun 13, 2021
 *      Author: baram
 */

#ifndef SRC_BSP_BSP_H_
#define SRC_BSP_BSP_H_

#include "def.h"


#ifdef __cplusplus
 extern "C" {
#endif

#include "RP2040.h"
#include "hardware/clocks.h"
#include "hardware/flash.h"
#include "pico/stdlib.h"
#include "pico/platform.h"


bool bspInit(void);

void delay(uint32_t time_ms);
uint32_t millis(void);


void logPrintf(const char *fmt, ...);


#ifdef __cplusplus
 }
#endif

#endif /* SRC_BSP_BSP_H_ */