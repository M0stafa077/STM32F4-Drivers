/**
 ******************************************************************************
 * @file           : NVIC.c
 * @author         : Mostafa Asaad (https://github.com/M0stafa077)
 * @brief          : NVIC Devicce-Driver Code Implementation File.
 ******************************************************************************
 */
/* --------------- Section : Includes --------------- */
#include "CortexM4/NVIC/NVIC.h"
/* --------------- Section: Global Variables --------------- */

/*---------------  Section: Functions Definition --------------- */
/**
  @brief   Enable Interrupt
  @details Enables a device specific interrupt in the NVIC interrupt controller.
  @param [in]      IRQn  Device specific interrupt number.
  @note    IRQn must not be negative.
 */
void NVIC_EnableIRQ(IRQn_t IRQn)
{
	if(0 <= IRQn)
	{
		NVIC->ISER[((uint32_t)IRQn) >> 5UL] = ((uint32_t)1UL << ((uint32_t)IRQn % REG_WIDTH));
	}
}
/**
  @brief   Disable Interrupt
  @details Disables a device specific interrupt in the NVIC interrupt controller.
  @param [in]      IRQn  Device specific interrupt number.
  @note    IRQn must not be negative.
 */
void NVIC_DisableIRQ(IRQn_t IRQn)
{
	if(0 <= IRQn)
	{
		NVIC->ICER[((uint32_t)IRQn) >> 5UL] = ((uint32_t)1UL << ((uint32_t)IRQn % REG_WIDTH));
	}
}
/**
  @brief   Get Interrupt Enable status
  @details Returns a device specific interrupt enable status from the NVIC interrupt controller.
  @param [in]      IRQn  Device specific interrupt number.
  @return             0  Interrupt is not enabled.
  @return             1  Interrupt is enabled.
  @note    IRQn must not be negative.
 */
uint32_t NVIC_GetEnableIRQ(IRQn_t IRQn)
{
	if(0 <= IRQn)
	{
		return ((NVIC->ICER[((uint32_t)IRQn) >> 5UL]) >> (((uint32_t)IRQn % REG_WIDTH))) & 1UL;
	}
	return 0;
}
/**
  @brief   Set Pending Interrupt
  @details Sets the pending bit of a device specific interrupt in the NVIC pending register.
  @param [in]      IRQn  Device specific interrupt number.
  @note    IRQn must not be negative.
 */
void NVIC_SetPending(IRQn_t IRQn)
{
	if(0 <= IRQn)
	{
		NVIC->ISPR[((uint32_t)IRQn) >> 5UL] = ((uint32_t)1UL << ((uint32_t)IRQn % REG_WIDTH));
	}
}
/**
  @brief   Clear Pending Interrupt
  @details Clears the pending bit of a device specific interrupt in the NVIC pending register.
  @param [in]      IRQn  Device specific interrupt number.
  @note    IRQn must not be negative.
 */
void NVIC_ClearPending(IRQn_t IRQn)
{
	if(0 <= IRQn)
	{
		NVIC->ICPR[((uint32_t)IRQn) >> 5UL] = ((uint32_t)1UL << ((uint32_t)IRQn % REG_WIDTH));
	}
}
/**
  @brief   Get Pending Interrupt
  @details Reads the NVIC pending register and returns the pending bit for the specified device specific interrupt.
  @param [in]      IRQn  Device specific interrupt number.
  @return             0  Interrupt status is not pending.
  @return             1  Interrupt status is pending.
  @note    IRQn must not be negative.
 */
uint32_t NVIC_GetPending(IRQn_t IRQn)
{
	if(0 <= IRQn)
	{
		return ((NVIC->ISPR[((uint32_t)IRQn) >> 5UL]) >> (((uint32_t)IRQn % REG_WIDTH))) & 1UL;
	}
	return 0;
}
/**
  @brief   Get Active Interrupt
  @details Reads the active register in the NVIC and returns the active bit for the device specific interrupt.
  @param [in]      IRQn  Device specific interrupt number.
  @return             0  Interrupt status is not active.
  @return             1  Interrupt status is active.
  @note    IRQn must not be negative.
 */
uint32_t NVIC_GetActiveStatus(IRQn_t IRQn)
{
	if(0 <= IRQn)
	{
		return ((NVIC->IABR[((uint32_t)IRQn) >> 5UL]) >> (((uint32_t)IRQn % REG_WIDTH))) & 1UL;
	}
	return 0;
}

/**
  @brief   Set Priority Grouping
  @details Sets the priority grouping field using the required unlock sequence.
           The parameter PriorityGroup is assigned to the field SCB->AIRCR [10:8] PRIGROUP field.
           Only values from 0..7 are used.
           In case of a conflict between priority grouping and available
           priority bits (__NVIC_PRIO_BITS), the smallest possible priority group is set.
  @param [in]      PriorityGroup  Priority grouping field.
 */
void NVIC_SetPriorityGrouping(uint32_t PriorityGroup)
{
	/* Get the Current value of the AIRCR Register */
	uint32_t AIRCR_Register_Value = SCB->AIRCR;
	/* Reset the wanted bits */
	AIRCR_Register_Value &= ~((0xFFFFUL << 16UL) | (0x07UL << 8UL));
	/* Calculate the new register value */
	AIRCR_Register_Value |= (0x05FA << 16UL) | ((uint32_t)PriorityGroup << 8UL);
	/* Write the new register value */
	SCB->AIRCR = AIRCR_Register_Value;
}

/**
  @brief   Set Interrupt Priority
  @details Sets the priority of a device specific interrupt or a processor exception.
           The interrupt number can be positive to specify a device specific interrupt,
           or negative to specify a processor exception.
  @param [in]      IRQn  Interrupt number.
  @param [in]  priority  Priority to set.
  @note    The priority cannot be set for every processor exception.
 */
void NVIC_SetPriority(IRQn_t IRQn, uint32_t Priority)
{
	if(IRQn >= 0)
	{
		NVIC->IP[(uint32_t)IRQn] = (uint8_t)(((uint8_t)Priority << 4UL) & 0xFFUL);
	}
	else
	{

	}
}
/**
  @brief   Get Interrupt Priority
  @details Reads the priority of a device specific interrupt or a processor exception.
           The interrupt number can be positive to specify a device specific interrupt,
           or negative to specify a processor exception.
  @param [in]   IRQn  Interrupt number.
  @return             Interrupt Priority.
                      Value is aligned automatically to the implemented priority bits of the microcontroller.
 */
uint32_t NVIC_GetPriority(IRQn_t IRQn)
{
	if(IRQn >= 0)
	{
		return (NVIC->IP[(uint32_t)IRQn] >> 4) & 0x0FUL;
	}
	else
	{
		return 0UL;
	}
}
