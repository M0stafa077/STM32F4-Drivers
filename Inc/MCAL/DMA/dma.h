/**
 ******************************************************************************
 * @file           : dma.h
 * @author         : Mostafa Asaad (https://github.com/M0stafa077)
 * @brief          : DMA Device-Driver Header Interface File.
 ******************************************************************************
 */

#ifndef MCAL_DMA_DMA_H_
#define MCAL_DMA_DMA_H_

/* --------------- Section : Includes --------------- */
#include "Common/Std_Types.h"
#include "Common/stm32f401_registers.h"
/* --------------- Section: Macro Declarations --------------- */

/** @defgroup DMA_Peripheral_incremented_mode DMA Peripheral incremented mode
  * @brief    DMA peripheral incremented mode
  */
#define DMA_PINC_ENABLE						(0x00000000UL)
#define DMA_PINC_DISABLE					(0x00000001UL)

/** @defgroup DMA_Memory_incremented_mode DMA Memory incremented mode
  * @brief    DMA Memoryincremented mode
  */
#define DMA_MINC_ENABLE						(0x00000001UL)
#define DMA_MINC_DISABLE					(0x00000000UL)

/** @defgroup DMA_Peripheral_data_size DMA Peripheral data size
  * @brief    DMA peripheral data size
  */
#define DMA_PDATAALIGN_BYTE         		(0x00000000UL)
#define DMA_PDATAALIGN_HALFWORD     		(0x00000001UL)
#define DMA_PDATAALIGN_WORD         		(0x00000002UL)
/** @defgroup DMA_Memory_data_size DMA Memory data size
  * @brief    DMA memory data size
  */
#define DMA_MDATAALIGN_BYTE         		(0x00000000UL)
#define DMA_MDATAALIGN_HALFWORD     		(0x00000001UL)
#define DMA_MDATAALIGN_WORD       			(0x00000002UL)

/** @defgroup DMA_mode DMA mode
  * @brief    DMA mode
  */
#define DMA_NORMAL                  		(0x00000000UL)
#define DMA_CIRCULAR                		(0x00000001UL)
#define DMA_PFCTRL             				(0x00000002UL)

/** @defgroup DMA_FIFO_direct_mode DMA FIFO direct mode
  * @brief    DMA FIFO direct mode
  */
#define DMA_FIFOMODE_DISABLE        		(0x00000000UL)
#define DMA_FIFOMODE_ENABLE					(0x00000001UL)

/** @defgroup DMA_FIFO_threshold_level DMA FIFO threshold level
  * @brief    DMA FIFO level
  */
#define DMA_FIFO_THRESHOLD_1QUARTERFULL     (0x00000000U)
#define DMA_FIFO_THRESHOLD_HALFFULL         (0x00000001UL)
#define DMA_FIFO_THRESHOLD_3QUARTERSFULL   	(0x00000002UL)
#define DMA_FIFO_THRESHOLD_FULL         	(0x00000003UL)

/** @defgroup DMA_Memory_burst DMA Memory burst
  * @brief    DMA memory burst
  * @{
  */
#define DMA_MBURST_SINGLE             		(0x00000000UL)
#define DMA_MBURST_INC4               		(0x00000001UL)
#define DMA_MBURST_INC8               		(0x00000002UL)
#define DMA_MBURST_INC16              		(0x00000003UL)
/** @defgroup DMA_Peripheral_burst DMA Peripheral burst
  * @brief    DMA peripheral burst
  * @{
  */
#define DMA_PBURST_SINGLE             		(0x00000000UL)
#define DMA_PBURST_INC4               		(0x00000001UL)
#define DMA_PBURST_INC8              		(0x00000002UL)
#define DMA_PBURST_INC16              		(0x00000003UL)

#define DMA_SxCR_RESET_VALUE 				(0x00000000UL)
#define DMA_SxFCR_RESET_VALUE 				(0x00000021UL)
#define DMA_SxM0AR_RESET_VALUE 				(0x00000000UL)
#define DMA_SxNDTR_RESET_VALUE 				(0x00000000UL)
#define DMA_SxPAR_RESET_VALUE 				(0x00000000UL)
#define DMA_SxM1AR_RESET_VALUE 				(0x00000000UL)

