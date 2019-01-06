
#include "rti.h"

unsigned char single = 0;

//初始化实时中断
void INIT_RTI(void)
{
	CRGINT = 0x80;       //使能实时中断
	RTICTL = 0x6f;       //设置实时中断的时间间隔为32.768ms
	//(15+1)*(2的（6+9）次方)/晶振16Mhz = 32.768ms
}

/*************************************************************/
/*                       实时中断函数                        */
/*************************************************************/
#pragma CODE_SEG __NEAR_SEG NON_BANKED
interrupt void rti_interrupt(void)
{
	EnableInterrupts;
	if(CRGFLG_RTIF == 1)
	{
		CRGFLG_RTIF = 1;
		single += 1;
		if(single == 15)
		{
			single = 0;
			PORTB_PB5 = 1- PORTB_PB5;  //大约0.5s将指示灯翻转一次
		}
	}
}
#pragma CODE_SEG DEFAULT











