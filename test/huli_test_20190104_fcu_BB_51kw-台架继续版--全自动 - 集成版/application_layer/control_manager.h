
#ifndef _CONTROL_MANAGER_H                                       
#define _CONTROL_MANAGER_H

#include"data_buff.h"
#include "atd.h"
                                                               
//低压电源24V
#define LOW_VOLTAGE_24V		 		24

//入口氢压限定值  下限400
#define  H2_PRESSURE_PROPORTIONAL_VALVE_FRONT_LOWER_LIMIT	400  
//入口氢压限定值  上限600
#define  H2_PRESSURE_PROPORTIONAL_VALVE_FRONT_UPPER_LIMIT	600 



//系统运行模式
typedef enum FCU_System_Running_Mode                              
{
	system_running_manual = 0,				//全手动
	system_running_semi_auto = 1,			//半自动
	system_running_full_auto = 2,			//全自动
	system_running_full_test = 4,			//调试
}FCU_System_Running_Mode;

//控制模式
typedef enum Working_Control_Mode
{
	working_control_outage = 0,			//控制中断
	
//	working_control_wait2 = 3,			//控制等待2（从待机到运行的中间过程）
//	working_control_error = 4,			//故障停机的等待状态，复位消息即可恢复到wait

	working_control_check1 = 11,			//自我检查
	working_control_check2 = 12,			//自我检查

	working_control_wait = 13,				//控制等待

	working_control_check3 = 14,			//自我检查

	working_control_start1  = 21,			//正在启动
	working_control_start2  = 22,			//正在启动
	working_control_start3  = 23,			//正在启动
	working_control_start4  = 24,			//正在启动
	working_control_start5  = 25,			//正在启动
	working_control_start6  = 26,			//正在启动
	working_control_start7  = 27,			//正在启动
	working_control_start8  = 28,			//正在启动
	working_control_start9  = 29,			//正在启动
	working_control_start10  = 30,			//正在启动
	working_control_start11  = 31,			//正在启动
	working_control_start12  = 32,			//正在启动
	working_control_start13  = 33,			//正在启动

	working_control_run = 40,				//正在运行

	working_control_stop1  = 41,			//正在停止
	working_control_stop2  = 42,			//正在停止
	working_control_stop3  = 43,			//正在停止
	working_control_stop4  = 44,			//正在停止
	working_control_stop5  = 45,			//正在停止
	working_control_stop6  = 46,			//正在停止
	working_control_stop7  = 47,			//正在停止
	working_control_stop8  = 48,			//正在停止
	working_control_stop9  = 49,			//正在停止
	working_control_stop10  = 50,			//正在停止
	working_control_stop11  = 51,			//正在停止
	working_control_stop12  = 52,			//正在停止

	working_control_fault0  = 60,			//故障停机
	working_control_fault1  = 61,			//故障停机
	working_control_fault2  = 62,			//故障停机
	working_control_fault3  = 63,			//故障停机
	working_control_fault4  = 64,			//故障停机
	working_control_fault5  = 65,			//故障停机
	working_control_fault6  = 66,			//故障停机
	working_control_fault7  = 67,			//故障停机
	working_control_fault8  = 68,			//故障停机
	working_control_fault9  = 69,			//故障停机
	working_control_fault10  = 70,			//故障停机
	working_control_fault11  = 71,			//故障停机
	working_control_fault12  = 72,			//故障停机

	working_control_fault_wait  = 80,		//故障停机的等待状态，复位消息即可恢复到wait

}Working_Control_Mode;


//工作模式
typedef enum Working_Status_Mode
{
	//通用
	working_status_communication_outage = 0,		//通信中断
	working_status_wait = 1,						//待机，
	working_status_run = 2,							//运行

	working_status_normal = 7,						//正常

	working_status_starting  = 4,			//正在启动
	working_status_stoping  = 5,			//正在停止

	//异常
	working_status_error = 101,				//故障，错误
}Working_Status_Mode;

//异常告警
typedef enum Working_Alarm_Mode
{
	one_level_fault = 1,			//一级告警
	two_level_fault = 2,			//二级告警
	three_level_fault = 3,			//三级告警
	working_normal = 4,				//正常状态，没有故障
}Working_Alarm_Mode;
/*
//fcu输出电流的等级
typedef enum FCU_Output_Electricity_Level
{
fcu_output_power_0_30A		= 0,
fcu_output_power_30_50A		= 1,
fcu_output_power_50_100A	= 2,
fcu_output_power_100_150A	= 3,
fcu_output_power_150_200A	= 4,
fcu_output_power_200_250A	= 5,
fcu_output_power_250_300A	= 6,
fcu_output_power_300_360A	= 7,
}FCU_Output_Electricity_Level;
*/

