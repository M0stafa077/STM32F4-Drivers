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
#include "CortexM4/SysTick/SysTick.h"
#include "MCAL/DMA/dma.h"
#include "MCAL/FLASH/flash.h"

void RCC_Clock_Config();


static volatile uint32_t x = 0;
Std_ReturnType_t retVal = E_OK;


DMA_InitTypeDef dma_cfgs =
{
	.Channel = DMA_CHANNEL_5,
	.Direction = DMA_PREPH_TO_MEMORY,
	.MemInc = DMA_MINC_ENABLE,
	.Mode = DMA_NORMAL,
	.PeriphInc = DMA_PINC_DISABLE,
	.Priority = DMA_PRIORITY_MEDIUM
};

DMA_Stream_InitCfgs_t stream_cfgs =
{
	.Memory_Address = (uint32_t)&x,
	.No_Of_Items = 15000,
	.Peripheral_Address = 0x4001204C,
	.Stream_Idx = 0
};

int main(void)
{
	NVIC_SetPriorityGrouping(NVIC_PRIORITY_GROUP_2_BITS);
	RCC_Clock_Config();

//	uint32_t No_Of_Ticks = 2000000;
//	retVal = SysTick_Init(No_Of_Ticks);
//	retVal = SysTick_PeriodicInterval(No_Of_Ticks, SysTick_ExcepHandler);
//	retVal |= DMA1_Init(&dma_cfgs, &stream_cfgs);
//	retVal |= Flash_Erase_Sector(FLASH_SECTOR_5);
//	retVal |= Flash_Erase_Mass();
//	retVal |= Flash_Program(&x, 0x12345678);
//	retVal |= Flash_Program(&x, 0x000000AA);
//	retVal |= Flash_SetReadProtection(FLASH_READ_PROTECT_LEV0);
//	retVal |= Flash_SetWriteProtection(FLASH_SECTOR_5);



    while(1)
    {
//    	x++;
    }
    return 0;
}


void SysTick_ExcepHandler(void)
{ x++; }

void RCC_Clock_Config()
{
	RCC_InitConfigs_t rcc_cfgs =
	{
		.Oscillator_Configurations = { RCC_HSE_OFF, RCC_HSI_ON, RCC_PLLI2S_OFF },
		.Clock_Source = RCC_CLOCK_SOURCE_HSI,
		.AHB_Prescaler = SYSTEM_CLOCK_NOT_DIVIDED,
		.APB1_Prescaler = APB1_CLOCK_NOT_DIVIDED,
		.APB2_Prescaler = APB2_CLOCK_NOT_DIVIDED,
		.PLL_Configurations = {
			RCC_PLL_SOURE_HSI,		// Clock Src
			0xA8,					// N
			0x08,					// M
			0x04,					// Q
			RCC_PLL_P_DIVIDE_BY_4	// P
		}
	};
	RCC_Init(&rcc_cfgs);
}


