/**
 ******************************************************************************
 ******************************************************************************
 * @file           : stm32fxxxx_i2c.c
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

#include "stm32f407x_i2c.h"
#include "stm32f4xxx_i2c.h"

#include "stm32f4xxx_rcc.h"


static void I2C_ClearADDRFlag(I2C_Handle_t *Copy_pstrI2CHandle );
static void I2C_MasterHandleTXEInterrupt(I2C_Handle_t *Copy_pstrI2CHandle);
static void I2C_MasterHandleRXNEInterrupt(I2C_Handle_t *Copy_pstrI2CHandle );


ES_t I2C_enuInit(I2C_Handle_t *Copy_pstrI2CHandle)
{
	ES_t Local_enuErrorState = ES_NOT_OK;

	u32 Local_u32APB1ClkFreq = 0;

	I2C_RegDef_t *Local_pstrI2CBaseAddr = MCAL_I2C_CODE_TO_BASADDR(Copy_pstrI2CHandle->I2C_ID);

	MCAL_I2C_AckBitControl(Local_pstrI2CBaseAddr,Copy_pstrI2CHandle->I2C_Config.I2C_AckControl);

	RCC_enuGetAPB1Value(&Local_u32APB1ClkFreq);

	MCAL_I2c_SetFreqFeild(Local_pstrI2CBaseAddr, Local_u32APB1ClkFreq);

	MCAL_I2C_SetDeviceOwnAddress(Local_pstrI2CBaseAddr, Copy_pstrI2CHandle->I2C_Config.I2C_DeviceAddress);

	MCAL_I2C_SetClockControl(Local_pstrI2CBaseAddr, Local_u32APB1ClkFreq,
			Copy_pstrI2CHandle->I2C_Config.I2C_SCLSpeed , Copy_pstrI2CHandle->I2C_Config.I2C_FMDutyCycle);

	MCAL_I2C_SetTRISEConfig(Local_pstrI2CBaseAddr, Local_u32APB1ClkFreq, Copy_pstrI2CHandle->I2C_Config.I2C_SCLSpeed );

	Local_enuErrorState = ES_OK;

	return Local_enuErrorState;
}


ES_t I2C_enuMasterSendData(I2C_Handle_t *Copy_pstrI2CHandle,u8 *Copy_pu8Data,
		u8 Copy_u8Len, u8 Copy_u8SlaveAddr,I2C_RepStartCtrl_t Copy_enuSr)
{
	ES_t Local_enuErrorState = ES_NOT_OK;


	I2C_RegDef_t *Local_pstrI2CBaseAddr = MCAL_I2C_CODE_TO_BASADDR(Copy_pstrI2CHandle->I2C_ID);

	// 1. Generate the START condition
	MCAL_I2C_GenerateStartCondition(Local_pstrI2CBaseAddr);

	//2. confirm that start generation is completed by checking the SB flag in the SR1
	//   Note: Until SB is cleared SCL will be stretched (pulled to LOW)
	while( !  MCAL_I2C_GetFlagStatus(Local_pstrI2CBaseAddr, MCAL_I2C_FLAG_SB)   );

	//3. Send the address of the slave with r/nw bit set to w(0) (total 8 bits )
	MCAL_I2C_ExecuteAddressPhaseWrite(Local_pstrI2CBaseAddr, Copy_u8SlaveAddr);

	//4. Confirm that address phase is completed by checking the ADDR flag in teh SR1
	while( !  MCAL_I2C_GetFlagStatus(Local_pstrI2CBaseAddr, MCAL_I2C_FLAG_ADDR)   );

	//5. clear the ADDR flag according to its software sequence
	//   Note: Until ADDR is cleared SCL will be stretched (pulled to LOW)
	I2C_ClearADDRFlag(Copy_pstrI2CHandle);

	//6. send the data until len becomes 0

	while(Copy_u8Len > 0)
	{
		while(! MCAL_I2C_GetFlagStatus(Local_pstrI2CBaseAddr, MCAL_I2C_FLAG_TXE) ); //Wait till TXE is set

		MCAL_I2C_WriteDataByte(Local_pstrI2CBaseAddr,*Copy_pu8Data);

		Copy_pu8Data++;
		Copy_u8Len--;
	}

	//7. when Len becomes zero wait for TXE=1 and BTF=1 before generating the STOP condition
	//   Note: TXE=1 , BTF=1 , means that both SR and DR are empty and next transmission should begin
	//   when BTF=1 SCL will be stretched (pulled to LOW)

	while(! MCAL_I2C_GetFlagStatus(Local_pstrI2CBaseAddr,MCAL_I2C_FLAG_TXE) );

	while(! MCAL_I2C_GetFlagStatus(Local_pstrI2CBaseAddr,MCAL_I2C_FLAG_BTF) );

	Local_enuErrorState = ES_OK;

	//8. Generate STOP condition and master need not to wait for the completion of stop condition.
	//   Note: generating STOP, automatically clears the BTF

	if(Copy_enuSr == I2C_DisableRepStart)
	{
		MCAL_I2C_GenerateStopCondition(Local_pstrI2CBaseAddr);
	}

	return Local_enuErrorState;
}

ES_t I2C_enuMasterReceiveData(I2C_Handle_t *Copy_pstrI2CHandle,u8 *Copy_pu8Data,
		u8 Copy_u8Len, u8 Copy_u8SlaveAddr,I2C_RepStartCtrl_t Copy_enuSr)
{
	ES_t Local_enuErrorState = ES_NOT_OK;

	I2C_RegDef_t *Local_pstrI2CBaseAddr = MCAL_I2C_CODE_TO_BASADDR(Copy_pstrI2CHandle->I2C_ID);

	// 1. Generate the START condition
	MCAL_I2C_GenerateStartCondition(Local_pstrI2CBaseAddr);

	//2. confirm that start generation is completed by checking the SB flag in the SR1
	//   Note: Until SB is cleared SCL will be stretched (pulled to LOW)
	while( !  MCAL_I2C_GetFlagStatus(Local_pstrI2CBaseAddr, MCAL_I2C_FLAG_SB)   );

	//3. Send the address of the slave with r/nw bit set to w(0) (total 8 bits )
	MCAL_I2C_ExecuteAddressPhaseRead(Local_pstrI2CBaseAddr, Copy_u8SlaveAddr);

	//4. wait until address phase is completed by checking the ADDR flag in teh SR1
	while( !  MCAL_I2C_GetFlagStatus(Local_pstrI2CBaseAddr, MCAL_I2C_FLAG_ADDR)   );


	//procedure to read only 1 byte from slave
	if(Copy_u8Len == 1)
	{
		//Disable Acking
		MCAL_I2C_AckBitControl(Local_pstrI2CBaseAddr, MCAL_I2C_ACK_DISABLE);

		//clear the ADDR flag
		I2C_ClearADDRFlag(Copy_pstrI2CHandle);

		//wait until  RXNE becomes 1
		while(! MCAL_I2C_GetFlagStatus(Local_pstrI2CBaseAddr,MCAL_I2C_FLAG_RXNE) );

		//generate STOP condition
		if(Copy_enuSr == I2C_DisableRepStart)
		{
			MCAL_I2C_GenerateStopCondition(Local_pstrI2CBaseAddr);
		}

		//read data in to buffer
		*Copy_pu8Data = (u8)MCAL_I2C_ReadDataByte(Local_pstrI2CBaseAddr);

		Local_enuErrorState = ES_OK;

	}


	//procedure to read data from slave when Len > 1
	if(Copy_u8Len > 1)
	{
		//clear the ADDR flag
		I2C_ClearADDRFlag(Copy_pstrI2CHandle);

		//read the data until Len becomes zero
		for (u32 i = Copy_u8Len ; i > 0 ; i--)
		{
			//wait until RXNE becomes 1
			while(! MCAL_I2C_GetFlagStatus(Local_pstrI2CBaseAddr,MCAL_I2C_FLAG_RXNE) );

			if(i == 2) //if last 2 bytes are remaining
			{
				//Disable Acking
				MCAL_I2C_AckBitControl(Local_pstrI2CBaseAddr, MCAL_I2C_ACK_DISABLE);

				//generate STOP condition
				if(Copy_enuSr == I2C_DisableRepStart)
				{
					MCAL_I2C_GenerateStopCondition(Local_pstrI2CBaseAddr);
				}
			}

			//read the data from data register in to buffer
			*Copy_pu8Data = (u8)MCAL_I2C_ReadDataByte(Local_pstrI2CBaseAddr);

			//increment the buffer address
			Copy_pu8Data++;

		}

		Local_enuErrorState = ES_OK;

	}

	//re-enable ACKing
	if(Copy_pstrI2CHandle->I2C_Config.I2C_AckControl == I2C_ACK_Enable)
	{
		MCAL_I2C_AckBitControl(Local_pstrI2CBaseAddr, MCAL_I2C_ACK_ENABLE);
	}

	return Local_enuErrorState;
}

ES_t I2C_enuSlaveSendData(I2C_t Copy_enuI2CId, u8 Copy_pu8Data)
{
	ES_t Local_enuErrorState = ES_NOT_OK;

	I2C_RegDef_t *Local_pstrI2CBaseAddr = MCAL_I2C_CODE_TO_BASADDR(Copy_enuI2CId);

	MCAL_I2C_WriteDataByte(Local_pstrI2CBaseAddr, Copy_pu8Data);

	return Local_enuErrorState;
}


ES_t I2C_enuSlaveReceiveData(I2C_t Copy_enuI2CId, u8 *Copy_pu8Data)
{
	ES_t Local_enuErrorState = ES_NOT_OK;

	I2C_RegDef_t *Local_pstrI2CBaseAddr = MCAL_I2C_CODE_TO_BASADDR(Copy_enuI2CId);

	*Copy_pu8Data = MCAL_I2C_ReadDataByte(Local_pstrI2CBaseAddr);

	return Local_enuErrorState;
}



/*
 * Data Send and Receive IT (Asynchronous mode)
 */
