#include "atd.h"

//ad采集的结果，原始结果。   
//实际结果为    原始结果 * 5v / （2的n次方）      n为采样精度
u16 atd0_original_data[ATD0_CONVERSION_NUMBER_MAX] = {0};


//ad采集的10次平均值
u16 atd0_mean_data[ATD0_CONVERSION_NUMBER_MAX] = {0};

//ad在单位时间采集的次数。
u32 atd0_capture_number = 0;

//ad在单位时间采集的次数最大值
u32 atd0_capture_number_max = 0;





//hsp
//实际结果为    原始结果 * 5v / （2的n次方）      n为采样精度
u16 atd1_original_data[ATD1_CONVERSION_NUMBER_MAX] = {0};

//ad1采集的10次平均值
u16 atd1_mean_data[ATD1_CONVERSION_NUMBER_MAX] = {0};

//ad1在单位时间采集的次数。     
u32 atd1_capture_number = 0;
//hsp_end
//ad在单位时间采集的次数最大值
u32 atd1_capture_number_max = 0;

//ad采集电压的时间（微秒us）
u32 atdx_time_count = 0;

//ad采集和转化的时间间隔（微秒us）
u32 atdx_time_period = ATDX_TIME_PERIOD;


const u16 AD_Result[141] = {
	0xF9D,0xF95,0xF8E,0xF85,0xF7D,0xF74,0xF6A,0xF60,0xF55,0xF49,
	0xF3D,0xF30,0xF23,0xF15,0xF06,0xEF7,0xEE6,0xED5,0xEC3,0xEB1,
	0xE9D,0xE89,0xE73,0xE5D,0xE46,0xE2E,0xE15,0xDFB,0xDE0,0xDC5,
	0xDA8,0xD8A,0xD6B,0xD4C,0xD2B,0xD0A,0xCE7,0xCC4,0xCA0,0xC7B,
	0xC55,0xC2E,0xC07,0xBDE,0xBB6,0xB8C,0xB62,0xB37,0xB0B,0xADF,
	0xAB3,0xA86,0xA58,0xA2B,0x9FD,0x9CF,0x9A0,0x972,0x943,0x915,
	0x8E6,0x8B8,0x88A,0x85C,0x82E,0x800,0x7D3,0x7A6,0x779,0x74D,
	0x721,0x6F6,0x6CB,0x6A1,0x677,0x64E,0x626,0x5FE,0x5D7,0x5B1,
	0x58B,0x566,0x542,0x51E,0x4FB,0x4D9,0x4B8,0x497,0x477,0x458,
	0x43A,0x41C,0x3FF,0x3E3,0x3C7,0x3AC,0x392,0x378,0x35F,0x347,
	0x330,0x319,0x302,0x2ED,0x2D8,0x2C3,0x2AF,0x29C,0x289,0x277,
	0x265,0x254,0x243,0x233,0x223,0x214,0x205,0x1F6,0x1E8,0x1DB,
	0x1CE,0x1C1,0x1B4,0x1A8,0x19D,0x191,0x186,0x17C,0x171,0x167,
	0x15E,0x154,0x14B,0x142,0x13A,0x131,0x129,0x121,0x11A,0x112,
	0x10B
};

const i8 Temp_Value[141] = {
	-40,-39,-38,-37,-36,-35,-34,-33,-32,-31,
	-30,-29,-28,-27,-26,-25,-24,-23,-22,-21,
	-20,-19,-18,-17,-16,-15,-14,-13,-12,-11,
	-10,-9,-8,-7,-6,-5,-4,-3,-2,-1,
	0,1,2,3,4,5,6,7,8,9,
	10,11,12,13,14,15,16,17,18,19,
	20,21,22,23,24,25,26,27,28,29,
	30,31,32,33,34,35,36,37,38,39,
	40,41,42,43,44,45,46,47,48,49,
	50,51,52,53,54,55,56,57,58,59,
	60,61,62,63,64,65,66,67,68,69,
	70,71,72,73,74,75,76,77,78,79,
	80,81,82,83,84,85,86,87,88,89,
	90,91,92,93,94,95,96,97,98,99,
	100
};


//test
u32 test_atdx_begin = 0;
u32 test_atdx_end = 0;
u32 test_atdx_last = 0;
u32 test_atdx_now = 0;











enum ATD_input_mode atd0_input_mode =  atdx_input_analog;
enum ATD_conversion_accuracy atd0_conversion_accuracy = atdx_conversion_accuracy_12bit;
enum ATD_conversion_number atd0_conversion_number   = atdx_conversion_number_16;
enum ATD_start_number atd0_start_number = atdx_start_number_0;
//enum ATD_conversion_is_continuous atd0_conversion_is_continuous  =  ATD_discontinuous;
enum ATD_conversion_is_continuous atd0_conversion_is_continuous  =  atdx_continuous ;


