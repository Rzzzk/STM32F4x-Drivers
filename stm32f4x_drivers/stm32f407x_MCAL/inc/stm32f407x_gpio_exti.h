/**
 ******************************************************************************
 ******************************************************************************
 * @file           : stm32f407x_gpio_exti.h
 * @author         : Rezk Ahmed
 * @Layer          : MCAL
 * @brief          : Ensure that all hardware information is gathered and abstracted
 *                   from the drivers layer (ECU or Board layer), and provide higher
 *                   layer APIs with access and control over the peripheral drivers.
 ******************************************************************************
 ******************************************************************************
 */

#ifndef STM32F407X_MCAL_INC_STM32F407X_GPIO_EXTI_H_
#define STM32F407X_MCAL_INC_STM32F407X_GPIO_EXTI_H_


#define PERIPH_BASEADDR 						0x40000000U
#define APB1PERIPH_BASEADDR						PERIPH_BASEADDR
#define APB2PERIPH_BASEADDR						0x40010000U
#define AHB1PERIPH_BASEADDR						0x40020000U
#define AHB2PERIPH_BASEADDR						0x50000000U

#define GPIOA_BASEADDR                   (AHB1PERIPH_BASEADDR + 0x0000)
#define GPIOB_BASEADDR                   (AHB1PERIPH_BASEADDR + 0x0400)
#define GPIOC_BASEADDR 					 (AHB1PERIPH_BASEADDR + 0x0800)
#define GPIOD_BASEADDR 					 (AHB1PERIPH_BASEADDR + 0x0C00)
#define GPIOE_BASEADDR 					 (AHB1PERIPH_BASEADDR + 0x1000)
#define GPIOF_BASEADDR 					 (AHB1PERIPH_BASEADDR + 0x1400)
#define GPIOG_BASEADDR 					 (AHB1PERIPH_BASEADDR + 0x1800)
#define GPIOH_BASEADDR 					 (AHB1PERIPH_BASEADDR + 0x1C00)
#define GPIOI_BASEADDR 					 (AHB1PERIPH_BASEADDR + 0x2000)

#define EXTI_BASEADDR					 (APB2PERIPH_BASEADDR + 0x3C00)
#define SYSCFG_BASEADDR        			 (APB2PERIPH_BASEADDR + 0x3800)

typedef struct
{
	__vo u32 MODER;
	__vo u32 OTYPER;
	__vo u32 OSPEEDR;
	__vo u32 PUPDR;
	__vo u32 IDR;
	__vo u32 ODR;
	__vo u32 BSRR;
	__vo u32 LCKR;
	__vo u32 AFR[2];
}GPIO_RegDef_t;

#define GPIOA  				((GPIO_RegDef_t*)GPIOA_BASEADDR)
#define GPIOB  				((GPIO_RegDef_t*)GPIOB_BASEADDR)
#define GPIOC  				((GPIO_RegDef_t*)GPIOC_BASEADDR)
#define GPIOD  				((GPIO_RegDef_t*)GPIOD_BASEADDR)
#define GPIOE  				((GPIO_RegDef_t*)GPIOE_BASEADDR)
#define GPIOF  				((GPIO_RegDef_t*)GPIOF_BASEADDR)
#define GPIOG  				((GPIO_RegDef_t*)GPIOG_BASEADDR)
#define GPIOH  				((GPIO_RegDef_t*)GPIOH_BASEADDR)
#define GPIOI  				((GPIO_RegDef_t*)GPIOI_BASEADDR)


typedef struct
{
	__vo u32 IMR;    /*!< Give a short description,          	  	     Address offset: 0x00 */
	__vo u32 EMR;    /*!< TODO,                						     Address offset: 0x04 */
	__vo u32 RTSR;   /*!< TODO,  									     Address offset: 0x08 */
	__vo u32 FTSR;   /*!< TODO, 									   	 Address offset: 0x0C */
	__vo u32 SWIER;  /*!< TODO,  									     Address offset: 0x10 */
	__vo u32 PR;     /*!< TODO,                   					     Address offset: 0x14 */

}EXTI_RegDef_t;

