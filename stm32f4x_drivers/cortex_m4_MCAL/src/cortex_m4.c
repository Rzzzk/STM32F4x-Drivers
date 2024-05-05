/**
 ******************************************************************************
 ******************************************************************************
 * @file           : cortex_m4.c
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

#include "cortex_m4.h"

/***********************************************************
 *
 *                     NVIC
 *
 * *********************************************************
 */

u8 SCB_SubPriBits = 0;

ES_t MCAL_SCB_ConfigPriorityGrouping(u32 PriorityGroupingField)
{
	ES_t errorState = ES_NOT_OK;

	switch (PriorityGroupingField)
	{
	case MCAL_NVIC_4_BIT_GROUP_0_BIT_SUB:

		SCB_AIRCR = 0x05FA0300;

		SCB_SubPriBits = 0;

		errorState = ES_OK;
		break;

	case MCAL_NVIC_3_BIT_GROUP_1_BIT_SUB:

		SCB_AIRCR = 0x05FA0400;

		SCB_SubPriBits = 1;

		errorState = ES_OK;
		break;

	case MCAL_NVIC_2_BIT_GROUP_2_BIT_SUB:

		SCB_AIRCR = 0x05FA0500;

		SCB_SubPriBits = 2;

		errorState = ES_OK;
		break;

	case MCAL_NVIC_1_BIT_GROUP_3_BIT_SUB:

		SCB_AIRCR = 0x05FA0600;

		SCB_SubPriBits = 3;

		errorState = ES_OK;
		break;

	case MCAL_NVIC_0_BIT_GROUP_4_BIT_SUB:

		SCB_AIRCR = 0x05FA0700;

		SCB_SubPriBits = 4;

		errorState = ES_OK;
		break;
	}

	return errorState;
}


ES_t MCAL_NVIC_EnableIRQn(u8 IRQn)
{

	ES_t errorState=ES_NOT_OK;

	if(IRQn <= 31 )
	{
		NVIC_ISER0 = (1<<IRQn);
		errorState = ES_OK;
	}
	else if(IRQn <= 59)
	{
		IRQn-=32;
		NVIC_ISER1 = (1<<IRQn);
		errorState = ES_OK;
	}

	return errorState;
}


ES_t MCAL_NVIC_DisableIRQn(u8 IRQn)
{

	ES_t errorState=ES_NOT_OK;

	if(IRQn <= 31 )
	{
		NVIC_ICER0 = (1<<IRQn);
		errorState = ES_OK;
	}
	else if(IRQn <= 59)
	{
		IRQn-=32;
		NVIC_ICER1 = (1<<IRQn);
		errorState = ES_OK;
	}

	return errorState;
}

ES_t MCAL_NVIC_GetEnableIRQn(u8 IRQn,u8 *IRQnEnOrDi)
{
	ES_t errorState=ES_NOT_OK;
	if(IRQn <= 31 )
	{
		*IRQnEnOrDi = GET_BIT(NVIC_ISER0,IRQn);
		errorState = ES_OK;
	}
	else if(IRQn <= 59)
	{
		IRQn-=32;
		*IRQnEnOrDi = GET_BIT(NVIC_ISER1,IRQn);
		errorState = ES_OK;
	}
	return errorState;
}

ES_t MCAL_NVIC_SetPendingIRQn(u8 IRQn)
{
	ES_t errorState=ES_NOT_OK;

	if(IRQn <= 31 )
	{
		NVIC_ISPR0 = (1<<IRQn);
		errorState = ES_OK;
	}
	else if(IRQn <= 59)
	{
		IRQn-=32;
		NVIC_ISPR1 = (1<<IRQn);
		errorState = ES_OK;
	}

	return errorState;
}

ES_t MCAL_NVIC_ClearPendingIRQn(u8 IRQn)
{
	ES_t errorState=ES_NOT_OK;

	if(IRQn <= 31 )
	{
		NVIC_ICPR0 = (1<<IRQn);
		errorState = ES_OK;
	}
	else if(IRQn <= 59)
	{
		IRQn-=32;
		NVIC_ICPR1 = (1<<IRQn);
		errorState = ES_OK;
	}

	return errorState;
}


ES_t MCAL_NVIC_GetPendingIRQn(u8 IRQn,u8 *IRQnPend)
{
	ES_t errorState=ES_NOT_OK;

	if(IRQn <= 31 )
	{
		*IRQnPend = GET_BIT(NVIC_ISPR0,IRQn);
		errorState = ES_OK;
	}
	else if(IRQn <= 59)
	{
		IRQn-=32;
		*IRQnPend = GET_BIT(NVIC_ISPR1,IRQn);
		errorState = ES_OK;
	}

	return errorState;
}


ES_t MCAL_NVIC_GetActiveIRQn(u8 IRQn,u8 *IRQnAct)
{
	ES_t errorState=ES_NOT_OK;

	if(IRQn <= 31 )
	{
		*IRQnAct = GET_BIT(NVIC_IABR0,IRQn);
		errorState = ES_OK;
	}
	else if(IRQn <= 59)
	{
		IRQn-=32;
		*IRQnAct = GET_BIT(NVIC_IABR1,IRQn);
		errorState = ES_OK;
	}

	return errorState;
}

