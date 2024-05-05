/**
 ******************************************************************************
 ******************************************************************************
 * @file           : stm32f407x_spi.c
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
#include "stm32f407x_spi.h"

void MCAL_PSI_Enable(SPI_RegDef_t *pPSIx)
{
	SET_BIT(pPSIx->CR1,MCAL_SPI_CR1_SPE);
}

void MCAL_PSI_Disable(SPI_RegDef_t *pPSIx)
{
	CLR_BIT(pPSIx->CR1,MCAL_SPI_CR1_SPE);
}

void MCAL_SPI_SetDeviceMode(SPI_RegDef_t *pPSIx, u8 DeviceMode)
{
	if(DeviceMode == MCAL_SPI_DEVICE_MODE_MASTER)
	{
		SET_BIT(pPSIx->CR1,MCAL_SPI_CR1_MSTR);
	}
	else if(DeviceMode == MCAL_SPI_DEVICE_MODE_SLAVE)
	{
		CLR_BIT(pPSIx->CR1,MCAL_SPI_CR1_MSTR);
	}
}

void MCAL_SPI_SetBusConfig(SPI_RegDef_t *pPSIx, u8 BusConfig)
{
	if(BusConfig == MCAL_SPI_BUS_CONFIG_FD)
	{
		CLR_BIT(pPSIx->CR1,MCAL_SPI_CR1_BIDIMODE);
	}
	else if(BusConfig == MCAL_SPI_BUS_CONFIG_HD)
	{
		SET_BIT(pPSIx->CR1,MCAL_SPI_CR1_BIDIMODE);
	}
	else if(BusConfig == MCAL_SPI_BUS_CONFIG_SIMPLEX_RXONLY)
	{
		CLR_BIT(pPSIx->CR1,MCAL_SPI_CR1_BIDIMODE);
		SET_BIT(pPSIx->CR1,MCAL_SPI_CR1_RXONLY);
	}
}

void MCAL_SPI_SetClkSpeed(SPI_RegDef_t *pPSIx, u8 SclkSpeed)
{
	SclkSpeed &= 0x7;
	pPSIx->CR1 |= SclkSpeed << 3 ;
}


void MCAL_SPI_SetDataFrameFormate(SPI_RegDef_t *pPSIx, u8 DataFrameFormate)
{
	if (DataFrameFormate == MCAL_SPI_DFF_8BITS)
	{
		CLR_BIT(pPSIx->CR1,MCAL_SPI_CR1_DFF);
	}
	else if(DataFrameFormate == MCAL_SPI_DFF_16BITS)
	{
		SET_BIT(pPSIx->CR1,MCAL_SPI_CR1_DFF);
	}
}

void MCAL_SPI_SetCPOL(SPI_RegDef_t *pPSIx, u8 CPOL)
{
	if(CPOL == MCAL_SPI_CPOL_HIGH)
	{
		SET_BIT(pPSIx->CR1,MCAL_SPI_CR1_CPOL);
	}
	else if(CPOL == MCAL_SPI_CPOL_LOW)
	{
		CLR_BIT(pPSIx->CR1,MCAL_SPI_CR1_CPOL);
	}
}

void MCAL_SPI_SetCPHA(SPI_RegDef_t *pPSIx, u8 CPHA)
{
	if(CPHA == MCAL_SPI_CPHA_HIGH)
	{
		SET_BIT(pPSIx->CR1,MCAL_SPI_CR1_CPHA);
	}
	else if(CPHA == MCAL_SPI_CPHA_LOW)
	{
		CLR_BIT(pPSIx->CR1,MCAL_SPI_CR1_CPHA);
	}
}



void MCAL_SPI_Write(SPI_RegDef_t *pPSIx, u16 Data)
{
	pPSIx->DR = Data;
}


u16 MCAL_SPI_Read(SPI_RegDef_t *pPSIx)
{
	return pPSIx->DR;
}

void MCAL_SPI_EnableTxInterrupt(SPI_RegDef_t *pPSIx)
{
	if(pPSIx == NULL)
		return;

	SET_BIT(pPSIx->CR2,MCAL_SPI_CR2_TXEIE);
}

void MCAL_SPI_DisableTxInterrupt(SPI_RegDef_t *pPSIx)
{
	CLR_BIT(pPSIx->CR2,MCAL_SPI_CR2_TXEIE);
}


void MCAL_SPI_EnableRxInterrupt(SPI_RegDef_t *pPSIx)
{
	CLR_BIT(pPSIx->CR2,MCAL_SPI_CR2_RXNEIE);
}

void MCAL_SPI_DisableRxInterrupt(SPI_RegDef_t *pPSIx)
{
	CLR_BIT(pPSIx->CR2,MCAL_SPI_CR2_RXNEIE);
}


u8 MCAL_SPI_GetFlagStatus(SPI_RegDef_t *pSPIx, u8 StatusFlagName)
{

	if(pSPIx->SR & StatusFlagName)
	{
		return SET;
	}

	return RESET;
}

u8 MCAL_SPI_GetInterruptStatus(SPI_RegDef_t *pPSIx,u8 IntSourceName)
{
	if(pPSIx->CR2 & 1<<IntSourceName)
	{
		return ENABLE;
	}

	return DISABLE;
}

void MCAL_SPI_ClearOVFLag(SPI_RegDef_t *pSPIx)
{
	u8 temp;
	temp = pSPIx->DR;
	temp = pSPIx->SR;
	(void)temp;
}

