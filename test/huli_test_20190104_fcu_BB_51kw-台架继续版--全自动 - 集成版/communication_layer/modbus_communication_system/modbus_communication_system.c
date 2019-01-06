/*
modbus_communication_system 本模块是can通信系统
功能：配置modbus，并且收发数据。
用法：
其他模块直接包含本模块，然后作为函数的返回值。
上层通过分析错误码来判断函数的执行情况。
*/ 
//-----------------------------------------------------------------------------------------------

#include "modbus_communication_system.h"

int cre_test=0;
int cre_test1=0;
int cre_test2=0;

u16 cre_value=0;
u16 cre_value1=0;

#include "common_list.h"
#include "error_system.h"	 
#include  "sci.h"  


struct Modbus_Frame_Buffer modbus_send_frame;
struct Modbus_Frame_Buffer modbus_receive_frame;

Common_list Modbus1_receive_message_list1;//全局变量，接受消息缓存
struct Modbus_Data_Buffer modbus1_send_message_Buffer;


//Modbus1初始化
enum Error_code Modbus1_Init_ex()
{
	enum Error_code error_code = Succeed;
	int i  = 0;



	Common_list_init( &Modbus1_receive_message_list1 );

	modbus1_send_message_Buffer.direction_data_transmission = 0;
	modbus1_send_message_Buffer.function_code = 0;
	modbus1_send_message_Buffer.data_length = 0;
	modbus1_send_message_Buffer.check_value = 0;
	for(i=0; i<MODBUS_MODBUS_DATA_LENGTH_MAX; i++)
	{
		modbus1_send_message_Buffer.modbus_data[i] = 0;
	}

	modbus_send_frame.frameok = 0;
	modbus_send_frame.frame_length = 0;
	for(i=0; i<MODBUS_FRAME_DATA_LENGTH_MAX; i++)
	{
		modbus_send_frame.frame_data[i] = 0;
	}

	modbus_receive_frame.frameok = 0;
	modbus_receive_frame.frame_length = 0;
	
	for(i=0; i<MODBUS_FRAME_DATA_LENGTH_MAX; i++)
	{
		modbus_receive_frame.frame_data[i] = 0;
	}

	return error_code;
}


//modbus帧数据的解析
enum Error_code Pack_rs485_to_modbus(struct Modbus_Frame_Buffer * p_modbus_frame_buffer , struct Modbus_Data_Buffer * p_modbus_data_buffer)
{
	enum Error_code error_code = Succeed;
	u16 crc_calculated = 0;	//计算的结果
	u16 crc_actual = 0;		//实际的结果
	int i = 0;
  
	if(p_modbus_frame_buffer == NULL || p_modbus_data_buffer == NULL)
	{return Pointer_is_null;}

	if(p_modbus_frame_buffer->frame_length < MODBUS_FRAME_DATA_LENGTH_MIN)
	{return Parameter_error;}
	//先校验crc
	error_code = CRC_16(p_modbus_frame_buffer->frame_data, (p_modbus_frame_buffer->frame_length) -2,&crc_calculated);

   cre_value=crc_calculated;
        
	if(error_code != Succeed)	{return error_code;}

	crc_actual = (u16)( p_modbus_frame_buffer->frame_data[(p_modbus_frame_buffer->frame_length) -2] )  
		|  ( (u16)( p_modbus_frame_buffer->frame_data[(p_modbus_frame_buffer->frame_length) -1] ) <<8 );

    cre_value1= crc_actual;
	
