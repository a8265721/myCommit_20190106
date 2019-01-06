/*---------------------------------------------------------*/
/************************************************************
飞翔科技MC9S12XS128汽车电子综合开发平台 
E-mail:bhfengchong@gmail.com
2008f.d@163.com
淘宝店：http://fxfreefly.taobao.com
http://fxfreefly2.taobao.com
************************************************************/
/*---------------------------------------------------------*/
#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

//#include "stdio.h"
#include "pll.h"
#include"data_buff.h"
#include "sci.h"                                        
//#include "key.h"
#include "led.h"                
#include "error_system.h"                   

#include "pwm.h"
#include "atd.h"
#include "ect.h"
#include "interrupt.h"
//#include "rti.h"
//#include "spi.h"
//#include "8BIT_LED_Segment_Displays.h"
#include "can.h"
#include "pit.h"

#include "freemaster.h"
#include "freemaster_example.h"

#include "pid.h"
#include "custom_math.h"
#include "control_manager.h"  

//#include "modbus_communication_system.h"
//#include "modbus_communication_protocol.h"

#include "cop.h"

//#define LED_ON 0                           
//#define LED_OFF 1

/*
u32 system_time_first = 0;
u32 system_time_second = 0;
u32 system_time_difference = 0;
*/
/*
u32 system_time_ad = 0;
u32 system_time_outlet = 0;
u32 outlet_open_time = 500;
u32 outlet_close_time = 10000;
*/
enum Error_code error_code_main;
u32     control_manager_refresh_system_time;
/*
float H2_pressure_voltage1 = 0;    
float H2_pressure_value1 = 0;    

float H2_pressure_voltage2 = 0;    
float H2_pressure_value2 = 0;    

float H2_pressure_target_value  = 0;

u32 H2_inlet_valve = 1;
u32 H2_outlet_valve = 1;

u32 zzz_temop0 = 0;
u32 zzz_temop1 = 0;
u32 zzz_temop2 = 0;
u32 zzz_temop3 = 0;
u32 zzz_temop4 = 0;

//u8 is_enble_pid = 0;
//u8 is_enble_outlet = 0;
*/

/*
u32  advance_time = 0;//1500;
float advance_value = 0;//10;

//u32  pid1_time = 100;

u8  huli_test_enable = 0;
float huli_test_max = 0;
float huli_test_min = 0;
*/


//PID water_pid;
//float	water_temperature_target_value = 55;			//电堆入口水温 目标值


