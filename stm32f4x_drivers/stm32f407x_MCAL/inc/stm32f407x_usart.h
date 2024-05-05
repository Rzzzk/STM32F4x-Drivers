/**
 ******************************************************************************
 ******************************************************************************
 * @file           : stm32f407x_usart.h
 * @author         : Rezk Ahmed
 * @Layer          : MCAL
 * @brief          : Ensure that all hardware information is gathered and abstracted
 *                   from the drivers layer (ECU or Board layer), and provide higher
 *                   layer APIs with access and control over the peripheral drivers.
 ******************************************************************************
 ******************************************************************************
 */

#ifndef STM32F407X_MCAL_INC_STM32F407X_USART_H_
#define STM32F407X_MCAL_INC_STM32F407X_USART_H_


#define USART2_BASEADDR						(0x40004400)
#define USART3_BASEADDR						(0x40004800)
#define UART4_BASEADDR						(0x40004C00)
#define UART5_BASEADDR						(0x40005000)

#define USART1_BASEADDR						(0x40001000)
#define USART6_BASEADDR						(0x40001400)

typedef struct
{
	__vo u32 SR;         /*Address offset: 0x00 */
	__vo u32 DR;         /*Address offset: 0x04 */
	__vo u32 BRR;        /*Address offset: 0x08 */
	__vo u32 CR1;        /*Address offset: 0x0C */
	__vo u32 CR2;        /*Address offset: 0x10 */
	__vo u32 CR3;        /*Address offset: 0x14 */
	__vo u32 GTPR;       /*Address offset: 0x18 */
} USART_RegDef_t;


#define USART1  			((USART_RegDef_t*)USART1_BASEADDR)
#define USART2  			((USART_RegDef_t*)USART2_BASEADDR)
#define USART3  			((USART_RegDef_t*)USART3_BASEADDR)
#define UART4  				((USART_RegDef_t*)UART4_BASEADDR)
#define UART5  				((USART_RegDef_t*)UART5_BASEADDR)
#define USART6  			((USART_RegDef_t*)USART6_BASEADDR)



#define MCAL_USART_BASEADDR_TO_CODE(x)      ( (x == 0)?USART1:\
		                                      (x == 1)?USART2:\
			                                  (x == 2)?USART3:\
						                      (x == 3)?UART4 :\
								              (x == 4)?UART5 :\
										      (x == 5)?USART6:0)


/******************************************************************************************
 *Bit position definitions of USART peripheral
 ******************************************************************************************/

/*
 * Bit position definitions USART_CR1
 */
#define MCAL_USART_CR1_SBK					0
#define MCAL_USART_CR1_RWU 					1
#define MCAL_USART_CR1_RE  					2
#define MCAL_USART_CR1_TE 					3
#define MCAL_USART_CR1_IDLEIE 				4
#define MCAL_USART_CR1_RXNEIE  				5
#define MCAL_USART_CR1_TCIE					6
#define MCAL_USART_CR1_TXEIE				7
#define MCAL_USART_CR1_PEIE 				8
#define MCAL_USART_CR1_PS 					9
#define MCAL_USART_CR1_PCE 					10
#define MCAL_USART_CR1_WAKE  				11
#define MCAL_USART_CR1_M 					12
#define MCAL_USART_CR1_UE 					13
#define MCAL_USART_CR1_OVER8  				15



/*
 * Bit position definitions USART_CR2
 */
#define MCAL_USART_CR2_ADD   				0
#define MCAL_USART_CR2_LBDL   				5
#define MCAL_USART_CR2_LBDIE  				6
#define MCAL_USART_CR2_LBCL   				8
#define MCAL_USART_CR2_CPHA   				9
#define MCAL_USART_CR2_CPOL   				10
#define MCAL_USART_CR2_STOP   				12
#define MCAL_USART_CR2_LINEN   				14


/*
 * Bit position definitions USART_CR3
 */
#define MCAL_USART_CR3_EIE   				0
#define MCAL_USART_CR3_IREN   				1
#define MCAL_USART_CR3_IRLP  				2
#define MCAL_USART_CR3_HDSEL   				3
#define MCAL_USART_CR3_NACK   				4
#define MCAL_USART_CR3_SCEN   				5
#define MCAL_USART_CR3_DMAR  				6
#define MCAL_USART_CR3_DMAT   				7
#define MCAL_USART_CR3_RTSE   				8
#define MCAL_USART_CR3_CTSE   				9
#define MCAL_USART_CR3_CTSIE   				10
#define MCAL_USART_CR3_ONEBIT   			11

/*
 * Bit position definitions USART_SR
 */

#define MCAL_USART_SR_PE        			0
#define MCAL_USART_SR_FE        			1
#define MCAL_USART_SR_NE        			2
#define MCAL_USART_SR_ORE       			3
#define MCAL_USART_SR_IDLE       			4
#define MCAL_USART_SR_RXNE        			5
#define MCAL_USART_SR_TC        			6
#define MCAL_USART_SR_TXE        			7
#define MCAL_USART_SR_LBD        			8
#define MCAL_USART_SR_CTS        			9

/*
 * ***********************************************************
 */
/*
 *@USART_Mode
 *Possible options for USART_Mode
 */
#define MCAL_USART_MODE_ONLY_TX 	0
#define MCAL_USART_MODE_ONLY_RX 	1
#define MCAL_USART_MODE_TXRX  	    2

/*
 *@USART_Baud
 *Possible options for USART_Baud
 */