//fcu运行时，电流档位的总数   51kw的堆   默认为12个电流档
#define FCU_OUTPUT_ELECTRICITY_TOTAL_NUMBER		 	12

//fcu运行时，电流档位的参数调整的结构体
typedef struct FCU_Run_Data_Debug
{
	float	fcu_output_electricity_lower_limit;         //电堆输出电流，档位下限
	float	fcu_output_electricity_upper_limit;         //电堆输出电流，档位上限

	float	pid1_Kp;
	float	pid1_Ki;
	float	pid1_Kd;
	float	pid2_Kp;
	float	pid2_Ki;
	float	pid2_Kd;
	float   h2_pressure_target_value;               //氢压 目标值
	float   h2_pressure_advance_set_value;          //氢压 提前量  设定值  默认为0，一般设为5
	u32		h2_outlet_valve_open_time ;				//氢气尾排阀开启的时间
	u32		h2_outlet_valve_close_time ;			//氢气尾排阀关闭的时间
	u16     h2_circulating_pump_speed_setpoint;       //氢气循环泵转速设定                            输出can

	u32		air_compressor_speed_setpoint;		    //空压机转速，控制变频器，				输出can，
    float   air_rate_of_flow_target;                //空气流量的目标值
    	
	float   water_temperature_target_value;         //电堆入口水温 目标值

}FCU_Run_Data_Debug;





//系统状态更改的最大延时，完成任务之后，需要等待这个延时，才能进入下一个状态(默认为0.1s)
#define FCU_SYSTEM_CHANGE_MODE_DELAY_100MS		 	100
//系统状态更改的最大延时，完成任务之后，需要等待这个延时，才能进入下一个状态(默认为1s)
#define FCU_SYSTEM_CHANGE_MODE_DELAY_1S		 		1000
//系统状态更改的最大延时，完成任务之后，需要等待这个延时，才能进入下一个状态(默认为2s)
#define FCU_SYSTEM_CHANGE_MODE_DELAY_2S		 		2000
//系统状态更改的最大延时，完成任务之后，需要等待这个延时，才能进入下一个状态(默认为3s)
#define FCU_SYSTEM_CHANGE_MODE_DELAY_3S		 		3000
//系统状态更改的最大延时，完成任务之后，需要等待这个延时，才能进入下一个状态(默认为5s)
#define FCU_SYSTEM_CHANGE_MODE_DELAY_5S		 		5000
//系统状态更改的最大延时，完成任务之后，需要等待这个延时，才能进入下一个状态(默认为6s)
#define FCU_SYSTEM_CHANGE_MODE_DELAY_6S		 		6000
//系统状态更改的最大延时，完成任务之后，需要等待这个延时，才能进入下一个状态(默认为10s)
#define FCU_SYSTEM_CHANGE_MODE_DELAY_10S	 		10000
//系统状态更改的最大延时，完成任务之后，需要等待这个延时，才能进入下一个状态(默认为15s)
#define FCU_SYSTEM_CHANGE_MODE_DELAY_15S	 		15000
//系统状态更改的最大延时，完成任务之后，需要等待这个延时，才能进入下一个状态(默认为20s)
#define FCU_SYSTEM_CHANGE_MODE_DELAY_20S	 		20000
//系统状态更改的最大延时，完成任务之后，需要等待这个延时，才能进入下一个状态(默认为30s)
#define FCU_SYSTEM_CHANGE_MODE_DELAY_30S	 		30000
//系统状态更改的最大延时，完成任务之后，需要等待这个延时，才能进入下一个状态(默认为60s)
#define FCU_SYSTEM_CHANGE_MODE_DELAY_60S	 		60000
//系统状态更改的最大延时，完成任务之后，需要等待这个延时，才能进入下一个状态(默认为70s)
#define FCU_SYSTEM_CHANGE_MODE_DELAY_70S	 		70000
//系统状态更改的最大延时，完成任务之后，需要等待这个延时，才能进入下一个状态(默认为60s)
#define FCU_SYSTEM_CHANGE_MODE_DELAY_100S	 		100000

