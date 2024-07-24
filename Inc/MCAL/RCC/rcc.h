/**
 ******************************************************************************
 * @file           : rcc.h
 * @author         : Mostafa Asaad (https://github.com/M0stafa077)
 * @brief          : Header File Interface for the Reset and Clock Control Module
 *					 In STM32F401RCT6
 ******************************************************************************
 */

#ifndef MCAL_RCC_RCC_H_
#define MCAL_RCC_RCC_H_

/* --------------- Section : Includes --------------- */
#include "Common/Std_Types.h"
#include "Common/stm32f401_registers.h"
/* --------------- Section: Macro Declarations --------------- */

/** @defgroup RCC_HSE_Config HSE Config
  * @{
  */
#define RCC_HSE_OFF                     	0x00000000U
#define RCC_HSE_ON                      	0x00000001U

/** @defgroup RCC_HSI_Config HSI Config
  * @{
  */
#define RCC_HSI_OFF                     	0x00000000U
#define RCC_HSI_ON                     		0x00000001U

/** @defgroup RCC_PLLI2S_Config PLLI2S Config
  * @{
  */
#define RCC_PLLI2S_OFF                		0x00000000U
#define RCC_PLLI2S_ON                 		0x00000001U

#define RCC_SW_POS							0x00000000U
#define RCC_SW_MASK							0x00000003U
#define RCC_HSI_SW_MASK						0x00000000U
#define RCC_HSE_SW_MASK						0x00000001U
#define RCC_PLL_SW_MASK						0x00000002U

#define RCC_HPRE_POS						0x00000004U
#define RCC_PPRE1_POS						0x0000000AU
#define RCC_PPRE2_POS						0x0000000DU
/* --------------- Section: Macro Functions Declarations --------------- */
/* !< IO port A clock enable */
#define PORTA_CLOCK_ENABLE_POS				0
#define RCC_PORTA_CLOCK_ENABLE()			(SET_BIT(RCC->AHB1ENR, PORTA_CLOCK_ENABLE_POS))
#define RCC_PORTA_CLOCK_DISABLE()			(CLEAR_BIT(RCC->AHB1ENR, PORTA_CLOCK_ENABLE_POS))

/* !< IO port B clock enable */
#define PORTB_CLOCK_ENABLE_POS				1
#define RCC_PORTB_CLOCK_ENABLE()			(SET_BIT(RCC->AHB1ENR, PORTB_CLOCK_ENABLE_POS))
#define RCC_PORTB_CLOCK_DISABLE()			(CLEAR_BIT(RCC->AHB1ENR, PORTB_CLOCK_ENABLE_POS))

/* !< IO port C clock enable */
#define PORTC_CLOCK_ENABLE_POS				2
#define RCC_PORTC_CLOCK_ENABLE()			(SET_BIT(RCC->AHB1ENR, PORTC_CLOCK_ENABLE_POS))
#define RCC_PORTC_CLOCK_DISABLE()			(CLEAR_BIT(RCC->AHB1ENR, PORTC_CLOCK_ENABLE_POS))

/* !< IO port D clock enable */
#define PORTD_CLOCK_ENABLE_POS				3
#define RCC_PORTD_CLOCK_ENABLE()			(SET_BIT(RCC->AHB1ENR, PORTD_CLOCK_ENABLE_POS))
#define RCC_PORTD_CLOCK_DISABLE()			(CLEAR_BIT(RCC->AHB1ENR, PORTD_CLOCK_ENABLE_POS))

/* !< IO port E clock enable */
#define PORTE_CLOCK_ENABLE_POS				4
#define RCC_PORTE_CLOCK_ENABLE()			(SET_BIT(RCC->AHB1ENR, PORTE_CLOCK_ENABLE_POS))
#define RCC_PORTE_CLOCK_DISABLE()			(CLEAR_BIT(RCC->AHB1ENR, PORTE_CLOCK_ENABLE_POS))

/* !< IO port H clock enable */
#define PORTH_CLOCK_ENABLE_POS				7
#define RCC_PORTH_CLOCK_ENABLE()			(SET_BIT(RCC->AHB1ENR, PORTH_CLOCK_ENABLE_POS))
#define RCC_PORTH_CLOCK_DISABLE()			(CLEAR_BIT(RCC->AHB1ENR, PORTH_CLOCK_ENABLE_POS))

#define RCC_PLL_ENABLE()					(SET_BIT(RCC->CR, 24))
#define RCC_PLL_DISABLE()					(CLEAR_BIT(RCC->CR, 24))

/* --------------- Section: Data Type Declarations --------------- */
typedef enum
{
	RCC_OSC_NONE = 0x00000000U,
	RCC_OSC_HSE = 0x00000001U,
	RCC_OSC_LSE = 0x00000002U,
	RCC_OSC_HSI = 0x00000003U,
	RCC_OSC_LSI = 0x00000004U
} RCC_OscType_t;


