/**
 ******************************************************************************
 * @file           : dma.c
 * @author         : Mostafa Asaad (https://github.com/M0stafa077)
 * @brief          : DMA Device-Driver Static Code Implementation
 ******************************************************************************
 */
/* --------------- Section : Includes --------------- */
#include "MCAL/DMA/dma.h"
/*---------------  Section: Staatic Global Variables --------------- */

static Interrupt_Handler_t DMA1_Streams_DefaultInterruptHandlers[8];
static Interrupt_Handler_t DMA2_Streams_DefaultInterruptHandlers[8];


/*---------------  Section: Function Definitions --------------- */
Std_ReturnType_t DMA1_Init(const DMA_InitTypeDef * dma_cfgs, const DMA_Stream_InitCfgs_t * StreamCfgs)
{
	Std_ReturnType_t retVal = E_OK;
	if((NULL == StreamCfgs) || (NULL == dma_cfgs) || (StreamCfgs->Stream_Idx >= 8))
	{
		retVal = E_NOT_OK;
	}
	else
	{
		/* 1. Disable the DMA Stream */
		CLEAR_BIT(DMA1->Streams[StreamCfgs->Stream_Idx].CR, 0);
		DMA1->Streams[StreamCfgs->Stream_Idx].CR = DMA_SxCR_RESET_VALUE;
		/* 2. Enable the DMA Clock */
		RCC->AHB1ENR |= (1UL << 21);
		/* 3. Peripheral address */
		DMA1->Streams[StreamCfgs->Stream_Idx].PAR = StreamCfgs->Peripheral_Address;
		/* 4. Memory address */
		DMA1->Streams[StreamCfgs->Stream_Idx].M0AR = StreamCfgs->Memory_Address;
		/* 5. Number of data items to transfer */
		DMA1->Streams[StreamCfgs->Stream_Idx].NDTR = (uint16_t)(StreamCfgs->No_Of_Items);
		/* 6. Priority level */
		DMA1->Streams[StreamCfgs->Stream_Idx].CR |= (((dma_cfgs->Priority) & (3UL)) << (16UL));
		/* 7. Memory & Peripherla Incremant Mode */
		if(dma_cfgs->MemInc == DMA_MINC_ENABLE)
			{ DMA1->Streams[StreamCfgs->Stream_Idx].CR |= (1UL << 10); }
		else if(dma_cfgs->MemInc == DMA_MINC_DISABLE)
			{ DMA1->Streams[StreamCfgs->Stream_Idx].CR &= ~(1UL << 10); }
		if(dma_cfgs->PeriphInc == DMA_PINC_ENABLE)
			{ DMA1->Streams[StreamCfgs->Stream_Idx].CR |= (1UL << 9); }
		else if(dma_cfgs->PeriphInc == DMA_PINC_DISABLE)
			{ DMA1->Streams[StreamCfgs->Stream_Idx].CR &= ~(1UL << 9); }
		/* 8. Transfer Complete Interrupt Enable */
		DMA1->Streams[StreamCfgs->Stream_Idx].CR |= (1UL << 4UL);
		/* 9. Configure transfer direction */
		DMA1->Streams[StreamCfgs->Stream_Idx].CR |= (((uint32_t)(dma_cfgs->Direction) & (3UL)) << 6);
		/* 10. Select the channel */
		DMA1->Streams[StreamCfgs->Stream_Idx].CR |= ((uint32_t)((dma_cfgs->Channel) & (7UL)) << 25);
		/* 11. Configure the FIFO Mode */
		// Reset the FIFO Control Register First
		DMA1->Streams[StreamCfgs->Stream_Idx].FCR = DMA_SxFCR_RESET_VALUE;
		switch(dma_cfgs->FIFOMode)
		{
			case DMA_FIFOMODE_ENABLE: SET_BIT(DMA1->Streams[StreamCfgs->Stream_Idx].FCR, 2);
								break;	/* !< FIFO Mode */
			case DMA_FIFOMODE_DISABLE: CLEAR_BIT(DMA1->Streams[StreamCfgs->Stream_Idx].FCR, 2);
								break;	/* !< Direct Mode */
			default: retVal |= E_NOT_OK;
		}
		/* 12. Configure the FIFO Threshold value */
		DMA1->Streams[StreamCfgs->Stream_Idx].FCR &= ~(3UL);
		DMA1->Streams[StreamCfgs->Stream_Idx].FCR |= (uint32_t)(dma_cfgs->FIFOThreshold & 3UL);
		/* 13. Assign the Interrupt Handler */
		DMA1_Streams_DefaultInterruptHandlers[StreamCfgs->Stream_Idx] = dma_cfgs->DMA_DefaultHandler;
		/* 13. Enable the Transfer Complete Interrupt */
		SET_BIT(DMA1->Streams[StreamCfgs->Stream_Idx].CR, 4);
		/* 14. Enable the Stream */
		DMA1->Streams[StreamCfgs->Stream_Idx].CR |= (1UL);
	}
	return retVal;
}

