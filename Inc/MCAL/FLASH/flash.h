/**
 ******************************************************************************
 * @file           : flash.h
 * @author         : Mostafa Asaad (https://github.com/M0stafa077)
 * @brief          : Flash Device-Driver Header Interface File.
 ******************************************************************************
 */

#ifndef MCAL_FLASH_FLASH_H_
#define MCAL_FLASH_FLASH_H_

/* --------------- Section : Includes --------------- */
#include "Common/Std_Types.h"
#include "Common/stm32f401_registers.h"
/* --------------- Section: Macro Declarations --------------- */

#define FLASH_CR_KEY_1				(0x45670123UL)
#define FLASH_CR_KEY_2				(0xCDEF89ABUL)

#define FLASH_OB_KEY_1				(0x08192A3BUL)
#define FLASH_OB_KEY_2				(0x4C5D6E7FUL)

/* --------------- Section: Macro Functions Declarations --------------- */

#define FLASH_WAIT_FOR_COMPLETION()	while(READ_BIT(FLASH->SR, 16))

#define FLASH_START_OPERATION()		(SET_BIT(FLASH->CR, 16))

/* --------------- Section: Data Type Declarations --------------- */

/*
 * @brief 	The sector numbers in the STM32F401RC
 */
typedef enum
{
	FLASH_SECTOR_0 = 0,
	FLASH_SECTOR_1,
	FLASH_SECTOR_2,
	FLASH_SECTOR_3,
	FLASH_SECTOR_4,
	FLASH_SECTOR_5
} Flash_Sector_t;

/*
 * @brief 	The read protection levels for Flash Memory
 */
typedef enum
{
	FLASH_READ_PROTECT_LEV0,
	FLASH_READ_PROTECT_LEV1,
	FLASH_READ_PROTECT_LEV2
} Flash_ReadProtectionLev_t;


/*---------------  Section: Function Declarations --------------- */
Std_ReturnType_t Flash_Erase_Sector(const Flash_Sector_t Sector);

Std_ReturnType_t Flash_Erase_Mass(void);

Std_ReturnType_t Flash_Program(uint32_t address, uint32_t data);

Std_ReturnType_t Flash_SetReadProtection(const Flash_ReadProtectionLev_t Protection_Level);

Std_ReturnType_t Flash_SetWriteProtection(const Flash_Sector_t Sector);


#endif /* MCAL_FLASH_FLASH_H_ */