ES_t MCAL_NVIC_SetPriorityIRQn(u8 IRQn,u8 GrPri,u8 SubPri)
{
	ES_t errorState=ES_NOT_OK;

	u8 Pri ;

	Pri = SubPri | (GrPri << SCB_SubPriBits);

	if(IRQn >= 0)
	{
		/* External Interrupt*/
		NVIC_IPR[IRQn] = (Pri << (8 - NO_PR_BITS_IMPLEMENTED));
		errorState = ES_OK;
	}
	else
	{
		/* System Exceptions*/
	}
	return errorState;
}


/***********************************************************
 *
 *                     SysTick
 *
 * *********************************************************
 */


u8 MCAL_SysTick_Type = MCAL_SYSTICK_BUSY_WAIT;

void (*SysTick_pfSingleTickCallBack)(void)   = NULL;
void (*SysTick_pfPeriodicTickCallBack)(void) = NULL;


ES_t MCAL_SysTick_EnableCounter(void)
{
	ES_t errorState=ES_NOT_OK;

	SET_BIT(SysTick->CTRL,SYST_CTRL_ENABLE);
	errorState = ES_OK;

	return errorState;
}
ES_t MCAL_SysTick_DisableCounter(void)
{
	ES_t errorState=ES_NOT_OK;

	CLR_BIT(SysTick->CTRL,SYST_CTRL_ENABLE);
	errorState = ES_OK;

	return errorState;
}

ES_t MCAL_SysTick_EnableExceptionRequest(void)
{
	ES_t errorState=ES_NOT_OK;

	SET_BIT(SysTick->CTRL,SYST_CTRL_TICKINT);
	errorState = ES_OK;

	return errorState;
}

ES_t MCAL_SysTick_DisableExceptionRequest(void)
{
	ES_t errorState=ES_NOT_OK;

	CLR_BIT(SysTick->CTRL,SYST_CTRL_TICKINT);
	errorState = ES_OK;

	return errorState;
}

ES_t MCAL_SysTick_ClearTheCounter(void)
{
	ES_t errorState=ES_NOT_OK;

	SysTick->VAL = 0;
	errorState = ES_OK;

	return errorState;
}

ES_t MCAL_SysTick_SetReloadValue(u32 RelVal)
{
	ES_t errorState=ES_NOT_OK;

	SysTick->LOAD = (RelVal);
	errorState = ES_OK;

	return errorState;
}

ES_t MCAL_SysTick_SelectCPUClockSource(void)
{
	ES_t errorState=ES_NOT_OK;

	SET_BIT(SysTick->CTRL,SYST_CTRL_CLKSOURCE);
	errorState = ES_OK;

	return errorState;
}


ES_t MCAL_SysTick_SelectExternalClockSource(void)
{
	ES_t errorState=ES_NOT_OK;

	CLR_BIT(SysTick->CTRL,SYST_CTRL_CLKSOURCE);
	errorState = ES_OK;

	return errorState;
}



ES_t MCAL_SysTick_BaisyWait(u32 TimeOut)
{
	ES_t errorState=ES_NOT_OK;
	u32 i = 0;

	MCAL_SysTick_Type = MCAL_SYSTICK_BUSY_WAIT;

	while( !((SysTick->CTRL >> SYST_CTRL_COUNTFLAG)) && (i <  TimeOut) )
	{
		i++;
	}

	if(i < TimeOut)
	{
		errorState=ES_OK;
	}

	return errorState;
}


ES_t MCAL_SysTick_SingleTick(void (*CallBackFuc)(void))
{
	ES_t errorState=ES_NOT_OK;

	MCAL_SysTick_Type = MCAL_SYSTICK_SINGLE_TICK;

	SysTick_pfSingleTickCallBack = CallBackFuc;

	return errorState;
}


ES_t MCAL_SysTick_PeriodicTick(void (*CallBackFuc)(void))
{
	ES_t errorState=ES_NOT_OK;

	MCAL_SysTick_Type = MCAL_SYSTICK_PERIODIC_TICK;

	SysTick_pfPeriodicTickCallBack = CallBackFuc;

	return errorState;
}


void SysTick_Handler(void)
{

	if (MCAL_SysTick_Type == MCAL_SYSTICK_SINGLE_TICK)
	{

		MCAL_SysTick_DisableExceptionRequest();

		MCAL_SysTick_SetReloadValue(0);

		MCAL_SysTick_DisableCounter();

		if(SysTick_pfSingleTickCallBack != NULL)
		{
			SysTick_pfSingleTickCallBack();
		}
	}
	else if (MCAL_SysTick_Type == MCAL_SYSTICK_PERIODIC_TICK)
	{
		if( SysTick_pfPeriodicTickCallBack != NULL)
		{
			SysTick_pfPeriodicTickCallBack();
		}

	}
}


