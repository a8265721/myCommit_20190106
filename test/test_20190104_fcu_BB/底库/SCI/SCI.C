#include "SCI.h"
#include "KEY.h"
#include <stdio.h>
extern  struct SCI_receive_data  SCI_R_Ddata;

//SCIXBD:设置SCIX波特率
//SCIXCR1:设置SCIX为正常模式，八位数据位，无奇偶校验
//SCI0CR2://允许接收,发送数据,接收中断功能  
//SCI0BD=BUS_CLOCK/16/BAUD     SCI_INIT(SCI_CH0,115200);
void SCI_INIT(u8 Serial_Channel,u32 BAUD)//串口初始化
{
	u16 BAUD_DATA;
	BAUD_DATA=(u16)(BUS_CLOCK/16/BAUD);
	switch(Serial_Channel)
	{
	case 1: 
		{
			SCI0BD  = BAUD_DATA;  
			SCI0CR1 = 0x00;        
			SCI0CR2 = 0x3C;        
		}break;
	case 2: 
		{
			SCI1BD  = BAUD_DATA;  
			SCI1CR1 = 0x00;        
			SCI1CR2 = 0x2C;       
		}break;
	case 3: 
		{
			SCI2BD  = BAUD_DATA;  
			SCI2CR1 = 0x00;        
			SCI2CR2 = 0x2C;       
		}break;
	case 4: 
		{
			SCI3BD  = BAUD_DATA;
			SCI3CR1 = 0x00;        
			SCI3CR2 = 0x2C;       
		}break;
	case 5: 
		{
			SCI4BD  = BAUD_DATA; 
			SCI4CR1 = 0x00;        
			SCI4CR2 = 0x2C;       
		}break;	
	case 6: 
		{
			SCI5BD  = BAUD_DATA;  
			SCI5CR1 = 0x00;        
			SCI5CR2 = 0x2C;       
		}break;
	case 7: 
		{
			SCI6BD  = BAUD_DATA;  
			SCI6CR1 = 0x00;        
			SCI6CR2 = 0x2C;       
		}break;	
	case 8: 
		{
			SCI7BD  = BAUD_DATA;  
			SCI7CR1 = 0x00;        
			SCI7CR2 = 0x2C;       
		}break;		
	}		
}

u8 SCI_receive(u8 Serial_Channel)    //串口接收0-7
{
	u8 receive_data;
	switch(Serial_Channel)
	{
	case 1:	
		while(!SCI0SR1_RDRF);          //等待发送数据寄存器满
		receive_data=SCI0DRL;      
		break;
	case 2:	
		while(!SCI1SR1_RDRF);          //等待发送数据寄存器满
		receive_data=SCI1DRL;       
		break;
	case 3:	
		while(!SCI2SR1_RDRF);          //等待发送数据寄存器满
		receive_data=SCI2DRL;        
		break;
	case 4:	
		while(!SCI3SR1_RDRF);          //等待发送数据寄存器满
		receive_data=SCI3DRL;        
		break;
	case 5:	
		while(!SCI4SR1_RDRF);          //等待发送数据寄存器满
		receive_data=SCI4DRL;        
		break;	
	case 6:	
		while(!SCI5SR1_RDRF);          //等待发送数据寄存器满
		receive_data=SCI5DRL;      
		break;
	case 7:	
		while(!SCI6SR1_RDRF);          //等待发送数据寄存器满
		receive_data=SCI6DRL; 		
		break;	
	case 8:	
		while(!SCI7SR1_RDRF);          //等待发送数据寄存器满
		receive_data=SCI7DRL;       
		break;		
	}		
	return(receive_data);	
}
void SCI_send(u8 Serial_Channel,u8 Send_data)//串口发送0-7 
{
	switch(Serial_Channel)
	{
	case 1:	
		while(!SCI0SR1_TDRE);         //等待发送数据寄存器（缓冲器）为空   
		SCI0DRL = Send_data;        
		break;
	case 2:	
		while(!SCI1SR1_TDRE);         //等待发送数据寄存器（缓冲器）为空
		SCI1DRL = Send_data;        
		break;
	case 3:	
		while(!SCI2SR1_TDRE);         //等待发送数据寄存器（缓冲器）为空 
		SCI2DRL = Send_data;        
		break;
	case 4:	
		while(!SCI3SR1_TDRE);         //等待发送数据寄存器（缓冲器）为空  
		SCI3DRL = Send_data;        
		break;	
	case 5:	
		while(!SCI4SR1_TDRE);         //等待发送数据寄存器（缓冲器）为空   
		SCI4DRL = Send_data;        
		break;	
	case 6:	
		while(!SCI5SR1_TDRE);         //等待发送数据寄存器（缓冲器）为空 
		SCI5DRL = Send_data;        
		break;	
	case 7:	
		while(!SCI6SR1_TDRE);         //等待发送数据寄存器（缓冲器）为空   
		SCI6DRL = Send_data;        
		break;	
	case 8:	
		while(!SCI7SR1_TDRE);         //等待发送数据寄存器（缓冲器）为空   
		SCI7DRL = Send_data;        
		break;	
	}
}

