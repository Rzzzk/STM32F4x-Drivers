/**
 ******************************************************************************
 ******************************************************************************
 * @file           : stm32f407x_spi.h
 * @author         : Rezk Ahmed
 * @Layer          : MCAL
 * @brief          : Ensure that all hardware information is gathered and abstracted
 *                   from the drivers layer (ECU or Board layer), and provide higher
 *                   layer APIs with access and control over the peripheral drivers.
 ******************************************************************************
 ******************************************************************************
 */

#ifndef STM32F407X_MCAL_INC_STM32F407X_SPI_H_
#define STM32F407X_MCAL_INC_STM32F407X_SPI_H_



/*
 * Memory map and register definitions
 */

#define SPI1_BASEADDR         0x40013000
#define SPI2_BASEADDR         0x40003800
#define SPI3_BASEADDR         0x40003C00
#define SPI4_BASEADDR         0x40013400
#define SPI5_BASEADDR         0x40015000
#define SPI6_BASEADDR         0x40015400


typedef struct
{
	__vo u32 CR1;
	__vo u32 CR2;
	__vo u32 SR;
	__vo u32 DR;
	__vo u32 CRCPR;
	__vo u32 RXCRCR;
	__vo u32 TXCRCR;
	__vo u32 I2SCFGR;
	__vo u32 I2SPR;
} SPI_RegDef_t;


#define SPI1      ((SPI_RegDef_t*)SPI1_BASEADDR)
#define SPI2      ((SPI_RegDef_t*)SPI2_BASEADDR)
#define SPI3      ((SPI_RegDef_t*)SPI3_BASEADDR)
#define SPI4      ((SPI_RegDef_t*)SPI4_BASEADDR)
#define SPI5      ((SPI_RegDef_t*)SPI5_BASEADDR)
#define SPI6      ((SPI_RegDef_t*)SPI6_BASEADDR)

/******************************************************************************************
 *Bit position definitions of SPI peripheral
 ******************************************************************************************/
/*
 * Bit position definitions SPI_CR1
 */
#define MCAL_SPI_CR1_CPHA     				 0
#define MCAL_SPI_CR1_CPOL      				 1
#define MCAL_SPI_CR1_MSTR     				 2
#define MCAL_SPI_CR1_BR   					 3
#define MCAL_SPI_CR1_SPE     				 6
#define MCAL_SPI_CR1_LSBFIRST   			 7
#define MCAL_SPI_CR1_SSI     				 8
#define MCAL_SPI_CR1_SSM      				 9
#define MCAL_SPI_CR1_RXONLY      		 	10
#define MCAL_SPI_CR1_DFF     			 	11
#define MCAL_SPI_CR1_CRCNEXT   			 	12
#define MCAL_SPI_CR1_CRCEN   			 	13
#define MCAL_SPI_CR1_BIDIOE     			14
#define MCAL_SPI_CR1_BIDIMODE      			15

/*
 * Bit position definitions SPI_CR2
 */
#define MCAL_SPI_CR2_RXDMAEN		 		0
#define MCAL_SPI_CR2_TXDMAEN				1
#define MCAL_SPI_CR2_SSOE				 	2
#define MCAL_SPI_CR2_FRF					4
#define MCAL_SPI_CR2_ERRIE					5
#define MCAL_SPI_CR2_RXNEIE				 	6
#define MCAL_SPI_CR2_TXEIE					7


/*
 * Bit position definitions SPI_SR
 */
#define MCAL_SPI_SR_RXNE					0
#define MCAL_SPI_SR_TXE				 		1
#define MCAL_SPI_SR_CHSIDE				 	2
#define MCAL_SPI_SR_UDR					 	3
#define MCAL_SPI_SR_CRCERR				 	4
#define MCAL_SPI_SR_MODF					5
#define MCAL_SPI_SR_OVR					 	6
#define MCAL_SPI_SR_BSY					 	7
#define MCAL_SPI_SR_FRE					 	8

/*
 * @SPI_DeviceMode
 */
#define MCAL_SPI_DEVICE_MODE_MASTER    1
#define MCAL_SPI_DEVICE_MODE_SLAVE     0


/*
 * @SPI_BusConfig
 */
#define MCAL_SPI_BUS_CONFIG_FD                1
#define MCAL_SPI_BUS_CONFIG_HD                2
#define MCAL_SPI_BUS_CONFIG_SIMPLEX_RXONLY    3

