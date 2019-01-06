
#include "control_manager.h"             


struct Control_Policy_Total_Manager   control_policy_total_manager;
u8 zxc[20] = {0};


//pcu主控的管理初始化
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
	
	//临时加的一级故障判断的延时  3秒
	p_control_policy_total_manager->one_level_fault_flag_temp = 0; //一级告警标记位，0正常，1出现一级告警
	p_control_policy_total_manager->one_level_fault_time_temp = 0; //一级告警标记时间。就是出现一级告警的时间。	

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



//fcu主控的管理更新数据（通过rs232调试接口）
enum Error_code Control_Policy_Total_Manager_updata_by_manual(struct Control_Policy_Total_Manager  * p_control_policy_total_manager, float * rs232_test)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL || rs232_test == NULL)
	{return Pointer_is_null;}

	return error_code;
}		


//fcu主控的管理更新数据（自动控制）
enum Error_code Control_Policy_Total_Manager_updata_by_Automatic (struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}


	return error_code;
}	



//fcu主控的管理更新数据（通过can和modbus通信接口）
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



//FCU稳定运行时，自动调档
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






//运行时的保护检验，通用型，
enum Error_code FCU_run_protect_check_common(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	//判断每个模块的数据是否正常。
	//注意了，这里全部都是if，就是说都要进行判断的，然后根据告警等级进行覆盖，最终只有一个错误码。

	//氢气回路
	//判断比例阀前氢压
	if(fcu_data_buffer.h2_data_buffer.h2_pressure_proportional_valve_front < 200 && 
		p_control_policy_total_manager->working_alarm_mode > one_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_fault0;
		p_control_policy_total_manager->working_status_mode = working_status_error;
		p_control_policy_total_manager->working_alarm_mode = one_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = H2_pressure_proportional_valve_front_under_error1;//比例阀前氢压	欠压（一级故障）
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
		p_control_policy_total_manager->working_FCU_error_code = H2_pressure_proportional_valve_front_under_error3;//比例阀前氢压	欠压（3级故障）
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
	if(fcu_data_buffer.h2_data_buffer.h2_pressure_proportional_valve_front > 260 && 
		p_control_policy_total_manager->working_FCU_error_code == H2_pressure_proportional_valve_front_under_error3)
	{
		//恢复正常
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
		p_control_policy_total_manager->working_FCU_error_code = H2_pressure_proportional_valve_front_over_error1;//比例阀前氢压	过压（一级故障）
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
		p_control_policy_total_manager->working_FCU_error_code = H2_pressure_proportional_valve_front_over_error3 ;	//比例阀前氢压  过压（3级故障）
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}  
	if(fcu_data_buffer.h2_data_buffer.h2_pressure_proportional_valve_front < 600 && 
		p_control_policy_total_manager->working_FCU_error_code == H2_pressure_proportional_valve_front_over_error3)
	{
		//恢复正常
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = working_normal;
		p_control_policy_total_manager->working_FCU_error_code = Succeed;
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}

	//判断比例阀后氢压，直接判断氢压波动，然后附加判断上限。
	if(fcu_data_buffer.h2_data_buffer.h2_pressure_proportional_valve_rear < 10 && 
		p_control_policy_total_manager->working_alarm_mode > one_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_fault0;
		p_control_policy_total_manager->working_status_mode = working_status_error;
		p_control_policy_total_manager->working_alarm_mode = one_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = H2_pressure_proportional_valve_rear_under_error1;	//比例阀后氢压  欠压（一级故障）
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
		p_control_policy_total_manager->working_FCU_error_code = H2_pressure_proportional_valve_rear_under_error3 ,	//比例阀后氢压  欠压（3级故障）
			p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}  
	if(fcu_data_buffer.h2_data_buffer.h2_pressure_proportional_valve_rear > 25 && 
		p_control_policy_total_manager->working_FCU_error_code == H2_pressure_proportional_valve_rear_under_error3)
	{
		//恢复正常
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
		p_control_policy_total_manager->working_FCU_error_code = H2_pressure_proportional_valve_rear_over_error1 ;	//比例阀后氢压  过压（一级故障）
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
		p_control_policy_total_manager->working_FCU_error_code = H2_pressure_proportional_valve_rear_over_error3 ;	//比例阀后氢压  过压（3级故障）
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}  
	if(fcu_data_buffer.h2_data_buffer.h2_pressure_proportional_valve_rear < 125 &&
		p_control_policy_total_manager->working_FCU_error_code == H2_pressure_proportional_valve_rear_over_error3)
	{
		//恢复正常
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = working_normal;
		p_control_policy_total_manager->working_FCU_error_code = Succeed;
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
	
	//判断入堆氢压
	if((fcu_data_buffer.h2_data_buffer.h2_pressure_fluctuate_last_min < -40 ||
	    fcu_data_buffer.h2_data_buffer.h2_pressure_pile_inlet < 10 ) && 
		p_control_policy_total_manager->working_alarm_mode > one_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_fault0;
		p_control_policy_total_manager->working_status_mode = working_status_error;
		p_control_policy_total_manager->working_alarm_mode = one_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = H2_pressure_pile_inlet_under_error1;	//入堆氢压  欠压（一级故障）
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
		p_control_policy_total_manager->working_FCU_error_code = H2_pressure_pile_inlet_under_error3;		//入堆氢压  欠压（3级故障）
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
	if((fcu_data_buffer.h2_data_buffer.h2_pressure_fluctuate_last_min > -25 &&
	    fcu_data_buffer.h2_data_buffer.h2_pressure_pile_inlet > 25 ) && 
		p_control_policy_total_manager->working_FCU_error_code == H2_pressure_pile_inlet_under_error3)
	{
		//恢复正常
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
		p_control_policy_total_manager->working_FCU_error_code = H2_pressure_pile_inlet_over_error1;		//入堆氢压  过压（一级故障）
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
		p_control_policy_total_manager->working_FCU_error_code = H2_pressure_pile_inlet_over_error3;	//入堆氢压  过压（3级故障）
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}  
	if((fcu_data_buffer.h2_data_buffer.h2_pressure_fluctuate_last_max < 25 && 
		fcu_data_buffer.h2_data_buffer.h2_pressure_pile_inlet < 95 ) && 
		p_control_policy_total_manager->working_FCU_error_code == H2_pressure_pile_inlet_over_error3)
	{
		//恢复正常
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = working_normal;
		p_control_policy_total_manager->working_FCU_error_code = Succeed;
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}

	//出口氢压和尾排氢压，并不重要，且与 比例阀后氢压、电堆耗氢量、尾排阀 有关，所以不做上下限的判断
	//入口氢压，出口氢压，尾排氢压    都随着比例阀氢压一起波动。
	//所以直接判断是否跟随即可。
	//这个因为不是很重要，所以就只报三级报警，提示作用。
	if((fcu_data_buffer.h2_data_buffer.h2_pressure_pile_inlet - fcu_data_buffer.h2_data_buffer.h2_pressure_proportional_valve_rear < -30 ||
		fcu_data_buffer.h2_data_buffer.h2_pressure_pile_inlet - fcu_data_buffer.h2_data_buffer.h2_pressure_proportional_valve_rear > 5) &&
		p_control_policy_total_manager->working_alarm_mode > three_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = three_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = H2_pressure_pile_inlet_no_follow_error3 ;	//入堆氢压  没有跟随比例阀后氢压（3级故障）
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}  
	if(fcu_data_buffer.h2_data_buffer.h2_pressure_pile_inlet - fcu_data_buffer.h2_data_buffer.h2_pressure_proportional_valve_rear > -25 &&
		fcu_data_buffer.h2_data_buffer.h2_pressure_pile_inlet - fcu_data_buffer.h2_data_buffer.h2_pressure_proportional_valve_rear < 2 &&
		p_control_policy_total_manager->working_FCU_error_code == H2_pressure_pile_inlet_no_follow_error3)
	{
		//恢复正常
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
		p_control_policy_total_manager->working_FCU_error_code = H2_pressure_pile_outlet_no_follow_error3 ;	//出堆氢压	没有跟随比例阀后氢压（3级故障）
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}  
	if(fcu_data_buffer.h2_data_buffer.h2_pressure_pile_outlet - fcu_data_buffer.h2_data_buffer.h2_pressure_proportional_valve_rear > -22 &&
		fcu_data_buffer.h2_data_buffer.h2_pressure_pile_outlet - fcu_data_buffer.h2_data_buffer.h2_pressure_proportional_valve_rear < 2 &&
		p_control_policy_total_manager->working_FCU_error_code == H2_pressure_pile_outlet_no_follow_error3)
	{
		//恢复正常
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = working_normal;
		p_control_policy_total_manager->working_FCU_error_code = Succeed;
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}  */
	//尾排氢压 因为靠近尾排阀，在尾排阀开启的瞬间会过降，短时间内不会跟随，所以不做跟随下限判断
	if(	fcu_data_buffer.h2_data_buffer.h2_pressure_tail_outlet - fcu_data_buffer.h2_data_buffer.h2_pressure_proportional_valve_rear > 5 &&
		p_control_policy_total_manager->working_alarm_mode > three_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = three_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = H2_pressure_tail_outlet_no_follow_error3;	//尾排氢压	没有跟随比例阀后氢压（3级故障）
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}  
	if(fcu_data_buffer.h2_data_buffer.h2_pressure_tail_outlet - fcu_data_buffer.h2_data_buffer.h2_pressure_proportional_valve_rear < 2 &&
		p_control_policy_total_manager->working_FCU_error_code == H2_pressure_tail_outlet_no_follow_error3)
	{
		//恢复正常
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = working_normal;
		p_control_policy_total_manager->working_FCU_error_code = Succeed;
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}



	//氢气循环泵 can通信
	//判断can通信是否正常。
	if(fcu_data_buffer.h2_data_buffer.h2_circulating_pump_working_communication_status == working_communication_outage && 
		p_control_policy_total_manager->working_alarm_mode > one_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_fault0;
		p_control_policy_total_manager->working_status_mode = working_status_error;
		p_control_policy_total_manager->working_alarm_mode = one_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = H2_circulating_pump_communication_error1;//氢气循环泵  can通信故障（一级故障）
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		p_control_policy_total_manager->working_error_count++;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
	//判断氢气循环泵里面的 can数据判断
	if(Succeed != approximate(LOW_VOLTAGE_24V, fcu_data_buffer.h2_data_buffer.h2_circulating_pump_actual_voltage) && 
		p_control_policy_total_manager->working_alarm_mode > one_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_fault0;
		p_control_policy_total_manager->working_status_mode = working_status_error;
		p_control_policy_total_manager->working_alarm_mode = one_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = H2_circulating_pump_low_voltage_power_error1;//氢气循环泵的  24V低压电源故障。（一级故障）
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
		p_control_policy_total_manager->working_FCU_error_code = H2_circulating_pump_temperature_over_error1;//氢气循环泵 温度过高（一级故障）
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		p_control_policy_total_manager->working_error_count++; 
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	} 
	if(fcu_data_buffer.h2_data_buffer.h2_circulating_pump_actual_electronic_temperature > 110 && 
		p_control_policy_total_manager->working_alarm_mode > two_level_fault)
	{
		//氢气循环泵  温度过高，2级故障  采取措施  转速降低50%
		fcu_data_buffer.h2_data_buffer.h2_circulating_pump_speed_setpoint_percent = 0.5;

		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = three_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = H2_circulating_pump_temperature_over_error2 ;	//氢气循环泵 温度过高（2级故障）
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	} 
	if(fcu_data_buffer.h2_data_buffer.h2_circulating_pump_actual_electronic_temperature < 105 && 
		p_control_policy_total_manager->working_FCU_error_code == H2_circulating_pump_temperature_over_error2)
	{
		fcu_data_buffer.h2_data_buffer.h2_circulating_pump_speed_setpoint_percent = 1;
		//恢复正常
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
		p_control_policy_total_manager->working_FCU_error_code = H2_circulating_pump_temperature_under_error1;//氢气循环泵 温度过低（一级故障）
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
		p_control_policy_total_manager->working_FCU_error_code = H2_circulating_pump_temperature_under_error3;	//氢气循环泵 温度过低（3级故障）
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}   
	if(fcu_data_buffer.h2_data_buffer.h2_circulating_pump_actual_electronic_temperature > 0 && 
		p_control_policy_total_manager->working_FCU_error_code == H2_circulating_pump_temperature_under_error3)
	{
		//恢复正常
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
		p_control_policy_total_manager->working_FCU_error_code = H2_circulating_pump_working_statas_error1;		//氢气循环泵工作状态故障（一级故障）
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
		p_control_policy_total_manager->working_FCU_error_code = H2_concentration_over_error1;	//氢气浓度检测  浓度过高（一级故障）
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		p_control_policy_total_manager->working_error_count++; 
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}



	//空气回路
	//判断入堆风压     35000转的时候   入堆风压 只有8kpa
	if(fcu_data_buffer.air_data_buffer.air_pressure_pile_inlet < 3 && 
		p_control_policy_total_manager->working_alarm_mode > one_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_fault0;
		p_control_policy_total_manager->working_status_mode = working_status_error;
		p_control_policy_total_manager->working_alarm_mode = one_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Air_pressure_pile_inlet_under_error1;	//入堆风压  欠压（一级故障）
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		p_control_policy_total_manager->working_error_count++;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
	if(fcu_data_buffer.air_data_buffer.air_pressure_pile_inlet < 5 && 
		p_control_policy_total_manager->working_alarm_mode > two_level_fault)
	{
	//	fcu_data_buffer.air_data_buffer.air_compressor_speed_setpoint_increment = 10000;//空压机转速，控制变频器，增量

		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = two_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Air_pressure_pile_inlet_under_error2 ;	//入堆风压	欠压（2级故障）
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
	if(fcu_data_buffer.air_data_buffer.air_pressure_pile_inlet > 7 && 
		p_control_policy_total_manager->working_FCU_error_code == Air_pressure_pile_inlet_under_error2)
	{
	//	fcu_data_buffer.air_data_buffer.air_compressor_speed_setpoint_increment = 0;//空压机转速，控制变频器，增量
		//恢复正常
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
		p_control_policy_total_manager->working_FCU_error_code = Air_pressure_pile_inlet_over_error1 ;		//入堆风压  过压（一级故障）
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
		p_control_policy_total_manager->working_FCU_error_code = Air_pressure_pile_inlet_over_error3 ;		//入堆风压  过压（3级故障）
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}  
	if(fcu_data_buffer.air_data_buffer.air_pressure_pile_inlet < 85 && 
		p_control_policy_total_manager->working_FCU_error_code == Air_pressure_pile_inlet_over_error3)
	{
		//恢复正常
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = working_normal;
		p_control_policy_total_manager->working_FCU_error_code = Succeed;
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}

	//出堆风压 3级故障
	if(fcu_data_buffer.air_data_buffer.air_pressure_pile_outlet > 100 && 
		p_control_policy_total_manager->working_alarm_mode > three_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = three_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Air_pressure_pile_outlet_over_error3 ;		//出堆风压  过压（3级故障）
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}   
	if(fcu_data_buffer.air_data_buffer.air_pressure_pile_outlet < 90 && 
		p_control_policy_total_manager->working_FCU_error_code == Air_pressure_pile_outlet_over_error3)
	{
		//恢复正常
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = working_normal;
		p_control_policy_total_manager->working_FCU_error_code = Succeed;
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
	//出口背压 3级故障
	if(fcu_data_buffer.air_data_buffer.air_pressure_pile_back > 100 && 
		p_control_policy_total_manager->working_alarm_mode > three_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = three_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Air_pressure_pile_back_over_error3;		//出口背压  过压（3级故障）
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}   
	if(fcu_data_buffer.air_data_buffer.air_pressure_pile_back < 90 && 
		p_control_policy_total_manager->working_FCU_error_code == Air_pressure_pile_back_over_error3)
	{
		//恢复正常
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = working_normal;
		p_control_policy_total_manager->working_FCU_error_code = Succeed;
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}        
	//检测空气流量
	if(fcu_data_buffer.air_data_buffer.air_rate_of_flow < 100 && 
		p_control_policy_total_manager->working_alarm_mode > one_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_fault0;
		p_control_policy_total_manager->working_status_mode = working_status_error;
		p_control_policy_total_manager->working_alarm_mode = one_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Air_rate_of_flow_under_error1 ;			//空气流量过低（一级故障）
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		p_control_policy_total_manager->working_error_count++; 
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}

	//判断入堆风温
	if(fcu_data_buffer.air_data_buffer.air_temperature_pile_inlet >75 && 
		p_control_policy_total_manager->working_alarm_mode > one_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_fault0;
		p_control_policy_total_manager->working_status_mode = working_status_error;
		p_control_policy_total_manager->working_alarm_mode = one_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Air_temperature_pile_inlet_over_error1;		//入堆风温  过温（一级故障）
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
		p_control_policy_total_manager->working_FCU_error_code = Air_temperature_pile_inlet_over_error3;		//入堆风温  过温（3级故障）
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
	if(fcu_data_buffer.air_data_buffer.air_temperature_pile_inlet <68&& 
		p_control_policy_total_manager->working_FCU_error_code == Air_temperature_pile_inlet_over_error3)
	{
		//恢复正常
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
		p_control_policy_total_manager->working_FCU_error_code = Air_temperature_pile_inlet_under_error3;		//入堆风温	欠温（3级故障）
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}  
	if(fcu_data_buffer.air_data_buffer.air_temperature_pile_inlet > 0 && 
		p_control_policy_total_manager->working_FCU_error_code == Air_temperature_pile_inlet_under_error3)
	{
		//恢复正常
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = working_normal;
		p_control_policy_total_manager->working_FCU_error_code = Succeed;
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
	//出堆风温 3级故障
	if(fcu_data_buffer.air_data_buffer.air_temperature_pile_outlet > 90 && 
		p_control_policy_total_manager->working_alarm_mode > three_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = three_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Air_temperature_pile_outlet_over_error3 ;	//出堆风温  过温（3级故障）
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}   
	if(fcu_data_buffer.air_data_buffer.air_temperature_pile_outlet < 85 && 
		p_control_policy_total_manager->working_FCU_error_code == Air_temperature_pile_outlet_over_error3)
	{
		//恢复正常
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = working_normal;
		p_control_policy_total_manager->working_FCU_error_code = Succeed;
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
	//空气尾排温度 3级故障
/*	if(fcu_data_buffer.air_data_buffer.air_temperature_pile_back > 90 && 
		p_control_policy_total_manager->working_alarm_mode > three_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = three_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Air_temperature_pile_back_over_error3;			//出口背温  过温（3级故障）
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}   
	if(fcu_data_buffer.air_data_buffer.air_temperature_pile_back < 85 && 
		p_control_policy_total_manager->working_FCU_error_code == Air_temperature_pile_back_over_error3)
	{
		//恢复正常
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = working_normal;
		p_control_policy_total_manager->working_FCU_error_code = Succeed;
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}       */


	//判断空压机的can数据
	//空压机  can通信模式
	if(fcu_data_buffer.air_data_buffer.air_compressor_working_communication_status == working_communication_outage && 
		p_control_policy_total_manager->working_alarm_mode > one_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_fault0;
		p_control_policy_total_manager->working_status_mode = working_status_error;
		p_control_policy_total_manager->working_alarm_mode = one_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Air_compressor_communication_error1;//空压机  can通信故障（一级故障）
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		p_control_policy_total_manager->working_error_count++;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
	//空压机控制器温度
	if(fcu_data_buffer.air_data_buffer.air_compressor_converter_temperature > 110 && 
		p_control_policy_total_manager->working_alarm_mode > one_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_fault0;
		p_control_policy_total_manager->working_status_mode = working_status_error;
		p_control_policy_total_manager->working_alarm_mode = one_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Air_compressor_temperature_over_error1;	//空压机 温度过高（一级故障）
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
		p_control_policy_total_manager->working_FCU_error_code = Air_compressor_temperature_over_error2 ,	//空压机 温度过高（2级故障）
			p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}   
	if(fcu_data_buffer.air_data_buffer.air_compressor_converter_temperature < 95 && 
		p_control_policy_total_manager->working_FCU_error_code == Air_compressor_temperature_over_error2)
	{
		//恢复正常
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
		p_control_policy_total_manager->working_FCU_error_code = Air_compressor_temperature_over_error3 ,	//空压机 温度过高（3级故障）
			p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}   
	if(fcu_data_buffer.air_data_buffer.air_compressor_converter_temperature < 85 && 
		p_control_policy_total_manager->working_FCU_error_code == Air_compressor_temperature_over_error3)
	{
		//恢复正常
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
		p_control_policy_total_manager->working_FCU_error_code = Air_compressor_temperature_under_error1;	//空压机 温度过低（一级故障）
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
		p_control_policy_total_manager->working_FCU_error_code = Air_compressor_temperature_under_error3 ,	//空压机 温度过低（3级故障）
			p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}   
	if(fcu_data_buffer.air_data_buffer.air_compressor_converter_temperature > 0 && 
		p_control_policy_total_manager->working_FCU_error_code == Air_compressor_temperature_under_error3)
	{
		//恢复正常
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = working_normal;
		p_control_policy_total_manager->working_FCU_error_code = Succeed;
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
	//检查氢空压机can  实际转速   
	//注意了，这里实际转速是随时都可能变的，在变化的瞬间，设定值会瞬间变化，而实际值会缓慢变化，此时是不相等的。
	//所以只需要判断实际转速是>20000即可。不要求等于设定值。
	if(	fcu_data_buffer.air_data_buffer.air_compressor_act_speed <20000 && 
		p_control_policy_total_manager->working_alarm_mode > one_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_fault0;
		p_control_policy_total_manager->working_status_mode = working_status_error;
		p_control_policy_total_manager->working_alarm_mode = one_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Air_compressor_act_speed_error1;			//空压机 实际转速故障（一级故障）
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		p_control_policy_total_manager->working_error_count++; 
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
	//检查氢空压机can  状态
	if(fcu_data_buffer.air_data_buffer.air_compressor_state != 12 &&
		fcu_data_buffer.air_data_buffer.air_compressor_state != 76 && 
		p_control_policy_total_manager->working_alarm_mode > one_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_fault0;
		p_control_policy_total_manager->working_status_mode = working_status_error;
		p_control_policy_total_manager->working_alarm_mode = one_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Air_compressor_working_statas_error1;		//空压机工作状态故障（一级故障）
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		p_control_policy_total_manager->working_error_count++; 
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}






	//三合一散热系统 数据校验
	//空压机出口水温
	if(fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_compressor_outlet >80 && 
		p_control_policy_total_manager->working_alarm_mode > one_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_fault0;
		p_control_policy_total_manager->working_status_mode = working_status_error;
		p_control_policy_total_manager->working_alarm_mode = one_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Water_temperature_compressor_outlet_over_error1;	//空压机出口水温  过温（一级故障）
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
		p_control_policy_total_manager->working_FCU_error_code = Water_temperature_compressor_outlet_over_error3 ;	//空压机出口水温  过温（3级故障）
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
	if(fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_compressor_outlet <70 && 
		p_control_policy_total_manager->working_FCU_error_code == Water_temperature_compressor_outlet_over_error3)
	{
		//恢复正常
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
		p_control_policy_total_manager->working_FCU_error_code = Water_temperature_compressor_outlet_under_error3;	//空压机出口水温  欠温（3级故障）
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}  
	if(fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_compressor_outlet > 0 && 
		p_control_policy_total_manager->working_FCU_error_code == Water_temperature_compressor_outlet_under_error3)
	{
		//恢复正常
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = working_normal;
		p_control_policy_total_manager->working_FCU_error_code = Succeed;
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
	//三合一水泵出口水温
	if(fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_pump_outlet >70 && 
		p_control_policy_total_manager->working_alarm_mode > one_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_fault0;
		p_control_policy_total_manager->working_status_mode = working_status_error;
		p_control_policy_total_manager->working_alarm_mode = one_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Water_temperature_pump_outlet_over_error1;		//三合一水泵出口水温  过温（一级故障）
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
		p_control_policy_total_manager->working_FCU_error_code = Water_temperature_pump_outlet_over_error3 ;		//三合一水泵出口水温  过温（3级故障）
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
	if(fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_pump_outlet <63 && 
		p_control_policy_total_manager->working_FCU_error_code == Water_temperature_pump_outlet_over_error3)
	{
		//恢复正常
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
		p_control_policy_total_manager->working_FCU_error_code = Water_temperature_pump_outlet_under_error3 ;	//三合一水泵出口水温  欠温（3级故障）
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}  
	if(fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_pump_outlet > 0 && 
		p_control_policy_total_manager->working_FCU_error_code == Water_temperature_pump_outlet_under_error3)
	{
		//恢复正常
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = working_normal;
		p_control_policy_total_manager->working_FCU_error_code = Succeed;
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
	//空压机出口水压，水泵是不可控的，所以三合一水压也是固定的。所以只有一级故障
/*	if(fcu_data_buffer.water_for_compressor_data_bufferr.water_pressure_compressor_outlet < 20 && 
		p_control_policy_total_manager->working_alarm_mode > one_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_fault0;
		p_control_policy_total_manager->working_status_mode = working_status_error;
		p_control_policy_total_manager->working_alarm_mode = one_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Water_pressure_compressor_outlet_under_error1 ;	//空压机出口水压	欠压（一级故障）
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		p_control_policy_total_manager->working_error_count++; 
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
 */



        
	//电堆散热系统 数据
	//电堆入口水压
	if(fcu_data_buffer.water_for_pile_data_buffer.water_pressure_pile_inlet1 > 90 && 
		p_control_policy_total_manager->working_alarm_mode > one_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_fault0;
		p_control_policy_total_manager->working_status_mode = working_status_error;
		p_control_policy_total_manager->working_alarm_mode = one_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Water_pressure_pile_inlet_over_error1;				//电堆入口水压  过压（一级故障）
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
		p_control_policy_total_manager->working_FCU_error_code = Water_pressure_pile_inlet_under_error1;				//电堆入口水压  欠压（一级故障）
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		p_control_policy_total_manager->working_error_count++; 
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
	//电堆出口水压
	if(fcu_data_buffer.water_for_pile_data_buffer.water_pressure_pile_outlet1 > 30 && 
		p_control_policy_total_manager->working_alarm_mode > one_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_fault0;
		p_control_policy_total_manager->working_status_mode = working_status_error;
		p_control_policy_total_manager->working_alarm_mode = one_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Water_pressure_pile_outlet_over_error1;					//电堆出口水压  过压（一级故障）
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
		p_control_policy_total_manager->working_FCU_error_code = Water_pressure_pile_outlet_under_error1;				//电堆出口水压  欠压（一级故障）
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		p_control_policy_total_manager->working_error_count++; 
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
	//电堆入口和出口的水压差
	if(fcu_data_buffer.water_for_pile_data_buffer.water_pressure_pile_inlet1 - 
		fcu_data_buffer.water_for_pile_data_buffer.water_pressure_pile_outlet1 > 80 && 
		p_control_policy_total_manager->working_alarm_mode > one_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_fault0;
		p_control_policy_total_manager->working_status_mode = working_status_error;
		p_control_policy_total_manager->working_alarm_mode = one_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Water_pressure_differential_pile_inlet_and_outlet_over_error1;	//电堆入口和出口的水压差  过压（一级故障）
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
		p_control_policy_total_manager->working_FCU_error_code = Water_pressure_differential_pile_inlet_and_outlet_under_error1;	//电堆入口和出口的水压差  欠压（一级故障）
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		p_control_policy_total_manager->working_error_count++; 
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
           
	//电堆入口水温
	if(fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_inlet1 > 80 && 
		p_control_policy_total_manager->working_alarm_mode > one_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_fault0;
		p_control_policy_total_manager->working_status_mode = working_status_error;
		p_control_policy_total_manager->working_alarm_mode = one_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Water_temperature_pile_inlet_over_error1;				//电堆入口水温  过温（一级故障）
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
		p_control_policy_total_manager->working_FCU_error_code = Water_temperature_pile_inlet_over_error3;				//电堆入口水温  过温（3级故障）
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}  
	if(fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_inlet1 < 70 && 
		p_control_policy_total_manager->working_FCU_error_code == Water_temperature_pile_inlet_over_error3)
	{
		//恢复正常
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
		p_control_policy_total_manager->working_FCU_error_code = Water_temperature_pile_inlet_under_error1;				//电堆入口水温  欠温（一级故障）
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		p_control_policy_total_manager->working_error_count++; 
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
	//电堆出口水温
	if(fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_outlet1 > 90 && 
		p_control_policy_total_manager->working_alarm_mode > one_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_fault0;
		p_control_policy_total_manager->working_status_mode = working_status_error;
		p_control_policy_total_manager->working_alarm_mode = one_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Water_temperature_pile_outlet_over_error1;					//电堆出口水温  过温（一级故障）
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
		p_control_policy_total_manager->working_FCU_error_code = Water_temperature_pile_outlet_over_error3;					//电堆出口水温  过温（3级故障）
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}  
	if(fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_outlet1 < 80 && 
		p_control_policy_total_manager->working_FCU_error_code == Water_temperature_pile_outlet_over_error3)
	{
		//恢复正常
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
		p_control_policy_total_manager->working_FCU_error_code = Water_temperature_pile_outlet_under_error1;				//电堆出口水温  欠温（一级故障）
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		p_control_policy_total_manager->working_error_count++; 
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
	//电堆入口和出口的水温差
	if(fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_outlet1 - 
		fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_inlet1 > 16 && 
		p_control_policy_total_manager->working_alarm_mode > one_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_fault0;
		p_control_policy_total_manager->working_status_mode = working_status_error;
		p_control_policy_total_manager->working_alarm_mode = one_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Water_temperature_differential_pile_inlet_and_outlet_over_error1;	//电堆入口和出口的水温差  过温（一级故障）
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
		p_control_policy_total_manager->working_FCU_error_code = Water_temperature_differential_pile_inlet_and_outlet_over_error3;	//电堆入口和出口的水温差  过温（3级故障）
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}  
	if(fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_outlet1 - 
		fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_inlet1 < 10 && 
		p_control_policy_total_manager->working_FCU_error_code == Water_temperature_differential_pile_inlet_and_outlet_over_error3)
	{
		//恢复正常
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = working_normal;
		p_control_policy_total_manager->working_FCU_error_code = Succeed;
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}

       



	//电堆发电的数据
	//电堆的电压
	if(fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_voltage < 130 && 
		p_control_policy_total_manager->working_alarm_mode > one_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_fault0;
		p_control_policy_total_manager->working_status_mode = working_status_error;
		p_control_policy_total_manager->working_alarm_mode = one_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Galvanic_pile_voltage_under_error1;			//电堆电压过低（一级故障）
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
		p_control_policy_total_manager->working_FCU_error_code = Galvanic_pile_voltage_under_error2;		//电堆电压过低（2级故障）
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}  
	if(fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_voltage > 137 && 
		p_control_policy_total_manager->working_FCU_error_code == Galvanic_pile_voltage_under_error2)
	{
		//恢复正常
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
		p_control_policy_total_manager->working_FCU_error_code = Galvanic_pile_voltage_under_error3;		//电堆电压过低（3级故障）
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}  
	if(fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_voltage > 143 && 
		p_control_policy_total_manager->working_FCU_error_code == Galvanic_pile_voltage_under_error3)
	{
		//恢复正常
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
		p_control_policy_total_manager->working_FCU_error_code = Galvanic_pile_voltage_over_error1 ;				//电堆电压过高（一级故障）
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		p_control_policy_total_manager->working_error_count++; 
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}

	//电堆电流
	if(fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_electricity > 390 && 
		p_control_policy_total_manager->working_alarm_mode > one_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_fault0;
		p_control_policy_total_manager->working_status_mode = working_status_error;
		p_control_policy_total_manager->working_alarm_mode = one_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Galvanic_pile_electricity_over_error1 ;			//电堆电流过高（一级故障）
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
		p_control_policy_total_manager->working_FCU_error_code = Galvanic_pile_electricity_over_error2;		//电堆电流过高（2级故障）
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}  
	if(fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_electricity < 375 && 
		p_control_policy_total_manager->working_FCU_error_code == Galvanic_pile_electricity_over_error2)
	{
		//恢复正常
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
		p_control_policy_total_manager->working_FCU_error_code = Galvanic_pile_electricity_over_error3;			//电堆电流过高（3级故障）
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}  
	if(fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_electricity < 365 && 
		p_control_policy_total_manager->working_FCU_error_code == Galvanic_pile_electricity_over_error3)
	{
		//恢复正常
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
		p_control_policy_total_manager->working_FCU_error_code = Galvanic_pile_electricity_under_error1 ;	//电堆电流过低（一级故障）
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		p_control_policy_total_manager->working_error_count++; 
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}

	//电堆氢氧两侧的压差 
	if(fcu_data_buffer.h2_data_buffer.h2_pressure_pile_inlet - 
		fcu_data_buffer.air_data_buffer.air_pressure_pile_inlet > 80 && 
		p_control_policy_total_manager->working_alarm_mode > one_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_fault0;
		p_control_policy_total_manager->working_status_mode = working_status_error;
		p_control_policy_total_manager->working_alarm_mode = one_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Galvanic_pile_pressure_differential_h2_and_air_over_error1;	//电堆氢氧两侧的压差  过压（一级故障）
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
		p_control_policy_total_manager->working_FCU_error_code = Galvanic_pile_pressure_differential_h2_and_air_over_error2 ;	//电堆氢氧两侧的压差  过压（2级故障）
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}  
	if(fcu_data_buffer.h2_data_buffer.h2_pressure_pile_inlet - 
		fcu_data_buffer.air_data_buffer.air_pressure_pile_inlet < 73 && 
		p_control_policy_total_manager->working_FCU_error_code == Galvanic_pile_pressure_differential_h2_and_air_over_error2)
	{
		//恢复正常
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
		p_control_policy_total_manager->working_FCU_error_code = Galvanic_pile_pressure_differential_h2_and_air_over_error3 ;	//电堆氢氧两侧的压差  过压（3级故障）
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}  
	if(fcu_data_buffer.h2_data_buffer.h2_pressure_pile_inlet - 
		fcu_data_buffer.air_data_buffer.air_pressure_pile_inlet < 68 && 
		p_control_policy_total_manager->working_FCU_error_code == Galvanic_pile_pressure_differential_h2_and_air_over_error3)
	{
		//恢复正常
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = working_normal;
		p_control_policy_total_manager->working_FCU_error_code = Succeed;
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}


	//巡检
	if(fcu_data_buffer.galvanic_pile_data_buffer.itinerant_detective_working_communication_status == working_communication_outage && 
		p_control_policy_total_manager->working_alarm_mode > one_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_fault0;
		p_control_policy_total_manager->working_status_mode = working_status_error;
		p_control_policy_total_manager->working_alarm_mode = one_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Itinerant_detective_communication_error1;//巡检  can通信故障（一级故障）
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		p_control_policy_total_manager->working_error_count++;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
/*	//如果故障停机，巡检的电压在待机的时候，可能会出现异常判断，因此这里就不判断状态了，只在运行发电之后，判断最小电压。
	//运行期间状态错误只报2级告警，由后面的单片最小电压来判断巡检的状态
	if(fcu_data_buffer.galvanic_pile_data_buffer.itinerant_detective_working_statas  != 1 && 
		p_control_policy_total_manager->working_alarm_mode > two_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = two_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Itinerant_detective_working_statas_error2 ;	//巡检工作状态故障（2级故障）
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}  
	if(fcu_data_buffer.galvanic_pile_data_buffer.itinerant_detective_working_statas  == 1 && 
		p_control_policy_total_manager->working_FCU_error_code == Itinerant_detective_working_statas_error2)
	{
		//恢复正常
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
		p_control_policy_total_manager->working_FCU_error_code = Glectric1_single_chip_minimum_voltage_under_error1;			//巡检单片电压过低（一级故障）
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
		p_control_policy_total_manager->working_FCU_error_code = Glectric1_single_chip_minimum_voltage_under_error2 ;			//巡检单片电压过低（2级故障）
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}  
	if(fcu_data_buffer.galvanic_pile_data_buffer.electric1_single_chip_minimum_voltage > 0.88 && 
		p_control_policy_total_manager->working_FCU_error_code == Glectric1_single_chip_minimum_voltage_under_error2)
	{
		//恢复正常
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
		p_control_policy_total_manager->working_FCU_error_code = Glectric1_single_chip_minimum_voltage_under_error3;		//巡检单片电压过低（3级故障）
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}  
	if(fcu_data_buffer.galvanic_pile_data_buffer.electric1_single_chip_minimum_voltage > 0.92 && 
		p_control_policy_total_manager->working_FCU_error_code == Glectric1_single_chip_minimum_voltage_under_error3)
	{
		//恢复正常
		p_control_policy_total_manager->working_control_mode = working_control_run;
		p_control_policy_total_manager->working_status_mode = working_status_run;
		p_control_policy_total_manager->working_alarm_mode = working_normal;
		p_control_policy_total_manager->working_FCU_error_code = Succeed;
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}


 /*   //绝缘检测，
	if(fcu_data_buffer.galvanic_pile_data_buffer.insulation_monitor_working_communication_status == working_communication_outage && 
		p_control_policy_total_manager->working_alarm_mode > one_level_fault)
	{
		p_control_policy_total_manager->working_control_mode = working_control_fault0;
		p_control_policy_total_manager->working_status_mode = working_status_error;
		p_control_policy_total_manager->working_alarm_mode = one_level_fault;
		p_control_policy_total_manager->working_FCU_error_code = Insulation_monitor_communication_error1;//绝缘模块  can通信故障（一级故障）
		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		p_control_policy_total_manager->working_error_count++;
		//p_control_policy_total_manager->fcu_updata_event_time = system_time;
	}
  */



	return Succeed;
}






//FCU主控的管理更新数据（控制算法）
//最核心的控制算法，自动管理所有的数据，并保证发电机的正常运行。
enum Error_code Control_Policy_Total_Manager_updata_by_system(
struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

    if(fcu_data_buffer.galvanic_pile_data_buffer.fcu_stutter_stop_enable == 1)
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




//fcu主控，控制中断的算法，刚开机时的状态，进入自检1阶段
enum Error_code Control_Policy_Total_Manager_for_outage(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->fcu_system_running_mode && p_control_policy_total_manager->working_control_mode == working_control_outage)
	{
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_1S)
		{
			//pcu板子启动之后，直接从控制无效跳掉自检1阶段
			p_control_policy_total_manager->working_control_mode = working_control_check1;
			p_control_policy_total_manager->working_status_mode = working_status_communication_outage;
			p_control_policy_total_manager->working_alarm_mode = working_normal;
			p_control_policy_total_manager->fcu_updata_event_time = system_time;
			p_control_policy_total_manager->working_error_count = 0;


			//半自动模式，单步运行（运行一次之后会切换到手动，然后就不会运行了，必须再次切换到半自动模式才能运行）
			if(p_control_policy_total_manager->fcu_system_running_mode == system_running_semi_auto)
			{
				p_control_policy_total_manager->fcu_system_running_mode = system_running_manual;
			}

		}
	}

	return error_code;
}			




//fcu主控，自我检查1的算法，检查通信，进入等待状态
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
				//切换到等待状态，并控制其他模块进入待机准备。（控制状态：待机，	工作状态：待机，	故障等级：正常）
				p_control_policy_total_manager->working_control_mode = working_control_wait;
				p_control_policy_total_manager->working_status_mode = working_status_wait;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
				//只有上电自检，才有权力清除错误计数。
				p_control_policy_total_manager->working_error_count = 0;

				//fcu data切换到wait状态
				//need programe

				//半自动模式，单步运行（运行一次之后会切换到手动，然后就不会运行了，必须再次切换到半自动模式才能运行）
				if(p_control_policy_total_manager->fcu_system_running_mode == system_running_semi_auto)
				{
					p_control_policy_total_manager->fcu_system_running_mode = system_running_manual;
				}
			}
			//上电自检错误，并且接受到启动命令，那么直接跳转到自检2
			else if(fcu_data_buffer.galvanic_pile_data_buffer.fcu_start_enable == 1)
			{
				//这里直接跳转到自检2，因为要重新刷新时间。
				p_control_policy_total_manager->working_control_mode = working_control_check2;
				p_control_policy_total_manager->working_status_mode = working_status_communication_outage;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			//上电自检错误，并且没有接受到启动命令，则无限进行自检.
			else
			{
				//上电自检，超时60s，则直接报错，自检超时故障
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
					else if(atd_wait_check() != Succeed)//ad待机检测，判断传感器是否正常
					{
						p_control_policy_total_manager->working_FCU_error_code = atd_wait_check();
					}
				}
				else
				{
					//继续自检，直到通信恢复，
					p_control_policy_total_manager->working_control_mode = working_control_check1;
					p_control_policy_total_manager->working_status_mode = working_status_communication_outage;
				}

			}
		}

	}


	return error_code;
}	




//FCU主控，自检2的算法，（当自检1没有通过，但是就接收到了启动命令，超时判断，10s内如果自检通过，那么进入待机，否则报错）
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
				//切换到等待状态，并控制其他模块进入待机准备。（控制状态：待机，	工作状态：待机，	故障等级：正常）
				p_control_policy_total_manager->working_control_mode = working_control_wait;
				p_control_policy_total_manager->working_status_mode = working_status_wait;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
				//只有上电自检，才有权力清除错误计数。
				p_control_policy_total_manager->working_error_count = 0;

				//fcu data切换到wait状态
				//need programe

				//半自动模式，单步运行（运行一次之后会切换到手动，然后就不会运行了，必须再次切换到半自动模式才能运行）
				if(p_control_policy_total_manager->fcu_system_running_mode == system_running_semi_auto)
				{
					p_control_policy_total_manager->fcu_system_running_mode = system_running_manual;
				}
			}
			//超时判断，10s内如果自检通过，那么进入待机，否则报错
			else
			{
				//上电自检，超时10s，则直接报错，自检超时故障
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
					else if(atd_wait_check() != Succeed)//ad待机检测，判断传感器是否正常
					{
						p_control_policy_total_manager->working_FCU_error_code = atd_wait_check();
					}
				}
				else
				{
					//继续自检，直到通信恢复，
					p_control_policy_total_manager->working_control_mode = working_control_check2;
					p_control_policy_total_manager->working_status_mode = working_status_communication_outage;
				}
			}
		}

	}


	return error_code;
}	


//fcu主控，等待处理的算法，判断是否需要启动fc，如果需要启动，则进入自检2状态，否则继续停留在等待状态。
enum Error_code Control_Policy_Total_Manager_for_wait(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->fcu_system_running_mode && p_control_policy_total_manager->working_control_mode == working_control_wait)
	{
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_100MS)
		{
			//收到启动命令
			if(fcu_data_buffer.galvanic_pile_data_buffer.fcu_start_enable == 1)
			{
				//打开氢气入口阀，自检3，需要判断氢气是否供上
				fcu_data_buffer.h2_data_buffer.h2_inlet_valve = 1;

				//如果允许启动，从等待状态跳到自检3阶段
				p_control_policy_total_manager->working_control_mode = working_control_check3;
				p_control_policy_total_manager->working_status_mode = working_status_wait;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;

				//半自动模式，单步运行（运行一次之后会切换到手动，然后就不会运行了，必须再次切换到半自动模式才能运行）
				if(p_control_policy_total_manager->fcu_system_running_mode == system_running_semi_auto)
				{
					p_control_policy_total_manager->fcu_system_running_mode = system_running_manual;
				}
			}
			//否则，就一直等待启动命令
		}
	}

	return error_code;
}			



//fcu主控，自检3的算法，分析子模块的数据，判断是否状态正常，如果正常，就进入启动阶段
enum Error_code Control_Policy_Total_Manager_for_check3(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->fcu_system_running_mode && p_control_policy_total_manager->working_control_mode == working_control_check3)
	{
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_100MS)
		{
			//判断can通信是否正常。
			if(fcu_data_buffer.h2_data_buffer.h2_circulating_pump_working_communication_status == working_communication_outage)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = H2_circulating_pump_communication_error1;//氢气循环泵  can通信故障（一级故障）
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_check3;
				p_control_policy_total_manager->working_error_count++;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			else if(fcu_data_buffer.air_data_buffer.air_compressor_working_communication_status == working_communication_outage)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = Air_compressor_communication_error1;//空压机  can通信故障（一级故障）
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_check3;
				p_control_policy_total_manager->working_error_count++;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
		/*	else if(fcu_data_buffer.galvanic_pile_data_buffer.insulation_monitor_working_communication_status == working_communication_outage)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = Insulation_monitor_communication_error1;//绝缘模块  can通信故障（一级故障）
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_check3;
				p_control_policy_total_manager->working_error_count++;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}   */
			else if(fcu_data_buffer.galvanic_pile_data_buffer.itinerant_detective_working_communication_status == working_communication_outage)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = Itinerant_detective_communication_error1;//巡检  can通信故障（一级故障）
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_check3;
				p_control_policy_total_manager->working_error_count++;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			else if(fcu_data_buffer.galvanic_pile_data_buffer.itinerant_detective_working_communication_status2 == working_communication_outage)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = Itinerant_detective_communication_error1;//巡检  can通信故障（一级故障）
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_check3;
				p_control_policy_total_manager->working_error_count++;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			//判断比例阀前氢压
			else if(fcu_data_buffer.h2_data_buffer.h2_pressure_proportional_valve_front < H2_PRESSURE_PROPORTIONAL_VALVE_FRONT_LOWER_LIMIT)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = H2_pressure_proportional_valve_front_under_error1;//比例阀前氢压	欠压（一级故障）
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_check3;
				p_control_policy_total_manager->working_error_count++;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			else if(fcu_data_buffer.h2_data_buffer.h2_pressure_proportional_valve_front > H2_PRESSURE_PROPORTIONAL_VALVE_FRONT_UPPER_LIMIT)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = H2_pressure_proportional_valve_front_over_error1;//比例阀前氢压	过压（一级故障）
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_check3;
				p_control_policy_total_manager->working_error_count++;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			//判断atd采样的数据
			else if(atd_wait_check_ex() != Succeed)//ad待机检测，判断传感器是否正常 ,不带比例阀前氢压
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = atd_wait_check_ex();//ad待机检测，判断传感器是否正常 ,不带比例阀前氢压
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_check3;
				p_control_policy_total_manager->working_error_count++;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			//判断氢气循环泵里面的 can数据判断
			else if(Succeed != approximate(LOW_VOLTAGE_24V, 
				fcu_data_buffer.h2_data_buffer.h2_circulating_pump_actual_voltage))
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = H2_circulating_pump_low_voltage_power_error1;//氢气循环泵的  24V低压电源故障。（一级故障）
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_check3;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			} 
			else if(fcu_data_buffer.h2_data_buffer.h2_circulating_pump_actual_electronic_temperature > 120)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = H2_circulating_pump_temperature_over_error1;//氢气循环泵 温度过高（一级故障）
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_check3;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			} 
			else if(fcu_data_buffer.h2_data_buffer.h2_circulating_pump_actual_electronic_temperature < -20)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = H2_circulating_pump_temperature_under_error1;//氢气循环泵 温度过低（一级故障）
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_check3;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			} 
			else if(fcu_data_buffer.h2_data_buffer.h2_circulating_pump_status_diagnose_word != 4)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = H2_circulating_pump_working_statas_error1;		//氢气循环泵工作状态故障（一级故障）
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_check3;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			} 
			//空压机的can数据 判断
			else if(fcu_data_buffer.air_data_buffer.air_compressor_state != 0 &&
				fcu_data_buffer.air_data_buffer.air_compressor_state != 64)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = Air_compressor_working_statas_error1;		//空压机工作状态故障（一级故障）
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_check3;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			} 
			else if(fcu_data_buffer.air_data_buffer.air_compressor_converter_temperature > 120)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = Air_compressor_temperature_over_error1;	//空压机 温度过高（一级故障）
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_check3;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			} 
			else if(fcu_data_buffer.air_data_buffer.air_compressor_converter_temperature < -20)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = Air_compressor_temperature_under_error1;	//空压机 温度过低（一级故障）
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_check3;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			} 
		/*	//巡检的can数据 判断  如果故障停机，巡检的电压在待机的时候，可能会出现异常判断，因此这里就不判断状态了，只在运行发电之后，判断最小电压。
			else if(fcu_data_buffer.galvanic_pile_data_buffer.itinerant_detective_working_statas  != 0 )
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = Itinerant_detective_working_statas_error1;		//巡检工作状态故障（一级故障）
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_check3;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}   */
			//氢气浓度传感器
			else if(fcu_data_buffer.h2_data_buffer.h2_concentration > H2_CONCENTRATION_OVER_MAX)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = H2_concentration_over_error1;	//氢气浓度检测  浓度过高（一级故障）
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_check3;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			} 
			//如果没有错误，就是启动前自检ok，数据正常，那么允许fc启动
			else
			{
				//切换到启动1状态，（控制状态：启动，	工作状态：启动，	故障等级：正常）
				p_control_policy_total_manager->working_control_mode = working_control_start1;
				p_control_policy_total_manager->working_status_mode = working_status_starting;
				p_control_policy_total_manager->working_alarm_mode = working_normal;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;


				//fcu data切换到启动状态
				//need programe

				//半自动模式，单步运行（运行一次之后会切换到手动，然后就不会运行了，必须再次切换到半自动模式才能运行）
				if(p_control_policy_total_manager->fcu_system_running_mode == system_running_semi_auto)
				{
					p_control_policy_total_manager->fcu_system_running_mode = system_running_manual;
				}
			}
		}
	}

	return error_code;
}			



//fcu主控，启动1的算法，按照时序启动fc，如果启动成功，就进入运行阶段，如果启动失败，则进行回退处理，然后返回等待阶段
enum Error_code Control_Policy_Total_Manager_for_start1(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->fcu_system_running_mode && p_control_policy_total_manager->working_control_mode == working_control_start1)
	{
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_100MS)
		{
		    //开启小电阻负载的继电器。45kw的新操作。确保燃料电池在启动的过程中阴极电位不至于过高
		    fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_is_enble_load_resistance = 1;
			//开启2个水泵
			fcu_data_buffer.water_for_pile_data_buffer.water_pump_pwm_dutyfactor1 = 9000;
			fcu_data_buffer.water_for_compressor_data_bufferr.water_pump_pwm_dutyfactor = 9000;

			//切换到启动2状态，（控制状态：启动，	工作状态：启动，	故障等级：正常）
			p_control_policy_total_manager->working_control_mode = working_control_start2;
			p_control_policy_total_manager->working_status_mode = working_status_starting;
			p_control_policy_total_manager->working_alarm_mode = working_normal;
			p_control_policy_total_manager->fcu_updata_event_time = system_time;

			//半自动模式，单步运行（运行一次之后会切换到手动，然后就不会运行了，必须再次切换到半自动模式才能运行）
			if(p_control_policy_total_manager->fcu_system_running_mode == system_running_semi_auto)
			{
				p_control_policy_total_manager->fcu_system_running_mode = system_running_manual;
			}

		}
	}

	return error_code;
}	

