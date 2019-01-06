
#include "pit.h"

#include "freemaster.h"
#include "freemaster_example.h"
#include "control_manager.h"

//微秒的计时器。
u32 system_time_us = 0;

enum ISlock  freemaster_lock = unlock;



//test                       
u32 test_can_begin = 0;
u32 test_can_end = 0;
u32 test_can_last = 0;
u32 test_can_now = 0;
u32 test_can_receive = 0;
u32 test_can_send = 0;



//test
u32 test_pid_begin = 0;
u32 test_pid_end = 0;
u32 test_pid_last = 0;
u32 test_pid_now = 0;


//test

u32 over_pressure_alarm = 0;



//pit初始化
void init_PIT(void)
{
	PITMTLD0=249;			//为0通道8位计数器赋值
	//	PITMTLD1=31;			//为1通道8位计数器赋值
	PITMTLD1=63;		//	32M改为120M

	//	PITLD0=63999;			//为0通道16位计数器赋值   (249+1)*(63999+1) / 64M = 0.5秒
	PITLD0=9;		    	//为0通道16位计数器赋值   (63+1)*(9+1) / 64M = 0.01ms
	PITLD1=8878;		    	//为1通道16位计数器赋值   (63+1)*(888+1) / 64M = 10ms
	PITLD2=987;			    //为2通道16位计数器赋值   (63+1)*(987+1) / 64M = 1ms
    PITLD3=6327;			//为3通道16位计数器赋值   (249+1)*(63999+1) / 64M = 0.5秒
    PITLD4=9967;		    //为4通道16位计数器赋值   (63+1)*(9967+1) / 64M = 10ms
    PITLD5=2943;		    //为4通道16位计数器赋值   (63+1)*(2943+1) / 64M = 3ms

	//注意了，pit不同定时器的周期一定要错开，否则可能会同时触发，产生中断覆盖。

 /*
	PITMUX = 0x07;			//第0~1通道使用微计数器1, 其他通道使用微计数器0
	PITCE = 0x07;			//第0~1通道计数器工作 
	PITCFLMT = 0X80;		//使能周期中断定时器
	PITINTE = 0x07;			//第0~1通道定时器定时中断被使能
	*/
	
	PITMUX = 0x37;			//第0~2通道和4~5通道使用微计数器1, 其他通道使用微计数器0
	PITCE = 0x3F;			//第0~5通道计数器工作 
	PITCFLMT = 0X80;		//使能周期中断定时器
	PITINTE = 0x3F;			//第0~5通道定时器定时中断被使能
	
	
	//   PITINTE = 0x02;
	//   PITINTE = 0x01;		
}



//pit0中断	微秒的计时器。//定时器0.01ms触发一次
#pragma CODE_SEG __NEAR_SEG NON_BANKED
interrupt void PIT0_interrupt(void) 
{
	EnableInterrupts;
	if(PITTF_PTF0==1) {

		PITTF_PTF0=1;            
		system_time_us += 10;		//定时器0.01ms触发一次

		if(freemaster_lock == unlock)
		{
			freemaster_lock = lock;
			//注意了，freemaster使用了sci0， 232串口通信，这个通信是不能被其他中断打断的。
			//所以，必须放在pit的中断里面，然后按照最高优先级执行。
			FMSTR_Example_Poll();
			freemaster_lock = unlock;
		}

		if(system_time_us == 4294967290)		//2的32次方 = 4294967296
		{
			system_time_us = 0;

			//need pragrom
			//这里要清除所有程序中，相关的所有时间
		}

	}
}
#pragma CODE_SEG DEFAULT
                                      

//can通信管理函数
//主要负责把接收的can消息缓存，按某种顺序读取出来（目前按照顺序，后期优化按照优先级）
//然后按照一定的频率发送数据。
enum Error_code can_communication_control(void)
{
	enum Error_code error_code = Succeed;

	CAN_message RxMessage;	//can接受消息
	CAN_message TxMessage;	//can发送消息

	//	u32 test_test =  system_time_us;

