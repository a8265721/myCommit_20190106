#ifndef __CAN_COMMUNICATION_PROTOCOL2_H             
#define __CAN_COMMUNICATION_PROTOCOL2_H
                                                              

#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

#include "ect.h"
#include "error_system.h"
//#include "custom_math.h"
#include "pit.h"
#include "data_buff.h"
#include "can.h"
//#include "can_communication_protocol.h"




//巡检板单片电压  消息的数量  21
#define ITINERANT_DETECTIVE_CAN_MESSAGE_NUMBER			21

//巡检板单片电压  单片的数量  82
#define ITINERANT_DETECTIVE_SINGLE_VOLTAGE_NUMBER		82




#define AIR_COMPRESSOR_CONTROL_MSG_ID					    0x0CFF02A7//空压机控制信息ID
#define AIR_COMPRESSOR_STATS_MSG2_ID				    	0x1812A7B2//空压机状态信息ID
#define AIR_COMPRESSOR_ALARM_MSG3                           0x1811A7B2//空压机故障信息ID

#define H2_PUMP_CONTROL_MSG_ID                              0x0CFFA63D //氢气循环泵控制ID
#define H2_CIRCULATING_PUMP_DATA_ID                         0x0CFFA7B4 //氢气循环泵数据信息ID
#define H2_CIRCULATING_PUMP_PARAMETER_VALUES_ID             0x0CFFA83D   
#define H2_CIRCULATING_PUMP_ACKNOWLEDGMENT                  0x18FFABB4

#define ITINERANT_DETECTIVE_SINGLE_VOLTAGE_ACTUAL_DATA      0x1880BCBA   //实际电压值ID
#define ITINERANT_DETECTIVE_OPERATE_STATAS                  0x1801BCBA     //电堆运行状态
#define ITINERANT_DETECTIVE_SINGLE_CHIP_HIGHEST_VOLTAGE     0x1802BCBA  //电堆最高单片电压
#define ITINERANT_DETECTIVE_SINGLE_CHIP_MINIMUM_VOLTAGE     0x1803BCBA  //电堆最低单片电压
#define ITINERANT_DETECTIVE_SINGLE_VOLTAGE_SUM              0x18D4D0BA      //总电压ID

#define ITINERANT_DETECTIVE_SINGLE_VOLTAGE_ACTUAL_DATA2     0x1820BCBA   //实际电压值ID
#define ITINERANT_DETECTIVE_OPERATE_STATAS2                 0x1811BCBA     //电堆运行状态
#define ITINERANT_DETECTIVE_SINGLE_CHIP_HIGHEST_VOLTAGE2    0x1812BCBA  //电堆最高单片电压
#define ITINERANT_DETECTIVE_SINGLE_CHIP_MINIMUM_VOLTAGE2    0x1813BCBA  //电堆最低单片电压
#define ITINERANT_DETECTIVE_SINGLE_VOLTAGE_SUM2             0x1814D0BA      //总电压ID

#define INSULATION_MONITOR_DATA_ID                          0x1801D0D7  //绝缘监测仪数据


//ad采集 辅助板的can消息id
#define AD_AUXILIARY_BOARD_MESSAGE_ID                       0x12340001  //第一个为0x12340001  后面的依次递增

//ad采集 辅助板    can消息的条数  默认为6
#define AD_AUXILIARY_BOARD_MESSAGE_NUMBER_MAX           6

/*
//ad采集 辅助板    转换通道的数量最大值， 有24个ad
#define AD_AUXILIARY_BOARD_CONVERSION_NUMBER_MAX		24
//ad采集 辅助板    采集的平均值
extern u16 ad_auxiliary_board_mean_data[AD_AUXILIARY_BOARD_CONVERSION_NUMBER_MAX];
  */



