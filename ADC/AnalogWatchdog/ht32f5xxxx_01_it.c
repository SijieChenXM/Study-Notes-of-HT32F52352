/*********************************************************************************************************//**
 * @file    ADC/AnalogWatchdog/ht32f5xxxx_01_it.c
 * @version $Rev:: 1704         $
 * @date    $Date:: 2017-08-17 #$
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

/** @addtogroup AnalogWatchdog
  * @{
  */


/* Private function prototypes -----------------------------------------------------------------------------*/
static void _Delay(vu32 count);

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
  if (ADC_GetIntStatus(HT_ADC, ADC_INT_AWD_LOWER))
  {
    ADC_ClearIntPendingBit(HT_ADC, ADC_INT_AWD_LOWER);
    HT32F_DVB_LEDOn(HT_LED2);
    _Delay(30);
    HT32F_DVB_LEDOff(HT_LED2);
  }

  if (ADC_GetIntStatus(HT_ADC, ADC_INT_AWD_UPPER))
  {
    ADC_ClearIntPendingBit(HT_ADC, ADC_INT_AWD_UPPER);
    HT32F_DVB_LEDOn(HT_LED1);
    _Delay(30);
    HT32F_DVB_LEDOff(HT_LED1);
  }
}

/* Private functions ---------------------------------------------------------------------------------------*/

/*********************************************************************************************************//**
 * @brief   Delay function
 * @retval  None
 ************************************************************************************************************/
static void _Delay(vu32 count)
{
  while (count--);
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
