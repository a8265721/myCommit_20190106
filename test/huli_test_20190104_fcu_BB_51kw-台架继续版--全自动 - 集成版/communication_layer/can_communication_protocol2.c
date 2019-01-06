#include "can_communication_protocol2.h"
//#include "can_communication_protocol.h"
//#include "error_system.h"

     /*
//ad�ɼ� ������    �ɼ���ƽ��ֵ
u16 ad_auxiliary_board_mean_data[AD_AUXILIARY_BOARD_CONVERSION_NUMBER_MAX] = {0};
  */



struct Can_Communication_Protocol2_Total    can_communication_protocol2_total;

//1.1.0��ѹ��������Ϣ//��ʼ��
enum Error_code Air_compressor_Control_Msg_init(struct Air_compressor_Control_Msg *  p_Air_compressor_Control_Msg)
{

	enum Error_code error_code = Succeed;

	if(p_Air_compressor_Control_Msg == NULL )
	{return Pointer_is_null;}

	p_Air_compressor_Control_Msg->updata_event_time = system_time;
	p_Air_compressor_Control_Msg->send_message_time_max = CAN_SEND_MESSAGE_TIME_MAX_100;
	p_Air_compressor_Control_Msg->Message_id = AIR_COMPRESSOR_CONTROL_MSG_ID;
	p_Air_compressor_Control_Msg->CompressorStart=0;
	p_Air_compressor_Control_Msg->SpeedSetpoint=0;
	//	p_temperature_data_acquisition->DCDC_heartbeat_frame = 0;
	return error_code;

}
//1.1.1��ѹ��������Ϣ//���ݽ���
enum Error_code Air_compressor_Control_Msg_analysis(CAN_message * p_can_msg, struct Air_compressor_Control_Msg *  p_Air_compressor_Control_Msg)
{

	return Succeed;
}
//1.1.2��ѹ��������Ϣ//���ݷ�װ
enum Error_code Air_compressor_Control_Msg_encapsulation(struct Air_compressor_Control_Msg *  p_Air_compressor_Control_Msg, CAN_message * p_can_msg)
{
	enum Error_code error_code = Succeed;
	u16 temp;

	if(p_Air_compressor_Control_Msg == NULL || p_can_msg == NULL)
	{return Pointer_is_null;}

	p_Air_compressor_Control_Msg->updata_event_time = system_time;

	//�������ݷ�װ
	p_can_msg->can_message_id = p_Air_compressor_Control_Msg->Message_id;
	p_can_msg->can_ide = CAN_Id_Extended;
	p_can_msg->can_rtr = CAN_RTR_Data;
	p_can_msg->can_len = 8;

	temp = (u16)(p_Air_compressor_Control_Msg->SpeedSetpoint / 10);
	p_can_msg->can_data[0] = p_Air_compressor_Control_Msg->CompressorStart;
	p_can_msg->can_data[1] =  (u8)(temp); 
	p_can_msg->can_data[2] =  (u8)(temp>>8);
	p_can_msg->can_data[3] = 0;
	p_can_msg->can_data[4] = 0;
	p_can_msg->can_data[5] = 0;
	p_can_msg->can_data[6] = 0;
	p_can_msg->can_data[7] = 0;

	p_can_msg->can_priorty = 0;
	return error_code;                                       

}
//1.1.3��ѹ��������Ϣ//���ݴ���
enum Error_code Air_compressor_Control_Msg_execute(struct Air_compressor_Control_Msg *  p_Air_compressor_Control_Msg)
{

	return Succeed;
}





//1.2.0��ѹ��״̬��Ϣ//��ʼ��
enum Error_code Air_compressor_stats_Msg2_init(struct Air_compressor_stats_Msg2 *  p_Air_compressor_stats_Msg2)
{
	enum Error_code error_code = Succeed;

	if(p_Air_compressor_stats_Msg2 == NULL )
	{return Pointer_is_null;}

	p_Air_compressor_stats_Msg2->updata_event_time = system_time;
	p_Air_compressor_stats_Msg2->overtime_max = CAN_OVERTIME_MAX;
	p_Air_compressor_stats_Msg2->Message_id = AIR_COMPRESSOR_STATS_MSG2_ID;
	p_Air_compressor_stats_Msg2->InputCur=0;
	p_Air_compressor_stats_Msg2->InputVol=0;
	p_Air_compressor_stats_Msg2->OutPutPower=0;
	p_Air_compressor_stats_Msg2->MotorTemp=0;
	p_Air_compressor_stats_Msg2->ConverterTemp=0;
	p_Air_compressor_stats_Msg2->InsideTemp = 0;
	//	p_temperature_data_acquisition->DCDC_heartbeat_frame = 0;
	return error_code;
}
//1.2.1��ѹ��״̬��Ϣ//���ݽ���
enum Error_code Air_compressor_stats_Msg2_analysis(CAN_message * p_can_msg, struct Air_compressor_stats_Msg2 *  p_Air_compressor_stats_Msg2)
{
	enum Error_code error_code = Succeed;

	if(p_can_msg == NULL || p_Air_compressor_stats_Msg2 == NULL)
	{return Pointer_is_null;}

	if(p_Air_compressor_stats_Msg2->Message_id != p_can_msg->can_message_id)
	{
		error_code =  CAN_data_analysis_id_error;
	}
	else
	{
		p_Air_compressor_stats_Msg2->updata_event_time = system_time;

		p_Air_compressor_stats_Msg2->InputCur = p_can_msg->can_data[0];
		p_Air_compressor_stats_Msg2->InputVol =  (u16)(p_can_msg->can_data[1]) | (u16)((p_can_msg->can_data[2]))<<8;
		p_Air_compressor_stats_Msg2->OutPutPower =  (u16)(p_can_msg->can_data[3]) | (u16)((p_can_msg->can_data[4]))<<8;
		p_Air_compressor_stats_Msg2->MotorTemp =  (i16)p_can_msg->can_data[5]-40;
		p_Air_compressor_stats_Msg2->ConverterTemp =  (i16)p_can_msg->can_data[6]-40;
        p_Air_compressor_stats_Msg2->InsideTemp = (i16)p_can_msg->can_data[7]-40;
	}


	return error_code;
}
//1.2.2��ѹ��״̬��Ϣ//���ݷ�װ
enum Error_code Air_compressor_stats_Msg2_encapsulation(struct Air_compressor_stats_Msg2 *  p_Air_compressor_stats_Msg2, CAN_message * p_can_msg)
{
	return Succeed;
}
//1.2.3��ѹ��״̬��Ϣ//���ݴ���
enum Error_code Air_compressor_stats_Msg2_execute(struct Air_compressor_stats_Msg2 *  p_Air_compressor_stats_Msg2)
{
	return Succeed;
}





//1.3.0��ѹ��������Ϣ//��ʼ��
enum Error_code Air_compressor_alarm_Msg3_init(struct Air_compressor_alarm_Msg3 *  p_Air_compressor_alarm_Msg3)
{
	enum Error_code error_code = Succeed;

	if(p_Air_compressor_alarm_Msg3 == NULL )
	{return Pointer_is_null;}

	p_Air_compressor_alarm_Msg3->updata_event_time = system_time;
	p_Air_compressor_alarm_Msg3->overtime_max = CAN_OVERTIME_MAX;
	p_Air_compressor_alarm_Msg3->Message_id = AIR_COMPRESSOR_ALARM_MSG3;
	p_Air_compressor_alarm_Msg3->CompressorState=0;
	p_Air_compressor_alarm_Msg3->FaultCode=0;
	p_Air_compressor_alarm_Msg3->faultLev=0;
	p_Air_compressor_alarm_Msg3->ActSpeed=0;

	//	p_temperature_data_acquisition->DCDC_heartbeat_frame = 0;
	return error_code;
}
//1.3.1��ѹ��������Ϣ//���ݽ���
enum Error_code Air_compressor_alarm_Msg3_analysis(CAN_message * p_can_msg, struct Air_compressor_alarm_Msg3 *  p_Air_compressor_alarm_Msg3)
{
	u16 temp = 0;
	enum Error_code error_code = Succeed;
	if(p_can_msg == NULL || p_Air_compressor_alarm_Msg3 == NULL)
	{return Pointer_is_null;}

	if(p_Air_compressor_alarm_Msg3->Message_id != p_can_msg->can_message_id)
	{
		error_code =  CAN_data_analysis_id_error;
	}
	else
	{
		p_Air_compressor_alarm_Msg3->updata_event_time = system_time;

		p_Air_compressor_alarm_Msg3->CompressorState = p_can_msg->can_data[0];
		p_Air_compressor_alarm_Msg3->FaultCode =  (u16)(p_can_msg->can_data[1]) | (u16)((p_can_msg->can_data[2]))<<8;
		p_Air_compressor_alarm_Msg3->faultLev =  p_can_msg->can_data[3];
		temp =  (u16)(p_can_msg->can_data[4]) | (u16)((p_can_msg->can_data[5]))<<8;
		p_Air_compressor_alarm_Msg3->ActSpeed =  ((u32)temp)*10;


	}


	return error_code;

}
//1.3.2��ѹ��������Ϣ//���ݷ�װ
enum Error_code Air_compressor_alarm_Msg3_Msg_encapsulation(struct Air_compressor_alarm_Msg3 *  p_Air_compressor_alarm_Msg3, CAN_message * p_can_msg)
{
	return Succeed;
}
//1.3.3��ѹ��������Ϣ//���ݴ���
enum Error_code Air_compressor_alarm_Msg3_execute(struct Air_compressor_alarm_Msg3 *  p_Air_compressor_alarm_Msg3)
{
	return Succeed;
}






//2.1.0����ѭ���ÿ�����Ϣ//��ʼ��
enum Error_code H2_PUMP_Control_Msg_init(struct H2_PUMP_Control_Msg *  p_H2_PUMP_Control_Msg)
{
	enum Error_code error_code = Succeed;

	if(p_H2_PUMP_Control_Msg == NULL )
	{return Pointer_is_null;}

	p_H2_PUMP_Control_Msg->updata_event_time = system_time;
	p_H2_PUMP_Control_Msg->send_message_time_max = CAN_SEND_MESSAGE_TIME_MAX_100;
	p_H2_PUMP_Control_Msg->Message_id = H2_PUMP_CONTROL_MSG_ID;
	p_H2_PUMP_Control_Msg->Mass_Flow_Setpoint=0;
	p_H2_PUMP_Control_Msg->Speed_setpoint=0;
	p_H2_PUMP_Control_Msg->Enable_Pump=0;
	p_H2_PUMP_Control_Msg->Enable_Mass_Flow_Govemor=0;

	//	p_temperature_data_acquisition->DCDC_heartbeat_frame = 0;
	return error_code;
}



//2.1.1����ѭ���ÿ�����Ϣ//���ݽ���
enum Error_code H2_PUMP_Control_Msg_analysis(CAN_message * p_can_msg, struct H2_PUMP_Control_Msg *  p_H2_PUMP_Control_Msg)
{
	return Succeed;
}

//2.1.2����ѭ���ÿ�����Ϣ//���ݷ�װ
enum Error_code H2_PUMP_Control_Msg_encapsulation(struct H2_PUMP_Control_Msg *  p_H2_PUMP_Control_Msg, CAN_message * p_can_msg)
{
	enum Error_code error_code = Succeed;
	u16 temp,temp1;

	if(p_H2_PUMP_Control_Msg == NULL || p_can_msg == NULL)
	{return Pointer_is_null;}

	p_H2_PUMP_Control_Msg->updata_event_time = system_time;

	//�������ݷ�װ
	p_can_msg->can_message_id = p_H2_PUMP_Control_Msg->Message_id;
	p_can_msg->can_ide = CAN_Id_Extended;
	p_can_msg->can_rtr = CAN_RTR_Data;
	p_can_msg->can_len = 8;

	temp = (u16)(p_H2_PUMP_Control_Msg->Mass_Flow_Setpoint*1000);
	temp1= (u16)(p_H2_PUMP_Control_Msg->Speed_setpoint);
	p_can_msg->can_data[0] = (u8)(temp);
	p_can_msg->can_data[1] = (u8)(temp>>8); 
	p_can_msg->can_data[2] = (u8)(temp1);
	p_can_msg->can_data[3] = (u8)(temp1>>8); 
	p_can_msg->can_data[4] = p_H2_PUMP_Control_Msg->Enable_Pump  |  (p_H2_PUMP_Control_Msg->Enable_Mass_Flow_Govemor)<<2;
	p_can_msg->can_data[5] = 0;
	p_can_msg->can_data[6] = 0;
	p_can_msg->can_data[7] = 0;

	p_can_msg->can_priorty = 0;
	return error_code;
}
//2.1.3����ѭ���ÿ�����Ϣ//���ݴ���
enum Error_code H2_PUMP_Control_Msg_execute(struct H2_PUMP_Control_Msg *  p_H2_PUMP_Control_Msg)
{
	return Succeed;
}





