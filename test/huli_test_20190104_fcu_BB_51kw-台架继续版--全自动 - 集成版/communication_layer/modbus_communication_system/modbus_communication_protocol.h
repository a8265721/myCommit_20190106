/*
can_communication_system 本模块是can通信系统
功能：配置can，并且收发数据。
用法：
其他模块直接包含本模块，然后作为函数的返回值。
上层通过分析错误码来判断函数的执行情况。
*/ 
//-----------------------------------------------------------------------------------------------





#ifndef __MODBUS_COMMUNICATION_PROTOCOL_H
#define __MODBUS_COMMUNICATION_PROTOCOL_H

#include "error_system.h"
#include "modbus_communication_system.h"
#include "control_manager.h"





#define MODBUS_232_SEND_MESSAGE_TIME_MAX   1500        //modbus_232的发送时间间隔

#define DIRECTION_DATA_TRANSMISSION_PC_TO_FCU  0XAA

#define DIRECTION_DATA_TRANSMISSION_FCU_TO_PC  0XBB

#define FUNCTION_CODE_01  1
#define FUNCTION_CODE_02  2
#define FUNCTION_CODE_03  3
#define FUNCTION_CODE_04  4
#define FUNCTION_CODE_05  5
#define FUNCTION_CODE_06  6


extern struct FCU_modbus_tatal_manager_data  fcu_modbus_tatal_manager_data;









//1、氢气数据

//1.1氢气数据信息
struct Hydrogen_detective_data
{	

  u32   updata_event_time;    //数据更新时间
  u32		send_message_time_max;         //这个超时时间可以理解为 发送信息的时间频率 比如500ms发送一次
  u8    direction_data_transmission;   //数据传输方向
	u8		function_code;				//帧功能
  u8		data_length;				//数据字节长度
  float	h2_pressure_proportional_valve_front;	//比例阀前氢压，fcu系统的H2供气口，		输入4-20mA
  float	h2_pressure_proportional_valve_rear;	//比例阀后氢压，                		输入4-20mA
	float	h2_pressure_pile_inlet;	                //入堆氢压，是电堆的H2入口          	输入4-20mA	
  float	h2_pressure_pile_outlet;	            //出堆氢压，是电堆的H2出口  	输入4-20mA	
  float	h2_pressure_tail_outlet;				//氢气尾排的压力,也是电堆H2出口压力		输入4-20mA	


  //输出
  u8		h2_inlet_valve;							//氢气进气阀，							输出0或1
	u8		h2_outlet_valve;						//氢气尾排阀，							输出0或1
	float	h2_proportional_valve_pwm_dutyfactor;	//比例阀PWM占空比，pid自动控制。		输出pwm 0~5V  频率>1000HZ
	u8		h2_circulating_pump_enble;				//氢气循环泵的IO使能					输出0或1
	
	//氢气循环泵  can通信
	enum 	Working_Communication_Mode		h2_circulating_pump_working_communication_mode;	//氢气循环泵  can通信模式
	u16     h2_circulating_pump_speed_setpoint;             //氢气循环泵转速设定            输出can
	u8      h2_circulating_pump_enable_pump;                //氢气循环泵CAN使能                输出can
	float	  h2_circulating_pump_actual_mass_flow;        		//  氢气循环泵质量流量      接收can
	
	float	h2_circulating_pump_actual_speed;        			//  氢气循环泵实际转速      接收can
	float	h2_circulating_pump_actual_current;        			//  氢气循环泵电流          接收can
	float	h2_circulating_pump_actual_voltage;        			//  氢气循环泵电压          接收can
	i16		h2_circulating_pump_actual_electronic_temperature;  //  氢气循环泵电机温度      接收can
	
	//pid控制
	float   h2_pressure_target_value;               //氢压 设定目标值
	float   h2_pressure_real_target_value;          //氢压 实际目标值
	float   h2_pressure_advance_current_value;      //氢压 提前量  实际值
	float   h2_pressure_advance_set_value;          //氢压 提前量  设定值  默认为0，一般设为5
	u32     h2_pressure_pid1_advance_time;          //pid1时间提前量      默认250ms
	u32     h2_pressure_pid2_advance_time;          //pid2时间提前量      默认1000ms
			
