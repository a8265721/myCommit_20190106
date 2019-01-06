#include "can_communication_protocol.h"
#include "error_system.h"
#include "pit.h"

//can通信协议汇总
struct Can_Communication_Protocol_Total    can_communication_protocol_total;

//温度采集数据//初始化
enum Error_code temperature_data_acquisition_init(struct Temperature_Data_Acquisition *  p_temperature_data_acquisition)
{
	enum Error_code error_code = Succeed;

	if(p_temperature_data_acquisition == NULL )
	{return Pointer_is_null;}

	p_temperature_data_acquisition->updata_event_time = system_time;
	p_temperature_data_acquisition->overtime_max = CAN_OVERTIME_MAX;
	p_temperature_data_acquisition->Message_id = TEMPERATURE_DATA_ACQUISITION_MESSAGE_ID;

	p_temperature_data_acquisition->DCDC_heartbeat_frame = 0;
	return error_code;
}

//温度采集数据//数据解析
enum Error_code temperature_data_acquisition_analysis(CAN_message * p_can_msg, struct Temperature_Data_Acquisition *  p_temperature_data_acquisition)
{
	enum Error_code error_code = Succeed;

	if(p_can_msg == NULL || p_temperature_data_acquisition == NULL)
	{return Pointer_is_null;}

	if(p_temperature_data_acquisition->Message_id != p_can_msg->can_message_id)
	{
		error_code =  CAN_data_analysis_id_error;
	}
	else
	{
		p_temperature_data_acquisition->updata_event_time = system_time;

		fcu_data_buffer.air_data_buffer.air_temperature_pile_inlet = (float)(p_can_msg->can_data[0]) - 40;
		fcu_data_buffer.air_data_buffer.air_temperature_pile_outlet = (float)(p_can_msg->can_data[1]) - 40;
		fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_inlet = (float)(p_can_msg->can_data[2]) - 40;
		fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_outlet = (float)(p_can_msg->can_data[3]) - 40;
		fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_compressor_outlet = (float)(p_can_msg->can_data[4]) - 40;
		fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_intercooler_outlet = (float)(p_can_msg->can_data[5]) - 40;
		fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_compressor_shell = (float)(p_can_msg->can_data[6]) - 40;

		p_temperature_data_acquisition->DCDC_heartbeat_frame = p_can_msg->can_data[7];
	}


	return error_code;
}

//温度采集数据//数据封装
enum Error_code temperature_data_acquisition_encapsulation(struct Temperature_Data_Acquisition *  p_temperature_data_acquisition, CAN_message * p_can_msg)
{
	return Succeed;
}

//温度采集数据//数据处理
enum Error_code temperature_data_acquisition_execute(struct Temperature_Data_Acquisition *  p_temperature_data_acquisition)
{
	return Succeed;
}





//压力采集数据1//初始化
enum Error_code pressure_data1_acquisition_init(struct Pressure_Data1_Acquisition *  p_pressure_data1_acquisition)
{
	enum Error_code error_code = Succeed;

	if(p_pressure_data1_acquisition == NULL )
	{return Pointer_is_null;}

	p_pressure_data1_acquisition->updata_event_time = system_time;
	p_pressure_data1_acquisition->overtime_max = CAN_OVERTIME_MAX;
	p_pressure_data1_acquisition->Message_id = PRESSURE_DATA1_ACQUISITION_MESSAGE_ID;

	return error_code;
}

//压力采集数据1//数据解析
enum Error_code pressure_data1_acquisition_analysis(CAN_message * p_can_msg, struct Pressure_Data1_Acquisition *  p_pressure_data1_acquisition)
{
	enum Error_code error_code = Succeed;
	u16	temp;

	if(p_can_msg == NULL || p_pressure_data1_acquisition == NULL)
	{return Pointer_is_null;}

