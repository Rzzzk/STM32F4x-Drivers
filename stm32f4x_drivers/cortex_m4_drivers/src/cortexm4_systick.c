/**
 ******************************************************************************
 ******************************************************************************
 * @file           : cortexm4_systick.c
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

#include "cortexm4_systick.h"
#include "cortex_m4.h"


ES_t SysTick_enuInit(SysTic_ClkSrc_t Copy_enuClockSource)
{
	ES_t Local_enuErrorState = ES_NOT_OK;

	if (Copy_enuClockSource == SysTick_ProcessorClock)
	{
		MCAL_SysTick_SelectCPUClockSource();
		Local_enuErrorState = ES_OK;
	}
	else if(Copy_enuClockSource == SysTick_ExternalClock)
	{
		MCAL_SysTick_SelectExternalClockSource();
		Local_enuErrorState = ES_OK;
	}

	return Local_enuErrorState;
}




ES_t SysTick_enuStart(SysTick_Handle_t *Copy_pstrSysTickHandle)
{
	ES_t Local_enuErrorState = ES_NOT_OK;

	if(Copy_pstrSysTickHandle->Type == SysTick_BusyWait)
	{
		MCAL_SysTick_SetReloadValue(Copy_pstrSysTickHandle->cofig.LoadValue - 1UL);

		MCAL_SysTick_ClearTheCounter();

		MCAL_SysTick_EnableCounter();

		MCAL_SysTick_BaisyWait(Copy_pstrSysTickHandle->cofig.BasyWaitTimeOut);

		MCAL_SysTick_DisableCounter();
	}
	else if(Copy_pstrSysTickHandle->Type == SysTick_SingleTick)
	{

		MCAL_SysTick_SetReloadValue(Copy_pstrSysTickHandle->cofig.LoadValue - 1UL);

		MCAL_SysTick_ClearTheCounter();

		MCAL_SysTick_SingleTick(Copy_pstrSysTickHandle->cofig.CallBackFun);

		MCAL_SysTick_EnableExceptionRequest();

		MCAL_SysTick_EnableCounter();

	}
	else if(Copy_pstrSysTickHandle->Type == SysTick_PeriodicTick)
	{

		MCAL_SysTick_SetReloadValue(Copy_pstrSysTickHandle->cofig.LoadValue - 1UL);

		MCAL_SysTick_ClearTheCounter();

		MCAL_SysTick_PeriodicTick(Copy_pstrSysTickHandle->cofig.CallBackFun);

		MCAL_SysTick_EnableExceptionRequest();

		MCAL_SysTick_EnableCounter();

	}

	return Local_enuErrorState;
}












