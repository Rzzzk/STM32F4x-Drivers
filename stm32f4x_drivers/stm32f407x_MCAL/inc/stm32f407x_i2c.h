/**
 ******************************************************************************
 ******************************************************************************
 * @file           : stm32f407x_i2c.h
 * @author         : Rezk Ahmed
 * @Layer          : MCAL
 * @brief          : Ensure that all hardware information is gathered and abstracted
 *                   from the drivers layer (ECU or Board layer), and provide higher
 *                   layer APIs with access and control over the peripheral drivers.
 ******************************************************************************
 ******************************************************************************
 */

#ifndef STM32F407X_MCAL_INC_STM32F407X_I2C_H_
#define STM32F407X_MCAL_INC_STM32F407X_I2C_H_

#define I2C1_BASEADDR						0x40005400
#define I2C2_BASEADDR						0x40005800
#define I2C3_BASEADDR						0x40005C00

typedef struct
{
  __vo u8 CR1;
  __vo u8 CR2;
  __vo u8 OAR1;
  __vo u8 OAR2;
  __vo u8 DR;
  __vo u8 SR1;
  __vo u8 SR2;
  __vo u8 CCR;
  __vo u8 TRISE;
  __vo u8 FLTR;
}I2C_RegDef_t;


#define I2C1  				((I2C_RegDef_t*)I2C1_BASEADDR)
#define I2C2  				((I2C_RegDef_t*)I2C2_BASEADDR)
#define I2C3  				((I2C_RegDef_t*)I2C3_BASEADDR)


/******************************************************************************************
 *Bit position definitions of I2C peripheral
 ******************************************************************************************/
/*
 * Bit position definitions I2C_CR1
 */
#define MCAL_I2C_CR1_PE						0
#define MCAL_I2C_CR1_NOSTRETCH  			7
#define MCAL_I2C_CR1_START 					8
#define MCAL_I2C_CR1_STOP  				 	9
#define MCAL_I2C_CR1_ACK 				 	10
#define MCAL_I2C_CR1_SWRST  				15

/*
 * Bit position definitions I2C_CR2
 */
#define MCAL_I2C_CR2_FREQ				 	0
#define MCAL_I2C_CR2_ITERREN				8
#define MCAL_I2C_CR2_ITEVTEN				9
#define MCAL_I2C_CR2_ITBUFEN 			    10

/*
 * Bit position definitions I2C_OAR1
 */
#define MCAL_I2C_OAR1_ADD0    				 0
#define MCAL_I2C_OAR1_ADD71 				 1
#define MCAL_I2C_OAR1_ADD98  			 	 8
#define MCAL_I2C_OAR1_ADDMODE   			 15

/*
 * Bit position definitions I2C_SR1
 */

#define MCAL_I2C_SR1_SB 					0
#define MCAL_I2C_SR1_ADDR 				 	1
#define MCAL_I2C_SR1_BTF 					2
#define MCAL_I2C_SR1_ADD10 					3
#define MCAL_I2C_SR1_STOPF 					4
#define MCAL_I2C_SR1_RXNE 					6
#define MCAL_I2C_SR1_TXE 					7
#define MCAL_I2C_SR1_BERR 					8
#define MCAL_I2C_SR1_ARLO 					9
#define MCAL_I2C_SR1_AF 					10
#define MCAL_I2C_SR1_OVR 					11
#define MCAL_I2C_SR1_TIMEOUT 				14

/*
 * Bit position definitions I2C_SR2
 */
#define MCAL_I2C_SR2_MSL					0
#define MCAL_I2C_SR2_BUSY 					1
#define MCAL_I2C_SR2_TRA 					2
#define MCAL_I2C_SR2_GENCALL 				4
#define MCAL_I2C_SR2_DUALF 					7

/*
 * Bit position definitions I2C_CCR
 */
#define MCAL_I2C_CCR_CCR 					 0
#define MCAL_I2C_CCR_DUTY 					14
#define MCAL_I2C_CCR_FS  				 	15


/*
 * I2C application states
 */
#define MCAL_I2C_READY 				    	0
#define MCAL_I2C_BUSY_IN_RX 				1
#define MCAL_I2C_BUSY_IN_TX 				2

/*
 * @I2C_SCLSpeed
 */
#define MCAL_I2C_SCL_SPEED_SM 	    100000
#define MCAL_I2C_SCL_SPEED_FM4K 	400000
#define MCAL_I2C_SCL_SPEED_FM2K     200000

/*
 * @I2C_AckControl
 */
#define MCAL_I2C_ACK_ENABLE        1
#define MCAL_I2C_ACK_DISABLE       0


/*
 * @I2C_FMDutyCycle
 */
#define MCAL_I2C_FM_DUTY_2        0
#define MCAL_I2C_FM_DUTY_16_9     1

/*
 * I2C related status flags definitions
 */
