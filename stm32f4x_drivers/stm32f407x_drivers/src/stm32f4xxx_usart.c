/**
 ******************************************************************************
 ******************************************************************************
 * @file           : stm32fxxxx_usart.c
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

#include "stm32f407x_usart.h"
#include "stm32f4xxx_usart.h"


ES_t USART_enuInit(USART_Handle_t* Copy_pstrUSARTHandler)
{
	ES_t Local_enuErrSt = ES_NOT_OK;

	if(Copy_pstrUSARTHandler != NULL)
	{
		// Get USARTx Base address
		USART_RegDef_t *Local_USARTBaseAddr = MCAL_USART_BASEADDR_TO_CODE(Copy_pstrUSARTHandler->USARTx);

		// 1. configure the mode
		if(Copy_pstrUSARTHandler->USART_Config.USART_Mode == USART_Mode_RxOnly)
		{
			MCAL_USART_EnableRxOnly(Local_USARTBaseAddr);
		}
		else if(Copy_pstrUSARTHandler->USART_Config.USART_Mode == USART_Mode_TxOnly)
		{
			MCAL_USART_EnableTxOnly(Local_USARTBaseAddr);
		}
		else if(Copy_pstrUSARTHandler->USART_Config.USART_Mode == USART_Mode_RxTx)
		{
			MCAL_USART_EnableRxTx(Local_USARTBaseAddr);
		}
		else
		{

		}

		//2. configure the word length

		if(Copy_pstrUSARTHandler->USART_Config.USART_WordLen == USART_WordLen_8Bits)
		{
			MCAL_USART_SetWordLen8Bit(Local_USARTBaseAddr);
		}
		else if(Copy_pstrUSARTHandler->USART_Config.USART_WordLen == USART_WordLen_9Bits)
		{
			MCAL_USART_SetWordLen9Bit(Local_USARTBaseAddr);
		}
		else
		{

		}

		// 3. configure the parity
		if(Copy_pstrUSARTHandler->USART_Config.USART_Parity == USART_Parity_Disable)
		{
			MCAL_USART_DisableParity(Local_USARTBaseAddr);
		}
		else if (Copy_pstrUSARTHandler->USART_Config.USART_Parity == USART_Parity_Even)
		{
			MCAL_USART_EnableEvenParity(Local_USARTBaseAddr);
		}
		else if (Copy_pstrUSARTHandler->USART_Config.USART_Parity == USART_Parity_Odd)
		{
			MCAL_USART_EnableOddParity(Local_USARTBaseAddr);
		}
		else
		{

		}

		// 4. configure stop pin

		MCAL_USART_SetStopConfig(Local_USARTBaseAddr, Copy_pstrUSARTHandler->USART_Config.USART_StopBits);

		// 5. configure the HW flow control

		if(Copy_pstrUSARTHandler->USART_Config.USART_HwFlowCtrl == USART_HwFlowCtrl_None)
		{
			MCAL_USART_DisableCTSFlowControl(Local_USARTBaseAddr);
			MCAL_USART_DisableRTSFlowControl(Local_USARTBaseAddr);
		}
		else if(Copy_pstrUSARTHandler->USART_Config.USART_HwFlowCtrl == USART_HwFlowCtrl_CTS)
		{
			MCAL_USART_EnableCTSFlowControl(Local_USARTBaseAddr);
			MCAL_USART_DisableRTSFlowControl(Local_USARTBaseAddr);
		}
		else if(Copy_pstrUSARTHandler->USART_Config.USART_HwFlowCtrl == USART_HwFlowCtrl_RTS)
		{
			MCAL_USART_DisableCTSFlowControl(Local_USARTBaseAddr);
			MCAL_USART_EnableRTSFlowControl(Local_USARTBaseAddr);
		}
		else if(Copy_pstrUSARTHandler->USART_Config.USART_HwFlowCtrl == USART_HwFlowCtrl_CTS_RTS)
		{
			MCAL_USART_EnableRTSFlowControl(Local_USARTBaseAddr);
			MCAL_USART_EnableCTSFlowControl(Local_USARTBaseAddr);
		}
		else
		{

		}

		//6. configure baud rate

		MCAL_USART_SetBaudRateValue(Local_USARTBaseAddr, Copy_pstrUSARTHandler->USART_Config.USART_BaudRate);


		// 7. Enable USARTx

		MCAL_USART_Enable(Local_USARTBaseAddr);

	}
	else
	{
		Local_enuErrSt = ES_NULL_PTR;
	}


	return Local_enuErrSt;
}


ES_t USART_enuSendDataSyn(USART_Handle_t* Copy_pstrUSARTHandler, u8 *Copy_pu8Data,u8 Copy_u8Len)
{
	ES_t Local_enuErrSt = ES_NOT_OK;

	if(Copy_pstrUSARTHandler == NULL || Copy_pu8Data == NULL)
	{
		return ES_NULL_PTR;
	}

	// Get USARTx Base address
	USART_RegDef_t *Local_USARTBaseAddr = MCAL_USART_BASEADDR_TO_CODE(Copy_pstrUSARTHandler->USARTx);


	u16 *LocalData;

	for(u8 i=0 ; i<Copy_u8Len ; i++)
	{

		while(! MCAL_USART_GetFlagStatus(Local_USARTBaseAddr,MCAL_USART_FLAG_TXE));

		if(Copy_pstrUSARTHandler->USART_Config.USART_WordLen == USART_WordLen_9Bits)
		{
			LocalData = (u16*) Copy_pu8Data;

			MCAL_USART_WriteData(Local_USARTBaseAddr, (*LocalData & (u16)0x01FF));

			if(Copy_pstrUSARTHandler->USART_Config.USART_Parity == USART_Parity_Disable)
			{
				Copy_pu8Data++;
				Copy_pu8Data++;
			}
			else
			{
				Copy_pu8Data++;
			}

		}
		else if(Copy_pstrUSARTHandler->USART_Config.USART_WordLen == USART_WordLen_8Bits)
		{
			MCAL_USART_WriteData(Local_USARTBaseAddr ,*Copy_pu8Data & (u8)0x0FF);
			Copy_pu8Data++;
		}

	}


	while(! MCAL_USART_GetFlagStatus(Local_USARTBaseAddr,MCAL_USART_FLAG_TC));

	return Local_enuErrSt;
}


ES_t USART_enuReceiveDataSyn(USART_Handle_t* Copy_pstrUSARTHandler, u8 *Copy_pu8Data,u8 Copy_u8Len)
{
	ES_t Local_enuErrSt = ES_NOT_OK;

	if(Copy_pstrUSARTHandler == NULL || Copy_pu8Data == NULL)
	{
		return ES_NULL_PTR;
	}

	// Get USARTx Base address
	USART_RegDef_t *Local_USARTBaseAddr = MCAL_USART_BASEADDR_TO_CODE(Copy_pstrUSARTHandler->USARTx);



	for(u8 i=0 ; i<Copy_u8Len ; i++)
	{

		while(! MCAL_USART_GetFlagStatus(Local_USARTBaseAddr,MCAL_USART_FLAG_RXNE));


		if(Copy_pstrUSARTHandler->USART_Config.USART_WordLen == USART_WordLen_9Bits)
		{

			if(Copy_pstrUSARTHandler->USART_Config.USART_Parity == USART_Parity_Disable)
			{
				// read first 9 bits

				*(u16*)Copy_pu8Data = ( (u16)MCAL_USART_ReadData(Local_USARTBaseAddr) & (u16)0x01FF);
				Copy_pu8Data++;
				Copy_pu8Data++;
			}
			else
			{
				// read 8 bits
				*Copy_pu8Data = ( (u8)MCAL_USART_ReadData(Local_USARTBaseAddr) & (u8)0x0FF);
				Copy_pu8Data++;

			}

		}
		else if(Copy_pstrUSARTHandler->USART_Config.USART_WordLen == USART_WordLen_8Bits)
		{

			if(Copy_pstrUSARTHandler->USART_Config.USART_Parity == USART_Parity_Disable)
			{
				// read 8 bits
				*Copy_pu8Data = ( (u8)MCAL_USART_ReadData(Local_USARTBaseAddr) & (u8)0x0FF);
			}
			else
			{
				// read 7 bits
				*Copy_pu8Data = ( (u8)MCAL_USART_ReadData(Local_USARTBaseAddr) & (u8)0x07F);
			}

			Copy_pu8Data++;
		}

	}

	return Local_enuErrSt;
}


ES_t USART_enuReceiveDataIT(USART_Handle_t* Copy_pstrUSARTHandler, u8 *Copy_pu8Data,u8 Copy_u8Len,void (*callBack)(void))
{

	ES_t Local_enuErrSt = ES_NOT_OK;

	if(Copy_pstrUSARTHandler == NULL || Copy_pu8Data == NULL)
	{
		return ES_NULL_PTR;
	}

	// get USART base address
	USART_RegDef_t *Local_USARTBaseAddr =  MCAL_USART_BASEADDR_TO_CODE(Copy_pstrUSARTHandler->USARTx);

	USART_BusyState_t Local_USARTBusyState = Copy_pstrUSARTHandler->RxBusyState;

	if(Local_USARTBusyState != USART_Busy_InRX)
	{
		Copy_pstrUSARTHandler->pRxBuffer = Copy_pu8Data;
		Copy_pstrUSARTHandler->RxLen = Copy_u8Len;
		Copy_pstrUSARTHandler->RxBusyState = USART_Busy_InRX;

		//set callback function
		Copy_pstrUSARTHandler->RxCallBackFunc = callBack;

		//Enable the interrupt
		MCAL_USART_EnableRXNI(Local_USARTBaseAddr);

		Local_enuErrSt = ES_OK;
	}

	return Local_enuErrSt;
}



ES_t USART_enuSendDataIT(USART_Handle_t* Copy_pstrUSARTHandler, u8 *Copy_pu8Data,u8 Copy_u8Len, void (*callBack)(void) )
{

	ES_t Local_enuErrSt = ES_NOT_OK;

	if(Copy_pstrUSARTHandler == NULL || Copy_pu8Data == NULL)
	{
		return ES_NULL_PTR;
	}

	// get USART base address
	USART_RegDef_t *Local_USARTBaseAddr =  MCAL_USART_BASEADDR_TO_CODE(Copy_pstrUSARTHandler->USARTx);

	USART_BusyState_t Local_USARTBusyState = Copy_pstrUSARTHandler->TxBusyState;

	if(Local_USARTBusyState != USART_Busy_InTX)
	{

		Copy_pstrUSARTHandler->pTxBuffer = Copy_pu8Data;
		Copy_pstrUSARTHandler->TxLen = Copy_u8Len;
		Copy_pstrUSARTHandler->TxBusyState = USART_Busy_InTX;


		Copy_pstrUSARTHandler->TxCallBackFunc = callBack;

		//Enable the interrupt
		MCAL_USART_EnableTCI(Local_USARTBaseAddr);
		MCAL_USART_EnableTXEI(Local_USARTBaseAddr);

		Local_enuErrSt = ES_OK;
	}

	return Local_enuErrSt;
}

void USART_IRQHandling(USART_Handle_t *Copy_pstrUSARTHandler)
{
	if(Copy_pstrUSARTHandler == NULL)
	{
		return;
	}

	USART_RegDef_t *Local_USARTBaseAddr =  MCAL_USART_BASEADDR_TO_CODE(Copy_pstrUSARTHandler->USARTx);

	u8 Temp1 , Temp2;
	u16 *pData;


	Temp1 = MCAL_USART_GetFlagStatus(Local_USARTBaseAddr, MCAL_USART_FLAG_TC);
	Temp2 = MCAL_USART_ReadTXEI(Local_USARTBaseAddr);

	if(Temp1 && Temp2)
	{
		/******************* the interrupt because TC ************************/
		if(Copy_pstrUSARTHandler->TxBusyState == USART_Busy_InTX)
		{
			if(Copy_pstrUSARTHandler->TxLen < 0)
			{

				MCAL_USART_ClearFlag(Local_USARTBaseAddr,MCAL_USART_FLAG_TC);

				Copy_pstrUSARTHandler->TxBusyState = USART_Ready;
				Copy_pstrUSARTHandler->TxLen = 0;
				Copy_pstrUSARTHandler->pTxBuffer = NULL;
				Copy_pstrUSARTHandler->TxCallBackFunc();
			}
		}
	}

	Temp1 = MCAL_USART_GetFlagStatus(Local_USARTBaseAddr, MCAL_USART_FLAG_TXE);
	Temp2 = MCAL_USART_ReadTXEI(Local_USARTBaseAddr);

	if(Temp1 && Temp2)
	{
		/******************* the interrupt because TXE ************************/
		if(Copy_pstrUSARTHandler->TxBusyState == USART_Busy_InTX)
		{
			if(Copy_pstrUSARTHandler->TxLen > 0)
			{

				if(Copy_pstrUSARTHandler->USART_Config.USART_WordLen == USART_WordLen_9Bits)
				{
					pData = (u16*)Copy_pstrUSARTHandler->pTxBuffer;
					MCAL_USART_WriteData(Local_USARTBaseAddr, (*pData & 0x1FF));


					if(Copy_pstrUSARTHandler->USART_Config.USART_Parity == USART_Parity_Disable)
					{
						Copy_pstrUSARTHandler->TxLen-=2;
						Copy_pstrUSARTHandler->pTxBuffer++;
						Copy_pstrUSARTHandler->pTxBuffer++;
					}
					else
					{
						Copy_pstrUSARTHandler->TxLen--;
						Copy_pstrUSARTHandler->pTxBuffer++;
					}


				}
				else if(Copy_pstrUSARTHandler->USART_Config.USART_WordLen == USART_WordLen_8Bits)
				{
					MCAL_USART_WriteData(Local_USARTBaseAddr,(*Copy_pstrUSARTHandler->pTxBuffer & 0x0FF));

					Copy_pstrUSARTHandler->TxLen--;
					Copy_pstrUSARTHandler->pTxBuffer++;
				}

			}

			if(Copy_pstrUSARTHandler->TxLen == 0)
			{
				MCAL_USART_DisableTXEI(Local_USARTBaseAddr);
			}
		}
	}


	Temp1 = MCAL_USART_GetFlagStatus(Local_USARTBaseAddr, MCAL_USART_FLAG_RXNE);
	Temp2 = MCAL_USART_ReadRXNI(Local_USARTBaseAddr);

	if(Temp1 && Temp2)
	{
		/******************* the interrupt because RXNE ************************/
		if(Copy_pstrUSARTHandler->RxBusyState == USART_Busy_InRX)
		{
			if(Copy_pstrUSARTHandler->RxLen > 0)
			{

				if(Copy_pstrUSARTHandler->USART_Config.USART_WordLen == USART_WordLen_9Bits)
				{

					if(Copy_pstrUSARTHandler->USART_Config.USART_Parity == USART_Parity_Disable)
					{
						// Read 9 bits
						*(u16*)Copy_pstrUSARTHandler->pRxBuffer = (MCAL_USART_ReadData(Local_USARTBaseAddr) & (u16)0x01FF);

						Copy_pstrUSARTHandler->RxLen-=2;
						Copy_pstrUSARTHandler->pRxBuffer++;
						Copy_pstrUSARTHandler->pRxBuffer++;

					}
					else
					{
						// Read 8 bits
						*Copy_pstrUSARTHandler->pRxBuffer = (MCAL_USART_ReadData(Local_USARTBaseAddr) & (u8)0x0FF);

						Copy_pstrUSARTHandler->RxLen--;
						Copy_pstrUSARTHandler->pRxBuffer++;
					}


				}
				else if(Copy_pstrUSARTHandler->USART_Config.USART_WordLen == USART_WordLen_8Bits)
				{

					if(Copy_pstrUSARTHandler->USART_Config.USART_Parity == USART_Parity_Disable)
					{
						// Read 8 bits
						*Copy_pstrUSARTHandler->pRxBuffer = (u8)(MCAL_USART_ReadData(Local_USARTBaseAddr) & (u8)0x0FF);

					}
					else
					{
						// Read 7 bits
						*Copy_pstrUSARTHandler->pRxBuffer = (u8)(MCAL_USART_ReadData(Local_USARTBaseAddr) & (u8)0x07F);
					}


					Copy_pstrUSARTHandler->RxLen--;
					Copy_pstrUSARTHandler->pRxBuffer++;
				}

			}

			if(!Copy_pstrUSARTHandler->RxLen)
			{
				MCAL_USART_DisableRXNI(Local_USARTBaseAddr);
				Copy_pstrUSARTHandler->RxBusyState = USART_Ready;
				//CALLBACK function
				Copy_pstrUSARTHandler->RxCallBackFunc();
			}
		}
	}
}






