/**
 ******************************************************************************
 * @file           : SCB.h
 * @author         : Mostafa Asaad (https://github.com/M0stafa077)
 * @brief          : System-Control-Block Devicce-Driver Header Interface File.
 ******************************************************************************
 */
#ifndef CORTEXM4_SCB_SCB_H_
#define CORTEXM4_SCB_SCB_H_

/* --------------- Section : Includes --------------- */
#include "../../Std_Types.h"
/* --------------- Section: Macro Declarations --------------- */
#define SCB_BASE_ADDRESS			0xE000ED00

#define SCB							((SCB_t *)(SCB_BASE_ADDRESS))
/* --------------- Section: Macro Functions Declarations --------------- */

/* --------------- Section: Data Type Declarations --------------- */
typedef struct
{
	volatile uint32_t CPUID;		/*!< (R/ )  CPUID Base Register */
	volatile uint32_t ICSR;			/*!< (R/W)  Interrupt Control and State Register */
	volatile uint32_t VTOR;     	/*!< (R/W)  Vector Table Offset Register */
	volatile uint32_t AIRCR;    	/*!< (R/W)  Application Interrupt and Reset Control Register */
	volatile uint32_t SCR;      	/*!< (R/W)  System Control Register */
	volatile uint32_t CCR;         	/*!< (R/W)  Configuration Control Register */
	volatile uint32_t SHPR[12U];   	/*!< (R/W)  System Handlers Priority Registers (4-7, 8-11, 12-15) */
	volatile uint32_t SHCSR;       	/*!< (R/W)  System Handler Control and State Register */
	volatile uint32_t CFSR;        	/*!< (R/W)  Configurable Fault Status Register */
} SCB_t;
/*---------------  Section: Function Declarations --------------- */

#endif /* CORTEXM4_SCB_SCB_H_ */