//ATD参数默认配置  hsp
enum ATD_input_mode atd1_input_mode =  atdx_input_analog;
enum ATD_conversion_accuracy atd1_conversion_accuracy = atdx_conversion_accuracy_12bit;
enum ATD_conversion_number atd1_conversion_number   = atdx_conversion_number_8;
enum ATD_start_number atd1_start_number = atdx_start_number_0;
enum ATD_conversion_is_continuous atd1_conversion_is_continuous  =  atdx_continuous ;
//hsp_end

//注意了，ad采集有2种模式。
//1.开启连续采集，开启中断。
//缺点：ad采集太快了，大约30us，
//这个时间不能用来pid计算，只能进行采集

//2.main函数手动采集，禁止中断。可以降低ad采集速度。
//然后在pit定时器里面进行pid控制。


// 初始化atd               
enum Error_code INIT_ATD0(void)
{
	//输入模拟量（0~5V之间的电压）
	if(atd0_input_mode == atdx_input_analog)
	{
		ATD0CTL1_SRES = (Byte)atd0_conversion_accuracy;  //选用xx位模数转换

		//默认为开启快速清除，就是当读取结果寄存器的时候，对应的标志位就直接清除
		ATD0CTL2 = 0x40;  //启动A/D转换,快速清零,禁止中断
		//	ATD0CTL2 = 0x42;  //启动A/D转换,快速清零,开启中断 

		//默认 0x80表示右对齐
		if(atd0_conversion_number == ATD0_CONVERSION_NUMBER_MAX)
		{       
			ATD0CTL3 = 0x80 ; //注意了，转换16个通道，S8C, S4C, S2C, S1C寄存器写0
		}
		else
		{
			ATD0CTL3 = 0x80 | (atd0_conversion_number << 3);
		}


		//实际的ad频率 = 总线频率/ 2 /（PRS+1）
		ATD0CTL4 = 0x07;   //AD模块时钟频率，影响到ad测量一次的时间和准确度
	}
	//输入数字量（0或5v 的数字信号， 就是当做普通的io输入口）
	else if(atd0_input_mode == atdx_input_digital)
	{
		ATD0DIEN= 0x03;   //将AD00和AD01设置为数字输入通道
		DDR1AD0 = 0X00;   //设置AD00和AD01为输入 //和普通的io口类似
		//后续通过 PT01AD0 PT0AD0 PT1AD0 访问数据。
		/*** PT01AD0 - Port AD0 Data Register; 0x00000270 ***/
	}

	return Succeed;
}


//ad连续性配置,和初始化一样，配置一次
enum Error_code ATD0_set_continuous(void)
{
	Byte mult_temp = 0;
	Byte i =0;

	//ad采集电压 的 开始通道 + 通道的数量 > 16 则报错
	if(atd0_conversion_number + atd0_start_number  > ATD0_CONVERSION_NUMBER_MAX)
	{
		return ATDX_conversion_number_error;
	}

	if(atd0_conversion_is_continuous == atdx_continuous)
	{
		//判断是否开启多通道采集
		if(atd0_conversion_number == atdx_conversion_number_1)
		{
			mult_temp = 0;
		}
		else
		{
			mult_temp = 1;
		}

		//设定采集的开始通道 和 是否连续采集
		//注意了，在不连续的情况下。只有对ATD0CTL4 和 ATD0CTL5 写入的时候，才会开始新的一轮采集电压
		ATD0CTL5 = (atdx_continuous << 5) | (mult_temp << 4) | atd0_start_number;
	}

	return Succeed;
}

//ad采集电压，需要循环调用，刷新数据
enum Error_code ATD0_capture(void)
{
	Byte mult_temp = 0;
	Byte i =0;

	//	Byte ad_number_temp = atd_start_number + i;
	Word ad_data_temp = 0;

	//ad采集电压 的 开始通道 + 通道的数量 > 16 则报错
	if(atd0_conversion_number + atd0_start_number  > ATD0_CONVERSION_NUMBER_MAX)
	{
		return ATDX_conversion_number_error;
	}

	if(atd0_conversion_is_continuous == atdx_discontinuous)
	{
		//判断是否开启多通道采集
		if(atd0_conversion_number == atdx_conversion_number_1)
		{
			mult_temp = 0;
		}
		else
		{
			mult_temp = 1;
		}

		//设定采集的开始通道 和 是否连续采集
		//注意了，在不连续的情况下。只有对ATD0CTL4 和 ATD0CTL5 写入的时候，才会开始新的一轮采集电压
		ATD0CTL5 = (mult_temp << 4) | atd0_start_number;
	}

	//判断采集完成的标志位
	while(!ATD0STAT0_SCF);

