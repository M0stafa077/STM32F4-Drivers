/**
 ******************************************************************************
 * @file           : rcc.c
 * @author         : Mostafa Asaad (https://github.com/M0stafa077)
 * @brief          : Reset and Clock Control Module Static Code Implementation.
 ******************************************************************************
 */

/* --------------- Section : Includes --------------- */
#include "MCAL/RCC/rcc.h"
/*---------------  Section: Static Functions Decllaration --------------- */
static inline __attribute__((always_inline)) void RCC_Osc_Config(const RCC_InitConfigs_t * rcc_cfgs);
static inline __attribute__((always_inline)) void RCC_ClockSource_Config(const RCC_Clock_Source_t Clock_Source);
static inline __attribute__((always_inline)) void RCC_Bus_Pre_Config(const RCC_InitConfigs_t * rcc_cfgs);
static inline __attribute__((always_inline)) void RCC_PLL_Config(const RCC_InitConfigs_t * rcc_cfgs);
/*---------------  Section: Function Definitions --------------- */
Std_ReturnType_t RCC_Init(const RCC_InitConfigs_t * rcc_cfgs)
{
	Std_ReturnType_t Ret_Value = E_OK;
	if(NULL == rcc_cfgs)
		{ Ret_Value = E_NOT_OK; }
	else
	{
		/* 1. Configure the Oscillator */
		RCC_Osc_Config(rcc_cfgs);

		/* 2. Configure the Clock Source */
		if(rcc_cfgs->Clock_Source == RCC_CLOCK_SOURCE_PLL)
			{ RCC_PLL_Config(rcc_cfgs); }
		RCC_ClockSource_Config(rcc_cfgs->Clock_Source);

		/* 3. Configure all the Prescalers */
		RCC_Bus_Pre_Config(rcc_cfgs);
	}
	return Ret_Value;
}

void RCC_Switch_Systen_Clock(const RCC_Clock_Source_t Clock_Source)
{
	RCC_ClockSource_Config(Clock_Source);
}

RCC_Clock_Source_t RCC_Get_Systen_Clock(void)
{
	return (RCC->CFGR & (3UL << 2)) >> 2;
}

/*---------------  Section: Static Functions Definitions --------------- */
static inline void RCC_Osc_Config(const RCC_InitConfigs_t * rcc_cfgs)
{
	if(RCC_HSE_ON == rcc_cfgs->Oscillator_Configurations.HSE_State)
		{ SET_BIT(RCC->CR, 16); }
	else if(RCC_HSE_OFF == rcc_cfgs->Oscillator_Configurations.HSE_State)
		{ CLEAR_BIT(RCC->CR, 16); }

	if(RCC_HSI_ON == rcc_cfgs->Oscillator_Configurations.HSI_State)
		{ SET_BIT(RCC->CR, 0); }
	else if(RCC_HSI_OFF == rcc_cfgs->Oscillator_Configurations.HSI_State)
		{ CLEAR_BIT(RCC->CR, 0); }

	if(RCC_PLLI2S_ON == rcc_cfgs->Oscillator_Configurations.PLLI2S)
	{ SET_BIT(RCC->CR, 26); }
	else if(RCC_PLLI2S_OFF == rcc_cfgs->Oscillator_Configurations.PLLI2S)
		{ CLEAR_BIT(RCC->CR, 26); }
}

static inline void RCC_ClockSource_Config(const RCC_Clock_Source_t Clock_Source)
{
	RCC->CFGR &= ~((uint32_t)(RCC_SW_MASK << RCC_SW_POS));
	switch(Clock_Source)
	{
		case RCC_CLOCK_SOURCE_HSI:
			RCC->CFGR |= (RCC_HSI_SW_MASK << RCC_SW_POS);
			break;
		case RCC_CLOCK_SOURCE_HSE:
			RCC->CFGR |= (RCC_HSE_SW_MASK << RCC_SW_POS);
			break;
		case RCC_CLOCK_SOURCE_PLL:
			RCC->CFGR |= (RCC_PLL_SW_MASK << RCC_SW_POS);
			break;
		default: RCC->CFGR |= (RCC_HSI_SW_MASK << RCC_SW_POS);
				break;
	}
}

static inline void RCC_Bus_Pre_Config(const RCC_InitConfigs_t * rcc_cfgs)
{
	// 1. AHB Prescaler:
	RCC->CFGR |= (rcc_cfgs->AHB_Prescaler << RCC_HPRE_POS);
	// 2. APB1 Prescaler:
	RCC->CFGR |= (rcc_cfgs->APB1_Prescaler << RCC_PPRE1_POS);
	// 3. APB2 Prescaler:
	RCC->CFGR |= (rcc_cfgs->APB2_Prescaler << RCC_PPRE2_POS);
}

static inline void RCC_PLL_Config(const RCC_InitConfigs_t * rcc_cfgs)
{
	/* !< 1. Disable the PLL Circuit */
	RCC_PLL_DISABLE();

	/* !< 2. Assign the PLL Clock Source */
//	RCC->PLLCFGR &= ~((uint32_t)(rcc_cfgs->PLL_Configurations.Pll_) << 22);
	RCC->PLLCFGR |= ((uint32_t)(rcc_cfgs->PLL_Configurations.Pll_Clk_Src) << 22);

	/* !< 2. Assign the Prescalers */
	// PLL_M: Division factor for the main PLL
	RCC->PLLCFGR &= ~(0x0000003F);
	RCC->PLLCFGR |= (uint32_t)(rcc_cfgs->PLL_Configurations.PLL_M);
	// PLLN: Main PLL (PLL) multiplication factor
	RCC->PLLCFGR &= ~(0x000001FFU << 6);
	RCC->PLLCFGR |= (uint32_t)((rcc_cfgs->PLL_Configurations.PLL_N) << (6));
	// PLL_P: Main PLL (PLL) division factor
	RCC->PLLCFGR &= ~(0X00000003U << 16);
	RCC->PLLCFGR |= (uint32_t)((rcc_cfgs->PLL_Configurations.PLL_P) << (16));
	// PLL_Q
	RCC->PLLCFGR &= ~(0X0000000FU << 24);
	RCC->PLLCFGR |= (uint32_t)((rcc_cfgs->PLL_Configurations.PLL_Q) << (24));

	/* !< 3. Enable the PLL Circuit */
	RCC_PLL_ENABLE();
}




