#ifndef _ATD_H
#define _ATD_H


#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "error_system.h"
#include "sci.h"
#include "pwm.h"                                      
#include "pit.h"
                                           

//ad采集和转化的时间间隔（微秒us） 默认1000微秒，大约可以采集10次
#define ATDX_TIME_PERIOD		5000

//ad转换通道的数量最大值，mc9s12 有16个ad
#define ATD0_CONVERSION_NUMBER_MAX		16		


//ad采集的结果，原始结果。   
//实际结果为    原始结果 * 5v / （2的n次方）      n为采样精度
extern u16 atd0_original_data[ATD0_CONVERSION_NUMBER_MAX] ;


//ad采集的10次平均值
extern u16 atd0_mean_data[ATD0_CONVERSION_NUMBER_MAX];

//ad在单位时间采集的次数。
extern u32 atd0_capture_number;

//ad在单位时间采集的次数最大值
extern u32 atd0_capture_number_max ;





//ad1转换通道的数量最大值，mc9s12 有8个ad
#define ATD1_CONVERSION_NUMBER_MAX		8	
//ad1采集的结果，原始结果。
extern u16 atd1_original_data[ATD1_CONVERSION_NUMBER_MAX];
//ad1采集的10次平均值
extern u16 atd1_mean_data[ATD1_CONVERSION_NUMBER_MAX];

//ad1在单位时间采集的次数。
extern u32 atd1_capture_number;

//ad在单位时间采集的次数最大值
extern u32 atd1_capture_number_max ;




//ad采集电压的时间（微秒us）
extern u32 atdx_time_count;

//ad采集和转化的时间间隔（微秒us）
extern u32 atdx_time_period ;


//NTC的转化列表  寄存器对应温度值。
extern const u16 AD_Result[141];
extern const i8 Temp_Value[141];


//test
extern u32 test_atdx_begin ;
extern u32 test_atdx_end ;
extern u32 test_atdx_last;
extern u32 test_atdx_now ;





//ad转化精度 配置ATD0CTL1_SRES， 直接影响到结果的有效位数。
enum ATDX_conversion_accuracy
{
	atdx_conversion_accuracy_8bit = 0x0,
	atdx_conversion_accuracy_10bit = 0x1,
	atdx_conversion_accuracy_12bit = 0x2,
};

//ad通道的输入模式
enum ATDX_input_mode
{
	atdx_input_analog ,		//输入模拟量（0~5V之间的电压）
	atdx_input_digital ,		//输入数字量（0或5v 的数字信号， 就是当做普通的io输入口）
};

//ad使用采集电压通道的数量
//单通道采集则为atd_conversion_number_1，多通道采集，则对应其他的。
enum ATDX_conversion_number
{
	atdx_conversion_number_1 = 0x1,
	atdx_conversion_number_2 = 0x2,
	atdx_conversion_number_3 = 0x3,
	atdx_conversion_number_4 = 0x4,
	atdx_conversion_number_5 = 0x5,
	atdx_conversion_number_6 = 0x6,
	atdx_conversion_number_7 = 0x7,
	atdx_conversion_number_8 = 0x8,
	atdx_conversion_number_9 = 0x9,
	atdx_conversion_number_10 = 0xa,
	atdx_conversion_number_11 = 0xb,
	atdx_conversion_number_12 = 0xc,
	atdx_conversion_number_13 = 0xd,
	atdx_conversion_number_14 = 0xe,
	atdx_conversion_number_15 = 0xf,
	atdx_conversion_number_16 = 0x10,//注意了，转换16个通道，S8C, S4C, S2C, S1C寄存器写0
};

//ad采集电压 的 开始通道（就是从哪个通道口开始采集）
//例如采集数量为2，开始通道为3，那么实际采集3和4号通道口的电压。
//对应的结果寄存器为ATD0DR0L ATD0DR1L
//注意了，结果寄存器的储存，每次循环永远都是从ATD0DR0L 开始，不受开始通道影响

