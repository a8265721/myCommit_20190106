
#include "sci.h"
#include "modbus_communication_system.h"
#include "error_system.h"

//#include "modbus_communication_system.h"
//#include "modbus_communication_protocol.h"


unsigned char data_receive[100];
int data_num = 0;
int frame_num = 0;
int is_receive_finish = 0;

u32 test_huli1 = 0;
u32 test_huli2 = 0;
u32 test_huli3 = 0;
u32 test_huli4 = 0;
u32 test_huli123 = 0;

//初始化SCI0
void INIT_SCI0(void)
{
	SCI0BD = BUS_CLOCK/16/BAUD_115200;   //设置SCI0波特率为9600

	//    SCI0CR1的ILT设为1，防止空闲特性的错误判断。
	SCI0CR1 = 0x00;        //设置SCI0为正常模式，八位数据位，无奇偶校验
	//  SCI0CR2 = 0x2c;        //允许接收和发送数据，允许接收中断功能 
	SCI0CR2 = 0x0c;        //禁止中断，只有普通的接受和发送功能
}

//串口发送函数 
void SCI0_send(unsigned char data)
{
	while(!SCI0SR1_TDRE);         //等待发送数据寄存器（缓冲器）为空
	SCI0DRL = data;
}

//串口接收函数                        
unsigned char SCI0_receive(void)
{
	while(!SCI0SR1_RDRF);          //等待发送数据寄存器满
	return(SCI0DRL);
}


#pragma CODE_SEG __NEAR_SEG NON_BANKED

// 串口中断接收函数    
interrupt void SCI0_interrupt_receive(void)
{     
	unsigned char res;
	EnableInterrupts;
	if(SCI0SR1_RDRF == 1) 
	{
		res = SCI0DRL;
		if(is_receive_finish == 0)
		{
			if(data_num < 100)
			{
				data_receive[data_num] = res;
				data_num++;
			}
			else
			{
				//如果越界，则重新开始接受
				data_num = 0;
			}
		}
	}
	else if(SCI0SR1_IDLE == 1)
	{
		res = SCI0DRL;//读数据，清除idle标志位
		if(is_receive_finish == 0)
		{
			frame_num++;
			is_receive_finish = 1; //

			//need programe //可以在此添加数据处理。。。。。。

			//处理数据完成之后，就要长度复位，准备下一次的接受。
			//		data_num = 0;
			//		is_receive_finish = 0;
		}
	}   
}
#pragma CODE_SEG DEFAULT







//初始化SCI1
void INIT_SCI1(void)
{
	SCI1BD = BUS_CLOCK/16/BAUD_115200;   //设置SCI0波特率为9600

	//    SCI0CR1的ILT设为1，防止空闲特性的错误判断。
	SCI1CR1 = 0x04;        //设置SCI0为正常模式，八位数据位，无奇偶校验
	//  SCI0CR2 = 0x2c;        //允许接收和发送数据，允许接收中断功能 
	SCI1CR2 = 0x3c;        //允许接收和发送数据，允许接收中断功能，接受空闲中断 
}

//串口发送函数 
void SCI1_send(unsigned char data)
{
	while(!SCI1SR1_TDRE);         //等待发送数据寄存器（缓冲器）为空
	SCI1DRL = data;
}

void SCI1_send_string(u8 *data,u8 len)
{
	  u8 t;
  	for(t=0;t<len;t++)	
	{
	 	while(!SCI1SR1_TDRE);         //等待发送数据寄存器（缓冲器）为空
    	SCI1DRL = data[t];
	}	 
	while(!SCI1SR1_TDRE);         //等待发送数据寄存器（缓冲器）为空
}


//串口接收函数                        
unsigned char SCI1_receive(void)
{
	while(!SCI1SR1_RDRF);          //等待发送数据寄存器满
	return(SCI1DRL);
}


#pragma CODE_SEG __NEAR_SEG NON_BANKED

// 串口中断接收函数    
interrupt void SCI1_interrupt_receive(void)
{   
	enum Error_code error_code = Succeed;  
	struct Modbus_Data_Buffer modbus1_receive_message_Buffer;
	unsigned char res;
	EnableInterrupts;
	if(SCI1SR1_RDRF == 1) 
	{
		res = SCI1DRL;
		
		
		
			if(modbus_receive_frame.frame_length  < 100)
			{                
		  	modbus_receive_frame.frame_data[modbus_receive_frame.frame_length]=res;
				modbus_receive_frame.frame_length++;
			}
			else
			{               
				//如果越界，则重新开始接受
					modbus_receive_frame.frame_length = 0;
			}
	}	
	else if(SCI1SR1_IDLE == 1)
	{
     res = SCI1DRL;//读数据，清除idle标志位
     		if(modbus_receive_frame.frame_length >= 5)
		{
			error_code = Pack_rs485_to_modbus( &modbus_receive_frame, &modbus1_receive_message_Buffer);
			if(error_code == Succeed)	
			{
				error_code = Common_list_insert_data_from_tail(&Modbus1_receive_message_list1, 0, (char*)(&modbus1_receive_message_Buffer), sizeof(struct Modbus_Data_Buffer));	
				if(error_code != Succeed)	{;}
			}	
			modbus_receive_frame.frame_length=0;
		}
		else 
		{
		
			modbus_receive_frame.frame_length=0;
		}
	}   
}
#pragma CODE_SEG DEFAULT


         
//输出重定向
void TERMIO_PutChar(char C)
{
//	while(!SCI1SR1_TDRE);         //等待发送数据寄存器（缓冲器）为空
//	SCI1DRL = C;
}

//输入重定向
char TERMIO_GetChar(void)
{
//	while(!SCI1SR1_RDRF);          //等待发送数据寄存器满
//	return(SCI1DRL);
}

       




