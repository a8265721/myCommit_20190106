#ifndef __CAN_COMMUNICATION_PROTOCOL_H
#define __CAN_COMMUNICATION_PROTOCOL_H


#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

#include "ect.h"
#include "error_system.h"
#include "custom_math.h"
#include "pid.h"                    
#include "data_buff.h"
#include "can.h"
/*
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
*/
#define TEMPERATURE_DATA_ACQUISITION_MESSAGE_ID					0x1801D0CC//温度采集数据
#define PRESSURE_DATA1_ACQUISITION_MESSAGE_ID					0x1802D0CC//压力采集数据1
#define PRESSURE_DATA2_ACQUISITION_MESSAGE_ID					0x1803D0CC//压力采集数据2
#define PRESSURE_DATA3_ACQUISITION_MESSAGE_ID					0x1804D0CC//压力采集数据3
#define DIGITAL_QUANTITY_INPUT_MESSAGE_ID						0x1805D0CC//数字量输入

#define DIGITAL_QUANTITY_OUTPUT_MESSAGE_ID						0x1801BCD0//数字量输出
#define PWM_OUTPUT_MESSAGE_ID									0x1802BCD0//PWM输出


//温度采集数据
typedef struct Temperature_Data_Acquisition
{
	u32		updata_event_time;	//数据更新的时间
	u32		overtime_max;		//超时的时间（当前系统时间 减去 上一次数据更新的时间 大于 超时时间，即为超时，通讯中断）
	u32		Message_id;			//CAN消息id（ID:0x1801D0BC）

	u8		DCDC_heartbeat_frame;		//心跳帧	每次加1	
}Temperature_Data_Acquisition;

//温度采集数据//初始化
enum Error_code temperature_data_acquisition_init(struct Temperature_Data_Acquisition *  p_temperature_data_acquisition);
//温度采集数据//数据解析
enum Error_code temperature_data_acquisition_analysis(CAN_message * p_can_msg, struct Temperature_Data_Acquisition *  p_temperature_data_acquisition);
//温度采集数据//数据封装
enum Error_code temperature_data_acquisition_encapsulation(struct Temperature_Data_Acquisition *  p_temperature_data_acquisition, CAN_message * p_can_msg);
//温度采集数据//数据处理
enum Error_code temperature_data_acquisition_execute(struct Temperature_Data_Acquisition *  p_temperature_data_acquisition);






//压力采集数据1
typedef struct Pressure_Data1_Acquisition
{
	u32		updata_event_time;	//数据更新的时间
	u32		overtime_max;		//超时的时间（当前系统时间 减去 上一次数据更新的时间 大于 超时时间，即为超时，通讯中断）
	u32		Message_id;			//CAN消息id（ID:0x1802D0BC）
}Pressure_Data1_Acquisition;

//压力采集数据1//初始化
enum Error_code pressure_data1_acquisition_init(struct Pressure_Data1_Acquisition *  p_pressure_data1_acquisition);
//压力采集数据1//数据解析
enum Error_code pressure_data1_acquisition_analysis(CAN_message * p_can_msg, struct Pressure_Data1_Acquisition *  p_pressure_data1_acquisition);
//压力采集数据1//数据封装
enum Error_code pressure_data1_acquisition_encapsulation(struct Pressure_Data1_Acquisition *  p_pressure_data1_acquisition, CAN_message * p_can_msg);
//压力采集数据1//数据处理
enum Error_code pressure_data1_acquisition_execute(struct Pressure_Data1_Acquisition *  p_pressure_data1_acquisition);







//压力采集数据2
typedef struct Pressure_Data2_Acquisition
{
	u32		updata_event_time;	//数据更新的时间
	u32		overtime_max;		//超时的时间（当前系统时间 减去 上一次数据更新的时间 大于 超时时间，即为超时，通讯中断）
	u32		Message_id;			//CAN消息id（ID:0x1803D0BC）
}Pressure_Data2_Acquisition;

//压力采集数据2//初始化
enum Error_code pressure_data2_acquisition_init(struct Pressure_Data2_Acquisition *  p_pressure_data2_acquisition);
//压力采集数据2//数据解析
enum Error_code pressure_data2_acquisition_analysis(CAN_message * p_can_msg, struct Pressure_Data2_Acquisition *  p_pressure_data2_acquisition);
//压力采集数据2//数据封装
enum Error_code pressure_data2_acquisition_encapsulation(struct Pressure_Data2_Acquisition *  p_pressure_data2_acquisition, CAN_message * p_can_msg);
//压力采集数据2//数据处理
enum Error_code pressure_data2_acquisition_execute(struct Pressure_Data2_Acquisition *  p_pressure_data2_acquisition);






//压力采集数据3
typedef struct Pressure_Data3_Acquisition
{
	u32		updata_event_time;	//数据更新的时间
	u32		overtime_max;		//超时的时间（当前系统时间 减去 上一次数据更新的时间 大于 超时时间，即为超时，通讯中断）
	u32		Message_id;			//CAN消息id（ID:0x1804D0BC）
}Pressure_Data3_Acquisition;

