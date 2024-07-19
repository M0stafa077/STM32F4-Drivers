/**
 ******************************************************************************
 * @file           : NVIC.h
 * @author         : Mostafa Asaad (https://github.com/M0stafa077)
 * @brief          : NVIC Devicce-Driver Header Interface File.
 ******************************************************************************
 */

#ifndef CORTEXM4_NVIC_NVIC_H_
#define CORTEXM4_NVIC_NVIC_H_

/* --------------- Section : Includes --------------- */
#include "../../Std_Types.h"
#include "../SCB/SCB.h"
/* --------------- Section: Macro Declarations --------------- */
#define REG_WIDTH			(uint32_t)32
#define REG_MAX_IDX			(uint32_t)31
#define NVIC_BASE_ADDRESS 	0xE000E100UL


#define NVIC				((NVIC_t *)(NVIC_BASE_ADDRESS))
/* --------------- Section: Macro Functions Declarations --------------- */

/* --------------- Section: Data Type Declarations --------------- */

/**
  @brief  Structure type to access the Nested Vectored Interrupt Controller (NVIC).
 */
typedef struct
{
	volatile uint32_t ISER[8U];               /*!< Offset: 0x000 (R/W)  Interrupt Set Enable Register */
	uint32_t RESERVED0[24U];
	volatile uint32_t ICER[8U];               /*!< Offset: 0x080 (R/W)  Interrupt Clear Enable Register */
	uint32_t RESERVED1[24U];
	volatile uint32_t ISPR[8U];               /*!< Offset: 0x100 (R/W)  Interrupt Set Pending Register */
	uint32_t RESERVED2[24U];
	volatile uint32_t ICPR[8U];               /*!< Offset: 0x180 (R/W)  Interrupt Clear Pending Register */
	uint32_t RESERVED3[24U];
	volatile uint32_t IABR[8U];               /*!< Offset: 0x200 (R/W)  Interrupt Active bit Register */
	uint32_t RESERVED4[56U];
	volatile uint8_t  IP[240U];               /*!< Offset: 0x300 (R/W)  Interrupt Priority Register (8Bit wide) */
	uint32_t RESERVED5[644U];
	volatile  uint32_t STIR;                   /*!< Offset: 0xE00 ( /W)  Software Trigger Interrupt Register */
} NVIC_t;


/**
 * @brief Interrupt Number Definition
 */
