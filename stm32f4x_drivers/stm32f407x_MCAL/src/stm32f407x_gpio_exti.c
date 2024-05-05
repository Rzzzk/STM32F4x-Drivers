/**
 ******************************************************************************
 ******************************************************************************
 * @file           : stm32f407x_gpio_exti.c
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
#include "stm32f407x_gpio_exti.h"

void (*EXTI_CallBack[16])(void) = {NULL};

ES_t MCAL_GPIO_SelectPort(u8 Copy_enuGPIOPort,GPIO_RegDef_t** GPIO_BaseAddr)
{
	ES_t errorState = ES_NOT_OK;

	switch(Copy_enuGPIOPort)
	{
	case MCAL_GPIO_PORTA : *GPIO_BaseAddr = GPIOA; errorState = ES_OK; break;
	case MCAL_GPIO_PORTB : *GPIO_BaseAddr = GPIOB; errorState = ES_OK; break;
	case MCAL_GPIO_PORTC : *GPIO_BaseAddr = GPIOC; errorState = ES_OK; break;
	case MCAL_GPIO_PORTD : *GPIO_BaseAddr = GPIOD; errorState = ES_OK; break;
	case MCAL_GPIO_PORTE : *GPIO_BaseAddr = GPIOE; errorState = ES_OK; break;
	case MCAL_GPIO_PORTF : *GPIO_BaseAddr = GPIOF; errorState = ES_OK; break;
	case MCAL_GPIO_PORTG : *GPIO_BaseAddr = GPIOG; errorState = ES_OK; break;
	case MCAL_GPIO_PORTH : *GPIO_BaseAddr = GPIOH; errorState = ES_OK; break;
	}
	return errorState;
}


ES_t MCAL_GPIO_SetPinMode(GPIO_RegDef_t* GPIO_BaseAddr,u8 PinNum,u8 Mode)
{
	ES_t errorState = ES_NOT_OK;

	if(Mode <= MCAL_GPIO_MODE_INPUT_ANALOG)
	{
		GPIO_BaseAddr->MODER &= ~(0x3 << 2 * PinNum);
		GPIO_BaseAddr->MODER |= (Mode<< 2 * PinNum);
		errorState = ES_OK;
	}
	return errorState;
}


ES_t MCAL_GPIO_SelectSpeed(GPIO_RegDef_t* GPIO_BaseAddr,u8 PinNum,u8 Speed)
{
	ES_t errorState = ES_NOT_OK;

	GPIO_BaseAddr->OSPEEDR &= ~(0x3 << 2 *PinNum);
	GPIO_BaseAddr->OSPEEDR |= (Speed << 2 * PinNum);;

	return errorState;
}



ES_t MCAL_GPIO_SetPullUpPullDown(GPIO_RegDef_t* GPIO_BaseAddr,u8 PinNum,u8 PuPd)
{
	ES_t errorState = ES_NOT_OK;


	GPIO_BaseAddr->PUPDR &= ~(0x3 << 2 * PinNum);
	GPIO_BaseAddr->PUPDR |= (PuPd << 2 * PinNum);

	errorState = ES_OK;
	return errorState;
}


ES_t MCAL_GPIO_SelectPinOutputType(GPIO_RegDef_t* GPIO_BaseAddr,u8 PinNum,u8 PinOPType)
{
	ES_t errorState = ES_NOT_OK;

	GPIO_BaseAddr->OTYPER &= ~(1<< PinNum);
	GPIO_BaseAddr->OTYPER |= (PinOPType<< PinNum);

	return errorState;
}

ES_t MCAL_GPIO_SetAltFuncMode(GPIO_RegDef_t* GPIO_BaseAddr,u8 PinNum,u8 AltFunMode)
{
	ES_t errorState = ES_NOT_OK;

	// configure the alt function registers.
	u8 Temp1,Temp2;

	Temp1 = PinNum / 8;
	Temp2 = PinNum % 8;

	GPIO_BaseAddr->AFR[Temp1] &= ~(0xF << (4 * Temp2));
	GPIO_BaseAddr->AFR[Temp1] |= (AltFunMode << (4 * Temp2));

	errorState = ES_OK;

	return errorState;
}


ES_t MCAL_GPIO_WritePin(GPIO_RegDef_t *GPIO_BaseAddr, u8 PinNum,u8 Value)
{
	ES_t errorState = ES_NOT_OK;

	GPIO_BaseAddr->ODR &= ~(1 << PinNum);
	GPIO_BaseAddr->ODR |= (Value << PinNum);

	errorState = ES_OK;

	return errorState;
}

ES_t MCAL_GPIO_ReadPin(GPIO_RegDef_t *GPIO_BaseAddr, u8 PinNum,u8 *Value)
{
	ES_t errorState = ES_NOT_OK;

	*Value = GET_BIT(GPIO_BaseAddr->IDR, PinNum);
	errorState = ES_OK;

	return errorState;
}


ES_t MCAL_GPIO_TogglePin(GPIO_RegDef_t *GPIO_BaseAddr, u8 PinNum)
{
	ES_t errorState = ES_NOT_OK;

	TOG_BIT(GPIO_BaseAddr->ODR, PinNum);
	errorState = ES_OK;

	return errorState;
}


/*********************************************/