	if(crc_calculated == crc_actual  /*&& p_modbus_frame_buffer->frame_data[2] + MODBUS_FRAME_DATA_LENGTH_MIN == p_modbus_frame_buffer->frame_length*/)
	{
		p_modbus_data_buffer->direction_data_transmission = p_modbus_frame_buffer->frame_data[0];
		
		cre_test= p_modbus_frame_buffer->frame_data[0];
		p_modbus_data_buffer->function_code = p_modbus_frame_buffer->frame_data[1];
		
		cre_test1=p_modbus_frame_buffer->frame_data[1];
		
		p_modbus_data_buffer->data_length = p_modbus_frame_buffer->frame_data[2];
		
		 cre_test2= p_modbus_frame_buffer->frame_data[2];
		p_modbus_data_buffer->check_value = crc_actual;
		for(i=0; i<p_modbus_data_buffer->data_length ; i++)
		{
			p_modbus_data_buffer->modbus_data[i] = p_modbus_frame_buffer->frame_data[i+3];
		}

	}
	else
	{
		return Failed;
		printf("CRC校验失败");
	}
	

	return error_code;
}


//modbus帧数据的包装
enum Error_code Unpack_modbus_to_rs485( struct Modbus_Data_Buffer * p_modbus_data_buffer, struct Modbus_Frame_Buffer * p_modbus_frame_buffer )
{
	enum Error_code error_code = Succeed;
	u16 crc_calculated = 0;	//计算的结果
	u16 i=0;
	u16 num=0;
	


	if(p_modbus_frame_buffer == NULL || p_modbus_data_buffer == NULL)
	{return Pointer_is_null;}

	p_modbus_frame_buffer->frameok = 0;
//	p_modbus_frame_buffer->frame_length = 8;//长度固定为8  这里我没有用到这个数据
	
	
  
	p_modbus_frame_buffer->frame_data[0] = p_modbus_data_buffer->direction_data_transmission;
	p_modbus_frame_buffer->frame_data[1] = p_modbus_data_buffer->function_code;
	p_modbus_frame_buffer->frame_data[2] = p_modbus_data_buffer->data_length;
	
	num= p_modbus_data_buffer->data_length;
	
//	for(i=0;i<num;i++)
  for(i=0;i<p_modbus_data_buffer->data_length;i++)
	{
	  	p_modbus_frame_buffer->frame_data[3+i]=p_modbus_data_buffer->modbus_data[i];
	}

	p_modbus_frame_buffer->frame_length =  p_modbus_data_buffer->data_length + 5;
	
	error_code = CRC_16(p_modbus_frame_buffer->frame_data, 3+num, &crc_calculated);
	if(error_code != Succeed)	{return error_code;}
	p_modbus_frame_buffer->frame_data[3+num] = crc_calculated & 0x00FF;           
	p_modbus_frame_buffer->frame_data[4+num] = crc_calculated >>8;
	
	
	

	return error_code;
}


              



//modbus   CRC16校验
enum Error_code CRC_16(u8 * p_bufData, u8 length, u16 * p_crc)
{
	enum Error_code error_code = Succeed;
	u8 i, j, temp;

	if(p_bufData == NULL ||  p_crc == NULL)
	{return Pointer_is_null;}

	(*p_crc) = 0xFFFF;
	for(i=0; i< length; i++)
	{
		(*p_crc) ^= p_bufData[i];
		for(j=0; j< 8; j++)
		{
			temp = (*p_crc) & 0x0001;
			(*p_crc) = (*p_crc) >> 1;
			if(temp)
			{
				(*p_crc) = (*p_crc) ^ 0xA001;
			}
		}
	}


	return error_code;
}



//定时发送modbus
enum Error_code ontime_modbus_232_send_data(struct Modbus_Data_Buffer *p_modbus_send_data_buffer)
{
 	enum Error_code error_code = Succeed;
	struct Modbus_Frame_Buffer modbus_frame_buffer;
	 		

	if(p_modbus_send_data_buffer == NULL)
	{return Pointer_is_null;}                                     
                  
	error_code = Unpack_modbus_to_rs485(p_modbus_send_data_buffer, &modbus_frame_buffer);
	if(error_code != Succeed)	{return error_code;}

  SCI1_send_string(modbus_frame_buffer.frame_data, modbus_frame_buffer.frame_length);

	return error_code;
}




