
#include "pit.h"

#include "freemaster.h"
#include "freemaster_example.h"
#include "control_manager.h"

//΢��ļ�ʱ����
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



//pit��ʼ��
void init_PIT(void)
{
	PITMTLD0=249;			//Ϊ0ͨ��8λ��������ֵ
	//	PITMTLD1=31;			//Ϊ1ͨ��8λ��������ֵ
	PITMTLD1=63;		//	32M��Ϊ120M

	//	PITLD0=63999;			//Ϊ0ͨ��16λ��������ֵ   (249+1)*(63999+1) / 64M = 0.5��
	PITLD0=9;		    	//Ϊ0ͨ��16λ��������ֵ   (63+1)*(9+1) / 64M = 0.01ms
	PITLD1=8878;		    	//Ϊ1ͨ��16λ��������ֵ   (63+1)*(888+1) / 64M = 10ms
	PITLD2=987;			    //Ϊ2ͨ��16λ��������ֵ   (63+1)*(987+1) / 64M = 1ms
    PITLD3=6327;			//Ϊ3ͨ��16λ��������ֵ   (249+1)*(63999+1) / 64M = 0.5��
    PITLD4=9967;		    //Ϊ4ͨ��16λ��������ֵ   (63+1)*(9967+1) / 64M = 10ms
    PITLD5=2943;		    //Ϊ4ͨ��16λ��������ֵ   (63+1)*(2943+1) / 64M = 3ms

	//ע���ˣ�pit��ͬ��ʱ��������һ��Ҫ����������ܻ�ͬʱ�����������жϸ��ǡ�

 /*
	PITMUX = 0x07;			//��0~1ͨ��ʹ��΢������1, ����ͨ��ʹ��΢������0
	PITCE = 0x07;			//��0~1ͨ������������ 
	PITCFLMT = 0X80;		//ʹ�������ж϶�ʱ��
	PITINTE = 0x07;			//��0~1ͨ����ʱ����ʱ�жϱ�ʹ��
	*/
	
	PITMUX = 0x37;			//��0~2ͨ����4~5ͨ��ʹ��΢������1, ����ͨ��ʹ��΢������0
	PITCE = 0x3F;			//��0~5ͨ������������ 
	PITCFLMT = 0X80;		//ʹ�������ж϶�ʱ��
	PITINTE = 0x3F;			//��0~5ͨ����ʱ����ʱ�жϱ�ʹ��
	
	
	//   PITINTE = 0x02;
	//   PITINTE = 0x01;		
}



//pit0�ж�	΢��ļ�ʱ����//��ʱ��0.01ms����һ��
#pragma CODE_SEG __NEAR_SEG NON_BANKED
interrupt void PIT0_interrupt(void) 
{
	EnableInterrupts;
	if(PITTF_PTF0==1) {

		PITTF_PTF0=1;            
		system_time_us += 10;		//��ʱ��0.01ms����һ��

		if(freemaster_lock == unlock)
		{
			freemaster_lock = lock;
			//ע���ˣ�freemasterʹ����sci0�� 232����ͨ�ţ����ͨ���ǲ��ܱ������жϴ�ϵġ�
			//���ԣ��������pit���ж����棬Ȼ����������ȼ�ִ�С�
			FMSTR_Example_Poll();
			freemaster_lock = unlock;
		}

		if(system_time_us == 4294967290)		//2��32�η� = 4294967296
		{
			system_time_us = 0;

			//need pragrom
			//����Ҫ������г����У���ص�����ʱ��
		}

	}
}
#pragma CODE_SEG DEFAULT
                                      

//canͨ�Ź�����
//��Ҫ����ѽ��յ�can��Ϣ���棬��ĳ��˳���ȡ������Ŀǰ����˳�򣬺����Ż��������ȼ���
//Ȼ����һ����Ƶ�ʷ������ݡ�
enum Error_code can_communication_control(void)
{
	enum Error_code error_code = Succeed;

	CAN_message RxMessage;	//can������Ϣ
	CAN_message TxMessage;	//can������Ϣ

	//	u32 test_test =  system_time_us;

