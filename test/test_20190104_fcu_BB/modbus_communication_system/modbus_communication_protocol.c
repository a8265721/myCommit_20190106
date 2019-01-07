/*
can_communication_system 本模块是can通信系统
功能：配置can，并且收发数据。
用法：
其他模块直接包含本模块，然后作为函数的返回值。
上层通过分析错误码来判断函数的执行情况。
*/ 
//-----------------------------------------------------------------------------------------------




#include "modbus_communication_protocol.h"

#include "error_system.h"
#include "pit.h"
#include"data_buff.h"                           

int hushui1_test=0; 



struct FCU_modbus_tatal_manager_data  fcu_modbus_tatal_manager_data;




//1.1氢气数据信息
//氢气数据信息//初始化

enum Error_code Hydrogen_detective_data_init(struct Hydrogen_detective_data *  p_Hydrogen_detective_data)
{
	enum Error_code error_code = Succeed;
	int i =0;
	
	if(p_Hydrogen_detective_data == NULL )
	{return Pointer_is_null;}
	
	
	p_Hydrogen_detective_data->updata_event_time = system_time;
	p_Hydrogen_detective_data->send_message_time_max = MODBUS_232_SEND_MESSAGE_TIME_MAX;	
	p_Hydrogen_detective_data->direction_data_transmission = 0xbb;
	p_Hydrogen_detective_data->function_code = 0x01;       
	p_Hydrogen_detective_data->data_length = 117;
	p_Hydrogen_detective_data->h2_pressure_proportional_valve_front = 0;
	p_Hydrogen_detective_data->h2_pressure_proportional_valve_rear = 0;
	p_Hydrogen_detective_data->h2_pressure_pile_inlet = 0;
	p_Hydrogen_detective_data->h2_pressure_pile_outlet = 0;
	p_Hydrogen_detective_data->h2_pressure_tail_outlet = 0;
	p_Hydrogen_detective_data->h2_inlet_valve = 0;
	p_Hydrogen_detective_data->h2_outlet_valve = 0;
	p_Hydrogen_detective_data->h2_proportional_valve_pwm_dutyfactor = 0;
	p_Hydrogen_detective_data->h2_circulating_pump_enble = 0;
	p_Hydrogen_detective_data->h2_circulating_pump_working_communication_mode = 0;
	p_Hydrogen_detective_data->h2_circulating_pump_speed_setpoint = 0;
  p_Hydrogen_detective_data->h2_circulating_pump_enable_pump = 0;
  p_Hydrogen_detective_data->h2_circulating_pump_actual_mass_flow = 0;
  p_Hydrogen_detective_data->h2_circulating_pump_actual_speed = 0;
  p_Hydrogen_detective_data->h2_circulating_pump_actual_current = 0;
  p_Hydrogen_detective_data->h2_circulating_pump_actual_voltage = 0;
  p_Hydrogen_detective_data->h2_circulating_pump_actual_electronic_temperature = 0;  
  p_Hydrogen_detective_data->h2_pressure_target_value = 0;
  p_Hydrogen_detective_data->h2_pressure_real_target_value = 0;
  p_Hydrogen_detective_data->h2_pressure_advance_current_value = 0;
  p_Hydrogen_detective_data->h2_pressure_advance_set_value = 0;
  p_Hydrogen_detective_data->h2_pressure_pid1_advance_time = 0;
  p_Hydrogen_detective_data->h2_pressure_pid2_advance_time = 0;
  p_Hydrogen_detective_data->PID1_is_enble_pid = 0;
  p_Hydrogen_detective_data->PID1_Kp = 0;
  p_Hydrogen_detective_data->PID1_Ki = 0;
  p_Hydrogen_detective_data->PID1_Kd = 0;
  p_Hydrogen_detective_data->PID2_is_enble_pid = 0;
  p_Hydrogen_detective_data->PID2_Kp = 0;
  p_Hydrogen_detective_data->PID2_Ki = 0;
  p_Hydrogen_detective_data->PID2_Kd = 0;
  p_Hydrogen_detective_data->h2_pid_mode = 0;
  p_Hydrogen_detective_data->h2_is_enable_outlet_valve = 0;
  p_Hydrogen_detective_data->h2_outlet_valve_open_time = 0;
  p_Hydrogen_detective_data->h2_outlet_valve_close_time = 0;
  p_Hydrogen_detective_data->h2_pressure_fluctuate_last_max = 0;
  p_Hydrogen_detective_data->h2_pressure_fluctuate_last_min = 0;
  

	return error_code;
}



//氢气数据信息//数据解析
enum Error_code Hydrogen_detective_data_analysis(struct Modbus_Data_Buffer * p_modbus_receive_data_buffer, struct Hydrogen_detective_data *  p_Hydrogen_detective_data)
{
	enum Error_code error_code = Succeed;
	int i =0;
	
	if(p_modbus_receive_data_buffer == NULL || p_Hydrogen_detective_data == NULL)
	{return Pointer_is_null;}
		
	return error_code;
}



//氢气数据信息//数据封装
enum Error_code Hydrogen_detective_data_encapsulation( struct Hydrogen_detective_data *  p_Hydrogen_detective_data, struct Modbus_Data_Buffer * p_modbus_send_data_buffer)
{

  enum Error_code error_code = Succeed;

	if(p_Hydrogen_detective_data == NULL || p_modbus_send_data_buffer == NULL)
	{return Pointer_is_null;}
	
    p_Hydrogen_detective_data->updata_event_time = system_time;
	
  	p_modbus_send_data_buffer->direction_data_transmission = p_Hydrogen_detective_data->direction_data_transmission;
  	p_modbus_send_data_buffer->function_code = p_Hydrogen_detective_data->function_code;
  	p_modbus_send_data_buffer->data_length = p_Hydrogen_detective_data->data_length;

	
	 float_convert_four_byte(&(p_Hydrogen_detective_data->h2_pressure_proportional_valve_front),
	                        &(p_modbus_send_data_buffer->modbus_data[0]),
	                        &(p_modbus_send_data_buffer->modbus_data[1]),
                          &(p_modbus_send_data_buffer->modbus_data[2]),
                          &(p_modbus_send_data_buffer->modbus_data[3]));  
                          
                          
  float_convert_four_byte(&(p_Hydrogen_detective_data->h2_pressure_proportional_valve_rear),
	                        &(p_modbus_send_data_buffer->modbus_data[4]),
	                        &(p_modbus_send_data_buffer->modbus_data[5]),
                          &(p_modbus_send_data_buffer->modbus_data[6]),
                          &(p_modbus_send_data_buffer->modbus_data[7])); 
                          
  float_convert_four_byte(&(p_Hydrogen_detective_data->h2_pressure_pile_inlet),
	                        &(p_modbus_send_data_buffer->modbus_data[8]),
	                        &(p_modbus_send_data_buffer->modbus_data[9]),
                          &(p_modbus_send_data_buffer->modbus_data[10]),
                          &(p_modbus_send_data_buffer->modbus_data[11]));                           
                          
                           
  float_convert_four_byte(&(p_Hydrogen_detective_data->h2_pressure_pile_outlet),
	                        &(p_modbus_send_data_buffer->modbus_data[12]),
	                        &(p_modbus_send_data_buffer->modbus_data[13]),
                          &(p_modbus_send_data_buffer->modbus_data[14]),
                          &(p_modbus_send_data_buffer->modbus_data[15])); 
	
  float_convert_four_byte(&(p_Hydrogen_detective_data->h2_pressure_tail_outlet),
	                        &(p_modbus_send_data_buffer->modbus_data[16]),
	                        &(p_modbus_send_data_buffer->modbus_data[17]),
                          &(p_modbus_send_data_buffer->modbus_data[18]),
                          &(p_modbus_send_data_buffer->modbus_data[19])); 
   
   p_modbus_send_data_buffer->modbus_data[20]= p_Hydrogen_detective_data->h2_inlet_valve;
   p_modbus_send_data_buffer->modbus_data[21]= p_Hydrogen_detective_data->h2_outlet_valve;
                        
                          
	
   float_convert_four_byte(&(p_Hydrogen_detective_data->h2_proportional_valve_pwm_dutyfactor),
	                        &(p_modbus_send_data_buffer->modbus_data[22]),
	                        &(p_modbus_send_data_buffer->modbus_data[23]),
                          &(p_modbus_send_data_buffer->modbus_data[24]),
                          &(p_modbus_send_data_buffer->modbus_data[25])); 
                          
   p_modbus_send_data_buffer->modbus_data[26]= p_Hydrogen_detective_data->h2_circulating_pump_enble;
   p_modbus_send_data_buffer->modbus_data[27]= p_Hydrogen_detective_data->h2_circulating_pump_working_communication_mode;
   
   p_modbus_send_data_buffer->modbus_data[28]= (u8)(p_Hydrogen_detective_data->h2_circulating_pump_speed_setpoint);
   p_modbus_send_data_buffer->modbus_data[29]= (u8)((p_Hydrogen_detective_data->h2_circulating_pump_speed_setpoint)>>8);
                                                 
   p_modbus_send_data_buffer->modbus_data[30]=  p_Hydrogen_detective_data->h2_circulating_pump_enable_pump;
                          
                          
   float_convert_four_byte(&(p_Hydrogen_detective_data->h2_circulating_pump_actual_mass_flow),
	                        &(p_modbus_send_data_buffer->modbus_data[31]),
	                        &(p_modbus_send_data_buffer->modbus_data[32]),
                          &(p_modbus_send_data_buffer->modbus_data[33]),
                          &(p_modbus_send_data_buffer->modbus_data[34]));                        
                          
   float_convert_four_byte(&(p_Hydrogen_detective_data->h2_circulating_pump_actual_speed),
	                        &(p_modbus_send_data_buffer->modbus_data[35]),
	                        &(p_modbus_send_data_buffer->modbus_data[36]),
                          &(p_modbus_send_data_buffer->modbus_data[37]),
                          &(p_modbus_send_data_buffer->modbus_data[38]));                        
                                                   
   float_convert_four_byte(&(p_Hydrogen_detective_data->h2_circulating_pump_actual_current),
	                        &(p_modbus_send_data_buffer->modbus_data[39]),
	                        &(p_modbus_send_data_buffer->modbus_data[40]),
                          &(p_modbus_send_data_buffer->modbus_data[41]),
                          &(p_modbus_send_data_buffer->modbus_data[42]));                        
   
   float_convert_four_byte(&(p_Hydrogen_detective_data->h2_circulating_pump_actual_voltage),
	                        &(p_modbus_send_data_buffer->modbus_data[43]),
	                        &(p_modbus_send_data_buffer->modbus_data[44]),
                          &(p_modbus_send_data_buffer->modbus_data[45]),
                          &(p_modbus_send_data_buffer->modbus_data[46]));   
  
   // 这里温度是i16类型  转换成u8                        
   p_modbus_send_data_buffer->modbus_data[47]= (u8)(p_Hydrogen_detective_data->h2_circulating_pump_actual_electronic_temperature);    
   p_modbus_send_data_buffer->modbus_data[48]= (u8)((p_Hydrogen_detective_data->h2_circulating_pump_actual_electronic_temperature)>>8);                                          
                          
                                               
 
    float_convert_four_byte(&(p_Hydrogen_detective_data->h2_pressure_target_value),
	                        &(p_modbus_send_data_buffer->modbus_data[49]),       
	                        &(p_modbus_send_data_buffer->modbus_data[50]),
                          &(p_modbus_send_data_buffer->modbus_data[51]),
                          &(p_modbus_send_data_buffer->modbus_data[52]));  
                          
    float_convert_four_byte(&(p_Hydrogen_detective_data->h2_pressure_real_target_value),
	                        &(p_modbus_send_data_buffer->modbus_data[53]),
	                        &(p_modbus_send_data_buffer->modbus_data[54]),
                          &(p_modbus_send_data_buffer->modbus_data[55]),
                          &(p_modbus_send_data_buffer->modbus_data[56]));                                                 
                          
                          
    float_convert_four_byte(&(p_Hydrogen_detective_data->h2_pressure_advance_current_value),
	                        &(p_modbus_send_data_buffer->modbus_data[57]),
	                        &(p_modbus_send_data_buffer->modbus_data[58]),
                          &(p_modbus_send_data_buffer->modbus_data[59]),
                          &(p_modbus_send_data_buffer->modbus_data[60]));                        
	
	
	  float_convert_four_byte(&(p_Hydrogen_detective_data->h2_pressure_advance_set_value),
	                        &(p_modbus_send_data_buffer->modbus_data[61]),
	                        &(p_modbus_send_data_buffer->modbus_data[62]),
                          &(p_modbus_send_data_buffer->modbus_data[63]),
                          &(p_modbus_send_data_buffer->modbus_data[64]));  
                          
                          
   p_modbus_send_data_buffer->modbus_data[65]= (u8)(p_Hydrogen_detective_data->h2_pressure_pid1_advance_time);  
   p_modbus_send_data_buffer->modbus_data[66]= (u8)((p_Hydrogen_detective_data->h2_pressure_pid1_advance_time)>>8);                                         
   p_modbus_send_data_buffer->modbus_data[67]= (u8)((p_Hydrogen_detective_data->h2_pressure_pid1_advance_time)>>16);   
   p_modbus_send_data_buffer->modbus_data[68]= (u8)((p_Hydrogen_detective_data->h2_pressure_pid1_advance_time)>>24);  
                       
                       
                       
                       
                       
	 p_modbus_send_data_buffer->modbus_data[69]= (u8)(p_Hydrogen_detective_data->h2_pressure_pid2_advance_time);   
   p_modbus_send_data_buffer->modbus_data[70]= (u8)((p_Hydrogen_detective_data->h2_pressure_pid2_advance_time)>>8);                                            
   p_modbus_send_data_buffer->modbus_data[71]= (u8)((p_Hydrogen_detective_data->h2_pressure_pid2_advance_time)>>16);
   p_modbus_send_data_buffer->modbus_data[72]= (u8)((p_Hydrogen_detective_data->h2_pressure_pid2_advance_time)>>24);                                            
  
	                               
  p_modbus_send_data_buffer->modbus_data[73]=  p_Hydrogen_detective_data->PID1_is_enble_pid;
	 
