/*
can_communication_protocol_VMS_shanghai 本模块是针对上海强检而定做的一套can通信协议
有VMS和FCU进行通信，500kbit/s的波特率，can id是11位的标准帧。
通信协议由上海强检机构来制定，我们遵守。

用法：其他模块直接包含本模块，然后作为函数的返回值。
上层通过分析错误码来判断函数的执行情况。
*/ 
//-----------------------------------------------------------------------------------------------

#ifndef __CAN_COMMUNICATION_PROTOCOL_VMS_SHANGHAI_H             
#define __CAN_COMMUNICATION_PROTOCOL_VMS_SHANGHAI_H

#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

#include "ect.h"
#include "error_system.h"
//#include "custom_math.h"
#include "pit.h"
#include "data_buff.h"
#include "can.h"

//vms是指整车控制器，强检的时候，由上海强检机构来模拟

#define VMS_TO_FCU_CONTROL_MSG_ID					    0x303//vms发给fcu的控制命令
#define FCU_TO_VMS_SYSTEM_STATUS_MSG_ID					0x313//fcu发给vms的状态信息
#define FCU_TO_VMS_GALVANIC_PILE_MSG_ID					0x314//fcu发给vms的电堆信息
#define FCU_TO_VMS_H2_DATA_MSG_ID						0x316//fcu发给vms的氢气信息
#define FCU_TO_VMS_AIR_DATA_MSG_ID						0x317//fcu发给vms的空气信息
#define FCU_TO_VMS_WATER_FOR_PILE_DATA_MSG_ID			0x318//fcu发给vms的电堆水路信息





//一、vms发给fcu的控制命令
typedef struct VMS_to_FCU_control_msg
{
	u32		updata_event_time;	//数据更新的时间
	u32		overtime_max;		//超时的时间（当前系统时间 减去 上一次数据更新的时间 大于 超时时间，即为超时，通讯中断）
	u32		Message_id;			//CAN消息id（ID:0x303）
}VMS_to_FCU_control_msg;

//vms发给fcu的控制命令//初始化
enum Error_code VMS_to_FCU_control_msg_init(struct VMS_to_FCU_control_msg *  p_vms_to_fcu_control_msg);
//vms发给fcu的控制命令//数据解析
enum Error_code VMS_to_FCU_control_msg_analysis(CAN_message * p_can_msg, struct VMS_to_FCU_control_msg *  p_vms_to_fcu_control_msg);
//vms发给fcu的控制命令//数据封装
enum Error_code VMS_to_FCU_control_msg_encapsulation(struct VMS_to_FCU_control_msg *  p_vms_to_fcu_control_msg, CAN_message * p_can_msg);
//vms发给fcu的控制命令//数据处理
enum Error_code VMS_to_FCU_control_msg_execute(struct VMS_to_FCU_control_msg *  p_vms_to_fcu_control_msg);




//二、fcu发给vms的状态信息
typedef struct FCU_to_VMS_system_status_msg
{
	u32		updata_event_time;	//数据更新的时间
	u32		send_message_time_max;		//超时的时间（当前系统时间 减去 上一次数据更新的时间 大于 超时时间，即为超时，通讯中断）
	u32		Message_id;			//CAN消息id（ID:0x313）

	u32		power_output_max;			//当前输出功率最大值允许值
	u32		power_output_max_updata_time;//系统更新 当前输出功率最大值允许值  的更新的时间。用来防止更新的太快。目前先试1s。
	int		fcu_output_electricity_level;		//fcu输出电流的等级

}FCU_to_VMS_system_status_msg;

//fcu发给vms的状态信息//初始化
enum Error_code FCU_to_VMS_system_status_msg_init(struct FCU_to_VMS_system_status_msg *  p_fcu_to_vms_system_status_msg);
//fcu发给vms的状态信息//数据解析
enum Error_code FCU_to_VMS_system_status_msg_analysis(CAN_message * p_can_msg, struct FCU_to_VMS_system_status_msg *  p_fcu_to_vms_system_status_msg);
//fcu发给vms的状态信息//数据封装
enum Error_code FCU_to_VMS_system_status_msg_encapsulation(struct FCU_to_VMS_system_status_msg *  p_fcu_to_vms_system_status_msg, CAN_message * p_can_msg);
//fcu发给vms的状态信息//数据处理
enum Error_code FCU_to_VMS_system_status_msg_execute(struct FCU_to_VMS_system_status_msg *  p_fcu_to_vms_system_status_msg);