/* --------------- Section: Macro Functions Declarations --------------- */


/* --------------- Section: Data Type Declarations --------------- */

/**
 * @brief 	DMA_Channel_selection
 */
typedef enum
{
	DMA_CHANNEL_0,
	DMA_CHANNEL_1,
	DMA_CHANNEL_2,
	DMA_CHANNEL_3,
	DMA_CHANNEL_4,
	DMA_CHANNEL_5,
	DMA_CHANNEL_6,
	DMA_CHANNEL_7,
} DMA_Channel_t;

/**
 * @brief 	DMA_Data_transfer_direction
 */
typedef enum
{
	DMA_PREPH_TO_MEMORY = 0,
	DMA_MEMORY_TO_PREPH,
	DMA_MEMORY_TO_MEMORY
} DMA_Transfer_Direction_t;
/*
 * @brief DMA_Priority_level
 */
typedef enum
{
	DMA_PRIORITY_LOW,
	DMA_PRIORITY_MEDIUM,
	DMA_PRIORITY_HIGH,
	DMA_PRIORITY_VERY_HIGH
} DMA_Priority_t;

/**
  * @brief  DMA Configuration Structure definition
  */
typedef struct
{
	DMA_Channel_t Channel;       	/*!< Specifies the channel used for the specified stream.
                                      This parameter can be a value of @ref DMA_Channel_selection                    */

	DMA_Transfer_Direction_t Direction;	/*!< Specifies if the data will be transferred from memory to peripheral,
                                      from memory to memory or from peripheral to memory.
                                      This parameter can be a value of @ref DMA_Data_transfer_direction              */

	uint32_t PeriphInc;            	/*!< Specifies whether the Peripheral address register should be incremented or not.
                                      This parameter can be a value of @ref DMA_Peripheral_incremented_mode          */

	uint32_t MemInc;               	/*!< Specifies whether the memory address register should be incremented or not.
                                      This parameter can be a value of @ref DMA_Memory_incremented_mode              */

	uint32_t PeriphDataAlignment;  	/*!< Specifies the Peripheral data width.
                                      This parameter can be a value of @ref DMA_Peripheral_data_size                 */

	uint32_t MemDataAlignment;     	/*!< Specifies the Memory data width.
                                      This parameter can be a value of @ref DMA_Memory_data_size                     */

	uint32_t Mode;                 	/*!< Specifies the operation mode of the DMAy Streamx.
                                      This parameter can be a value of @ref DMA_mode
                                      @note The circular buffer mode cannot be used if the memory-to-memory
                                            data transfer is configured on the selected Stream                        */

	DMA_Priority_t Priority;		/*!< Specifies the software priority for the DMAy Streamx.
                                      This parameter can be a value of @ref DMA_Priority_level                       */

	uint32_t FIFOMode;             	/*!< Specifies if the FIFO mode or Direct mode will be used for the specified stream.
                                      This parameter can be a value of @ref DMA_FIFO_direct_mode
                                      @note The Direct mode (FIFO mode disabled) cannot be used if the
                                            memory-to-memory data transfer is configured on the selected stream       */

	uint32_t FIFOThreshold;        	/*!< Specifies the FIFO threshold level.
                                      This parameter can be a value of @ref DMA_FIFO_threshold_level                  */

	uint32_t MemBurst;             	/*!< Specifies the Burst transfer configuration for the memory transfers.
                                      It specifies the amount of data to be transferred in a single non interruptible
                                      transaction.
                                      This parameter can be a value of @ref DMA_Memory_burst
                                      @note The burst mode is possible only if the address Increment mode is enabled. */

	uint32_t PeriphBurst;          	/*!< Specifies the Burst transfer configuration for the peripheral transfers.
                                      It specifies the amount of data to be transferred in a single non interruptible
                                      transaction.
                                      This parameter can be a value of @ref DMA_Peripheral_burst
                                      @note The burst mode is possible only if the address Increment mode is enabled. */
	Interrupt_Handler_t DMA_DefaultHandler;
} DMA_InitTypeDef;