ES_t I2C_enuMasterSendDataIT(I2C_Handle_t *Copy_pstrI2CHandle,u8 *Copy_pu8Data,
		u8 Copy_u8Len, u8 Copy_u8SlaveAddr,I2C_RepStartCtrl_t Copy_enuSr)
{
	ES_t Local_enuErrorState = ES_NOT_OK;

	if( (Copy_pstrI2CHandle->TxRxState != I2C_BusyInTx) && (Copy_pstrI2CHandle->TxRxState != I2C_BusyInRx))
	{

		I2C_RegDef_t *Local_pstrI2CBaseAddr = MCAL_I2C_CODE_TO_BASADDR(Copy_pstrI2CHandle->I2C_ID);


		Copy_pstrI2CHandle->pTxBuffer = Copy_pu8Data;
		Copy_pstrI2CHandle->TxLen = Copy_u8Len;
		Copy_pstrI2CHandle->TxRxState = I2C_BusyInTx;
		Copy_pstrI2CHandle->DevAddr = Copy_u8SlaveAddr;
		Copy_pstrI2CHandle->Sr = Copy_enuSr;

		//Implement code to Generate START Condition
		MCAL_I2C_GenerateStartCondition(Local_pstrI2CBaseAddr);

		//Implement the code to enable ITBUFEN Control Bit
		MCAL_I2C_InterruptControl(Local_pstrI2CBaseAddr, MCAL_I2C_ITBUFEN_INT, ENABLE);

		//Implement the code to enable ITEVFEN Control Bit
		MCAL_I2C_InterruptControl(Local_pstrI2CBaseAddr, MCAL_I2C_ITEVFEN_INT, ENABLE);

		//Implement the code to enable ITERREN Control Bit
		MCAL_I2C_InterruptControl(Local_pstrI2CBaseAddr, MCAL_I2C_ITERREN_INT, ENABLE);

		Local_enuErrorState = ES_OK;
	}

	return Local_enuErrorState;
}


