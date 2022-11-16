/*
 * ssd.h
 *
 * BOARD SUPPORT PACKAGE
 *
 * 
 * author: Ömer Faruk Koç
 */

#ifndef SSD_H_
#define SSD_H_

#include "stm32g0xx.h"
#include "keypad.h"
#include "ssd.h"
#include "bsp.h"
#include <math.h>

void screen_open(int);
void display(int);

void BSP_ssd_init(void);
void BSP_ssd_set(int);


void delay(volatile uint32_t);

#endif