/*
 * @SPI_SclkSpeed
 */
#define MCAL_SPI_SCLK_SPEED_DIV2             	0
#define MCAL_SPI_SCLK_SPEED_DIV4             	1
#define MCAL_SPI_SCLK_SPEED_DIV8             	2
#define MCAL_SPI_SCLK_SPEED_DIV16             	3
#define MCAL_SPI_SCLK_SPEED_DIV32             	4
#define MCAL_SPI_SCLK_SPEED_DIV64             	5
#define MCAL_SPI_SCLK_SPEED_DIV128             	6
#define MCAL_SPI_SCLK_SPEED_DIV256             	7

/*
 * @SPI_DFF "DataFrameFormate"
 */
#define MCAL_SPI_DFF_8BITS  	0
#define MCAL_SPI_DFF_16BITS     1

/*
 * @CPOL
 */
#define MCAL_SPI_CPOL_HIGH       1
#define MCAL_SPI_CPOL_LOW        0

/*
 * @CPHA
 */
#define MCAL_SPI_CPHA_HIGH 		1
#define MCAL_SPI_CPHA_LOW 		0

/*
 * @SPI_SSM
 */
#define MCAL_SPI_SSM_EN    		 1
#define MCAL_SPI_SSM_DI     	 0


/*
 * SPI related status flags definitions
 */
#define MCAL_SPI_TXE_FLAG            (1 << MCAL_SPI_SR_TXE)
#define MCAL_SPI_RXNE_FLAG           (1 << MCAL_SPI_SR_RXNE)
#define MCAL_SPI_BUSY_FLAG           (1 << MCAL_SPI_SR_BSY)
#define MCAL_SPI_OVR_FLAG            (1 << MCAL_SPI_SR_OVR)
/*
 * SPI related interrupt sources
 */
#define MCAL_SPI_TXE_INT                  MCAL_SPI_CR2_TXEIE
#define MCAL_SPI_RXNE_INT                 MCAL_SPI_CR2_RXNEIE
#define MCAL_SPI_ERR_INT                  MCAL_SPI_CR2_ERRIE

#define MCAL_SPI_CODE_TO_BASADDR(x)         ( (x == 0)?SPI1:\
		                                      (x == 1)?SPI2:\
			                                  (x == 2)?SPI3:\
						                      (x == 3)?SPI4:\
								              (x == 4)?SPI5:\
										      (x == 5)?SPI6:0)

void MCAL_PSI_Enable(SPI_RegDef_t *pPSIx);
void MCAL_PSI_Disable(SPI_RegDef_t *pPSIx);
void MCAL_SPI_SetDeviceMode(SPI_RegDef_t *pPSIx,u8 DeviceMode);
void MCAL_SPI_SetBusConfig(SPI_RegDef_t *pPSIx,u8 BusConfig);
void MCAL_SPI_SetClkSpeed(SPI_RegDef_t *pPSIx,u8 SclkSpeed);
void MCAL_SPI_SetDataFrameFormate(SPI_RegDef_t *pPSIx,u8 DataFrameFormate);
void MCAL_SPI_SetCPOL(SPI_RegDef_t *pPSIx,u8 CPOL);
void MCAL_SPI_SetCPHA(SPI_RegDef_t *pPSIx,u8 CPHA);


void MCAL_SPI_Write(SPI_RegDef_t *pPSIx, u16 Data);
u16 MCAL_SPI_Read(SPI_RegDef_t *pPSIx);


void MCAL_SPI_EnableTxInterrupt(SPI_RegDef_t *pPSIx);
void MCAL_SPI_DisableTxInterrupt(SPI_RegDef_t *pPSIx);
void MCAL_SPI_EnableRxInterrupt(SPI_RegDef_t *pPSIx);
void MCAL_SPI_DisableRxInterrupt(SPI_RegDef_t *pPSIx);

u8 MCAL_SPI_GetInterruptStatus(SPI_RegDef_t *pPSIx,u8 IntSourceName);
u8 MCAL_SPI_GetFlagStatus(SPI_RegDef_t *pSPIx, u8 StatusFlagName);

void MCAL_SPI_ClearOVFLag(SPI_RegDef_t *pSPIx);

#endif /* STM32F407X_MCAL_INC_STM32F407X_SPI_H_ */