//fcu主控，启动2的算法，按照时序启动fc，如果启动成功，就进入运行阶段，如果启动失败，则进行回退处理，然后返回等待阶段
enum Error_code Control_Policy_Total_Manager_for_start2(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->fcu_system_running_mode && p_control_policy_total_manager->working_control_mode == working_control_start2)
	{
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_100MS)
		{
			//开启氢气尾排，常开。
			fcu_data_buffer.h2_data_buffer.h2_is_enable_outlet_valve = 1;

			//切换到启动3状态，（控制状态：启动，	工作状态：启动，	故障等级：正常）
			p_control_policy_total_manager->working_control_mode = working_control_start3;
			p_control_policy_total_manager->working_status_mode = working_status_starting;
			p_control_policy_total_manager->working_alarm_mode = working_normal;
			p_control_policy_total_manager->fcu_updata_event_time = system_time;

			//半自动模式，单步运行（运行一次之后会切换到手动，然后就不会运行了，必须再次切换到半自动模式才能运行）
			if(p_control_policy_total_manager->fcu_system_running_mode == system_running_semi_auto)
			{
				p_control_policy_total_manager->fcu_system_running_mode = system_running_manual;
			}

		}
	}

	return error_code;
}

//fcu主控，启动3的算法，按照时序启动fc，如果启动成功，就进入运行阶段，如果启动失败，则进行回退处理，然后返回等待阶段
enum Error_code Control_Policy_Total_Manager_for_start3(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->fcu_system_running_mode && p_control_policy_total_manager->working_control_mode == working_control_start3)
	{
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_1S)
		{
			//开启氢气比例阀。pwm初始化为0，之后只开启pid2的使能
			fcu_data_buffer.h2_data_buffer.h2_pid_mode = 2;
			fcu_data_buffer.h2_data_buffer.h2_pressure_target_value = 50;
			fcu_data_buffer.h2_data_buffer.h2_pressure_advance_set_value = 0;
			fcu_data_buffer.h2_data_buffer.h2_pressure_pid2_advance_time = 200;

			fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid2.Kp = PID2_KP;
			fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid2.Ki = PID2_KI;
			fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid2.Kd = PID2_KD;
			fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pwm_dutyfactor = 0;
			fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid2.is_enble_pid = 1;

			//切换到启动4状态，（控制状态：启动，	工作状态：启动，	故障等级：正常）
			p_control_policy_total_manager->working_control_mode = working_control_start4;
			p_control_policy_total_manager->working_status_mode = working_status_starting;
			p_control_policy_total_manager->working_alarm_mode = working_normal;
			p_control_policy_total_manager->fcu_updata_event_time = system_time;

			//半自动模式，单步运行（运行一次之后会切换到手动，然后就不会运行了，必须再次切换到半自动模式才能运行）
			if(p_control_policy_total_manager->fcu_system_running_mode == system_running_semi_auto)
			{
				p_control_policy_total_manager->fcu_system_running_mode = system_running_manual;
			}

		}
	}

	return error_code;
}