	  float_convert_four_byte(&(p_Hydrogen_detective_data->PID1_Kp),
	                        &(p_modbus_send_data_buffer->modbus_data[74]),
	                        &(p_modbus_send_data_buffer->modbus_data[75]),
                          &(p_modbus_send_data_buffer->modbus_data[76]),
                          &(p_modbus_send_data_buffer->modbus_data[77]));  
                          
                          
    float_convert_four_byte(&(p_Hydrogen_detective_data->PID1_Ki),
	                        &(p_modbus_send_data_buffer->modbus_data[78]),
	                        &(p_modbus_send_data_buffer->modbus_data[79]),
                          &(p_modbus_send_data_buffer->modbus_data[80]),
                          &(p_modbus_send_data_buffer->modbus_data[81]));  
                          
                          
    float_convert_four_byte(&(p_Hydrogen_detective_data->PID1_Kd),
	                        &(p_modbus_send_data_buffer->modbus_data[82]),
	                        &(p_modbus_send_data_buffer->modbus_data[83]),
                          &(p_modbus_send_data_buffer->modbus_data[84]),
                          &(p_modbus_send_data_buffer->modbus_data[85]));  
                          
      p_modbus_send_data_buffer->modbus_data[86]=  p_Hydrogen_detective_data->PID2_is_enble_pid;                      
                  
                  
                  
   float_convert_four_byte(&(p_Hydrogen_detective_data->PID2_Kp),
	                        &(p_modbus_send_data_buffer->modbus_data[87]),
	                        &(p_modbus_send_data_buffer->modbus_data[88]),
                          &(p_modbus_send_data_buffer->modbus_data[89]),
                          &(p_modbus_send_data_buffer->modbus_data[90]));  
     
   float_convert_four_byte(&(p_Hydrogen_detective_data->PID2_Ki),
	                        &(p_modbus_send_data_buffer->modbus_data[91]),
	                        &(p_modbus_send_data_buffer->modbus_data[92]),
                          &(p_modbus_send_data_buffer->modbus_data[93]),
                          &(p_modbus_send_data_buffer->modbus_data[94]));   
                          
                          
   float_convert_four_byte(&(p_Hydrogen_detective_data->PID2_Kd),
	                        &(p_modbus_send_data_buffer->modbus_data[95]),
	                        &(p_modbus_send_data_buffer->modbus_data[96]),
                          &(p_modbus_send_data_buffer->modbus_data[97]),
                          &(p_modbus_send_data_buffer->modbus_data[98])); 
                          
                          
   p_modbus_send_data_buffer->modbus_data[99]=  p_Hydrogen_detective_data->h2_pid_mode;   
       
   p_modbus_send_data_buffer->modbus_data[100]=  p_Hydrogen_detective_data->h2_is_enable_outlet_valve; 
        
   p_modbus_send_data_buffer->modbus_data[101]= (u8)(p_Hydrogen_detective_data->h2_outlet_valve_open_time);   
   p_modbus_send_data_buffer->modbus_data[102]= (u8)((p_Hydrogen_detective_data->h2_outlet_valve_open_time)>>8);                                            
   p_modbus_send_data_buffer->modbus_data[103]= (u8)((p_Hydrogen_detective_data->h2_outlet_valve_open_time)>>16);   
   p_modbus_send_data_buffer->modbus_data[104]= (u8)((p_Hydrogen_detective_data->h2_outlet_valve_open_time)>>24);                                       
   
                                         
   
   p_modbus_send_data_buffer->modbus_data[105]= (u8)(p_Hydrogen_detective_data->h2_outlet_valve_close_time);    
   p_modbus_send_data_buffer->modbus_data[106]= (u8)((p_Hydrogen_detective_data->h2_outlet_valve_close_time)>>8);                                         
   p_modbus_send_data_buffer->modbus_data[107]= (u8)((p_Hydrogen_detective_data->h2_outlet_valve_close_time)>>16);          
   p_modbus_send_data_buffer->modbus_data[108]= (u8)((p_Hydrogen_detective_data->h2_outlet_valve_close_time)>>24);                                      
   
   float_convert_four_byte(&(p_Hydrogen_detective_data->h2_pressure_fluctuate_last_max),
	                        &(p_modbus_send_data_buffer->modbus_data[109]),
	                        &(p_modbus_send_data_buffer->modbus_data[110]),
                          &(p_modbus_send_data_buffer->modbus_data[111]),
                          &(p_modbus_send_data_buffer->modbus_data[112]));  
                           
   float_convert_four_byte(&(p_Hydrogen_detective_data->h2_pressure_fluctuate_last_min),
	                        &(p_modbus_send_data_buffer->modbus_data[113]),
	                        &(p_modbus_send_data_buffer->modbus_data[114]),
                          &(p_modbus_send_data_buffer->modbus_data[115]),
                          &(p_modbus_send_data_buffer->modbus_data[116]));                                    
                          
                                                                                                                              
	return error_code;


	

}

//氢气数据信息//数据处理
enum Error_code Hydrogen_detective_data_execute(struct Hydrogen_detective_data *  p_Hydrogen_detective_data)
{
	enum Error_code error_code = Succeed;
	int i =0;
	
	if(p_Hydrogen_detective_data == NULL)
	{return Pointer_is_null;}
	
	/*
     printf("data");
	*/
	
		
	return error_code;
}


//氢气数据信息//清除更新状态
enum Error_code Hydrogen_detective_data_clear_updata(struct Hydrogen_detective_data *  p_Hydrogen_detective_data)
{
	enum Error_code error_code = Succeed;
//	int i =0;
	
	if(p_Hydrogen_detective_data == NULL)
	{return Pointer_is_null;}
	
//	p_itinerant_detective_single_board_data->is_update = 0;	
//	p_itinerant_detective_single_board_data->updata_event_time = system_time_us;
	
	return error_code;
}	




//2、空气数据
//2.1空气数据信息
//空气数据信息//初始化
enum Error_code Air_detective_data_init(struct Air_detective_data *  p_Air_detective_data)
{
  enum Error_code error_code = Succeed;
	int i =0;
	
	if(p_Air_detective_data == NULL )
	{return Pointer_is_null;}
	
	
	p_Air_detective_data->updata_event_time = system_time;
	p_Air_detective_data->send_message_time_max = MODBUS_232_SEND_MESSAGE_TIME_MAX;	
	p_Air_detective_data->direction_data_transmission = 0xbb;
	p_Air_detective_data->function_code = 0x02;
	p_Air_detective_data->data_length = 44;
	p_Air_detective_data->air_pressure_pile_inlet = 0;
	p_Air_detective_data->air_pressure_pile_outlet = 0;
	p_Air_detective_data->air_pressure_pile_back = 0;
	p_Air_detective_data->air_temperature_pile_inlet = 0;
	p_Air_detective_data->air_temperature_pile_outlet = 0;
	p_Air_detective_data->air_temperature_pile_back = 0;
	p_Air_detective_data->air_temperature_humidifier = 0;
	p_Air_detective_data->air_rate_of_flow = 0;
	p_Air_detective_data->air_outlet_valve = 0;
	p_Air_detective_data->air_compressor_working_communication_mode = 0;
	p_Air_detective_data->air_compressor_enable = 0;
  p_Air_detective_data->air_compressor_speed_setpoint = 0;
  p_Air_detective_data->air_is_enable_outlet_valve = 0;
  p_Air_detective_data->air_outlet_valve_open_time = 0;
  p_Air_detective_data->air_outlet_valve_close_time = 0;

  

	return error_code;
}
//空气数据信息//数据解析
enum Error_code Air_detective_data_analysis(struct Modbus_Data_Buffer * p_modbus_receive_data_buffer, struct Air_detective_data *  p_Air_detective_data)
{
 	enum Error_code error_code = Succeed;
	int i =0;
	
	if(p_modbus_receive_data_buffer == NULL || p_Air_detective_data == NULL)
	{return Pointer_is_null;}
		
	return error_code;
}

//空气数据信息//数据封装
enum Error_code Air_detective_data_encapsulation( struct Air_detective_data *  p_Air_detective_data, struct Modbus_Data_Buffer * p_modbus_send_data_buffer)
{

    enum Error_code error_code = Succeed;

	if(p_Air_detective_data == NULL || p_modbus_send_data_buffer == NULL)
	{return Pointer_is_null;}
	
    p_Air_detective_data->updata_event_time = system_time;
	
  	p_modbus_send_data_buffer->direction_data_transmission = p_Air_detective_data->direction_data_transmission;
  	p_modbus_send_data_buffer->function_code = p_Air_detective_data->function_code;
  	p_modbus_send_data_buffer->data_length = p_Air_detective_data->data_length;
  	
  	float_convert_four_byte(&(p_Air_detective_data->air_pressure_pile_inlet),
	                        &(p_modbus_send_data_buffer->modbus_data[0]),
	                        &(p_modbus_send_data_buffer->modbus_data[1]),
                          &(p_modbus_send_data_buffer->modbus_data[2]),
                          &(p_modbus_send_data_buffer->modbus_data[3])); 
                          
    float_convert_four_byte(&(p_Air_detective_data->air_pressure_pile_outlet),
	                        &(p_modbus_send_data_buffer->modbus_data[4]),
	                        &(p_modbus_send_data_buffer->modbus_data[5]),
                          &(p_modbus_send_data_buffer->modbus_data[6]),
                          &(p_modbus_send_data_buffer->modbus_data[7]));  
   
   	float_convert_four_byte(&(p_Air_detective_data->air_pressure_pile_back),
	                        &(p_modbus_send_data_buffer->modbus_data[8]),
	                        &(p_modbus_send_data_buffer->modbus_data[9]),
                          &(p_modbus_send_data_buffer->modbus_data[10]),
                          &(p_modbus_send_data_buffer->modbus_data[11]));   
                          
    float_convert_four_byte(&(p_Air_detective_data->air_temperature_pile_inlet),
	                        &(p_modbus_send_data_buffer->modbus_data[12]),
	                        &(p_modbus_send_data_buffer->modbus_data[13]),
                          &(p_modbus_send_data_buffer->modbus_data[14]),
                          &(p_modbus_send_data_buffer->modbus_data[15]));  
                          
     	float_convert_four_byte(&(p_Air_detective_data->air_temperature_pile_outlet),
	                        &(p_modbus_send_data_buffer->modbus_data[16]),
	                        &(p_modbus_send_data_buffer->modbus_data[17]),
                          &(p_modbus_send_data_buffer->modbus_data[18]),
                          &(p_modbus_send_data_buffer->modbus_data[19])); 
                          
      	float_convert_four_byte(&(p_Air_detective_data->air_temperature_pile_back),
	                        &(p_modbus_send_data_buffer->modbus_data[20]),
	                        &(p_modbus_send_data_buffer->modbus_data[21]),
                          &(p_modbus_send_data_buffer->modbus_data[22]),
                          &(p_modbus_send_data_buffer->modbus_data[23]));                                                                                        
                                               
                                               
       	float_convert_four_byte(&(p_Air_detective_data->air_temperature_humidifier),
	                        &(p_modbus_send_data_buffer->modbus_data[24]),
	                        &(p_modbus_send_data_buffer->modbus_data[25]),
                          &(p_modbus_send_data_buffer->modbus_data[26]),
                          &(p_modbus_send_data_buffer->modbus_data[27])); 
                          
        p_modbus_send_data_buffer->modbus_data[28]=  p_Air_detective_data->air_outlet_valve;                    
        p_modbus_send_data_buffer->modbus_data[29]=  p_Air_detective_data->air_compressor_working_communication_mode;                    
        p_modbus_send_data_buffer->modbus_data[30]=  p_Air_detective_data->air_compressor_enable;                    
        
                                                            
         p_modbus_send_data_buffer->modbus_data[31]= (u8)(p_Air_detective_data->air_compressor_speed_setpoint);     
         p_modbus_send_data_buffer->modbus_data[32]= (u8)((p_Air_detective_data->air_compressor_speed_setpoint)>>8);                                            
         p_modbus_send_data_buffer->modbus_data[33]= (u8)((p_Air_detective_data->air_compressor_speed_setpoint)>>16); 
         p_modbus_send_data_buffer->modbus_data[34]= (u8)((p_Air_detective_data->air_compressor_speed_setpoint)>>24);                                         
                   
         p_modbus_send_data_buffer->modbus_data[35]=  p_Air_detective_data->air_is_enable_outlet_valve; 
                                                       
         p_modbus_send_data_buffer->modbus_data[36]= (u8)(p_Air_detective_data->air_outlet_valve_open_time);   
         p_modbus_send_data_buffer->modbus_data[37]= (u8)((p_Air_detective_data->air_outlet_valve_open_time)>>8);                                          
         p_modbus_send_data_buffer->modbus_data[38]= (u8)((p_Air_detective_data->air_outlet_valve_open_time)>>16);    
         p_modbus_send_data_buffer->modbus_data[39]= (u8)((p_Air_detective_data->air_outlet_valve_open_time)>>24);                                         
        
                                                        
         p_modbus_send_data_buffer->modbus_data[40]=(u8)(p_Air_detective_data->air_outlet_valve_close_time); 
         p_modbus_send_data_buffer->modbus_data[41]=(u8)((p_Air_detective_data->air_outlet_valve_close_time)>>8);                                            
         p_modbus_send_data_buffer->modbus_data[42]=(u8)((p_Air_detective_data->air_outlet_valve_close_time)>>16); 
         p_modbus_send_data_buffer->modbus_data[43]=(u8)((p_Air_detective_data->air_outlet_valve_close_time)>>24);                                              
                           
                                               
                                                                                                                              
	return error_code;                                  
}
//空气数据信息//数据处理                                 
enum Error_code Air_detective_data_execute(struct Air_detective_data *  p_Air_detective_data)
{
  	enum Error_code error_code = Succeed;
  	int i =0;
  	
  	if(p_Air_detective_data == NULL)
  	{return Pointer_is_null;}
  	
  	/*
       printf("data");
  	*/
  	
  		
  	return error_code;

}
//空气数据信息//清除更新状态
enum Error_code Air_detective_data_clear_updata(struct Air_detective_data *  p_Air_detective_data)
{
  	enum Error_code error_code = Succeed;
  //	int i =0;
  	
  	if(p_Air_detective_data == NULL)
  	{return Pointer_is_null;}
  	
  //	p_itinerant_detective_single_board_data->is_update = 0;	
  //	p_itinerant_detective_single_board_data->updata_event_time = system_time_us;
  	
  	return error_code;

}




//3、电堆散热系统数据
//3.1电堆散热系统数据
//电堆散热系统数据//初始化
enum Error_code Fell_temperature_data_init(struct Fell_temperature_data *  p_Fell_temperature_data)
{
  enum Error_code error_code = Succeed;
	int i =0;
	