	if(p_pressure_data1_acquisition->Message_id != p_can_msg->can_message_id)
	{
		error_code =  CAN_data_analysis_id_error;
	}
	else
	{
		p_pressure_data1_acquisition->updata_event_time = system_time;

		temp = ((u16)(p_can_msg->can_data[0])) | ((u16)(p_can_msg->can_data[1]))<<8;
		//		fcu_data_buffer.h2_data_buffer.h2_pressure_proportional_valve_front = ( ((float)temp) * 5000 / 4095 / 235 - 4 ) / 16 * 1000;
		temp = ((u16)(p_can_msg->can_data[2])) | ((u16)(p_can_msg->can_data[3]))<<8;
		//		fcu_data_buffer.h2_data_buffer.h2_pressure_proportional_valve_rear = ( ((float)temp) * 5000 / 4095 / 235 - 4 ) / 16 * 150;
		temp = ((u16)(p_can_msg->can_data[4])) | ((u16)(p_can_msg->can_data[5]))<<8;
		fcu_data_buffer.h2_data_buffer.h2_pressure_tail_outlet = ( ((float)temp) * 5000 / 4095 / 235 - 4 ) / 16 * 150;
		temp = ((u16)(p_can_msg->can_data[6])) | ((u16)(p_can_msg->can_data[7]))<<8;
		fcu_data_buffer.air_data_buffer.air_pressure_pile_inlet = ( ((float)temp) * 5000 / 4095 / 235 - 4 ) / 16 * 150;

	}

	return error_code;
}

//压力采集数据1//数据封装
enum Error_code pressure_data1_acquisition_encapsulation(struct Pressure_Data1_Acquisition *  p_pressure_data1_acquisition, CAN_message * p_can_msg)
{
	return Succeed;
}

//压力采集数据1//数据处理
enum Error_code pressure_data1_acquisition_execute(struct Pressure_Data1_Acquisition *  p_pressure_data1_acquisition)
{
	return Succeed;
}







//压力采集数据2//初始化
enum Error_code pressure_data2_acquisition_init(struct Pressure_Data2_Acquisition *  p_pressure_data2_acquisition)
{
	enum Error_code error_code = Succeed;

	if(p_pressure_data2_acquisition == NULL )
	{return Pointer_is_null;}

	p_pressure_data2_acquisition->updata_event_time = system_time;
	p_pressure_data2_acquisition->overtime_max = CAN_OVERTIME_MAX;
	p_pressure_data2_acquisition->Message_id = PRESSURE_DATA2_ACQUISITION_MESSAGE_ID;

	return error_code;
}

//压力采集数据2//数据解析
enum Error_code pressure_data2_acquisition_analysis(CAN_message * p_can_msg, struct Pressure_Data2_Acquisition *  p_pressure_data2_acquisition)
{
	enum Error_code error_code = Succeed;
	u16	temp;

	if(p_can_msg == NULL || p_pressure_data2_acquisition == NULL)
	{return Pointer_is_null;}

	if(p_pressure_data2_acquisition->Message_id != p_can_msg->can_message_id)
	{
		error_code =  CAN_data_analysis_id_error;
	}
	else
	{
		p_pressure_data2_acquisition->updata_event_time = system_time;

		temp = ((u16)(p_can_msg->can_data[0])) | ((u16)(p_can_msg->can_data[1]))<<8;
		fcu_data_buffer.air_data_buffer.air_pressure_pile_outlet = ( ((float)temp) * 5000 / 4095 / 235 - 4 ) / 16 * 150;
		temp = ((u16)(p_can_msg->can_data[2])) | ((u16)(p_can_msg->can_data[3]))<<8;
		fcu_data_buffer.air_data_buffer.air_pressure_pile_back = ( ((float)temp) * 5000 / 4095 / 235 - 4 ) / 16 * 100;
		temp = ((u16)(p_can_msg->can_data[4])) | ((u16)(p_can_msg->can_data[5]))<<8;
		fcu_data_buffer.water_for_pile_data_buffer.water_pressure_pile_inlet = ( ((float)temp) * 5000 / 4095 / 235 - 4 ) / 16 * 250;
		temp = ((u16)(p_can_msg->can_data[6])) | ((u16)(p_can_msg->can_data[7]))<<8;
		fcu_data_buffer.water_for_pile_data_buffer.water_pressure_pile_outlet = ( ((float)temp) * 5000 / 4095 / 235 - 4 ) / 16 * 250;

	}

