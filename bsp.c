/*
 *BSP.c
 *
 *BOARD SUPPORT PACKAGE
 *
 * 
 * author: Ömer Faruk Koç
 */
#include "stm32g0xx.h"
#include "bsp.h"
#include <math.h>

void HardFault_Handler(void)
{
	__asm("ldr   r0, =_estack"); /*set stack pointer */
	__asm("mov   sp, r0");
	NVIC_SystemReset();
	__asm("b Reset_Handler");

}

void BSP_pin_init(char abc, int pinnum, char type)
{
	if (type == 'O')
	{
		if (abc == 'A')
		{
			RCC->IOPENR |= (1U << 0);
			GPIOA->MODER &= ~(3U << 2 *pinnum);
			GPIOA->MODER |= (1U << 2 *pinnum);
		}
		else if (abc == 'B')
		{
			RCC->IOPENR |= (2U << 0);
			GPIOB->MODER &= ~(3U << 2 *pinnum);
			GPIOB->MODER |= (1U << 2 *pinnum);

		}
		else if (abc == 'C')
		{
			RCC->IOPENR |= (4U << 0);
			GPIOC->MODER &= ~(3U << 2 *pinnum);
			GPIOC->MODER |= (1U << 2 *pinnum);
		}
	}
	else if (type == 'I')
	{
		if (abc == 'A')
		{
			RCC->IOPENR |= (1U << 0);
			GPIOA->MODER &= ~(3U << 2 *pinnum);

		}
		else if (abc == 'B')
		{
			RCC->IOPENR |= (2U << 0);
			GPIOB->MODER &= ~(3U << 2 *pinnum);

		}
		else if (abc == 'C')
		{
			RCC->IOPENR |= (4U << 0);
			GPIOC->MODER &= ~(3U << 2 *pinnum);

		}
	}
}

void BSP_output_set(char abc, int pinnum)
{
	if (abc == 'A')
	{
		GPIOA->ODR |= 1U << (pinnum);

	}
	else if (abc == 'B')
	{
		GPIOB->ODR |= 1U << (pinnum);

	}
	else if (abc == 'C')
	{
		GPIOC->ODR |= 1U << (pinnum);
	}
}

int BSP_input_read(char abc, int pinnum)
{
	int x;
	if (abc == 'A')
	{
		x = (GPIOA->IDR >> pinnum) &1;

	}
	else if (abc == 'B')
	{
		x = (GPIOB->IDR >> pinnum) &1;
	}

	return x;
}

void BSP_output_toggle(char abc, int pinnum)
{
	if (abc == 'A')
	{
		GPIOA->ODR ^= (1U << (pinnum));

	}
	else if (abc == 'B')
	{
		GPIOB->ODR ^= (1U << (pinnum));

	}
	else if (abc == 'C')
	{
		GPIOC->ODR ^= (1U << (pinnum));
	}
}

void BSP_output_reset(char abc, int pinnum)
{
	if (abc == 'A')
	{
		GPIOA->BRR |= 1U << (pinnum);

	}
	else if (abc == 'B')
	{
		GPIOB->BRR |= 1U << (pinnum);

	}
	else if (abc == 'C')
	{
		GPIOC->BRR |= 1U << (pinnum);
	}
}

void BSP_timer_init(int timer_num, int reload_value, int priority)
{
	if (timer_num == 2)
	{
		RCC->APBENR1 |= (1U << 0);	//timer 2 clock open

		TIM2->CR1 = 0;
		TIM2->CR1 |= (1U << 7);	//arpe

		TIM2->ARR = reload_value;

		TIM2->DIER |= (1U << 0);
		TIM2->CR1 |= (1U << 0);

		NVIC_SetPriority(TIM2_IRQn, priority);
		NVIC_EnableIRQ(TIM2_IRQn);

		TIM2->CNT = 4294967295;	//max value
		/*reason for this it is not working other way*/
	}
	else if (timer_num == 3)
	{
		RCC->APBENR1 |= (1U << 1);	//timer 2 clock open

		TIM3->CR1 = 0;
		TIM3->CR1 |= (1U << 7);	//arpe

		TIM3->ARR = reload_value;

		TIM3->DIER |= (1U << 0);
		TIM3->CR1 |= (1U << 0);

		NVIC_SetPriority(TIM3_IRQn, priority);
		NVIC_EnableIRQ(TIM3_IRQn);

		TIM3->CNT = 4294967295;	//max value
		/*reason for this it is not working other way*/
	}
	else if (timer_num == 1)
	{
		RCC->APBENR2 |= (1U << 11);	//timer 1 clock open

		TIM1->CR1 = 0;
		TIM1->CR1 |= (1U << 7);	//arpe

		TIM1->ARR = reload_value / 999;
		TIM1->PSC = 999;
		TIM1->DIER |= (1U << 0);
		TIM1->CR1 |= (1U << 0);

		NVIC_SetPriority(TIM3_IRQn, priority);
		NVIC_EnableIRQ(TIM3_IRQn);

		TIM3->CNT = 4294967295;	//max value
		/*reason for this it is not working other way*/
	}
}

void BSP_timer_flagup(int timer_num)
{
	if (timer_num == 1)
		TIM1->SR &= ~(1U << 0);
	else if (timer_num == 2)
		TIM2->SR &= ~(1U << 0);
	else if (timer_num == 3)
		TIM3->SR &= ~(1U << 0);

}