  u8      PID1_is_enble_pid;      //是否使能pid
	float   PID1_Kp;                  //比例系数    （实际值*1000）
	float   PID1_Ki;                  //积分系数    （实际值*1000）
	float   PID1_Kd;                  //微分系数    （实际值*1000）
	
	u8      PID2_is_enble_pid;      //是否使能pid
	float   PID2_Kp;                  //比例系数    （实际值*1000）
	float   PID2_Ki;                  //积分系数    （实际值*1000）
	float   PID2_Kd;                  //微分系数    （实际值*1000）
	
	u8		h2_pid_mode ;   						//pid算法控制模式，1表示使用pid1来控制，2表示使用pid2来控制
	
  //氢气尾排控制
	u8		h2_is_enable_outlet_valve;				//氢气尾排阀的自动控制的使能开关
	u32		h2_outlet_valve_open_time ;				//氢气尾排阀开启的时间
	u32		h2_outlet_valve_close_time ;			//氢气尾排阀关闭的时间
	
	float   h2_pressure_fluctuate_last_max;		    //氢压 波动  上次最大值
	float   h2_pressure_fluctuate_last_min;			//氢压 波动  上次最小值
	
	
};


//氢气数据信息//初始化
enum Error_code Hydrogen_detective_data_init(struct Hydrogen_detective_data *  p_Hydrogen_detective_data);
//氢气数据信息//数据解析
enum Error_code Hydrogen_detective_data_analysis(struct Modbus_Data_Buffer * p_modbus_receive_data_buffer, struct Hydrogen_detective_data *  p_Hydrogen_detective_data);
//氢气数据信息//数据封装
              
enum Error_code Hydrogen_detective_data_encapsulation( struct Hydrogen_detective_data *  p_Hydrogen_detective_data, struct Modbus_Data_Buffer * p_modbus_send_data_buffer);
//氢气数据信息//数据处理
enum Error_code Hydrogen_detective_data_execute(struct Hydrogen_detective_data *  p_Hydrogen_detective_data);
//氢气数据信息//清除更新状态
enum Error_code Hydrogen_detective_data_clear_updata(struct Hydrogen_detective_data *  p_Hydrogen_detective_data);




//2、空气数据

//2.1空气数据信息
struct Air_detective_data
{	

  u32   updata_event_time;    //数据更新时间
  u32		send_message_time_max;         //这个超时时间可以理解为 发送信息的时间频率 比如500ms发送一次
  u8    direction_data_transmission;   //数据传输方向
	u8		function_code;				//帧功能
  u8		data_length;				//数据字节长度
  
  	//输入
  float	air_pressure_pile_inlet;				//电堆入口风压							输入4-20mA
	float	air_pressure_pile_outlet;				//电堆出口风压							输入4-20mA
	float	air_pressure_pile_back;					//电堆出口背压							输入4-20mA
	float	air_temperature_pile_inlet;				//电堆入口风温							输入电阻值
	float	air_temperature_pile_outlet;			//电堆出口风温							输入电阻值
	float	air_temperature_pile_back;				//电堆出口背压温度						输入电阻值
	float	air_temperature_humidifier;				//加湿器入口风温						输入电阻值
	float	air_rate_of_flow;						//空气流量								输入0~5V

  	//输出
	u8		air_outlet_valve;						//空气气尾排阀，						输出0或1

	//空压机  can
	enum 	Working_Communication_Mode		air_compressor_working_communication_mode;		//空压机  can通信模式
	u8      air_compressor_enable;                  //空压机开关	                        输出can
	u32		air_compressor_speed_setpoint;		    //空压机转速，控制变频器，				输出can，


	//空气尾排控制
	u8		air_is_enable_outlet_valve;				//空气尾排阀的自动控制的使能开关
	u32		air_outlet_valve_open_time ;			//空气尾排阀开启的时间
	u32		air_outlet_valve_close_time ;			//空气尾排阀关闭的时间	
	
	
};


