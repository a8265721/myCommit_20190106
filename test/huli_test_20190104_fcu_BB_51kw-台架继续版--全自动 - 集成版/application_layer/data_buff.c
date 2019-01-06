
#include"data_buff.h"

struct FCU_Data_Buffer		fcu_data_buffer  ;

                  

//初始化
void FCU_data_buffer_init(void)    
{                                        
	//氢气数据层                                               
	//输入
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
	
	//输出
	fcu_data_buffer.h2_data_buffer.h2_inlet_valve = 0;
	fcu_data_buffer.h2_data_buffer.h2_outlet_valve = 0;
	fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pwm_dutyfactor = 0;
	//注意了，这里一定要在上电之后就瞬间打开 氢气循环泵的IO使能，这样才会有can通信，
	fcu_data_buffer.h2_data_buffer.h2_circulating_pump_enble = 1; 

	//氢气循环泵转速设定  百分比	二级告警之后，降速使用的	1指的是100%
	fcu_data_buffer.h2_data_buffer.h2_circulating_pump_speed_setpoint_percent = 1;
	//氢气循环泵  can通信
	fcu_data_buffer.h2_data_buffer.h2_circulating_pump_working_communication_status = working_communication_outage;
	fcu_data_buffer.h2_data_buffer.h2_circulating_pump_mass_flow_setpoint = 0;
	fcu_data_buffer.h2_data_buffer.h2_circulating_pump_speed_setpoint = H2_CIRCULATING_PUMP_SPEED_SETPOINT_1500;
	fcu_data_buffer.h2_data_buffer.h2_circulating_pump_enable_pump = 0;
	fcu_data_buffer.h2_data_buffer.h2_circulating_pump_enable_mass_flow_govemor = 0;
	fcu_data_buffer.h2_data_buffer.h2_circulating_pump_actual_mass_flow = 0;       							//  质量流量
	fcu_data_buffer.h2_data_buffer.h2_circulating_pump_actual_speed = 0;       					            //  氢气循环泵转速
	fcu_data_buffer.h2_data_buffer.h2_circulating_pump_actual_current = 0;      								//  氢气循环泵电流
	fcu_data_buffer.h2_data_buffer.h2_circulating_pump_actual_voltage = 0;      								//  氢气循环泵电压
	fcu_data_buffer.h2_data_buffer.h2_circulating_pump_actual_electronic_temperature = 0;                     //  氢气循环泵电机温度
	fcu_data_buffer.h2_data_buffer.h2_circulating_pump_actual_air_temperature = 0;       		        	    //  氢气循环泵气体温度
	fcu_data_buffer.h2_data_buffer.h2_circulating_pump_status_diagnose_word = 0;      		    		    //  氢气循环泵状态诊断字节

	//pid控制
	fcu_data_buffer.h2_data_buffer.h2_pressure_target_value = H2_PRESSURE_SET_VALUE_50;
	fcu_data_buffer.h2_data_buffer.h2_pressure_real_target_value = 0;
	fcu_data_buffer.h2_data_buffer.h2_pressure_advance_current_value = 0;    //氢压 提前量  实际值
	fcu_data_buffer.h2_data_buffer.h2_pressure_advance_set_value = 0;    //氢压 提前量  设定值  默认为0，一般设为5
	fcu_data_buffer.h2_data_buffer.h2_pressure_pid1_advance_time = H2_PRESSURE_PID1_ADVANCE_TIME;     //氢压 pid1时间提前量      默认250ms
	fcu_data_buffer.h2_data_buffer.h2_pressure_pid2_advance_time = H2_PRESSURE_PID2_ADVANCE_TIME;    //氢压 pid2时间提前量      默认1000ms	        	
	PID_init(&(fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid1), PID1_KP, PID1_KI, PID1_KD);
	PID_init(&(fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid2), PID2_KP, PID2_KI, PID2_KD);				
	fcu_data_buffer.h2_data_buffer.h2_pid_mode = 0;        //pid算法控制模式，1表示使用pid1来控制，2表示使用pid2来控制

	//氢气尾排控制
	fcu_data_buffer.h2_data_buffer.h2_is_enable_outlet_valve = 0;
	fcu_data_buffer.h2_data_buffer.h2_outlet_valve_current_time = 0;		//尾排阀当前的时间	
	fcu_data_buffer.h2_data_buffer.h2_outlet_valve_open_time = H2_OUTLET_VALVE_OPEN_TIME_500;
	fcu_data_buffer.h2_data_buffer.h2_outlet_valve_close_time = H2_OUTLET_VALVE_CLOSE_TIME_1000;

	//氢压波动
	fcu_data_buffer.h2_data_buffer.h2_pressure_fluctuate_reset = 0;            //氢压 波动  重置
	fcu_data_buffer.h2_data_buffer.h2_pressure_fluctuate_current_max = 0;      //氢压 波动  当前最大值
	fcu_data_buffer.h2_data_buffer.h2_pressure_fluctuate_current_min = 0;      //氢压 波动  当前最小值
	fcu_data_buffer.h2_data_buffer.h2_pressure_fluctuate_last_max = 0;		    //氢压 波动  上次最大值
	fcu_data_buffer.h2_data_buffer.h2_pressure_fluctuate_last_min = 0;			//氢压 波动  上次最小值



	//空气数据层    
	fcu_data_buffer.air_data_buffer.air_temperature_pile_inlet_duration_time = 0;//入堆温度超过75度的持续时间（超过20s，则报一级故障）
	//输入
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

	//输出
	fcu_data_buffer.air_data_buffer.air_outlet_valve = 0;

	fcu_data_buffer.air_data_buffer.air_compressor_speed_setpoint_increment = 0;//空压机转速，控制变频器，增量
	//空压机  can
	fcu_data_buffer.air_data_buffer.air_compressor_working_communication_status = working_communication_outage;
	fcu_data_buffer.air_data_buffer.air_compressor_enable = 0;
	fcu_data_buffer.air_data_buffer.air_compressor_speed_setpoint = AIR_COMPRESSOR_SPEED_SETPOINT_35000;
	fcu_data_buffer.air_data_buffer.air_compressor_input_electricity = 0;		//变频器输入电流
	fcu_data_buffer.air_data_buffer.air_compressor_input_voltage = 0;			//变频器输入电压
	fcu_data_buffer.air_data_buffer.air_compressor_output_power = 0;			//输出功率
	fcu_data_buffer.air_data_buffer.air_compressor_motor_temperature = 0;       //电机温度
	fcu_data_buffer.air_data_buffer.air_compressor_converter_temperature = 0;   //控制器温度
	fcu_data_buffer.air_data_buffer.air_compressor_inside_temperature = 0;		//空压机内部温度
	fcu_data_buffer.air_data_buffer.air_compressor_state = 0;					//空压机状态
	fcu_data_buffer.air_data_buffer.air_compressor_fault_code = 0;				//故障码
	fcu_data_buffer.air_data_buffer.air_compressor_fault_level = 0;				//故障等级
	fcu_data_buffer.air_data_buffer.air_compressor_act_speed = 0;				//空压机实际转速
	
	//20181112，按照冯工的要求，在此增加，根据空气流量来控制空压机的转速，目前使用pid调节。
	PID_init(&(fcu_data_buffer.air_data_buffer.air_compressor_speed_pid), PID_COMPRESSOR_KP, PID_COMPRESSOR_KI, PID_COMPRESSOR_KD);
	fcu_data_buffer.air_data_buffer.air_compressor_speed_pid.pid_over_time = 1000;//10秒	
	fcu_data_buffer.air_data_buffer.air_rate_of_flow_target = 0;

	//空气尾排控制
	fcu_data_buffer.air_data_buffer.air_is_enable_outlet_valve = 0;
	fcu_data_buffer.air_data_buffer.air_outlet_valve_current_time = 0;		//尾排阀当前的时间	
	fcu_data_buffer.air_data_buffer.air_outlet_valve_open_time = AIR_OUTLET_VALVE_OPEN_TIME_500;
	fcu_data_buffer.air_data_buffer.air_outlet_valve_close_time = AIR_OUTLET_VALVE_CLOSE_TIME_8000;	


	//电堆散热系统 数据层 
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
    fcu_data_buffer.water_for_pile_data_buffer.water_temperature_fan_pid1.pid_over_time = 1000;//10秒	
    fcu_data_buffer.water_for_pile_data_buffer.water_temperature_target_value1 = 0;     //电堆的水路 的温度控制，运行之后，随着电流档位控制
      
    PID_init(&(fcu_data_buffer.water_for_pile_data_buffer.water_temperature_fan_pid2), PID_WATER_KP, PID_WATER_KI, PID_WATER_KD);
    fcu_data_buffer.water_for_pile_data_buffer.water_temperature_fan_pid2.pid_over_time = 1000;//10秒	
    fcu_data_buffer.water_for_pile_data_buffer.water_temperature_target_value2 = 0;     //电堆的水路 的温度控制，运行之后，随着电流档位控制
      
	//三合一散热系统 数据层                             

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
    fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_fan_pid.pid_over_time = 1000;//10秒	
    fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_target_value = 60;  //三合一水路 的温度控制，就稳定在60度，就好了。
    
	//电堆发电的数据层
	fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_voltage = 0;
	fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_electricity = 0;
	fcu_data_buffer.galvanic_pile_data_buffer.fcu_start_enable = 0;
	fcu_data_buffer.galvanic_pile_data_buffer.fcu_stutter_stop_enable = 0;
    fcu_data_buffer.galvanic_pile_data_buffer.fcu_reset_enable = 0;
    
	fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_is_enble_output = 0;
	fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_is_enble_load_resistance = 0;

	//巡检  can
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
	
	//巡检  can
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

    //绝缘模块 can通信数据
    fcu_data_buffer.galvanic_pile_data_buffer.insulation_monitor_working_communication_status = working_communication_outage;
	fcu_data_buffer.galvanic_pile_data_buffer.insulation_monitor_fault_level = 0;
	fcu_data_buffer.galvanic_pile_data_buffer.insulation_monitor_error_code = 0;
	fcu_data_buffer.galvanic_pile_data_buffer.insulation_resistance_value = 0;
	fcu_data_buffer.galvanic_pile_data_buffer.insulation_battery_voltage = 0;
	
	//数据保护锁  
	fcu_data_buffer.islock = unlock;
}


//通过通信  更新数据   空压机和氢气循环泵
void FCU_data_buffer_updata_by_communication(void)
{

	//如果加锁了，那么一直等待，直到解锁。（注意，如果timer长时间不解锁，那么会导致程序死锁，就是卡死）
	while(fcu_data_buffer.islock == lock);

	if(fcu_data_buffer.islock == unlock)
	{
		fcu_data_buffer.islock = lock;
         
		//氢气循环泵  can
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
			//这里比较特殊，因为氢气循环泵的保护策略，2级故障，降低转速50%，所以加上了百分比
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


		//空压机  can
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
           

		//巡检  can
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
		
		//巡检  can
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
	
		//绝缘模块 can通信数据
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
		//ad采集 辅助板    can消息
		//目前就只是临时的can协议。就不做通信判断了。
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