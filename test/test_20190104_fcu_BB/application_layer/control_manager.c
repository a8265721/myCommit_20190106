
#include "control_manager.h"             


struct Control_Policy_Total_Manager   control_policy_total_manager;
u8 zxc[20] = {0};


//pcu���صĹ�����ʼ��
enum Error_code Control_Policy_Total_Manager_init(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL )
	{return Pointer_is_null;}

	p_control_policy_total_manager->working_control_mode = working_control_outage;
	p_control_policy_total_manager->working_status_mode = working_status_communication_outage;
	p_control_policy_total_manager->working_alarm_mode = working_normal;
	p_control_policy_total_manager->working_FCU_error_code = Succeed;

	p_control_policy_total_manager->fcu_updata_event_time = system_time;
	//p_control_policy_total_manager->fcu_system_change_mode_delay = FCU_SYSTEM_CHANGE_MODE_DELAY_10_SECOND;
	//p_control_policy_total_manager->fcu_system_overtime_max = FCU_SYSTEM_OVERTIME_MAX_10;
	p_control_policy_total_manager->fcu_system_running_mode = system_running_manual;
	p_control_policy_total_manager->working_error_count = 0;

	p_control_policy_total_manager->galvanic_pile_load_resistance_switch_count = 0;

	p_control_policy_total_manager->fcu_output_electricity_level = 0;
	
	//��ʱ�ӵ�һ�������жϵ���ʱ  3��
	p_control_policy_total_manager->one_level_fault_flag_temp = 0; //һ���澯���λ��0������1����һ���澯
	p_control_policy_total_manager->one_level_fault_time_temp = 0; //һ���澯���ʱ�䡣���ǳ���һ���澯��ʱ�䡣	

	p_control_policy_total_manager->fcu_run_data_debug[0].fcu_output_electricity_lower_limit = -10;
	p_control_policy_total_manager->fcu_run_data_debug[0].fcu_output_electricity_upper_limit = 65;
	p_control_policy_total_manager->fcu_run_data_debug[0].pid1_Kp = 0.3;
	p_control_policy_total_manager->fcu_run_data_debug[0].pid1_Ki = 0.00001;
	p_control_policy_total_manager->fcu_run_data_debug[0].pid1_Kd = 170;
	p_control_policy_total_manager->fcu_run_data_debug[0].pid2_Kp = 0.3;
	p_control_policy_total_manager->fcu_run_data_debug[0].pid2_Ki = 0.00001;
	p_control_policy_total_manager->fcu_run_data_debug[0].pid2_Kd = 100;
	p_control_policy_total_manager->fcu_run_data_debug[0].h2_pressure_target_value = 52;
	p_control_policy_total_manager->fcu_run_data_debug[0].h2_pressure_advance_set_value = 0;
	p_control_policy_total_manager->fcu_run_data_debug[0].h2_outlet_valve_open_time = 500;
	p_control_policy_total_manager->fcu_run_data_debug[0].h2_outlet_valve_close_time = 6000;
	p_control_policy_total_manager->fcu_run_data_debug[0].h2_circulating_pump_speed_setpoint = 3000;
	p_control_policy_total_manager->fcu_run_data_debug[0].air_compressor_speed_setpoint = 35000;
	p_control_policy_total_manager->fcu_run_data_debug[0].air_rate_of_flow_target = 960+500;
	p_control_policy_total_manager->fcu_run_data_debug[0].water_temperature_target_value = 53;

	p_control_policy_total_manager->fcu_run_data_debug[1].fcu_output_electricity_lower_limit = 55;
	p_control_policy_total_manager->fcu_run_data_debug[1].fcu_output_electricity_upper_limit = 95;
	p_control_policy_total_manager->fcu_run_data_debug[1].pid1_Kp = 0.3;
	p_control_policy_total_manager->fcu_run_data_debug[1].pid1_Ki = 0.00001;
	p_control_policy_total_manager->fcu_run_data_debug[1].pid1_Kd = 170;
	p_control_policy_total_manager->fcu_run_data_debug[1].pid2_Kp = 0.3;
	p_control_policy_total_manager->fcu_run_data_debug[1].pid2_Ki = 0.00001;
	p_control_policy_total_manager->fcu_run_data_debug[1].pid2_Kd = 100;
	p_control_policy_total_manager->fcu_run_data_debug[1].h2_pressure_target_value = 57;
	p_control_policy_total_manager->fcu_run_data_debug[1].h2_pressure_advance_set_value = 0;
	p_control_policy_total_manager->fcu_run_data_debug[1].h2_outlet_valve_open_time = 800;
	p_control_policy_total_manager->fcu_run_data_debug[1].h2_outlet_valve_close_time = 6000;
	p_control_policy_total_manager->fcu_run_data_debug[1].h2_circulating_pump_speed_setpoint = 3000;
	p_control_policy_total_manager->fcu_run_data_debug[1].air_compressor_speed_setpoint = 35000;
	p_control_policy_total_manager->fcu_run_data_debug[1].air_rate_of_flow_target = 1192+500;
	p_control_policy_total_manager->fcu_run_data_debug[1].water_temperature_target_value = 57;

	p_control_policy_total_manager->fcu_run_data_debug[2].fcu_output_electricity_lower_limit = 85;
	p_control_policy_total_manager->fcu_run_data_debug[2].fcu_output_electricity_upper_limit = 125;
	p_control_policy_total_manager->fcu_run_data_debug[2].pid1_Kp = 0.3;
	p_control_policy_total_manager->fcu_run_data_debug[2].pid1_Ki = 0.00001;
	p_control_policy_total_manager->fcu_run_data_debug[2].pid1_Kd = 170;
	p_control_policy_total_manager->fcu_run_data_debug[2].pid2_Kp = 0.3;
	p_control_policy_total_manager->fcu_run_data_debug[2].pid2_Ki = 0.00001;
	p_control_policy_total_manager->fcu_run_data_debug[2].pid2_Kd = 100;
	p_control_policy_total_manager->fcu_run_data_debug[2].h2_pressure_target_value = 57;
	p_control_policy_total_manager->fcu_run_data_debug[2].h2_pressure_advance_set_value = 0;
	p_control_policy_total_manager->fcu_run_data_debug[2].h2_outlet_valve_open_time = 800;
	p_control_policy_total_manager->fcu_run_data_debug[2].h2_outlet_valve_close_time = 6000;
	p_control_policy_total_manager->fcu_run_data_debug[2].h2_circulating_pump_speed_setpoint = 3000;
	p_control_policy_total_manager->fcu_run_data_debug[2].air_compressor_speed_setpoint = 45000;
	p_control_policy_total_manager->fcu_run_data_debug[2].air_rate_of_flow_target = 1476+500;
	p_control_policy_total_manager->fcu_run_data_debug[2].water_temperature_target_value = 57;

	p_control_policy_total_manager->fcu_run_data_debug[3].fcu_output_electricity_lower_limit = 115;
	p_control_policy_total_manager->fcu_run_data_debug[3].fcu_output_electricity_upper_limit = 155;
	p_control_policy_total_manager->fcu_run_data_debug[3].pid1_Kp = 0.3;
	p_control_policy_total_manager->fcu_run_data_debug[3].pid1_Ki = 0.00001;
	p_control_policy_total_manager->fcu_run_data_debug[3].pid1_Kd = 170;
	p_control_policy_total_manager->fcu_run_data_debug[3].pid2_Kp = 0.3;
	p_control_policy_total_manager->fcu_run_data_debug[3].pid2_Ki = 0.00001;
	p_control_policy_total_manager->fcu_run_data_debug[3].pid2_Kd = 100;
	p_control_policy_total_manager->fcu_run_data_debug[3].h2_pressure_target_value = 62;
	p_control_policy_total_manager->fcu_run_data_debug[3].h2_pressure_advance_set_value = 0;
	p_control_policy_total_manager->fcu_run_data_debug[3].h2_outlet_valve_open_time = 1000;
	p_control_policy_total_manager->fcu_run_data_debug[3].h2_outlet_valve_close_time = 6000;
	p_control_policy_total_manager->fcu_run_data_debug[3].h2_circulating_pump_speed_setpoint = 3000;
	p_control_policy_total_manager->fcu_run_data_debug[3].air_compressor_speed_setpoint = 55000;
	p_control_policy_total_manager->fcu_run_data_debug[3].air_rate_of_flow_target = 1702+500;
	p_control_policy_total_manager->fcu_run_data_debug[3].water_temperature_target_value = 61;

	p_control_policy_total_manager->fcu_run_data_debug[4].fcu_output_electricity_lower_limit = 145;
	p_control_policy_total_manager->fcu_run_data_debug[4].fcu_output_electricity_upper_limit = 185;
	p_control_policy_total_manager->fcu_run_data_debug[4].pid1_Kp = 0.3;
	p_control_policy_total_manager->fcu_run_data_debug[4].pid1_Ki = 0.00001;
	p_control_policy_total_manager->fcu_run_data_debug[4].pid1_Kd = 170;
	p_control_policy_total_manager->fcu_run_data_debug[4].pid2_Kp = 0.3;
	p_control_policy_total_manager->fcu_run_data_debug[4].pid2_Ki = 0.00001;
	p_control_policy_total_manager->fcu_run_data_debug[4].pid2_Kd = 100;
	p_control_policy_total_manager->fcu_run_data_debug[4].h2_pressure_target_value = 62;
	p_control_policy_total_manager->fcu_run_data_debug[4].h2_pressure_advance_set_value = 0;
	p_control_policy_total_manager->fcu_run_data_debug[4].h2_outlet_valve_open_time = 1000;
	p_control_policy_total_manager->fcu_run_data_debug[4].h2_outlet_valve_close_time = 6000;
	p_control_policy_total_manager->fcu_run_data_debug[4].h2_circulating_pump_speed_setpoint = 3000;
	p_control_policy_total_manager->fcu_run_data_debug[4].air_compressor_speed_setpoint = 60000;
	p_control_policy_total_manager->fcu_run_data_debug[4].air_rate_of_flow_target = 2044+500;
	p_control_policy_total_manager->fcu_run_data_debug[4].water_temperature_target_value = 61;

	p_control_policy_total_manager->fcu_run_data_debug[5].fcu_output_electricity_lower_limit = 175;
	p_control_policy_total_manager->fcu_run_data_debug[5].fcu_output_electricity_upper_limit = 215;
	p_control_policy_total_manager->fcu_run_data_debug[5].pid1_Kp = 0.3;
	p_control_policy_total_manager->fcu_run_data_debug[5].pid1_Ki = 0.00001;
	p_control_policy_total_manager->fcu_run_data_debug[5].pid1_Kd = 170;
	p_control_policy_total_manager->fcu_run_data_debug[5].pid2_Kp = 0.3;
	p_control_policy_total_manager->fcu_run_data_debug[5].pid2_Ki = 0.00001;
	p_control_policy_total_manager->fcu_run_data_debug[5].pid2_Kd = 100;
	p_control_policy_total_manager->fcu_run_data_debug[5].h2_pressure_target_value = 67;
	p_control_policy_total_manager->fcu_run_data_debug[5].h2_pressure_advance_set_value = 0;
	p_control_policy_total_manager->fcu_run_data_debug[5].h2_outlet_valve_open_time = 1000;
	p_control_policy_total_manager->fcu_run_data_debug[5].h2_outlet_valve_close_time = 5000;
	p_control_policy_total_manager->fcu_run_data_debug[5].h2_circulating_pump_speed_setpoint = 3000;
	p_control_policy_total_manager->fcu_run_data_debug[5].air_compressor_speed_setpoint = 65000;
	p_control_policy_total_manager->fcu_run_data_debug[5].air_rate_of_flow_target = 2284+500;
	p_control_policy_total_manager->fcu_run_data_debug[5].water_temperature_target_value = 63;

	p_control_policy_total_manager->fcu_run_data_debug[6].fcu_output_electricity_lower_limit = 205;
	p_control_policy_total_manager->fcu_run_data_debug[6].fcu_output_electricity_upper_limit = 245;
	p_control_policy_total_manager->fcu_run_data_debug[6].pid1_Kp = 0.3;
	p_control_policy_total_manager->fcu_run_data_debug[6].pid1_Ki = 0.00001;
	p_control_policy_total_manager->fcu_run_data_debug[6].pid1_Kd = 170;
	p_control_policy_total_manager->fcu_run_data_debug[6].pid2_Kp = 0.3;
	p_control_policy_total_manager->fcu_run_data_debug[6].pid2_Ki = 0.00001;
	p_control_policy_total_manager->fcu_run_data_debug[6].pid2_Kd = 100;
	p_control_policy_total_manager->fcu_run_data_debug[6].h2_pressure_target_value = 67;
	p_control_policy_total_manager->fcu_run_data_debug[6].h2_pressure_advance_set_value = 0;
	p_control_policy_total_manager->fcu_run_data_debug[6].h2_outlet_valve_open_time = 1000;
	p_control_policy_total_manager->fcu_run_data_debug[6].h2_outlet_valve_close_time = 5000;
	p_control_policy_total_manager->fcu_run_data_debug[6].h2_circulating_pump_speed_setpoint = 3000;
	p_control_policy_total_manager->fcu_run_data_debug[6].air_compressor_speed_setpoint = 70000;
	p_control_policy_total_manager->fcu_run_data_debug[6].air_rate_of_flow_target = 2610+500;
	p_control_policy_total_manager->fcu_run_data_debug[6].water_temperature_target_value = 63;

	p_control_policy_total_manager->fcu_run_data_debug[7].fcu_output_electricity_lower_limit = 235;
	p_control_policy_total_manager->fcu_run_data_debug[7].fcu_output_electricity_upper_limit = 275;
	p_control_policy_total_manager->fcu_run_data_debug[7].pid1_Kp = 0.3;
	p_control_policy_total_manager->fcu_run_data_debug[7].pid1_Ki = 0.00001;
	p_control_policy_total_manager->fcu_run_data_debug[7].pid1_Kd = 170;
	p_control_policy_total_manager->fcu_run_data_debug[7].pid2_Kp = 0.3;
	p_control_policy_total_manager->fcu_run_data_debug[7].pid2_Ki = 0.00001;
	p_control_policy_total_manager->fcu_run_data_debug[7].pid2_Kd = 100;
	p_control_policy_total_manager->fcu_run_data_debug[7].h2_pressure_target_value = 72;
	p_control_policy_total_manager->fcu_run_data_debug[7].h2_pressure_advance_set_value = 0;
	p_control_policy_total_manager->fcu_run_data_debug[7].h2_outlet_valve_open_time = 1000;
	p_control_policy_total_manager->fcu_run_data_debug[7].h2_outlet_valve_close_time = 4000;
	p_control_policy_total_manager->fcu_run_data_debug[7].h2_circulating_pump_speed_setpoint = 3000;
	p_control_policy_total_manager->fcu_run_data_debug[7].air_compressor_speed_setpoint = 76000;
	p_control_policy_total_manager->fcu_run_data_debug[7].air_rate_of_flow_target = 2936+500;
	p_control_policy_total_manager->fcu_run_data_debug[7].water_temperature_target_value = 65;

	p_control_policy_total_manager->fcu_run_data_debug[8].fcu_output_electricity_lower_limit = 265;
	p_control_policy_total_manager->fcu_run_data_debug[8].fcu_output_electricity_upper_limit = 305;
	p_control_policy_total_manager->fcu_run_data_debug[8].pid1_Kp = 0.3;
	p_control_policy_total_manager->fcu_run_data_debug[8].pid1_Ki = 0.00001;
	p_control_policy_total_manager->fcu_run_data_debug[8].pid1_Kd = 170;
	p_control_policy_total_manager->fcu_run_data_debug[8].pid2_Kp = 0.3;
	p_control_policy_total_manager->fcu_run_data_debug[8].pid2_Ki = 0.00001;
	p_control_policy_total_manager->fcu_run_data_debug[8].pid2_Kd = 100;
	p_control_policy_total_manager->fcu_run_data_debug[8].h2_pressure_target_value = 72;
	p_control_policy_total_manager->fcu_run_data_debug[8].h2_pressure_advance_set_value = 0;
	p_control_policy_total_manager->fcu_run_data_debug[8].h2_outlet_valve_open_time = 1000;
	p_control_policy_total_manager->fcu_run_data_debug[8].h2_outlet_valve_close_time = 4000;
	p_control_policy_total_manager->fcu_run_data_debug[8].h2_circulating_pump_speed_setpoint = 3000;
	p_control_policy_total_manager->fcu_run_data_debug[8].air_compressor_speed_setpoint = 80000;
	p_control_policy_total_manager->fcu_run_data_debug[8].air_rate_of_flow_target = 3264+500;
	p_control_policy_total_manager->fcu_run_data_debug[8].water_temperature_target_value = 65;
	
	p_control_policy_total_manager->fcu_run_data_debug[9].fcu_output_electricity_lower_limit = 295;
	p_control_policy_total_manager->fcu_run_data_debug[9].fcu_output_electricity_upper_limit = 325;
	p_control_policy_total_manager->fcu_run_data_debug[9].pid1_Kp = 0.3;
	p_control_policy_total_manager->fcu_run_data_debug[9].pid1_Ki = 0.00001;
	p_control_policy_total_manager->fcu_run_data_debug[9].pid1_Kd = 170;
	p_control_policy_total_manager->fcu_run_data_debug[9].pid2_Kp = 0.3;
	p_control_policy_total_manager->fcu_run_data_debug[9].pid2_Ki = 0.00001;
	p_control_policy_total_manager->fcu_run_data_debug[9].pid2_Kd = 100;
	p_control_policy_total_manager->fcu_run_data_debug[9].h2_pressure_target_value = 77;
	p_control_policy_total_manager->fcu_run_data_debug[9].h2_pressure_advance_set_value = 0;
	p_control_policy_total_manager->fcu_run_data_debug[9].h2_outlet_valve_open_time = 2000;
	p_control_policy_total_manager->fcu_run_data_debug[9].h2_outlet_valve_close_time = 4000;
	p_control_policy_total_manager->fcu_run_data_debug[9].h2_circulating_pump_speed_setpoint = 3000;
	p_control_policy_total_manager->fcu_run_data_debug[9].air_compressor_speed_setpoint = 82000;
	p_control_policy_total_manager->fcu_run_data_debug[9].air_rate_of_flow_target = 3524+500;
	p_control_policy_total_manager->fcu_run_data_debug[9].water_temperature_target_value = 66;	
	
	p_control_policy_total_manager->fcu_run_data_debug[10].fcu_output_electricity_lower_limit = 315;
	p_control_policy_total_manager->fcu_run_data_debug[10].fcu_output_electricity_upper_limit = 345;
	p_control_policy_total_manager->fcu_run_data_debug[10].pid1_Kp = 0.3;
	p_control_policy_total_manager->fcu_run_data_debug[10].pid1_Ki = 0.00001;
	p_control_policy_total_manager->fcu_run_data_debug[10].pid1_Kd = 170;
	p_control_policy_total_manager->fcu_run_data_debug[10].pid2_Kp = 0.3;
	p_control_policy_total_manager->fcu_run_data_debug[10].pid2_Ki = 0.00001;
	p_control_policy_total_manager->fcu_run_data_debug[10].pid2_Kd = 100;
	p_control_policy_total_manager->fcu_run_data_debug[10].h2_pressure_target_value = 77;
	p_control_policy_total_manager->fcu_run_data_debug[10].h2_pressure_advance_set_value = 0;
	p_control_policy_total_manager->fcu_run_data_debug[10].h2_outlet_valve_open_time = 2000;
	p_control_policy_total_manager->fcu_run_data_debug[10].h2_outlet_valve_close_time = 4000;
	p_control_policy_total_manager->fcu_run_data_debug[10].h2_circulating_pump_speed_setpoint = 3000;
	p_control_policy_total_manager->fcu_run_data_debug[10].air_compressor_speed_setpoint = 82000;
	p_control_policy_total_manager->fcu_run_data_debug[10].air_rate_of_flow_target = 3588+500;
	p_control_policy_total_manager->fcu_run_data_debug[10].water_temperature_target_value = 67;		

	p_control_policy_total_manager->fcu_run_data_debug[11].fcu_output_electricity_lower_limit = 335;
	p_control_policy_total_manager->fcu_run_data_debug[11].fcu_output_electricity_upper_limit = 365;
	p_control_policy_total_manager->fcu_run_data_debug[11].pid1_Kp = 0.3;
	p_control_policy_total_manager->fcu_run_data_debug[11].pid1_Ki = 0.00001;
	p_control_policy_total_manager->fcu_run_data_debug[11].pid1_Kd = 170;
	p_control_policy_total_manager->fcu_run_data_debug[11].pid2_Kp = 0.3;
	p_control_policy_total_manager->fcu_run_data_debug[11].pid2_Ki = 0.00001;
	p_control_policy_total_manager->fcu_run_data_debug[11].pid2_Kd = 100;
	p_control_policy_total_manager->fcu_run_data_debug[11].h2_pressure_target_value = 77;
	p_control_policy_total_manager->fcu_run_data_debug[11].h2_pressure_advance_set_value = 0;
	p_control_policy_total_manager->fcu_run_data_debug[11].h2_outlet_valve_open_time = 2000;
	p_control_policy_total_manager->fcu_run_data_debug[11].h2_outlet_valve_close_time = 4000;
	p_control_policy_total_manager->fcu_run_data_debug[11].h2_circulating_pump_speed_setpoint = 3000;
	p_control_policy_total_manager->fcu_run_data_debug[11].air_compressor_speed_setpoint = 82000;
	p_control_policy_total_manager->fcu_run_data_debug[11].air_rate_of_flow_target = 3664+500;
	p_control_policy_total_manager->fcu_run_data_debug[11].water_temperature_target_value = 68;	
	
	
	return error_code;
}	



//fcu���صĹ����������ݣ�ͨ��rs232���Խӿڣ�
enum Error_code Control_Policy_Total_Manager_updata_by_manual(struct Control_Policy_Total_Manager  * p_control_policy_total_manager, float * rs232_test)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL || rs232_test == NULL)
	{return Pointer_is_null;}

	return error_code;
}		


//fcu���صĹ����������ݣ��Զ����ƣ�
enum Error_code Control_Policy_Total_Manager_updata_by_Automatic (struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}


	return error_code;
}	



//fcu���صĹ����������ݣ�ͨ��can��modbusͨ�Žӿڣ�
enum Error_code Control_Policy_Total_Manager_updata_by_communication(
struct Control_Policy_Total_Manager  * p_control_policy_total_manager, 
struct FCU_Data_Buffer * p_fcu_data_buffer)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL || p_fcu_data_buffer == NULL)
	{return Pointer_is_null;}

	FCU_data_buffer_updata_by_communication();

	return error_code;
}	



//FCU�ȶ�����ʱ���Զ�����
enum Error_code FCU_automatic_gear_shift()
{
	enum Error_code error_code = Succeed;

	if(fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_electricity >
		control_policy_total_manager.fcu_run_data_debug[control_policy_total_manager.fcu_output_electricity_level].fcu_output_electricity_upper_limit)
	{
		if(control_policy_total_manager.fcu_output_electricity_level != FCU_OUTPUT_ELECTRICITY_TOTAL_NUMBER-1 )
		{
			control_policy_total_manager.fcu_output_electricity_level++;
		}
	}
	else  if(fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_electricity <
		control_policy_total_manager.fcu_run_data_debug[control_policy_total_manager.fcu_output_electricity_level].fcu_output_electricity_lower_limit)
	{
		if(control_policy_total_manager.fcu_output_electricity_level != 0 )
		{
			control_policy_total_manager.fcu_output_electricity_level--;
		}
	}

	fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid1.Kp = 
		control_policy_total_manager.fcu_run_data_debug[control_policy_total_manager.fcu_output_electricity_level].pid1_Kp;
	fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid1.Ki = 
		control_policy_total_manager.fcu_run_data_debug[control_policy_total_manager.fcu_output_electricity_level].pid1_Ki;
	fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid1.Kd = 
		control_policy_total_manager.fcu_run_data_debug[control_policy_total_manager.fcu_output_electricity_level].pid1_Kd;
	fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid2.Kp = 
		control_policy_total_manager.fcu_run_data_debug[control_policy_total_manager.fcu_output_electricity_level].pid2_Kp;
	fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid2.Ki = 
		control_policy_total_manager.fcu_run_data_debug[control_policy_total_manager.fcu_output_electricity_level].pid2_Ki;
	fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid2.Kd = 
		control_policy_total_manager.fcu_run_data_debug[control_policy_total_manager.fcu_output_electricity_level].pid2_Kd;   
	fcu_data_buffer.h2_data_buffer.h2_pressure_target_value = 
		control_policy_total_manager.fcu_run_data_debug[control_policy_total_manager.fcu_output_electricity_level].h2_pressure_target_value;
	fcu_data_buffer.h2_data_buffer.h2_pressure_advance_set_value = 
		control_policy_total_manager.fcu_run_data_debug[control_policy_total_manager.fcu_output_electricity_level].h2_pressure_advance_set_value;
	fcu_data_buffer.h2_data_buffer.h2_outlet_valve_open_time = 
		control_policy_total_manager.fcu_run_data_debug[control_policy_total_manager.fcu_output_electricity_level].h2_outlet_valve_open_time;
	fcu_data_buffer.h2_data_buffer.h2_outlet_valve_close_time = 
		control_policy_total_manager.fcu_run_data_debug[control_policy_total_manager.fcu_output_electricity_level].h2_outlet_valve_close_time;
	fcu_data_buffer.h2_data_buffer.h2_circulating_pump_speed_setpoint = 
		control_policy_total_manager.fcu_run_data_debug[control_policy_total_manager.fcu_output_electricity_level].h2_circulating_pump_speed_setpoint;
//	fcu_data_buffer.air_data_buffer.air_compressor_speed_setpoint = 
//		control_policy_total_manager.fcu_run_data_debug[control_policy_total_manager.fcu_output_electricity_level].air_compressor_speed_setpoint; 
	fcu_data_buffer.air_data_buffer.air_rate_of_flow_target = 
		control_policy_total_manager.fcu_run_data_debug[control_policy_total_manager.fcu_output_electricity_level].air_rate_of_flow_target;
	
	fcu_data_buffer.water_for_pile_data_buffer.water_temperature_target_value1 = 
		control_policy_total_manager.fcu_run_data_debug[control_policy_total_manager.fcu_output_electricity_level].water_temperature_target_value;
    fcu_data_buffer.water_for_pile_data_buffer.water_temperature_target_value2 = 
		control_policy_total_manager.fcu_run_data_debug[control_policy_total_manager.fcu_output_electricity_level].water_temperature_target_value;


	return error_code;
}	






