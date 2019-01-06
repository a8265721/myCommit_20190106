/*
error_system 本模块是错误码的处理
用法：其他模块直接包含本模块，然后作为函数的返回值。
上层通过分析错误码来判断函数的执行情况。
*/ 
//-----------------------------------------------------------------------------------------------

#ifndef __ERROR_SYSTEM_H       
#define __ERROR_SYSTEM_H	              
//#include "sys.h"
#include "stdlib.h"                    
#include "stdio.h"          
                                                        

/* exact-width signed integer types */
typedef   signed char		int8_t;                 
typedef   signed short      int16_t;
typedef   signed long		int32_t;


/* exact-width unsigned integer types */
typedef unsigned char		uint8_t;
typedef unsigned short		uint16_t;
typedef unsigned long		uint32_t;

/* exact-width signed integer types */
typedef   signed char		int8_T;
typedef   signed short      int16_T;
typedef   signed long		int32_T;


/* exact-width unsigned integer types */
typedef unsigned char		uint8_T;
typedef unsigned short		uint16_T;
typedef unsigned long		uint32_T;

typedef int32_t		i32;
typedef int16_t		i16;
typedef int8_t		i8;

typedef uint32_t	u32;
typedef uint16_t	u16;
typedef uint8_t		u8;

typedef enum ISlock
{
	unlock = 0,
	lock = 1,
}ISlock;


#define ERROR_STRING_LENGTH		256		//错误码的文本说明字符串长度


enum IsAbled
{
	Enabled =1,
	Unabled =0,
};


//错误码的枚举，如果需要新增错误码，直接在下路的枚举中追加
enum Error_code
{
	Succeed = 0,					//成功

	//普通错误
	Failed = 1,						//失败
	Partial_success = 2, 			//部分成功
	Warning = 3,					//警告
	Error = 4,						//错误

	//后期优化错误告警时，会使用
	NoData = 5,						//没有数据（比如说查询链表或者缓存，结果发现没有需要处理的数据）


	//指针和内存错误，和参数的数据不符合
	Pointer_is_null = 100, 			//空指针
	Parameter_error = 101,			//参数错误
	Pointer_malloc_fail = 103,		//指针手动分配内存错误


	//can底层模块
	CAN_length_error = 201,		//can长度错误
	CAN_out_synchronization = 202,	//can不同步
	CAN_receive_flag_error = 203,	//接受标志位错误


	//can通信模块
	CAN_send_overtime = 301,		//CAN发送消息超时
	CAN_receive_overtime = 302,	//CAN接受消息超时
	CAN_receive_nothing = 303,		//接收事件处理成功，但是没有接受到消息，//warning
	CAN_data_analysis_id_error = 310,//数据解析，id不匹配
	CAN_data_analysis_data_error = 311,//数据解析，数据不匹配
	CAN_data_invalid_data_error =312,  // 无效数据


	//MODBUS通信模块
	MODBUS_send_overtime = 401,		//MODBUS发送消息超时
	MODBUS_receive_overtime = 402,	//MODBUS接受消息超时
	MODBUS_receive_nothing = 403,		//接收事件处理成功，但是没有接受到消息，//warning
	MODBUS_data_analysis_id_error = 410,//数据解析，id不匹配
	MODBUS_data_analysis_data_error = 411,//数据解析，数据不匹配
	MODBUS_data_invalid_data_error =412,  // 无效数据
	MODBUS_receive_wait_for_reply =413,  // 等待答复

	//ad转化
	ATDX_conversion_number_error = 501,		//ad采集的通道错误







	//fcu系统错误码
	//	Check1_overtime_error1,		//自检1，超时（一级故障）                                            


	//氢气数据
	H2_pressure_proportional_valve_front_over_error1			 = 0x1101,//4353		//比例阀前氢压	过压（一级故障）
	H2_pressure_proportional_valve_front_over_error3			 = 0x1103,//4355		//比例阀前氢压	过压（3级故障）
	H2_pressure_proportional_valve_front_under_error1			 = 0x1104,//4356		//比例阀前氢压	欠压（一级故障）
	H2_pressure_proportional_valve_front_under_error3			 = 0x1106,//4358		//比例阀前氢压	欠压（3级故障）
	H2_pressure_proportional_valve_front_atd_error1				 = 0x110a,//4362		//比例阀前氢压	ad采样异常（一级故障）

