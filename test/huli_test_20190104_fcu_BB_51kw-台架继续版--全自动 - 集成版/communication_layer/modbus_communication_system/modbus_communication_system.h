/*
modbus_communication_system 本模块是can通信系统
功能：配置modbus，并且收发数据。
用法：
其他模块直接包含本模块，然后作为函数的返回值。
上层通过分析错误码来判断函数的执行情况。
*/ 
//-----------------------------------------------------------------------------------------------

#ifndef __MODBUS_COMMUNICATION_SYSTEM_H
#define __MODBUS_COMMUNICATION_SYSTEM_H
#include "error_system.h"
#include "common_list.h"

#define MODBUS_FRAME_DATA_LENGTH_MAX 122 		//modebus帧最大字节    
#define MODBUS_FRAME_DATA_LENGTH_MIN 5		//modbus帧的最小长度 5

#define MODBUS_MODBUS_DATA_LENGTH_MAX 117		//modbus数据的最大长度

extern struct Modbus_Frame_Buffer modbus_send_frame;
extern struct Modbus_Frame_Buffer modbus_receive_frame;

extern Common_list Modbus1_receive_message_list1;//全局变量，接受消息缓存
extern struct Modbus_Data_Buffer modbus1_send_message_Buffer;

//modbus的数据结构(modbus)
//这些不一定是都有效的。得看数据解析和封装怎么处理。
//（发送帧 = device_address + function_code + register_address + register_number + check_value）一共8byte
//（接收帧 = device_address + function_code + data_length + data + check_value） 一共5+length
struct Modbus_Data_Buffer
{
	u8 	direction_data_transmission;									//设备地址：0，广播地址；1~255，设备地址。
	u8 	function_code;									//帧功能，0~255
	u16	data_length;								//寄存器地址
	u8	modbus_data[MODBUS_MODBUS_DATA_LENGTH_MAX];		//数据（内存长度为64，实际使用按照data_length为准）
	u16	check_value;									//校验值
	
};

//modbus的帧结构(rs485)
struct Modbus_Frame_Buffer
{
	u8	frame_length;									//帧长度(数据的实际长度，<=74 )
	u8	frame_data[MODBUS_FRAME_DATA_LENGTH_MAX];		//帧（内存长度为64，实际使用按frame_length准）(注：frame[MODBUS_FRAME_LENGTH_MAX]就是Modbus_Data_Buffer)
	u8	frameok;										//一帧数据接收完成标记：0，还没完成；1，完成了一帧数据的接收（接受帧有效，发送帧无效）
};



//Modbus1初始化
enum Error_code Modbus1_Init_ex( );

//modbus帧数据的解析
enum Error_code Pack_rs485_to_modbus(struct Modbus_Frame_Buffer * p_modbus_frame_buffer , struct Modbus_Data_Buffer * p_modbus_data_buffer);

//modbus帧数据的包装
enum Error_code Unpack_modbus_to_rs485( struct Modbus_Data_Buffer * p_modbus_data_buffer, struct Modbus_Frame_Buffer * p_modbus_frame_buffer );


//modbus   CRC16校验
enum Error_code CRC_16(u8 * p_bufData, u8 length, u16 * p_crc);

enum Error_code ontime_modbus_232_send_data(struct Modbus_Data_Buffer *p_modbus_send_data_buffer);




#endif



