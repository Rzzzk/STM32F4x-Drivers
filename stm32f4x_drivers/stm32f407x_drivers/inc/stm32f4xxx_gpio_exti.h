/**
 ******************************************************************************
 ******************************************************************************
 * @file           : stm32fxxxx_gpio_exti.h
 * @author         : Rezk Ahmed
 * @Layer          : ECU / Board
 * @brief          : For control across the entire STM32F4x family,
 *                   this layer is not aware of specific hardware information
 *                   such as register addresses.
 *                   It utilizes all peripherals through MCAL APIs.
 ******************************************************************************
 ******************************************************************************
 */

#ifndef STM32F407X_DRIVERS_INC_STM32F4XXX_GPIO_EXTI_H_
#define STM32F407X_DRIVERS_INC_STM32F4XXX_GPIO_EXTI_H_

typedef enum
{
	GPIO_PORTA,
	GPIO_PORTB,
	GPIO_PORTC,
	GPIO_PORTD,
	GPIO_PORTE,
	GPIO_PORTF,
	GPIO_PORTG,
	GPIO_PORTH
}GPIO_Port_t;

typedef enum
{
	GPIO_PIN0=0,
	GPIO_PIN1,
	GPIO_PIN2,
	GPIO_PIN3,
	GPIO_PIN4,
	GPIO_PIN5,
	GPIO_PIN6,
	GPIO_PIN7,
	GPIO_PIN8,
	GPIO_PIN9,
	GPIO_PIN10,
	GPIO_PIN11,
	GPIO_PIN12,
	GPIO_PIN13,
	GPIO_PIN14,
	GPIO_PIN15

}GPIO_Pin_t;


typedef enum
{
	GPIO_LOW=0,
	GPIO_HIGH
}GPIO_PinState_t;

typedef enum
{
	GPIO_Mode_input=0,
	GPIO_Mode_output,
	GPIO_Mode_altFun,
	GPIO_Mode_inputAnal,
	GPIO_Mode_EXTI_FT,
	GPIO_Mode_EXTI_RT,
	GPIO_Mode_EXTI_RFT

}GPIO_Mode_t;

typedef enum
{
	GPIO_Speed_Low=0,
	GPIO_Speed_Med,
	GPIO_Speed_Fast,
	GPIO_Speed_High
}GPIO_Speed_t;

typedef enum
{
	GPIO_Float=0,
	GPIO_PullUp,
	GPIO_PullDown
}GPIO_PuPdCtrl_t;

typedef enum
{
	GPIO_Output_PP=0,
	GPIO_Output_OD
}GPIO_OutputType_t;


typedef struct
{
	GPIO_Pin_t        GPIO_PinNumber;
	GPIO_Mode_t       GPIO_PinMode;
	GPIO_Speed_t      GPIO_PinSpeed;
	GPIO_PuPdCtrl_t   GPIO_PinPuPdControl;
	GPIO_OutputType_t GPIO_PinOPType;
	u8                GPIO_PinAltFunMode;
	void (*EXTI_pfCallBackFunc)(void);
}GPIO_PinConfig_t;


typedef struct
{
	GPIO_Port_t GPIO_Port;
	GPIO_PinConfig_t GPIO_Config;
}GPIO_Handle_t;


/*
 * Init and De-init
 */
ES_t GPIO_enuInit(GPIO_Handle_t *Copy_pstrGPIOHandle);


/*
 * Data read and write
 */
ES_t GPIO_enuReadFromInputPin(GPIO_Port_t Copy_enuGPIOPort,GPIO_Pin_t Copy_enuGPIOPin,GPIO_PinState_t *Copy_pu8State);

ES_t GPIO_enuWriteToOutputPin(GPIO_Port_t Copy_enuGPIOPort,GPIO_Pin_t Copy_enuGPIOPin,GPIO_PinState_t Copy_pu8State);

ES_t GPIO_enuToggleOutputPin(GPIO_Port_t Copy_enuGPIOPort,GPIO_Pin_t Copy_enuGPIOPin);



#endif /* STM32F407X_DRIVERS_INC_STM32F4XXX_GPIO_EXTI_H_ */