//fcu主控，启动4的算法，按照时序启动fc，如果启动成功，就进入运行阶段，如果启动失败，则进行回退处理，然后返回等待阶段
enum Error_code Control_Policy_Total_Manager_for_start4(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->fcu_system_running_mode && p_control_policy_total_manager->working_control_mode == working_control_start4)
	{
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_5S)
		{
			//检查比例阀后氢压是否达到指定的50
			if(Succeed != approximate(fcu_data_buffer.h2_data_buffer.h2_pressure_proportional_valve_rear, 50+3))
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = H2_pressure_proportional_valve_rear_unstable_error1;	//比例阀后氢压	压力不稳（一级故障）
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_start4;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			//检查入堆氢压是否达到指定的50
			else if(Succeed != approximate(fcu_data_buffer.h2_data_buffer.h2_pressure_pile_inlet, 50))
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = H2_pressure_pile_inlet_unstable_error1;	//入堆氢压	压力不稳（一级故障）
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_start4;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			//检查出堆氢压是否达到指定的50-10
	/*		else if(Succeed != approximate(fcu_data_buffer.h2_data_buffer.h2_pressure_pile_outlet, 50-10))
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = H2_pressure_pile_outlet_unstable_error1;	//出堆氢压	压力不稳（一级故障）
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_start4;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}    */
			//检查尾排氢压是否达到指定的50-10
			else if(Succeed != approximate(fcu_data_buffer.h2_data_buffer.h2_pressure_tail_outlet, 50-10))
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = H2_pressure_tail_outlet_unstable_error1;	//尾排氢压	压力不稳（一级故障）
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_start4;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			//检测比例阀开度， 尾排常开时，目标氢压50，比例阀一般会稳定在2000+
			else if(fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pwm_dutyfactor < 1000)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = H2_proportional_valve_statas_error1;	//比例阀状态故障（一级故障）
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_start4;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			else
			{
			/*	//在尾排常开的情况下，直接开启氢气循环泵。
				fcu_data_buffer.h2_data_buffer.h2_circulating_pump_speed_setpoint = H2_CIRCULATING_PUMP_SPEED_SETPOINT_1500;
				fcu_data_buffer.h2_data_buffer.h2_circulating_pump_enble = 1;
				fcu_data_buffer.h2_data_buffer.h2_circulating_pump_enable_pump = 1;   */
				
				//45kw新方案，氢气循环泵的启动顺序延后了，这里就直接进行吹扫模式。
				//氢气尾排由常开，变为吹扫模式。1s/0.5s
				fcu_data_buffer.h2_data_buffer.h2_outlet_valve_open_time = 500;
				fcu_data_buffer.h2_data_buffer.h2_outlet_valve_close_time = 1000;
				fcu_data_buffer.h2_data_buffer.h2_pressure_advance_set_value = 0;
				fcu_data_buffer.h2_data_buffer.h2_pressure_pid2_advance_time = 200;
				fcu_data_buffer.h2_data_buffer.h2_is_enable_outlet_valve = 2;

				//切换到启动5状态，（控制状态：启动，	工作状态：启动，	故障等级：正常）
				p_control_policy_total_manager->working_control_mode = working_control_start5;
				p_control_policy_total_manager->working_status_mode = working_status_starting;
				p_control_policy_total_manager->working_alarm_mode = working_normal;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;

				//半自动模式，单步运行（运行一次之后会切换到手动，然后就不会运行了，必须再次切换到半自动模式才能运行）
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
//fcu主控，启动5的算法，按照时序启动fc，如果启动成功，就进入运行阶段，如果启动失败，则进行回退处理，然后返回等待阶段
enum Error_code Control_Policy_Total_Manager_for_start5(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->fcu_system_running_mode && p_control_policy_total_manager->working_control_mode == working_control_start5)
	{
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_1S)
		{
			//检查氢气循环泵can  实际转速。
			if(Succeed != approximate(fcu_data_buffer.h2_data_buffer.h2_circulating_pump_actual_speed, H2_CIRCULATING_PUMP_SPEED_SETPOINT_1500))
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = H2_circulating_pump_actual_speed_error1;	//氢气循环泵 实际转速故障（一级故障）
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_start5;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			//检查氢气循环泵can  状态
			else if(fcu_data_buffer.h2_data_buffer.h2_circulating_pump_status_diagnose_word != 5)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = H2_circulating_pump_working_statas_error1;	//氢气循环泵工作状态故障（一级故障）
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_start5;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			else
			{   
				//氢气尾排由常开，变为吹扫模式。1s/0.5s
				fcu_data_buffer.h2_data_buffer.h2_outlet_valve_open_time = 500;
				fcu_data_buffer.h2_data_buffer.h2_outlet_valve_close_time = 1000;
				fcu_data_buffer.h2_data_buffer.h2_pressure_advance_set_value = 0;
				fcu_data_buffer.h2_data_buffer.h2_pressure_pid2_advance_time = 200;
				fcu_data_buffer.h2_data_buffer.h2_is_enable_outlet_valve = 2;

				//切换到启动6状态，（控制状态：启动，	工作状态：启动，	故障等级：正常）
				p_control_policy_total_manager->working_control_mode = working_control_start6;
				p_control_policy_total_manager->working_status_mode = working_status_starting;
				p_control_policy_total_manager->working_alarm_mode = working_normal;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;

				//半自动模式，单步运行（运行一次之后会切换到手动，然后就不会运行了，必须再次切换到半自动模式才能运行）
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
//fcu主控，启动5的算法，按照时序启动fc，如果启动成功，就进入运行阶段，如果启动失败，则进行回退处理，然后返回等待阶段
enum Error_code Control_Policy_Total_Manager_for_start5(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->fcu_system_running_mode && p_control_policy_total_manager->working_control_mode == working_control_start5)
	{
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_6S)
		{
			//检查氢压波动，pid1没有开，正常情况下为高频波动。波动要求大于10
			if(fcu_data_buffer.h2_data_buffer.h2_pressure_fluctuate_last_max -
				fcu_data_buffer.h2_data_buffer.h2_pressure_fluctuate_last_min < 10)	
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = H2_pressure_no_fluctuations_error1;	//氢气压力没有波动，可能是尾排阀故障（一级故障）
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_start5;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			else
			{
				//氢气尾排由吹扫模式（1s/0.5s）变为正常模式
				fcu_data_buffer.h2_data_buffer.h2_outlet_valve_open_time = 500;
				fcu_data_buffer.h2_data_buffer.h2_outlet_valve_close_time = 6000;
				fcu_data_buffer.h2_data_buffer.h2_pressure_advance_set_value = 0;
				fcu_data_buffer.h2_data_buffer.h2_pressure_pid2_advance_time = 1000;
				fcu_data_buffer.h2_data_buffer.h2_is_enable_outlet_valve = 2;

				//切换到启动7状态，（控制状态：启动，	工作状态：启动，	故障等级：正常）
				p_control_policy_total_manager->working_control_mode = working_control_start6;
				p_control_policy_total_manager->working_status_mode = working_status_starting;
				p_control_policy_total_manager->working_alarm_mode = working_normal;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;

				//半自动模式，单步运行（运行一次之后会切换到手动，然后就不会运行了，必须再次切换到半自动模式才能运行）
				if(p_control_policy_total_manager->fcu_system_running_mode == system_running_semi_auto)
				{
					p_control_policy_total_manager->fcu_system_running_mode = system_running_manual;
				}
			}
		}
	}

	return error_code;
}


//fcu主控，启动6的算法，按照时序启动fc，如果启动成功，就进入运行阶段，如果启动失败，则进行回退处理，然后返回等待阶段
enum Error_code Control_Policy_Total_Manager_for_start6(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->fcu_system_running_mode && p_control_policy_total_manager->working_control_mode == working_control_start6)
	{
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_100MS)
		{
			//检查氢压波动，pid1没有开，正常情况下为高频波动。波动要求大于10
			if(fcu_data_buffer.h2_data_buffer.h2_pressure_fluctuate_last_max -
				fcu_data_buffer.h2_data_buffer.h2_pressure_fluctuate_last_min < 10)	
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = H2_pressure_no_fluctuations_error1;	//氢气压力没有波动，可能是尾排阀故障（一级故障）
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_start6;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			else
			{
				//45kw新方案，空压机不使用转速控制，改用流量控制。
				fcu_data_buffer.air_data_buffer.air_compressor_speed_setpoint = 20000;
				fcu_data_buffer.air_data_buffer.air_compressor_enable = 1;
				
				fcu_data_buffer.air_data_buffer.air_rate_of_flow_target = 960;
				fcu_data_buffer.air_data_buffer.air_compressor_speed_pid.is_enble_pid = 1;

				//切换到启动8状态，（控制状态：启动，	工作状态：启动，	故障等级：正常）
				p_control_policy_total_manager->working_control_mode = working_control_start7;
				p_control_policy_total_manager->working_status_mode = working_status_starting;
				p_control_policy_total_manager->working_alarm_mode = working_normal;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;

				//半自动模式，单步运行（运行一次之后会切换到手动，然后就不会运行了，必须再次切换到半自动模式才能运行）
				if(p_control_policy_total_manager->fcu_system_running_mode == system_running_semi_auto)
				{
					p_control_policy_total_manager->fcu_system_running_mode = system_running_manual;
				}
			}
		}
	}

	return error_code;
}


