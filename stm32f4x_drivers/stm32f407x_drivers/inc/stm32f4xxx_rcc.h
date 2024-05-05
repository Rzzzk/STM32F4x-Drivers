/**
 ******************************************************************************
 ******************************************************************************
 * @file           : stm32fxxxx_rcc.h
 * @author         : Rezk Ahmed
 * @Layer          : ECU / Board
 * @brief          : For control across the entire STM32F4x family,
 *                   this layer is not aware of specific hardware information
 *                   such as register addresses.
 *                   It utilizes all peripherals through MCAL APIs.
 ******************************************************************************
 ******************************************************************************
 */

#ifndef STM32F407X_DRIVERS_INC_STM32F4XXX_RCC_H_
#define STM32F407X_DRIVERS_INC_STM32F4XXX_RCC_H_

typedef enum
{
	RCC_SYSCLK_HSE_Crys,
	RCC_SYSCLK_HSE_RC,
	RCC_SYSCLK_HSI,
	RCC_SYSCLK_PLL
}RCC_SysClk_t;

typedef enum
{
	RCC_AHB_not_divided,
	RCC_AHB_div_by_2=8,
	RCC_AHB_div_by_4,
	RCC_AHB_div_by_8,
	RCC_AHB_div_by_16,
	RCC_AHB_div_by_64,
	RCC_AHB_div_by_128,
	RCC_AHB_div_by_256,
	RCC_AHB_div_by_512,
}RCC_AHBPrescaler_t;

typedef enum
{
	RCC_APB_not_divided,
	RCC_APB_divBy_2=4,
	RCC_APB_divBy_4,
	RCC_APB_divBy_8,
	RCC_APB_divBy_16,
}RCC_APBPrescaler_t;

typedef enum
{
	RCC_PLL_inputHSE,
	RCC_PLL_inputHSI
}RCC_PLLInputClk_t;


typedef enum
{
	RCC_AHB1_BUS,
	RCC_AHB2_BUS,
	RCC_APB1_BUS,
	RCC_APB2_BUS
}RCC_Bus_t;

typedef enum
{
	AHB1_GPIOA,
	AHB1_GPIOB,
	AHB1_GPIOC,
	AHB1_GPIOD,
	AHB1_GPIOE,
	AHB1_GPIOF,
	AHB1_GPIOG

}RCC_AHB1Periph_t;

typedef enum
{
	AHB_DE,

}RCC_AHB2Periph_t;

typedef enum
{
	APB1_DEMO,

}RCC_APB1Periph_t;

typedef enum
{
	APB2_SYSCFG=14,
}RCC_APB2Periph_t;


typedef struct
{
	RCC_SysClk_t       RCC_SysClkSource;
	RCC_AHBPrescaler_t RCC_AHBPrescaler;
	RCC_APBPrescaler_t RCC_APB1Prescaler;
	RCC_APBPrescaler_t RCC_APB2Prescaler;
}RCC_Handler_t;


/*****************************************/

ES_t RCC_enuInitSystemClk(RCC_Handler_t *Copy_pstrRCCConfig);


/******************************************/
/***      peripheral clock control      ***/
/******************************************/

ES_t RCC_enuAHB1PeriphClkCtrl(RCC_AHB1Periph_t Copy_enuPerphNum, u8 Copy_u8EnOrDi);

ES_t RCC_enuAHB2PeriphClkCtrl(RCC_AHB2Periph_t Copy_enuPerphNum, u8 Copy_u8EnOrDi);

ES_t RCC_enuAPB1PeriphClkCtrl(RCC_APB1Periph_t Copy_enuPerphNum, u8 Copy_u8EnOrDi);

ES_t RCC_enuAPB2PeriphClkCtrl(RCC_APB2Periph_t Copy_enuPerphNum, u8 Copy_u8EnOrDi);


/******************************************/
/***         peripherals reset          ***/
/******************************************/

ES_t RCC_enuAHB1PeriphReset(RCC_AHB1Periph_t Copy_enuPerphNum);

ES_t RCC_enuAHB2PeriphReset(RCC_AHB2Periph_t Copy_enuPerphNum);

ES_t RCC_enuAPB1PeriphReset(RCC_APB1Periph_t Copy_enuPerphNum);

ES_t RCC_enuAPB2PeriphReset(RCC_APB2Periph_t Copy_enuPerphNum);


/******************************************/
/******************************************/

ES_t RCC_enuGetAPB1Value(u32 *Copy_pu8APB2Value);

ES_t RCC_enuGetAPB2Value(u32 *Copy_pu8APB2Value);

ES_t RCC_enuGetSysClkType(RCC_SysClk_t *Copy_penuSysClk);

ES_t RCC_enuGetSysClkValue(u32 *Copy_pu32SysClkValue);

#endif /* STM32F407X_DRIVERS_INC_STM32F4XXX_RCC_H_ */
