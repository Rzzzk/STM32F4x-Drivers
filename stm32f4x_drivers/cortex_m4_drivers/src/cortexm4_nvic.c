/**
 ******************************************************************************
 ******************************************************************************
 * @file           : cortexm4_nvic.c
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

#include "cortexm4_nvic.h"
#include "cortex_m4.h"


ES_t SCB_enuInit(SCB_PriGro_t Copy_enuPriorityGroupingField)
{
	ES_t Local_enuErrorState = ES_NOT_OK;

	Local_enuErrorState = MCAL_SCB_ConfigPriorityGrouping(Copy_enuPriorityGroupingField);

	return Local_enuErrorState;
}



ES_t NVIC_enuInitIRQn(NVIC_Handle_t *Copy_pstrNVICHandle)
{
	ES_t Local_enuErrorState = ES_NOT_OK;

	Local_enuErrorState = MCAL_NVIC_SetPriorityIRQn(Copy_pstrNVICHandle->IRQn,
			Copy_pstrNVICHandle->NVIC_Confg.GroupPriority,
			Copy_pstrNVICHandle->NVIC_Confg.SubPriority);

	Local_enuErrorState = MCAL_NVIC_EnableIRQn(Copy_pstrNVICHandle->IRQn);

	if(Copy_pstrNVICHandle->NVIC_Confg.PendingFlag == NVIC_PendFlagIsHigh)
	{
		Local_enuErrorState = MCAL_NVIC_SetPendingIRQn(Copy_pstrNVICHandle->IRQn);
	}

	return Local_enuErrorState;
}



ES_t NVIC_enuEnableIRQn(NVIC_IRQ_t Copy_enuIRQn)
{
	ES_t Local_enuErrorState = ES_NOT_OK;

	Local_enuErrorState = MCAL_NVIC_EnableIRQn(Copy_enuIRQn);

	return Local_enuErrorState;
}

ES_t NVIC_enuDisableIRQn(NVIC_IRQ_t Copy_enuIRQn)
{
	ES_t Local_enuErrorState = ES_NOT_OK;

	Local_enuErrorState = MCAL_NVIC_DisableIRQn(Copy_enuIRQn);

	return Local_enuErrorState;
}

ES_t NVIC_enuGetEnableIRQn(NVIC_IRQ_t Copy_enuIRQn,u8 *Copy_pu8IRQnEnOrDi)
{
	ES_t Local_enuErrorState = ES_NOT_OK;

	Local_enuErrorState = MCAL_NVIC_GetEnableIRQn(Copy_enuIRQn, Copy_pu8IRQnEnOrDi);

	return Local_enuErrorState;
}


ES_t NVIC_enuSetPendingIRQn(NVIC_IRQ_t Copy_enuIRQn)
{
	ES_t Local_enuErrorState = ES_NOT_OK;

	Local_enuErrorState = MCAL_NVIC_SetPendingIRQn(Copy_enuIRQn);

	return Local_enuErrorState;
}

ES_t NVIC_enuClearPendingIRQn(NVIC_IRQ_t Copy_enuIRQn)
{
	ES_t Local_enuErrorState = ES_NOT_OK;

	Local_enuErrorState = MCAL_NVIC_ClearPendingIRQn(Copy_enuIRQn);

	return Local_enuErrorState;
}


ES_t NVIC_enuGetPendingIRQn(NVIC_IRQ_t Copy_enuIRQn,NVIC_PenFlage_t *Copy_penuIRQnPend)
{
	ES_t Local_enuErrorState = ES_NOT_OK;

	Local_enuErrorState = MCAL_NVIC_GetPendingIRQn(Copy_enuIRQn, Copy_penuIRQnPend);

	return Local_enuErrorState;
}



ES_t NVIC_enuGetActiveIRQn(NVIC_IRQ_t Copy_enuIRQn,NVIC_ActvFlage_t *Copy_penuIRQnAct)
{
	ES_t Local_enuErrorState = ES_NOT_OK;

	Local_enuErrorState = MCAL_NVIC_GetActiveIRQn(Copy_enuIRQn, Copy_penuIRQnAct);

	return Local_enuErrorState;
}


ES_t NVIC_enuSetPriorityIRQn(NVIC_IRQ_t Copy_enuIRQn,u8 Copy_u8GrPri,u8 Copy_u8SubPri)
{
	ES_t Local_enuErrorState = ES_NOT_OK;

	Local_enuErrorState = MCAL_NVIC_SetPriorityIRQn(Copy_enuIRQn, Copy_u8GrPri, Copy_u8SubPri);

	return Local_enuErrorState;
}