	if(fcu_data_buffer.islock == unlock)
	{
		fcu_data_buffer.islock = lock;


		//����can������Ϣ
		while(error_code == 0)
		{
			error_code = Common_list_moveout_data_from_head(&CAN_receive_message_list, 0, (char*)(&RxMessage), sizeof(CAN_message));
                                  
			if(error_code != 0)
			{
				;//���ɹ���ʾlistû�����ݡ���ô�Ͳ�������
			}
			else
			{                
				test_can_receive++;
				//ͨ�����ܵ�CAN��Ϣ�����������ݡ�
		//		error_code = Can_communication_protocol_updata_receivev_can( &can_communication_protocol_total, &RxMessage);
				error_code = Can_communication_protocol2_updata_receivev_can( &can_communication_protocol2_total, &RxMessage);

				//	//��Ҫ������ӡ
				//	if((system_time/1000)%10 == 0)
				//	{
				//		//��ӡ���ܵ�����
				//		error_code = Control_Policy_printf_can_receivev_data( &control_policy_data_buffer, &RxMessage);
				//		if(error_code != Succeed)	{return error_code;}
				//	}

			}		
		}
		//ǰ�����can������Ϣ��ʱ�򣬿����д���
		if(error_code == NoData)
		{error_code = Succeed;}


		//��װ�ͷ���can��Ϣ	

		error_code = Can_communication_protocol2_can_encapsulation_and_send(&can_communication_protocol2_total, &TxMessage);
	//	error_code = Can_communication_protocol_can_encapsulation_and_send(&can_communication_protocol_total, &TxMessage);	

		//ǰ���װ�ͷ���can��Ϣ��ʱ�򣬿����д���
		if(error_code == NoData)
		{error_code = Succeed;}

		fcu_data_buffer.islock = unlock;
	}


	return error_code;
}




//pit1�жϣ�can��Ϣ�Ķ�ʱ�����ͷ�װ����//��ʱ��1ms����һ��
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




