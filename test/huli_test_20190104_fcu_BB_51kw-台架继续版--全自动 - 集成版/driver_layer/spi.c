
#include "spi.h"



unsigned char SPI_receive_data = 0;


//��ʼ��SPIģ�� 
void INIT_SPI(void) 
{
	CS_dir = 1;

	//	SPI0CR1 = 0b01010000;   //ʹ��SPI����ֹ�жϣ�ʱ�Ӹ���Ч����λΪ0��

	//���������ж�
	SPI0CR1 = 0b11010000;   //ʹ��SPI����ֹ�жϣ�ʱ�Ӹ���Ч����λΪ0��

	SPI0CR2 = 0x00;         //SS�ܽ�Ϊ��ͨI/O
	SPI0BR = 0x70;          //����SPIʱ��Ƶ��Ϊ2MHz;
	CS = 1;
};



//SPI���ͺ���          
void SPI_send(unsigned char data) 
{
	while(!SPI0SR_SPTEF);
	SPI0DRL = data; 
}


//SPI���պ���                
unsigned char SPI_receive(void) 
{
	unsigned char temp,data;

	//ע���ˣ����ﲻ����ʹ��while��
	//��Ϊ��Щ����Χ�豸û���������͹��ܣ��������������ѭ����	
	while(!SPI0SR_SPIF);
	temp = SPI0SR;
	data = SPI0DRL;
	return(data);
}   

/*************************************************************/
/*                       SPI0�жϺ���                        */
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




//��ʼ��FM25040A        
void INIT_FM25040A(void) 
{
	HOLD_dir = 1;
	HOLD = 1;
	CS = 0;
}













