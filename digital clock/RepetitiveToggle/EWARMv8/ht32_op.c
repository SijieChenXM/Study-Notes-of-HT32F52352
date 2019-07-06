/*********************************************************************************************************//**
 * @file    ht32_op.c
 * @version V1.01
 * @date    2017-07-13
 * @brief   The option byre settings of HT32 Series.
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

/* Settings ------------------------------------------------------------------------------------------------*/
/* !!! Note: One OB_PP bit for setting n Pages. Check FMC chapter of User Manual for detailed.              */
#define OB_PP0    (0x00000000)    /*!< Main Flash Page Erase/Program Protection                             */
#define OB_PP1    (0x00000000)    /*!< Main Flash Page Erase/Program Protection                             */
#define OB_PP2    (0x00000000)    /*!< Main Flash Page Erase/Program Protection                             */
#define OB_PP3    (0x00000000)    /*!< Main Flash Page Erase/Program Protection                             */
#define OB_CP0    (0)             /*!< Flash Security Protection                                            */
#define OB_CP1    (0)             /*!< Option Byte Erase/Program Protection                                 */

//#define BOOT_OPT  (0)             /*!< Bootloader Options. 1: Enable, 0: Disable                            */
//#define BOOTOPTV  (1500)          /*!< Bootloader waiting time baesed on ms. Range 1500~14200ms, Steps: 50) */

#define CK_CODE   (0xFFFFFFFF)    /*!< Writer checksum: code                                                */
#define CK_DATA   (0xFFFFFFFF)    /*!< Writer checksum: data                                                */
#define CK_CODEOP (0xFFFFFFFF)    /*!< Writer checksum: code + option                                       */

#define WDT_OPT   (0)             /*!< WDT had been open automatically after MCU Power On, and WDT Reload 
                                       Value = 8s. Note : Not Support HT32 full Series. 
                                       HT32F1755_65 does not support the function.
                                       HT32F1653_54 does not support the function.
                                       HT32F1655_56 does not support the function.
                                       HT32F12345 does not support the function.
                                       HT32F12365_66 does not support the function.
                                       HT32F52220_30 does not support the function.
                                       HT32F52231_41 does not support the function.
                                       HT32F52331_41 does not support the function.
                                       HT32F52342_52 does not support the function.
                                       HT32F52243_53 does not support the function.                         */
/* How to use-----------------------------------------------------------------------------------------------*/
/*
    Step1: Modify the above Option Bytes value (OB_PP0, OB_PP1, OB_PP2, OB_PP3, OB_CP0, OB_CP1).

    Step2: Add "HT32Option" into keep symbols setting.
           Project Option -> Linker -> Input -> Keep symbols: (one pre line) -> Add HT32Option
*/

/*----------------------------------------------------------------------------------------------------------*/
/* DO NOT MODIFY                                                                                            */
/*----------------------------------------------------------------------------------------------------------*/
#define OPT_RES   (0xFFFFFFFF)

//#if (BOOT_OPT == 1)
//  #define BOOTOPT (0xFFFFFF00 | ((BOOTOPTV - 1500)/50))
//#else
//  #define BOOTOPT (0xFFFFFFFF)
//#endif

#if (WDT_OPT == 1)
  #if defined(USE_HT32F52220_30) || \
      defined(USE_HT32F52231_41) || \
      defined(USE_HT32F52331_41) || \
      defined(USE_HT32F52342_52) || \
      defined(USE_HT32F52243_53)
    #error "USE_HT32_CHIP does not support WDT_OPT!"
  #elif defined(USE_HT32F50220_30) || \
        defined(USE_HT32F50231_41)
      #define WDT_MAGIC_KEY_AREA0   (0xFFFFFFFF)
      #define WDT_MAGIC_KEY_AREA1   (0xFFFF7A92)
  #else
    #define WDT_MAGIC_KEY_AREA0   (0xFFFF7A92)
    #define WDT_MAGIC_KEY_AREA1   (0xFFFFFFFF)
  #endif
#else
  #define WDT_MAGIC_KEY_AREA0   (0xFFFFFFFF)
  #define WDT_MAGIC_KEY_AREA1   (0xFFFFFFFF)
#endif
#if (OB_PP0 == 0 && OB_PP1 == 0 && OB_PP2 == 0 && OB_PP3 == 0 && OB_CP0 == 0 && OB_CP1 == 0)
  #define OPT_CK (0xFFFFFFFF)
#else
  #define OPT_CK ((unsigned long)(~OB_PP0 + ~OB_PP1 + ~OB_PP2 + ~OB_PP3 + ~(OB_CP0 | OB_CP1 << 1)))
#endif

#pragma section = "HT32_OPTIONS"
__root const unsigned long HT32Option[15] @ "HT32_OPTIONS" = {
  ~OB_PP0,
  ~OB_PP1,
  ~OB_PP2,
  ~OB_PP3,
  ~(OB_CP0 | OB_CP1 << 1),
  OPT_RES,
  OPT_RES,
  OPT_RES,
  OPT_CK,
  OPT_RES,
  OPT_RES,
  WDT_MAGIC_KEY_AREA0,
  CK_CODE,
  CK_DATA,
  CK_CODEOP,
};
#if defined(USE_HT32F50220_30) || \
    defined(USE_HT32F50231_41)
__root const unsigned long HT32WDT_OPT1[1] @ "HT32_OPT_WDT_AREA1" = {
  WDT_MAGIC_KEY_AREA1,
};
#endif