//ad采集电压 的 开始通道（就是从哪个通道口开始采集）
enum ATDX_start_number
{
	atdx_start_number_0 = 0x0,
	atdx_start_number_1 = 0x1,
	atdx_start_number_2 = 0x2,
	atdx_start_number_3 = 0x3,
	atdx_start_number_4 = 0x4,
	atdx_start_number_5 = 0x5,
	atdx_start_number_6 = 0x6,
	atdx_start_number_7 = 0x7,
	atdx_start_number_8 = 0x8,
	atdx_start_number_9 = 0x9,
	atdx_start_number_10 = 0xa,
	atdx_start_number_11 = 0xb,
	atdx_start_number_12 = 0xc,
	atdx_start_number_13 = 0xd,
	atdx_start_number_14 = 0xe,
	atdx_start_number_15 = 0xf,
};

//ad采集是否连续，
enum ATDX_conversion_is_continuous
{
	atdx_continuous = 1,		//连续采集，只需要配置一次 ATD0CTL5	， 即可连续不断的采集电压
	atdx_discontinuous = 0,	//不连续采集，每采集一次循环，就会进入空闲，需要重新写入ATD0CTL5，才会开始新的采集
};


extern enum ATD_input_mode atd0_input_mode;
extern enum ATD_conversion_accuracy atd0_conversion_accuracy;
extern enum ATD_conversion_number atd0_conversion_number;
extern enum ATD_start_number atd0_start_number;
extern enum ATD_conversion_is_continuous atd0_conversion_is_continuous;


// 初始化atd               
enum Error_code INIT_ATD0(void);

//ad连续性配置,和初始化一样，配置一次
enum Error_code ATD0_set_continuous(void) ;

//ad采集电压，需要循环调用，刷新数据
enum Error_code ATD0_capture(void) ;

//ad采集电压，10次平均值
enum Error_code ATD0_capture_mean(void) ;


//压力传感器，ad测量电压转化为压力信号
//内置220电阻，压力传感器输出4~20mA的电流信号
//所以实测的电压应该在0.88~4.4V之间。
//输入ad寄存器原始值，ad采样精度，和压力传感器的范围。
//输出压力的实际值。
float atdx_transformed_to_pressure
	(u16 ad_value, enum ATD_conversion_accuracy atdx_conversion_accuracy, 
	float pressure_max);



/*******************************************/
//以下是ADC1的代码  hsp
/******************************************/	

extern enum ATD_input_mode atd1_input_mode;
extern enum ATD_conversion_accuracy atd1_conversion_accuracy;
extern enum ATD_conversion_number atd1_conversion_number;
extern enum ATD_start_number atd1_start_number;
extern enum ATD_conversion_is_continuous atd1_conversion_is_continuous;	



enum Error_code INIT_ATD1(void);


enum Error_code ATD1_set_continuous(void); 


enum Error_code ATD1_capture(void);                                       

enum Error_code ATD1_capture_mean(void);



//NTC温度传感器 计算
float atd_ntc_calculation(u16 da_data);

//4~20mA电流传感器 计算
float atd_electricity_calculation(u16 da_data, u16 range_data );

//0.5~4.5V电压传感器 计算
float atd_voltage_calculation_for_pressuer(u16 da_data, u16 range_data );

//电压传感器 计算
//ad 转化为 电堆电压
float atd_voltage_calculation_for_pile_voltage(u16 da_data, u16 range_data);
//ad 转化为 电堆电流
float atd_voltage_calculation_for_pile_electricity(u16 da_data);
//ad 转化为 空气流量
float atd_voltage_calculation_for_air_rate_of_flow(u16 da_data);
//ad 转化为 氢气浓度	
float atd_voltage_calculation_for_h2_concentration(u16 da_data);

//ad待机检测，判断传感器是否正常
enum Error_code atd_wait_check(void);

//ad待机检测，判断传感器是否正常 ,不带比例阀前氢压
enum Error_code atd_wait_check_ex(void);

#endif