//2.2.0����ѭ����������Ϣ/��ʼ��
enum Error_code H2_circulating_pump_data_data_init(struct H2_circulating_pump_data *  p_H2_circulating_pump_data)
{
	enum Error_code error_code = Succeed;

	if(p_H2_circulating_pump_data == NULL )
	{return Pointer_is_null;}

	p_H2_circulating_pump_data->updata_event_time = system_time;
	p_H2_circulating_pump_data->overtime_max = CAN_OVERTIME_MAX;
	p_H2_circulating_pump_data->Message_id = H2_CIRCULATING_PUMP_DATA_ID;
	p_H2_circulating_pump_data->Actual_mass_flow=0;
	p_H2_circulating_pump_data->Actual_speed=0;
	p_H2_circulating_pump_data->Actual_current=0;
	p_H2_circulating_pump_data->Actual_voltage=0;
	p_H2_circulating_pump_data->Actual_electronic_temperature=0;
	p_H2_circulating_pump_data->Actual_air_temperature=0;
	p_H2_circulating_pump_data->status_diagnose_word=0;

	//	p_temperature_data_acquisition->DCDC_heartbeat_frame = 0;
	return error_code;
}
//2.2.1����ѭ����������Ϣ/���ݽ���
enum Error_code H2_circulating_pump_data_analysis(CAN_message * p_can_msg, struct H2_circulating_pump_data *  p_H2_circulating_pump_data)
{
	enum Error_code error_code = Succeed;
	float temp;
	if(p_can_msg == NULL || p_H2_circulating_pump_data == NULL)
	{return Pointer_is_null;}

	if(p_H2_circulating_pump_data->Message_id != p_can_msg->can_message_id)
	{
		error_code =  CAN_data_analysis_id_error;
	}
	else
	{
		p_H2_circulating_pump_data->updata_event_time = system_time;

		temp= ((u16)(p_can_msg->can_data[0]) | ((u16)(p_can_msg->can_data[1]))<<8)*0.002;
		p_H2_circulating_pump_data->Actual_mass_flow =  temp - 60;
		p_H2_circulating_pump_data->Actual_speed =    (float)p_can_msg->can_data[2]*40;
		p_H2_circulating_pump_data->Actual_current =  (float)p_can_msg->can_data[3]*0.5;
		p_H2_circulating_pump_data->Actual_voltage =  (float)p_can_msg->can_data[4]*0.2;
		p_H2_circulating_pump_data->Actual_electronic_temperature = (i16)p_can_msg->can_data[5]-40;
		p_H2_circulating_pump_data->Actual_air_temperature =   (i16)p_can_msg->can_data[6]-40;
		p_H2_circulating_pump_data->status_diagnose_word =  p_can_msg->can_data[7];


	}


	return error_code;
}
//2.2.2����ѭ����������Ϣ//���ݷ�װ
enum Error_code H2_circulating_pump_data_encapsulation(struct H2_circulating_pump_data *  p_H2_circulating_pump_data, CAN_message * p_can_msg)
{    
	return Succeed;
}
//2.2.3����ѭ����������Ϣ//���ݴ���
enum Error_code H2_circulating_pump_data_data_execute(struct H2_circulating_pump_data *  p_H2_circulating_pump_data)
{
	return Succeed;
}






//2.3.0����ѭ���ò�����Ϣ/��ʼ��
enum Error_code H2_circulating_pump_Parameter_values_init(struct H2_circulating_pump_Parameter_values *  p_H2_circulating_pump_Parameter_values) 
{
	enum Error_code error_code = Succeed;

	if(p_H2_circulating_pump_Parameter_values == NULL )
	{return Pointer_is_null;}

	p_H2_circulating_pump_Parameter_values->updata_event_time = system_time;
	p_H2_circulating_pump_Parameter_values->overtime_max = CAN_OVERTIME_MAX;
	p_H2_circulating_pump_Parameter_values->Message_id = H2_CIRCULATING_PUMP_PARAMETER_VALUES_ID;
	p_H2_circulating_pump_Parameter_values->Bm_tPt1MassFlow_c=0;
	p_H2_circulating_pump_Parameter_values->Bm_KpAirGvnr_c=0;
	p_H2_circulating_pump_Parameter_values->Bm_kiAirGvnr_c=0;
	p_H2_circulating_pump_Parameter_values->Bm_nSetErrorRepValue_c=0;


	//	p_temperature_data_acquisition->DCDC_heartbeat_frame = 0;
	return error_code;
}

//2.3.1����ѭ���ò�����Ϣ/���ݽ���  
enum Error_code H2_circulating_pump_Parameter_values_analysis(CAN_message * p_can_msg, struct H2_circulating_pump_Parameter_values *  p_H2_circulating_pump_Parameter_values)
{
	enum Error_code error_code = Succeed;

	if(p_can_msg == NULL || p_H2_circulating_pump_Parameter_values == NULL)
	{return Pointer_is_null;}

	if(p_H2_circulating_pump_Parameter_values->Message_id != p_can_msg->can_message_id)
	{
		error_code =  CAN_data_analysis_id_error;
	}
	else
	{
		p_H2_circulating_pump_Parameter_values->updata_event_time = system_time;


		p_H2_circulating_pump_Parameter_values->Bm_tPt1MassFlow_c =  (float)p_can_msg->can_data[0]*10;
		p_H2_circulating_pump_Parameter_values->Bm_KpAirGvnr_c =    (float)p_can_msg->can_data[1]*0.05;
		p_H2_circulating_pump_Parameter_values->Bm_kiAirGvnr_c =    (float)p_can_msg->can_data[2]*0.05;
		p_H2_circulating_pump_Parameter_values->Bm_nSetErrorRepValue_c = (float)p_can_msg->can_data[3]*20;



	}


	return error_code;
}

//2.3.2����ѭ���ò�����Ϣ//���ݷ�װ
enum Error_code H2_circulating_pump_Parameter_values_encapsulation(struct H2_circulating_pump_Parameter_values *  p_H2_circulating_pump_Parameter_values, CAN_message * p_can_msg)
{
	return Succeed;
} 
//2.3.3����ѭ���ò�����Ϣ//���ݴ���
enum Error_code H2_circulating_pump_Parameter_values_execute(struct H2_circulating_pump_data *  p_H2_circulating_pump_Parameter_values)
{
	return Succeed;
}



//2.4.0����ѭ����AcKnowledgment��Ϣ/��ʼ��
enum Error_code H2_circulating_pump_AcKnowledgment_init(struct H2_circulating_pump_AcKnowledgment *  p_H2_circulating_pump_AcKnowledgment)
{
	enum Error_code error_code = Succeed;

	if(p_H2_circulating_pump_AcKnowledgment == NULL )
	{return Pointer_is_null;}

	p_H2_circulating_pump_AcKnowledgment->updata_event_time = system_time;
	p_H2_circulating_pump_AcKnowledgment->overtime_max = CAN_OVERTIME_MAX;
	p_H2_circulating_pump_AcKnowledgment->Message_id = H2_CIRCULATING_PUMP_ACKNOWLEDGMENT;
	p_H2_circulating_pump_AcKnowledgment->AcKnowledgment=0;
	p_H2_circulating_pump_AcKnowledgment->Parameter_Group_number=0;

	//	p_temperature_data_acquisition->DCDC_heartbeat_frame = 0;
	return error_code;
}

//2.4.1����ѭ����AcKnowledgment��Ϣ/���ݽ���  
enum Error_code H2_circulating_pump_AcKnowledgment_analysis(CAN_message * p_can_msg, struct H2_circulating_pump_AcKnowledgment *  p_H2_circulating_pump_AcKnowledgment)
{
	enum Error_code error_code = Succeed;

	if(p_can_msg == NULL || p_H2_circulating_pump_AcKnowledgment == NULL)
	{return Pointer_is_null;}

	if(p_H2_circulating_pump_AcKnowledgment->Message_id != p_can_msg->can_message_id)
	{
		error_code =  CAN_data_analysis_id_error;
	}
	else
	{
		p_H2_circulating_pump_AcKnowledgment->updata_event_time = system_time;


		p_H2_circulating_pump_AcKnowledgment->AcKnowledgment =  p_can_msg->can_data[0];

		p_H2_circulating_pump_AcKnowledgment->Parameter_Group_number =    (u32)(p_can_msg->can_data[5]) | ((u32)(p_can_msg->can_data[6]))<<8 | ((u32)(p_can_msg->can_data[7]))<<16;

	}


	return error_code;
}

//2.4.2����ѭ����AcKnowledgment��Ϣ//���ݷ�װ
enum Error_code H2_circulating_pump_AcKnowledgment_encapsulation(struct H2_circulating_pump_AcKnowledgment *  p_H2_circulating_pump_AcKnowledgment, CAN_message * p_can_msg)
{
	return Succeed;
}
//2.4.3����ѭ���AcKnowledgment��Ϣ//���ݴ���
enum Error_code H2_circulating_pump_AcKnowledgment_execute(struct H2_circulating_pump_AcKnowledgment *  p_H2_circulating_pump_AcKnowledgment)
{
	return Succeed;
}





//3.1.0Ѳ����ʵ�ʵ�ѹֵ//��ʼֵ
enum Error_code Itinerant_detective_Single_voltage_actual_data_init(struct Itinerant_detective_Single_voltage_actual_data *  p_Itinerant_detective_Single_voltage_actual_data,int ID_num)
{
	enum Error_code error_code = Succeed;
	u8 i=0;

	if(p_Itinerant_detective_Single_voltage_actual_data == NULL )
	{return Pointer_is_null;}

	p_Itinerant_detective_Single_voltage_actual_data->updata_event_time = system_time;
	p_Itinerant_detective_Single_voltage_actual_data->overtime_max = CAN_OVERTIME_MAX;

	p_Itinerant_detective_Single_voltage_actual_data->Message_id = ITINERANT_DETECTIVE_SINGLE_VOLTAGE_ACTUAL_DATA+ID_num;
	for(i=0;i<4;i++)
	{
		p_Itinerant_detective_Single_voltage_actual_data->fell_single_voltage[i] = 0; 
	}

	return error_code;
}
//Ѳ����ʵ�ʵ�ѹֵ//���ݽ���
enum Error_code Itinerant_detective_Single_voltage_actual_data_analysis(CAN_message * p_can_msg, struct Itinerant_detective_Single_voltage_actual_data *  p_Itinerant_detective_Single_voltage_actual_data)
{
	enum Error_code error_code = Succeed;
	u8 i=0;

	if(p_can_msg == NULL || p_Itinerant_detective_Single_voltage_actual_data == NULL)
	{return Pointer_is_null;}

	if(p_Itinerant_detective_Single_voltage_actual_data->Message_id != p_can_msg->can_message_id)
	{
		error_code =  CAN_data_analysis_id_error;
	}
	else
	{
		p_Itinerant_detective_Single_voltage_actual_data->updata_event_time = system_time;


		for(i=0;i<4;i++)
		{

			p_Itinerant_detective_Single_voltage_actual_data->fell_single_voltage[i] =  ((u16)(p_can_msg->can_data[2*i]) | (u16)((p_can_msg->can_data[2*i+1])<<8))/1000;
		}

	}
	return error_code;
}
//Ѳ����ʵ�ʵ�ѹֵ//���ݷ�װ
enum Error_code Itinerant_detective_Single_voltage_actual_data_encapsulation(struct Itinerant_detective_Single_voltage_actual_data *  p_Itinerant_detective_Single_voltage_actual_data, CAN_message * p_can_msg)
{
	return Succeed;
}
//Ѳ����ʵ�ʵ�ѹֵ//���ݴ���
enum Error_code Itinerant_detective_Single_voltage_actual_data_execute(struct Itinerant_detective_Single_voltage_actual_data *  p_Itinerant_detective_Single_voltage_actual_data)
{
	return Succeed;
}



//Ѳ������״̬//��ʼֵ
enum Error_code Itinerant_detective_operate_statas_init(struct Itinerant_detective_operate_statas *  p_Itinerant_detective_operate_statas, u32 can_message_id)
{
	enum Error_code error_code = Succeed;
	u8 i=0;

	if(p_Itinerant_detective_operate_statas == NULL )
	{return Pointer_is_null;}

	p_Itinerant_detective_operate_statas->updata_event_time = system_time;
	p_Itinerant_detective_operate_statas->overtime_max = CAN_OVERTIME_MAX;

	p_Itinerant_detective_operate_statas->Message_id = can_message_id;
	p_Itinerant_detective_operate_statas->itinerant_detective_working_statas = 0; 
	p_Itinerant_detective_operate_statas->health_of_telectric_heap = 0; 
	p_Itinerant_detective_operate_statas->Single_battery_overvoltage_alarm = 0; 
	p_Itinerant_detective_operate_statas->Single_battery_undervoltage_alarm = 0; 
	p_Itinerant_detective_operate_statas->Single_voltage_unbalance_alarm = 0; 
	p_Itinerant_detective_operate_statas->electric1_mean_voltage = 0; 
	p_Itinerant_detective_operate_statas->electric2_mean_voltage = 0; 
	p_Itinerant_detective_operate_statas->heartbeat_frame = 0; 


