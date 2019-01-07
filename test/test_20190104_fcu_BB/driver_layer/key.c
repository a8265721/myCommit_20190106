#include "key.h"
#include "data_buff.h"
#include "ect.h"

u32 key_time = 0;

/*                                                 
// 初始化key               
void INIT_KEY(void)
{
	UP_dir =0;       //设置为输入
	DOWN_dir=0;
	LEFT_dir=0;
	RIGHT_dir=0;

	PPSH = 0x00;		      //极性选择寄存器,0 选择下降沿;
	//   PERH = 0x03;          //开启上拉和下拉
	//  PPSH = 0x01;		       //极性选择寄存器,1 选择上升沿;
	PIFH = 0x0f;					//对PIFH的每一位写1来清除标志位;
	PIEH = 0x0f;		      //中断使能寄存器;
}
*/



// 初始化key   
void INIT_KEY(void)
{
	K1_dir=0;       //设置为输入
	K2_dir=0;
	K3_dir=0;
	K4_dir=0;
	K5_dir=0;      
	K6_dir=0;
	K7_dir=0;
	K8_dir=0;

	PPSH = 0x00;		      //极性选择寄存器,0 选择下降沿;
	//   PERH = 0x03;          //开启上拉和下拉
	//  PPSH = 0x01;		       //极性选择寄存器,1 选择上升沿;
	PIFH = 0xff;					//对PIFH的每一位写1来清除标志位;
	PIEH = 0xff;		      //中断使能寄存器;
}



//按键中断函数                           
#pragma CODE_SEG __NEAR_SEG NON_BANKED
interrupt void PTH_interrupt(void) 
{

	EnableInterrupts;
	if(PIFH != 0)     //判断中断标志
	{
		   PIFH = 0xff;     //清除中断标志
		   
		   
		   if(system_time - key_time > 1000 && FCU_START_ENABLE_K5 == 0)
		   {
		      fcu_data_buffer.galvanic_pile_data_buffer.fcu_start_enable
		        =1- fcu_data_buffer.galvanic_pile_data_buffer.fcu_start_enable;
		        
		        key_time = system_time;
		   }
		  
	}
}
#pragma CODE_SEG DEFAULT

/*
//按键中断函数                           
#pragma CODE_SEG __NEAR_SEG NON_BANKED
interrupt void PTH_interrupt(void) 
{
	enum Pwm_channel   pwm_channel = pwm_channel_23;

	EnableInterrupts;
	if(PIFH != 0)     //判断中断标志
	{
		//   PIFH = 0xff;     //清除中断标志
		PIFH = 0x0f;     //清除中断标志
		if(UP == 0)         //按键1按下
		{       
			PORTB_PB0 = 1 - PORTB_PB0;
		}
		if(DOWN == 0) 
		{       
			PORTB_PB1 = 1 - PORTB_PB1;
		}
		if(LEFT == 0)
		{
			PORTB_PB2 = 1 - PORTB_PB2;

			if(dutyfactor_test >= 500)
			{                                   
				dutyfactor_test	-= 500;
			}
			else
			{
				dutyfactor_test = 0;   
			}
			pwm_set_dutyfactor(pwm_channel, (u16)dutyfactor_test) ;

		}
		if(RIGHT == 0)
		{ 
			PORTB_PB3 = 1 - PORTB_PB3;

			if(dutyfactor_test <=9500)
			{
				dutyfactor_test	+= 500;
			}
			else
			{
				dutyfactor_test = 10000;  
			}
			pwm_set_dutyfactor(pwm_channel, (u16)dutyfactor_test) ;

		}
	}
}
#pragma CODE_SEG DEFAULT
*/