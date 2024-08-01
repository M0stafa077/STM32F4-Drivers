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

/* -------------------------- DMA Defines Start ----------------------------- */
#define DMA1_BASE_ADDRESS		0x40026000
#define DMA1					((DMA_Registers_t *)(DMA1_BASE_ADDRESS))
#define DMA2_BASE_ADDRESS		0x40026400
#define DMA2					((DMA_Registers_t *)(DMA2_BASE_ADDRESS))

/*
 * @defgroup	DMA1 Streams
 */
#define DMA1_STR0_BASE_ADDRESS	(DMA1_BASE_ADDRESS + 0x10)
#define DMA1_STREAM0			((DMA_Stream_Registers_t *)(DMA1_STR0_BASE_ADDRESS))
#define DMA1_STR1_BASE_ADDRESS	(DMA1_BASE_ADDRESS + 0x28)
#define DMA1_STREAM1			((DMA_Stream_Registers_t *)(DMA1_STR1_BASE_ADDRESS))
#define DMA1_STR2_BASE_ADDRESS	(DMA1_BASE_ADDRESS + 0x40)
#define DMA1_STREAM2			((DMA_Stream_Registers_t *)(DMA1_STR2_BASE_ADDRESS))
#define DMA1_STR3_BASE_ADDRESS	(DMA1_BASE_ADDRESS + 0x58)
#define DMA1_STREAM3			((DMA_Stream_Registers_t *)(DMA1_STR3_BASE_ADDRESS))
#define DMA1_STR4_BASE_ADDRESS	(DMA1_BASE_ADDRESS + 0x70)
#define DMA1_STREAM4			((DMA_Stream_Registers_t *)(DMA1_STR4_BASE_ADDRESS))
#define DMA1_STR5_BASE_ADDRESS	(DMA1_BASE_ADDRESS + 0x88)
#define DMA1_STREAM5			((DMA_Stream_Registers_t *)(DMA1_STR5_BASE_ADDRESS))
#define DMA1_STR6_BASE_ADDRESS	(DMA1_BASE_ADDRESS + 0xA0)
#define DMA1_STREAM6			((DMA_Stream_Registers_t *)(DMA1_STR6_BASE_ADDRESS))
#define DMA1_STR7_BASE_ADDRESS	(DMA1_BASE_ADDRESS + 0xB8)
#define DMA1_STREAM7			((DMA_Stream_Registers_t *)(DMA1_STR7_BASE_ADDRESS))

/*
 * @defgroup	DMA2 Streams
 */
#define DMA2_STR0_BASE_ADDRESS	(DMA2_BASE_ADDRESS + 0x10)
#define DMA2_STREAM0			((DMA_Stream_Registers_t *)(DMA2_STR0_BASE_ADDRESS))
#define DMA2_STR1_BASE_ADDRESS	(DMA2_BASE_ADDRESS + 0x28)
#define DMA2_STREAM1			((DMA_Stream_Registers_t *)(DMA2_STR1_BASE_ADDRESS))
#define DMA2_STR2_BASE_ADDRESS	(DMA2_BASE_ADDRESS + 0x40)
#define DMA2_STREAM2			((DMA_Stream_Registers_t *)(DMA2_STR2_BASE_ADDRESS))
#define DMA2_STR3_BASE_ADDRESS	(DMA2_BASE_ADDRESS + 0x58)
#define DMA2_STREAM3			((DMA_Stream_Registers_t *)(DMA2_STR3_BASE_ADDRESS))
#define DMA2_STR4_BASE_ADDRESS	(DMA2_BASE_ADDRESS + 0x70)
#define DMA2_STREAM4			((DMA_Stream_Registers_t *)(DMA2_STR4_BASE_ADDRESS))
#define DMA2_STR5_BASE_ADDRESS	(DMA2_BASE_ADDRESS + 0x88)
#define DMA2_STREAM5			((DMA_Stream_Registers_t *)(DMA2_STR5_BASE_ADDRESS))
#define DMA2_STR6_BASE_ADDRESS	(DMA2_BASE_ADDRESS + 0xA0)
#define DMA2_STREAM6			((DMA_Stream_Registers_t *)(DMA2_STR6_BASE_ADDRESS))
#define DMA2_STR7_BASE_ADDRESS	(DMA2_BASE_ADDRESS + 0xB8)
#define DMA2_STREAM7			((DMA_Stream_Registers_t *)(DMA2_STR7_BASE_ADDRESS))


/**
  * @brief Direct-Memory-Access
  */
typedef struct
{
	volatile uint32_t CR;     /*!< DMA stream x configuration register      */
	volatile uint32_t NDTR;   /*!< DMA stream x number of data register     */
	volatile uint32_t PAR;    /*!< DMA stream x peripheral address register */
	volatile uint32_t M0AR;   /*!< DMA stream x memory 0 address register   */
	volatile uint32_t M1AR;   /*!< DMA stream x memory 1 address register   */
	volatile uint32_t FCR;    /*!< DMA stream x FIFO control register       */
} DMA_Stream_Registers_t;

typedef struct
{
	volatile uint32_t LISR;   /*!< DMA low interrupt status register,      Address offset: 0x00 */
	volatile uint32_t HISR;   /*!< DMA high interrupt status register,     Address offset: 0x04 */
	volatile uint32_t LIFCR;  /*!< DMA low interrupt flag clear register,  Address offset: 0x08 */
	volatile uint32_t HIFCR;  /*!< DMA high interrupt flag clear register, Address offset: 0x0C */
	DMA_Stream_Registers_t Streams[8];
} DMA_Registers_t;

/* -------------------------- RCC Defines End ----------------------------- */



/* -------------------------- FLASH Defines Start ----------------------------- */

#define FLASH_BASE_ADDRESS			0x40023C00
#define FLASH						((FLASH_Registers_t * )(FLASH_BASE_ADDRESS))


typedef struct
{
	volatile uint32_t ACR;     		/*!< FLASH access control register, Address offset: 0x00 */
	volatile uint32_t KEYR;    		/*!< FLASH key register, Address offset: 0x04 */
	volatile uint32_t OPTKEYR; 		/*!< FLASH option key register, Address offset: 0x08 */
	volatile uint32_t SR;      		/*!< FLASH status register, Address offset: 0x0C */
	volatile uint32_t CR;      		/*!< FLASH control register, Address offset: 0x10 */
	volatile uint32_t OPTCR;		/*!< FLASH option Control register, Address offset: 0x14*/
} FLASH_Registers_t;

/* -------------------------- FLASH Defines End ----------------------------- */

#endif /* COMMON_STM32F401_REGISTERS_H_ */
