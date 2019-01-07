
#include"data_buff.h"

struct FCU_Data_Buffer		fcu_data_buffer  ;

                  

//��ʼ��
void FCU_data_buffer_init(void)    
{                                        
	//�������ݲ�                                               
	//����
	fcu_data_buffer.h2_data_buffer.h2_pressure_proportional_valve_front = 0;	
	fcu_data_buffer.h2_data_buffer.h2_pressure_proportional_valve_rear = 0;
	fcu_data_buffer.h2_data_buffer.h2_pressure_pile_inlet = 0;
	fcu_data_buffer.h2_data_buffer.h2_pressure_pile_inlet1 = 0;
	fcu_data_buffer.h2_data_buffer.h2_pressure_pile_inlet2 = 0;
	fcu_data_buffer.h2_data_buffer.h2_pressure_pile_outlet1 = 0;
	fcu_data_buffer.h2_data_buffer.h2_pressure_pile_outlet2 = 0;
	fcu_data_buffer.h2_data_buffer.h2_pressure_tail_outlet = 0;
	fcu_data_buffer.h2_data_buffer.h2_concentration = 0;
	fcu_data_buffer.h2_data_buffer.h2_humidity = 0;
	fcu_data_buffer.h2_data_buffer.h2_temperature_tail_outlet = 0;
	fcu_data_buffer.h2_data_buffer.h2_temperature_pile_inlet = 0;
	
	//���
	fcu_data_buffer.h2_data_buffer.h2_inlet_valve = 0;
	fcu_data_buffer.h2_data_buffer.h2_outlet_valve = 0;
	fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pwm_dutyfactor = 0;
	//ע���ˣ�����һ��Ҫ���ϵ�֮���˲��� ����ѭ���õ�IOʹ�ܣ������Ż���canͨ�ţ�
	fcu_data_buffer.h2_data_buffer.h2_circulating_pump_enble = 1; 

	//����ѭ����ת���趨  �ٷֱ�	�����澯֮�󣬽���ʹ�õ�	1ָ����100%
	fcu_data_buffer.h2_data_buffer.h2_circulating_pump_speed_setpoint_percent = 1;
	//����ѭ����  canͨ��
	fcu_data_buffer.h2_data_buffer.h2_circulating_pump_working_communication_status = working_communication_outage;
	fcu_data_buffer.h2_data_buffer.h2_circulating_pump_mass_flow_setpoint = 0;
	fcu_data_buffer.h2_data_buffer.h2_circulating_pump_speed_setpoint = H2_CIRCULATING_PUMP_SPEED_SETPOINT_1500;
	fcu_data_buffer.h2_data_buffer.h2_circulating_pump_enable_pump = 0;
	fcu_data_buffer.h2_data_buffer.h2_circulating_pump_enable_mass_flow_govemor = 0;
	fcu_data_buffer.h2_data_buffer.h2_circulating_pump_actual_mass_flow = 0;       							//  ��������
	fcu_data_buffer.h2_data_buffer.h2_circulating_pump_actual_speed = 0;       					            //  ����ѭ����ת��
	fcu_data_buffer.h2_data_buffer.h2_circulating_pump_actual_current = 0;      								//  ����ѭ���õ���
	fcu_data_buffer.h2_data_buffer.h2_circulating_pump_actual_voltage = 0;      								//  ����ѭ���õ�ѹ
	fcu_data_buffer.h2_data_buffer.h2_circulating_pump_actual_electronic_temperature = 0;                     //  ����ѭ���õ���¶�
	fcu_data_buffer.h2_data_buffer.h2_circulating_pump_actual_air_temperature = 0;       		        	    //  ����ѭ���������¶�
	fcu_data_buffer.h2_data_buffer.h2_circulating_pump_status_diagnose_word = 0;      		    		    //  ����ѭ����״̬����ֽ�

	//pid����
	fcu_data_buffer.h2_data_buffer.h2_pressure_target_value = H2_PRESSURE_SET_VALUE_50;
	fcu_data_buffer.h2_data_buffer.h2_pressure_real_target_value = 0;
	fcu_data_buffer.h2_data_buffer.h2_pressure_advance_current_value = 0;    //��ѹ ��ǰ��  ʵ��ֵ
	fcu_data_buffer.h2_data_buffer.h2_pressure_advance_set_value = 0;    //��ѹ ��ǰ��  �趨ֵ  Ĭ��Ϊ0��һ����Ϊ5
	fcu_data_buffer.h2_data_buffer.h2_pressure_pid1_advance_time = H2_PRESSURE_PID1_ADVANCE_TIME;     //��ѹ pid1ʱ����ǰ��      Ĭ��250ms
	fcu_data_buffer.h2_data_buffer.h2_pressure_pid2_advance_time = H2_PRESSURE_PID2_ADVANCE_TIME;    //��ѹ pid2ʱ����ǰ��      Ĭ��1000ms	        	
	PID_init(&(fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid1), PID1_KP, PID1_KI, PID1_KD);
	PID_init(&(fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid2), PID2_KP, PID2_KI, PID2_KD);				
	fcu_data_buffer.h2_data_buffer.h2_pid_mode = 0;        //pid�㷨����ģʽ��1��ʾʹ��pid1�����ƣ�2��ʾʹ��pid2������

	//����β�ſ���
	fcu_data_buffer.h2_data_buffer.h2_is_enable_outlet_valve = 0;
	fcu_data_buffer.h2_data_buffer.h2_outlet_valve_current_time = 0;		//β�ŷ���ǰ��ʱ��	
	fcu_data_buffer.h2_data_buffer.h2_outlet_valve_open_time = H2_OUTLET_VALVE_OPEN_TIME_500;
	fcu_data_buffer.h2_data_buffer.h2_outlet_valve_close_time = H2_OUTLET_VALVE_CLOSE_TIME_1000;

	//��ѹ����
	fcu_data_buffer.h2_data_buffer.h2_pressure_fluctuate_reset = 0;            //��ѹ ����  ����
	fcu_data_buffer.h2_data_buffer.h2_pressure_fluctuate_current_max = 0;      //��ѹ ����  ��ǰ���ֵ
	fcu_data_buffer.h2_data_buffer.h2_pressure_fluctuate_current_min = 0;      //��ѹ ����  ��ǰ��Сֵ
	fcu_data_buffer.h2_data_buffer.h2_pressure_fluctuate_last_max = 0;		    //��ѹ ����  �ϴ����ֵ
	fcu_data_buffer.h2_data_buffer.h2_pressure_fluctuate_last_min = 0;			//��ѹ ����  �ϴ���Сֵ



	//�������ݲ�    
	fcu_data_buffer.air_data_buffer.air_temperature_pile_inlet_duration_time = 0;//����¶ȳ���75�ȵĳ���ʱ�䣨����20s����һ�����ϣ�
	//����
	fcu_data_buffer.air_data_buffer.air_pressure_pile_inlet = 0;		
	fcu_data_buffer.air_data_buffer.air_pressure_pile_outlet = 0;		
	fcu_data_buffer.air_data_buffer.air_pressure_pile_back = 0;		
	fcu_data_buffer.air_data_buffer.air_temperature_pile_inlet = 0;
	fcu_data_buffer.air_data_buffer.air_temperature_pile_outlet = 0;
	fcu_data_buffer.air_data_buffer.air_temperature_pile_back = 0;
	fcu_data_buffer.air_data_buffer.air_temperature_humidifier = 0;
	fcu_data_buffer.air_data_buffer.air_rate_of_flow = 0;
	fcu_data_buffer.air_data_buffer.air_humidity = 0;
	fcu_data_buffer.air_data_buffer.air_temperature_humidifier_front = 0;

	//���
	fcu_data_buffer.air_data_buffer.air_outlet_valve = 0;

	fcu_data_buffer.air_data_buffer.air_compressor_speed_setpoint_increment = 0;//��ѹ��ת�٣����Ʊ�Ƶ��������
	//��ѹ��  can
	fcu_data_buffer.air_data_buffer.air_compressor_working_communication_status = working_communication_outage;
	fcu_data_buffer.air_data_buffer.air_compressor_enable = 0;
	fcu_data_buffer.air_data_buffer.air_compressor_speed_setpoint = AIR_COMPRESSOR_SPEED_SETPOINT_35000;
	fcu_data_buffer.air_data_buffer.air_compressor_input_electricity = 0;		//��Ƶ���������
	fcu_data_buffer.air_data_buffer.air_compressor_input_voltage = 0;			//��Ƶ�������ѹ
	fcu_data_buffer.air_data_buffer.air_compressor_output_power = 0;			//�������
	fcu_data_buffer.air_data_buffer.air_compressor_motor_temperature = 0;       //����¶�
	fcu_data_buffer.air_data_buffer.air_compressor_converter_temperature = 0;   //�������¶�
	fcu_data_buffer.air_data_buffer.air_compressor_inside_temperature = 0;		//��ѹ���ڲ��¶�
	fcu_data_buffer.air_data_buffer.air_compressor_state = 0;					//��ѹ��״̬
	fcu_data_buffer.air_data_buffer.air_compressor_fault_code = 0;				//������
	fcu_data_buffer.air_data_buffer.air_compressor_fault_level = 0;				//���ϵȼ�
	fcu_data_buffer.air_data_buffer.air_compressor_act_speed = 0;				//��ѹ��ʵ��ת��
	
	//20181112�����շ빤��Ҫ���ڴ����ӣ����ݿ������������ƿ�ѹ����ת�٣�Ŀǰʹ��pid���ڡ�
	PID_init(&(fcu_data_buffer.air_data_buffer.air_compressor_speed_pid), PID_COMPRESSOR_KP, PID_COMPRESSOR_KI, PID_COMPRESSOR_KD);
	fcu_data_buffer.air_data_buffer.air_compressor_speed_pid.pid_over_time = 1000;//10��	
	fcu_data_buffer.air_data_buffer.air_rate_of_flow_target = 0;

	//����β�ſ���
	fcu_data_buffer.air_data_buffer.air_is_enable_outlet_valve = 0;
	fcu_data_buffer.air_data_buffer.air_outlet_valve_current_time = 0;		//β�ŷ���ǰ��ʱ��	
	fcu_data_buffer.air_data_buffer.air_outlet_valve_open_time = AIR_OUTLET_VALVE_OPEN_TIME_500;
	fcu_data_buffer.air_data_buffer.air_outlet_valve_close_time = AIR_OUTLET_VALVE_CLOSE_TIME_8000;	


	//���ɢ��ϵͳ ���ݲ� 
	fcu_data_buffer.water_for_pile_data_buffer.water_pressure_pile_inlet1 = 0;	
	fcu_data_buffer.water_for_pile_data_buffer.water_pressure_pile_outlet1 = 0;
	fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_inlet1 = 0;
	fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_outlet1 = 0;
	fcu_data_buffer.water_for_pile_data_buffer.water_pressure_pile_inlet2 = 0;	
	fcu_data_buffer.water_for_pile_data_buffer.water_pressure_pile_outlet2 = 0;
	fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_inlet2 = 0;
	fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_outlet2 = 0;
	
	fcu_data_buffer.water_for_pile_data_buffer.water_pump_feedback1 = 0;		
	fcu_data_buffer.water_for_pile_data_buffer.water_pump_feedback2 = 0;		
	fcu_data_buffer.water_for_pile_data_buffer.water_fan_feedback1 = 0;	
	fcu_data_buffer.water_for_pile_data_buffer.water_fan_feedback2 = 0;		
	fcu_data_buffer.water_for_pile_data_buffer.water_position = 0;

	fcu_data_buffer.water_for_pile_data_buffer.water_pump_pwm_dutyfactor1 = 0;
	fcu_data_buffer.water_for_pile_data_buffer.water_pump_pwm_dutyfactor2 = 0;
	fcu_data_buffer.water_for_pile_data_buffer.water_fan_pwm_dutyfactor1 = 0;
	fcu_data_buffer.water_for_pile_data_buffer.water_fan_pwm_dutyfactor2 = 0;

    PID_init(&(fcu_data_buffer.water_for_pile_data_buffer.water_temperature_fan_pid1), PID_WATER_KP, PID_WATER_KI, PID_WATER_KD);
    fcu_data_buffer.water_for_pile_data_buffer.water_temperature_fan_pid1.pid_over_time = 1000;//10��	
    fcu_data_buffer.water_for_pile_data_buffer.water_temperature_target_value1 = 0;     //��ѵ�ˮ· ���¶ȿ��ƣ�����֮�����ŵ�����λ����
      
    PID_init(&(fcu_data_buffer.water_for_pile_data_buffer.water_temperature_fan_pid2), PID_WATER_KP, PID_WATER_KI, PID_WATER_KD);
    fcu_data_buffer.water_for_pile_data_buffer.water_temperature_fan_pid2.pid_over_time = 1000;//10��	
    fcu_data_buffer.water_for_pile_data_buffer.water_temperature_target_value2 = 0;     //��ѵ�ˮ· ���¶ȿ��ƣ�����֮�����ŵ�����λ����
      
	//����һɢ��ϵͳ ���ݲ�                             

	fcu_data_buffer.water_for_compressor_data_bufferr.water_pressure_compressor_outlet = 0;
	fcu_data_buffer.water_for_compressor_data_bufferr.water_pressure_frequency_outlet  = 0;	
	fcu_data_buffer.water_for_compressor_data_bufferr.water_pressure_intercooler_outlet = 0;
	fcu_data_buffer.water_for_compressor_data_bufferr.water_pressure_pump_outlet = 0;	
	fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_compressor_outlet = 0;
	fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_compressor_shell = 0;
	fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_frequency_outlet  = 0;
	fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_intercooler_outlet = 0;	
	fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_pump_outlet = 0;
	fcu_data_buffer.water_for_compressor_data_bufferr.water_fan_feedback = 0;			
	fcu_data_buffer.water_for_compressor_data_bufferr.water_position = 0;

	fcu_data_buffer.water_for_compressor_data_bufferr.water_pump_enable = 0;	
	fcu_data_buffer.water_for_compressor_data_bufferr.water_pump_pwm_dutyfactor = 0;				
	fcu_data_buffer.water_for_compressor_data_bufferr.water_fan_pwm_dutyfactor = 0;

    PID_init(&(fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_fan_pid), PID_WATER_KP, PID_WATER_KI, PID_WATER_KD);
    fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_fan_pid.pid_over_time = 1000;//10��	
    fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_target_value = 60;  //����һˮ· ���¶ȿ��ƣ����ȶ���60�ȣ��ͺ��ˡ�
    
	//��ѷ�������ݲ�
	fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_voltage = 0;
	fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_electricity = 0;
	fcu_data_buffer.galvanic_pile_data_buffer.fcu_start_enable = 0;
	fcu_data_buffer.galvanic_pile_data_buffer.fcu_stutter_stop_enable = 0;
    fcu_data_buffer.galvanic_pile_data_buffer.fcu_reset_enable = 0;
    
	fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_is_enble_output = 0;
	fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_is_enble_load_resistance = 0;

	//Ѳ��  can
	fcu_data_buffer.galvanic_pile_data_buffer.itinerant_detective_working_communication_status = working_communication_outage;
	fcu_data_buffer.galvanic_pile_data_buffer.itinerant_detective_working_statas = 0;
	fcu_data_buffer.galvanic_pile_data_buffer.Single_battery_overvoltage_alarm = 0;
	fcu_data_buffer.galvanic_pile_data_buffer.Single_battery_undervoltage_alarm = 0;
	fcu_data_buffer.galvanic_pile_data_buffer.Single_voltage_unbalance_alarm = 0;
	fcu_data_buffer.galvanic_pile_data_buffer.electric1_mean_voltage = 0;
	fcu_data_buffer.galvanic_pile_data_buffer.electric1_single_chip_highest_voltage = 0;
	fcu_data_buffer.galvanic_pile_data_buffer.electric1_single_chip_highest_voltage_num = 0;
	fcu_data_buffer.galvanic_pile_data_buffer.electric1_single_chip_minimum_voltage = 0;
	fcu_data_buffer.galvanic_pile_data_buffer.electric1_single_chip_minimum_voltage_num = 0;
	fcu_data_buffer.galvanic_pile_data_buffer.itinerant_detective_total_voltage = 0;
	
	//Ѳ��  can
	fcu_data_buffer.galvanic_pile_data_buffer.itinerant_detective_working_communication_status2 = working_communication_outage;
	fcu_data_buffer.galvanic_pile_data_buffer.itinerant_detective_working_statas2 = 0;
	fcu_data_buffer.galvanic_pile_data_buffer.Single_battery_overvoltage_alarm2 = 0;
	fcu_data_buffer.galvanic_pile_data_buffer.Single_battery_undervoltage_alarm2 = 0;
	fcu_data_buffer.galvanic_pile_data_buffer.Single_voltage_unbalance_alarm2 = 0;
	fcu_data_buffer.galvanic_pile_data_buffer.electric1_mean_voltage2 = 0;
	fcu_data_buffer.galvanic_pile_data_buffer.electric1_single_chip_highest_voltage2 = 0;
	fcu_data_buffer.galvanic_pile_data_buffer.electric1_single_chip_highest_voltage_num2 = 0;
	fcu_data_buffer.galvanic_pile_data_buffer.electric1_single_chip_minimum_voltage2 = 0;
	fcu_data_buffer.galvanic_pile_data_buffer.electric1_single_chip_minimum_voltage_num2 = 0;
	fcu_data_buffer.galvanic_pile_data_buffer.itinerant_detective_total_voltage2 = 0;	

    //��Եģ�� canͨ������
    fcu_data_buffer.galvanic_pile_data_buffer.insulation_monitor_working_communication_status = working_communication_outage;
	fcu_data_buffer.galvanic_pile_data_buffer.insulation_monitor_fault_level = 0;
	fcu_data_buffer.galvanic_pile_data_buffer.insulation_monitor_error_code = 0;
	fcu_data_buffer.galvanic_pile_data_buffer.insulation_resistance_value = 0;
	fcu_data_buffer.galvanic_pile_data_buffer.insulation_battery_voltage = 0;
	
	//���ݱ�����  
	fcu_data_buffer.islock = unlock;
}