Std_ReturnType_t DMA1_DeInit(const DMA_InitTypeDef * dma_cfgs, const DMA_Stream_InitCfgs_t * StreamCfgs)
{
	Std_ReturnType_t retVal = E_OK;
	if((NULL == StreamCfgs) || (NULL == dma_cfgs) || (StreamCfgs->Stream_Idx >= 8))
	{
		retVal = E_NOT_OK;
	}
	else
	{
		/* 1. Disable the DMA Stream */
		CLEAR_BIT(DMA1->Streams[StreamCfgs->Stream_Idx].CR, 0);
		/* 2. Reset all the Register for the DMA */
		DMA1->Streams[StreamCfgs->Stream_Idx].CR = DMA_SxCR_RESET_VALUE;
		DMA1->Streams[StreamCfgs->Stream_Idx].FCR = DMA_SxFCR_RESET_VALUE;
		DMA1->Streams[StreamCfgs->Stream_Idx].M0AR = DMA_SxM0AR_RESET_VALUE;
		DMA1->Streams[StreamCfgs->Stream_Idx].M1AR = DMA_SxM1AR_RESET_VALUE;
		DMA1->Streams[StreamCfgs->Stream_Idx].NDTR = DMA_SxNDTR_RESET_VALUE;
		DMA1->Streams[StreamCfgs->Stream_Idx].PAR = DMA_SxPAR_RESET_VALUE;
	}
	return retVal;
}

Std_ReturnType_t DMA2_Init(const DMA_InitTypeDef * dma_cfgs, const DMA_Stream_InitCfgs_t * StreamCfgs)
{
	Std_ReturnType_t retVal = E_OK;
	if((NULL == StreamCfgs) || (NULL == dma_cfgs) || (StreamCfgs->Stream_Idx >= 8))
	{
		retVal = E_NOT_OK;
	}
	else
	{
		/* 1. Disable the DMA Stream */
		CLEAR_BIT(DMA2->Streams[StreamCfgs->Stream_Idx].CR, 0);
		DMA2->Streams[StreamCfgs->Stream_Idx].CR = DMA_SxCR_RESET_VALUE;
		/* 2. Enable the DMA Clock */
		RCC->AHB1ENR |= (1UL << 22);
		/* 3. Peripheral address */
		DMA2->Streams[StreamCfgs->Stream_Idx].PAR = StreamCfgs->Peripheral_Address;
		/* 4. Memory address */
		DMA2->Streams[StreamCfgs->Stream_Idx].M0AR = StreamCfgs->Memory_Address;
		/* 5. Number of data items to transfer */
		DMA2->Streams[StreamCfgs->Stream_Idx].NDTR = (uint16_t)(StreamCfgs->No_Of_Items);
		/* 6. Priority level */
		DMA2->Streams[StreamCfgs->Stream_Idx].CR |= (((dma_cfgs->Priority) & (3UL)) << (16UL));
		/* 7. Memory & Peripherla Incremant Mode */
		if(dma_cfgs->MemInc == DMA_MINC_ENABLE)
			{ DMA2->Streams[StreamCfgs->Stream_Idx].CR |= (1UL << 10); }
		else if(dma_cfgs->MemInc == DMA_MINC_DISABLE)
			{ DMA2->Streams[StreamCfgs->Stream_Idx].CR &= ~(1UL << 10); }
		if(dma_cfgs->PeriphInc == DMA_PINC_ENABLE)
			{ DMA2->Streams[StreamCfgs->Stream_Idx].CR |= (1UL << 9); }
		else if(dma_cfgs->PeriphInc == DMA_PINC_DISABLE)
			{ DMA2->Streams[StreamCfgs->Stream_Idx].CR &= ~(1UL << 9); }
		/* 8. Transfer Complete Interrupt Enable */
		DMA2->Streams[StreamCfgs->Stream_Idx].CR |= (1UL << 4UL);
		/* 9. Configure transfer direction */
		DMA2->Streams[StreamCfgs->Stream_Idx].CR |= (((uint32_t)(dma_cfgs->Direction) & (3UL)) << 6);
		/* 10. Select the channel */
		DMA2->Streams[StreamCfgs->Stream_Idx].CR |= ((uint32_t)((dma_cfgs->Channel) & (7UL)) << 25);
		/* 11. Configure the FIFO Mode */
		// Reset the FIFO Control Register First
		DMA2->Streams[StreamCfgs->Stream_Idx].FCR = DMA_SxFCR_RESET_VALUE;
		switch(dma_cfgs->FIFOMode)
		{
			case DMA_FIFOMODE_ENABLE: SET_BIT(DMA2->Streams[StreamCfgs->Stream_Idx].FCR, 2);
								break;	/* !< FIFO Mode */
			case DMA_FIFOMODE_DISABLE: CLEAR_BIT(DMA2->Streams[StreamCfgs->Stream_Idx].FCR, 2);
								break;	/* !< Direct Mode */
			default: retVal |= E_NOT_OK;
		}
		/* 12. Configure the FIFO Threshold value */
		DMA2->Streams[StreamCfgs->Stream_Idx].FCR &= ~(3UL);
		DMA2->Streams[StreamCfgs->Stream_Idx].FCR |= (uint32_t)(dma_cfgs->FIFOThreshold & 3UL);

		/* 13. Assign the Interrupt Handler */
		DMA2_Streams_DefaultInterruptHandlers[StreamCfgs->Stream_Idx] = dma_cfgs->DMA_DefaultHandler;
		/* 13. Enable the Transfer Complete Interrupt */
		SET_BIT(DMA2->Streams[StreamCfgs->Stream_Idx].CR, 4);
		/* 14. Enable the Stream */
		DMA2->Streams[StreamCfgs->Stream_Idx].CR |= (1UL);
	}
	return retVal;
}

