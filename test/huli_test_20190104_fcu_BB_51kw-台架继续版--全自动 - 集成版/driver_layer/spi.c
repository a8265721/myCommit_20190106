
#include "spi.h"



unsigned char SPI_receive_data = 0;


//初始化SPI模块 
void INIT_SPI(void) 
{
	CS_dir = 1;

	//	SPI0CR1 = 0b01010000;   //使能SPI，禁止中断，时钟高有效，相位为0；

	//开启接受中断
	SPI0CR1 = 0b11010000;   //使能SPI，禁止中断，时钟高有效，相位为0；

	SPI0CR2 = 0x00;         //SS管脚为普通I/O
	SPI0BR = 0x70;          //设置SPI时钟频率为2MHz;
	CS = 1;
};



//SPI发送函数          
void SPI_send(unsigned char data) 
{
	while(!SPI0SR_SPTEF);
	SPI0DRL = data; 
}


//SPI接收函数                
unsigned char SPI_receive(void) 
{
	unsigned char temp,data;

	//注意了，这里不建议使用while，
	//因为有些我外围设备没有主动发送功能，这里可能陷入死循环。	
	while(!SPI0SR_SPIF);
	temp = SPI0SR;
	data = SPI0DRL;
	return(data);
}   

/*************************************************************/
/*                       SPI0中断函数                        */
/*************************************************************/
#pragma CODE_SEG __NEAR_SEG NON_BANKED
interrupt void spi0_interrupt(void)
{
	unsigned char temp;
	EnableInterrupts;
	if(SPI0SR_SPIF == 1)
	{
		temp = SPI0SR;
		SPI_receive_data = SPI0DRL;
		printf("SPI_receive data = 0x%x  \r\n",  SPI_receive_data );

	}
}
#pragma CODE_SEG DEFAULT




//初始化FM25040A        
void INIT_FM25040A(void) 
{
	HOLD_dir = 1;
	HOLD = 1;
	CS = 0;
}













