/**
 ******************************************************************************
 * @file           : stm32f401_registers.h
 * @author         : Mostafa Asaad (https://github.com/M0stafa077)
 * @brief          : Register Fefinition File for STM32F401RCT6 Peripherals.
 ******************************************************************************
 */


#ifndef COMMON_STM32F401_REGISTERS_H_
#define COMMON_STM32F401_REGISTERS_H_

/* --------------- Section : Includes --------------- */
#include "Std_Types.h"

/* -------------------------- RCC Defines Start ----------------------------- */
#define RCC_BASE_ADDRESS		0x40023800
#define RCC						((RCC_Registers_t *)(RCC_BASE_ADDRESS))

/**
  * @brief Reset and Clock Control
  */
typedef struct
{
	volatile uint32_t CR;			/* !< RCC clock control register */
	volatile uint32_t PLLCFGR;		/* !< RCC PLL configuration register */
	volatile uint32_t CFGR;			/* !< RCC clock configuration register */
	volatile uint32_t CIR;			/* !< RCC clock interrupt register */
	volatile uint32_t AHB1RSTR;		/* !< RCC AHB1 peripheral reset register */
	volatile uint32_t AHB2RSTR;		/* !< RCC AHB2 peripheral reset register */
	uint32_t RESERVED[2];			/* !< Reserved */
	volatile uint32_t APB1RSTR;		/* !< RCC APB1 peripheral reset register */
	volatile uint32_t APB2RSTR;		/* !< RCC APB2 peripheral reset register */
	uint32_t RESERVED1[2];			/* !< Reserved */
	volatile uint32_t AHB1ENR;		/* !< RCC AHB1 peripheral clock register */
	volatile uint32_t AHB2ENR;		/* !< RCC AHB2 peripheral clock register */
	uint32_t RESERVED2[2];			/* !< Reserved */
	volatile uint32_t APB1ENR;		/* !< RCC APB1 peripheral clock register */
	volatile uint32_t APB2ENR;		/* !< RCC APB2 peripheral clock register */
	uint32_t RESERVED3[2];			/* !< Reserved */
	volatile uint32_t AHB1LPENR;	/* !< RCC AHB1 peripheral clock enable in low power mode register */
	volatile uint32_t AHB2LPENR;	/* !< RCC AHB2 peripheral clock enable in low power mode register */
	uint32_t RESERVED4[2];			/* !< Reserved */
	volatile uint32_t APB1LPENR;	/* !< RCC APB1 peripheral clock enable in low power mode register */
	volatile uint32_t APB2LPENR;	/* !< RCC APB2 peripheral clock enable in low power mode register */
	uint32_t RESERVED5[2];			/* !< Reserved */
	volatile uint32_t BDCR;			/* !< RCC Backup domain control register */
	volatile uint32_t CSR;			/* !< RCC clock control & status register */
	uint32_t RESERVED6[2];			/* !< Reserved */
	volatile uint32_t SSCGR;		/* !< RCC spread spectrum clock generation register */
	volatile uint32_t PLLI2SCFGR; 	/* !< RCC PLLI2S configuration register */
	uint32_t RESERVED7;				/* !< Reserved */
	volatile uint32_t DCKCFGR;		/* !< RCC Dedicated Clocks configuration register */
} RCC_Registers_t;
/* -------------------------- RCC Defines End ----------------------------- */

#endif /* COMMON_STM32F401_REGISTERS_H_ */