//fcu主控，启动7的算法，按照时序启动fc，如果启动成功，就进入运行阶段，如果启动失败，则进行回退处理，然后返回等待阶段
enum Error_code Control_Policy_Total_Manager_for_start7(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->fcu_system_running_mode && p_control_policy_total_manager->working_control_mode == working_control_start7)
	{
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_5S)
		{
			//检查空压机can  实际转速
			//注意了，空压机提速很慢，所以不要求实际转速达到35000，只要求大于10000，表示已经启动即可
			if(fcu_data_buffer.air_data_buffer.air_compressor_act_speed < 10000)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = Air_compressor_act_speed_error1;			//空压机 实际转速故障（一级故障）
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_start7;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			//检查空压机can  状态
			else if(fcu_data_buffer.air_data_buffer.air_compressor_state != 12 &&
				fcu_data_buffer.air_data_buffer.air_compressor_state != 76)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = Air_compressor_working_statas_error1;		//空压机工作状态故障（一级故障）
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_start7;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			else
			{
				//开启空气尾排，8s/0.5s
				fcu_data_buffer.air_data_buffer.air_outlet_valve_open_time = 500;
				fcu_data_buffer.air_data_buffer.air_outlet_valve_close_time = 8000;
				fcu_data_buffer.air_data_buffer.air_is_enable_outlet_valve = 2;

				//切换到启动9状态，（控制状态：启动，	工作状态：启动，	故障等级：正常）
				p_control_policy_total_manager->working_control_mode = working_control_start8;
				p_control_policy_total_manager->working_status_mode = working_status_starting;
				p_control_policy_total_manager->working_alarm_mode = working_normal;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;

				//半自动模式，单步运行（运行一次之后会切换到手动，然后就不会运行了，必须再次切换到半自动模式才能运行）
				if(p_control_policy_total_manager->fcu_system_running_mode == system_running_semi_auto)
				{
					p_control_policy_total_manager->fcu_system_running_mode = system_running_manual;
				}
			}
		}
	}

	return error_code;
}


//fcu主控，启动8的算法，按照时序启动fc，如果启动成功，就进入运行阶段，如果启动失败，则进行回退处理，然后返回等待阶段
enum Error_code Control_Policy_Total_Manager_for_start8(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->fcu_system_running_mode && p_control_policy_total_manager->working_control_mode == working_control_start8)
	{
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_1S)
		{
			//此时检测风压，如果成功，则进入电堆检测  
			//注意了，空压机转速35000的时候，入堆风压只有7kpa，并且刚启动空压机，风压可能不稳
			if(fcu_data_buffer.air_data_buffer.air_pressure_pile_inlet < 3)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = Air_pressure_pile_inlet_under_error1;//入堆风压	欠压（一级故障）
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_start8;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			//检测空气流量
			else if(fcu_data_buffer.air_data_buffer.air_rate_of_flow < 100)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = Air_rate_of_flow_under_error1 ;			//空气流量过低（一级故障）
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_start8;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			else
			{
			    //45kw新方案，在启动空压机之后，再断开小电阻负载，并启动氢气循环泵。
			    fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_is_enble_load_resistance = 0;
			    
			    //目前是双堆方案，氢气侧产生的水量翻倍了，实测氢气循环泵的转速3000是最优的。
				fcu_data_buffer.h2_data_buffer.h2_circulating_pump_speed_setpoint = H2_CIRCULATING_PUMP_SPEED_SETPOINT_3000;
				fcu_data_buffer.h2_data_buffer.h2_circulating_pump_enble = 1;
				fcu_data_buffer.h2_data_buffer.h2_circulating_pump_enable_pump = 1;
			    
				//切换到启动10状态，（控制状态：启动，	工作状态：启动，	故障等级：正常）
				p_control_policy_total_manager->working_control_mode = working_control_start9;
				p_control_policy_total_manager->working_status_mode = working_status_starting;
				p_control_policy_total_manager->working_alarm_mode = working_normal;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;

				//半自动模式，单步运行（运行一次之后会切换到手动，然后就不会运行了，必须再次切换到半自动模式才能运行）
				if(p_control_policy_total_manager->fcu_system_running_mode == system_running_semi_auto)
				{
					p_control_policy_total_manager->fcu_system_running_mode = system_running_manual;
				}
			}
		}
	}

	return error_code;
}



//fcu主控，启动9的算法，按照时序启动fc，如果启动成功，就进入运行阶段，如果启动失败，则进行回退处理，然后返回等待阶段
enum Error_code Control_Policy_Total_Manager_for_start9(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->fcu_system_running_mode && p_control_policy_total_manager->working_control_mode == working_control_start9)
	{
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_3S)
		{
			//检查氢气循环泵can  实际转速。
			if(Succeed != approximate(fcu_data_buffer.h2_data_buffer.h2_circulating_pump_actual_speed, H2_CIRCULATING_PUMP_SPEED_SETPOINT_3000))
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = H2_circulating_pump_actual_speed_error1;	//氢气循环泵 实际转速故障（一级故障）
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_start9;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			//检查氢气循环泵can  状态
			else if(fcu_data_buffer.h2_data_buffer.h2_circulating_pump_status_diagnose_word != 5)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = H2_circulating_pump_working_statas_error1;	//氢气循环泵工作状态故障（一级故障）
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_start9;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			else
			{
				//下一步进入电堆检测  

				//切换到启动6状态，（控制状态：启动，	工作状态：启动，	故障等级：正常）
				p_control_policy_total_manager->working_control_mode = working_control_start10;
				p_control_policy_total_manager->working_status_mode = working_status_starting;
				p_control_policy_total_manager->working_alarm_mode = working_normal;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;

				//半自动模式，单步运行（运行一次之后会切换到手动，然后就不会运行了，必须再次切换到半自动模式才能运行）
				if(p_control_policy_total_manager->fcu_system_running_mode == system_running_semi_auto)
				{
					p_control_policy_total_manager->fcu_system_running_mode = system_running_manual;
				}
			}
		}
	}

	return error_code;
}