typedef struct
{
	uint32_t Peripheral_Address;
	uint32_t Memory_Address;
	uint16_t No_Of_Items;
	uint8_t Stream_Idx;
} DMA_Stream_InitCfgs_t;
/*---------------  Section: Function Declarations --------------- */

/**
 * @brief  Initializes the DMA stream with specified configurations.
 *
 * @param  dma_cfgs  Pointer to the DMA initialization structure
 * 		containing the configuration information.
 * @param  StreamCfgs Pointer to the DMA stream initialization
 * 		structure containing the peripheral and memory addresses,
 * 		number of items to transfer, and stream index.
 *
 * @retval Std_ReturnType_t Returns E_OK if initialization is successful, otherwise E_NOT_OK.
 *
 * This function configures the specified DMA stream with
 * the provided parameters. It ensures that the stream is disabled
 * before configuring, enables the DMA clock, and sets the necessary
 * parameters such as peripheral and memory addresses, number
 * of data items to transfer, priority level,
 * increment modes, transfer direction, channel, FIFO mode,
 * and FIFO threshold. Finally, it enables
 * the DMA stream.
 */
Std_ReturnType_t DMA1_Init(const DMA_InitTypeDef * dma_cfgs, const DMA_Stream_InitCfgs_t * StreamCfgs);
/**
 * @brief  DeInitializes the DMA stream with specified configurations.
 *
 * @param  dma_cfgs  Pointer to the DMA initialization structure
 * 		containing the configuration information.
 * @param  StreamCfgs Pointer to the DMA stream initialization
 * 		structure containing the peripheral and memory addresses,
 * 		number of items to transfer, and stream index.
 *
 * @retval Std_ReturnType_t Returns E_OK if initialization is successful,
 * 			otherwise E_NOT_OK.
 *
 * This function resets all the DMA Controller registers to their
 * reset value.
 */
Std_ReturnType_t DMA1_DeInit(const DMA_InitTypeDef * dma_cfgs, const DMA_Stream_InitCfgs_t * StreamCfgs);

/**
 * @brief  Initializes the DMA stream with specified configurations.
 *
 * @param  dma_cfgs  Pointer to the DMA initialization structure
 * 		containing the configuration information.
 * @param  StreamCfgs Pointer to the DMA stream initialization
 * 		structure containing the peripheral and memory addresses,
 * 		number of items to transfer, and stream index.
 *
 * @retval Std_ReturnType_t Returns E_OK if initialization is successful, otherwise E_NOT_OK.
 *
 * This function configures the specified DMA stream with
 * the provided parameters. It ensures that the stream is disabled
 * before configuring, enables the DMA clock, and sets the necessary
 * parameters such as peripheral and memory addresses, number
 * of data items to transfer, priority level,
 * increment modes, transfer direction, channel, FIFO mode,
 * and FIFO threshold. Finally, it enables
 * the DMA stream.
 */
Std_ReturnType_t DMA2_Init(const DMA_InitTypeDef * dma_cfgs, const DMA_Stream_InitCfgs_t * StreamCfgs);
/**
 * @brief  DeInitializes the DMA stream with specified configurations.
 *
 * @param  dma_cfgs  Pointer to the DMA initialization structure
 * 		containing the configuration information.
 * @param  StreamCfgs Pointer to the DMA stream initialization
 * 		structure containing the peripheral and memory addresses,
 * 		number of items to transfer, and stream index.
 *
 * @retval Std_ReturnType_t Returns E_OK if initialization is successful,
 * 			otherwise E_NOT_OK.
 *
 * This function resets all the DMA Controller registers to their
 * reset value.
 */
Std_ReturnType_t DMA2_DeInit(const DMA_InitTypeDef * dma_cfgs, const DMA_Stream_InitCfgs_t * StreamCfgs);


#endif /* MCAL_DMA_DMA_H_ */
