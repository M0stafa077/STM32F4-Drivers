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
	}
	return retVal;
}

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

	return retVAl;
}

Std_ReturnType_t Flash_Program(uint32_t address, uint32_t data);

Std_ReturnType_t Flash_SetReadProtection(const Flash_ReadProtectionLev_t Protection_Level);

Std_ReturnType_t Flash_SetWriteProtection(const Flash_Sector_t Sector);




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