#define MCAL_I2C_FLAG_TXE   		( 1 << MCAL_I2C_SR1_TXE)
#define MCAL_I2C_FLAG_RXNE   	    ( 1 << MCAL_I2C_SR1_RXNE)
#define MCAL_I2C_FLAG_SB			( 1 << MCAL_I2C_SR1_SB)
#define MCAL_I2C_FLAG_OVR  		    ( 1 << MCAL_I2C_SR1_OVR)
#define MCAL_I2C_FLAG_AF   		    ( 1 << MCAL_I2C_SR1_AF)
#define MCAL_I2C_FLAG_ARLO 		    ( 1 << MCAL_I2C_SR1_ARLO)
#define MCAL_I2C_FLAG_BERR 		    ( 1 << MCAL_I2C_SR1_BERR)
#define MCAL_I2C_FLAG_STOPF 		( 1 << MCAL_I2C_SR1_STOPF)
#define MCAL_I2C_FLAG_ADD10 		( 1 << MCAL_I2C_SR1_ADD10)
#define MCAL_I2C_FLAG_BTF  		    ( 1 << MCAL_I2C_SR1_BTF)
#define MCAL_I2C_FLAG_ADDR 		    ( 1 << MCAL_I2C_SR1_ADDR)
#define MCAL_I2C_FLAG_TIMEOUT 	    ( 1 << MCAL_I2C_SR1_TIMEOUT)


/*
 * I2C related Interrupt sources names
 */
#define MCAL_I2C_ITBUFEN_INT            MCAL_I2C_CR2_ITBUFEN
#define MCAL_I2C_ITEVFEN_INT			MCAL_I2C_CR2_ITEVTEN
#define MCAL_I2C_ITERREN_INT            MCAL_I2C_CR2_ITERREN


#define MCAL_I2C_DISABLE_SR  	    RESET
#define MCAL_I2C_ENABLE_SR   	    SET

/*
 * I2C application events macros
 */
#define MCAL_I2C_EV_TX_CMPLT  	 	0
#define MCAL_I2C_EV_RX_CMPLT  	 	1
#define MCAL_I2C_EV_STOP       		2
#define MCAL_I2C_ERROR_BERR 	 	3
#define MCAL_I2C_ERROR_ARLO  		4
#define MCAL_I2C_ERROR_AF    		5
#define MCAL_I2C_ERROR_OVR   		6
#define MCAL_I2C_ERROR_TIMEOUT 		7
#define MCAL_I2C_EV_DATA_REQ        8
#define MCAL_I2C_EV_DATA_RCV        9


#define MCAL_I2C_MASTER             1
#define MCAL_I2C_SLAVE              0

#define MCAL_I2C_TRANSMITTER        1
#define MCAL_I2C_RECEIVER           0



#define MCAL_I2C_CODE_TO_BASADDR(x)         ( (x == 0)?I2C1:\
		                                      (x == 1)?I2C2:\
			                                  (x == 2)?I2C3:0)


void MCAL_I2C_AckBitControl(I2C_RegDef_t *pI2Cx,u8 AckEnOrDi);
void MCAL_I2c_SetFreqFeild(I2C_RegDef_t *pI2Cx, u32 APB1Freq);
void MCAL_I2C_SetDeviceOwnAddress(I2C_RegDef_t *pI2Cx,u8 DeviceAddress);
void MCAL_I2C_SetClockControl(I2C_RegDef_t *pI2Cx,u32 APB1Freq,u32 Speed, u8 FMDutyCycle);
void MCAL_I2C_SetTRISEConfig(I2C_RegDef_t *pI2Cx, u32 APB1Freq, u32 Speed);

void MCAL_I2C_WriteDataByte(I2C_RegDef_t *pI2Cx,u8 Data);
u32 MCAL_I2C_ReadDataByte(I2C_RegDef_t *pI2Cx);
void MCAL_I2C_ClearADDRFlag(I2C_RegDef_t *pI2Cx);

void MCAL_I2C_GenerateStartCondition(I2C_RegDef_t *pI2Cx);
void MCAL_I2C_GenerateStopCondition(I2C_RegDef_t *pI2Cx);

void MCAL_I2C_ExecuteAddressPhaseWrite(I2C_RegDef_t *pI2Cx, u8 SlaveAddr);
void MCAL_I2C_ExecuteAddressPhaseRead(I2C_RegDef_t *pI2Cx, u8 SlaveAddr);


u8 MCAL_I2C_GetFlagStatus(I2C_RegDef_t *pI2Cx, u32 FlagName);
void MCAL_I2C_ClearFlag(I2C_RegDef_t *pI2Cx, u32 FlagName);


void MCAL_I2C_InterruptControl(I2C_RegDef_t *pI2Cx, u8 InterruptName, u8 EnOrDi);
u8 MCAL_I2C_GetInterruptStatus(I2C_RegDef_t *pI2Cx, u8 InterruptName);

void MCAL_I2C_ClearSTOPFlag(I2C_RegDef_t *pI2Cx);

u8 MCAL_I2C_GetDeviceMode(I2C_RegDef_t *pI2Cx);
u8 MCAL_I2C_GetTransceiverMode(I2C_RegDef_t *pI2Cx);


#endif /* STM32F407X_MCAL_INC_STM32F407X_I2C_H_ */
