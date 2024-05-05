/**
 ******************************************************************************
 ******************************************************************************
 * @file           : stm32fxxxx_spi.c
 * @author         : Rezk Ahmed
 * @Layer          : ECU / Board
 * @brief          : For control across the entire STM32F4x family,
 *                   this layer is not aware of specific hardware information
 *                   such as register addresses.
 *                   It utilizes all peripherals through MCAL APIs.
 ******************************************************************************
 ******************************************************************************
 */
#include "std_types.h"
#include "bit_math.h"
#include "error_state.h"

#include "stm32f407x_spi.h"
#include "stm32f4xxx_spi.h"

static void  spi_txe_interrupt_handle(SPI_Handle_t *pSPIHandle);
static void  spi_rxne_interrupt_handle(SPI_Handle_t *pSPIHandle);
static void  spi_ovr_err_interrupt_handle(SPI_Handle_t *pSPIHandle);


ES_t SPI_enuInit(SPI_Handle_t *Copy_pstrSPIHandle)
{
	ES_t Local_enuErrorState = ES_NOT_OK;

	SPI_RegDef_t *Local_SPIBaseAddr = MCAL_SPI_CODE_TO_BASADDR(Copy_pstrSPIHandle->SPIx);

	MCAL_SPI_SetDeviceMode(Local_SPIBaseAddr, Copy_pstrSPIHandle->SPIConfig.SPI_DeviceMode);

	MCAL_SPI_SetBusConfig(Local_SPIBaseAddr,Copy_pstrSPIHandle->SPIConfig.SPI_BusConfig);

	MCAL_SPI_SetClkSpeed(Local_SPIBaseAddr,Copy_pstrSPIHandle->SPIConfig.SPI_SclkSpeed);

	MCAL_SPI_SetDataFrameFormate(Local_SPIBaseAddr,Copy_pstrSPIHandle->SPIConfig.SPI_DFF);

	MCAL_SPI_SetCPOL(Local_SPIBaseAddr,Copy_pstrSPIHandle->SPIConfig.SPI_CPOL);

	MCAL_SPI_SetCPHA(Local_SPIBaseAddr,Copy_pstrSPIHandle->SPIConfig.SPI_CPHA);

	return Local_enuErrorState;
}

ES_t SPI_enuSendData(SPI_Handle_t *Copy_pstrSPIHandle,u8 *Copy_pu8Data, u32 Copy_u32Len)
{
	ES_t Local_enuErrorState = ES_NOT_OK;


	if(Copy_pstrSPIHandle==NULL || Copy_pu8Data==NULL )
		return ES_NULL_PTR;


	SPI_RegDef_t *Local_SPIBaseAddr = MCAL_SPI_CODE_TO_BASADDR(Copy_pstrSPIHandle->SPIx);

	while(Copy_u32Len > 0)
	{
		while( ! MCAL_SPI_GetFlagStatus(Local_SPIBaseAddr,MCAL_SPI_TXE_FLAG));

		if(Copy_pstrSPIHandle->SPIConfig.SPI_DFF == SPI_DFF_16Bits)
		{
			MCAL_SPI_Write(Local_SPIBaseAddr,*((u16*)Copy_pu8Data));
			Copy_u32Len--;
			Copy_u32Len--;
			(u16*)Copy_pu8Data++;
		}
		else if(Copy_pstrSPIHandle->SPIConfig.SPI_DFF == SPI_DFF_8Bits)
		{
			MCAL_SPI_Write(Local_SPIBaseAddr,*Copy_pu8Data & (u8)0xFF);
			Copy_u32Len--;
			Copy_pu8Data++;
		}

	}

	return Local_enuErrorState;
}


ES_t SPI_enuReceiveData(SPI_Handle_t *Copy_pstrSPIHandle,u8 *Copy_pu8Data, u32 Copy_u32Len)
{
	ES_t Local_enuErrorState = ES_NOT_OK;


	if(Copy_pstrSPIHandle==NULL || Copy_pu8Data==NULL )
		return ES_NULL_PTR;


	SPI_RegDef_t *Local_SPIBaseAddr = MCAL_SPI_CODE_TO_BASADDR(Copy_pstrSPIHandle->SPIx);

	while(Copy_u32Len > 0)
	{

		while( ! MCAL_SPI_GetFlagStatus(Local_SPIBaseAddr,MCAL_SPI_RXNE_FLAG));

		if(Copy_pstrSPIHandle->SPIConfig.SPI_DFF == SPI_DFF_16Bits)
		{
			*((u16*)Copy_pu8Data) = MCAL_SPI_Read(Local_SPIBaseAddr);
			Copy_u32Len--;
			Copy_u32Len--;
			(u16*)Copy_pu8Data++;
		}
		else if(Copy_pstrSPIHandle->SPIConfig.SPI_DFF == SPI_DFF_8Bits)
		{
			*Copy_pu8Data = MCAL_SPI_Read(Local_SPIBaseAddr);
			Copy_u32Len--;
			Copy_pu8Data++;
		}

	}

	return Local_enuErrorState;
}