//三、fcu发给vms的电堆信息
typedef struct FCU_to_VMS_galvanic_pile_msg
{
	u32		updata_event_time;	//数据更新的时间
	u32		send_message_time_max;		//超时的时间（当前系统时间 减去 上一次数据更新的时间 大于 超时时间，即为超时，通讯中断）
	u32		Message_id;			//CAN消息id（ID:0x314）

}FCU_to_VMS_galvanic_pile_msg;

//fcu发给vms的电堆信息//初始化
enum Error_code FCU_to_VMS_galvanic_pile_msg_init(struct FCU_to_VMS_galvanic_pile_msg *  p_fcu_to_vms_galvanic_pile_msg);
//fcu发给vms的电堆信息//数据解析
enum Error_code FCU_to_VMS_galvanic_pile_msg_analysis(CAN_message * p_can_msg, struct FCU_to_VMS_galvanic_pile_msg *  p_fcu_to_vms_galvanic_pile_msg);
//fcu发给vms的电堆信息//数据封装
enum Error_code FCU_to_VMS_galvanic_pile_msg_encapsulation(struct FCU_to_VMS_galvanic_pile_msg *  p_fcu_to_vms_galvanic_pile_msg, CAN_message * p_can_msg);
//fcu发给vms的电堆信息//数据处理
enum Error_code FCU_to_VMS_galvanic_pile_msg_execute(struct FCU_to_VMS_galvanic_pile_msg *  p_fcu_to_vms_galvanic_pile_msg);





//四、fcu发给vms的氢气信息
typedef struct FCU_to_VMS_h2_data_msg
{
	u32		updata_event_time;	//数据更新的时间
	u32		send_message_time_max;		//超时的时间（当前系统时间 减去 上一次数据更新的时间 大于 超时时间，即为超时，通讯中断）
	u32		Message_id;			//CAN消息id（ID:0x316）

}FCU_to_VMS_h2_data_msg;

//fcu发给vms的氢气信息//初始化
enum Error_code FCU_to_VMS_h2_data_msg_init(struct FCU_to_VMS_h2_data_msg *  p_fcu_to_vms_h2_data_msg);
//fcu发给vms的氢气信息//数据解析
enum Error_code FCU_to_VMS_h2_data_msg_analysis(CAN_message * p_can_msg, struct FCU_to_VMS_h2_data_msg *  p_fcu_to_vms_h2_data_msg);
//fcu发给vms的氢气信息//数据封装
enum Error_code FCU_to_VMS_h2_data_msg_encapsulation(struct FCU_to_VMS_h2_data_msg *  p_fcu_to_vms_h2_data_msg, CAN_message * p_can_msg);
//fcu发给vms的氢气信息//数据处理
enum Error_code FCU_to_VMS_h2_data_msg_execute(struct FCU_to_VMS_h2_data_msg *  p_fcu_to_vms_h2_data_msg);






//五、fcu发给vms的空气信息
typedef struct FCU_to_VMS_air_data_msg
{
	u32		updata_event_time;	//数据更新的时间
	u32		send_message_time_max;		//超时的时间（当前系统时间 减去 上一次数据更新的时间 大于 超时时间，即为超时，通讯中断）
	u32		Message_id;			//CAN消息id（ID:0x317）

}FCU_to_VMS_air_data_msg;

//fcu发给vms的空气信息//初始化
enum Error_code FCU_to_VMS_air_data_msg_init(struct FCU_to_VMS_air_data_msg *  p_fcu_to_vms_air_data_msg);
//fcu发给vms的空气信息//数据解析
enum Error_code FCU_to_VMS_air_data_msg_analysis(CAN_message * p_can_msg, struct FCU_to_VMS_air_data_msg *  p_fcu_to_vms_air_data_msg);
//fcu发给vms的空气信息//数据封装
enum Error_code FCU_to_VMS_air_data_msg_encapsulation(struct FCU_to_VMS_air_data_msg *  p_fcu_to_vms_air_data_msg, CAN_message * p_can_msg);
//fcu发给vms的空气信息//数据处理
enum Error_code FCU_to_VMS_air_data_msg_execute(struct FCU_to_VMS_air_data_msg *  p_fcu_to_vms_air_data_msg);






