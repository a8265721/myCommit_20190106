#ifndef _DATA_BUFFER_H
#define _DATA_BUFFER_H


#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */


#include "error_system.h"                         
#include "custom_math.h"                               
#include "pid.h"
#include "can_communication_protocol2.h"          


#define H2_PRESSURE_ADVANCE_SET_VALUE           5
#define H2_PRESSURE_PID1_ADVANCE_TIME           250
#define H2_PRESSURE_PID2_ADVANCE_TIME           200

#define H2_PRESSURE_ALARM_VALUE_95          95

#define H2_PRESSURE_SET_VALUE_50            50
#define H2_PRESSURE_SET_VALUE_55            55
#define H2_PRESSURE_SET_VALUE_60            60
#define H2_PRESSURE_SET_VALUE_65            65
#define H2_PRESSURE_SET_VALUE_70            70
#define H2_PRESSURE_SET_VALUE_75            75

#define H2_CIRCULATING_PUMP_SPEED_SETPOINT_1000         1000
#define H2_CIRCULATING_PUMP_SPEED_SETPOINT_1500         1500
#define H2_CIRCULATING_PUMP_SPEED_SETPOINT_2000         2000
#define H2_CIRCULATING_PUMP_SPEED_SETPOINT_3000         3000

#define AIR_COMPRESSOR_SPEED_SETPOINT_20000            20000
#define AIR_COMPRESSOR_SPEED_SETPOINT_35000            35000
#define AIR_COMPRESSOR_SPEED_SETPOINT_45000            45000
#define AIR_COMPRESSOR_SPEED_SETPOINT_55000            55000
#define AIR_COMPRESSOR_SPEED_SETPOINT_60000            60000
#define AIR_COMPRESSOR_SPEED_SETPOINT_65000            65000
#define AIR_COMPRESSOR_SPEED_SETPOINT_70000            70000
#define AIR_COMPRESSOR_SPEED_SETPOINT_73000            73000
#define AIR_COMPRESSOR_SPEED_SETPOINT_75000            75000

#define H2_OUTLET_VALVE_OPEN_TIME_500         500
#define H2_OUTLET_VALVE_OPEN_TIME_800         800
#define H2_OUTLET_VALVE_OPEN_TIME_1000       1000
#define H2_OUTLET_VALVE_OPEN_TIME_1500       1500
#define H2_OUTLET_VALVE_OPEN_TIME_2000       2000

#define H2_OUTLET_VALVE_CLOSE_TIME_1000      1000
#define H2_OUTLET_VALVE_CLOSE_TIME_4000      4000
#define H2_OUTLET_VALVE_CLOSE_TIME_5000      5000
#define H2_OUTLET_VALVE_CLOSE_TIME_6000      6000

#define AIR_OUTLET_VALVE_OPEN_TIME_500        500
#define AIR_OUTLET_VALVE_CLOSE_TIME_8000     8000


#define  PID1_KP  0.3
#define  PID1_KI  0.00001
#define  PID1_KD  170

#define  PID2_KP  0.3
#define  PID2_KI  0.00001
#define  PID2_KD  100  

#define  PID_COMPRESSOR_KP  0.5
#define  PID_COMPRESSOR_KI  0.00001
#define  PID_COMPRESSOR_KD  5

#define  PID_WATER_KP  100
#define  PID_WATER_KI  0
#define  PID_WATER_KD  1000

//氢气浓度过高最大值
#define  H2_CONCENTRATION_OVER_MAX  1
//通信状态
typedef enum Working_Communication_Status
{
	working_communication_outage = 0,		//通信中断
	working_communication_normal = 1,						//正常
}Working_Communication_Status;




                                         