ES_t SPI_enuSendDataIT(SPI_Handle_t *Copy_pstrSPIHandle,u8 *Copy_pu8Data, u32 Copy_u32Len, void(*CallBack)(void))
{
	ES_t Local_enuErrorState = ES_NOT_OK;

	if(Copy_pstrSPIHandle==NULL || Copy_pu8Data==NULL || CallBack==NULL )
		return ES_NULL_PTR;

	if(Copy_pstrSPIHandle->TxState != SPI_BUSY_InTx)
	{
		SPI_RegDef_t *Local_SPIBaseAddr = MCAL_SPI_CODE_TO_BASADDR(Copy_pstrSPIHandle->SPIx);

		Copy_pstrSPIHandle->TxState = SPI_BUSY_InTx;

		Copy_pstrSPIHandle->TxLen = Copy_u32Len;

		Copy_pstrSPIHandle->pTxBuffer = Copy_pu8Data;

		Copy_pstrSPIHandle->TxCallBackFunc = CallBack;

		MCAL_SPI_EnableTxInterrupt(Local_SPIBaseAddr);

	}

	return Local_enuErrorState;
}

ES_t SPI_enuReceiveDataIT(SPI_Handle_t *Copy_pstrSPIHandle,u8 *Copy_pu8Data, u32 Copy_u32Len, void(*CallBack)(void))
{
	ES_t Local_enuErrorState = ES_NOT_OK;

	if(Copy_pstrSPIHandle==NULL || Copy_pu8Data==NULL || CallBack==NULL )
		return ES_NULL_PTR;

	if(Copy_pstrSPIHandle->RxState != SPI_BUSY_InRx)
	{
		SPI_RegDef_t *Local_SPIBaseAddr = MCAL_SPI_CODE_TO_BASADDR(Copy_pstrSPIHandle->SPIx);

		Copy_pstrSPIHandle->RxState = SPI_BUSY_InRx;

		Copy_pstrSPIHandle->RxLen = Copy_u32Len;

		Copy_pstrSPIHandle->pRxBuffer = Copy_pu8Data;

		Copy_pstrSPIHandle->RxCallBackFunc = CallBack;

		MCAL_SPI_EnableRxInterrupt(Local_SPIBaseAddr);

	}

	return Local_enuErrorState;
}


void SPI_IRQHandling(SPI_Handle_t *Copy_pstrSPIHandle)
{

	u8 temp1 , temp2;

	SPI_RegDef_t *Local_SPIBaseAddr = MCAL_SPI_CODE_TO_BASADDR(Copy_pstrSPIHandle->SPIx);

	//first lets check for TXE
	temp1 = MCAL_SPI_GetFlagStatus(Local_SPIBaseAddr,MCAL_SPI_TXE_FLAG);
	temp2 = MCAL_SPI_GetInterruptStatus(Local_SPIBaseAddr,MCAL_SPI_TXE_INT);
	if( temp1 && temp2)
	{
		//handle TXE
		spi_txe_interrupt_handle(Copy_pstrSPIHandle);
	}

	// check for RXNE
	temp1 = MCAL_SPI_GetFlagStatus(Local_SPIBaseAddr,MCAL_SPI_RXNE_FLAG);
	temp2 = MCAL_SPI_GetInterruptStatus(Local_SPIBaseAddr,MCAL_SPI_RXNE_INT);
	if( temp1 && temp2)
	{
		//handle RXNE
		spi_rxne_interrupt_handle(Copy_pstrSPIHandle);
	}

	// check for ovr flag
	temp1 = MCAL_SPI_GetFlagStatus(Local_SPIBaseAddr,MCAL_SPI_OVR_FLAG);
	temp2 = MCAL_SPI_GetInterruptStatus(Local_SPIBaseAddr,MCAL_SPI_ERR_INT);
	if( temp1 && temp2)
	{
		//handle ovr error
		spi_ovr_err_interrupt_handle(Copy_pstrSPIHandle);
	}

}

ES_t SPI_enuStopTransmission(SPI_Handle_t *Copy_pstrSPIHandle)
{
	SPI_RegDef_t *Local_SPIBaseAddr = MCAL_SPI_CODE_TO_BASADDR(Copy_pstrSPIHandle->SPIx);
	MCAL_SPI_DisableTxInterrupt(Local_SPIBaseAddr);
	Copy_pstrSPIHandle->TxState = SPI_Ready;
	Copy_pstrSPIHandle->TxLen = 0;
	Copy_pstrSPIHandle->pTxBuffer = NULL;
	Copy_pstrSPIHandle->TxCallBackFunc = NULL;

	return ES_OK;
}