//六、fcu发给vms的电堆水路信息
typedef struct FCU_to_VMS_water_for_pile_data_msg
{
	u32		updata_event_time;	//数据更新的时间
	u32		send_message_time_max;		//超时的时间（当前系统时间 减去 上一次数据更新的时间 大于 超时时间，即为超时，通讯中断）
	u32		Message_id;			//CAN消息id（ID:0x318）

}FCU_to_VMS_water_for_pile_data_msg;

//fcu发给vms的电堆水路信息//初始化
enum Error_code FCU_to_VMS_water_for_pile_data_msg_init(struct FCU_to_VMS_water_for_pile_data_msg *  p_fcu_to_vms_water_for_pile_data_msg);
//fcu发给vms的电堆水路信息//数据解析
enum Error_code FCU_to_VMS_water_for_pile_data_msg_analysis(CAN_message * p_can_msg, struct FCU_to_VMS_water_for_pile_data_msg *  p_fcu_to_vms_water_for_pile_data_msg);
//fcu发给vms的电堆水路信息//数据封装
enum Error_code FCU_to_VMS_water_for_pile_data_msg_encapsulation(struct FCU_to_VMS_water_for_pile_data_msg *  p_fcu_to_vms_water_for_pile_data_msg, CAN_message * p_can_msg);
//fcu发给vms的电堆水路信息//数据处理
enum Error_code FCU_to_VMS_water_for_pile_data_msg_execute(struct FCU_to_VMS_water_for_pile_data_msg *  p_fcu_to_vms_water_for_pile_data_msg);




//上海强检 can通信协议汇总
typedef struct Can_Communication_Protocol_VMS_Shanghai_Total
{
	struct VMS_to_FCU_control_msg					vms_to_fcu_control_msg;
	struct FCU_to_VMS_system_status_msg				fcu_to_vms_system_status_msg;
	struct FCU_to_VMS_galvanic_pile_msg				fcu_to_vms_galvanic_pile_msg;
	struct FCU_to_VMS_h2_data_msg					fcu_to_vms_h2_data_msg;
	struct FCU_to_VMS_air_data_msg					fcu_to_vms_air_data_msg;
	struct FCU_to_VMS_water_for_pile_data_msg		fcu_to_vms_water_for_pile_data_msg;

}Can_Communication_Protocol_VMS_Shanghai_Total;

//上海强检 can通信协议汇总       
extern struct Can_Communication_Protocol_VMS_Shanghai_Total    can_communication_protocol_vms_shanghai_total;                                     

//上海强检 can通信协议汇总 初始化
enum Error_code Can_communication_protocol_vms_shanghai_init(struct Can_Communication_Protocol_VMS_Shanghai_Total * p_can_communication_protocol_vms_shanghai_total);

//上海强检 把所有数据的时间清零
enum Error_code Can_communication_protocol_vms_shanghai_clear_time(struct Can_Communication_Protocol_VMS_Shanghai_Total * p_can_communication_protocol_vms_shanghai_total);


//上海强检 通过接受的CAN消息，来更新数据。
enum Error_code Can_communication_protocol_vms_shanghai_updata_receivev_can(struct Can_Communication_Protocol_VMS_Shanghai_Total * p_can_communication_protocol_vms_shanghai_total, CAN_message * p_can_msg);


//上海强检 定时封装can数据
//如果没有需要发送的消息，返回错误
//注：一次只能转化一条发送消息。如果有多条，请循环调用本函数。直到本函数返回错误
enum Error_code Can_communication_protocol_vms_shanghai_can_encapsulation_and_send(struct Can_Communication_Protocol_VMS_Shanghai_Total * p_can_communication_protocol_vms_shanghai_total, CAN_message * p_can_msg);






#endif
