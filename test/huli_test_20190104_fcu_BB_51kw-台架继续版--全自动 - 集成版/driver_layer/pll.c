#include "pll.h"



//延时函数
//time_ms 为延时的具体时间，单位是ms （1秒 对应 1000）
//注意u16 最大值为65535
void delay_ms(unsigned int time_ms) 
{

	unsigned int i,j;
	float temp =  BUS_CLOCK / 1000000;
	temp = 4600 * (temp / 32);  //注意了，先算除法，防止越界
	for(i=0;i<temp;i++) 

		for(j=0;j<time_ms;j++)  ;

	return ;  
} 




//锁相环，cpu默认的总线频率为8M HZ
//可以用过锁相环，将cpu加快，缺点是容易导致不稳定。
//注意了，当总线时间更改，一些和时间相关的都会受到影响。（例如延时，波特率.....）
void INIT_PLL(void)
{
	CLKSEL &= 0x7f;       //设置OSCCLK作为系统时钟
	PLLCTL &= 0x8F;       //禁止锁相环
	CRGINT &= 0xDF;

	//PLLCLK=2×OSCCLK×(SYNR+1)/(REFDV+1), fbus=PLLCLK/2
#if(BUS_CLOCK == 120000000) 
	SYNR = 0xcd;
#elif(BUS_CLOCK == 104000000) 
	SYNR = 0xcc;
#elif(BUS_CLOCK == 96000000) 
	SYNR = 0xcb;
#elif(BUS_CLOCK == 88000000) 
	SYNR = 0xca;
#elif(BUS_CLOCK == 80000000) 
	SYNR = 0xc9;
#elif(BUS_CLOCK == 72000000) 
	SYNR = 0xc8;
#elif(BUS_CLOCK == 64000000) 
	SYNR = 0xc7;
#elif(BUS_CLOCK == 56000000) 
	SYNR = 0xc6;
#elif(BUS_CLOCK == 48000000) 
	SYNR = 0xc5;
#elif(BUS_CLOCK == 40000000) 
	SYNR = 0x44;
#elif(BUS_CLOCK == 32000000)
	SYNR = 0x43;     
#elif(BUS_CLOCK == 24000000)
	SYNR = 0x42;
#elif(BUS_CLOCK == 16000000)
	SYNR = 0x01;
#endif 

	REFDV = 0x81;
	PLLCTL |=0x70;  //使能锁相环
	asm NOP;
	asm NOP;
	while(!(CRGFLG&0x08)); //PLLCLK锁定
	CLKSEL |= 0x80;        //设置PLLCLK为系统时钟
}