ES_t SPI_enuStopReception(SPI_Handle_t *Copy_pstrSPIHandle)
{
	SPI_RegDef_t *Local_SPIBaseAddr = MCAL_SPI_CODE_TO_BASADDR(Copy_pstrSPIHandle->SPIx);
	MCAL_SPI_DisableRxInterrupt(Local_SPIBaseAddr);
	Copy_pstrSPIHandle->RxState = SPI_Ready;
	Copy_pstrSPIHandle->RxLen = 0;
	Copy_pstrSPIHandle->pRxBuffer = NULL;
	Copy_pstrSPIHandle->RxCallBackFunc = NULL;

	return ES_OK;
}


//some helper function implementations
static void  spi_txe_interrupt_handle(SPI_Handle_t *Copy_pstrSPIHandle)
{

	SPI_RegDef_t *Local_SPIBaseAddr = MCAL_SPI_CODE_TO_BASADDR(Copy_pstrSPIHandle->SPIx);

	if(Copy_pstrSPIHandle->SPIConfig.SPI_DFF == SPI_DFF_16Bits)
	{
		MCAL_SPI_Write(Local_SPIBaseAddr,*((u16*)Copy_pstrSPIHandle->pTxBuffer));
		Copy_pstrSPIHandle->TxLen--;
		Copy_pstrSPIHandle->TxLen--;
		(u16*)Copy_pstrSPIHandle->pTxBuffer++;
	}
	else if(Copy_pstrSPIHandle->SPIConfig.SPI_DFF == SPI_DFF_8Bits)
	{
		MCAL_SPI_Write(Local_SPIBaseAddr,*Copy_pstrSPIHandle->pTxBuffer & (u8)0xFF);
		Copy_pstrSPIHandle->TxLen--;
		Copy_pstrSPIHandle->pTxBuffer++;
	}


	if(Copy_pstrSPIHandle->TxLen == 0)
	{
		// stop transmission
		MCAL_SPI_DisableTxInterrupt(Local_SPIBaseAddr);
		Copy_pstrSPIHandle->TxState = SPI_Ready;
		Copy_pstrSPIHandle->TxLen = 0;
		Copy_pstrSPIHandle->pTxBuffer = NULL;
		Copy_pstrSPIHandle->TxCallBackFunc();
	}

}



static void  spi_rxne_interrupt_handle(SPI_Handle_t *Copy_pstrSPIHandle)
{
	SPI_RegDef_t *Local_SPIBaseAddr = MCAL_SPI_CODE_TO_BASADDR(Copy_pstrSPIHandle->SPIx);

	if(Copy_pstrSPIHandle->SPIConfig.SPI_DFF == SPI_DFF_16Bits)
	{
		*((u16*)Copy_pstrSPIHandle->pRxBuffer) = MCAL_SPI_Read(Local_SPIBaseAddr);
		Copy_pstrSPIHandle->TxLen--;
		Copy_pstrSPIHandle->TxLen--;
		(u16*)Copy_pstrSPIHandle->pTxBuffer++;
	}
	else if(Copy_pstrSPIHandle->SPIConfig.SPI_DFF == SPI_DFF_8Bits)
	{
		*Copy_pstrSPIHandle->pRxBuffer = MCAL_SPI_Read(Local_SPIBaseAddr);
		Copy_pstrSPIHandle->TxLen--;
		Copy_pstrSPIHandle->pTxBuffer++;
	}

	if(Copy_pstrSPIHandle->TxLen == 0)
	{
		MCAL_SPI_DisableRxInterrupt(Local_SPIBaseAddr);
		Copy_pstrSPIHandle->RxState = SPI_Ready;
		Copy_pstrSPIHandle->RxLen = 0;
		Copy_pstrSPIHandle->pRxBuffer = NULL;
		Copy_pstrSPIHandle->RxCallBackFunc();
	}
}

static void  spi_ovr_err_interrupt_handle(SPI_Handle_t *Copy_pstrSPIHandle)
{
	if(Copy_pstrSPIHandle->TxState == SPI_BUSY_InTx)
	{
		SPI_RegDef_t *Local_SPIBaseAddr = MCAL_SPI_CODE_TO_BASADDR(Copy_pstrSPIHandle->SPIx);
		MCAL_SPI_ClearOVFLag(Local_SPIBaseAddr);
		Copy_pstrSPIHandle->ErrorCallBackFunc();
	}
}