	return error_code;
}
//Ѳ������״̬//���ݽ���
enum Error_code Itinerant_detective_operate_statas_analysis(CAN_message * p_can_msg, struct Itinerant_detective_operate_statas *  p_Itinerant_detective_operate_statas)
{
	enum Error_code error_code = Succeed;
	u8 i=0;
	u16 temp = 0;

	if(p_can_msg == NULL || p_Itinerant_detective_operate_statas == NULL)
	{return Pointer_is_null;}

	if(p_Itinerant_detective_operate_statas->Message_id != p_can_msg->can_message_id)
	{
		error_code =  CAN_data_analysis_id_error;
	}
	else
	{
		p_Itinerant_detective_operate_statas->updata_event_time = system_time;

		p_Itinerant_detective_operate_statas->itinerant_detective_working_statas= p_can_msg->can_data[0];
		p_Itinerant_detective_operate_statas->health_of_telectric_heap= p_can_msg->can_data[1];
		p_Itinerant_detective_operate_statas->Single_battery_overvoltage_alarm= p_can_msg->can_data[2]&0x3;
		p_Itinerant_detective_operate_statas->Single_battery_undervoltage_alarm=((p_can_msg->can_data[2])>>2)&0x3;
		p_Itinerant_detective_operate_statas->Single_voltage_unbalance_alarm=((p_can_msg->can_data[2])>>4)&0x3;
		
		temp = (u16)(p_can_msg->can_data[3]) | (u16)((p_can_msg->can_data[4])<<8);
		p_Itinerant_detective_operate_statas->electric1_mean_voltage =  ((float)temp) /1000;
		
		temp = (u16)(p_can_msg->can_data[5]) | (u16)((p_can_msg->can_data[6])<<8);
		p_Itinerant_detective_operate_statas->electric2_mean_voltage =  ((float)temp) /1000;
		
		p_Itinerant_detective_operate_statas->heartbeat_frame=p_can_msg->can_data[7];

	}
	return error_code;

}
//Ѳ������״̬//���ݷ�װ
enum Error_code Itinerant_detective_operate_statas_encapsulation(struct Itinerant_detective_operate_statas *  p_Itinerant_detective_operate_statas, CAN_message * p_can_msg)
{
	return Succeed;
}
//Ѳ������״̬//���ݴ���
enum Error_code Itinerant_detective_operate_statas_execute(struct Itinerant_detective_operate_statas *  p_Itinerant_detective_operate_statas)
{
	return Succeed;
}



//3.2.1 Ѳ�쵥Ƭ��ߵ�ѹ
//Ѳ�쵥Ƭ��ߵ�ѹ//��ʼֵ
enum Error_code Itinerant_detective_single_chip_highest_voltage_init(struct Itinerant_detective_single_chip_highest_voltage *  p_Itinerant_detective_single_chip_highest_voltage, u32 can_message_id)
{
	enum Error_code error_code = Succeed;

	if(p_Itinerant_detective_single_chip_highest_voltage == NULL )
	{return Pointer_is_null;}

	p_Itinerant_detective_single_chip_highest_voltage->updata_event_time = system_time;
	p_Itinerant_detective_single_chip_highest_voltage->overtime_max = CAN_OVERTIME_MAX;

	p_Itinerant_detective_single_chip_highest_voltage->Message_id = can_message_id;
	p_Itinerant_detective_single_chip_highest_voltage->electric1_single_chip_highest_voltage = 0; 
	p_Itinerant_detective_single_chip_highest_voltage->electric1_single_chip_highest_voltage_num = 0; 
	p_Itinerant_detective_single_chip_highest_voltage->electric2_single_chip_highest_voltage = 0; 
	p_Itinerant_detective_single_chip_highest_voltage->electric2_single_chip_highest_voltage_num = 0; 

	return error_code;
}
//Ѳ�쵥Ƭ��ߵ�ѹ//���ݽ���
enum Error_code Itinerant_detective_single_chip_highest_voltage_analysis(CAN_message * p_can_msg, struct Itinerant_detective_single_chip_highest_voltage *  p_Itinerant_detective_single_chip_highest_voltage)
{
	enum Error_code error_code = Succeed;
	u8 i=0;
	u16 temp1 = 0;
	u16 temp2 = 0;

	if(p_can_msg == NULL || p_Itinerant_detective_single_chip_highest_voltage == NULL)
	{return Pointer_is_null;}

	if(p_Itinerant_detective_single_chip_highest_voltage->Message_id != p_can_msg->can_message_id)
	{
		error_code =  CAN_data_analysis_id_error;
	}
	else
	{
		p_Itinerant_detective_single_chip_highest_voltage->updata_event_time = system_time;

		temp1 =  (u16)(p_can_msg->can_data[0]) | ((u16)(p_can_msg->can_data[1]))<<8;
		p_Itinerant_detective_single_chip_highest_voltage->electric1_single_chip_highest_voltage =  ((float)temp1) /1000;
		p_Itinerant_detective_single_chip_highest_voltage->electric1_single_chip_highest_voltage_num =  (u16)(p_can_msg->can_data[2]) | ((u16)(p_can_msg->can_data[3]))<<8;

		temp2 = (u16)(p_can_msg->can_data[4]) | ((u16)(p_can_msg->can_data[5]))<<8;
		p_Itinerant_detective_single_chip_highest_voltage->electric2_single_chip_highest_voltage=  ((float)temp2) /1000;
		p_Itinerant_detective_single_chip_highest_voltage->electric2_single_chip_highest_voltage_num= (u16)(p_can_msg->can_data[6]) | ((u16)(p_can_msg->can_data[7]))<<8;

	}
	return error_code;


}
//Ѳ�쵥Ƭ��ߵ�ѹ//���ݷ�װ
enum Error_code Itinerant_detective_single_chip_highest_voltage_encapsulation(struct Itinerant_detective_single_chip_highest_voltage *  p_Itinerant_detective_single_chip_highest_voltage, CAN_message * p_can_msg)
{
	return Succeed;
}
//Ѳ�쵥Ƭ��ߵ�ѹ//���ݴ���
enum Error_code Itinerant_detective_single_chip_highest_voltage_execute(struct Itinerant_detective_single_chip_highest_voltage *  p_Itinerant_detective_single_chip_highest_voltage)
{
	return Succeed;
}




//Ѳ�쵥Ƭ��͵�ѹ	//��ʼֵ
enum Error_code Itinerant_detective_single_chip_minimum_voltage_init(struct Itinerant_detective_single_chip_minimum_voltage *  p_Itinerant_detective_single_chip_minimum_voltage, u32 can_message_id)
{
	enum Error_code error_code = Succeed;

	if(p_Itinerant_detective_single_chip_minimum_voltage == NULL )
	{return Pointer_is_null;}

	p_Itinerant_detective_single_chip_minimum_voltage->updata_event_time = system_time;
	p_Itinerant_detective_single_chip_minimum_voltage->overtime_max = CAN_OVERTIME_MAX;

	p_Itinerant_detective_single_chip_minimum_voltage->Message_id = can_message_id;
	p_Itinerant_detective_single_chip_minimum_voltage->electric1_single_chip_minimum_voltage = 0; 
	p_Itinerant_detective_single_chip_minimum_voltage->electric1_single_chip_minimum_voltage_num = 0; 
	p_Itinerant_detective_single_chip_minimum_voltage->electric2_single_chip_minimum_voltage = 0; 
	p_Itinerant_detective_single_chip_minimum_voltage->electric2_single_chip_minimum_voltage_num = 0; 

	return error_code;
}
//Ѳ�쵥Ƭ��͵�ѹ	//���ݽ���
enum Error_code Itinerant_detective_single_chip_minimum_voltage_analysis(CAN_message * p_can_msg, struct Itinerant_detective_single_chip_minimum_voltage *  p_Itinerant_detective_single_chip_minimum_voltage)
{
	enum Error_code error_code = Succeed;
	u8 i=0;
	u16 temp1 = 0;
	u16 temp2 = 0;

	if(p_can_msg == NULL || p_Itinerant_detective_single_chip_minimum_voltage == NULL)
	{return Pointer_is_null;}

	if(p_Itinerant_detective_single_chip_minimum_voltage->Message_id != p_can_msg->can_message_id)
	{
		error_code =  CAN_data_analysis_id_error;
	}
	else
	{
		p_Itinerant_detective_single_chip_minimum_voltage->updata_event_time = system_time;


		temp1 =  (u16)(p_can_msg->can_data[0]) | ((u16)(p_can_msg->can_data[1]))<<8;
		p_Itinerant_detective_single_chip_minimum_voltage->electric1_single_chip_minimum_voltage =  ((float)temp1) /1000;
		p_Itinerant_detective_single_chip_minimum_voltage->electric1_single_chip_minimum_voltage_num =  (u16)(p_can_msg->can_data[2]) | ((u16)(p_can_msg->can_data[3]))<<8;

		temp2 = (u16)(p_can_msg->can_data[4]) | ((u16)(p_can_msg->can_data[5]))<<8;
		p_Itinerant_detective_single_chip_minimum_voltage->electric2_single_chip_minimum_voltage=  ((float)temp2) /1000;
		p_Itinerant_detective_single_chip_minimum_voltage->electric2_single_chip_minimum_voltage_num= (u16)(p_can_msg->can_data[6]) | ((u16)(p_can_msg->can_data[7]))<<8;

	}
	return error_code;

}
//Ѳ�쵥Ƭ��͵�ѹ	//���ݷ�װ
enum Error_code Itinerant_detective_single_chip_minimum_voltage_encapsulation(struct Itinerant_detective_single_chip_minimum_voltage *  p_Itinerant_detective_single_chip_minimum_voltage, CAN_message * p_can_msg)
{
	return Succeed;
}
//Ѳ�쵥Ƭ��͵�ѹ	//���ݴ���
enum Error_code Itinerant_detective_single_chip_minimum_voltage_execute(struct Itinerant_detective_single_chip_minimum_voltage *  p_Itinerant_detective_single_chip_minimum_voltage)
{
	return Succeed;
}





//Ѳ���ܵ�ѹ//��ʼֵ
enum Error_code Itinerant_detective_voltage_data_init(struct Itinerant_detective_voltage_data *  p_Itinerant_detective_voltage_data, u32 can_message_id)
{
	enum Error_code error_code = Succeed;

	if(p_Itinerant_detective_voltage_data == NULL )
	{return Pointer_is_null;}

	p_Itinerant_detective_voltage_data->updata_event_time = system_time;
	p_Itinerant_detective_voltage_data->overtime_max = CAN_OVERTIME_MAX;

	p_Itinerant_detective_voltage_data->Message_id = can_message_id;
	p_Itinerant_detective_voltage_data->Itinerant_detective_total_voltage = 0; 
	
	return error_code;
}

//Ѳ���ܵ�ѹ//���ݽ���
enum Error_code Itinerant_detective_voltage_data_analysis(CAN_message * p_can_msg, struct Itinerant_detective_voltage_data *  p_Itinerant_detective_voltage_data)
{


	enum Error_code error_code = Succeed;
	u8 i=0;
	u32 temp = 0;

	if(p_can_msg == NULL || p_Itinerant_detective_voltage_data == NULL)
	{return Pointer_is_null;}
           
	if(p_Itinerant_detective_voltage_data->Message_id != p_can_msg->can_message_id)
	{
		error_code =  CAN_data_analysis_id_error;
	}
	else
	{
		p_Itinerant_detective_voltage_data->updata_event_time = system_time;

		temp =    (u32)(p_can_msg->can_data[0]) | ((u32)(p_can_msg->can_data[1]))<<8 |
			((u32)(p_can_msg->can_data[2]))<<16 | ((u32)(p_can_msg->can_data[3]))<<24;
		p_Itinerant_detective_voltage_data->Itinerant_detective_total_voltage = ((float)temp)/1000;

        
	}
	return error_code;


}
//Ѳ���ܵ�ѹ//���ݷ�װ
enum Error_code Itinerant_detective_voltage_data_encapsulation(struct Itinerant_detective_voltage_data *  p_Itinerant_detective_voltage_data, CAN_message * p_can_msg)
{
	return Succeed;
}
//Ѳ���ܵ�ѹ//���ݴ���
enum Error_code Itinerant_detective_voltage_data_execute(struct Itinerant_detective_voltage_data *  p_Itinerant_detective_voltage_data)
{
	return Succeed;
}







//	��Ե�����
//��Ե�����//��ʼֵ
enum Error_code Insulation_monitor_data_init(struct Insulation_monitor_data *  p_Insulation_monitor_data)
{
   	enum Error_code error_code = Succeed;

	if(p_Insulation_monitor_data == NULL )
	{return Pointer_is_null;}