//氢气数据层
typedef struct H2_Data_Buffer
{
	//输入
	float	h2_pressure_proportional_valve_front;	//比例阀前氢压，fcu系统的H2供气口，		输入4-20mA
	float	h2_pressure_proportional_valve_rear;	//比例阀后氢压，                		输入4-20mA
	float	h2_pressure_pile_inlet;	                //入堆氢压，是电堆的H2入口          	输入4-20mA	
	float	h2_pressure_pile_inlet1;	            //入堆氢压，是电堆的H2入口          	输入4-20mA	
	float	h2_pressure_pile_inlet2;	            //入堆氢压，是电堆的H2入口          	输入4-20mA	
	float	h2_pressure_pile_outlet1;	            //出堆氢压，是电堆的H2出口          	输入4-20mA	
	float	h2_pressure_pile_outlet2;	            //出堆氢压，是电堆的H2出口          	输入4-20mA	
	float	h2_pressure_tail_outlet;				//氢气尾排的压力,也是电堆H2出口压力		输入4-20mA
	float	h2_concentration;						//氢气浓度								输入pwm，采集周期和占空比
	float	h2_humidity;					 		//氢气湿度

	float   h2_temperature_tail_outlet;             //电堆尾排氢气温度                      输入ntc电阻	
	float   h2_temperature_pile_inlet;              //电堆入口氢气温度                      输入ntc电阻

	//输出
	u8		h2_inlet_valve;							//氢气进气阀，							输出0或1
	u8		h2_outlet_valve;						//氢气尾排阀，							输出0或1
	float	h2_proportional_valve_pwm_dutyfactor;	//比例阀PWM占空比，pid自动控制。		输出pwm 0~5V  频率>1000HZ
	u8		h2_circulating_pump_enble;				//氢气循环泵的IO使能					输出0或1

	//氢气循环泵转速设定  百分比	二级告警之后，降速使用的
	float	h2_circulating_pump_speed_setpoint_percent;             //氢气循环泵转速设定   百分比
	//氢气循环泵  can通信
	enum 	Working_Communication_Status		h2_circulating_pump_working_communication_status;	//氢气循环泵  can通信状态
	float   h2_circulating_pump_mass_flow_setpoint;         //氢气循环泵流量设定            输出can
	u16     h2_circulating_pump_speed_setpoint;             //氢气循环泵转速设定            输出can
	u8      h2_circulating_pump_enable_pump;                //氢气循环泵使能                输出can
	u8      h2_circulating_pump_enable_mass_flow_govemor;   //氢气循环泵流量监控使能        输出can

	float	h2_circulating_pump_actual_mass_flow;        		//  氢气循环泵质量流量      接收can
	float	h2_circulating_pump_actual_speed;        			//  氢气循环泵实际转速      接收can
	float	h2_circulating_pump_actual_current;        			//  氢气循环泵电流          接收can
	float	h2_circulating_pump_actual_voltage;        			//  氢气循环泵电压          接收can
	i16		h2_circulating_pump_actual_electronic_temperature;  //  氢气循环泵电机温度      接收can
	i16		h2_circulating_pump_actual_air_temperature;        	//  氢气循环泵气体温度      接收can
	u8	    h2_circulating_pump_status_diagnose_word;        	//  氢气循环泵状态诊断字节  接收can

	//pid控制
	float   h2_pressure_target_value;               //氢压 设定目标值
	float   h2_pressure_real_target_value;          //氢压 实际目标值
	float   h2_pressure_advance_current_value;      //氢压 提前量  实际值
	float   h2_pressure_advance_set_value;          //氢压 提前量  设定值  默认为0，一般设为5
	u32     h2_pressure_pid1_advance_time;          //pid1时间提前量      默认250ms
	u32     h2_pressure_pid2_advance_time;          //pid2时间提前量      默认1000ms		
	PID		h2_proportional_valve_pid1;				//比例阀的pid1
	PID		h2_proportional_valve_pid2;				//比例阀的pid2
	u8		h2_pid_mode ;   						//pid算法控制模式，1表示使用pid1来控制，2表示使用pid2来控制
	//氢气尾排控制
	u8		h2_is_enable_outlet_valve;				//氢气尾排阀的自动控制的使能开关
	u32		h2_outlet_valve_current_time ;	    	//氢气尾排阀当前的时间
	u32		h2_outlet_valve_open_time ;				//氢气尾排阀开启的时间
	u32		h2_outlet_valve_close_time ;			//氢气尾排阀关闭的时间
	//氢压波动
	u8      h2_pressure_fluctuate_reset;            //氢压 波动  重置
	float   h2_pressure_fluctuate_current_max;      //氢压 波动  当前最大值
	float   h2_pressure_fluctuate_current_min;      //氢压 波动  当前最小值
	float   h2_pressure_fluctuate_last_max;		    //氢压 波动  上次最大值
	float   h2_pressure_fluctuate_last_min;			//氢压 波动  上次最小值
}H2_Data_Buffer;