//超时的时间（当前系统时间 减去 上一次数据更新的时间 大于 超时时间，那么就超时，如果没有在规定的时间内完成任务，那么报错。(默认为10s)
#define FCU_SYSTEM_OVERTIME_MAX_10					 		10000
//超时的时间（当前系统时间 减去 上一次数据更新的时间 大于 超时时间，那么就超时，如果没有在规定的时间内完成任务，那么报错。(默认为10s)
#define FCU_SYSTEM_OVERTIME_MAX_120					 		120000
//超时的时间（当前系统时间 减去 上一次数据更新的时间 大于 超时时间，那么就超时，如果没有在规定的时间内完成任务，那么报错。(默认为10s)
#define FCU_SYSTEM_OVERTIME_MAX_600							600000

/*
//fcu运行时，电堆电流的档位切换
#define GALVANIC_PILE_ELECTRICITY_0			0
#define GALVANIC_PILE_ELECTRICITY_30		30
#define GALVANIC_PILE_ELECTRICITY_40		40
#define GALVANIC_PILE_ELECTRICITY_50		50
#define GALVANIC_PILE_ELECTRICITY_60		60
#define GALVANIC_PILE_ELECTRICITY_90		90
#define GALVANIC_PILE_ELECTRICITY_100		100
#define GALVANIC_PILE_ELECTRICITY_110		110
#define GALVANIC_PILE_ELECTRICITY_140		140
#define GALVANIC_PILE_ELECTRICITY_150		150
#define GALVANIC_PILE_ELECTRICITY_160		160
#define GALVANIC_PILE_ELECTRICITY_190		190
#define GALVANIC_PILE_ELECTRICITY_200		200
#define GALVANIC_PILE_ELECTRICITY_210		210
#define GALVANIC_PILE_ELECTRICITY_240		240
#define GALVANIC_PILE_ELECTRICITY_250		250
#define GALVANIC_PILE_ELECTRICITY_260		260
#define GALVANIC_PILE_ELECTRICITY_290		260
#define GALVANIC_PILE_ELECTRICITY_300		270
#define GALVANIC_PILE_ELECTRICITY_310		280
*/

//fcu的总 控制管理
typedef struct Control_Policy_Total_Manager
{
	enum Working_Control_Mode		working_control_mode;	//控制模式
	enum Working_Status_Mode		working_status_mode;	//工作模式		
	enum Working_Alarm_Mode 		working_alarm_mode;		//异常告警	
	enum Error_code					working_FCU_error_code;	//fcu错误码
	enum Working_Control_Mode		working_FCU_error_control_mode;	//出错瞬间，fcu的控制模式

	enum FCU_System_Running_Mode		fcu_system_running_mode;	//系统运行模式

	u32						fcu_updata_event_time;								 //数据更新的时间

	u8						working_error_count;			//错误的次数，如果出现三次，则取消本次命令。

	int						fcu_output_electricity_level;		//fcu输出电流的等级
	struct FCU_Run_Data_Debug		fcu_run_data_debug[FCU_OUTPUT_ELECTRICITY_TOTAL_NUMBER];			//fcu运行时，电流档位的参数调整的结构体

	u8						galvanic_pile_load_resistance_switch_count;		//小负载的切换次数
	
	//临时加的一级故障判断的延时  3秒
	u8  one_level_fault_flag_temp; //一级告警标记位，0正常，1出现一级告警
	u32 one_level_fault_time_temp; //一级告警标记时间。就是出现一级告警的时间。

}Control_Policy_Total_Manager;

extern struct Control_Policy_Total_Manager   control_policy_total_manager;

