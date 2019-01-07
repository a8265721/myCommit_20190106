
#include "interrupt.h"



//#define Vsci0                           0xFFD6U
//配置方法如下：
//MC9SX128.h中 找到对应中断的地址位的宏。
//前面的FF不管，关注后面的一个byte。 例如Vsci0 的最后一个字节为d6   6/2=3
//INT_CFADDR = 0xd;
//INT_CFDATA3=0x4;		//把Vsci0的中断优先级设置为4


//中断优先级设置, 中断默认优先级为1, 
void init_interruput_priorty_set(void)
{
	//把 Vsci0  0xFFD6U 的中断优先级设置为6
	INT_CFADDR = 0xd0;
	INT_CFDATA3=0x6;		

	//把  Vectmdcu  0xFFCAU  的中断优先级设置为4
	INT_CFADDR = 0xc0;
	INT_CFDATA5=0x4;	

	//把  Vectovf  0xFFDEU  的中断优先级设置为1
	//	INT_CFADDR = 0xd0;
	//	INT_CFDATA7=0x1;	

	//把  PIT0  0xFF7A  的中断优先级设置为5
	INT_CFADDR = 0x70;
	INT_CFDATA5=0x5;

	//把  PIT1  0xFF78  的中断优先级设置为2
	INT_CFADDR = 0x70;
	INT_CFDATA4=0x2;

	//把  0xFFB2 can0  的中断优先级设置为2
	INT_CFADDR = 0xB0;
	INT_CFDATA1=0x2;

	//把  0xFFAA can1  的中断优先级设置为2
	INT_CFADDR = 0xA0;
	INT_CFDATA5=0x2;
	
	//把  0xFFA2 can2  的中断优先级设置为2
	INT_CFADDR = 0xA0;
	INT_CFDATA1=0x2;

	/*
	//把  	0xFFD2 atd0     的中断优先级设置为3
	INT_CFADDR = 0xd0;
	INT_CFDATA1=0x3;
	*/

	//把  	0xFF76 PIT2   的中断优先级设置为3
	INT_CFADDR = 0x70;
	INT_CFDATA3=0x3; 
	
		//把  	0xFF74 PIT3   的中断优先级设置为1
	INT_CFADDR = 0x70;
	INT_CFDATA2=0x1;
	
	//把  	0xFF5E PIT4   的中断优先级设置为1
	INT_CFADDR = 0x50;
	INT_CFDATA7=0x1;
	
	//把  	0xFF5C PIT5   的中断优先级设置为3
	INT_CFADDR = 0x50;
	INT_CFDATA6=0x3;	
	
	//把  	0xFFD4 SCI1   的中断优先级设置为2
	INT_CFADDR = 0xD0;
	INT_CFDATA2=0x4;
	
	//把  	0xFF88 SCI3   的中断优先级设置为2
	INT_CFADDR = 0x80;
	INT_CFDATA4=0x4;		
}

//注意了，如果要进行嵌套，高优先级中断的可以嵌套低优先级中断，需要在低级中断中再开一次总中断
//增加   EnableInterrupts;