//fcu主控，启动10的算法，按照时序启动fc，如果启动成功，就进入运行阶段，如果启动失败，则进行回退处理，然后返回等待阶段
enum Error_code Control_Policy_Total_Manager_for_start10(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->fcu_system_running_mode && p_control_policy_total_manager->working_control_mode == working_control_start10)
	{
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_1S)
		{
			//检测电压和巡检
			if(fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_voltage < GALVANIC_PILE_OPEN_CIRCUIT_VOLTAGE )
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = Galvanic_pile_voltage_under_error1;			//电堆电压过低（一级故障）
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_start10;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			else if(fcu_data_buffer.galvanic_pile_data_buffer.electric1_single_chip_minimum_voltage < ITINERANT_DETECTIVE_OPEN_CIRCUIT_SINGLE_VOLTAGE)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = Glectric1_single_chip_minimum_voltage_under_error1;			//巡检单片电压过低（一级故障）
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_start10;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			else if(fcu_data_buffer.galvanic_pile_data_buffer.electric1_single_chip_minimum_voltage2 < ITINERANT_DETECTIVE_OPEN_CIRCUIT_SINGLE_VOLTAGE)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = Glectric1_single_chip_minimum_voltage_under_error1;			//巡检单片电压过低（一级故障）
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_start10;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
		/*	//巡检的can数据 判断  如果故障停机，巡检的电压在待机的时候，可能会出现异常判断，因此这里就不判断状态了，只在运行发电之后，判断最小电压。
			else if(fcu_data_buffer.galvanic_pile_data_buffer.itinerant_detective_working_statas  != 1 )
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = Itinerant_detective_working_statas_error1;		//巡检工作状态故障（一级故障）
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_start10;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}    */
			//检测电堆电流
			else if(fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_electricity > 5 ||
				fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_electricity < -5 )
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = Galvanic_pile_electricity_statas_error1;	//电堆电流传感器状态故障，可能是输出继电器故障（一级故障）
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_start10;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			else
			{
				//在正常发电之后，此时电压稳定后，就开启pid1
				//			fcu_data_buffer.h2_data_buffer.h2_pressure_advance_set_value = 0;
				fcu_data_buffer.h2_data_buffer.h2_pressure_pid1_advance_time = 250;

				fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid1.Kp = PID1_KP;
				fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid1.Ki = PID1_KI;
				fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid1.Kd = PID1_KD;
				fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid1.is_enble_pid = 1;

				//切换到启动11状态，（控制状态：启动，	工作状态：启动，	故障等级：正常）
				p_control_policy_total_manager->working_control_mode = working_control_start11;
				p_control_policy_total_manager->working_status_mode = working_status_starting;
				p_control_policy_total_manager->working_alarm_mode = working_normal;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;

				//半自动模式，单步运行（运行一次之后会切换到手动，然后就不会运行了，必须再次切换到半自动模式才能运行）
				if(p_control_policy_total_manager->fcu_system_running_mode == system_running_semi_auto)
				{
					p_control_policy_total_manager->fcu_system_running_mode = system_running_manual;
				}
			}
		}
	}

	return error_code;
}


//fcu主控，启动11的算法，按照时序启动fc，如果启动成功，就进入运行阶段，如果启动失败，则进行回退处理，然后返回等待阶段
enum Error_code Control_Policy_Total_Manager_for_start11(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->fcu_system_running_mode && p_control_policy_total_manager->working_control_mode == working_control_start11)
	{
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_15S)
		{
			//延时2个周期 ，检测氢压的波动，这里开启了pid，氢压波动会很小的。
			if(fcu_data_buffer.h2_data_buffer.h2_pressure_fluctuate_last_max -
				fcu_data_buffer.h2_data_buffer.h2_pressure_fluctuate_last_min < 2)	
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = H2_pressure_no_fluctuations_error1;	//氢气压力没有波动，可能是尾排阀故障（一级故障）
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_start11;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			else if(fcu_data_buffer.h2_data_buffer.h2_pressure_fluctuate_last_max > 30 )
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = 	H2_pressure_proportional_valve_rear_over_error1;	//比例阀后氢压  过压（一级故障）
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_start11;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			else if(fcu_data_buffer.h2_data_buffer.h2_pressure_fluctuate_last_min < -30)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = H2_pressure_proportional_valve_rear_under_error1;	//比例阀后氢压  欠压（一级故障）
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_start11;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			else
			{
				//切换到启动12状态，（控制状态：启动，	工作状态：启动，	故障等级：正常）
				p_control_policy_total_manager->working_control_mode = working_control_start12;
				p_control_policy_total_manager->working_status_mode = working_status_starting;
				p_control_policy_total_manager->working_alarm_mode = working_normal;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;

				//半自动模式，单步运行（运行一次之后会切换到手动，然后就不会运行了，必须再次切换到半自动模式才能运行）
				if(p_control_policy_total_manager->fcu_system_running_mode == system_running_semi_auto)
				{
					p_control_policy_total_manager->fcu_system_running_mode = system_running_manual;
				}
			}
		}
	}

	return error_code;
}


//fcu主控，启动12的算法，按照时序启动fc，如果启动成功，就进入运行阶段，如果启动失败，则进行回退处理，然后返回等待阶段
enum Error_code Control_Policy_Total_Manager_for_start12(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->fcu_system_running_mode && p_control_policy_total_manager->working_control_mode == working_control_start12)
	{
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_1S)
		{
			//检测2个散热系统的水压
			if(fcu_data_buffer.water_for_pile_data_buffer.water_pressure_pile_inlet1 < 40)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = Water_pressure_pile_inlet_under_error1;	//入堆水压	欠压（一级故障）
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_start12;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			else if(fcu_data_buffer.water_for_pile_data_buffer.water_pressure_pile_outlet1 < 5)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = Water_pressure_pile_outlet_under_error1;	//出堆水压	欠压（一级故障）
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_start12;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			else if(fcu_data_buffer.water_for_compressor_data_bufferr.water_pressure_pump_outlet < 20)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault0;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = Water_pressure_compressor_outlet_under_error1 ;	//空压机出口水压	欠压（一级故障）
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_start12;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			else     
			{
				//打开散热系统的风扇pid使能
				fcu_data_buffer.water_for_pile_data_buffer.water_temperature_fan_pid1.is_enble_pid = 1;
				fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_fan_pid.is_enble_pid = 1;	

				//打开电堆输出继电器，fcu进入run状态
				fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_is_enble_output = 1;
				//切换到运行状态，（控制状态：运行，	工作状态：运行，	故障等级：正常）
				p_control_policy_total_manager->working_control_mode = working_control_run;
				p_control_policy_total_manager->working_status_mode = working_status_run;
				p_control_policy_total_manager->working_alarm_mode = working_normal;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;

				//半自动模式，单步运行（运行一次之后会切换到手动，然后就不会运行了，必须再次切换到半自动模式才能运行）
				if(p_control_policy_total_manager->fcu_system_running_mode == system_running_semi_auto)
				{
					p_control_policy_total_manager->fcu_system_running_mode = system_running_manual;
				}
			}
		}
	}

	return error_code;
}











//fcu主控，运行的算法，功率控制，如果运行出现异常，则进行回退处理，然后返回等待阶段
enum Error_code Control_Policy_Total_Manager_for_run(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL )
	{return Pointer_is_null;}


	if(p_control_policy_total_manager->fcu_system_running_mode && p_control_policy_total_manager->working_control_mode == working_control_run)
	{
		//如果仍然是fcu开启的命令   100ms调整一次
		if(fcu_data_buffer.galvanic_pile_data_buffer.fcu_start_enable == 1 )
		{

			//100ms调整一次
			if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_100MS)
			{
				//先调档，然后在进行保护性的判断
				//FCU稳定运行时，自动调档
				FCU_automatic_gear_shift();    

				//运行时的保护检验，通用型，
				FCU_run_protect_check_common(p_control_policy_total_manager);    
				
				//临时加的一级故障判断的延时  3秒
				//如果出现一级告警，那么就要进行临时的延时判断
				if(p_control_policy_total_manager->working_alarm_mode == one_level_fault)
				{
				    //如果不是氢路比例阀后氢压和入堆氢压异常，那么就要对故障延时处理
				   if(p_control_policy_total_manager->working_FCU_error_code < 0x1201 ||
				        p_control_policy_total_manager->working_FCU_error_code > 0x130c) 
				   {
				        //如果是第一次出故障，那么就修改标记为1，并且进行时间计数。然后清除故障状态，让系统恢复到run状态
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
				        //如果上一次已经出现故障，那么这次就要进行时间判断，
				        else
				        {
				            //没有超时，那就清除故障状态，让系统恢复到run状态
				            if(system_time - p_control_policy_total_manager->one_level_fault_time_temp <= 5000)
				            {
	                        	p_control_policy_total_manager->working_control_mode = working_control_run;
	                        	p_control_policy_total_manager->working_status_mode = working_status_run;
	                        	p_control_policy_total_manager->working_alarm_mode = working_normal;
	                        	p_control_policy_total_manager->working_FCU_error_code = Succeed;
	                        	p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
		            	    	p_control_policy_total_manager->working_error_count = 0; 				                
				            }
				            //超时，那就不处理，那么就会直接到fault0去故障停机。
				            else
			            	{
			            	   p_control_policy_total_manager->one_level_fault_flag_temp = 0; 
		            		}  		            
				        }
				   }
				   // 氢路比例阀后氢压和入堆氢压异常，不处理，那么就会直接到fault0去故障停机。
				   else
		    		{
			    	   p_control_policy_total_manager->one_level_fault_flag_temp = 0; 
			    	}	   
				}
				//如果恢复正常，那么清除标志位，如果正常，故障状态是没有的，就没有必要清除。
				else
				{
				   p_control_policy_total_manager->one_level_fault_flag_temp = 0; 
				}

				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}

			//半自动模式，单步运行（运行一次之后会切换到手动，然后就不会运行了，必须再次切换到半自动模式才能运行）
			if(p_control_policy_total_manager->fcu_system_running_mode == system_running_semi_auto)
			{
				p_control_policy_total_manager->fcu_system_running_mode = system_running_manual;
			}
		}
		//如果收到停机命令
		else
		{
			if(fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_electricity > 50 )
			{
				//带载时，收到停机命令，不会立刻停机，
				//延时30秒，期间照常 调档和保护校验，但是会报错，提示操作员，在30s内进行降载
				//30s之后，强制
				if(system_time - p_control_policy_total_manager->fcu_updata_event_time < FCU_SYSTEM_CHANGE_MODE_DELAY_30S)
				{

					//先调档，然后在进行保护性的判断
					//FCU稳定运行时，自动调档
					FCU_automatic_gear_shift();    

					//运行时的保护检验，通用型，
					FCU_run_protect_check_common(p_control_policy_total_manager);   

					if(p_control_policy_total_manager->working_alarm_mode > one_level_fault)
					{			
						p_control_policy_total_manager->working_control_mode = working_control_run;
						p_control_policy_total_manager->working_status_mode = working_status_run;
						p_control_policy_total_manager->working_alarm_mode = three_level_fault;
						p_control_policy_total_manager->working_FCU_error_code = Galvanic_pile_electricity_over_when_stop_error2;	//收到停机指令时，电流大于100A，提示用户不能带载停机（2级故障）
						p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
						//		p_control_policy_total_manager->fcu_updata_event_time = system_time;
					}
				}
				else
				{
					//切换到停止1状态，（控制状态：停止，	工作状态：停止，	故障等级：正常）
					//注意了，这里要清除2级高级和3级告警
					p_control_policy_total_manager->working_control_mode = working_control_stop1;
					p_control_policy_total_manager->working_status_mode = working_status_stoping;
					p_control_policy_total_manager->working_alarm_mode = working_normal;
			//		p_control_policy_total_manager->working_FCU_error_code = Succeed;
			//		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
					p_control_policy_total_manager->fcu_updata_event_time = system_time;
					
					//半自动模式，单步运行（运行一次之后会切换到手动，然后就不会运行了，必须再次切换到半自动模式才能运行）
	    	    	if(p_control_policy_total_manager->fcu_system_running_mode == system_running_semi_auto)
	    	    	{
	    	    		p_control_policy_total_manager->fcu_system_running_mode = system_running_manual;
	    	    	}
				}
			}
			else
			{
				//切换到停止1状态，（控制状态：停止，	工作状态：停止，	故障等级：正常）
				//注意了，这里要清除2级高级和3级告警
				p_control_policy_total_manager->working_control_mode = working_control_stop1;
				p_control_policy_total_manager->working_status_mode = working_status_stoping;
				p_control_policy_total_manager->working_alarm_mode = working_normal;
		//		p_control_policy_total_manager->working_FCU_error_code = Succeed;
		//		p_control_policy_total_manager->working_FCU_error_control_mode = working_control_run;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
				
				//半自动模式，单步运行（运行一次之后会切换到手动，然后就不会运行了，必须再次切换到半自动模式才能运行）
			if(p_control_policy_total_manager->fcu_system_running_mode == system_running_semi_auto)
			{
				p_control_policy_total_manager->fcu_system_running_mode = system_running_manual;
			}
			}
		}
	}


}




//fcu主控，停止1的算法，按照时序停止fc，最终进入等待阶段
enum Error_code Control_Policy_Total_Manager_for_stop1(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->fcu_system_running_mode && p_control_policy_total_manager->working_control_mode == working_control_stop1)
	{
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_1S)
		{
			//判断电流，只有在小电流或者空载的时候，才能正常停机
			if(fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_electricity > 50 )
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault1;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = Galvanic_pile_electricity_over_when_stop_error1;//收到停机指令时，电流大于100A，提示用户不能带载停机（一级故障）
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_stop1;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			else
			{
				//关闭散热系统的风扇pid使能
				fcu_data_buffer.water_for_pile_data_buffer.water_temperature_fan_pid1.is_enble_pid = 0;
				fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_fan_pid.is_enble_pid = 0;	

				//开启氢气尾排，常开。
				fcu_data_buffer.h2_data_buffer.h2_is_enable_outlet_valve = 1;
				fcu_data_buffer.h2_data_buffer.h2_pid_mode = 2;
				fcu_data_buffer.h2_data_buffer.h2_pressure_advance_current_value = 0;

				//切换到停止2状态，（控制状态：停止，	工作状态：停止，	故障等级：正常）
				p_control_policy_total_manager->working_control_mode = working_control_stop2;
				p_control_policy_total_manager->working_status_mode = working_status_stoping;
				p_control_policy_total_manager->working_alarm_mode = working_normal;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;

				//半自动模式，单步运行（运行一次之后会切换到手动，然后就不会运行了，必须再次切换到半自动模式才能运行）
				if(p_control_policy_total_manager->fcu_system_running_mode == system_running_semi_auto)
				{
					p_control_policy_total_manager->fcu_system_running_mode = system_running_manual;
				}
			}
		}
	}

	return error_code;
}




//fcu主控，停止2的算法，按照时序停止fc，最终进入等待阶段
enum Error_code Control_Policy_Total_Manager_for_stop2(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->fcu_system_running_mode && p_control_policy_total_manager->working_control_mode == working_control_stop2)
	{
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_2S)
		{
			//调整pid1和pid2
			fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid1.Kp = PID1_KP;
			fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid1.Ki = PID1_KI;
			fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid1.Kd = PID1_KD;
			fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid2.Kp = PID2_KP;
			fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid2.Ki = PID2_KI;
			fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid2.Kd = PID2_KD;

			//切断负载，关闭电堆输出继电器
			fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_is_enble_output = 0;
			
			//45kw新方案，提前开启小电阻负载，
			fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_is_enble_load_resistance = 1;

			//切换到停止3状态，（控制状态：停止，	工作状态：停止，	故障等级：正常）
			p_control_policy_total_manager->working_control_mode = working_control_stop3;
			p_control_policy_total_manager->working_status_mode = working_status_stoping;
			p_control_policy_total_manager->working_alarm_mode = working_normal;
			p_control_policy_total_manager->fcu_updata_event_time = system_time;

			//半自动模式，单步运行（运行一次之后会切换到手动，然后就不会运行了，必须再次切换到半自动模式才能运行）
			if(p_control_policy_total_manager->fcu_system_running_mode == system_running_semi_auto)
			{
				p_control_policy_total_manager->fcu_system_running_mode = system_running_manual;
			}

		}
	}

	return error_code;
}



//fcu主控，停止3的算法，按照时序停止fc，最终进入等待阶段
enum Error_code Control_Policy_Total_Manager_for_stop3(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->fcu_system_running_mode && p_control_policy_total_manager->working_control_mode == working_control_stop3)
	{
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_1S)
		{
			//判断电流是否为0，不为0就表示 电堆输出接触器坏了，这个是相当危险的。
			//45kw新方案，提前开启了小负载，会有5A的电流
			if(fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_electricity > 12 ||
				fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_electricity < -5 )
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault3;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = Galvanic_pile_electricity_statas_error1;	//电堆电流传感器状态故障，可能是输出继电器故障（一级故障）
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_stop3;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			else
			{
				//降低目标氢压，和空压机转速。
				fcu_data_buffer.h2_data_buffer.h2_pressure_target_value = 50;
				
				fcu_data_buffer.air_data_buffer.air_compressor_speed_pid.is_enble_pid = 0;
				fcu_data_buffer.air_data_buffer.air_rate_of_flow_target = 960;
				fcu_data_buffer.air_data_buffer.air_compressor_speed_setpoint = 20000;

				//切换到停止4状态，（控制状态：停止，	工作状态：停止，	故障等级：正常）
				p_control_policy_total_manager->working_control_mode = working_control_stop4;
				p_control_policy_total_manager->working_status_mode = working_status_stoping;
				p_control_policy_total_manager->working_alarm_mode = working_normal;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;

				//半自动模式，单步运行（运行一次之后会切换到手动，然后就不会运行了，必须再次切换到半自动模式才能运行）
				if(p_control_policy_total_manager->fcu_system_running_mode == system_running_semi_auto)
				{
					p_control_policy_total_manager->fcu_system_running_mode = system_running_manual;
				}
			}
		}
	}

	return error_code;
}



