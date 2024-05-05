/**
 ******************************************************************************
 ******************************************************************************
 * @file           : stm32f407x_rcc.c
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
#include "stm32f407x_rcc.h"

static void EnableHSE_crys(void);
static void EnableHSE_rc(void);
static void DisableHSE(void);
static void SelectHSE(void);
static void EnableHSI(void);
static void DisableHSI(void);
static void SelectHSI(void);

u16 AHB_PreScaler[8] = {2,4,8,16,64,128,256,512};
u8 APB_PreScaler[4] = { 2, 4 , 8, 16};



void MCAL_RCC_SetAHBPrescaller(u8 AHBPrescaller)
{
	RCC->CFGR &= ~(0xF << 4);
	RCC->CFGR |= (AHBPrescaller << 4);         //AHB  pre-scaler
}

void MCAL_RCC_SetAPB1Prescaller(u8 APB1Prescaller)
{
	RCC->CFGR &= ~(0x7 << 10);
	RCC->CFGR |= (APB1Prescaller << 10);      //APB1 pre-scaler
}

void MCAL_RCC_SetAPB2Prescaller(u8 APB2Prescaller)
{
	RCC->CFGR &= ~(0x7 << 13);
	RCC->CFGR |= (APB2Prescaller << 13);      //APB2 pre-scaler
}



ES_t MCAL_RCC_SelectSystemClockSource(u8 SysClkSrc)
{

	ES_t errorState =ES_NOT_OK;

	if(SysClkSrc == MCAL_RCC_SYSCLK_HSE_CRYSTAL)
	{
		EnableHSE_crys(); // enable the HSE
		SelectHSE();      // select HSE
		DisableHSI();     // disable HSI
		errorState =ES_OK;
	}
	else if(SysClkSrc == MCAL_RCC_SYSCLK_HSE_RC)
	{
		EnableHSE_rc();    // enable the HSE
		SelectHSE();       // select HSE
		DisableHSI();      // disable HSI
		errorState =ES_OK;
	}
	else if(SysClkSrc == MCAL_RCC_SYSCLK_HSI)
	{
		EnableHSI();      // enable the HSI
		SelectHSI();      // select HSI
		DisableHSE();     // disable HSE
		errorState =ES_OK;
	}
	else if(SysClkSrc == MCAL_RCC_SYSCLK_PLL)
	{

	}

	return errorState;
}


ES_t MCAL_RCC_AHB1PeriphClockEnable(u8 PerNum)
{
	ES_t errorState = ES_NOT_OK;

	SET_BIT(RCC->AHB1ENR,PerNum);

	errorState = ES_OK;

	return errorState;
}


ES_t MCAL_RCC_AHB2PeriphClockEnable(u8 PerNum)
{
	ES_t errorState = ES_NOT_OK;

	SET_BIT(RCC->AHB2ENR,PerNum);

	errorState = ES_OK;

	return errorState;
}


ES_t MCAL_RCC_APB1PeriphClockEnable(u8 PerNum)
{
	ES_t errorState = ES_NOT_OK;

	SET_BIT(RCC->APB1ENR,PerNum);

	errorState = ES_OK;

	return errorState;
}


ES_t MCAL_RCC_APB2PeriphClockEnable(u8 PerNum)
{
	ES_t errorState = ES_NOT_OK;

	SET_BIT(RCC->APB2ENR,PerNum);

	errorState = ES_OK;

	return errorState;
}


ES_t MCAL_RCC_AHB1PeriphClockDisable(u8 PerNum)
{
	ES_t errorState = ES_NOT_OK;

	CLR_BIT(RCC->AHB1ENR,PerNum);

	errorState = ES_OK;

	return errorState;
}


ES_t MCAL_RCC_AHB2PeriphClockDisable(u8 PerNum)
{
	ES_t errorState = ES_NOT_OK;

	CLR_BIT(RCC->AHB2ENR,PerNum);

	errorState = ES_OK;

	return errorState;
}


ES_t MCAL_RCC_APB1PeriphClockDisable(u8 PerNum)
{
	ES_t errorState = ES_NOT_OK;

	CLR_BIT(RCC->APB1ENR,PerNum);

	errorState = ES_OK;

	return errorState;
}

ES_t MCAL_RCC_AHB1PeriphReset(u8 PerNum)
{
	ES_t errorState = ES_NOT_OK;

	SET_BIT(RCC->AHB1RSTR,PerNum);
	CLR_BIT(RCC->AHB1RSTR,PerNum);

	errorState = ES_OK;
	return errorState;
}

ES_t MCAL_RCC_APB2PeriphClockDisable(u8 PerNum)
{
	ES_t errorState = ES_NOT_OK;

	CLR_BIT(RCC->APB2ENR,PerNum);

	errorState = ES_OK;

	return errorState;
}

ES_t MCAL_RCC_AHB2PeriphReset(u8 PerNum)
{
	ES_t errorState = ES_NOT_OK;

	SET_BIT(RCC->AHB2RSTR,PerNum);
	CLR_BIT(RCC->AHB2RSTR,PerNum);

	errorState = ES_OK;

	return errorState;
}


ES_t MCAL_RCC_APB1PeriphReset(u8 PerNum)
{
	ES_t errorState = ES_NOT_OK;

	SET_BIT(RCC->APB1RSTR,PerNum);
	CLR_BIT(RCC->APB1RSTR,PerNum);

	errorState = ES_OK;

	return errorState;
}


ES_t MCAL_RCC_APB2PeriphReset(u8 PerNum)
{
	ES_t errorState = ES_NOT_OK;

	SET_BIT(RCC->APB2RSTR,PerNum);
	CLR_BIT(RCC->APB2RSTR,PerNum);

	errorState = ES_OK;

	return errorState;
}


ES_t MCAL_RCC_GetAPB1Value(u32 *APB2Value)
{
	ES_t errorState = ES_NOT_OK;

	u32 PCLK1,SystemClk;
	u8 ClockSource, Temp,APB1Prescaler;
	u16 AHBPrescaler;


	ClockSource = ((RCC->CFGR >> RCC_CFGR_SWS0) & 0x3);

	if(ClockSource == 0 )
	{
		SystemClk = 16000000; //HSI
	}
	else if(ClockSource == 1)
	{
		SystemClk = 8000000; //HSE
	}
	else if (ClockSource == 2)
	{
		// PLL
	}
	else
	{
		return errorState;
	}

	//for AHB pre-scaler
	Temp = ((RCC->CFGR >> 4 ) & 0xF);

	if(Temp < 8)
	{
		AHBPrescaler = 1;
	}
	else
	{
		AHBPrescaler = AHB_PreScaler[Temp-8];
	}


	//apb1
	Temp = ((RCC->CFGR >> 10 ) & 0x7);

	if(Temp < 4)
	{
		APB1Prescaler = 1;
	}
	else
	{
		APB1Prescaler = APB_PreScaler[Temp-4];
	}

	PCLK1 =  (SystemClk / AHBPrescaler) /APB1Prescaler;
	errorState = ES_OK;

	*APB2Value = PCLK1;

	return errorState;
}

ES_t MCAL_RCC_GetAPB2Value(u32 *APB2Value)
{
	ES_t errorState = ES_NOT_OK;

	u32 PCLK1,SystemClk;

	u8 ClockSource, Temp, APB2Prescaler;
	u16 AHBPrescaler;


	ClockSource = ((RCC->CFGR >> RCC_CFGR_SWS0) & 0x3);

	if(ClockSource == 0 )
	{
		SystemClk = 16000000; //HSI
	}
	else if(ClockSource == 1)
	{
		SystemClk = 8000000; //HSE
	}
	else if (ClockSource == 2)
	{
		// PLL
	}
	else
	{
		return errorState;
	}

	//for AHB pre-scaler
	Temp = ((RCC->CFGR >> 4 ) & 0xF);

	if(Temp < 8)
	{
		AHBPrescaler = 1;
	}
	else
	{
		AHBPrescaler = AHB_PreScaler[Temp-8];
	}


	//apb1
	Temp = ((RCC->CFGR >> 13 ) & 0x7);

	if(Temp < 4)
	{
		APB2Prescaler = 1;
	}
	else
	{
		APB2Prescaler = APB_PreScaler[Temp-4];
	}

	PCLK1 =  (SystemClk / APB2Prescaler) /AHBPrescaler;
	errorState = ES_OK;

	*APB2Value = PCLK1;

	return errorState;
}

ES_t MCAL_RCC_GetSysClkValue(u32 *SysClkValue)
{
	ES_t errorState = ES_NOT_OK;

	u8 ClockSource = ((RCC->CFGR >> RCC_CFGR_SWS0) & 0x3);

	if(ClockSource == 0 )
	{
		*SysClkValue = 16000000; //HSI
		errorState = ES_OK;
	}
	else if(ClockSource == 1)
	{
		*SysClkValue = 8000000; //HSE
		errorState = ES_OK;
	}
	else if (ClockSource == 2)
	{
		// PLL
	}

	return errorState;
}


ES_t MCAL_RCC_GetSysClkType(u8 *SysClkType)
{
	ES_t errorState = ES_NOT_OK;

	u8 ClockSource;

	ClockSource = ((RCC->CFGR >> RCC_CFGR_SWS0) & 0x3);

	if(ClockSource == 0 )
	{
		*SysClkType = MCAL_RCC_SYSCLK_HSI; //HSI
		errorState = ES_OK;
	}
	else if(ClockSource == 1)
	{
		*SysClkType = MCAL_RCC_SYSCLK_HSE_CRYSTAL; //HSE
		errorState = ES_OK;
	}
	else if (ClockSource == 2)
	{
		*SysClkType = MCAL_RCC_SYSCLK_PLL; // PLL
		errorState = ES_OK;
	}

	return errorState;
}



/****************************************** static functions ********************************************/

static void EnableHSE_crys(void)
{
	SET_BIT(RCC->CR,RCC_CR_HSEON);
	SET_BIT(RCC->CR,RCC_CR_HSYBYP);
}

static void EnableHSE_rc(void)
{
	SET_BIT(RCC->CR,RCC_CR_HSEON);
	SET_BIT(RCC->CR,RCC_CR_HSYBYP);
}

static void DisableHSE(void)
{
	CLR_BIT(RCC->CR,RCC_CR_HSEON);
	CLR_BIT(RCC->CR,RCC_CR_HSYBYP);
}

static void SelectHSE(void)
{
	SET_BIT(RCC->CFGR,RCC_CFGR_SW0);
	CLR_BIT(RCC->CFGR,RCC_CFGR_SW1);
}


static void EnableHSI(void)
{
	SET_BIT(RCC->CR,RCC_CR_HSION);
	SET_BIT(RCC->CR,7);  // HSITRIM[4:0]=0x8
}

static void DisableHSI(void)
{
	CLR_BIT(RCC->CR,RCC_CR_HSION);
}



static void SelectHSI(void)
{
	CLR_BIT(RCC->CFGR,RCC_CFGR_SW0);
	CLR_BIT(RCC->CFGR,RCC_CFGR_SW1);
}