	if(fcu_data_buffer.islock == unlock)
	{
		fcu_data_buffer.islock = lock;


		//解析can接受消息
		while(error_code == 0)
		{
			error_code = Common_list_moveout_data_from_head(&CAN_receive_message_list, 0, (char*)(&RxMessage), sizeof(CAN_message));
                                  
			if(error_code != 0)
			{
				;//不成功表示list没有数据。那么就不做处理。
			}
			else
			{                
				test_can_receive++;
				//通过接受的CAN消息，来更新数据。
		//		error_code = Can_communication_protocol_updata_receivev_can( &can_communication_protocol_total, &RxMessage);
				error_code = Can_communication_protocol2_updata_receivev_can( &can_communication_protocol2_total, &RxMessage);

				//	//不要经常打印
				//	if((system_time/1000)%10 == 0)
				//	{
				//		//打印接受的数据
				//		error_code = Control_Policy_printf_can_receivev_data( &control_policy_data_buffer, &RxMessage);
				//		if(error_code != Succeed)	{return error_code;}
				//	}

			}		
		}
		//前面解析can接受消息的时候，可能有错误
		if(error_code == NoData)
		{error_code = Succeed;}


		//封装和发送can消息	

		error_code = Can_communication_protocol2_can_encapsulation_and_send(&can_communication_protocol2_total, &TxMessage);
	//	error_code = Can_communication_protocol_can_encapsulation_and_send(&can_communication_protocol_total, &TxMessage);	

		//前面封装和发送can消息的时候，可能有错误
		if(error_code == NoData)
		{error_code = Succeed;}

		fcu_data_buffer.islock = unlock;
	}


	return error_code;
}




//pit1中断，can消息的定时解析和封装发送//定时器1ms触发一次
#pragma CODE_SEG __NEAR_SEG NON_BANKED
interrupt void PIT1_interrupt(void) 
{
	enum Error_code error_code = Succeed;
	EnableInterrupts;

	if(PITTF_PTF1==1)
	{

		PITTF_PTF1=1;    

		//		 test_can_now =  system_time_us - test_can_last;
		//		  test_can_last =  system_time_us;

		//		test_can_begin =   system_time_us;      
		error_code = can_communication_control();
		if(error_code != Succeed)	{printf("can_communication_control failed, error_code:%d \r\n", error_code);}
		//		 test_can_end =  system_time_us - test_can_begin;

	}
}
#pragma CODE_SEG DEFAULT




