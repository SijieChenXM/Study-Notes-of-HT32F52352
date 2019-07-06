/*********************************************************************************************************//**
 * @file    ADC/TM_Trigger/ht32_board_config.h
 * @version $Rev:: 2814         $
 * @date    $Date:: 2018-05-17 #$
 * @brief   The header file of board configuration.
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
/* Define to prevent recursive inclusion -------------------------------------------------------------------*/
#ifndef __HT32_BOARD_CONFIG_H
#define __HT32_BOARD_CONFIG_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Settings ------------------------------------------------------------------------------------------------*/
#if defined(USE_HT32F52230_SK)
  #define HTCFG_AD0_GPIO_ID                 (GPIO_PA)
  #define HTCFG_AD0_AFIO_PIN                (AFIO_PIN_7)
  #define HTCFG_AD0_ADC_CH                  (ADC_CH_7)

  #define HTCFG_AD1_GPIO_ID                 (GPIO_PA)
  #define HTCFG_AD1_AFIO_PIN                (AFIO_PIN_0)
  #define HTCFG_AD1_ADC_CH                  (ADC_CH_0)

  #define HTCFG_AD2_GPIO_ID                 (GPIO_PA)
  #define HTCFG_AD2_AFIO_PIN                (AFIO_PIN_1)
  #define HTCFG_AD2_ADC_CH                  (ADC_CH_1)
#endif

#if defined(USE_HT32F52241_SK)
  #define HTCFG_AD0_GPIO_ID                 (GPIO_PA)
  #define HTCFG_AD0_AFIO_PIN                (AFIO_PIN_6)
  #define HTCFG_AD0_ADC_CH                  (ADC_CH_8)

  #define HTCFG_AD1_GPIO_ID                 (GPIO_PA)
  #define HTCFG_AD1_AFIO_PIN                (AFIO_PIN_0)
  #define HTCFG_AD1_ADC_CH                  (ADC_CH_2)

  #define HTCFG_AD2_GPIO_ID                 (GPIO_PA)
  #define HTCFG_AD2_AFIO_PIN                (AFIO_PIN_1)
  #define HTCFG_AD2_ADC_CH                  (ADC_CH_3)
#endif

#if defined(USE_HT32F52253_SK)
  #define HTCFG_AD0_GPIO_ID                 (GPIO_PA)
  #define HTCFG_AD0_AFIO_PIN                (AFIO_PIN_6)
  #define HTCFG_AD0_ADC_CH                  (ADC_CH_6)

  #define HTCFG_AD1_GPIO_ID                 (GPIO_PA)
  #define HTCFG_AD1_AFIO_PIN                (AFIO_PIN_0)
  #define HTCFG_AD1_ADC_CH                  (ADC_CH_0)

  #define HTCFG_AD2_GPIO_ID                 (GPIO_PA)
  #define HTCFG_AD2_AFIO_PIN                (AFIO_PIN_1)
  #define HTCFG_AD2_ADC_CH                  (ADC_CH_1)
#endif

#if defined(USE_HT32F52341_SK)
  #define HTCFG_AD0_GPIO_ID                 (GPIO_PA)
  #define HTCFG_AD0_AFIO_PIN                (AFIO_PIN_6)
  #define HTCFG_AD0_ADC_CH                  (ADC_CH_8)

  #define HTCFG_AD1_GPIO_ID                 (GPIO_PA)
  #define HTCFG_AD1_AFIO_PIN                (AFIO_PIN_0)
  #define HTCFG_AD1_ADC_CH                  (ADC_CH_2)

  #define HTCFG_AD2_GPIO_ID                 (GPIO_PA)
  #define HTCFG_AD2_AFIO_PIN                (AFIO_PIN_1)
  #define HTCFG_AD2_ADC_CH                  (ADC_CH_3)
#endif

#if defined(USE_HT32F52352_SK)
  #define HTCFG_AD0_GPIO_ID                 (GPIO_PA)
  #define HTCFG_AD0_AFIO_PIN                (AFIO_PIN_6)
  #define HTCFG_AD0_ADC_CH                  (ADC_CH_6)

  #define HTCFG_AD1_GPIO_ID                 (GPIO_PA)
  #define HTCFG_AD1_AFIO_PIN                (AFIO_PIN_0)
  #define HTCFG_AD1_ADC_CH                  (ADC_CH_0)

  #define HTCFG_AD2_GPIO_ID                 (GPIO_PA)
  #define HTCFG_AD2_AFIO_PIN                (AFIO_PIN_1)
  #define HTCFG_AD2_ADC_CH                  (ADC_CH_1)
#endif

#if defined(USE_HT32F0008_SK)
  #error "This example code does not apply to the chip you selected."
#endif

#if defined(USE_HT32F50230_SK)
  #define HTCFG_AD0_GPIO_ID                 (GPIO_PA)
  #define HTCFG_AD0_AFIO_PIN                (AFIO_PIN_2)
  #define HTCFG_AD0_ADC_CH                  (ADC_CH_4)

  #define HTCFG_AD1_GPIO_ID                 (GPIO_PA)
  #define HTCFG_AD1_AFIO_PIN                (AFIO_PIN_0)
  #define HTCFG_AD1_ADC_CH                  (ADC_CH_2)

  #define HTCFG_AD2_GPIO_ID                 (GPIO_PA)
  #define HTCFG_AD2_AFIO_PIN                (AFIO_PIN_1)
  #define HTCFG_AD2_ADC_CH                  (ADC_CH_3)
#endif

#if defined(USE_HT32F50241_SK)
  #define HTCFG_AD0_GPIO_ID                 (GPIO_PA)
  #define HTCFG_AD0_AFIO_PIN                (AFIO_PIN_6)
  #define HTCFG_AD0_ADC_CH                  (ADC_CH_8)

  #define HTCFG_AD1_GPIO_ID                 (GPIO_PA)
  #define HTCFG_AD1_AFIO_PIN                (AFIO_PIN_0)
  #define HTCFG_AD1_ADC_CH                  (ADC_CH_2)

  #define HTCFG_AD2_GPIO_ID                 (GPIO_PA)
  #define HTCFG_AD2_AFIO_PIN                (AFIO_PIN_1)
  #define HTCFG_AD2_ADC_CH                  (ADC_CH_3)
#endif

#if defined(USE_HT32F52354_SK)
  #define HTCFG_AD0_GPIO_ID                 (GPIO_PA)
  #define HTCFG_AD0_AFIO_PIN                (AFIO_PIN_6)
  #define HTCFG_AD0_ADC_CH                  (ADC_CH_6)

  #define HTCFG_AD1_GPIO_ID                 (GPIO_PA)
  #define HTCFG_AD1_AFIO_PIN                (AFIO_PIN_0)
  #define HTCFG_AD1_ADC_CH                  (ADC_CH_0)

  #define HTCFG_AD2_GPIO_ID                 (GPIO_PA)
  #define HTCFG_AD2_AFIO_PIN                (AFIO_PIN_1)
  #define HTCFG_AD2_ADC_CH                  (ADC_CH_1)
#endif

#ifdef __cplusplus
}
#endif

#endif