//空气数据层
typedef struct Air_Data_Buffer
{
	u32		air_temperature_pile_inlet_duration_time;//入堆温度超过75度的持续时间（超过20s，则报一级故障）
	//输入
	float	air_pressure_pile_inlet;				//电堆入口风压							输入4-20mA
	float	air_pressure_pile_outlet;				//电堆出口风压							输入4-20mA
	float	air_pressure_pile_back;					//电堆出口背压							输入4-20mA
	float	air_temperature_pile_inlet;				//电堆入口风温							输入电阻值
	float	air_temperature_pile_outlet;			//电堆出口风温							输入电阻值
	float	air_temperature_pile_back;				//电堆出口背压温度						输入电阻值
	float	air_temperature_humidifier;				//加湿器入口风温						输入电阻值
	float	air_rate_of_flow;						//空气流量								输入0~5V
	float	air_humidity;							//空气湿度                              0-70000   
	
    float	air_temperature_humidifier_front;        //加湿器前空气温度                  	输入电阻值    

	//输出
	u8		air_outlet_valve;						//空气气尾排阀，						输出0或1


	u32		air_compressor_speed_setpoint_increment;//空压机转速，控制变频器，增量
	//空压机  can
	enum 	Working_Communication_Status		air_compressor_working_communication_status;		//空压机  can通信状态
	u8      air_compressor_enable;                  //空压机开关	                        输出can
	u32		air_compressor_speed_setpoint;		    //空压机转速，控制变频器，				输出can，

	u8		air_compressor_input_electricity;		//空压机变频器输入电流
	u16		air_compressor_input_voltage;			//空压机变频器输入电压
	u16		air_compressor_output_power;			//空压机输出功率
	i16		air_compressor_motor_temperature;       //空压机电机温度
	i16		air_compressor_converter_temperature;   //空压机控制器温度
	i16		air_compressor_inside_temperature;		//空压机内部温度
	u8		air_compressor_state;					//空压机状态
	u16		air_compressor_fault_code;				//空压机故障码
	u8		air_compressor_fault_level;				//空压机故障等级
	u32		air_compressor_act_speed;				//空压机实际转速
	
	
	//20181112，按照冯工的要求，在此增加，根据空气流量来控制空压机的转速，目前使用pid调节。
	PID     air_compressor_speed_pid;               //空压机的pid控制
	float   air_rate_of_flow_target;                //空气流量的目标值

	//空气尾排控制
	u8		air_is_enable_outlet_valve;				//空气尾排阀的自动控制的使能开关
	u32		air_outlet_valve_current_time ;	    	//空气尾排阀当前的时间
	u32		air_outlet_valve_open_time ;			//空气尾排阀开启的时间
	u32		air_outlet_valve_close_time ;			//空气尾排阀关闭的时间	
}Air_Data_Buffer;


//电堆散热系统 数据层
typedef struct Water_For_Pile_Data_Buffer
{
	//输入
	float	water_pressure_pile_inlet1;				//电堆入口水压							输入4-20mA
	float	water_pressure_pile_outlet1;				//电堆出口水压							输入4-20mA
	float	water_temperature_pile_inlet1;			//电堆入口水温							输入电阻值
	float	water_temperature_pile_outlet1;			//电堆出口水温							输入电阻值

	float	water_pressure_pile_inlet2;				//电堆入口水压							输入4-20mA
	float	water_pressure_pile_outlet2;				//电堆出口水压							输入4-20mA
	float	water_temperature_pile_inlet2;			//电堆入口水温							输入电阻值
	float	water_temperature_pile_outlet2;			//电堆出口水温							输入电阻值

	u8		water_pump_feedback1;					//水泵的反馈信号	1：正常           0：异常	
	u8		water_pump_feedback2;					//水泵的反馈信号	1：正常           0：异常
	u8		water_fan_feedback1;					//风扇1的反馈信号	1：正常           0：异常
	u8		water_fan_feedback2;					//风扇2的反馈信号	1：正常           0：异常
	u8		water_position;							//散热水箱的液位	1：检测到液体     0：没有液体			

	//输出
	float	water_pump_pwm_dutyfactor1;				//水泵1PWM占空比						输出pwm 0~24V 
	float	water_pump_pwm_dutyfactor2;				//水泵2PWM占空比						输出pwm 0~24V 
	float	water_fan_pwm_dutyfactor1;				//风扇1PWM占空比						输出pwm 0~24V 
	float	water_fan_pwm_dutyfactor2;				//风扇2PWM占空比						输出pwm 0~24V 
	
	//控制 电堆水温和风扇的pid控制
	PID     water_temperature_fan_pid1;              //水温和风扇的pid控制
	PID     water_temperature_fan_pid2;              //水温和风扇的pid控制
	float   water_temperature_target_value1;         //电堆入口水温 目标值
	float   water_temperature_target_value2;         //电堆入口水温 目标值

}Water_For_Pile_Data_Buffer;


