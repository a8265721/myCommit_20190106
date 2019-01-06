
#include "rti.h"

unsigned char single = 0;

//��ʼ��ʵʱ�ж�
void INIT_RTI(void)
{
	CRGINT = 0x80;       //ʹ��ʵʱ�ж�
	RTICTL = 0x6f;       //����ʵʱ�жϵ�ʱ����Ϊ32.768ms
	//(15+1)*(2�ģ�6+9���η�)/����16Mhz = 32.768ms
}

/*************************************************************/
/*                       ʵʱ�жϺ���                        */
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
			PORTB_PB5 = 1- PORTB_PB5;  //��Լ0.5s��ָʾ�Ʒ�תһ��
		}
	}
}
#pragma CODE_SEG DEFAULT