	return error_code;
}

//压力采集数据2//数据封装
enum Error_code pressure_data2_acquisition_encapsulation(struct Pressure_Data2_Acquisition *  p_pressure_data2_acquisition, CAN_message * p_can_msg)
{
	return Succeed;
}

//压力采集数据2//数据处理
enum Error_code pressure_data2_acquisition_execute(struct Pressure_Data2_Acquisition *  p_pressure_data2_acquisition)
{
	return Succeed;
}






//压力采集数据3//初始化
enum Error_code pressure_data3_acquisition_init(struct Pressure_Data3_Acquisition *  p_pressure_data3_acquisition)
{
	enum Error_code error_code = Succeed;

	if(p_pressure_data3_acquisition == NULL )
	{return Pointer_is_null;}

	p_pressure_data3_acquisition->updata_event_time = system_time;
	p_pressure_data3_acquisition->overtime_max = CAN_OVERTIME_MAX;
	p_pressure_data3_acquisition->Message_id = PRESSURE_DATA3_ACQUISITION_MESSAGE_ID;

	return error_code;
}

//压力采集数据3//数据解析
enum Error_code pressure_data3_acquisition_analysis(CAN_message * p_can_msg, struct Pressure_Data3_Acquisition *  p_pressure_data3_acquisition)
{
	enum Error_code error_code = Succeed;
	u16	temp;
	float temp_ad;

	if(p_can_msg == NULL || p_pressure_data3_acquisition == NULL)
	{return Pointer_is_null;}

	if(p_pressure_data3_acquisition->Message_id != p_can_msg->can_message_id)
	{
		error_code =  CAN_data_analysis_id_error;
	}
	else
	{
		p_pressure_data3_acquisition->updata_event_time = system_time;

		temp = ((u16)(p_can_msg->can_data[0])) | ((u16)(p_can_msg->can_data[1]))<<8;
		fcu_data_buffer.water_for_compressor_data_bufferr.water_pressure_compressor_outlet = ( ((float)temp) * 5000 / 4095 / 235 - 4 ) / 16 * 250;
		temp = ((u16)(p_can_msg->can_data[2])) | ((u16)(p_can_msg->can_data[3]))<<8;
		temp_ad = ((float)temp) * 5000 / 4095 * 1000 / 909;
		fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_voltage = temp_ad / 10;
		temp = ((u16)(p_can_msg->can_data[4])) | ((u16)(p_can_msg->can_data[5]))<<8;
		temp_ad = ((float)temp) * 5000 / 4095 * 1000 / 909;
		fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_electricity = (temp_ad - 2500) / 4;
		temp = ((u16)(p_can_msg->can_data[6])) | ((u16)(p_can_msg->can_data[7]))<<8;
		temp_ad = ((float)temp) * 5000 / 4095  / 909;
		if(temp_ad <= 1)
		{
			fcu_data_buffer.air_data_buffer.air_rate_of_flow = 0;
		}
		else
		{
			fcu_data_buffer.air_data_buffer.air_rate_of_flow =
				163.8*temp_ad*temp_ad*temp_ad - 644.5*temp_ad*temp_ad + 1299.0*temp_ad - 837.1;
			if(fcu_data_buffer.air_data_buffer.air_rate_of_flow < 0)
			{
				fcu_data_buffer.air_data_buffer.air_rate_of_flow = 0;
			}
		}
		//y = 163.8x3 - 644.5x2 + 1299.x - 837.1			R2 = 0.999
	}

	return error_code;
}