//1.1空压机控制信息
typedef struct Air_compressor_Control_Msg
{
	u32		updata_event_time;	//数据更新的时间
	u32		send_message_time_max;		//超时的时间（当前系统时间 减去 上一次数据更新的时间 大于 超时时间，即为超时，通讯中断）
	u32		Message_id;			//CAN消息id（ID:0x0CFF02A7）
	u8    CompressorStart;     //空压机开关
	u32   SpeedSetpoint;       //空压机设定转速

	//	u8		DCDC_heartbeat_frame;		//心跳帧	每次加1	
}Air_compressor_Control_Msg;

//空压机控制信息//初始化
enum Error_code Air_compressor_Control_Msg_init(struct Air_compressor_Control_Msg *  p_Air_compressor_Control_Msg);
//空压机控制信息//数据解析
enum Error_code Air_compressor_Control_Msg_analysis(CAN_message * p_can_msg, struct Air_compressor_Control_Msg *  p_Air_compressor_Control_Msg);
//空压机控制信息//数据封装
enum Error_code Air_compressor_Control_Msg_encapsulation(struct Air_compressor_Control_Msg *  p_Air_compressor_Control_Msg, CAN_message * p_can_msg);
//空压机控制信息//数据处理
enum Error_code Air_compressor_Control_Msg_execute(struct Air_compressor_Control_Msg *  p_Air_compressor_Control_Msg);




//1.2空压机状态信息
typedef struct Air_compressor_stats_Msg2
{
	u32		updata_event_time;	//数据更新的时间
	u32		overtime_max;		//超时的时间（当前系统时间 减去 上一次数据更新的时间 大于 超时时间，即为超时，通讯中断）
	u32		Message_id;			//CAN消息id（ID:0x0CFF02A7）
	u8    InputCur;       //变频器输入电流
	u16   InputVol;       // 变频器输入电压
	u16   OutPutPower;     //输出功率
	i16    MotorTemp;       //电机温度
	i16    ConverterTemp;   // 控制器温度
 	i16    InsideTemp;   // 空压机内部温度

	//	u8		DCDC_heartbeat_frame;		//心跳帧	每次加1	
}Air_compressor_stats_Msg2;

//空压机状态信息//初始化
enum Error_code Air_compressor_stats_Msg2_init(struct Air_compressor_stats_Msg2 *  p_Air_compressor_stats_Msg2);
//空压机状态信息//数据解析
enum Error_code Air_compressor_stats_Msg2_analysis(CAN_message * p_can_msg, struct Air_compressor_stats_Msg2 *  p_Air_compressor_stats_Msg2);
//空压机状态信息//数据封装
enum Error_code Air_compressor_stats_Msg2_encapsulation(struct Air_compressor_stats_Msg2 *  p_Air_compressor_stats_Msg2, CAN_message * p_can_msg);
//空压机状态信息//数据处理
enum Error_code Air_compressor_stats_Msg2_execute(struct Air_compressor_stats_Msg2 *  p_Air_compressor_stats_Msg2);



//1.3空压机故障信息
typedef struct Air_compressor_alarm_Msg3
{
	u32		updata_event_time;	//数据更新的时间
	u32		overtime_max;		//超时的时间（当前系统时间 减去 上一次数据更新的时间 大于 超时时间，即为超时，通讯中断）
	u32		Message_id;			//CAN消息id（ID:0x1811A7B2）
	u8    CompressorState;   //空压机状态
	u16   FaultCode;         //故障码
	u8    faultLev;          //故障等级
	u32   ActSpeed;          //空压机实际转速

	//	u8		DCDC_heartbeat_frame;		//心跳帧	每次加1	
}Air_compressor_alarm_Msg3;

//空压机故障信息//初始化
enum Error_code Air_compressor_alarm_Msg3_init(struct Air_compressor_alarm_Msg3 *  p_Air_compressor_alarm_Msg3);
//空压机故障信息//数据解析
enum Error_code Air_compressor_alarm_Msg3_analysis(CAN_message * p_can_msg, struct Air_compressor_alarm_Msg3 *  p_Air_compressor_alarm_Msg3);
//空压机故障信息//数据封装
enum Error_code Air_compressor_alarm_Msg3_Msg_encapsulation(struct Air_compressor_alarm_Msg3 *  p_Air_compressor_alarm_Msg3, CAN_message * p_can_msg);
//空压机故障信息//数据处理
enum Error_code Air_compressor_alarm_Msg3_execute(struct Air_compressor_alarm_Msg3 *  p_Air_compressor_alarm_Msg3);