#define EXTI				((EXTI_RegDef_t*)EXTI_BASEADDR)

/*
 * peripheral register definition structure for SYSCFG
 */
typedef struct
{
	__vo u32 MEMRMP;
	__vo u32 PMC;
	__vo u32 EXTICR[4];
	u32      RESERVED1[2];
	__vo u32 CMPCR;
	u32      RESERVED2[2];
	__vo u32 CFGR;
} SYSCFG_RegDef_t;

#define SYSCFG				((SYSCFG_RegDef_t*)SYSCFG_BASEADDR)


#define MCAL_GPIO_PORTA               0
#define MCAL_GPIO_PORTB               1
#define MCAL_GPIO_PORTC               2
#define MCAL_GPIO_PORTD               3
#define MCAL_GPIO_PORTE               4
#define MCAL_GPIO_PORTF               5
#define MCAL_GPIO_PORTG               6
#define MCAL_GPIO_PORTH               7

#define MCAL_GPIO_MODE_INPUT               0
#define MCAL_GPIO_MODE_OUTPUT              1
#define MCAL_GPIO_MODE_ALTFUN              2
#define MCAL_GPIO_MODE_INPUT_ANALOG        3
#define MCAL_GPIO_MODE_EXTI_FT             4
#define MCAL_GPIO_MODE_EXTI_RT             5
#define MCAL_GPIO_MODE_EXTI_RFT            6

#define MCAL_GPIO_SPEED_LOW                0
#define MCAL_GPIO_SPEED_MED                1
#define MCAL_GPIO_SPEED_FAST               2
#define MCAL_GPIO_SPEED_HIGH               3

#define MCAL_GPIO_FLOAT                    0
#define MCAL_GPIO_PULL_UP                  1
#define MCAL_GPIO_PULL_DOWN                2

#define MCAL_GPIO_PIN_PUSH_PULL            0
#define MCAL_GPIO_PIN_OPEN_DRAIN           1

ES_t MCAL_GPIO_SelectPort(u8 Copy_enuGPIOPort,GPIO_RegDef_t** GPIO_BaseAddr);

ES_t MCAL_GPIO_SetPinMode(GPIO_RegDef_t* GPIO_BaseAddr,u8 PinNum,u8 Mode);
ES_t MCAL_GPIO_SelectSpeed(GPIO_RegDef_t* GPIO_BaseAddr,u8 PinNum,u8 Speed);
ES_t MCAL_GPIO_SetPullUpPullDown(GPIO_RegDef_t* GPIO_BaseAddr,u8 PinNum,u8 PuPd);
ES_t MCAL_GPIO_SelectPinOutputType(GPIO_RegDef_t* GPIO_BaseAddr,u8 PinNum,u8 PinOPType);
ES_t MCAL_GPIO_SetAltFuncMode(GPIO_RegDef_t* GPIO_BaseAddr,u8 PinNum,u8 AltFunMode);
ES_t MCAL_GPIO_WritePin(GPIO_RegDef_t *GPIO_BaseAddr, u8 PinNum,u8 Value);
ES_t MCAL_GPIO_ReadPin(GPIO_RegDef_t *GPIO_BaseAddr, u8 PinNum,u8 *Value);
ES_t MCAL_GPIO_TogglePin(GPIO_RegDef_t *GPIO_BaseAddr, u8 PinNum);

ES_t MCAL_SYSCFG_SellectEXTIChannel(u8 GPIO_Port,u8 PinNum);

ES_t MCAL_EXTI_SetEdgeTrig(u8 PinNum,u8 Mode);
ES_t MCAL_EXTI_EnableLine(u8 PinNum);
ES_t MCAL_EXTI_SetCallBack(u8 Line, void (*callBackFun)(void));


#endif /* STM32F407X_MCAL_INC_STM32F407X_GPIO_EXTI_H_ */