//pit2中断，pid算法。//定时器1ms触发一次
#pragma CODE_SEG __NEAR_SEG NON_BANKED
interrupt void PIT2_interrupt(void) 
{
	u32 temp_u32 = 0;
	float temp_float = 0;

	enum Error_code error_code = Succeed;
	EnableInterrupts;

	if(PITTF_PTF2==1)
	{

		PITTF_PTF2=1;    

		//	test_pid_begin =   system_time_us;
		//	test_pid_now =   system_time_us -   test_pid_last;
		//	test_pid_last =  system_time_us;
      
		//清除计数和时间
		atd0_capture_number_max =  atd0_capture_number;
		atd0_capture_number = 0;
		atd1_capture_number_max =  atd1_capture_number;
		atd1_capture_number = 0;                                                       

		//ad寄存器 转化 为实际数据

		//NTC传感器  AD 12个
		fcu_data_buffer.air_data_buffer.air_temperature_pile_outlet = atd_ntc_calculation(atd0_mean_data[2]);	
//	    fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_compressor_outlet = atd_ntc_calculation(atd0_mean_data[3]);
	    fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_pump_outlet = atd_ntc_calculation(atd0_mean_data[4]);
//		fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_inlet2 = atd_ntc_calculation(atd0_mean_data[5]);
//		fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_outlet2 = atd_ntc_calculation(atd0_mean_data[6]);	
		fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_outlet1 = atd_ntc_calculation(atd0_mean_data[7]);
		fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_inlet1 = atd_ntc_calculation(atd1_mean_data[0]);	
		fcu_data_buffer.h2_data_buffer.h2_temperature_tail_outlet = atd_ntc_calculation(atd1_mean_data[2]);		
		fcu_data_buffer.air_data_buffer.air_temperature_pile_inlet = atd_ntc_calculation(atd1_mean_data[4]);
		fcu_data_buffer.air_data_buffer.air_temperature_humidifier_front = atd_ntc_calculation(atd1_mean_data[6]);		
		

		//电压0~5V传感器
    	fcu_data_buffer.air_data_buffer.air_pressure_pile_inlet = atd_voltage_calculation_for_pressuer(atd0_mean_data[8], 160);		
		fcu_data_buffer.air_data_buffer.air_pressure_pile_outlet = atd_voltage_calculation_for_pressuer(atd0_mean_data[9], 160);		
		fcu_data_buffer.air_data_buffer.air_pressure_pile_back = atd_voltage_calculation_for_pressuer(atd0_mean_data[10], 160);
    	fcu_data_buffer.h2_data_buffer.h2_pressure_proportional_valve_front = atd_voltage_calculation_for_pressuer(atd0_mean_data[11], 1000);
		fcu_data_buffer.h2_data_buffer.h2_pressure_proportional_valve_rear = atd_voltage_calculation_for_pressuer(atd0_mean_data[12], 160);
		fcu_data_buffer.water_for_pile_data_buffer.water_pressure_pile_inlet1 = atd_voltage_calculation_for_pressuer(atd0_mean_data[15], 160);	
		fcu_data_buffer.water_for_pile_data_buffer.water_pressure_pile_outlet1 = atd_voltage_calculation_for_pressuer(atd1_mean_data[1], 160);		
		fcu_data_buffer.h2_data_buffer.h2_pressure_pile_inlet = atd_voltage_calculation_for_pressuer(atd1_mean_data[3], 160);	
		fcu_data_buffer.h2_data_buffer.h2_pressure_tail_outlet = atd_voltage_calculation_for_pressuer(atd1_mean_data[5], 160);	
	    fcu_data_buffer.water_for_compressor_data_bufferr.water_pressure_pump_outlet = atd_voltage_calculation_for_pressuer(atd1_mean_data[7], 160);

		//电压传感器
		fcu_data_buffer.air_data_buffer.air_rate_of_flow = atd_voltage_calculation_for_air_rate_of_flow(atd0_mean_data[13]-10);
		fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_voltage = atd_voltage_calculation_for_pile_voltage(atd0_mean_data[0], 500);
		fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_electricity = atd_voltage_calculation_for_pile_electricity(atd0_mean_data[1]) -2;
        fcu_data_buffer.h2_data_buffer.h2_concentration = atd_voltage_calculation_for_h2_concentration(atd0_mean_data[3]);

		//pid调整氢压的  真实目标值。 加上偏移量之后的
		fcu_data_buffer.h2_data_buffer.h2_pressure_real_target_value
		 =	fcu_data_buffer.h2_data_buffer.h2_pressure_target_value + fcu_data_buffer.h2_data_buffer.h2_pressure_advance_current_value; 

		//重置最大最小值
		if(fcu_data_buffer.h2_data_buffer.h2_pressure_fluctuate_reset == 1)
		{
			fcu_data_buffer.h2_data_buffer.h2_pressure_fluctuate_last_max = 
				fcu_data_buffer.h2_data_buffer.h2_pressure_fluctuate_current_max;
			fcu_data_buffer.h2_data_buffer.h2_pressure_fluctuate_last_min = 
				fcu_data_buffer.h2_data_buffer.h2_pressure_fluctuate_current_min;
			fcu_data_buffer.h2_data_buffer.h2_pressure_fluctuate_current_max = 0;
			fcu_data_buffer.h2_data_buffer.h2_pressure_fluctuate_current_min = 0; 
			fcu_data_buffer.h2_data_buffer.h2_pressure_fluctuate_reset = 0;   
		}
		//获取最大最小值
		if(fcu_data_buffer.h2_data_buffer.h2_pressure_pile_inlet 
			- fcu_data_buffer.h2_data_buffer.h2_pressure_target_value
			> fcu_data_buffer.h2_data_buffer.h2_pressure_fluctuate_current_max)
		{
			fcu_data_buffer.h2_data_buffer.h2_pressure_fluctuate_current_max =  
				fcu_data_buffer.h2_data_buffer.h2_pressure_pile_inlet 
				- fcu_data_buffer.h2_data_buffer.h2_pressure_target_value;
		}

		if(fcu_data_buffer.h2_data_buffer.h2_pressure_pile_inlet 
			- fcu_data_buffer.h2_data_buffer.h2_pressure_target_value
			< fcu_data_buffer.h2_data_buffer.h2_pressure_fluctuate_current_min)
		{
			fcu_data_buffer.h2_data_buffer.h2_pressure_fluctuate_current_min =  
				fcu_data_buffer.h2_data_buffer.h2_pressure_pile_inlet 
				- fcu_data_buffer.h2_data_buffer.h2_pressure_target_value;
		} 	
/*		
		//过压保护，当氢压超出100，关闭比例阀。     缺点瞬间关闭比例阀，会导致过降
		if(fcu_data_buffer.h2_data_buffer.h2_pressure_proportional_valve_rear >= 130 ||
			fcu_data_buffer.h2_data_buffer.h2_pressure_pile_inlet >= 100 && system_time >= 1000) 
		{
                //直接跳保护

                //关闭氢气入口阀，调整开关频率，再把氢气尾排阀常开，防止急停之后氢压过高
				fcu_data_buffer.h2_data_buffer.h2_inlet_valve = 0;
				fcu_data_buffer.h2_data_buffer.h2_outlet_valve_open_time = 500;
				fcu_data_buffer.h2_data_buffer.h2_outlet_valve_close_time = 1000;
				fcu_data_buffer.h2_data_buffer.h2_is_enable_outlet_valve = 1;
                //关闭比例阀的自动控制
				fcu_data_buffer.h2_data_buffer.h2_pid_mode = 2;
				fcu_data_buffer.h2_data_buffer.h2_pressure_advance_set_value = 0;
				fcu_data_buffer.h2_data_buffer.h2_pressure_pid2_advance_time = 200;
				fcu_data_buffer.h2_data_buffer.h2_pressure_target_value = 50;
				fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid1.is_enble_pid = 0;
				fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid2.is_enble_pid = 0;
				fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pwm_dutyfactor = 0;
                //关闭氢气循环泵
				fcu_data_buffer.h2_data_buffer.h2_circulating_pump_enble = 1;
				fcu_data_buffer.h2_data_buffer.h2_circulating_pump_enable_pump = 0;
                //关闭空气排水阀和空压机pid使能
                fcu_data_buffer.air_data_buffer.air_is_enable_outlet_valve = 0;
				fcu_data_buffer.air_data_buffer.air_compressor_enable = 0;
				fcu_data_buffer.air_data_buffer.air_compressor_speed_pid.is_enble_pid = 0;
				fcu_data_buffer.air_data_buffer.air_rate_of_flow_target = 0;
				fcu_data_buffer.air_data_buffer.air_compressor_speed_setpoint = 20000;
				
				//关闭电堆散热系统的的水泵和风扇pid使能
				fcu_data_buffer.water_for_pile_data_buffer.water_temperature_fan_pid1.is_enble_pid = 0;
				fcu_data_buffer.water_for_pile_data_buffer.water_temperature_fan_pid2.is_enble_pid = 0;
				fcu_data_buffer.water_for_pile_data_buffer.water_pump_pwm_dutyfactor1 = 0;
				fcu_data_buffer.water_for_pile_data_buffer.water_fan_pwm_dutyfactor1 = 0;
				fcu_data_buffer.water_for_pile_data_buffer.water_pump_pwm_dutyfactor2 = 0;
				fcu_data_buffer.water_for_pile_data_buffer.water_fan_pwm_dutyfactor2 = 0;
				//关闭三合一散热系统的水泵和风扇pid使能
				fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_fan_pid.is_enble_pid = 0;
				fcu_data_buffer.water_for_compressor_data_bufferr.water_pump_pwm_dutyfactor = 0;
				fcu_data_buffer.water_for_compressor_data_bufferr.water_fan_pwm_dutyfactor = 0;

                //关闭电堆发电系统的主输出继电器和小电阻负载的继电器
				fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_is_enble_output = 0;
				fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_is_enble_load_resistance = 0;
			
			control_policy_total_manager.working_control_mode = working_control_fault_wait;
	    	control_policy_total_manager.working_status_mode = working_status_error;
	    	control_policy_total_manager.working_alarm_mode = one_level_fault;
	    	control_policy_total_manager.working_FCU_error_code = H2_pressure_proportional_valve_rear_over_error1 ;	//比例阀后氢压  过压（一级故障）
	    	control_policy_total_manager.working_FCU_error_control_mode = working_control_wait;
	    	control_policy_total_manager.working_error_count++;
	    	control_policy_total_manager.fcu_updata_event_time = system_time;       
		}
*/		

		//pid控制算法
		//pid控制。
		//注意了。pid算法需要很高的实时性，所以每次ad采样完成之后，就要立即进行pid算法控制，并且以较高的中断优先级2
		//注意了。pid算法需要很高的稳定性，所以固定一定的时间，来周期触发
		//20181212注意了，45kw台架氢气循环泵转速开到3000，此时比例阀后氢压和入堆氢压相差20kpa。
		//因此，为了保持入堆氢压的稳定，使用入堆氢压来参与pid运算。
		if(fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid1.is_enble_pid == 1
			&& fcu_data_buffer.h2_data_buffer.h2_pid_mode == 1)
		{
			PID_position_mode_ex(&(fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid1),
				fcu_data_buffer.h2_data_buffer.h2_pressure_pile_inlet,
				fcu_data_buffer.h2_data_buffer.h2_pressure_target_value + fcu_data_buffer.h2_data_buffer.h2_pressure_advance_current_value);

			fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pwm_dutyfactor +=  
				fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid1.output_value_float;


		}
		if(fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid2.is_enble_pid == 1
			&& fcu_data_buffer.h2_data_buffer.h2_pid_mode == 2)
		{
			PID_position_mode_ex(&(fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid2),
				fcu_data_buffer.h2_data_buffer.h2_pressure_pile_inlet,
				fcu_data_buffer.h2_data_buffer.h2_pressure_target_value + fcu_data_buffer.h2_data_buffer.h2_pressure_advance_current_value);

			fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pwm_dutyfactor +=  
				fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid2.output_value_float;
		}


		//比例阀限定范围，最小值不能为0
		//20181211注意了：比例阀的控制修改方案，去掉比例阀的控制器，直接驱动阀体，pwm6400hz改为pwm900hz输出
		//在初始化的时候，900hz不好配置。于是使用800hz。
		//在实际操作过程中，前氢压500kpa时，比例阀5000以下都是关闭的，为了响应速度，将比例阀的pwm占空比的可调范围改为4000~10000
		range_float(&(fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pwm_dutyfactor), 4000, 10000); 

		//比例阀的控制，直接放到pit2里面去，增加响应速度。
		pwm_set_dutyfactor(pwm_channel_67,(u16)(fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pwm_dutyfactor)) ;


		// test_pid_end =  system_time_us -  test_pid_begin;
	}
}
#pragma CODE_SEG DEFAULT

       /*
//modbus_232 通信管理函数
//主要负责把接收的232消息缓存，按某种顺序读取出来（目前按照顺序，后期优化按照优先级）
//然后按照一定的频率发送数据。
enum Error_code modbus_232_communication_control(void)
{
	enum Error_code error_code = Succeed;
	
	struct Modbus_Data_Buffer modbus_receive_data_buffer;
	struct Modbus_Data_Buffer modbus_send_data_buffer;
	
	struct Modbus_Data_Buffer * p_modbus_receive_data_buffer = &modbus_receive_data_buffer;
	struct Modbus_Data_Buffer * p_modbus_send_data_buffer = &modbus_send_data_buffer;
	
   if(fcu_modbus_tatal_manager_data.islock == unlock)
	{
		fcu_modbus_tatal_manager_data.islock = lock;


		error_code = Common_list_moveout_data_from_head(&Modbus1_receive_message_list1, 0, (char*)p_modbus_receive_data_buffer, sizeof(struct Modbus_Data_Buffer));
		if(error_code != 0)
		{
			
		}
		else
		{
	         
			error_code = FCU_modbus_tatal_manager_data_analysis(p_modbus_receive_data_buffer ,&fcu_data_buffer,&control_policy_total_manager);
			if(error_code != Succeed)	{printf("failed, error_code = %d",error_code);}
		}
		error_code = Succeed;
		
		
       
		error_code = FCU_modbus_tatal_manager_data_encapsulation(&fcu_modbus_tatal_manager_data, p_modbus_send_data_buffer);
		if(error_code == Succeed)
		{
		
	     
			error_code = ontime_modbus_232_send_data(p_modbus_send_data_buffer);
			if(error_code != Succeed)	{return error_code;}
			
		} 
			
		
		error_code = Succeed;
	 fcu_modbus_tatal_manager_data.islock = unlock;
	 
	 
	}
	
	return error_code;
}

        */