ES_t I2C_enuMasterReceiveDataIT(I2C_Handle_t *Copy_pstrI2CHandle,u8 *Copy_pu8Data,
		u8 Copy_u8Len, u8 Copy_u8SlaveAddr,I2C_RepStartCtrl_t Copy_enuSr)
{
	ES_t Local_enuErrorState = ES_NOT_OK;

	if( (Copy_pstrI2CHandle->TxRxState != I2C_BusyInTx) && (Copy_pstrI2CHandle->TxRxState != I2C_BusyInRx))
	{

		I2C_RegDef_t *Local_pstrI2CBaseAddr = MCAL_I2C_CODE_TO_BASADDR(Copy_pstrI2CHandle->I2C_ID);

		Copy_pstrI2CHandle->pRxBuffer = Copy_pu8Data;
		Copy_pstrI2CHandle->RxLen = Copy_u8Len;
		Copy_pstrI2CHandle->TxRxState = I2C_BusyInRx;
		Copy_pstrI2CHandle->RxSize = Copy_u8Len;
		Copy_pstrI2CHandle->DevAddr = Copy_u8SlaveAddr;
		Copy_pstrI2CHandle->Sr = Copy_enuSr;

		//Implement code to Generate START Condition
		MCAL_I2C_GenerateStartCondition(Local_pstrI2CBaseAddr);

		//Implement the code to enable ITBUFEN Control Bit
		MCAL_I2C_InterruptControl(Local_pstrI2CBaseAddr, MCAL_I2C_ITBUFEN_INT, ENABLE);

		//Implement the code to enable ITEVFEN Control Bit
		MCAL_I2C_InterruptControl(Local_pstrI2CBaseAddr, MCAL_I2C_ITEVFEN_INT, ENABLE);

		//Implement the code to enable ITERREN Control Bit
		MCAL_I2C_InterruptControl(Local_pstrI2CBaseAddr, MCAL_I2C_ITERREN_INT, ENABLE);

		Local_enuErrorState = ES_OK;
	}

	return Local_enuErrorState;
}


