/**
 ******************************************************************************
 ******************************************************************************
 * @file           : stm32f407x_rcc.h
 * @author         : Rezk Ahmed
 * @Layer          : MCAL
 * @brief          : Ensure that all hardware information is gathered and abstracted
 *                   from the drivers layer (ECU or Board layer), and provide higher
 *                   layer APIs with access and control over the peripheral drivers.
 ******************************************************************************
 ******************************************************************************
 */
#ifndef STM32F407X_MCAL_INC_STM32F407X_RCC_H_
#define STM32F407X_MCAL_INC_STM32F407X_RCC_H_


/*
 * *****************************
 *
 *            RCC
 *
 * *****************************
 */



#define RCC_BASEADDR                     (0x40003800)

/*
 * peripheral register definition structure for RCC
 */
typedef struct
{
	__vo u32 CR;
	__vo u32 PLLCFGR;
	__vo u32 CFGR;
	__vo u32 CIR;
	__vo u32 AHB1RSTR;
	__vo u32 AHB2RSTR;
	__vo u32 AHB3RSTR;
	u32      RESERVED0;
	__vo u32 APB1RSTR;
	__vo u32 APB2RSTR;
	u32      RESERVED1[2];
	__vo u32 AHB1ENR;
	__vo u32 AHB2ENR;
	__vo u32 AHB3ENR;
	u32      RESERVED2;
	__vo u32 APB1ENR;
	__vo u32 APB2ENR;
	u32      RESERVED3[2];
	__vo u32 AHB1LPENR;
	__vo u32 AHB2LPENR;
	__vo u32 AHB3LPENR;
	u32      RESERVED4;
	__vo u32 APB1LPENR;
	__vo u32 APB2LPENR;
	u32      RESERVED5[2];
	__vo u32 BDCR;
	__vo u32 CSR;
	u32      RESERVED6[2];
	__vo u32 SSCGR;
	__vo u32 PLLI2SCFGR;
	__vo u32 PLLSAICFGR;
	__vo u32 DCKCFGR;
	__vo u32 CKGATENR;
	__vo u32 DCKCFGR2;

} RCC_RegDef_t;

#define RCC 				((RCC_RegDef_t*)RCC_BASEADDR)

#define RCC_CR_HSION    0
#define RCC_CR_HSIRDY   1
#define RCC_CR_HSEON    16
#define RCC_CR_HSERDY   17
#define RCC_CR_HSYBYP   18
#define RCC_CR_CSSON    19
#define RCC_CR_PLLON    24
#define RCC_CR_PLLRDY   25
#define RCC_CR_PLL2SON  26
#define RCC_CR_PLL2SRDY 27


#define RCC_CFGR_SW0    0
#define RCC_CFGR_SW1    1
#define RCC_CFGR_SWS0   2
#define RCC_CFGR_SWS1   3



/**********  Pre-scaller options  ***********/

#define MCAL_RCC_AHB_NO_PRE_SCAL            0
#define MCAL_RCC_AHB_PRE_SCAL_BY_2          8
#define MCAL_RCC_AHB_PRE_SCAL_BY_4          9
#define MCAL_RCC_AHB_PRE_SCAL_BY_8          10
#define MCAL_RCC_AHB_PRE_SCAL_BY_16         11
#define MCAL_RCC_AHB_PRE_SCAL_BY_64         12
#define MCAL_RCC_AHB_PRE_SCAL_BY_128        13
#define MCAL_RCC_AHB_PRE_SCAL_BY_256        14
#define MCAL_RCC_AHB_PRE_SCAL_BY_512        15


#define MCAL_RCC_APB_NO_PRE_SCAL             0
#define MCAL_RCC_APB_PRE_SCAL_BY_2           4
#define MCAL_RCC_APB_PRE_SCAL_BY_4           5
#define MCAL_RCC_APB_PRE_SCAL_BY_8           6
#define MCAL_RCC_APB_PRE_SCAL_BY_16          7



/************************* system Clock Source ******************/

#define MCAL_RCC_SYSCLK_HSE_CRYSTAL          0
#define MCAL_RCC_SYSCLK_HSE_RC               1
#define MCAL_RCC_SYSCLK_HSI                  2
#define MCAL_RCC_SYSCLK_PLL                  3


void MCAL_RCC_SetAHBPrescaller(u8 AHBPrescaller);
void MCAL_RCC_SetAPB1Prescaller(u8 APB1Prescaller);
void MCAL_RCC_SetAPB2Prescaller(u8 APB2Prescaller);

ES_t MCAL_RCC_SelectSystemClockSource(u8 SysClkSrc);
ES_t MCAL_RCC_AHB1PeriphClockEnable(u8 PerNum);
ES_t MCAL_RCC_AHB2PeriphClockEnable(u8 PerNum);
ES_t MCAL_RCC_APB1PeriphClockEnable(u8 PerNum);
ES_t MCAL_RCC_APB2PeriphClockEnable(u8 PerNum);
ES_t MCAL_RCC_AHB1PeriphClockDisable(u8 PerNum);
ES_t MCAL_RCC_AHB2PeriphClockDisable(u8 PerNum);
ES_t MCAL_RCC_APB1PeriphClockDisable(u8 PerNum);
ES_t MCAL_RCC_APB2PeriphClockDisable(u8 PerNum);
ES_t MCAL_RCC_AHB1PeriphReset(u8 PerNum);
ES_t MCAL_RCC_APB2PeriphClockDisable(u8 PerNum);
ES_t MCAL_RCC_AHB2PeriphReset(u8 PerNum);
ES_t MCAL_RCC_APB1PeriphReset(u8 PerNum);
ES_t MCAL_RCC_APB2PeriphReset(u8 PerNum);
ES_t MCAL_RCC_GetAPB1Value(u32 *APB2Value);
ES_t MCAL_RCC_GetAPB2Value(u32 *APB2Value);
ES_t MCAL_RCC_GetSysClkType(u8 *SysClkType);
ES_t MCAL_RCC_GetSysClkValue(u32 *SysClkValue);


#endif /* STM32F407X_MCAL_INC_STM32F407X_RCC_H_ */