	H2_pressure_proportional_valve_rear_over_error1				 = 0x1201,//4609		//比例阀后氢压  过压（一级故障）
	H2_pressure_proportional_valve_rear_over_error3				 = 0x1203,//4611		//比例阀后氢压  过压（3级故障）
	H2_pressure_proportional_valve_rear_under_error1			 = 0x1204,//4612		//比例阀后氢压  欠压（一级故障）
	H2_pressure_proportional_valve_rear_under_error3			 = 0x1206,//4614		//比例阀后氢压  欠压（3级故障）
	H2_pressure_proportional_valve_rear_atd_error1				 = 0x120a,//4618		//比例阀后氢压	ad采样异常（一级故障）
	H2_pressure_proportional_valve_rear_unstable_error1			 = 0x120b,//4619		//比例阀后氢压	压力不稳（一级故障）
	H2_pressure_no_fluctuations_error1							 = 0x120c,//4620		//氢气压力没有波动，可能是尾排阀故障（一级故障）

	H2_pressure_pile_inlet_over_error1							 = 0x1301,//4865		//入堆氢压  过压（一级故障）
	H2_pressure_pile_inlet_over_error3							 = 0x1303,//4867		//入堆氢压  过压（3级故障）
	H2_pressure_pile_inlet_under_error1							 = 0x1304,//4868		//入堆氢压  欠压（一级故障）
	H2_pressure_pile_inlet_under_error3							 = 0x1306,//4870		//入堆氢压  欠压（3级故障）
	H2_pressure_pile_inlet_atd_error1							 = 0x130a,//4874		//入堆氢压	ad采样异常（一级故障）
	H2_pressure_pile_inlet_unstable_error1						 = 0x130b,//4875		//入堆氢压	压力不稳（一级故障）
	H2_pressure_pile_inlet_no_follow_error3						 = 0x130c,//4876		//入堆氢压  没有跟随比例阀后氢压（3级故障）

	H2_pressure_pile_outlet_atd_error1							 = 0x140a,//5130		//出堆氢压	ad采样异常（一级故障）
	H2_pressure_pile_outlet_unstable_error1						 = 0x140b,//5131		//出堆氢压	压力不稳（一级故障）
	H2_pressure_pile_outlet_no_follow_error3					 = 0x140c,//5132		//出堆氢压	没有跟随比例阀后氢压（3级故障）

	H2_pressure_tail_outlet_atd_error1							 = 0x150a,//5386		//氢气尾排的压力	ad采样异常（一级故障）
	H2_pressure_tail_outlet_unstable_error1						 = 0x150b,//5387		//尾排氢压	压力不稳（一级故障）
	H2_pressure_tail_outlet_no_follow_error3					 = 0x150c,//5388		//尾排氢压	没有跟随比例阀后氢压（3级故障）
	//	H2_pressure_tail_outlet_under_error3 ,		//尾堆氢压  欠压（3级故障）

	H2_proportional_valve_statas_error1							 = 0x1601,//5633		//比例阀状态故障（一级故障）

	H2_outlet_valve_control_error1								 = 0x1701,//5889		//尾排阀控制故障（一级故障）
	
	//氢气浓度检测的ad采样    
	H2_concentration_over_error1						       	 = 0x1801,//6145		//氢气浓度检测  浓度过高（一级故障）
    H2_concentration_atd_error1                                  = 0x180a,//6154		//氢气浓度检测	ad采样异常（一级故障）
    
    //氢气入堆温度
	H2_temperature_pile_inlet_over_error1						 = 0x1901,//6401		//入堆氢温  过温（一级故障）
	H2_temperature_pile_inlet_over_error3						 = 0x1903,//6403		//入堆氢温  过温（3级故障）
	H2_temperature_pile_inlet_under_error1						 = 0x1904,//6404		//入堆氢温	欠温（一级故障）
	H2_temperature_pile_inlet_under_error3						 = 0x1906,//6406		//入堆氢温	欠温（3级故障）
	H2_temperature_pile_inlet_atd_error1						 = 0x190a,//6410		//电堆入口氢温	ad采样异常（一级故障）
	 
