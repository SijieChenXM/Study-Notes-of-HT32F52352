/*********************************************************************************************************//**
 * @file    ADC/Potentiometer_ContinuousMode/main.c
 * @version $Rev:: 1396         $
 * @date    $Date:: 2017-06-21 #$
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
#define DIV 200
unsigned long value;
const unsigned short SEG_TAB[] = {		      //7-Segment Table
			         0x3F,0x06,0x5B,0x4F,0x66,
			         0x6D,0x7D,0x07,0x7F,0x67};
			         


/*
	PB0~PB6:7段数码管的a~g端口
  PC0~PC3:数码管的使能端
	PA6：电子秤DT端   date
	PC5:电子秤SCK端   clock
*/


static void __Delay(u32 count)
{
  while(count--)
  {
    __NOP(); // Prevent delay loop be optimized
  }
}




void Delay__hx711_us(void)
{
	__NOP();
	__NOP();
}





unsigned long ReadCount(void)     //把数据用count值表示
{
	FlagStatus AD;
	unsigned long Count;
	int i;
	Count=0;

	for (i = 0; i < 24; i++) {     
		GPIO_WriteOutBits(HT_GPIOC,GPIO_PIN_5,1);
		Count=Count<<1; 
		GPIO_WriteOutBits(HT_GPIOC,GPIO_PIN_5,0);
		if((AD=GPIO_ReadInBit(HT_GPIOA,GPIO_PIN_6))==SET) 
				Count++;
	}
	GPIO_WriteOutBits(HT_GPIOC,GPIO_PIN_5,1);
	Count = Count^0x800000;
	GPIO_WriteOutBits(HT_GPIOC,GPIO_PIN_5,0);
	__Delay(1000);
	return(Count);
}


int main(void)
{
	unsigned long read = 0;
	CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
   
	CKCUClock.Bit.PA       = 1;
	CKCUClock.Bit.PB       = 1;
	CKCUClock.Bit.PC       = 1;
	CKCUClock.Bit.BFTM0    = 1;
	CKCUClock.Bit.AFIO     = 1;
	CKCUClock.Bit.ADC   	 = 1;
	
	CKCU_PeripClockConfig(CKCUClock, ENABLE);
	NVIC_EnableIRQ(BFTM0_IRQn);
	 
	// toggel LED1 every 0.005 second by match interrupt 
  BFTM_SetCompare(HT_BFTM0, SystemCoreClock / 200);
  BFTM_SetCounter(HT_BFTM0, 0);
  BFTM_IntConfig(HT_BFTM0, ENABLE);
  BFTM_EnaCmd(HT_BFTM0, ENABLE);
	
	/* Configure AFIO mode of output pins                                                                     */
	AFIO_GPxConfig(GPIO_PA, AFIO_PIN_ALL, AFIO_MODE_DEFAULT);
	AFIO_GPxConfig(GPIO_PB, AFIO_PIN_ALL, AFIO_MODE_DEFAULT);
	AFIO_GPxConfig(GPIO_PC, AFIO_PIN_ALL, AFIO_MODE_DEFAULT);

	/* Configure GPIO direction of output pins                                                                */
	GPIO_DirectionConfig(HT_GPIOA, GPIO_PIN_ALL, GPIO_DIR_IN);
	GPIO_DirectionConfig(HT_GPIOB, GPIO_PIN_ALL, GPIO_DIR_OUT);
	GPIO_DirectionConfig(HT_GPIOC, GPIO_PIN_ALL, GPIO_DIR_OUT);

	GPIO_InputConfig(HT_GPIOA, GPIO_PIN_ALL, ENABLE);
	

	while (1)
	{		
		if(!read) {
			if(GPIO_ReadInBit(HT_GPIOA,GPIO_PIN_6) == 1) {   //当数据输出管脚PA6为高电平时，表明A/D转换器还没准备好输出数据，                                              
				GPIO_WriteOutBits(HT_GPIOC,GPIO_PIN_5,0);      //此时串口时钟输入信号应为低电平    
				}
			else read=1;
			}
		if(read) {
			value =ReadCount();
			read=0;
			value/=1000;
			value=value-9000;   //去皮
		}
				
		//display(&value);
		
		__Delay(3000);
	}
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


