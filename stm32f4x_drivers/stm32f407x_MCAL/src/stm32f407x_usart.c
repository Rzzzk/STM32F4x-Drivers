/**
 ******************************************************************************
 ******************************************************************************
 * @file           : stm32f407x_usart.c
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
#include "stm32f407x_usart.h"
#include "stm32f4xxx_rcc.h"

void MCAL_USART_Enable(USART_RegDef_t *pUSARTx)
{
	SET_BIT(pUSARTx->CR1,MCAL_USART_CR1_UE);
}

void MCAL_USART_Disable(USART_RegDef_t *pUSARTx)
{
	CLR_BIT(pUSARTx->CR1 ,MCAL_USART_CR1_UE);
}

void MCAL_USART_EnableRxOnly(USART_RegDef_t *pUSARTx)
{
	SET_BIT(pUSARTx->CR1,MCAL_USART_CR1_RE);
	CLR_BIT(pUSARTx->CR1,MCAL_USART_CR1_TE);
}

void MCAL_USART_EnableTxOnly(USART_RegDef_t *pUSARTx)
{
	CLR_BIT(pUSARTx->CR1,MCAL_USART_CR1_RE);
	SET_BIT(pUSARTx->CR1,MCAL_USART_CR1_TE);
}

void MCAL_USART_EnableRxTx(USART_RegDef_t *pUSARTx)
{
	SET_BIT(pUSARTx->CR1,MCAL_USART_CR1_RE);
	SET_BIT(pUSARTx->CR1,MCAL_USART_CR1_TE);
}

void MCAL_USART_SetWordLen8Bit(USART_RegDef_t *pUSARTx)
{
	CLR_BIT(pUSARTx->CR1,MCAL_USART_CR1_M);
}

void MCAL_USART_SetWordLen9Bit(USART_RegDef_t *pUSARTx)
{
	SET_BIT(pUSARTx->CR1,MCAL_USART_CR1_M);
}

void MCAL_USART_EnableOddParity(USART_RegDef_t *pUSARTx)
{
	SET_BIT(pUSARTx->CR1,MCAL_USART_CR1_PCE);
	CLR_BIT(pUSARTx->CR1,MCAL_USART_CR1_PS);
}

void MCAL_USART_EnableEvenParity(USART_RegDef_t *pUSARTx)
{
	SET_BIT(pUSARTx->CR1,MCAL_USART_CR1_PCE);
	SET_BIT(pUSARTx->CR1,MCAL_USART_CR1_PS);
}

void MCAL_USART_DisableParity(USART_RegDef_t *pUSARTx)
{
	CLR_BIT(pUSARTx->CR1,MCAL_USART_CR1_PCE);
	CLR_BIT(pUSARTx->CR1,MCAL_USART_CR1_PS);

}

void MCAL_USART_SetStopConfig(USART_RegDef_t *pUSARTx,u8 StopBitConfig)
{
	if(StopBitConfig < MCAL_USART_STOPBITS_1_5)
	{
		pUSARTx->CR2 |= StopBitConfig << MCAL_USART_CR2_STOP;
	}

}
/*
 *
 *
 * interrupt control
 *
 *
 */
void MCAL_USART_EnableTXEI(USART_RegDef_t *pUSARTx)
{
	SET_BIT(pUSARTx->CR1,MCAL_USART_CR1_TXEIE);
}

void MCAL_USART_DisableTXEI(USART_RegDef_t *pUSARTx)
{
	CLR_BIT(pUSARTx->CR1,MCAL_USART_CR1_TXEIE);
}

u8 MCAL_USART_ReadTXEI(USART_RegDef_t *pUSARTx)
{
	return GET_BIT(pUSARTx->CR1,MCAL_USART_CR1_TXEIE);
}

void MCAL_USART_EnableTCI(USART_RegDef_t *pUSARTx)
{
	SET_BIT(pUSARTx->CR1,MCAL_USART_CR1_TCIE);
}

void MCAL_USART_DisableTCI(USART_RegDef_t *pUSARTx)
{
	CLR_BIT(pUSARTx->CR1,MCAL_USART_CR1_TCIE);
}