//2.1氢气循环泵控制信息
typedef struct H2_PUMP_Control_Msg
{
	u32		updata_event_time;	//数据更新的时间
	u32		send_message_time_max;		//超时的时间（当前系统时间 减去 上一次数据更新的时间 大于 超时时间，即为超时，通讯中断）
	u32		Message_id;			//CAN消息id（ID:0xOCFFA63D）
	float Mass_Flow_Setpoint;     //流量设定
	float   Speed_setpoint;       //转速设定
	u8    Enable_Pump;          //循环泵使能
	u8    Enable_Mass_Flow_Govemor;  //流量监控使能

	//	u8		DCDC_heartbeat_frame;		//心跳帧	每次加1	
}H2_PUMP_Control_Msg;

//氢气循环泵控制信息//初始化
enum Error_code H2_PUMP_Control_Msg_init(struct H2_PUMP_Control_Msg *  p_H2_PUMP_Control_Msg);
//氢气循环泵控制信息//数据解析
enum Error_code H2_PUMP_Control_Msg_analysis(CAN_message * p_can_msg, struct H2_PUMP_Control_Msg *  p_H2_PUMP_Control_Msg);
//氢气循环泵控制信息//数据封装
enum Error_code H2_PUMP_Control_Msg_encapsulation(struct H2_PUMP_Control_Msg *  p_H2_PUMP_Control_Msg, CAN_message * p_can_msg);
//氢气循环泵控制信息//数据处理
enum Error_code H2_PUMP_Control_Msg_execute(struct H2_PUMP_Control_Msg *  p_H2_PUMP_Control_Msg);


//2.2氢气循环泵数据信息
typedef struct H2_circulating_pump_data
{
	u32		updata_event_time;								 //  数据更新的时间
	u32		overtime_max;									 //  超时的时间（当前系统时间 减去 上一次数据更新的时间 大于 超时时间，即为超时，通讯中断）
	u32		Message_id;										 //  CAN消息id（ID:0xOCFFA7B4）

	float	    Actual_mass_flow;        					    //  质量流量
	float	  Actual_speed;        					            //  氢气循环泵转速
	float	    Actual_current;        					        //  氢气循环泵电流
	float	    Actual_voltage;        					        //  氢气循环泵电压
	i16	  Actual_electronic_temperature;                        //  氢气循环泵电机温度
	i16	  Actual_air_temperature;        		        	    //  氢气循环泵气体温度
	u8	    status_diagnose_word;        		    		    //  氢气循环泵状态诊断字节

}H2_circulating_pump_data;



//氢气循环泵数据信息/初始化
enum Error_code H2_circulating_pump_data_data_init(struct H2_circulating_pump_data *  p_H2_circulating_pump_data);

//氢气循环泵数据信息/数据解析  
enum Error_code H2_circulating_pump_data_analysis(CAN_message * p_can_msg, struct H2_circulating_pump_data *  p_H2_circulating_pump_data);

//氢气循环泵数据信息//数据封装
enum Error_code H2_circulating_pump_data_encapsulation(struct H2_circulating_pump_data *  p_H2_circulating_pump_data, CAN_message * p_can_msg);
//氢气循环泵数据信息//数据处理
enum Error_code H2_circulating_pump_data_data_execute(struct H2_circulating_pump_data *  p_H2_circulating_pump_data);