	p_Insulation_monitor_data->updata_event_time = system_time;
	p_Insulation_monitor_data->overtime_max = CAN_OVERTIME_MAX;

	p_Insulation_monitor_data->Message_id = INSULATION_MONITOR_DATA_ID;
	p_Insulation_monitor_data->fault_level = 0;
	p_Insulation_monitor_data->error_code = 0; 
	p_Insulation_monitor_data->Insulation_resistance_value = 0; 
	p_Insulation_monitor_data->Battery_voltage = 0; 
	p_Insulation_monitor_data->life_frame = 0; 
	
	return error_code;
}
//��Ե�����//���ݽ���
enum Error_code Insulation_monitor_data_analysis(CAN_message * p_can_msg, struct Insulation_monitor_data *  p_Insulation_monitor_data)
{
 	enum Error_code error_code = Succeed;
	u16 temp = 0;
	u16 temp1 = 0;
	

	if(p_can_msg == NULL || p_Insulation_monitor_data == NULL)
	{return Pointer_is_null;}
           
	if(p_Insulation_monitor_data->Message_id != p_can_msg->can_message_id)
	{
		error_code =  CAN_data_analysis_id_error;
	}
	else
	{
		p_Insulation_monitor_data->updata_event_time = system_time;
		
		p_Insulation_monitor_data->fault_level=(p_can_msg->can_data[0])>>4;	
		p_Insulation_monitor_data->error_code=p_can_msg->can_data[0] & 0x0f;
		temp =    (u16)(p_can_msg->can_data[1]) | ((u16)(p_can_msg->can_data[2]))<<8;
		p_Insulation_monitor_data->Insulation_resistance_value= temp;
  	temp1 =    (u16)(p_can_msg->can_data[3]) | ((u16)(p_can_msg->can_data[4]))<<8;
		p_Insulation_monitor_data->Battery_voltage = temp1;
		p_Insulation_monitor_data->life_frame=p_can_msg->can_data[7];

        
	}
	return error_code;
}
//��Ե�����//���ݷ�װ
enum Error_code Insulation_monitor_data_encapsulation(struct Insulation_monitor_data *  p_Insulation_monitor_data, CAN_message * p_can_msg)
{
  	return Succeed;
}
//��Ե�����//���ݴ���
enum Error_code Insulation_monitor_data_execute(struct Insulation_monitor_data *  p_Insulation_monitor_data)
{
  	return Succeed;
}








//ad�ɼ� ������//��ʼֵ
enum Error_code ad_auxiliary_board_message_init(struct Ad_auxiliary_board_message *  p_ad_auxiliary_board_message, u16 num_id)
{
   	enum Error_code error_code = Succeed;
   	u8 i=0;

	if(p_ad_auxiliary_board_message == NULL )
	{return Pointer_is_null;}

	p_ad_auxiliary_board_message->updata_event_time = system_time;
	p_ad_auxiliary_board_message->overtime_max = CAN_OVERTIME_MAX;
    p_ad_auxiliary_board_message->message_id = AD_AUXILIARY_BOARD_MESSAGE_ID + num_id;
    for(i=0;i<4;i++)
	{
		p_ad_auxiliary_board_message->ad_auxiliary_board_message_data[i] = 0; 
	}
	
	return error_code;
}
//ad�ɼ� ������//���ݽ���
enum Error_code ad_auxiliary_board_message_analysis(CAN_message * p_can_msg, struct Ad_auxiliary_board_message *  p_ad_auxiliary_board_message)
{
 	enum Error_code error_code = Succeed;
	u8 i=0;

	if(p_can_msg == NULL || p_ad_auxiliary_board_message == NULL)
	{return Pointer_is_null;}

	if(p_ad_auxiliary_board_message->message_id != p_can_msg->can_message_id)
	{
		error_code =  CAN_data_analysis_id_error;
	}
	else
	{
		p_ad_auxiliary_board_message->updata_event_time = system_time;

   		for(i=0;i<4;i++)
		{    
			p_ad_auxiliary_board_message->ad_auxiliary_board_message_data[i] =  
			    ((u16)(p_can_msg->can_data[2*i]) | (u16)((p_can_msg->can_data[2*i+1])<<8));
		}

	}
	return error_code;
}
//ad�ɼ� ������//���ݷ�װ
enum Error_code ad_auxiliary_board_message_encapsulation(struct Ad_auxiliary_board_message *  p_ad_auxiliary_board_message, CAN_message * p_can_msg)
{
  	return Succeed;
}
//ad�ɼ� ������//���ݴ���
enum Error_code ad_auxiliary_board_message_execute(struct Ad_auxiliary_board_message *  p_ad_auxiliary_board_message)
{
  	return Succeed;
}




//fcu������λ��//��ʼֵ
enum Error_code pc_can_communication_fcu_to_labview_init(struct PC_can_communication_fcu_to_labview *  p_pc_can_communication_fcu_to_labview)
{
	enum Error_code error_code = Succeed;
	u8 i=0;

	if(p_pc_can_communication_fcu_to_labview == NULL )
	{return Pointer_is_null;}

	p_pc_can_communication_fcu_to_labview->updata_event_time = system_time;
	p_pc_can_communication_fcu_to_labview->send_message_time_max = CAN_SEND_MESSAGE_TIME_MAX_1000;
	p_pc_can_communication_fcu_to_labview->message_id = PC_CAN_COMMUNICATION_FCU_TO_LABVIEW_ID;
	p_pc_can_communication_fcu_to_labview->can_message_index = 0;

	return error_code;
}      
//fcu������λ��//���ݽ���
enum Error_code pc_can_communication_fcu_to_labview_analysis(CAN_message * p_can_msg, struct PC_can_communication_fcu_to_labview *  p_pc_can_communication_fcu_to_labview)
{
	return Succeed;
}
//fcu������λ��//���ݷ�װ
enum Error_code pc_can_communication_fcu_to_labview_encapsulation(struct PC_can_communication_fcu_to_labview *  p_pc_can_communication_fcu_to_labview, CAN_message * p_can_msg)
{
	enum Error_code error_code = Succeed;


	if(p_pc_can_communication_fcu_to_labview == NULL || p_can_msg == NULL)
	{return Pointer_is_null;}

	//	p_pc_can_communication_fcu_to_labview->updata_event_time = system_time;

	//�������ݷ�װ
	p_can_msg->can_message_id = p_pc_can_communication_fcu_to_labview->message_id + 0x00010000 * p_pc_can_communication_fcu_to_labview->can_message_index;
	p_can_msg->can_ide = CAN_Id_Extended;
	p_can_msg->can_rtr = CAN_RTR_Data;
	p_can_msg->can_len = 8;

