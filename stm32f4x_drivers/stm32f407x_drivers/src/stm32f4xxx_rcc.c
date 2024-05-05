/**
 ******************************************************************************
 ******************************************************************************
 * @file           : stm32fxxxx_rcc.c
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

#include "stm32f407x_rcc.h"
#include "stm32f4xxx_rcc.h"

ES_t RCC_enuInitSystemClk(RCC_Handler_t *Copy_pstrRCCConfig)
{
	ES_t Local_enuErrSt = ES_NOT_OK;

	/**************  set pre-scalers first   **************************/
	MCAL_RCC_SetAHBPrescaller(Copy_pstrRCCConfig->RCC_AHBPrescaler);
	MCAL_RCC_SetAPB1Prescaller(Copy_pstrRCCConfig->RCC_APB1Prescaler);
	MCAL_RCC_SetAPB2Prescaller(Copy_pstrRCCConfig->RCC_APB2Prescaler);

	/*************  select the system clock source  *******************/
	Local_enuErrSt = MCAL_RCC_SelectSystemClockSource(Copy_pstrRCCConfig->RCC_SysClkSource);

	return Local_enuErrSt;
}

ES_t RCC_enuAHB1PeriphClkCtrl(RCC_AHB1Periph_t Copy_enuPerphNum, u8 Copy_u8EnOrDi)
{
	ES_t Local_enuErrSt = ES_NOT_OK;

	if(Copy_u8EnOrDi == ENABLE)
	{
		Local_enuErrSt = MCAL_RCC_AHB1PeriphClockEnable(Copy_enuPerphNum);

	}
	else if(Copy_u8EnOrDi == DISABLE)
	{
		Local_enuErrSt = MCAL_RCC_AHB1PeriphClockDisable(Copy_enuPerphNum);
	}

	return Local_enuErrSt;
}



ES_t RCC_enuAHB2PeriphClkCtrl(RCC_AHB2Periph_t Copy_enuPerphNum, u8 Copy_u8EnOrDi)
{
	ES_t Local_enuErrSt = ES_NOT_OK;

	if(Copy_u8EnOrDi == ENABLE)
	{
		Local_enuErrSt = MCAL_RCC_AHB2PeriphClockEnable(Copy_enuPerphNum);
	}
	else if(Copy_u8EnOrDi == DISABLE)
	{
		Local_enuErrSt = MCAL_RCC_AHB2PeriphClockDisable(Copy_enuPerphNum);
	}
	return Local_enuErrSt;
}



ES_t RCC_enuAPB1PeriphClkCtrl(RCC_APB1Periph_t Copy_enuPerphNum, u8 Copy_u8EnOrDi)
{
	ES_t Local_enuErrSt = ES_NOT_OK;

	if(Copy_u8EnOrDi == ENABLE)
	{
		Local_enuErrSt = MCAL_RCC_APB1PeriphClockEnable(Copy_enuPerphNum);
	}
	else if(Copy_u8EnOrDi == DISABLE)
	{
		Local_enuErrSt = MCAL_RCC_APB1PeriphClockDisable(Copy_enuPerphNum);
	}
	return Local_enuErrSt;
}



ES_t RCC_enuAPB2PeriphClkCtrl(RCC_APB2Periph_t Copy_enuPerphNum, u8 Copy_u8EnOrDi)
{
	ES_t Local_enuErrSt = ES_NOT_OK;


	if(Copy_u8EnOrDi == ENABLE)
	{
		Local_enuErrSt = MCAL_RCC_APB2PeriphClockEnable(Copy_enuPerphNum);
	}
	else if(Copy_u8EnOrDi == DISABLE)
	{
		Local_enuErrSt = MCAL_RCC_APB2PeriphClockDisable(Copy_enuPerphNum);
	}

	return Local_enuErrSt;
}


/*******************************************************************************************/


ES_t RCC_enuAHB1PeriphReset(RCC_AHB1Periph_t Copy_enuPerphNum)
{
	ES_t Local_enuErrSt = ES_NOT_OK;

	Local_enuErrSt = MCAL_RCC_AHB1PeriphReset(Copy_enuPerphNum);

	return Local_enuErrSt;
}

ES_t RCC_enuAHB2PeriphReset(RCC_AHB2Periph_t Copy_enuPerphNum)
{
	ES_t Local_enuErrSt = ES_NOT_OK;

	Local_enuErrSt = MCAL_RCC_AHB2PeriphReset(Copy_enuPerphNum);

	return Local_enuErrSt;
}


ES_t RCC_enuAPB1PeriphReset(RCC_APB1Periph_t Copy_enuPerphNum)
{
	ES_t Local_enuErrSt = ES_NOT_OK;

	Local_enuErrSt = MCAL_RCC_APB1PeriphReset(Copy_enuPerphNum);

	return Local_enuErrSt;
}


ES_t RCC_enuAPB2PeriphReset(RCC_APB2Periph_t Copy_enuPerphNum)
{
	ES_t Local_enuErrSt = ES_NOT_OK;

	Local_enuErrSt = MCAL_RCC_APB2PeriphReset(Copy_enuPerphNum);

	return Local_enuErrSt;
}


/**********************************************************************************************/


ES_t RCC_enuGetAPB1Value(u32 *Copy_pu8APB2Value)
{
	ES_t Local_enuErrSt = ES_NOT_OK;

	Local_enuErrSt = MCAL_RCC_GetAPB1Value(Copy_pu8APB2Value);

	return Local_enuErrSt;
}


ES_t RCC_enuGetAPB2Value(u32 *Copy_pu8APB2Value)
{
	ES_t Local_enuErrSt = ES_NOT_OK;

	Local_enuErrSt = MCAL_RCC_GetAPB2Value(Copy_pu8APB2Value);

	return Local_enuErrSt;
}

ES_t RCC_enuGetSysClkValue(u32 *Copy_pu32SysClkValue)
{
	ES_t Local_enuErrSt = ES_NOT_OK;

	Local_enuErrSt = MCAL_RCC_GetSysClkValue(Copy_pu32SysClkValue);

	return Local_enuErrSt;
}


ES_t RCC_enuGetSysClkType(RCC_SysClk_t *Copy_penuSysClk)
{
	ES_t Local_enuErrSt = ES_NOT_OK;

	Local_enuErrSt = MCAL_RCC_GetSysClkType(Copy_penuSysClk);

	return Local_enuErrSt;
}