	//读取结果，注意了  开启 开启快速清除 之后，读取结果寄存器，便会自动清除标志位
	for(i=0; i< atd0_conversion_number; i++)
	{


		//结果寄存器，每次一轮采集 都是从ATD0DR0L开始储存。和 采集的开始通道 无关
		switch(i)
		{                 
		case 0:
			ad_data_temp = ATD0DR0;
			break;
		case 1:
			ad_data_temp = ATD0DR1;
			break;
		case 2:
			ad_data_temp = ATD0DR2;
			break;
		case 3:
			ad_data_temp = ATD0DR3;
			break;
		case 4:
			ad_data_temp = ATD0DR4;
			break;
		case 5:
			ad_data_temp = ATD0DR5;
			break;
		case 6:
			ad_data_temp = ATD0DR6;
			break;
		case 7:
			ad_data_temp = ATD0DR7;
			break;
		case 8:
			ad_data_temp = ATD0DR8;
			break;
		case 9:
			ad_data_temp = ATD0DR9;
			break;
		case 10:
			ad_data_temp = ATD0DR10;
			break;
		case 11:
			ad_data_temp = ATD0DR11;
			break;
		case 12:
			ad_data_temp = ATD0DR12;
			break;
		case 13:
			ad_data_temp = ATD0DR13;
			break;
		case 14:
			ad_data_temp = ATD0DR14;
			break;
		case 15:
			ad_data_temp = ATD0DR15;
			break;
		}

		atd0_original_data[atd0_start_number + i] = ad_data_temp;
	}

	return Succeed;
}


//ad采集电压，10次平均值
enum Error_code ATD0_capture_mean(void)
{
	/*
	int i = 0 ;
	int j = 0;

	for(j=0; j<16; j++)
	{
	ad_sum_data[j] = 0;
	}

	for(i =0; i<20;i++)
	{
	AD_capture(atd_conversion_number, atd_start_number, atd_conversion_is_continuous);
	for(j=0; j<16; j++)
	{
	ad_sum_data[j] += (u32)(ad_original_data[j]);
	}
	}

	for(j=0; j<16; j++)
	{
	ad_mean_data[j] = ad_sum_data[j] / 20;
	}
	*/



	//新的取平均值的算法。
	int j = 0;

	ATD0_capture();
	for(j=atd0_start_number; j<atd0_start_number+atd0_conversion_number; j++)
	{
		atd0_mean_data[j] = ((atd0_mean_data[j] *7) +  (atd0_original_data[j] ) ) >>3;
	}    


	//叠加计数
	atd0_capture_number++;
	return Succeed;
}


//压力传感器，ad测量电压转化为压力信号
//内置220电阻，压力传感器输出4~20mA的电流信号
//所以实测的电压应该在0.88~4.4V之间。
//输入ad寄存器原始值，ad采样精度，和压力传感器的范围。
//输出压力的实际值。
float atdx_transformed_to_pressure
	(u16 ad_value, enum ATD_conversion_accuracy atdx_conversion_accuracy, 
	float pressure_max)
{
	float voltage_actual = 0;			//ad实测的电压值 0~5V
	float pressure_value = 0;			//最终压力值

	//转化为实际电压0~5V
	switch(atdx_conversion_accuracy)
	{
	case atdx_conversion_accuracy_8bit:
		voltage_actual = (float)ad_value * 5 / 256 ;
		break;
	case atdx_conversion_accuracy_10bit:
		voltage_actual = (float)ad_value * 5 / 1024 ;
		break;
	case atdx_conversion_accuracy_12bit:
		voltage_actual = (float)ad_value * 5 / 4096 ;
		break;
	default:
		break;
	}

	//把电压值控制在0.88~4.4V之间
	if(voltage_actual < 0.88)
	{
		voltage_actual = 0.88;
	}
	if(voltage_actual > 4.4)
	{
		voltage_actual = 4.4;
	}

	//转化为实际的压力值。
	pressure_value = (voltage_actual - 0.88) * pressure_max / 3.52; 

	return pressure_value;
}



