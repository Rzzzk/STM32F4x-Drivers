/**
 ******************************************************************************
 ******************************************************************************
 * @file           : stm32fxxxx_gpio_exti.c
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

#include "stm32f407x_gpio_exti.h"
#include "stm32f4xxx_gpio_exti.h"

/*
 * Init and De-init
 */
ES_t GPIO_enuInit(GPIO_Handle_t *Copy_pstrGPIOHandle)
{
	ES_t Local_enuErrSt = ES_NOT_OK;

	GPIO_RegDef_t *Local_pstrGPIOx = NULL;


	/*
	 * 1. select the base address
	 */
	MCAL_GPIO_SelectPort(Copy_pstrGPIOHandle->GPIO_Port,&Local_pstrGPIOx);

	/*
	 * 2. Configure the mode
	 */
	if(Copy_pstrGPIOHandle->GPIO_Config.GPIO_PinMode <= GPIO_Mode_inputAnal)
	{

		/*Non-Interrupt mode*/

		// alternative function mode
		if (Copy_pstrGPIOHandle->GPIO_Config.GPIO_PinMode == GPIO_Mode_altFun)
		{
			Local_enuErrSt = MCAL_GPIO_SetAltFuncMode(Local_pstrGPIOx,
				Copy_pstrGPIOHandle->GPIO_Config.GPIO_PinNumber,
				Copy_pstrGPIOHandle->GPIO_Config.GPIO_PinAltFunMode);
		}


		// normal modes
		Local_enuErrSt = MCAL_GPIO_SetPinMode(Local_pstrGPIOx,
				Copy_pstrGPIOHandle->GPIO_Config.GPIO_PinNumber,
				Copy_pstrGPIOHandle->GPIO_Config.GPIO_PinMode);

	}
	else
	{
		/*Interrupt mode*/

		//Configure the edge trigger
		Local_enuErrSt = MCAL_EXTI_SetEdgeTrig(Copy_pstrGPIOHandle->GPIO_Config.GPIO_PinNumber,
				Copy_pstrGPIOHandle->GPIO_Config.GPIO_PinMode);

		// Configure the GPIO port selection in SYSCFG_EXTICR
		Local_enuErrSt = MCAL_SYSCFG_SellectEXTIChannel(Copy_pstrGPIOHandle->GPIO_Port,Copy_pstrGPIOHandle->GPIO_Config.GPIO_PinNumber);

		// Set Callback function
		Local_enuErrSt = MCAL_EXTI_SetCallBack(Copy_pstrGPIOHandle->GPIO_Config.GPIO_PinNumber,
				Copy_pstrGPIOHandle->GPIO_Config.EXTI_pfCallBackFunc);

		// Enable the EXTI line
		Local_enuErrSt = MCAL_EXTI_EnableLine(Copy_pstrGPIOHandle->GPIO_Config.GPIO_PinNumber);
	}

	/*
	 * 3. Speed selection
	 */
	Local_enuErrSt = MCAL_GPIO_SelectSpeed(Local_pstrGPIOx,
			Copy_pstrGPIOHandle->GPIO_Config.GPIO_PinNumber,
			Copy_pstrGPIOHandle->GPIO_Config.GPIO_PinSpeed);


	/*
	 *4. pull up/ pull down
	 */
	Local_enuErrSt = MCAL_GPIO_SetPullUpPullDown(Local_pstrGPIOx,
			Copy_pstrGPIOHandle->GPIO_Config.GPIO_PinNumber,
			Copy_pstrGPIOHandle->GPIO_Config.GPIO_PinPuPdControl);


	/*
	 *5. output type
	 */
	Local_enuErrSt = MCAL_GPIO_SelectPinOutputType(Local_pstrGPIOx,
			Copy_pstrGPIOHandle->GPIO_Config.GPIO_PinNumber,
			Copy_pstrGPIOHandle->GPIO_Config.GPIO_PinOPType);


	return Local_enuErrSt;

}

/*
 * Data read and write
 */
ES_t GPIO_enuReadFromInputPin(GPIO_Port_t Copy_enuGPIOPort, GPIO_Pin_t Copy_enuGPIOPin, GPIO_PinState_t *Copy_pu8State)
{
	ES_t Local_enuErrSt = ES_NOT_OK;

	GPIO_RegDef_t *Local_pstrGPIOx = NULL;

	MCAL_GPIO_SelectPort(Copy_enuGPIOPort,&Local_pstrGPIOx);
	Local_enuErrSt = MCAL_GPIO_ReadPin(Local_pstrGPIOx, Copy_enuGPIOPin, Copy_pu8State);

	return Local_enuErrSt;
}


ES_t GPIO_enuWriteToOutputPin(GPIO_Port_t Copy_enuGPIOPort, GPIO_Pin_t Copy_enuGPIOPin, GPIO_PinState_t Copy_enuGPIOPinState)
{
	ES_t Local_enuErrSt = ES_NOT_OK;

	GPIO_RegDef_t *Local_pstrGPIOx = NULL;

	MCAL_GPIO_SelectPort(Copy_enuGPIOPort,&Local_pstrGPIOx);
	Local_enuErrSt = MCAL_GPIO_WritePin(Local_pstrGPIOx,Copy_enuGPIOPin,Copy_enuGPIOPinState);

	return Local_enuErrSt;
}



ES_t GPIO_enuToggleOutputPin(GPIO_Port_t Copy_enuGPIOPort, GPIO_Pin_t Copy_enuGPIOPin)
{
	ES_t Local_enuErrSt = ES_NOT_OK;

	GPIO_RegDef_t *Local_pstrGPIOx = NULL;

	MCAL_GPIO_SelectPort(Copy_enuGPIOPort,&Local_pstrGPIOx);
	Local_enuErrSt = MCAL_GPIO_TogglePin(Local_pstrGPIOx, Copy_enuGPIOPin);
	Local_pstrGPIOx = GPIOH;
	return Local_enuErrSt;
}