//空气数据信息//初始化
enum Error_code Air_detective_data_init(struct Air_detective_data *  p_Air_detective_data);
//空气数据信息//数据解析
enum Error_code Air_detective_data_analysis(struct Modbus_Data_Buffer * p_modbus_receive_data_buffer, struct Air_detective_data *  p_Air_detective_data);
//空气数据信息//数据封装
enum Error_code Air_detective_data_encapsulation( struct Air_detective_data *  p_Air_detective_data, struct Modbus_Data_Buffer * p_modbus_send_data_buffer);
//空气数据信息//数据处理
enum Error_code Air_detective_data_execute(struct Air_detective_data *  p_Air_detective_data);
//空气数据信息//清除更新状态
enum Error_code Air_detective_data_clear_updata(struct Air_detective_data *  p_Air_detective_data);




//3、电堆散热系统数据
//3.1电堆散热系统数据
struct Fell_temperature_data
{	

  u32   updata_event_time;    //数据更新时间
  u32		send_message_time_max;         //这个超时时间可以理解为 发送信息的时间频率 比如500ms发送一次
  u8    direction_data_transmission;   //数据传输方向
	u8		function_code;				//帧功能
  u8		data_length;				//数据字节长度
 
 	//输入 
	float	water_pressure_pile_inlet;				//电堆入口水压							输入4-20mA
	float	water_pressure_pile_outlet;				//电堆出口水压							输入4-20mA
	float	water_temperature_pile_inlet;			//电堆入口水温							输入电阻值
	float	water_temperature_pile_outlet;			//电堆出口水温							输入电阻值
	
		//输出
	float	water_pump_pwm_dutyfactor;				//水泵PWM占空比							输出pwm 0~24V 
	float	water_fan1_pwm_dutyfactor;				//风扇1PWM占空比						输出pwm 0~24V 
	float	water_fan2_pwm_dutyfactor;				//风扇2PWM占空比						输出pwm 0~24V 
	
	
	u8      water_PID_is_enble_pid;      //是否使能pid
	float   water_PID_Kp;                  //比例系数    （实际值*1000）
	float   water_PID_Ki;                  //积分系数    （实际值*1000）
	float   water_PID_Kd;                  //微分系数    （实际值*1000）
	
  float   water_temperature_target_value;         //电堆入口水温 目标值
	
};


//电堆散热系统数据//初始化
enum Error_code Fell_temperature_data_init(struct Fell_temperature_data *  p_Fell_temperature_data);
//电堆散热系统数据//数据解析
enum Error_code Fell_temperature_data_analysis(struct Modbus_Data_Buffer * p_modbus_receive_data_buffer, struct Fell_temperature_data *  p_Fell_temperature_data);
//电堆散热系统数据//数据封装
enum Error_code Fell_temperature_data_encapsulation( struct Fell_temperature_data *  p_Fell_temperature_data, struct Modbus_Data_Buffer * p_modbus_send_data_buffer);
//电堆散热系统数据//数据处理
enum Error_code Fell_temperature_data_execute(struct Fell_temperature_data *  p_Fell_temperature_data);
//电堆散热系统数据//清除更新状态
enum Error_code Fell_temperature_data_updata(struct Fell_temperature_data *  p_Fell_temperature_data);




//4、空压机散热系统数据
//4.1空压机散热系统数据
struct Air_compressor_temperature_data
{	

  u32   updata_event_time;    //数据更新时间
  u32		send_message_time_max;         //这个超时时间可以理解为 发送信息的时间频率 比如500ms发送一次
  u8    direction_data_transmission;   //数据传输方向
	u8		function_code;				//帧功能
  u8		data_length;				//数据字节长度
  
  	//输入
  float	water_pressure_compressor_outlet;		//空压机出口水压						输入4-20mA
  float	water_temperature_compressor_outlet;	//空压机出口水温						输入电阻值
  float	water_temperature_pump_outlet;			//三合一水泵出口水温					输入电阻值
  float	water_temperature_compressor_shell;		//空压机壳体温度						输入电阻值
  
  	//输出
	u8		water_pump_enable;						//水泵的使能							输出0或1
	float	water_fan_pwm_dutyfactor;				//风扇PWM占空比							输出pwm 0~24V 

	
};


