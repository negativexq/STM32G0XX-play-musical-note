/*
 * keypad.h
 *
 * BOARD SUPPORT PACKAGE
 *
 * 
 * author: Ömer Faruk Koç 
 *
 */

#ifndef KYP_H_
#define KYP_H_

#include "stm32g0xx.h"
#include "keypad.h"
#include "ssd.h"
#include "bsp.h"
#include <math.h>

int keypad_control(int);
void BSP_numpad_init(void);


#endif
