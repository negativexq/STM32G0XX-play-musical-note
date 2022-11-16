/*
 * BSP.h
 *
 * BOARD SUPPORT PACKAGE
 *
 * 
 * author: Ömer Faruk Koç 
 */

#ifndef BSP_H_
#define BSP_H_

#include "stm32g0xx.h"

void BSP_pin_init(char, int, char);
void BSP_output_set(char, int);
void BSP_output_toggle(char, int);
void BSP_output_reset(char, int);
int BSP_input_read(char, int);
void BSP_EXTI_init(char, int, int);
void BSP_timer_init(int, int, int);
void BSP_timer_flagup(int);
void BSP_IWDG_init(void);
void BSP_feed_dog(void);

#endif
