/*---------------------------------------------------------*/
/************************************************************
����Ƽ�MC9S12XS128���������ۺϿ���ƽ̨ 
E-mail:bhfengchong@gmail.com
2008f.d@163.com
�Ա��꣺http://fxfreefly.taobao.com
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
//float	water_temperature_target_value = 55;			//������ˮ�� Ŀ��ֵ


/*************************************************************/
/*                         ������                            */
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

    //�ж����ȼ�����, 
	init_interruput_priorty_set();	

	//fcu���ݻ������ݳ�ʼ��
	FCU_data_buffer_init();
	
	//pcu���صĹ����ʼ��
	Control_Policy_Total_Manager_init(&control_policy_total_manager);

	//canͨ��Э����� ��ʼ��
	Can_communication_protocol2_init(&can_communication_protocol2_total);
	//��ʼ��������������
	Common_list_init(& CAN_receive_message_list );
	
	//�Ϻ�ǿ��  //canͨ��Э����� ��ʼ��
	Can_communication_protocol_vms_shanghai_init(&can_communication_protocol_vms_shanghai_total);
	//�Ϻ�ǿ��  //��ʼ��������������
	Common_list_init(& CAN_receive_message_list_vms_shanghai );	
	
			
	//modbus_232ͨ��Э��ṹ��ĳ�ʼ��
//	FCU_modbus_tatal_manager_data_init(&fcu_modbus_tatal_manager_data);
	//modbus���� ����֡�Լ� databuf֡�ĳ�ʼ��
//	Modbus1_Init_ex();
	INIT_PLL();
	INIT_SCI0();     
//	INIT_SCI1();      

	INIT_LED();     