	switch(p_pc_can_communication_fcu_to_labview->can_message_index)
	{
		//�������ݣ�0~17��0x1800BDBC~0x1811BDBC
	case 0:
		p_pc_can_communication_fcu_to_labview->updata_event_time = system_time; //ע���ˣ�ֻ�е�һ֡���͵�ʱ���ˢ��ʱ�䡣
		float_convert_four_byte(&(fcu_data_buffer.h2_data_buffer.h2_pressure_proportional_valve_front),
			p_can_msg->can_data+0, p_can_msg->can_data+1, p_can_msg->can_data+2, p_can_msg->can_data+3);
		float_convert_four_byte(&(fcu_data_buffer.h2_data_buffer.h2_pressure_proportional_valve_rear),
			p_can_msg->can_data+4, p_can_msg->can_data+5, p_can_msg->can_data+6, p_can_msg->can_data+7);
		break;
	case 1:
		float_convert_four_byte(&(fcu_data_buffer.h2_data_buffer.h2_pressure_pile_inlet),
			p_can_msg->can_data+0, p_can_msg->can_data+1, p_can_msg->can_data+2, p_can_msg->can_data+3);
		float_convert_four_byte(&(fcu_data_buffer.h2_data_buffer.h2_pressure_pile_inlet1),
			p_can_msg->can_data+4, p_can_msg->can_data+5, p_can_msg->can_data+6, p_can_msg->can_data+7);
		break;
	case 2:
		float_convert_four_byte(&(fcu_data_buffer.h2_data_buffer.h2_pressure_pile_inlet2),
			p_can_msg->can_data+0, p_can_msg->can_data+1, p_can_msg->can_data+2, p_can_msg->can_data+3);
		float_convert_four_byte(&(fcu_data_buffer.h2_data_buffer.h2_pressure_pile_outlet1),
			p_can_msg->can_data+4, p_can_msg->can_data+5, p_can_msg->can_data+6, p_can_msg->can_data+7);
		break;
	case 3:
		float_convert_four_byte(&(fcu_data_buffer.h2_data_buffer.h2_pressure_pile_outlet2),
			p_can_msg->can_data+0, p_can_msg->can_data+1, p_can_msg->can_data+2, p_can_msg->can_data+3);
		float_convert_four_byte(&(fcu_data_buffer.h2_data_buffer.h2_pressure_tail_outlet),
			p_can_msg->can_data+4, p_can_msg->can_data+5, p_can_msg->can_data+6, p_can_msg->can_data+7);
		break;
	case 4:
		p_can_msg->can_data[0] = fcu_data_buffer.h2_data_buffer.h2_inlet_valve;
		p_can_msg->can_data[1] = fcu_data_buffer.h2_data_buffer.h2_outlet_valve; 
		p_can_msg->can_data[2] = 0;
		p_can_msg->can_data[3] = fcu_data_buffer.h2_data_buffer.h2_is_enable_outlet_valve;
		p_can_msg->can_data[4] = (u8)(fcu_data_buffer.h2_data_buffer.h2_outlet_valve_open_time);  
		p_can_msg->can_data[5] = (u8)((fcu_data_buffer.h2_data_buffer.h2_outlet_valve_open_time)>>8);                                         
		p_can_msg->can_data[6] = (u8)((fcu_data_buffer.h2_data_buffer.h2_outlet_valve_open_time)>>16);   
		p_can_msg->can_data[7] = (u8)((fcu_data_buffer.h2_data_buffer.h2_outlet_valve_open_time)>>24);  
		break;
	case 5:
		p_can_msg->can_data[0] = (u8)(fcu_data_buffer.h2_data_buffer.h2_outlet_valve_close_time);  
		p_can_msg->can_data[1] = (u8)((fcu_data_buffer.h2_data_buffer.h2_outlet_valve_close_time)>>8);                                         
		p_can_msg->can_data[2] = (u8)((fcu_data_buffer.h2_data_buffer.h2_outlet_valve_close_time)>>16);   
		p_can_msg->can_data[3] = (u8)((fcu_data_buffer.h2_data_buffer.h2_outlet_valve_close_time)>>24); 
		float_convert_four_byte(&(fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pwm_dutyfactor),
			p_can_msg->can_data+4, p_can_msg->can_data+5, p_can_msg->can_data+6, p_can_msg->can_data+7);
		break;
	case 6:
		float_convert_four_byte(&(fcu_data_buffer.h2_data_buffer.h2_concentration),
			p_can_msg->can_data+0, p_can_msg->can_data+1, p_can_msg->can_data+2, p_can_msg->can_data+3);
		float_convert_four_byte(&(fcu_data_buffer.h2_data_buffer.h2_humidity),
			p_can_msg->can_data+4, p_can_msg->can_data+5, p_can_msg->can_data+6, p_can_msg->can_data+7);
		break;
	case 7:
		p_can_msg->can_data[0] = fcu_data_buffer.h2_data_buffer.h2_circulating_pump_enble;
		p_can_msg->can_data[1] = fcu_data_buffer.h2_data_buffer.h2_circulating_pump_working_communication_status; 
		p_can_msg->can_data[2] = (u8)(fcu_data_buffer.h2_data_buffer.h2_circulating_pump_speed_setpoint);  
		p_can_msg->can_data[3] = (u8)((fcu_data_buffer.h2_data_buffer.h2_circulating_pump_speed_setpoint)>>8);     
		p_can_msg->can_data[4] = fcu_data_buffer.h2_data_buffer.h2_circulating_pump_enable_pump;
		p_can_msg->can_data[5] = (u8)(fcu_data_buffer.h2_data_buffer.h2_circulating_pump_actual_electronic_temperature);                                       
		p_can_msg->can_data[6] = (u8)((fcu_data_buffer.h2_data_buffer.h2_circulating_pump_actual_electronic_temperature)>>8);
		p_can_msg->can_data[7] = 0; 
		break;
	case 8:
		float_convert_four_byte(&(fcu_data_buffer.h2_data_buffer.h2_circulating_pump_actual_mass_flow),
			p_can_msg->can_data+0, p_can_msg->can_data+1, p_can_msg->can_data+2, p_can_msg->can_data+3);
		float_convert_four_byte(&(fcu_data_buffer.h2_data_buffer.h2_circulating_pump_actual_speed),
			p_can_msg->can_data+4, p_can_msg->can_data+5, p_can_msg->can_data+6, p_can_msg->can_data+7);
		break;
	case 9:
		float_convert_four_byte(&(fcu_data_buffer.h2_data_buffer.h2_circulating_pump_actual_current),
			p_can_msg->can_data+0, p_can_msg->can_data+1, p_can_msg->can_data+2, p_can_msg->can_data+3);
		float_convert_four_byte(&(fcu_data_buffer.h2_data_buffer.h2_circulating_pump_actual_voltage),
			p_can_msg->can_data+4, p_can_msg->can_data+5, p_can_msg->can_data+6, p_can_msg->can_data+7);
		break;
	case 10:
		float_convert_four_byte(&(fcu_data_buffer.h2_data_buffer.h2_pressure_target_value),
			p_can_msg->can_data+0, p_can_msg->can_data+1, p_can_msg->can_data+2, p_can_msg->can_data+3);
		float_convert_four_byte(&(fcu_data_buffer.h2_data_buffer.h2_pressure_real_target_value),
			p_can_msg->can_data+4, p_can_msg->can_data+5, p_can_msg->can_data+6, p_can_msg->can_data+7);
		break;
	case 11:
		float_convert_four_byte(&(fcu_data_buffer.h2_data_buffer.h2_pressure_advance_current_value),
			p_can_msg->can_data+0, p_can_msg->can_data+1, p_can_msg->can_data+2, p_can_msg->can_data+3);
		float_convert_four_byte(&(fcu_data_buffer.h2_data_buffer.h2_pressure_advance_set_value),
			p_can_msg->can_data+4, p_can_msg->can_data+5, p_can_msg->can_data+6, p_can_msg->can_data+7);
		break;
	case 12:
		p_can_msg->can_data[0] = (u8)(fcu_data_buffer.h2_data_buffer.h2_pressure_pid1_advance_time);  
		p_can_msg->can_data[1] = (u8)((fcu_data_buffer.h2_data_buffer.h2_pressure_pid1_advance_time)>>8);     
		p_can_msg->can_data[2] = (u8)((fcu_data_buffer.h2_data_buffer.h2_pressure_pid1_advance_time)>>16);   
		p_can_msg->can_data[3] = (u8)((fcu_data_buffer.h2_data_buffer.h2_pressure_pid1_advance_time)>>24); 
		p_can_msg->can_data[4] = (u8)(fcu_data_buffer.h2_data_buffer.h2_pressure_pid2_advance_time);  
		p_can_msg->can_data[5] = (u8)((fcu_data_buffer.h2_data_buffer.h2_pressure_pid2_advance_time)>>8);                                         
		p_can_msg->can_data[6] = (u8)((fcu_data_buffer.h2_data_buffer.h2_pressure_pid2_advance_time)>>16);   
		p_can_msg->can_data[7] = (u8)((fcu_data_buffer.h2_data_buffer.h2_pressure_pid2_advance_time)>>24);  	
		break;
	case 13:
		p_can_msg->can_data[0] = fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid1.is_enble_pid;
		p_can_msg->can_data[1] = 0; 
		p_can_msg->can_data[2] = 0;  
		p_can_msg->can_data[3] = 0;  
		float_convert_four_byte(&(fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid1.Kp),
			p_can_msg->can_data+4, p_can_msg->can_data+5, p_can_msg->can_data+6, p_can_msg->can_data+7);
		break;
	case 14:
		float_convert_four_byte(&(fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid1.Ki),
			p_can_msg->can_data+0, p_can_msg->can_data+1, p_can_msg->can_data+2, p_can_msg->can_data+3);
		float_convert_four_byte(&(fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid1.Kd),
			p_can_msg->can_data+4, p_can_msg->can_data+5, p_can_msg->can_data+6, p_can_msg->can_data+7);
		break;
	case 15:
		p_can_msg->can_data[0] = fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid2.is_enble_pid;
		p_can_msg->can_data[1] = 0; 
		p_can_msg->can_data[2] = 0;  
		p_can_msg->can_data[3] = 0;  
		float_convert_four_byte(&(fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid2.Kp),
			p_can_msg->can_data+4, p_can_msg->can_data+5, p_can_msg->can_data+6, p_can_msg->can_data+7);
		break;
	case 16:
		float_convert_four_byte(&(fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid2.Ki),
			p_can_msg->can_data+0, p_can_msg->can_data+1, p_can_msg->can_data+2, p_can_msg->can_data+3);
		float_convert_four_byte(&(fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid2.Kd),
			p_can_msg->can_data+4, p_can_msg->can_data+5, p_can_msg->can_data+6, p_can_msg->can_data+7);
		break;
	case 17:
		float_convert_four_byte(&(fcu_data_buffer.h2_data_buffer.h2_pressure_fluctuate_last_max),
			p_can_msg->can_data+0, p_can_msg->can_data+1, p_can_msg->can_data+2, p_can_msg->can_data+3);
		float_convert_four_byte(&(fcu_data_buffer.h2_data_buffer.h2_pressure_fluctuate_last_min),
			p_can_msg->can_data+4, p_can_msg->can_data+5, p_can_msg->can_data+6, p_can_msg->can_data+7);
		break;

		//�������ݣ� 18~23�� 0x1812BDBC~0x1817BDBC   
	case 18:
		float_convert_four_byte(&(fcu_data_buffer.air_data_buffer.air_pressure_pile_inlet),
			p_can_msg->can_data+0, p_can_msg->can_data+1, p_can_msg->can_data+2, p_can_msg->can_data+3);
		float_convert_four_byte(&(fcu_data_buffer.air_data_buffer.air_pressure_pile_outlet),
			p_can_msg->can_data+4, p_can_msg->can_data+5, p_can_msg->can_data+6, p_can_msg->can_data+7);
		break;
	case 19:
		float_convert_four_byte(&(fcu_data_buffer.air_data_buffer.air_pressure_pile_back),
			p_can_msg->can_data+0, p_can_msg->can_data+1, p_can_msg->can_data+2, p_can_msg->can_data+3);
		float_convert_four_byte(&(fcu_data_buffer.air_data_buffer.air_temperature_pile_inlet),
			p_can_msg->can_data+4, p_can_msg->can_data+5, p_can_msg->can_data+6, p_can_msg->can_data+7);
		break;
	case 20:
		float_convert_four_byte(&(fcu_data_buffer.air_data_buffer.air_temperature_pile_outlet),
			p_can_msg->can_data+0, p_can_msg->can_data+1, p_can_msg->can_data+2, p_can_msg->can_data+3);
		float_convert_four_byte(&(fcu_data_buffer.air_data_buffer.air_temperature_humidifier_front),
			p_can_msg->can_data+4, p_can_msg->can_data+5, p_can_msg->can_data+6, p_can_msg->can_data+7);
		break;
	case 21:
		float_convert_four_byte(&(fcu_data_buffer.air_data_buffer.air_rate_of_flow),
			p_can_msg->can_data+0, p_can_msg->can_data+1, p_can_msg->can_data+2, p_can_msg->can_data+3);
		p_can_msg->can_data[4] = fcu_data_buffer.air_data_buffer.air_outlet_valve;
		p_can_msg->can_data[5] = 0;                                       
		p_can_msg->can_data[6] = 0;
		p_can_msg->can_data[7] = fcu_data_buffer.air_data_buffer.air_is_enable_outlet_valve; 
		break;
	case 22:
		p_can_msg->can_data[0] = (u8)(fcu_data_buffer.air_data_buffer.air_outlet_valve_open_time);  
		p_can_msg->can_data[1] = (u8)((fcu_data_buffer.air_data_buffer.air_outlet_valve_open_time)>>8);     
		p_can_msg->can_data[2] = (u8)((fcu_data_buffer.air_data_buffer.air_outlet_valve_open_time)>>16);   
		p_can_msg->can_data[3] = (u8)((fcu_data_buffer.air_data_buffer.air_outlet_valve_open_time)>>24); 
		p_can_msg->can_data[4] = (u8)(fcu_data_buffer.air_data_buffer.air_outlet_valve_close_time);  
		p_can_msg->can_data[5] = (u8)((fcu_data_buffer.air_data_buffer.air_outlet_valve_close_time)>>8);                                         
		p_can_msg->can_data[6] = (u8)((fcu_data_buffer.air_data_buffer.air_outlet_valve_close_time)>>16);   
		p_can_msg->can_data[7] = (u8)((fcu_data_buffer.air_data_buffer.air_outlet_valve_close_time)>>24);  	
		break;
	case 23:
		p_can_msg->can_data[0] = fcu_data_buffer.air_data_buffer.air_compressor_working_communication_status; 
		p_can_msg->can_data[1] = fcu_data_buffer.air_data_buffer.air_compressor_enable; 
		p_can_msg->can_data[2] = 0;
		p_can_msg->can_data[3] = 0;
		p_can_msg->can_data[4] = (u8)(fcu_data_buffer.air_data_buffer.air_compressor_speed_setpoint);  
		p_can_msg->can_data[5] = (u8)((fcu_data_buffer.air_data_buffer.air_compressor_speed_setpoint)>>8);                                         
		p_can_msg->can_data[6] = (u8)((fcu_data_buffer.air_data_buffer.air_compressor_speed_setpoint)>>16);   
		p_can_msg->can_data[7] = (u8)((fcu_data_buffer.air_data_buffer.air_compressor_speed_setpoint)>>24);  	
		break;

		//���ɢ��ϵͳ��24~29, 0x1818BDBC~0x181DBDBC      
	case 24:
		float_convert_four_byte(&(fcu_data_buffer.water_for_pile_data_buffer.water_pressure_pile_inlet1),
			p_can_msg->can_data+0, p_can_msg->can_data+1, p_can_msg->can_data+2, p_can_msg->can_data+3);
		float_convert_four_byte(&(fcu_data_buffer.water_for_pile_data_buffer.water_pressure_pile_outlet1),
			p_can_msg->can_data+4, p_can_msg->can_data+5, p_can_msg->can_data+6, p_can_msg->can_data+7);
		break;
	case 25:
		float_convert_four_byte(&(fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_inlet1),
			p_can_msg->can_data+0, p_can_msg->can_data+1, p_can_msg->can_data+2, p_can_msg->can_data+3);
		float_convert_four_byte(&(fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_outlet1),
			p_can_msg->can_data+4, p_can_msg->can_data+5, p_can_msg->can_data+6, p_can_msg->can_data+7);
		break;
	case 26:
		float_convert_four_byte(&(fcu_data_buffer.water_for_pile_data_buffer.water_pump_pwm_dutyfactor1),
			p_can_msg->can_data+0, p_can_msg->can_data+1, p_can_msg->can_data+2, p_can_msg->can_data+3);
		float_convert_four_byte(&(fcu_data_buffer.water_for_pile_data_buffer.water_fan_pwm_dutyfactor1),
			p_can_msg->can_data+4, p_can_msg->can_data+5, p_can_msg->can_data+6, p_can_msg->can_data+7);
		break;
	case 27:
		float_convert_four_byte(&(fcu_data_buffer.water_for_pile_data_buffer.water_fan_pwm_dutyfactor2),
			p_can_msg->can_data+0, p_can_msg->can_data+1, p_can_msg->can_data+2, p_can_msg->can_data+3);
		p_can_msg->can_data[4] = fcu_data_buffer.water_for_pile_data_buffer.water_temperature_fan_pid1.is_enble_pid;  
		p_can_msg->can_data[5] = 0;                                         
		p_can_msg->can_data[6] = 0;   
		p_can_msg->can_data[7] = 0; 
		break;
	case 28:
		float_convert_four_byte(&(fcu_data_buffer.water_for_pile_data_buffer.water_temperature_fan_pid1.Kp),
			p_can_msg->can_data+0, p_can_msg->can_data+1, p_can_msg->can_data+2, p_can_msg->can_data+3);
		float_convert_four_byte(&(fcu_data_buffer.water_for_pile_data_buffer.water_temperature_fan_pid1.Ki),
			p_can_msg->can_data+4, p_can_msg->can_data+5, p_can_msg->can_data+6, p_can_msg->can_data+7);
		break;
	case 29:
		float_convert_four_byte(&(fcu_data_buffer.water_for_pile_data_buffer.water_temperature_fan_pid1.Kd),
			p_can_msg->can_data+0, p_can_msg->can_data+1, p_can_msg->can_data+2, p_can_msg->can_data+3);
		float_convert_four_byte(&(fcu_data_buffer.water_for_pile_data_buffer.water_temperature_target_value1),
			p_can_msg->can_data+4, p_can_msg->can_data+5, p_can_msg->can_data+6, p_can_msg->can_data+7);
		break;

		//����һɢ��ϵͳ�� 30~33, 0x181EBDBC~0x1821BDBC             
	case 30:
		float_convert_four_byte(&(fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_compressor_outlet),
			p_can_msg->can_data+0, p_can_msg->can_data+1, p_can_msg->can_data+2, p_can_msg->can_data+3);
		float_convert_four_byte(&(fcu_data_buffer.water_for_compressor_data_bufferr.water_pressure_compressor_outlet),
			p_can_msg->can_data+4, p_can_msg->can_data+5, p_can_msg->can_data+6, p_can_msg->can_data+7);
		break;
	case 31:
		float_convert_four_byte(&(fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_frequency_outlet),
			p_can_msg->can_data+0, p_can_msg->can_data+1, p_can_msg->can_data+2, p_can_msg->can_data+3);
		float_convert_four_byte(&(fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_intercooler_outlet),
			p_can_msg->can_data+4, p_can_msg->can_data+5, p_can_msg->can_data+6, p_can_msg->can_data+7);
		break;
	case 32:
		float_convert_four_byte(&(fcu_data_buffer.water_for_compressor_data_bufferr.water_temperature_pump_outlet),
			p_can_msg->can_data+0, p_can_msg->can_data+1, p_can_msg->can_data+2, p_can_msg->can_data+3);
		float_convert_four_byte(&(fcu_data_buffer.water_for_compressor_data_bufferr.water_pressure_pump_outlet),
			p_can_msg->can_data+4, p_can_msg->can_data+5, p_can_msg->can_data+6, p_can_msg->can_data+7);
		break;
	case 33:
		p_can_msg->can_data[0] = fcu_data_buffer.water_for_compressor_data_bufferr.water_pump_enable; 
		p_can_msg->can_data[1] = 0; 
		p_can_msg->can_data[2] = 0;
		p_can_msg->can_data[3] = 0;
		float_convert_four_byte(&(fcu_data_buffer.water_for_compressor_data_bufferr.water_fan_pwm_dutyfactor),
			p_can_msg->can_data+4, p_can_msg->can_data+5, p_can_msg->can_data+6, p_can_msg->can_data+7);
		break;

		//��ѷ������ݣ�34~42,  0x1822BDBC~0x182ABDBC           
	case 34:
		float_convert_four_byte(&(fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_voltage),
			p_can_msg->can_data+0, p_can_msg->can_data+1, p_can_msg->can_data+2, p_can_msg->can_data+3);
		float_convert_four_byte(&(fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_electricity),
			p_can_msg->can_data+4, p_can_msg->can_data+5, p_can_msg->can_data+6, p_can_msg->can_data+7);
		break;
	case 35:
		p_can_msg->can_data[0] = fcu_data_buffer.galvanic_pile_data_buffer.fcu_start_enable;
		p_can_msg->can_data[1] = fcu_data_buffer.galvanic_pile_data_buffer.fcu_stutter_stop_enable;
		p_can_msg->can_data[2] = fcu_data_buffer.galvanic_pile_data_buffer.fcu_reset_enable;
		p_can_msg->can_data[3] = fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_is_enble_output;
		p_can_msg->can_data[4] = fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_is_enble_load_resistance;
		p_can_msg->can_data[5] = fcu_data_buffer.galvanic_pile_data_buffer.itinerant_detective_working_communication_status;
		p_can_msg->can_data[6] = fcu_data_buffer.galvanic_pile_data_buffer.itinerant_detective_working_statas;
		p_can_msg->can_data[7] = 0;
		break;
	case 36:
		float_convert_four_byte(&(fcu_data_buffer.galvanic_pile_data_buffer.electric1_mean_voltage),
			p_can_msg->can_data+0, p_can_msg->can_data+1, p_can_msg->can_data+2, p_can_msg->can_data+3);
		float_convert_four_byte(&(fcu_data_buffer.galvanic_pile_data_buffer.electric1_single_chip_highest_voltage),
			p_can_msg->can_data+4, p_can_msg->can_data+5, p_can_msg->can_data+6, p_can_msg->can_data+7);
		break;
	case 37:
		p_can_msg->can_data[0] = (u8)(fcu_data_buffer.galvanic_pile_data_buffer.electric1_single_chip_highest_voltage_num);  
		p_can_msg->can_data[1] = (u8)((fcu_data_buffer.galvanic_pile_data_buffer.electric1_single_chip_highest_voltage_num)>>8);     
		p_can_msg->can_data[2] = 0;   
		p_can_msg->can_data[3] = 0; 
		float_convert_four_byte(&(fcu_data_buffer.galvanic_pile_data_buffer.electric1_single_chip_minimum_voltage),
			p_can_msg->can_data+4, p_can_msg->can_data+5, p_can_msg->can_data+6, p_can_msg->can_data+7);
		break;
	case 38:
		p_can_msg->can_data[0] = (u8)(fcu_data_buffer.galvanic_pile_data_buffer.electric1_single_chip_minimum_voltage_num);  
		p_can_msg->can_data[1] = (u8)((fcu_data_buffer.galvanic_pile_data_buffer.electric1_single_chip_minimum_voltage_num)>>8);     
		p_can_msg->can_data[2] = 0;   
		p_can_msg->can_data[3] = 0; 
		float_convert_four_byte(&(fcu_data_buffer.galvanic_pile_data_buffer.itinerant_detective_total_voltage),
			p_can_msg->can_data+4, p_can_msg->can_data+5, p_can_msg->can_data+6, p_can_msg->can_data+7);
		break; 
	case 39:
		float_convert_four_byte(&(fcu_data_buffer.galvanic_pile_data_buffer.electric1_mean_voltage2),
			p_can_msg->can_data+0, p_can_msg->can_data+1, p_can_msg->can_data+2, p_can_msg->can_data+3);
		float_convert_four_byte(&(fcu_data_buffer.galvanic_pile_data_buffer.electric1_single_chip_highest_voltage2),
			p_can_msg->can_data+4, p_can_msg->can_data+5, p_can_msg->can_data+6, p_can_msg->can_data+7);
		break;
	case 40:
		p_can_msg->can_data[0] = (u8)(fcu_data_buffer.galvanic_pile_data_buffer.electric1_single_chip_highest_voltage_num2);  
		p_can_msg->can_data[1] = (u8)((fcu_data_buffer.galvanic_pile_data_buffer.electric1_single_chip_highest_voltage_num2)>>8);     
		p_can_msg->can_data[2] = 0;   
		p_can_msg->can_data[3] = 0; 
		float_convert_four_byte(&(fcu_data_buffer.galvanic_pile_data_buffer.electric1_single_chip_minimum_voltage2),
			p_can_msg->can_data+4, p_can_msg->can_data+5, p_can_msg->can_data+6, p_can_msg->can_data+7);
		break;
	case 41:
		p_can_msg->can_data[0] = (u8)(fcu_data_buffer.galvanic_pile_data_buffer.electric1_single_chip_minimum_voltage_num2);  
		p_can_msg->can_data[1] = (u8)((fcu_data_buffer.galvanic_pile_data_buffer.electric1_single_chip_minimum_voltage_num2)>>8);     
		p_can_msg->can_data[2] = 0;   
		p_can_msg->can_data[3] = 0; 
		float_convert_four_byte(&(fcu_data_buffer.galvanic_pile_data_buffer.itinerant_detective_total_voltage2),
			p_can_msg->can_data+4, p_can_msg->can_data+5, p_can_msg->can_data+6, p_can_msg->can_data+7);
		break;
	case 42:
		p_can_msg->can_data[0] = 0;  
		p_can_msg->can_data[1] = 0;     
		p_can_msg->can_data[2] = 0;   
		p_can_msg->can_data[3] = 0; 
		p_can_msg->can_data[4] = 0;  
		p_can_msg->can_data[5] = 0;                                          
		p_can_msg->can_data[6] = 0;   
		p_can_msg->can_data[7] = 0; 
		break;


		//fcu�ܹ���43�� 0x182BBDBC    
	case 43:
		p_can_msg->can_data[0] = control_policy_total_manager.working_control_mode;  
		p_can_msg->can_data[1] = control_policy_total_manager.working_status_mode;      
		p_can_msg->can_data[2] = control_policy_total_manager.working_alarm_mode; 
		p_can_msg->can_data[3] = (u8)((u16)control_policy_total_manager.working_FCU_error_code);  
		p_can_msg->can_data[4] = (u8)(((u16)control_policy_total_manager.working_FCU_error_code)>>8);   
		p_can_msg->can_data[5] = control_policy_total_manager.working_FCU_error_control_mode;                                  
		p_can_msg->can_data[6] = control_policy_total_manager.fcu_system_running_mode;   
		p_can_msg->can_data[7] = 0;
		break;

	default:
		break;
	}

