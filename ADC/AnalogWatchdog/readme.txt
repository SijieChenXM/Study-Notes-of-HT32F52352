/**
 @page ADC_AnalogWatchdog

 @verbatim
 * @file    ADC/AnalogWatchdog/readme.txt
 * @version V1.00
 * @date    2014-06-30
 * @brief   Description of ADC analog watchdog example.
 @endverbatim

@par Example Description:

This example shows how to use the ADC analog watchdog to monitor input voltage level of ADC channel. The
program do the configuration below:
- ADCLK frequency: CK_AHB/64
- Conversion time: (1/(CK_AHB/64)) * 14
- Continuous mode, Length = 1, Sub Length = 1. Trigger by software.
- Enable Analog watchdog function. Upper threshold = 3000, Lower threshold = 1000.

Therefore, the ADC interrupt will occur when the ADC channel's level is above 3000 or below 1000. The ADC
interrupt service routine will turn on/off LED1 or LED2 depending on the input voltage level of ADC channel.

@par Directory Contents:

- ADC/AnalogWatchdog/main.c               Main program
- ADC/AnalogWatchdog/ht32fxxxx_it.c       Interrupt handlers

@par Hardware and Software Environment:

- Adjust the potentiometer to change the input level and observe the LEDs.
- This example can be run on HT32 Series development board.

@par Firmware Disclaimer Information

1. The customer hereby acknowledges and agrees that the program technical documentation, including the
   code, which is supplied by Holtek Semiconductor Inc., (hereinafter referred to as "HOLTEK") is the
   proprietary and confidential intellectual property of HOLTEK, and is protected by copyright law and
   other intellectual property laws.

2. The customer hereby acknowledges and agrees that the program technical documentation, including the
   code, is confidential information belonging to HOLTEK, and must not be disclosed to any third parties
   other than HOLTEK and the customer.

3. The program technical documentation, including the code, is provided "as is" and for customer reference
   only. After delivery by HOLTEK, the customer shall use the program technical documentation, including
   the code, at their own risk. HOLTEK disclaims any expressed, implied or statutory warranties, including
   the warranties of merchantability, satisfactory quality and fitness for a particular purpose.

 * <h2><center>Copyright (C) Holtek Semiconductor Inc. All rights reserved</center></h2>
 */