typedef enum
{
  /******  Cortex-M4 Processor Exceptions Numbers ****************************************************************/
  NonMaskableInt_IRQn         = -14,    /*!< 2 Non Maskable Interrupt                                          */
  MemoryManagement_IRQn       = -12,    /*!< 4 Cortex-M4 Memory Management Interrupt                           */
  BusFault_IRQn               = -11,    /*!< 5 Cortex-M4 Bus Fault Interrupt                                   */
  UsageFault_IRQn             = -10,    /*!< 6 Cortex-M4 Usage Fault Interrupt                                 */
  SVCall_IRQn                 = -5,     /*!< 11 Cortex-M4 SV Call Interrupt                                    */
  DebugMonitor_IRQn           = -4,     /*!< 12 Cortex-M4 Debug Monitor Interrupt                              */
  PendSV_IRQn                 = -2,     /*!< 14 Cortex-M4 Pend SV Interrupt                                    */
  SysTick_IRQn                = -1,     /*!< 15 Cortex-M4 System Tick Interrupt                                */
  /******  STM32 specific Interrupt Numbers **********************************************************************/
  WWDG_IRQn                   = 0,      /*!< Window WatchDog Interrupt                                         */
  PVD_IRQn                    = 1,      /*!< PVD through EXTI Line detection Interrupt                         */
  TAMP_STAMP_IRQn             = 2,      /*!< Tamper and TimeStamp interrupts through the EXTI line             */
  RTC_WKUP_IRQn               = 3,      /*!< RTC Wakeup interrupt through the EXTI line                        */
  FLASH_IRQn                  = 4,      /*!< FLASH global Interrupt                                            */
  RCC_IRQn                    = 5,      /*!< RCC global Interrupt                                              */
  EXTI0_IRQn                  = 6,      /*!< EXTI Line0 Interrupt                                              */
  EXTI1_IRQn                  = 7,      /*!< EXTI Line1 Interrupt                                              */
  EXTI2_IRQn                  = 8,      /*!< EXTI Line2 Interrupt                                              */
  EXTI3_IRQn                  = 9,      /*!< EXTI Line3 Interrupt                                              */
  EXTI4_IRQn                  = 10,     /*!< EXTI Line4 Interrupt                                              */
  DMA1_Stream0_IRQn           = 11,     /*!< DMA1 Stream 0 global Interrupt                                    */
  DMA1_Stream1_IRQn           = 12,     /*!< DMA1 Stream 1 global Interrupt                                    */
  DMA1_Stream2_IRQn           = 13,     /*!< DMA1 Stream 2 global Interrupt                                    */
  DMA1_Stream3_IRQn           = 14,     /*!< DMA1 Stream 3 global Interrupt                                    */
  DMA1_Stream4_IRQn           = 15,     /*!< DMA1 Stream 4 global Interrupt                                    */
  DMA1_Stream5_IRQn           = 16,     /*!< DMA1 Stream 5 global Interrupt                                    */
  DMA1_Stream6_IRQn           = 17,     /*!< DMA1 Stream 6 global Interrupt                                    */
  ADC_IRQn                    = 18,     /*!< ADC1, ADC2 and ADC3 global Interrupts                             */
  EXTI9_5_IRQn                = 23,     /*!< External Line[9:5] Interrupts                                     */
  TIM1_BRK_TIM9_IRQn          = 24,     /*!< TIM1 Break interrupt and TIM9 global interrupt                    */
  TIM1_UP_TIM10_IRQn          = 25,     /*!< TIM1 Update Interrupt and TIM10 global interrupt                  */
  TIM1_TRG_COM_TIM11_IRQn     = 26,     /*!< TIM1 Trigger and Commutation Interrupt and TIM11 global interrupt */
  TIM1_CC_IRQn                = 27,     /*!< TIM1 Capture Compare Interrupt                                    */
  TIM2_IRQn                   = 28,     /*!< TIM2 global Interrupt                                             */
  TIM3_IRQn                   = 29,     /*!< TIM3 global Interrupt                                             */
  TIM4_IRQn                   = 30,     /*!< TIM4 global Interrupt                                             */
  I2C1_EV_IRQn                = 31,     /*!< I2C1 Event Interrupt                                              */
  I2C1_ER_IRQn                = 32,     /*!< I2C1 Error Interrupt                                              */
  I2C2_EV_IRQn                = 33,     /*!< I2C2 Event Interrupt                                              */
  I2C2_ER_IRQn                = 34,     /*!< I2C2 Error Interrupt                                              */
  SPI1_IRQn                   = 35,     /*!< SPI1 global Interrupt                                             */
  SPI2_IRQn                   = 36,     /*!< SPI2 global Interrupt                                             */
  USART1_IRQn                 = 37,     /*!< USART1 global Interrupt                                           */
  USART2_IRQn                 = 38,     /*!< USART2 global Interrupt                                           */
  EXTI15_10_IRQn              = 40,     /*!< External Line[15:10] Interrupts                                   */
  RTC_Alarm_IRQn              = 41,     /*!< RTC Alarm (A and B) through EXTI Line Interrupt                   */
  OTG_FS_WKUP_IRQn            = 42,     /*!< USB OTG FS Wakeup through EXTI line interrupt                     */
  DMA1_Stream7_IRQn           = 47,     /*!< DMA1 Stream7 Interrupt                                            */
  SDIO_IRQn                   = 49,     /*!< SDIO global Interrupt                                             */
  TIM5_IRQn                   = 50,     /*!< TIM5 global Interrupt                                             */
  SPI3_IRQn                   = 51,     /*!< SPI3 global Interrupt                                             */
  DMA2_Stream0_IRQn           = 56,     /*!< DMA2 Stream 0 global Interrupt                                    */
  DMA2_Stream1_IRQn           = 57,     /*!< DMA2 Stream 1 global Interrupt                                    */
  DMA2_Stream2_IRQn           = 58,     /*!< DMA2 Stream 2 global Interrupt                                    */
  DMA2_Stream3_IRQn           = 59,     /*!< DMA2 Stream 3 global Interrupt                                    */
  DMA2_Stream4_IRQn           = 60,     /*!< DMA2 Stream 4 global Interrupt                                    */
  OTG_FS_IRQn                 = 67,     /*!< USB OTG FS global Interrupt                                       */
  DMA2_Stream5_IRQn           = 68,     /*!< DMA2 Stream 5 global interrupt                                    */
  DMA2_Stream6_IRQn           = 69,     /*!< DMA2 Stream 6 global interrupt                                    */
  DMA2_Stream7_IRQn           = 70,     /*!< DMA2 Stream 7 global interrupt                                    */
  USART6_IRQn                 = 71,     /*!< USART6 global interrupt                                           */
  I2C3_EV_IRQn                = 72,     /*!< I2C3 event interrupt                                              */
  I2C3_ER_IRQn                = 73,     /*!< I2C3 error interrupt                                              */
  FPU_IRQn                    = 81,     /*!< FPU global interrupt                                              */
  SPI4_IRQn                   = 84      /*!< SPI4 global Interrupt                                              */
} IRQn_t;