	p_can_msg->can_priorty = 0;
	return error_code;
}
//fcu������λ��//���ݴ���
enum Error_code pc_can_communication_fcu_to_labview_execute(struct PC_can_communication_fcu_to_labview *  p_pc_can_communication_fcu_to_labview)
{
	return Succeed;
}    



//��λ������fcu//��ʼֵ
enum Error_code pc_can_communication_labview_to_fcu_init(struct PC_can_communication_labview_to_fcu *  p_pc_can_communication_labview_to_fcu)
{
	enum Error_code error_code = Succeed;
	u8 i=0;

	if(p_pc_can_communication_labview_to_fcu == NULL )
	{return Pointer_is_null;}

	p_pc_can_communication_labview_to_fcu->updata_event_time = system_time;
	p_pc_can_communication_labview_to_fcu->overtime_max = CAN_OVERTIME_MAX;
	p_pc_can_communication_labview_to_fcu->message_id = PC_CAN_COMMUNICATION_LABVIEW_TO_FCU_ID;
	return error_code;
}  
//��λ������fcu//���ݽ���
enum Error_code pc_can_communication_labview_to_fcu_analysis(CAN_message * p_can_msg, struct PC_can_communication_labview_to_fcu *  p_pc_can_communication_labview_to_fcu)
{
	enum Error_code error_code = Succeed;
	u8 function_code_temp=0;

	if(p_can_msg == NULL || p_pc_can_communication_labview_to_fcu == NULL)
	{return Pointer_is_null;}