//fcu主控，停止4的算法，按照时序停止fc，最终进入等待阶段
enum Error_code Control_Policy_Total_Manager_for_stop4(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->fcu_system_running_mode && p_control_policy_total_manager->working_control_mode == working_control_stop4)
	{
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_5S)
		{
			//检查比例阀后氢压是否达到指定的65
	/*		if(Succeed != approximate(fcu_data_buffer.h2_data_buffer.h2_pressure_proportional_valve_rear, 65))
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault3;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = H2_pressure_proportional_valve_rear_unstable_error1;	//比例阀后氢压	压力不稳（一级故障）
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_stop4;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			//检查入堆氢压是否达到指定的50
			else */if(Succeed != approximate(fcu_data_buffer.h2_data_buffer.h2_pressure_pile_inlet, 50))
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault3;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = H2_pressure_pile_inlet_unstable_error1;	//入堆氢压	压力不稳（一级故障）
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_stop4;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			//检查出堆氢压是否达到指定的50-10
	/*		else if(Succeed != approximate(fcu_data_buffer.h2_data_buffer.h2_pressure_pile_outlet, 50-10))
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault3;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = H2_pressure_pile_outlet_unstable_error1;	//出堆氢压	压力不稳（一级故障）
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_stop4;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}     */
			//检查尾排氢压是否达到指定的50-10
			else if(Succeed != approximate(fcu_data_buffer.h2_data_buffer.h2_pressure_tail_outlet, 50-10))
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault3;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = H2_pressure_tail_outlet_unstable_error1;	//尾排氢压	压力不稳（一级故障）
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_stop4;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			//检测比例阀开度， 尾排常开时，目标氢压50，比例阀一般会稳定在2000+
			else if(fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pwm_dutyfactor < 1000)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault3;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = H2_proportional_valve_statas_error1;	//比例阀状态故障（一级故障）
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_stop4;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			//检查氢空压机can  实际转速
			else if(Succeed != approximate(fcu_data_buffer.air_data_buffer.air_compressor_speed_setpoint, 
				fcu_data_buffer.air_data_buffer.air_compressor_act_speed))
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault3;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = Air_compressor_act_speed_error1;			//空压机 实际转速故障（一级故障）
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_stop4;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			//检查氢空压机can  状态
			else if(fcu_data_buffer.air_data_buffer.air_compressor_state != 12 &&
				fcu_data_buffer.air_data_buffer.air_compressor_state != 76)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault3;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = Air_compressor_working_statas_error1;		//空压机工作状态故障（一级故障）
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_stop4;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			else
			{
				//关闭pid1，调整pid2，然后进入吹扫模式
				fcu_data_buffer.h2_data_buffer.h2_pid_mode = 2;
				fcu_data_buffer.h2_data_buffer.h2_pressure_advance_set_value = 0;
				fcu_data_buffer.h2_data_buffer.h2_pressure_pid2_advance_time = 200;

				fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid2.Kp = PID2_KP;
				fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid2.Ki = PID2_KI;
				fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid2.Kd = PID2_KD;
				//		fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pwm_dutyfactor = 0;
				fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid2.is_enble_pid = 1;
				fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid1.is_enble_pid = 0;

				//然后进入吹扫模式，氢气循环泵继续运转
				//氢气尾排由常开，变为吹扫模式。1s/0.5s
				fcu_data_buffer.h2_data_buffer.h2_outlet_valve_open_time = 500;
				fcu_data_buffer.h2_data_buffer.h2_outlet_valve_close_time = 1000;
				fcu_data_buffer.h2_data_buffer.h2_is_enable_outlet_valve = 2;
				//开启空气尾排，变为吹扫模式，2s/0.5s
				fcu_data_buffer.air_data_buffer.air_outlet_valve_open_time = 500;
				fcu_data_buffer.air_data_buffer.air_outlet_valve_close_time = 2000;
				fcu_data_buffer.air_data_buffer.air_is_enable_outlet_valve = 2;

				//氢气循环泵在较大的转速下运行，要把循环泵里面的水吹扫出来。
				fcu_data_buffer.h2_data_buffer.h2_circulating_pump_speed_setpoint = H2_CIRCULATING_PUMP_SPEED_SETPOINT_3000;

				//切换到停止5状态，（控制状态：停止，	工作状态：停止，	故障等级：正常）
				p_control_policy_total_manager->working_control_mode = working_control_stop5;
				p_control_policy_total_manager->working_status_mode = working_status_stoping;
				p_control_policy_total_manager->working_alarm_mode = working_normal;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;

				//半自动模式，单步运行（运行一次之后会切换到手动，然后就不会运行了，必须再次切换到半自动模式才能运行）
				if(p_control_policy_total_manager->fcu_system_running_mode == system_running_semi_auto)
				{
					p_control_policy_total_manager->fcu_system_running_mode = system_running_manual;
				}
			}
		}
	}

	return error_code;
}


//fcu主控，停止5的算法，按照时序停止fc，最终进入等待阶段
enum Error_code Control_Policy_Total_Manager_for_stop5(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->fcu_system_running_mode && p_control_policy_total_manager->working_control_mode == working_control_stop5)
	{
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_1S)
		{
			//水泵和风扇全开，加快散热。
			//电堆入口水温    电堆出口水温    空压机出口水温    三合一水泵出口水温
			if(fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_inlet1 > 45 || 
				fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_outlet1 > 45 )
			{
				//水泵和风扇全开，加快散热。
				fcu_data_buffer.water_for_pile_data_buffer.water_pump_pwm_dutyfactor1 = 9000;
				fcu_data_buffer.water_for_pile_data_buffer.water_fan_pwm_dutyfactor1 = 9000;
				fcu_data_buffer.water_for_pile_data_buffer.water_fan_pwm_dutyfactor2 = 9000;
			}

			if(fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_compressor_outlet > 45 ||
				fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_pump_outlet > 45)
			{
				//水泵和风扇全开，加快散热。
				fcu_data_buffer.water_for_compressor_data_bufferr.water_pump_pwm_dutyfactor = 9000;
				fcu_data_buffer.water_for_compressor_data_bufferr.water_fan_pwm_dutyfactor = 9000;
			}

			//切换到停止6状态，（控制状态：停止，	工作状态：停止，	故障等级：正常）
			p_control_policy_total_manager->working_control_mode = working_control_stop6;
			p_control_policy_total_manager->working_status_mode = working_status_stoping;
			p_control_policy_total_manager->working_alarm_mode = working_normal;
			p_control_policy_total_manager->fcu_updata_event_time = system_time;

			//半自动模式，单步运行（运行一次之后会切换到手动，然后就不会运行了，必须再次切换到半自动模式才能运行）
			if(p_control_policy_total_manager->fcu_system_running_mode == system_running_semi_auto)
			{
				p_control_policy_total_manager->fcu_system_running_mode = system_running_manual;
			}

		}
	}

	return error_code;
}


//fcu主控，停止6的算法，按照时序停止fc，最终进入等待阶段
enum Error_code Control_Policy_Total_Manager_for_stop6(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->fcu_system_running_mode && p_control_policy_total_manager->working_control_mode == working_control_stop6)
	{
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_20S)
		{
			//检查氢压波动，pid1没有开，正常情况下为高频波动。波动要求大于10
			if(fcu_data_buffer.h2_data_buffer.h2_pressure_fluctuate_last_max -
				fcu_data_buffer.h2_data_buffer.h2_pressure_fluctuate_last_min < 10)
			{
			    //关闭氢气循环泵
				fcu_data_buffer.h2_data_buffer.h2_circulating_pump_speed_setpoint = H2_CIRCULATING_PUMP_SPEED_SETPOINT_3000;
				fcu_data_buffer.h2_data_buffer.h2_circulating_pump_enble = 1;
				fcu_data_buffer.h2_data_buffer.h2_circulating_pump_enable_pump = 0;
				
				p_control_policy_total_manager->working_control_mode = working_control_fault7;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = H2_pressure_no_fluctuations_error1;	//氢气压力没有波动，可能是尾排阀故障（一级故障）
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_stop6;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			else
			{
				//关闭氢气循环泵
				fcu_data_buffer.h2_data_buffer.h2_circulating_pump_speed_setpoint = H2_CIRCULATING_PUMP_SPEED_SETPOINT_3000;
				fcu_data_buffer.h2_data_buffer.h2_circulating_pump_enble = 1;
				fcu_data_buffer.h2_data_buffer.h2_circulating_pump_enable_pump = 0;

				//切换到停止7状态，（控制状态：停止，	工作状态：停止，	故障等级：正常）
				p_control_policy_total_manager->working_control_mode = working_control_stop7;
				p_control_policy_total_manager->working_status_mode = working_status_stoping;
				p_control_policy_total_manager->working_alarm_mode = working_normal;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;

				//半自动模式，单步运行（运行一次之后会切换到手动，然后就不会运行了，必须再次切换到半自动模式才能运行）
				if(p_control_policy_total_manager->fcu_system_running_mode == system_running_semi_auto)
				{
					p_control_policy_total_manager->fcu_system_running_mode = system_running_manual;
				}
			}
		}
	}

	return error_code;
}


//fcu主控，停止7的算法，按照时序停止fc，最终进入等待阶段
enum Error_code Control_Policy_Total_Manager_for_stop7(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->fcu_system_running_mode && p_control_policy_total_manager->working_control_mode == working_control_stop7)
	{
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_2S)
		{
			//检查氢气循环泵can  实际转速。
			if(fcu_data_buffer.h2_data_buffer.h2_circulating_pump_actual_speed > 500)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault7;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = H2_circulating_pump_actual_speed_error1;	//氢气循环泵 实际转速故障（一级故障）
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_stop7;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			//检查氢气循环泵can  状态
			else if(fcu_data_buffer.h2_data_buffer.h2_circulating_pump_status_diagnose_word != 4)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault7;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = H2_circulating_pump_working_statas_error1;	//氢气循环泵工作状态故障（一级故障）
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_stop7;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			else
			{
				//关闭氢气入口阀，切断氢气来源
				fcu_data_buffer.h2_data_buffer.h2_inlet_valve = 0;
				
				//20181218这里常开氢气尾排阀，快速将氢气排出，
				//个人感觉啊，之前是1/0.5s的吹扫模式，在这里关闭氢气入口阀，切断氢气来源之后，吹扫变不成立了。
				//目的在于排出氢气，因此直接常开氢气尾排阀，快速将氢气排出，
				fcu_data_buffer.h2_data_buffer.h2_is_enable_outlet_valve = 1;	

				//同时关闭空压机和空气尾排
				fcu_data_buffer.air_data_buffer.air_compressor_enable = 0;
				fcu_data_buffer.air_data_buffer.air_is_enable_outlet_valve = 0;

				//切换到停止8状态，（控制状态：停止，	工作状态：停止，	故障等级：正常）
				p_control_policy_total_manager->working_control_mode = working_control_stop8;
				p_control_policy_total_manager->working_status_mode = working_status_stoping;
				p_control_policy_total_manager->working_alarm_mode = working_normal;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;

				//半自动模式，单步运行（运行一次之后会切换到手动，然后就不会运行了，必须再次切换到半自动模式才能运行）
				if(p_control_policy_total_manager->fcu_system_running_mode == system_running_semi_auto)
				{
					p_control_policy_total_manager->fcu_system_running_mode = system_running_manual;
				}
			}
		}
	}

	return error_code;
}



//fcu主控，停止8的算法，按照时序停止fc，最终进入等待阶段
enum Error_code Control_Policy_Total_Manager_for_stop8(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->fcu_system_running_mode && p_control_policy_total_manager->working_control_mode == working_control_stop8)
	{
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_5S)
		{
			//判断比例阀前和后的氢压
			if(fcu_data_buffer.h2_data_buffer.h2_pressure_proportional_valve_front > 85)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault7;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = H2_pressure_proportional_valve_front_over_error1 ;//比例阀前氢压	过压（一级故障）
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_stop8;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			else if(fcu_data_buffer.h2_data_buffer.h2_pressure_proportional_valve_rear > 10)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault7;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = H2_pressure_proportional_valve_rear_over_error1 ;//比例阀后氢压  过压（一级故障）
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_stop8;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			else if(fcu_data_buffer.h2_data_buffer.h2_pressure_pile_inlet > 10)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault7;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = H2_pressure_pile_inlet_over_error1;		//入堆氢压  过压（一级故障）
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_stop8;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			//检查氢空压机can  实际转速
			else if(fcu_data_buffer.air_data_buffer.air_compressor_act_speed > 10000)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault7;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = Air_compressor_act_speed_error1;			//空压机 实际转速故障（一级故障）
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_stop8;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			//检查氢空压机can  状态
			else if(fcu_data_buffer.air_data_buffer.air_compressor_state != 0 &&
				fcu_data_buffer.air_data_buffer.air_compressor_state != 64)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault7;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = Air_compressor_working_statas_error1;		//空压机工作状态故障（一级故障）
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_stop8;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			else
			{
				//关闭比例阀，pid2， 关闭比例阀pwm，    
				fcu_data_buffer.h2_data_buffer.h2_pid_mode = 2;
				fcu_data_buffer.h2_data_buffer.h2_pressure_advance_set_value = 0;
				fcu_data_buffer.h2_data_buffer.h2_pressure_pid2_advance_time = 200;
				fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid2.is_enble_pid = 0;
				fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pwm_dutyfactor = 0;
				//关闭氢气尾排
				fcu_data_buffer.h2_data_buffer.h2_is_enable_outlet_valve = 0;

				//切换到停止9状态，（控制状态：停止，	工作状态：停止，	故障等级：正常）
				p_control_policy_total_manager->working_control_mode = working_control_stop9;
				p_control_policy_total_manager->working_status_mode = working_status_stoping;
				p_control_policy_total_manager->working_alarm_mode = working_normal;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;

				//半自动模式，单步运行（运行一次之后会切换到手动，然后就不会运行了，必须再次切换到半自动模式才能运行）
				if(p_control_policy_total_manager->fcu_system_running_mode == system_running_semi_auto)
				{
					p_control_policy_total_manager->fcu_system_running_mode = system_running_manual;
				}
			}
		}
	}

	return error_code;
}


//fcu主控，停止9的算法，按照时序停止fc，最终进入等待阶段
enum Error_code Control_Policy_Total_Manager_for_stop9(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->fcu_system_running_mode && p_control_policy_total_manager->working_control_mode == working_control_stop9)
	{
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_1S)
		{
			//打开负载小电阻，前面已经提前打开了 
			fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_is_enble_load_resistance = 1;

			//切换到停止10状态，（控制状态：停止，	工作状态：停止，	故障等级：正常）
			p_control_policy_total_manager->working_control_mode = working_control_stop10;
			p_control_policy_total_manager->working_status_mode = working_status_stoping;
			p_control_policy_total_manager->working_alarm_mode = working_normal;
			p_control_policy_total_manager->fcu_updata_event_time = system_time;

			//半自动模式，单步运行（运行一次之后会切换到手动，然后就不会运行了，必须再次切换到半自动模式才能运行）
			if(p_control_policy_total_manager->fcu_system_running_mode == system_running_semi_auto)
			{
				p_control_policy_total_manager->fcu_system_running_mode = system_running_manual;
			}

		}
	}

	return error_code;
}


//fcu主控，停止10的算法，按照时序停止fc，最终进入等待阶段
enum Error_code Control_Policy_Total_Manager_for_stop10(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->fcu_system_running_mode && p_control_policy_total_manager->working_control_mode == working_control_stop10)
	{
		//超时算法，70s内，判断电压是否小于16V
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time < FCU_SYSTEM_CHANGE_MODE_DELAY_70S)
		{
			//判断电压是否小于16V
			if(fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_voltage < 39)
			{
				//切断负载小电阻
				fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_is_enble_load_resistance = 0;

				//切换到停止11状态，（控制状态：停止，	工作状态：停止，	故障等级：正常）
				p_control_policy_total_manager->working_control_mode = working_control_stop11;
				p_control_policy_total_manager->working_status_mode = working_status_stoping;
				p_control_policy_total_manager->working_alarm_mode = working_normal;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;

				//半自动模式，单步运行（运行一次之后会切换到手动，然后就不会运行了，必须再次切换到半自动模式才能运行）
				if(p_control_policy_total_manager->fcu_system_running_mode == system_running_semi_auto)
				{
					p_control_policy_total_manager->fcu_system_running_mode = system_running_manual;
				}
			}
			//否则继续等待，
		}
		else
		{
		    //切断负载小电阻
			fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_is_enble_load_resistance = 0;
				
			p_control_policy_total_manager->working_control_mode = working_control_fault10;
			p_control_policy_total_manager->working_status_mode = working_status_error;
			p_control_policy_total_manager->working_alarm_mode = one_level_fault;
			p_control_policy_total_manager->working_FCU_error_code = Galvanic_pile_voltage_statas_error1;	//电堆电压在停机的时候没有降为16，可能是小电阻的继电器故障（一级故障）
			p_control_policy_total_manager->working_FCU_error_control_mode = working_control_stop10;
			p_control_policy_total_manager->working_error_count++; 
			p_control_policy_total_manager->fcu_updata_event_time = system_time;

		}

	}

	return error_code;
}