	//氢气循环泵
	H2_circulating_pump_communication_error1					 = 0x1a0a,//6666		//氢气循环泵  can通信故障（一级故障）
	H2_circulating_pump_low_voltage_power_error1				 = 0x1a0b,//6667		//氢气循环泵的  24V低压电源故障。（一级故障）
	H2_circulating_pump_working_statas_error1					 = 0x1a0c,//6668		//氢气循环泵工作状态故障（一级故障）
	H2_circulating_pump_actual_speed_error1						 = 0x1a0d,//6669		//氢气循环泵 实际转速故障（一级故障）
	H2_circulating_pump_temperature_over_error1					 = 0x1a11,//6673		//氢气循环泵 温度过高（一级故障）
	H2_circulating_pump_temperature_over_error2					 = 0x1a12,//6674		//氢气循环泵 温度过高（2级故障）//氢气循环泵 减速50%
	H2_circulating_pump_temperature_under_error1				 = 0x1a14,//6676		//氢气循环泵 温度过低（一级故障）
	H2_circulating_pump_temperature_under_error3				 = 0x1a16,//6678		//氢气循环泵 温度过低（3级故障）






	//空气数据
	Air_pressure_pile_inlet_over_error1							 = 0x2101,//8449		//入堆风压  过压（一级故障）
	Air_pressure_pile_inlet_over_error3							 = 0x2103,//8451		//入堆风压  过压（3级故障）
	Air_pressure_pile_inlet_under_error1						 = 0x2104,//8452		//入堆风压	欠压（一级故障）
	Air_pressure_pile_inlet_under_error2						 = 0x2105,//8453		//入堆风压	欠压（2级故障）	//空压机 加速10000
	Air_pressure_pile_inlet_atd_error1							 = 0x210a,//8458		//电堆入口风压	ad采样异常（一级故障）

	Air_pressure_pile_outlet_over_error3						 = 0x2203,//8707		//出堆风压  过压（3级故障）
	Air_pressure_pile_outlet_atd_error1 						 = 0x220a,//8714		//电堆出口风压	ad采样异常（一级故障）

	Air_pressure_pile_back_over_error3							 = 0x2303,//8963		//出口背压  过压（3级故障）
	Air_pressure_pile_back_atd_error1							 = 0x230a,//8970		//电堆出口背压	ad采样异常（一级故障）	

	Air_temperature_pile_inlet_over_error1						 = 0x2401,//9217		//入堆风温  过温（一级故障）
	Air_temperature_pile_inlet_over_error3						 = 0x2403,//9219		//入堆风温  过温（3级故障）
	Air_temperature_pile_inlet_under_error1						 = 0x2404,//9220		//入堆风温	欠温（一级故障）
	Air_temperature_pile_inlet_under_error3						 = 0x2406,//9222		//入堆风温	欠温（3级故障）
	Air_temperature_pile_inlet_atd_error1						 = 0x240a,//9226		//电堆入口风温	ad采样异常（一级故障）

	Air_temperature_pile_outlet_over_error3						 = 0x2503,//9475		//出堆风温  过温（3级故障）
	Air_temperature_pile_outlet_atd_error1						 = 0x250a,//9482		//电堆出口风温	ad采样异常（一级故障）

	Air_temperature_pile_back_over_error3						 = 0x2603,//9731		//出口背温  过温（3级故障）
	Air_temperature_pile_back_atd_error1						 = 0x260a,//9738		//电堆出口背压温度	ad采样异常（一级故障）

	Air_rate_of_flow_under_error1								 = 0x2704,//9988		//空气流量过低（一级故障）
	Air_rate_of_flow_atd_error1 								 = 0x270a,//9994		//空气流量	ad采样异常（一级故障）
    