//ad0的中断函数
#pragma CODE_SEG __NEAR_SEG NON_BANKED
interrupt void atd0_interrupt(void) 
{   

	int i = 0 ;
	int j = 0;
	u16 ad_data_temp = 0;

	EnableInterrupts;
	if(ATD0STAT0_SCF==1)
	{
		//	   test_ad_now =  system_time_us -  test_ad_last;
		//	    test_ad_last =   system_time_us;


		//test_ad_begin = system_time_us;
		//读取结果，注意了  开启 开启快速清除 之后，读取结果寄存器，便会自动清除标志位
		for(i=0; i< atd0_conversion_number; i++)
		{
			//结果寄存器，每次一轮采集 都是从ATD0DR0L开始储存。和 采集的开始通道 无关
			switch(i)
			{
			case 0:
				ad_data_temp = ATD0DR0;
				break;
			case 1:
				ad_data_temp = ATD0DR1;
				break;
			case 2:
				ad_data_temp = ATD0DR2;
				break;
			case 3:
				ad_data_temp = ATD0DR3;
				break;
			case 4:
				ad_data_temp = ATD0DR4;
				break;
			case 5:
				ad_data_temp = ATD0DR5;
				break;
			case 6:
				ad_data_temp = ATD0DR6;
				break;
			case 7:
				ad_data_temp = ATD0DR7;
				break;
			case 8:
				ad_data_temp = ATD0DR8;
				break;
			case 9:
				ad_data_temp = ATD0DR9;
				break;
			case 10:
				ad_data_temp = ATD0DR10;
				break;
			case 11:
				ad_data_temp = ATD0DR11;
				break;
			case 12:
				ad_data_temp = ATD0DR12;
				break;
			case 13:
				ad_data_temp = ATD0DR13;
				break;
			case 14:
				ad_data_temp = ATD0DR14;
				break;
			case 15:
				ad_data_temp = ATD0DR15;
				break;
			}

			atd0_original_data[atd0_start_number + i] = ad_data_temp;
		}
		/* 
		//叠加汇总，
		for(j=0; j<16; j++)
		{
		ad_sum_data[j] += (u32)(ad_original_data[j]);

		}

		//叠加计数
		ad_capture_number++;


		//时间间隔一段时间之后，就求一次平均值，并进行pid运算
		if(system_time_us - ad_time_count >= ad_time_period)
		{
		for(j=0; j<16; j++)
		{
		//注意了，ad采样是，每隔1ms就取一次平均数，不是固定采集多少次
		ad_mean_data[j] = ad_sum_data[j] / ad_capture_number;
		ad_sum_data[j] = 0;
		}
		test_huli1 =   ad_capture_number;
		//清除计数和时间
		ad_capture_number = 0;
		ad_time_count = system_time_us;



		//pid控制。
		//注意了。pid算法需要很高的实时性，所以每次ad采样完成之后，就要立即进行pid算法控制，并且以较高的中断优先级2
		//注意了。pid算法需要很高的稳定性，所以固定一定的时间，来周期触发
		fcu_data_buffer.h2_data_buffer.h2_pressure_proportional_valve_front = 
		ad_transformed_to_pressure((u16)ad_mean_data[3], atd_conversion_accuracy, 1000);
		fcu_data_buffer.h2_data_buffer.h2_pressure_proportional_valve_rear =
		ad_transformed_to_pressure((u16)ad_mean_data[5], atd_conversion_accuracy, 100);

		fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid.is_enble_pid = 1;

		PID_position_mode_ex(&(fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid),
		&(fcu_data_buffer.h2_data_buffer.h2_pressure_proportional_valve_rear),
		&(fcu_data_buffer.h2_data_buffer.h2_pressure_target_value));

		fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pwm_dutyfactor +=  
		fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid.output_value_float;
		range_float(&(fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pwm_dutyfactor), 0, 10000);

		pwm_set_dutyfactor(pwm_channel_23, (u16)(fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pwm_dutyfactor)) ;

		//		fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid..pid_updata_time = system_time;	

		}    */
		//	test_ad_end = 	system_time_us -   test_ad_begin;
	}     
}
#pragma CODE_SEG DEFAULT






/****************************************************************/
//以下是ADC1的代码    hsp
/**************************************************************/


// 初始化atd1              
enum Error_code INIT_ATD1(void)
{
	//输入模拟量（0~5V之间的电压）
	if(atd1_input_mode == atdx_input_analog)
	{    
		ATD1CTL1_SRES = (Byte)atd1_conversion_accuracy;  //选用xx位模数转换

		//默认为开启快速清除，就是当读取结果寄存器的时候，对应的标志位就直接清
		ATD1CTL2 = 0x40;  //启动A/D转换,快速清零,禁止中断
		//	ATD0CTL2 = 0x42;  //启动A/D转换,快速清零,开启中断 

		//默认 0x80表示右对齐
		if(atd1_conversion_number == ATD1_CONVERSION_NUMBER_MAX)
		{       
			ATD1CTL3 = 0xC8 ; //注意了，转换16个通道，S8C, S4C, S2C, S1C寄存器写0
		}
		else
		{
			ATD1CTL3 = 0x80 | (atd1_conversion_number << 3);
		}


		//实际的ad频率 = 总线频率/ 2 /（PRS+1）
		ATD1CTL4 = 0x07;   //AD模块时钟频率，影响到ad测量一次的时间和准确度
	}
	//输入数字量（0或5v 的数字信号， 就是当做普通的io输入口）
	else if(atd1_input_mode == atdx_input_digital)
	{
		ATD1DIEN= 0x03;   //将AD00和AD01设置为数字输入通道
		DDR1AD1 = 0X00;   //设置AD00和AD01为输入 //和普通的io口类似
		//后续通过 PT01AD0 PT0AD0 PT1AD0 访问数据。
		/*** PT01AD0 - Port AD0 Data Register; 0x00000270 ***/
	}

	return Succeed;
}


//ad连续性配置,和初始化一样，配置一次
enum Error_code ATD1_set_continuous(void)
{
	Byte mult_temp = 0;
	Byte i =0;

	//ad采集电压 的 开始通道 + 通道的数量 > 8 则报错
	if(atd1_conversion_number + atd1_start_number  > ATD1_CONVERSION_NUMBER_MAX)
	{
		return ATDX_conversion_number_error;
	}