//	INIT_KEY();
  
	INIT_ATD0();
	//ad����������,�ͳ�ʼ��һ��������һ��
	ATD0_set_continuous();

	INIT_ATD1();
	//ad����������,�ͳ�ʼ��һ��������һ��
	ATD1_set_continuous();

	init_pwm_hybrids();

	ect_init_mdc();

	INIT_CAN0();
	INIT_CAN1();
	INIT_CAN2();
	init_PIT();
	
	// ��ʼ�����Ź�                     
	INIT_COP();

	// Initialisation of example application
	FMSTR_Example_Init();


	EnableInterrupts;               

  
	for(;;)
	{     
	    _FEED_COP();  //ι������
	    /*                
		  if(freemaster_lock == unlock)
		  {
		  freemaster_lock = lock;
		  //ע���ˣ�freemasterʹ����sci0�� 232����ͨ�ţ����ͨ���ǲ��ܱ������жϴ�ϵġ�
		  //���ԣ��������pit���ж����棬Ȼ����������ȼ�ִ�С�
		  FMSTR_Example_Poll();
		  freemaster_lock = unlock;
		  }
		  */

		//���ˮ·�� ���ˮ��pid���ƣ�2�����ˮ·�ϲ�Ϊһ���ˣ���˿���ģ����룬����Ŀǰ���Ȼ���2�顣
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
	    	//��ѷ���pwm����  ˮ��pid1����
			PID_position_mode_ex(&(fcu_data_buffer.water_for_pile_data_buffer.water_temperature_fan_pid1), 
				fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_inlet1,
				fcu_data_buffer.water_for_pile_data_buffer.water_temperature_target_value1) ;

			fcu_data_buffer.water_for_pile_data_buffer.water_fan_pwm_dutyfactor1 -= 
				fcu_data_buffer.water_for_pile_data_buffer.water_temperature_fan_pid1.output_value_float; 

			//��ѷ���pwm�޶���Χ����Сֵ����Ϊ0������pwm90%���ϣ���û��Ҫ�ˣ���100%ʱ���Ȼ�ͣ��
			range_float(&(fcu_data_buffer.water_for_pile_data_buffer.water_fan_pwm_dutyfactor1), 0, 9000);    

			fcu_data_buffer.water_for_pile_data_buffer.water_temperature_fan_pid1.pid_updata_time =  system_time;  
             
			//Ŀǰ��pwm1��pwm2���Ƿ��ȣ�ˮ·�ϲ���ʱ��ˮ��ֻʣһ���ˣ����Ƿ��Ȼ���2�飬��2��pwm���ơ�
			//��ʵ�ǿ���ͬһ�����ˮ·������Զ����Ƶ�ʱ�򡣶�ʹ��1�ŷ��ȵ�pwm�����Ƽ��ɡ� 
			fcu_data_buffer.water_for_pile_data_buffer.water_fan_pwm_dutyfactor2 = 
				fcu_data_buffer.water_for_pile_data_buffer.water_fan_pwm_dutyfactor1;
			     /*
            //��ѷ���pwm����  ˮ��pid2����
            PID_position_mode_ex(&(fcu_data_buffer.water_for_pile_data_buffer.water_temperature_fan_pid2), 
				fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_inlet2,
				fcu_data_buffer.water_for_pile_data_buffer.water_temperature_target_value2) ;

			fcu_data_buffer.water_for_pile_data_buffer.water_fan_pwm_dutyfactor2 -= 
				fcu_data_buffer.water_for_pile_data_buffer.water_temperature_fan_pid2.output_value_float; 

			//��ѷ���pwm�޶���Χ����Сֵ����Ϊ0������pwm90%���ϣ���û��Ҫ�ˣ���100%ʱ���Ȼ�ͣ��
			range_float(&(fcu_data_buffer.water_for_pile_data_buffer.water_fan_pwm_dutyfactor2), 0, 9000); 
 

			fcu_data_buffer.water_for_pile_data_buffer.water_temperature_fan_pid2.pid_updata_time =  system_time;  
			    */

			//���ˮ��pwm����  ˮ���²�������ˮ�á�
			//ʵ�⣬ת�ٲ��ȣ��¶�Ҳ���ȡ����Ʋ��ˡ�
			//���Ը���ʱ�������
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


        //����һˮ·�� ˮ��pid���ƣ�ˮ·�������¶ȴ������Ϳ���·������������£���Щȡ���ֵ��Ȼ���Դ��������ƣ�Ҫ�����60�ȡ�
		if(fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_fan_pid.is_enble_pid == 1 &&
			system_time -  fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_fan_pid.pid_updata_time >= 
		    	fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_fan_pid.pid_over_time  )    	
		{
		    //����һˮ·�������¶ȴ������Ϳ���·������������£���Щȡ���ֵ��
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
           //����һ���ȵĿ��� 
           PID_position_mode_ex(&(fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_fan_pid), 
				water_temperature_for_compressor_max,
				fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_target_value) ;

			fcu_data_buffer.water_for_compressor_data_bufferr.water_fan_pwm_dutyfactor -= 
				fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_fan_pid.output_value_float; 

			//����һ����pwm�޶���Χ����Сֵ����Ϊ0
			range_float(&(fcu_data_buffer.water_for_compressor_data_bufferr.water_fan_pwm_dutyfactor), 0, 8000); 
 
            //����һˮ�õĿ���
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

		//ad�ֶ��ɼ�������ѭ���ɼ���ѹ
		//    pit_delay_us(1000);
		error_code_main = 	ATD0_capture_mean();
		error_code_main = 	ATD1_capture_mean();             


        //����ϵͳ�Ŀ����㷨
		if(system_time - control_manager_refresh_system_time > FCU_SYSTEM_CHANGE_MODE_DELAY_100MS)
		{

		//����β���Զ�����
		if(fcu_data_buffer.h2_data_buffer.h2_is_enable_outlet_valve == 2)
		{
		    //�Զ���������pid2��ʱ����ǰ��
		    if(fcu_data_buffer.h2_data_buffer.h2_outlet_valve_close_time >= 4000 )
		    {
		         fcu_data_buffer.h2_data_buffer.h2_pressure_pid2_advance_time = 1000;  
		    }
		    else
		    {
		        fcu_data_buffer.h2_data_buffer.h2_pressure_pid2_advance_time = 200;
		    }
		
			//β�ſ���ʱ
			if(fcu_data_buffer.h2_data_buffer.h2_outlet_valve == 1)
			{

				//���Ĳ�������open_time ��ر�β�ţ�
				if(system_time - fcu_data_buffer.h2_data_buffer.h2_outlet_valve_current_time
					>= fcu_data_buffer.h2_data_buffer.h2_outlet_valve_open_time )
				{
					fcu_data_buffer.h2_data_buffer.h2_outlet_valve = 0;
					fcu_data_buffer.h2_data_buffer.h2_outlet_valve_current_time =   system_time; 
				}  

				//��������ʹ����ǰ������ open_time���ڣ���ѹ10kpa
				else if(system_time - fcu_data_buffer.h2_data_buffer.h2_outlet_valve_current_time
					>= fcu_data_buffer.h2_data_buffer.h2_pressure_pid1_advance_time   )
					//   && fcu_data_buffer.h2_data_buffer.h2_pressure_advance_value != - advance_value )
				{
					fcu_data_buffer.h2_data_buffer.h2_pressure_advance_current_value = 
						- fcu_data_buffer.h2_data_buffer.h2_pressure_advance_set_value;
				}  


			}

			//β�Źر�ʱ
			if(fcu_data_buffer.h2_data_buffer.h2_outlet_valve == 0)
			{

				//�ڶ���������close_time ����β�ţ��л���pid1��  ��ʱ���벨����
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

				//��һ����ʹ����ǰ������ǰ2����ѹ10kpa
				else if(system_time - fcu_data_buffer.h2_data_buffer.h2_outlet_valve_current_time
					>= fcu_data_buffer.h2_data_buffer.h2_outlet_valve_close_time - 
					fcu_data_buffer.h2_data_buffer.h2_pressure_pid2_advance_time       )
					// 	     && fcu_data_buffer.h2_data_buffer.h2_pressure_advance_value != advance_value)
				{
					fcu_data_buffer.h2_data_buffer.h2_pressure_advance_current_value = 
						fcu_data_buffer.h2_data_buffer.h2_pressure_advance_set_value;
				}



				//�������� �ر�β�ź���ʱ4�룬 ȡ����ǰ���� ��ʱ�����ȶ���
				else if(system_time - fcu_data_buffer.h2_data_buffer.h2_outlet_valve_current_time
					>= fcu_data_buffer.h2_data_buffer.h2_pressure_pid2_advance_time *2  )
					//  && 	system_time - fcu_data_buffer.h2_data_buffer.h2_outlet_valve_current_time
					//      < fcu_data_buffer.h2_data_buffer.h2_outlet_valve_close_time - advance_time  
					//  && fcu_data_buffer.h2_data_buffer.h2_pressure_advance_value != 0   )
				{
					fcu_data_buffer.h2_data_buffer.h2_pressure_advance_current_value = 0;		   	      
				}

				//���岽�� �ر�β�ź���ʱ2�룬 �л���pid2��  ��ʱ�����ȶ���
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
		//����β�ų���
		else if(fcu_data_buffer.h2_data_buffer.h2_is_enable_outlet_valve == 0)
		{
			fcu_data_buffer.h2_data_buffer.h2_outlet_valve = 0;
			fcu_data_buffer.h2_data_buffer.h2_pid_mode = 2;
			fcu_data_buffer.h2_data_buffer.h2_pressure_advance_current_value = 0;
		}
		//����β�ų���	
		else if(fcu_data_buffer.h2_data_buffer.h2_is_enable_outlet_valve == 1)
		{
		    fcu_data_buffer.h2_data_buffer.h2_outlet_valve = 1;
			fcu_data_buffer.h2_data_buffer.h2_pid_mode = 2;
			fcu_data_buffer.h2_data_buffer.h2_pressure_advance_current_value = 0;
		}




		//����β���Զ�����
		if(fcu_data_buffer.air_data_buffer.air_is_enable_outlet_valve == 2)
		{
			//β�ſ���ʱ
			if(fcu_data_buffer.air_data_buffer.air_outlet_valve == 1)
			{

				//����open_time ��ر�β�ţ�
				if(system_time - fcu_data_buffer.air_data_buffer.air_outlet_valve_current_time
					>= fcu_data_buffer.air_data_buffer.air_outlet_valve_open_time )
				{
					fcu_data_buffer.air_data_buffer.air_outlet_valve = 0;
					fcu_data_buffer.air_data_buffer.air_outlet_valve_current_time =   system_time; 
				}  



			}

			//β�Źر�ʱ
			if(fcu_data_buffer.air_data_buffer.air_outlet_valve == 0)
			{

				//����close_time ����β��
				if(system_time - fcu_data_buffer.air_data_buffer.air_outlet_valve_current_time
					>= fcu_data_buffer.air_data_buffer.air_outlet_valve_close_time  )
				{

					fcu_data_buffer.air_data_buffer.air_outlet_valve = 1;
					fcu_data_buffer.air_data_buffer.air_outlet_valve_current_time =   system_time;

				} 


			}


		} 
		//����β�ų���
		else if(fcu_data_buffer.air_data_buffer.air_is_enable_outlet_valve == 0)
		{
			fcu_data_buffer.air_data_buffer.air_outlet_valve = 0;
		}
		//����β�ų���
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
		//Ŀǰ��pwm1��pwm2���Ƿ��ȣ�ˮ·�ϲ���ʱ��ˮ��ֻʣһ���ˣ����Ƿ��Ȼ���2�飬��2��pwm���ơ�
		//��ʵ�ǿ���ͬһ�����ˮ·������Զ����Ƶ�ʱ�򡣶�ʹ��1�ŷ��ȵ�pwm�����Ƽ��ɡ�
		pwm_set_dutyfactor(pwm_channel_0, 100-(u16)(fcu_data_buffer.water_for_pile_data_buffer.water_fan_pwm_dutyfactor1 /100)) ;	 
		pwm_set_dutyfactor(pwm_channel_1, 100-(u16)(fcu_data_buffer.water_for_pile_data_buffer.water_fan_pwm_dutyfactor2 /100)) ;
		pwm_set_dutyfactor(pwm_channel_23,10000-(u16)(fcu_data_buffer.water_for_compressor_data_bufferr.water_fan_pwm_dutyfactor)) ;
//		pwm_set_dutyfactor(pwm_channel_4, 100-(u16)(fcu_data_buffer.water_for_pile_data_buffer.water_pump_pwm_dutyfactor2 /100)) ;
        pwm_set_dutyfactor(pwm_channel_4, 100-(u16)(fcu_data_buffer.water_for_compressor_data_bufferr.water_pump_pwm_dutyfactor /100)) ;
		pwm_set_dutyfactor(pwm_channel_5, 100-(u16)(fcu_data_buffer.water_for_pile_data_buffer.water_pump_pwm_dutyfactor1 /100)) ;
//		pwm_set_dutyfactor(pwm_channel_67,(u16)(fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pwm_dutyfactor)) ;
        //�������Ŀ��ƣ�ֱ�ӷŵ�pit2����ȥ��������Ӧ�ٶȡ�
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