//pit2�жϣ�pid�㷨��//��ʱ��1ms����һ��
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
      
		//���������ʱ��
		atd0_capture_number_max =  atd0_capture_number;
		atd0_capture_number = 0;
		atd1_capture_number_max =  atd1_capture_number;
		atd1_capture_number = 0;                                                       

		//ad�Ĵ��� ת�� Ϊʵ������

		//NTC������  AD 12��
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
		

		//��ѹ0~5V������
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

		//��ѹ������
		fcu_data_buffer.air_data_buffer.air_rate_of_flow = atd_voltage_calculation_for_air_rate_of_flow(atd0_mean_data[13]-10);
		fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_voltage = atd_voltage_calculation_for_pile_voltage(atd0_mean_data[0], 500);
		fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_electricity = atd_voltage_calculation_for_pile_electricity(atd0_mean_data[1]) -2;
        fcu_data_buffer.h2_data_buffer.h2_concentration = atd_voltage_calculation_for_h2_concentration(atd0_mean_data[3]);

		//pid������ѹ��  ��ʵĿ��ֵ�� ����ƫ����֮���
		fcu_data_buffer.h2_data_buffer.h2_pressure_real_target_value
		 =	fcu_data_buffer.h2_data_buffer.h2_pressure_target_value + fcu_data_buffer.h2_data_buffer.h2_pressure_advance_current_value; 

		//���������Сֵ
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
		//��ȡ�����Сֵ
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
		//��ѹ����������ѹ����100���رձ�������     ȱ��˲��رձ��������ᵼ�¹���
		if(fcu_data_buffer.h2_data_buffer.h2_pressure_proportional_valve_rear >= 130 ||
			fcu_data_buffer.h2_data_buffer.h2_pressure_pile_inlet >= 100 && system_time >= 1000) 
		{
                //ֱ��������

                //�ر�������ڷ�����������Ƶ�ʣ��ٰ�����β�ŷ���������ֹ��֮ͣ����ѹ����
				fcu_data_buffer.h2_data_buffer.h2_inlet_valve = 0;
				fcu_data_buffer.h2_data_buffer.h2_outlet_valve_open_time = 500;
				fcu_data_buffer.h2_data_buffer.h2_outlet_valve_close_time = 1000;
				fcu_data_buffer.h2_data_buffer.h2_is_enable_outlet_valve = 1;
                //�رձ��������Զ�����
				fcu_data_buffer.h2_data_buffer.h2_pid_mode = 2;
				fcu_data_buffer.h2_data_buffer.h2_pressure_advance_set_value = 0;
				fcu_data_buffer.h2_data_buffer.h2_pressure_pid2_advance_time = 200;
				fcu_data_buffer.h2_data_buffer.h2_pressure_target_value = 50;
				fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid1.is_enble_pid = 0;
				fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid2.is_enble_pid = 0;
				fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pwm_dutyfactor = 0;
                //�ر�����ѭ����
				fcu_data_buffer.h2_data_buffer.h2_circulating_pump_enble = 1;
				fcu_data_buffer.h2_data_buffer.h2_circulating_pump_enable_pump = 0;
                //�رտ�����ˮ���Ϳ�ѹ��pidʹ��
                fcu_data_buffer.air_data_buffer.air_is_enable_outlet_valve = 0;
				fcu_data_buffer.air_data_buffer.air_compressor_enable = 0;
				fcu_data_buffer.air_data_buffer.air_compressor_speed_pid.is_enble_pid = 0;
				fcu_data_buffer.air_data_buffer.air_rate_of_flow_target = 0;
				fcu_data_buffer.air_data_buffer.air_compressor_speed_setpoint = 20000;
				
				//�رյ��ɢ��ϵͳ�ĵ�ˮ�úͷ���pidʹ��
				fcu_data_buffer.water_for_pile_data_buffer.water_temperature_fan_pid1.is_enble_pid = 0;
				fcu_data_buffer.water_for_pile_data_buffer.water_temperature_fan_pid2.is_enble_pid = 0;
				fcu_data_buffer.water_for_pile_data_buffer.water_pump_pwm_dutyfactor1 = 0;
				fcu_data_buffer.water_for_pile_data_buffer.water_fan_pwm_dutyfactor1 = 0;
				fcu_data_buffer.water_for_pile_data_buffer.water_pump_pwm_dutyfactor2 = 0;
				fcu_data_buffer.water_for_pile_data_buffer.water_fan_pwm_dutyfactor2 = 0;
				//�ر�����һɢ��ϵͳ��ˮ�úͷ���pidʹ��
				fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_fan_pid.is_enble_pid = 0;
				fcu_data_buffer.water_for_compressor_data_bufferr.water_pump_pwm_dutyfactor = 0;
				fcu_data_buffer.water_for_compressor_data_bufferr.water_fan_pwm_dutyfactor = 0;

                //�رյ�ѷ���ϵͳ��������̵�����С���踺�صļ̵���
				fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_is_enble_output = 0;
				fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_is_enble_load_resistance = 0;
			
			control_policy_total_manager.working_control_mode = working_control_fault_wait;
	    	control_policy_total_manager.working_status_mode = working_status_error;
	    	control_policy_total_manager.working_alarm_mode = one_level_fault;
	    	control_policy_total_manager.working_FCU_error_code = H2_pressure_proportional_valve_rear_over_error1 ;	//����������ѹ  ��ѹ��һ�����ϣ�
	    	control_policy_total_manager.working_FCU_error_control_mode = working_control_wait;
	    	control_policy_total_manager.working_error_count++;
	    	control_policy_total_manager.fcu_updata_event_time = system_time;       
		}