void BSP_EXTI_init(char abc, int pinnumber, int priority)
{
	EXTI->IMR1 |= (1U << pinnumber);
	EXTI->RTSR1 |= (1U << pinnumber);

	if (abc == 'A')
	{
		if (pinnumber == 0 || pinnumber == 1 || pinnumber == 2 || pinnumber == 3)
		{
			EXTI->EXTICR[0] &= ~(1U << 8 *pinnumber);
			if (pinnumber == 0 || pinnumber == 1)
			{
				NVIC_SetPriority(EXTI0_1_IRQn, priority);
				NVIC_EnableIRQ(EXTI0_1_IRQn);
			}
			else
			{
				NVIC_SetPriority(EXTI2_3_IRQn, priority);
				NVIC_EnableIRQ(EXTI2_3_IRQn);

			}
		}
		else if (pinnumber == 4 || pinnumber == 5 || pinnumber == 6 || pinnumber == 7)
		{
			pinnumber = pinnumber % 4;
			EXTI->EXTICR[1] &= ~(1U << 8 *pinnumber);
			NVIC_SetPriority(EXTI4_15_IRQn, priority);
			NVIC_EnableIRQ(EXTI4_15_IRQn);

		}
		else if (pinnumber == 8 || pinnumber == 9 || pinnumber == 10 || pinnumber == 11)
		{
			pinnumber = pinnumber % 4;
			EXTI->EXTICR[2] &= ~(1U << 8 *pinnumber);
			NVIC_SetPriority(EXTI4_15_IRQn, priority);
			NVIC_EnableIRQ(EXTI4_15_IRQn);

		}
		else if (pinnumber == 12 || pinnumber == 13 || pinnumber == 14 || pinnumber == 15)
		{
			pinnumber = pinnumber % 4;
			EXTI->EXTICR[3] &= ~(1U << 8 *pinnumber);
			NVIC_SetPriority(EXTI4_15_IRQn, priority);
			NVIC_EnableIRQ(EXTI4_15_IRQn);

		}
	}
	else if (abc == 'B')
	{
		if (pinnumber == 0 || pinnumber == 1 || pinnumber == 2 || pinnumber == 3)
		{
			EXTI->EXTICR[0] |= (1U << 8 *pinnumber);
			if (pinnumber == 0 || pinnumber == 1)
			{
				NVIC_SetPriority(EXTI0_1_IRQn, priority);
				NVIC_EnableIRQ(EXTI0_1_IRQn);
			}
			else
			{
				NVIC_SetPriority(EXTI2_3_IRQn, priority);
				NVIC_EnableIRQ(EXTI2_3_IRQn);

			}
		}
		else if (pinnumber == 4 || pinnumber == 5 || pinnumber == 6 || pinnumber == 7)
		{
			pinnumber = pinnumber % 4;
			EXTI->EXTICR[1] |= (1U << 8 *pinnumber);
			NVIC_SetPriority(EXTI4_15_IRQn, priority);
			NVIC_EnableIRQ(EXTI4_15_IRQn);

		}
		else if (pinnumber == 8 || pinnumber == 9 || pinnumber == 10 || pinnumber == 11)
		{
			pinnumber = pinnumber % 4;
			EXTI->EXTICR[2] |= (1U << 8 *pinnumber);
			NVIC_SetPriority(EXTI4_15_IRQn, priority);
			NVIC_EnableIRQ(EXTI4_15_IRQn);

		}
		else if (pinnumber == 12 || pinnumber == 13 || pinnumber == 14 || pinnumber == 15)
		{
			pinnumber = pinnumber % 4;
			EXTI->EXTICR[3] |= (1U << 8 *pinnumber);
			NVIC_SetPriority(EXTI4_15_IRQn, priority);
			NVIC_EnableIRQ(EXTI4_15_IRQn);

		}
	}
	else if (abc == 'C')
	{
		if (pinnumber == 0 || pinnumber == 1 || pinnumber == 2 || pinnumber == 3)
		{
			EXTI->EXTICR[0] |= (2U << 8 *pinnumber);
			if (pinnumber == 0 || pinnumber == 1)
			{
				NVIC_SetPriority(EXTI0_1_IRQn, priority);
				NVIC_EnableIRQ(EXTI0_1_IRQn);
			}
			else
			{
				NVIC_SetPriority(EXTI2_3_IRQn, priority);
				NVIC_EnableIRQ(EXTI2_3_IRQn);

			}
		}
		else if (pinnumber == 4 || pinnumber == 5 || pinnumber == 6 || pinnumber == 7)
		{
			pinnumber = pinnumber % 4;
			EXTI->EXTICR[1] |= (2U << 8 *pinnumber);
			NVIC_SetPriority(EXTI4_15_IRQn, priority);
			NVIC_EnableIRQ(EXTI4_15_IRQn);

		}
		else if (pinnumber == 8 || pinnumber == 9 || pinnumber == 10 || pinnumber == 11)
		{
			pinnumber = pinnumber % 4;
			EXTI->EXTICR[2] |= (2U << 8 *pinnumber);
			NVIC_SetPriority(EXTI4_15_IRQn, priority);
			NVIC_EnableIRQ(EXTI4_15_IRQn);

		}
		else if (pinnumber == 12 || pinnumber == 13 || pinnumber == 14 || pinnumber == 15)
		{
			pinnumber = pinnumber % 4;
			EXTI->EXTICR[3] |= (2U << 8 *pinnumber);
			NVIC_SetPriority(EXTI4_15_IRQn, priority);
			NVIC_EnableIRQ(EXTI4_15_IRQn);

		}
	}
}

void BSP_IWDG_init(void)
{
	IWDG->KR = 0xCCCCU;
	IWDG->KR = 0x5555U;
	IWDG->PR = 7;
	IWDG->RLR = 1250;
}

void BSP_feed_dog(void)
{
	IWDG->KR = 0xAAAAU;
}