//压力采集数据3//数据封装
enum Error_code pressure_data3_acquisition_encapsulation(struct Pressure_Data3_Acquisition *  p_pressure_data3_acquisition, CAN_message * p_can_msg)
{
	return Succeed;
}

//压力采集数据3//数据处理
enum Error_code pressure_data3_acquisition_execute(struct Pressure_Data3_Acquisition *  p_pressure_data3_acquisition)
{
	return Succeed;
}







//数字量输入//初始化
enum Error_code digital_quantity_input_init(struct Digital_Quantity_Input *  p_digital_quantity_input)
{
	enum Error_code error_code = Succeed;

	if(p_digital_quantity_input == NULL )
	{return Pointer_is_null;}

	p_digital_quantity_input->updata_event_time = system_time;
	p_digital_quantity_input->overtime_max = CAN_OVERTIME_MAX;
	p_digital_quantity_input->Message_id = DIGITAL_QUANTITY_INPUT_MESSAGE_ID;

	return error_code;
}

//数字量输入//数据解析
enum Error_code digital_quantity_input_analysis(CAN_message * p_can_msg, struct Digital_Quantity_Input *  p_digital_quantity_input)
{
	enum Error_code error_code = Succeed;

	if(p_can_msg == NULL || p_digital_quantity_input == NULL)
	{return Pointer_is_null;}

	if(p_digital_quantity_input->Message_id != p_can_msg->can_message_id)
	{
		error_code =  CAN_data_analysis_id_error;
	}
	else
	{
		p_digital_quantity_input->updata_event_time = system_time;

		fcu_data_buffer.galvanic_pile_data_buffer.fcu_start_enable = (p_can_msg->can_data[0] & 0x01);
		fcu_data_buffer.galvanic_pile_data_buffer.fcu_stutter_stop_enable = (p_can_msg->can_data[0] & 0x02) >> 1;
		fcu_data_buffer.water_for_pile_data_buffer.water_position = (p_can_msg->can_data[0] & 0x04) >> 2;
		fcu_data_buffer.water_for_compressor_data_bufferr.water_position = (p_can_msg->can_data[0] & 0x08) >> 3;
		fcu_data_buffer.water_for_compressor_data_bufferr.water_fan_feedback = (p_can_msg->can_data[0] & 0x10) >> 4;
		fcu_data_buffer.water_for_pile_data_buffer.water_fan1_feedback = (p_can_msg->can_data[0] & 0x20) >> 5;
		fcu_data_buffer.water_for_pile_data_buffer.water_fan2_feedback = (p_can_msg->can_data[0] & 0x40) >> 6;

	}

	return error_code;
}

//数字量输入//数据封装
enum Error_code digital_quantity_input_encapsulation(struct Digital_Quantity_Input *  p_digital_quantity_input, CAN_message * p_can_msg)
{
	return Succeed;
}

//数字量输入//数据处理
enum Error_code digital_quantity_input_execute(struct Digital_Quantity_Input *  p_digital_quantity_input)
{
	return Succeed;
}








//数字量输出//初始化
enum Error_code digital_quantity_output_init(struct Digital_Quantity_Output *  p_digital_quantity_output)
{
	enum Error_code error_code = Succeed;

	if(p_digital_quantity_output == NULL )
	{return Pointer_is_null;}

	p_digital_quantity_output->updata_event_time = system_time;
	p_digital_quantity_output->send_message_time_max = CAN_SEND_MESSAGE_TIME_MAX_5;
	p_digital_quantity_output->Message_id = DIGITAL_QUANTITY_OUTPUT_MESSAGE_ID;

	return error_code;
}

//数字量输出//数据解析
enum Error_code digital_quantity_output_analysis(CAN_message * p_can_msg, struct Digital_Quantity_Output *  p_digital_quantity_output)
{
	return Succeed;
}

//数字量输出//数据封装
enum Error_code digital_quantity_output_encapsulation(struct Digital_Quantity_Output *  p_digital_quantity_output, CAN_message * p_can_msg)
{
	enum Error_code error_code = Succeed;
	u16 temp;