static void I2C_MasterHandleTXEInterrupt(I2C_Handle_t *Copy_pstrI2CHandle)
{
	if(Copy_pstrI2CHandle->TxLen > 0)
	{
		I2C_RegDef_t *Local_pstrI2CBaseAddr = MCAL_I2C_CODE_TO_BASADDR(Copy_pstrI2CHandle->I2C_ID);

		//1. load the data in to DR
		MCAL_I2C_WriteDataByte(Local_pstrI2CBaseAddr,*Copy_pstrI2CHandle->pTxBuffer);

		//2. decrement the TxLen
		Copy_pstrI2CHandle->TxLen--;

		//3. Increment the buffer address
		Copy_pstrI2CHandle->pTxBuffer++;
	}
}



static void I2C_MasterHandleRXNEInterrupt(I2C_Handle_t *Copy_pstrI2CHandle )
{
	//We have to do the data reception
	I2C_RegDef_t *Local_pstrI2CBaseAddr = MCAL_I2C_CODE_TO_BASADDR(Copy_pstrI2CHandle->I2C_ID);

	if(Copy_pstrI2CHandle->RxSize == 1)
	{
		// Read Just one byte
		*Copy_pstrI2CHandle->pRxBuffer = MCAL_I2C_ReadDataByte(Local_pstrI2CBaseAddr);
		Copy_pstrI2CHandle->RxLen--;
	}


	if(Copy_pstrI2CHandle->RxSize > 1)
	{
		if(Copy_pstrI2CHandle->RxLen == 2)
		{
			//clear the ack bit
			MCAL_I2C_AckBitControl(Local_pstrI2CBaseAddr, MCAL_I2C_ACK_DISABLE);
		}

		//read DR
		*Copy_pstrI2CHandle->pRxBuffer = MCAL_I2C_ReadDataByte(Local_pstrI2CBaseAddr);
		Copy_pstrI2CHandle->pRxBuffer++;
		Copy_pstrI2CHandle->RxLen--;
	}

	if(Copy_pstrI2CHandle->RxLen == 0 )
	{
		//close the I2C data reception and notify the application

		//1. generate the stop condition
		//generate STOP condition
		if(Copy_pstrI2CHandle->Sr == I2C_DisableRepStart)
		{
			MCAL_I2C_GenerateStopCondition(Local_pstrI2CBaseAddr);
		}

		//2 . Close the I2C rx
		I2C_CloseReceiveData(Copy_pstrI2CHandle);

		//3. Notify the application
		if(Copy_pstrI2CHandle->CallBackFun != NULL)
		{
			Copy_pstrI2CHandle->CallBackFun(I2C_Event_RxComplete);
		}
	}
}



