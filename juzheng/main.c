/*********************************************************************************************************//**
 * @file    GPIO/InputOutput/main.c
 * @version $Rev:: 1277         $
 * @date    $Date:: 2016-11-22 #$
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

/** @addtogroup GPIO_Examples GPIO
  * @{
  */

/** @addtogroup InputOutput
  * @{
  */


/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  * @note At this stage the microcontroller clock setting should has already been configured.
  *       This can be done through SystemInit() function which is called from startup
  *       file (startup_ht32fxxxx.s) before branching to application main().
  *       To reconfigure the default setting of SystemInit() function, please refer to
  *       system_ht32fxxxx.c file
  * @details The main function works as the following:
  *    - Check if the backup domain is ready for access so as to disable isolation.
  *      Because some GPIO pins are located in the backup domain.
  *    - Enable AFIO peripheral clock
  *    - Configure WEAKUP, KEY1, KEY2 pins as the input function
  *      - Enable GPIO peripheral clock of input pins
  *      - Configure AFIO mode of input pins
  *      - Configure GPIO direction of input pins
  *    - Configure LED1, LED2, LED3 pins as the output function
  *      - Enable GPIO peripheral clock of output pins
  *      - Configure AFIO mode of output pins
  *      - Configure GPIO direction of output pins
  *    - Infinite loop to read data from the input pin and then output to LED
  *      - Read WEAKUP and then output via LED1
  *      - Read KEY1 and then output via LED2
  *      - Read KEY2 and then output via LED3
  *
  ***********************************************************************************************************/