u8 MCAL_USART_ReadTCI(USART_RegDef_t *pUSARTx)
{
	return GET_BIT(pUSARTx->CR1,MCAL_USART_CR1_TCIE);
}

void MCAL_USART_EnableRXNI(USART_RegDef_t *pUSARTx)
{
	SET_BIT(pUSARTx->CR1,MCAL_USART_CR1_RXNEIE);
}

void MCAL_USART_DisableRXNI(USART_RegDef_t *pUSARTx)
{
	CLR_BIT(pUSARTx->CR1,MCAL_USART_CR1_RXNEIE);
}


u8 MCAL_USART_ReadRXNI(USART_RegDef_t *pUSARTx)
{
	return GET_BIT(pUSARTx->CR1,MCAL_USART_CR1_RXNEIE);
}



/*
 * HW flow control
 */
void MCAL_USART_EnableCTSFlowControl(USART_RegDef_t *pUSARTx)
{
	SET_BIT(pUSARTx->CR3,MCAL_USART_CR3_CTSE);
}

void MCAL_USART_DisableCTSFlowControl(USART_RegDef_t *pUSARTx)
{
	CLR_BIT(pUSARTx->CR3,MCAL_USART_CR3_CTSE);
}


void MCAL_USART_EnableRTSFlowControl(USART_RegDef_t *pUSARTx)
{
	SET_BIT(pUSARTx->CR3,MCAL_USART_CR3_RTSE);
}

void MCAL_USART_DisableRTSFlowControl(USART_RegDef_t *pUSARTx)
{
	CLR_BIT(pUSARTx->CR3,MCAL_USART_CR3_RTSE);
}


/*
 * baud rate
 */
void MCAL_USART_SetBaudRateValue(USART_RegDef_t *pUSARTx, u32 BaudRate)
{

	//Variable to hold the APB clock
	u32 PCLKx;

	u32 usartdiv;

	//variables to hold Mantissa and Fraction values
	u32 M_part,F_part;

	u32 tempreg=0;

	//Get the value of APB bus clock in to the variable PCLKx
	if(pUSARTx == USART1 || pUSARTx == USART6)
	{
		//USART1 and USART6 are hanging on APB2 bus
		RCC_enuGetAPB1Value(&PCLKx);
	}
	else
	{
		RCC_enuGetAPB1Value(&PCLKx);
	}


	//Check for OVER8 configuration bit
	if(pUSARTx->CR1 & (1 << MCAL_USART_CR1_OVER8))
	{
		//OVER8 = 1 , over sampling by 8
		usartdiv = ((25 * PCLKx) / (2 *BaudRate));
	}
	else
	{
		//over sampling by 16
		usartdiv = ((25 * PCLKx) / (4 *BaudRate));
	}

	//Calculate the Mantissa part
	M_part = usartdiv/100;

	//Place the Mantissa part in appropriate bit position . refer USART_BRR
	tempreg |= M_part << 4;

	//Extract the fraction part
	F_part = (usartdiv - (M_part * 100));

	//Calculate the final fractional
	if(pUSARTx->CR1 & ( 1 << MCAL_USART_CR1_OVER8))
	{
		//OVER8 = 1 , over sampling by 8
		F_part = ((( F_part * 8)+ 50) / 100)& ((u8)0x07);

	}else
	{
		//over sampling by 16
		F_part = ((( F_part * 16)+ 50) / 100) & ((u8)0x0F);

	}

	//Place the fractional part in appropriate bit position . refer USART_BRR
	tempreg |= F_part;

	//copy the value of tempreg in to BRR register
	pUSARTx->BRR = tempreg;

}

u8 MCAL_USART_GetFlagStatus(USART_RegDef_t *pUSARTx, u8 StatusFlagName)
{
    if(pUSARTx->SR & StatusFlagName)
    {
    	return SET;
    }

   return RESET;
}


void MCAL_USART_ClearFlag(USART_RegDef_t *pUSARTx, u8 StatusFlagName)
{
	pUSARTx->SR &=~ StatusFlagName;
}


void MCAL_USART_WriteData(USART_RegDef_t *pUSARTx, u16 Data)
{
	pUSARTx->DR = Data;
}

u16 MCAL_USART_ReadData(USART_RegDef_t *pUSARTx)
{
	return pUSARTx->DR;
}