//fcu主控，停止11的算法，按照时序停止fc，最终进入等待阶段
enum Error_code Control_Policy_Total_Manager_for_stop11(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->fcu_system_running_mode && p_control_policy_total_manager->working_control_mode == working_control_stop11)
	{
		//超时判断，在10s内，判断电压是否反弹，超过32V
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time < FCU_SYSTEM_CHANGE_MODE_DELAY_10S)
		{
			//判断电压是否反弹
			if(fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_voltage > 52
				&& p_control_policy_total_manager->galvanic_pile_load_resistance_switch_count < 3)
			{
				//注意了，这里从stop11回退到stop10，重新打开小电阻，进行降电压。

				//打开负载小电阻 
				fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_is_enble_load_resistance = 1;

				//小负载的切换次数  +1
				p_control_policy_total_manager->galvanic_pile_load_resistance_switch_count++;

				//切换到停止10状态，（控制状态：停止，	工作状态：停止，	故障等级：正常）
				p_control_policy_total_manager->working_control_mode = working_control_stop10;
				p_control_policy_total_manager->working_status_mode = working_status_stoping;
				p_control_policy_total_manager->working_alarm_mode = working_normal;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;

				//半自动模式，单步运行（运行一次之后会切换到手动，然后就不会运行了，必须再次切换到半自动模式才能运行）
				if(p_control_policy_total_manager->fcu_system_running_mode == system_running_semi_auto)
				{
					p_control_policy_total_manager->fcu_system_running_mode = system_running_manual;
				}
			}
			//否则继续等待，
		}
		else
		{
			//小负载的切换次数  清除
			p_control_policy_total_manager->galvanic_pile_load_resistance_switch_count = 0;
			//切换到停止12状态，（控制状态：停止，	工作状态：停止，	故障等级：正常）
			p_control_policy_total_manager->working_control_mode = working_control_stop12;
			p_control_policy_total_manager->working_status_mode = working_status_stoping;
			p_control_policy_total_manager->working_alarm_mode = working_normal;
			p_control_policy_total_manager->fcu_updata_event_time = system_time;

			//半自动模式，单步运行（运行一次之后会切换到手动，然后就不会运行了，必须再次切换到半自动模式才能运行）
			if(p_control_policy_total_manager->fcu_system_running_mode == system_running_semi_auto)
			{
				p_control_policy_total_manager->fcu_system_running_mode = system_running_manual;
			}
		}
	}

	return error_code;
}


//fcu主控，停止12的算法，按照时序停止fc，最终进入等待阶段
enum Error_code Control_Policy_Total_Manager_for_stop12(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->fcu_system_running_mode && p_control_policy_total_manager->working_control_mode == working_control_stop12)
	{
		//超时判断，在60s内，判断散热系统的温度 是否降到45度
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time < FCU_SYSTEM_CHANGE_MODE_DELAY_100S)
		{
			//电堆入口水温    电堆出口水温    空压机出口水温    三合一水泵出口水温
			if(fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_inlet1 <= 45 && 
				fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_outlet1 <= 45 &&
				fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_compressor_outlet <= 45 &&
				fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_pump_outlet <= 45)
			{
				//关闭风扇和水泵
				//水温的pid，在stop1就已经关了
				fcu_data_buffer.water_for_pile_data_buffer.water_pump_pwm_dutyfactor1 = 0;
				fcu_data_buffer.water_for_pile_data_buffer.water_fan_pwm_dutyfactor1 = 0;
				fcu_data_buffer.water_for_pile_data_buffer.water_fan_pwm_dutyfactor2 = 0;
				fcu_data_buffer.water_for_compressor_data_bufferr.water_pump_pwm_dutyfactor = 0;
				fcu_data_buffer.water_for_compressor_data_bufferr.water_fan_pwm_dutyfactor = 0;

				//切换到待机状态，（控制状态：停止，	工作状态：停止，	故障等级：正常）
				p_control_policy_total_manager->working_control_mode = working_control_wait;
				p_control_policy_total_manager->working_status_mode = working_status_wait;
				p_control_policy_total_manager->working_alarm_mode = working_normal;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;

				//半自动模式，单步运行（运行一次之后会切换到手动，然后就不会运行了，必须再次切换到半自动模式才能运行）
				if(p_control_policy_total_manager->fcu_system_running_mode == system_running_semi_auto)
				{
					p_control_policy_total_manager->fcu_system_running_mode = system_running_manual;
				}
			}
			//否则继续等待，
		}
		else
		{
		    //关闭风扇和水泵
			//水温的pid，在stop1就已经关了
			fcu_data_buffer.water_for_pile_data_buffer.water_pump_pwm_dutyfactor1 = 0;
			fcu_data_buffer.water_for_pile_data_buffer.water_fan_pwm_dutyfactor1 = 0;
			fcu_data_buffer.water_for_pile_data_buffer.water_fan_pwm_dutyfactor2 = 0;
			fcu_data_buffer.water_for_compressor_data_bufferr.water_pump_pwm_dutyfactor = 0;
			fcu_data_buffer.water_for_compressor_data_bufferr.water_fan_pwm_dutyfactor = 0;
				
			//注意了，实测在夏天常温30度的时候，降温效果很差。100s无法把水温降到45度，所以故障判断就不用45，而是55	
			//电堆入口水温
			if(fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_inlet1 > 55)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault_wait;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = Water_temperature_pile_inlet_over_error1;				//电堆入口水温  过温（一级故障）
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_stop12;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			//电堆出口水温
			else if(fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_outlet1 > 55)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault_wait;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = Water_temperature_pile_outlet_over_error1;					//电堆出口水温  过温（一级故障）
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_stop12;
				p_control_policy_total_manager->working_error_count++; 
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			//空压机出口水温
			else if(fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_compressor_outlet > 55)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault_wait;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = Water_temperature_compressor_outlet_over_error1;	//空压机出口水温  过温（一级故障）
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_stop12;
				p_control_policy_total_manager->working_error_count++;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			//三合一水泵出口水温
			else if(fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_pump_outlet > 55)
			{
				p_control_policy_total_manager->working_control_mode = working_control_fault_wait;
				p_control_policy_total_manager->working_status_mode = working_status_error;
				p_control_policy_total_manager->working_alarm_mode = one_level_fault;
				p_control_policy_total_manager->working_FCU_error_code = Water_temperature_pump_outlet_over_error1;		//三合一水泵出口水温  过温（一级故障）
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_stop12;
				p_control_policy_total_manager->working_error_count++;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			//就有可能上一次判断大于45，然后下一次就小于45了。
			else
			{
				//切换到待机状态，（控制状态：停止，	工作状态：停止，	故障等级：正常）
				p_control_policy_total_manager->working_control_mode = working_control_wait;
				p_control_policy_total_manager->working_status_mode = working_status_wait;
				p_control_policy_total_manager->working_alarm_mode = working_normal;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;

				//半自动模式，单步运行（运行一次之后会切换到手动，然后就不会运行了，必须再次切换到半自动模式才能运行）
				if(p_control_policy_total_manager->fcu_system_running_mode == system_running_semi_auto)
				{
					p_control_policy_total_manager->fcu_system_running_mode = system_running_manual;
				}
			}


		}
	}

	return error_code;
}



//fcu主控，故障停机的算法，目前是直接跳保护。
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
			//如果是在自检阶段就故障了，那就直接跳保护，   否则就要走故障停机的流程
			if(p_control_policy_total_manager->working_FCU_error_control_mode <= working_control_check3 )
			{    zxc[0] += 1;
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


//fcu主控，故障停机1的算法，按照错误码停止fc，最终进入故障停机阶段
enum Error_code Control_Policy_Total_Manager_for_fault1(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->working_control_mode == working_control_fault1)
	{
		//故障停机没有什么保护判断，但是停机速度要快，所以延时缩短，只保留设备的响应时间即可。并不需要等到设备响应并改变状态。
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_1S)
		{   zxc[1] += 1;
			//不用判断电流了，故障停机大部分都是带载急停的，所以直接停止就好了

			//关闭散热系统的风扇pid使能
			fcu_data_buffer.water_for_pile_data_buffer.water_temperature_fan_pid1.is_enble_pid = 0;
			fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_fan_pid.is_enble_pid = 0;	

			//开启氢气尾排，常开。
			fcu_data_buffer.h2_data_buffer.h2_is_enable_outlet_valve = 1;
			fcu_data_buffer.h2_data_buffer.h2_pid_mode = 2;
			fcu_data_buffer.h2_data_buffer.h2_pressure_advance_current_value = 0;

			p_control_policy_total_manager->working_control_mode = working_control_fault2;
			p_control_policy_total_manager->fcu_updata_event_time = system_time;

		}
	} 

	return error_code;
}




//fcu主控，故障停机2的算法，按照错误码停止fc，最终进入故障停机阶段
enum Error_code Control_Policy_Total_Manager_for_fault2(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->working_control_mode == working_control_fault2)
	{
		//故障停机没有什么保护判断，但是停机速度要快，所以延时缩短，只保留设备的响应时间即可。并不需要等到设备响应并改变状态。
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_1S)
		{    zxc[2] += 1;
			//调整pid1和pid2
			fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid1.Kp = PID1_KP;
			fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid1.Ki = PID1_KI;
			fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid1.Kd = PID1_KD;
			fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid2.Kp = PID2_KP;
			fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid2.Ki = PID2_KI;
			fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid2.Kd = PID2_KD;

			//切断负载，关闭电堆输出继电器
			fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_is_enble_output = 0;

			//45kw新方案，提前开启小电阻负载，
			fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_is_enble_load_resistance = 1;

			p_control_policy_total_manager->working_control_mode = working_control_fault3;
			p_control_policy_total_manager->fcu_updata_event_time = system_time;

		}
	}

	return error_code;
}



//fcu主控，故障停机3的算法，按照错误码停止fc，最终进入故障停机阶段
enum Error_code Control_Policy_Total_Manager_for_fault3(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->working_control_mode == working_control_fault3)
	{
		//故障停机没有什么保护判断，但是停机速度要快，所以延时缩短，只保留设备的响应时间即可。并不需要等到设备响应并改变状态。
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_1S)
		{
			//氢路故障，并且在已经开启比例阀的情况下，那么就直接关掉比例阀，（出口氢压和尾排氢压 的故障不管）
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
				//关闭氢气入口阀，切断氢气来源
				fcu_data_buffer.h2_data_buffer.h2_inlet_valve = 0;

				//关闭pid1和pid2，关闭比例阀，pid2， 关闭比例阀pwm，  
				fcu_data_buffer.h2_data_buffer.h2_pid_mode = 2;
				fcu_data_buffer.h2_data_buffer.h2_pressure_advance_set_value = 0;
				fcu_data_buffer.h2_data_buffer.h2_pressure_pid2_advance_time = 200;
				fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid2.is_enble_pid = 0;
				fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid1.is_enble_pid = 0;
				fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pwm_dutyfactor = 0;

				//降低目标氢压
				fcu_data_buffer.h2_data_buffer.h2_pressure_target_value = 50;
			}
			//否则就只降低目标氢压 到50kpa
			else
			{    zxc[3] += 2;
				//注意了，不要开启氢路的使能                                                                         
				//降低目标氢压
				fcu_data_buffer.h2_data_buffer.h2_pressure_target_value = 50;                                 
			}


			//空压机故障和三合一散热系统故障，并且在已经开启空压机的情况下，那么就直接关掉空压机
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
				//同时关闭空压机和空气尾排
				fcu_data_buffer.air_data_buffer.air_compressor_enable = 0;
				fcu_data_buffer.air_data_buffer.air_is_enable_outlet_valve = 0;
				//降低空压机转速。
				fcu_data_buffer.air_data_buffer.air_compressor_speed_pid.is_enble_pid = 0;
				fcu_data_buffer.air_data_buffer.air_rate_of_flow_target = 960;
				fcu_data_buffer.air_data_buffer.air_compressor_speed_setpoint = 20000;
			}
			//三合一散热系统 水压 故障，并且在已经开启空压机的情况下，那么就直接关掉空压机，并且关掉三合一的水泵和风扇
			else if(p_control_policy_total_manager->working_FCU_error_code == Water_pressure_compressor_outlet_under_error1
				&& p_control_policy_total_manager->working_FCU_error_control_mode >= working_control_start8 )
			{   zxc[3] += 20;            
				//同时关闭空压机和空气尾排
				fcu_data_buffer.air_data_buffer.air_compressor_enable = 0;
				fcu_data_buffer.air_data_buffer.air_is_enable_outlet_valve = 0;
				//降低空压机转速。
				fcu_data_buffer.air_data_buffer.air_compressor_speed_pid.is_enble_pid = 0;
				fcu_data_buffer.air_data_buffer.air_rate_of_flow_target = 960;
				fcu_data_buffer.air_data_buffer.air_compressor_speed_setpoint = 20000;
				//关掉三合一的水泵和风扇
				fcu_data_buffer.water_for_compressor_data_bufferr.water_pump_pwm_dutyfactor = 0;
				fcu_data_buffer.water_for_compressor_data_bufferr.water_fan_pwm_dutyfactor = 0;
			}
			//否则就只降低空压机转速。
			else
			{   zxc[3] += 30;
				//注意了，不要开启空压机的使能
				//降低空压机转速。
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



//fcu主控，故障停机4的算法，按照错误码停止fc，最终进入故障停机阶段
enum Error_code Control_Policy_Total_Manager_for_fault4(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->working_control_mode == working_control_fault4)
	{
		//故障停机没有什么保护判断，但是停机速度要快，所以延时缩短，只保留设备的响应时间即可。并不需要等到设备响应并改变状态。
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_1S)
		{
			//如果fault3氢路故障，那就不用吹扫了
			if(fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid2.is_enble_pid == 0)
			{    zxc[4] += 1;
				//fault3已经把氢路关了
				fcu_data_buffer.h2_data_buffer.h2_outlet_valve_open_time = 500;
				fcu_data_buffer.h2_data_buffer.h2_outlet_valve_close_time = 1000;
				fcu_data_buffer.h2_data_buffer.h2_is_enable_outlet_valve = 0;
			}
			//否则就进行氢路吹扫
			else 
			{    zxc[4] += 2;
				//关闭pid1，调整pid2，然后进入吹扫模式
				fcu_data_buffer.h2_data_buffer.h2_pid_mode = 2;
				fcu_data_buffer.h2_data_buffer.h2_pressure_advance_set_value = 0;
				fcu_data_buffer.h2_data_buffer.h2_pressure_pid2_advance_time = 200;

				fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid2.Kp = PID2_KP;
				fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid2.Ki = PID2_KI;
				fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid2.Kd = PID2_KD;
				//		fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pwm_dutyfactor = 0;
				fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid2.is_enble_pid = 1;
				fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid1.is_enble_pid = 0;

				//然后进入吹扫模式，氢气循环泵继续运转
				//氢气尾排由常开，变为吹扫模式。1s/0.5s
				fcu_data_buffer.h2_data_buffer.h2_outlet_valve_open_time = 500;
				fcu_data_buffer.h2_data_buffer.h2_outlet_valve_close_time = 1000;
				fcu_data_buffer.h2_data_buffer.h2_is_enable_outlet_valve = 2;
			}

			//如果fault3空压机故障和三合一散热系统故障，那就不用吹扫了
			if(fcu_data_buffer.air_data_buffer.air_compressor_enable == 0)
			{   zxc[4] += 10;
				fcu_data_buffer.air_data_buffer.air_outlet_valve_open_time = 500;
				fcu_data_buffer.air_data_buffer.air_outlet_valve_close_time = 2000;
				fcu_data_buffer.air_data_buffer.air_is_enable_outlet_valve = 0;
			}
			else
			{    zxc[4] += 20;
				//开启空气尾排，变为吹扫模式，2s/0.5s
				fcu_data_buffer.air_data_buffer.air_outlet_valve_open_time = 500;
				fcu_data_buffer.air_data_buffer.air_outlet_valve_close_time = 2000;
				fcu_data_buffer.air_data_buffer.air_is_enable_outlet_valve = 2;
			}

			//如果氢气循环泵故障，并且在已经开启氢气循环泵的情况下，那么这里就关掉氢气循环泵
			if((p_control_policy_total_manager->working_FCU_error_code == H2_circulating_pump_communication_error1 ||
				p_control_policy_total_manager->working_FCU_error_code == H2_circulating_pump_low_voltage_power_error1 ||
				p_control_policy_total_manager->working_FCU_error_code == H2_circulating_pump_working_statas_error1 ||
				p_control_policy_total_manager->working_FCU_error_code == H2_circulating_pump_actual_speed_error1 ||
				p_control_policy_total_manager->working_FCU_error_code == H2_circulating_pump_temperature_over_error1 ||
				p_control_policy_total_manager->working_FCU_error_code == H2_circulating_pump_temperature_under_error1 )
				&& p_control_policy_total_manager->working_FCU_error_control_mode >= working_control_start5 )
			{    zxc[4] += 100;
				//关掉氢气循环泵
				fcu_data_buffer.h2_data_buffer.h2_circulating_pump_enable_pump = 0;
			}
			else
			{    zxc[4] += 200;
				//氢气循环泵在较大的转速下运行，要把循环泵里面的水吹扫出来。
				fcu_data_buffer.h2_data_buffer.h2_circulating_pump_speed_setpoint = H2_CIRCULATING_PUMP_SPEED_SETPOINT_3000;
			}

			p_control_policy_total_manager->working_control_mode = working_control_fault5;
			p_control_policy_total_manager->fcu_updata_event_time = system_time;
		}
	}

	return error_code;
}