//pit3中断，pid算法。//定时器0.5s触发一次
#pragma CODE_SEG __NEAR_SEG NON_BANKED
interrupt void PIT3_interrupt(void)
{
  enum Error_code error_code = Succeed;
	EnableInterrupts;
 
	if(PITTF_PTF3==1)
	{

		PITTF_PTF3=1;    
		 
	  //暂时不开启上位机监视系统     
//		error_code = modbus_232_communication_control();
	//	if(error_code != Succeed)	{printf("modbus_communication_control failed, error_code:%d \r\n", error_code);}
		//		 test_can_end =  system_time_us - test_can_begin;

	}
}
#pragma CODE_SEG DEFAULT

float  air_compressor_speed_setpoint_temp = 0;

//pit4中断，pid算法。//定时器2ms触发一次
#pragma CODE_SEG __NEAR_SEG NON_BANKED
interrupt void PIT4_interrupt(void)
{
    enum Error_code error_code = Succeed;
    //这里使用静态局部变量，作用域只在pid4里面可以使用，但是生命周期永久。
    //static float  air_compressor_speed_setpoint_temp = 0;
	EnableInterrupts;
 
	if(PITTF_PTF4==1)
	{

		PITTF_PTF4=1;    
		 
        if(fcu_data_buffer.air_data_buffer.air_compressor_speed_pid.is_enble_pid == 1 
     /*   && system_time -  fcu_data_buffer.air_data_buffer.air_compressor_speed_pid.pid_updata_time >= 
		    	fcu_data_buffer.air_data_buffer.air_compressor_speed_pid.pid_over_time */)
        {
             PID_position_mode_ex(&(fcu_data_buffer.air_data_buffer.air_compressor_speed_pid), 
				fcu_data_buffer.air_data_buffer.air_rate_of_flow,
				fcu_data_buffer.air_data_buffer.air_rate_of_flow_target) ;

    			fcu_data_buffer.air_data_buffer.air_compressor_speed_pid.pid_updata_time = system_time;
      
			air_compressor_speed_setpoint_temp = fcu_data_buffer.air_data_buffer.air_compressor_speed_setpoint + 
				fcu_data_buffer.air_data_buffer.air_compressor_speed_pid.output_value_float; 

			//空压机转速限定范围，20000~70000
			range_float(&(air_compressor_speed_setpoint_temp), 20000, 70000);
			fcu_data_buffer.air_data_buffer.air_compressor_speed_setpoint = air_compressor_speed_setpoint_temp;
			  
        }
	}
}
#pragma CODE_SEG DEFAULT


