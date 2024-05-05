/**
 ******************************************************************************
 ******************************************************************************
 * @file           : cortex_m4.h
 * @author         : Rezk Ahmed
 * @Layer          : MCAL
 * @brief          : Ensure that all hardware information is gathered and abstracted
 *                   from the drivers layer (ECU or Board layer), and provide higher
 *                   layer APIs with access and control over the peripheral drivers.
 ******************************************************************************
 ******************************************************************************
 */

#ifndef CORTEX_M4_MCAL_INC_CORTEX_M4_H_
#define CORTEX_M4_MCAL_INC_CORTEX_M4_H_

/***********************************************************
 *
 *                     NVIC
 *
 * *********************************************************
 */

#define NVIC_BASE_ADDRESS      0xE000E100

#define NVIC_ISER0  *((__vo u32*)0xE000E100)/*Enable external interrupt from 0  to 31*/
#define NVIC_ISER1  *((__vo u32*)0xE000E104)/*Enable external interrupt from 32 to 63*/

#define NVIC_ICER0  *((__vo u32*)0xE000E180)/*Disable external interrupt from 0   to 31*/
#define NVIC_ICER1  *((__vo u32*)0xE000E184)/*Disable external interrupt from 32  to 63*/

#define NVIC_ISPR0  *((__vo u32*)0xE000E200)/*Set pending flag register from 0  to 31*/
#define NVIC_ISPR1  *((__vo u32*)0xE000E204)/*Set pending flag register from 32 to 63*/

#define NVIC_ICPR0  *((__vo u32*)0xE000E280)/*Clear pending flag register from 0  to 31*/
#define NVIC_ICPR1  *((__vo u32*)0xE000E284)/*Clear pending flag register from 0  to 31*/

#define NVIC_IABR0  *((__vo u32*)0xE000E300)/*Interrupt active flag status from 0  to 31*/
#define NVIC_IABR1  *((__vo u32*)0xE000E304)/*Interrupt active flag status from 32 to 63*/


#define SCB_AIRCR   *((__vo u32*)0xE000ED0C)
#define NVIC_IPR     ((__vo u8*)0xE000E400)



#define NO_PR_BITS_IMPLEMENTED      4