//B0 CLK
//B1 CS
//B2 DIN
#define uchar unsigned char
#define uint  unsigned int
#define Max7219_pinCLK  GPIO_PIN_0
#define Max7219_pinCS   GPIO_PIN_1
#define Max7219_pinDIN  GPIO_PIN_2
const uchar disp1[49][8]= {
{0x38,0x54,0x92,0x92,0x82,0x44,0x38,0x00},
{0x38,0x44,0x8A,0x92,0x82,0x44,0x38,0x00},
{0x38,0x44,0x82,0x9E,0x82,0x44,0x38,0x00},
{0x38,0x44,0x82,0x92,0x8A,0x44,0x38,0x00},
{0x38,0x44,0x82,0x92,0x92,0x54,0x38,0x00},
{0x38,0x44,0x82,0x92,0xA2,0x44,0x38,0x00},
{0x38,0x44,0x82,0xF2,0x82,0x44,0x38,0x00},
{0x38,0x44,0xA2,0x92,0x82,0x44,0x38,0x00},//旋转（前8个）
{0x66,0xFF,0xFF,0xFF,0x7E,0x3C,0x18,0x00},//心形
{0x42,0xE7,0x42,0x00,0x81,0x42,0x3C,0x00},//笑脸
{0x8,0x7F,0x49,0x49,0x7F,0x8,0x8,0x8},//中
{0xFE,0xBA,0x92,0xBA,0x92,0x9A,0xBA,0xFE},//国
{0x28,0x7E,0x88,0x08,0xFF,0x08,0x08,0x08},//牛
{0x3C,0x42,0x42,0x42,0x42,0x42,0x42,0x3C},//0
{0x10,0x30,0x10,0x10,0x10,0x10,0x10,0x38},//1
{0x7E,0x2,0x2,0x7E,0x40,0x40,0x40,0x7E},//2
{0x3E,0x2,0x2,0x3E,0x2,0x2,0x3E,0x0},//3
{0x8,0x18,0x28,0x48,0xFE,0x8,0x8,0x8},//4
{0x3C,0x20,0x20,0x3C,0x4,0x4,0x3C,0x0},//5
{0x3C,0x20,0x20,0x3C,0x24,0x24,0x3C,0x0},//6
{0x3E,0x22,0x4,0x8,0x8,0x8,0x8,0x8},//7
{0x0,0x3E,0x22,0x22,0x3E,0x22,0x22,0x3E},//8
{0x3E,0x22,0x22,0x3E,0x2,0x2,0x2,0x3E},//9
{0x8,0x14,0x22,0x3E,0x22,0x22,0x22,0x22},//A
{0x3C,0x22,0x22,0x3E,0x22,0x22,0x3C,0x0},//B
{0x3C,0x40,0x40,0x40,0x40,0x40,0x3C,0x0},//C
{0x7C,0x42,0x42,0x42,0x42,0x42,0x7C,0x0},//D
{0x7C,0x40,0x40,0x7C,0x40,0x40,0x40,0x7C},//E
{0x7C,0x40,0x40,0x7C,0x40,0x40,0x40,0x40},//F
{0x3C,0x40,0x40,0x40,0x40,0x44,0x44,0x3C},//G
{0x44,0x44,0x44,0x7C,0x44,0x44,0x44,0x44},//H
{0x7C,0x10,0x10,0x10,0x10,0x10,0x10,0x7C},//I
{0x3C,0x8,0x8,0x8,0x8,0x8,0x48,0x30},//J
{0x0,0x24,0x28,0x30,0x20,0x30,0x28,0x24},//K
{0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x7C},//L
{0x81,0xC3,0xA5,0x99,0x81,0x81,0x81,0x81},//M
{0x0,0x42,0x62,0x52,0x4A,0x46,0x42,0x0},//N
{0x3C,0x42,0x42,0x42,0x42,0x42,0x42,0x3C},//O
{0x3C,0x22,0x22,0x22,0x3C,0x20,0x20,0x20},//P
{0x1C,0x22,0x22,0x22,0x22,0x26,0x22,0x1D},//Q
{0x3C,0x22,0x22,0x22,0x3C,0x24,0x22,0x21},//R
{0x0,0x1E,0x20,0x20,0x3E,0x2,0x2,0x3C},//S
{0x0,0x3E,0x8,0x8,0x8,0x8,0x8,0x8},//T
{0x42,0x42,0x42,0x42,0x42,0x42,0x22,0x1C},//U
{0x42,0x42,0x42,0x42,0x42,0x42,0x24,0x18},//V
{0x0,0x49,0x49,0x49,0x49,0x2A,0x1C,0x0},//W
{0x0,0x41,0x22,0x14,0x8,0x14,0x22,0x41},//X
{0x41,0x22,0x14,0x8,0x8,0x8,0x8,0x8},//Y
{0x0,0x7F,0x2,0x4,0x8,0x10,0x20,0x7F}//Z
};
void Delay_xms(uint x)
{
 uint i,j;
 for(i = 0; i < x; i++)
  for(j = 0; j < 112; j++);
}
//--------------------------------------------
//功能：向MAX7219(U3)写入字节
//入口参数：DATA 
//出口参数：无
//说明：
void Write_Max7219_byte(uchar DATA)         
{
	uchar i; 
	GPIO_WriteOutBits(HT_GPIOB, Max7219_pinCS, 0);		
	for(i = 8; i >= 1 ; i--) {
		GPIO_WriteOutBits(HT_GPIOB, Max7219_pinCLK, 0);
		if((DATA&0x80)==0x80) 
			GPIO_WriteOutBits(HT_GPIOB, Max7219_pinDIN, 1);
			else
				GPIO_WriteOutBits(HT_GPIOB, Max7219_pinDIN, 0);
		DATA = DATA<<1;
		GPIO_WriteOutBits(HT_GPIOB, Max7219_pinCLK, 1);
	}                                 
}
//-------------------------------------------
//功能：向MAX7219写入数据
//入口参数：address、dat
//出口参数：无
//说明：
void Write_Max7219(uchar address, uchar dat)
{
	GPIO_WriteOutBits(HT_GPIOB, Max7219_pinCS, 0);
	Write_Max7219_byte(address);           //写入地址，即数码管编号
  Write_Max7219_byte(dat);               //写入数据，即数码管显示数字
	GPIO_WriteOutBits(HT_GPIOB, Max7219_pinCS, 1);               
}

void Init_MAX7219(void)
{
 Write_Max7219(0x09, 0x00);       //译码方式：BCD码
 Write_Max7219(0x0a, 0x03);       //亮度 
 Write_Max7219(0x0b, 0x07);       //扫描界限；8个数码管显示
 Write_Max7219(0x0c, 0x01);       //掉电模式：0，普通模式：1
 Write_Max7219(0x0f, 0x00);       //显示测试：1；测试结束，正常显示：0
}

int main(void)
{
	uchar i,j;
	
	CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};

	CKCUClock.Bit.PB			 = 1;
	CKCUClock.Bit.AFIO       = 1;
	
	CKCU_PeripClockConfig(CKCUClock, ENABLE);
	
	AFIO_GPxConfig(GPIO_PB, Max7219_pinCLK | Max7219_pinCS | Max7219_pinDIN, AFIO_MODE_DEFAULT);
	GPIO_DirectionConfig(HT_GPIOB, Max7219_pinCLK | Max7219_pinCS | Max7219_pinDIN, GPIO_DIR_OUT);
	GPIO_WriteOutBits(HT_GPIOB, Max7219_pinCLK | Max7219_pinCS | Max7219_pinDIN, RESET);
	
	Delay_xms(50);
	Init_MAX7219();  
	while(1)
	{
		for(j = 0; j < 49; j++) {
			for(i = 1; i < 9; i++)
				Write_Max7219(i, disp1[j][i-1]);
			Delay_xms(100000);
		}  
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


/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
