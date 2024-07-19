/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Mostafa Asaad (https://github.com/M0stafa077)
 * @brief          : Main program body
 ******************************************************************************
 */

#include <stdint.h>
#include "CortexM4/NVIC/NVIC.h"

static volatile uint32_t isr_flag = 0;
static volatile uint32_t Interrupt_Active_Status = 0;
static uint32_t IRQ_Status = 0;

int main(void)
{
	NVIC_EnableIRQ(EXTI4_IRQn);

	Interrupt_Active_Status = NVIC_GetActiveStatus(EXTI4_IRQn);

	IRQ_Status = NVIC_GetEnableIRQ(EXTI4_IRQn);

	NVIC_SetPending(EXTI4_IRQn);

	Interrupt_Active_Status = NVIC_GetActiveStatus(EXTI4_IRQn);

	NVIC_DisableIRQ(EXTI4_IRQn);

	IRQ_Status = NVIC_GetEnableIRQ(EXTI4_IRQn);

    while(1)
    {

    }
}

void EXTI4_IRQHandler(void)
{
	isr_flag = 1;
	Interrupt_Active_Status = NVIC_GetActiveStatus(EXTI4_IRQn);
}