	if(atd1_conversion_is_continuous == atdx_continuous)
	{
		//判断是否开启多通道采集
		if(atd1_conversion_number == atdx_conversion_number_1)
		{
			mult_temp = 0;
		}
		else
		{
			mult_temp = 1;
		}

		//设定采集的开始通道 和 是否连续采集
		//注意了，在不连续的情况下。只有对ATD0CTL4 和 ATD0CTL5 写入的时候，才会开始新的一轮采集电压
		ATD1CTL5 = (atdx_continuous << 5) | (mult_temp << 4) | atd1_start_number;
	}

	return Succeed;
}



//ad1采集电压，需要循环调用，刷新数据
enum Error_code ATD1_capture(void)
{
	Byte mult_temp = 0;
	Byte i =0;

	//	Byte ad_number_temp = atd_start_number + i;
	Word ad_data_temp = 0;

	//ad采集电压 的 开始通道 + 通道的数量 > 8 则报错
	if(atd1_conversion_number + atd1_start_number  > ATD1_CONVERSION_NUMBER_MAX)
	{
		return ATDX_conversion_number_error;
	}

	if(atd1_conversion_is_continuous == atdx_discontinuous)
	{
		//判断是否开启多通道采集
		if(atd1_conversion_number == atdx_conversion_number_1)
		{
			mult_temp = 0;
		}
		else
		{
			mult_temp = 1;
		}

		//设定采集的开始通道 和 是否连续采集
		//注意了，在不连续的情况下。只有对ATD0CTL4 和 ATD0CTL5 写入的时候，才会开始新的一轮采集电压
		ATD1CTL5 = (mult_temp << 4) | atd1_start_number;
	}

	//判断采集完成的标志位
	while(!ATD1STAT0_SCF);

	//读取结果，注意了  开启 开启快速清除 之后，读取结果寄存器，便会自动清除标志位
	for(i=0; i< atd1_conversion_number; i++)
	{


		//结果寄存器，每次一轮采集 都是从ATD0DR0L开始储存。和 采集的开始通道 无关
		switch(i)
		{                 
		case 0:
			ad_data_temp = ATD1DR0;
			break;
		case 1:
			ad_data_temp = ATD1DR1;
			break;
		case 2:
			ad_data_temp = ATD1DR2;
			break;
		case 3:
			ad_data_temp = ATD1DR3;
			break;
		case 4:
			ad_data_temp = ATD1DR4;
			break;
		case 5:
			ad_data_temp = ATD1DR5;
			break;
		case 6:
			ad_data_temp = ATD1DR6;
			break;
		case 7:
			ad_data_temp = ATD1DR7;
			break;

		}

		atd1_original_data[atd1_start_number + i] = ad_data_temp;
	}

	return Succeed;
}

//ad1采集电压，10次平均值
enum Error_code ATD1_capture_mean(void)
{


	//新的取平均值的算法。
	int j = 0;

	ATD1_capture();
	for(j=atd1_start_number; j<atd1_start_number+atd1_conversion_number; j++)
	{
		atd1_mean_data[j] = ((atd1_mean_data[j] *7) +  (atd1_original_data[j] ) ) >>3;
	}    


	//叠加计数
	atd1_capture_number++;
	return Succeed;
}



//ad1的中断函数
#pragma CODE_SEG __NEAR_SEG NON_BANKED
interrupt void atd1_interrupt(void) 
{   

	int i = 0 ;
	int j = 0;
	u16 ad_data_temp = 0;

	EnableInterrupts;
	if(ATD1STAT0_SCF==1)
	{
		//	   test_ad_now =  system_time_us -  test_ad_last;
		//	    test_ad_last =   system_time_us;


		//test_ad_begin = system_time_us;
		//读取结果，注意了  开启 开启快速清除 之后，读取结果寄存器，便会自动清除标志位
		for(i=0; i< atd1_conversion_number; i++)     
		{
			//结果寄存器，每次一轮采集 都是从ATD0DR0L开始储存。和 采集的开始通道 无关
			switch(i)
			{
			case 0:
				ad_data_temp = ATD1DR0;
				break;
			case 1:
				ad_data_temp = ATD1DR1;
				break;
			case 2:
				ad_data_temp = ATD1DR2;
				break;
			case 3:
				ad_data_temp = ATD1DR3;
				break;
			case 4:
				ad_data_temp = ATD1DR4;
				break;
			case 5:
				ad_data_temp = ATD1DR5;
				break;
			case 6:
				ad_data_temp = ATD1DR6;
				break;
			case 7:
				ad_data_temp = ATD1DR7;
				break;

			}

			atd1_original_data[atd1_start_number + i] = ad_data_temp;
		}

	}     
}
#pragma CODE_SEG DEFAULT