//fcu主控，故障停机5的算法，按照错误码停止fc，最终进入故障停机阶段
enum Error_code Control_Policy_Total_Manager_for_fault5(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->working_control_mode == working_control_fault5)
	{
		//故障停机没有什么保护判断，但是停机速度要快，所以延时缩短，只保留设备的响应时间即可。并不需要等到设备响应并改变状态。
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_1S)
		{
			//如果电堆散热系统 水压故障，在水泵开启的情况下，那就水泵和风扇直接关掉，（只判断水压，水温在下面判断）
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
			//否则就水泵和风扇全开，加快散热。
			else
			{
				//电堆入口水温    电堆出口水温    
				if(fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_inlet1 > 45 || 
					fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_outlet1 > 45 )
				{    zxc[5] += 2;
					//水泵和风扇全开，加快散热。
					fcu_data_buffer.water_for_pile_data_buffer.water_pump_pwm_dutyfactor1 = 9000;
					fcu_data_buffer.water_for_pile_data_buffer.water_fan_pwm_dutyfactor1 = 9000;
					fcu_data_buffer.water_for_pile_data_buffer.water_fan_pwm_dutyfactor2 = 9000;
				}
			}


			//如果电堆散热系统 水压故障，在水泵开启的情况下，那就水泵和风扇直接关掉，（只判断水压，水温在下面判断）
			if(p_control_policy_total_manager->working_FCU_error_code == Water_pressure_compressor_outlet_under_error1
				&& p_control_policy_total_manager->working_FCU_error_control_mode >= working_control_start2 )
			{     zxc[5] += 10;
				fcu_data_buffer.water_for_compressor_data_bufferr.water_pump_pwm_dutyfactor = 0;
				fcu_data_buffer.water_for_compressor_data_bufferr.water_fan_pwm_dutyfactor = 0;
			}
			//否则就水泵和风扇全开，加快散热。
			else
			{
				//空压机出口水温    三合一水泵出口水温
				if(fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_compressor_outlet > 45 ||
					fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_pump_outlet > 45)
				{   zxc[5] += 20;
					//水泵和风扇全开，加快散热。
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


//fcu主控，故障停机6的算法，按照错误码停止fc，最终进入故障停机阶段
enum Error_code Control_Policy_Total_Manager_for_fault6(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->working_control_mode == working_control_fault6)
	{
		//故障停机没有什么保护判断，但是停机速度要快，所以延时缩短，只保留设备的响应时间即可。并不需要等到设备响应并改变状态。

		//如果前面判断需要吹扫，那么这里延时20s，等待氢路和空路吹扫，              否则就直接1s过
		if(fcu_data_buffer.h2_data_buffer.h2_is_enable_outlet_valve == 2  ||
			fcu_data_buffer.air_data_buffer.air_is_enable_outlet_valve == 2)
		{
			if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_20S)
			{     zxc[6] += 1;
				//关闭氢气循环泵（无论前面是否提前关闭，这里再关一次）
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
				//关闭氢气循环泵（无论前面是否提前关闭，这里再关一次）
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


//fcu主控，故障停机7的算法，按照错误码停止fc，最终进入故障停机阶段
enum Error_code Control_Policy_Total_Manager_for_fault7(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->working_control_mode == working_control_fault7)
	{
		//故障停机没有什么保护判断，但是停机速度要快，所以延时缩短，只保留设备的响应时间即可。并不需要等到设备响应并改变状态。
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_1S)
		{   zxc[7] += 1;
			//关闭氢气入口阀，切断氢气来源（无论前面是否提前关闭，这里再关一次）
			fcu_data_buffer.h2_data_buffer.h2_inlet_valve = 0;

			//20181218这里常开氢气尾排阀，快速将氢气排出，
			//个人感觉啊，之前是1/0.5s的吹扫模式，在这里关闭氢气入口阀，切断氢气来源之后，吹扫变不成立了。
			//目的在于排出氢气，因此直接常开氢气尾排阀，快速将氢气排出，
			fcu_data_buffer.h2_data_buffer.h2_is_enable_outlet_valve = 1;
				
			//同时关闭空压机和空气尾排（无论前面是否提前关闭，这里再关一次）
			fcu_data_buffer.air_data_buffer.air_compressor_enable = 0;
			fcu_data_buffer.air_data_buffer.air_is_enable_outlet_valve = 0;

			p_control_policy_total_manager->working_control_mode = working_control_fault8;
			p_control_policy_total_manager->fcu_updata_event_time = system_time;
		}
	}

	return error_code;
}



//fcu主控，故障停机8的算法，按照错误码停止fc，最终进入故障停机阶段
enum Error_code Control_Policy_Total_Manager_for_fault8(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->working_control_mode == working_control_fault8)
	{
		//如果前面判断需要吹扫，那么这里延时5s，等待氢压降下来，    否则就直接1s过
		if(fcu_data_buffer.h2_data_buffer.h2_is_enable_outlet_valve == 2 )
		{
			//故障停机没有什么保护判断，但是停机速度要快，所以延时缩短，只保留设备的响应时间即可。并不需要等到设备响应并改变状态。
			if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_5S)
			{    zxc[8] += 1;
				//关闭比例阀，pid2， 关闭比例阀pwm，    （无论前面是否提前关闭，这里再关一次）
				fcu_data_buffer.h2_data_buffer.h2_pid_mode = 2;
				fcu_data_buffer.h2_data_buffer.h2_pressure_advance_set_value = 0;
				fcu_data_buffer.h2_data_buffer.h2_pressure_pid2_advance_time = 200;
				fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid2.is_enble_pid = 0;
				fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pwm_dutyfactor = 0;
			
				//关闭氢气尾排（无论前面是否提前关闭，这里再关一次）
				//注意了，如果氢路故障，那么氢气尾排常开。保护电堆。
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
			//故障停机没有什么保护判断，但是停机速度要快，所以延时缩短，只保留设备的响应时间即可。并不需要等到设备响应并改变状态。
			if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_1S)
			{    zxc[8] += 2;
				//关闭比例阀，pid2， 关闭比例阀pwm，    （无论前面是否提前关闭，这里再关一次）
				fcu_data_buffer.h2_data_buffer.h2_pid_mode = 2;
				fcu_data_buffer.h2_data_buffer.h2_pressure_advance_set_value = 0;
				fcu_data_buffer.h2_data_buffer.h2_pressure_pid2_advance_time = 200;
				fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid2.is_enble_pid = 0;
				fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pwm_dutyfactor = 0;
			
				//关闭氢气尾排（无论前面是否提前关闭，这里再关一次）
				//注意了，如果氢路故障，那么氢气尾排常开。保护电堆。
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


//fcu主控，故障停机9的算法，按照错误码停止fc，最终进入故障停机阶段
enum Error_code Control_Policy_Total_Manager_for_fault9(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->working_control_mode == working_control_fault9)
	{
		//故障停机没有什么保护判断，但是停机速度要快，所以延时缩短，只保留设备的响应时间即可。并不需要等到设备响应并改变状态。
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_1S)
		{
			//只有在电压大于52的时候，就打开负载小电阻，（因为有可能还没发出电就故障了。）
			if(fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_voltage > 52)
			{      zxc[9] += 1;
				//打开负载小电阻 
				fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_is_enble_load_resistance = 1;
			}
			p_control_policy_total_manager->working_control_mode = working_control_fault10;
			p_control_policy_total_manager->fcu_updata_event_time = system_time;
		}
	}

	return error_code;
}


//fcu主控，故障停机10的算法，按照错误码停止fc，最终进入故障停机阶段
enum Error_code Control_Policy_Total_Manager_for_fault10(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->working_control_mode == working_control_fault10)
	{
		//如果开启了小电阻来降低电压，那么就超时70s，  否则就直接1s过
		if(fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_is_enble_load_resistance == 1)
		{
			//超时算法，70s内，判断电压是否小于16V
			//故障停机没有什么保护判断，但是停机速度要快，所以延时缩短，只保留设备的响应时间即可。并不需要等到设备响应并改变状态。
			if(system_time - p_control_policy_total_manager->fcu_updata_event_time < FCU_SYSTEM_CHANGE_MODE_DELAY_70S)
			{   
				//判断电压是否小于16V
				if(fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_voltage < 39)
				{    zxc[10] += 20;
					//切断负载小电阻
					fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_is_enble_load_resistance = 0;

					p_control_policy_total_manager->working_control_mode = working_control_fault11;
					p_control_policy_total_manager->fcu_updata_event_time = system_time;
				}
				//否则继续等待，
			}
			else
			{    zxc[10] += 30;
				//切断负载小电阻
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


//fcu主控，故障停机11的算法，按照错误码停止fc，最终进入故障停机阶段
enum Error_code Control_Policy_Total_Manager_for_fault11(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->working_control_mode == working_control_fault11)
	{
		//35V~50V之间，则表示曾经开启过小电阻，那么就做10s的超时判断，    否则直接1s过
		if(fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_voltage > 35 
			&& fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_voltage < 50  )
		{
			//故障停机没有什么保护判断，但是停机速度要快，所以延时缩短，只保留设备的响应时间即可。并不需要等到设备响应并改变状态。
			//超时判断，在10s内，判断电压是否反弹，超过32V
			if(system_time - p_control_policy_total_manager->fcu_updata_event_time < FCU_SYSTEM_CHANGE_MODE_DELAY_10S)
			{   
				//判断电压是否反弹
				if(fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_voltage > 52
					&& p_control_policy_total_manager->galvanic_pile_load_resistance_switch_count < 3)
				{     zxc[11] += 20;
					//注意了，这里从stop11回退到stop10，重新打开小电阻，进行降电压。

					//打开负载小电阻 
					fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_is_enble_load_resistance = 1;

					//小负载的切换次数  +1
					p_control_policy_total_manager->galvanic_pile_load_resistance_switch_count++;

					//切换到停止10状态，（控制状态：停止，	工作状态：停止，	故障等级：正常）
					p_control_policy_total_manager->working_control_mode = working_control_fault10;
					p_control_policy_total_manager->fcu_updata_event_time = system_time;
				}
				//否则继续等待，
			}
			else
			{     zxc[11] += 30;
				//小负载的切换次数  清除
				p_control_policy_total_manager->galvanic_pile_load_resistance_switch_count = 0;
				//切换到停止12状态，（控制状态：停止，	工作状态：停止，	故障等级：正常）
				p_control_policy_total_manager->working_control_mode = working_control_fault12;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
		}
		//否则就是降电压有问题了。那就直接过
		else
		{
			if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_1S)
			{     zxc[11] += 40;
				//小负载的切换次数  清除
				p_control_policy_total_manager->galvanic_pile_load_resistance_switch_count = 0;
				//切换到停止12状态，（控制状态：停止，	工作状态：停止，	故障等级：正常）
				p_control_policy_total_manager->working_control_mode = working_control_fault12;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
		}

	}

	return error_code;
}


//fcu主控，故障停机12的算法，按照错误码停止fc，最终进入故障停机阶段
enum Error_code Control_Policy_Total_Manager_for_fault12(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->working_control_mode == working_control_fault12)
	{

		//超时判断，在60s内，判断散热系统的温度 是否降到45度
		//故障停机没有什么保护判断，但是停机速度要快，所以延时缩短，只保留设备的响应时间即可。并不需要等到设备响应并改变状态。
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time < FCU_SYSTEM_CHANGE_MODE_DELAY_100S)
		{
			//注意了，错误码只有一个，也就是说，至少有一个散热系统是好的。那么必须要进行  超时60s的判断
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
				//如果电堆的散热系统有问题，那就只判断三合一的散热系统
				if(fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_compressor_outlet <= 45 &&
					fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_pump_outlet <= 45)
				{    zxc[12] += 20;
					//关闭风扇和水泵
					//水温的pid，在fault1就已经关了
	    			fcu_data_buffer.water_for_pile_data_buffer.water_pump_pwm_dutyfactor1 = 0;
	    			fcu_data_buffer.water_for_pile_data_buffer.water_fan_pwm_dutyfactor1 = 0;
	    			fcu_data_buffer.water_for_pile_data_buffer.water_fan_pwm_dutyfactor2 = 0;
	    			fcu_data_buffer.water_for_compressor_data_bufferr.water_pump_pwm_dutyfactor = 0;
	    			fcu_data_buffer.water_for_compressor_data_bufferr.water_fan_pwm_dutyfactor = 0;

					//切换到待机状态，（控制状态：停止，	工作状态：停止，	故障等级：正常）
					p_control_policy_total_manager->working_control_mode = working_control_fault_wait;
					p_control_policy_total_manager->fcu_updata_event_time = system_time;
				}
				//否则继续等待，
			}
			else if(p_control_policy_total_manager->working_FCU_error_code == Water_temperature_compressor_outlet_over_error1 ||
				p_control_policy_total_manager->working_FCU_error_code == Water_temperature_compressor_outlet_under_error1 ||
				p_control_policy_total_manager->working_FCU_error_code == Water_temperature_pump_outlet_over_error1 ||
				p_control_policy_total_manager->working_FCU_error_code == Water_temperature_pump_outlet_under_error1 ||
				p_control_policy_total_manager->working_FCU_error_code == Water_pressure_compressor_outlet_under_error1)
			{     
				//如果三合一的散热系统有问题，那就只判断电堆的散热系统
				//电堆入口水温    电堆出口水温    空压机出口水温    三合一水泵出口水温
				if(fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_inlet1 <= 45 && 
					fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_outlet1 <= 45 )
				{   zxc[12] += 40;
					//关闭风扇和水泵
					//水温的pid，在fault1就已经关了
	    			fcu_data_buffer.water_for_pile_data_buffer.water_pump_pwm_dutyfactor1 = 0;
	    			fcu_data_buffer.water_for_pile_data_buffer.water_fan_pwm_dutyfactor1 = 0;
	    			fcu_data_buffer.water_for_pile_data_buffer.water_fan_pwm_dutyfactor2 = 0;
	    			fcu_data_buffer.water_for_compressor_data_bufferr.water_pump_pwm_dutyfactor = 0;
	    			fcu_data_buffer.water_for_compressor_data_bufferr.water_fan_pwm_dutyfactor = 0;

					//切换到待机状态，（控制状态：停止，	工作状态：停止，	故障等级：正常）
					p_control_policy_total_manager->working_control_mode = working_control_fault_wait;
					p_control_policy_total_manager->fcu_updata_event_time = system_time;
				}
				//否则继续等待，
			}
			//如果2个散热系统都没有问题，那就要判断全部了
			else
			{
				//电堆入口水温    电堆出口水温    空压机出口水温    三合一水泵出口水温
				if(fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_inlet1 <= 45 && 
					fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_outlet1 <= 45 &&
					fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_compressor_outlet <= 45 &&
					fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_pump_outlet <= 45)
				{     zxc[12] += 5;
					//关闭风扇和水泵
					//need programe  水温的pid
					fcu_data_buffer.water_for_pile_data_buffer.water_pump_pwm_dutyfactor1 = 0;
	    		fcu_data_buffer.water_for_pile_data_buffer.water_fan_pwm_dutyfactor1 = 0;
	    		fcu_data_buffer.water_for_pile_data_buffer.water_fan_pwm_dutyfactor2 = 0;
	    	  fcu_data_buffer.water_for_compressor_data_bufferr.water_pump_pwm_dutyfactor = 0;
	    		fcu_data_buffer.water_for_compressor_data_bufferr.water_fan_pwm_dutyfactor = 0;

					//切换到待机状态，（控制状态：停止，	工作状态：停止，	故障等级：正常）
					p_control_policy_total_manager->working_control_mode = working_control_fault_wait;
					p_control_policy_total_manager->fcu_updata_event_time = system_time;
				}
				//否则继续等待，
			}
		}
		else                                                                      
		{     zxc[12] += 60;
			//关闭风扇和水泵
			//need programe  水温的pid
			fcu_data_buffer.water_for_pile_data_buffer.water_pump_pwm_dutyfactor1 = 0;
	  	fcu_data_buffer.water_for_pile_data_buffer.water_fan_pwm_dutyfactor1 = 0;
	  	fcu_data_buffer.water_for_pile_data_buffer.water_fan_pwm_dutyfactor2 = 0;
	    fcu_data_buffer.water_for_compressor_data_bufferr.water_pump_pwm_dutyfactor = 0;
	    fcu_data_buffer.water_for_compressor_data_bufferr.water_fan_pwm_dutyfactor = 0;

			//切换到待机状态，（控制状态：停止，	工作状态：停止，	故障等级：正常）
			p_control_policy_total_manager->working_control_mode = working_control_fault_wait;
			p_control_policy_total_manager->fcu_updata_event_time = system_time;

		}
	}

	return error_code;
}


//fcu主控，//故障停机的等待状态，复位消息即可恢复到wait
enum Error_code Control_Policy_Total_Manager_for_fault_wait(struct Control_Policy_Total_Manager  * p_control_policy_total_manager)
{
	enum Error_code error_code = Succeed;

	if(p_control_policy_total_manager == NULL)
	{return Pointer_is_null;}

	if(p_control_policy_total_manager->working_control_mode == working_control_fault_wait)
	{
		if(system_time - p_control_policy_total_manager->fcu_updata_event_time > FCU_SYSTEM_CHANGE_MODE_DELAY_100MS)
		{
			//收到复位命令，要求  急停为0，复位为1
			if(fcu_data_buffer.galvanic_pile_data_buffer.fcu_reset_enable == 1 &&
			    fcu_data_buffer.galvanic_pile_data_buffer.fcu_stutter_stop_enable == 0)
			{    zxc[13] += 1;
				fcu_data_buffer.galvanic_pile_data_buffer.fcu_reset_enable = 0;
				fcu_data_buffer.galvanic_pile_data_buffer.fcu_start_enable = 0;

				//如果允许复位，从  故障停机的等待状态  跳到  自检3阶段
				p_control_policy_total_manager->working_control_mode = working_control_wait;
				p_control_policy_total_manager->working_status_mode = working_status_wait;
				p_control_policy_total_manager->working_alarm_mode = working_normal;
				p_control_policy_total_manager->working_FCU_error_code = Succeed;
				p_control_policy_total_manager->working_FCU_error_control_mode = working_control_wait;
				p_control_policy_total_manager->working_error_count = 0;
				p_control_policy_total_manager->fcu_updata_event_time = system_time;
			}
			//否则，就一直等待启动命令
		}
	}

	return error_code;
}			







//判断2个值是否约等于，误差在10%则返回Succeed，否则返回Failed
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

//判断2个值是否约等于，误差在10%则返回Succeed，否则返回Failed
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


//按照优先级集成告警等级。（）
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










