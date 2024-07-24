/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Mostafa Asaad (https://github.com/M0stafa077)
 * @brief          : Main program body
 ******************************************************************************
 */

#include <stdint.h>
#include "CortexM4/NVIC/NVIC.h"
#include "Common/stm32f401_registers.h"
#include "MCAL/RCC/rcc.h"


void RCC_Clock_Config();

int x = 0;

int main(void)
{

	RCC_Clock_Config();
    while(1)
    {
    	x++;
    	if(100 == x) x = 0;
    }
}

void RCC_Clock_Config()
{
	RCC_InitConfigs_t rcc_cfgs =
	{
		.Oscillator_Configurations = { RCC_HSE_OFF, RCC_HSI_ON, RCC_PLLI2S_OFF },
		.Clock_Source = RCC_CLOCK_SOURCE_PLL,
		.PLL_Configurations = {
				RCC_PLL_SOURE_HSI,		// Clock Src
				168,					// N
				8,						// M
				4,						// Q
				RCC_PLL_P_DIVIDE_BY_4	// P

		},
		.AHB_Prescaler = SYSTEM_CLOCK_NOT_DIVIDED,
		.APB1_Prescaler = APB1_CLOCK_DIVIDED_BY_2,
		.APB2_Prescaler = APB2_CLOCK_NOT_DIVIDED
	};
	RCC_Init(&rcc_cfgs);
}


