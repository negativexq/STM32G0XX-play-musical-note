/*
 *ssd.c
 *
 *definition: Includes seven segment display pin settings, display float-integer-negative numbers, display text.
 *
 * 
 * author: Ömer Faruk Koç
 */
#include "stm32g0xx.h"
#include "keypad.h"
#include "ssd.h"
#include "bsp.h"
#include <math.h>

static volatile int SSD_DELAY = 8000;

void BSP_ssd_init(void)
{
	/*please use this pin numbers */

	BSP_pin_init('A', 0, 'O');	// a A0
	BSP_pin_init('A', 1, 'O');	// b A1
	BSP_pin_init('A', 4, 'O');	// c A2
	BSP_pin_init('A', 5, 'O');	// d A3
	BSP_pin_init('A', 12, 'O');	// e A4
	BSP_pin_init('A', 11, 'O');	// f A5
	BSP_pin_init('A', 6, 'O');	// g A6

	BSP_pin_init('B', 6, 'O');	// d1 B6
	BSP_pin_init('B', 7, 'O');	// d2 B7
	BSP_pin_init('B', 1, 'O');	// d3 B1
	BSP_pin_init('B', 3, 'O');	// d4 B3

}

void BSP_ssd_set(int number){

		int digit = 0;

		digit = number / 1000;
		screen_open(1);
		display(digit);
		delay(SSD_DELAY);

		number = (number - digit *1000);
		digit = number / 100;
		screen_open(2);
		display(digit);
		delay(SSD_DELAY);

		number = (number - digit *100);
		digit = number / 10;
		screen_open(3);
		display(digit);
		delay(SSD_DELAY);

		number = (number - digit *10);
		digit = number;
		screen_open(4);
		display(digit);
		delay(SSD_DELAY);

	}



void screen_open(int screen_num)
{
	if (screen_num == 1)
	{
		/*PB0-1-2-3 as seven segment d1-d2-d3-d4*/
		GPIOB->ODR &= 0;
		GPIOB->ODR |= (1U << 6);
	}
	else if (screen_num == 2)
	{
		/*PB0-2-3-4 as seven segment d1-d2-d3-d4*/
		GPIOB->ODR &= 0;
		GPIOB->ODR |= (1U << 7);
	}
	else if (screen_num == 3)
	{
		/*PB0-2-3-4 as seven segment d1-d2-d3-d4*/
		GPIOB->ODR &= 0;
		GPIOB->ODR |= (1U << 1);
	}
	else if (screen_num == 4)
	{
		/*PB0-2-3-4 as seven segment d1-d2-d3-d4*/
		GPIOB->ODR &= 0;
		GPIOB->ODR |= (1U << 3);
	}
}

void display(int digit)
{
	GPIOA->ODR &= 0;
	GPIOA->ODR = ~GPIOA->ODR;

	if (digit == -1)
	{
		GPIOA->ODR &= ~(1U << 6);	//g

	}
	else if (digit == 0)
	{
		GPIOA->ODR &= ~(1U << 0);	//a
		GPIOA->ODR &= ~(1U << 1);	//b
		GPIOA->ODR &= ~(1U << 4);	//c
		GPIOA->ODR &= ~(1U << 5);	//d
		GPIOA->ODR &= ~(1U << 12);	//e
		GPIOA->ODR &= ~(1U << 11);	//f
	}
	else if (digit == 1)
	{
		GPIOA->ODR &= ~(1U << 1);	//b
		GPIOA->ODR &= ~(1U << 4);	//c

	}
	else if (digit == 2)
	{
		GPIOA->ODR &= ~(1U << 0);	//a
		GPIOA->ODR &= ~(1U << 1);	//b

		GPIOA->ODR &= ~(1U << 5);	//d
		GPIOA->ODR &= ~(1U << 12);	//e

		GPIOA->ODR &= ~(1U << 6);	//g
	}
	else if (digit == 3)
	{
		GPIOA->ODR &= ~(1U << 0);	//a
		GPIOA->ODR &= ~(1U << 1);	//b
		GPIOA->ODR &= ~(1U << 4);	//c
		GPIOA->ODR &= ~(1U << 5);	//d
		GPIOA->ODR &= ~(1U << 6);	//g
	}
	else if (digit == 4)
	{
		GPIOA->ODR &= ~(1U << 1);	//b
		GPIOA->ODR &= ~(1U << 4);	//c

		GPIOA->ODR &= ~(1U << 11);	//f
		GPIOA->ODR &= ~(1U << 6);	//g
	}
	else if (digit == 5)
	{
		GPIOA->ODR &= ~(1U << 0);	//a
		GPIOA->ODR &= ~(1U << 4);	//c
		GPIOA->ODR &= ~(1U << 5);	//d
		GPIOA->ODR &= ~(1U << 11);	//f
		GPIOA->ODR &= ~(1U << 6);	//g
	}
	else if (digit == 6)
	{
		GPIOA->ODR &= ~(1U << 0);	//a

		GPIOA->ODR &= ~(1U << 4);	//c
		GPIOA->ODR &= ~(1U << 5);	//d
		GPIOA->ODR &= ~(1U << 12);	//e
		GPIOA->ODR &= ~(1U << 11);	//f
		GPIOA->ODR &= ~(1U << 6);	//g
	}
	else if (digit == 7)
	{
		GPIOA->ODR &= ~(1U << 0);	//a
		GPIOA->ODR &= ~(1U << 1);	//b
		GPIOA->ODR &= ~(1U << 4);	//c

	}
	else if (digit == 8)
	{
		GPIOA->ODR &= ~(1U << 0);	//a
		GPIOA->ODR &= ~(1U << 1);	//b
		GPIOA->ODR &= ~(1U << 4);	//c
		GPIOA->ODR &= ~(1U << 5);	//d
		GPIOA->ODR &= ~(1U << 12);	//e
		GPIOA->ODR &= ~(1U << 11);	//f
		GPIOA->ODR &= ~(1U << 6);	//g
	}
	else if (digit == 9)
	{
		GPIOA->ODR &= ~(1U << 0);	//a
		GPIOA->ODR &= ~(1U << 1);	//b
		GPIOA->ODR &= ~(1U << 4);	//c
		GPIOA->ODR &= ~(1U << 5);	//d
		GPIOA->ODR &= ~(1U << 11);	//f
		GPIOA->ODR &= ~(1U << 6);	//g
	}
}


void delay(volatile uint32_t s)
{
	for (int i = 0; i < s; ++i);

}
