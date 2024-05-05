/**
 ******************************************************************************
 ******************************************************************************
 * @file           : stm32f407x_i2c.c
 * @author         : Rezk Ahmed
 * @Layer          : MCAL
 * @brief          : Ensure that all hardware information is gathered and abstracted
 *                   from the drivers layer (ECU or Board layer), and provide higher
 *                   layer APIs with access and control over the peripheral drivers.
 ******************************************************************************
 ******************************************************************************
 */


#include "std_types.h"
#include "bit_math.h"
#include "error_state.h"
#include "stm32f407x_i2c.h"

/*************************************** For Initializations **************************************************/

void MCAL_I2C_AckBitControl(I2C_RegDef_t *pI2Cx,u8 AckEnOrDi)
{
	if(AckEnOrDi == MCAL_I2C_ACK_ENABLE)
	{
		SET_BIT(pI2Cx->CR1,MCAL_I2C_CR1_ACK);
	}
	else
	{
		CLR_BIT(pI2Cx->CR1,MCAL_I2C_CR1_ACK);
	}
}

void MCAL_I2c_SetFreqFeild(I2C_RegDef_t *pI2Cx, u32 APB1Freq)
{
	//configure the FREQ field of CR2
	u32 tempreg = 0;
	tempreg |= APB1Freq /1000000U ;
	pI2Cx->CR2 |=  (tempreg & 0x3F);
}

void MCAL_I2C_SetDeviceOwnAddress(I2C_RegDef_t *pI2Cx,u8 DeviceAddress)
{
	//program the device own address
	u32 tempreg = 0;
	tempreg |= DeviceAddress << 1;
	tempreg |= ( 1 << 14);
	pI2Cx->OAR1 |= tempreg;
}

void MCAL_I2C_SetClockControl(I2C_RegDef_t *pI2Cx,u32 APB1Freq,u32 Speed, u8 FMDutyCycle)
{
	//CCR calculations
	u16 ccr_value = 0;
	u32 tempreg = 0;

	if(Speed <= MCAL_I2C_SCL_SPEED_SM)
	{
		//mode is standard mode
		ccr_value = (APB1Freq / ( 2 * Speed ) );
		tempreg |= (ccr_value & 0xFFF);
	}
	else
	{
		//mode is fast mode
		tempreg |= ( 1 << 15);
		tempreg |= (FMDutyCycle << 14);

		if(FMDutyCycle == MCAL_I2C_FM_DUTY_2)
		{
			ccr_value = (APB1Freq / ( 3 * Speed ) );
		}else
		{
			ccr_value = (APB1Freq / ( 25 * Speed ) );
		}
		tempreg |= (ccr_value & 0xFFF);

	}
	pI2Cx->CCR = tempreg;

}

void MCAL_I2C_SetTRISEConfig(I2C_RegDef_t *pI2Cx, u32 APB1Freq, u32 Speed)
{
	u32 tempreg = 0;

	//TRISE Configuration
	if(Speed <= MCAL_I2C_SCL_SPEED_SM)
	{
		//mode is standard mode

		tempreg = (APB1Freq /1000000U) + 1 ;

	}else
	{
		//mode is fast mode
		tempreg = ( (APB1Freq * 300) / 1000000000U ) + 1;

	}

	pI2Cx->TRISE = (tempreg & 0x3F);
}


/***************************************************************************************************************/


void MCAL_I2C_WriteDataByte(I2C_RegDef_t *pI2Cx,u8 Data)
{
	pI2Cx->DR = Data;
}

u32 MCAL_I2C_ReadDataByte(I2C_RegDef_t *pI2Cx)
{
	return pI2Cx->DR;
}

void MCAL_I2C_ClearADDRFlag(I2C_RegDef_t *pI2Cx)
{
	u32 dummy_read=0;

	//clear the ADDR flag ( read SR1 , read SR2)
	dummy_read = pI2Cx->SR1;
	dummy_read = pI2Cx->SR2;
	(void)dummy_read;

}

void MCAL_I2C_GenerateStartCondition(I2C_RegDef_t *pI2Cx)
{
	pI2Cx->CR1 |= ( 1 << MCAL_I2C_CR1_START);
}

void MCAL_I2C_GenerateStopCondition(I2C_RegDef_t *pI2Cx)
{
	pI2Cx->CR1 |= ( 1 << MCAL_I2C_CR1_STOP);
}

void MCAL_I2C_ExecuteAddressPhaseWrite(I2C_RegDef_t *pI2Cx, u8 SlaveAddr)
{
	SlaveAddr = SlaveAddr << 1;
	SlaveAddr &= ~(1); //SlaveAddr is Slave address + r/nw bit=0
	pI2Cx->DR = SlaveAddr;
}

void MCAL_I2C_ExecuteAddressPhaseRead(I2C_RegDef_t *pI2Cx, u8 SlaveAddr)
{
	SlaveAddr = SlaveAddr << 1;
	SlaveAddr |= 1; //SlaveAddr is Slave address + r/nw bit=1
	pI2Cx->DR = SlaveAddr;
}

u8 MCAL_I2C_GetFlagStatus(I2C_RegDef_t *pI2Cx, u32 FlagName)
{
	if(pI2Cx->SR1 & FlagName)
	{
		return SET;
	}
	return RESET;
}

void MCAL_I2C_ClearFlag(I2C_RegDef_t *pI2Cx, u32 FlagName)
{
	pI2Cx->SR1 &= ~FlagName;
}

void MCAL_I2C_InterruptControl(I2C_RegDef_t *pI2Cx, u8 InterruptName, u8 EnOrDi)
{
	if(EnOrDi == ENABLE)
	{
		SET_BIT(pI2Cx->CR2,InterruptName);
	}
	else
	{
		CLR_BIT(pI2Cx->CR2,InterruptName);
	}
}

u8 MCAL_I2C_GetInterruptStatus(I2C_RegDef_t *pI2Cx, u8 InterruptName)
{
	if(pI2Cx->CR2 & (1<<InterruptName))
	{
		return ENABLE;
	}
	else
	{
		return DISABLE;
	}
}




void MCAL_I2C_ClearSTOPFlag(I2C_RegDef_t *pI2Cx)
{
	//STOF flag is set
	//Clear the STOPF ( i.e 1) read SR1 2) Write to CR1 )
	pI2Cx->CR1 |= 0x0000;
}


u8 MCAL_I2C_GetDeviceMode(I2C_RegDef_t *pI2Cx)
{
	if(pI2Cx->SR2 & ( 1 << MCAL_I2C_SR2_MSL))
	{
		return MCAL_I2C_MASTER;
	}

	return MCAL_I2C_SLAVE;
}



u8 MCAL_I2C_GetTransceiverMode(I2C_RegDef_t *pI2Cx)
{
	if(pI2Cx->SR2 & ( 1 << MCAL_I2C_SR2_TRA))
	{
		return MCAL_I2C_TRANSMITTER;
	}
	return MCAL_I2C_RECEIVER;
}


