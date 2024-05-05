/**
 ******************************************************************************
 ******************************************************************************
 * @file           : stm32fxxxx_spi.h
 * @author         : Rezk Ahmed
 * @Layer          : ECU / Board
 * @brief          : For control across the entire STM32F4x family,
 *                   this layer is not aware of specific hardware information
 *                   such as register addresses.
 *                   It utilizes all peripherals through MCAL APIs.
 ******************************************************************************
 ******************************************************************************
 */

#ifndef STM32F407X_DRIVERS_INC_STM32F4XXX_SPI_H_
#define STM32F407X_DRIVERS_INC_STM32F4XXX_SPI_H_

/*
 * @SPIx
 */
typedef enum
{
	SPI_1,
	SPI_2,
	SPI_3,
	SPI_4,
	SPI_5,
	SPI_6,
}SPI_t;

/*
 * @SPI_DeviceMode
 */
typedef enum
{
	SPI_DeviceModeSlave,
	SPI_DeviceModeMaster
}SPI_DeviceMode_t;

/*
 * @SPI_BusConfig
 */
typedef enum
{
	SPI_BusConfig_FD=1,
	SPI_BusConfig_HD,
	SPI_BusConfig_Simlex_RxOnly
}SPI_BusConfig_t;


/*
 * @SPI_SclkSpeed
 */
typedef enum
{
	SPI_SclkSpeed_Div2,
	SPI_SclkSpeed_Div4,
	SPI_SclkSpeed_Div8,
	SPI_SclkSpeed_Div16,
	SPI_SclkSpeed_Div32,
	SPI_SclkSpeed_Div64,
	SPI_SclkSpeed_Div128,
	SPI_SclkSpeed_Div256,
}SPI_SclkSpeed_t;

/*
 * @SPI_DFF
 */
typedef enum
{
	SPI_DFF_8Bits,
	SPI_DFF_16Bits
}SPI_DFF_t;

/*
 * @CPOL
 */
typedef enum
{
	SPI_CPOL_Low,
	SPI_CPOL_High
}SPI_CPOL_t;

/*
 * @CPHA
 */
typedef enum
{
	SPI_CPHA_Low,
	SPI_CPHA_High
}SPI_CPHA_t;

/*
 * @SPI_SSM
 */
typedef enum
{
	SPI_SSM_Disable,
	SPI_SSM_Enable
}SPI_SSM_t;

typedef enum
{
	SPI_Ready,
	SPI_BUSY_InRx,
	SPI_BUSY_InTx
}SPI_BusyState_t;

/*
 *  Configuration structure for SPIx peripheral
 */
typedef struct
{
	SPI_DeviceMode_t SPI_DeviceMode;
	SPI_BusConfig_t SPI_BusConfig;
	SPI_SclkSpeed_t SPI_SclkSpeed;
	SPI_DFF_t SPI_DFF;
	SPI_CPOL_t SPI_CPOL;
	SPI_CPHA_t SPI_CPHA;
	SPI_SSM_t SPI_SSM;
}SPI_Config_t;


/*
 *Handle structure for SPIx peripheral
 */
typedef struct
{
	SPI_t      	      SPIx;
	SPI_Config_t 	  SPIConfig;
	u8 	        	  *pTxBuffer;
	u8 		          *pRxBuffer;
	u32 		      TxLen;
	u32 		      RxLen;
	SPI_BusyState_t   TxState;
	SPI_BusyState_t   RxState;
	void (*TxCallBackFunc)(void);
	void (*RxCallBackFunc)(void);
	void (*ErrorCallBackFunc)(void);
}SPI_Handle_t;


ES_t SPI_enuInit(SPI_Handle_t *Copy_pstrSPIHandle);

ES_t SPI_enuSendData(SPI_Handle_t *Copy_pstrSPIHandle,u8 *Copy_pu8Data, u32 Copy_u32Len);

ES_t SPI_enuReceiveData(SPI_Handle_t *Copy_pstrSPIHandle,u8 *Copy_pu8Data, u32 Copy_u32Len);

ES_t SPI_enuSendDataIT(SPI_Handle_t *Copy_pstrSPIHandle,u8 *Copy_pu8Data, u32 Copy_u32Len, void(*CallBack)(void));

ES_t SPI_enuReceiveDataIT(SPI_Handle_t *Copy_pstrSPIHandle,u8 *Copy_pu8Data, u32 Copy_u32Len, void(*CallBack)(void));

ES_t SPI_enuStopTransmission(SPI_Handle_t *Copy_pstrSPIHandle);

ES_t SPI_enuStopReception(SPI_Handle_t *Copy_pstrSPIHandle);

void SPI_IRQHandling(SPI_Handle_t *Copy_pstrSPIHandle);


#endif /* STM32F407X_DRIVERS_INC_STM32F4XXX_SPI_H_ */
