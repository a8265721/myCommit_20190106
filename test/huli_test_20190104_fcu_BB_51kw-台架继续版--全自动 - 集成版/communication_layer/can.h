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

#define CAN_DATA_LENGTH_MAX		8		//can数据最大长度

extern Common_list CAN_receive_message_list;//全局变量，接受消息缓存
extern Common_list CAN_receive_message_list_vms_shanghai; //全局变量，接受消息缓存
//extern u32 can_receive_number ;
//extern u32 can_send_number ;

//can消息id的模式。标准帧11位，扩展帧29位
enum CAN_IDE_mode
{
	CAN_Id_Standard = 0,		//标准帧
	CAN_Id_Extended = 1,		//扩展帧               
};


//can消息数据的类型。数据帧和远程帧
//（远程帧没有发送数据，通常作为主机的请求消息，然后由从机填充数据，发送同一个id的数据帧回来）
enum CAN_RTR_mode
{
	CAN_RTR_Data = 0,			//数据帧
	CAN_RTR_Remote = 1,			//远程帧
};


//CAN消息报文的结构体，发送和接收通用
typedef struct CAN_message     
{
	u32					can_message_id;		//can消息id，标准帧11位，扩展帧29位
	enum CAN_IDE_mode	can_ide;			//can消息id的模式。标准帧11位，扩展帧29位
	enum CAN_RTR_mode	can_rtr;			//can消息数据的类型。数据帧和远程帧		
	u8					can_data[8];		//8byte的数据		
	u8					can_len;			//数据长度（0~8）		
	u8					can_priorty;		//优先级（只有发送需要配置，接受不需要解析）
	u16					can_time;			//接受的时间（只有接受要读取，发送不用写入，系统会自动添加）
	//如果使能了CAN0CTL0_TIME，那么发送帧，系统会自动添加时间。
}CAN_message;



//初始化can0
void INIT_CAN0(void);

//can0发送
enum Error_code MSCAN0_SendMsg(struct CAN_message *p_msg);

//can0接受
enum Error_code MSCAN0_ReceiveMsg(struct CAN_message *p_msg);

//can0接受中断
//void interrupt can0_interrupt_receive(void)  ;


//初始化can1
void INIT_CAN1(void);

//can1发送
enum Error_code MSCAN1_SendMsg(struct CAN_message *p_msg);

//can1接受
enum Error_code MSCAN1_ReceiveMsg(struct CAN_message *p_msg);

//can1接受中断
//void interrupt can1_interrupt_receive(void)  ;



//初始化can2
void INIT_CAN2(void);

//can2发送
enum Error_code MSCAN2_SendMsg(struct CAN_message *p_msg);

//can2接受
enum Error_code MSCAN2_ReceiveMsg(struct CAN_message *p_msg);

//can2接受中断
//void interrupt can2_interrupt_receive(void)  ;

 //定时发送can数据（默认can0）
enum Error_code Control_Policy_ontime_can_send_data(enum Can_Channels CANx, CAN_message * p_can_msg);


#endif
