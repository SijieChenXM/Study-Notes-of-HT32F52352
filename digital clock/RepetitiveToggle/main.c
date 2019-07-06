/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"
#include "ht32_board.h"
#include "ht32_board_config.h"

FlagStatus TimerInt = RESET;



const u16 SEG_TAB[] = {		      //∆ﬂ∂Œ ˝¬Îπ‹
			         0x3F,0x06,0x5B,0x4F,0x66,
			         0x6D,0x7D,0x07,0x7F,0x67};
			         
static void __Delay(u32 count);
unsigned short ScanKey(void);


/*
  PA0~PA6£∫∆ﬂ∂Œ ˝¬Îπ‹∂‘”¶∂Àø⁄
	PC0~PC3£∫ ˝¬Îπ‹ πƒ‹∂À
	PB0~PB7£∫4*4º¸≈Ãæÿ’Û
	PD0£∫  ˝¬Îπ‹÷–º‰œ‘ æµ∆æ
	PD2£∫ ∑‰√˘∆˜∂
*/

int main(void)
{ 
	
	u16 i,j,count,sec,key,flag,mod,miaob_control,fuwei,count1,sec1,naozhong;
	u16 miao0,miao1,fen0,fen1,shi0,shi1;
	u16 miaob_miao0,miaob_miao1,miaob_fen0,miaob_fen1;

//¥Úø™◊‹œﬂ ±÷”  
CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};

	CKCUClock.Bit.PA       = 1;
	CKCUClock.Bit.PB       = 1;
	CKCUClock.Bit.PC       = 1;
	CKCUClock.Bit.PD       = 1;
  CKCUClock.Bit.AFIO       = 1;
  CKCUClock.Bit.BFTM0      = 1;

  CKCU_PeripClockConfig(CKCUClock, ENABLE);


