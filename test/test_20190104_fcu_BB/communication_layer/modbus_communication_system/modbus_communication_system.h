/*
modbus_communication_system ��ģ����canͨ��ϵͳ
���ܣ�����modbus�������շ����ݡ�
�÷���
����ģ��ֱ�Ӱ�����ģ�飬Ȼ����Ϊ�����ķ���ֵ��
�ϲ�ͨ���������������жϺ�����ִ�������
*/ 
//-----------------------------------------------------------------------------------------------

#ifndef __MODBUS_COMMUNICATION_SYSTEM_H
#define __MODBUS_COMMUNICATION_SYSTEM_H
#include "error_system.h"
#include "common_list.h"

#define MODBUS_FRAME_DATA_LENGTH_MAX 122 		//modebus֡����ֽ�    
#define MODBUS_FRAME_DATA_LENGTH_MIN 5		//modbus֡����С���� 5

#define MODBUS_MODBUS_DATA_LENGTH_MAX 117		//modbus���ݵ���󳤶�

extern struct Modbus_Frame_Buffer modbus_send_frame;
extern struct Modbus_Frame_Buffer modbus_receive_frame;

extern Common_list Modbus1_receive_message_list1;//ȫ�ֱ�����������Ϣ����
extern struct Modbus_Data_Buffer modbus1_send_message_Buffer;

//modbus�����ݽṹ(modbus)
//��Щ��һ���Ƕ���Ч�ġ��ÿ����ݽ����ͷ�װ��ô����
//������֡ = device_address + function_code + register_address + register_number + check_value��һ��8byte
//������֡ = device_address + function_code + data_length + data + check_value�� һ��5+length
struct Modbus_Data_Buffer
{
	u8 	direction_data_transmission;									//�豸��ַ��0���㲥��ַ��1~255���豸��ַ��
	u8 	function_code;									//֡���ܣ�0~255
	u16	data_length;								//�Ĵ�����ַ
	u8	modbus_data[MODBUS_MODBUS_DATA_LENGTH_MAX];		//���ݣ��ڴ泤��Ϊ64��ʵ��ʹ�ð���data_lengthΪ׼��
	u16	check_value;									//У��ֵ
	
};

//modbus��֡�ṹ(rs485)
struct Modbus_Frame_Buffer
{
	u8	frame_length;									//֡����(���ݵ�ʵ�ʳ��ȣ�<=74 )
	u8	frame_data[MODBUS_FRAME_DATA_LENGTH_MAX];		//֡���ڴ泤��Ϊ64��ʵ��ʹ�ð�frame_length׼��(ע��frame[MODBUS_FRAME_LENGTH_MAX]����Modbus_Data_Buffer)
	u8	frameok;										//һ֡���ݽ�����ɱ�ǣ�0����û��ɣ�1�������һ֡���ݵĽ��գ�����֡��Ч������֡��Ч��
};



//Modbus1��ʼ��
enum Error_code Modbus1_Init_ex( );

//modbus֡���ݵĽ���
enum Error_code Pack_rs485_to_modbus(struct Modbus_Frame_Buffer * p_modbus_frame_buffer , struct Modbus_Data_Buffer * p_modbus_data_buffer);

//modbus֡���ݵİ�װ
enum Error_code Unpack_modbus_to_rs485( struct Modbus_Data_Buffer * p_modbus_data_buffer, struct Modbus_Frame_Buffer * p_modbus_frame_buffer );


//modbus   CRC16У��
enum Error_code CRC_16(u8 * p_bufData, u8 length, u16 * p_crc);

enum Error_code ontime_modbus_232_send_data(struct Modbus_Data_Buffer *p_modbus_send_data_buffer);




#endif