    //加湿器前的空气温度	
    Air_temperature_humidifier_front_over_error1				 = 0x2801,//10241		//加湿器前的空气温度    过温（一级故障）
	Air_temperature_humidifier_front_over_error3				 = 0x2803,//10243		//加湿器前的空气温度    过温（3级故障）
	Air_temperature_humidifier_front_under_error1				 = 0x2804,//10244		//加湿器前的空气温度    欠温（一级故障）
	Air_temperature_humidifier_front_under_error3				 = 0x2806,//10246		//加湿器前的空气温度	欠温（3级故障）
	Air_temperature_humidifier_front_atd_error1					 = 0x280a,//10250		//加湿器前的空气温度	ad采样异常（一级故障）
	
	//空压机
	Air_compressor_communication_error1							 = 0x2a0a,//10762		//空压机  can通信故障（一级故障）
	Air_compressor_working_statas_error1						 = 0x2a0b,//10763		//空压机工作状态故障（一级故障）
	Air_compressor_act_speed_error1								 = 0x2a0c,//10764		//空压机 实际转速故障（一级故障）
    Air_compressor_input_voltage_power_error1                    = 0x2a0d,//10765       //空压机 输入电压故障（一级故障）
	Air_compressor_temperature_over_error1						 = 0x2a11,//10769		//空压机 温度过高（一级故障）
	Air_compressor_temperature_over_error2						 = 0x2a12,//10770		//空压机 温度过高（2级故障）
	Air_compressor_temperature_over_error3						 = 0x2a13,//10771		//空压机 温度过高（3级故障）
	Air_compressor_temperature_under_error1						 = 0x2a14,//10772		//空压机 温度过低（一级故障）
	Air_compressor_temperature_under_error2						 = 0x2a15,//10773		//空压机 温度过低（2级故障）
	Air_compressor_temperature_under_error3						 = 0x2a16,//10774		//空压机 温度过低（3级故障）








	//电堆散热系统 
	Water_pressure_pile_inlet_over_error1							 = 0x3101,//12545		//电堆入口水压  过压（一级故障）
	Water_pressure_pile_inlet_under_error1							 = 0x3104,//12548		//电堆入口水压  欠压（一级故障）
	Water_pressure_pile_inlet_atd_error1							 = 0x310a,//12554		//电堆入口水压	ad采样异常（一级故障）

	Water_pressure_pile_outlet_over_error1							 = 0x3201,//12801		//电堆出口水压  过压（一级故障）
	Water_pressure_pile_outlet_under_error1							 = 0x3204,//12804		//电堆出口水压  欠压（一级故障）
	Water_pressure_pile_outlet_atd_error1							 = 0x320a,//12810		//电堆出口水压	ad采样异常（一级故障）

	Water_pressure_differential_pile_inlet_and_outlet_over_error1	 = 0x3301,//13057		//电堆入口和出口的水压差  过压（一级故障）
	Water_pressure_differential_pile_inlet_and_outlet_under_error1	 = 0x3304,//13060		//电堆入口和出口的水压差  欠压（一级故障）

	Water_temperature_pile_inlet_over_error1						 = 0x3401,//13313		//电堆入口水温  过温（一级故障）
	Water_temperature_pile_inlet_over_error3						 = 0x3403,//13315		//电堆入口水温  过温（3级故障）
	Water_temperature_pile_inlet_under_error1						 = 0x3404,//13316		//电堆入口水温  欠温（一级故障）
	Water_temperature_pile_inlet_atd_error1							 = 0x340a,//13322		//电堆入口水温	ad采样异常（一级故障）

	Water_temperature_pile_outlet_over_error1						 = 0x3501,//13569		//电堆出口水温  过温（一级故障）
	Water_temperature_pile_outlet_over_error3						 = 0x3503,//13571		//电堆出口水温  过温（3级故障）
	Water_temperature_pile_outlet_under_error1						 = 0x3504,//13572		//电堆出口水温  欠温（一级故障）
	Water_temperature_pile_outlet_atd_error1						 = 0x350a,//13578		//电堆出口水温	ad采样异常（一级故障）	

	Water_temperature_differential_pile_inlet_and_outlet_over_error1 = 0x3601,//13825		//电堆入口和出口的水温差  过温（一级故障）
	Water_temperature_differential_pile_inlet_and_outlet_over_error3 = 0x3603,//13827		//电堆入口和出口的水温差  过温（3级故障）
	Water_temperature_differential_pile_inlet_and_outlet_under_error1= 0x3604,//13828		//电堆入口和出口的水温差  欠温（一级故障）