//空压机散热系统数据//初始化
enum Error_code Air_compressor_temperature_data_init(struct Air_compressor_temperature_data *  p_Air_compressor_temperature_data);
//空压机散热系统数据//数据解析
enum Error_code Air_compressor_temperature_data_analysis(struct Modbus_Data_Buffer * p_modbus_receive_data_buffer, struct Air_compressor_temperature_data *  p_Air_compressor_temperature_data);
//空压机散热系统数据//数据封装
enum Error_code Air_compressor_temperature_data_encapsulation( struct Air_compressor_temperature_data *  p_Air_compressor_temperature_data, struct Modbus_Data_Buffer * p_modbus_send_data_buffer);
//空压机散热系统数据//数据处理
enum Error_code Air_compressor_temperature_data_execute(struct Air_compressor_temperature_data *  p_Air_compressor_temperature_data);
//空压机散热系统数据//清除更新状态
enum Error_code Air_compressor_temperature_data_updata(struct Air_compressor_temperature_data *  p_Air_compressor_temperature_data);





//5、电堆输出数据
//5.1电堆输出数据
struct Fell_output_data
{	

  u32   updata_event_time;    //数据更新时间
  u32		send_message_time_max;         //这个超时时间可以理解为 发送信息的时间频率 比如500ms发送一次
  u8    direction_data_transmission;   //数据传输方向
	u8		function_code;				//帧功能
  u8		data_length;				//数据字节长度
  
 //输入
	float	galvanic_pile_voltage;					//电堆的电压							输入0~5V
	float	galvanic_pile_electricity;				//电堆的电流							输入0~5V
	u8		fcu_start_enable;						//电堆的启动使能1：启动信号有效   0：启动信号无效	
	u8		fcu_stutter_stop_enable;				//电堆的急停使能1：急停信号有效   0：急停信号无效

	//输出
	u8		galvanic_pile_is_enble_output;			//电堆输出接触器						输出0或1
	u8		galvanic_pile_is_enble_load_resistance;	//电堆负载电阻接触器					输出0或1

	//巡检  can
	enum 	Working_Communication_Mode		itinerant_detective_working_communication_mode;	//巡检  can通信模式
	u8		itinerant_detective_working_statas;		//巡检运行状态
	u8		Single_battery_overvoltage_alarm;		//单体电池过压报警
	u8		Single_battery_undervoltage_alarm;		//单体电池欠压报警
	u8		Single_voltage_unbalance_alarm;			//单体电池不均报警
	float   electric1_mean_voltage;					//电堆1平均电压
	float 	electric1_single_chip_highest_voltage;	//电堆1单片最高电压
	u16		electric1_single_chip_highest_voltage_num;	//电堆1单片最高电压编号
	float 	electric1_single_chip_minimum_voltage;	//电堆1最低电压
	u16     electric1_single_chip_minimum_voltage_num; //电堆1最低电压编号
	float	itinerant_detective_total_voltage;		//巡检总电压				

	
};

//电堆输出数据//初始化
enum Error_code Fell_output_data_init(struct Fell_output_data *  p_Fell_output_data);
//电堆输出数据//数据解析
enum Error_code Fell_output_data_analysis(struct Modbus_Data_Buffer * p_modbus_receive_data_buffer, struct Fell_output_data *  p_Fell_output_data);
//电堆输出数据//数据封装
enum Error_code Fell_output_data_encapsulation( struct Fell_output_data *  p_Fell_output_data, struct Modbus_Data_Buffer * p_modbus_send_data_buffer);
//电堆输出数据//数据处理
enum Error_code Fell_output_data_execute(struct Fell_output_data *  p_Fell_output_data);
//电堆输出数据//清除更新状态
enum Error_code Fell_output_data_updata(struct Fell_output_data *  p_Fell_output_data);




//6、FCU运行状态信息
//6.1FCU运行状态信息
struct FCU_run_stata_data
{	

    u32   updata_event_time;    //数据更新时间
    u32		send_message_time_max;         //这个超时时间可以理解为 发送信息的时间频率 比如500ms发送一次
    u8    direction_data_transmission;   //数据传输方向
  	u8		function_code;				//帧功能
    u8		data_length;				//数据字节长度

    u8 FCU_control_mode;  //FCU控制模式
    u8 FCU_work_mode;    //FCU工作模式
    u8 FCU_alarm_mode;   //FCU异常告警
    u16 FCU_error_code;   //FUC错误码
    u8 FCU_erroring_control_mode; //出错瞬间,FCU的控制模式
    u8 FCU_system_run_mode;     //系统运行模式
    	
};