	if(p_Fell_temperature_data == NULL )
	{return Pointer_is_null;}
	
	
	p_Fell_temperature_data->updata_event_time = system_time;
	p_Fell_temperature_data->send_message_time_max = MODBUS_232_SEND_MESSAGE_TIME_MAX;	
	p_Fell_temperature_data->direction_data_transmission = 0xbb;
	p_Fell_temperature_data->function_code = 0x03;
	p_Fell_temperature_data->data_length = 45;
	
	p_Fell_temperature_data->water_pressure_pile_inlet = 0;
	p_Fell_temperature_data->water_pressure_pile_outlet = 0;
	p_Fell_temperature_data->water_temperature_pile_inlet = 0;
	p_Fell_temperature_data->water_temperature_pile_outlet = 0;
	p_Fell_temperature_data->water_pump_pwm_dutyfactor = 0;
	p_Fell_temperature_data->water_fan1_pwm_dutyfactor = 0;
	p_Fell_temperature_data->water_fan2_pwm_dutyfactor = 0;
	p_Fell_temperature_data->water_PID_is_enble_pid = 0;
	p_Fell_temperature_data->water_PID_Kp = 0;
	p_Fell_temperature_data->water_PID_Ki = 0;
	p_Fell_temperature_data->water_PID_Kd = 0;
  p_Fell_temperature_data->water_temperature_target_value = 0;

	return error_code;
}
//电堆散热系统数据//数据解析
enum Error_code Fell_temperature_data_analysis(struct Modbus_Data_Buffer * p_modbus_receive_data_buffer, struct Fell_temperature_data *  p_Fell_temperature_data)
{
  enum Error_code error_code = Succeed;
	int i =0;
	
	if(p_modbus_receive_data_buffer == NULL || p_Fell_temperature_data == NULL)
	{return Pointer_is_null;}
		
	return error_code;
}
//电堆散热系统数据//数据封装
enum Error_code Fell_temperature_data_encapsulation( struct Fell_temperature_data *  p_Fell_temperature_data, struct Modbus_Data_Buffer * p_modbus_send_data_buffer)
{
      enum Error_code error_code = Succeed;

	if(p_Fell_temperature_data == NULL || p_modbus_send_data_buffer == NULL)
	{return Pointer_is_null;}
	
    p_Fell_temperature_data->updata_event_time = system_time;
	
  	p_modbus_send_data_buffer->direction_data_transmission = p_Fell_temperature_data->direction_data_transmission;
  	p_modbus_send_data_buffer->function_code = p_Fell_temperature_data->function_code;
  	p_modbus_send_data_buffer->data_length = p_Fell_temperature_data->data_length;
  	
  	float_convert_four_byte(&(p_Fell_temperature_data->water_pressure_pile_inlet),
	                        &(p_modbus_send_data_buffer->modbus_data[0]),
	                        &(p_modbus_send_data_buffer->modbus_data[1]),
                          &(p_modbus_send_data_buffer->modbus_data[2]),
                          &(p_modbus_send_data_buffer->modbus_data[3])); 
                          
    float_convert_four_byte(&(p_Fell_temperature_data->water_pressure_pile_outlet),
	                        &(p_modbus_send_data_buffer->modbus_data[4]),
	                        &(p_modbus_send_data_buffer->modbus_data[5]),
                          &(p_modbus_send_data_buffer->modbus_data[6]),
                          &(p_modbus_send_data_buffer->modbus_data[7]));  
   
   	float_convert_four_byte(&(p_Fell_temperature_data->water_temperature_pile_inlet),
	                        &(p_modbus_send_data_buffer->modbus_data[8]),
	                        &(p_modbus_send_data_buffer->modbus_data[9]),
                          &(p_modbus_send_data_buffer->modbus_data[10]),
                          &(p_modbus_send_data_buffer->modbus_data[11]));   
                          
    float_convert_four_byte(&(p_Fell_temperature_data->water_temperature_pile_outlet),
	                        &(p_modbus_send_data_buffer->modbus_data[12]),
	                        &(p_modbus_send_data_buffer->modbus_data[13]),
                          &(p_modbus_send_data_buffer->modbus_data[14]),
                          &(p_modbus_send_data_buffer->modbus_data[15]));  
                          
     	float_convert_four_byte(&(p_Fell_temperature_data->water_pump_pwm_dutyfactor),
	                        &(p_modbus_send_data_buffer->modbus_data[16]),
	                        &(p_modbus_send_data_buffer->modbus_data[17]),
                          &(p_modbus_send_data_buffer->modbus_data[18]),
                          &(p_modbus_send_data_buffer->modbus_data[19])); 
                          
      	float_convert_four_byte(&(p_Fell_temperature_data->water_fan1_pwm_dutyfactor),
	                        &(p_modbus_send_data_buffer->modbus_data[20]),
	                        &(p_modbus_send_data_buffer->modbus_data[21]),
                          &(p_modbus_send_data_buffer->modbus_data[22]),
                          &(p_modbus_send_data_buffer->modbus_data[23]));                                                                                        
                                               
                                               
       	float_convert_four_byte(&(p_Fell_temperature_data->water_fan2_pwm_dutyfactor),
	                        &(p_modbus_send_data_buffer->modbus_data[24]),
	                        &(p_modbus_send_data_buffer->modbus_data[25]),
                          &(p_modbus_send_data_buffer->modbus_data[26]),
                          &(p_modbus_send_data_buffer->modbus_data[27])); 
                          
        p_modbus_send_data_buffer->modbus_data[28]=  p_Fell_temperature_data->water_PID_is_enble_pid;                    
 
       
       
       float_convert_four_byte(&(p_Fell_temperature_data->water_PID_Kp),
	                        &(p_modbus_send_data_buffer->modbus_data[29]),
	                        &(p_modbus_send_data_buffer->modbus_data[30]),
                          &(p_modbus_send_data_buffer->modbus_data[31]),
                          &(p_modbus_send_data_buffer->modbus_data[32]));  
                          
     	float_convert_four_byte(&(p_Fell_temperature_data->water_PID_Ki),
	                        &(p_modbus_send_data_buffer->modbus_data[33]),
	                        &(p_modbus_send_data_buffer->modbus_data[34]),
                          &(p_modbus_send_data_buffer->modbus_data[35]),
                          &(p_modbus_send_data_buffer->modbus_data[36])); 
                          
      	float_convert_four_byte(&(p_Fell_temperature_data->water_PID_Kd),
	                        &(p_modbus_send_data_buffer->modbus_data[37]),
	                        &(p_modbus_send_data_buffer->modbus_data[38]),
                          &(p_modbus_send_data_buffer->modbus_data[39]),
                          &(p_modbus_send_data_buffer->modbus_data[40]));                                                                                        
                                               
                                               
       	float_convert_four_byte(&(p_Fell_temperature_data->water_temperature_target_value),
	                        &(p_modbus_send_data_buffer->modbus_data[41]),
	                        &(p_modbus_send_data_buffer->modbus_data[42]),
                          &(p_modbus_send_data_buffer->modbus_data[43]),
                          &(p_modbus_send_data_buffer->modbus_data[44]));  
                    

                                                                                                                              
	return error_code;
}
//电堆散热系统数据//数据处理
enum Error_code Fell_temperature_data_execute(struct Fell_temperature_data *  p_Fell_temperature_data)
{
      	enum Error_code error_code = Succeed;
  	int i =0;
  	
  	if(p_Fell_temperature_data == NULL)
  	{return Pointer_is_null;}
  	
  	/*
       printf("data");
  	*/
  	
  		
  	return error_code;
}
//电堆散热系统数据//清除更新状态
enum Error_code Fell_temperature_data_updata(struct Fell_temperature_data *  p_Fell_temperature_data)
{
     	enum Error_code error_code = Succeed;
  //	int i =0;
  	
  	if(p_Fell_temperature_data == NULL)
  	{return Pointer_is_null;}
  	
  //	p_itinerant_detective_single_board_data->is_update = 0;	
  //	p_itinerant_detective_single_board_data->updata_event_time = system_time_us;
  	
  	return error_code;
}












//4、空压机散热系统数据
//4.1空压机散热系统数据
//空压机散热系统数据//初始化
enum Error_code Air_compressor_temperature_data_init(struct Air_compressor_temperature_data *  p_Air_compressor_temperature_data)
{
  enum Error_code error_code = Succeed;
	int i =0;
	
	if(p_Air_compressor_temperature_data == NULL )
	{return Pointer_is_null;}
	
	
	p_Air_compressor_temperature_data->updata_event_time = system_time;
	p_Air_compressor_temperature_data->send_message_time_max = MODBUS_232_SEND_MESSAGE_TIME_MAX;	
	p_Air_compressor_temperature_data->direction_data_transmission = 0xbb;
	p_Air_compressor_temperature_data->function_code = 0x04;
	p_Air_compressor_temperature_data->data_length = 21;
	
	p_Air_compressor_temperature_data->water_pressure_compressor_outlet = 0;
	p_Air_compressor_temperature_data->water_temperature_compressor_outlet = 0;
	p_Air_compressor_temperature_data->water_temperature_pump_outlet = 0;
	p_Air_compressor_temperature_data->water_temperature_compressor_shell = 0;
	p_Air_compressor_temperature_data->water_pump_enable = 0;
	p_Air_compressor_temperature_data->water_fan_pwm_dutyfactor = 0;


	return error_code;
}
//空压机散热系统数据//数据解析
enum Error_code Air_compressor_temperature_data_analysis(struct Modbus_Data_Buffer * p_modbus_receive_data_buffer, struct Air_compressor_temperature_data *  p_Air_compressor_temperature_data)
{
  enum Error_code error_code = Succeed;
	int i =0;
	
	if(p_modbus_receive_data_buffer == NULL || p_Air_compressor_temperature_data == NULL)
	{return Pointer_is_null;}
		
	return error_code;
}
//空压机散热系统数据//数据封装
enum Error_code Air_compressor_temperature_data_encapsulation( struct Air_compressor_temperature_data *  p_Air_compressor_temperature_data, struct Modbus_Data_Buffer * p_modbus_send_data_buffer)
{
           enum Error_code error_code = Succeed;

	if(p_Air_compressor_temperature_data == NULL || p_modbus_send_data_buffer == NULL)
	{return Pointer_is_null;}
	
    p_Air_compressor_temperature_data->updata_event_time = system_time;
	
  	p_modbus_send_data_buffer->direction_data_transmission = p_Air_compressor_temperature_data->direction_data_transmission;
  	p_modbus_send_data_buffer->function_code = p_Air_compressor_temperature_data->function_code;
  	p_modbus_send_data_buffer->data_length = p_Air_compressor_temperature_data->data_length;
  	
  	float_convert_four_byte(&(p_Air_compressor_temperature_data->water_pressure_compressor_outlet),
	                        &(p_modbus_send_data_buffer->modbus_data[0]),
	                        &(p_modbus_send_data_buffer->modbus_data[1]),
                          &(p_modbus_send_data_buffer->modbus_data[2]),
                          &(p_modbus_send_data_buffer->modbus_data[3])); 
                          
    float_convert_four_byte(&(p_Air_compressor_temperature_data->water_temperature_compressor_outlet),
	                        &(p_modbus_send_data_buffer->modbus_data[4]),
	                        &(p_modbus_send_data_buffer->modbus_data[5]),
                          &(p_modbus_send_data_buffer->modbus_data[6]),
                          &(p_modbus_send_data_buffer->modbus_data[7]));  
   
   	float_convert_four_byte(&(p_Air_compressor_temperature_data->water_temperature_pump_outlet),
	                        &(p_modbus_send_data_buffer->modbus_data[8]),
	                        &(p_modbus_send_data_buffer->modbus_data[9]),
                          &(p_modbus_send_data_buffer->modbus_data[10]),
                          &(p_modbus_send_data_buffer->modbus_data[11]));   
                          
    float_convert_four_byte(&(p_Air_compressor_temperature_data->water_temperature_compressor_shell),
	                        &(p_modbus_send_data_buffer->modbus_data[12]),
	                        &(p_modbus_send_data_buffer->modbus_data[13]),
                          &(p_modbus_send_data_buffer->modbus_data[14]),
                          &(p_modbus_send_data_buffer->modbus_data[15]));  

                          

                          
     p_modbus_send_data_buffer->modbus_data[16]=  p_Air_compressor_temperature_data->water_pump_enable;       
        
                                  
   	float_convert_four_byte(&(p_Air_compressor_temperature_data->water_fan_pwm_dutyfactor),
	                        &(p_modbus_send_data_buffer->modbus_data[17]),
	                        &(p_modbus_send_data_buffer->modbus_data[18]),
                          &(p_modbus_send_data_buffer->modbus_data[19]),
                          &(p_modbus_send_data_buffer->modbus_data[20]));              
 
       
       


                                                                                                                              
	return error_code;
}
//空压机散热系统数据//数据处理
enum Error_code Air_compressor_temperature_data_execute(struct Air_compressor_temperature_data *  p_Air_compressor_temperature_data)
{
           	enum Error_code error_code = Succeed;
  	int i =0;
  	
  	if(p_Air_compressor_temperature_data == NULL)
  	{return Pointer_is_null;}
  	
  	/*
       printf("data");
  	*/
  	
  		
  	return error_code;
}
//空压机散热系统数据//清除更新状态
enum Error_code Air_compressor_temperature_data_updata(struct Air_compressor_temperature_data *  p_Air_compressor_temperature_data)
{
         	enum Error_code error_code = Succeed;
  //	int i =0;
  	
  	if(p_Air_compressor_temperature_data == NULL)
  	{return Pointer_is_null;}
  	
  //	p_itinerant_detective_single_board_data->is_update = 0;	
  //	p_itinerant_detective_single_board_data->updata_event_time = system_time_us;
  	
  	return error_code;
}











//5、电堆输出数据
//5.1电堆输出数据
//电堆输出数据//初始化
enum Error_code Fell_output_data_init(struct Fell_output_data *  p_Fell_output_data)
{
  enum Error_code error_code = Succeed;
	int i =0;
	
	if(p_Fell_output_data == NULL )
	{return Pointer_is_null;}

	
	p_Fell_output_data->updata_event_time = system_time;
	p_Fell_output_data->send_message_time_max = MODBUS_232_SEND_MESSAGE_TIME_MAX;	
	p_Fell_output_data->direction_data_transmission = 0xbb;
	p_Fell_output_data->function_code = 0x05;
	p_Fell_output_data->data_length = 37;
	