	//三合一散热系统 数据
	Water_temperature_compressor_outlet_over_error1				 = 0x4101,//16641		//空压机出口水温  过温（一级故障）
	Water_temperature_compressor_outlet_over_error3				 = 0x4103,//16643		//空压机出口水温  过温（3级故障）
	Water_temperature_compressor_outlet_under_error1			 = 0x4104,//16644		//空压机出口水温  欠温（一级故障）
	Water_temperature_compressor_outlet_under_error3			 = 0x4106,//16646		//空压机出口水温  欠温（3级故障）
	Water_temperature_compressor_outlet_atd_error1				 = 0x410a,//16650		//空压机出口水温	ad采样异常（一级故障）

	Water_temperature_pump_outlet_over_error1					 = 0x4201,//16897		//三合一水泵出口水温  过温（一级故障）
	Water_temperature_pump_outlet_over_error3					 = 0x4203,//16899		//三合一水泵出口水温  过温（3级故障）
	Water_temperature_pump_outlet_under_error1					 = 0x4204,//16900		//三合一水泵出口水温  欠温（一级故障）
	Water_temperature_pump_outlet_under_error3					 = 0x4206,//16902		//三合一水泵出口水温  欠温（3级故障）
	Water_temperature_pump_outlet_atd_error1					 = 0x420a,//16906		//三合一水泵出口水温	ad采样异常（一级故障）

	Water_temperature_compressor_shell_over_error1				 = 0x4301,//17153		//空压机壳体温度  过温（一级故障）
	Water_temperature_compressor_shell_over_error3				 = 0x4303,//17155		//空压机壳体温度  过温（3级故障）
	Water_temperature_compressor_shell_under_error1				 = 0x4304,//17156		//空压机壳体温度  欠温（一级故障）
	Water_temperature_compressor_shell_under_error3				 = 0x4306,//17158		//空压机壳体温度  欠温（3级故障）
	Water_temperature_compressor_shell_atd_error1				 = 0x430a,//17162		//空压机壳体温度	ad采样异常（一级故障）

	Water_pressure_compressor_outlet_under_error1				 = 0x4404,//17412		//空压机出口水压	欠压（一级故障） 
	Water_pressure_compressor_outlet_atd_error1					 = 0x440a,//17418		//空压机出口水压	ad采样异常（一级故障）

	Water_temperature_frequency_outlet_over_error1				 = 0x4501,//17665		//变频器出口水温  过温（一级故障）
	Water_temperature_frequency_outlet_over_error3				 = 0x4503,//17667		//变频器出口水温  过温（3级故障）
	Water_temperature_frequency_outlet_under_error1		    	 = 0x4504,//17668		//变频器出口水温  欠温（一级故障）
	Water_temperature_frequency_outlet_under_error3	    		 = 0x4506,//17670		//变频器出口水温  欠温（3级故障）
	Water_temperature_frequency_outlet_atd_error1				 = 0x450a,//17674		//变频器出口水温	ad采样异常（一级故障）

	Water_temperature_intercooler_outlet_over_error1			 = 0x4601,//17921		//中冷器出口水温  过温（一级故障）
	Water_temperature_intercooler_outlet_over_error3			 = 0x4603,//17923		//中冷器出口水温  过温（3级故障）
	Water_temperature_intercooler_outlet_under_error1			 = 0x4604,//17924		//中冷器出口水温  欠温（一级故障）
	Water_temperature_intercooler_outlet_under_error3			 = 0x4606,//17926		//中冷器出口水温  欠温（3级故障）
	Water_temperature_intercooler_outlet_atd_error1				 = 0x460a,//17930		//中冷器出口水温	ad采样异常（一级故障）
	
	Water_pressure_pump_outlet_over_error1				         = 0x4701,//18177		//三合一水泵出口水压  过压（一级故障）
	Water_pressure_pump_outlet_over_error3				    	 = 0x4703,//18179		//三合一水泵出口水压  过压（3级故障）
	Water_pressure_pump_outlet_under_error1			    		 = 0x4704,//18180		//三合一水泵出口水压  欠压（一级故障）
	Water_pressure_pump_outlet_under_error3			    		 = 0x4706,//18182		//三合一水泵出口水压  欠压（3级故障）
	Water_pressure_pump_outlet_atd_error1			    		 = 0x470a,//18186		//三合一水泵出口水压	ad采样异常（一级故障）		
	
	
	
	
	