//FCU运行状态信息//初始化
enum Error_code FCU_run_stata_data_init(struct FCU_run_stata_data *  p_FCU_run_stata_data);
//FCU运行状态信息//数据解析
enum Error_code FCU_run_stata_data_analysis(struct Modbus_Data_Buffer * p_modbus_receive_data_buffer, struct FCU_run_stata_data *  p_FCU_run_stata_data);
//FCU运行状态信息//数据封装
enum Error_code FCU_run_stata_data_encapsulation( struct FCU_run_stata_data *  p_FCU_run_stata_data, struct Modbus_Data_Buffer * p_modbus_send_data_buffer);
//FCU运行状态信息//数据处理
enum Error_code FCU_run_stata_data_execute(struct FCU_run_stata_data *  p_FCU_run_stata_data);
//FCU运行状态信息//清除更新状态
enum Error_code FCU_run_stata_data_updata(struct FCU_run_stata_data *  p_FCU_run_stata_data);








/*

//7、FCU接收命令数据
//7.1FCU接收命令数据
struct FCU_receive_orde_data
{	

  //u32   updata_event_time;    //数据更新时间
  //u32		overtime_max;         //这个超时时间可以理解为 发送信息的时间频率 比如500ms发送一次
  u8    direction_data_transmission;   //数据传输方向
	u8		function_code;				//帧功能
  u8		data_length;				//数据字节长度
  u8    receive_orde_data[4];   //4个字节的数据
  
  
  u8    h2_inlet_valve;      //氢气进气阀
  u8		h2_is_enable_outlet_valve;				//氢气尾排阀的自动控制的使能开关
  u32		h2_outlet_valve_open_time ;				//氢气尾排阀开启的时间
	u32		h2_outlet_valve_close_time ;			//氢气尾排阀关闭的时间
  float	h2_proportional_valve_pwm_dutyfactor;	//比例阀PWM占空比，pid自动控制。		输出pwm 0~5V  频率>1000HZ
  u8		h2_circulating_pump_enble;				//氢气循环泵的IO使能					输出0或1
  u8      h2_circulating_pump_enable_pump;                //氢气循环泵使能                输出can
  float   h2_pressure_target_value;               //氢压 设定目标值
  float   h2_pressure_advance_set_value;          //氢压 提前量  设定值  默认为0，一般设为5
  u8      PID1_is_enble_pid;      //是否使能pid
	float   PID1_Kp;                  //比例系数    （实际值*1000）
	float   PID1_Ki;                  //积分系数    （实际值*1000）
	float   PID1_Kd;                  //微分系数    （实际值*1000）
	
	u8      PID2_is_enble_pid;      //是否使能pid
	float   PID2_Kp;                  //比例系数    （实际值*1000）
	float   PID2_Ki;                  //积分系数    （实际值*1000）
	float   PID2_Kd;                  //微分系数    （实际值*1000）	
	u8		h2_pid_mode ;   						//pid算法控制模式，1表示使用pid1来控制，2表示使用pid2来控制
	u8    air_compressor_enable;                  //空压机开关	                        输出can
	u32		air_compressor_speed_setpoint;		    //空压机转速，控制变频器，				输出can，
	u8		air_is_enable_outlet_valve;				//空气尾排阀的自动控制的使能开关
	u32		air_outlet_valve_open_time ;			//空气尾排阀开启的时间
	u32		air_outlet_valve_close_time ;			//空气尾排阀关闭的时间
	float	water_pump_pwm_dutyfactor;				//水泵PWM占空比							输出pwm 0~24V 
	float	water_fan1_pwm_dutyfactor;				//风扇1PWM占空比						输出pwm 0~24V 
	float	water_fan2_pwm_dutyfactor;				//风扇2PWM占空比						输出pwm 0~24V 
	
	u8      water_PID_is_enble_pid;      //是否使能pid
	float   water_PID_Kp;                  //比例系数    （实际值*1000）
	float   water_PID_Ki;                  //积分系数    （实际值*1000）
	float   water_PID_Kd;                  //微分系数    （实际值*1000）
	
  float   water_temperature_target_value;         //电堆入口水温 目标值
  
  u8		compressor_water_pump_enable;						//水泵的使能							输出0或1
	float	compressor_water_fan_pwm_dutyfactor;				//风扇PWM占空比							输出pwm 0~24V 
	
	u8		fcu_start_enable;						//电堆的启动使能1：启动信号有效   0：启动信号无效	
	u8		fcu_stutter_stop_enable;				//电堆的急停使能1：急停信号有效   0：急停信号无效
	u8		galvanic_pile_is_enble_output;			//电堆输出接触器						输出0或1
	u8		galvanic_pile_is_enble_load_resistance;	//电堆负载电阻接触器					输出0或1
	u8    FCU_system_run_mode;     //系统运行模式

	
};



//FCU接收命令数据//初始化
enum Error_code FCU_receive_orde_data_init(struct FCU_receive_orde_data *  p_FCU_receive_orde_data);
//FCU接收命令数据//数据解析
enum Error_code FCU_receive_orde_data_analysis(struct Modbus_Data_Buffer * p_modbus_receive_data_buffer, struct FCU_receive_orde_data *  p_FCU_receive_orde_data);
//FCU接收命令数据//数据封装
enum Error_code FCU_receive_orde_data_encapsulation( struct FCU_receive_orde_data *  p_FCU_receive_orde_data, struct Modbus_Data_Buffer * p_modbus_send_data_buffer);
//FCU接收命令数据//数据处理
enum Error_code FCU_receive_orde_data_execute(struct FCU_receive_orde_data *  p_FCU_receive_orde_data);
//FCU接收命令数据//清除更新状态
enum Error_code FCU_receive_orde_data_updata(struct FCU_receive_orde_data *  p_FCU_receive_orde_data);

*/