//FCU主控的管理初始化
enum Error_code Control_Policy_Total_Manager_init(
struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//FCU主控的管理更新数据（手动控制）通过rs232调试接口，
enum Error_code Control_Policy_Total_Manager_updata_by_manual(
struct Control_Policy_Total_Manager  * p_control_policy_total_manager, float * rs232_test);
//FCU主控的管理更新数据（自动控制）
enum Error_code Control_Policy_Total_Manager_updata_by_Automatic (
struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//FCU主控的管理更新数据（通过can和modbus通信接口）
enum Error_code Control_Policy_Total_Manager_updata_by_communication(
struct Control_Policy_Total_Manager  * p_control_policy_total_manager, 
struct FCU_Data_Buffer * p_fcu_data_buffer);

//FCU稳定运行时，自动调档
enum Error_code FCU_automatic_gear_shift(void);

//运行时的保护检验，通用型，
enum Error_code FCU_run_protect_check_common(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);

//FCU主控的管理更新数据（控制算法）
//最核心的控制算法，自动管理所有的数据，并保证发电机的正常运行。
enum Error_code Control_Policy_Total_Manager_updata_by_system(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);

//FCU主控，控制断开的算法，刚开机时的状态，进入自检1阶段
enum Error_code Control_Policy_Total_Manager_for_outage(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//FCU主控，自检1的算法，检查通信，进入等待状态
enum Error_code Control_Policy_Total_Manager_for_check1(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//FCU主控，自检2的算法，（当自检1没有通过，但是就接收到了启动命令，超时判断，10s内如果自检通过，那么进入待机，否则报错）
enum Error_code Control_Policy_Total_Manager_for_check2(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//FCU主控，等待处理的算法，判断是否需要启动fc，如果需要启动，则进入自检2状态，否则继续停留在等待状态。
enum Error_code Control_Policy_Total_Manager_for_wait(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//FCU主控，自检3的算法，分析子模块的数据，判断是否状态正常，如果正常，就进入启动阶段，如果检测失败，则进行回退处理，然后返回等待阶段
enum Error_code Control_Policy_Total_Manager_for_check3(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);

//fcu主控，启动1的算法，按照时序启动fc，如果启动成功，就进入运行阶段，如果启动失败，则进行回退处理，然后返回等待阶段
enum Error_code Control_Policy_Total_Manager_for_start1(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//fcu主控，启动2的算法，按照时序启动fc，如果启动成功，就进入运行阶段，如果启动失败，则进行回退处理，然后返回等待阶段
enum Error_code Control_Policy_Total_Manager_for_start2(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//fcu主控，启动3的算法，按照时序启动fc，如果启动成功，就进入运行阶段，如果启动失败，则进行回退处理，然后返回等待阶段
enum Error_code Control_Policy_Total_Manager_for_start3(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//fcu主控，启动4的算法，按照时序启动fc，如果启动成功，就进入运行阶段，如果启动失败，则进行回退处理，然后返回等待阶段
enum Error_code Control_Policy_Total_Manager_for_start4(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//fcu主控，启动5的算法，按照时序启动fc，如果启动成功，就进入运行阶段，如果启动失败，则进行回退处理，然后返回等待阶段
enum Error_code Control_Policy_Total_Manager_for_start5(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//fcu主控，启动6的算法，按照时序启动fc，如果启动成功，就进入运行阶段，如果启动失败，则进行回退处理，然后返回等待阶段
enum Error_code Control_Policy_Total_Manager_for_start6(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//fcu主控，启动7的算法，按照时序启动fc，如果启动成功，就进入运行阶段，如果启动失败，则进行回退处理，然后返回等待阶段
enum Error_code Control_Policy_Total_Manager_for_start7(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//fcu主控，启动8的算法，按照时序启动fc，如果启动成功，就进入运行阶段，如果启动失败，则进行回退处理，然后返回等待阶段
enum Error_code Control_Policy_Total_Manager_for_start8(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//fcu主控，启动9的算法，按照时序启动fc，如果启动成功，就进入运行阶段，如果启动失败，则进行回退处理，然后返回等待阶段
enum Error_code Control_Policy_Total_Manager_for_start9(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//fcu主控，启动10的算法，按照时序启动fc，如果启动成功，就进入运行阶段，如果启动失败，则进行回退处理，然后返回等待阶段
enum Error_code Control_Policy_Total_Manager_for_start10(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//fcu主控，启动11的算法，按照时序启动fc，如果启动成功，就进入运行阶段，如果启动失败，则进行回退处理，然后返回等待阶段
enum Error_code Control_Policy_Total_Manager_for_start11(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//fcu主控，启动12的算法，按照时序启动fc，如果启动成功，就进入运行阶段，如果启动失败，则进行回退处理，然后返回等待阶段
enum Error_code Control_Policy_Total_Manager_for_start12(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);


//fcu主控，运行的算法，功率控制，如果运行出现异常，则进行回退处理，然后返回等待阶段
enum Error_code Control_Policy_Total_Manager_for_run(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);



//fcu主控，停止1的算法，按照时序停止fc，最终进入等待阶段
enum Error_code Control_Policy_Total_Manager_for_stop1(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//fcu主控，停止2的算法，按照时序停止fc，最终进入等待阶段
enum Error_code Control_Policy_Total_Manager_for_stop2(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//fcu主控，停止3的算法，按照时序停止fc，最终进入等待阶段
enum Error_code Control_Policy_Total_Manager_for_stop3(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//fcu主控，停止4的算法，按照时序停止fc，最终进入等待阶段
enum Error_code Control_Policy_Total_Manager_for_stop4(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//fcu主控，停止5的算法，按照时序停止fc，最终进入等待阶段
enum Error_code Control_Policy_Total_Manager_for_stop5(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//fcu主控，停止6的算法，按照时序停止fc，最终进入等待阶段
enum Error_code Control_Policy_Total_Manager_for_stop6(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//fcu主控，停止7的算法，按照时序停止fc，最终进入等待阶段
enum Error_code Control_Policy_Total_Manager_for_stop7(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//fcu主控，停止8的算法，按照时序停止fc，最终进入等待阶段
enum Error_code Control_Policy_Total_Manager_for_stop8(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//fcu主控，停止9的算法，按照时序停止fc，最终进入等待阶段
enum Error_code Control_Policy_Total_Manager_for_stop9(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//fcu主控，停止10的算法，按照时序停止fc，最终进入等待阶段
enum Error_code Control_Policy_Total_Manager_for_stop10(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//fcu主控，停止11的算法，按照时序停止fc，最终进入等待阶段
enum Error_code Control_Policy_Total_Manager_for_stop11(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//fcu主控，停止12的算法，按照时序停止fc，最终进入等待阶段
enum Error_code Control_Policy_Total_Manager_for_stop12(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);



//fcu主控，故障停机的算法，目前是直接跳保护。
enum Error_code Control_Policy_Total_Manager_for_fault0(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//fcu主控，故障停机1的算法，按照错误码停止fc，最终进入故障停机阶段
enum Error_code Control_Policy_Total_Manager_for_fault1(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//fcu主控，故障停机2的算法，按照错误码停止fc，最终进入故障停机阶段
enum Error_code Control_Policy_Total_Manager_for_fault2(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//fcu主控，故障停机3的算法，按照错误码停止fc，最终进入故障停机阶段
enum Error_code Control_Policy_Total_Manager_for_fault3(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//fcu主控，故障停机4的算法，按照错误码停止fc，最终进入故障停机阶段
enum Error_code Control_Policy_Total_Manager_for_fault4(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//fcu主控，故障停机5的算法，按照错误码停止fc，最终进入故障停机阶段
enum Error_code Control_Policy_Total_Manager_for_fault5(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//fcu主控，故障停机6的算法，按照错误码停止fc，最终进入故障停机阶段
enum Error_code Control_Policy_Total_Manager_for_fault6(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//fcu主控，故障停机7的算法，按照错误码停止fc，最终进入故障停机阶段
enum Error_code Control_Policy_Total_Manager_for_fault7(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//fcu主控，故障停机8的算法，按照错误码停止fc，最终进入故障停机阶段
enum Error_code Control_Policy_Total_Manager_for_fault8(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//fcu主控，故障停机9的算法，按照错误码停止fc，最终进入故障停机阶段
enum Error_code Control_Policy_Total_Manager_for_fault9(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//fcu主控，故障停机10的算法，按照错误码停止fc，最终进入故障停机阶段
enum Error_code Control_Policy_Total_Manager_for_fault10(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//fcu主控，故障停机11的算法，按照错误码停止fc，最终进入故障停机阶段
enum Error_code Control_Policy_Total_Manager_for_fault11(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//fcu主控，故障停机12的算法，按照错误码停止fc，最终进入故障停机阶段
enum Error_code Control_Policy_Total_Manager_for_fault12(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);

//fcu主控，//故障停机的等待状态，复位消息即可恢复到wait
enum Error_code Control_Policy_Total_Manager_for_fault_wait(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);





//判断2个值是否约等于  的容错率   20%
#define ERROR_TOLERANT_RATE 		0.2f

//判断2个值是否约等于，误差在容错率内，则返回Succeed，否则返回Failed
enum Error_code approximate(float value1, float value2);

//判断2个值是否约等于  的容错率   20%
#define ERROR_TOLERANT_RATE2 		0.05f

//判断2个值是否约等于，误差在容错率内，则返回Succeed，否则返回Failed
enum Error_code approximate2(float value1, float value2);


//按照优先级集成告警等级。（）
enum Error_code merge_alarm_mode(enum Working_Alarm_Mode * p_working_alarm_mode_source, enum Working_Alarm_Mode * p_working_alarm_mode_new);





#endif