//pit5中断，can消息的定时解析和封装发送//定时器1ms触发一次
#pragma CODE_SEG __NEAR_SEG NON_BANKED
interrupt void PIT5_interrupt(void) 
{
	enum Error_code error_code = Succeed;
	EnableInterrupts;

	if(PITTF_PTF5==1)
	{

		PITTF_PTF5=1;    
  
		error_code = can_communication_control_vms_shanghai();


	}
}
#pragma CODE_SEG DEFAULT


//上海强检  can通信管理函数
//主要负责把接收的can消息缓存，按某种顺序读取出来（目前按照顺序，后期优化按照优先级）
//然后按照一定的频率发送数据。
enum Error_code can_communication_control_vms_shanghai(void)
{
	enum Error_code error_code = Succeed;

	CAN_message RxMessage;	//can接受消息
	CAN_message TxMessage;	//can发送消息

	//	u32 test_test =  system_time_us;

	if(fcu_data_buffer.islock == unlock)
	{
		fcu_data_buffer.islock = lock;


		//解析can接受消息
		while(error_code == 0)
		{
			error_code = Common_list_moveout_data_from_head(&CAN_receive_message_list_vms_shanghai, 0, (char*)(&RxMessage), sizeof(CAN_message));
                                  
			if(error_code != 0)
			{
				;//不成功表示list没有数据。那么就不做处理。
			}
			else
			{                
				test_can_receive++;
				//通过接受的CAN消息，来更新数据。
				error_code = Can_communication_protocol_vms_shanghai_updata_receivev_can( &can_communication_protocol_vms_shanghai_total, &RxMessage);
			}		
		}
		//前面解析can接受消息的时候，可能有错误
		if(error_code == NoData)
		{error_code = Succeed;}


		//封装和发送can消息	    
		error_code = Can_communication_protocol_vms_shanghai_can_encapsulation_and_send(&can_communication_protocol_vms_shanghai_total, &TxMessage);

		//前面封装和发送can消息的时候，可能有错误
		if(error_code == NoData)
		{error_code = Succeed;}

		fcu_data_buffer.islock = unlock;
	}


	return error_code;
}



//延时函数，单位us，利用时间差
void pit_delay_us(u32 delay_time)
{
	u32 time_temp = system_time_us;
	while(system_time_us - time_temp  <  delay_time)
	{}
}