#define MCAL_NonMaskableInt_IRQn         (-14)    /*!< 2 Non Maskable Interrupt                                          */
#define MCAL_MemoryManagement_IRQn       (-12)    /*!< 4 Cortex-M4 Memory Management Interrupt                           */
#define MCAL_BusFault_IRQn               (-11)    /*!< 5 Cortex-M4 Bus Fault Interrupt                                   */
#define MCAL_UsageFault_IRQn             (-10)    /*!< 6 Cortex-M4 Usage Fault Interrupt                                 */
#define MCAL_SVCall_IRQn                 (-5)     /*!< 11 Cortex-M4 SV Call Interrupt                                    */
#define MCAL_DebugMonitor_IRQn           (-4)     /*!< 12 Cortex-M4 Debug Monitor Interrupt                              */
#define MCAL_PendSV_IRQn                 (-2)     /*!< 14 Cortex-M4 Pend SV Interrupt                                    */
#define MCAL_SysTick_IRQn                (-1)     /*!< 15 Cortex-M4 System Tick Interrupt                                */
#define MCAL_WWDG_IRQn                   (0)      /*!< Window WatchDog Interrupt                                         */
#define MCAL_PVD_IRQn                    (1)      /*!< PVD through EXTI Line detection Interrupt                         */
#define MCAL_TAMP_STAMP_IRQn             (2)      /*!< Tamper and TimeStamp interrupts through the EXTI line             */
#define MCAL_RTC_WKUP_IRQn               (3)      /*!< RTC Wakeup interrupt through the EXTI line                        */
#define MCAL_FLASH_IRQn                  (4)      /*!< FLASH global Interrupt                                            */
#define MCAL_RCC_IRQn                    (5)      /*!< RCC global Interrupt                                              */
#define MCAL_EXTI0_IRQn                  (6)      /*!< EXTI Line0 Interrupt                                              */
#define MCAL_EXTI1_IRQn                  (7)      /*!< EXTI Line1 Interrupt                                              */
#define MCAL_EXTI2_IRQn                  (8)      /*!< EXTI Line2 Interrupt                                              */
#define MCAL_EXTI3_IRQn                  (9)      /*!< EXTI Line3 Interrupt                                              */
#define MCAL_EXTI4_IRQn                  (10)     /*!< EXTI Line4 Interrupt                                              */
#define MCAL_DMA1_Stream0_IRQn           (11)     /*!< DMA1 Stream 0 global Interrupt                                    */
#define MCAL_DMA1_Stream1_IRQn           (12)     /*!< DMA1 Stream 1 global Interrupt                                    */
#define MCAL_DMA1_Stream2_IRQn           (13)     /*!< DMA1 Stream 2 global Interrupt                                    */
#define MCAL_DMA1_Stream3_IRQn           (14)     /*!< DMA1 Stream 3 global Interrupt                                    */
#define MCAL_DMA1_Stream4_IRQn           (15)     /*!< DMA1 Stream 4 global Interrupt                                    */
#define MCAL_DMA1_Stream5_IRQn           (16)     /*!< DMA1 Stream 5 global Interrupt                                    */
#define MCAL_DMA1_Stream6_IRQn           (17)     /*!< DMA1 Stream 6 global Interrupt                                    */
#define MCAL_ADC_IRQn                    (18)     /*!< ADC1, ADC2 and ADC3 global Interrupts                             */
#define MCAL_CAN1_TX_IRQn                (19)     /*!< CAN1 TX Interrupt                                                 */
#define MCAL_CAN1_RX0_IRQn               (20)     /*!< CAN1 RX0 Interrupt                                                */
#define MCAL_CAN1_RX1_IRQn               (21)     /*!< CAN1 RX1 Interrupt                                                */
#define MCAL_CAN1_SCE_IRQn               (22)     /*!< CAN1 SCE Interrupt                                                */
#define MCAL_EXTI9_5_IRQn                (23)     /*!< External Line[9:5] Interrupts                                     */
#define MCAL_TIM1_BRK_TIM9_IRQn          (24)     /*!< TIM1 Break interrupt and TIM9 global interrupt                    */
#define MCAL_TIM1_UP_TIM10_IRQn          (25)     /*!< TIM1 Update Interrupt and TIM10 global interrupt                  */
#define MCAL_TIM1_TRG_COM_TIM11_IRQn     (26)     /*!< TIM1 Trigger and Commutation Interrupt and TIM11 global interrupt */
#define MCAL_TIM1_CC_IRQn                (27)     /*!< TIM1 Capture Compare Interrupt                                    */
#define MCAL_TIM2_IRQn                   (28)     /*!< TIM2 global Interrupt                                             */
#define MCAL_TIM3_IRQn                   (29)     /*!< TIM3 global Interrupt                                             */
#define MCAL_TIM4_IRQn                   (30)     /*!< TIM4 global Interrupt                                             */
#define MCAL_I2C1_EV_IRQn                (31)     /*!< I2C1 Event Interrupt                                              */
#define MCAL_I2C1_ER_IRQn                (32)     /*!< I2C1 Error Interrupt                                              */
#define MCAL_I2C2_EV_IRQn                (33)     /*!< I2C2 Event Interrupt                                              */
#define MCAL_I2C2_ER_IRQn                (34)     /*!< I2C2 Error Interrupt                                              */
#define MCAL_SPI1_IRQn                   (35)     /*!< SPI1 global Interrupt                                             */
#define MCAL_SPI2_IRQn                   (36)     /*!< SPI2 global Interrupt                                             */
#define MCAL_USART1_IRQn                 (37)     /*!< USART1 global Interrupt                                           */
#define MCAL_USART2_IRQn                 (38)     /*!< USART2 global Interrupt                                           */
#define MCAL_USART3_IRQn                 (39)     /*!< USART3 global Interrupt                                           */
#define MCAL_EXTI15_10_IRQn              (40)     /*!< External Line[15:10] Interrupts                                   */
#define MCAL_RTC_Alarm_IRQn              (41)     /*!< RTC Alarm (A and B) through EXTI Line Interrupt                   */
#define MCAL_OTG_FS_WKUP_IRQn            (42)     /*!< USB OTG FS Wakeup through EXTI line interrupt                     */
#define MCAL_TIM8_BRK_TIM12_IRQn         (43)     /*!< TIM8 Break Interrupt and TIM12 global interrupt                   */
#define MCAL_TIM8_UP_TIM13_IRQn          (44)     /*!< TIM8 Update Interrupt and TIM13 global interrupt                  */
#define MCAL_TIM8_TRG_COM_TIM14_IRQn     (45)     /*!< TIM8 Trigger and Commutation Interrupt and TIM14 global interrupt */
#define MCAL_TIM8_CC_IRQn                (46)     /*!< TIM8 Capture Compare global interrupt                             */
#define MCAL_DMA1_Stream7_IRQn           (47)     /*!< DMA1 Stream7 Interrupt                                            */
#define MCAL_FSMC_IRQn                   (48)     /*!< FSMC global Interrupt                                             */
#define MCAL_SDIO_IRQn                   (49)     /*!< SDIO global Interrupt                                             */
#define MCAL_TIM5_IRQn                   (50)     /*!< TIM5 global Interrupt                                             */
#define MCAL_SPI3_IRQn                   (51)     /*!< SPI3 global Interrupt                                             */
#define MCAL_UART4_IRQn                  (52)     /*!< UART4 global Interrupt                                            */
#define MCAL_UART5_IRQn                  (53)     /*!< UART5 global Interrupt                                            */
#define MCAL_TIM6_DAC_IRQn               (54)     /*!< TIM6 global and DAC1&2 underrun error  interrupts                 */
#define MCAL_TIM7_IRQn                   (55)     /*!< TIM7 global interrupt                                             */
#define MCAL_DMA2_Stream0_IRQn           (56)     /*!< DMA2 Stream 0 global Interrupt                                    */
#define MCAL_DMA2_Stream1_IRQn           (57)     /*!< DMA2 Stream 1 global Interrupt                                    */
#define MCAL_DMA2_Stream2_IRQn           (58)     /*!< DMA2 Stream 2 global Interrupt                                    */
#define MCAL_DMA2_Stream3_IRQn           (59)     /*!< DMA2 Stream 3 global Interrupt                                    */
#define MCAL_DMA2_Stream4_IRQn           (60)     /*!< DMA2 Stream 4 global Interrupt                                    */
#define MCAL_ETH_IRQn                    (61)     /*!< Ethernet global Interrupt                                         */
#define MCAL_ETH_WKUP_IRQn               (62)     /*!< Ethernet Wakeup through EXTI line Interrupt                       */
#define MCAL_CAN2_TX_IRQn                (63)     /*!< CAN2 TX Interrupt                                                 */
#define MCAL_CAN2_RX0_IRQn               (64)     /*!< CAN2 RX0 Interrupt                                                */
#define MCAL_CAN2_RX1_IRQn               (65)     /*!< CAN2 RX1 Interrupt                                                */
#define MCAL_CAN2_SCE_IRQn               (66)     /*!< CAN2 SCE Interrupt                                                */
#define MCAL_OTG_FS_IRQn                 (67)     /*!< USB OTG FS global Interrupt                                       */
#define MCAL_DMA2_Stream5_IRQn           (68)     /*!< DMA2 Stream 5 global interrupt                                    */
#define MCAL_DMA2_Stream6_IRQn           (69)     /*!< DMA2 Stream 6 global interrupt                                    */
#define MCAL_DMA2_Stream7_IRQn           (70)     /*!< DMA2 Stream 7 global interrupt                                    */
#define MCAL_USART6_IRQn                 (71)     /*!< USART6 global interrupt                                           */
#define MCAL_I2C3_EV_IRQn                (72)     /*!< I2C3 event interrupt                                              */
#define MCAL_I2C3_ER_IRQn                (73)     /*!< I2C3 error interrupt                                              */
#define MCAL_OTG_HS_EP1_OUT_IRQn         (74)     /*!< USB OTG HS End Point 1 Out global interrupt                       */
#define MCAL_OTG_HS_EP1_IN_IRQn          (75)     /*!< USB OTG HS End Point 1 In global interrupt                        */
#define MCAL_OTG_HS_WKUP_IRQn            (76)     /*!< USB OTG HS Wakeup through EXTI interrupt                          */
#define MCAL_OTG_HS_IRQn                 (77)     /*!< USB OTG HS global interrupt                                       */
#define MCAL_DCMI_IRQn                   (78)     /*!< DCMI global interrupt                                             */
#define MCAL_RNG_IRQn                    (80)     /*!< RNG global Interrupt                                              */
#define MCAL_FPU_IRQn                    (81)     /*!< FPU global interrupt                                               */



