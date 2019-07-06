/*********************************************************************************************************//**
 * @file    ADC/TM_Trigger_with_Delay/ht32f5xxxx_01_it.c
 * @version $Rev:: 1209         $
 * @date    $Date:: 2016-10-17 #$
 * @brief   This file provides all interrupt service routine.
 *************************************************************************************************************
 * @attention
 *
 * Firmware Disclaimer Information
 *
 * 1. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, which is supplied by Holtek Semiconductor Inc., (hereinafter referred to as "HOLTEK") is the
 *    proprietary and confidential intellectual property of HOLTEK, and is protected by copyright law and
 *    other intellectual property laws.
 *
 * 2. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, is confidential information belonging to HOLTEK, and must not be disclosed to any third parties
 *    other than HOLTEK and the customer.
 *
 * 3. The program technical documentation, including the code, is provided "as is" and for customer reference
 *    only. After delivery by HOLTEK, the customer shall use the program technical documentation, including
 *    the code, at their own risk. HOLTEK disclaims any expressed, implied or statutory warranties, including
 *    the warranties of merchantability, satisfactory quality and fitness for a particular purpose.
 *
 * <h2><center>Copyright (C) Holtek Semiconductor Inc. All rights reserved</center></h2>
 ************************************************************************************************************/

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"
#include "ht32_board.h"

/** @addtogroup HT32_Series_Peripheral_Examples HT32 Peripheral Examples
  * @{
  */

/** @addtogroup ADC_Examples ADC
  * @{
  */

/** @addtogroup TM_Trigger_with_Delay
  * @{
  */


/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
 * @brief   This function handles NMI exception.
 * @retval  None
 ************************************************************************************************************/
void NMI_Handler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles Hard Fault exception.
 * @retval  None
 ************************************************************************************************************/
void HardFault_Handler(void)
{
  while (1);
}

/*********************************************************************************************************//**
 * @brief   This function handles SVCall exception.
 * @retval  None
 ************************************************************************************************************/
void SVC_Handler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles PendSVC exception.
 * @retval  None
 ************************************************************************************************************/
void PendSV_Handler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles SysTick Handler.
 * @retval  None
 ************************************************************************************************************/
void SysTick_Handler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles ADC interrupt.
 * @retval  None
 ************************************************************************************************************/
void ADC_IRQHandler(void)
{
  extern u32 gADC_Result[3];
  extern vu32 gADC_CycleEndOfConversion;
  if (ADC_GetIntStatus(HT_ADC, ADC_INT_SINGLE_EOC) == SET)
  {
    ADC_ClearIntPendingBit(HT_ADC, ADC_FLAG_SINGLE_EOC);
    HT32F_DVB_LEDToggle(HT_LED2);
  }

  if (ADC_GetIntStatus(HT_ADC, ADC_INT_CYCLE_EOC) == SET)
  {
    HT32F_DVB_LEDToggle(HT_LED3);
    ADC_ClearIntPendingBit(HT_ADC, ADC_FLAG_CYCLE_EOC);
    gADC_CycleEndOfConversion = TRUE;
    gADC_Result[0] = HT_ADC->DR[0] & 0x0FFF;
    gADC_Result[1] = HT_ADC->DR[1] & 0x0FFF;
    gADC_Result[2] = HT_ADC->DR[2] & 0x0FFF;
  }
}

/*********************************************************************************************************//**
 * @brief   This function handles GPTM interrupt.
 * @retval  None
 ************************************************************************************************************/
void GPTM0_IRQHandler(void)
{
  if (TM_GetIntStatus(HT_GPTM0, TM_INT_CH3CC) == SET)
  {
    TM_ClearIntPendingBit(HT_GPTM0, TM_INT_CH3CC);
    HT32F_DVB_LEDToggle(HT_LED1);
  }
}


/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