	if(p_digital_quantity_output == NULL || p_can_msg == NULL)
	{return Pointer_is_null;}

	p_digital_quantity_output->updata_event_time = system_time;

	//数据数据封装
	p_can_msg->can_message_id = p_digital_quantity_output->Message_id;
	p_can_msg->can_ide = CAN_Id_Extended;
	p_can_msg->can_rtr = CAN_RTR_Data;
	p_can_msg->can_len = 8;

	p_can_msg->can_data[0] = (fcu_data_buffer.h2_data_buffer.h2_outlet_valve) 
		| (fcu_data_buffer.air_data_buffer.air_outlet_valve << 1) 
		| (fcu_data_buffer.h2_data_buffer.h2_inlet_valve << 2) 
		| (fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_is_enble_output << 3)
		| (fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_is_enble_load_resistance << 4) 
		| (fcu_data_buffer.water_for_compressor_data_bufferr.water_pump_enable << 5)
		| (fcu_data_buffer.h2_data_buffer.h2_circulating_pump_enble << 6);
	temp = (u16)(fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pwm_dutyfactor);
	p_can_msg->can_data[1] = (u8)temp;
	p_can_msg->can_data[2] = (u8)(temp>>8);

	p_can_msg->can_data[3] = 0x00; 

	temp = (u16)(fcu_data_buffer.h2_data_buffer.h2_pressure_proportional_valve_front * 100);
	p_can_msg->can_data[4] = (u8)temp;
	p_can_msg->can_data[5] = (u8)(temp>>8);
	temp = (u16)(fcu_data_buffer.h2_data_buffer.h2_pressure_proportional_valve_rear * 100);
	p_can_msg->can_data[6] = (u8)temp;
	p_can_msg->can_data[7] = (u8)(temp>>8);

	p_can_msg->can_priorty = 0;
	return error_code;
}

//数字量输出//数据处理
enum Error_code digital_quantity_output_execute(struct Digital_Quantity_Output *  p_digital_quantity_output)
{
	return Succeed;
}









//PWM输出//初始化
enum Error_code pwm_output_init(struct Pwm_Output *  p_pwm_output)
{
	enum Error_code error_code = Succeed;

	if(p_pwm_output == NULL )
	{return Pointer_is_null;}

	p_pwm_output->updata_event_time = system_time;
	p_pwm_output->send_message_time_max = CAN_SEND_MESSAGE_TIME_MAX_5;
	p_pwm_output->Message_id = PWM_OUTPUT_MESSAGE_ID;

	return error_code;
}

//PWM输出//数据解析
enum Error_code pwm_output_analysis(CAN_message * p_can_msg, struct Pwm_Output *  p_pwm_output)
{
	return Succeed;
}

//PWM输出//数据封装
enum Error_code pwm_output_encapsulation(struct Pwm_Output *  p_pwm_output, CAN_message * p_can_msg)
{
	enum Error_code error_code = Succeed;
	u16 temp;

	if(p_pwm_output == NULL || p_can_msg == NULL)
	{return Pointer_is_null;}

	p_pwm_output->updata_event_time = system_time;

	//数据数据封装
	p_can_msg->can_message_id = p_pwm_output->Message_id;
	p_can_msg->can_ide = CAN_Id_Extended;
	p_can_msg->can_rtr = CAN_RTR_Data;
	p_can_msg->can_len = 8;

	temp = (u16)(fcu_data_buffer.water_for_pile_data_buffer.water_pump_pwm_dutyfactor);
	p_can_msg->can_data[0] = (u8)temp;
	p_can_msg->can_data[1] = (u8)(temp>>8);
	temp = (u16)(fcu_data_buffer.water_for_pile_data_buffer.water_fan1_pwm_dutyfactor);
	p_can_msg->can_data[2] = (u8)temp;
	p_can_msg->can_data[3] = (u8)(temp>>8);
	temp = (u16)(fcu_data_buffer.water_for_pile_data_buffer.water_fan2_pwm_dutyfactor);
	p_can_msg->can_data[4] = (u8)temp;
	p_can_msg->can_data[5] = (u8)(temp>>8);
	temp = (u16)(fcu_data_buffer.water_for_compressor_data_bufferr.water_fan_pwm_dutyfactor);
	p_can_msg->can_data[6] = (u8)temp;
	p_can_msg->can_data[7] = (u8)(temp>>8);