#define MCAL_NVIC_4_BIT_GROUP_0_BIT_SUB       0
#define MCAL_NVIC_3_BIT_GROUP_1_BIT_SUB       1
#define MCAL_NVIC_2_BIT_GROUP_2_BIT_SUB       2
#define MCAL_NVIC_1_BIT_GROUP_3_BIT_SUB       3
#define MCAL_NVIC_0_BIT_GROUP_4_BIT_SUB       4


ES_t MCAL_SCB_ConfigPriorityGrouping(u32 PriorityGroupingField);
ES_t MCAL_NVIC_EnableIRQn(u8 IRQn);
ES_t MCAL_NVIC_DisableIRQn(u8 IRQn);
ES_t MCAL_NVIC_GetEnableIRQn(u8 IRQn,u8 *IRQnEnOrDi);
ES_t MCAL_NVIC_SetPendingIRQn(u8 IRQn);
ES_t MCAL_NVIC_ClearPendingIRQn(u8 IRQn);
ES_t MCAL_NVIC_GetPendingIRQn(u8 IRQn,u8 *IRQnPend);
ES_t MCAL_NVIC_GetActiveIRQn(u8 IRQn,u8 *IRQnAct);
ES_t MCAL_NVIC_SetPriorityIRQn(u8 IRQn,u8 GrPri,u8 SubPri);