*/		

		//pid�����㷨
		//pid���ơ�
		//ע���ˡ�pid�㷨��Ҫ�ܸߵ�ʵʱ�ԣ�����ÿ��ad�������֮�󣬾�Ҫ��������pid�㷨���ƣ������Խϸߵ��ж����ȼ�2
		//ע���ˡ�pid�㷨��Ҫ�ܸߵ��ȶ��ԣ����Թ̶�һ����ʱ�䣬�����ڴ���
		//20181212ע���ˣ�45kw̨������ѭ����ת�ٿ���3000����ʱ����������ѹ�������ѹ���20kpa��
		//��ˣ�Ϊ�˱��������ѹ���ȶ���ʹ�������ѹ������pid���㡣
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


		//�������޶���Χ����Сֵ����Ϊ0
		//20181211ע���ˣ��������Ŀ����޸ķ�����ȥ���������Ŀ�������ֱ���������壬pwm6400hz��Ϊpwm900hz���
		//�ڳ�ʼ����ʱ��900hz�������á�����ʹ��800hz��
		//��ʵ�ʲ��������У�ǰ��ѹ500kpaʱ��������5000���¶��ǹرյģ�Ϊ����Ӧ�ٶȣ�����������pwmռ�ձȵĿɵ���Χ��Ϊ4000~10000
		range_float(&(fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pwm_dutyfactor), 4000, 10000); 

		//�������Ŀ��ƣ�ֱ�ӷŵ�pit2����ȥ��������Ӧ�ٶȡ�
		pwm_set_dutyfactor(pwm_channel_67,(u16)(fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pwm_dutyfactor)) ;


		// test_pid_end =  system_time_us -  test_pid_begin;
	}
}
#pragma CODE_SEG DEFAULT

       /*
//modbus_232 ͨ�Ź�����
//��Ҫ����ѽ��յ�232��Ϣ���棬��ĳ��˳���ȡ������Ŀǰ����˳�򣬺����Ż��������ȼ���
//Ȼ����һ����Ƶ�ʷ������ݡ�
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


//pit3�жϣ�pid�㷨��//��ʱ��0.5s����һ��
#pragma CODE_SEG __NEAR_SEG NON_BANKED
interrupt void PIT3_interrupt(void)
{
  enum Error_code error_code = Succeed;
	EnableInterrupts;
 
	if(PITTF_PTF3==1)
	{

		PITTF_PTF3=1;    
		 
	  //��ʱ��������λ������ϵͳ     
//		error_code = modbus_232_communication_control();
	//	if(error_code != Succeed)	{printf("modbus_communication_control failed, error_code:%d \r\n", error_code);}
		//		 test_can_end =  system_time_us - test_can_begin;

	}
}
#pragma CODE_SEG DEFAULT

float  air_compressor_speed_setpoint_temp = 0;

//pit4�жϣ�pid�㷨��//��ʱ��2ms����һ��
#pragma CODE_SEG __NEAR_SEG NON_BANKED
interrupt void PIT4_interrupt(void)
{
    enum Error_code error_code = Succeed;
    //����ʹ�þ�̬�ֲ�������������ֻ��pid4�������ʹ�ã����������������á�
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

			//��ѹ��ת���޶���Χ��20000~70000
			range_float(&(air_compressor_speed_setpoint_temp), 20000, 70000);
			fcu_data_buffer.air_data_buffer.air_compressor_speed_setpoint = air_compressor_speed_setpoint_temp;
			  
        }
	}
}
#pragma CODE_SEG DEFAULT


//pit5�жϣ�can��Ϣ�Ķ�ʱ�����ͷ�װ����//��ʱ��1ms����һ��
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


//�Ϻ�ǿ��  canͨ�Ź�����
//��Ҫ����ѽ��յ�can��Ϣ���棬��ĳ��˳���ȡ������Ŀǰ����˳�򣬺����Ż��������ȼ���
//Ȼ����һ����Ƶ�ʷ������ݡ�
enum Error_code can_communication_control_vms_shanghai(void)
{
	enum Error_code error_code = Succeed;

	CAN_message RxMessage;	//can������Ϣ
	CAN_message TxMessage;	//can������Ϣ

	//	u32 test_test =  system_time_us;

	if(fcu_data_buffer.islock == unlock)
	{
		fcu_data_buffer.islock = lock;


		//����can������Ϣ
		while(error_code == 0)
		{
			error_code = Common_list_moveout_data_from_head(&CAN_receive_message_list_vms_shanghai, 0, (char*)(&RxMessage), sizeof(CAN_message));
                                  
			if(error_code != 0)
			{
				;//���ɹ���ʾlistû�����ݡ���ô�Ͳ�������
			}
			else
			{                
				test_can_receive++;
				//ͨ�����ܵ�CAN��Ϣ�����������ݡ�
				error_code = Can_communication_protocol_vms_shanghai_updata_receivev_can( &can_communication_protocol_vms_shanghai_total, &RxMessage);
			}		
		}
		//ǰ�����can������Ϣ��ʱ�򣬿����д���
		if(error_code == NoData)
		{error_code = Succeed;}


		//��װ�ͷ���can��Ϣ	    
		error_code = Can_communication_protocol_vms_shanghai_can_encapsulation_and_send(&can_communication_protocol_vms_shanghai_total, &TxMessage);

		//ǰ���װ�ͷ���can��Ϣ��ʱ�򣬿����д���
		if(error_code == NoData)
		{error_code = Succeed;}

		fcu_data_buffer.islock = unlock;
	}


	return error_code;
}



//��ʱ��������λus������ʱ���
void pit_delay_us(u32 delay_time)
{
	u32 time_temp = system_time_us;
	while(system_time_us - time_temp  <  delay_time)
	{}
}