//2.3氢气循环泵参数信息
typedef struct H2_circulating_pump_Parameter_values
{
	u32		updata_event_time;								 //  数据更新的时间
	u32		overtime_max;									 //  超时的时间（当前系统时间 减去 上一次数据更新的时间 大于 超时时间，即为超时，通讯中断）
	u32		Message_id;										 //  CAN消息id（ID:0x0CFFA83D）

	float	    Bm_tPt1MassFlow_c;        					
	float	      Bm_KpAirGvnr_c;        					     
	float	      Bm_kiAirGvnr_c;        					     
	float	    Bm_nSetErrorRepValue_c;        		


}H2_circulating_pump_Parameter_values;



//氢气循环泵参数信息/初始化
enum Error_code H2_circulating_pump_Parameter_values_init(struct H2_circulating_pump_Parameter_values *  p_H2_circulating_pump_Parameter_values);

//氢气循环泵参数信息/数据解析  
enum Error_code H2_circulating_pump_Parameter_values_analysis(CAN_message * p_can_msg, struct H2_circulating_pump_Parameter_values *  p_H2_circulating_pump_Parameter_values);

//氢气循环泵参数信息//数据封装
enum Error_code H2_circulating_pump_Parameter_values_encapsulation(struct H2_circulating_pump_Parameter_values *  p_H2_circulating_pump_Parameter_values, CAN_message * p_can_msg);
//氢气循环泵参数信息//数据处理
enum Error_code H2_circulating_pump_Parameter_values_execute(struct H2_circulating_pump_data *  p_H2_circulating_pump_Parameter_values);


//2.4氢气循环泵AcKnowledgment信息
typedef struct H2_circulating_pump_AcKnowledgment
{
	u32		updata_event_time;								 //  数据更新的时间
	u32		overtime_max;									 //  超时的时间（当前系统时间 减去 上一次数据更新的时间 大于 超时时间，即为超时，通讯中断）
	u32		Message_id;										 //  CAN消息id（ID:0x18FFABB4）

	u8	    AcKnowledgment;        					
	u32	    Parameter_Group_number;      //需要查询的参数组编号 					     



}H2_circulating_pump_AcKnowledgment;



//氢气循环泵AcKnowledgment信息/初始化
enum Error_code H2_circulating_pump_AcKnowledgment_init(struct H2_circulating_pump_AcKnowledgment *  p_H2_circulating_pump_AcKnowledgment);

//氢气循环泵AcKnowledgment信息/数据解析  
enum Error_code H2_circulating_pump_AcKnowledgment_analysis(CAN_message * p_can_msg, struct H2_circulating_pump_AcKnowledgment *  p_H2_circulating_pump_AcKnowledgment);

//氢气循环泵AcKnowledgment信息//数据封装
enum Error_code H2_circulating_pump_AcKnowledgment_encapsulation(struct H2_circulating_pump_AcKnowledgment *  p_H2_circulating_pump_AcKnowledgment, CAN_message * p_can_msg);
//氢气循环盇cKnowledgment信息//数据处理
enum Error_code H2_circulating_pump_AcKnowledgment_execute(struct H2_circulating_pump_AcKnowledgment *  p_H2_circulating_pump_AcKnowledgment);




//3.1.0巡检电堆实际电压值
struct Itinerant_detective_Single_voltage_actual_data
{
	u32		updata_event_time;					//数据更新时间
	u32		overtime_max;		  //接受时间间隔
	u32		Message_id;							//CAN消息ID
	float		fell_single_voltage[4];				//巡检单片电压

};

//巡检电堆实际电压值//初始值
enum Error_code Itinerant_detective_Single_voltage_actual_data_init(struct Itinerant_detective_Single_voltage_actual_data *  p_Itinerant_detective_Single_voltage_actual_data,int ID_num);
//巡检电堆实际电压值//数据解析
enum Error_code Itinerant_detective_Single_voltage_actual_data_analysis(CAN_message * p_can_msg, struct Itinerant_detective_Single_voltage_actual_data *  p_Itinerant_detective_Single_voltage_actual_data);
//巡检电堆实际电压值//数据封装
enum Error_code Itinerant_detective_Single_voltage_actual_data_encapsulation(struct Itinerant_detective_Single_voltage_actual_data *  p_Itinerant_detective_Single_voltage_actual_data, CAN_message * p_can_msg);
//巡检电堆实际电压值//数据处理
enum Error_code Itinerant_detective_Single_voltage_actual_data_execute(struct Itinerant_detective_Single_voltage_actual_data *  p_Itinerant_detective_Single_voltage_actual_data);