	if(p_pc_can_communication_labview_to_fcu->message_id != p_can_msg->can_message_id)
	{
		error_code =  CAN_data_analysis_id_error;
	}
	else
	{
		p_pc_can_communication_labview_to_fcu->updata_event_time = system_time;

		switch(function_code_temp)

		{
		case 1:
			fcu_data_buffer.h2_data_buffer.h2_inlet_valve =
				p_can_msg->can_data[7];
			break;
		case 2:
			fcu_data_buffer.h2_data_buffer.h2_is_enable_outlet_valve =
				p_can_msg->can_data[7]; 
			break;
		case 3:
			fcu_data_buffer.h2_data_buffer.h2_outlet_valve_open_time =
				((u32)(	p_can_msg->can_data[7]))<<24 |
				((u32)(	p_can_msg->can_data[6]))<16  |
				((u32)(	p_can_msg->can_data[5]))<<8  |
				((u32)(	p_can_msg->can_data[4]));    
			break;	
		case 4:
			fcu_data_buffer.h2_data_buffer.h2_outlet_valve_close_time =
				((u32)(	p_can_msg->can_data[7]))<<24 |
				((u32)(	p_can_msg->can_data[6]))<<16 |
				((u32)(	p_can_msg->can_data[5]))<<8  |
				((u32)(	p_can_msg->can_data[4]));      
			break;    
		case 5:
			fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pwm_dutyfactor =
				four_byte_convert_float(	p_can_msg->can_data[4],	p_can_msg->can_data[5],
				p_can_msg->can_data[6],	p_can_msg->can_data[7]);
			break; 
		case 6:
			fcu_data_buffer.h2_data_buffer.h2_circulating_pump_enble =
				p_can_msg->can_data[7];   
			break;                     
		case 7:
			fcu_data_buffer.h2_data_buffer.h2_circulating_pump_enable_pump =
				p_can_msg->can_data[7]; 
			break;   
		case 8:
			fcu_data_buffer.h2_data_buffer.h2_circulating_pump_speed_setpoint = 
				(u16)( ((u16)(	p_can_msg->can_data[7]))<<8  |
				((u16)(	p_can_msg->can_data[6])));           	             
			break; 
		case 9:
			fcu_data_buffer.h2_data_buffer.h2_pressure_target_value =
				four_byte_convert_float(	p_can_msg->can_data[4],	p_can_msg->can_data[5],
				p_can_msg->can_data[6],	p_can_msg->can_data[7]);    
			break;
		case 10:
			fcu_data_buffer.h2_data_buffer.h2_pressure_advance_set_value =
				four_byte_convert_float(	p_can_msg->can_data[4],	p_can_msg->can_data[5],
				p_can_msg->can_data[6],	p_can_msg->can_data[7]);
			break;   			
		case 11:
			fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid1.is_enble_pid =
				p_can_msg->can_data[7];      
			break;
		case 12:
			fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid1.Kp =
				four_byte_convert_float(	p_can_msg->can_data[4],	p_can_msg->can_data[5],
				p_can_msg->can_data[6],	p_can_msg->can_data[7]);
			break;                          			
		case 13:
			fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid1.Ki =
				four_byte_convert_float(	p_can_msg->can_data[4],	p_can_msg->can_data[5],
				p_can_msg->can_data[6],	p_can_msg->can_data[7]);
			break;                          			
		case 14:
			fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid1.Kd =
				four_byte_convert_float(	p_can_msg->can_data[4],	p_can_msg->can_data[5],
				p_can_msg->can_data[6],	p_can_msg->can_data[7]);
			break;                         
		case 15:
			fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid2.is_enble_pid =
				p_can_msg->can_data[7];    
			break;                                           
		case 16:
			fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid2.Kp =
				four_byte_convert_float(	p_can_msg->can_data[4],	p_can_msg->can_data[5],
				p_can_msg->can_data[6],	p_can_msg->can_data[7]);
			break;
		case 17:
			fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid2.Ki =
				four_byte_convert_float(	p_can_msg->can_data[4],	p_can_msg->can_data[5],
				p_can_msg->can_data[6],	p_can_msg->can_data[7]);
			break; 
		case 18:
			fcu_data_buffer.h2_data_buffer.h2_proportional_valve_pid2.Kd =
				four_byte_convert_float(	p_can_msg->can_data[4],	p_can_msg->can_data[5],
				p_can_msg->can_data[6],	p_can_msg->can_data[7]);
			break;                                         
		case 19:
			fcu_data_buffer.h2_data_buffer.h2_pid_mode =
				p_can_msg->can_data[7];                 
			break;
			
			
			
		case 20:
			fcu_data_buffer.air_data_buffer.air_is_enable_outlet_valve =
				p_can_msg->can_data[7]; 
            break; 
		case 21:
			fcu_data_buffer.air_data_buffer.air_outlet_valve_open_time =
				((u32)(	p_can_msg->can_data[7]))<<24 |
				((u32)(	p_can_msg->can_data[6]))<<16 |
				((u32)(	p_can_msg->can_data[5]))<<8  |
				((u32)(	p_can_msg->can_data[4]));                
			break;    
		case 22:
			fcu_data_buffer.air_data_buffer.air_outlet_valve_close_time =
				((u32)(	p_can_msg->can_data[7]))<<24 |
				((u32)(	p_can_msg->can_data[6]))<<16 |
				((u32)(	p_can_msg->can_data[5]))<<8  |
				((u32)(	p_can_msg->can_data[4]));       
			break;                                  
		case 23:
			fcu_data_buffer.air_data_buffer.air_compressor_enable =
				p_can_msg->can_data[7];  
			break;
		case 24:
			fcu_data_buffer.air_data_buffer.air_compressor_speed_setpoint =
				((u32)(	p_can_msg->can_data[7]))<<24 |
				((u32)(	p_can_msg->can_data[6]))<<16 |
				((u32)(	p_can_msg->can_data[5]))<<8  |
				((u32)(	p_can_msg->can_data[4]));          
			break;       
			
			
			               
		case 25:
			fcu_data_buffer.water_for_pile_data_buffer.water_pump_pwm_dutyfactor1 =
				four_byte_convert_float(	p_can_msg->can_data[4],	p_can_msg->can_data[5],
				p_can_msg->can_data[6],	p_can_msg->can_data[7]);
			break;
		case 26:
			fcu_data_buffer.water_for_pile_data_buffer.water_fan_pwm_dutyfactor1 =
				four_byte_convert_float(	p_can_msg->can_data[4],	p_can_msg->can_data[5],
				p_can_msg->can_data[6],	p_can_msg->can_data[7]);
			break;
		case 27:
			fcu_data_buffer.water_for_pile_data_buffer.water_fan_pwm_dutyfactor2 =
				four_byte_convert_float(	p_can_msg->can_data[4],	p_can_msg->can_data[5],
				p_can_msg->can_data[6],	p_can_msg->can_data[7]);
			break; 
		case 28:
			fcu_data_buffer.water_for_pile_data_buffer.water_temperature_fan_pid1.is_enble_pid =
				p_can_msg->can_data[7]; 
			break;   
		case 29:
			fcu_data_buffer.water_for_pile_data_buffer.water_temperature_fan_pid1.Kp =
				four_byte_convert_float(	p_can_msg->can_data[4],	p_can_msg->can_data[5],
				p_can_msg->can_data[6],	p_can_msg->can_data[7]);
			break;
		case 30:
			fcu_data_buffer.water_for_pile_data_buffer.water_temperature_fan_pid1.Ki =
				four_byte_convert_float(	p_can_msg->can_data[4],	p_can_msg->can_data[5],
				p_can_msg->can_data[6],	p_can_msg->can_data[7]);
			break;
		case 31:
			fcu_data_buffer.water_for_pile_data_buffer.water_temperature_fan_pid1.Kd =
				four_byte_convert_float(	p_can_msg->can_data[4],	p_can_msg->can_data[5],
				p_can_msg->can_data[6],	p_can_msg->can_data[7]);
			break;
		case 32:
			fcu_data_buffer.water_for_pile_data_buffer.water_temperature_target_value1 =
				four_byte_convert_float(	p_can_msg->can_data[4],	p_can_msg->can_data[5],
				p_can_msg->can_data[6],	p_can_msg->can_data[7]);
			break;  
			
			
			
		case 33:
			fcu_data_buffer.water_for_compressor_data_bufferr.water_pump_enable =
				p_can_msg->can_data[7];  
			break;
		case 34:
			fcu_data_buffer.water_for_compressor_data_bufferr.water_fan_pwm_dutyfactor =
				four_byte_convert_float(	p_can_msg->can_data[4],	p_can_msg->can_data[5],
				p_can_msg->can_data[6],	p_can_msg->can_data[7]);
			break; 
			
			
			  
		case 35:
			fcu_data_buffer.galvanic_pile_data_buffer.fcu_start_enable =
				p_can_msg->can_data[7]; 
			break;
		case 36:
			fcu_data_buffer.galvanic_pile_data_buffer.fcu_stutter_stop_enable =
				p_can_msg->can_data[7]; 
			break;  
		case 37:
			fcu_data_buffer.galvanic_pile_data_buffer.fcu_reset_enable =
				p_can_msg->can_data[7]; 
			break; 
		case 38:
			fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_is_enble_output =
				p_can_msg->can_data[7]; 
			break;
		case 39:
			fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_is_enble_load_resistance =
				p_can_msg->can_data[7]; 
			break;  
			
			

		case 40:
			control_policy_total_manager.fcu_system_running_mode =
				p_can_msg->can_data[7]; 
			break;

		default:
			break;      	


		}

	}
	return error_code;
}
//��λ������fcu//���ݷ�װ
enum Error_code pc_can_communication_labview_to_fcu_encapsulation(struct PC_can_communication_labview_to_fcu *  p_pc_can_communication_labview_to_fcu, CAN_message * p_can_msg)
{
	return Succeed;
}    
//��λ������fcu//���ݴ���
enum Error_code pc_can_communication_labview_to_fcu_execute(struct PC_can_communication_labview_to_fcu *  p_pc_can_communication_labview_to_fcu)
{
	return Succeed;
}           



//canͨ��Э����� ��ʼ��
enum Error_code Can_communication_protocol2_init(struct Can_Communication_Protocol2_Total * p_can_communication_protocol2_total)
{
	enum Error_code error_code = Succeed;
	int i = 0;

	if(p_can_communication_protocol2_total == NULL )
	{return Pointer_is_null;}

	error_code = Air_compressor_Control_Msg_init( &(p_can_communication_protocol2_total->air_compressor_control_msg) );
	if(error_code != Succeed)	{return error_code;}
	error_code = Air_compressor_stats_Msg2_init( &(p_can_communication_protocol2_total->air_compressor_stats_msg2) );
	if(error_code != Succeed)	{return error_code;}
	error_code = Air_compressor_alarm_Msg3_init( &(p_can_communication_protocol2_total->air_compressor_alarm_msg3) );
	if(error_code != Succeed)	{return error_code;}


	error_code = H2_PUMP_Control_Msg_init( &(p_can_communication_protocol2_total->h2_pump_control_msg) );
	if(error_code != Succeed)	{return error_code;}
	error_code = H2_circulating_pump_data_data_init( &(p_can_communication_protocol2_total->h2_circulating_pump_data) );
	if(error_code != Succeed)	{return error_code;}
	error_code = H2_circulating_pump_Parameter_values_init( &(p_can_communication_protocol2_total->h2_circulating_pump_parameter_values) );
	if(error_code != Succeed)	{return error_code;}
	error_code = H2_circulating_pump_AcKnowledgment_init( &(p_can_communication_protocol2_total->h2_circulating_pump_acknowledgment) );
	if(error_code != Succeed)	{return error_code;}


	for(i = 0 ;  i < ITINERANT_DETECTIVE_CAN_MESSAGE_NUMBER; i++)
	{
		error_code = Itinerant_detective_Single_voltage_actual_data_init( &(p_can_communication_protocol2_total->itinerant_detective_single_voltage_actual_data[i]) , i);
		if(error_code != Succeed)	{return error_code;}
	}
	error_code = Itinerant_detective_operate_statas_init( &(p_can_communication_protocol2_total->itinerant_detective_operate_statas), ITINERANT_DETECTIVE_OPERATE_STATAS );
	if(error_code != Succeed)	{return error_code;}
	error_code = Itinerant_detective_single_chip_highest_voltage_init( &(p_can_communication_protocol2_total->itinerant_detective_single_chip_highest_voltage), ITINERANT_DETECTIVE_SINGLE_CHIP_HIGHEST_VOLTAGE );
	if(error_code != Succeed)	{return error_code;}
	error_code = Itinerant_detective_single_chip_minimum_voltage_init( &(p_can_communication_protocol2_total->itinerant_detective_single_chip_minimum_voltage), ITINERANT_DETECTIVE_SINGLE_CHIP_MINIMUM_VOLTAGE );
	if(error_code != Succeed)	{return error_code;}
	error_code = Itinerant_detective_voltage_data_init( &(p_can_communication_protocol2_total->itinerant_detective_voltage_data), ITINERANT_DETECTIVE_SINGLE_VOLTAGE_SUM );
	if(error_code != Succeed)	{return error_code;}	

	error_code = Itinerant_detective_operate_statas_init( &(p_can_communication_protocol2_total->itinerant_detective_operate_statas2), ITINERANT_DETECTIVE_OPERATE_STATAS2 );
	if(error_code != Succeed)	{return error_code;}
	error_code = Itinerant_detective_single_chip_highest_voltage_init( &(p_can_communication_protocol2_total->itinerant_detective_single_chip_highest_voltage2), ITINERANT_DETECTIVE_SINGLE_CHIP_HIGHEST_VOLTAGE2 );
	if(error_code != Succeed)	{return error_code;}
	error_code = Itinerant_detective_single_chip_minimum_voltage_init( &(p_can_communication_protocol2_total->itinerant_detective_single_chip_minimum_voltage2), ITINERANT_DETECTIVE_SINGLE_CHIP_MINIMUM_VOLTAGE2 );
	if(error_code != Succeed)	{return error_code;}
	error_code = Itinerant_detective_voltage_data_init( &(p_can_communication_protocol2_total->itinerant_detective_voltage_data2), ITINERANT_DETECTIVE_SINGLE_VOLTAGE_SUM2 );
	if(error_code != Succeed)	{return error_code;}	

	error_code = Insulation_monitor_data_init( &(p_can_communication_protocol2_total->insulation_monitor_data) );
	if(error_code != Succeed)	{return error_code;}    

	for(i = 0 ;  i < AD_AUXILIARY_BOARD_MESSAGE_NUMBER_MAX; i++)
	{
		error_code = ad_auxiliary_board_message_init( &(p_can_communication_protocol2_total->ad_auxiliary_board_message_array[i]) , i);
		if(error_code != Succeed)	{return error_code;}
	}
	
	
	error_code = pc_can_communication_fcu_to_labview_init( &(p_can_communication_protocol2_total->pc_can_communication_fcu_to_labview) );
	if(error_code != Succeed)	{return error_code;}	
	error_code = pc_can_communication_labview_to_fcu_init( &(p_can_communication_protocol2_total->pc_can_communication_labview_to_fcu) );
	if(error_code != Succeed)	{return error_code;}	

	return error_code;
}






//���������ݵ�ʱ������
enum Error_code Can_communication_protocol2_clear_time(struct Can_Communication_Protocol2_Total * p_can_communication_protocol2_total)
{
	enum Error_code error_code = Succeed;
	int i = 0;

	if(p_can_communication_protocol2_total == NULL )
	{return Pointer_is_null;}

	p_can_communication_protocol2_total->air_compressor_control_msg.updata_event_time = 0;
	p_can_communication_protocol2_total->air_compressor_stats_msg2.updata_event_time = 0;
	p_can_communication_protocol2_total->air_compressor_alarm_msg3.updata_event_time = 0;

	p_can_communication_protocol2_total->h2_pump_control_msg.updata_event_time = 0;
	p_can_communication_protocol2_total->h2_circulating_pump_data.updata_event_time = 0;
	p_can_communication_protocol2_total->h2_circulating_pump_parameter_values.updata_event_time = 0;
	p_can_communication_protocol2_total->h2_circulating_pump_acknowledgment.updata_event_time = 0;