Std_ReturnType_t DMA2_DeInit(const DMA_InitTypeDef * dma_cfgs, const DMA_Stream_InitCfgs_t * StreamCfgs)
{
	Std_ReturnType_t retVal = E_OK;
	if((NULL == StreamCfgs) || (NULL == dma_cfgs) || (StreamCfgs->Stream_Idx >= 8))
	{
		retVal = E_NOT_OK;
	}
	else
	{
		/* 1. Disable the DMA Stream */
		CLEAR_BIT(DMA2->Streams[StreamCfgs->Stream_Idx].CR, 0);
		/* 2. Reset all the Register for the DMA */
		DMA2->Streams[StreamCfgs->Stream_Idx].CR = DMA_SxCR_RESET_VALUE;
		DMA2->Streams[StreamCfgs->Stream_Idx].FCR = DMA_SxFCR_RESET_VALUE;
		DMA2->Streams[StreamCfgs->Stream_Idx].M0AR = DMA_SxM0AR_RESET_VALUE;
		DMA2->Streams[StreamCfgs->Stream_Idx].M1AR = DMA_SxM1AR_RESET_VALUE;
		DMA2->Streams[StreamCfgs->Stream_Idx].NDTR = DMA_SxNDTR_RESET_VALUE;
		DMA2->Streams[StreamCfgs->Stream_Idx].PAR = DMA_SxPAR_RESET_VALUE;
	}
	return retVal;
}

/* -------- Interrupt handlers for DMA Streams ----------- */

/**
 * @brief  DMA1 Stream0 Interrupt Handler
 */
void DMA1_Stream0_IRQHandler(void)
{
    /* Clear the interrupt flag */
	SET_BIT(DMA1->LIFCR, 5);
    /* Call the ISR */
    if(DMA1_Streams_DefaultInterruptHandlers[0])
    	DMA1_Streams_DefaultInterruptHandlers[0]();
}

/**
 * @brief  DMA1 Stream1 Interrupt Handler
 */
void DMA1_Stream1_IRQHandler(void)
{
    /* Clear the interrupt flag */
	SET_BIT(DMA1->LIFCR, 11);
    /* Call the ISR */
    if(DMA1_Streams_DefaultInterruptHandlers[1])
    	DMA1_Streams_DefaultInterruptHandlers[1]();
}

/**
 * @brief  DMA1 Stream2 Interrupt Handler
 */
void DMA1_Stream2_IRQHandler(void)
{
    /* Clear the interrupt flag */
	SET_BIT(DMA1->LIFCR, 21);
    /* Call the ISR */
    if(DMA1_Streams_DefaultInterruptHandlers[2])
    	DMA1_Streams_DefaultInterruptHandlers[2]();
}

/**
 * @brief  DMA1 Stream3 Interrupt Handler
 */
void DMA1_Stream3_IRQHandler(void)
{
    /* Clear the interrupt flag */
	SET_BIT(DMA1->LIFCR, 27);
    /* Call the ISR */
    if(DMA1_Streams_DefaultInterruptHandlers[3])
    	DMA1_Streams_DefaultInterruptHandlers[3]();
}

/**
 * @brief  DMA1 Stream4 Interrupt Handler
 */