void I2C_CloseReceiveData(I2C_Handle_t *Copy_pstrI2CHandle)
{
	I2C_RegDef_t *Local_pstrI2CBaseAddr = MCAL_I2C_CODE_TO_BASADDR(Copy_pstrI2CHandle->I2C_ID);

	//Implement the code to disable ITBUFEN Control Bit
	MCAL_I2C_InterruptControl(Local_pstrI2CBaseAddr, MCAL_I2C_ITBUFEN_INT, DISABLE);

	//Implement the code to disable ITEVFEN Control Bit
	MCAL_I2C_InterruptControl(Local_pstrI2CBaseAddr, MCAL_I2C_ITEVFEN_INT, DISABLE);

	Copy_pstrI2CHandle->TxRxState = I2C_Ready;
	Copy_pstrI2CHandle->pRxBuffer = NULL;
	Copy_pstrI2CHandle->RxLen = 0;
	Copy_pstrI2CHandle->RxSize = 0;

	if(Copy_pstrI2CHandle->I2C_Config.I2C_AckControl == I2C_ACK_Enable)
	{
		MCAL_I2C_AckBitControl(Local_pstrI2CBaseAddr, MCAL_I2C_ACK_ENABLE);
	}
}



void I2C_CloseSendData(I2C_Handle_t *Copy_pstrI2CHandle)
{

	I2C_RegDef_t *Local_pstrI2CBaseAddr = MCAL_I2C_CODE_TO_BASADDR(Copy_pstrI2CHandle->I2C_ID);

	//Implement the code to disable ITBUFEN Control Bit
	MCAL_I2C_InterruptControl(Local_pstrI2CBaseAddr, MCAL_I2C_ITBUFEN_INT, DISABLE);

	//Implement the code to disable ITEVFEN Control Bit
	MCAL_I2C_InterruptControl(Local_pstrI2CBaseAddr, MCAL_I2C_ITEVFEN_INT, DISABLE);


	Copy_pstrI2CHandle->TxRxState = I2C_Ready;
	Copy_pstrI2CHandle->pTxBuffer = NULL;
	Copy_pstrI2CHandle->TxLen = 0;
}