//NTC温度传感器 计算
float atd_ntc_calculation(u16 da_data)   
{
	u16 TMPC_DATA;
	int TMPCun=0,TMPCun1,TMPCun2;
	float result = 0.0;

	TMPC_DATA = da_data;
	TMPCun1=0;                     
	TMPCun2=140;                    
	if(TMPC_DATA>=AD_Result[TMPCun1]) 
	{
		result = (float)Temp_Value[TMPCun1];
	}
	else if(TMPC_DATA<=AD_Result[TMPCun2]) 
	{
		result = (float)Temp_Value[TMPCun2];
	}
	else 
	{
		while(TMPCun1<TMPCun2-1)       
		{
			TMPCun = (TMPCun1+TMPCun2)>>1;    
			if(TMPC_DATA>AD_Result[TMPCun]) 
			{
				TMPCun2=TMPCun;     
			}
			else  
			{
				TMPCun1=TMPCun;   
			}
		}	
		result = (float)(Temp_Value[TMPCun1]);
		result = result + ((float)(AD_Result[TMPCun1] - TMPC_DATA)) / (AD_Result[TMPCun1] - AD_Result[TMPCun1+1]);
    
	}

	return result;
}

//4~20mA电流传感器 计算（200欧的电阻  4~20mA  0.8~4V）
float atd_electricity_calculation(u16 da_data, u16 range_data )
{
	u32 temp_u32 = da_data;
	float result = 0.0;

	range_u32(&temp_u32, 656, 3276);
	temp_u32 = (50 * temp_u32 - 32768) * range_data;
	result =  temp_u32 / 131072.0;   

	return result;
}
      
//0.5~4.5V电压传感器 计算
float atd_voltage_calculation_for_pressuer(u16 da_data, u16 range_data )
{
 	u32 temp_u32 = da_data;
	float result = 0.0;   
/*	
	range_u32(&temp_u32, 410, 3686); 
	temp_u32 = (temp_u32 * 5 - 2048) * range_data;
    result =  temp_u32 / 16384.0;
*/
    temp_u32 = (u32)da_data * range_data;
    result = temp_u32 / 4096.0;
   	return result; 
}



//电压传感器 计算
//ad 转化为 电堆电压
float atd_voltage_calculation_for_pile_voltage(u16 da_data, u16 range_data)
{
	float result = 0.0;
	result =  ((float)da_data) * 5000 / 4096 * range_data / 5000;
	return result;
}
//ad 转化为 电堆电流
float atd_voltage_calculation_for_pile_electricity(u16 da_data)
{
	float result = 0.0;
	result = ( ((float)da_data) * 5000 / 4096 - 2500) / 4;
	return result;
}
//ad 转化为 空气流量
float atd_voltage_calculation_for_air_rate_of_flow(u16 da_data)
{
	float temp_ad = 0.0;
	float result = 0.0;

	temp_ad = ((float)da_data) * 5 / 4096;
	if(temp_ad <= 1)
	{
		result = 0;
	}
	else
	{
		result = 163.8*temp_ad*temp_ad*temp_ad - 644.5*temp_ad*temp_ad + 1299.0*temp_ad - 837.1;
		if(result < 0)
		{
			result = 0;
		}
	}
	//y = 163.8x3 - 644.5x2 + 1299.x - 837.1			R2 = 0.999

	return result;
}

//ad 转化为 氢气浓度	
float atd_voltage_calculation_for_h2_concentration(u16 da_data)
{
	float temp_ad = ((float)da_data) * 5 / 4096;
    float result = 0.0;
    
    if(temp_ad<1)
    {
        result = 0;    
    }
    else if(temp_ad<4)
    {
        result = temp_ad - 1;    
    }
    else
    {
       result = (temp_ad-4)*2 + 3;
    }
    return result;
}
      
//ad待机检测，判断传感器是否正常
enum Error_code atd_wait_check()
{
	//温度传感器 462~3741 允许待机启动的 温度范围  -20~80  （0xE9D是-20，0x1CE是80）
	if(atd0_mean_data[0] >= 0xE9D || atd0_mean_data[0] <= 0x1CE )
	{
		return Water_temperature_frequency_outlet_atd_error1;    
	}
	if(atd0_mean_data[1] >= 0xE9D || atd0_mean_data[1] <= 0x1CE )
	{
		return Air_temperature_pile_outlet_atd_error1;           
	}
	if(atd0_mean_data[2] >= 0xE9D || atd0_mean_data[2] <= 0x1CE )
	{
		return Water_temperature_intercooler_outlet_atd_error1;           
	}
	if(atd0_mean_data[3] >= 0xE9D || atd0_mean_data[3] <= 0x1CE )
	{
		return Water_temperature_compressor_outlet_atd_error1;          
	}
	if(atd0_mean_data[4] >= 0xE9D || atd0_mean_data[4] <= 0x1CE )
	{
		return Water_temperature_pump_outlet_atd_error1;          
	}
/*	if(atd0_mean_data[5] >= 0xE9D || atd0_mean_data[5] <= 0x1CE )
	{
		return Water_temperature_pile_inlet_atd_error1;         
	}
	if(atd0_mean_data[6] >= 0xE9D || atd0_mean_data[6] <= 0x1CE )
	{
		return Water_temperature_pile_outlet_atd_error1;        
	}   */
	if(atd0_mean_data[7] >= 0xE9D || atd0_mean_data[7] <= 0x1CE )
	{
		return Water_temperature_pile_inlet_atd_error1;    
	} 
	if(atd1_mean_data[0] >= 0xE9D || atd1_mean_data[0] <= 0x1CE )
	{
		return Water_temperature_pile_outlet_atd_error1;    
	}
/*	if(atd1_mean_data[2] >= 0xE9D || atd1_mean_data[2] <= 0x1CE )
	{
		return H2_temperature_pile_inlet_atd_error1;    
	}   */
	if(atd1_mean_data[4] >= 0xE9D || atd1_mean_data[4] <= 0x1CE )
	{
		return Air_temperature_pile_inlet_atd_error1;     
	}
	if(atd1_mean_data[6] >= 0xE9D || atd1_mean_data[6] <= 0x1CE )
	{
		return Air_temperature_humidifier_front_atd_error1;     
	}

