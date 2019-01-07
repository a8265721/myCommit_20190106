#include "key.h"
#include "data_buff.h"
#include "ect.h"

u32 key_time = 0;

/*                                                 
// ��ʼ��key               
void INIT_KEY(void)
{
	UP_dir =0;       //����Ϊ����
	DOWN_dir=0;
	LEFT_dir=0;
	RIGHT_dir=0;

	PPSH = 0x00;		      //����ѡ��Ĵ���,0 ѡ���½���;
	//   PERH = 0x03;          //��������������
	//  PPSH = 0x01;		       //����ѡ��Ĵ���,1 ѡ��������;
	PIFH = 0x0f;					//��PIFH��ÿһλд1�������־λ;
	PIEH = 0x0f;		      //�ж�ʹ�ܼĴ���;
}
*/



// ��ʼ��key   
void INIT_KEY(void)
{
	K1_dir=0;       //����Ϊ����
	K2_dir=0;
	K3_dir=0;
	K4_dir=0;
	K5_dir=0;      
	K6_dir=0;
	K7_dir=0;
	K8_dir=0;

	PPSH = 0x00;		      //����ѡ��Ĵ���,0 ѡ���½���;
	//   PERH = 0x03;          //��������������
	//  PPSH = 0x01;		       //����ѡ��Ĵ���,1 ѡ��������;
	PIFH = 0xff;					//��PIFH��ÿһλд1�������־λ;
	PIEH = 0xff;		      //�ж�ʹ�ܼĴ���;
}



//�����жϺ���                           
#pragma CODE_SEG __NEAR_SEG NON_BANKED
interrupt void PTH_interrupt(void) 
{

	EnableInterrupts;
	if(PIFH != 0)     //�ж��жϱ�־
	{
		   PIFH = 0xff;     //����жϱ�־
		   
		   
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
//�����жϺ���                           
#pragma CODE_SEG __NEAR_SEG NON_BANKED
interrupt void PTH_interrupt(void) 
{
	enum Pwm_channel   pwm_channel = pwm_channel_23;

	EnableInterrupts;
	if(PIFH != 0)     //�ж��жϱ�־
	{
		//   PIFH = 0xff;     //����жϱ�־
		PIFH = 0x0f;     //����жϱ�־
		if(UP == 0)         //����1����
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