void I2C_EV_IRQHandling(I2C_Handle_t *Copy_pstrI2CHandle)
{
	//Interrupt handling for both master and slave mode of a device

	u32 temp1, temp2, temp3;

	I2C_RegDef_t *Local_pstrI2CBaseAddr = MCAL_I2C_CODE_TO_BASADDR(Copy_pstrI2CHandle->I2C_ID);

	temp1   = MCAL_I2C_GetInterruptStatus(Local_pstrI2CBaseAddr, MCAL_I2C_ITBUFEN_INT);
	temp2   = MCAL_I2C_GetInterruptStatus(Local_pstrI2CBaseAddr, MCAL_I2C_ITEVFEN_INT);


	temp3   = MCAL_I2C_GetFlagStatus(Local_pstrI2CBaseAddr, MCAL_I2C_FLAG_SB);

	//1. Handle For interrupt generated by SB event
	//	Note : SB flag is only applicable in Master mode
	if(temp1 && temp3)
	{
		//The interrupt is generated because of SB event
		//This block will not be executed in slave mode because for slave SB is always zero
		//In this block lets executed the address phase
		if(Copy_pstrI2CHandle->TxRxState == I2C_BusyInTx)
		{
			MCAL_I2C_ExecuteAddressPhaseWrite(Local_pstrI2CBaseAddr,Copy_pstrI2CHandle->DevAddr);
		}
		else if (Copy_pstrI2CHandle->TxRxState == I2C_BusyInRx )
		{
			MCAL_I2C_ExecuteAddressPhaseRead(Local_pstrI2CBaseAddr,Copy_pstrI2CHandle->DevAddr);
		}
	}

	temp3   = MCAL_I2C_GetFlagStatus(Local_pstrI2CBaseAddr, MCAL_I2C_FLAG_ADDR);
	//2. Handle For interrupt generated by ADDR event
	//Note : When master mode : Address is sent
	//		 When Slave mode   : Address matched with own address
	if(temp1 && temp3)
	{
		// interrupt is generated because of ADDR event
		I2C_ClearADDRFlag(Copy_pstrI2CHandle);
	}


	temp3   = MCAL_I2C_GetFlagStatus(Local_pstrI2CBaseAddr, MCAL_I2C_FLAG_BTF);
	//3. Handle For interrupt generated by BTF(Byte Transfer Finished) event
	if(temp1 && temp3)
	{
		//BTF flag is set
		if(Copy_pstrI2CHandle->TxRxState == I2C_BusyInTx)
		{
			//make sure that TXE is also set .
			if( MCAL_I2C_GetFlagStatus(Local_pstrI2CBaseAddr,MCAL_I2C_FLAG_TXE) )
			{
				//BTF, TXE = 1
				if(Copy_pstrI2CHandle->TxLen == 0)
				{
					//1. generate the STOP condition
					if(Copy_pstrI2CHandle->Sr == I2C_DisableRepStart)
					{
						MCAL_I2C_GenerateStopCondition(Local_pstrI2CBaseAddr);
					}

					//2. reset all the member elements of the handle structure.
					I2C_CloseSendData(Copy_pstrI2CHandle);

					//3. notify the application about transmission complete
					Copy_pstrI2CHandle->CallBackFun(I2C_Event_TxComplete);
				}
			}
		}
	}

	temp3   = MCAL_I2C_GetFlagStatus(Local_pstrI2CBaseAddr, MCAL_I2C_FLAG_STOPF);
	//4. Handle For interrupt generated by STOPF event
	// Note : Stop detection flag is applicable only slave mode . For master this flag will never be set
	//The below code block will not be executed by the master since STOPF will not set in master mode
	if(temp1 && temp3)
	{
		//STOF flag is set
		//Clear the STOPF ( i.e 1) read SR1 2) Write to CR1 )
		MCAL_I2C_ClearSTOPFlag(Local_pstrI2CBaseAddr);

		//Notify the application that STOP is detected
		Copy_pstrI2CHandle->CallBackFun(I2C_Event_Stop);
	}


	temp3  = MCAL_I2C_GetFlagStatus(Local_pstrI2CBaseAddr,MCAL_I2C_FLAG_TXE);
	//5. Handle For interrupt generated by TXE event
	if(temp1 && temp2 && temp3)
	{
		//Check for device mode
		if(MCAL_I2C_GetDeviceMode(Local_pstrI2CBaseAddr) == MCAL_I2C_MASTER)
		{
			//TXE flag is set
			//We have to do the data transmission
			if(Copy_pstrI2CHandle->TxRxState == I2C_BusyInTx)
			{
				I2C_MasterHandleTXEInterrupt(Copy_pstrI2CHandle);
			}
		}
		else
		{
			//slave
			//make sure that the slave is really in transmitter mode
			if(MCAL_I2C_GetTransceiverMode(Local_pstrI2CBaseAddr)==MCAL_I2C_TRANSMITTER)
			{
				Copy_pstrI2CHandle->CallBackFun(I2C_Event_DataReq);
			}
		}
	}

	temp3  = MCAL_I2C_GetFlagStatus(Local_pstrI2CBaseAddr,MCAL_I2C_FLAG_RXNE);
	//6. Handle For interrupt generated by RXNE event
	if(temp1 && temp2 && temp3)
	{
		//check device mode .
		if(MCAL_I2C_GetDeviceMode(Local_pstrI2CBaseAddr) == MCAL_I2C_MASTER)
		{
			//The device is master
			//RXNE flag is set
			if(Copy_pstrI2CHandle->TxRxState == I2C_BusyInRx)
			{
				I2C_MasterHandleRXNEInterrupt(Copy_pstrI2CHandle);
			}

		}
		else
		{
			//slave
			//make sure that the slave is really in receiver mode
			if(MCAL_I2C_GetTransceiverMode(Local_pstrI2CBaseAddr)==MCAL_I2C_RECEIVER)
			{
				Copy_pstrI2CHandle->CallBackFun(I2C_Event_DataRcv);
			}
		}
	}
}