	p_Fell_output_data->galvanic_pile_voltage = 0;
	p_Fell_output_data->galvanic_pile_electricity = 0;
	p_Fell_output_data->fcu_start_enable = 0;
	p_Fell_output_data->fcu_stutter_stop_enable = 0;
	p_Fell_output_data->galvanic_pile_is_enble_output = 0;
	p_Fell_output_data->galvanic_pile_is_enble_load_resistance = 0;
	p_Fell_output_data->itinerant_detective_working_communication_mode = 0;
	p_Fell_output_data->itinerant_detective_working_statas = 0;
	p_Fell_output_data->Single_battery_overvoltage_alarm = 0;
	p_Fell_output_data->Single_battery_undervoltage_alarm = 0;
	p_Fell_output_data->Single_voltage_unbalance_alarm = 0;
	p_Fell_output_data->electric1_mean_voltage = 0;
	p_Fell_output_data->electric1_single_chip_highest_voltage = 0;
	p_Fell_output_data->electric1_single_chip_highest_voltage_num = 0;
	p_Fell_output_data->electric1_single_chip_minimum_voltage = 0;
	p_Fell_output_data->electric1_single_chip_minimum_voltage_num = 0;
	p_Fell_output_data->itinerant_detective_total_voltage = 0;

	return error_code;
}
//电堆输出数据//数据解析
enum Error_code Fell_output_data_analysis(struct Modbus_Data_Buffer * p_modbus_receive_data_buffer, struct Fell_output_data *  p_Fell_output_data)
{
  enum Error_code error_code = Succeed;
	int i =0;
	
	if(p_modbus_receive_data_buffer == NULL || p_Fell_output_data == NULL)
	{return Pointer_is_null;}
		
	return error_code;

}
//电堆输出数据//数据封装
enum Error_code Fell_output_data_encapsulation( struct Fell_output_data *  p_Fell_output_data, struct Modbus_Data_Buffer * p_modbus_send_data_buffer)
{
   enum Error_code error_code = Succeed;

	if(p_Fell_output_data == NULL || p_modbus_send_data_buffer == NULL)
	{return Pointer_is_null;}
	
    p_Fell_output_data->updata_event_time = system_time;
	
  	p_modbus_send_data_buffer->direction_data_transmission = p_Fell_output_data->direction_data_transmission;
  	p_modbus_send_data_buffer->function_code = p_Fell_output_data->function_code;
  	p_modbus_send_data_buffer->data_length = p_Fell_output_data->data_length;
  	
  	float_convert_four_byte(&(p_Fell_output_data->galvanic_pile_voltage),
	                        &(p_modbus_send_data_buffer->modbus_data[0]),
	                        &(p_modbus_send_data_buffer->modbus_data[1]),
                          &(p_modbus_send_data_buffer->modbus_data[2]),
                          &(p_modbus_send_data_buffer->modbus_data[3])); 
                          
    float_convert_four_byte(&(p_Fell_output_data->galvanic_pile_electricity),
	                        &(p_modbus_send_data_buffer->modbus_data[4]),
	                        &(p_modbus_send_data_buffer->modbus_data[5]),
                          &(p_modbus_send_data_buffer->modbus_data[6]),
                          &(p_modbus_send_data_buffer->modbus_data[7]));  
                          
    p_modbus_send_data_buffer->modbus_data[8]=  p_Fell_output_data->fcu_start_enable; 
    p_modbus_send_data_buffer->modbus_data[9]=  p_Fell_output_data->fcu_stutter_stop_enable; 
    p_modbus_send_data_buffer->modbus_data[10]=  p_Fell_output_data->galvanic_pile_is_enble_output;                       
    p_modbus_send_data_buffer->modbus_data[11]=  p_Fell_output_data->galvanic_pile_is_enble_load_resistance;
    p_modbus_send_data_buffer->modbus_data[12]=  p_Fell_output_data->itinerant_detective_working_communication_mode;  
    p_modbus_send_data_buffer->modbus_data[13]=  p_Fell_output_data->itinerant_detective_working_statas; 
    p_modbus_send_data_buffer->modbus_data[14]=  p_Fell_output_data->Single_battery_overvoltage_alarm; 
    p_modbus_send_data_buffer->modbus_data[15]=  p_Fell_output_data->Single_battery_undervoltage_alarm;
    p_modbus_send_data_buffer->modbus_data[16]=  p_Fell_output_data->Single_voltage_unbalance_alarm;
   

   
   	float_convert_four_byte(&(p_Fell_output_data->electric1_mean_voltage),
	                        &(p_modbus_send_data_buffer->modbus_data[17]),
	                        &(p_modbus_send_data_buffer->modbus_data[18]),
                          &(p_modbus_send_data_buffer->modbus_data[19]),
                          &(p_modbus_send_data_buffer->modbus_data[20]));   
                          
    float_convert_four_byte(&(p_Fell_output_data->electric1_single_chip_highest_voltage),
	                        &(p_modbus_send_data_buffer->modbus_data[21]),
	                        &(p_modbus_send_data_buffer->modbus_data[22]),
                          &(p_modbus_send_data_buffer->modbus_data[23]),
                          &(p_modbus_send_data_buffer->modbus_data[24]));  

                     
    p_modbus_send_data_buffer->modbus_data[25]= (u8)(p_Fell_output_data->electric1_single_chip_highest_voltage_num);  
    p_modbus_send_data_buffer->modbus_data[26]= (u8)((p_Fell_output_data->electric1_single_chip_highest_voltage_num)>>8); 
                                                
   	float_convert_four_byte(&(p_Fell_output_data->electric1_single_chip_minimum_voltage),
	                        &(p_modbus_send_data_buffer->modbus_data[27]),
	                        &(p_modbus_send_data_buffer->modbus_data[28]),
                          &(p_modbus_send_data_buffer->modbus_data[29]),
                          &(p_modbus_send_data_buffer->modbus_data[30]));  
                          
                          
    p_modbus_send_data_buffer->modbus_data[31]= (u8)(p_Fell_output_data->electric1_single_chip_minimum_voltage_num);   
    p_modbus_send_data_buffer->modbus_data[32]= (u8)((p_Fell_output_data->electric1_single_chip_minimum_voltage_num)>>8);
                                                
   	float_convert_four_byte(&(p_Fell_output_data->itinerant_detective_total_voltage),
	                        &(p_modbus_send_data_buffer->modbus_data[33]),
	                        &(p_modbus_send_data_buffer->modbus_data[34]),
                          &(p_modbus_send_data_buffer->modbus_data[35]),
                          &(p_modbus_send_data_buffer->modbus_data[36])); 
                          
    return error_code;                      
                          
                                                 
}
//电堆输出数据//数据处理
enum Error_code Fell_output_data_execute(struct Fell_output_data *  p_Fell_output_data)
{
    enum Error_code error_code = Succeed;
  	int i =0;
  	
  	if(p_Fell_output_data == NULL)
  	{return Pointer_is_null;}
  	
  	/*
       printf("data");
  	*/
  	
  		
  	return error_code;
}
//电堆输出数据//清除更新状态
enum Error_code Fell_output_data_updata(struct Fell_output_data *  p_Fell_output_data)
{
   	enum Error_code error_code = Succeed;
  //	int i =0;
  	
  	if(p_Fell_output_data == NULL)
  	{return Pointer_is_null;}
  	
  //	p_itinerant_detective_single_board_data->is_update = 0;	
  //	p_itinerant_detective_single_board_data->updata_event_time = system_time_us;
  	
  	return error_code;
}




//6、FCU运行状态信息
//6.1FCU运行状态信息
//FCU运行状态信息//初始化
enum Error_code FCU_run_stata_data_init(struct FCU_run_stata_data *  p_FCU_run_stata_data)
{
  enum Error_code error_code = Succeed;
  int i=0;
	if(p_FCU_run_stata_data == NULL )
	{return Pointer_is_null;}
	

 	p_FCU_run_stata_data->updata_event_time = system_time;
	p_FCU_run_stata_data->send_message_time_max = MODBUS_232_SEND_MESSAGE_TIME_MAX;	

	p_FCU_run_stata_data->direction_data_transmission = 0xbb;
	p_FCU_run_stata_data->function_code = 0x06;
	p_FCU_run_stata_data->data_length = 7;
	 
	p_FCU_run_stata_data->FCU_control_mode=0; 
	p_FCU_run_stata_data->FCU_work_mode=0; 
	p_FCU_run_stata_data->FCU_alarm_mode=0; 
	p_FCU_run_stata_data->FCU_error_code=0; 
	p_FCU_run_stata_data->FCU_erroring_control_mode=0; 
	p_FCU_run_stata_data->FCU_system_run_mode=0; 


	
	return error_code;
}
//FCU运行状态信息//数据解析
enum Error_code FCU_run_stata_data_analysis(struct Modbus_Data_Buffer * p_modbus_receive_data_buffer, struct FCU_run_stata_data *  p_FCU_run_stata_data)
{
  enum Error_code error_code = Succeed;
	int i =0;
	
	if(p_modbus_receive_data_buffer == NULL || p_FCU_run_stata_data == NULL)
	{return Pointer_is_null;}
		
	return error_code;
}
//FCU运行状态信息//数据封装
enum Error_code FCU_run_stata_data_encapsulation( struct FCU_run_stata_data *  p_FCU_run_stata_data, struct Modbus_Data_Buffer * p_modbus_send_data_buffer)
{
     enum Error_code error_code = Succeed;

  	if(p_FCU_run_stata_data == NULL || p_modbus_send_data_buffer == NULL)
  	{return Pointer_is_null;}
	
    p_FCU_run_stata_data->updata_event_time = system_time;
	
  	p_modbus_send_data_buffer->direction_data_transmission = p_FCU_run_stata_data->direction_data_transmission;
  	p_modbus_send_data_buffer->function_code = p_FCU_run_stata_data->function_code;
  	p_modbus_send_data_buffer->data_length = p_FCU_run_stata_data->data_length;
  	

                          
    p_modbus_send_data_buffer->modbus_data[0]=  p_FCU_run_stata_data->FCU_control_mode; 
    p_modbus_send_data_buffer->modbus_data[1]=  p_FCU_run_stata_data->FCU_work_mode; 
    p_modbus_send_data_buffer->modbus_data[2]=  p_FCU_run_stata_data->FCU_alarm_mode;                       
    p_modbus_send_data_buffer->modbus_data[3]=  (u8)(p_FCU_run_stata_data->FCU_error_code);  
    p_modbus_send_data_buffer->modbus_data[4]=  (u8)((p_FCU_run_stata_data->FCU_error_code)>>8);  
    p_modbus_send_data_buffer->modbus_data[5]=  p_FCU_run_stata_data->FCU_erroring_control_mode;  
    p_modbus_send_data_buffer->modbus_data[6]=  p_FCU_run_stata_data->FCU_system_run_mode; 
 
   

 
                          
    return error_code;  
}
//FCU运行状态信息//数据处理
enum Error_code FCU_run_stata_data_execute(struct FCU_run_stata_data *  p_FCU_run_stata_data)
{
    enum Error_code error_code = Succeed;
  	int i =0;
  	
  	if(p_FCU_run_stata_data == NULL)
  	{return Pointer_is_null;}
  	
  	
   //    printf("data");
  	
  	
  		
  	return error_code;
}




//FCU运行状态信息//清除更新状态
enum Error_code FCU_run_stata_data_updata(struct FCU_run_stata_data *  p_FCU_run_stata_data)
{
     enum Error_code error_code = Succeed;
  //	int i =0;
  	
  	if(p_FCU_run_stata_data == NULL)
  	{return Pointer_is_null;}
  	
  //	p_itinerant_detective_single_board_data->is_update = 0;	
  //	p_itinerant_detective_single_board_data->updata_event_time = system_time_us;
  	
  	return error_code;
}