//压力采集数据3//初始化
enum Error_code pressure_data3_acquisition_init(struct Pressure_Data3_Acquisition *  p_pressure_data3_acquisition);
//压力采集数据3//数据解析
enum Error_code pressure_data3_acquisition_analysis(CAN_message * p_can_msg, struct Pressure_Data3_Acquisition *  p_pressure_data3_acquisition);
//压力采集数据3//数据封装
enum Error_code pressure_data3_acquisition_encapsulation(struct Pressure_Data3_Acquisition *  p_pressure_data3_acquisition, CAN_message * p_can_msg);
//压力采集数据3//数据处理
enum Error_code pressure_data3_acquisition_execute(struct Pressure_Data3_Acquisition *  p_pressure_data3_acquisition);






//数字量输入
typedef struct Digital_Quantity_Input
{
	u32		updata_event_time;	//数据更新的时间
	u32		overtime_max;		//超时的时间（当前系统时间 减去 上一次数据更新的时间 大于 超时时间，即为超时，通讯中断）
	u32		Message_id;			//CAN消息id（ID:0x1801D0BC）
}Digital_Quantity_Input;

//数字量输入//初始化
enum Error_code digital_quantity_input_init(struct Digital_Quantity_Input *  p_digital_quantity_input);
//数字量输入//数据解析
enum Error_code digital_quantity_input_analysis(CAN_message * p_can_msg, struct Digital_Quantity_Input *  p_digital_quantity_input);
//数字量输入//数据封装
enum Error_code digital_quantity_input_encapsulation(struct Digital_Quantity_Input *  p_digital_quantity_input, CAN_message * p_can_msg);
//数字量输入//数据处理
enum Error_code digital_quantity_input_execute(struct Digital_Quantity_Input *  p_digital_quantity_input);








//数字量输出
typedef struct Digital_Quantity_Output
{
	u32		updata_event_time;	//数据更新的时间
	u32		send_message_time_max;		//超时的时间（当前系统时间 减去 上一次数据更新的时间 大于 超时时间，即为超时，通讯中断）
	u32		Message_id;			//CAN消息id（ID:0x1801BCD0）
}Digital_Quantity_Output;

//数字量输出//初始化
enum Error_code digital_quantity_output_init(struct Digital_Quantity_Output *  p_digital_quantity_output);
//数字量输出//数据解析
enum Error_code digital_quantity_output_analysis(CAN_message * p_can_msg, struct Digital_Quantity_Output *  p_digital_quantity_output);
//数字量输出//数据封装
enum Error_code digital_quantity_output_encapsulation(struct Digital_Quantity_Output *  p_digital_quantity_output, CAN_message * p_can_msg);
//数字量输出//数据处理
enum Error_code digital_quantity_output_execute(struct Digital_Quantity_Output *  p_digital_quantity_output);





//PWM输出
typedef struct Pwm_Output
{
	u32		updata_event_time;	//数据更新的时间
	u32		send_message_time_max;		//超时的时间（当前系统时间 减去 上一次数据更新的时间 大于 超时时间，即为超时，通讯中断）
	u32		Message_id;			//CAN消息id（ID:0x1802BCD0）
}Pwm_Output;

//PWM输出//初始化
enum Error_code pwm_output_init(struct Pwm_Output *  p_pwm_output);
//PWM输出//数据解析
enum Error_code pwm_output_analysis(CAN_message * p_can_msg, struct Pwm_Output *  p_pwm_output);
//PWM输出//数据封装
enum Error_code pwm_output_encapsulation(struct Pwm_Output *  p_pwm_output, CAN_message * p_can_msg);
//PWM输出//数据处理
enum Error_code pwm_output_execute(struct Pwm_Output *  p_pwm_output);







//can通信协议汇总
typedef struct Can_Communication_Protocol_Total
{
	struct Temperature_Data_Acquisition			temperature_data_acquisition;
	struct Pressure_Data1_Acquisition			pressure_data1_acquisition;
	struct Pressure_Data2_Acquisition			pressure_data2_acquisition;
	struct Pressure_Data3_Acquisition			pressure_data3_acquisition;
	struct Digital_Quantity_Input				digital_quantity_input;		

	struct Digital_Quantity_Output				digital_quantity_output;
	struct Pwm_Output							pwm_output;
}Can_Communication_Protocol_Total;

//can通信协议汇总       
extern struct Can_Communication_Protocol_Total    can_communication_protocol_total;                                     

//can通信协议汇总 初始化
enum Error_code Can_communication_protocol_init(struct Can_Communication_Protocol_Total * p_can_communication_protocol_total);

//把所有数据的时间清零
enum Error_code Can_communication_protocol_clear_time(struct Can_Communication_Protocol_Total * p_can_communication_protocol_total);


//通过接受的CAN消息，来更新数据。
enum Error_code Can_communication_protocol_updata_receivev_can(struct Can_Communication_Protocol_Total * p_can_communication_protocol_total, CAN_message * p_can_msg);


//定时封装can数据
//如果没有需要发送的消息，返回错误
//注：一次只能转化一条发送消息。如果有多条，请循环调用本函数。直到本函数返回错误
enum Error_code Can_communication_protocol_can_encapsulation_and_send(struct Can_Communication_Protocol_Total * p_can_communication_protocol_total, CAN_message * p_can_msg);

/*
//定时发送can数据（默认can0）
enum Error_code Control_Policy_ontime_can_send_data(enum Can_Channels CANx, CAN_message * p_can_msg);
*/













#endif