//3.2.0巡检运行状态
struct Itinerant_detective_operate_statas
{
	u32		updata_event_time;					//数据更新时间
	u32		overtime_max;				      //接受时间间隔
	u32		Message_id;								//CAN消息ID (0x1801BCBA)
	u8	  itinerant_detective_working_statas;			//巡检运行状态
	u8 		health_of_telectric_heap;							//电池健康状态
	u8		Single_battery_overvoltage_alarm;		//单体电池过压报警
	u8    Single_battery_undervoltage_alarm;   //单体电池欠压报警
	u8		Single_voltage_unbalance_alarm;				//单体电池不均报警
	float   electric1_mean_voltage;							//电堆1平均电压
	float   electric2_mean_voltage;							//电堆2平均电压
	u8		heartbeat_frame;						//心跳帧

};

//巡检运行状态//初始值
enum Error_code Itinerant_detective_operate_statas_init(struct Itinerant_detective_operate_statas *  p_Itinerant_detective_operate_statas, u32 can_message_id);
//巡检运行状态//数据解析
enum Error_code Itinerant_detective_operate_statas_analysis(CAN_message * p_can_msg, struct Itinerant_detective_operate_statas *  p_Itinerant_detective_operate_statas);
//巡检运行状态//数据封装
enum Error_code Itinerant_detective_operate_statas_encapsulation(struct Itinerant_detective_operate_statas *  p_Itinerant_detective_operate_statas, CAN_message * p_can_msg);
//巡检运行状态//数据处理
enum Error_code Itinerant_detective_operate_statas_execute(struct Itinerant_detective_operate_statas *  p_Itinerant_detective_operate_statas);



//3.2.1 巡检单片最高电压
struct Itinerant_detective_single_chip_highest_voltage
{
	u32		updata_event_time;					//数据更新时间
	u32		overtime_max;				        //接受时间间隔;				
	u32		Message_id;							    //CAN消息ID
	float 	electric1_single_chip_highest_voltage;							//电堆1单片最高电压
	u16		electric1_single_chip_highest_voltage_num;					//电堆1单片最高电压编号
	float 	electric2_single_chip_highest_voltage;							//电堆2单片最高电压
	u16		electric2_single_chip_highest_voltage_num;					//电堆2单片最高电压编号

};

//巡检单片最高电压//初始值
enum Error_code Itinerant_detective_single_chip_highest_voltage_init(struct Itinerant_detective_single_chip_highest_voltage *  p_Itinerant_detective_single_chip_highest_voltage, u32 can_message_id);
//巡检单片最高电压//数据解析
enum Error_code Itinerant_detective_single_chip_highest_voltage_analysis(CAN_message * p_can_msg, struct Itinerant_detective_single_chip_highest_voltage *  p_Itinerant_detective_single_chip_highest_voltage);
//巡检单片最高电压//数据封装
enum Error_code Itinerant_detective_single_chip_highest_voltage_encapsulation(struct Itinerant_detective_single_chip_highest_voltage *  p_Itinerant_detective_single_chip_highest_voltage, CAN_message * p_can_msg);
//巡检单片最高电压//数据处理
enum Error_code Itinerant_detective_single_chip_highest_voltage_execute(struct Itinerant_detective_single_chip_highest_voltage *  p_Itinerant_detective_single_chip_highest_voltage);



//1.7 巡检单片最低电压	
struct Itinerant_detective_single_chip_minimum_voltage
{
	u32		updata_event_time;					//数据更新时间
	u32		overtime_max;				       //接受时间间隔;
	u32		Message_id;							   //CAN消息ID
	float 	electric1_single_chip_minimum_voltage;							//电堆1最低电压
	u16		electric1_single_chip_minimum_voltage_num;					//电堆1最低电压编号
	float 	electric2_single_chip_minimum_voltage;							//电堆2最低电压
	u16		electric2_single_chip_minimum_voltage_num;					//电堆2最低编号

};