//8、FCU总管理状态
//8.1FCU总管理状态
struct FCU_modbus_tatal_manager_data
{	

   	enum ISlock     islock;      //数据保护锁
    
    struct Hydrogen_detective_data   hydrogen_detective_data;
    struct Air_detective_data   air_detective_data;
    struct Fell_temperature_data  fell_temperature_data;
    struct Air_compressor_temperature_data  air_compressor_temperature_data;
    struct Fell_output_data   fell_output_data;
    struct FCU_run_stata_data  fcu_run_stata_data;
  //  struct FCU_receive_orde_data  fcu_receive_orde_data;
    
    
	
};


//FCU总管理状态//初始化
enum Error_code FCU_modbus_tatal_manager_data_init(struct FCU_modbus_tatal_manager_data *  p_FCU_modbus_tatal_manager_data);
//FCU总管理状态//数据解析
enum Error_code FCU_modbus_tatal_manager_data_analysis(struct Modbus_Data_Buffer * p_modbus_receive_data_buffer,struct FCU_Data_Buffer * p_FCU_Data_Buffer,struct Control_Policy_Total_Manager * p_Control_Policy_Total_Manager);
//FCU总管理状态//数据封装
enum Error_code FCU_modbus_tatal_manager_data_encapsulation( struct FCU_modbus_tatal_manager_data *  p_FCU_modbus_tatal_manager_data, struct Modbus_Data_Buffer * p_modbus_send_data_buffer);
//FCU总管理状态//数据处理
enum Error_code FCU_modbus_tatal_manager_data_data_execute(struct FCU_modbus_tatal_manager_data *  p_FCU_modbus_tatal_manager_data);
//FCU总管理状态//清除更新状态
enum Error_code FCU_modbus_tatal_manager_data_updata(struct FCU_modbus_tatal_manager_data *  p_FCU_modbus_tatal_manager_data);






//通过通信  232 modbus格式更新串口通信数据  
enum Error_code  p_FCU_modbus_tatal_manager_data_updata_by_232_modbus_communication();

//接收数据根据通信协议解析数据
enum Error_code modbus_232_receive_to_databuff(struct Modbus_Data_Buffer * p_modbus_receive_data_buffer,struct FCU_Data_Buffer * p_FCU_Data_Buffer,struct Control_Policy_Total_Manager *p_Control_Policy_Total_Manager);










void float_convert_four_byte(float *f,unsigned char *a,unsigned char *b,unsigned char *c,unsigned char *d);

float four_byte_convert_float(unsigned char a,unsigned char b,unsigned char c,unsigned char d);  






#endif




