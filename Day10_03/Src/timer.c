/*
 * timer.c
 *
 *  Created on: Apr 4, 2024
 *      Author: sourabh
 */
#include<stdio.h>
#include "i2c_lcd.h"
#include "timer.h"

volatile int counter = 0;

void TimerInit(uint32_t ms) {

	RCC->APB1ENR |= RCC_APB1ENR_TIM7EN;

	TIM7->PSC = TIM_PR-1;

	uint16_t cnt = (TCLK / 1000) * ms / TIM_PR;
	TIM7->ARR = cnt - 1;

	TIM7->CNT = 0;

	TIM7->DIER |= TIM_DIER_UIE;

	NVIC_EnableIRQ(TIM7_IRQn);

	TIM7->CR1 |= TIM_CR1_CEN;
}


void TIM7_IRQHandler (void)
{
	char str[24];

	if(TIM7->SR & TIM_SR_UIF) {

		TIM7->SR &= ~TIM_SR_UIF;

		    counter++;
			sprintf(str, "Count %d",counter);
			LcdPuts(LCD_LINE2, str);

	}
}