//巡检单片最低电压	//初始值
enum Error_code Itinerant_detective_single_chip_minimum_voltage_init(struct Itinerant_detective_single_chip_minimum_voltage *  p_Itinerant_detective_single_chip_minimum_voltage, u32 can_message_id);
//巡检单片最低电压	//数据解析
enum Error_code Itinerant_detective_single_chip_minimum_voltage_analysis(CAN_message * p_can_msg, struct Itinerant_detective_single_chip_minimum_voltage *  p_Itinerant_detective_single_chip_minimum_voltage);
//巡检单片最低电压	//数据封装
enum Error_code Itinerant_detective_single_chip_minimum_voltage_encapsulation(struct Itinerant_detective_single_chip_minimum_voltage *  p_Itinerant_detective_single_chip_minimum_voltage, CAN_message * p_can_msg);
//巡检单片最低电压	//数据处理
enum Error_code Itinerant_detective_single_chip_minimum_voltage_execute(struct Itinerant_detective_single_chip_minimum_voltage *  p_Itinerant_detective_single_chip_minimum_voltage);


//1.8	巡检总电压
struct Itinerant_detective_voltage_data
{
	u32		updata_event_time;					//数据更新时间
	u32		overtime_max;				        //接受时间间隔;
	u32		Message_id;						    	 //CAN消息ID
	float	Itinerant_detective_total_voltage;			//巡检总电压				




};

//巡检总电压//初始值
enum Error_code Itinerant_detective_voltage_data_init(struct Itinerant_detective_voltage_data *  p_Itinerant_detective_voltage_data, u32 can_message_id);
//巡检总电压//数据解析
enum Error_code Itinerant_detective_voltage_data_analysis(CAN_message * p_can_msg, struct Itinerant_detective_voltage_data *  p_Itinerant_detective_voltage_data);
//巡检总电压//数据封装
enum Error_code Itinerant_detective_voltage_data_encapsulation(struct Itinerant_detective_voltage_data *  p_Itinerant_detective_voltage_data, CAN_message * p_can_msg);
//巡检总电压//数据处理
enum Error_code Itinerant_detective_voltage_data_execute(struct Itinerant_detective_voltage_data *  p_Itinerant_detective_voltage_data);





//	绝缘监测仪
struct Insulation_monitor_data
{
	u32		updata_event_time;					//数据更新时间
	u32		overtime_max;				        //接受时间间隔;
	u32		Message_id;						    	 //CAN消息ID
	u8    fault_level;                          //故障等级
	u8    error_code	;			         //故障码
	u16   Insulation_resistance_value;  //绝缘电阻值
	u16   Battery_voltage;            //电池电压
	u8    life_frame;                      //心跳帧
};

//绝缘监测仪//初始值
enum Error_code Insulation_monitor_data_init(struct Insulation_monitor_data *  p_Insulation_monitor_data);
//绝缘监测仪//数据解析
enum Error_code Insulation_monitor_data_analysis(CAN_message * p_can_msg, struct Insulation_monitor_data *  p_Insulation_monitor_data);
//绝缘监测仪//数据封装
enum Error_code Insulation_monitor_data_encapsulation(struct Insulation_monitor_data *  p_Insulation_monitor_data, CAN_message * p_can_msg);
//绝缘监测仪//数据处理
enum Error_code Insulation_monitor_data_execute(struct Insulation_monitor_data *  p_Insulation_monitor_data);







////ad采集 辅助板       作为数组 6个
struct Ad_auxiliary_board_message
{
	u32		updata_event_time;					//数据更新时间
	u32		overtime_max;				        //接受时间间隔;
	u32		message_id;						    	 //CAN消息ID
	u16     ad_auxiliary_board_message_data[4]; //can消息的ad原始值  12位ad    
};

