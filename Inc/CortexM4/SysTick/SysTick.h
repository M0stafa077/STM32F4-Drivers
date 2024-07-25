/**
 ******************************************************************************
 * @file           : SysTick.h
 * @author         : Mostafa Asaad (https://github.com/M0stafa077)
 * @brief          : System-Timer Device-Driver Header Interface File.
 ******************************************************************************
 */

#ifndef CORTEXM4_SYSTICK_SYSTICK_H_
#define CORTEXM4_SYSTICK_SYSTICK_H_

/* --------------- Section : Includes --------------- */
#include "Common/Std_Types.h"
#include "SysTick_Cfg.h"
#include "../NVIC/NVIC.h"
/* --------------- Section: Macro Declarations --------------- */
#define SYSTICK_BASE_ADDRESS			(0xE000E010)
#define SysTick							((SysTick_Registers_t *)(SYSTICK_BASE_ADDRESS))

#define SYSTICK_ENABLE_BIT_POS			0UL
#define SYSTICK_EXCEPTION_EN_POS		1UL
#define SYSTICK_CLKSOURCE_BIT_POS		2UL
#define SYSTICK_COUNTFLAG_BIT_POS		16UL

#define SYSTICK_MODE_INIT_VALUE			0U
#define SYSTICK_MODE_SINGLE_INTERVAL	1U
#define SYSTICK_MODE_PERIODIC_INTERVAL	2U

/* --------------- Section: Macro Functions Declarations --------------- */

/* @brief Function-Like-Macro Enables the SysTick Timer */
#define SYSTICK_TIMER_ENABLE()			(SET_BIT(SysTick->CSR, SYSTICK_ENABLE_BIT_POS))
/* @brief Function-Like-Macro Disables the SysTick Timer */
#define SYSTICK_TIMER_DISABLE()			(CLEAR_BIT(SysTick->CSR, SYSTICK_ENABLE_BIT_POS))

/* @brief Function-Like-Macro Enables the SysTick Timer Exception */
#define SYSTICK_EXCEPTION_ENABLE()		(SET_BIT(SysTick->CSR, SYSTICK_EXCEPTION_EN_POS))
/* @brief Function-Like-Macro Disables the SysTick Timer Exception */
#define SYSTICK_EXCEPTION_DISABLE()		(CLEAR_BIT(SysTick->CSR, SYSTICK_EXCEPTION_EN_POS))

/* @brief Function-Like-Macro Selects SysTick Clock Without Prescaler */
#define SYSTICK_CLK_WITHOUT_PRESCALER()	(SET_BIT(SysTick->CSR, SYSTICK_CLKSOURCE_BIT_POS))
/* @brief Function-Like-Macro Selects SysTick Clock With Prescaler */
#define SYSTICK_CLK_WITH_PRESCALER()	(CLEAR_BIT(SysTick->CSR, SYSTICK_CLKSOURCE_BIT_POS))

/* @brief Function-Like-Macro Returns 1 if timer counted to 0 */
#define SYSTICK_GET_COUNTFLAG()			(READ_BIT(SysTick->CSR, SYSTICK_COUNTFLAG_BIT_POS))

/* --------------- Section: Data Type Declarations --------------- */

typedef struct
{
	volatile uint32_t CSR;		/* !< SysTick Control and Status Register */
	volatile uint32_t RVR;		/* !< SysTick Reload Value Register */
	volatile uint32_t CVR;		/* !< SysTick Current Value Register */
	volatile uint32_t CALIB;	/* !< SysTick Calibration Value Register */
} SysTick_Registers_t;
/*---------------  Section: Function Declarations --------------- */

/*
 * @brief A software interface initializes the SysTick timer.
 * @param No_Of_Ticks: Number of timer ticks to fire an interrupt.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType_t SysTick_Init(uint32_t No_Of_Ticks);
/*
 * @brief A software interface de-initializes the SysTick timer.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType_t SysTick_DeInit(void);
/*
 * @brief A software interface halts the processor execution for a
 * defined interval.
 * @param delay_ms: The delay time in milliseconds.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType_t SysTick_Delay_ms(uint32_t No_Of_Ticks);
/*
 * @brief A software interface fires one interrupt request
 * for one interval only.
 * @param No_Of_Ticks: Number of timer ticks to fire an interrupt.
 * @param isr: Pointer to the callback function.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType_t SysTick_SingleInterval(uint32_t No_Of_Ticks, Interrupt_Handler_t isr);
/*
 * @brief A software interface fires one interrupt request
 * for periodic intervals of time.
 * @param No_Of_Ticks: Number of timer ticks to fire an interrupt.
 * @param isr: Pointer to the callback function.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType_t SysTick_PeriodicInterval(uint32_t No_Of_Ticks, Interrupt_Handler_t isr);


#endif /* CORTEXM4_SYSTICK_SYSTICK_H_ */