	p_can_msg->can_priorty = 0;
	return error_code;
}

//PWM输出//数据处理
enum Error_code pwm_output_execute(struct Pwm_Output *  p_pwm_output)
{
	return Succeed;
}









//can通信协议汇总 初始化
enum Error_code Can_communication_protocol_init(struct Can_Communication_Protocol_Total * p_can_communication_protocol_total)
{
	enum Error_code error_code = Succeed;

	if(p_can_communication_protocol_total == NULL )
	{return Pointer_is_null;}

	error_code = temperature_data_acquisition_init( &(p_can_communication_protocol_total->temperature_data_acquisition) );
	if(error_code != Succeed)	{return error_code;}
	error_code = pressure_data1_acquisition_init( &(p_can_communication_protocol_total->pressure_data1_acquisition) );
	if(error_code != Succeed)	{return error_code;}
	error_code = pressure_data2_acquisition_init( &(p_can_communication_protocol_total->pressure_data2_acquisition) );
	if(error_code != Succeed)	{return error_code;}
	error_code = pressure_data3_acquisition_init( &(p_can_communication_protocol_total->pressure_data3_acquisition) );
	if(error_code != Succeed)	{return error_code;}
	error_code = digital_quantity_input_init( &(p_can_communication_protocol_total->digital_quantity_input) );
	if(error_code != Succeed)	{return error_code;}


	error_code = digital_quantity_output_init( &(p_can_communication_protocol_total->digital_quantity_output) );
	if(error_code != Succeed)	{return error_code;}
	error_code = pwm_output_init( &(p_can_communication_protocol_total->pwm_output) );
	if(error_code != Succeed)	{return error_code;}

	return error_code;
}






//把所有数据的时间清零
enum Error_code Can_communication_protocol_clear_time(struct Can_Communication_Protocol_Total * p_can_communication_protocol_total)
{
	enum Error_code error_code = Succeed;
	int i = 0;

	if(p_can_communication_protocol_total == NULL )
	{return Pointer_is_null;}

	p_can_communication_protocol_total->temperature_data_acquisition.updata_event_time = 0;
	p_can_communication_protocol_total->pressure_data1_acquisition.updata_event_time = 0;
	p_can_communication_protocol_total->pressure_data2_acquisition.updata_event_time = 0;
	p_can_communication_protocol_total->pressure_data3_acquisition.updata_event_time = 0;
	p_can_communication_protocol_total->digital_quantity_input.updata_event_time = 0;

	p_can_communication_protocol_total->digital_quantity_output.updata_event_time = 0;
	p_can_communication_protocol_total->pwm_output.updata_event_time = 0;

	return error_code;    
}



//通过接受的CAN消息，来更新数据。
enum Error_code Can_communication_protocol_updata_receivev_can(struct Can_Communication_Protocol_Total * p_can_communication_protocol_total, CAN_message * p_can_msg)
{
	enum Error_code error_code = Succeed;