typedef struct
{
	uint32_t HSE_State; 				/*!< The new state of the HSE.
                                      	  This parameter can be a value of @ref RCC_HSE_Config  */

	uint32_t HSI_State; 				/*!< The new state of the HSO.
                                      	  This parameter can be a value of @ref RCC_HSI_Config  */
	uint32_t PLLI2S;					/*!< The new state of the PLLI2S.
                                      	  This parameter can be a value of @ref RCC_PLLI2S_Config  */
} RCC_OscInit_t;

typedef enum
{
	RCC_CLOCK_SOURCE_HSI = 0,
	RCC_CLOCK_SOURCE_HSE = 1,
	RCC_CLOCK_SOURCE_PLL = 2
} RCC_Clock_Source_t;

typedef enum
{
	SYSTEM_CLOCK_NOT_DIVIDED = 0b0000,
	SYSTEM_CLOCK_DIVIDED_BY_2 = 0b1000,
	SYSTEM_CLOCK_DIVIDED_BY_4 = 0b1001,
	SYSTEM_CLOCK_DIVIDED_BY_8 = 0b1010,
	SYSTEM_CLOCK_DIVIDED_BY_16 = 0b1011,
	SYSTEM_CLOCK_DIVIDED_BY_64 = 0b1100,
	SYSTEM_CLOCK_DIVIDED_BY_128 = 0b1101,
	SYSTEM_CLOCK_DIVIDED_BY_256 = 0b1110,
	SYSTEM_CLOCK_DIVIDED_BY_512 = 0b1111
} RCC_AHB_Prescaler_t;

typedef enum
{
	APB1_CLOCK_NOT_DIVIDED = 0b000,
	APB1_CLOCK_DIVIDED_BY_2 = 0b100,
	APB1_CLOCK_DIVIDED_BY_4 = 0b101,
	APB1_CLOCK_DIVIDED_BY_8 = 0b110,
	APB1_CLOCK_DIVIDED_BY_16 = 0b111
} RCC_APB1_Prescaler_t;

typedef enum
{
	APB2_CLOCK_NOT_DIVIDED = 0b000,
	APB2_CLOCK_DIVIDED_BY_2 = 0b100,
	APB2_CLOCK_DIVIDED_BY_4 = 0b101,
	APB2_CLOCK_DIVIDED_BY_8 = 0b110,
	APB2_CLOCK_DIVIDED_BY_16 = 0b111
} RCC_APB2_Prescaler_t;

typedef enum
{
	RCC_PLL_SOURE_HSI = 0x00U,
	RCC_PLL_SOURE_HSE = 0x01U
} RCC_PLL_Source_t;

typedef enum
{
	RCC_PLL_P_DIVIDE_BY_2 = 0,
	RCC_PLL_P_DIVIDE_BY_4,
	RCC_PLL_P_DIVIDE_BY_6,
	RCC_PLL_P_DIVIDE_BY_8
} RCC_PLL_P_t;

typedef struct
{
	RCC_PLL_Source_t Pll_Clk_Src;	/* !< Main PLL (PLL) Clock source
	 	 	 	 	 	 	 	 	 Takes RCC_PLL_SOURE_HSI or RCC_PLL_SOURE_HSE */
	uint32_t PLL_N;					/* !< Main PLL (PLL) multiplication factor
										Takes a value from (192) to (432)
										Anything else is wrong configurations */
	uint32_t PLL_M;					/* !< Division factor for the main PLL
										Takes a value from (2) to (63) */
	uint32_t PLL_Q;					/* !< Main PLL (PLL) division factor for USB OTG FS,
										SDIO and random number generator clocks
	 	 	 	 	 	 	 	 	  	 Takes a value from (2) to (15) */
	uint32_t PLL_P;					/* !< Main PLL (PLL) division factor
	 	 	 	 	 	 	 	 	 	 for main system clock
	 	 	 	 	 	 	 	 		Takes 2, 4, 6, or 8*/
} RCC_PLL_Cfgs_t;

typedef struct
{
	RCC_OscInit_t Oscillator_Configurations;
	RCC_Clock_Source_t Clock_Source;
	RCC_AHB_Prescaler_t AHB_Prescaler;
	RCC_APB1_Prescaler_t APB1_Prescaler;
	RCC_APB2_Prescaler_t APB2_Prescaler;
	RCC_PLL_Cfgs_t PLL_Configurations;
} RCC_InitConfigs_t;
/*---------------  Section: Function Declarations --------------- */
Std_ReturnType_t RCC_Init(const RCC_InitConfigs_t * rcc_cfgs);

void RCC_Switch_Systen_Clock(const RCC_Clock_Source_t Clock_Source);
RCC_Clock_Source_t RCC_Get_Systen_Clock(void);

#endif /* MCAL_RCC_RCC_H_ */