	for(i = 0 ;  i < ITINERANT_DETECTIVE_CAN_MESSAGE_NUMBER; i++)
	{
		p_can_communication_protocol2_total->itinerant_detective_single_voltage_actual_data[i].updata_event_time = 0;    
	}
	p_can_communication_protocol2_total->itinerant_detective_operate_statas.updata_event_time = 0;
	p_can_communication_protocol2_total->itinerant_detective_single_chip_highest_voltage.updata_event_time = 0;
	p_can_communication_protocol2_total->itinerant_detective_single_chip_minimum_voltage.updata_event_time = 0;
	p_can_communication_protocol2_total->itinerant_detective_voltage_data.updata_event_time = 0;
	

	p_can_communication_protocol2_total->itinerant_detective_operate_statas2.updata_event_time = 0;
	p_can_communication_protocol2_total->itinerant_detective_single_chip_highest_voltage2.updata_event_time = 0;
	p_can_communication_protocol2_total->itinerant_detective_single_chip_minimum_voltage2.updata_event_time = 0;
	p_can_communication_protocol2_total->itinerant_detective_voltage_data2.updata_event_time = 0;

	p_can_communication_protocol2_total->insulation_monitor_data.updata_event_time = 0;
	
	for(i = 0 ;  i < AD_AUXILIARY_BOARD_MESSAGE_NUMBER_MAX; i++)
	{
		p_can_communication_protocol2_total->ad_auxiliary_board_message_array[i].updata_event_time = 0;    
	}

	p_can_communication_protocol2_total->pc_can_communication_fcu_to_labview.updata_event_time = 0;
	p_can_communication_protocol2_total->pc_can_communication_labview_to_fcu.updata_event_time = 0;
	
	return error_code;    
}
                            

//ͨ�����ܵ�CAN��Ϣ�����������ݡ�
enum Error_code Can_communication_protocol2_updata_receivev_can(struct Can_Communication_Protocol2_Total * p_can_communication_protocol2_total, CAN_message * p_can_msg)
{
	enum Error_code error_code = Succeed;

	if(p_can_communication_protocol2_total == NULL || p_can_msg == NULL)
	{return Pointer_is_null;}

	if(p_can_msg->can_rtr == CAN_RTR_Data)
	{	
		//��չ֡
		if(p_can_msg->can_ide == CAN_Id_Extended)
		{
			switch(p_can_msg->can_message_id)
			{
			case AIR_COMPRESSOR_STATS_MSG2_ID:
				error_code = Air_compressor_stats_Msg2_analysis(p_can_msg, &(p_can_communication_protocol2_total->air_compressor_stats_msg2) );
				if(error_code != Succeed)	{return error_code;}
				break;
			case AIR_COMPRESSOR_ALARM_MSG3:
				error_code = Air_compressor_alarm_Msg3_analysis(p_can_msg, &(p_can_communication_protocol2_total->air_compressor_alarm_msg3) );
				if(error_code != Succeed)	{return error_code;}
				break;	

			case H2_CIRCULATING_PUMP_DATA_ID:
				error_code = H2_circulating_pump_data_analysis(p_can_msg, &(p_can_communication_protocol2_total->h2_circulating_pump_data) );
				if(error_code != Succeed)	{return error_code;}
				break;
				//ʵ�⣬��2������ѭ����û�з���fcu���²⣬��2����fcu��Ҫ��������ѭ���õ�
/*			case H2_CIRCULATING_PUMP_PARAMETER_VALUES_ID:
				error_code = H2_circulating_pump_Parameter_values_analysis(p_can_msg, &(p_can_communication_protocol2_total->h2_circulating_pump_parameter_values) );
				if(error_code != Succeed)	{return error_code;}
				break;
			case H2_CIRCULATING_PUMP_ACKNOWLEDGMENT:
				error_code = H2_circulating_pump_AcKnowledgment_analysis(p_can_msg, &(p_can_communication_protocol2_total->h2_circulating_pump_acknowledgment) );
				if(error_code != Succeed)	{return error_code;}
				break;
        */

			case ITINERANT_DETECTIVE_OPERATE_STATAS:       
				error_code = Itinerant_detective_operate_statas_analysis(p_can_msg, &(p_can_communication_protocol2_total->itinerant_detective_operate_statas) );
				if(error_code != Succeed)	{return error_code;}
				break;
			case ITINERANT_DETECTIVE_SINGLE_CHIP_HIGHEST_VOLTAGE:     
				error_code = Itinerant_detective_single_chip_highest_voltage_analysis(p_can_msg, &(p_can_communication_protocol2_total->itinerant_detective_single_chip_highest_voltage) );
				if(error_code != Succeed)	{return error_code;}
				break;
			case ITINERANT_DETECTIVE_SINGLE_CHIP_MINIMUM_VOLTAGE:     
				error_code = Itinerant_detective_single_chip_minimum_voltage_analysis(p_can_msg, &(p_can_communication_protocol2_total->itinerant_detective_single_chip_minimum_voltage) );
				if(error_code != Succeed)	{return error_code;}
				break;   
		  case ITINERANT_DETECTIVE_SINGLE_VOLTAGE_SUM:   
				error_code = Itinerant_detective_voltage_data_analysis(p_can_msg, &(p_can_communication_protocol2_total->itinerant_detective_voltage_data) );
				if(error_code != Succeed)	{return error_code;}        
				break;
			
			
			case ITINERANT_DETECTIVE_OPERATE_STATAS2:              
				error_code = Itinerant_detective_operate_statas_analysis(p_can_msg, &(p_can_communication_protocol2_total->itinerant_detective_operate_statas2) );
				if(error_code != Succeed)	{return error_code;}
				break;
			case ITINERANT_DETECTIVE_SINGLE_CHIP_HIGHEST_VOLTAGE2:      
				error_code = Itinerant_detective_single_chip_highest_voltage_analysis(p_can_msg, &(p_can_communication_protocol2_total->itinerant_detective_single_chip_highest_voltage2) );
				if(error_code != Succeed)	{return error_code;}
				break;
			case ITINERANT_DETECTIVE_SINGLE_CHIP_MINIMUM_VOLTAGE2:      
				error_code = Itinerant_detective_single_chip_minimum_voltage_analysis(p_can_msg, &(p_can_communication_protocol2_total->itinerant_detective_single_chip_minimum_voltage2) );
				if(error_code != Succeed)	{return error_code;}
				break;
			case ITINERANT_DETECTIVE_SINGLE_VOLTAGE_SUM2:           
				error_code = Itinerant_detective_voltage_data_analysis(p_can_msg, &(p_can_communication_protocol2_total->itinerant_detective_voltage_data2) );
				if(error_code != Succeed)	{return error_code;}        
				break;
									                            
			case INSULATION_MONITOR_DATA_ID:
				error_code = Insulation_monitor_data_analysis(p_can_msg, &(p_can_communication_protocol2_total->insulation_monitor_data) );
				if(error_code != Succeed)	{return error_code;}
				break;                                 
				
			//labview����fcu	
			case PC_CAN_COMMUNICATION_LABVIEW_TO_FCU_ID:           
				error_code = pc_can_communication_labview_to_fcu_analysis(p_can_msg, &(p_can_communication_protocol2_total->pc_can_communication_labview_to_fcu) );
				if(error_code != Succeed)	{return error_code;}        
				break;	


			default:
				if(p_can_msg->can_message_id >= ITINERANT_DETECTIVE_SINGLE_VOLTAGE_ACTUAL_DATA &&
					p_can_msg->can_message_id < ITINERANT_DETECTIVE_SINGLE_VOLTAGE_ACTUAL_DATA+ITINERANT_DETECTIVE_CAN_MESSAGE_NUMBER)
				{
					int i =  (u32)(p_can_msg->can_message_id -  ITINERANT_DETECTIVE_SINGLE_VOLTAGE_ACTUAL_DATA);
					error_code = Itinerant_detective_Single_voltage_actual_data_analysis(p_can_msg, &(p_can_communication_protocol2_total->itinerant_detective_single_voltage_actual_data[i]) );
					if(error_code != Succeed)	{return error_code;}
				}
				
				if(p_can_msg->can_message_id >= AD_AUXILIARY_BOARD_MESSAGE_ID &&
					p_can_msg->can_message_id < AD_AUXILIARY_BOARD_MESSAGE_ID + AD_AUXILIARY_BOARD_MESSAGE_NUMBER_MAX)
				{
					int i =  (u32)(p_can_msg->can_message_id -  AD_AUXILIARY_BOARD_MESSAGE_ID);
					error_code = ad_auxiliary_board_message_analysis(p_can_msg, &(p_can_communication_protocol2_total->ad_auxiliary_board_message_array[i]) );
					if(error_code != Succeed)	{return error_code;}
				}
				break;
			}
		}

		//��׼֡
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




//��ʱ��װcan����
//���û����Ҫ���͵���Ϣ�����ش���
//ע��һ��ֻ��ת��һ��������Ϣ������ж�������ѭ�����ñ�������ֱ�����������ش���
enum Error_code Can_communication_protocol2_can_encapsulation_and_send(struct Can_Communication_Protocol2_Total * p_can_communication_protocol2_total, CAN_message * p_can_msg)
{
	enum Error_code error_code = Succeed;

	if(p_can_msg == NULL || p_can_communication_protocol2_total == NULL)
	{return Pointer_is_null;}

	if(system_time - p_can_communication_protocol2_total->air_compressor_control_msg.updata_event_time > p_can_communication_protocol2_total->air_compressor_control_msg.send_message_time_max)
	{                         
		error_code = Air_compressor_Control_Msg_encapsulation( &(p_can_communication_protocol2_total->air_compressor_control_msg),  p_can_msg);
		if(error_code == Succeed)
		{                  
//			error_code = Control_Policy_ontime_can_send_data( CAN0,  p_can_msg);
			error_code = Control_Policy_ontime_can_send_data( CAN1,  p_can_msg);
//			error_code = Control_Policy_ontime_can_send_data( CAN2,  p_can_msg);
			test_can_send++;
		}
		return error_code;//���۳ɹ���񣬶�Ҫ���������������Ϊ����һ��ֻ�ܴ���һ����Ϣ��ת��
	}     
	if(system_time - p_can_communication_protocol2_total->h2_pump_control_msg.updata_event_time > p_can_communication_protocol2_total->h2_pump_control_msg.send_message_time_max)
	{                        
		error_code = H2_PUMP_Control_Msg_encapsulation( &(p_can_communication_protocol2_total->h2_pump_control_msg),  p_can_msg);
		if(error_code == Succeed)
		{                 
//			error_code = Control_Policy_ontime_can_send_data( CAN0,  p_can_msg);
			error_code = Control_Policy_ontime_can_send_data( CAN1,  p_can_msg);
//			error_code = Control_Policy_ontime_can_send_data( CAN2,  p_can_msg);
			test_can_send++;
		}
		return error_code;//���۳ɹ���񣬶�Ҫ���������������Ϊ����һ��ֻ�ܴ���һ����Ϣ��ת��
	}	
     
    //fcu����labview
    if((p_can_communication_protocol2_total->pc_can_communication_fcu_to_labview.can_message_index == 0 &&
        system_time - p_can_communication_protocol2_total->pc_can_communication_fcu_to_labview.updata_event_time > 
        p_can_communication_protocol2_total->pc_can_communication_fcu_to_labview.send_message_time_max)
        ||  (p_can_communication_protocol2_total->pc_can_communication_fcu_to_labview.can_message_index > 0 &&
            p_can_communication_protocol2_total->pc_can_communication_fcu_to_labview.can_message_index < 44)  )
    {
        error_code = pc_can_communication_fcu_to_labview_encapsulation( &(p_can_communication_protocol2_total->pc_can_communication_fcu_to_labview),  p_can_msg);
		if(error_code == Succeed)
		{  
		    error_code = Control_Policy_ontime_can_send_data( CAN0,  p_can_msg);               
//			error_code = Control_Policy_ontime_can_send_data( CAN1,  p_can_msg);
			test_can_send++;
			p_can_communication_protocol2_total->pc_can_communication_fcu_to_labview.can_message_index++;
			if(p_can_communication_protocol2_total->pc_can_communication_fcu_to_labview.can_message_index >= 44 )
			{
			    p_can_communication_protocol2_total->pc_can_communication_fcu_to_labview.can_message_index = 0;
			}
		}
		return error_code;//���۳ɹ���񣬶�Ҫ���������������Ϊ����һ��ֻ�ܴ���һ����Ϣ��ת��
    }

	//���û�е�������Ϣ��ʱ�䣬��ôת��ʧ�ܡ���ʾ��ǰ����Ҫ���͡�
	error_code = NoData;
	return error_code;
}



/*
//��ʱ����can���ݣ�Ĭ��can1��
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