//����ʱ�ı������飬ͨ���ͣ�
enum Error_code FCU_run_protect_check_common(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	//�ж�ÿ��ģ��������Ƿ�������
	//ע���ˣ�����ȫ������if������˵��Ҫ�����жϵģ�Ȼ����ݸ澯�ȼ����и��ǣ�����ֻ��һ�������롣

	//������·
	//�жϱ�����ǰ��ѹ
	if(fcu_data_buffer.h2_data_buffer.h2_pressure_proportional_valve_front < 200 && 
		p_control_policy_total_manager->working_alarm_mode > one_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_fault0;
		p_control_policy_total_manager->working_status_mode = working_status_error;
		p_control_policy_total_manager->working_alarm_mode = one_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = H2_pressure_proportional_valve_front_under_error1;//������ǰ��ѹ	Ƿѹ��һ�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		p_control_policy_total_manager->working_error_count++;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
	if(fcu_data_buffer.h2_data_buffer.h2_pressure_proportional_valve_front < 250 && 
		p_control_policy_total_manager->working_alarm_mode > three_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = three_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = H2_pressure_proportional_valve_front_under_error3;//������ǰ��ѹ	Ƿѹ��3�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
	if(fcu_data_buffer.h2_data_buffer.h2_pressure_proportional_valve_front > 260 && 
		p_control_policy_total_manager->working_FCU_error_code == H2_pressure_proportional_valve_front_under_error3)
	{
		//�ָ�����
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = working_normal;
		p_control_policy_total_manager->working_FCU_error_code = Succeed;
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
	if(fcu_data_buffer.h2_data_buffer.h2_pressure_proportional_valve_front > 620 && 
		p_control_policy_total_manager->working_alarm_mode > one_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_fault0;
		p_control_policy_total_manager->working_status_mode = working_status_error;
		p_control_policy_total_manager->working_alarm_mode = one_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = H2_pressure_proportional_valve_front_over_error1;//������ǰ��ѹ	��ѹ��һ�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		p_control_policy_total_manager->working_error_count++;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}   
	if(fcu_data_buffer.h2_data_buffer.h2_pressure_proportional_valve_front > 610 && 
		p_control_policy_total_manager->working_alarm_mode > three_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = three_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = H2_pressure_proportional_valve_front_over_error3 ;	//������ǰ��ѹ  ��ѹ��3�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}  
	if(fcu_data_buffer.h2_data_buffer.h2_pressure_proportional_valve_front < 600 && 
		p_control_policy_total_manager->working_FCU_error_code == H2_pressure_proportional_valve_front_over_error3)
	{
		//�ָ�����
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = working_normal;
		p_control_policy_total_manager->working_FCU_error_code = Succeed;
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}

	//�жϱ���������ѹ��ֱ���ж���ѹ������Ȼ�󸽼��ж����ޡ�
	if(fcu_data_buffer.h2_data_buffer.h2_pressure_proportional_valve_rear < 10 && 
		p_control_policy_total_manager->working_alarm_mode > one_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_fault0;
		p_control_policy_total_manager->working_status_mode = working_status_error;
		p_control_policy_total_manager->working_alarm_mode = one_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = H2_pressure_proportional_valve_rear_under_error1;	//����������ѹ  Ƿѹ��һ�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		p_control_policy_total_manager->working_error_count++;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}   
	if(fcu_data_buffer.h2_data_buffer.h2_pressure_proportional_valve_rear < 20 && 
		p_control_policy_total_manager->working_alarm_mode > three_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = three_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = H2_pressure_proportional_valve_rear_under_error3 ,	//����������ѹ  Ƿѹ��3�����ϣ�
			p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}  
	if(fcu_data_buffer.h2_data_buffer.h2_pressure_proportional_valve_rear > 25 && 
		p_control_policy_total_manager->working_FCU_error_code == H2_pressure_proportional_valve_rear_under_error3)
	{
		//�ָ�����
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = working_normal;
		p_control_policy_total_manager->working_FCU_error_code = Succeed;
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
	if(fcu_data_buffer.h2_data_buffer.h2_pressure_proportional_valve_rear > 135 &&
		p_control_policy_total_manager->working_alarm_mode > one_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_fault0;
		p_control_policy_total_manager->working_status_mode = working_status_error;
		p_control_policy_total_manager->working_alarm_mode = one_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = H2_pressure_proportional_valve_rear_over_error1 ;	//����������ѹ  ��ѹ��һ�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		p_control_policy_total_manager->working_error_count++;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}   
	if(fcu_data_buffer.h2_data_buffer.h2_pressure_proportional_valve_rear > 130 &&
		p_control_policy_total_manager->working_alarm_mode > three_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = three_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = H2_pressure_proportional_valve_rear_over_error3 ;	//����������ѹ  ��ѹ��3�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}  
	if(fcu_data_buffer.h2_data_buffer.h2_pressure_proportional_valve_rear < 125 &&
		p_control_policy_total_manager->working_FCU_error_code == H2_pressure_proportional_valve_rear_over_error3)
	{
		//�ָ�����
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = working_normal;
		p_control_policy_total_manager->working_FCU_error_code = Succeed;
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
	
	//�ж������ѹ
	if((fcu_data_buffer.h2_data_buffer.h2_pressure_fluctuate_last_min < -40 ||
	    fcu_data_buffer.h2_data_buffer.h2_pressure_pile_inlet < 10 ) && 
		p_control_policy_total_manager->working_alarm_mode > one_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_fault0;
		p_control_policy_total_manager->working_status_mode = working_status_error;
		p_control_policy_total_manager->working_alarm_mode = one_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = H2_pressure_pile_inlet_under_error1;	//�����ѹ  Ƿѹ��һ�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		p_control_policy_total_manager->working_error_count++;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
	if((fcu_data_buffer.h2_data_buffer.h2_pressure_fluctuate_last_min < -30 ||
	    fcu_data_buffer.h2_data_buffer.h2_pressure_pile_inlet < 20 ) && 
		p_control_policy_total_manager->working_alarm_mode > three_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = three_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = H2_pressure_pile_inlet_under_error3;		//�����ѹ  Ƿѹ��3�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
	if((fcu_data_buffer.h2_data_buffer.h2_pressure_fluctuate_last_min > -25 &&
	    fcu_data_buffer.h2_data_buffer.h2_pressure_pile_inlet > 25 ) && 
		p_control_policy_total_manager->working_FCU_error_code == H2_pressure_pile_inlet_under_error3)
	{
		//�ָ�����
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = working_normal;
		p_control_policy_total_manager->working_FCU_error_code = Succeed;
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
	if((fcu_data_buffer.h2_data_buffer.h2_pressure_fluctuate_last_max > 40 || 
		fcu_data_buffer.h2_data_buffer.h2_pressure_pile_inlet > 105 ) && 
		p_control_policy_total_manager->working_alarm_mode > one_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_fault0;
		p_control_policy_total_manager->working_status_mode = working_status_error;
		p_control_policy_total_manager->working_alarm_mode = one_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = H2_pressure_pile_inlet_over_error1;		//�����ѹ  ��ѹ��һ�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		p_control_policy_total_manager->working_error_count++;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}   
	if((fcu_data_buffer.h2_data_buffer.h2_pressure_fluctuate_last_max > 30 || 
		fcu_data_buffer.h2_data_buffer.h2_pressure_pile_inlet > 100 ) && 
		p_control_policy_total_manager->working_alarm_mode > three_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = three_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = H2_pressure_pile_inlet_over_error3;	//�����ѹ  ��ѹ��3�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}  
	if((fcu_data_buffer.h2_data_buffer.h2_pressure_fluctuate_last_max < 25 && 
		fcu_data_buffer.h2_data_buffer.h2_pressure_pile_inlet < 95 ) && 
		p_control_policy_total_manager->working_FCU_error_code == H2_pressure_pile_inlet_over_error3)
	{
		//�ָ�����
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = working_normal;
		p_control_policy_total_manager->working_FCU_error_code = Succeed;
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}

	//������ѹ��β����ѹ��������Ҫ������ ����������ѹ����Ѻ�������β�ŷ� �йأ����Բ��������޵��ж�
	//�����ѹ��������ѹ��β����ѹ    �����ű�������ѹһ�𲨶���
	//����ֱ���ж��Ƿ���漴�ɡ�
	//�����Ϊ���Ǻ���Ҫ�����Ծ�ֻ��������������ʾ���á�
	if((fcu_data_buffer.h2_data_buffer.h2_pressure_pile_inlet - fcu_data_buffer.h2_data_buffer.h2_pressure_proportional_valve_rear < -30 ||
		fcu_data_buffer.h2_data_buffer.h2_pressure_pile_inlet - fcu_data_buffer.h2_data_buffer.h2_pressure_proportional_valve_rear > 5) &&
		p_control_policy_total_manager->working_alarm_mode > three_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = three_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = H2_pressure_pile_inlet_no_follow_error3 ;	//�����ѹ  û�и������������ѹ��3�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}  
	if(fcu_data_buffer.h2_data_buffer.h2_pressure_pile_inlet - fcu_data_buffer.h2_data_buffer.h2_pressure_proportional_valve_rear > -25 &&
		fcu_data_buffer.h2_data_buffer.h2_pressure_pile_inlet - fcu_data_buffer.h2_data_buffer.h2_pressure_proportional_valve_rear < 2 &&
		p_control_policy_total_manager->working_FCU_error_code == H2_pressure_pile_inlet_no_follow_error3)
	{
		//�ָ�����
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = working_normal;
		p_control_policy_total_manager->working_FCU_error_code = Succeed;
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
/*	if((fcu_data_buffer.h2_data_buffer.h2_pressure_pile_outlet - fcu_data_buffer.h2_data_buffer.h2_pressure_proportional_valve_rear < -25 ||
		fcu_data_buffer.h2_data_buffer.h2_pressure_pile_outlet - fcu_data_buffer.h2_data_buffer.h2_pressure_proportional_valve_rear > 5) &&
		p_control_policy_total_manager->working_alarm_mode > three_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = three_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = H2_pressure_pile_outlet_no_follow_error3 ;	//������ѹ	û�и������������ѹ��3�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}  
	if(fcu_data_buffer.h2_data_buffer.h2_pressure_pile_outlet - fcu_data_buffer.h2_data_buffer.h2_pressure_proportional_valve_rear > -22 &&
		fcu_data_buffer.h2_data_buffer.h2_pressure_pile_outlet - fcu_data_buffer.h2_data_buffer.h2_pressure_proportional_valve_rear < 2 &&
		p_control_policy_total_manager->working_FCU_error_code == H2_pressure_pile_outlet_no_follow_error3)
	{
		//�ָ�����
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = working_normal;
		p_control_policy_total_manager->working_FCU_error_code = Succeed;
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}  */
	//β����ѹ ��Ϊ����β�ŷ�����β�ŷ�������˲����������ʱ���ڲ�����棬���Բ������������ж�
	if(	fcu_data_buffer.h2_data_buffer.h2_pressure_tail_outlet - fcu_data_buffer.h2_data_buffer.h2_pressure_proportional_valve_rear > 5 &&
		p_control_policy_total_manager->working_alarm_mode > three_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = three_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = H2_pressure_tail_outlet_no_follow_error3;	//β����ѹ	û�и������������ѹ��3�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}  
	if(fcu_data_buffer.h2_data_buffer.h2_pressure_tail_outlet - fcu_data_buffer.h2_data_buffer.h2_pressure_proportional_valve_rear < 2 &&
		p_control_policy_total_manager->working_FCU_error_code == H2_pressure_tail_outlet_no_follow_error3)
	{
		//�ָ�����
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = working_normal;
		p_control_policy_total_manager->working_FCU_error_code = Succeed;
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}



	//����ѭ���� canͨ��
	//�ж�canͨ���Ƿ�������
	if(fcu_data_buffer.h2_data_buffer.h2_circulating_pump_working_communication_status == working_communication_outage && 
		p_control_policy_total_manager->working_alarm_mode > one_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_fault0;
		p_control_policy_total_manager->working_status_mode = working_status_error;
		p_control_policy_total_manager->working_alarm_mode = one_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = H2_circulating_pump_communication_error1;//����ѭ����  canͨ�Ź��ϣ�һ�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		p_control_policy_total_manager->working_error_count++;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
	//�ж�����ѭ��������� can�����ж�
	if(Succeed != approximate(LOW_VOLTAGE_24V, fcu_data_buffer.h2_data_buffer.h2_circulating_pump_actual_voltage) && 
		p_control_policy_total_manager->working_alarm_mode > one_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_fault0;
		p_control_policy_total_manager->working_status_mode = working_status_error;
		p_control_policy_total_manager->working_alarm_mode = one_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = H2_circulating_pump_low_voltage_power_error1;//����ѭ���õ�  24V��ѹ��Դ���ϡ���һ�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		p_control_policy_total_manager->working_error_count++; 
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	} 
	if(fcu_data_buffer.h2_data_buffer.h2_circulating_pump_actual_electronic_temperature > 120 && 
		p_control_policy_total_manager->working_alarm_mode > one_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_fault0;
		p_control_policy_total_manager->working_status_mode = working_status_error;
		p_control_policy_total_manager->working_alarm_mode = one_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = H2_circulating_pump_temperature_over_error1;//����ѭ���� �¶ȹ��ߣ�һ�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		p_control_policy_total_manager->working_error_count++; 
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	} 
	if(fcu_data_buffer.h2_data_buffer.h2_circulating_pump_actual_electronic_temperature > 110 && 
		p_control_policy_total_manager->working_alarm_mode > two_level_fault)
	{
		//����ѭ����  �¶ȹ��ߣ�2������  ��ȡ��ʩ  ת�ٽ���50%
		fcu_data_buffer.h2_data_buffer.h2_circulating_pump_speed_setpoint_percent = 0.5;

		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = three_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = H2_circulating_pump_temperature_over_error2 ;	//����ѭ���� �¶ȹ��ߣ�2�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	} 
	if(fcu_data_buffer.h2_data_buffer.h2_circulating_pump_actual_electronic_temperature < 105 && 
		p_control_policy_total_manager->working_FCU_error_code == H2_circulating_pump_temperature_over_error2)
	{
		fcu_data_buffer.h2_data_buffer.h2_circulating_pump_speed_setpoint_percent = 1;
		//�ָ�����
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = working_normal;
		p_control_policy_total_manager->working_FCU_error_code = Succeed;
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
	if(fcu_data_buffer.h2_data_buffer.h2_circulating_pump_actual_electronic_temperature < -20 && 
		p_control_policy_total_manager->working_alarm_mode > one_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_fault0;
		p_control_policy_total_manager->working_status_mode = working_status_error;
		p_control_policy_total_manager->working_alarm_mode = one_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = H2_circulating_pump_temperature_under_error1;//����ѭ���� �¶ȹ��ͣ�һ�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		p_control_policy_total_manager->working_error_count++; 
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	} 
	if(fcu_data_buffer.h2_data_buffer.h2_circulating_pump_actual_electronic_temperature < -10 && 
		p_control_policy_total_manager->working_alarm_mode > three_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = three_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = H2_circulating_pump_temperature_under_error3;	//����ѭ���� �¶ȹ��ͣ�3�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}   
	if(fcu_data_buffer.h2_data_buffer.h2_circulating_pump_actual_electronic_temperature > 0 && 
		p_control_policy_total_manager->working_FCU_error_code == H2_circulating_pump_temperature_under_error3)
	{
		//�ָ�����
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = working_normal;
		p_control_policy_total_manager->working_FCU_error_code = Succeed;
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
	if(fcu_data_buffer.h2_data_buffer.h2_circulating_pump_status_diagnose_word != 5 && 
		p_control_policy_total_manager->working_alarm_mode > one_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_fault0;
		p_control_policy_total_manager->working_status_mode = working_status_error;
		p_control_policy_total_manager->working_alarm_mode = one_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = H2_circulating_pump_working_statas_error1;		//����ѭ���ù���״̬���ϣ�һ�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		p_control_policy_total_manager->working_error_count++; 
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	} 

    if(fcu_data_buffer.h2_data_buffer.h2_concentration > H2_CONCENTRATION_OVER_MAX && 
		p_control_policy_total_manager->working_alarm_mode > one_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_fault0;
		p_control_policy_total_manager->working_status_mode = working_status_error;
		p_control_policy_total_manager->working_alarm_mode = one_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = H2_concentration_over_error1;	//����Ũ�ȼ��  Ũ�ȹ��ߣ�һ�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		p_control_policy_total_manager->working_error_count++; 
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}



	//������·
	//�ж���ѷ�ѹ     35000ת��ʱ��   ��ѷ�ѹ ֻ��8kpa
	if(fcu_data_buffer.air_data_buffer.air_pressure_pile_inlet < 3 && 
		p_control_policy_total_manager->working_alarm_mode > one_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_fault0;
		p_control_policy_total_manager->working_status_mode = working_status_error;
		p_control_policy_total_manager->working_alarm_mode = one_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Air_pressure_pile_inlet_under_error1;	//��ѷ�ѹ  Ƿѹ��һ�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		p_control_policy_total_manager->working_error_count++;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
	if(fcu_data_buffer.air_data_buffer.air_pressure_pile_inlet < 5 && 
		p_control_policy_total_manager->working_alarm_mode > two_level_fault)
	{
	//	fcu_data_buffer.air_data_buffer.air_compressor_speed_setpoint_increment = 10000;//��ѹ��ת�٣����Ʊ�Ƶ��������

		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = two_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Air_pressure_pile_inlet_under_error2 ;	//��ѷ�ѹ	Ƿѹ��2�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
	if(fcu_data_buffer.air_data_buffer.air_pressure_pile_inlet > 7 && 
		p_control_policy_total_manager->working_FCU_error_code == Air_pressure_pile_inlet_under_error2)
	{
	//	fcu_data_buffer.air_data_buffer.air_compressor_speed_setpoint_increment = 0;//��ѹ��ת�٣����Ʊ�Ƶ��������
		//�ָ�����
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = working_normal;
		p_control_policy_total_manager->working_FCU_error_code = Succeed;
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
	if(fcu_data_buffer.air_data_buffer.air_pressure_pile_inlet > 100 && 
		p_control_policy_total_manager->working_alarm_mode > one_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_fault0;
		p_control_policy_total_manager->working_status_mode = working_status_error;
		p_control_policy_total_manager->working_alarm_mode = one_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Air_pressure_pile_inlet_over_error1 ;		//��ѷ�ѹ  ��ѹ��һ�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		p_control_policy_total_manager->working_error_count++;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}   
	if(fcu_data_buffer.air_data_buffer.air_pressure_pile_inlet > 90 && 
		p_control_policy_total_manager->working_alarm_mode > three_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = three_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Air_pressure_pile_inlet_over_error3 ;		//��ѷ�ѹ  ��ѹ��3�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}  
	if(fcu_data_buffer.air_data_buffer.air_pressure_pile_inlet < 85 && 
		p_control_policy_total_manager->working_FCU_error_code == Air_pressure_pile_inlet_over_error3)
	{
		//�ָ�����
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = working_normal;
		p_control_policy_total_manager->working_FCU_error_code = Succeed;
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}

	//���ѷ�ѹ 3������
	if(fcu_data_buffer.air_data_buffer.air_pressure_pile_outlet > 100 && 
		p_control_policy_total_manager->working_alarm_mode > three_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = three_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Air_pressure_pile_outlet_over_error3 ;		//���ѷ�ѹ  ��ѹ��3�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}   
	if(fcu_data_buffer.air_data_buffer.air_pressure_pile_outlet < 90 && 
		p_control_policy_total_manager->working_FCU_error_code == Air_pressure_pile_outlet_over_error3)
	{
		//�ָ�����
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = working_normal;
		p_control_policy_total_manager->working_FCU_error_code = Succeed;
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
	//���ڱ�ѹ 3������
	if(fcu_data_buffer.air_data_buffer.air_pressure_pile_back > 100 && 
		p_control_policy_total_manager->working_alarm_mode > three_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = three_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Air_pressure_pile_back_over_error3;		//���ڱ�ѹ  ��ѹ��3�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}   
	if(fcu_data_buffer.air_data_buffer.air_pressure_pile_back < 90 && 
		p_control_policy_total_manager->working_FCU_error_code == Air_pressure_pile_back_over_error3)
	{
		//�ָ�����
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = working_normal;
		p_control_policy_total_manager->working_FCU_error_code = Succeed;
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}        
	//����������
	if(fcu_data_buffer.air_data_buffer.air_rate_of_flow < 100 && 
		p_control_policy_total_manager->working_alarm_mode > one_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_fault0;
		p_control_policy_total_manager->working_status_mode = working_status_error;
		p_control_policy_total_manager->working_alarm_mode = one_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Air_rate_of_flow_under_error1 ;			//�����������ͣ�һ�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		p_control_policy_total_manager->working_error_count++; 
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}

	//�ж���ѷ���
	if(fcu_data_buffer.air_data_buffer.air_temperature_pile_inlet >75 && 
		p_control_policy_total_manager->working_alarm_mode > one_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_fault0;
		p_control_policy_total_manager->working_status_mode = working_status_error;
		p_control_policy_total_manager->working_alarm_mode = one_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Air_temperature_pile_inlet_over_error1;		//��ѷ���  ���£�һ�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		p_control_policy_total_manager->working_error_count++;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
	if(fcu_data_buffer.air_data_buffer.air_temperature_pile_inlet >70 && 
		p_control_policy_total_manager->working_alarm_mode > three_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = three_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Air_temperature_pile_inlet_over_error3;		//��ѷ���  ���£�3�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
	if(fcu_data_buffer.air_data_buffer.air_temperature_pile_inlet <68&& 
		p_control_policy_total_manager->working_FCU_error_code == Air_temperature_pile_inlet_over_error3)
	{
		//�ָ�����
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = working_normal;
		p_control_policy_total_manager->working_FCU_error_code = Succeed;
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
	if(fcu_data_buffer.air_data_buffer.air_temperature_pile_inlet < -10 && 
		p_control_policy_total_manager->working_alarm_mode > three_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = three_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Air_temperature_pile_inlet_under_error3;		//��ѷ���	Ƿ�£�3�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}  
	if(fcu_data_buffer.air_data_buffer.air_temperature_pile_inlet > 0 && 
		p_control_policy_total_manager->working_FCU_error_code == Air_temperature_pile_inlet_under_error3)
	{
		//�ָ�����
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = working_normal;
		p_control_policy_total_manager->working_FCU_error_code = Succeed;
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
	//���ѷ��� 3������
	if(fcu_data_buffer.air_data_buffer.air_temperature_pile_outlet > 90 && 
		p_control_policy_total_manager->working_alarm_mode > three_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = three_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Air_temperature_pile_outlet_over_error3 ;	//���ѷ���  ���£�3�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}   
	if(fcu_data_buffer.air_data_buffer.air_temperature_pile_outlet < 85 && 
		p_control_policy_total_manager->working_FCU_error_code == Air_temperature_pile_outlet_over_error3)
	{
		//�ָ�����
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = working_normal;
		p_control_policy_total_manager->working_FCU_error_code = Succeed;
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
	//����β���¶� 3������
/*	if(fcu_data_buffer.air_data_buffer.air_temperature_pile_back > 90 && 
		p_control_policy_total_manager->working_alarm_mode > three_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = three_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Air_temperature_pile_back_over_error3;			//���ڱ���  ���£�3�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}   
	if(fcu_data_buffer.air_data_buffer.air_temperature_pile_back < 85 && 
		p_control_policy_total_manager->working_FCU_error_code == Air_temperature_pile_back_over_error3)
	{
		//�ָ�����
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = working_normal;
		p_control_policy_total_manager->working_FCU_error_code = Succeed;
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}       */


	//�жϿ�ѹ����can����
	//��ѹ��  canͨ��ģʽ
	if(fcu_data_buffer.air_data_buffer.air_compressor_working_communication_status == working_communication_outage && 
		p_control_policy_total_manager->working_alarm_mode > one_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_fault0;
		p_control_policy_total_manager->working_status_mode = working_status_error;
		p_control_policy_total_manager->working_alarm_mode = one_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Air_compressor_communication_error1;//��ѹ��  canͨ�Ź��ϣ�һ�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		p_control_policy_total_manager->working_error_count++;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
	//��ѹ���������¶�
	if(fcu_data_buffer.air_data_buffer.air_compressor_converter_temperature > 110 && 
		p_control_policy_total_manager->working_alarm_mode > one_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_fault0;
		p_control_policy_total_manager->working_status_mode = working_status_error;
		p_control_policy_total_manager->working_alarm_mode = one_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Air_compressor_temperature_over_error1;	//��ѹ�� �¶ȹ��ߣ�һ�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		p_control_policy_total_manager->working_error_count++; 
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	} 
	if(fcu_data_buffer.air_data_buffer.air_compressor_converter_temperature > 100 && 
		p_control_policy_total_manager->working_alarm_mode > two_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = three_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Air_compressor_temperature_over_error2 ,	//��ѹ�� �¶ȹ��ߣ�2�����ϣ�
			p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}   
	if(fcu_data_buffer.air_data_buffer.air_compressor_converter_temperature < 95 && 
		p_control_policy_total_manager->working_FCU_error_code == Air_compressor_temperature_over_error2)
	{
		//�ָ�����
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = working_normal;
		p_control_policy_total_manager->working_FCU_error_code = Succeed;
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
	if(fcu_data_buffer.air_data_buffer.air_compressor_converter_temperature > 90 && 
		p_control_policy_total_manager->working_alarm_mode > three_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = three_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Air_compressor_temperature_over_error3 ,	//��ѹ�� �¶ȹ��ߣ�3�����ϣ�
			p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}   
	if(fcu_data_buffer.air_data_buffer.air_compressor_converter_temperature < 85 && 
		p_control_policy_total_manager->working_FCU_error_code == Air_compressor_temperature_over_error3)
	{
		//�ָ�����
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = working_normal;
		p_control_policy_total_manager->working_FCU_error_code = Succeed;
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
	if(fcu_data_buffer.air_data_buffer.air_compressor_converter_temperature < -20 && 
		p_control_policy_total_manager->working_alarm_mode > one_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_fault0;
		p_control_policy_total_manager->working_status_mode = working_status_error;
		p_control_policy_total_manager->working_alarm_mode = one_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Air_compressor_temperature_under_error1;	//��ѹ�� �¶ȹ��ͣ�һ�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		p_control_policy_total_manager->working_error_count++; 
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	} 
	if(fcu_data_buffer.air_data_buffer.air_compressor_converter_temperature < -10 && 
		p_control_policy_total_manager->working_alarm_mode > three_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = three_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Air_compressor_temperature_under_error3 ,	//��ѹ�� �¶ȹ��ͣ�3�����ϣ�
			p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}   
	if(fcu_data_buffer.air_data_buffer.air_compressor_converter_temperature > 0 && 
		p_control_policy_total_manager->working_FCU_error_code == Air_compressor_temperature_under_error3)
	{
		//�ָ�����
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = working_normal;
		p_control_policy_total_manager->working_FCU_error_code = Succeed;
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
	//������ѹ��can  ʵ��ת��   
	//ע���ˣ�����ʵ��ת������ʱ�����ܱ�ģ��ڱ仯��˲�䣬�趨ֵ��˲��仯����ʵ��ֵ�Ỻ���仯����ʱ�ǲ���ȵġ�
	//����ֻ��Ҫ�ж�ʵ��ת����>20000���ɡ���Ҫ������趨ֵ��
	if(	fcu_data_buffer.air_data_buffer.air_compressor_act_speed <20000 && 
		p_control_policy_total_manager->working_alarm_mode > one_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_fault0;
		p_control_policy_total_manager->working_status_mode = working_status_error;
		p_control_policy_total_manager->working_alarm_mode = one_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Air_compressor_act_speed_error1;			//��ѹ�� ʵ��ת�ٹ��ϣ�һ�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		p_control_policy_total_manager->working_error_count++; 
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
	//������ѹ��can  ״̬
	if(fcu_data_buffer.air_data_buffer.air_compressor_state != 12 &&
		fcu_data_buffer.air_data_buffer.air_compressor_state != 76 && 
		p_control_policy_total_manager->working_alarm_mode > one_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_fault0;
		p_control_policy_total_manager->working_status_mode = working_status_error;
		p_control_policy_total_manager->working_alarm_mode = one_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Air_compressor_working_statas_error1;		//��ѹ������״̬���ϣ�һ�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		p_control_policy_total_manager->working_error_count++; 
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}






	//����һɢ��ϵͳ ����У��
	//��ѹ������ˮ��
	if(fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_compressor_outlet >80 && 
		p_control_policy_total_manager->working_alarm_mode > one_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_fault0;
		p_control_policy_total_manager->working_status_mode = working_status_error;
		p_control_policy_total_manager->working_alarm_mode = one_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Water_temperature_compressor_outlet_over_error1;	//��ѹ������ˮ��  ���£�һ�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		p_control_policy_total_manager->working_error_count++;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
	if(fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_compressor_outlet >75 && 
		p_control_policy_total_manager->working_alarm_mode > three_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = three_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Water_temperature_compressor_outlet_over_error3 ;	//��ѹ������ˮ��  ���£�3�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
	if(fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_compressor_outlet <70 && 
		p_control_policy_total_manager->working_FCU_error_code == Water_temperature_compressor_outlet_over_error3)
	{
		//�ָ�����
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = working_normal;
		p_control_policy_total_manager->working_FCU_error_code = Succeed;
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
	if(fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_compressor_outlet < -10 && 
		p_control_policy_total_manager->working_alarm_mode > three_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = three_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Water_temperature_compressor_outlet_under_error3;	//��ѹ������ˮ��  Ƿ�£�3�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}  
	if(fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_compressor_outlet > 0 && 
		p_control_policy_total_manager->working_FCU_error_code == Water_temperature_compressor_outlet_under_error3)
	{
		//�ָ�����
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = working_normal;
		p_control_policy_total_manager->working_FCU_error_code = Succeed;
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
	//����һˮ�ó���ˮ��
	if(fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_pump_outlet >70 && 
		p_control_policy_total_manager->working_alarm_mode > one_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_fault0;
		p_control_policy_total_manager->working_status_mode = working_status_error;
		p_control_policy_total_manager->working_alarm_mode = one_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Water_temperature_pump_outlet_over_error1;		//����һˮ�ó���ˮ��  ���£�һ�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		p_control_policy_total_manager->working_error_count++;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
	if(fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_pump_outlet >65 && 
		p_control_policy_total_manager->working_alarm_mode > three_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = three_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Water_temperature_pump_outlet_over_error3 ;		//����һˮ�ó���ˮ��  ���£�3�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
	if(fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_pump_outlet <63 && 
		p_control_policy_total_manager->working_FCU_error_code == Water_temperature_pump_outlet_over_error3)
	{
		//�ָ�����
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = working_normal;
		p_control_policy_total_manager->working_FCU_error_code = Succeed;
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
	if(fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_pump_outlet < -10 && 
		p_control_policy_total_manager->working_alarm_mode > three_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = three_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Water_temperature_pump_outlet_under_error3 ;	//����һˮ�ó���ˮ��  Ƿ�£�3�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}  
	if(fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_pump_outlet > 0 && 
		p_control_policy_total_manager->working_FCU_error_code == Water_temperature_pump_outlet_under_error3)
	{
		//�ָ�����
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = working_normal;
		p_control_policy_total_manager->working_FCU_error_code = Succeed;
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
	//��ѹ������ˮѹ��ˮ���ǲ��ɿصģ���������һˮѹҲ�ǹ̶��ġ�����ֻ��һ������
/*	if(fcu_data_buffer.water_for_compressor_data_bufferr.water_pressure_compressor_outlet < 20 && 
		p_control_policy_total_manager->working_alarm_mode > one_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_fault0;
		p_control_policy_total_manager->working_status_mode = working_status_error;
		p_control_policy_total_manager->working_alarm_mode = one_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Water_pressure_compressor_outlet_under_error1 ;	//��ѹ������ˮѹ	Ƿѹ��һ�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		p_control_policy_total_manager->working_error_count++; 
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
 */



        
	//���ɢ��ϵͳ ����
	//������ˮѹ
	if(fcu_data_buffer.water_for_pile_data_buffer.water_pressure_pile_inlet1 > 90 && 
		p_control_policy_total_manager->working_alarm_mode > one_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_fault0;
		p_control_policy_total_manager->working_status_mode = working_status_error;
		p_control_policy_total_manager->working_alarm_mode = one_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Water_pressure_pile_inlet_over_error1;				//������ˮѹ  ��ѹ��һ�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		p_control_policy_total_manager->working_error_count++; 
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
	if(fcu_data_buffer.water_for_pile_data_buffer.water_pressure_pile_inlet1 < 10 && 
		p_control_policy_total_manager->working_alarm_mode > one_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_fault0;
		p_control_policy_total_manager->working_status_mode = working_status_error;
		p_control_policy_total_manager->working_alarm_mode = one_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Water_pressure_pile_inlet_under_error1;				//������ˮѹ  Ƿѹ��һ�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		p_control_policy_total_manager->working_error_count++; 
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
	//��ѳ���ˮѹ
	if(fcu_data_buffer.water_for_pile_data_buffer.water_pressure_pile_outlet1 > 30 && 
		p_control_policy_total_manager->working_alarm_mode > one_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_fault0;
		p_control_policy_total_manager->working_status_mode = working_status_error;
		p_control_policy_total_manager->working_alarm_mode = one_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Water_pressure_pile_outlet_over_error1;					//��ѳ���ˮѹ  ��ѹ��һ�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		p_control_policy_total_manager->working_error_count++; 
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
	if(fcu_data_buffer.water_for_pile_data_buffer.water_pressure_pile_outlet1 < 3 && 
		p_control_policy_total_manager->working_alarm_mode > one_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_fault0;
		p_control_policy_total_manager->working_status_mode = working_status_error;
		p_control_policy_total_manager->working_alarm_mode = one_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Water_pressure_pile_outlet_under_error1;				//��ѳ���ˮѹ  Ƿѹ��һ�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		p_control_policy_total_manager->working_error_count++; 
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
	//�����ںͳ��ڵ�ˮѹ��
	if(fcu_data_buffer.water_for_pile_data_buffer.water_pressure_pile_inlet1 - 
		fcu_data_buffer.water_for_pile_data_buffer.water_pressure_pile_outlet1 > 80 && 
		p_control_policy_total_manager->working_alarm_mode > one_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_fault0;
		p_control_policy_total_manager->working_status_mode = working_status_error;
		p_control_policy_total_manager->working_alarm_mode = one_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Water_pressure_differential_pile_inlet_and_outlet_over_error1;	//�����ںͳ��ڵ�ˮѹ��  ��ѹ��һ�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		p_control_policy_total_manager->working_error_count++; 
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
	if(fcu_data_buffer.water_for_pile_data_buffer.water_pressure_pile_inlet1 - 
		fcu_data_buffer.water_for_pile_data_buffer.water_pressure_pile_outlet1 < 3 && 
		p_control_policy_total_manager->working_alarm_mode > one_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_fault0;
		p_control_policy_total_manager->working_status_mode = working_status_error;
		p_control_policy_total_manager->working_alarm_mode = one_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Water_pressure_differential_pile_inlet_and_outlet_under_error1;	//�����ںͳ��ڵ�ˮѹ��  Ƿѹ��һ�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		p_control_policy_total_manager->working_error_count++; 
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
           
	//������ˮ��
	if(fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_inlet1 > 80 && 
		p_control_policy_total_manager->working_alarm_mode > one_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_fault0;
		p_control_policy_total_manager->working_status_mode = working_status_error;
		p_control_policy_total_manager->working_alarm_mode = one_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Water_temperature_pile_inlet_over_error1;				//������ˮ��  ���£�һ�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		p_control_policy_total_manager->working_error_count++; 
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
	if(fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_inlet1 > 75 && 
		p_control_policy_total_manager->working_alarm_mode > three_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = three_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Water_temperature_pile_inlet_over_error3;				//������ˮ��  ���£�3�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}  
	if(fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_inlet1 < 70 && 
		p_control_policy_total_manager->working_FCU_error_code == Water_temperature_pile_inlet_over_error3)
	{
		//�ָ�����
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = working_normal;
		p_control_policy_total_manager->working_FCU_error_code = Succeed;
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
	if(fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_inlet1 < 0 && 
		p_control_policy_total_manager->working_alarm_mode > one_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_fault0;
		p_control_policy_total_manager->working_status_mode = working_status_error;
		p_control_policy_total_manager->working_alarm_mode = one_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Water_temperature_pile_inlet_under_error1;				//������ˮ��  Ƿ�£�һ�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		p_control_policy_total_manager->working_error_count++; 
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
	//��ѳ���ˮ��
	if(fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_outlet1 > 90 && 
		p_control_policy_total_manager->working_alarm_mode > one_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_fault0;
		p_control_policy_total_manager->working_status_mode = working_status_error;
		p_control_policy_total_manager->working_alarm_mode = one_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Water_temperature_pile_outlet_over_error1;					//��ѳ���ˮ��  ���£�һ�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		p_control_policy_total_manager->working_error_count++; 
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
	if(fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_outlet1 > 85 && 
		p_control_policy_total_manager->working_alarm_mode > three_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = three_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Water_temperature_pile_outlet_over_error3;					//��ѳ���ˮ��  ���£�3�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}  
	if(fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_outlet1 < 80 && 
		p_control_policy_total_manager->working_FCU_error_code == Water_temperature_pile_outlet_over_error3)
	{
		//�ָ�����
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = working_normal;
		p_control_policy_total_manager->working_FCU_error_code = Succeed;
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
	if(fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_outlet1 < 0 && 
		p_control_policy_total_manager->working_alarm_mode > one_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_fault0;
		p_control_policy_total_manager->working_status_mode = working_status_error;
		p_control_policy_total_manager->working_alarm_mode = one_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Water_temperature_pile_outlet_under_error1;				//��ѳ���ˮ��  Ƿ�£�һ�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		p_control_policy_total_manager->working_error_count++; 
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
	//�����ںͳ��ڵ�ˮ�²�
	if(fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_outlet1 - 
		fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_inlet1 > 16 && 
		p_control_policy_total_manager->working_alarm_mode > one_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_fault0;
		p_control_policy_total_manager->working_status_mode = working_status_error;
		p_control_policy_total_manager->working_alarm_mode = one_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Water_temperature_differential_pile_inlet_and_outlet_over_error1;	//�����ںͳ��ڵ�ˮ�²�  ���£�һ�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		p_control_policy_total_manager->working_error_count++; 
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
	if(fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_outlet1 - 
		fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_inlet1 > 12 && 
		p_control_policy_total_manager->working_alarm_mode > three_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = three_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Water_temperature_differential_pile_inlet_and_outlet_over_error3;	//�����ںͳ��ڵ�ˮ�²�  ���£�3�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}  
	if(fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_outlet1 - 
		fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_inlet1 < 10 && 
		p_control_policy_total_manager->working_FCU_error_code == Water_temperature_differential_pile_inlet_and_outlet_over_error3)
	{
		//�ָ�����
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = working_normal;
		p_control_policy_total_manager->working_FCU_error_code = Succeed;
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}

       



	//��ѷ��������
	//��ѵĵ�ѹ
	if(fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_voltage < 130 && 
		p_control_policy_total_manager->working_alarm_mode > one_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_fault0;
		p_control_policy_total_manager->working_status_mode = working_status_error;
		p_control_policy_total_manager->working_alarm_mode = one_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Galvanic_pile_voltage_under_error1;			//��ѵ�ѹ���ͣ�һ�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		p_control_policy_total_manager->working_error_count++; 
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
	if(fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_voltage < 135  && 
		p_control_policy_total_manager->working_alarm_mode > two_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = two_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Galvanic_pile_voltage_under_error2;		//��ѵ�ѹ���ͣ�2�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}  
	if(fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_voltage > 137 && 
		p_control_policy_total_manager->working_FCU_error_code == Galvanic_pile_voltage_under_error2)
	{
		//�ָ�����
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;             
		p_control_policy_total_manager->working_alarm_mode = working_normal;             
		p_control_policy_total_manager->working_FCU_error_code = Succeed;
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
	if(fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_voltage < 140 && 
		p_control_policy_total_manager->working_alarm_mode > three_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = three_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Galvanic_pile_voltage_under_error3;		//��ѵ�ѹ���ͣ�3�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}  
	if(fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_voltage > 143 && 
		p_control_policy_total_manager->working_FCU_error_code == Galvanic_pile_voltage_under_error3)
	{
		//�ָ�����
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = working_normal;
		p_control_policy_total_manager->working_FCU_error_code = Succeed;
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
	if(fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_voltage > 280 && 
		p_control_policy_total_manager->working_alarm_mode > one_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_fault0;
		p_control_policy_total_manager->working_status_mode = working_status_error;
		p_control_policy_total_manager->working_alarm_mode = one_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Galvanic_pile_voltage_over_error1 ;				//��ѵ�ѹ���ߣ�һ�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		p_control_policy_total_manager->working_error_count++; 
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}

	//��ѵ���
	if(fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_electricity > 390 && 
		p_control_policy_total_manager->working_alarm_mode > one_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_fault0;
		p_control_policy_total_manager->working_status_mode = working_status_error;
		p_control_policy_total_manager->working_alarm_mode = one_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Galvanic_pile_electricity_over_error1 ;			//��ѵ������ߣ�һ�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		p_control_policy_total_manager->working_error_count++; 
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
	if(fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_electricity > 380  && 
		p_control_policy_total_manager->working_alarm_mode > two_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = two_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Galvanic_pile_electricity_over_error2;		//��ѵ������ߣ�2�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}  
	if(fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_electricity < 375 && 
		p_control_policy_total_manager->working_FCU_error_code == Galvanic_pile_electricity_over_error2)
	{
		//�ָ�����
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = working_normal;
		p_control_policy_total_manager->working_FCU_error_code = Succeed;
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
	if(fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_electricity > 370 && 
		p_control_policy_total_manager->working_alarm_mode > three_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = three_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Galvanic_pile_electricity_over_error3;			//��ѵ������ߣ�3�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}  
	if(fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_electricity < 365 && 
		p_control_policy_total_manager->working_FCU_error_code == Galvanic_pile_electricity_over_error3)
	{
		//�ָ�����
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = working_normal;
		p_control_policy_total_manager->working_FCU_error_code = Succeed;
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
	if(fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_electricity < -10 && 
		p_control_policy_total_manager->working_alarm_mode > one_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_fault0;
		p_control_policy_total_manager->working_status_mode = working_status_error;
		p_control_policy_total_manager->working_alarm_mode = one_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Galvanic_pile_electricity_under_error1 ;	//��ѵ������ͣ�һ�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		p_control_policy_total_manager->working_error_count++; 
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}

	//������������ѹ�� 
	if(fcu_data_buffer.h2_data_buffer.h2_pressure_pile_inlet - 
		fcu_data_buffer.air_data_buffer.air_pressure_pile_inlet > 80 && 
		p_control_policy_total_manager->working_alarm_mode > one_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_fault0;
		p_control_policy_total_manager->working_status_mode = working_status_error;
		p_control_policy_total_manager->working_alarm_mode = one_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Galvanic_pile_pressure_differential_h2_and_air_over_error1;	//������������ѹ��  ��ѹ��һ�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		p_control_policy_total_manager->working_error_count++; 
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
	if(fcu_data_buffer.h2_data_buffer.h2_pressure_pile_inlet - 
		fcu_data_buffer.air_data_buffer.air_pressure_pile_inlet > 75 && 
		p_control_policy_total_manager->working_alarm_mode > two_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = two_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Galvanic_pile_pressure_differential_h2_and_air_over_error2 ;	//������������ѹ��  ��ѹ��2�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}  
	if(fcu_data_buffer.h2_data_buffer.h2_pressure_pile_inlet - 
		fcu_data_buffer.air_data_buffer.air_pressure_pile_inlet < 73 && 
		p_control_policy_total_manager->working_FCU_error_code == Galvanic_pile_pressure_differential_h2_and_air_over_error2)
	{
		//�ָ�����
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = working_normal;
		p_control_policy_total_manager->working_FCU_error_code = Succeed;
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
	if(fcu_data_buffer.h2_data_buffer.h2_pressure_pile_inlet - 
		fcu_data_buffer.air_data_buffer.air_pressure_pile_inlet > 70 && 
		p_control_policy_total_manager->working_alarm_mode > three_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = three_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Galvanic_pile_pressure_differential_h2_and_air_over_error3 ;	//������������ѹ��  ��ѹ��3�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}  
	if(fcu_data_buffer.h2_data_buffer.h2_pressure_pile_inlet - 
		fcu_data_buffer.air_data_buffer.air_pressure_pile_inlet < 68 && 
		p_control_policy_total_manager->working_FCU_error_code == Galvanic_pile_pressure_differential_h2_and_air_over_error3)
	{
		//�ָ�����
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = working_normal;
		p_control_policy_total_manager->working_FCU_error_code = Succeed;
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}


	//Ѳ��
	if(fcu_data_buffer.galvanic_pile_data_buffer.itinerant_detective_working_communication_status == working_communication_outage && 
		p_control_policy_total_manager->working_alarm_mode > one_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_fault0;
		p_control_policy_total_manager->working_status_mode = working_status_error;
		p_control_policy_total_manager->working_alarm_mode = one_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Itinerant_detective_communication_error1;//Ѳ��  canͨ�Ź��ϣ�һ�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		p_control_policy_total_manager->working_error_count++;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
/*	//�������ͣ����Ѳ��ĵ�ѹ�ڴ�����ʱ�򣬿��ܻ�����쳣�жϣ��������Ͳ��ж�״̬�ˣ�ֻ�����з���֮���ж���С��ѹ��
	//�����ڼ�״̬����ֻ��2���澯���ɺ���ĵ�Ƭ��С��ѹ���ж�Ѳ���״̬
	if(fcu_data_buffer.galvanic_pile_data_buffer.itinerant_detective_working_statas  != 1 && 
		p_control_policy_total_manager->working_alarm_mode > two_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = two_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Itinerant_detective_working_statas_error2 ;	//Ѳ�칤��״̬���ϣ�2�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}  
	if(fcu_data_buffer.galvanic_pile_data_buffer.itinerant_detective_working_statas  == 1 && 
		p_control_policy_total_manager->working_FCU_error_code == Itinerant_detective_working_statas_error2)
	{
		//�ָ�����
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = working_normal;
		p_control_policy_total_manager->working_FCU_error_code = Succeed;
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}       */
	if(fcu_data_buffer.galvanic_pile_data_buffer.electric1_single_chip_minimum_voltage < 0.8 && 
		p_control_policy_total_manager->working_alarm_mode > one_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_fault0;
		p_control_policy_total_manager->working_status_mode = working_status_error;
		p_control_policy_total_manager->working_alarm_mode = one_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Glectric1_single_chip_minimum_voltage_under_error1;			//Ѳ�쵥Ƭ��ѹ���ͣ�һ�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		p_control_policy_total_manager->working_error_count++; 
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
	if(fcu_data_buffer.galvanic_pile_data_buffer.electric1_single_chip_minimum_voltage < 0.85 && 
		p_control_policy_total_manager->working_alarm_mode > two_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = two_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Glectric1_single_chip_minimum_voltage_under_error2 ;			//Ѳ�쵥Ƭ��ѹ���ͣ�2�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}  
	if(fcu_data_buffer.galvanic_pile_data_buffer.electric1_single_chip_minimum_voltage > 0.88 && 
		p_control_policy_total_manager->working_FCU_error_code == Glectric1_single_chip_minimum_voltage_under_error2)
	{
		//�ָ�����
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = working_normal;
		p_control_policy_total_manager->working_FCU_error_code = Succeed;
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
	if(fcu_data_buffer.galvanic_pile_data_buffer.electric1_single_chip_minimum_voltage < 0.9 && 
		p_control_policy_total_manager->working_alarm_mode > three_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = three_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Glectric1_single_chip_minimum_voltage_under_error3;		//Ѳ�쵥Ƭ��ѹ���ͣ�3�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}  
	if(fcu_data_buffer.galvanic_pile_data_buffer.electric1_single_chip_minimum_voltage > 0.92 && 
		p_control_policy_total_manager->working_FCU_error_code == Glectric1_single_chip_minimum_voltage_under_error3)
	{
		//�ָ�����
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = working_normal;
		p_control_policy_total_manager->working_FCU_error_code = Succeed;
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}


 /*   //��Ե��⣬
	if(fcu_data_buffer.galvanic_pile_data_buffer.insulation_monitor_working_communication_status == working_communication_outage && 
		p_control_policy_total_manager->working_alarm_mode > one_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_fault0;
		p_control_policy_total_manager->working_status_mode = working_status_error;
		p_control_policy_total_manager->working_alarm_mode = one_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Insulation_monitor_communication_error1;//��Եģ��  canͨ�Ź��ϣ�һ�����ϣ�
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		p_control_policy_total_manager->working_error_count++;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
  */



	return Succeed;
}






//FCU���صĹ����������ݣ������㷨��
//����ĵĿ����㷨���Զ��������е����ݣ�����֤��������������С�
enum Error_code Control_Policy_Total_Manager_updata_by_system(
struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

    if(fcu_data_buffer.galvanic_pile_data_buffer.fcu_stutter_stop_enable == 1)
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
				
				//p_control_policy_total_manager->working_error_count++;
				p_control_policy_total_manager->working_control_mode = working_control_fault_wait;
		    	p_control_policy_total_manager->fcu_updata_event_time = system_time;
    }
     else
     {
   
	switch(p_control_policy_total_manager->working_control_mode)
	{
	case working_control_outage :
		Control_Policy_Total_Manager_for_outage(p_control_policy_total_manager);
		break;
	case working_control_wait :
		Control_Policy_Total_Manager_for_wait(p_control_policy_total_manager);
		break;
	case working_control_run :
		Control_Policy_Total_Manager_for_run(p_control_policy_total_manager);
		break;
	case working_control_check1 :
		Control_Policy_Total_Manager_for_check1(p_control_policy_total_manager);
		break;
	case working_control_check2 :
		Control_Policy_Total_Manager_for_check2(p_control_policy_total_manager);
		break;
	case working_control_check3 :
		Control_Policy_Total_Manager_for_check3(p_control_policy_total_manager);
		break;	

	case working_control_start1 :
		Control_Policy_Total_Manager_for_start1(p_control_policy_total_manager);
		break;
	case working_control_start2 :
		Control_Policy_Total_Manager_for_start2(p_control_policy_total_manager);
		break;
	case working_control_start3 :
		Control_Policy_Total_Manager_for_start3(p_control_policy_total_manager);
		break;
	case working_control_start4 :
		Control_Policy_Total_Manager_for_start4(p_control_policy_total_manager);
		break;
	case working_control_start5 :
		Control_Policy_Total_Manager_for_start5(p_control_policy_total_manager);
		break;
	case working_control_start6 :
		Control_Policy_Total_Manager_for_start6(p_control_policy_total_manager);
		break;
	case working_control_start7 :
		Control_Policy_Total_Manager_for_start7(p_control_policy_total_manager);
		break;
	case working_control_start8 :
		Control_Policy_Total_Manager_for_start8(p_control_policy_total_manager);
		break;
	case working_control_start9 :
		Control_Policy_Total_Manager_for_start9(p_control_policy_total_manager);
		break;
	case working_control_start10 :
		Control_Policy_Total_Manager_for_start10(p_control_policy_total_manager);
		break;
	case working_control_start11 :
		Control_Policy_Total_Manager_for_start11(p_control_policy_total_manager);
		break;
	case working_control_start12 :
		Control_Policy_Total_Manager_for_start12(p_control_policy_total_manager);
		break;

	case working_control_stop1 :
		Control_Policy_Total_Manager_for_stop1(p_control_policy_total_manager);
		break;
	case working_control_stop2 :
		Control_Policy_Total_Manager_for_stop2(p_control_policy_total_manager);
		break;
	case working_control_stop3 :
		Control_Policy_Total_Manager_for_stop3(p_control_policy_total_manager);
		break;
	case working_control_stop4 :
		Control_Policy_Total_Manager_for_stop4(p_control_policy_total_manager);
		break;
	case working_control_stop5 :
		Control_Policy_Total_Manager_for_stop5(p_control_policy_total_manager);
		break;
	case working_control_stop6 :
		Control_Policy_Total_Manager_for_stop6(p_control_policy_total_manager);
		break;
	case working_control_stop7 :
		Control_Policy_Total_Manager_for_stop7(p_control_policy_total_manager);
		break;
	case working_control_stop8 :
		Control_Policy_Total_Manager_for_stop8(p_control_policy_total_manager);
		break;
	case working_control_stop9 :
		Control_Policy_Total_Manager_for_stop9(p_control_policy_total_manager);
		break;
	case working_control_stop10 :
		Control_Policy_Total_Manager_for_stop10(p_control_policy_total_manager);
		break;
	case working_control_stop11 :
		Control_Policy_Total_Manager_for_stop11(p_control_policy_total_manager);
		break;
	case working_control_stop12 :
		Control_Policy_Total_Manager_for_stop12(p_control_policy_total_manager);
		break;
		
	case working_control_fault0 :
		Control_Policy_Total_Manager_for_fault0(p_control_policy_total_manager);
		break;	
	case working_control_fault1 :
		Control_Policy_Total_Manager_for_fault1(p_control_policy_total_manager);
		break;	
	case working_control_fault2 :
		Control_Policy_Total_Manager_for_fault2(p_control_policy_total_manager);
		break;	
	case working_control_fault3 :
		Control_Policy_Total_Manager_for_fault3(p_control_policy_total_manager);
		break;	
	case working_control_fault4 :
		Control_Policy_Total_Manager_for_fault4(p_control_policy_total_manager);
		break;	
	case working_control_fault5 :
		Control_Policy_Total_Manager_for_fault5(p_control_policy_total_manager);
		break;	
	case working_control_fault6 :
		Control_Policy_Total_Manager_for_fault6(p_control_policy_total_manager);
		break;	
	case working_control_fault7 :
		Control_Policy_Total_Manager_for_fault7(p_control_policy_total_manager);
		break;	
	case working_control_fault8 :
		Control_Policy_Total_Manager_for_fault8(p_control_policy_total_manager);
		break;	
	case working_control_fault9 :
		Control_Policy_Total_Manager_for_fault9(p_control_policy_total_manager);
		break;	
	case working_control_fault10 :
		Control_Policy_Total_Manager_for_fault10(p_control_policy_total_manager);
		break;	
	case working_control_fault11:
		Control_Policy_Total_Manager_for_fault11(p_control_policy_total_manager);
		break;	
	case working_control_fault12:
		Control_Policy_Total_Manager_for_fault12(p_control_policy_total_manager);
		break;	
	case working_control_fault_wait:
		Control_Policy_Total_Manager_for_fault_wait(p_control_policy_total_manager);
		break;	
	default:
		break;
	}


     }
	return error_code;
}	




//fcu���أ������жϵ��㷨���տ���ʱ��״̬�������Լ�1�׶�
enum Error_code Control_Policy_Total_Manager_for_outage(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->fcu_system_running_mode && p_control_policy_total_manager->working_control_mode == working_control_outage)
	{
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_1S)
		{
			//pcu��������֮��ֱ�Ӵӿ�����Ч�����Լ�1�׶�
			p_control_policy_total_manager->working_control_mode = working_control_check1;
			p_control_policy_total_manager->working_status_mode = working_status_communication_outage;
			p_control_policy_total_manager->working_alarm_mode = working_normal;
			p_control_policy_total_manager->fcu_updata_event_time = system_time;
			p_control_policy_total_manager->working_error_count = 0;


			//���Զ�ģʽ���������У�����һ��֮����л����ֶ���Ȼ��Ͳ��������ˣ������ٴ��л������Զ�ģʽ�������У�
			if(p_control_policy_total_manager->fcu_system_running_mode == system_running_semi_auto)
			{
				p_control_policy_total_manager->fcu_system_running_mode = system_running_manual;
			}

		}
	}

	return error_code;
}			




//fcu���أ����Ҽ��1���㷨�����ͨ�ţ�����ȴ�״̬
enum Error_code Control_Policy_Total_Manager_for_check1(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->fcu_system_running_mode && p_control_policy_total_manager->working_control_mode == working_control_check1)
	{
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_100MS)
		{
			if(fcu_data_buffer.h2_data_buffer.h2_circulating_pump_working_communication_status &&
				fcu_data_buffer.air_data_buffer.air_compressor_working_communication_status &&
			//	fcu_data_buffer.galvanic_pile_data_buffer.insulation_monitor_working_communication_status &&
				fcu_data_buffer.galvanic_pile_data_buffer.itinerant_detective_working_communication_status &&
				fcu_data_buffer.galvanic_pile_data_buffer.itinerant_detective_working_communication_status2 &&
				atd_wait_check() == Succeed)
			{
				//�л����ȴ�״̬������������ģ��������׼����������״̬��������	����״̬��������	���ϵȼ���������
				p_control_policy_total_manager->working_control_mode = working_control_wait;
				p_control_policy_total_manager->working_status_mode = working_status_wait;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
				//ֻ���ϵ��Լ죬����Ȩ��������������
				p_control_policy_total_manager->working_error_count = 0;

				//fcu data�л���wait״̬
				//need programe

				//���Զ�ģʽ���������У�����һ��֮����л����ֶ���Ȼ��Ͳ��������ˣ������ٴ��л������Զ�ģʽ�������У�
				if(p_control_policy_total_manager->fcu_system_running_mode == system_running_semi_auto)
				{
					p_control_policy_total_manager->fcu_system_running_mode = system_running_manual;
				}
			}
			//�ϵ��Լ���󣬲��ҽ��ܵ����������ôֱ����ת���Լ�2
			else if(fcu_data_buffer.galvanic_pile_data_buffer.fcu_start_enable == 1)
			{
				//����ֱ����ת���Լ�2����ΪҪ����ˢ��ʱ�䡣
				p_control_policy_total_manager->working_control_mode = working_control_check2;
				p_control_policy_total_manager->working_status_mode = working_status_communication_outage;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			//�ϵ��Լ���󣬲���û�н��ܵ�������������޽����Լ�.
			else
			{
				//�ϵ��Լ죬��ʱ60s����ֱ�ӱ������Լ쳬ʱ����
				if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_60S)
				{
					p_control_policy_total_manager->working_control_mode = working_control_fault0;
					p_control_policy_total_manager->working_status_mode = working_status_error;
					p_control_policy_total_manager->working_alarm_mode = one_level_fault;
					//	p_control_policy_total_manager->working_FCU_error_code = Check1_overtime_error;
					p_control_policy_total_manager->working_FCU_error_control_mode = working_control_check1;
					p_control_policy_total_manager->working_error_count++;
					p_control_policy_total_manager->fcu_updata_event_time = system_time;

					if(fcu_data_buffer.h2_data_buffer.h2_circulating_pump_working_communication_status == working_communication_outage)
					{
						p_control_policy_total_manager->working_FCU_error_code = H2_circulating_pump_communication_error1;
					}
					else if(fcu_data_buffer.air_data_buffer.air_compressor_working_communication_status == working_communication_outage)
					{
						p_control_policy_total_manager->working_FCU_error_code = Air_compressor_communication_error1;
					}  
				/*	else if(fcu_data_buffer.galvanic_pile_data_buffer.insulation_monitor_working_communication_status == working_communication_outage)
					{
						p_control_policy_total_manager->working_FCU_error_code = Insulation_monitor_communication_error1;
					}     */
					else if(fcu_data_buffer.galvanic_pile_data_buffer.itinerant_detective_working_communication_status == working_communication_outage)
					{
						p_control_policy_total_manager->working_FCU_error_code = Itinerant_detective_communication_error1;
					}
					else if(fcu_data_buffer.galvanic_pile_data_buffer.itinerant_detective_working_communication_status2 == working_communication_outage)
					{
						p_control_policy_total_manager->working_FCU_error_code = Itinerant_detective_communication_error1;
					}
					else if(atd_wait_check() != Succeed)//ad������⣬�жϴ������Ƿ�����
					{
						p_control_policy_total_manager->working_FCU_error_code = atd_wait_check();
					}
				}
				else
				{
					//�����Լ죬ֱ��ͨ�Żָ���
					p_control_policy_total_manager->working_control_mode = working_control_check1;
					p_control_policy_total_manager->working_status_mode = working_status_communication_outage;
				}

			}
		}

	}


	return error_code;
}	




//FCU���أ��Լ�2���㷨�������Լ�1û��ͨ�������Ǿͽ��յ������������ʱ�жϣ�10s������Լ�ͨ������ô������������򱨴���
enum Error_code Control_Policy_Total_Manager_for_check2(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->fcu_system_running_mode && p_control_policy_total_manager->working_control_mode == working_control_check2)
	{
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_100MS)
		{
			if(fcu_data_buffer.h2_data_buffer.h2_circulating_pump_working_communication_status &&
				fcu_data_buffer.air_data_buffer.air_compressor_working_communication_status &&
		//		fcu_data_buffer.galvanic_pile_data_buffer.insulation_monitor_working_communication_status &&
				fcu_data_buffer.galvanic_pile_data_buffer.itinerant_detective_working_communication_status &&
				fcu_data_buffer.galvanic_pile_data_buffer.itinerant_detective_working_communication_status2 &&
				atd_wait_check() == Succeed)
			{
				//�л����ȴ�״̬������������ģ��������׼����������״̬��������	����״̬��������	���ϵȼ���������
				p_control_policy_total_manager->working_control_mode = working_control_wait;
				p_control_policy_total_manager->working_status_mode = working_status_wait;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
				//ֻ���ϵ��Լ죬����Ȩ��������������
				p_control_policy_total_manager->working_error_count = 0;

				//fcu data�л���wait״̬
				//need programe

				//���Զ�ģʽ���������У�����һ��֮����л����ֶ���Ȼ��Ͳ��������ˣ������ٴ��л������Զ�ģʽ�������У�
				if(p_control_policy_total_manager->fcu_system_running_mode == system_running_semi_auto)
				{
					p_control_policy_total_manager->fcu_system_running_mode = system_running_manual;
				}
			}
			//��ʱ�жϣ�10s������Լ�ͨ������ô������������򱨴�
			else
			{
				//�ϵ��Լ죬��ʱ10s����ֱ�ӱ������Լ쳬ʱ����
				if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_10S)
				{
					p_control_policy_total_manager->working_control_mode = working_control_fault0;
					p_control_policy_total_manager->working_status_mode = working_status_error;
					p_control_policy_total_manager->working_alarm_mode = one_level_fault;
					//	p_control_policy_total_manager->working_FCU_error_code = Check1_overtime_error;
					p_control_policy_total_manager->working_FCU_error_control_mode = working_control_check2;
					p_control_policy_total_manager->working_error_count++;
					p_control_policy_total_manager->fcu_updata_event_time = system_time;

					if(fcu_data_buffer.h2_data_buffer.h2_circulating_pump_working_communication_status == working_communication_outage)
					{
						p_control_policy_total_manager->working_FCU_error_code = H2_circulating_pump_communication_error1;
					}
					else if(fcu_data_buffer.air_data_buffer.air_compressor_working_communication_status == working_communication_outage)
					{
						p_control_policy_total_manager->working_FCU_error_code = Air_compressor_communication_error1;
					}
				/*	else if(fcu_data_buffer.galvanic_pile_data_buffer.insulation_monitor_working_communication_status == working_communication_outage)
					{
						p_control_policy_total_manager->working_FCU_error_code = Insulation_monitor_communication_error1;
					}   */
					else if(fcu_data_buffer.galvanic_pile_data_buffer.itinerant_detective_working_communication_status == working_communication_outage)
					{
						p_control_policy_total_manager->working_FCU_error_code = Itinerant_detective_communication_error1;
					}
					else if(fcu_data_buffer.galvanic_pile_data_buffer.itinerant_detective_working_communication_status2 == working_communication_outage)
					{
						p_control_policy_total_manager->working_FCU_error_code = Itinerant_detective_communication_error1;
					}					
					else if(atd_wait_check() != Succeed)//ad������⣬�жϴ������Ƿ�����
					{
						p_control_policy_total_manager->working_FCU_error_code = atd_wait_check();
					}
				}
				else
				{
					//�����Լ죬ֱ��ͨ�Żָ���
					p_control_policy_total_manager->working_control_mode = working_control_check2;
					p_control_policy_total_manager->working_status_mode = working_status_communication_outage;
				}
			}
		}

	}


	return error_code;
}	


//fcu���أ��ȴ��������㷨���ж��Ƿ���Ҫ����fc�������Ҫ������������Լ�2״̬���������ͣ���ڵȴ�״̬��
enum Error_code Control_Policy_Total_Manager_for_wait(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->fcu_system_running_mode && p_control_policy_total_manager->working_control_mode == working_control_wait)
	{
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_100MS)
		{
			//�յ���������
			if(fcu_data_buffer.galvanic_pile_data_buffer.fcu_start_enable == 1)
			{
				//��������ڷ����Լ�3����Ҫ�ж������Ƿ���
				fcu_data_buffer.h2_data_buffer.h2_inlet_valve = 1;

				//��������������ӵȴ�״̬�����Լ�3�׶�
				p_control_policy_total_manager->working_control_mode = working_control_check3;
				p_control_policy_total_manager->working_status_mode = working_status_wait;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;

				//���Զ�ģʽ���������У�����һ��֮����л����ֶ���Ȼ��Ͳ��������ˣ������ٴ��л������Զ�ģʽ�������У�
				if(p_control_policy_total_manager->fcu_system_running_mode == system_running_semi_auto)
				{
					p_control_policy_total_manager->fcu_system_running_mode = system_running_manual;
				}
			}
			//���򣬾�һֱ�ȴ���������
		}
	}

	return error_code;
}			



//fcu���أ��Լ�3���㷨��������ģ������ݣ��ж��Ƿ�״̬����������������ͽ��������׶�
enum Error_code Control_Policy_Total_Manager_for_check3(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->fcu_system_running_mode && p_control_policy_total_manager->working_control_mode == working_control_check3)
	{
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_100MS)
		{
			//�ж�canͨ���Ƿ�������
			if(fcu_data_buffer.h2_data_buffer.h2_circulating_pump_working_communication_status == working_communication_outage)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = H2_circulating_pump_communication_error1;//����ѭ����  canͨ�Ź��ϣ�һ�����ϣ�
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_check3;
				p_control_policy_total_manager->working_error_count++;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			else if(fcu_data_buffer.air_data_buffer.air_compressor_working_communication_status == working_communication_outage)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = Air_compressor_communication_error1;//��ѹ��  canͨ�Ź��ϣ�һ�����ϣ�
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_check3;
				p_control_policy_total_manager->working_error_count++;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
		/*	else if(fcu_data_buffer.galvanic_pile_data_buffer.insulation_monitor_working_communication_status == working_communication_outage)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = Insulation_monitor_communication_error1;//��Եģ��  canͨ�Ź��ϣ�һ�����ϣ�
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_check3;
				p_control_policy_total_manager->working_error_count++;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}   */
			else if(fcu_data_buffer.galvanic_pile_data_buffer.itinerant_detective_working_communication_status == working_communication_outage)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = Itinerant_detective_communication_error1;//Ѳ��  canͨ�Ź��ϣ�һ�����ϣ�
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_check3;
				p_control_policy_total_manager->working_error_count++;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			else if(fcu_data_buffer.galvanic_pile_data_buffer.itinerant_detective_working_communication_status2 == working_communication_outage)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = Itinerant_detective_communication_error1;//Ѳ��  canͨ�Ź��ϣ�һ�����ϣ�
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_check3;
				p_control_policy_total_manager->working_error_count++;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			//�жϱ�����ǰ��ѹ
			else if(fcu_data_buffer.h2_data_buffer.h2_pressure_proportional_valve_front < H2_PRESSURE_PROPORTIONAL_VALVE_FRONT_LOWER_LIMIT)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = H2_pressure_proportional_valve_front_under_error1;//������ǰ��ѹ	Ƿѹ��һ�����ϣ�
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_check3;
				p_control_policy_total_manager->working_error_count++;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			else if(fcu_data_buffer.h2_data_buffer.h2_pressure_proportional_valve_front > H2_PRESSURE_PROPORTIONAL_VALVE_FRONT_UPPER_LIMIT)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = H2_pressure_proportional_valve_front_over_error1;//������ǰ��ѹ	��ѹ��һ�����ϣ�
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_check3;
				p_control_policy_total_manager->working_error_count++;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			//�ж�atd����������
			else if(atd_wait_check_ex() != Succeed)//ad������⣬�жϴ������Ƿ����� ,����������ǰ��ѹ
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = atd_wait_check_ex();//ad������⣬�жϴ������Ƿ����� ,����������ǰ��ѹ
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_check3;
				p_control_policy_total_manager->working_error_count++;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			//�ж�����ѭ��������� can�����ж�
			else if(Succeed != approximate(LOW_VOLTAGE_24V, 
				fcu_data_buffer.h2_data_buffer.h2_circulating_pump_actual_voltage))
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = H2_circulating_pump_low_voltage_power_error1;//����ѭ���õ�  24V��ѹ��Դ���ϡ���һ�����ϣ�
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_check3;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			} 
			else if(fcu_data_buffer.h2_data_buffer.h2_circulating_pump_actual_electronic_temperature > 120)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = H2_circulating_pump_temperature_over_error1;//����ѭ���� �¶ȹ��ߣ�һ�����ϣ�
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_check3;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			} 
			else if(fcu_data_buffer.h2_data_buffer.h2_circulating_pump_actual_electronic_temperature < -20)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = H2_circulating_pump_temperature_under_error1;//����ѭ���� �¶ȹ��ͣ�һ�����ϣ�
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_check3;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			} 
			else if(fcu_data_buffer.h2_data_buffer.h2_circulating_pump_status_diagnose_word != 4)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = H2_circulating_pump_working_statas_error1;		//����ѭ���ù���״̬���ϣ�һ�����ϣ�
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_check3;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			} 
			//��ѹ����can���� �ж�
			else if(fcu_data_buffer.air_data_buffer.air_compressor_state != 0 &&
				fcu_data_buffer.air_data_buffer.air_compressor_state != 64)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = Air_compressor_working_statas_error1;		//��ѹ������״̬���ϣ�һ�����ϣ�
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_check3;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			} 
			else if(fcu_data_buffer.air_data_buffer.air_compressor_converter_temperature > 120)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = Air_compressor_temperature_over_error1;	//��ѹ�� �¶ȹ��ߣ�һ�����ϣ�
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_check3;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			} 
			else if(fcu_data_buffer.air_data_buffer.air_compressor_converter_temperature < -20)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = Air_compressor_temperature_under_error1;	//��ѹ�� �¶ȹ��ͣ�һ�����ϣ�
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_check3;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			} 
		/*	//Ѳ���can���� �ж�  �������ͣ����Ѳ��ĵ�ѹ�ڴ�����ʱ�򣬿��ܻ�����쳣�жϣ��������Ͳ��ж�״̬�ˣ�ֻ�����з���֮���ж���С��ѹ��
			else if(fcu_data_buffer.galvanic_pile_data_buffer.itinerant_detective_working_statas  != 0 )
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = Itinerant_detective_working_statas_error1;		//Ѳ�칤��״̬���ϣ�һ�����ϣ�
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_check3;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}   */
			//����Ũ�ȴ�����
			else if(fcu_data_buffer.h2_data_buffer.h2_concentration > H2_CONCENTRATION_OVER_MAX)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = H2_concentration_over_error1;	//����Ũ�ȼ��  Ũ�ȹ��ߣ�һ�����ϣ�
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_check3;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			} 
			//���û�д��󣬾�������ǰ�Լ�ok��������������ô����fc����
			else
			{
				//�л�������1״̬��������״̬��������	����״̬��������	���ϵȼ���������
				p_control_policy_total_manager->working_control_mode = working_control_start1;
				p_control_policy_total_manager->working_status_mode = working_status_starting;
				p_control_policy_total_manager->working_alarm_mode = working_normal;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;


				//fcu data�л�������״̬
				//need programe

				//���Զ�ģʽ���������У�����һ��֮����л����ֶ���Ȼ��Ͳ��������ˣ������ٴ��л������Զ�ģʽ�������У�
				if(p_control_policy_total_manager->fcu_system_running_mode == system_running_semi_auto)
				{
					p_control_policy_total_manager->fcu_system_running_mode = system_running_manual;
				}
			}
		}
	}

	return error_code;
}			



//fcu���أ�����1���㷨������ʱ������fc����������ɹ����ͽ������н׶Σ��������ʧ�ܣ�����л��˴�����Ȼ�󷵻صȴ��׶�
enum Error_code Control_Policy_Total_Manager_for_start1(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->fcu_system_running_mode && p_control_policy_total_manager->working_control_mode == working_control_start1)
	{
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_100MS)
		{
		    //����С���踺�صļ̵�����45kw���²�����ȷ��ȼ�ϵ���������Ĺ�����������λ�����ڹ���
		    fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_is_enble_load_resistance = 1;
			//����2��ˮ��
			fcu_data_buffer.water_for_pile_data_buffer.water_pump_pwm_dutyfactor1 = 9000;
			fcu_data_buffer.water_for_compressor_data_bufferr.water_pump_pwm_dutyfactor = 9000;

			//�л�������2״̬��������״̬��������	����״̬��������	���ϵȼ���������
			p_control_policy_total_manager->working_control_mode = working_control_start2;
			p_control_policy_total_manager->working_status_mode = working_status_starting;
			p_control_policy_total_manager->working_alarm_mode = working_normal;
			p_control_policy_total_manager->fcu_updata_event_time = system_time;

			//���Զ�ģʽ���������У�����һ��֮����л����ֶ���Ȼ��Ͳ��������ˣ������ٴ��л������Զ�ģʽ�������У�
			if(p_control_policy_total_manager->fcu_system_running_mode == system_running_semi_auto)
			{
				p_control_policy_total_manager->fcu_system_running_mode = system_running_manual;
			}

		}
	}

	return error_code;
}	

//fcu���أ�����2���㷨������ʱ������fc����������ɹ����ͽ������н׶Σ��������ʧ�ܣ�����л��˴�����Ȼ�󷵻صȴ��׶�
enum Error_code Control_Policy_Total_Manager_for_start2(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->fcu_system_running_mode && p_control_policy_total_manager->working_control_mode == working_control_start2)
	{
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_100MS)
		{
			//��������β�ţ�������
			fcu_data_buffer.h2_data_buffer.h2_is_enable_outlet_valve = 1;

			//�л�������3״̬��������״̬��������	����״̬��������	���ϵȼ���������
			p_control_policy_total_manager->working_control_mode = working_control_start3;
			p_control_policy_total_manager->working_status_mode = working_status_starting;
			p_control_policy_total_manager->working_alarm_mode = working_normal;
			p_control_policy_total_manager->fcu_updata_event_time = system_time;

			//���Զ�ģʽ���������У�����һ��֮����л����ֶ���Ȼ��Ͳ��������ˣ������ٴ��л������Զ�ģʽ�������У�
			if(p_control_policy_total_manager->fcu_system_running_mode == system_running_semi_auto)
			{
				p_control_policy_total_manager->fcu_system_running_mode = system_running_manual;
			}

		}
	}

	return error_code;
}

//fcu���أ�����3���㷨������ʱ������fc����������ɹ����ͽ������н׶Σ��������ʧ�ܣ�����л��˴�����Ȼ�󷵻صȴ��׶�
enum Error_code Control_Policy_Total_Manager_for_start3(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->fcu_system_running_mode && p_control_policy_total_manager->working_control_mode == working_control_start3)
	{
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_1S)
		{
			//����������������pwm��ʼ��Ϊ0��֮��ֻ����pid2��ʹ��
			fcu_data_buffer.h2_data_buffer.h2_pid_mode = 2;
			fcu_data_buffer.h2_data_buffer.h2_pressure_target_value = 50;
			fcu_data_buffer.h2_data_buffer.h2_pressure_advance_set_value = 0;
			fcu_data_buffer.h2_data_buffer.h2_pressure_pid2_advance_time = 200;

			fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid2.Kp = PID2_KP;
			fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid2.Ki = PID2_KI;
			fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid2.Kd = PID2_KD;
			fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pwm_dutyfactor = 0;
			fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid2.is_enble_pid = 1;

			//�л�������4״̬��������״̬��������	����״̬��������	���ϵȼ���������
			p_control_policy_total_manager->working_control_mode = working_control_start4;
			p_control_policy_total_manager->working_status_mode = working_status_starting;
			p_control_policy_total_manager->working_alarm_mode = working_normal;
			p_control_policy_total_manager->fcu_updata_event_time = system_time;

			//���Զ�ģʽ���������У�����һ��֮����л����ֶ���Ȼ��Ͳ��������ˣ������ٴ��л������Զ�ģʽ�������У�
			if(p_control_policy_total_manager->fcu_system_running_mode == system_running_semi_auto)
			{
				p_control_policy_total_manager->fcu_system_running_mode = system_running_manual;
			}

		}
	}

	return error_code;
}

//fcu���أ�����4���㷨������ʱ������fc����������ɹ����ͽ������н׶Σ��������ʧ�ܣ�����л��˴�����Ȼ�󷵻صȴ��׶�
enum Error_code Control_Policy_Total_Manager_for_start4(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->fcu_system_running_mode && p_control_policy_total_manager->working_control_mode == working_control_start4)
	{
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_5S)
		{
			//������������ѹ�Ƿ�ﵽָ����50
			if(Succeed != approximate(fcu_data_buffer.h2_data_buffer.h2_pressure_proportional_valve_rear, 50+3))
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = H2_pressure_proportional_valve_rear_unstable_error1;	//����������ѹ	ѹ�����ȣ�һ�����ϣ�
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_start4;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			//��������ѹ�Ƿ�ﵽָ����50
			else if(Succeed != approximate(fcu_data_buffer.h2_data_buffer.h2_pressure_pile_inlet, 50))
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = H2_pressure_pile_inlet_unstable_error1;	//�����ѹ	ѹ�����ȣ�һ�����ϣ�
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_start4;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			//��������ѹ�Ƿ�ﵽָ����50-10
	/*		else if(Succeed != approximate(fcu_data_buffer.h2_data_buffer.h2_pressure_pile_outlet, 50-10))
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = H2_pressure_pile_outlet_unstable_error1;	//������ѹ	ѹ�����ȣ�һ�����ϣ�
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_start4;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}    */
			//���β����ѹ�Ƿ�ﵽָ����50-10
			else if(Succeed != approximate(fcu_data_buffer.h2_data_buffer.h2_pressure_tail_outlet, 50-10))
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = H2_pressure_tail_outlet_unstable_error1;	//β����ѹ	ѹ�����ȣ�һ�����ϣ�
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_start4;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			//�����������ȣ� β�ų���ʱ��Ŀ����ѹ50��������һ����ȶ���2000+
			else if(fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pwm_dutyfactor < 1000)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = H2_proportional_valve_statas_error1;	//������״̬���ϣ�һ�����ϣ�
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_start4;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			else
			{
			/*	//��β�ų���������£�ֱ�ӿ�������ѭ���á�
				fcu_data_buffer.h2_data_buffer.h2_circulating_pump_speed_setpoint = H2_CIRCULATING_PUMP_SPEED_SETPOINT_1500;
				fcu_data_buffer.h2_data_buffer.h2_circulating_pump_enble = 1;
				fcu_data_buffer.h2_data_buffer.h2_circulating_pump_enable_pump = 1;   */
				
				//45kw�·���������ѭ���õ�����˳���Ӻ��ˣ������ֱ�ӽ��д�ɨģʽ��
				//����β���ɳ�������Ϊ��ɨģʽ��1s/0.5s
				fcu_data_buffer.h2_data_buffer.h2_outlet_valve_open_time = 500;
				fcu_data_buffer.h2_data_buffer.h2_outlet_valve_close_time = 1000;
				fcu_data_buffer.h2_data_buffer.h2_pressure_advance_set_value = 0;
				fcu_data_buffer.h2_data_buffer.h2_pressure_pid2_advance_time = 200;
				fcu_data_buffer.h2_data_buffer.h2_is_enable_outlet_valve = 2;

				//�л�������5״̬��������״̬��������	����״̬��������	���ϵȼ���������
				p_control_policy_total_manager->working_control_mode = working_control_start5;
				p_control_policy_total_manager->working_status_mode = working_status_starting;
				p_control_policy_total_manager->working_alarm_mode = working_normal;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;

				//���Զ�ģʽ���������У�����һ��֮����л����ֶ���Ȼ��Ͳ��������ˣ������ٴ��л������Զ�ģʽ�������У�
				if(p_control_policy_total_manager->fcu_system_running_mode == system_running_semi_auto)
				{
					p_control_policy_total_manager->fcu_system_running_mode = system_running_manual;
				}
			}
		}
	}

	return error_code;
}
/*
//fcu���أ�����5���㷨������ʱ������fc����������ɹ����ͽ������н׶Σ��������ʧ�ܣ�����л��˴�����Ȼ�󷵻صȴ��׶�
enum Error_code Control_Policy_Total_Manager_for_start5(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->fcu_system_running_mode && p_control_policy_total_manager->working_control_mode == working_control_start5)
	{
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_1S)
		{
			//�������ѭ����can  ʵ��ת�١�
			if(Succeed != approximate(fcu_data_buffer.h2_data_buffer.h2_circulating_pump_actual_speed, H2_CIRCULATING_PUMP_SPEED_SETPOINT_1500))
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = H2_circulating_pump_actual_speed_error1;	//����ѭ���� ʵ��ת�ٹ��ϣ�һ�����ϣ�
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_start5;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			//�������ѭ����can  ״̬
			else if(fcu_data_buffer.h2_data_buffer.h2_circulating_pump_status_diagnose_word != 5)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = H2_circulating_pump_working_statas_error1;	//����ѭ���ù���״̬���ϣ�һ�����ϣ�
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_start5;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			else
			{   
				//����β���ɳ�������Ϊ��ɨģʽ��1s/0.5s
				fcu_data_buffer.h2_data_buffer.h2_outlet_valve_open_time = 500;
				fcu_data_buffer.h2_data_buffer.h2_outlet_valve_close_time = 1000;
				fcu_data_buffer.h2_data_buffer.h2_pressure_advance_set_value = 0;
				fcu_data_buffer.h2_data_buffer.h2_pressure_pid2_advance_time = 200;
				fcu_data_buffer.h2_data_buffer.h2_is_enable_outlet_valve = 2;

				//�л�������6״̬��������״̬��������	����״̬��������	���ϵȼ���������
				p_control_policy_total_manager->working_control_mode = working_control_start6;
				p_control_policy_total_manager->working_status_mode = working_status_starting;
				p_control_policy_total_manager->working_alarm_mode = working_normal;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;

				//���Զ�ģʽ���������У�����һ��֮����л����ֶ���Ȼ��Ͳ��������ˣ������ٴ��л������Զ�ģʽ�������У�
				if(p_control_policy_total_manager->fcu_system_running_mode == system_running_semi_auto)
				{
					p_control_policy_total_manager->fcu_system_running_mode = system_running_manual;
				}
	//		}
		}
	}

	return error_code;
}
*/
//fcu���أ�����5���㷨������ʱ������fc����������ɹ����ͽ������н׶Σ��������ʧ�ܣ�����л��˴�����Ȼ�󷵻صȴ��׶�
enum Error_code Control_Policy_Total_Manager_for_start5(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->fcu_system_running_mode && p_control_policy_total_manager->working_control_mode == working_control_start5)
	{
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_6S)
		{
			//�����ѹ������pid1û�п������������Ϊ��Ƶ����������Ҫ�����10
			if(fcu_data_buffer.h2_data_buffer.h2_pressure_fluctuate_last_max -
				fcu_data_buffer.h2_data_buffer.h2_pressure_fluctuate_last_min < 10)	
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = H2_pressure_no_fluctuations_error1;	//����ѹ��û�в�����������β�ŷ����ϣ�һ�����ϣ�
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_start5;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			else
			{
				//����β���ɴ�ɨģʽ��1s/0.5s����Ϊ����ģʽ
				fcu_data_buffer.h2_data_buffer.h2_outlet_valve_open_time = 500;
				fcu_data_buffer.h2_data_buffer.h2_outlet_valve_close_time = 6000;
				fcu_data_buffer.h2_data_buffer.h2_pressure_advance_set_value = 0;
				fcu_data_buffer.h2_data_buffer.h2_pressure_pid2_advance_time = 1000;
				fcu_data_buffer.h2_data_buffer.h2_is_enable_outlet_valve = 2;

				//�л�������7״̬��������״̬��������	����״̬��������	���ϵȼ���������
				p_control_policy_total_manager->working_control_mode = working_control_start6;
				p_control_policy_total_manager->working_status_mode = working_status_starting;
				p_control_policy_total_manager->working_alarm_mode = working_normal;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;

				//���Զ�ģʽ���������У�����һ��֮����л����ֶ���Ȼ��Ͳ��������ˣ������ٴ��л������Զ�ģʽ�������У�
				if(p_control_policy_total_manager->fcu_system_running_mode == system_running_semi_auto)
				{
					p_control_policy_total_manager->fcu_system_running_mode = system_running_manual;
				}
			}
		}
	}

	return error_code;
}


//fcu���أ�����6���㷨������ʱ������fc����������ɹ����ͽ������н׶Σ��������ʧ�ܣ�����л��˴�����Ȼ�󷵻صȴ��׶�
enum Error_code Control_Policy_Total_Manager_for_start6(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->fcu_system_running_mode && p_control_policy_total_manager->working_control_mode == working_control_start6)
	{
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_100MS)
		{
			//�����ѹ������pid1û�п������������Ϊ��Ƶ����������Ҫ�����10
			if(fcu_data_buffer.h2_data_buffer.h2_pressure_fluctuate_last_max -
				fcu_data_buffer.h2_data_buffer.h2_pressure_fluctuate_last_min < 10)	
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = H2_pressure_no_fluctuations_error1;	//����ѹ��û�в�����������β�ŷ����ϣ�һ�����ϣ�
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_start6;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			else
			{
				//45kw�·�������ѹ����ʹ��ת�ٿ��ƣ������������ơ�
				fcu_data_buffer.air_data_buffer.air_compressor_speed_setpoint = 20000;
				fcu_data_buffer.air_data_buffer.air_compressor_enable = 1;
				
				fcu_data_buffer.air_data_buffer.air_rate_of_flow_target = 960;
				fcu_data_buffer.air_data_buffer.air_compressor_speed_pid.is_enble_pid = 1;

				//�л�������8״̬��������״̬��������	����״̬��������	���ϵȼ���������
				p_control_policy_total_manager->working_control_mode = working_control_start7;
				p_control_policy_total_manager->working_status_mode = working_status_starting;
				p_control_policy_total_manager->working_alarm_mode = working_normal;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;

				//���Զ�ģʽ���������У�����һ��֮����л����ֶ���Ȼ��Ͳ��������ˣ������ٴ��л������Զ�ģʽ�������У�
				if(p_control_policy_total_manager->fcu_system_running_mode == system_running_semi_auto)
				{
					p_control_policy_total_manager->fcu_system_running_mode = system_running_manual;
				}
			}
		}
	}

	return error_code;
}


//fcu���أ�����7���㷨������ʱ������fc����������ɹ����ͽ������н׶Σ��������ʧ�ܣ�����л��˴�����Ȼ�󷵻صȴ��׶�
enum Error_code Control_Policy_Total_Manager_for_start7(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->fcu_system_running_mode && p_control_policy_total_manager->working_control_mode == working_control_start7)
	{
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_5S)
		{
			//����ѹ��can  ʵ��ת��
			//ע���ˣ���ѹ�����ٺ��������Բ�Ҫ��ʵ��ת�ٴﵽ35000��ֻҪ�����10000����ʾ�Ѿ���������
			if(fcu_data_buffer.air_data_buffer.air_compressor_act_speed < 10000)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = Air_compressor_act_speed_error1;			//��ѹ�� ʵ��ת�ٹ��ϣ�һ�����ϣ�
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_start7;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			//����ѹ��can  ״̬
			else if(fcu_data_buffer.air_data_buffer.air_compressor_state != 12 &&
				fcu_data_buffer.air_data_buffer.air_compressor_state != 76)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = Air_compressor_working_statas_error1;		//��ѹ������״̬���ϣ�һ�����ϣ�
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_start7;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			else
			{
				//��������β�ţ�8s/0.5s
				fcu_data_buffer.air_data_buffer.air_outlet_valve_open_time = 500;
				fcu_data_buffer.air_data_buffer.air_outlet_valve_close_time = 8000;
				fcu_data_buffer.air_data_buffer.air_is_enable_outlet_valve = 2;

				//�л�������9״̬��������״̬��������	����״̬��������	���ϵȼ���������
				p_control_policy_total_manager->working_control_mode = working_control_start8;
				p_control_policy_total_manager->working_status_mode = working_status_starting;
				p_control_policy_total_manager->working_alarm_mode = working_normal;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;

				//���Զ�ģʽ���������У�����һ��֮����л����ֶ���Ȼ��Ͳ��������ˣ������ٴ��л������Զ�ģʽ�������У�
				if(p_control_policy_total_manager->fcu_system_running_mode == system_running_semi_auto)
				{
					p_control_policy_total_manager->fcu_system_running_mode = system_running_manual;
				}
			}
		}
	}

	return error_code;
}


//fcu���أ�����8���㷨������ʱ������fc����������ɹ����ͽ������н׶Σ��������ʧ�ܣ�����л��˴�����Ȼ�󷵻صȴ��׶�
enum Error_code Control_Policy_Total_Manager_for_start8(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->fcu_system_running_mode && p_control_policy_total_manager->working_control_mode == working_control_start8)
	{
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_1S)
		{
			//��ʱ����ѹ������ɹ���������Ѽ��  
			//ע���ˣ���ѹ��ת��35000��ʱ����ѷ�ѹֻ��7kpa�����Ҹ�������ѹ������ѹ���ܲ���
			if(fcu_data_buffer.air_data_buffer.air_pressure_pile_inlet < 3)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = Air_pressure_pile_inlet_under_error1;//��ѷ�ѹ	Ƿѹ��һ�����ϣ�
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_start8;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			//����������
			else if(fcu_data_buffer.air_data_buffer.air_rate_of_flow < 100)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = Air_rate_of_flow_under_error1 ;			//�����������ͣ�һ�����ϣ�
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_start8;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			else
			{
			    //45kw�·�������������ѹ��֮���ٶϿ�С���踺�أ�����������ѭ���á�
			    fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_is_enble_load_resistance = 0;
			    
			    //Ŀǰ��˫�ѷ����������������ˮ�������ˣ�ʵ������ѭ���õ�ת��3000�����ŵġ�
				fcu_data_buffer.h2_data_buffer.h2_circulating_pump_speed_setpoint = H2_CIRCULATING_PUMP_SPEED_SETPOINT_3000;
				fcu_data_buffer.h2_data_buffer.h2_circulating_pump_enble = 1;
				fcu_data_buffer.h2_data_buffer.h2_circulating_pump_enable_pump = 1;
			    
				//�л�������10״̬��������״̬��������	����״̬��������	���ϵȼ���������
				p_control_policy_total_manager->working_control_mode = working_control_start9;
				p_control_policy_total_manager->working_status_mode = working_status_starting;
				p_control_policy_total_manager->working_alarm_mode = working_normal;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;

				//���Զ�ģʽ���������У�����һ��֮����л����ֶ���Ȼ��Ͳ��������ˣ������ٴ��л������Զ�ģʽ�������У�
				if(p_control_policy_total_manager->fcu_system_running_mode == system_running_semi_auto)
				{
					p_control_policy_total_manager->fcu_system_running_mode = system_running_manual;
				}
			}
		}
	}

	return error_code;
}



//fcu���أ�����9���㷨������ʱ������fc����������ɹ����ͽ������н׶Σ��������ʧ�ܣ�����л��˴�����Ȼ�󷵻صȴ��׶�
enum Error_code Control_Policy_Total_Manager_for_start9(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->fcu_system_running_mode && p_control_policy_total_manager->working_control_mode == working_control_start9)
	{
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_3S)
		{
			//�������ѭ����can  ʵ��ת�١�
			if(Succeed != approximate(fcu_data_buffer.h2_data_buffer.h2_circulating_pump_actual_speed, H2_CIRCULATING_PUMP_SPEED_SETPOINT_3000))
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = H2_circulating_pump_actual_speed_error1;	//����ѭ���� ʵ��ת�ٹ��ϣ�һ�����ϣ�
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_start9;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			//�������ѭ����can  ״̬
			else if(fcu_data_buffer.h2_data_buffer.h2_circulating_pump_status_diagnose_word != 5)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = H2_circulating_pump_working_statas_error1;	//����ѭ���ù���״̬���ϣ�һ�����ϣ�
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_start9;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			else
			{
				//��һ�������Ѽ��  

				//�л�������6״̬��������״̬��������	����״̬��������	���ϵȼ���������
				p_control_policy_total_manager->working_control_mode = working_control_start10;
				p_control_policy_total_manager->working_status_mode = working_status_starting;
				p_control_policy_total_manager->working_alarm_mode = working_normal;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;

				//���Զ�ģʽ���������У�����һ��֮����л����ֶ���Ȼ��Ͳ��������ˣ������ٴ��л������Զ�ģʽ�������У�
				if(p_control_policy_total_manager->fcu_system_running_mode == system_running_semi_auto)
				{
					p_control_policy_total_manager->fcu_system_running_mode = system_running_manual;
				}
			}
		}
	}

	return error_code;
}


//fcu���أ�����10���㷨������ʱ������fc����������ɹ����ͽ������н׶Σ��������ʧ�ܣ�����л��˴�����Ȼ�󷵻صȴ��׶�
enum Error_code Control_Policy_Total_Manager_for_start10(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->fcu_system_running_mode && p_control_policy_total_manager->working_control_mode == working_control_start10)
	{
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_1S)
		{
			//����ѹ��Ѳ��
			if(fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_voltage < GALVANIC_PILE_OPEN_CIRCUIT_VOLTAGE )
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = Galvanic_pile_voltage_under_error1;			//��ѵ�ѹ���ͣ�һ�����ϣ�
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_start10;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			else if(fcu_data_buffer.galvanic_pile_data_buffer.electric1_single_chip_minimum_voltage < ITINERANT_DETECTIVE_OPEN_CIRCUIT_SINGLE_VOLTAGE)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = Glectric1_single_chip_minimum_voltage_under_error1;			//Ѳ�쵥Ƭ��ѹ���ͣ�һ�����ϣ�
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_start10;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			else if(fcu_data_buffer.galvanic_pile_data_buffer.electric1_single_chip_minimum_voltage2 < ITINERANT_DETECTIVE_OPEN_CIRCUIT_SINGLE_VOLTAGE)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = Glectric1_single_chip_minimum_voltage_under_error1;			//Ѳ�쵥Ƭ��ѹ���ͣ�һ�����ϣ�
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_start10;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
		/*	//Ѳ���can���� �ж�  �������ͣ����Ѳ��ĵ�ѹ�ڴ�����ʱ�򣬿��ܻ�����쳣�жϣ��������Ͳ��ж�״̬�ˣ�ֻ�����з���֮���ж���С��ѹ��
			else if(fcu_data_buffer.galvanic_pile_data_buffer.itinerant_detective_working_statas  != 1 )
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = Itinerant_detective_working_statas_error1;		//Ѳ�칤��״̬���ϣ�һ�����ϣ�
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_start10;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}    */
			//����ѵ���
			else if(fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_electricity > 5 ||
				fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_electricity < -5 )
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = Galvanic_pile_electricity_statas_error1;	//��ѵ���������״̬���ϣ�����������̵������ϣ�һ�����ϣ�
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_start10;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			else
			{
				//����������֮�󣬴�ʱ��ѹ�ȶ��󣬾Ϳ���pid1
				//			fcu_data_buffer.h2_data_buffer.h2_pressure_advance_set_value = 0;
				fcu_data_buffer.h2_data_buffer.h2_pressure_pid1_advance_time = 250;

				fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid1.Kp = PID1_KP;
				fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid1.Ki = PID1_KI;
				fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid1.Kd = PID1_KD;
				fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid1.is_enble_pid = 1;

				//�л�������11״̬��������״̬��������	����״̬��������	���ϵȼ���������
				p_control_policy_total_manager->working_control_mode = working_control_start11;
				p_control_policy_total_manager->working_status_mode = working_status_starting;
				p_control_policy_total_manager->working_alarm_mode = working_normal;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;

				//���Զ�ģʽ���������У�����һ��֮����л����ֶ���Ȼ��Ͳ��������ˣ������ٴ��л������Զ�ģʽ�������У�
				if(p_control_policy_total_manager->fcu_system_running_mode == system_running_semi_auto)
				{
					p_control_policy_total_manager->fcu_system_running_mode = system_running_manual;
				}
			}
		}
	}

	return error_code;
}


//fcu���أ�����11���㷨������ʱ������fc����������ɹ����ͽ������н׶Σ��������ʧ�ܣ�����л��˴�����Ȼ�󷵻صȴ��׶�
enum Error_code Control_Policy_Total_Manager_for_start11(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->fcu_system_running_mode && p_control_policy_total_manager->working_control_mode == working_control_start11)
	{
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_15S)
		{
			//��ʱ2������ �������ѹ�Ĳ��������￪����pid����ѹ�������С�ġ�
			if(fcu_data_buffer.h2_data_buffer.h2_pressure_fluctuate_last_max -
				fcu_data_buffer.h2_data_buffer.h2_pressure_fluctuate_last_min < 2)	
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = H2_pressure_no_fluctuations_error1;	//����ѹ��û�в�����������β�ŷ����ϣ�һ�����ϣ�
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_start11;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			else if(fcu_data_buffer.h2_data_buffer.h2_pressure_fluctuate_last_max > 30 )
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = 	H2_pressure_proportional_valve_rear_over_error1;	//����������ѹ  ��ѹ��һ�����ϣ�
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_start11;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			else if(fcu_data_buffer.h2_data_buffer.h2_pressure_fluctuate_last_min < -30)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = H2_pressure_proportional_valve_rear_under_error1;	//����������ѹ  Ƿѹ��һ�����ϣ�
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_start11;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			else
			{
				//�л�������12״̬��������״̬��������	����״̬��������	���ϵȼ���������
				p_control_policy_total_manager->working_control_mode = working_control_start12;
				p_control_policy_total_manager->working_status_mode = working_status_starting;
				p_control_policy_total_manager->working_alarm_mode = working_normal;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;

				//���Զ�ģʽ���������У�����һ��֮����л����ֶ���Ȼ��Ͳ��������ˣ������ٴ��л������Զ�ģʽ�������У�
				if(p_control_policy_total_manager->fcu_system_running_mode == system_running_semi_auto)
				{
					p_control_policy_total_manager->fcu_system_running_mode = system_running_manual;
				}
			}
		}
	}

	return error_code;
}


//fcu���أ�����12���㷨������ʱ������fc����������ɹ����ͽ������н׶Σ��������ʧ�ܣ�����л��˴�����Ȼ�󷵻صȴ��׶�
enum Error_code Control_Policy_Total_Manager_for_start12(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->fcu_system_running_mode && p_control_policy_total_manager->working_control_mode == working_control_start12)
	{
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_1S)
		{
			//���2��ɢ��ϵͳ��ˮѹ
			if(fcu_data_buffer.water_for_pile_data_buffer.water_pressure_pile_inlet1 < 40)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = Water_pressure_pile_inlet_under_error1;	//���ˮѹ	Ƿѹ��һ�����ϣ�
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_start12;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			else if(fcu_data_buffer.water_for_pile_data_buffer.water_pressure_pile_outlet1 < 5)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = Water_pressure_pile_outlet_under_error1;	//����ˮѹ	Ƿѹ��һ�����ϣ�
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_start12;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			else if(fcu_data_buffer.water_for_compressor_data_bufferr.water_pressure_pump_outlet < 20)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = Water_pressure_compressor_outlet_under_error1 ;	//��ѹ������ˮѹ	Ƿѹ��һ�����ϣ�
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_start12;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			else     
			{
				//��ɢ��ϵͳ�ķ���pidʹ��
				fcu_data_buffer.water_for_pile_data_buffer.water_temperature_fan_pid1.is_enble_pid = 1;
				fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_fan_pid.is_enble_pid = 1;	

				//�򿪵������̵�����fcu����run״̬
				fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_is_enble_output = 1;
				//�л�������״̬��������״̬�����У�	����״̬�����У�	���ϵȼ���������
				p_control_policy_total_manager->working_control_mode = working_control_run;
				p_control_policy_total_manager->working_status_mode = working_status_run;
				p_control_policy_total_manager->working_alarm_mode = working_normal;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;

				//���Զ�ģʽ���������У�����һ��֮����л����ֶ���Ȼ��Ͳ��������ˣ������ٴ��л������Զ�ģʽ�������У�
				if(p_control_policy_total_manager->fcu_system_running_mode == system_running_semi_auto)
				{
					p_control_policy_total_manager->fcu_system_running_mode = system_running_manual;
				}
			}
		}
	}

	return error_code;
}











//fcu���أ����е��㷨�����ʿ��ƣ�������г����쳣������л��˴�����Ȼ�󷵻صȴ��׶�
enum Error_code Control_Policy_Total_Manager_for_run(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL )
	{return Pointer_is_null;}


	if(p_control_policy_total_manager->fcu_system_running_mode && p_control_policy_total_manager->working_control_mode == working_control_run)
	{
		//�����Ȼ��fcu����������   100ms����һ��
		if(fcu_data_buffer.galvanic_pile_data_buffer.fcu_start_enable == 1 )
		{

			//100ms����һ��
			if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_100MS)
			{
				//�ȵ�����Ȼ���ڽ��б����Ե��ж�
				//FCU�ȶ�����ʱ���Զ�����
				FCU_automatic_gear_shift();    

				//����ʱ�ı������飬ͨ���ͣ�
				FCU_run_protect_check_common(p_control_policy_total_manager);    
				
				//��ʱ�ӵ�һ�������жϵ���ʱ  3��
				//�������һ���澯����ô��Ҫ������ʱ����ʱ�ж�
				if(p_control_policy_total_manager->working_alarm_mode == one_level_fault)
				{
				    //���������·����������ѹ�������ѹ�쳣����ô��Ҫ�Թ�����ʱ����
				   if(p_control_policy_total_manager->working_FCU_error_code < 0x1201 ||
				        p_control_policy_total_manager->working_FCU_error_code > 0x130c) 
				   {
				        //����ǵ�һ�γ����ϣ���ô���޸ı��Ϊ1�����ҽ���ʱ�������Ȼ���������״̬����ϵͳ�ָ���run״̬
				        if(p_control_policy_total_manager->one_level_fault_flag_temp == 0) 
				        {
				            p_control_policy_total_manager->one_level_fault_flag_temp = 1; 
				            p_control_policy_total_manager->one_level_fault_time_temp = system_time;
				            
	                    	p_control_policy_total_manager->working_control_mode = working_control_run;
	                    	p_control_policy_total_manager->working_status_mode = working_status_run;
	                    	p_control_policy_total_manager->working_alarm_mode = working_normal;
	                    	p_control_policy_total_manager->working_FCU_error_code = Succeed;
	                    	p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		            		p_control_policy_total_manager->working_error_count = 0; 
		            		
				        }
				        //�����һ���Ѿ����ֹ��ϣ���ô��ξ�Ҫ����ʱ���жϣ�
				        else
				        {
				            //û�г�ʱ���Ǿ��������״̬����ϵͳ�ָ���run״̬
				            if(system_time - p_control_policy_total_manager->one_level_fault_time_temp <= 5000)
				            {
	                        	p_control_policy_total_manager->working_control_mode = working_control_run;
	                        	p_control_policy_total_manager->working_status_mode = working_status_run;
	                        	p_control_policy_total_manager->working_alarm_mode = working_normal;
	                        	p_control_policy_total_manager->working_FCU_error_code = Succeed;
	                        	p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		            	    	p_control_policy_total_manager->working_error_count = 0; 				                
				            }
				            //��ʱ���ǾͲ���������ô�ͻ�ֱ�ӵ�fault0ȥ����ͣ����
				            else
			            	{
			            	   p_control_policy_total_manager->one_level_fault_flag_temp = 0; 
		            		}  		            
				        }
				   }
				   // ��·����������ѹ�������ѹ�쳣������������ô�ͻ�ֱ�ӵ�fault0ȥ����ͣ����
				   else
		    		{
			    	   p_control_policy_total_manager->one_level_fault_flag_temp = 0; 
			    	}	   
				}
				//����ָ���������ô�����־λ���������������״̬��û�еģ���û�б�Ҫ�����
				else
				{
				   p_control_policy_total_manager->one_level_fault_flag_temp = 0; 
				}

				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}

			//���Զ�ģʽ���������У�����һ��֮����л����ֶ���Ȼ��Ͳ��������ˣ������ٴ��л������Զ�ģʽ�������У�
			if(p_control_policy_total_manager->fcu_system_running_mode == system_running_semi_auto)
			{
				p_control_policy_total_manager->fcu_system_running_mode = system_running_manual;
			}
		}
		//����յ�ͣ������
		else
		{
			if(fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_electricity > 50 )
			{
				//����ʱ���յ�ͣ�������������ͣ����
				//��ʱ30�룬�ڼ��ճ� �����ͱ���У�飬���ǻᱨ������ʾ����Ա����30s�ڽ��н���
				//30s֮��ǿ��
				if(system_time - p_control_policy_total_manager->fcu_updata_event_time < FCU_SYSTEM_CHANGE_MODE_DELAY_30S)
				{

					//�ȵ�����Ȼ���ڽ��б����Ե��ж�
					//FCU�ȶ�����ʱ���Զ�����
					FCU_automatic_gear_shift();    

					//����ʱ�ı������飬ͨ���ͣ�
					FCU_run_protect_check_common(p_control_policy_total_manager);   

					if(p_control_policy_total_manager->working_alarm_mode > one_level_fault)
					{			
						p_control_policy_total_manager->working_control_mode = working_control_run;
						p_control_policy_total_manager->working_status_mode = working_status_run;
						p_control_policy_total_manager->working_alarm_mode = three_level_fault;
						p_control_policy_total_manager->working_FCU_error_code = Galvanic_pile_electricity_over_when_stop_error2;	//�յ�ͣ��ָ��ʱ����������100A����ʾ�û����ܴ���ͣ����2�����ϣ�
						p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
						//		p_control_policy_total_manager->fcu_updata_event_time = system_time;
					}
				}
				else
				{
					//�л���ֹͣ1״̬��������״̬��ֹͣ��	����״̬��ֹͣ��	���ϵȼ���������
					//ע���ˣ�����Ҫ���2���߼���3���澯
					p_control_policy_total_manager->working_control_mode = working_control_stop1;
					p_control_policy_total_manager->working_status_mode = working_status_stoping;
					p_control_policy_total_manager->working_alarm_mode = working_normal;
			//		p_control_policy_total_manager->working_FCU_error_code = Succeed;
			//		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
					p_control_policy_total_manager->fcu_updata_event_time = system_time;
					
					//���Զ�ģʽ���������У�����һ��֮����л����ֶ���Ȼ��Ͳ��������ˣ������ٴ��л������Զ�ģʽ�������У�
	    	    	if(p_control_policy_total_manager->fcu_system_running_mode == system_running_semi_auto)
	    	    	{
	    	    		p_control_policy_total_manager->fcu_system_running_mode = system_running_manual;
	    	    	}
				}
			}
			else
			{
				//�л���ֹͣ1״̬��������״̬��ֹͣ��	����״̬��ֹͣ��	���ϵȼ���������
				//ע���ˣ�����Ҫ���2���߼���3���澯
				p_control_policy_total_manager->working_control_mode = working_control_stop1;
				p_control_policy_total_manager->working_status_mode = working_status_stoping;
				p_control_policy_total_manager->working_alarm_mode = working_normal;
		//		p_control_policy_total_manager->working_FCU_error_code = Succeed;
		//		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
				
				//���Զ�ģʽ���������У�����һ��֮����л����ֶ���Ȼ��Ͳ��������ˣ������ٴ��л������Զ�ģʽ�������У�
			if(p_control_policy_total_manager->fcu_system_running_mode == system_running_semi_auto)
			{
				p_control_policy_total_manager->fcu_system_running_mode = system_running_manual;
			}
			}
		}
	}


}




//fcu���أ�ֹͣ1���㷨������ʱ��ֹͣfc�����ս���ȴ��׶�
enum Error_code Control_Policy_Total_Manager_for_stop1(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->fcu_system_running_mode && p_control_policy_total_manager->working_control_mode == working_control_stop1)
	{
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_1S)
		{
			//�жϵ�����ֻ����С�������߿��ص�ʱ�򣬲�������ͣ��
			if(fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_electricity > 50 )
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault1;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = Galvanic_pile_electricity_over_when_stop_error1;//�յ�ͣ��ָ��ʱ����������100A����ʾ�û����ܴ���ͣ����һ�����ϣ�
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_stop1;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			else
			{
				//�ر�ɢ��ϵͳ�ķ���pidʹ��
				fcu_data_buffer.water_for_pile_data_buffer.water_temperature_fan_pid1.is_enble_pid = 0;
				fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_fan_pid.is_enble_pid = 0;	

				//��������β�ţ�������
				fcu_data_buffer.h2_data_buffer.h2_is_enable_outlet_valve = 1;
				fcu_data_buffer.h2_data_buffer.h2_pid_mode = 2;
				fcu_data_buffer.h2_data_buffer.h2_pressure_advance_current_value = 0;

				//�л���ֹͣ2״̬��������״̬��ֹͣ��	����״̬��ֹͣ��	���ϵȼ���������
				p_control_policy_total_manager->working_control_mode = working_control_stop2;
				p_control_policy_total_manager->working_status_mode = working_status_stoping;
				p_control_policy_total_manager->working_alarm_mode = working_normal;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;

				//���Զ�ģʽ���������У�����һ��֮����л����ֶ���Ȼ��Ͳ��������ˣ������ٴ��л������Զ�ģʽ�������У�
				if(p_control_policy_total_manager->fcu_system_running_mode == system_running_semi_auto)
				{
					p_control_policy_total_manager->fcu_system_running_mode = system_running_manual;
				}
			}
		}
	}

	return error_code;
}




//fcu���أ�ֹͣ2���㷨������ʱ��ֹͣfc�����ս���ȴ��׶�
enum Error_code Control_Policy_Total_Manager_for_stop2(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->fcu_system_running_mode && p_control_policy_total_manager->working_control_mode == working_control_stop2)
	{
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_2S)
		{
			//����pid1��pid2
			fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid1.Kp = PID1_KP;
			fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid1.Ki = PID1_KI;
			fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid1.Kd = PID1_KD;
			fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid2.Kp = PID2_KP;
			fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid2.Ki = PID2_KI;
			fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid2.Kd = PID2_KD;

			//�жϸ��أ��رյ������̵���
			fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_is_enble_output = 0;
			
			//45kw�·�������ǰ����С���踺�أ�
			fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_is_enble_load_resistance = 1;

			//�л���ֹͣ3״̬��������״̬��ֹͣ��	����״̬��ֹͣ��	���ϵȼ���������
			p_control_policy_total_manager->working_control_mode = working_control_stop3;
			p_control_policy_total_manager->working_status_mode = working_status_stoping;
			p_control_policy_total_manager->working_alarm_mode = working_normal;
			p_control_policy_total_manager->fcu_updata_event_time = system_time;

			//���Զ�ģʽ���������У�����һ��֮����л����ֶ���Ȼ��Ͳ��������ˣ������ٴ��л������Զ�ģʽ�������У�
			if(p_control_policy_total_manager->fcu_system_running_mode == system_running_semi_auto)
			{
				p_control_policy_total_manager->fcu_system_running_mode = system_running_manual;
			}

		}
	}

	return error_code;
}



//fcu���أ�ֹͣ3���㷨������ʱ��ֹͣfc�����ս���ȴ��׶�
enum Error_code Control_Policy_Total_Manager_for_stop3(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->fcu_system_running_mode && p_control_policy_total_manager->working_control_mode == working_control_stop3)
	{
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_1S)
		{
			//�жϵ����Ƿ�Ϊ0����Ϊ0�ͱ�ʾ �������Ӵ������ˣ�������൱Σ�յġ�
			//45kw�·�������ǰ������С���أ�����5A�ĵ���
			if(fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_electricity > 12 ||
				fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_electricity < -5 )
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault3;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = Galvanic_pile_electricity_statas_error1;	//��ѵ���������״̬���ϣ�����������̵������ϣ�һ�����ϣ�
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_stop3;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			else
			{
				//����Ŀ����ѹ���Ϳ�ѹ��ת�١�
				fcu_data_buffer.h2_data_buffer.h2_pressure_target_value = 50;
				
				fcu_data_buffer.air_data_buffer.air_compressor_speed_pid.is_enble_pid = 0;
				fcu_data_buffer.air_data_buffer.air_rate_of_flow_target = 960;
				fcu_data_buffer.air_data_buffer.air_compressor_speed_setpoint = 20000;

				//�л���ֹͣ4״̬��������״̬��ֹͣ��	����״̬��ֹͣ��	���ϵȼ���������
				p_control_policy_total_manager->working_control_mode = working_control_stop4;
				p_control_policy_total_manager->working_status_mode = working_status_stoping;
				p_control_policy_total_manager->working_alarm_mode = working_normal;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;

				//���Զ�ģʽ���������У�����һ��֮����л����ֶ���Ȼ��Ͳ��������ˣ������ٴ��л������Զ�ģʽ�������У�
				if(p_control_policy_total_manager->fcu_system_running_mode == system_running_semi_auto)
				{
					p_control_policy_total_manager->fcu_system_running_mode = system_running_manual;
				}
			}
		}
	}

	return error_code;
}



//fcu���أ�ֹͣ4���㷨������ʱ��ֹͣfc�����ս���ȴ��׶�
enum Error_code Control_Policy_Total_Manager_for_stop4(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->fcu_system_running_mode && p_control_policy_total_manager->working_control_mode == working_control_stop4)
	{
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_5S)
		{
			//������������ѹ�Ƿ�ﵽָ����65
	/*		if(Succeed != approximate(fcu_data_buffer.h2_data_buffer.h2_pressure_proportional_valve_rear, 65))
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault3;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = H2_pressure_proportional_valve_rear_unstable_error1;	//����������ѹ	ѹ�����ȣ�һ�����ϣ�
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_stop4;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			//��������ѹ�Ƿ�ﵽָ����50
			else */if(Succeed != approximate(fcu_data_buffer.h2_data_buffer.h2_pressure_pile_inlet, 50))
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault3;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = H2_pressure_pile_inlet_unstable_error1;	//�����ѹ	ѹ�����ȣ�һ�����ϣ�
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_stop4;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			//��������ѹ�Ƿ�ﵽָ����50-10
	/*		else if(Succeed != approximate(fcu_data_buffer.h2_data_buffer.h2_pressure_pile_outlet, 50-10))
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault3;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = H2_pressure_pile_outlet_unstable_error1;	//������ѹ	ѹ�����ȣ�һ�����ϣ�
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_stop4;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}     */
			//���β����ѹ�Ƿ�ﵽָ����50-10
			else if(Succeed != approximate(fcu_data_buffer.h2_data_buffer.h2_pressure_tail_outlet, 50-10))
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault3;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = H2_pressure_tail_outlet_unstable_error1;	//β����ѹ	ѹ�����ȣ�һ�����ϣ�
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_stop4;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			//�����������ȣ� β�ų���ʱ��Ŀ����ѹ50��������һ����ȶ���2000+
			else if(fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pwm_dutyfactor < 1000)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault3;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = H2_proportional_valve_statas_error1;	//������״̬���ϣ�һ�����ϣ�
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_stop4;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			//������ѹ��can  ʵ��ת��
			else if(Succeed != approximate(fcu_data_buffer.air_data_buffer.air_compressor_speed_setpoint, 
				fcu_data_buffer.air_data_buffer.air_compressor_act_speed))
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault3;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = Air_compressor_act_speed_error1;			//��ѹ�� ʵ��ת�ٹ��ϣ�һ�����ϣ�
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_stop4;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			//������ѹ��can  ״̬
			else if(fcu_data_buffer.air_data_buffer.air_compressor_state != 12 &&
				fcu_data_buffer.air_data_buffer.air_compressor_state != 76)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault3;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = Air_compressor_working_statas_error1;		//��ѹ������״̬���ϣ�һ�����ϣ�
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_stop4;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			else
			{
				//�ر�pid1������pid2��Ȼ����봵ɨģʽ
				fcu_data_buffer.h2_data_buffer.h2_pid_mode = 2;
				fcu_data_buffer.h2_data_buffer.h2_pressure_advance_set_value = 0;
				fcu_data_buffer.h2_data_buffer.h2_pressure_pid2_advance_time = 200;

				fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid2.Kp = PID2_KP;
				fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid2.Ki = PID2_KI;
				fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid2.Kd = PID2_KD;
				//		fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pwm_dutyfactor = 0;
				fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid2.is_enble_pid = 1;
				fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid1.is_enble_pid = 0;

				//Ȼ����봵ɨģʽ������ѭ���ü�����ת
				//����β���ɳ�������Ϊ��ɨģʽ��1s/0.5s
				fcu_data_buffer.h2_data_buffer.h2_outlet_valve_open_time = 500;
				fcu_data_buffer.h2_data_buffer.h2_outlet_valve_close_time = 1000;
				fcu_data_buffer.h2_data_buffer.h2_is_enable_outlet_valve = 2;
				//��������β�ţ���Ϊ��ɨģʽ��2s/0.5s
				fcu_data_buffer.air_data_buffer.air_outlet_valve_open_time = 500;
				fcu_data_buffer.air_data_buffer.air_outlet_valve_close_time = 2000;
				fcu_data_buffer.air_data_buffer.air_is_enable_outlet_valve = 2;

				//����ѭ�����ڽϴ��ת�������У�Ҫ��ѭ���������ˮ��ɨ������
				fcu_data_buffer.h2_data_buffer.h2_circulating_pump_speed_setpoint = H2_CIRCULATING_PUMP_SPEED_SETPOINT_3000;

				//�л���ֹͣ5״̬��������״̬��ֹͣ��	����״̬��ֹͣ��	���ϵȼ���������
				p_control_policy_total_manager->working_control_mode = working_control_stop5;
				p_control_policy_total_manager->working_status_mode = working_status_stoping;
				p_control_policy_total_manager->working_alarm_mode = working_normal;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;

				//���Զ�ģʽ���������У�����һ��֮����л����ֶ���Ȼ��Ͳ��������ˣ������ٴ��л������Զ�ģʽ�������У�
				if(p_control_policy_total_manager->fcu_system_running_mode == system_running_semi_auto)
				{
					p_control_policy_total_manager->fcu_system_running_mode = system_running_manual;
				}
			}
		}
	}

	return error_code;
}


//fcu���أ�ֹͣ5���㷨������ʱ��ֹͣfc�����ս���ȴ��׶�
enum Error_code Control_Policy_Total_Manager_for_stop5(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->fcu_system_running_mode && p_control_policy_total_manager->working_control_mode == working_control_stop5)
	{
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_1S)
		{
			//ˮ�úͷ���ȫ�����ӿ�ɢ�ȡ�
			//������ˮ��    ��ѳ���ˮ��    ��ѹ������ˮ��    ����һˮ�ó���ˮ��
			if(fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_inlet1 > 45 || 
				fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_outlet1 > 45 )
			{
				//ˮ�úͷ���ȫ�����ӿ�ɢ�ȡ�
				fcu_data_buffer.water_for_pile_data_buffer.water_pump_pwm_dutyfactor1 = 9000;
				fcu_data_buffer.water_for_pile_data_buffer.water_fan_pwm_dutyfactor1 = 9000;
				fcu_data_buffer.water_for_pile_data_buffer.water_fan_pwm_dutyfactor2 = 9000;
			}

			if(fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_compressor_outlet > 45 ||
				fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_pump_outlet > 45)
			{
				//ˮ�úͷ���ȫ�����ӿ�ɢ�ȡ�
				fcu_data_buffer.water_for_compressor_data_bufferr.water_pump_pwm_dutyfactor = 9000;
				fcu_data_buffer.water_for_compressor_data_bufferr.water_fan_pwm_dutyfactor = 9000;
			}

			//�л���ֹͣ6״̬��������״̬��ֹͣ��	����״̬��ֹͣ��	���ϵȼ���������
			p_control_policy_total_manager->working_control_mode = working_control_stop6;
			p_control_policy_total_manager->working_status_mode = working_status_stoping;
			p_control_policy_total_manager->working_alarm_mode = working_normal;
			p_control_policy_total_manager->fcu_updata_event_time = system_time;

			//���Զ�ģʽ���������У�����һ��֮����л����ֶ���Ȼ��Ͳ��������ˣ������ٴ��л������Զ�ģʽ�������У�
			if(p_control_policy_total_manager->fcu_system_running_mode == system_running_semi_auto)
			{
				p_control_policy_total_manager->fcu_system_running_mode = system_running_manual;
			}

		}
	}

	return error_code;
}


//fcu���أ�ֹͣ6���㷨������ʱ��ֹͣfc�����ս���ȴ��׶�
enum Error_code Control_Policy_Total_Manager_for_stop6(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->fcu_system_running_mode && p_control_policy_total_manager->working_control_mode == working_control_stop6)
	{
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_20S)
		{
			//�����ѹ������pid1û�п������������Ϊ��Ƶ����������Ҫ�����10
			if(fcu_data_buffer.h2_data_buffer.h2_pressure_fluctuate_last_max -
				fcu_data_buffer.h2_data_buffer.h2_pressure_fluctuate_last_min < 10)
			{
			    //�ر�����ѭ����
				fcu_data_buffer.h2_data_buffer.h2_circulating_pump_speed_setpoint = H2_CIRCULATING_PUMP_SPEED_SETPOINT_3000;
				fcu_data_buffer.h2_data_buffer.h2_circulating_pump_enble = 1;
				fcu_data_buffer.h2_data_buffer.h2_circulating_pump_enable_pump = 0;
				
				p_control_policy_total_manager->working_control_mode = working_control_fault7;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = H2_pressure_no_fluctuations_error1;	//����ѹ��û�в�����������β�ŷ����ϣ�һ�����ϣ�
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_stop6;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			else
			{
				//�ر�����ѭ����
				fcu_data_buffer.h2_data_buffer.h2_circulating_pump_speed_setpoint = H2_CIRCULATING_PUMP_SPEED_SETPOINT_3000;
				fcu_data_buffer.h2_data_buffer.h2_circulating_pump_enble = 1;
				fcu_data_buffer.h2_data_buffer.h2_circulating_pump_enable_pump = 0;

				//�л���ֹͣ7״̬��������״̬��ֹͣ��	����״̬��ֹͣ��	���ϵȼ���������
				p_control_policy_total_manager->working_control_mode = working_control_stop7;
				p_control_policy_total_manager->working_status_mode = working_status_stoping;
				p_control_policy_total_manager->working_alarm_mode = working_normal;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;

				//���Զ�ģʽ���������У�����һ��֮����л����ֶ���Ȼ��Ͳ��������ˣ������ٴ��л������Զ�ģʽ�������У�
				if(p_control_policy_total_manager->fcu_system_running_mode == system_running_semi_auto)
				{
					p_control_policy_total_manager->fcu_system_running_mode = system_running_manual;
				}
			}
		}
	}

	return error_code;
}


//fcu���أ�ֹͣ7���㷨������ʱ��ֹͣfc�����ս���ȴ��׶�
enum Error_code Control_Policy_Total_Manager_for_stop7(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->fcu_system_running_mode && p_control_policy_total_manager->working_control_mode == working_control_stop7)
	{
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_2S)
		{
			//�������ѭ����can  ʵ��ת�١�
			if(fcu_data_buffer.h2_data_buffer.h2_circulating_pump_actual_speed > 500)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault7;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = H2_circulating_pump_actual_speed_error1;	//����ѭ���� ʵ��ת�ٹ��ϣ�һ�����ϣ�
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_stop7;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			//�������ѭ����can  ״̬
			else if(fcu_data_buffer.h2_data_buffer.h2_circulating_pump_status_diagnose_word != 4)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault7;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = H2_circulating_pump_working_statas_error1;	//����ѭ���ù���״̬���ϣ�һ�����ϣ�
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_stop7;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			else
			{
				//�ر�������ڷ����ж�������Դ
				fcu_data_buffer.h2_data_buffer.h2_inlet_valve = 0;
				
				//20181218���ﳣ������β�ŷ������ٽ������ų���
				//���˸о�����֮ǰ��1/0.5s�Ĵ�ɨģʽ��������ر�������ڷ����ж�������Դ֮�󣬴�ɨ�䲻�����ˡ�
				//Ŀ�������ų����������ֱ�ӳ�������β�ŷ������ٽ������ų���
				fcu_data_buffer.h2_data_buffer.h2_is_enable_outlet_valve = 1;	

				//ͬʱ�رտ�ѹ���Ϳ���β��
				fcu_data_buffer.air_data_buffer.air_compressor_enable = 0;
				fcu_data_buffer.air_data_buffer.air_is_enable_outlet_valve = 0;

				//�л���ֹͣ8״̬��������״̬��ֹͣ��	����״̬��ֹͣ��	���ϵȼ���������
				p_control_policy_total_manager->working_control_mode = working_control_stop8;
				p_control_policy_total_manager->working_status_mode = working_status_stoping;
				p_control_policy_total_manager->working_alarm_mode = working_normal;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;

				//���Զ�ģʽ���������У�����һ��֮����л����ֶ���Ȼ��Ͳ��������ˣ������ٴ��л������Զ�ģʽ�������У�
				if(p_control_policy_total_manager->fcu_system_running_mode == system_running_semi_auto)
				{
					p_control_policy_total_manager->fcu_system_running_mode = system_running_manual;
				}
			}
		}
	}

	return error_code;
}



//fcu���أ�ֹͣ8���㷨������ʱ��ֹͣfc�����ս���ȴ��׶�
enum Error_code Control_Policy_Total_Manager_for_stop8(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->fcu_system_running_mode && p_control_policy_total_manager->working_control_mode == working_control_stop8)
	{
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_5S)
		{
			//�жϱ�����ǰ�ͺ����ѹ
			if(fcu_data_buffer.h2_data_buffer.h2_pressure_proportional_valve_front > 85)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault7;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = H2_pressure_proportional_valve_front_over_error1 ;//������ǰ��ѹ	��ѹ��һ�����ϣ�
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_stop8;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			else if(fcu_data_buffer.h2_data_buffer.h2_pressure_proportional_valve_rear > 10)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault7;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = H2_pressure_proportional_valve_rear_over_error1 ;//����������ѹ  ��ѹ��һ�����ϣ�
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_stop8;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			else if(fcu_data_buffer.h2_data_buffer.h2_pressure_pile_inlet > 10)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault7;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = H2_pressure_pile_inlet_over_error1;		//�����ѹ  ��ѹ��һ�����ϣ�
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_stop8;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			//������ѹ��can  ʵ��ת��
			else if(fcu_data_buffer.air_data_buffer.air_compressor_act_speed > 10000)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault7;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = Air_compressor_act_speed_error1;			//��ѹ�� ʵ��ת�ٹ��ϣ�һ�����ϣ�
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_stop8;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			//������ѹ��can  ״̬
			else if(fcu_data_buffer.air_data_buffer.air_compressor_state != 0 &&
				fcu_data_buffer.air_data_buffer.air_compressor_state != 64)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault7;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = Air_compressor_working_statas_error1;		//��ѹ������״̬���ϣ�һ�����ϣ�
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_stop8;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			else
			{
				//�رձ�������pid2�� �رձ�����pwm��    
				fcu_data_buffer.h2_data_buffer.h2_pid_mode = 2;
				fcu_data_buffer.h2_data_buffer.h2_pressure_advance_set_value = 0;
				fcu_data_buffer.h2_data_buffer.h2_pressure_pid2_advance_time = 200;
				fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid2.is_enble_pid = 0;
				fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pwm_dutyfactor = 0;
				//�ر�����β��
				fcu_data_buffer.h2_data_buffer.h2_is_enable_outlet_valve = 0;

				//�л���ֹͣ9״̬��������״̬��ֹͣ��	����״̬��ֹͣ��	���ϵȼ���������
				p_control_policy_total_manager->working_control_mode = working_control_stop9;
				p_control_policy_total_manager->working_status_mode = working_status_stoping;
				p_control_policy_total_manager->working_alarm_mode = working_normal;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;

				//���Զ�ģʽ���������У�����һ��֮����л����ֶ���Ȼ��Ͳ��������ˣ������ٴ��л������Զ�ģʽ�������У�
				if(p_control_policy_total_manager->fcu_system_running_mode == system_running_semi_auto)
				{
					p_control_policy_total_manager->fcu_system_running_mode = system_running_manual;
				}
			}
		}
	}

	return error_code;
}


//fcu���أ�ֹͣ9���㷨������ʱ��ֹͣfc�����ս���ȴ��׶�
enum Error_code Control_Policy_Total_Manager_for_stop9(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->fcu_system_running_mode && p_control_policy_total_manager->working_control_mode == working_control_stop9)
	{
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_1S)
		{
			//�򿪸���С���裬ǰ���Ѿ���ǰ���� 
			fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_is_enble_load_resistance = 1;

			//�л���ֹͣ10״̬��������״̬��ֹͣ��	����״̬��ֹͣ��	���ϵȼ���������
			p_control_policy_total_manager->working_control_mode = working_control_stop10;
			p_control_policy_total_manager->working_status_mode = working_status_stoping;
			p_control_policy_total_manager->working_alarm_mode = working_normal;
			p_control_policy_total_manager->fcu_updata_event_time = system_time;

			//���Զ�ģʽ���������У�����һ��֮����л����ֶ���Ȼ��Ͳ��������ˣ������ٴ��л������Զ�ģʽ�������У�
			if(p_control_policy_total_manager->fcu_system_running_mode == system_running_semi_auto)
			{
				p_control_policy_total_manager->fcu_system_running_mode = system_running_manual;
			}

		}
	}

	return error_code;
}


//fcu���أ�ֹͣ10���㷨������ʱ��ֹͣfc�����ս���ȴ��׶�
enum Error_code Control_Policy_Total_Manager_for_stop10(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->fcu_system_running_mode && p_control_policy_total_manager->working_control_mode == working_control_stop10)
	{
		//��ʱ�㷨��70s�ڣ��жϵ�ѹ�Ƿ�С��16V
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time < FCU_SYSTEM_CHANGE_MODE_DELAY_70S)
		{
			//�жϵ�ѹ�Ƿ�С��16V
			if(fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_voltage < 39)
			{
				//�жϸ���С����
				fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_is_enble_load_resistance = 0;

				//�л���ֹͣ11״̬��������״̬��ֹͣ��	����״̬��ֹͣ��	���ϵȼ���������
				p_control_policy_total_manager->working_control_mode = working_control_stop11;
				p_control_policy_total_manager->working_status_mode = working_status_stoping;
				p_control_policy_total_manager->working_alarm_mode = working_normal;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;

				//���Զ�ģʽ���������У�����һ��֮����л����ֶ���Ȼ��Ͳ��������ˣ������ٴ��л������Զ�ģʽ�������У�
				if(p_control_policy_total_manager->fcu_system_running_mode == system_running_semi_auto)
				{
					p_control_policy_total_manager->fcu_system_running_mode = system_running_manual;
				}
			}
			//��������ȴ���
		}
		else
		{
		    //�жϸ���С����
			fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_is_enble_load_resistance = 0;
				
			p_control_policy_total_manager->working_control_mode = working_control_fault10;
			p_control_policy_total_manager->working_status_mode = working_status_error;
			p_control_policy_total_manager->working_alarm_mode = one_level_fault;
			p_control_policy_total_manager->working_FCU_error_code = Galvanic_pile_voltage_statas_error1;	//��ѵ�ѹ��ͣ����ʱ��û�н�Ϊ16��������С����ļ̵������ϣ�һ�����ϣ�
			p_control_policy_total_manager->working_FCU_error_control_mode = working_control_stop10;
			p_control_policy_total_manager->working_error_count++; 
			p_control_policy_total_manager->fcu_updata_event_time = system_time;

		}

	}

	return error_code;
}


//fcu���أ�ֹͣ11���㷨������ʱ��ֹͣfc�����ս���ȴ��׶�
enum Error_code Control_Policy_Total_Manager_for_stop11(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->fcu_system_running_mode && p_control_policy_total_manager->working_control_mode == working_control_stop11)
	{
		//��ʱ�жϣ���10s�ڣ��жϵ�ѹ�Ƿ񷴵�������32V
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time < FCU_SYSTEM_CHANGE_MODE_DELAY_10S)
		{
			//�жϵ�ѹ�Ƿ񷴵�
			if(fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_voltage > 52
				&& p_control_policy_total_manager->galvanic_pile_load_resistance_switch_count < 3)
			{
				//ע���ˣ������stop11���˵�stop10�����´�С���裬���н���ѹ��

				//�򿪸���С���� 
				fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_is_enble_load_resistance = 1;

				//С���ص��л�����  +1
				p_control_policy_total_manager->galvanic_pile_load_resistance_switch_count++;

				//�л���ֹͣ10״̬��������״̬��ֹͣ��	����״̬��ֹͣ��	���ϵȼ���������
				p_control_policy_total_manager->working_control_mode = working_control_stop10;
				p_control_policy_total_manager->working_status_mode = working_status_stoping;
				p_control_policy_total_manager->working_alarm_mode = working_normal;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;

				//���Զ�ģʽ���������У�����һ��֮����л����ֶ���Ȼ��Ͳ��������ˣ������ٴ��л������Զ�ģʽ�������У�
				if(p_control_policy_total_manager->fcu_system_running_mode == system_running_semi_auto)
				{
					p_control_policy_total_manager->fcu_system_running_mode = system_running_manual;
				}
			}
			//��������ȴ���
		}
		else
		{
			//С���ص��л�����  ���
			p_control_policy_total_manager->galvanic_pile_load_resistance_switch_count = 0;
			//�л���ֹͣ12״̬��������״̬��ֹͣ��	����״̬��ֹͣ��	���ϵȼ���������
			p_control_policy_total_manager->working_control_mode = working_control_stop12;
			p_control_policy_total_manager->working_status_mode = working_status_stoping;
			p_control_policy_total_manager->working_alarm_mode = working_normal;
			p_control_policy_total_manager->fcu_updata_event_time = system_time;

			//���Զ�ģʽ���������У�����һ��֮����л����ֶ���Ȼ��Ͳ��������ˣ������ٴ��л������Զ�ģʽ�������У�
			if(p_control_policy_total_manager->fcu_system_running_mode == system_running_semi_auto)
			{
				p_control_policy_total_manager->fcu_system_running_mode = system_running_manual;
			}
		}
	}

	return error_code;
}


//fcu���أ�ֹͣ12���㷨������ʱ��ֹͣfc�����ս���ȴ��׶�
enum Error_code Control_Policy_Total_Manager_for_stop12(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->fcu_system_running_mode && p_control_policy_total_manager->working_control_mode == working_control_stop12)
	{
		//��ʱ�жϣ���60s�ڣ��ж�ɢ��ϵͳ���¶� �Ƿ񽵵�45��
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time < FCU_SYSTEM_CHANGE_MODE_DELAY_100S)
		{
			//������ˮ��    ��ѳ���ˮ��    ��ѹ������ˮ��    ����һˮ�ó���ˮ��
			if(fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_inlet1 <= 45 && 
				fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_outlet1 <= 45 &&
				fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_compressor_outlet <= 45 &&
				fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_pump_outlet <= 45)
			{
				//�رշ��Ⱥ�ˮ��
				//ˮ�µ�pid����stop1���Ѿ�����
				fcu_data_buffer.water_for_pile_data_buffer.water_pump_pwm_dutyfactor1 = 0;
				fcu_data_buffer.water_for_pile_data_buffer.water_fan_pwm_dutyfactor1 = 0;
				fcu_data_buffer.water_for_pile_data_buffer.water_fan_pwm_dutyfactor2 = 0;
				fcu_data_buffer.water_for_compressor_data_bufferr.water_pump_pwm_dutyfactor = 0;
				fcu_data_buffer.water_for_compressor_data_bufferr.water_fan_pwm_dutyfactor = 0;

				//�л�������״̬��������״̬��ֹͣ��	����״̬��ֹͣ��	���ϵȼ���������
				p_control_policy_total_manager->working_control_mode = working_control_wait;
				p_control_policy_total_manager->working_status_mode = working_status_wait;
				p_control_policy_total_manager->working_alarm_mode = working_normal;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;

				//���Զ�ģʽ���������У�����һ��֮����л����ֶ���Ȼ��Ͳ��������ˣ������ٴ��л������Զ�ģʽ�������У�
				if(p_control_policy_total_manager->fcu_system_running_mode == system_running_semi_auto)
				{
					p_control_policy_total_manager->fcu_system_running_mode = system_running_manual;
				}
			}
			//��������ȴ���
		}
		else
		{
		    //�رշ��Ⱥ�ˮ��
			//ˮ�µ�pid����stop1���Ѿ�����
			fcu_data_buffer.water_for_pile_data_buffer.water_pump_pwm_dutyfactor1 = 0;
			fcu_data_buffer.water_for_pile_data_buffer.water_fan_pwm_dutyfactor1 = 0;
			fcu_data_buffer.water_for_pile_data_buffer.water_fan_pwm_dutyfactor2 = 0;
			fcu_data_buffer.water_for_compressor_data_bufferr.water_pump_pwm_dutyfactor = 0;
			fcu_data_buffer.water_for_compressor_data_bufferr.water_fan_pwm_dutyfactor = 0;
				
			//ע���ˣ�ʵ�������쳣��30�ȵ�ʱ�򣬽���Ч���ܲ100s�޷���ˮ�½���45�ȣ����Թ����жϾͲ���45������55	
			//������ˮ��
			if(fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_inlet1 > 55)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault_wait;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = Water_temperature_pile_inlet_over_error1;				//������ˮ��  ���£�һ�����ϣ�
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_stop12;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			//��ѳ���ˮ��
			else if(fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_outlet1 > 55)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault_wait;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = Water_temperature_pile_outlet_over_error1;					//��ѳ���ˮ��  ���£�һ�����ϣ�
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_stop12;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			//��ѹ������ˮ��
			else if(fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_compressor_outlet > 55)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault_wait;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = Water_temperature_compressor_outlet_over_error1;	//��ѹ������ˮ��  ���£�һ�����ϣ�
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_stop12;
				p_control_policy_total_manager->working_error_count++;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			//����һˮ�ó���ˮ��
			else if(fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_pump_outlet > 55)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault_wait;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = Water_temperature_pump_outlet_over_error1;		//����һˮ�ó���ˮ��  ���£�һ�����ϣ�
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_stop12;
				p_control_policy_total_manager->working_error_count++;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			//���п�����һ���жϴ���45��Ȼ����һ�ξ�С��45�ˡ�
			else
			{
				//�л�������״̬��������״̬��ֹͣ��	����״̬��ֹͣ��	���ϵȼ���������
				p_control_policy_total_manager->working_control_mode = working_control_wait;
				p_control_policy_total_manager->working_status_mode = working_status_wait;
				p_control_policy_total_manager->working_alarm_mode = working_normal;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;

				//���Զ�ģʽ���������У�����һ��֮����л����ֶ���Ȼ��Ͳ��������ˣ������ٴ��л������Զ�ģʽ�������У�
				if(p_control_policy_total_manager->fcu_system_running_mode == system_running_semi_auto)
				{
					p_control_policy_total_manager->fcu_system_running_mode = system_running_manual;
				}
			}


		}
	}

	return error_code;
}



//fcu���أ�����ͣ�����㷨��Ŀǰ��ֱ����������
enum Error_code Control_Policy_Total_Manager_for_fault0(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->fcu_system_running_mode == system_running_full_auto && 
	        p_control_policy_total_manager->working_control_mode == working_control_fault0)
	{
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_1S)
		{
			//��������Լ�׶ξ͹����ˣ��Ǿ�ֱ����������   �����Ҫ�߹���ͣ��������
			if(p_control_policy_total_manager->working_FCU_error_control_mode <= working_control_check3 )
			{    zxc[0] += 1;
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

				//p_control_policy_total_manager->working_error_count++;
				
				p_control_policy_total_manager->working_control_mode = working_control_fault_wait;
		    	p_control_policy_total_manager->fcu_updata_event_time = system_time;

			}
			else
			{   zxc[0] += 2;
				p_control_policy_total_manager->working_control_mode = working_control_fault1;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}

		}
	}

	return error_code;
}


//fcu���أ�����ͣ��1���㷨�����մ�����ֹͣfc�����ս������ͣ���׶�
enum Error_code Control_Policy_Total_Manager_for_fault1(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->working_control_mode == working_control_fault1)
	{
		//����ͣ��û��ʲô�����жϣ�����ͣ���ٶ�Ҫ�죬������ʱ���̣�ֻ�����豸����Ӧʱ�伴�ɡ�������Ҫ�ȵ��豸��Ӧ���ı�״̬��
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_1S)
		{   zxc[1] += 1;
			//�����жϵ����ˣ�����ͣ���󲿷ֶ��Ǵ��ؼ�ͣ�ģ�����ֱ��ֹͣ�ͺ���

			//�ر�ɢ��ϵͳ�ķ���pidʹ��
			fcu_data_buffer.water_for_pile_data_buffer.water_temperature_fan_pid1.is_enble_pid = 0;
			fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_fan_pid.is_enble_pid = 0;	

			//��������β�ţ�������
			fcu_data_buffer.h2_data_buffer.h2_is_enable_outlet_valve = 1;
			fcu_data_buffer.h2_data_buffer.h2_pid_mode = 2;
			fcu_data_buffer.h2_data_buffer.h2_pressure_advance_current_value = 0;

			p_control_policy_total_manager->working_control_mode = working_control_fault2;
			p_control_policy_total_manager->fcu_updata_event_time = system_time;

		}
	} 

	return error_code;
}




//fcu���أ�����ͣ��2���㷨�����մ�����ֹͣfc�����ս������ͣ���׶�
enum Error_code Control_Policy_Total_Manager_for_fault2(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->working_control_mode == working_control_fault2)
	{
		//����ͣ��û��ʲô�����жϣ�����ͣ���ٶ�Ҫ�죬������ʱ���̣�ֻ�����豸����Ӧʱ�伴�ɡ�������Ҫ�ȵ��豸��Ӧ���ı�״̬��
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_1S)
		{    zxc[2] += 1;
			//����pid1��pid2
			fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid1.Kp = PID1_KP;
			fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid1.Ki = PID1_KI;
			fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid1.Kd = PID1_KD;
			fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid2.Kp = PID2_KP;
			fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid2.Ki = PID2_KI;
			fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid2.Kd = PID2_KD;

			//�жϸ��أ��رյ������̵���
			fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_is_enble_output = 0;

			//45kw�·�������ǰ����С���踺�أ�
			fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_is_enble_load_resistance = 1;

			p_control_policy_total_manager->working_control_mode = working_control_fault3;
			p_control_policy_total_manager->fcu_updata_event_time = system_time;

		}
	}

	return error_code;
}



//fcu���أ�����ͣ��3���㷨�����մ�����ֹͣfc�����ս������ͣ���׶�
enum Error_code Control_Policy_Total_Manager_for_fault3(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->working_control_mode == working_control_fault3)
	{
		//����ͣ��û��ʲô�����жϣ�����ͣ���ٶ�Ҫ�죬������ʱ���̣�ֻ�����豸����Ӧʱ�伴�ɡ�������Ҫ�ȵ��豸��Ӧ���ı�״̬��
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_1S)
		{
			//��·���ϣ��������Ѿ�����������������£���ô��ֱ�ӹص�����������������ѹ��β����ѹ �Ĺ��ϲ��ܣ�
			if((p_control_policy_total_manager->working_FCU_error_code == H2_pressure_proportional_valve_front_over_error1 ||
			    p_control_policy_total_manager->working_FCU_error_code == H2_pressure_proportional_valve_front_under_error1 ||
			    p_control_policy_total_manager->working_FCU_error_code == H2_pressure_proportional_valve_front_atd_error1 ||
				p_control_policy_total_manager->working_FCU_error_code == H2_pressure_proportional_valve_rear_over_error1 ||
				p_control_policy_total_manager->working_FCU_error_code == H2_pressure_proportional_valve_rear_under_error1 ||
				p_control_policy_total_manager->working_FCU_error_code == H2_pressure_proportional_valve_rear_atd_error1 ||
				p_control_policy_total_manager->working_FCU_error_code == H2_pressure_proportional_valve_rear_unstable_error1 ||
				p_control_policy_total_manager->working_FCU_error_code == H2_pressure_no_fluctuations_error1 ||
				p_control_policy_total_manager->working_FCU_error_code == H2_pressure_pile_inlet_over_error1 ||
				p_control_policy_total_manager->working_FCU_error_code == H2_pressure_pile_inlet_under_error1 ||
				p_control_policy_total_manager->working_FCU_error_code == H2_pressure_pile_inlet_atd_error1 ||
				p_control_policy_total_manager->working_FCU_error_code == H2_pressure_pile_inlet_unstable_error1 ||
				p_control_policy_total_manager->working_FCU_error_code == H2_proportional_valve_statas_error1 ||
				p_control_policy_total_manager->working_FCU_error_code == H2_outlet_valve_control_error1 )
				&& p_control_policy_total_manager->working_FCU_error_control_mode >= working_control_start4 )
			{    zxc[3] += 1;
				//�ر�������ڷ����ж�������Դ
				fcu_data_buffer.h2_data_buffer.h2_inlet_valve = 0;

				//�ر�pid1��pid2���رձ�������pid2�� �رձ�����pwm��  
				fcu_data_buffer.h2_data_buffer.h2_pid_mode = 2;
				fcu_data_buffer.h2_data_buffer.h2_pressure_advance_set_value = 0;
				fcu_data_buffer.h2_data_buffer.h2_pressure_pid2_advance_time = 200;
				fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid2.is_enble_pid = 0;
				fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid1.is_enble_pid = 0;
				fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pwm_dutyfactor = 0;

				//����Ŀ����ѹ
				fcu_data_buffer.h2_data_buffer.h2_pressure_target_value = 50;
			}
			//�����ֻ����Ŀ����ѹ ��50kpa
			else
			{    zxc[3] += 2;
				//ע���ˣ���Ҫ������·��ʹ��                                                                         
				//����Ŀ����ѹ
				fcu_data_buffer.h2_data_buffer.h2_pressure_target_value = 50;                                 
			}


			//��ѹ�����Ϻ�����һɢ��ϵͳ���ϣ��������Ѿ�������ѹ��������£���ô��ֱ�ӹص���ѹ��
			if((p_control_policy_total_manager->working_FCU_error_code == Air_pressure_pile_inlet_over_error1 ||
				p_control_policy_total_manager->working_FCU_error_code == Air_pressure_pile_inlet_under_error1 ||
				p_control_policy_total_manager->working_FCU_error_code == Air_pressure_pile_inlet_atd_error1 ||
				p_control_policy_total_manager->working_FCU_error_code == Air_temperature_pile_inlet_over_error1 ||
				p_control_policy_total_manager->working_FCU_error_code == Air_temperature_pile_inlet_under_error1 ||
				p_control_policy_total_manager->working_FCU_error_code == Air_temperature_pile_inlet_atd_error1 ||
				p_control_policy_total_manager->working_FCU_error_code == Air_rate_of_flow_under_error1 ||
				p_control_policy_total_manager->working_FCU_error_code == Air_rate_of_flow_atd_error1 ||	
				p_control_policy_total_manager->working_FCU_error_code == Air_compressor_communication_error1 ||
				p_control_policy_total_manager->working_FCU_error_code == Air_compressor_working_statas_error1 ||
				p_control_policy_total_manager->working_FCU_error_code == Air_compressor_act_speed_error1 ||
				p_control_policy_total_manager->working_FCU_error_code == Air_compressor_temperature_over_error1 ||
				p_control_policy_total_manager->working_FCU_error_code == Air_compressor_temperature_under_error1 ||
				p_control_policy_total_manager->working_FCU_error_code == Water_temperature_compressor_outlet_over_error1 ||
				p_control_policy_total_manager->working_FCU_error_code == Water_temperature_compressor_outlet_under_error1 ||
				p_control_policy_total_manager->working_FCU_error_code == Water_temperature_pump_outlet_over_error1 ||
				p_control_policy_total_manager->working_FCU_error_code == Water_temperature_pump_outlet_under_error1)
				&& p_control_policy_total_manager->working_FCU_error_control_mode > working_control_start7 )
			{    zxc[3] += 10;               
				//ͬʱ�رտ�ѹ���Ϳ���β��
				fcu_data_buffer.air_data_buffer.air_compressor_enable = 0;
				fcu_data_buffer.air_data_buffer.air_is_enable_outlet_valve = 0;
				//���Ϳ�ѹ��ת�١�
				fcu_data_buffer.air_data_buffer.air_compressor_speed_pid.is_enble_pid = 0;
				fcu_data_buffer.air_data_buffer.air_rate_of_flow_target = 960;
				fcu_data_buffer.air_data_buffer.air_compressor_speed_setpoint = 20000;
			}
			//����һɢ��ϵͳ ˮѹ ���ϣ��������Ѿ�������ѹ��������£���ô��ֱ�ӹص���ѹ�������ҹص�����һ��ˮ�úͷ���
			else if(p_control_policy_total_manager->working_FCU_error_code == Water_pressure_compressor_outlet_under_error1
				&& p_control_policy_total_manager->working_FCU_error_control_mode >= working_control_start8 )
			{   zxc[3] += 20;            
				//ͬʱ�رտ�ѹ���Ϳ���β��
				fcu_data_buffer.air_data_buffer.air_compressor_enable = 0;
				fcu_data_buffer.air_data_buffer.air_is_enable_outlet_valve = 0;
				//���Ϳ�ѹ��ת�١�
				fcu_data_buffer.air_data_buffer.air_compressor_speed_pid.is_enble_pid = 0;
				fcu_data_buffer.air_data_buffer.air_rate_of_flow_target = 960;
				fcu_data_buffer.air_data_buffer.air_compressor_speed_setpoint = 20000;
				//�ص�����һ��ˮ�úͷ���
				fcu_data_buffer.water_for_compressor_data_bufferr.water_pump_pwm_dutyfactor = 0;
				fcu_data_buffer.water_for_compressor_data_bufferr.water_fan_pwm_dutyfactor = 0;
			}
			//�����ֻ���Ϳ�ѹ��ת�١�
			else
			{   zxc[3] += 30;
				//ע���ˣ���Ҫ������ѹ����ʹ��
				//���Ϳ�ѹ��ת�١�
				fcu_data_buffer.air_data_buffer.air_compressor_speed_pid.is_enble_pid = 0;
				fcu_data_buffer.air_data_buffer.air_rate_of_flow_target = 960;
				fcu_data_buffer.air_data_buffer.air_compressor_speed_setpoint = 20000;
			}

			p_control_policy_total_manager->working_control_mode = working_control_fault4;
			p_control_policy_total_manager->fcu_updata_event_time = system_time;
		}
	}

	return error_code;
}



//fcu���أ�����ͣ��4���㷨�����մ�����ֹͣfc�����ս������ͣ���׶�
enum Error_code Control_Policy_Total_Manager_for_fault4(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->working_control_mode == working_control_fault4)
	{
		//����ͣ��û��ʲô�����жϣ�����ͣ���ٶ�Ҫ�죬������ʱ���̣�ֻ�����豸����Ӧʱ�伴�ɡ�������Ҫ�ȵ��豸��Ӧ���ı�״̬��
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_1S)
		{
			//���fault3��·���ϣ��ǾͲ��ô�ɨ��
			if(fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid2.is_enble_pid == 0)
			{    zxc[4] += 1;
				//fault3�Ѿ�����·����
				fcu_data_buffer.h2_data_buffer.h2_outlet_valve_open_time = 500;
				fcu_data_buffer.h2_data_buffer.h2_outlet_valve_close_time = 1000;
				fcu_data_buffer.h2_data_buffer.h2_is_enable_outlet_valve = 0;
			}
			//����ͽ�����·��ɨ
			else 
			{    zxc[4] += 2;
				//�ر�pid1������pid2��Ȼ����봵ɨģʽ
				fcu_data_buffer.h2_data_buffer.h2_pid_mode = 2;
				fcu_data_buffer.h2_data_buffer.h2_pressure_advance_set_value = 0;
				fcu_data_buffer.h2_data_buffer.h2_pressure_pid2_advance_time = 200;

				fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid2.Kp = PID2_KP;
				fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid2.Ki = PID2_KI;
				fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid2.Kd = PID2_KD;
				//		fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pwm_dutyfactor = 0;
				fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid2.is_enble_pid = 1;
				fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid1.is_enble_pid = 0;

				//Ȼ����봵ɨģʽ������ѭ���ü�����ת
				//����β���ɳ�������Ϊ��ɨģʽ��1s/0.5s
				fcu_data_buffer.h2_data_buffer.h2_outlet_valve_open_time = 500;
				fcu_data_buffer.h2_data_buffer.h2_outlet_valve_close_time = 1000;
				fcu_data_buffer.h2_data_buffer.h2_is_enable_outlet_valve = 2;
			}

			//���fault3��ѹ�����Ϻ�����һɢ��ϵͳ���ϣ��ǾͲ��ô�ɨ��
			if(fcu_data_buffer.air_data_buffer.air_compressor_enable == 0)
			{   zxc[4] += 10;
				fcu_data_buffer.air_data_buffer.air_outlet_valve_open_time = 500;
				fcu_data_buffer.air_data_buffer.air_outlet_valve_close_time = 2000;
				fcu_data_buffer.air_data_buffer.air_is_enable_outlet_valve = 0;
			}
			else
			{    zxc[4] += 20;
				//��������β�ţ���Ϊ��ɨģʽ��2s/0.5s
				fcu_data_buffer.air_data_buffer.air_outlet_valve_open_time = 500;
				fcu_data_buffer.air_data_buffer.air_outlet_valve_close_time = 2000;
				fcu_data_buffer.air_data_buffer.air_is_enable_outlet_valve = 2;
			}

			//�������ѭ���ù��ϣ��������Ѿ���������ѭ���õ�����£���ô����͹ص�����ѭ����
			if((p_control_policy_total_manager->working_FCU_error_code == H2_circulating_pump_communication_error1 ||
				p_control_policy_total_manager->working_FCU_error_code == H2_circulating_pump_low_voltage_power_error1 ||
				p_control_policy_total_manager->working_FCU_error_code == H2_circulating_pump_working_statas_error1 ||
				p_control_policy_total_manager->working_FCU_error_code == H2_circulating_pump_actual_speed_error1 ||
				p_control_policy_total_manager->working_FCU_error_code == H2_circulating_pump_temperature_over_error1 ||
				p_control_policy_total_manager->working_FCU_error_code == H2_circulating_pump_temperature_under_error1 )
				&& p_control_policy_total_manager->working_FCU_error_control_mode >= working_control_start5 )
			{    zxc[4] += 100;
				//�ص�����ѭ����
				fcu_data_buffer.h2_data_buffer.h2_circulating_pump_enable_pump = 0;
			}
			else
			{    zxc[4] += 200;
				//����ѭ�����ڽϴ��ת�������У�Ҫ��ѭ���������ˮ��ɨ������
				fcu_data_buffer.h2_data_buffer.h2_circulating_pump_speed_setpoint = H2_CIRCULATING_PUMP_SPEED_SETPOINT_3000;
			}

			p_control_policy_total_manager->working_control_mode = working_control_fault5;
			p_control_policy_total_manager->fcu_updata_event_time = system_time;
		}
	}

	return error_code;
}


//fcu���أ�����ͣ��5���㷨�����մ�����ֹͣfc�����ս������ͣ���׶�
enum Error_code Control_Policy_Total_Manager_for_fault5(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->working_control_mode == working_control_fault5)
	{
		//����ͣ��û��ʲô�����жϣ�����ͣ���ٶ�Ҫ�죬������ʱ���̣�ֻ�����豸����Ӧʱ�伴�ɡ�������Ҫ�ȵ��豸��Ӧ���ı�״̬��
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_1S)
		{
			//������ɢ��ϵͳ ˮѹ���ϣ���ˮ�ÿ���������£��Ǿ�ˮ�úͷ���ֱ�ӹص�����ֻ�ж�ˮѹ��ˮ���������жϣ�
			if((p_control_policy_total_manager->working_FCU_error_code == Water_pressure_pile_inlet_over_error1 ||
				p_control_policy_total_manager->working_FCU_error_code == Water_pressure_pile_inlet_under_error1 ||
				p_control_policy_total_manager->working_FCU_error_code == Water_pressure_pile_outlet_over_error1 ||
				p_control_policy_total_manager->working_FCU_error_code == Water_pressure_pile_outlet_under_error1 ||
				p_control_policy_total_manager->working_FCU_error_code == Water_pressure_differential_pile_inlet_and_outlet_over_error1 ||
				p_control_policy_total_manager->working_FCU_error_code == Water_pressure_differential_pile_inlet_and_outlet_under_error1)
				&& p_control_policy_total_manager->working_FCU_error_control_mode >= working_control_start2 )
			{   zxc[5] += 1;
				fcu_data_buffer.water_for_pile_data_buffer.water_pump_pwm_dutyfactor1 = 0;
				fcu_data_buffer.water_for_pile_data_buffer.water_pump_pwm_dutyfactor2 = 0;
				fcu_data_buffer.water_for_pile_data_buffer.water_fan_pwm_dutyfactor1 = 0;
				fcu_data_buffer.water_for_pile_data_buffer.water_fan_pwm_dutyfactor2 = 0;
			}
			//�����ˮ�úͷ���ȫ�����ӿ�ɢ�ȡ�
			else
			{
				//������ˮ��    ��ѳ���ˮ��    
				if(fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_inlet1 > 45 || 
					fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_outlet1 > 45 )
				{    zxc[5] += 2;
					//ˮ�úͷ���ȫ�����ӿ�ɢ�ȡ�
					fcu_data_buffer.water_for_pile_data_buffer.water_pump_pwm_dutyfactor1 = 9000;
					fcu_data_buffer.water_for_pile_data_buffer.water_fan_pwm_dutyfactor1 = 9000;
					fcu_data_buffer.water_for_pile_data_buffer.water_fan_pwm_dutyfactor2 = 9000;
				}
			}


			//������ɢ��ϵͳ ˮѹ���ϣ���ˮ�ÿ���������£��Ǿ�ˮ�úͷ���ֱ�ӹص�����ֻ�ж�ˮѹ��ˮ���������жϣ�
			if(p_control_policy_total_manager->working_FCU_error_code == Water_pressure_compressor_outlet_under_error1
				&& p_control_policy_total_manager->working_FCU_error_control_mode >= working_control_start2 )
			{     zxc[5] += 10;
				fcu_data_buffer.water_for_compressor_data_bufferr.water_pump_pwm_dutyfactor = 0;
				fcu_data_buffer.water_for_compressor_data_bufferr.water_fan_pwm_dutyfactor = 0;
			}
			//�����ˮ�úͷ���ȫ�����ӿ�ɢ�ȡ�
			else
			{
				//��ѹ������ˮ��    ����һˮ�ó���ˮ��
				if(fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_compressor_outlet > 45 ||
					fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_pump_outlet > 45)
				{   zxc[5] += 20;
					//ˮ�úͷ���ȫ�����ӿ�ɢ�ȡ�
					fcu_data_buffer.water_for_compressor_data_bufferr.water_pump_pwm_dutyfactor = 9000;
					fcu_data_buffer.water_for_compressor_data_bufferr.water_fan_pwm_dutyfactor = 9000;
				}
			}


			p_control_policy_total_manager->working_control_mode = working_control_fault6;
			p_control_policy_total_manager->fcu_updata_event_time = system_time;
		}
	}

	return error_code;
}


//fcu���أ�����ͣ��6���㷨�����մ�����ֹͣfc�����ս������ͣ���׶�
enum Error_code Control_Policy_Total_Manager_for_fault6(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->working_control_mode == working_control_fault6)
	{
		//����ͣ��û��ʲô�����жϣ�����ͣ���ٶ�Ҫ�죬������ʱ���̣�ֻ�����豸����Ӧʱ�伴�ɡ�������Ҫ�ȵ��豸��Ӧ���ı�״̬��

		//���ǰ���ж���Ҫ��ɨ����ô������ʱ20s���ȴ���·�Ϳ�·��ɨ��              �����ֱ��1s��
		if(fcu_data_buffer.h2_data_buffer.h2_is_enable_outlet_valve == 2  ||
			fcu_data_buffer.air_data_buffer.air_is_enable_outlet_valve == 2)
		{
			if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_20S)
			{     zxc[6] += 1;
				//�ر�����ѭ���ã�����ǰ���Ƿ���ǰ�رգ������ٹ�һ�Σ�
				fcu_data_buffer.h2_data_buffer.h2_circulating_pump_speed_setpoint = H2_CIRCULATING_PUMP_SPEED_SETPOINT_3000;
				fcu_data_buffer.h2_data_buffer.h2_circulating_pump_enble = 1;
				fcu_data_buffer.h2_data_buffer.h2_circulating_pump_enable_pump = 0;

				p_control_policy_total_manager->working_control_mode = working_control_fault7;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
		}
		else
		{
			if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_1S)
			{    zxc[6] += 2;
				//�ر�����ѭ���ã�����ǰ���Ƿ���ǰ�رգ������ٹ�һ�Σ�
				fcu_data_buffer.h2_data_buffer.h2_circulating_pump_speed_setpoint = H2_CIRCULATING_PUMP_SPEED_SETPOINT_3000;
				fcu_data_buffer.h2_data_buffer.h2_circulating_pump_enble = 1;
				fcu_data_buffer.h2_data_buffer.h2_circulating_pump_enable_pump = 0;

				p_control_policy_total_manager->working_control_mode = working_control_fault7;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
		}



	}

	return error_code;
}


//fcu���أ�����ͣ��7���㷨�����մ�����ֹͣfc�����ս������ͣ���׶�
enum Error_code Control_Policy_Total_Manager_for_fault7(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->working_control_mode == working_control_fault7)
	{
		//����ͣ��û��ʲô�����жϣ�����ͣ���ٶ�Ҫ�죬������ʱ���̣�ֻ�����豸����Ӧʱ�伴�ɡ�������Ҫ�ȵ��豸��Ӧ���ı�״̬��
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_1S)
		{   zxc[7] += 1;
			//�ر�������ڷ����ж�������Դ������ǰ���Ƿ���ǰ�رգ������ٹ�һ�Σ�
			fcu_data_buffer.h2_data_buffer.h2_inlet_valve = 0;

			//20181218���ﳣ������β�ŷ������ٽ������ų���
			//���˸о�����֮ǰ��1/0.5s�Ĵ�ɨģʽ��������ر�������ڷ����ж�������Դ֮�󣬴�ɨ�䲻�����ˡ�
			//Ŀ�������ų����������ֱ�ӳ�������β�ŷ������ٽ������ų���
			fcu_data_buffer.h2_data_buffer.h2_is_enable_outlet_valve = 1;
				
			//ͬʱ�رտ�ѹ���Ϳ���β�ţ�����ǰ���Ƿ���ǰ�رգ������ٹ�һ�Σ�
			fcu_data_buffer.air_data_buffer.air_compressor_enable = 0;
			fcu_data_buffer.air_data_buffer.air_is_enable_outlet_valve = 0;

			p_control_policy_total_manager->working_control_mode = working_control_fault8;
			p_control_policy_total_manager->fcu_updata_event_time = system_time;
		}
	}

	return error_code;
}



//fcu���أ�����ͣ��8���㷨�����մ�����ֹͣfc�����ս������ͣ���׶�
enum Error_code Control_Policy_Total_Manager_for_fault8(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->working_control_mode == working_control_fault8)
	{
		//���ǰ���ж���Ҫ��ɨ����ô������ʱ5s���ȴ���ѹ��������    �����ֱ��1s��
		if(fcu_data_buffer.h2_data_buffer.h2_is_enable_outlet_valve == 2 )
		{
			//����ͣ��û��ʲô�����жϣ�����ͣ���ٶ�Ҫ�죬������ʱ���̣�ֻ�����豸����Ӧʱ�伴�ɡ�������Ҫ�ȵ��豸��Ӧ���ı�״̬��
			if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_5S)
			{    zxc[8] += 1;
				//�رձ�������pid2�� �رձ�����pwm��    ������ǰ���Ƿ���ǰ�رգ������ٹ�һ�Σ�
				fcu_data_buffer.h2_data_buffer.h2_pid_mode = 2;
				fcu_data_buffer.h2_data_buffer.h2_pressure_advance_set_value = 0;
				fcu_data_buffer.h2_data_buffer.h2_pressure_pid2_advance_time = 200;
				fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid2.is_enble_pid = 0;
				fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pwm_dutyfactor = 0;
			
				//�ر�����β�ţ�����ǰ���Ƿ���ǰ�رգ������ٹ�һ�Σ�
				//ע���ˣ������·���ϣ���ô����β�ų�����������ѡ�
				if((p_control_policy_total_manager->working_FCU_error_code == H2_pressure_proportional_valve_front_over_error1 ||
    			    p_control_policy_total_manager->working_FCU_error_code == H2_pressure_proportional_valve_front_under_error1 ||
    			    p_control_policy_total_manager->working_FCU_error_code == H2_pressure_proportional_valve_front_atd_error1 ||
    				p_control_policy_total_manager->working_FCU_error_code == H2_pressure_proportional_valve_rear_over_error1 ||
    				p_control_policy_total_manager->working_FCU_error_code == H2_pressure_proportional_valve_rear_under_error1 ||
    				p_control_policy_total_manager->working_FCU_error_code == H2_pressure_proportional_valve_rear_atd_error1 ||
    				p_control_policy_total_manager->working_FCU_error_code == H2_pressure_proportional_valve_rear_unstable_error1 ||
    				p_control_policy_total_manager->working_FCU_error_code == H2_pressure_no_fluctuations_error1 ||
    				p_control_policy_total_manager->working_FCU_error_code == H2_pressure_pile_inlet_over_error1 ||
    				p_control_policy_total_manager->working_FCU_error_code == H2_pressure_pile_inlet_under_error1 ||
    				p_control_policy_total_manager->working_FCU_error_code == H2_pressure_pile_inlet_atd_error1 ||
    				p_control_policy_total_manager->working_FCU_error_code == H2_pressure_pile_inlet_unstable_error1 ||
    				p_control_policy_total_manager->working_FCU_error_code == H2_proportional_valve_statas_error1 ||
    				p_control_policy_total_manager->working_FCU_error_code == H2_outlet_valve_control_error1 )
    				&& p_control_policy_total_manager->working_FCU_error_control_mode >= working_control_start4 )
		    	{  
			    	fcu_data_buffer.h2_data_buffer.h2_is_enable_outlet_valve = 1;
		    	}
		    	else
		    	{
		         	fcu_data_buffer.h2_data_buffer.h2_is_enable_outlet_valve = 0;
		    	}

				p_control_policy_total_manager->working_control_mode = working_control_fault9;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
		}
		else
		{
			//����ͣ��û��ʲô�����жϣ�����ͣ���ٶ�Ҫ�죬������ʱ���̣�ֻ�����豸����Ӧʱ�伴�ɡ�������Ҫ�ȵ��豸��Ӧ���ı�״̬��
			if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_1S)
			{    zxc[8] += 2;
				//�رձ�������pid2�� �رձ�����pwm��    ������ǰ���Ƿ���ǰ�رգ������ٹ�һ�Σ�
				fcu_data_buffer.h2_data_buffer.h2_pid_mode = 2;
				fcu_data_buffer.h2_data_buffer.h2_pressure_advance_set_value = 0;
				fcu_data_buffer.h2_data_buffer.h2_pressure_pid2_advance_time = 200;
				fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid2.is_enble_pid = 0;
				fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pwm_dutyfactor = 0;
			
				//�ر�����β�ţ�����ǰ���Ƿ���ǰ�رգ������ٹ�һ�Σ�
				//ע���ˣ������·���ϣ���ô����β�ų�����������ѡ�
				if((p_control_policy_total_manager->working_FCU_error_code == H2_pressure_proportional_valve_front_over_error1 ||
			    p_control_policy_total_manager->working_FCU_error_code == H2_pressure_proportional_valve_front_under_error1 ||
			    p_control_policy_total_manager->working_FCU_error_code == H2_pressure_proportional_valve_front_atd_error1 ||
				p_control_policy_total_manager->working_FCU_error_code == H2_pressure_proportional_valve_rear_over_error1 ||
				p_control_policy_total_manager->working_FCU_error_code == H2_pressure_proportional_valve_rear_under_error1 ||
				p_control_policy_total_manager->working_FCU_error_code == H2_pressure_proportional_valve_rear_atd_error1 ||
				p_control_policy_total_manager->working_FCU_error_code == H2_pressure_proportional_valve_rear_unstable_error1 ||
				p_control_policy_total_manager->working_FCU_error_code == H2_pressure_no_fluctuations_error1 ||
				p_control_policy_total_manager->working_FCU_error_code == H2_pressure_pile_inlet_over_error1 ||
				p_control_policy_total_manager->working_FCU_error_code == H2_pressure_pile_inlet_under_error1 ||
				p_control_policy_total_manager->working_FCU_error_code == H2_pressure_pile_inlet_atd_error1 ||
				p_control_policy_total_manager->working_FCU_error_code == H2_pressure_pile_inlet_unstable_error1 ||
				p_control_policy_total_manager->working_FCU_error_code == H2_proportional_valve_statas_error1 ||
				p_control_policy_total_manager->working_FCU_error_code == H2_outlet_valve_control_error1 )
				&& p_control_policy_total_manager->working_FCU_error_control_mode >= working_control_start4 )
		    	{  
			    	fcu_data_buffer.h2_data_buffer.h2_is_enable_outlet_valve = 1;
		    	}
		    	else
		    	{
		         	fcu_data_buffer.h2_data_buffer.h2_is_enable_outlet_valve = 0;
		    	}
			

				p_control_policy_total_manager->working_control_mode = working_control_fault9;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
		}
	}

	return error_code;
}


//fcu���أ�����ͣ��9���㷨�����մ�����ֹͣfc�����ս������ͣ���׶�
enum Error_code Control_Policy_Total_Manager_for_fault9(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->working_control_mode == working_control_fault9)
	{
		//����ͣ��û��ʲô�����жϣ�����ͣ���ٶ�Ҫ�죬������ʱ���̣�ֻ�����豸����Ӧʱ�伴�ɡ�������Ҫ�ȵ��豸��Ӧ���ı�״̬��
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_1S)
		{
			//ֻ���ڵ�ѹ����52��ʱ�򣬾ʹ򿪸���С���裬����Ϊ�п��ܻ�û������͹����ˡ���
			if(fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_voltage > 52)
			{      zxc[9] += 1;
				//�򿪸���С���� 
				fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_is_enble_load_resistance = 1;
			}
			p_control_policy_total_manager->working_control_mode = working_control_fault10;
			p_control_policy_total_manager->fcu_updata_event_time = system_time;
		}
	}

	return error_code;
}


//fcu���أ�����ͣ��10���㷨�����մ�����ֹͣfc�����ս������ͣ���׶�
enum Error_code Control_Policy_Total_Manager_for_fault10(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->working_control_mode == working_control_fault10)
	{
		//���������С���������͵�ѹ����ô�ͳ�ʱ70s��  �����ֱ��1s��
		if(fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_is_enble_load_resistance == 1)
		{
			//��ʱ�㷨��70s�ڣ��жϵ�ѹ�Ƿ�С��16V
			//����ͣ��û��ʲô�����жϣ�����ͣ���ٶ�Ҫ�죬������ʱ���̣�ֻ�����豸����Ӧʱ�伴�ɡ�������Ҫ�ȵ��豸��Ӧ���ı�״̬��
			if(system_time - p_control_policy_total_manager->fcu_updata_event_time < FCU_SYSTEM_CHANGE_MODE_DELAY_70S)
			{   
				//�жϵ�ѹ�Ƿ�С��16V
				if(fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_voltage < 39)
				{    zxc[10] += 20;
					//�жϸ���С����
					fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_is_enble_load_resistance = 0;

					p_control_policy_total_manager->working_control_mode = working_control_fault11;
					p_control_policy_total_manager->fcu_updata_event_time = system_time;
				}
				//��������ȴ���
			}
			else
			{    zxc[10] += 30;
				//�жϸ���С����
				fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_is_enble_load_resistance = 0;

				p_control_policy_total_manager->working_control_mode = working_control_fault11;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
		}
		else
		{
			if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_1S)
			{   zxc[10] += 40;
				p_control_policy_total_manager->working_control_mode = working_control_fault11;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
		}

	}

	return error_code;
}


//fcu���أ�����ͣ��11���㷨�����մ�����ֹͣfc�����ս������ͣ���׶�
enum Error_code Control_Policy_Total_Manager_for_fault11(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->working_control_mode == working_control_fault11)
	{
		//35V~50V֮�䣬���ʾ����������С���裬��ô����10s�ĳ�ʱ�жϣ�    ����ֱ��1s��
		if(fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_voltage > 35 
			&& fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_voltage < 50  )
		{
			//����ͣ��û��ʲô�����жϣ�����ͣ���ٶ�Ҫ�죬������ʱ���̣�ֻ�����豸����Ӧʱ�伴�ɡ�������Ҫ�ȵ��豸��Ӧ���ı�״̬��
			//��ʱ�жϣ���10s�ڣ��жϵ�ѹ�Ƿ񷴵�������32V
			if(system_time - p_control_policy_total_manager->fcu_updata_event_time < FCU_SYSTEM_CHANGE_MODE_DELAY_10S)
			{   
				//�жϵ�ѹ�Ƿ񷴵�
				if(fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_voltage > 52
					&& p_control_policy_total_manager->galvanic_pile_load_resistance_switch_count < 3)
				{     zxc[11] += 20;
					//ע���ˣ������stop11���˵�stop10�����´�С���裬���н���ѹ��

					//�򿪸���С���� 
					fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_is_enble_load_resistance = 1;

					//С���ص��л�����  +1
					p_control_policy_total_manager->galvanic_pile_load_resistance_switch_count++;

					//�л���ֹͣ10״̬��������״̬��ֹͣ��	����״̬��ֹͣ��	���ϵȼ���������
					p_control_policy_total_manager->working_control_mode = working_control_fault10;
					p_control_policy_total_manager->fcu_updata_event_time = system_time;
				}
				//��������ȴ���
			}
			else
			{     zxc[11] += 30;
				//С���ص��л�����  ���
				p_control_policy_total_manager->galvanic_pile_load_resistance_switch_count = 0;
				//�л���ֹͣ12״̬��������״̬��ֹͣ��	����״̬��ֹͣ��	���ϵȼ���������
				p_control_policy_total_manager->working_control_mode = working_control_fault12;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
		}
		//������ǽ���ѹ�������ˡ��Ǿ�ֱ�ӹ�
		else
		{
			if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_1S)
			{     zxc[11] += 40;
				//С���ص��л�����  ���
				p_control_policy_total_manager->galvanic_pile_load_resistance_switch_count = 0;
				//�л���ֹͣ12״̬��������״̬��ֹͣ��	����״̬��ֹͣ��	���ϵȼ���������
				p_control_policy_total_manager->working_control_mode = working_control_fault12;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
		}

	}

	return error_code;
}


//fcu���أ�����ͣ��12���㷨�����մ�����ֹͣfc�����ս������ͣ���׶�
enum Error_code Control_Policy_Total_Manager_for_fault12(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->working_control_mode == working_control_fault12)
	{

		//��ʱ�жϣ���60s�ڣ��ж�ɢ��ϵͳ���¶� �Ƿ񽵵�45��
		//����ͣ��û��ʲô�����жϣ�����ͣ���ٶ�Ҫ�죬������ʱ���̣�ֻ�����豸����Ӧʱ�伴�ɡ�������Ҫ�ȵ��豸��Ӧ���ı�״̬��
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time < FCU_SYSTEM_CHANGE_MODE_DELAY_100S)
		{
			//ע���ˣ�������ֻ��һ����Ҳ����˵��������һ��ɢ��ϵͳ�Ǻõġ���ô����Ҫ����  ��ʱ60s���ж�
			if(p_control_policy_total_manager->working_FCU_error_code == Water_pressure_pile_inlet_over_error1 ||
				p_control_policy_total_manager->working_FCU_error_code == Water_pressure_pile_inlet_under_error1 ||
				p_control_policy_total_manager->working_FCU_error_code == Water_pressure_pile_outlet_over_error1 ||
				p_control_policy_total_manager->working_FCU_error_code == Water_pressure_pile_outlet_under_error1 ||
				p_control_policy_total_manager->working_FCU_error_code == Water_pressure_differential_pile_inlet_and_outlet_over_error1 ||
				p_control_policy_total_manager->working_FCU_error_code == Water_pressure_differential_pile_inlet_and_outlet_under_error1 ||
				p_control_policy_total_manager->working_FCU_error_code == Water_temperature_pile_inlet_over_error1 ||
				p_control_policy_total_manager->working_FCU_error_code == Water_temperature_pile_inlet_under_error1 ||
				p_control_policy_total_manager->working_FCU_error_code == Water_temperature_pile_outlet_over_error1 ||
				p_control_policy_total_manager->working_FCU_error_code == Water_temperature_pile_outlet_under_error1 ||
				p_control_policy_total_manager->working_FCU_error_code == Water_temperature_differential_pile_inlet_and_outlet_over_error1 ||
				p_control_policy_total_manager->working_FCU_error_code == Water_temperature_differential_pile_inlet_and_outlet_under_error1)
			{     
				//�����ѵ�ɢ��ϵͳ�����⣬�Ǿ�ֻ�ж�����һ��ɢ��ϵͳ
				if(fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_compressor_outlet <= 45 &&
					fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_pump_outlet <= 45)
				{    zxc[12] += 20;
					//�رշ��Ⱥ�ˮ��
					//ˮ�µ�pid����fault1���Ѿ�����
	    			fcu_data_buffer.water_for_pile_data_buffer.water_pump_pwm_dutyfactor1 = 0;
	    			fcu_data_buffer.water_for_pile_data_buffer.water_fan_pwm_dutyfactor1 = 0;
	    			fcu_data_buffer.water_for_pile_data_buffer.water_fan_pwm_dutyfactor2 = 0;
	    			fcu_data_buffer.water_for_compressor_data_bufferr.water_pump_pwm_dutyfactor = 0;
	    			fcu_data_buffer.water_for_compressor_data_bufferr.water_fan_pwm_dutyfactor = 0;

					//�л�������״̬��������״̬��ֹͣ��	����״̬��ֹͣ��	���ϵȼ���������
					p_control_policy_total_manager->working_control_mode = working_control_fault_wait;
					p_control_policy_total_manager->fcu_updata_event_time = system_time;
				}
				//��������ȴ���
			}
			else if(p_control_policy_total_manager->working_FCU_error_code == Water_temperature_compressor_outlet_over_error1 ||
				p_control_policy_total_manager->working_FCU_error_code == Water_temperature_compressor_outlet_under_error1 ||
				p_control_policy_total_manager->working_FCU_error_code == Water_temperature_pump_outlet_over_error1 ||
				p_control_policy_total_manager->working_FCU_error_code == Water_temperature_pump_outlet_under_error1 ||
				p_control_policy_total_manager->working_FCU_error_code == Water_pressure_compressor_outlet_under_error1)
			{     
				//�������һ��ɢ��ϵͳ�����⣬�Ǿ�ֻ�жϵ�ѵ�ɢ��ϵͳ
				//������ˮ��    ��ѳ���ˮ��    ��ѹ������ˮ��    ����һˮ�ó���ˮ��
				if(fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_inlet1 <= 45 && 
					fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_outlet1 <= 45 )
				{   zxc[12] += 40;
					//�رշ��Ⱥ�ˮ��
					//ˮ�µ�pid����fault1���Ѿ�����
	    			fcu_data_buffer.water_for_pile_data_buffer.water_pump_pwm_dutyfactor1 = 0;
	    			fcu_data_buffer.water_for_pile_data_buffer.water_fan_pwm_dutyfactor1 = 0;
	    			fcu_data_buffer.water_for_pile_data_buffer.water_fan_pwm_dutyfactor2 = 0;
	    			fcu_data_buffer.water_for_compressor_data_bufferr.water_pump_pwm_dutyfactor = 0;
	    			fcu_data_buffer.water_for_compressor_data_bufferr.water_fan_pwm_dutyfactor = 0;

					//�л�������״̬��������״̬��ֹͣ��	����״̬��ֹͣ��	���ϵȼ���������
					p_control_policy_total_manager->working_control_mode = working_control_fault_wait;
					p_control_policy_total_manager->fcu_updata_event_time = system_time;
				}
				//��������ȴ���
			}
			//���2��ɢ��ϵͳ��û�����⣬�Ǿ�Ҫ�ж�ȫ����
			else
			{
				//������ˮ��    ��ѳ���ˮ��    ��ѹ������ˮ��    ����һˮ�ó���ˮ��
				if(fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_inlet1 <= 45 && 
					fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_outlet1 <= 45 &&
					fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_compressor_outlet <= 45 &&
					fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_pump_outlet <= 45)
				{     zxc[12] += 5;
					//�رշ��Ⱥ�ˮ��
					//need programe  ˮ�µ�pid
					fcu_data_buffer.water_for_pile_data_buffer.water_pump_pwm_dutyfactor1 = 0;
	    		fcu_data_buffer.water_for_pile_data_buffer.water_fan_pwm_dutyfactor1 = 0;
	    		fcu_data_buffer.water_for_pile_data_buffer.water_fan_pwm_dutyfactor2 = 0;
	    	  fcu_data_buffer.water_for_compressor_data_bufferr.water_pump_pwm_dutyfactor = 0;
	    		fcu_data_buffer.water_for_compressor_data_bufferr.water_fan_pwm_dutyfactor = 0;

					//�л�������״̬��������״̬��ֹͣ��	����״̬��ֹͣ��	���ϵȼ���������
					p_control_policy_total_manager->working_control_mode = working_control_fault_wait;
					p_control_policy_total_manager->fcu_updata_event_time = system_time;
				}
				//��������ȴ���
			}
		}
		else                                                                      
		{     zxc[12] += 60;
			//�رշ��Ⱥ�ˮ��
			//need programe  ˮ�µ�pid
			fcu_data_buffer.water_for_pile_data_buffer.water_pump_pwm_dutyfactor1 = 0;
	  	fcu_data_buffer.water_for_pile_data_buffer.water_fan_pwm_dutyfactor1 = 0;
	  	fcu_data_buffer.water_for_pile_data_buffer.water_fan_pwm_dutyfactor2 = 0;
	    fcu_data_buffer.water_for_compressor_data_bufferr.water_pump_pwm_dutyfactor = 0;
	    fcu_data_buffer.water_for_compressor_data_bufferr.water_fan_pwm_dutyfactor = 0;

			//�л�������״̬��������״̬��ֹͣ��	����״̬��ֹͣ��	���ϵȼ���������
			p_control_policy_total_manager->working_control_mode = working_control_fault_wait;
			p_control_policy_total_manager->fcu_updata_event_time = system_time;

		}
	}

	return error_code;
}


