
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

//��ʼ��SCI0
void INIT_SCI0(void)
{
	SCI0BD = BUS_CLOCK/16/BAUD_115200;   //����SCI0������Ϊ9600

	//    SCI0CR1��ILT��Ϊ1����ֹ�������ԵĴ����жϡ�
	SCI0CR1 = 0x00;        //����SCI0Ϊ����ģʽ����λ����λ������żУ��
	//  SCI0CR2 = 0x2c;        //������պͷ������ݣ���������жϹ��� 
	SCI0CR2 = 0x0c;        //��ֹ�жϣ�ֻ����ͨ�Ľ��ܺͷ��͹���
}

//���ڷ��ͺ��� 
void SCI0_send(unsigned char data)
{
	while(!SCI0SR1_TDRE);         //�ȴ��������ݼĴ�������������Ϊ��
	SCI0DRL = data;
}

//���ڽ��պ���                        
unsigned char SCI0_receive(void)
{
	while(!SCI0SR1_RDRF);          //�ȴ��������ݼĴ�����
	return(SCI0DRL);
}


#pragma CODE_SEG __NEAR_SEG NON_BANKED

// �����жϽ��պ���    
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
				//���Խ�磬�����¿�ʼ����
				data_num = 0;
			}
		}
	}
	else if(SCI0SR1_IDLE == 1)
	{
		res = SCI0DRL;//�����ݣ����idle��־λ
		if(is_receive_finish == 0)
		{
			frame_num++;
			is_receive_finish = 1; //

			//need programe //�����ڴ�������ݴ�������������

			//�����������֮�󣬾�Ҫ���ȸ�λ��׼����һ�εĽ��ܡ�
			//		data_num = 0;
			//		is_receive_finish = 0;
		}
	}   
}
#pragma CODE_SEG DEFAULT







//��ʼ��SCI1
void INIT_SCI1(void)
{
	SCI1BD = BUS_CLOCK/16/BAUD_115200;   //����SCI0������Ϊ9600

	//    SCI0CR1��ILT��Ϊ1����ֹ�������ԵĴ����жϡ�
	SCI1CR1 = 0x04;        //����SCI0Ϊ����ģʽ����λ����λ������żУ��
	//  SCI0CR2 = 0x2c;        //������պͷ������ݣ���������жϹ��� 
	SCI1CR2 = 0x3c;        //������պͷ������ݣ���������жϹ��ܣ����ܿ����ж� 
}

//���ڷ��ͺ��� 
void SCI1_send(unsigned char data)
{
	while(!SCI1SR1_TDRE);         //�ȴ��������ݼĴ�������������Ϊ��
	SCI1DRL = data;
}

void SCI1_send_string(u8 *data,u8 len)
{
	  u8 t;
  	for(t=0;t<len;t++)	
	{
	 	while(!SCI1SR1_TDRE);         //�ȴ��������ݼĴ�������������Ϊ��
    	SCI1DRL = data[t];
	}	 
	while(!SCI1SR1_TDRE);         //�ȴ��������ݼĴ�������������Ϊ��
}


//���ڽ��պ���                        
unsigned char SCI1_receive(void)
{
	while(!SCI1SR1_RDRF);          //�ȴ��������ݼĴ�����
	return(SCI1DRL);
}


#pragma CODE_SEG __NEAR_SEG NON_BANKED

// �����жϽ��պ���    
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
				//���Խ�磬�����¿�ʼ����
					modbus_receive_frame.frame_length = 0;
			}
	}	
	else if(SCI1SR1_IDLE == 1)
	{
     res = SCI1DRL;//�����ݣ����idle��־λ
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


         
//����ض���
void TERMIO_PutChar(char C)
{
//	while(!SCI1SR1_TDRE);         //�ȴ��������ݼĴ�������������Ϊ��
//	SCI1DRL = C;
}

//�����ض���
char TERMIO_GetChar(void)
{
//	while(!SCI1SR1_RDRF);          //�ȴ��������ݼĴ�����
//	return(SCI1DRL);
}

       