/**
 * @brief Interrupt Group Priority number of bits.
 */
typedef enum
{
	NVIC_PRIORITY_GROUP_4_BITS = 0UL,
	NVIC_PRIORITY_GROUP_3_BITS = 4UL,
	NVIC_PRIORITY_GROUP_2_BITS = 5UL,
	NVIC_PRIORITY_GROUP_1_BITS = 6UL,
	NVIC_PRIORITY_GROUP_0_BITS = 7UL
} NVIC_PriorityGroupBits_t;

/*---------------  Section: Function Declarations --------------- */

/**
  @brief   Enable Interrupt
  @details Enables a device specific interrupt in the NVIC interrupt controller.
  @param [in]      IRQn  Device specific interrupt number.
  @note    IRQn must not be negative.
 */
void NVIC_EnableIRQ(IRQn_t IRQn);
/**
  @brief   Disable Interrupt
  @details Disables a device specific interrupt in the NVIC interrupt controller.
  @param [in]      IRQn  Device specific interrupt number.
  @note    IRQn must not be negative.
 */
void NVIC_DisableIRQ(IRQn_t IRQn);
/**
  @brief   Get Interrupt Enable status
  @details Returns a device specific interrupt enable status from the NVIC interrupt controller.
  @param [in]      IRQn  Device specific interrupt number.
  @return             0  Interrupt is not enabled.
  @return             1  Interrupt is enabled.
  @note    IRQn must not be negative.
 */
uint32_t NVIC_GetEnableIRQ(IRQn_t IRQn);
/**
  @brief   Set Pending Interrupt
  @details Sets the pending bit of a device specific interrupt in the NVIC pending register.
  @param [in]      IRQn  Device specific interrupt number.
  @note    IRQn must not be negative.
 */
void NVIC_SetPending(IRQn_t IRQn);
/**
  @brief   Clear Pending Interrupt
  @details Clears the pending bit of a device specific interrupt in the NVIC pending register.
  @param [in]      IRQn  Device specific interrupt number.
  @note    IRQn must not be negative.
 */
void NVIC_ClearPending(IRQn_t IRQn);
/**
  @brief   Get Pending Interrupt
  @details Reads the NVIC pending register and returns the pending bit for the specified device specific interrupt.
  @param [in]      IRQn  Device specific interrupt number.
  @return             0  Interrupt status is not pending.
  @return             1  Interrupt status is pending.
  @note    IRQn must not be negative.
 */
uint32_t NVIC_GetPending(IRQn_t IRQn);
/**
  @brief   Get Active Interrupt
  @details Reads the active register in the NVIC and returns the active bit for the device specific interrupt.
  @param [in]      IRQn  Device specific interrupt number.
  @return             0  Interrupt status is not active.
  @return             1  Interrupt status is active.
  @note    IRQn must not be negative.
 */
uint32_t NVIC_GetActiveStatus(IRQn_t IRQn);
/**
  @brief   Set Priority Grouping
  @details Sets the priority grouping field using the required unlock sequence.
           The parameter PriorityGroup is assigned to the field SCB->AIRCR [10:8] PRIGROUP field.
           Only values from 0..7 are used.
           In case of a conflict between priority grouping and available
           priority bits (__NVIC_PRIO_BITS), the smallest possible priority group is set.
  @param [in]      PriorityGroup  Priority grouping field.
 */
void NVIC_SetPriorityGrouping(uint32_t PriorityGroup);
/**
  @brief   Set Interrupt Priority
  @details Sets the priority of a device specific interrupt or a processor exception.
           The interrupt number can be positive to specify a device specific interrupt,
           or negative to specify a processor exception.
  @param [in]      IRQn  Interrupt number.
  @param [in]  priority  Priority to set.
  @note    The priority cannot be set for every processor exception.
 */
void NVIC_SetPriority(IRQn_t IRQn, uint32_t Priority);
/**
  @brief   Get Interrupt Priority
  @details Reads the priority of a device specific interrupt or a processor exception.
           The interrupt number can be positive to specify a device specific interrupt,
           or negative to specify a processor exception.
  @param [in]   IRQn  Interrupt number.
  @return             Interrupt Priority.
                      Value is aligned automatically to the implemented priority bits of the microcontroller.
 */
uint32_t NVIC_GetPriority(IRQn_t IRQn);


#endif /* CORTEXM4_NVIC_NVIC_H_ */