//fcu���أ�//����ͣ���ĵȴ�״̬����λ��Ϣ���ɻָ���wait
enum Error_code Control_Policy_Total_Manager_for_fault_wait(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->working_control_mode == working_control_fault_wait)
	{
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_100MS)
		{
			//�յ���λ���Ҫ��  ��ͣΪ0����λΪ1
			if(fcu_data_buffer.galvanic_pile_data_buffer.fcu_reset_enable == 1 &&
			    fcu_data_buffer.galvanic_pile_data_buffer.fcu_stutter_stop_enable == 0)
			{    zxc[13] += 1;
				fcu_data_buffer.galvanic_pile_data_buffer.fcu_reset_enable = 0;
				fcu_data_buffer.galvanic_pile_data_buffer.fcu_start_enable = 0;

				//���������λ����  ����ͣ���ĵȴ�״̬  ����  �Լ�3�׶�
				p_control_policy_total_manager->working_control_mode = working_control_wait;
				p_control_policy_total_manager->working_status_mode = working_status_wait;
				p_control_policy_total_manager->working_alarm_mode = working_normal;
				p_control_policy_total_manager->working_FCU_error_code = Succeed;
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_wait;
				p_control_policy_total_manager->working_error_count = 0;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			//���򣬾�һֱ�ȴ���������
		}
	}

	return error_code;
}			