/*
//7、FCU接收命令数据
//7.1FCU接收命令数据
//FCU接收命令数据//初始化
enum Error_code FCU_receive_orde_data_init(struct FCU_receive_orde_data *  p_FCU_receive_orde_data)
{
  enum Error_code error_code = Succeed;
  int i=0;
	if(p_FCU_receive_orde_data == NULL )
	{return Pointer_is_null;}
	

	p_FCU_receive_orde_data->direction_data_transmission = 0;
	p_FCU_receive_orde_data->function_code = 0;
	p_FCU_receive_orde_data->data_length = 0;
	 
	for(i=0;i<4;i++)
	{
	    p_FCU_receive_orde_data->receive_orde_data[i]=0;
	}
	p_FCU_receive_orde_data->h2_inlet_valve = 0;
	p_FCU_receive_orde_data->h2_is_enable_outlet_valve = 0;
	p_FCU_receive_orde_data->h2_outlet_valve_open_time = 0;
	p_FCU_receive_orde_data->h2_outlet_valve_close_time = 0;

	p_FCU_receive_orde_data->h2_proportional_valve_pwm_dutyfactor = 0;

	p_FCU_receive_orde_data->h2_circulating_pump_enble = 0;

	p_FCU_receive_orde_data->h2_circulating_pump_enable_pump = 0;

	p_FCU_receive_orde_data->h2_pressure_target_value = 0;

	p_FCU_receive_orde_data->h2_pressure_advance_set_value = 0;

	p_FCU_receive_orde_data->PID1_is_enble_pid = 0;
	p_FCU_receive_orde_data->PID2_Kp = 0;
	p_FCU_receive_orde_data->PID2_Ki = 0;
	p_FCU_receive_orde_data->PID2_Kd = 0;
	p_FCU_receive_orde_data->h2_pid_mode = 0;
	p_FCU_receive_orde_data->air_compressor_enable = 0;
	p_FCU_receive_orde_data->air_compressor_speed_setpoint = 0;
	p_FCU_receive_orde_data->air_is_enable_outlet_valve = 0;
	p_FCU_receive_orde_data->air_outlet_valve_open_time = 0;
	p_FCU_receive_orde_data->air_outlet_valve_close_time = 0;
	p_FCU_receive_orde_data->water_pump_pwm_dutyfactor = 0;
	p_FCU_receive_orde_data->water_fan1_pwm_dutyfactor = 0;
	p_FCU_receive_orde_data->water_fan2_pwm_dutyfactor = 0;
	p_FCU_receive_orde_data->water_PID_is_enble_pid = 0;
	p_FCU_receive_orde_data->water_PID_Kp = 0;
	p_FCU_receive_orde_data->water_PID_Ki = 0;
	p_FCU_receive_orde_data->water_PID_Kd = 0;
	p_FCU_receive_orde_data->water_temperature_target_value = 0;
	p_FCU_receive_orde_data->compressor_water_pump_enable = 0;
	p_FCU_receive_orde_data->compressor_water_fan_pwm_dutyfactor = 0;
	p_FCU_receive_orde_data->fcu_start_enable = 0;
	p_FCU_receive_orde_data->fcu_stutter_stop_enable = 0;
	p_FCU_receive_orde_data->galvanic_pile_is_enble_output = 0;
	p_FCU_receive_orde_data->galvanic_pile_is_enble_load_resistance = 0;
	p_FCU_receive_orde_data->FCU_system_run_mode = 0;


	
	return error_code;
}
//FCU接收命令数据//数据解析
enum Error_code FCU_receive_orde_data_analysis(struct Modbus_Data_Buffer * p_modbus_receive_data_buffer, struct FCU_receive_orde_data *  p_FCU_receive_orde_data)
{
     enum Error_code error_code = Succeed;
     int i=0;
    
     	if(p_modbus_receive_data_buffer == NULL || p_FCU_receive_orde_data == NULL)
    	{return Pointer_is_null;}
    	
//    	direction_data_transmission_temp= p_modbus_receive_data_buffer->direction_data_transmission;
      p_FCU_receive_orde_data->direction_data_transmission=p_modbus_receive_data_buffer->direction_data_transmission;
//      function_code_temp=p_modbus_receive_data_buffer->function_code;
      p_FCU_receive_orde_data->function_code=p_modbus_receive_data_buffer->function_code;
      p_FCU_receive_orde_data->data_length=p_modbus_receive_data_buffer->data_length;
      
      for(i=0;i<4;i++)
      {
         p_FCU_receive_orde_data->receive_orde_data[i]=p_modbus_receive_data_buffer->modbus_data[i];
      }
      

      
     	return error_code;
}
//FCU接收命令数据//数据封装
enum Error_code FCU_receive_orde_data_encapsulation( struct FCU_receive_orde_data *  p_FCU_receive_orde_data, struct Modbus_Data_Buffer * p_modbus_send_data_buffer)
{
    enum Error_code error_code = Succeed;	
  	
  	if(p_FCU_receive_orde_data == NULL)
  	{return Pointer_is_null;}
  	
  	
     //  printf("data");
  	
  	
  		
  	return error_code;
}
//FCU接收命令数据//数据处理
enum Error_code FCU_receive_orde_data_execute(struct FCU_receive_orde_data *  p_FCU_receive_orde_data)
{
    enum Error_code error_code = Succeed;
  	if(p_FCU_receive_orde_data == NULL)
  	{return Pointer_is_null;}	
  	
     //  printf("data");
    			
  	return error_code;
}
//FCU接收命令数据//清除更新状态
enum Error_code FCU_receive_orde_data_updata(struct FCU_receive_orde_data *  p_FCU_receive_orde_data)
{
    enum Error_code error_code = Succeed;	
  	if(p_FCU_receive_orde_data == NULL)
  	{return Pointer_is_null;} 	
  //	p_itinerant_detective_single_board_data->is_update = 0;	
  //	p_itinerant_detective_single_board_data->updata_event_time = system_time_us;	
  	return error_code;
}


*/

//7、FCU总管理状态
//7.1FCU总管理状态
//FCU总管理状态//初始化
enum Error_code FCU_modbus_tatal_manager_data_init(struct FCU_modbus_tatal_manager_data *  p_FCU_modbus_tatal_manager_data)
{

 	if(p_FCU_modbus_tatal_manager_data == NULL)
     {return Pointer_is_null;}
  
  p_FCU_modbus_tatal_manager_data->islock=unlock;   
  Hydrogen_detective_data_init(&(p_FCU_modbus_tatal_manager_data->hydrogen_detective_data));
  Air_detective_data_init(&(p_FCU_modbus_tatal_manager_data->air_detective_data));
  Fell_temperature_data_init(&(p_FCU_modbus_tatal_manager_data->fell_temperature_data));
  Air_compressor_temperature_data_init(&(p_FCU_modbus_tatal_manager_data->air_compressor_temperature_data));
  Fell_output_data_init(&(p_FCU_modbus_tatal_manager_data->fell_output_data));
  FCU_run_stata_data_init(&(p_FCU_modbus_tatal_manager_data->fcu_run_stata_data));
//  FCU_receive_orde_data_init(&(p_FCU_modbus_tatal_manager_data->fcu_receive_orde_data));

}




//FCU总管理状态//数据解析
enum Error_code FCU_modbus_tatal_manager_data_analysis(struct Modbus_Data_Buffer * p_modbus_receive_data_buffer,struct FCU_Data_Buffer * p_FCU_Data_Buffer,struct Control_Policy_Total_Manager *p_Control_Policy_Total_Manager)
{
    enum Error_code error_code = Succeed;	

    		
   // FCU_receive_orde_data_analysis(p_modbus_receive_data_buffer,  &(p_FCU_modbus_tatal_manager_data->fcu_receive_orde_data));	
   
   modbus_232_receive_to_databuff(p_modbus_receive_data_buffer,p_FCU_Data_Buffer,p_Control_Policy_Total_Manager);		
    

    return error_code;
  
  
  
}
//FCU总管理状态//数据封装
enum Error_code FCU_modbus_tatal_manager_data_encapsulation( struct FCU_modbus_tatal_manager_data *  p_FCU_modbus_tatal_manager_data, struct Modbus_Data_Buffer * p_modbus_send_data_buffer)
{
   enum Error_code error_code = Succeed;	
   
   u8 data_directe_temp=0;
   u8 function_code_temp=0;
   u8 data_length_temp=0;
   

   	if(system_time - p_FCU_modbus_tatal_manager_data->hydrogen_detective_data.updata_event_time > p_FCU_modbus_tatal_manager_data->hydrogen_detective_data.send_message_time_max)
   	{
   	  error_code = Hydrogen_detective_data_encapsulation(&(p_FCU_modbus_tatal_manager_data->hydrogen_detective_data), p_modbus_send_data_buffer);  
   	  
   	      	
    		return error_code;//无论成功与否，都要结束这个函数，因为函数一次只能处理一条消息的转换
    		
    		

   	}
   	
   	if(system_time - p_FCU_modbus_tatal_manager_data->air_detective_data.updata_event_time > p_FCU_modbus_tatal_manager_data->air_detective_data.send_message_time_max)
   	{
   	  error_code = Air_detective_data_encapsulation(&(p_FCU_modbus_tatal_manager_data->air_detective_data), p_modbus_send_data_buffer);
   	  
   
    	
    		return error_code;//无论成功与否，都要结束这个函数，因为函数一次只能处理一条消息的转换

   	}
   	
   	if(system_time - p_FCU_modbus_tatal_manager_data->fell_temperature_data.updata_event_time > p_FCU_modbus_tatal_manager_data->fell_temperature_data.send_message_time_max)
   	{
   	  error_code = Fell_temperature_data_encapsulation(&(p_FCU_modbus_tatal_manager_data->fell_temperature_data), p_modbus_send_data_buffer);
   
   	  
    	
    		return error_code;//无论成功与否，都要结束这个函数，因为函数一次只能处理一条消息的转换

   	}
   	
   	if(system_time - p_FCU_modbus_tatal_manager_data->air_compressor_temperature_data.updata_event_time > p_FCU_modbus_tatal_manager_data->air_compressor_temperature_data.send_message_time_max)
   	{
   	  error_code = Air_compressor_temperature_data_encapsulation(&(p_FCU_modbus_tatal_manager_data->air_compressor_temperature_data), p_modbus_send_data_buffer);
   	  
   	

    	
    		return error_code;//无论成功与否，都要结束这个函数，因为函数一次只能处理一条消息的转换

   	}
   	  
   	if(system_time - p_FCU_modbus_tatal_manager_data->fell_output_data.updata_event_time > p_FCU_modbus_tatal_manager_data->fell_output_data.send_message_time_max)
   	{
   	  error_code = Fell_output_data_encapsulation(&(p_FCU_modbus_tatal_manager_data->fell_output_data), p_modbus_send_data_buffer);
   	  
   	

    	
    		return error_code;//无论成功与否，都要结束这个函数，因为函数一次只能处理一条消息的转换

   	}
   	
   	if(system_time - p_FCU_modbus_tatal_manager_data->fcu_run_stata_data.updata_event_time > p_FCU_modbus_tatal_manager_data->fcu_run_stata_data.send_message_time_max)
   	{
   	  error_code =  FCU_run_stata_data_encapsulation(&(p_FCU_modbus_tatal_manager_data->fcu_run_stata_data), p_modbus_send_data_buffer);
   	  

	
    		return error_code;//无论成功与否，都要结束这个函数，因为函数一次只能处理一条消息的转换

   	}

     

	error_code = NoData;
	return error_code;
}
//FCU总管理状态//数据处理
enum Error_code FCU_modbus_tatal_manager_data_data_execute(struct FCU_modbus_tatal_manager_data *  p_FCU_modbus_tatal_manager_data)
{
    enum Error_code error_code = Succeed;
  	if(p_FCU_modbus_tatal_manager_data == NULL)
  	{return Pointer_is_null;}	
  	/*
       printf("data");
  	*/  			
  	return error_code;
}
//FCU总管理状态//清除更新状态
enum Error_code FCU_modbus_tatal_manager_data_updata(struct FCU_modbus_tatal_manager_data *  p_FCU_modbus_tatal_manager_data)
{
    enum Error_code error_code = Succeed;	
  	if(p_FCU_modbus_tatal_manager_data == NULL)
  	{return Pointer_is_null;} 	
  //	p_itinerant_detective_single_board_data->is_update = 0;	
  //	p_itinerant_detective_single_board_data->updata_event_time = system_time_us;	
  	return error_code;
}





//通过通信  232 modbus格式更新串口通信数据  
enum Error_code  p_FCU_modbus_tatal_manager_data_updata_by_232_modbus_communication()
{

  	enum Error_code error_code = Succeed;
  	
 //  u8 direction_data_transmission_temp=0;
 //  u8 function_code_temp=0;
 // u8 data_length_temp=0;
 

  while(fcu_modbus_tatal_manager_data.islock == lock);

