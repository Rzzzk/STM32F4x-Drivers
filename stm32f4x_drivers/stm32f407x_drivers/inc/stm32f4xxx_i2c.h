/**
 ******************************************************************************
 ******************************************************************************
 * @file           : stm32fxxxx_i2c.h
 * @author         : Rezk Ahmed
 * @Layer          : ECU / Board
 * @brief          : For control across the entire STM32F4x family,
 *                   this layer is not aware of specific hardware information
 *                   such as register addresses.
 *                   It utilizes all peripherals through MCAL APIs.
 ******************************************************************************
 ******************************************************************************
 */

#ifndef STM32F407X_DRIVERS_INC_STM32F4XXX_I2C_H_
#define STM32F407X_DRIVERS_INC_STM32F4XXX_I2C_H_


/*
 * @I2C_SCLSpeed
 */
#define I2C_SCL_SPEED_SM 	100000
#define I2C_SCL_SPEED_FM4K 	400000
#define I2C_SCL_SPEED_FM2K  200000

/*
 * I2C application states
 */
typedef enum
{
	I2C_Ready,
	I2C_BusyInRx,
	I2C_BusyInTx
}I2C_BusyStete_t;

/*
 * @I2C_AckControl
 */
typedef enum
{
	I2C_ACK_Disable,
	I2C_ACK_Enable
}I2C_AckCtrl_t;

/*
 * @I2C_FMDutyCycle
 */
typedef enum
{
	I2C_FM_Duty2,
	I2C_FM_Duty16_9
}I2C_FMDutyCycle_t;


typedef enum
{
	I2C_DisableRepStart,
	I2C_EnableRepStart
}I2C_RepStartCtrl_t;


typedef enum
{
    I2C_Event_TxComplete,
    I2C_Event_RxComplete,
    I2C_Event_Stop,
    I2C_Event_ErrorBerr,
    I2C_Event_ErrorArlo,
    I2C_Event_ErrorAf,
    I2C_Event_ErrorOvr,
    I2C_Event_ErrorTimeout,
    I2C_Event_DataReq,
    I2C_Event_DataRcv,
} I2C_AppEvent_t;


typedef enum
{
	I2C_1,
	I2C_2,
	I2C_3
}I2C_t;

typedef struct
{
	u32 I2C_SCLSpeed;
	u8  I2C_DeviceAddress;
	I2C_AckCtrl_t     I2C_AckControl;
	I2C_FMDutyCycle_t  I2C_FMDutyCycle;

}I2C_Config_t;


typedef struct
{
	I2C_t 	I2C_ID;
	I2C_Config_t 	I2C_Config;
	I2C_BusyStete_t		TxRxState;
    I2C_RepStartCtrl_t  Sr;
	u8 		DevAddr;
	u8 		*pTxBuffer;
	u8 		*pRxBuffer;
	u32 	TxLen;
	u32 	RxLen;
    u32     RxSize;
    void (*CallBackFun)(I2C_AppEvent_t Status);
}I2C_Handle_t;


ES_t I2C_enuInit(I2C_Handle_t *Copy_pstrI2CHandle);


/*
 * Data Send and Receive Synchronous (Polling mode or blocking)
 */
ES_t I2C_enuMasterSendData(I2C_Handle_t *Copy_pstrI2CHandle,u8 *Copy_pu8Data,
		u8 Copy_u8Len, u8 Copy_u8SlaveAddr,I2C_RepStartCtrl_t Copy_enuSr);

ES_t I2C_enuMasterReceiveData(I2C_Handle_t *Copy_pstrI2CHandle,u8 *Copy_pu8Data,
		u8 Copy_u8Len, u8 Copy_u8SlaveAddr,I2C_RepStartCtrl_t Copy_enuSr);

ES_t I2C_enuSlaveSendData(I2C_t Copy_enuI2CId, u8 Copy_pu8Data);
ES_t I2C_enuSlaveReceiveData(I2C_t Copy_enuI2CId, u8 *Copy_pu8Data);

/*
 * Data Send and Receive IT (Asynchronous mode)
 */
ES_t I2C_enuMasterSendDataIT(I2C_Handle_t *Copy_pstrI2CHandle,u8 *Copy_pu8Data,
		u8 Copy_u8Len, u8 Copy_u8SlaveAddr,I2C_RepStartCtrl_t Copy_enuSr);

ES_t I2C_enuMasterReceiveDataIT(I2C_Handle_t *Copy_pstrI2CHandle,u8 *Copy_pu8Data,
		u8 Copy_u8Len, u8 Copy_u8SlaveAddr,I2C_RepStartCtrl_t Copy_enuSr);


void I2C_CloseReceiveData(I2C_Handle_t *Copy_pstrI2CHandle);
void I2C_CloseSendData(I2C_Handle_t *Copy_pstrI2CHandle);


#endif /* STM32F407X_DRIVERS_INC_STM32F4XXX_I2C_H_ */