void send_string(u8 Channelz,u8 *putchar)//串口发送字符串函数     
{    
	while(*putchar!=0x00)       //判断字符串是否发送完毕   
	{     
		SCI_send(Channelz,*putchar++);     
	} 
}   



void send0_string(u8 *putchar) 
{
	while(*putchar!=0x00)       //判断字符串是否发送完毕
	{
		SCI0_send(*putchar++);  
	}
}



void SCI0_send(u8 Send_data) 
{
	while(!SCI0SR1_TDRE);       //等待发送数据寄存器（缓冲器）为空
	SCI0DRL = Send_data;
}


u8 SCI0_receive(void)   //串口接收函数
{
	while(!SCI0SR1_RDRF);          //等待发送数据寄存器满
	return(SCI0DRL);
}


void TERMIO_PutChar(char Send_data) 
{
	while(!SCI0SR1_TDRE);       //等待发送数据寄存器（缓冲器）为空
	SCI0DRL = Send_data;
}

char TERMIO_GetChar(void)
{
	while(!(SCI0SR1&0x80)) ;          //keep waiting when not empty  
	return (SCI0DRL);
}
#pragma CODE_SEG __NEAR_SEG NON_BANKED
void interrupt 20 SCI0_ISR(void) 
{  
	if(SCI0SR1_RDRF)   
	{
		LED4=~LED4;	  
		SCI_R_Ddata.Receive_D[SCI_R_Ddata.Receive_Length] = SCI_receive(SCI_CH0);
		SCI_R_Ddata.Receive_Length++;
	}
	if(SCI0SR1_IDLE)   
	{ 
		if(SCI_R_Ddata.Receive_Length>0) 
		{
			SCI_R_Ddata.Receive_L=SCI_R_Ddata.Receive_Length;
			SCI_R_Ddata.Receive_Length=0;     
			SCI_R_Ddata.Receive_Complete_tag=1;
			LED3=~LED3;
		} 
		else 
		{
			SCI_R_Ddata.Receive_Length=0;
			SCI_R_Ddata.Receive_Error_tag=1;
		}  
	}                                   


}
void interrupt 21 SCI1_ISR(void) 
{
	//	u8 data_receive;
	//  data_receive = SCI_receive(SCI_CH1);

}
void interrupt 58 SCI2_ISR(void) 
{
	//	u8 data_receive;
	//  data_receive = SCI_receive(SCI_CH2);

}
void interrupt 59 SCI3_ISR(void) 
{
	//	u8 data_receive;
	//  data_receive = SCI_receive(SCI_CH3);

}
void interrupt 60 SCI4_ISR(void) 
{
	//	u8 data_receive;
	// data_receive = SCI_receive(SCI_CH4);

}
void interrupt 61 SCI5_ISR(void) 
{
	//	u8 data_receive;
	//  data_receive = SCI_receive(SCI_CH5);

}
void interrupt 30 SCI6_ISR(void) 
{
	//	u8 data_receive;
	//  data_receive = SCI_receive(SCI_CH6);

}
void interrupt 84 SCI7_ISR(void) 
{
	//	u8 data_receive;
	// data_receive = SCI_receive(SCI_CH7);

}
#pragma CODE_SEG DEFAULT





