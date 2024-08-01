/**
 ******************************************************************************
 * @file           : flash.c
 * @author         : Mostafa Asaad (https://github.com/M0stafa077)
 * @brief          : Flash Device-Driver Static Code Implementation.
 ******************************************************************************
 */
/* --------------- Section : Includes --------------- */
#include "MCAL/FLASH/flash.h"
/*---------------  Section: Helper Function Declarations --------------- */
static Std_ReturnType_t Flash_Unlock();
static Std_ReturnType_t Flash_Lock();
static Std_ReturnType_t OptionBytes_Unlock();
static Std_ReturnType_t OptionBytes_Lock();
/*---------------  Section: Function Definitions --------------- */

/**
 * @brief  Erases a specific sector of FLASH memory.
 * @param  Sector: The sector to be erased.
 *         This parameter should be of type `Flash_Sector_t` and
 *         indicate the specific FLASH sector to erase.
 * @retval Std_ReturnType_t: Status of the operation.
 *         - E_OK: Operation completed successfully
 *         - E_NOT_OK: Operation failed
 */
Std_ReturnType_t Flash_Erase_Sector(const Flash_Sector_t Sector)
{
	Std_ReturnType_t retVal = E_OK;

	if((uint32_t)Sector > (uint32_t)FLASH_SECTOR_5)
		{ retVal |= E_NOT_OK; }
	else
	{
		/* 1. Wait for the Flash Memory to be free */
		FLASH_WAIT_FOR_COMPLETION();

		/* 2. Unlock the Control register */
		retVal |= Flash_Unlock();

		/* 3. Set the SER bit */
		FLASH->CR |= (1UL << 1);

		/* 4. Select the Sector to be erased */
		FLASH->CR |= (uint32_t) (((uint32_t)Sector & 0x0000000F) << 3);

		/* 5. Start the erase operation */
		FLASH_START_OPERATION();

		/* 6. Wait for the Flash to complete the operation */
		FLASH_WAIT_FOR_COMPLETION();

		/* 7. Lock the Control register */
		retVal |= Flash_Lock();
	}
	return retVal;
}
/**
 * @brief  Erases all sectors of FLASH memory (mass erase).
 * @retval Std_ReturnType_t: Status of the operation.
 *         - E_OK: Operation completed successfully
 *         - E_NOT_OK: Operation failed
 */
Std_ReturnType_t Flash_Erase_Mass(void)
{
	Std_ReturnType_t retVAl = E_OK;

	/* 1. Wait for the Flash Memory to be free */
	FLASH_WAIT_FOR_COMPLETION();

	/* 2. Unlock the Control register */
	retVAl |= Flash_Unlock();

	/* 3. Set the MER bit */
	FLASH->CR |= (1UL << 2);

	/* 5. Start the erase operation */
	FLASH_START_OPERATION();

	/* 6. Wait for the Flash to complete the operation */
	FLASH_WAIT_FOR_COMPLETION();

	/* 7. Lock the Control register */
	retVAl |= Flash_Lock();

	return retVAl;
}
/**
 * @brief  Programs a word (32-bit) at a specified address in the FLASH memory.
 * @param  address: Address in FLASH memory where the data should be written.
 *         This parameter must be a multiple of 4 bytes (word-aligned).
 * @param  data: Data to be programmed at the specified address.
 * @retval Std_ReturnType_t: Status of the operation.
 *         - E_OK: Operation completed successfully
 *         - E_NOT_OK: Operation failed (e.g., address not aligned, programming error)
 */
Std_ReturnType_t Flash_Program(uint32_t address, uint32_t data)
{
	Std_ReturnType_t retVal = E_OK;

	if(address % 4 != 0)
	{
		retVal |= E_NOT_OK;	/* Address must be aligned to 4 bytes */
	}
	else
	{
		/* 1. Wait for the Flash Memory to be free */
		FLASH_WAIT_FOR_COMPLETION();

		/* 2. Unlock the Control register */
		retVal |= Flash_Unlock();
		if(E_NOT_OK == retVal)
			{ return E_NOT_OK; }

		/* 3. Set the parallelism size */
		FLASH->CR |= (uint32_t)((FLASH_PARALLELISM_32 & 0x3UL) << FLASH_PSIIZE_POS);

		/* 4. Set the PG bit */
		FLASH->CR |= (1UL);

		/* 5. Start writing the data */
		*((volatile uint32_t *)(address)) = data;

		/* 6. Wait for the Flash Memory to be free */
		FLASH_WAIT_FOR_COMPLETION();

		/* 7. Check for errors */
		if(FLASH_FLAG_PGAERR || FLASH_FLAG_PGPERR || FLASH_FLAG_PGSERR)
			{ retVal |= E_NOT_OK; }

		/* 8. Lock the Control register */
		retVal |= Flash_Lock();
	}

	return retVal;
}
/**
 * @brief  Sets the read protection level of the FLASH memory.
 * @param  Protection_Level: Level of read protection to be applied.
 *         This parameter should be of type `Flash_ReadProtectionLev_t` and indicate the desired read protection level.
 * @retval Std_ReturnType_t: Status of the operation.
 *         - E_OK: Operation completed successfully
 *         - E_NOT_OK: Operation failed
 */