	if(p_can_communication_protocol_total == NULL || p_can_msg == NULL)
	{return Pointer_is_null;}
	test_huli4 =  p_can_msg->can_message_id;
	if(p_can_msg->can_rtr == CAN_RTR_Data)
	{	
		//扩展帧
		if(p_can_msg->can_ide == CAN_Id_Extended)
		{
			switch(p_can_msg->can_message_id)
			{
			case TEMPERATURE_DATA_ACQUISITION_MESSAGE_ID:       
				error_code = temperature_data_acquisition_analysis(p_can_msg, &(p_can_communication_protocol_total->temperature_data_acquisition) );
				if(error_code != Succeed)	{return error_code;}
				break;
			case PRESSURE_DATA1_ACQUISITION_MESSAGE_ID:         
				error_code = pressure_data1_acquisition_analysis(p_can_msg, &(p_can_communication_protocol_total->pressure_data1_acquisition) );
				if(error_code != Succeed)	{return error_code;}
				break;	
			case PRESSURE_DATA2_ACQUISITION_MESSAGE_ID:         
				error_code = pressure_data2_acquisition_analysis(p_can_msg, &(p_can_communication_protocol_total->pressure_data2_acquisition) );
				if(error_code != Succeed)	{return error_code;}
				break;
			case PRESSURE_DATA3_ACQUISITION_MESSAGE_ID:       
				error_code = pressure_data3_acquisition_analysis(p_can_msg, &(p_can_communication_protocol_total->pressure_data3_acquisition) );
				if(error_code != Succeed)	{return error_code;}
				break;
			case DIGITAL_QUANTITY_INPUT_MESSAGE_ID:        
				error_code = digital_quantity_input_analysis(p_can_msg, &(p_can_communication_protocol_total->digital_quantity_input) );
				if(error_code != Succeed)	{return error_code;}
				break;

			default:
				//need 
				break;
			}
		}

		//标准帧
		else if(p_can_msg->can_ide == CAN_Id_Standard)
		{
			switch(p_can_msg->can_message_id)
			{

			default:
				//need 
				break;
			}
		}
	}


	return error_code;
}




//定时封装can数据
//如果没有需要发送的消息，返回错误
//注：一次只能转化一条发送消息。如果有多条，请循环调用本函数。直到本函数返回错误
enum Error_code Can_communication_protocol_can_encapsulation_and_send(struct Can_Communication_Protocol_Total * p_can_communication_protocol_total, CAN_message * p_can_msg)
{
	enum Error_code error_code = Succeed;

	if(p_can_msg == NULL || p_can_communication_protocol_total == NULL)
	{return Pointer_is_null;}

	if(system_time - p_can_communication_protocol_total->digital_quantity_output.updata_event_time > p_can_communication_protocol_total->digital_quantity_output.send_message_time_max)
	{ 
		error_code = digital_quantity_output_encapsulation( &(p_can_communication_protocol_total->digital_quantity_output),  p_can_msg);
		if(error_code == Succeed)
		{
			error_code = Control_Policy_ontime_can_send_data( CAN0,  p_can_msg);
			test_can_send++;
		}
		return error_code;//无论成功与否，都要结束这个函数，因为函数一次只能处理一条消息的转换
	}
	if(system_time - p_can_communication_protocol_total->pwm_output.updata_event_time > p_can_communication_protocol_total->pwm_output.send_message_time_max)
	{ 
		error_code = pwm_output_encapsulation( &(p_can_communication_protocol_total->pwm_output),  p_can_msg);
		if(error_code == Succeed)
		{
			error_code = Control_Policy_ontime_can_send_data( CAN0,  p_can_msg);
			test_can_send++;
		}
		return error_code;//无论成功与否，都要结束这个函数，因为函数一次只能处理一条消息的转换
	}	


	//如果没有到发送消息的时间，那么转化失败。表示当前不需要发送。
	error_code = NoData;
	return error_code;
}

/*
//定时发送can数据（默认can0）
enum Error_code Control_Policy_ontime_can_send_data(enum Can_Channels CANx, CAN_message * p_can_msg)
{
	enum Error_code error_code = Succeed;

	if(p_can_msg == NULL)
	{return Pointer_is_null;}

	switch(CANx)
	{
	case CAN0:
		error_code = MSCAN0_SendMsg(p_can_msg);
		break;
	case CAN1:
		error_code = MSCAN1_SendMsg(p_can_msg);
		break;
	default:
		//need 
		break;

	}

	return error_code;
}

*/