//�ж�2��ֵ�Ƿ�Լ���ڣ������10%�򷵻�Succeed�����򷵻�Failed
enum Error_code approximate(float value1, float value2)
{

	if(value1/value2 > 1-ERROR_TOLERANT_RATE  &&  value1/value2 < 1+ERROR_TOLERANT_RATE )	
	{
		return Succeed;
	}
	else
	{
		return Failed;
	}

}		

//�ж�2��ֵ�Ƿ�Լ���ڣ������10%�򷵻�Succeed�����򷵻�Failed
enum Error_code approximate2(float value1, float value2)
{

	if(value1/value2 > 1-ERROR_TOLERANT_RATE  &&  value1/value2 < 1+ERROR_TOLERANT_RATE2 )	
	{
		return Succeed;
	}
	else
	{
		return Failed;
	}

}		


//�������ȼ����ɸ澯�ȼ�������
enum Error_code merge_alarm_mode(enum Working_Alarm_Mode * p_working_alarm_mode_source, enum Working_Alarm_Mode * p_working_alarm_mode_new)
{
	enum Error_code error_code = Succeed;

	if(p_working_alarm_mode_source == NULL || p_working_alarm_mode_new == NULL)
	{return Pointer_is_null;}

	if(* p_working_alarm_mode_new != working_normal)
	{
		if(* p_working_alarm_mode_source == working_normal || * p_working_alarm_mode_source > * p_working_alarm_mode_new)
		{
			* p_working_alarm_mode_source = * p_working_alarm_mode_new;
		}
	}

	return error_code;
}