/*************************************************************/
/*                         主函数                            */
/*************************************************************/
void main(void) 
{

	u32 time_temp = 0;

	int arr[4] = {111, 222, 333, 444};
	u32 brr[4] = {111111, 222222, 333333, 444444};
	unsigned char * p = (unsigned char*)brr;

	u32 temp32 = 1234567898;
	int i = 0;

	u32 time_temp1 =0;
	u32 time_temp2 =0;    
	
	float  water_temperature_for_compressor_max = 0;

	DisableInterrupts; 

    //中断优先级设置, 
	init_interruput_priorty_set();	

	//fcu数据缓存数据初始化
	FCU_data_buffer_init();
	
	//pcu主控的管理初始化
	Control_Policy_Total_Manager_init(&control_policy_total_manager);

	//can通信协议汇总 初始化
	Can_communication_protocol2_init(&can_communication_protocol2_total);
	//初始化链表，（空链表）
	Common_list_init(& CAN_receive_message_list );
	
	//上海强检  //can通信协议汇总 初始化
	Can_communication_protocol_vms_shanghai_init(&can_communication_protocol_vms_shanghai_total);
	//上海强检  //初始化链表，（空链表）
	Common_list_init(& CAN_receive_message_list_vms_shanghai );	
	
			
	//modbus_232通信协议结构体的初始化
//	FCU_modbus_tatal_manager_data_init(&fcu_modbus_tatal_manager_data);
	//modbus发送 接收帧以及 databuf帧的初始化
//	Modbus1_Init_ex();
	INIT_PLL();
	INIT_SCI0();     
//	INIT_SCI1();      

	INIT_LED();     
//	INIT_KEY();
  
	INIT_ATD0();
	//ad连续性配置,和初始化一样，配置一次
	ATD0_set_continuous();

	INIT_ATD1();
	//ad连续性配置,和初始化一样，配置一次
	ATD1_set_continuous();

	init_pwm_hybrids();

	ect_init_mdc();

	INIT_CAN0();
	INIT_CAN1();
	INIT_CAN2();
	init_PIT();
	
	// 初始化看门狗                     
	INIT_COP();

	// Initialisation of example application
	FMSTR_Example_Init();


	EnableInterrupts;               

  
	for(;;)
	{     
	    _FEED_COP();  //喂狗函数
	    /*                
		  if(freemaster_lock == unlock)
		  {
		  freemaster_lock = lock;
		  //注意了，freemaster使用了sci0， 232串口通信，这个通信是不能被其他中断打断的。
		  //所以，必须放在pit的中断里面，然后按照最高优先级执行。
		  FMSTR_Example_Poll();
		  freemaster_lock = unlock;
		  }
		  */

		//电堆水路的 入堆水温pid控制，2个电堆水路合并为一个了，因此控制模块减半，但是目前风扇还是2组。
	/*	if(fcu_data_buffer.water_for_pile_data_buffer.water_temperature_fan_pid1.is_enble_pid == 1 &&
		    fcu_data_buffer.water_for_pile_data_buffer.water_temperature_fan_pid2.is_enble_pid == 1 &&
			system_time -  fcu_data_buffer.water_for_pile_data_buffer.water_temperature_fan_pid1.pid_updata_time >= 
		    	fcu_data_buffer.water_for_pile_data_buffer.water_temperature_fan_pid1.pid_over_time  && 
			system_time -  fcu_data_buffer.water_for_pile_data_buffer.water_temperature_fan_pid2.pid_updata_time >= 
		    	fcu_data_buffer.water_for_pile_data_buffer.water_temperature_fan_pid2.pid_over_time)  */
		if(fcu_data_buffer.water_for_pile_data_buffer.water_temperature_fan_pid1.is_enble_pid == 1 &&
			system_time -  fcu_data_buffer.water_for_pile_data_buffer.water_temperature_fan_pid1.pid_updata_time >= 
		    	fcu_data_buffer.water_for_pile_data_buffer.water_temperature_fan_pid1.pid_over_time  )    	
		{
	    	//电堆风扇pwm控制  水温pid1控制
			PID_position_mode_ex(&(fcu_data_buffer.water_for_pile_data_buffer.water_temperature_fan_pid1), 
				fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_inlet1,
				fcu_data_buffer.water_for_pile_data_buffer.water_temperature_target_value1) ;

			fcu_data_buffer.water_for_pile_data_buffer.water_fan_pwm_dutyfactor1 -= 
				fcu_data_buffer.water_for_pile_data_buffer.water_temperature_fan_pid1.output_value_float; 

			//电堆风扇pwm限定范围，最小值不能为0，风扇pwm90%以上，就没必要了，在100%时风扇会停机
			range_float(&(fcu_data_buffer.water_for_pile_data_buffer.water_fan_pwm_dutyfactor1), 0, 9000);    

			fcu_data_buffer.water_for_pile_data_buffer.water_temperature_fan_pid1.pid_updata_time =  system_time;  
             
			//目前，pwm1和pwm2都是风扇，水路合并的时候，水泵只剩一个了，但是风扇还有2组，由2个pwm控制。
			//其实是控制同一个电堆水路，因此自动控制的时候。都使用1号风扇的pwm来控制即可。 
			fcu_data_buffer.water_for_pile_data_buffer.water_fan_pwm_dutyfactor2 = 
				fcu_data_buffer.water_for_pile_data_buffer.water_fan_pwm_dutyfactor1;
			     /*
            //电堆风扇pwm控制  水温pid2控制
            PID_position_mode_ex(&(fcu_data_buffer.water_for_pile_data_buffer.water_temperature_fan_pid2), 
				fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_inlet2,
				fcu_data_buffer.water_for_pile_data_buffer.water_temperature_target_value2) ;

			fcu_data_buffer.water_for_pile_data_buffer.water_fan_pwm_dutyfactor2 -= 
				fcu_data_buffer.water_for_pile_data_buffer.water_temperature_fan_pid2.output_value_float; 

			//电堆风扇pwm限定范围，最小值不能为0，风扇pwm90%以上，就没必要了，在100%时风扇会停机
			range_float(&(fcu_data_buffer.water_for_pile_data_buffer.water_fan_pwm_dutyfactor2), 0, 9000); 
 

			fcu_data_buffer.water_for_pile_data_buffer.water_temperature_fan_pid2.pid_updata_time =  system_time;  
			    */

			//电堆水泵pwm控制  水的温差来控制水泵。
			//实测，转速不稳，温度也不稳。控制不了。
			//所以高温时开到最大。
	/*		if(fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_outlet1 - 
				fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_inlet1 >9)
			{
				fcu_data_buffer.water_for_pile_data_buffer.water_pump_pwm_dutyfactor1 = 9500;
			}
			else if(fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_outlet1 - 
				fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_inlet1 >8)
			{
				fcu_data_buffer.water_for_pile_data_buffer.water_pump_pwm_dutyfactor1 = 9000;
			}
			else if(fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_outlet1 - 
				fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_inlet1 >7)
			{
				fcu_data_buffer.water_for_pile_data_buffer.water_pump_pwm_dutyfactor1 = 8500;
			}
			else if(fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_outlet1 - 
				fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_inlet1 >6)
			{
				fcu_data_buffer.water_for_pile_data_buffer.water_pump_pwm_dutyfactor1 = 8000;
			}
			else if(fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_outlet1 - 
				fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_inlet1 >5)
			{
				fcu_data_buffer.water_for_pile_data_buffer.water_pump_pwm_dutyfactor1 = 7500;
			}
			else if(fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_outlet1 - 
				fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_inlet1 >4)
			{
				fcu_data_buffer.water_for_pile_data_buffer.water_pump_pwm_dutyfactor1 = 7000;
			}
			else 
			{
				fcu_data_buffer.water_for_pile_data_buffer.water_pump_pwm_dutyfactor1 = 6500;
			}
	*/	
	    if(fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_inlet1 >70)
			{
				fcu_data_buffer.water_for_pile_data_buffer.water_pump_pwm_dutyfactor1 = 9500;
			}
			else if(fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_inlet1 >68)
			{
				fcu_data_buffer.water_for_pile_data_buffer.water_pump_pwm_dutyfactor1 = 9000;
			}
			else if(fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_inlet1 >65)
			{
				fcu_data_buffer.water_for_pile_data_buffer.water_pump_pwm_dutyfactor1 = 8500;
			}
			else if(fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_inlet1 >62)
			{
				fcu_data_buffer.water_for_pile_data_buffer.water_pump_pwm_dutyfactor1 = 8000;
			}
			else if(fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_inlet1 >60)
			{
				fcu_data_buffer.water_for_pile_data_buffer.water_pump_pwm_dutyfactor1 = 7500;
			}
			else if(fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_inlet1 >58)
			{
				fcu_data_buffer.water_for_pile_data_buffer.water_pump_pwm_dutyfactor1 = 7000;
			}
			else 
			{
				fcu_data_buffer.water_for_pile_data_buffer.water_pump_pwm_dutyfactor1 = 6500;
			}	   
		}


        //三合一水路的 水温pid控制，水路的所有温度传感器和空气路的中冷器后空温，这些取最大值，然后以此来做控制，要求控温60度。
		if(fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_fan_pid.is_enble_pid == 1 &&
			system_time -  fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_fan_pid.pid_updata_time >= 
		    	fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_fan_pid.pid_over_time  )    	
		{
		    //三合一水路的所有温度传感器和空气路的中冷器后空温，这些取最大值，
            water_temperature_for_compressor_max = fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_compressor_outlet;          
            if(water_temperature_for_compressor_max < fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_pump_outlet)
            {
               water_temperature_for_compressor_max = fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_pump_outlet; 
            }
            if(water_temperature_for_compressor_max < fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_frequency_outlet)
            {
               water_temperature_for_compressor_max = fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_frequency_outlet; 
            }
            if(water_temperature_for_compressor_max < fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_intercooler_outlet)
            {
               water_temperature_for_compressor_max = fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_intercooler_outlet; 
            }
            if(water_temperature_for_compressor_max < fcu_data_buffer.air_data_buffer.air_temperature_humidifier_front)
            {
               water_temperature_for_compressor_max = fcu_data_buffer.air_data_buffer.air_temperature_humidifier_front; 
            }
           //三合一风扇的控制 
           PID_position_mode_ex(&(fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_fan_pid), 
				water_temperature_for_compressor_max,
				fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_target_value) ;

			fcu_data_buffer.water_for_compressor_data_bufferr.water_fan_pwm_dutyfactor -= 
				fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_fan_pid.output_value_float; 

			//三合一风扇pwm限定范围，最小值不能为0
			range_float(&(fcu_data_buffer.water_for_compressor_data_bufferr.water_fan_pwm_dutyfactor), 0, 8000); 
 
            //三合一水泵的控制
            if(water_temperature_for_compressor_max > 50)
			{
				fcu_data_buffer.water_for_compressor_data_bufferr.water_pump_pwm_dutyfactor = 9000;
			}
			else if(water_temperature_for_compressor_max > 45 )
			{
				fcu_data_buffer.water_for_compressor_data_bufferr.water_pump_pwm_dutyfactor = 8000;
			}
			else if(water_temperature_for_compressor_max > 40 )
			{
				fcu_data_buffer.water_for_compressor_data_bufferr.water_pump_pwm_dutyfactor = 7000;
			}
			else if(water_temperature_for_compressor_max > 35 )
			{
				fcu_data_buffer.water_for_compressor_data_bufferr.water_pump_pwm_dutyfactor = 6000;
			}
			else if(water_temperature_for_compressor_max > 30 )
			{
				fcu_data_buffer.water_for_compressor_data_bufferr.water_pump_pwm_dutyfactor = 5000;
			}
			else 
			{
				fcu_data_buffer.water_for_compressor_data_bufferr.water_pump_pwm_dutyfactor = 4000;
			} 
        }
        
		test_huli2++;
		//		PORTB_PB0 =  (u8)H2_inlet_valve ;
		//    PORTB_PB1 =  (u8)H2_outlet_valve ;           

		//ad手动采集，无线循环采集电压
		//    pit_delay_us(1000);
		error_code_main = 	ATD0_capture_mean();
		error_code_main = 	ATD1_capture_mean();             


        //控制系统的控制算法
		if(system_time - control_manager_refresh_system_time > FCU_SYSTEM_CHANGE_MODE_DELAY_100MS)
		{

		//氢气尾排自动控制
		if(fcu_data_buffer.h2_data_buffer.h2_is_enable_outlet_valve == 2)
		{
		    //自动控制氢气pid2的时间提前量
		    if(fcu_data_buffer.h2_data_buffer.h2_outlet_valve_close_time >= 4000 )
		    {
		         fcu_data_buffer.h2_data_buffer.h2_pressure_pid2_advance_time = 1000;  
		    }
		    else
		    {
		        fcu_data_buffer.h2_data_buffer.h2_pressure_pid2_advance_time = 200;
		    }
		
			//尾排开启时
			if(fcu_data_buffer.h2_data_buffer.h2_outlet_valve == 1)
			{

				//第四部，结束open_time 后关闭尾排，
				if(system_time - fcu_data_buffer.h2_data_buffer.h2_outlet_valve_current_time
					>= fcu_data_buffer.h2_data_buffer.h2_outlet_valve_open_time )
				{
					fcu_data_buffer.h2_data_buffer.h2_outlet_valve = 0;
					fcu_data_buffer.h2_data_buffer.h2_outlet_valve_current_time =   system_time; 
				}  

				//第三步，使用提前量，在 open_time中期，降压10kpa
				else if(system_time - fcu_data_buffer.h2_data_buffer.h2_outlet_valve_current_time
					>= fcu_data_buffer.h2_data_buffer.h2_pressure_pid1_advance_time   )
					//   && fcu_data_buffer.h2_data_buffer.h2_pressure_advance_value != - advance_value )
				{
					fcu_data_buffer.h2_data_buffer.h2_pressure_advance_current_value = 
						- fcu_data_buffer.h2_data_buffer.h2_pressure_advance_set_value;
				}  


			}

			//尾排关闭时
			if(fcu_data_buffer.h2_data_buffer.h2_outlet_valve == 0)
			{

				//第二步，结束close_time 后开启尾排，切换到pid1，  此时进入波动期
				if(system_time - fcu_data_buffer.h2_data_buffer.h2_outlet_valve_current_time
					>= fcu_data_buffer.h2_data_buffer.h2_outlet_valve_close_time     )
					//  	     && fcu_data_buffer.h2_data_buffer.h2_is_enable_pid != 1)
				{
					fcu_data_buffer.h2_data_buffer.h2_pid_mode = 1  ;
					fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid1.SumError = 0;
					fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid2.SumError = 0;

					fcu_data_buffer.h2_data_buffer.h2_outlet_valve = 1;
					fcu_data_buffer.h2_data_buffer.h2_outlet_valve_current_time =   system_time;
					fcu_data_buffer.h2_data_buffer.h2_pressure_fluctuate_reset = 1;
				} 

				//第一步，使用提前量，提前2秒升压10kpa
				else if(system_time - fcu_data_buffer.h2_data_buffer.h2_outlet_valve_current_time
					>= fcu_data_buffer.h2_data_buffer.h2_outlet_valve_close_time - 
					fcu_data_buffer.h2_data_buffer.h2_pressure_pid2_advance_time       )
					// 	     && fcu_data_buffer.h2_data_buffer.h2_pressure_advance_value != advance_value)
				{
					fcu_data_buffer.h2_data_buffer.h2_pressure_advance_current_value = 
						fcu_data_buffer.h2_data_buffer.h2_pressure_advance_set_value;
				}



				//第六步， 关闭尾排后，延时4秒， 取消提前量， 此时进入稳定期
				else if(system_time - fcu_data_buffer.h2_data_buffer.h2_outlet_valve_current_time
					>= fcu_data_buffer.h2_data_buffer.h2_pressure_pid2_advance_time *2  )
					//  && 	system_time - fcu_data_buffer.h2_data_buffer.h2_outlet_valve_current_time
					//      < fcu_data_buffer.h2_data_buffer.h2_outlet_valve_close_time - advance_time  
					//  && fcu_data_buffer.h2_data_buffer.h2_pressure_advance_value != 0   )
				{
					fcu_data_buffer.h2_data_buffer.h2_pressure_advance_current_value = 0;		   	      
				}

				//第五步， 关闭尾排后，延时2秒， 切换到pid2，  此时进入稳定期
				else if(system_time - fcu_data_buffer.h2_data_buffer.h2_outlet_valve_current_time
					>= fcu_data_buffer.h2_data_buffer.h2_pressure_pid2_advance_time    )
					// 	  && fcu_data_buffer.h2_data_buffer.h2_is_enable_pid != 2)
				{
					fcu_data_buffer.h2_data_buffer.h2_pid_mode = 2;
					fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid1.SumError = 0;
					fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid2.SumError = 0;		   	      
					//   fcu_data_buffer.h2_data_buffer.h2_pressure_advance_value = 0;		   	      
				}



			}


		} 
		//氢气尾排常关
		else if(fcu_data_buffer.h2_data_buffer.h2_is_enable_outlet_valve == 0)
		{
			fcu_data_buffer.h2_data_buffer.h2_outlet_valve = 0;
			fcu_data_buffer.h2_data_buffer.h2_pid_mode = 2;
			fcu_data_buffer.h2_data_buffer.h2_pressure_advance_current_value = 0;
		}
		//氢气尾排常开	
		else if(fcu_data_buffer.h2_data_buffer.h2_is_enable_outlet_valve == 1)
		{
		    fcu_data_buffer.h2_data_buffer.h2_outlet_valve = 1;
			fcu_data_buffer.h2_data_buffer.h2_pid_mode = 2;
			fcu_data_buffer.h2_data_buffer.h2_pressure_advance_current_value = 0;
		}




		//空气尾排自动控制
		if(fcu_data_buffer.air_data_buffer.air_is_enable_outlet_valve == 2)
		{
			//尾排开启时
			if(fcu_data_buffer.air_data_buffer.air_outlet_valve == 1)
			{

				//结束open_time 后关闭尾排，
				if(system_time - fcu_data_buffer.air_data_buffer.air_outlet_valve_current_time
					>= fcu_data_buffer.air_data_buffer.air_outlet_valve_open_time )
				{
					fcu_data_buffer.air_data_buffer.air_outlet_valve = 0;
					fcu_data_buffer.air_data_buffer.air_outlet_valve_current_time =   system_time; 
				}  



			}

			//尾排关闭时
			if(fcu_data_buffer.air_data_buffer.air_outlet_valve == 0)
			{

				//结束close_time 后开启尾排
				if(system_time - fcu_data_buffer.air_data_buffer.air_outlet_valve_current_time
					>= fcu_data_buffer.air_data_buffer.air_outlet_valve_close_time  )
				{

					fcu_data_buffer.air_data_buffer.air_outlet_valve = 1;
					fcu_data_buffer.air_data_buffer.air_outlet_valve_current_time =   system_time;

				} 


			}


		} 
		//空气尾排常关
		else if(fcu_data_buffer.air_data_buffer.air_is_enable_outlet_valve == 0)
		{
			fcu_data_buffer.air_data_buffer.air_outlet_valve = 0;
		}
		//空气尾排常开
		else if(fcu_data_buffer.air_data_buffer.air_is_enable_outlet_valve == 1)
		{
			fcu_data_buffer.air_data_buffer.air_outlet_valve = 1;
		}



                                      


		     FCU_data_buffer_updata_by_communication();
	    	Control_Policy_Total_Manager_updata_by_system(&control_policy_total_manager);
//			p_FCU_modbus_tatal_manager_data_updata_by_232_modbus_communication();
             control_manager_refresh_system_time =  system_time;

		
		
	
		IO_OUT_K1 =  fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_is_enble_output;
		IO_OUT_K7 =  IO_OUT_K1;	
			
		IO_OUT_K2 =  fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_is_enble_load_resistance;
		IO_OUT_K3 =  fcu_data_buffer.air_data_buffer.air_outlet_valve;
		IO_OUT_K5 =  fcu_data_buffer.h2_data_buffer.h2_outlet_valve;
		IO_OUT_K6 =  fcu_data_buffer.h2_data_buffer.h2_circulating_pump_enble;	
		IO_OUT_K8 =  fcu_data_buffer.h2_data_buffer.h2_inlet_valve;
	/*			
		//目前，pwm1和pwm2都是风扇，水路合并的时候，水泵只剩一个了，但是风扇还有2组，由2个pwm控制。
		//其实是控制同一个电堆水路，因此自动控制的时候。都使用1号风扇的pwm来控制即可。
		pwm_set_dutyfactor(pwm_channel_0, 100-(u16)(fcu_data_buffer.water_for_pile_data_buffer.water_fan_pwm_dutyfactor1 /100)) ;	 
		pwm_set_dutyfactor(pwm_channel_1, 100-(u16)(fcu_data_buffer.water_for_pile_data_buffer.water_fan_pwm_dutyfactor2 /100)) ;
		pwm_set_dutyfactor(pwm_channel_23,10000-(u16)(fcu_data_buffer.water_for_compressor_data_bufferr.water_fan_pwm_dutyfactor)) ;
//		pwm_set_dutyfactor(pwm_channel_4, 100-(u16)(fcu_data_buffer.water_for_pile_data_buffer.water_pump_pwm_dutyfactor2 /100)) ;
        pwm_set_dutyfactor(pwm_channel_4, 100-(u16)(fcu_data_buffer.water_for_compressor_data_bufferr.water_pump_pwm_dutyfactor /100)) ;
		pwm_set_dutyfactor(pwm_channel_5, 100-(u16)(fcu_data_buffer.water_for_pile_data_buffer.water_pump_pwm_dutyfactor1 /100)) ;
//		pwm_set_dutyfactor(pwm_channel_67,(u16)(fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pwm_dutyfactor)) ;
        //比例阀的控制，直接放到pit2里面去，增加响应速度。
//		pwm_set_dutyfactor(pwm_channel_67,(u16)(fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pwm_dutyfactor)) ;
     */
     /*
    	pwm_set_dutyfactor(pwm_channel_0, 100-(u16)(fcu_data_buffer.water_for_pile_data_buffer.water_fan_pwm_dutyfactor1 /100)) ;	 
		pwm_set_dutyfactor(pwm_channel_1, 100-(u16)(fcu_data_buffer.water_for_pile_data_buffer.water_fan_pwm_dutyfactor2 /100)) ;
		pwm_set_dutyfactor(pwm_channel_23,10000-(u16)(fcu_data_buffer.water_for_compressor_data_bufferr.water_pump_pwm_dutyfactor)) ;
        pwm_set_dutyfactor(pwm_channel_4, 100-(u16)(fcu_data_buffer.water_for_pile_data_buffer.water_pump_pwm_dutyfactor1 /100)) ;
		pwm_set_dutyfactor(pwm_channel_5, 100-(u16)(fcu_data_buffer.water_for_compressor_data_bufferr.water_fan_pwm_dutyfactor /100)) ;
		 */
		   	pwm_set_dutyfactor(pwm_channel_0, 10) ;	 
		pwm_set_dutyfactor(pwm_channel_1, 20) ;
		pwm_set_dutyfactor(pwm_channel_23,3000) ;
        pwm_set_dutyfactor(pwm_channel_4, 40) ;
		pwm_set_dutyfactor(pwm_channel_5, 60) ;
	
        }
	}


}