//ad采集 辅助板//初始值
enum Error_code ad_auxiliary_board_message_init(struct Ad_auxiliary_board_message *  p_ad_auxiliary_board_message, u16 num_id);
//ad采集 辅助板//数据解析
enum Error_code ad_auxiliary_board_message_analysis(CAN_message * p_can_msg, struct Ad_auxiliary_board_message *  p_ad_auxiliary_board_message);
//ad采集 辅助板//数据封装
enum Error_code ad_auxiliary_board_message_encapsulation(struct Ad_auxiliary_board_message *  p_ad_auxiliary_board_message, CAN_message * p_can_msg);
//ad采集 辅助板//数据处理
enum Error_code ad_auxiliary_board_message_execute(struct Ad_auxiliary_board_message *  p_ad_auxiliary_board_message);



//fcu发给上位机,can通信id
#define PC_CAN_COMMUNICATION_FCU_TO_LABVIEW_ID          0x1800BDBC

//上位机发给fcu,can通信id
#define PC_CAN_COMMUNICATION_LABVIEW_TO_FCU_ID          0x1400BCBD

//fcu发给上位机 的can数量
#define PC_CAN_COMMUNICATION_FCU_TO_LABVIEW_NUMBER     44

//fcu与上位机labview的can通信，
//fcu发给上位机，0x1800BDBC~0x182BBDBC
typedef struct PC_can_communication_fcu_to_labview
{
	u32		updata_event_time;	//数据更新的时间
	u32		send_message_time_max;		//超时的时间（当前系统时间 减去 上一次数据更新的时间 大于 超时时间，即为超时，通讯中断）
	u32		message_id;			//CAN消息id（ID:0x1800BDBC）
	u32     can_message_index;  //can消息索引0~43
	//数据就不再这里备份了，直接从data_buffer.h里面去拿。
}PC_can_communication_fcu_to_labview;                     

//fcu发给上位机//初始值
enum Error_code pc_can_communication_fcu_to_labview_init(struct PC_can_communication_fcu_to_labview *  p_pc_can_communication_fcu_to_labview);
//fcu发给上位机//数据解析
enum Error_code pc_can_communication_fcu_to_labview_analysis(CAN_message * p_can_msg, struct PC_can_communication_fcu_to_labview *  p_pc_can_communication_fcu_to_labview);
//fcu发给上位机//数据封装
enum Error_code pc_can_communication_fcu_to_labview_encapsulation(struct PC_can_communication_fcu_to_labview *  p_pc_can_communication_fcu_to_labview, CAN_message * p_can_msg);
//fcu发给上位机//数据处理
enum Error_code pc_can_communication_fcu_to_labview_execute(struct PC_can_communication_fcu_to_labview *  p_pc_can_communication_fcu_to_labview);        



//上位机发给fcu，0x1400BCBD
typedef struct PC_can_communication_labview_to_fcu
{
	u32		updata_event_time;					//数据更新时间
	u32		overtime_max;				        //接受时间间隔;
	u32		message_id;						    //CAN消息ID （ID:0x1400BCBD）
	//数据就不再这里备份了，直接从data_buffer.h里面去拿。
}PC_can_communication_labview_to_fcu;                     

//上位机发给fcu//初始值
enum Error_code pc_can_communication_labview_to_fcu_init(struct PC_can_communication_labview_to_fcu *  p_pc_can_communication_labview_to_fcu);
//上位机发给fcu//数据解析
enum Error_code pc_can_communication_labview_to_fcu_analysis(CAN_message * p_can_msg, struct PC_can_communication_labview_to_fcu *  p_pc_can_communication_labview_to_fcu);
//上位机发给fcu//数据封装
enum Error_code pc_can_communication_labview_to_fcu_encapsulation(struct PC_can_communication_labview_to_fcu *  p_pc_can_communication_labview_to_fcu, CAN_message * p_can_msg);
//上位机发给fcu//数据处理
enum Error_code pc_can_communication_labview_to_fcu_execute(struct PC_can_communication_labview_to_fcu *  p_pc_can_communication_labview_to_fcu);        

                           


