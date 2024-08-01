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

#define FLASH_PARALLELISM_32		(0x00000002UL)
#define FLASH_PSIIZE_POS			(0x08UL)

/* !< Operation error  */
#define FLASH_OPERR_POS				(1UL)
#define FLASH_FLAG_OPERR			(READ_BIT(FLASH->SR, FLASH_OPERR_POS))
/* !< Write protection error */
#define FLASH_WRPERR_POS			(4UL)
#define FLASH_FLAG_WRPERR			(READ_BIT(FLASH->SR, FLASH_WRPERR_POS))
/* !< Programming alignment error */
#define FLASH_PGAERR_POS			(5UL)
#define FLASH_FLAG_PGAERR			(READ_BIT(FLASH->SR, FLASH_PGAERR_POS))
/* !< Programming parallelism error */
#define FLASH_PGPERR_POS			(6UL)
#define FLASH_FLAG_PGPERR			(READ_BIT(FLASH->SR, FLASH_PGPERR_POS))
/* !< Programming sequence error */
#define FLASH_PGSERR_POS			(7UL)
#define FLASH_FLAG_PGSERR			(READ_BIT(FLASH->SR, FLASH_PGSERR_POS))
/* !< Read Protection Error */
#define FLASH_RDERR_POS				(8UL)
#define FLASH_FLAG_RDERR			(READ_BIT(FLASH->SR, FLASH_RDERR_POS))

/* --------------- Section: Macro Functions Declarations --------------- */

#define FLASH_WAIT_FOR_COMPLETION()	while(READ_BIT(FLASH->SR, 16))

#define FLASH_START_OPERATION()		(SET_BIT(FLASH->CR, 16))

#define FLASH_OB_START_OPERATION()	(SET_BIT(FLASH->OPTCR, 1))

/* --------------- Section: Data Type Declarations --------------- */

/*
 * @brief 	The sector numbers in the STM32F401RC
 */
typedef enum
{
	FLASH_SECTOR_0 = 16,
	FLASH_SECTOR_1 = 17,
	FLASH_SECTOR_2 = 18,
	FLASH_SECTOR_3 = 19,
	FLASH_SECTOR_4 = 20,
	FLASH_SECTOR_5 = 21
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

/**
 * @brief  Erases a specific sector of FLASH memory.
 * @param  Sector: The sector to be erased.
 *         This parameter should be of type `Flash_Sector_t` and
 *         indicate the specific FLASH sector to erase.
 * @retval Std_ReturnType_t: Status of the operation.
 *         - E_OK: Operation completed successfully
 *         - E_NOT_OK: Operation failed
 */
Std_ReturnType_t Flash_Erase_Sector(const Flash_Sector_t Sector);
/**
 * @brief  Erases all sectors of FLASH memory (mass erase).
 * @retval Std_ReturnType_t: Status of the operation.
 *         - E_OK: Operation completed successfully
 *         - E_NOT_OK: Operation failed
 */
Std_ReturnType_t Flash_Erase_Mass(void);
/**
 * @brief  Programs a word (32-bit) at a specified address in the FLASH memory.
 * @param  address: Address in FLASH memory where the data should be written.
 *         This parameter must be a multiple of 4 bytes (word-aligned).
 * @param  data: Data to be programmed at the specified address.
 * @retval Std_ReturnType_t: Status of the operation.
 *         - E_OK: Operation completed successfully
 *         - E_NOT_OK: Operation failed (e.g., address not aligned, programming error)
 */
Std_ReturnType_t Flash_Program(uint32_t address, uint32_t data);
/**
 * @brief  Sets the read protection level of the FLASH memory.
 * @param  Protection_Level: Level of read protection to be applied.
 *         This parameter should be of type `Flash_ReadProtectionLev_t` and indicate the desired read protection level.
 * @retval Std_ReturnType_t: Status of the operation.
 *         - E_OK: Operation completed successfully
 *         - E_NOT_OK: Operation failed
 */
Std_ReturnType_t Flash_SetReadProtection(const Flash_ReadProtectionLev_t Protection_Level);
/**
 * @brief  Sets the write protection for a specific sector of FLASH memory.
 * @param  Sector: The sector to be write-protected.
 *         This parameter should be of type `Flash_Sector_t` and indicate the specific FLASH sector to protect.
 * @retval Std_ReturnType_t: Status of the operation.
 *         - E_OK: Operation completed successfully
 *         - E_NOT_OK: Operation failed
 */
Std_ReturnType_t Flash_SetWriteProtection(const Flash_Sector_t Sector);

#endif /* MCAL_FLASH_FLASH_H_ */
