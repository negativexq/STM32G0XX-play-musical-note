/*
 *main.c
 *
 *
 * a
 * author: Ömer Faruk Koç
 */
#include "stm32g0xx.h"
#include "bsp.h"
#include "ssd.h"
#include "keypad.h"

static volatile uint32_t Scount = 0;
static volatile int button_prevent = 0;
static volatile float freq = 1;

void delay_ms(volatile uint32_t s)
{
	Scount = s;
	while (Scount);
}
void PWM_init(void)
{
	RCC->IOPENR |= (1U << 0);	// A clock open

	GPIOA->MODER &= ~(3U << 2 *7);
	GPIOA->MODER |= (2U << 2 *7);	// making A7 alterna mode

	GPIOA->OSPEEDR |= (3U << 2 *7);	// for very very fast changes

	// PA7 AF1 is TIM3_CH2
	GPIOA->AFR[0] &= ~(0xFU << 4 *7);	// AFSEL7 reset
	GPIOA->AFR[0] |= (1U << 4 *7);	// AFSEL7 to AF1 0001

	//setuping TIM3

	RCC->APBENR1 |= (1U << 1);	//timer 3 clock open

	TIM3->CR1 = 0;
	TIM3->CR1 |= (1U << 7);	//arpe

	TIM3->ARR = freq;
	TIM3->PSC = 999;
	TIM3->DIER |= (1U << 0);

	TIM3->CNT = 4294967295;	//max value
	/*reason for this it is not working other way*/

	TIM3->CCMR1 &= ~(0x7U << 12);	//first clean OC2M[2:0]
	TIM3->CCMR1 &= ~(0x1U << 24);	//clean OC2M[3]
	TIM3->CCMR1 |= (0x6U << 12);	//OC2M must be[0110]
	//now its 0110
	TIM3->CCMR1 |= (1U << 11);	//OC2PE  enable the preload
	TIM3->CCER |= (1U << 4);	// Compare 2 output enable

	TIM3->CCR2 = freq*0.6;
	TIM3->CR1 |= (1U << 0);
	NVIC_SetPriority(TIM3_IRQn, 1);
	NVIC_EnableIRQ(TIM3_IRQn);
}

void TIM3_IRQHandler(void){


	BSP_timer_flagup(3);
}
void TIM2_IRQHandler(void){
	if(freq == 1)
		BSP_ssd_set(0);
	else
		BSP_ssd_set(freq);
	BSP_timer_flagup(2);
}

void SysTick_Handler(void)
{
	if (Scount > 0)
		Scount--;

	else if (Scount == 0)
		button_prevent = 0;

}

void EXTI4_15_IRQHandler(void)
{

	if (button_prevent == 1) {}
	else
	{
		Scount = 70; //prevent double click by button prevent
		button_prevent = 1; // prevent for double click.
		int C1, C2, C3, C4; // It will reset after 700ms in Systick Handler
		int pressed = -1; //default value -1 because didn't use for any button press returns
		delay(SystemCoreClock/800); // little delay for debounce about 50ms

		C1 = BSP_input_read('B', 4); //reading coloums first
		C2 = BSP_input_read('B', 5);
		C3 = BSP_input_read('B', 8);
		C4 = BSP_input_read('B', 9);

		if (C1 == 1)
			pressed = keypad_control(1); //detecting which button pressed
		else if (C2 == 1)
			pressed = keypad_control(2); //pressed button number goes to pressed
		else if (C3 == 1)
			pressed = keypad_control(3);
		else if (C4 == 1)
			pressed = keypad_control(4);

		switch(pressed){
		case 1: freq = 26; break; //do
		case 2: freq = 28; break;//re
		case 3: freq = 30; break;//mi
		case 4: freq = 36; break;//fa
		case 5: freq = 40; break;//sol
		case 6: freq = 44; break;//la
		case 7: freq = 48; break;//si
		case 8: freq = 52; break;
		case 9: freq = 53; break;
		case 10: freq = 22; break;
		case 11: freq = 20; break;
		case 12: freq = 85; break;
		case 13: freq = 56; break;
		case 14: freq = 60; break;
		case 15: freq = 65; break;
		case 0: freq = 1; break;

		default : freq = freq; break;
		}

	}
	TIM3->ARR = freq;
	TIM3->CCR2 = freq*0.6;
	EXTI->RPR1 |= (1U << 4); //pending all interrupts for nolur nolmaz

	EXTI->RPR1 |= (1U << 5);

	EXTI->RPR1 |= (1U << 8);

	EXTI->RPR1 |= (1U << 9);

}

int main(void)
{
	BSP_ssd_init(); //seven segment display init

	BSP_numpad_init(); // numpad init

	BSP_output_set('A', 8); //Rows set
	BSP_output_set('A', 9);
	BSP_output_set('A', 10);
	BSP_output_set('A', 15);

	BSP_EXTI_init('B', 4, 0); // C1 EXTI4_15 init for pin 4 high priority
	BSP_EXTI_init('B', 5, 0); // C2 EXTI4_15 init for pin 5 high priority
	BSP_EXTI_init('B', 8, 0); // C3 EXTI4_15 init for pin 8 high priority
	BSP_EXTI_init('B', 9, 0); // C4 EXTI4_15 init for pin 9 high priority

	PWM_init();

	SysTick_Config(SystemCoreClock / 1000); //systick enable

	BSP_timer_init(2,SystemCoreClock/120,2);

	while (1) {


	}

	return 0;
}



