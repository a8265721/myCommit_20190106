#ifndef _CAN_H
#define _CAN_H


#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "error_system.h"
#include "sci.h"
#include "common_list.h"

typedef enum Can_Channels
{
	CAN0 = 0,
	CAN1 = 1,
	CAN2 = 2,
	CAN3 = 3,
}Can_Channels;

//CAN_OVERTIME_MAX: 5000ms
#define CAN_OVERTIME_MAX 5000

//CAN_SEND_MESSAGE_TIME_MAX : 
#define CAN_SEND_MESSAGE_TIME_MAX_5         5

//CAN_SEND_MESSAGE_TIME_MAX : 
#define CAN_SEND_MESSAGE_TIME_MAX_100       100
#define CAN_SEND_MESSAGE_TIME_MAX_20       20

//CAN_SEND_MESSAGE_TIME_MAX : 
#define CAN_SEND_MESSAGE_TIME_MAX_1000       1000

#define CAN_DATA_LENGTH_MAX		8		//can������󳤶�

extern Common_list CAN_receive_message_list;//ȫ�ֱ�����������Ϣ����
extern Common_list CAN_receive_message_list_vms_shanghai; //ȫ�ֱ�����������Ϣ����
//extern u32 can_receive_number ;
//extern u32 can_send_number ;

//can��Ϣid��ģʽ����׼֡11λ����չ֡29λ
enum CAN_IDE_mode
{
	CAN_Id_Standard = 0,		//��׼֡
	CAN_Id_Extended = 1,		//��չ֡               
};


//can��Ϣ���ݵ����͡�����֡��Զ��֡
//��Զ��֡û�з������ݣ�ͨ����Ϊ������������Ϣ��Ȼ���ɴӻ�������ݣ�����ͬһ��id������֡������
enum CAN_RTR_mode
{
	CAN_RTR_Data = 0,			//����֡
	CAN_RTR_Remote = 1,			//Զ��֡
};


//CAN��Ϣ���ĵĽṹ�壬���ͺͽ���ͨ��
typedef struct CAN_message     
{
	u32					can_message_id;		//can��Ϣid����׼֡11λ����չ֡29λ
	enum CAN_IDE_mode	can_ide;			//can��Ϣid��ģʽ����׼֡11λ����չ֡29λ
	enum CAN_RTR_mode	can_rtr;			//can��Ϣ���ݵ����͡�����֡��Զ��֡		
	u8					can_data[8];		//8byte������		
	u8					can_len;			//���ݳ��ȣ�0~8��		
	u8					can_priorty;		//���ȼ���ֻ�з�����Ҫ���ã����ܲ���Ҫ������
	u16					can_time;			//���ܵ�ʱ�䣨ֻ�н���Ҫ��ȡ�����Ͳ���д�룬ϵͳ���Զ���ӣ�
	//���ʹ����CAN0CTL0_TIME����ô����֡��ϵͳ���Զ����ʱ�䡣
}CAN_message;



//��ʼ��can0
void INIT_CAN0(void);

//can0����
enum Error_code MSCAN0_SendMsg(struct CAN_message *p_msg);

//can0����
enum Error_code MSCAN0_ReceiveMsg(struct CAN_message *p_msg);

//can0�����ж�
//void interrupt can0_interrupt_receive(void)  ;


//��ʼ��can1
void INIT_CAN1(void);

//can1����
enum Error_code MSCAN1_SendMsg(struct CAN_message *p_msg);

//can1����
enum Error_code MSCAN1_ReceiveMsg(struct CAN_message *p_msg);

//can1�����ж�
//void interrupt can1_interrupt_receive(void)  ;



//��ʼ��can2
void INIT_CAN2(void);

//can2����
enum Error_code MSCAN2_SendMsg(struct CAN_message *p_msg);

//can2����
enum Error_code MSCAN2_ReceiveMsg(struct CAN_message *p_msg);

//can2�����ж�
//void interrupt can2_interrupt_receive(void)  ;

 //��ʱ����can���ݣ�Ĭ��can0��
enum Error_code Control_Policy_ontime_can_send_data(enum Can_Channels CANx, CAN_message * p_can_msg);


#endif