//can通信协议汇总
typedef struct Can_Communication_Protocol2_Total
{
	struct Air_compressor_Control_Msg		    	air_compressor_control_msg;
	struct Air_compressor_stats_Msg2		    	air_compressor_stats_msg2;
	struct Air_compressor_alarm_Msg3		    	air_compressor_alarm_msg3;

	struct H2_PUMP_Control_Msg		            	h2_pump_control_msg;
	struct H2_circulating_pump_data			    	h2_circulating_pump_data;		
	struct H2_circulating_pump_Parameter_values		h2_circulating_pump_parameter_values;
	struct H2_circulating_pump_AcKnowledgment		h2_circulating_pump_acknowledgment;

    //  1号电堆   巡检1
	struct Itinerant_detective_Single_voltage_actual_data   itinerant_detective_single_voltage_actual_data[ITINERANT_DETECTIVE_CAN_MESSAGE_NUMBER];
	struct Itinerant_detective_operate_statas			    itinerant_detective_operate_statas;		
	struct Itinerant_detective_single_chip_highest_voltage	itinerant_detective_single_chip_highest_voltage;
	struct Itinerant_detective_single_chip_minimum_voltage	itinerant_detective_single_chip_minimum_voltage;	
	struct Itinerant_detective_voltage_data              	itinerant_detective_voltage_data;	   
	
    //  2号电堆   巡检2
//	struct Itinerant_detective_Single_voltage_actual_data   itinerant_detective_single_voltage_actual_data2[ITINERANT_DETECTIVE_CAN_MESSAGE_NUMBER];
	struct Itinerant_detective_operate_statas			    itinerant_detective_operate_statas2;		
	struct Itinerant_detective_single_chip_highest_voltage	itinerant_detective_single_chip_highest_voltage2;
	struct Itinerant_detective_single_chip_minimum_voltage	itinerant_detective_single_chip_minimum_voltage2;	
	struct Itinerant_detective_voltage_data              	itinerant_detective_voltage_data2;	   

	//绝缘检测模块
	struct Insulation_monitor_data                  insulation_monitor_data;     
			             
	//辅助小板的ad采集					 
    struct Ad_auxiliary_board_message                       ad_auxiliary_board_message_array[AD_AUXILIARY_BOARD_MESSAGE_NUMBER_MAX] ;
	
	struct PC_can_communication_fcu_to_labview       pc_can_communication_fcu_to_labview;
	struct PC_can_communication_labview_to_fcu       pc_can_communication_labview_to_fcu;
}Can_Communication_Protocol2_Total;

//can通信协议汇总       
extern struct Can_Communication_Protocol2_Total    can_communication_protocol2_total;                                     

//can通信协议汇总 初始化
enum Error_code Can_communication_protocol2_init(struct Can_Communication_Protocol2_Total * p_can_communication_protocol2_total);

//把所有数据的时间清零
enum Error_code Can_communication_protocol2_clear_time(struct Can_Communication_Protocol2_Total * p_can_communication_protocol2_total);


//通过接受的CAN消息，来更新数据。
enum Error_code Can_communication_protocol2_updata_receivev_can(struct Can_Communication_Protocol2_Total * p_can_communication_protocol2_total, CAN_message * p_can_msg);


//定时封装can数据
//如果没有需要发送的消息，返回错误
//注：一次只能转化一条发送消息。如果有多条，请循环调用本函数。直到本函数返回错误
enum Error_code Can_communication_protocol2_can_encapsulation_and_send(struct Can_Communication_Protocol2_Total * p_can_communication_protocol2_total, CAN_message * p_can_msg);

/*
//定时发送can数据（默认can1）
enum Error_code Control_Policy_ontime_can_send_data(enum Can_Channels CANx, CAN_message * p_can_msg);
*/



#endif
