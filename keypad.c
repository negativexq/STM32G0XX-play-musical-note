/*
 *keypad.c
 *
 *definition : Includes keypad pin settings and algorithm for detect which button pressed.
 *
 * 
 * author: �mer Faruk Ko� 
 */
#include "stm32g0xx.h"
#include "keypad.h"
#include "ssd.h"
#include "bsp.h"
#include <math.h>

void BSP_numpad_init(void)
{
	/*please use this pin numbers */

	BSP_pin_init('A', 8, 'O');	// R1 D9
	BSP_pin_init('A', 9, 'O');	// R2 D5
	BSP_pin_init('A', 10, 'O');	// R3 D4
	BSP_pin_init('A', 15, 'O');	// R4 D2
	BSP_pin_init('B', 4, 'I');	// C1 D12
	BSP_pin_init('B', 5, 'I');	// C2 D11
	BSP_pin_init('B', 8, 'I');	// C3 D8
	BSP_pin_init('B', 9, 'I');	// C4 D10

}

int keypad_control(int s)
//This function detect that which button is pressing.
//When a button pressed, Cx variable is 1 by input_read. After that
//Rows are closing one by one to detect which button is pressed.
//Example: C1 is 1. After Row2 turn off C1 is 0. This means button is R2C1, 4. returning that value
{
	int numdig;
	if (s == 1)
	{
		int C1;
		BSP_output_reset('A', 8);
		C1 = BSP_input_read('B', 4);
		//delay(5000);
		if (C1 != 1)
		{
			numdig = 1;

		}

		BSP_output_set('A', 8);

		BSP_output_reset('A', 9);
		C1 = BSP_input_read('B', 4);
		//delay(5000);
		if (C1 != 1)
		{
			numdig = 4;

		}

		BSP_output_set('A', 9);

		BSP_output_reset('A', 10);
		C1 = BSP_input_read('B', 4);
		//delay(5000);
		if (C1 != 1)
		{
			numdig = 7;

		}

		BSP_output_set('A', 10);

		BSP_output_reset('A', 15);
		C1 = BSP_input_read('B', 4);
		//delay(5000);
		if (C1 != 1)
		{
			numdig = 10;	//yÄ±ldÄ±z
		}

		BSP_output_set('A', 15);

	}
	else if (s == 2)
	{
		BSP_output_reset('A', 8);
		int C2;
		C2 = BSP_input_read('B', 5);
		//delay(5000);
		if (C2 != 1)
		{
			numdig = 2;

		}

		BSP_output_set('A', 8);

		BSP_output_reset('A', 9);
		C2 = BSP_input_read('B', 5);
		//delay(5000);
		if (C2 != 1)
		{
			numdig = 5;

		}

		BSP_output_set('A', 9);

		BSP_output_reset('A', 10);
		C2 = BSP_input_read('B', 5);
		//delay(5000);
		if (C2 != 1)
		{
			numdig = 8;

		}

		BSP_output_set('A', 10);

		BSP_output_reset('A', 15);
		C2 = BSP_input_read('B', 5);
		//delay(5000);
		if (C2 != 1)
		{
			numdig = 0;
		}

		BSP_output_set('A', 15);

	}
	else if (s == 3)
	{
		BSP_output_reset('A', 8);
		int C3;
		C3 = BSP_input_read('B', 8);
		//delay(5000);
		if (C3 != 1)
		{
			numdig = 3;

		}

		BSP_output_set('A', 8);

		BSP_output_reset('A', 9);
		C3 = BSP_input_read('B', 8);
		//delay(5000);
		if (C3 != 1)
		{
			numdig = 6;

		}

		BSP_output_set('A', 9);

		BSP_output_reset('A', 10);
		C3 = BSP_input_read('B', 8);
		//delay(5000);
		if (C3 != 1)
		{
			numdig = 9;

		}

		BSP_output_set('A', 10);

		BSP_output_reset('A', 15);
		C3 = BSP_input_read('B', 8);
		//delay(5000);
		if (C3 != 1)
		{
			numdig = 11;	//kare gÃ¶nder
		}

		BSP_output_set('A', 15);

	}
	else if (s == 4)
	{
		BSP_output_reset('A', 8);
		int C4;
		C4 = BSP_input_read('B', 9);
		//delay(500);
		if (C4 != 1)
		{
			numdig = 12;
		}

		BSP_output_set('A', 8);

		BSP_output_reset('A', 9);
		C4 = BSP_input_read('B', 9);
		//delay(500);
		if (C4 != 1)
		{
			numdig = 13;
		}

		BSP_output_set('A', 9);

		BSP_output_reset('A', 10);
		C4 = BSP_input_read('B', 9);
		//delay(5000);
		if (C4 != 1)
		{
			numdig = 14;
		}

		BSP_output_set('A', 10);

		BSP_output_reset('A', 15);
		C4 = BSP_input_read('B', 9);
		//delay(5000);
		if (C4 != 1)
		{
			numdig = 15;
		}

		BSP_output_set('A', 15);
	}

	return numdig;
}
