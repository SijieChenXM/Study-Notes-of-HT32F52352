/*********************************************************************************************************//**
 * @file    ADC/TM_Trigger/main.c
 * @version $Rev:: 2366         $
 * @date    $Date:: 2017-12-20 #$
 * @brief   Main program.
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
#include "ht32_board_config.h"

/** @addtogroup HT32_Series_Peripheral_Examples HT32 Peripheral Examples
  * @{
  */

/** @addtogroup ADC_Examples ADC
  * @{
  */

/** @addtogroup TM_Trigger

  * @{
  */

/*
  PB0~PB6：七段数码管对应端口
	PC0~PC3：数码管使能端
	PA6:ADC使用到的管脚
	
*/

/* Private function prototypes -----------------------------------------------------------------------------*/
void ADC_Configuration(void);
void TM_Configuration(void);
static void __Delay(u32 count);
void display(u16 ge,u16 shi,u16 bai,u16 qian);



const u16 SEG_TAB[] = {		      //七段数码管
			         0x3F,0x06,0x5B,0x4F,0x66,
			         0x6D,0x7D,0x07,0x7F,0x67};

const u16 POS_TAB[] = {
					 0x01,0x02,0x04,0x08};


/* Global variables ----------------------------------------------------------------------------------------*/
u32 gADC_Result[3];   
vu32 gADC_CycleEndOfConversion;
u16 ge,shi,bai,qian;
u32 j;


/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
  RETARGET_Configuration();           /* Retarget Related configuration                                     */

  /* Enable peripheral clocks of ADC, GPTM0                                                                 */
  {
  CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
  CKCUClock.Bit.AFIO       = 1;
  CKCUClock.Bit.GPTM0      = 1;
  CKCUClock.Bit.ADC        = 1;
	CKCUClock.Bit.PB       = 1;
	CKCUClock.Bit.PC       = 1;   
  CKCU_PeripClockConfig(CKCUClock, ENABLE);
  }

  HT32F_DVB_LEDInit(HT_LED1);
  HT32F_DVB_LEDInit(HT_LED2);
  HT32F_DVB_LEDInit(HT_LED3);
	
	AFIO_GPxConfig(GPIO_PB, AFIO_PIN_ALL, AFIO_MODE_DEFAULT);
  AFIO_GPxConfig(GPIO_PC, AFIO_PIN_ALL, AFIO_MODE_DEFAULT);
	
	GPIO_DirectionConfig(HT_GPIOB, GPIO_PIN_ALL, GPIO_DIR_OUT);
	GPIO_DirectionConfig(HT_GPIOC, GPIO_PIN_ALL, GPIO_DIR_OUT);   

  ADC_Configuration();
  TM_Configuration();

  /* Enable GPTM which will trigger ADC start of conversion every 1 second                                  */
  ADC_Cmd(HT_ADC, ENABLE);
  TM_Cmd(HT_GPTM0, ENABLE);

  while (1)
  {
		GPIO_WriteOutData(HT_GPIOC,0x0000);	
    if (gADC_CycleEndOfConversion)
    {
                                                                         
			ge = gADC_Result[0]%10;
			shi = (gADC_Result[0]/10)%10;
			bai = (gADC_Result[0]/100)%10;
			qian = (gADC_Result[0]/1000)%10;
			gADC_CycleEndOfConversion = FALSE;
    }
			for (j=0;j<99;j++)
			display(ge,shi,bai,qian);
  }
}

/*********************************************************************************************************//**
  * @brief  ADC Configuration.
  * @retval None
  ***********************************************************************************************************/