void DMA1_Stream4_IRQHandler(void)
{
    /* Clear the interrupt flag */
	SET_BIT(DMA1->HIFCR, 5);
    /* Call the ISR */
    if(DMA1_Streams_DefaultInterruptHandlers[4])
    	DMA1_Streams_DefaultInterruptHandlers[4]();
}

/**
 * @brief  DMA1 Stream5 Interrupt Handler
 */
void DMA1_Stream5_IRQHandler(void)
{
    /* Clear the interrupt flag */
	SET_BIT(DMA1->HIFCR, 11);
    /* Call the ISR */
    if(DMA1_Streams_DefaultInterruptHandlers[5])
    	DMA1_Streams_DefaultInterruptHandlers[5]();
}

/**
 * @brief  DMA1 Stream6 Interrupt Handler
 */
void DMA1_Stream6_IRQHandler(void)
{
    /* Clear the interrupt flag */
	SET_BIT(DMA1->HIFCR, 21);
    /* Call the ISR */
    if(DMA1_Streams_DefaultInterruptHandlers[6])
    	DMA1_Streams_DefaultInterruptHandlers[6]();
}

/**
 * @brief  DMA1 Stream7 Interrupt Handler
 */
void DMA1_Stream7_IRQHandler(void)
{
    /* Clear the interrupt flag */
	SET_BIT(DMA1->HIFCR, 27);
    /* Call the ISR */
    if(DMA1_Streams_DefaultInterruptHandlers[7])
    	DMA1_Streams_DefaultInterruptHandlers[7]();
}

/**
 * @brief  DMA2 Stream0 Interrupt Handler
 */
void DMA2_Stream0_IRQHandler(void)
{
    /* Clear the interrupt flag */
    SET_BIT(DMA2->LIFCR, 5);
    /* Call the ISR */
    if(DMA2_Streams_DefaultInterruptHandlers[0])
        DMA2_Streams_DefaultInterruptHandlers[0]();
}

/**
 * @brief  DMA2 Stream1 Interrupt Handler
 */
void DMA2_Stream1_IRQHandler(void)
{
    /* Clear the interrupt flag */
    SET_BIT(DMA2->LIFCR, 11);
    /* Call the ISR */
    if(DMA2_Streams_DefaultInterruptHandlers[1])
        DMA2_Streams_DefaultInterruptHandlers[1]();
}

/**
 * @brief  DMA2 Stream2 Interrupt Handler
 */
void DMA2_Stream2_IRQHandler(void)
{
    /* Clear the interrupt flag */
    SET_BIT(DMA2->LIFCR, 21);
    /* Call the ISR */
    if(DMA2_Streams_DefaultInterruptHandlers[2])
        DMA2_Streams_DefaultInterruptHandlers[2]();
}

/**
 * @brief  DMA2 Stream3 Interrupt Handler
 */
void DMA2_Stream3_IRQHandler(void)
{
    /* Clear the interrupt flag */
    SET_BIT(DMA2->LIFCR, 27);
    /* Call the ISR */
    if(DMA2_Streams_DefaultInterruptHandlers[3])
        DMA2_Streams_DefaultInterruptHandlers[3]();
}

/**
 * @brief  DMA2 Stream4 Interrupt Handler
 */
void DMA2_Stream4_IRQHandler(void)
{
    /* Clear the interrupt flag */
    SET_BIT(DMA2->HIFCR, 5);
    /* Call the ISR */
    if(DMA2_Streams_DefaultInterruptHandlers[4])
        DMA2_Streams_DefaultInterruptHandlers[4]();
}

/**
 * @brief  DMA2 Stream5 Interrupt Handler
 */
void DMA2_Stream5_IRQHandler(void)
{
    /* Clear the interrupt flag */
    SET_BIT(DMA2->HIFCR, 11);
    /* Call the ISR */
    if(DMA2_Streams_DefaultInterruptHandlers[5])
        DMA2_Streams_DefaultInterruptHandlers[5]();
}

/**
 * @brief  DMA2 Stream6 Interrupt Handler
 */
void DMA2_Stream6_IRQHandler(void)
{
    /* Clear the interrupt flag */
    SET_BIT(DMA2->HIFCR, 21);
    /* Call the ISR */
    if(DMA2_Streams_DefaultInterruptHandlers[6])
        DMA2_Streams_DefaultInterruptHandlers[6]();
}

/**
 * @brief  DMA2 Stream7 Interrupt Handler
 */
void DMA2_Stream7_IRQHandler(void)
{
    /* Clear the interrupt flag */
    SET_BIT(DMA2->HIFCR, 27);
    /* Call the ISR */
    if(DMA2_Streams_DefaultInterruptHandlers[7])
        DMA2_Streams_DefaultInterruptHandlers[7]();
}