	//电堆发电的数据
	Galvanic_pile_voltage_over_error1							 = 0x5101,//20737		//电堆电压  过高（一级故障）
	Galvanic_pile_voltage_under_error1							 = 0x5104,//20740		//电堆电压  过低（一级故障）
	Galvanic_pile_voltage_under_error2							 = 0x5105,//20741		//电堆电压  过低（2级故障）
	Galvanic_pile_voltage_under_error3							 = 0x5106,//20742		//电堆电压  过低（3级故障）
	Galvanic_pile_voltage_atd_error1							 = 0x510a,//20746		//电堆的电压	ad采样异常（一级故障）
	Galvanic_pile_voltage_statas_error1							 = 0x510b,//20747		//电堆电压在停机的时候没有降为0，可能是小电阻的继电器故障（一级故障）

	Galvanic_pile_electricity_over_error1						 = 0x5201,//20993		//电堆电流  过高（一级故障）
	Galvanic_pile_electricity_over_error2						 = 0x5202,//20994		//电堆电流  过高（2级故障）
	Galvanic_pile_electricity_over_error3						 = 0x5203,//20995		//电堆电流  过高（3级故障）
	Galvanic_pile_electricity_under_error1						 = 0x5204,//20996		//电堆电流  过低（一级故障）
	Galvanic_pile_electricity_atd_error1						 = 0x520a,//21002		//电堆的电流	ad采样异常（一级故障）
	Galvanic_pile_electricity_statas_error1						 = 0x520b,//21003		//电堆电流传感器状态故障，可能是输出继电器故障（一级故障）

	Galvanic_pile_pressure_differential_h2_and_air_over_error1	 = 0x5301,//21249		//电堆氢氧两侧的压差  过压（一级故障）
	Galvanic_pile_pressure_differential_h2_and_air_over_error2	 = 0x5302,//21250		//电堆氢氧两侧的压差  过压（2级故障）
	Galvanic_pile_pressure_differential_h2_and_air_over_error3	 = 0x5303,//21251		//电堆氢氧两侧的压差  过压（3级故障）

	//收到停机指令时，电流大于100A，提示用户不能带载停机
	Galvanic_pile_electricity_over_when_stop_error1				 = 0x5401,//21505		//收到停机指令时，电流大于100A，提示用户不能带载停机（一级故障）
	Galvanic_pile_electricity_over_when_stop_error2				 = 0x5402,//21506		//收到停机指令时，电流大于100A，提示用户不能带载停机（2级故障）

	//巡检
	Itinerant_detective_communication_error1					 = 0x5a0a,//23050		//巡检  can通信故障（一级故障）
	Itinerant_detective_working_statas_error1					 = 0x5a0b,//23051		//巡检工作状态故障（一级故障）
	Itinerant_detective_working_statas_error2					 = 0x5a0c,//23052		//巡检工作状态故障（2级故障）

	Glectric1_single_chip_minimum_voltage_under_error1			 = 0x5a14,//23060		//巡检单片电压过低（一级故障）
	Glectric1_single_chip_minimum_voltage_under_error2			 = 0x5a15,//23061		//巡检单片电压过低（2级故障）
	Glectric1_single_chip_minimum_voltage_under_error3			 = 0x5a16,//23062		//巡检单片电压过低（3级故障）

    //绝缘模块 can通信数据
    Insulation_monitor_communication_error1                      = 0x5b0a,//23306       //绝缘模块  can通信故障（一级故障）


};


//错误信息的结构体，里面包含错误码和错误码的文本说明字符串
struct Error_information
{
	enum Error_code error_code;	//错误码
	char Error_string[ERROR_STRING_LENGTH];		//错误码的文本说明字符串

};	


//错误码初始化，清空Error_information里面的所有内容
//p_error_information : 是要被初始化的Error_information错误码结构体的指针。
void Error_init(struct Error_information * p_error_information);

#endif