void ADC_Configuration(void)
{
  /* Configure specify IO's AFIO mode as ADC function                                                       */
  AFIO_GPxConfig(HTCFG_AD0_GPIO_ID, HTCFG_AD0_AFIO_PIN, AFIO_FUN_ADC);  //PA6
  AFIO_GPxConfig(HTCFG_AD1_GPIO_ID, HTCFG_AD1_AFIO_PIN, AFIO_FUN_ADC);  //PA0
  AFIO_GPxConfig(HTCFG_AD2_GPIO_ID, HTCFG_AD2_AFIO_PIN, AFIO_FUN_ADC);  //PA1

  /* ADCLK frequency is set to CK_AHB / 64                                                                  */
  CKCU_SetADCPrescaler(CKCU_ADCPRE_DIV64);

  /* One Shot Mode, Conversion/Sequence Length 3, SubLength 0                                               */
  ADC_RegularGroupConfig(HT_ADC, ONE_SHOT_MODE, 3, 0);

  /* Set sampling time as 1.5 + 36 ADCCLK, Conversion = 12.5 + 1.5 + 36 = 50 ADCCLK                         */
  ADC_SamplingTimeConfig(HT_ADC, 36);

  /* Set ADC Channel of Sequence                                                                            */
  ADC_RegularChannelConfig(HT_ADC, HTCFG_AD0_ADC_CH, 0);    
  ADC_RegularChannelConfig(HT_ADC, HTCFG_AD1_ADC_CH, 1);
  ADC_RegularChannelConfig(HT_ADC, HTCFG_AD2_ADC_CH, 2);

  /* Enable ADC single/cycle end of conversion interrupt                                                    */
  ADC_IntConfig(HT_ADC, ADC_INT_SINGLE_EOC | ADC_INT_CYCLE_EOC, ENABLE);

  /* Enable the ADC Interrupts                                                                              */
  NVIC_EnableIRQ(ADC_IRQn);

  /* Use GPTM0 CH3O as ADC trigger source                                                                   */
  ADC_RegularTrigConfig(HT_ADC, ADC_TRIG_GPTM0_CH3O);
}

/*********************************************************************************************************//**
  * @brief  Timer Configuration.
  * @retval None
  ***********************************************************************************************************/
void TM_Configuration(void)
{
  TM_TimeBaseInitTypeDef TimeBaseInit;
  TM_OutputInitTypeDef OutInit;

  /* Configure GPTM0 Channel 3 as PWM output mode used to trigger ADC start of conversion every 1 second    */
  TimeBaseInit.CounterMode = TM_CNT_MODE_UP;
  TimeBaseInit.CounterReload = 40000 - 1 ;
  TimeBaseInit.Prescaler = (SystemCoreClock / 40000) - 1; // GPTM Clock is 40K
  TimeBaseInit.PSCReloadTime = TM_PSC_RLD_IMMEDIATE;
  TM_TimeBaseInit(HT_GPTM0, &TimeBaseInit);

  OutInit.Channel = TM_CH_3;
  OutInit.OutputMode = TM_OM_PWM2;
  OutInit.Control = TM_CHCTL_ENABLE;
  OutInit.Polarity = TM_CHP_NONINVERTED;
  OutInit.Compare = 20000 - 1;
  TM_OutputInit(HT_GPTM0, &OutInit);

  TM_IntConfig(HT_GPTM0, TM_INT_CH3CC, ENABLE);
  NVIC_EnableIRQ(GPTM0_IRQn);
}

static void __Delay(u32 count)
{
  while(count--)
  {
    __NOP(); // Prevent delay loop be optimized
  }
}



void display(u16 ge,u16 shi,u16 bai,u16 qian)
{
	GPIO_WriteOutData(HT_GPIOC,POS_TAB[3]);		
	GPIO_WriteOutData(HT_GPIOB,SEG_TAB[qian]);	
	__Delay(40000);


	GPIO_WriteOutData(HT_GPIOC,POS_TAB[2]);		
	GPIO_WriteOutData(HT_GPIOB,SEG_TAB[bai]);		
	__Delay(40000);


	GPIO_WriteOutData(HT_GPIOC,POS_TAB[1]);		
	GPIO_WriteOutData(HT_GPIOB,SEG_TAB[shi]);		
	__Delay(40000);


	GPIO_WriteOutData(HT_GPIOC,POS_TAB[0]);		
	GPIO_WriteOutData(HT_GPIOB,SEG_TAB[ge]);		
	__Delay(40000);


}

#if (HT32_LIB_DEBUG == 1)
/*********************************************************************************************************//**
  * @brief  Report both the error name of the source file and the source line number.
  * @param  filename: pointer to the source file name.
  * @param  uline: error line source number.
  * @retval None
  ***********************************************************************************************************/
void assert_error(u8* filename, u32 uline)
{
  /*
     This function is called by IP library that the invalid parameters has been passed to the library API.
     Debug message can be added here.
     Example: printf("Parameter Error: file %s on line %d\r\n", filename, uline);
  */

  while (1)
  {
  }
}
#endif


/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