	//压力传感器，允许待机启动的  压力为0 就是410  允许误差±100，即为300~500
	if(atd0_mean_data[8] >= 500 || atd0_mean_data[8] <= 300 )
	{
		return Air_pressure_pile_inlet_atd_error1;      
	} 
	if(atd0_mean_data[9] >= 500 || atd0_mean_data[9] <= 300 )
	{
		return Air_pressure_pile_outlet_atd_error1;       
	}
/*	if(atd0_mean_data[10] >= 500 || atd0_mean_data[10] <= 300 )
	{
		return Air_pressure_pile_back_atd_error1;                     
	}    */
	//前氢压暂时不做判断
/*	if(atd0_mean_data[11] >= 500 || atd0_mean_data[11] <= 300 )
	{
		return H2_pressure_proportional_valve_front_atd_error1;                   
	}   */
/*	if(atd0_mean_data[12] >= 500 || atd0_mean_data[12] <= 100 )
	{
		return H2_pressure_proportional_valve_rear_atd_error1;                  
	}   */

	if(atd0_mean_data[14] >= 500 || atd0_mean_data[14] < 0 )
	{
		return H2_pressure_tail_outlet_atd_error1;                 
	}
	//这里电堆散热系统水压有点特殊，因为管路的问题，待机状态是有水的，由于高度问题，会有一点点的水压。一般为600（300~800）
	if(atd0_mean_data[15] >= 800 || atd0_mean_data[15] <= 300 )   
	{
		return Water_pressure_pile_outlet_atd_error1;                   
	}
	if(atd1_mean_data[1] >= 800 || atd1_mean_data[1] <= 300 )
	{
		return Water_pressure_pile_inlet_atd_error1;
	}
	if(atd1_mean_data[3] >= 500 || atd1_mean_data[3] < 0 )
	{
		return H2_pressure_pile_inlet_atd_error1;            
	} 
	if(atd1_mean_data[5] >= 500 || atd1_mean_data[5] <= 300 )
	{
		return Air_pressure_pile_back_atd_error1;    
	}     
	//这里三合一水泵的出口水压有点特殊，因为管路的问题，待机状态是有水的，由于高度问题，会有一点点的水压。一般为1830（880~980）
	if(atd1_mean_data[7] >= 800 || atd1_mean_data[7] <= 300 )
	{
		return Water_pressure_pump_outlet_atd_error1;       
	}

	//空气流量，待机默认为1V，即为819，误差50（即为770~870）
	if(atd0_mean_data[13] >= 970 || atd0_mean_data[13] <= 770 )
	{
		return Air_rate_of_flow_atd_error1;
	}
/*                                                            
	//电堆电压，待机默认为0，（0~400） 大约50V
	if(atd1_mean_data[2] >= 400 )
	{
		return Galvanic_pile_voltage_atd_error1;
	}

	//电堆电流，默认为0，但是ad范围是2.5V对应0点（因为可以测负电流），有因为有偏差，默认为2032（2000~2100）
	if(atd1_mean_data[4] >= 2100 || atd1_mean_data[4] <= 2000 )
	{
		return Galvanic_pile_electricity_atd_error1;
	}
*/
	return Succeed;
}