static void I2C_ClearADDRFlag(I2C_Handle_t *Copy_pstrI2CHandle )
{
	I2C_RegDef_t *Local_pstrI2CBaseAddr = MCAL_I2C_CODE_TO_BASADDR(Copy_pstrI2CHandle->I2C_ID);

	//check for device mode
	if(Local_pstrI2CBaseAddr->SR2 & ( 1 << MCAL_I2C_SR2_MSL))
	{
		//device is in master mode
		if(Copy_pstrI2CHandle->TxRxState == MCAL_I2C_BUSY_IN_RX)
		{
			if(Copy_pstrI2CHandle->RxSize  == 1)
			{
				//first disable the ack
				MCAL_I2C_AckBitControl(Local_pstrI2CBaseAddr, MCAL_I2C_ACK_DISABLE);
				MCAL_I2C_ClearADDRFlag(Local_pstrI2CBaseAddr);
			}
		}
		else
		{
			MCAL_I2C_ClearADDRFlag(Local_pstrI2CBaseAddr);
		}

	}
	else//device is in slave mode
	{
		MCAL_I2C_ClearADDRFlag(Local_pstrI2CBaseAddr);
	}

}


void I2C_ER_IRQHandling(I2C_Handle_t *Copy_pstrI2CHandle)
{

	u32 temp1,temp2;

	I2C_RegDef_t *Local_pstrI2CBaseAddr = MCAL_I2C_CODE_TO_BASADDR(Copy_pstrI2CHandle->I2C_ID);

	temp2   = MCAL_I2C_GetInterruptStatus(Local_pstrI2CBaseAddr, MCAL_I2C_ITERREN_INT);

	/***********************Check for Bus error************************************/
	temp1 = MCAL_I2C_GetFlagStatus(Local_pstrI2CBaseAddr, MCAL_I2C_FLAG_BERR);
	if(temp1  && temp2 )
	{
		//This is Bus error

		//Implement the code to clear the buss error flag
		MCAL_I2C_ClearFlag(Local_pstrI2CBaseAddr,MCAL_I2C_FLAG_BERR);

		//Implement the code to notify the application about the error
		Copy_pstrI2CHandle->CallBackFun(I2C_Event_ErrorBerr);
	}

	/***********************Check for arbitration lost error************************************/
	temp1 = MCAL_I2C_GetFlagStatus(Local_pstrI2CBaseAddr, MCAL_I2C_FLAG_ARLO);
	if(temp1  && temp2)
	{
		//This is arbitration lost error

		//Implement the code to clear the buss error flag
		MCAL_I2C_ClearFlag(Local_pstrI2CBaseAddr,MCAL_I2C_FLAG_ARLO);

		//Implement the code to notify the application about the error
		Copy_pstrI2CHandle->CallBackFun(I2C_Event_ErrorArlo);

	}

	/***********************Check for ACK failure  error************************************/

	temp1 = MCAL_I2C_GetFlagStatus(Local_pstrI2CBaseAddr, MCAL_I2C_FLAG_AF);
	if(temp1  && temp2)
	{
		//This is ACK failure error

		//Implement the code to clear the buss error flag
		MCAL_I2C_ClearFlag(Local_pstrI2CBaseAddr,MCAL_I2C_FLAG_AF);

		//Implement the code to notify the application about the error
		Copy_pstrI2CHandle->CallBackFun(I2C_Event_ErrorAf);
	}

	/***********************Check for Overrun/underrun error************************************/
	temp1 = MCAL_I2C_GetFlagStatus(Local_pstrI2CBaseAddr, MCAL_I2C_FLAG_OVR);
	if(temp1  && temp2)
	{
		//This is Overrun/underrun

		//Implement the code to clear the buss error flag
			MCAL_I2C_ClearFlag(Local_pstrI2CBaseAddr,MCAL_I2C_FLAG_OVR);

			//Implement the code to notify the application about the error
			Copy_pstrI2CHandle->CallBackFun(I2C_Event_ErrorOvr);
	}

	/***********************Check for Time out error************************************/
	temp1 = MCAL_I2C_GetFlagStatus(Local_pstrI2CBaseAddr, MCAL_I2C_FLAG_TIMEOUT);
	if(temp1  && temp2)
	{
		//This is Overrun/underrun

		//Implement the code to clear the buss error flag
			MCAL_I2C_ClearFlag(Local_pstrI2CBaseAddr,MCAL_I2C_FLAG_TIMEOUT);

			//Implement the code to notify the application about the error
			Copy_pstrI2CHandle->CallBackFun(I2C_Event_ErrorTimeout);
	}
}