Std_ReturnType_t Flash_SetReadProtection(const Flash_ReadProtectionLev_t Protection_Level)
{
	Std_ReturnType_t retVal = E_OK;
	if((uint8_t)Protection_Level > (uint8_t)FLASH_READ_PROTECT_LEV2)
	{
		retVal |= E_NOT_OK;
	}
	else
	{
		/* 1. Wait for the Flash Memory to be free */
		FLASH_WAIT_FOR_COMPLETION();

		/* 2. Unlock the Control register */
		retVal |= OptionBytes_Unlock();
		if(E_NOT_OK == retVal)
		{
			return E_NOT_OK;
		}

		/* 3. Write the level in the OPTCR */
		switch(Protection_Level)
		{
			case FLASH_READ_PROTECT_LEV0:
				FLASH->OPTCR |= (uint32_t)(0xAAUL << 8);
				break;
			case FLASH_READ_PROTECT_LEV1:
				FLASH->OPTCR |= (uint32_t)(0xBBUL << 8);
				break;
			case FLASH_READ_PROTECT_LEV2:
				/* Never Enter Level 2 ') */
				break;
			default:
				retVal |= E_NOT_OK;
				break;
		}

		/* 4. Start the operation */
		FLASH_OB_START_OPERATION();

		/* 5. Wait for the Flash Memory to be free */
		FLASH_WAIT_FOR_COMPLETION();

		/* 6. Lock the OPTCR again */
		retVal |= OptionBytes_Lock();
	}
	return retVal;
}
/**
 * @brief  Sets the write protection for a specific sector of FLASH memory.
 * @param  Sector: The sector to be write-protected.
 *         This parameter should be of type `Flash_Sector_t` and indicate the specific FLASH sector to protect.
 * @retval Std_ReturnType_t: Status of the operation.
 *         - E_OK: Operation completed successfully
 *         - E_NOT_OK: Operation failed
 */
Std_ReturnType_t Flash_SetWriteProtection(const Flash_Sector_t Sector)
{
	Std_ReturnType_t retVal = E_OK;
	if(FLASH_SECTOR_5 < Sector)
	{
		retVal |= E_NOT_OK;
	}
	else
	{
		/* 1. Wait for the Flash Memory to be free */
		FLASH_WAIT_FOR_COMPLETION();

		/* 2. Unlock the Control register */
		retVal |= OptionBytes_Unlock();
		if(E_NOT_OK == retVal)
		{
			return E_NOT_OK;
		}

		/* 3. Write the level of protection */
		CLEAR_BIT(FLASH->OPTCR, (uint8_t)Sector);

		/* 4. Start the operation */
		FLASH_OB_START_OPERATION();

		/* 5. Wait for the Flash Memory to be free */
		FLASH_WAIT_FOR_COMPLETION();

		/* 6. Lock the OPTCR again */
		retVal |= OptionBytes_Lock();
	}
	return retVal;
}
/*---------------  Section: Helper Function Definitions --------------- */
static Std_ReturnType_t Flash_Unlock()
{
	if(!READ_BIT(FLASH->CR, 31))
	{
		// Control register is already unlocked
		return E_OK;
	}
	// Unlock the Control Register
	FLASH->KEYR = FLASH_CR_KEY_1;
	FLASH->KEYR = FLASH_CR_KEY_2;

	// Return the status
	return (READ_BIT(FLASH->CR, 31) ? E_NOT_OK : E_OK);
}
static Std_ReturnType_t Flash_Lock()
{
	// Set the LOCK bit
	SET_BIT(FLASH->CR, 31);
	// Return the status
	return (READ_BIT(FLASH->CR, 31) ? E_OK : E_NOT_OK);
}

static Std_ReturnType_t OptionBytes_Unlock()
{
	if(!READ_BIT(FLASH->OPTCR, 0))
	{
		// Control register is already unlocked
		return E_OK;
	}
	// Unlock the Control Register
	FLASH->OPTKEYR = FLASH_OB_KEY_1;
	FLASH->OPTKEYR = FLASH_OB_KEY_2;

	// Return the status
	return (READ_BIT(FLASH->OPTCR, 0) ? E_NOT_OK : E_OK);
}

static Std_ReturnType_t OptionBytes_Lock()
{
	// Set the LOCK bit
	SET_BIT(FLASH->OPTCR, 0);
	// Return the status
	return (READ_BIT(FLASH->OPTCR, 0) ? E_OK : E_NOT_OK);
}