//ad待机检测，判断传感器是否正常 ,不带比例阀前氢压
enum Error_code atd_wait_check_ex()
{
	//温度传感器 462~3741 允许待机启动的 温度范围  -20~80  （0xE9D是-20，0x1CE是80）
	if(atd0_mean_data[0] >= 0xE9D || atd0_mean_data[0] <= 0x1CE )
	{
		return Water_temperature_frequency_outlet_atd_error1;    
	}
	if(atd0_mean_data[1] >= 0xE9D || atd0_mean_data[1] <= 0x1CE )
	{
		return Air_temperature_pile_outlet_atd_error1;           
	}
	if(atd0_mean_data[2] >= 0xE9D || atd0_mean_data[2] <= 0x1CE )
	{
		return Water_temperature_intercooler_outlet_atd_error1;           
	}
	if(atd0_mean_data[3] >= 0xE9D || atd0_mean_data[3] <= 0x1CE )
	{
		return Water_temperature_compressor_outlet_atd_error1;          
	}
	if(atd0_mean_data[4] >= 0xE9D || atd0_mean_data[4] <= 0x1CE )
	{
		return Water_temperature_pump_outlet_atd_error1;          
	}
/*	if(atd0_mean_data[5] >= 0xE9D || atd0_mean_data[5] <= 0x1CE )
	{
		return Water_temperature_pile_inlet_atd_error1;         
	}
	if(atd0_mean_data[6] >= 0xE9D || atd0_mean_data[6] <= 0x1CE )
	{
		return Water_temperature_pile_outlet_atd_error1;        
	}   */
	if(atd0_mean_data[7] >= 0xE9D || atd0_mean_data[7] <= 0x1CE )
	{
		return Water_temperature_pile_inlet_atd_error1;    
	} 
	if(atd1_mean_data[0] >= 0xE9D || atd1_mean_data[0] <= 0x1CE )
	{
		return Water_temperature_pile_outlet_atd_error1;    
	}
/*	if(atd1_mean_data[2] >= 0xE9D || atd1_mean_data[2] <= 0x1CE )
	{
		return H2_temperature_pile_inlet_atd_error1;    
	}   */
	if(atd1_mean_data[4] >= 0xE9D || atd1_mean_data[4] <= 0x1CE )
	{
		return Air_temperature_pile_inlet_atd_error1;     
	}
	if(atd1_mean_data[6] >= 0xE9D || atd1_mean_data[6] <= 0x1CE )
	{
		return Air_temperature_humidifier_front_atd_error1;     
	}

	//压力传感器，允许待机启动的  压力为0 就是410  允许误差±100，即为300~500
	if(atd0_mean_data[8] >= 500 || atd0_mean_data[8] <= 300 )
	{
		return Air_pressure_pile_inlet_atd_error1;      
	} 
	if(atd0_mean_data[9] >= 500 || atd0_mean_data[9] <= 300 )
	{
		return Air_pressure_pile_outlet_atd_error1;       
	}
/*	if(atd0_mean_data[10] >= 500 || atd0_mean_data[10] <= 300 )
	{
		return Air_pressure_pile_back_atd_error1;                     
	}     */
	//前氢压暂时不做判断
/*	if(atd0_mean_data[11] >= 500 || atd0_mean_data[11] <= 300 )
	{
		return H2_pressure_proportional_valve_front_atd_error1;                   
	}   */
/*	if(atd0_mean_data[12] >= 500 || atd0_mean_data[12] <= 100 )
	{
		return H2_pressure_proportional_valve_rear_atd_error1;                  
	}  */

	if(atd0_mean_data[14] >= 500 || atd0_mean_data[14] < 0 )
	{
		return H2_pressure_tail_outlet_atd_error1;                 
	}
	//这里电堆散热系统水压有点特殊，因为管路的问题，待机状态是有水的，由于高度问题，会有一点点的水压。一般为600（300~800）
	if(atd0_mean_data[15] >= 800 || atd0_mean_data[15] <= 300 )  
	{
		return Water_pressure_pile_outlet_atd_error1;                   
	}
	if(atd1_mean_data[1] >= 800 || atd1_mean_data[1] <= 300 )
	{
		return Water_pressure_pile_inlet_atd_error1;
	}
	if(atd1_mean_data[3] >= 500 || atd1_mean_data[3] < 0 )
	{
		return H2_pressure_pile_inlet_atd_error1;            
	}     
	if(atd1_mean_data[5] >= 500 || atd1_mean_data[5] <= 300 )
	{
		return Air_pressure_pile_back_atd_error1;    
	}  
	//这里三合一水泵的出口水压有点特殊，因为管路的问题，待机状态是有水的，由于高度问题，会有一点点的水压。一般为600（300~800）
	if(atd1_mean_data[7] >= 800 || atd1_mean_data[7] <= 300 )
	{
		return Water_pressure_pump_outlet_atd_error1;       
	}

	//空气流量，待机默认为1V，即为819，误差50（即为770~870）
	if(atd0_mean_data[13] >= 970 || atd0_mean_data[13] <= 770 )
	{
		return Air_rate_of_flow_atd_error1;
	}
/*                                                            
	//电堆电压，待机默认为0，（0~400） 大约50V
	if(atd1_mean_data[2] >= 400 )
	{
		return Galvanic_pile_voltage_atd_error1;
	}

	//电堆电流，默认为0，但是ad范围是2.5V对应0点（因为可以测负电流），有因为有偏差，默认为2032（2000~2100）
	if(atd1_mean_data[4] >= 2100 || atd1_mean_data[4] <= 2000 )
	{
		return Galvanic_pile_electricity_atd_error1;
	}
*/
	return Succeed;
}