ES_t MCAL_EXTI_SetEdgeTrig(u8 PinNum,u8 Mode)
{
	ES_t errorState = ES_NOT_OK;
	if (Mode == MCAL_GPIO_MODE_EXTI_FT)
	{
		// 1. configure the FTSR
		SET_BIT(EXTI->FTSR,PinNum);
		// Clear the corresponding RTSR bit
		CLR_BIT(EXTI->RTSR,PinNum);

		errorState = ES_OK;
	}
	else if (Mode == MCAL_GPIO_MODE_EXTI_RT)
	{
		// 1 . configure the RTSR
		SET_BIT(EXTI->RTSR,PinNum);
		// Clear the corresponding FTSR bit
		CLR_BIT(EXTI->FTSR,PinNum);

		errorState = ES_OK;
	}
	else if (Mode == MCAL_GPIO_MODE_EXTI_RFT)
	{
		// 1. configure both FTSR and RTSR
		SET_BIT(EXTI->RTSR,PinNum);
		SET_BIT(EXTI->FTSR,PinNum);

		errorState = ES_OK;
	}

	return errorState;
}




ES_t MCAL_SYSCFG_SellectEXTIChannel(u8 GPIO_Port,u8 PinNum)
{
	ES_t errorState = ES_NOT_OK;

	u8 RNTemp   = PinNum / 4;
	u8 IndxTemp = PinNum % 4;

	SYSCFG->EXTICR[RNTemp] = GPIO_Port << (IndxTemp * 4);

	errorState = ES_OK;

	return errorState;
}


ES_t MCAL_EXTI_EnableLine(u8 PinNum)
{
	ES_t errorState = ES_NOT_OK;

	SET_BIT(EXTI->IMR,PinNum);

	errorState = ES_OK;

	return errorState;
}


ES_t MCAL_EXTI_SetCallBack(u8 Line, void (*callBackFun)(void))
{
	ES_t errorState = ES_NOT_OK;

	if(Line <= 16)
	{
		EXTI_CallBack[Line] = callBackFun;
		errorState = ES_OK;
	}

	return errorState;
}



void EXTI0_IRQHandler(void)
{
	if (EXTI->PR & (1 << 0))
	{


		if (EXTI_CallBack[0] != NULL) // then call the callback function
		{
			EXTI_CallBack[0]();
		}

		EXTI->PR |= (1 << 0);
	}
}

void EXTI1_IRQHandler(void)
{
	if (EXTI->PR & (1 << 1))
	{

		if (EXTI_CallBack[1] != NULL) // then call the callback function
		{
			EXTI_CallBack[1]();
		}

		EXTI->PR |= (1 << 1);
	}
}
void EXTI2_IRQHandler(void)
{
	if (EXTI->PR & (1 << 2))
	{

		if (EXTI_CallBack[2] != NULL) // then call the callback function
		{
			EXTI_CallBack[2]();
		}
		EXTI->PR |= (1 << 2);
	}
}
void EXTI3_IRQHandler(void)
{
	if (EXTI->PR & (1 << 3))
	{

		if (EXTI_CallBack[3] != NULL) // then call the callback function
		{
			EXTI_CallBack[3]();
		}
		EXTI->PR |= (1 << 3);
	}
}
void EXTI4_IRQHandler(void)
{
	if (EXTI->PR & (1 << 4))
	{

		if (EXTI_CallBack[4] != NULL) // then call the callback function
		{
			EXTI_CallBack[4]();
		}

		EXTI->PR |= (1 << 4);
	}
}

void EXTI9_5_IRQHandler(void)
{

	if (EXTI->PR & (1 << 5))
	{

		if (EXTI_CallBack[5] != NULL) // then call the callback function
		{
			EXTI_CallBack[5]();
		}
		EXTI->PR |= (1 << 5);
	}

	if (EXTI->PR & (1 << 6))
	{

		if (EXTI_CallBack[6] != NULL) // then call the callback function
		{
			EXTI_CallBack[6]();
		}
		EXTI->PR |= (1 << 6);
	}

	if (EXTI->PR & (1 << 7))
	{
		if (EXTI_CallBack[7] != NULL) // then call the callback function
		{
			EXTI_CallBack[7]();
		}
		EXTI->PR |= (1 << 7);
	}

	if (EXTI->PR & (1 << 8))
	{

		if (EXTI_CallBack[8] != NULL) // then call the callback function
		{
			EXTI_CallBack[8]();
		}
		EXTI->PR |= (1 << 8);
	}

	if (EXTI->PR & (1 << 9))
	{

		if (EXTI_CallBack[9] != NULL) // then call the callback function
		{
			EXTI_CallBack[9]();
		}
		EXTI->PR |= (1 << 9);
	}
}

void EXTI15_10_IRQHandler(void)
{
	if (EXTI->PR & (1 << 10))
	{

		if (EXTI_CallBack[10] != NULL) // then call the callback function
		{
			EXTI_CallBack[10]();
		}
		EXTI->PR |= (1 << 10);
	}

	if (EXTI->PR & (1 << 11))
	{

		if (EXTI_CallBack[11] != NULL) // then call the callback function
		{
			EXTI_CallBack[11]();
		}
		EXTI->PR |= (1 << 11);
	}

	if (EXTI->PR & (1 << 12))
	{

		if (EXTI_CallBack[12] != NULL) // then call the callback function
		{
			EXTI_CallBack[12]();
		}
		EXTI->PR |= (1 << 12);
	}

	if (EXTI->PR & (1 << 13))
	{

		if (EXTI_CallBack[13] != NULL) // then call the callback function
		{
			EXTI_CallBack[13]();
		}
		EXTI->PR |= (1 << 13);
	}

	if (EXTI->PR & (1 << 14))
	{
		if (EXTI_CallBack[14] != NULL) // then call the callback function
		{
			EXTI_CallBack[14]();
		}
		EXTI->PR |= (1 << 14);
	}

	if (EXTI->PR & (1 << 15))
	{
		if (EXTI_CallBack[15] != NULL) // then call the callback function
		{
			EXTI_CallBack[15]();
		}
		EXTI->PR |= (1 << 15);
	}
}