	if(fcu_modbus_tatal_manager_data.islock == unlock)
	{
		fcu_modbus_tatal_manager_data.islock = lock;
	
	   /*
	//氢气发送交换数据	
	  fcu_modbus_tatal_manager_data.hydrogen_detective_data.h2_pressure_proportional_valve_front = 
				fcu_data_buffer.h2_data_buffer.h2_pressure_proportional_valve_front;
						
	  fcu_modbus_tatal_manager_data.hydrogen_detective_data.h2_pressure_proportional_valve_rear = 
				fcu_data_buffer.h2_data_buffer.h2_pressure_proportional_valve_rear;
				
	 	fcu_modbus_tatal_manager_data.hydrogen_detective_data.h2_pressure_pile_inlet = 
				fcu_data_buffer.h2_data_buffer.h2_pressure_pile_inlet;
		
	 	fcu_modbus_tatal_manager_data.hydrogen_detective_data.h2_pressure_pile_outlet = 
				fcu_data_buffer.h2_data_buffer.h2_pressure_pile_outlet;
				
	 	fcu_modbus_tatal_manager_data.hydrogen_detective_data.h2_pressure_tail_outlet = 
				fcu_data_buffer.h2_data_buffer.h2_pressure_tail_outlet;	
				                               					
	 	fcu_modbus_tatal_manager_data.hydrogen_detective_data.h2_inlet_valve = 
				fcu_data_buffer.h2_data_buffer.h2_inlet_valve;
				
	 	fcu_modbus_tatal_manager_data.hydrogen_detective_data.h2_outlet_valve = 
				fcu_data_buffer.h2_data_buffer.h2_outlet_valve;

	 	fcu_modbus_tatal_manager_data.hydrogen_detective_data.h2_proportional_valve_pwm_dutyfactor = 
				fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pwm_dutyfactor;

	 	fcu_modbus_tatal_manager_data.hydrogen_detective_data.h2_circulating_pump_enble = 
				fcu_data_buffer.h2_data_buffer.h2_circulating_pump_enble;

	 	fcu_modbus_tatal_manager_data.hydrogen_detective_data.h2_circulating_pump_working_communication_mode = 
				fcu_data_buffer.h2_data_buffer.h2_circulating_pump_working_communication_mode;

	 	fcu_modbus_tatal_manager_data.hydrogen_detective_data.h2_circulating_pump_speed_setpoint = 
				fcu_data_buffer.h2_data_buffer.h2_circulating_pump_speed_setpoint;

	 	fcu_modbus_tatal_manager_data.hydrogen_detective_data.h2_circulating_pump_enable_pump = 
				fcu_data_buffer.h2_data_buffer.h2_circulating_pump_enable_pump;	

	 	fcu_modbus_tatal_manager_data.hydrogen_detective_data.h2_circulating_pump_actual_mass_flow = 
				fcu_data_buffer.h2_data_buffer.h2_circulating_pump_actual_mass_flow;	
				
	 	fcu_modbus_tatal_manager_data.hydrogen_detective_data.h2_circulating_pump_actual_speed = 
				fcu_data_buffer.h2_data_buffer.h2_circulating_pump_actual_speed;	
				
	 	fcu_modbus_tatal_manager_data.hydrogen_detective_data.h2_circulating_pump_actual_current = 
				fcu_data_buffer.h2_data_buffer.h2_circulating_pump_actual_current;	
				
	 	fcu_modbus_tatal_manager_data.hydrogen_detective_data.h2_circulating_pump_actual_voltage = 
				fcu_data_buffer.h2_data_buffer.h2_circulating_pump_actual_voltage;	
																																												
	 	fcu_modbus_tatal_manager_data.hydrogen_detective_data.h2_circulating_pump_actual_electronic_temperature = 
				fcu_data_buffer.h2_data_buffer.h2_circulating_pump_actual_electronic_temperature;	
				
	 	fcu_modbus_tatal_manager_data.hydrogen_detective_data.h2_pressure_target_value = 
				fcu_data_buffer.h2_data_buffer.h2_pressure_target_value;	
				
	 	fcu_modbus_tatal_manager_data.hydrogen_detective_data.h2_pressure_real_target_value = 
				fcu_data_buffer.h2_data_buffer.h2_pressure_real_target_value;	
																
	 	fcu_modbus_tatal_manager_data.hydrogen_detective_data.h2_pressure_advance_current_value = 
				fcu_data_buffer.h2_data_buffer.h2_pressure_advance_current_value;	
				
	 	fcu_modbus_tatal_manager_data.hydrogen_detective_data.h2_pressure_advance_set_value = 
				fcu_data_buffer.h2_data_buffer.h2_pressure_advance_set_value;	

	 	fcu_modbus_tatal_manager_data.hydrogen_detective_data.h2_pressure_pid1_advance_time = 
				fcu_data_buffer.h2_data_buffer.h2_pressure_pid1_advance_time;	

	 	fcu_modbus_tatal_manager_data.hydrogen_detective_data.h2_pressure_pid2_advance_time = 
				fcu_data_buffer.h2_data_buffer.h2_pressure_pid2_advance_time;	
					
	 	fcu_modbus_tatal_manager_data.hydrogen_detective_data.PID1_is_enble_pid = 
				fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid1.is_enble_pid;	
															
	 	fcu_modbus_tatal_manager_data.hydrogen_detective_data.PID1_Kp = 
				fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid1.Kp;	
				
	 	fcu_modbus_tatal_manager_data.hydrogen_detective_data.PID1_Ki =            
				fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid1.Ki;	
				
	 	fcu_modbus_tatal_manager_data.hydrogen_detective_data.PID1_Kd = 
				fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid1.Kd;
				
	 	fcu_modbus_tatal_manager_data.hydrogen_detective_data.PID2_is_enble_pid = 
				fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid2.is_enble_pid;	
															
	 	fcu_modbus_tatal_manager_data.hydrogen_detective_data.PID2_Kp = 
				fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid2.Kp;	
				
	 	fcu_modbus_tatal_manager_data.hydrogen_detective_data.PID2_Ki =            
				fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid2.Ki;	
				
	 	fcu_modbus_tatal_manager_data.hydrogen_detective_data.PID2_Kd = 
				fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid2.Kd;
								
	 	fcu_modbus_tatal_manager_data.hydrogen_detective_data.h2_pid_mode = 
				fcu_data_buffer.h2_data_buffer.h2_pid_mode;	
				
	 	fcu_modbus_tatal_manager_data.hydrogen_detective_data.h2_is_enable_outlet_valve = 
				fcu_data_buffer.h2_data_buffer.h2_is_enable_outlet_valve;	
				
	 	fcu_modbus_tatal_manager_data.hydrogen_detective_data.h2_outlet_valve_open_time = 
				fcu_data_buffer.h2_data_buffer.h2_outlet_valve_open_time;	
				
	 	fcu_modbus_tatal_manager_data.hydrogen_detective_data.h2_outlet_valve_close_time = 
				fcu_data_buffer.h2_data_buffer.h2_outlet_valve_close_time;																																	
		
	 	fcu_modbus_tatal_manager_data.hydrogen_detective_data.h2_pressure_fluctuate_last_max = 
				fcu_data_buffer.h2_data_buffer.h2_pressure_fluctuate_last_max;	
				
	 	fcu_modbus_tatal_manager_data.hydrogen_detective_data.h2_pressure_fluctuate_last_min = 
				fcu_data_buffer.h2_data_buffer.h2_pressure_fluctuate_last_min;
	
		//空气发送交换数据
		
		fcu_modbus_tatal_manager_data.air_detective_data.air_pressure_pile_inlet = 
				fcu_data_buffer.air_data_buffer.air_pressure_pile_inlet;
				
		fcu_modbus_tatal_manager_data.air_detective_data.air_pressure_pile_outlet = 
				fcu_data_buffer.air_data_buffer.air_pressure_pile_outlet;
								                                				
		fcu_modbus_tatal_manager_data.air_detective_data.air_pressure_pile_back = 
				fcu_data_buffer.air_data_buffer.air_pressure_pile_back;				
		fcu_modbus_tatal_manager_data.air_detective_data.air_temperature_pile_inlet = 
				fcu_data_buffer.air_data_buffer.air_temperature_pile_inlet;
								
		fcu_modbus_tatal_manager_data.air_detective_data.air_temperature_pile_outlet = 
				fcu_data_buffer.air_data_buffer.air_temperature_pile_outlet;
								
		fcu_modbus_tatal_manager_data.air_detective_data.air_temperature_pile_back =
	     	fcu_data_buffer.air_data_buffer.air_temperature_pile_back;		
		
		fcu_modbus_tatal_manager_data.air_detective_data.air_rate_of_flow = 
				fcu_data_buffer.air_data_buffer.air_rate_of_flow;																																					
																																						
		fcu_modbus_tatal_manager_data.air_detective_data.air_outlet_valve = 
				fcu_data_buffer.air_data_buffer.air_outlet_valve;

 		fcu_modbus_tatal_manager_data.air_detective_data.air_compressor_working_communication_mode = 
				fcu_data_buffer.air_data_buffer.air_compressor_working_communication_mode;
				
 		fcu_modbus_tatal_manager_data.air_detective_data.air_compressor_enable = 
				fcu_data_buffer.air_data_buffer.air_compressor_enable;
				
		fcu_modbus_tatal_manager_data.air_detective_data.air_compressor_speed_setpoint = 
				fcu_data_buffer.air_data_buffer.air_compressor_speed_setpoint;
				
		fcu_modbus_tatal_manager_data.air_detective_data.air_is_enable_outlet_valve = 
				fcu_data_buffer.air_data_buffer.air_is_enable_outlet_valve;
				
		fcu_modbus_tatal_manager_data.air_detective_data.air_outlet_valve_open_time = 
				fcu_data_buffer.air_data_buffer.air_outlet_valve_open_time;
				
		fcu_modbus_tatal_manager_data.air_detective_data.air_outlet_valve_close_time = 
				fcu_data_buffer.air_data_buffer.air_outlet_valve_close_time;
				
				
		//电堆散热系统数据交换			                          
   	fcu_modbus_tatal_manager_data.fell_temperature_data.water_pressure_pile_inlet = 
				fcu_data_buffer.water_for_pile_data_buffer.water_pressure_pile_inlet;

   	fcu_modbus_tatal_manager_data.fell_temperature_data.water_pressure_pile_outlet = 
				fcu_data_buffer.water_for_pile_data_buffer.water_pressure_pile_outlet;

   	fcu_modbus_tatal_manager_data.fell_temperature_data.water_temperature_pile_inlet = 
				fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_inlet;

   	fcu_modbus_tatal_manager_data.fell_temperature_data.water_temperature_pile_outlet = 
				fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_outlet;

   	fcu_modbus_tatal_manager_data.fell_temperature_data.water_pump_pwm_dutyfactor = 
				fcu_data_buffer.water_for_pile_data_buffer.water_pump_pwm_dutyfactor;

   	fcu_modbus_tatal_manager_data.fell_temperature_data.water_fan1_pwm_dutyfactor = 
				fcu_data_buffer.water_for_pile_data_buffer.water_fan1_pwm_dutyfactor;
			
  	fcu_modbus_tatal_manager_data.fell_temperature_data.water_fan2_pwm_dutyfactor = 
				fcu_data_buffer.water_for_pile_data_buffer.water_fan2_pwm_dutyfactor;
						
   	fcu_modbus_tatal_manager_data.fell_temperature_data.water_PID_is_enble_pid =
				fcu_data_buffer.water_for_pile_data_buffer.water_temperature_fan_pid.is_enble_pid;
						
   	fcu_modbus_tatal_manager_data.fell_temperature_data.water_PID_Kp = 
				fcu_data_buffer.water_for_pile_data_buffer.water_temperature_fan_pid.Kp;
		
    fcu_modbus_tatal_manager_data.fell_temperature_data.water_PID_Ki = 
				fcu_data_buffer.water_for_pile_data_buffer.water_temperature_fan_pid.Ki;

   	fcu_modbus_tatal_manager_data.fell_temperature_data.water_PID_Kd = 
				fcu_data_buffer.water_for_pile_data_buffer.water_temperature_fan_pid.Kd;
				
   	fcu_modbus_tatal_manager_data.fell_temperature_data.water_temperature_target_value = 
				fcu_data_buffer.water_for_pile_data_buffer.water_temperature_target_value;
				
				
	 //空压机散热系统数据交换
	 	fcu_modbus_tatal_manager_data.air_compressor_temperature_data.water_pressure_compressor_outlet = 
				fcu_data_buffer.water_for_compressor_data_bufferr.water_pressure_compressor_outlet;
				
	 	fcu_modbus_tatal_manager_data.air_compressor_temperature_data.water_temperature_compressor_outlet = 
				fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_compressor_outlet;
				
	 	fcu_modbus_tatal_manager_data.air_compressor_temperature_data.water_temperature_pump_outlet = 
				fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_pump_outlet;
				
	 	fcu_modbus_tatal_manager_data.air_compressor_temperature_data.water_temperature_compressor_shell = 
				fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_compressor_shell;
				
	 	fcu_modbus_tatal_manager_data.air_compressor_temperature_data.water_pump_enable = 
				fcu_data_buffer.water_for_compressor_data_bufferr.water_pump_enable;
				
	 	fcu_modbus_tatal_manager_data.air_compressor_temperature_data.water_fan_pwm_dutyfactor = 
				fcu_data_buffer.water_for_compressor_data_bufferr.water_fan_pwm_dutyfactor;
				
				
		//电堆输出数据交换
		fcu_modbus_tatal_manager_data.fell_output_data.galvanic_pile_voltage = 
				fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_voltage;
				
		fcu_modbus_tatal_manager_data.fell_output_data.galvanic_pile_electricity = 
				fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_electricity;

		fcu_modbus_tatal_manager_data.fell_output_data.fcu_start_enable = 
				fcu_data_buffer.galvanic_pile_data_buffer.fcu_start_enable;

		fcu_modbus_tatal_manager_data.fell_output_data.fcu_stutter_stop_enable = 
				fcu_data_buffer.galvanic_pile_data_buffer.fcu_stutter_stop_enable;

		fcu_modbus_tatal_manager_data.fell_output_data.galvanic_pile_is_enble_output = 
				fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_is_enble_output;

		fcu_modbus_tatal_manager_data.fell_output_data.galvanic_pile_is_enble_load_resistance = 
				fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_is_enble_load_resistance;

		fcu_modbus_tatal_manager_data.fell_output_data.itinerant_detective_working_communication_mode = 
				fcu_data_buffer.galvanic_pile_data_buffer.itinerant_detective_working_communication_mode;

		fcu_modbus_tatal_manager_data.fell_output_data.itinerant_detective_working_statas = 
				fcu_data_buffer.galvanic_pile_data_buffer.itinerant_detective_working_statas;

		fcu_modbus_tatal_manager_data.fell_output_data.Single_battery_overvoltage_alarm = 
				fcu_data_buffer.galvanic_pile_data_buffer.Single_battery_overvoltage_alarm;

		fcu_modbus_tatal_manager_data.fell_output_data.Single_battery_undervoltage_alarm = 
				fcu_data_buffer.galvanic_pile_data_buffer.Single_battery_undervoltage_alarm;

		fcu_modbus_tatal_manager_data.fell_output_data.Single_voltage_unbalance_alarm = 
				fcu_data_buffer.galvanic_pile_data_buffer.Single_voltage_unbalance_alarm;

		fcu_modbus_tatal_manager_data.fell_output_data.electric1_mean_voltage = 
				fcu_data_buffer.galvanic_pile_data_buffer.electric1_mean_voltage;

		fcu_modbus_tatal_manager_data.fell_output_data.electric1_single_chip_highest_voltage = 
				fcu_data_buffer.galvanic_pile_data_buffer.electric1_single_chip_highest_voltage;

		fcu_modbus_tatal_manager_data.fell_output_data.electric1_single_chip_highest_voltage_num = 
				fcu_data_buffer.galvanic_pile_data_buffer.electric1_single_chip_highest_voltage_num;

		fcu_modbus_tatal_manager_data.fell_output_data.electric1_single_chip_minimum_voltage = 
				fcu_data_buffer.galvanic_pile_data_buffer.electric1_single_chip_minimum_voltage;

		fcu_modbus_tatal_manager_data.fell_output_data.electric1_single_chip_minimum_voltage_num = 
				fcu_data_buffer.galvanic_pile_data_buffer.electric1_single_chip_minimum_voltage_num;

		fcu_modbus_tatal_manager_data.fell_output_data.itinerant_detective_total_voltage = 
				fcu_data_buffer.galvanic_pile_data_buffer.itinerant_detective_total_voltage;
				
		//FCU运行状态数据交换
		
    fcu_modbus_tatal_manager_data.fcu_run_stata_data.FCU_control_mode=
		  control_policy_total_manager.working_control_mode;
		  
		fcu_modbus_tatal_manager_data.fcu_run_stata_data.FCU_work_mode=
		  control_policy_total_manager.working_status_mode;

    fcu_modbus_tatal_manager_data.fcu_run_stata_data.FCU_alarm_mode=
		  control_policy_total_manager.working_alarm_mode;

    fcu_modbus_tatal_manager_data.fcu_run_stata_data.FCU_error_code=
		  control_policy_total_manager.working_FCU_error_code;

    fcu_modbus_tatal_manager_data.fcu_run_stata_data.FCU_erroring_control_mode=
		  control_policy_total_manager.working_FCU_error_control_mode;

    fcu_modbus_tatal_manager_data.fcu_run_stata_data.FCU_system_run_mode=
		  control_policy_total_manager.fcu_system_running_mode;
		  	 	
    */	
	  fcu_modbus_tatal_manager_data.islock = unlock;	
	}
  	

	return error_code;	
    
   
}


//把一个float数值分解成4个内存单元 通过指针传出来
void float_convert_four_byte(float *f,unsigned char *a,unsigned char *b,unsigned char *c,unsigned char *d)
{
	unsigned char * p_f=(unsigned char *)f;
	*a= *(p_f);
	*b=*(p_f+1);
	*c=*(p_f+2);
	*d=*(p_f+3);
} 


//把float的四个内存内存单元的值转换成一个float
float four_byte_convert_float(unsigned char a,unsigned char b,unsigned char c,unsigned char d) 
{
	float ff=0;
	unsigned char * p_ff=(unsigned char*)&ff;
	*p_ff=a;
	*(p_ff+1)=b;
	*(p_ff+2)=c;
	*(p_ff+3)=d;
	return ff;
}




enum Error_code modbus_232_receive_to_databuff(struct Modbus_Data_Buffer * p_modbus_receive_data_buffer,struct FCU_Data_Buffer * p_FCU_Data_Buffer,struct Control_Policy_Total_Manager *p_Control_Policy_Total_Manager)
{
 