//三合一散热系统 数据层（空压机，变频器，中冷器）中冷器是在空气入堆前降低风温
typedef struct Water_For_Compressor_Data_Buffer
{
	//输入
	float	water_pressure_compressor_outlet;		//空压机出口水压						输入4-20mA
	float	water_pressure_frequency_outlet;		//变频器出口水压						输入4-20mA
	float	water_pressure_intercooler_outlet;		//中冷器出口水压						输入4-20mA
	float	water_pressure_pump_outlet;		    	//三合一水泵出口水压			    	输入4-20mA
	float	water_temperature_compressor_outlet;	//空压机出口水温						输入电阻值
	float	water_temperature_compressor_shell;		//空压机壳体温度						输入电阻值
	float	water_temperature_frequency_outlet;		//变频器出口水温						输入电阻值
	float	water_temperature_intercooler_outlet;	//中冷器出口水温						输入电阻值
	float	water_temperature_pump_outlet;			//三合一水泵出口水温					输入电阻值
		
	u8		water_fan_feedback;						//风扇的反馈信号	1：正常           0：异常
	u8		water_position;							//散热水箱的液位	1：检测到液体     0：没有液体


	//输出
	u8		water_pump_enable;						//水泵的使能							输出0或1
	float	water_pump_pwm_dutyfactor;				//水泵PWM占空比							输出pwm 0~24V 
	float	water_fan_pwm_dutyfactor;				//风扇PWM占空比							输出pwm 0~24V 
	
	//控制 电堆水温和风扇的pid控制
	PID     water_temperature_fan_pid;              //水温和风扇的pid控制
	float   water_temperature_target_value;         //电堆入口水温 目标值
	
}Water_For_Compressor_Data_Buffer;


//电堆电压开路限定值  230V   双堆130*2片（实际在260V左右）
#define  GALVANIC_PILE_OPEN_CIRCUIT_VOLTAGE		230.0f  

//巡检单片电压开路限定值  150V
#define  ITINERANT_DETECTIVE_OPEN_CIRCUIT_SINGLE_VOLTAGE		0.85f

//电堆发电的数据层
typedef struct Galvanic_Pile_Data_Buffer
{
	//输入
	float	galvanic_pile_voltage;					//电堆的电压							输入0~5V
	float	galvanic_pile_electricity;				//电堆的电流							输入0~5V
	u8		fcu_start_enable;						//电堆的启动使能1：启动信号有效   0：启动信号无效	
	u8		fcu_stutter_stop_enable;				//电堆的急停使能1：急停信号有效   0：急停信号无效
	u8		fcu_reset_enable;						//电堆的复位使能1：启动信号有效   0：启动信号无效	

	//输出
	u8		galvanic_pile_is_enble_output;			//电堆输出接触器						输出0或1
	u8		galvanic_pile_is_enble_load_resistance;	//电堆负载电阻接触器					输出0或1

	//巡检  can
	enum 	Working_Communication_Status		itinerant_detective_working_communication_status;	//巡检  can通信模式
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
	
	//巡检  can
	enum 	Working_Communication_Status		itinerant_detective_working_communication_status2;	//巡检  can通信模式
	u8		itinerant_detective_working_statas2;		//巡检运行状态
	u8		Single_battery_overvoltage_alarm2;		//单体电池过压报警
	u8		Single_battery_undervoltage_alarm2;		//单体电池欠压报警
	u8		Single_voltage_unbalance_alarm2;			//单体电池不均报警
	float   electric1_mean_voltage2;					//电堆1平均电压
	float 	electric1_single_chip_highest_voltage2;	//电堆1单片最高电压
	u16		electric1_single_chip_highest_voltage_num2;	//电堆1单片最高电压编号
	float 	electric1_single_chip_minimum_voltage2;	//电堆1最低电压
	u16     electric1_single_chip_minimum_voltage_num2; //电堆1最低电压编号
	float	itinerant_detective_total_voltage2;		//巡检总电压					

    //绝缘模块 can通信数据
	enum 	Working_Communication_Status		insulation_monitor_working_communication_status;	//绝缘模块  can通信模式    
	u8    insulation_monitor_fault_level;           //绝缘模块故障等级
	u8    insulation_monitor_error_code	;			//绝缘模块故障码
	u16   insulation_resistance_value;              //绝缘电阻值
	u16   insulation_battery_voltage;               //绝缘模块电池电压

}Galvanic_Pile_Data_Buffer;



//fcu汇总 数据层
typedef struct FCU_Data_Buffer
{                                 
	enum ISlock                                  islock;      //数据保护锁

	struct H2_Data_Buffer						h2_data_buffer;							//氢气数据层
	struct Air_Data_Buffer						air_data_buffer;						//空气数据层
	struct Water_For_Pile_Data_Buffer			water_for_pile_data_buffer;				//电堆散热系统 数据层
	struct Water_For_Compressor_Data_Buffer		water_for_compressor_data_bufferr;		//三合一散热系统 数据层
	struct Galvanic_Pile_Data_Buffer			galvanic_pile_data_buffer;				//电堆发电的数据层
}FCU_Data_Buffer;


extern struct FCU_Data_Buffer		fcu_data_buffer   ;

//fcu数据缓存数据初始化
void FCU_data_buffer_init(void);

//通过通信  更新数据  空压机和氢气循环泵
void FCU_data_buffer_updata_by_communication(void);


#endif