#define MCAL_USART_STD_BAUD_1200					1200
#define MCAL_USART_STD_BAUD_2400					400
#define MCAL_USART_STD_BAUD_9600					9600
#define MCAL_USART_STD_BAUD_19200 				    19200
#define MCAL_USART_STD_BAUD_38400 				    38400
#define MCAL_USART_STD_BAUD_57600 				    57600
#define MCAL_USART_STD_BAUD_115200 				    115200
#define MCAL_USART_STD_BAUD_230400 				    230400
#define MCAL_USART_STD_BAUD_460800 				    460800
#define MCAL_USART_STD_BAUD_921600 				    921600
#define MCAL_USART_STD_BAUD_2M 					    2000000
#define MCAL_SUART_STD_BAUD_3M 					    3000000


/*
 *@USART_ParityControl
 *Possible options for USART_ParityControl
 */
#define MCAL_USART_PARITY_DISABLE   0
#define MCAL_USART_PARITY_EN_EVEN   1
#define MCAL_USART_PARITY_EN_ODD    2



/*
 *@USART_WordLength
 *Possible options for USART_WordLength
 */
#define MCAL_USART_WORDLEN_8BITS  0
#define MCAL_USART_WORDLEN_9BITS  1

/*
 *@USART_NoOfStopBits
 *Possible options for USART_NoOfStopBits
 */
#define MCAL_USART_STOPBITS_1     0
#define MCAL_USART_STOPBITS_0_5   1
#define MCAL_USART_STOPBITS_2     2
#define MCAL_USART_STOPBITS_1_5   3


/*
 *@USART_HWFlowControl
 *Possible options for USART_HWFlowControl
 */
#define MCAL_USART_HW_FLOW_CTRL_NONE    	0
#define MCAL_USART_HW_FLOW_CTRL_CTS    	1
#define MCAL_USART_HW_FLOW_CTRL_RTS    	2
#define MCAL_USART_HW_FLOW_CTRL_CTS_RTS	3


/*
 * USART flags
 */
#define MCAL_USART_FLAG_TXE 			( 1 << MCAL_USART_SR_TXE)
#define MCAL_USART_FLAG_RXNE 		    ( 1 << MCAL_USART_SR_RXNE)
#define MCAL_USART_FLAG_TC 			    ( 1 << MCAL_USART_SR_TC)

/*
 * Application states
 */
#define MCAL_USART_BUSY_IN_RX 1
#define MCAL_USART_BUSY_IN_TX 2
#define MCAL_USART_READY 0


#define MCAL_USART_EVENT_TX_CMPLT   0
#define	MCAL_USART_EVENT_RX_CMPLT   1
#define	MCAL_USART_EVENT_IDLE       2
#define	MCAL_USART_EVENT_CTS        3
#define	MCAL_USART_EVENT_PE         4
#define	MCAL_USART_ERR_FE     	   5
#define	MCAL_USART_ERR_NE    	   6
#define	MCAL_USART_ERR_ORE    	   7


void MCAL_USART_Enable(USART_RegDef_t *pUSARTx);
void MCAL_USART_Disable(USART_RegDef_t *pUSARTx);
void MCAL_USART_EnableRxOnly(USART_RegDef_t *pUSARTx);
void MCAL_USART_EnableTxOnly(USART_RegDef_t *pUSARTx);
void MCAL_USART_EnableRxTx(USART_RegDef_t *pUSARTx);
void MCAL_USART_SetWordLen8Bit(USART_RegDef_t *pUSARTx);
void MCAL_USART_SetWordLen9Bit(USART_RegDef_t *pUSARTx);
void MCAL_USART_EnableOddParity(USART_RegDef_t *pUSARTx);
void MCAL_USART_EnableEvenParity(USART_RegDef_t *pUSARTx);
void MCAL_USART_DisableParity(USART_RegDef_t *pUSARTx);
void MCAL_USART_SetStopConfig(USART_RegDef_t *pUSARTx,u8 StopBitConfig);


void MCAL_USART_EnableTXEI(USART_RegDef_t *pUSARTx);
void MCAL_USART_DisableTXEI(USART_RegDef_t *pUSARTx);
void MCAL_USART_EnableTCI(USART_RegDef_t *pUSARTx);
void MCAL_USART_DisableTCI(USART_RegDef_t *pUSARTx);
void MCAL_USART_EnableRXNI(USART_RegDef_t *pUSARTx);
void MCAL_USART_DisableRXNI(USART_RegDef_t *pUSARTx);

u8 MCAL_USART_ReadRXNI(USART_RegDef_t *pUSARTx);
u8 MCAL_USART_ReadTCI(USART_RegDef_t *pUSARTx);
u8 MCAL_USART_ReadTXEI(USART_RegDef_t *pUSARTx);


/*
 * HW flow control
 */
void MCAL_USART_EnableCTSFlowControl(USART_RegDef_t *pUSARTx);
void MCAL_USART_DisableCTSFlowControl(USART_RegDef_t *pUSARTx);
void MCAL_USART_EnableRTSFlowControl(USART_RegDef_t *pUSARTx);
void MCAL_USART_DisableRTSFlowControl(USART_RegDef_t *pUSARTx);



void MCAL_USART_SetBaudRateValue(USART_RegDef_t *pUSARTx, u32 BaudRate);

u8 MCAL_USART_GetFlagStatus(USART_RegDef_t *pUSARTx, u8 StatusFlagName);

void MCAL_USART_WriteData(USART_RegDef_t *pUSARTx, u16 Data);

u16 MCAL_USART_ReadData(USART_RegDef_t *pUSARTx);

void MCAL_USART_ClearFlag(USART_RegDef_t *pUSARTx, u8 StatusFlagName);



#endif /* STM32F407X_MCAL_INC_STM32F407X_USART_H_ */