 	enum Error_code error_code = Succeed;
 
 	
    u8 direction_data_transmission_temp=0;
   u8 function_code_temp=0;
   u8 data_length_temp=0;
    
   		
		  		  
	   //计算机发给FCU的命令数据交换

    direction_data_transmission_temp = p_modbus_receive_data_buffer->direction_data_transmission;
    function_code_temp = p_modbus_receive_data_buffer->function_code;
    data_length_temp = p_modbus_receive_data_buffer->data_length;
 
    	 
           
    if(direction_data_transmission_temp==0xaa && data_length_temp==0x04)
        {
                        
                           
          	switch(function_code_temp)
      			{
      			      
      	
      		      
      				case 1:
      				
      				p_FCU_Data_Buffer->h2_data_buffer.h2_inlet_valve =
      				p_modbus_receive_data_buffer->modbus_data[3];
      			
      				
      				break;
      				
      				case 2:
      	    		p_FCU_Data_Buffer->h2_data_buffer.h2_is_enable_outlet_valve =
                   	p_modbus_receive_data_buffer->modbus_data[3]; 
      				break;	
      					
      				
      				case 3:
      				p_FCU_Data_Buffer->h2_data_buffer.h2_outlet_valve_open_time =
      				      	((u32)(	p_modbus_receive_data_buffer->modbus_data[3]))<<24 |
      				      	((u32)(	p_modbus_receive_data_buffer->modbus_data[2]))<16  |
      				        ((u32)(	p_modbus_receive_data_buffer->modbus_data[1]))<<8  |
      				      	((u32)(	p_modbus_receive_data_buffer->modbus_data[0]));    
      				    
      				      	
      				      	break;	
      				      	
      				  	   	
      				case 4:
      		    	p_FCU_Data_Buffer->h2_data_buffer.h2_outlet_valve_close_time =
      				      	((u32)(	p_modbus_receive_data_buffer->modbus_data[3]))<<24 |
      				      	((u32)(	p_modbus_receive_data_buffer->modbus_data[2]))<<16 |
      				        ((u32)(	p_modbus_receive_data_buffer->modbus_data[1]))<<8  |
      				      	((u32)(	p_modbus_receive_data_buffer->modbus_data[0]));      
       				      	break;
      			
      			    	      			
      				case 5:
      		         p_FCU_Data_Buffer->h2_data_buffer.h2_proportional_valve_pwm_dutyfactor =
      				        four_byte_convert_float(	p_modbus_receive_data_buffer->modbus_data[0],	p_modbus_receive_data_buffer->modbus_data[1],
      				                                	p_modbus_receive_data_buffer->modbus_data[2],	p_modbus_receive_data_buffer->modbus_data[3]);
      				                                	
      				                           	
      				      	break;
      				      	
      				      
      				case 6:
      		    	 p_FCU_Data_Buffer->h2_data_buffer.h2_circulating_pump_enble =
      			    	p_modbus_receive_data_buffer->modbus_data[3]; 
       				
      				      	break;
 				      	
      				case 7:
      		    	 p_FCU_Data_Buffer->h2_data_buffer.h2_circulating_pump_enable_pump =
      			    	p_modbus_receive_data_buffer->modbus_data[3]; 
      				
      				      	break;
      				      	
      				      	
      				 case 8:
      		 /*   	p_FCU_Data_Buffer->h2_data_buffer.h2_circulating_pump_speed_setpoint = 
      				      	(u16)(((u32)(	p_modbus_receive_data_buffer->modbus_data[3]))<<24 |
      				            	((u32)(	p_modbus_receive_data_buffer->modbus_data[2]))<<16 |
      				              ((u32)(	p_modbus_receive_data_buffer->modbus_data[1]))<<8  |
      				            	((u32)(	p_modbus_receive_data_buffer->modbus_data[0])));       */
      				p_FCU_Data_Buffer->h2_data_buffer.h2_circulating_pump_speed_setpoint = 
      				      	(u16)( ((u16)(	p_modbus_receive_data_buffer->modbus_data[3]))<<8  |
      				            	((u16)(	p_modbus_receive_data_buffer->modbus_data[2])));             	
      				      	    
       				      	break;     	
      				      	     	
      				case 9:
      		         p_FCU_Data_Buffer->h2_data_buffer.h2_pressure_target_value =
      				        four_byte_convert_float(	p_modbus_receive_data_buffer->modbus_data[0],	p_modbus_receive_data_buffer->modbus_data[1],
      				                                	p_modbus_receive_data_buffer->modbus_data[2],	p_modbus_receive_data_buffer->modbus_data[3]);
     				 
      				      	break;
      				case 10:
       		         p_FCU_Data_Buffer->h2_data_buffer.h2_pressure_advance_set_value =
      				        four_byte_convert_float(	p_modbus_receive_data_buffer->modbus_data[0],	p_modbus_receive_data_buffer->modbus_data[1],
      				                                	p_modbus_receive_data_buffer->modbus_data[2],	p_modbus_receive_data_buffer->modbus_data[3]);
      				      	break;
      				case 11:
      		    	 p_FCU_Data_Buffer->h2_data_buffer.h2_proportional_valve_pid1.is_enble_pid =
      			    	p_modbus_receive_data_buffer->modbus_data[3]; 
      				
      				      	break;
      				case 12:
       		         p_FCU_Data_Buffer->h2_data_buffer.h2_proportional_valve_pid1.Kp =
      				        four_byte_convert_float(	p_modbus_receive_data_buffer->modbus_data[0],	p_modbus_receive_data_buffer->modbus_data[1],
      				                                	p_modbus_receive_data_buffer->modbus_data[2],	p_modbus_receive_data_buffer->modbus_data[3]);
      				      	break;
      				case 13:
       		         p_FCU_Data_Buffer->h2_data_buffer.h2_proportional_valve_pid1.Ki =
      				        four_byte_convert_float(	p_modbus_receive_data_buffer->modbus_data[0],	p_modbus_receive_data_buffer->modbus_data[1],
      				                                	p_modbus_receive_data_buffer->modbus_data[2],	p_modbus_receive_data_buffer->modbus_data[3]);
      				      	break;
      				case 14:
       		         p_FCU_Data_Buffer->h2_data_buffer.h2_proportional_valve_pid1.Kd =
      				        four_byte_convert_float(	p_modbus_receive_data_buffer->modbus_data[0],	p_modbus_receive_data_buffer->modbus_data[1],
      				                                	p_modbus_receive_data_buffer->modbus_data[2],	p_modbus_receive_data_buffer->modbus_data[3]);
      				      	break;

      				case 15:
      		    	 p_FCU_Data_Buffer->h2_data_buffer.h2_proportional_valve_pid2.is_enble_pid =
      			    	p_modbus_receive_data_buffer->modbus_data[3]; 
      				
      				      	break;
      				case 16:
       		         p_FCU_Data_Buffer->h2_data_buffer.h2_proportional_valve_pid2.Kp =
      				        four_byte_convert_float(	p_modbus_receive_data_buffer->modbus_data[0],	p_modbus_receive_data_buffer->modbus_data[1],
      				                                	p_modbus_receive_data_buffer->modbus_data[2],	p_modbus_receive_data_buffer->modbus_data[3]);
      				      	break;
      				case 17:
       		         p_FCU_Data_Buffer->h2_data_buffer.h2_proportional_valve_pid2.Ki =
      				        four_byte_convert_float(	p_modbus_receive_data_buffer->modbus_data[0],	p_modbus_receive_data_buffer->modbus_data[1],
      				                                	p_modbus_receive_data_buffer->modbus_data[2],	p_modbus_receive_data_buffer->modbus_data[3]);
      				      	break;
      				case 18:
       		         p_FCU_Data_Buffer->h2_data_buffer.h2_proportional_valve_pid2.Kd =
      				        four_byte_convert_float(	p_modbus_receive_data_buffer->modbus_data[0],	p_modbus_receive_data_buffer->modbus_data[1],
      				                                	p_modbus_receive_data_buffer->modbus_data[2],	p_modbus_receive_data_buffer->modbus_data[3]);
      				      	break;
      				      	
      				case 19:
      		    	 p_FCU_Data_Buffer->h2_data_buffer.h2_pid_mode =
      			    	p_modbus_receive_data_buffer->modbus_data[3]; 
      			    	 hushui1_test=  p_FCU_Data_Buffer->h2_data_buffer.h2_pid_mode;
      			    	//hushui1_test++;
      				
      				      	break;
     			  	case 20:
      		    	 p_FCU_Data_Buffer->air_data_buffer.air_is_enable_outlet_valve =
      			    	p_modbus_receive_data_buffer->modbus_data[3]; 
      				
      				      	break;
      					
      				
      				case 21:
      				p_FCU_Data_Buffer->air_data_buffer.air_outlet_valve_open_time =
      				      	((u32)(	p_modbus_receive_data_buffer->modbus_data[3]))<<24 |
      				      	((u32)(	p_modbus_receive_data_buffer->modbus_data[2]))<<16 |
      				        ((u32)(	p_modbus_receive_data_buffer->modbus_data[1]))<<8  |
      				      	((u32)(	p_modbus_receive_data_buffer->modbus_data[0]));      
      				      	
      				      	break;
      				      	
      				     		
      				case 22:
      				p_FCU_Data_Buffer->air_data_buffer.air_outlet_valve_close_time =
      				      	((u32)(	p_modbus_receive_data_buffer->modbus_data[3]))<<24 |
      				      	((u32)(	p_modbus_receive_data_buffer->modbus_data[2]))<<16 |
      				        ((u32)(	p_modbus_receive_data_buffer->modbus_data[1]))<<8  |
      				      	((u32)(	p_modbus_receive_data_buffer->modbus_data[0]));      
      				      	
      				      	break;	
      				      	
                    
     				case 23:
      		    	 p_FCU_Data_Buffer->air_data_buffer.air_compressor_enable =
      			    	p_modbus_receive_data_buffer->modbus_data[3]; 
      				
      				      	break;
      				case 24:
      				p_FCU_Data_Buffer->air_data_buffer.air_compressor_speed_setpoint =
      				      	((u32)(	p_modbus_receive_data_buffer->modbus_data[3]))<<24 |
      				      	((u32)(	p_modbus_receive_data_buffer->modbus_data[2]))<<16 |
      				        ((u32)(	p_modbus_receive_data_buffer->modbus_data[1]))<<8  |
      				      	((u32)(	p_modbus_receive_data_buffer->modbus_data[0]));      
      				      	
      				      	break;	
      			/*	      	
      				case 25:
       		         p_FCU_Data_Buffer->water_for_pile_data_buffer.water_pump_pwm_dutyfactor =
      				        four_byte_convert_float(	p_modbus_receive_data_buffer->modbus_data[0],	p_modbus_receive_data_buffer->modbus_data[1],
      				                                	p_modbus_receive_data_buffer->modbus_data[2],	p_modbus_receive_data_buffer->modbus_data[3]);
      				      	break;
      				case 26:
       		         p_FCU_Data_Buffer->water_for_pile_data_buffer.water_fan1_pwm_dutyfactor =
      				        four_byte_convert_float(	p_modbus_receive_data_buffer->modbus_data[0],	p_modbus_receive_data_buffer->modbus_data[1],
      				                                	p_modbus_receive_data_buffer->modbus_data[2],	p_modbus_receive_data_buffer->modbus_data[3]);
      				      	break;
      				case 27:
       		         p_FCU_Data_Buffer->water_for_pile_data_buffer.water_fan2_pwm_dutyfactor =
      				        four_byte_convert_float(	p_modbus_receive_data_buffer->modbus_data[0],	p_modbus_receive_data_buffer->modbus_data[1],
      				                                	p_modbus_receive_data_buffer->modbus_data[2],	p_modbus_receive_data_buffer->modbus_data[3]);
      			    	    break; 
      				case 28:
      		    	 p_FCU_Data_Buffer->water_for_pile_data_buffer.water_temperature_fan_pid.is_enble_pid =
      			    	p_modbus_receive_data_buffer->modbus_data[3]; 
                       	     break; 
 
       				case 29:
       		         p_FCU_Data_Buffer->water_for_pile_data_buffer.water_temperature_fan_pid.Kp =
      				        four_byte_convert_float(	p_modbus_receive_data_buffer->modbus_data[0],	p_modbus_receive_data_buffer->modbus_data[1],
      				                                	p_modbus_receive_data_buffer->modbus_data[2],	p_modbus_receive_data_buffer->modbus_data[3]);
      				      	break;
      				case 30:
       		         p_FCU_Data_Buffer->water_for_pile_data_buffer.water_temperature_fan_pid.Ki =
      				        four_byte_convert_float(	p_modbus_receive_data_buffer->modbus_data[0],	p_modbus_receive_data_buffer->modbus_data[1],
      				                                	p_modbus_receive_data_buffer->modbus_data[2],	p_modbus_receive_data_buffer->modbus_data[3]);
      				      	break;
      				case 31:
       		         p_FCU_Data_Buffer->water_for_pile_data_buffer.water_temperature_fan_pid.Kd =
      				        four_byte_convert_float(	p_modbus_receive_data_buffer->modbus_data[0],	p_modbus_receive_data_buffer->modbus_data[1],
      				                                	p_modbus_receive_data_buffer->modbus_data[2],	p_modbus_receive_data_buffer->modbus_data[3]);
                           	break;
       				case 32:
       		         p_FCU_Data_Buffer->water_for_pile_data_buffer.water_temperature_target_value =
      				        four_byte_convert_float(	p_modbus_receive_data_buffer->modbus_data[0],	p_modbus_receive_data_buffer->modbus_data[1],
      				                                  	p_modbus_receive_data_buffer->modbus_data[2],	p_modbus_receive_data_buffer->modbus_data[3]);
       			            break; 
       				case 33:
      		    	 p_FCU_Data_Buffer->water_for_compressor_data_bufferr.water_pump_enable =
      			    	p_modbus_receive_data_buffer->modbus_data[3]; 
       		
        		        	break;
         			case 34:
       		         p_FCU_Data_Buffer->water_for_compressor_data_bufferr.water_fan_pwm_dutyfactor =
      				        four_byte_convert_float(	p_modbus_receive_data_buffer->modbus_data[0],	p_modbus_receive_data_buffer->modbus_data[1],
      				                                	p_modbus_receive_data_buffer->modbus_data[2],	p_modbus_receive_data_buffer->modbus_data[3]);
      		            	break;
        			case 35:
      		    	 p_FCU_Data_Buffer->galvanic_pile_data_buffer.fcu_start_enable =
      			    	p_modbus_receive_data_buffer->modbus_data[3]; 
      			    		break;
       				case 36:
      		    	 p_FCU_Data_Buffer->galvanic_pile_data_buffer.fcu_stutter_stop_enable =
      			    	p_modbus_receive_data_buffer->modbus_data[3]; 
      			    		break;
       				case 37:
      		    	 p_FCU_Data_Buffer->galvanic_pile_data_buffer.galvanic_pile_is_enble_output =
      			    	p_modbus_receive_data_buffer->modbus_data[3]; 
      			    		break;
       				case 38:
      		    	 p_FCU_Data_Buffer->galvanic_pile_data_buffer.galvanic_pile_is_enble_load_resistance =
      			    	p_modbus_receive_data_buffer->modbus_data[3]; 
      			    		break;
      			    	
       			
       				      	
       				case 39:
      		    	 p_Control_Policy_Total_Manager->fcu_system_running_mode =
      	        	   	p_modbus_receive_data_buffer->modbus_data[3]; 
      			    		break;
      			    		
      			   */ 	
        				      	
       				      	
       				default:
       				        break;      	
       				      	
       			
      			}  	
      		
	     }
	     
	     
	     
	     
	     