/***********************************************************
 *
 *                     SysTick
 *
 * *********************************************************
 */



typedef struct
{
  __vo u32 CTRL;                   /* SysTick Control and Status Register */
  __vo u32 LOAD;                   /* SysTick Reload Value Register       */
  __vo u32 VAL;                    /* SysTick Current Value Register A write of any value clears the field to 0, and also clears the SYST_CSR COUNTFLAG bit to 0   */
  __vo u32 CALIB;                  /* SysTick Calibration Register        */
} SysTick_t;

#define SysTick                  ((SysTick_t *)0xE000E010)



#define SYST_CTRL_COUNTFLAG                          16  /* Returns 1 if timer counted to 0 since last time this was read */
#define SYST_CTRL_CLKSOURCE                          2   /* Indicates the clock source        */
#define SYST_CTRL_TICKINT                            1   /* Enables SysTick exception request */
#define SYST_CTRL_ENABLE                             0   /* Enables the counter:              */


#define MCAL_SYSTICK_BUSY_WAIT                        0
#define MCAL_SYSTICK_SINGLE_TICK                      1
#define MCAL_SYSTICK_PERIODIC_TICK                    2



ES_t MCAL_SysTick_EnableCounter(void);
ES_t MCAL_SysTick_DisableCounter(void);

ES_t MCAL_SysTick_EnableExceptionRequest(void);
ES_t MCAL_SysTick_DisableExceptionRequest(void);

ES_t MCAL_SysTick_SelectCPUClockSource(void);
ES_t MCAL_SysTick_SelectExternalClockSource(void);

ES_t MCAL_SysTick_ClearTheCounter(void);
ES_t MCAL_SysTick_SetReloadValue(u32 RelVal);

ES_t MCAL_SysTick_BaisyWait(u32 TimeOut);
ES_t MCAL_SysTick_SingleTick(void (*CallBackFuc)(void));
ES_t MCAL_SysTick_PeriodicTick(void (*CallBackFuc)(void));



#endif /* CORTEX_M4_MCAL_INC_CORTEX_M4_H_ */
