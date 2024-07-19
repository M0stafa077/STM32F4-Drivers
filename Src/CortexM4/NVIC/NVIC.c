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
