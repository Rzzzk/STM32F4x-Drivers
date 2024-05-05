/**
 ******************************************************************************
 ******************************************************************************
 * @file           : stm32fxxxx_usart.h
 * @author         : Rezk Ahmed
 * @Layer          : ECU / Board
 * @brief          : For control across the entire STM32F4x family,
 *                   this layer is not aware of specific hardware information
 *                   such as register addresses.
 *                   It utilizes all peripherals through MCAL APIs.
 ******************************************************************************
 ******************************************************************************
 */

#ifndef STM32F407X_DRIVERS_INC_STM32F4XXX_USART_H_
#define STM32F407X_DRIVERS_INC_STM32F4XXX_USART_H_


#define USART_STD_BAUD_1200					1200
#define USART_STD_BAUD_2400					400
#define USART_STD_BAUD_9600					9600
#define USART_STD_BAUD_19200 				19200
#define USART_STD_BAUD_38400 				38400
#define USART_STD_BAUD_57600 				57600
#define USART_STD_BAUD_115200 				115200
#define USART_STD_BAUD_230400 				230400
#define USART_STD_BAUD_460800 				460800
#define USART_STD_BAUD_921600 				921600
#define USART_STD_BAUD_2M 					2000000
#define USART_STD_BAUD_3M 					3000000


typedef enum
{
	USART_1,
	USART_2,
	USART_3,
	UART_4,
	UART_5,
	USART_6
}USART_t;

typedef enum
{
	USART_Mode_TxOnly,
	USART_Mode_RxOnly,
	USART_Mode_RxTx
}USART_Mode_t;



typedef enum
{
	USART_WordLen_8Bits,
	USART_WordLen_9Bits
}USART_WordLen_t;

typedef enum
{
	USART_Parity_Disable,
	USART_Parity_Even,
	USART_Parity_Odd
}USART_Parity_t;


typedef enum
{
	USART_StopBits_1,
	USART_StopBits_0_5,
	USART_StopBits_2,
	USART_StopBits_1_5
}USART_StopBits_t;

typedef enum
{
	USART_HwFlowCtrl_None,
	USART_HwFlowCtrl_CTS,
	USART_HwFlowCtrl_RTS,
	USART_HwFlowCtrl_CTS_RTS
}USART_HwFlowCtrl_t;


typedef enum
{
	USART_Ready,
	USART_Busy_InRX,
	USART_Busy_InTX,

}USART_BusyState_t;


typedef struct
{
	USART_Mode_t        USART_Mode;
	USART_WordLen_t     USART_WordLen;
	USART_Parity_t      USART_Parity;
	USART_StopBits_t    USART_StopBits;
	USART_HwFlowCtrl_t  USART_HwFlowCtrl;
	u32                 USART_BaudRate;

}USART_PinConfig_t;


typedef struct
{
	USART_t USARTx;
	USART_PinConfig_t USART_Config;
	u8 *pTxBuffer;
	u8 *pRxBuffer;
	u8 TxLen;
	u8 RxLen;
	USART_BusyState_t TxBusyState;
	USART_BusyState_t RxBusyState;
	void (*TxCallBackFunc)(void);
	void (*RxCallBackFunc)(void);
}USART_Handle_t;


ES_t USART_enuInit(USART_Handle_t* Copy_pstrUSARTHandler);


ES_t USART_enuSendDataSyn(USART_Handle_t* Copy_pstrUSARTHandler, u8 *Copy_pu8Data,u8 Copy_u8Len);


ES_t USART_enuReceiveDataSyn(USART_Handle_t* Copy_pstrUSARTHandler, u8 *Copy_pu8Data,u8 Copy_u8Len);


ES_t USART_enuSendDataIT(USART_Handle_t* Copy_pstrUSARTHandler, u8 *Copy_pu8Data,u8 Copy_u8Len,void (*callBack)(void));


ES_t USART_enuReceiveDataIT(USART_Handle_t* Copy_pstrUSARTHandler, u8 *Copy_pu8Data,u8 Copy_u8Len,void (*callBack)(void));


void USART_IRQHandling(USART_Handle_t *Copy_pstrUSARTHandler);


#endif /* STM32F407X_DRIVERS_INC_STM32F4XXX_USART_H_ */