//ͨ��ͨ��  ��������   ��ѹ��������ѭ����
void FCU_data_buffer_updata_by_communication(void)
{

	//��������ˣ���ôһֱ�ȴ���ֱ����������ע�⣬���timer��ʱ�䲻��������ô�ᵼ�³������������ǿ�����
	while(fcu_data_buffer.islock == lock);

	if(fcu_data_buffer.islock == unlock)
	{
		fcu_data_buffer.islock = lock;
         
		//����ѭ����  can
		if(system_time - can_communication_protocol2_total.h2_circulating_pump_data.updata_event_time
			> can_communication_protocol2_total.h2_circulating_pump_data.overtime_max)
		{
			fcu_data_buffer.h2_data_buffer.h2_circulating_pump_working_communication_status = working_communication_outage;
		}
		else
		{
			fcu_data_buffer.h2_data_buffer.h2_circulating_pump_working_communication_status = working_communication_normal;

			can_communication_protocol2_total.h2_pump_control_msg.Mass_Flow_Setpoint = 
				fcu_data_buffer.h2_data_buffer.h2_circulating_pump_mass_flow_setpoint;
			//����Ƚ����⣬��Ϊ����ѭ���õı������ԣ�2�����ϣ�����ת��50%�����Լ����˰ٷֱ�
			can_communication_protocol2_total.h2_pump_control_msg.Speed_setpoint = 
				fcu_data_buffer.h2_data_buffer.h2_circulating_pump_speed_setpoint *
				fcu_data_buffer.h2_data_buffer.h2_circulating_pump_speed_setpoint_percent;
				
			can_communication_protocol2_total.h2_pump_control_msg.Enable_Pump = 
				fcu_data_buffer.h2_data_buffer.h2_circulating_pump_enable_pump ;
			can_communication_protocol2_total.h2_pump_control_msg.Enable_Mass_Flow_Govemor = 
				fcu_data_buffer.h2_data_buffer.h2_circulating_pump_enable_mass_flow_govemor ;

			fcu_data_buffer.h2_data_buffer.h2_circulating_pump_actual_mass_flow =          
				can_communication_protocol2_total.h2_circulating_pump_data.Actual_mass_flow; 
			fcu_data_buffer.h2_data_buffer.h2_circulating_pump_actual_speed =          
				can_communication_protocol2_total.h2_circulating_pump_data.Actual_speed; 
			fcu_data_buffer.h2_data_buffer.h2_circulating_pump_actual_current =          
				can_communication_protocol2_total.h2_circulating_pump_data.Actual_current; 
			fcu_data_buffer.h2_data_buffer.h2_circulating_pump_actual_voltage =          
				can_communication_protocol2_total.h2_circulating_pump_data.Actual_voltage; 
			fcu_data_buffer.h2_data_buffer.h2_circulating_pump_actual_electronic_temperature =          
				can_communication_protocol2_total.h2_circulating_pump_data.Actual_electronic_temperature; 
			fcu_data_buffer.h2_data_buffer.h2_circulating_pump_actual_air_temperature =          
				can_communication_protocol2_total.h2_circulating_pump_data.Actual_air_temperature; 
			fcu_data_buffer.h2_data_buffer.h2_circulating_pump_status_diagnose_word =          
				can_communication_protocol2_total.h2_circulating_pump_data.status_diagnose_word; 
		}


		//��ѹ��  can
		if(system_time - can_communication_protocol2_total.air_compressor_stats_msg2.updata_event_time
			> can_communication_protocol2_total.air_compressor_stats_msg2.overtime_max  && 
			system_time - can_communication_protocol2_total.air_compressor_alarm_msg3.updata_event_time
			> can_communication_protocol2_total.air_compressor_alarm_msg3.overtime_max	)
		{
			fcu_data_buffer.air_data_buffer.air_compressor_working_communication_status = working_communication_outage;
		}
		else
		{
			fcu_data_buffer.air_data_buffer.air_compressor_working_communication_status = working_communication_normal;


			can_communication_protocol2_total.air_compressor_control_msg.CompressorStart = 
				fcu_data_buffer.air_data_buffer.air_compressor_enable ;

			if(fcu_data_buffer.air_data_buffer.air_compressor_speed_setpoint + 
				fcu_data_buffer.air_data_buffer.air_compressor_speed_setpoint_increment >80000)
			{
				can_communication_protocol2_total.air_compressor_control_msg.SpeedSetpoint = 80000;
			}
			else
			{
				can_communication_protocol2_total.air_compressor_control_msg.SpeedSetpoint = 
					fcu_data_buffer.air_data_buffer.air_compressor_speed_setpoint +
					fcu_data_buffer.air_data_buffer.air_compressor_speed_setpoint_increment;
			}

			fcu_data_buffer.air_data_buffer.air_compressor_input_electricity =     
				can_communication_protocol2_total.air_compressor_stats_msg2.InputCur;   
			fcu_data_buffer.air_data_buffer.air_compressor_input_voltage =     
				can_communication_protocol2_total.air_compressor_stats_msg2.InputVol;    
			fcu_data_buffer.air_data_buffer.air_compressor_output_power =     
				can_communication_protocol2_total.air_compressor_stats_msg2.OutPutPower;    
			fcu_data_buffer.air_data_buffer.air_compressor_motor_temperature =     
				can_communication_protocol2_total.air_compressor_stats_msg2.MotorTemp;    
			fcu_data_buffer.air_data_buffer.air_compressor_converter_temperature =     
				can_communication_protocol2_total.air_compressor_stats_msg2.ConverterTemp;    
			fcu_data_buffer.air_data_buffer.air_compressor_inside_temperature =     
				can_communication_protocol2_total.air_compressor_stats_msg2.InsideTemp;   
			fcu_data_buffer.air_data_buffer.air_compressor_state =     
				can_communication_protocol2_total.air_compressor_alarm_msg3.CompressorState;    
			fcu_data_buffer.air_data_buffer.air_compressor_fault_code =     
				can_communication_protocol2_total.air_compressor_alarm_msg3.FaultCode;    
			fcu_data_buffer.air_data_buffer.air_compressor_fault_level =     
				can_communication_protocol2_total.air_compressor_alarm_msg3.faultLev;    
			fcu_data_buffer.air_data_buffer.air_compressor_act_speed =     
				can_communication_protocol2_total.air_compressor_alarm_msg3.ActSpeed;    

		}
           

		//Ѳ��  can
		if(system_time - can_communication_protocol2_total.itinerant_detective_operate_statas.updata_event_time
			> can_communication_protocol2_total.itinerant_detective_operate_statas.overtime_max  && 
			system_time - can_communication_protocol2_total.itinerant_detective_single_chip_highest_voltage.updata_event_time
			> can_communication_protocol2_total.itinerant_detective_single_chip_highest_voltage.overtime_max  && 
			system_time - can_communication_protocol2_total.itinerant_detective_single_chip_minimum_voltage.updata_event_time
			> can_communication_protocol2_total.itinerant_detective_single_chip_minimum_voltage.overtime_max  && 
			system_time - can_communication_protocol2_total.itinerant_detective_voltage_data.updata_event_time
			> can_communication_protocol2_total.itinerant_detective_voltage_data.overtime_max  	)
		{
			fcu_data_buffer.galvanic_pile_data_buffer.itinerant_detective_working_communication_status = working_communication_outage;
		}
		else
		{
			fcu_data_buffer.galvanic_pile_data_buffer.itinerant_detective_working_communication_status = working_communication_normal;

			fcu_data_buffer.galvanic_pile_data_buffer.itinerant_detective_working_statas = 
				can_communication_protocol2_total.itinerant_detective_operate_statas.itinerant_detective_working_statas;
			fcu_data_buffer.galvanic_pile_data_buffer.Single_battery_overvoltage_alarm = 
				can_communication_protocol2_total.itinerant_detective_operate_statas.Single_battery_overvoltage_alarm;
			fcu_data_buffer.galvanic_pile_data_buffer.Single_battery_undervoltage_alarm = 
				can_communication_protocol2_total.itinerant_detective_operate_statas.Single_battery_undervoltage_alarm;
			fcu_data_buffer.galvanic_pile_data_buffer.Single_voltage_unbalance_alarm = 
				can_communication_protocol2_total.itinerant_detective_operate_statas.Single_voltage_unbalance_alarm;
			fcu_data_buffer.galvanic_pile_data_buffer.electric1_mean_voltage = 
				can_communication_protocol2_total.itinerant_detective_operate_statas.electric1_mean_voltage;
			fcu_data_buffer.galvanic_pile_data_buffer.electric1_single_chip_highest_voltage = 
				can_communication_protocol2_total.itinerant_detective_single_chip_highest_voltage.electric1_single_chip_highest_voltage;
		   	fcu_data_buffer.galvanic_pile_data_buffer.electric1_single_chip_highest_voltage_num = 
				can_communication_protocol2_total.itinerant_detective_single_chip_highest_voltage.electric1_single_chip_highest_voltage_num;
			fcu_data_buffer.galvanic_pile_data_buffer.electric1_single_chip_minimum_voltage = 
				can_communication_protocol2_total.itinerant_detective_single_chip_minimum_voltage.electric1_single_chip_minimum_voltage;
			fcu_data_buffer.galvanic_pile_data_buffer.electric1_single_chip_minimum_voltage_num = 
				can_communication_protocol2_total.itinerant_detective_single_chip_minimum_voltage.electric1_single_chip_minimum_voltage_num;
			fcu_data_buffer.galvanic_pile_data_buffer.itinerant_detective_total_voltage = 
				can_communication_protocol2_total.itinerant_detective_voltage_data.Itinerant_detective_total_voltage;

		}
		
		//Ѳ��  can
		if(system_time - can_communication_protocol2_total.itinerant_detective_operate_statas2.updata_event_time
			> can_communication_protocol2_total.itinerant_detective_operate_statas2.overtime_max  && 
			system_time - can_communication_protocol2_total.itinerant_detective_single_chip_highest_voltage2.updata_event_time
			> can_communication_protocol2_total.itinerant_detective_single_chip_highest_voltage2.overtime_max  && 
			system_time - can_communication_protocol2_total.itinerant_detective_single_chip_minimum_voltage2.updata_event_time
			> can_communication_protocol2_total.itinerant_detective_single_chip_minimum_voltage2.overtime_max  && 
			system_time - can_communication_protocol2_total.itinerant_detective_voltage_data2.updata_event_time
			> can_communication_protocol2_total.itinerant_detective_voltage_data2.overtime_max  	)
		{
			fcu_data_buffer.galvanic_pile_data_buffer.itinerant_detective_working_communication_status2 = working_communication_outage;
		}
		else
		{
			fcu_data_buffer.galvanic_pile_data_buffer.itinerant_detective_working_communication_status2 = working_communication_normal;

			fcu_data_buffer.galvanic_pile_data_buffer.itinerant_detective_working_statas2 = 
				can_communication_protocol2_total.itinerant_detective_operate_statas2.itinerant_detective_working_statas;
			fcu_data_buffer.galvanic_pile_data_buffer.Single_battery_overvoltage_alarm2 = 
				can_communication_protocol2_total.itinerant_detective_operate_statas2.Single_battery_overvoltage_alarm;
			fcu_data_buffer.galvanic_pile_data_buffer.Single_battery_undervoltage_alarm2 = 
				can_communication_protocol2_total.itinerant_detective_operate_statas2.Single_battery_undervoltage_alarm;
			fcu_data_buffer.galvanic_pile_data_buffer.Single_voltage_unbalance_alarm2 = 
				can_communication_protocol2_total.itinerant_detective_operate_statas2.Single_voltage_unbalance_alarm;
			fcu_data_buffer.galvanic_pile_data_buffer.electric1_mean_voltage2 = 
				can_communication_protocol2_total.itinerant_detective_operate_statas2.electric1_mean_voltage;
			fcu_data_buffer.galvanic_pile_data_buffer.electric1_single_chip_highest_voltage2 = 
				can_communication_protocol2_total.itinerant_detective_single_chip_highest_voltage2.electric1_single_chip_highest_voltage;
		   	fcu_data_buffer.galvanic_pile_data_buffer.electric1_single_chip_highest_voltage_num2 = 
				can_communication_protocol2_total.itinerant_detective_single_chip_highest_voltage2.electric1_single_chip_highest_voltage_num;
			fcu_data_buffer.galvanic_pile_data_buffer.electric1_single_chip_minimum_voltage2 = 
				can_communication_protocol2_total.itinerant_detective_single_chip_minimum_voltage2.electric1_single_chip_minimum_voltage;
			fcu_data_buffer.galvanic_pile_data_buffer.electric1_single_chip_minimum_voltage_num2 = 
				can_communication_protocol2_total.itinerant_detective_single_chip_minimum_voltage2.electric1_single_chip_minimum_voltage_num;
			fcu_data_buffer.galvanic_pile_data_buffer.itinerant_detective_total_voltage2 = 
				can_communication_protocol2_total.itinerant_detective_voltage_data2.Itinerant_detective_total_voltage;

		}
	
		//��Եģ�� canͨ������
    	if(system_time - can_communication_protocol2_total.insulation_monitor_data.updata_event_time
			> can_communication_protocol2_total.insulation_monitor_data.overtime_max)
		{
			fcu_data_buffer.galvanic_pile_data_buffer.insulation_monitor_working_communication_status = working_communication_outage;
		}
		else
		{
			fcu_data_buffer.galvanic_pile_data_buffer.insulation_monitor_working_communication_status = working_communication_normal;

			fcu_data_buffer.galvanic_pile_data_buffer.insulation_monitor_fault_level =          
				can_communication_protocol2_total.insulation_monitor_data.fault_level; 
			fcu_data_buffer.galvanic_pile_data_buffer.insulation_monitor_error_code =          
				can_communication_protocol2_total.insulation_monitor_data.error_code; 
			fcu_data_buffer.galvanic_pile_data_buffer.insulation_resistance_value =          
				can_communication_protocol2_total.insulation_monitor_data.Insulation_resistance_value; 
			fcu_data_buffer.galvanic_pile_data_buffer.insulation_battery_voltage =          
				can_communication_protocol2_total.insulation_monitor_data.Battery_voltage; 
		}
		                 
	/*	      
		//ad�ɼ� ������    can��Ϣ
		//Ŀǰ��ֻ����ʱ��canЭ�顣�Ͳ���ͨ���ж��ˡ�
//	    fcu_data_buffer.air_data_buffer.air_rate_of_flow = 
//	        atd_voltage_calculation_for_air_rate_of_flow(can_communication_protocol2_total.ad_auxiliary_board_message_array[3].ad_auxiliary_board_message_data[0]);
		fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_voltage = 
		    atd_voltage_calculation_for_pile_voltage(can_communication_protocol2_total.ad_auxiliary_board_message_array[0].ad_auxiliary_board_message_data[3], 500);
		fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_electricity = 
		    atd_voltage_calculation_for_pile_electricity(can_communication_protocol2_total.ad_auxiliary_board_message_array[1].ad_auxiliary_board_message_data[0]) +3;
	
	 //   fcu_data_buffer.h2_data_buffer.h2_pressure_pile_inlet = 
	 //       atd_electricity_calculation(can_communication_protocol2_total.ad_auxiliary_board_message_array[2].ad_auxiliary_board_message_data[3], 150);
        fcu_data_buffer.h2_data_buffer.h2_pressure_pile_inlet1 = 
	        atd_electricity_calculation(can_communication_protocol2_total.ad_auxiliary_board_message_array[4].ad_auxiliary_board_message_data[3], 150);
	    fcu_data_buffer.h2_data_buffer.h2_pressure_pile_inlet2 = 
	        atd_electricity_calculation(can_communication_protocol2_total.ad_auxiliary_board_message_array[0].ad_auxiliary_board_message_data[2], 100);
	    fcu_data_buffer.h2_data_buffer.h2_pressure_pile_outlet1 = 
	        atd_electricity_calculation(can_communication_protocol2_total.ad_auxiliary_board_message_array[0].ad_auxiliary_board_message_data[1], 150);
	    fcu_data_buffer.h2_data_buffer.h2_pressure_pile_outlet2 = 
	        atd_electricity_calculation(can_communication_protocol2_total.ad_auxiliary_board_message_array[2].ad_auxiliary_board_message_data[2], 150);
	    fcu_data_buffer.water_for_compressor_data_bufferr.water_pressure_compressor_outlet = 
	        atd_electricity_calculation(can_communication_protocol2_total.ad_auxiliary_board_message_array[2].ad_auxiliary_board_message_data[1], 250);
     */           

		fcu_data_buffer.islock = unlock;
	}
}