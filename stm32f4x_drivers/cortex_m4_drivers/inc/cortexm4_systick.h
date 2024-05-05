/**
 ******************************************************************************
 ******************************************************************************
 * @file           : cortexm4_systick.h
 * @author         : Rezk Ahmed
 * @Layer          : ECU / Board
 * @brief          : For control across the entire STM32F4x family,
 *                   this layer is not aware of specific hardware information
 *                   such as register addresses.
 *                   It utilizes all peripherals through MCAL APIs.
 ******************************************************************************
 ******************************************************************************
 */


#ifndef CORTEX_M4_DRIVERS_INC_CORTEXM4_SYSTICK_H_
#define CORTEX_M4_DRIVERS_INC_CORTEXM4_SYSTICK_H_


typedef enum
{
	SysTick_BusyWait,
	SysTick_SingleTick,
	SysTick_PeriodicTick

}SysTick_Type_t;


typedef enum
{
	SysTick_ProcessorClock,
	SysTick_ExternalClock
}SysTic_ClkSrc_t;

typedef struct
{
	u32 LoadValue;
	u32 CurrenCountValue;
	SysTic_ClkSrc_t  ClockSource;
	u32 BasyWaitTimeOut;
	void (*CallBackFun)(void);

}SysTick_Config_t;

typedef struct
{
	SysTick_Type_t Type;
	SysTick_Config_t cofig;
}SysTick_Handle_t;

ES_t SysTick_enuInit(SysTic_ClkSrc_t Copy_enuClockSource);

ES_t SysTick_enuStart(SysTick_Handle_t *Copy_pstrSysTickHandle);


#endif /* CORTEX_M4_DRIVERS_INC_CORTEXM4_SYSTICK_H_ */