		return error_code;	
		
 
    
}




/*
                                                                   
void  modbus_232_PC_To_FCU_data_convert(&(p_FCU_modbus_tatal_manager_data->fcu_receive_orde_data))			
{

     u8 direction_data_transmission_temp=0;
     u8 function_code_temp=0;
     u8 data_length_temp=0;

   	if(p_modbus_receive_data_buffer == NULL || p_FCU_modbus_tatal_manager_data == NULL)
    	{return ;}

    	direction_data_transmission_temp=p_modbus_receive_data_buffer->direction_data_transmission;
    	function_code_temp=p_modbus_receive_data_buffer->function_code;
      data_length_temp=p_modbus_receive_data_buffer->data_length;
      
      
        if(direction_data_transmission_temp==0xbb && data_length_temp==0x04)
        {
        
          	switch(function_code_temp)
      			{
      				case 1:
      				
      			      	p_FCU_modbus_tatal_manager_data->hydrogen_detective_data.h2_inlet_valve=p_modbus_receive_data_buffer->modbus_data[3];
      				      	break;
      				case 2:
      				     	p_FCU_modbus_tatal_manager_data->hydrogen_detective_data.h2_is_enable_outlet_valve=p_modbus_receive_data_buffer->modbus_data[3];
      				
      				      	break;	
      				case 3:
      				      	p_FCU_modbus_tatal_manager_data->hydrogen_detective_data.h2_outlet_valve_open_time=
      				      	((u32)(p_modbus_receive_data_buffer->modbus_data[0]))<<24 |
      				      	((u32)(p_modbus_receive_data_buffer->modbus_data[1]))<<16 |
      				        ((u32)(p_modbus_receive_data_buffer->modbus_data[2]))<<8  |
      				      	((u32)(p_modbus_receive_data_buffer->modbus_data[3]));      
      				      	
      				      	break;	
      				case 4:
      			      	p_FCU_modbus_tatal_manager_data->hydrogen_detective_data.h2_outlet_valve_close_time=
      				      	((u32)(p_modbus_receive_data_buffer->modbus_data[0]))<<24 |
      				      	((u32)(p_modbus_receive_data_buffer->modbus_data[1]))<<16 |
      				        ((u32)(p_modbus_receive_data_buffer->modbus_data[2]))<<8  |
      				      	((u32)(p_modbus_receive_data_buffer->modbus_data[3])); 		      
      				      	break;	
      				case 5:
      				        p_FCU_modbus_tatal_manager_data->hydrogen_detective_data.h2_proportional_valve_pwm_dutyfactor=
      				        four_byte_convert_float(p_modbus_receive_data_buffer->modbus_data[0],p_modbus_receive_data_buffer->modbus_data[1],
      				                                p_modbus_receive_data_buffer->modbus_data[2],p_modbus_receive_data_buffer->modbus_data[3]);
      				      	break;	
      				case 6:
      				       	p_FCU_modbus_tatal_manager_data->hydrogen_detective_data.h2_circulating_pump_enble=p_modbus_receive_data_buffer->modbus_data[3];
      				
      				      	break;
      						case 7:
      				       	p_FCU_modbus_tatal_manager_data->hydrogen_detective_data.h2_circulating_pump_enable_pump=p_modbus_receive_data_buffer->modbus_data[3];
      				
      				      	break;
      						case 8:
      				        p_FCU_modbus_tatal_manager_data->hydrogen_detective_data.h2_pressure_target_value=
      				        four_byte_convert_float(p_modbus_receive_data_buffer->modbus_data[0],p_modbus_receive_data_buffer->modbus_data[1],
      				                                p_modbus_receive_data_buffer->modbus_data[2],p_modbus_receive_data_buffer->modbus_data[3]);
      				
      				      	break;
      						case 9:
							        p_FCU_modbus_tatal_manager_data->hydrogen_detective_data.h2_pressure_advance_set_value=
      				        four_byte_convert_float(p_modbus_receive_data_buffer->modbus_data[0],p_modbus_receive_data_buffer->modbus_data[1],
      				                                p_modbus_receive_data_buffer->modbus_data[2],p_modbus_receive_data_buffer->modbus_data[3]);				
      				      	break;
      					case 10:
      				       	p_FCU_modbus_tatal_manager_data->hydrogen_detective_data.PID1_is_enble_pid=p_modbus_receive_data_buffer->modbus_data[3];
      				
      				      	break;
               	case 11:
				              p_FCU_modbus_tatal_manager_data->hydrogen_detective_data.PID1_Kp=
      				        four_byte_convert_float(p_modbus_receive_data_buffer->modbus_data[0],p_modbus_receive_data_buffer->modbus_data[1],
      				                                p_modbus_receive_data_buffer->modbus_data[2],p_modbus_receive_data_buffer->modbus_data[3]);				
            				
      					      break;
      						case 12:
	                     p_FCU_modbus_tatal_manager_data->hydrogen_detective_data.PID1_Ki=
      				        four_byte_convert_float(p_modbus_receive_data_buffer->modbus_data[0],p_modbus_receive_data_buffer->modbus_data[1],
      				                                p_modbus_receive_data_buffer->modbus_data[2],p_modbus_receive_data_buffer->modbus_data[3]);				
              				
      				      	break;
      						case 13:
	                     p_FCU_modbus_tatal_manager_data->hydrogen_detective_data.PID1_Kd=
      				        four_byte_convert_float(p_modbus_receive_data_buffer->modbus_data[0],p_modbus_receive_data_buffer->modbus_data[1],
      				                                p_modbus_receive_data_buffer->modbus_data[2],p_modbus_receive_data_buffer->modbus_data[3]);				
              				
      				      	break;
      						case 14:
      				       	p_FCU_modbus_tatal_manager_data->hydrogen_detective_data.PID2_is_enble_pid=p_modbus_receive_data_buffer->modbus_data[3];
      				
      				      	break;
      						case 15:
      				       	p_FCU_modbus_tatal_manager_data->hydrogen_detective_data.PID2_Kp=p_modbus_receive_data_buffer->modbus_data[3];
      				
      				      	break;
      						case 16:
      				       	p_FCU_modbus_tatal_manager_data->hydrogen_detective_data.PID2_Ki=p_modbus_receive_data_buffer->modbus_data[3];
      				
      				      	break;
      						case 17:
      				       	p_FCU_modbus_tatal_manager_data->hydrogen_detective_data.PID2_Kd=p_modbus_receive_data_buffer->modbus_data[3];
      				
      				      	break;
      						case 18:
      				       	p_FCU_modbus_tatal_manager_data->hydrogen_detective_data.h2_pid_mode=p_modbus_receive_data_buffer->modbus_data[3];
      				
      				      	break;
      						case 19:
      				       	p_FCU_modbus_tatal_manager_data->air_detective_data.air_is_enable_outlet_valve=p_modbus_receive_data_buffer->modbus_data[3];
      				
      				      	break;
      				      	
      				      	
      				      				      
      				      	 
      						case 20:
     			        	 	p_FCU_modbus_tatal_manager_data->air_detective_data.air_outlet_valve_open_time=
          				      	((u32)(p_modbus_receive_data_buffer->modbus_data[0]))<<24 |
          				      	((u32)(p_modbus_receive_data_buffer->modbus_data[1]))<<16 |
          				        ((u32)(p_modbus_receive_data_buffer->modbus_data[2]))<<8  |
          				      	((u32)(p_modbus_receive_data_buffer->modbus_data[3])); 	
      				      	break;
      						case 21:
                    	p_FCU_modbus_tatal_manager_data->air_detective_data.air_outlet_valve_close_time=
          				      	((u32)(p_modbus_receive_data_buffer->modbus_data[0]))<<24 |
          				      	((u32)(p_modbus_receive_data_buffer->modbus_data[1]))<<16 |
          				        ((u32)(p_modbus_receive_data_buffer->modbus_data[2]))<<8  |
          				      	((u32)(p_modbus_receive_data_buffer->modbus_data[3])); 	     				
      					      break;
      						case 22:
      				       	p_FCU_modbus_tatal_manager_data->air_detective_data.air_compressor_enable=p_modbus_receive_data_buffer->modbus_data[3];
      				
      				      	break;
      						case 23:
      				       	p_FCU_modbus_tatal_manager_data->air_detective_data.air_compressor_speed_setpoint=p_modbus_receive_data_buffer->modbus_data[3];
      				
      				      	break;
      						case 24:
	                     p_FCU_modbus_tatal_manager_data->fell_temperature_data.water_pump_pwm_dutyfactor=
      				        four_byte_convert_float(p_modbus_receive_data_buffer->modbus_data[0],p_modbus_receive_data_buffer->modbus_data[1],
      				                                p_modbus_receive_data_buffer->modbus_data[2],p_modbus_receive_data_buffer->modbus_data[3]);				
        				
      				        break;
      						case 25:
	                     p_FCU_modbus_tatal_manager_data->fell_temperature_data.water_fan1_pwm_dutyfactor=
      				        four_byte_convert_float(p_modbus_receive_data_buffer->modbus_data[0],p_modbus_receive_data_buffer->modbus_data[1],
      				                                p_modbus_receive_data_buffer->modbus_data[2],p_modbus_receive_data_buffer->modbus_data[3]);				
        				
      				      	break;
      				      	
      				     case 26:
	                     p_FCU_modbus_tatal_manager_data->fell_temperature_data.water_fan2_pwm_dutyfactor=
      				        four_byte_convert_float(p_modbus_receive_data_buffer->modbus_data[0],p_modbus_receive_data_buffer->modbus_data[1],
      				                                p_modbus_receive_data_buffer->modbus_data[2],p_modbus_receive_data_buffer->modbus_data[3]);				
        				
      				      	break;
      				     case 27:
      				       	p_FCU_modbus_tatal_manager_data->fell_temperature_data.water_PID_is_enble_pid=p_modbus_receive_data_buffer->modbus_data[3];
      				
      				      	break;
      				    	case 28:
	                     p_FCU_modbus_tatal_manager_data->fell_temperature_data.water_PID_Kp=
      				        four_byte_convert_float(p_modbus_receive_data_buffer->modbus_data[0],p_modbus_receive_data_buffer->modbus_data[1],
      				                                p_modbus_receive_data_buffer->modbus_data[2],p_modbus_receive_data_buffer->modbus_data[3]);				
      				
      				      	break;
      				     	case 29:
                    p_FCU_modbus_tatal_manager_data->fell_temperature_data.water_PID_Ki=
      				        four_byte_convert_float(p_modbus_receive_data_buffer->modbus_data[0],p_modbus_receive_data_buffer->modbus_data[1],
      				                                p_modbus_receive_data_buffer->modbus_data[2],p_modbus_receive_data_buffer->modbus_data[3]);				
         				
      				      	break;
      				     	case 30:
                    p_FCU_modbus_tatal_manager_data->fell_temperature_data.water_PID_Kd=
      				        four_byte_convert_float(p_modbus_receive_data_buffer->modbus_data[0],p_modbus_receive_data_buffer->modbus_data[1],
      				                                p_modbus_receive_data_buffer->modbus_data[2],p_modbus_receive_data_buffer->modbus_data[3]);				
         				
      				      	break;
      				      case 31:
                    p_FCU_modbus_tatal_manager_data->fell_temperature_data.water_temperature_target_value=
      				        four_byte_convert_float(p_modbus_receive_data_buffer->modbus_data[0],p_modbus_receive_data_buffer->modbus_data[1],
      				                                p_modbus_receive_data_buffer->modbus_data[2],p_modbus_receive_data_buffer->modbus_data[3]);				
         				
      				      	break;
      				     	case 32:
      				       	p_FCU_modbus_tatal_manager_data->air_compressor_temperature_data.water_pump_enable=p_modbus_receive_data_buffer->modbus_data[3];
      				
      				      	break;

      					  	case 33:
      				       	p_FCU_modbus_tatal_manager_data->air_compressor_temperature_data.water_fan_pwm_dutyfactor=p_modbus_receive_data_buffer->modbus_data[3];
      				
      				      	break;
      				     case 34:
      				       	p_FCU_modbus_tatal_manager_data->fell_output_data.fcu_start_enable=p_modbus_receive_data_buffer->modbus_data[3];
      				
      				      	break;
      				     	case 35:
      				       	p_FCU_modbus_tatal_manager_data->fell_output_data.fcu_stutter_stop_enable=p_modbus_receive_data_buffer->modbus_data[3];
      				
      				      	break;
      				      case 36:
      				       	p_FCU_modbus_tatal_manager_data->fell_output_data.galvanic_pile_is_enble_output=p_modbus_receive_data_buffer->modbus_data[3];
      				
      				      	break;
      					  	case 37:
      				         	p_FCU_modbus_tatal_manager_data->fell_output_data.galvanic_pile_is_enble_load_resistance=p_modbus_receive_data_buffer->modbus_data[3];   				
      				      	break;
      				      case 38:
      				       	p_FCU_modbus_tatal_manager_data->FCU_system_run_mode=p_modbus_receive_data_buffer->modbus_data[3];
      				      	break;
      				default:
      				      break;
      				
      			}
        }	
        
        
}
*/
  
   









