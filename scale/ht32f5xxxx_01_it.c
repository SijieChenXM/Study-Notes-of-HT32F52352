/*********************************************************************************************************//**
 * @file    GPIO/InputOutput/ht32f5xxxx_01_it.c
 * @version $Rev:: 1704         $
 * @date    $Date:: 2017-08-17#$
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

/** @addtogroup HT32_Series_Peripheral_Examples HT32 Peripheral Examples
  * @{
  */

/** @addtogroup GPIO_Examples GPIO
  * @{
  */

/** @addtogroup InputOutput
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
 * @brief   This function handles BFTM0 interrupt.
 * @retval  None
 ************************************************************************************************************/
extern const unsigned short SEG_TAB[];
int flag = 0;
extern unsigned long value;

void BFTM0_IRQHandler(void)
{
		switch (flag) {
			case 0: 
				GPIO_WriteOutData(HT_GPIOC,0x01);
				GPIO_WriteOutData(HT_GPIOB,SEG_TAB[value%10]);
				flag++;
				break;
			case 1: 
				GPIO_WriteOutData(HT_GPIOC,0x02);
				GPIO_WriteOutData(HT_GPIOB,SEG_TAB[(value/10)%10]);
				flag++;
				break;
			case 2:
				GPIO_WriteOutData(HT_GPIOC,0x04);
				GPIO_WriteOutData(HT_GPIOB,SEG_TAB[(value/100)%10]);
				flag++;
				break;
			case 3:
				GPIO_WriteOutData(HT_GPIOC,0x08);
				GPIO_WriteOutData(HT_GPIOB,SEG_TAB[(value/1000)%10]);
				flag = 0;
				break;
		}

    BFTM_ClearFlag(HT_BFTM0);
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
