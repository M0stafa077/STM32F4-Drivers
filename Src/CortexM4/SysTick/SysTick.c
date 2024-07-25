/**
 ******************************************************************************
 * @file           : SysTick.c
 * @author         : Mostafa Asaad (https://github.com/M0stafa077)
 * @brief          : System-Timer Device-Driver Static Code Implementation.
 ******************************************************************************
 */
/* --------------- Section : Includes --------------- */
#include "CortexM4/SysTick/SysTick.h"
/*---------------  Section: Global Variables --------------- */
static Interrupt_Handler_t SysTick_Default_Interrupt_Handler = NULL;
static volatile uint8_t SysTick_Mode = SYSTICK_MODE_INIT_VALUE;
/*---------------  Section: Function Definitions --------------- */

/*
 * @brief A software interface initializes the SysTick timer.
 * @param No_Of_Ticks: Number of timer ticks to fire an interrupt.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType_t SysTick_Init(uint32_t No_Of_Ticks)
{
	Std_ReturnType_t retVal = E_OK;
	if((No_Of_Ticks > (16777215UL)) || (No_Of_Ticks == 0))
	{
		retVal = E_NOT_OK;
	}
	else
	{
		/* 1. Disable the SysTick timer */
		SYSTICK_TIMER_DISABLE();
		/* 2. Reset the counter register */
		SysTick->CVR = 0;
		/* 3. Initialize the Load register with the No_Of_Ticks */
		SysTick->RVR = No_Of_Ticks - 1;
		/* 4. Configure the SysTick Clock */
#if SYSTICK_CLOCK_SOURCE == SYSTICK_EXTERNAL_CLOCK
		SYSTICK_CLK_WITH_PRESCALER();
#elif SYSTICK_CLOCK_SOURCE == SYSTICK_PROCESSOR_CLOCK
		SYSTICK_CLK_WITHOUT_PRESCALER();
#else
#error "Invalid SysTick Clock Source Configurations"
#endif
		/* 5. Disable the SysTick Exceptions */
		SYSTICK_EXCEPTION_DISABLE();
	}
	return retVal;
}
/*
 * @brief A software interface de-initializes the SysTick timer.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType_t SysTick_DeInit(void)
{
	/* Disable the SysTic timer */
	SYSTICK_TIMER_DISABLE();
	/* Resset the relaod register */
	SysTick->RVR = 0;
	/* Reset the counter register */
	SysTick->CVR = 0;
	/* Disable the SysTic Exceptions */
	SYSTICK_EXCEPTION_DISABLE();

	return E_OK;
}
/*
 * @brief A software interface halts the processor execution for a
 * defined interval.
 * @param delay_ms: The delay time in milliseconds.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType_t SysTick_Delay_ms(uint32_t No_Of_Ticks)
{
	Std_ReturnType_t retVal = E_OK;
	if((No_Of_Ticks > (16777215UL)) || (No_Of_Ticks == 0))
	{
		retVal = E_NOT_OK;
	}
	else
	{
		/* Set the re-load value */
		SysTick->RVR = No_Of_Ticks;
		/* Enable SysTick Timer */
		SYSTICK_TIMER_ENABLE();
		/* Wait */
		while(0 == SYSTICK_GET_COUNTFLAG());
		/* Disable the Systick */
		SYSTICK_TIMER_DISABLE();
		/* Reset the LOAD value */
		SysTick->RVR = 0;
		/* Reset the Counter Register */
		SysTick->CVR = 0;
	}

	return retVal;
}
/*
 * @brief A software interface fires one interrupt request
 * for one interval only.
 * @param No_Of_Ticks: Number of timer ticks to fire an interrupt.
 * @param isr: Pointer to the callback function.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType_t SysTick_SingleInterval(uint32_t No_Of_Ticks, Interrupt_Handler_t isr)
{
	Std_ReturnType_t retVal = E_OK;
	if((No_Of_Ticks > (16777215UL)) || (No_Of_Ticks == 0))
	{
		retVal = E_NOT_OK;
	}
	else
	{
		/* Set the re-load value */
		SysTick->RVR = No_Of_Ticks;
		/* Assign the Callback Function */
		SysTick_Default_Interrupt_Handler = isr;
		/* Set the SysTic Mode flag to single interval */
		SysTick_Mode = SYSTICK_MODE_SINGLE_INTERVAL;
		/* Enable the SysTic timer exception */
		SYSTICK_EXCEPTION_ENABLE();
		/* Set the SysTic exception priority */
		NVIC_SetPriority(SysTick_IRQn, 0);
		/* Enable the SysTic timer */
		SYSTICK_TIMER_ENABLE();
	}
	return retVal;
}
/*
 * @brief A software interface fires one interrupt request
 * for periodic intervals of time.
 * @param No_Of_Ticks: Number of timer ticks to fire an interrupt.
 * @param isr: Pointer to the callback function.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType_t SysTick_PeriodicInterval(uint32_t No_Of_Ticks, Interrupt_Handler_t isr)
{
	Std_ReturnType_t retVal = E_OK;
	if((No_Of_Ticks > (16777215UL)) || (No_Of_Ticks == 0))
	{
		retVal = E_NOT_OK;
	}
	else
	{
		/* Set the re-load value */
		SysTick->RVR = No_Of_Ticks;
		/* Assign the Callback Function */
		SysTick_Default_Interrupt_Handler = isr;
		/* Set the SysTic Mode flag to single interval */
		SysTick_Mode = SYSTICK_MODE_PERIODIC_INTERVAL;
		/* Enable the SysTic timer exception */
		SYSTICK_EXCEPTION_ENABLE();
		/* Set the SysTic exception priority */
		NVIC_SetPriority(SysTick_IRQn, 0);
		/* Enable the SysTic timer */
		SYSTICK_TIMER_ENABLE();
	}
	return retVal;
}




void SysTick_Handler(void)
{
	if(SYSTICK_MODE_SINGLE_INTERVAL == SysTick_Mode)
	{
		/* Disable the SysTic timer */
		SYSTICK_TIMER_DISABLE();
		/* Resset the relaod register */
		SysTick->RVR = 0;
		/* Reset the counter register */
		SysTick->CVR = 0;
		/* Disable the SysTic Exceptions */
		SYSTICK_EXCEPTION_DISABLE();
	}

	if(SysTick_Default_Interrupt_Handler)
		SysTick_Default_Interrupt_Handler();
}