/* Configure PB pins as output function                                                     */

	//…Ë÷√“˝Ω≈∏¥”√
  /* Configure AFIO mode of output pins                                                                     */

  AFIO_GPxConfig(GPIO_PA, AFIO_PIN_ALL, AFIO_MODE_DEFAULT);
  AFIO_GPxConfig(GPIO_PC, AFIO_PIN_ALL, AFIO_MODE_DEFAULT);
	AFIO_GPxConfig(GPIO_PB, AFIO_PIN_ALL, AFIO_MODE_DEFAULT);
  AFIO_GPxConfig(GPIO_PD, AFIO_PIN_ALL, AFIO_MODE_DEFAULT);

 
 //…Ë÷√“˝Ω≈ ‰»Î ‰≥ˆ
  /* Configure GPIO direction of output pins                                                                */

	GPIO_DirectionConfig(HT_GPIOA, GPIO_PIN_ALL, GPIO_DIR_OUT);
	GPIO_DirectionConfig(HT_GPIOC, GPIO_PIN_ALL, GPIO_DIR_OUT);
	GPIO_DirectionConfig(HT_GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, GPIO_DIR_OUT);
	GPIO_DirectionConfig(HT_GPIOB, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, GPIO_DIR_IN);
	GPIO_DirectionConfig(HT_GPIOD, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2, GPIO_DIR_OUT);

  GPIO_PullResistorConfig(HT_GPIOB, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, GPIO_PR_DOWN);
	GPIO_InputConfig(HT_GPIOB, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, ENABLE);

  NVIC_EnableIRQ(BFTM0_IRQn);

  /*  match interrupt every 1/2000 second                                              */
  BFTM_SetCompare(HT_BFTM0, SystemCoreClock/2000);
  BFTM_SetCounter(HT_BFTM0, 0);
  BFTM_IntConfig(HT_BFTM0, ENABLE);

	count = 0;i = 0;j = 0;
	miao0= 0;miao1 = 0;fen0 = 0;fen1 = 1;shi0 = 0;shi1 = 1;
	miaob_miao0 = 0;miaob_miao1 = 0;miaob_fen0 = 0;miaob_fen1 = 0;
	sec = 0;mod = 1;
	miaob_control = 0;fuwei = 0;
	
	BFTM_EnaCmd(HT_BFTM0, ENABLE);
	
  while (1)
  {
		//º¸≈Ã…®√Ë
		flag=key;
	  key=ScanKey(); 	   
		
		//ƒ£ Ω—°‘Ò
		if(flag!=key)
		{
			//µ˜ ±˚£
			if(mod==2)
			{
			if(key==0) fen0++;
			if(key==1) {fen1++;if(fen1==6) fen1=0;}
			if(key==2) shi0++;
			if(key==3) {shi1++;if(shi1==3) shi1=0;}
			if(key==4) {if(fen0==0) fen0=10;fen0--;}
			if(key==5) {if(fen1==0) fen1=6;fen1--;}
			if(key==6) {if(shi0==0) shi0=10;shi0--;}
			if(key==7) {if(shi1==0) shi1=3;shi1--;}
		  }

			if(key==9)	miaob_control=!miaob_control;		
			if(key==10)	fuwei=1;	
			if(key==11)	{mod=4;fuwei=0;sec1=1;}
		  if(key==12) mod=3;
		  if(key==13) mod=1;
			if(key==14) mod=2;
			if(key==15) mod=1;
		}
		
    
		//∂® ±∆˜º∆ ±±		
		if(TimerInt)
		{
			TimerInt = RESET;
			count++;
			naozhong=!naozhong;    
			if(miaob_control==1) count1++;
			if(count>2000)
			{
				count=0;
				i++;
				miao0++;
				sec=!sec;
			}
			if(count1>2000)
			{
				count1=0;
				miaob_miao0++;
				sec1=!sec1;
			}	
			
			
			if(miaob_miao0 == 10)
			{
				miaob_miao1++;
				miaob_miao0 = 0;
			}
			if(miaob_miao1 == 6)
			{
				miaob_fen0++;
				miaob_miao1 = 0;
			}			
			if(miaob_fen0 == 10)
			{
				miaob_fen1++;
				miaob_fen0 = 0;
			}		
      if(miaob_fen1 == 6)
			{
				miaob_fen1 = 0;
			}
			if(miao0 == 10)
			{
				miao1++;
				miao0 = 0;
			}
			if(miao1 == 6)
			{
				fen0++;
				miao1 = 0;
			}			
			if(fen0 == 10)
			{
				fen1++;
				fen0 = 0;
			}		
      if(fen1 == 6)
			{
				shi0++;
				fen1 = 0;
			}		
      if(shi0 == 10)
			{
				shi1++;
				shi0 = 0;
			}				
			if(shi1 == 2 & shi0 ==4)
			{
				
				shi1=shi0=0;
			}
			
			
    // ˝¬Îπ‹ πƒ‹		
		switch (count%4)
			{
				case 0:
				{
					GPIO_WriteOutBits(HT_GPIOC,GPIO_PIN_0,1);	
          GPIO_WriteOutBits(HT_GPIOC,GPIO_PIN_1,0);
          GPIO_WriteOutBits(HT_GPIOC,GPIO_PIN_2,0);
					GPIO_WriteOutBits(HT_GPIOC,GPIO_PIN_3,0);
					break;		
			  }		
				case 1:
				{
					GPIO_WriteOutBits(HT_GPIOC,GPIO_PIN_0,0);	
          GPIO_WriteOutBits(HT_GPIOC,GPIO_PIN_1,1);
          GPIO_WriteOutBits(HT_GPIOC,GPIO_PIN_2,0);
					GPIO_WriteOutBits(HT_GPIOC,GPIO_PIN_3,0);
					break;		
			  }			
				case 2:
				{
					GPIO_WriteOutBits(HT_GPIOC,GPIO_PIN_0,0);	
          GPIO_WriteOutBits(HT_GPIOC,GPIO_PIN_1,0);
          GPIO_WriteOutBits(HT_GPIOC,GPIO_PIN_2,1);
					GPIO_WriteOutBits(HT_GPIOC,GPIO_PIN_3,0);
					break;		
			  }			
				case 3:
				{
					GPIO_WriteOutBits(HT_GPIOC,GPIO_PIN_0,0);	
          GPIO_WriteOutBits(HT_GPIOC,GPIO_PIN_1,0);
          GPIO_WriteOutBits(HT_GPIOC,GPIO_PIN_2,0);
					GPIO_WriteOutBits(HT_GPIOC,GPIO_PIN_3,1);
					break;		
			  }						
			}	
		GPIO_WriteOutBits(HT_GPIOD,GPIO_PIN_1,0);

		// ±∑÷œ‘ æ
    if(mod==1|mod==2)
		{
			GPIO_WriteOutBits(HT_GPIOD,GPIO_PIN_0,sec);
		  switch (count%4)
			{
				case 0:
					GPIO_WriteOutData(HT_GPIOA,SEG_TAB[fen0]);		break;		
				case 1:
					GPIO_WriteOutData(HT_GPIOA,SEG_TAB[fen1]);		break;		
				case 2:
					GPIO_WriteOutData(HT_GPIOA,SEG_TAB[shi0]);		break;		
				case 3:
					GPIO_WriteOutData(HT_GPIOA,SEG_TAB[shi1]);	break;					
			}	
		}
		
		
		//∑÷√Îœ‘ æ
    if(mod==3)
		{
      GPIO_WriteOutBits(HT_GPIOD,GPIO_PIN_0,sec);
		  switch (count%4)
			{
				case 0:
					GPIO_WriteOutData(HT_GPIOA,SEG_TAB[miao0]);		break;		
				case 1:
					GPIO_WriteOutData(HT_GPIOA,SEG_TAB[miao1]);		break;		
				case 2:
					GPIO_WriteOutData(HT_GPIOA,SEG_TAB[fen0]);		break;		
				case 3:
					GPIO_WriteOutData(HT_GPIOA,SEG_TAB[fen1]);	break;					
			}	
		}
		
		//√Î±Ìœ‘ æ
		if(mod==4)
		{
			if(fuwei==1)
			{
				miaob_miao0 = 0;miaob_miao1 = 0;miaob_fen0 = 0;miaob_fen1 = 0;fuwei=0;miaob_control=0;sec1=1;
			}
			GPIO_WriteOutBits(HT_GPIOD,GPIO_PIN_0,sec1);
		  switch (count%4)
			{
				case 0:
					GPIO_WriteOutData(HT_GPIOA,SEG_TAB[miaob_miao0]);		break;		
				case 1:
					GPIO_WriteOutData(HT_GPIOA,SEG_TAB[miaob_miao1]);		break;		
				case 2:
					GPIO_WriteOutData(HT_GPIOA,SEG_TAB[miaob_fen0]);		break;		
				case 3:
					GPIO_WriteOutData(HT_GPIOA,SEG_TAB[miaob_fen0]);	break;					
			}	
		}

		

		//’˚µ„œÏ¡Â
		if(fen0==0&&fen1==0&&miao1==0)
		{
			if(miao0==0||miao0==1||miao0==2)
			GPIO_WriteOutBits(HT_GPIOD,GPIO_PIN_2,naozhong);
		}
		
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

unsigned short ScanKey(void)
{	
	u8 KeyPort,i,key;
	GPIO_WriteOutData(HT_GPIOB,0xE);	
	KeyPort=GPIO_ReadOutData(HT_GPIOB);
	key=0;
	for(i=0;i<4;i++)
	{
		GPIO_WriteOutData(HT_GPIOB,KeyPort);	
		KeyPort=GPIO_ReadOutData(HT_GPIOB);
		if(GPIO_ReadInBit(HT_GPIOB,GPIO_PIN_4)==0)  break;
		key++;
		if(GPIO_ReadInBit(HT_GPIOB,GPIO_PIN_5)==0) 	break;
		key++;
		if(GPIO_ReadInBit(HT_GPIOB,GPIO_PIN_6)==0) 	break;
		key++;
		if(GPIO_ReadInBit(HT_GPIOB,GPIO_PIN_7)==0) 	break;
		key++;
		KeyPort<<=1; 
		KeyPort|=0x01;
	}
		return key;
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
