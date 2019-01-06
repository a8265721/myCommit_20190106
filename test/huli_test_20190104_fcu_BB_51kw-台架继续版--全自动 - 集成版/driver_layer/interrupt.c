
#include "interrupt.h"



//#define Vsci0                           0xFFD6U
//���÷������£�
//MC9SX128.h�� �ҵ���Ӧ�жϵĵ�ַλ�ĺꡣ
//ǰ���FF���ܣ���ע�����һ��byte�� ����Vsci0 �����һ���ֽ�Ϊd6   6/2=3
//INT_CFADDR = 0xd;
//INT_CFDATA3=0x4;		//��Vsci0���ж����ȼ�����Ϊ4


//�ж����ȼ�����, �ж�Ĭ�����ȼ�Ϊ1, 
void init_interruput_priorty_set(void)
{
	//�� Vsci0  0xFFD6U ���ж����ȼ�����Ϊ6
	INT_CFADDR = 0xd0;
	INT_CFDATA3=0x6;		

	//��  Vectmdcu  0xFFCAU  ���ж����ȼ�����Ϊ4
	INT_CFADDR = 0xc0;
	INT_CFDATA5=0x4;	

	//��  Vectovf  0xFFDEU  ���ж����ȼ�����Ϊ1
	//	INT_CFADDR = 0xd0;
	//	INT_CFDATA7=0x1;	

	//��  PIT0  0xFF7A  ���ж����ȼ�����Ϊ5
	INT_CFADDR = 0x70;
	INT_CFDATA5=0x5;

	//��  PIT1  0xFF78  ���ж����ȼ�����Ϊ2
	INT_CFADDR = 0x70;
	INT_CFDATA4=0x2;

	//��  0xFFB2 can0  ���ж����ȼ�����Ϊ2
	INT_CFADDR = 0xB0;
	INT_CFDATA1=0x2;

	//��  0xFFAA can1  ���ж����ȼ�����Ϊ2
	INT_CFADDR = 0xA0;
	INT_CFDATA5=0x2;
	
	//��  0xFFA2 can2  ���ж����ȼ�����Ϊ2
	INT_CFADDR = 0xA0;
	INT_CFDATA1=0x2;

	/*
	//��  	0xFFD2 atd0     ���ж����ȼ�����Ϊ3
	INT_CFADDR = 0xd0;
	INT_CFDATA1=0x3;
	*/

	//��  	0xFF76 PIT2   ���ж����ȼ�����Ϊ3
	INT_CFADDR = 0x70;
	INT_CFDATA3=0x3; 
	
		//��  	0xFF74 PIT3   ���ж����ȼ�����Ϊ1
	INT_CFADDR = 0x70;
	INT_CFDATA2=0x1;
	
	//��  	0xFF5E PIT4   ���ж����ȼ�����Ϊ1
	INT_CFADDR = 0x50;
	INT_CFDATA7=0x1;
	
	//��  	0xFF5C PIT5   ���ж����ȼ�����Ϊ3
	INT_CFADDR = 0x50;
	INT_CFDATA6=0x3;	
	
	//��  	0xFFD4 SCI1   ���ж����ȼ�����Ϊ2
	INT_CFADDR = 0xD0;
	INT_CFDATA2=0x4;
	
	//��  	0xFF88 SCI3   ���ж����ȼ�����Ϊ2
	INT_CFADDR = 0x80;
	INT_CFDATA4=0x4;		
}

//ע���ˣ����Ҫ����Ƕ�ף������ȼ��жϵĿ���Ƕ�׵����ȼ��жϣ���Ҫ�ڵͼ��ж����ٿ�һ�����ж�
//����   EnableInterrupts;
