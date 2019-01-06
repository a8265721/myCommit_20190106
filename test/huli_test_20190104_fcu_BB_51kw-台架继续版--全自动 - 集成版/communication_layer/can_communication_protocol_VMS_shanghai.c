#include "can_communication_protocol_VMS_shanghai.h"
#include "control_manager.h"   

//�Ϻ�ǿ�� canͨ��Э����� 
struct Can_Communication_Protocol_VMS_Shanghai_Total    can_communication_protocol_vms_shanghai_total;   


//vms����fcu�Ŀ�������//��ʼ��
enum Error_code VMS_to_FCU_control_msg_init(struct VMS_to_FCU_control_msg *  p_vms_to_fcu_control_msg)
{
	enum Error_code error_code = Succeed;

	if(p_vms_to_fcu_control_msg == NULL )
	{return Pointer_is_null;}

	p_vms_to_fcu_control_msg->updata_event_time = system_time;
	p_vms_to_fcu_control_msg->overtime_max = CAN_OVERTIME_MAX;
	p_vms_to_fcu_control_msg->Message_id = VMS_TO_FCU_CONTROL_MSG_ID;

	return error_code;
}

//vms����fcu�Ŀ�������//���ݽ���
enum Error_code VMS_to_FCU_control_msg_analysis(CAN_message * p_can_msg, struct VMS_to_FCU_control_msg *  p_vms_to_fcu_control_msg)
{
	enum Error_code error_code = Succeed;

	if(p_can_msg == NULL || p_vms_to_fcu_control_msg == NULL)
	{return Pointer_is_null;}

	if(p_vms_to_fcu_control_msg->Message_id != p_can_msg->can_message_id)
	{
		error_code =  CAN_data_analysis_id_error;
	}
	else
	{
		p_vms_to_fcu_control_msg->updata_event_time = system_time;

		/*
	?	1 Byte��FCEPSet��FCE�����趨�����ֽ�
	?	2 Byte��FCEPSet��FCE�����趨�����ֽ�
	?	3 Byte��FCECmdByte��FCE��ͣ���
	?		bit5��bit4:FCECommand��������00��/�����ػ���01��/ ������10��/��ɨͣ����11��
	?		bit3��bit2��FCE ʹ���źţ�FCEEnable���� ������10��/��ײ��01��
	?		bit1��bit0��FCE ��ͣ�����źţ�FCEShutdown����ȡ����10��/��ͣ��01��
		*/

		//����Ŀǰ���ز�����fcu�����ƣ�������ﲻ�ܽ���������ʵ��趨��
		//FCE ʹ���źţ�FCEEnable���� ������10��/��ײ��01�������ϵͳû�У����ϵ�֮��ϵͳ�Լ�ͻ�������״̬��Ȼ��ȴ��������
		if( (p_can_msg->can_data[2] & 0x03) == 0x02)
		{
			fcu_data_buffer.galvanic_pile_data_buffer.fcu_stutter_stop_enable = 0;
		}
		else if( (p_can_msg->can_data[2] & 0x03) == 0x01)
		{
			fcu_data_buffer.galvanic_pile_data_buffer.fcu_stutter_stop_enable = 1;
		}
		//��������������ʹ�ܡ�		�����������ػ��ʹ�ɨͣ�� ���ǹر�����ʹ��
		if( (p_can_msg->can_data[2] & 0x30) == 0x10)
		{
			fcu_data_buffer.galvanic_pile_data_buffer.fcu_start_enable = 1;
		}
		else 
		{
			fcu_data_buffer.galvanic_pile_data_buffer.fcu_start_enable = 0;
		}

	}

	return error_code;
}
//vms����fcu�Ŀ�������//���ݷ�װ
enum Error_code VMS_to_FCU_control_msg_encapsulation(struct VMS_to_FCU_control_msg *  p_vms_to_fcu_control_msg, CAN_message * p_can_msg)
{
	return Succeed;
}
//vms����fcu�Ŀ�������//���ݴ���
enum Error_code VMS_to_FCU_control_msg_execute(struct VMS_to_FCU_control_msg *  p_vms_to_fcu_control_msg)
{
	return Succeed;
}






//fcu����vms��״̬��Ϣ//��ʼ��
enum Error_code FCU_to_VMS_system_status_msg_init(struct FCU_to_VMS_system_status_msg *  p_fcu_to_vms_system_status_msg)
{
	enum Error_code error_code = Succeed;

	if(p_fcu_to_vms_system_status_msg == NULL )
	{return Pointer_is_null;}

	p_fcu_to_vms_system_status_msg->updata_event_time = system_time;
	p_fcu_to_vms_system_status_msg->send_message_time_max = CAN_SEND_MESSAGE_TIME_MAX_20;
	p_fcu_to_vms_system_status_msg->Message_id = FCU_TO_VMS_SYSTEM_STATUS_MSG_ID;

	p_fcu_to_vms_system_status_msg->power_output_max = 0;
	p_fcu_to_vms_system_status_msg->power_output_max_updata_time = 0;
	p_fcu_to_vms_system_status_msg->fcu_output_electricity_level = 0;
	return error_code;

}
//fcu����vms��״̬��Ϣ//���ݽ���
enum Error_code FCU_to_VMS_system_status_msg_analysis(CAN_message * p_can_msg, struct FCU_to_VMS_system_status_msg *  p_fcu_to_vms_system_status_msg)
{
	return Succeed;
}
//fcu����vms��״̬��Ϣ//���ݷ�װ
enum Error_code FCU_to_VMS_system_status_msg_encapsulation(struct FCU_to_VMS_system_status_msg *  p_fcu_to_vms_system_status_msg, CAN_message * p_can_msg)
{
	enum Error_code error_code = Succeed;
	u32 temp0;
	u32 temp1;
	u8  temp2;
	u8  temp3;
	if(p_fcu_to_vms_system_status_msg == NULL || p_can_msg == NULL)
	{return Pointer_is_null;}

	p_fcu_to_vms_system_status_msg->updata_event_time = system_time;

	//�������ݷ�װ
	p_can_msg->can_message_id = p_fcu_to_vms_system_status_msg->Message_id;
	p_can_msg->can_ide = CAN_Id_Standard;//��׼֡
	p_can_msg->can_rtr = CAN_RTR_Data;
	p_can_msg->can_len = 8;

	/*
?	1 Byte��FCEPstIs��ȼ�ϵ�ضѵ繦�ʣ����ֽ� 
?	2 Byte��FCEPstIs��ȼ�ϵ�ضѵ繦�ʣ����ֽ� 
?	3 Byte��FCEPLmt(��ǰ FCE ����������ֵ�����ֽ�		��ǰ����������ֵ����ֵ�����ֽڣ�
?	4 Byte��FCEPLmt(��ǰ FCE ����������ֵ�����ֽ�		��ǰ����������ֵ����ֵ�����ֽڣ�
?	5 Byte��FCEPParaIs�������豸���Ĺ��ʣ����ֽ�
?	6 Byte��FCEPParaIs�������豸���Ĺ��ʣ����ֽ�
?	7 Byte��FCEContStatus��FCE �̵�����ˮ��Һλ״̬��
		FCE �̵�����ˮ��Һλ״̬��
?		bit3��bit2: Һλ������10��/Һλ���ͣ�01��
?		bit1��bit0���Ͽ���01��/��ͨ��10��
?	8 Byte��FCEStatus��ȼ�ϵ�ص�ǰ״̬�룩
		bit 8~6��	100 ���Ƶ�Դ��ͨ��PowerUp��
					000 ������Ready��
					111 ��Ϻͱ궨��Diag_Cali��
					101 ���ϣ�Error��
					010 ʹ�ܹ���״̬��Enabled��
					110 ��ͣ����������EmergencyOn��
		bit 5~4��	������״̬λ��101
						00 �޹�������
						01 4������΢���ϣ�
						10 3����һ����ϣ�
					������״̬λ��101
						01 2�����θ߼���
						10 1������߼���
		bit 3~1��	��չ״̬λ	�������㲿��ʹ�ã���ϸ�������ҳβ����
*/
	
	//ȼ�ϵ�صĵ�ǰ����
	temp0 = (u32)(fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_voltage * 
		fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_electricity);
	p_can_msg->can_data[0] =  (u8)((temp0/60)); 
	p_can_msg->can_data[1] =  (u8)((temp0/60)>>8);

	//�ж�����̵�����ֻ����������֮�󣬲������� ����������ֵ����ֵ
	if(fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_is_enble_output == 1)
	{
		//ÿ�ε���֮�󣬶�Ҫ��2s�����ܸ���	����������ֵ����ֵ 
		if(system_time - p_fcu_to_vms_system_status_msg->power_output_max_updata_time > 2000 && 
			(fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_inlet1 > 63 ||
			(fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_inlet1 > 60 && fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_electricity <305 ) ||
			(fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_inlet1 > 55 && fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_electricity <275 ) ||
			(fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_inlet1 > 50 && fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_electricity <245 ) ||
			(fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_inlet1 > 45 && fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_electricity <215 ) ||
			(fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_inlet1 > 40 && fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_electricity <185 ) ||
			(fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_inlet1 > 35 && fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_electricity <155 ) ||
			(fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_inlet1 > 30 && fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_electricity <125 ) ||
			(fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_inlet1 > 25 && fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_electricity <95  ) ||
			(fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_inlet1 > 20 && fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_electricity <80  ) ||
			(fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_inlet1 > 15 && fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_electricity <60  ) ||
			(fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_inlet1 > 10 && fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_electricity <40  ) ||
			(fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_inlet1 > 5  && fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_electricity <20  ) ||
			(fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_inlet1 > 0  && fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_electricity <10  )   ))
			//ע���ˣ�0�����£��ǲ�����Ӹ��صġ�
		{
			//��������£��������أ�һ��1000w��
			if(fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_inlet1 < 30)
			{
				p_fcu_to_vms_system_status_msg->power_output_max = temp0 + 1000;
				p_fcu_to_vms_system_status_msg->power_output_max_updata_time = system_time;
			}
			else
			{
				//��ǰ����������ֵ����ֵ = ��ǰ��ѹ * ��һ����λ���޵��������޵�����ƽ��ֵ
				temp1 = (u32)(fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_voltage * 
					(control_policy_total_manager.fcu_run_data_debug[p_fcu_to_vms_system_status_msg->fcu_output_electricity_level + 1].fcu_output_electricity_lower_limit + 
					control_policy_total_manager.fcu_run_data_debug[p_fcu_to_vms_system_status_msg->fcu_output_electricity_level + 1].fcu_output_electricity_upper_limit) /2 );
				p_fcu_to_vms_system_status_msg->power_output_max = temp1 < 53000 ? temp1 : 53000;
			}
		}
		//����ά����һ�εĲ��䡣

		if(control_policy_total_manager.fcu_output_electricity_level != p_fcu_to_vms_system_status_msg->fcu_output_electricity_level)
		{
			p_fcu_to_vms_system_status_msg->power_output_max_updata_time = system_time;
			p_fcu_to_vms_system_status_msg->fcu_output_electricity_level = control_policy_total_manager.fcu_output_electricity_level;
		}
	}
	else
	{
		p_fcu_to_vms_system_status_msg->power_output_max = 0;
	}

	p_can_msg->can_data[2] =  (u8)((p_fcu_to_vms_system_status_msg->power_output_max/60)); 
	p_can_msg->can_data[3] =  (u8)((p_fcu_to_vms_system_status_msg->power_output_max/60)>>8);
	//�����豸���Ĺ��ʣ�Ŀǰû�У�Ĭ��Ϊ0
	p_can_msg->can_data[4] = 0;
	p_can_msg->can_data[5] = 0;

	//�ж�����̵�����Ŀǰû��ˮ��Һλ��Ĭ��Ϊˮλ������
	if(fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_is_enble_output == 1)
	{
		p_can_msg->can_data[6] = 0xa;
	}
	else
	{
		p_can_msg->can_data[6] = 0x9;
	}


	//�ж�fcu״̬�͹��ϼ���
	if(fcu_data_buffer.galvanic_pile_data_buffer.fcu_stutter_stop_enable == 1)
	{
		p_can_msg->can_data[7] = 0xc0;
	}
	else
	{
		switch(control_policy_total_manager.working_status_mode)
		{
			case working_status_communication_outage:
				p_can_msg->can_data[7] = 0x80;
				break;
			case working_status_wait:
				p_can_msg->can_data[7] = 0x00;
				break;
			//����״̬λ �� ��Ϻͱ궨��Diag_Cali��Ŀǰû��
			case working_status_error:
				p_can_msg->can_data[7] = 0xa0;
				break;
			case working_status_run:
			case working_status_starting:
			case working_status_stoping:
				p_can_msg->can_data[7] = 0x40;
				break;
			default:
				p_can_msg->can_data[7] = 0x00;
				break;
		}
	}
	/*
ȼ�ϵ�ؽγ���ȼ�ϵ�ع��ϱ�	
������Byte8��bit 5~4		��������			���ϵȼ�								fcu���ڲ�ϵͳ����
0x10						��߼���Σ�չ���	1 ��(����ͣ������)						û��
0x01						�θ߼������ع���	2 ��(����ͣ������)						1 �����Զ�ͣ����		
0x10						�εͼ���һ�����	3 ��(�����ʹ���)						2 �����Զ�������vms���Ը������أ�
0x01						��ͼ�����΢���� 	4 ��(ά��FCE���������У���¼����)		3 ������΢���ϣ�ֻ����ʾ���ã�	
*/
	switch(control_policy_total_manager.working_alarm_mode)
	{
		case one_level_fault:
			p_can_msg->can_data[7] |= 0x08;
			break;
		case two_level_fault:
			p_can_msg->can_data[7] |= 0x10;
			break;	
		case three_level_fault:
			p_can_msg->can_data[7] |= 0x08;
			break;	
		case working_normal:
			p_can_msg->can_data[7] |= 0x00;
			break;	
	}

	p_can_msg->can_priorty = 0;
	return error_code;                                       

}
//fcu����vms��״̬��Ϣ//���ݴ���
enum Error_code FCU_to_VMS_system_status_msg_execute(struct FCU_to_VMS_system_status_msg *  p_fcu_to_vms_system_status_msg)
{
	return Succeed;
}






//fcu����vms�ĵ����Ϣ//��ʼ��
enum Error_code FCU_to_VMS_galvanic_pile_msg_init(struct FCU_to_VMS_galvanic_pile_msg *  p_fcu_to_vms_galvanic_pile_msg)
{
	enum Error_code error_code = Succeed;

	if(p_fcu_to_vms_galvanic_pile_msg == NULL )
	{return Pointer_is_null;}

	p_fcu_to_vms_galvanic_pile_msg->updata_event_time = system_time;
	p_fcu_to_vms_galvanic_pile_msg->send_message_time_max = CAN_SEND_MESSAGE_TIME_MAX_20;
	p_fcu_to_vms_galvanic_pile_msg->Message_id = FCU_TO_VMS_GALVANIC_PILE_MSG_ID;

	return error_code;
}
//fcu����vms�ĵ����Ϣ//���ݽ���
enum Error_code FCU_to_VMS_galvanic_pile_msg_analysis(CAN_message * p_can_msg, struct FCU_to_VMS_galvanic_pile_msg *  p_fcu_to_vms_galvanic_pile_msg)
{
	return Succeed;
}
//fcu����vms�ĵ����Ϣ//���ݷ�װ
enum Error_code FCU_to_VMS_galvanic_pile_msg_encapsulation(struct FCU_to_VMS_galvanic_pile_msg *  p_fcu_to_vms_galvanic_pile_msg, CAN_message * p_can_msg)
{
	enum Error_code error_code = Succeed;
	u16 temp;

	if(p_fcu_to_vms_galvanic_pile_msg == NULL || p_can_msg == NULL)
	{return Pointer_is_null;}

	p_fcu_to_vms_galvanic_pile_msg->updata_event_time = system_time;

	//�������ݷ�װ
	p_can_msg->can_message_id = p_fcu_to_vms_galvanic_pile_msg->Message_id;
	p_can_msg->can_ide = CAN_Id_Standard;//��׼֡
	p_can_msg->can_rtr = CAN_RTR_Data;
	p_can_msg->can_len = 8;
	/*
Byte1	FCE ���������� ���ֽ�
Byte2	FCE ���������� ���ֽ�
Byte3	FCE ��������ѹ�����ֽڣ�
Byte4	FCE ��������ѹ�����ֽڣ�
Byte5	FCE2CellMax���������ѹ�����ֽڣ�
Byte6	FCE2CellMax���������ѹ�����ֽڣ�
Byte7	FCE2CellMin�������С��ѹ�����ֽڣ�
Byte8	FCE2CellMin�������С��ѹ�����ֽڣ�
*/
	temp = (u16)(fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_electricity/0.4);
	p_can_msg->can_data[0] =  (u8)(temp); 
	p_can_msg->can_data[1] =  (u8)(temp>>8);
	temp = (u16)(fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_voltage/0.55);
	p_can_msg->can_data[2] =  (u8)(temp); 
	p_can_msg->can_data[3] =  (u8)(temp>>8);
	//Ѳ�췢�͵�Ƭ��ѹ��ʱ�����������2Ƭһ�죬�Ϻ�ǿ��Ҫ��һƬһ�졣
	if(fcu_data_buffer.galvanic_pile_data_buffer.electric1_single_chip_minimum_voltage < 
	    fcu_data_buffer.galvanic_pile_data_buffer.electric1_single_chip_minimum_voltage2)
	{
		temp = (u16)(fcu_data_buffer.galvanic_pile_data_buffer.electric1_single_chip_minimum_voltage /2 /0.01);
	}
	else
	{
		temp = (u16)(fcu_data_buffer.galvanic_pile_data_buffer.electric1_single_chip_minimum_voltage2 /2 /0.01);		
	}
	p_can_msg->can_data[4] =  (u8)(temp); 
	p_can_msg->can_data[5] =  (u8)(temp>>8);
	if(fcu_data_buffer.galvanic_pile_data_buffer.electric1_single_chip_highest_voltage > 
	    fcu_data_buffer.galvanic_pile_data_buffer.electric1_single_chip_highest_voltage2)
	{
		temp = (u16)(fcu_data_buffer.galvanic_pile_data_buffer.electric1_single_chip_highest_voltage /2 /0.01);
	}
	else
	{
		temp = (u16)(fcu_data_buffer.galvanic_pile_data_buffer.electric1_single_chip_highest_voltage2 /2 /0.01);		
	}
	p_can_msg->can_data[6] =  (u8)(temp); 
	p_can_msg->can_data[7] =  (u8)(temp>>8);

	p_can_msg->can_priorty = 0;
	return error_code;                                       
}
//fcu����vms�ĵ����Ϣ//���ݴ���
enum Error_code FCU_to_VMS_galvanic_pile_msg_execute(struct FCU_to_VMS_galvanic_pile_msg *  p_fcu_to_vms_galvanic_pile_msg)
{
	return Succeed;
}






//fcu����vms��������Ϣ//��ʼ��
enum Error_code FCU_to_VMS_h2_data_msg_init(struct FCU_to_VMS_h2_data_msg *  p_fcu_to_vms_h2_data_msg)
{
	enum Error_code error_code = Succeed;

	if(p_fcu_to_vms_h2_data_msg == NULL )
	{return Pointer_is_null;}

	p_fcu_to_vms_h2_data_msg->updata_event_time = system_time;
	p_fcu_to_vms_h2_data_msg->send_message_time_max = CAN_SEND_MESSAGE_TIME_MAX_100;
	p_fcu_to_vms_h2_data_msg->Message_id = FCU_TO_VMS_H2_DATA_MSG_ID;

	return error_code;
}
//fcu����vms��������Ϣ//���ݽ���
enum Error_code FCU_to_VMS_h2_data_msg_analysis(CAN_message * p_can_msg, struct FCU_to_VMS_h2_data_msg *  p_fcu_to_vms_h2_data_msg)
{
	return Succeed;
}
//fcu����vms��������Ϣ//���ݷ�װ
enum Error_code FCU_to_VMS_h2_data_msg_encapsulation(struct FCU_to_VMS_h2_data_msg *  p_fcu_to_vms_h2_data_msg, CAN_message * p_can_msg)
{
	enum Error_code error_code = Succeed;
	u16 temp;

	if(p_fcu_to_vms_h2_data_msg == NULL || p_can_msg == NULL)
	{return Pointer_is_null;}

	p_fcu_to_vms_h2_data_msg->updata_event_time = system_time;

	//�������ݷ�װ
	p_can_msg->can_message_id = p_fcu_to_vms_h2_data_msg->Message_id;
	p_can_msg->can_ide = CAN_Id_Standard;//��׼֡
	p_can_msg->can_rtr = CAN_RTR_Data;
	p_can_msg->can_len = 8;
/*
Byte1	FCEoutH2PrsIS��������ѹ�����ֽ�
Byte2	FCEoutH2PrsIS��������ѹ�����ֽ�
Byte3	FCEoutH2PrsIS��������ѹ�����ֽ�
Byte4	FCEoutH2PrsIS��������ѹ�����ֽ�
Byte5	���������¶ȵ��ֽ�
Byte6	���������¶ȸ��ֽ�
Byte7	���������¶ȵ��ֽ�
Byte8	���������¶ȸ��ֽ�
*/
	
	temp = (u16)(fcu_data_buffer.h2_data_buffer.h2_pressure_tail_outlet);
	p_can_msg->can_data[0] =  (u8)(temp); 
	p_can_msg->can_data[1] =  (u8)(temp>>8);
	temp = (u16)(fcu_data_buffer.h2_data_buffer.h2_pressure_pile_inlet);
	p_can_msg->can_data[2] =  (u8)(temp); 
	p_can_msg->can_data[3] =  (u8)(temp>>8);
	//������·û�а�װ�¶ȴ����������û���¶����ݣ�����Ĭ��Ϊ0
	p_can_msg->can_data[4] = 0;
	p_can_msg->can_data[5] = 0;
	p_can_msg->can_data[6] = 0;
	p_can_msg->can_data[7] = 0;

	p_can_msg->can_priorty = 0;
	return error_code;                                       
}
//fcu����vms��������Ϣ//���ݴ���
enum Error_code FCU_to_VMS_h2_data_msg_execute(struct FCU_to_VMS_h2_data_msg *  p_fcu_to_vms_h2_data_msg)
{
	return Succeed;
}







//fcu����vms�Ŀ�����Ϣ//��ʼ��
enum Error_code FCU_to_VMS_air_data_msg_init(struct FCU_to_VMS_air_data_msg *  p_fcu_to_vms_air_data_msg)
{
	enum Error_code error_code = Succeed;

	if(p_fcu_to_vms_air_data_msg == NULL )
	{return Pointer_is_null;}

	p_fcu_to_vms_air_data_msg->updata_event_time = system_time;
	p_fcu_to_vms_air_data_msg->send_message_time_max = CAN_SEND_MESSAGE_TIME_MAX_100;
	p_fcu_to_vms_air_data_msg->Message_id = FCU_TO_VMS_AIR_DATA_MSG_ID;

	return error_code;
}
//fcu����vms�Ŀ�����Ϣ//���ݽ���
enum Error_code FCU_to_VMS_air_data_msg_analysis(CAN_message * p_can_msg, struct FCU_to_VMS_air_data_msg *  p_fcu_to_vms_air_data_msg)
{
	return Succeed;
}
//fcu����vms�Ŀ�����Ϣ//���ݷ�װ
enum Error_code FCU_to_VMS_air_data_msg_encapsulation(struct FCU_to_VMS_air_data_msg *  p_fcu_to_vms_air_data_msg, CAN_message * p_can_msg)
{
	enum Error_code error_code = Succeed;
	u16 temp;

	if(p_fcu_to_vms_air_data_msg == NULL || p_can_msg == NULL)
	{return Pointer_is_null;}

	p_fcu_to_vms_air_data_msg->updata_event_time = system_time;

	//�������ݷ�װ
	p_can_msg->can_message_id = p_fcu_to_vms_air_data_msg->Message_id;
	p_can_msg->can_ide = CAN_Id_Standard;//��׼֡
	p_can_msg->can_rtr = CAN_RTR_Data;
	p_can_msg->can_len = 8;
/*
Byte1	��������ѹ�����ֽ�          
Byte2	��������ѹ�����ֽ�
Byte3	��������ѹ�����ֽ�
Byte4	��������ѹ�����ֽ�
Byte5	���������¶ȵ��ֽ�
Byte6	���������¶ȸ��ֽ�
Byte7	���������¶ȵ��ֽ�
Byte8	���������¶ȸ��ֽ�
*/
	
	temp = (u16)(fcu_data_buffer.air_data_buffer.air_pressure_pile_outlet);
	p_can_msg->can_data[0] =  (u8)(temp); 
	p_can_msg->can_data[1] =  (u8)(temp>>8);
	temp = (u16)(fcu_data_buffer.air_data_buffer.air_pressure_pile_inlet);
	p_can_msg->can_data[2] =  (u8)(temp); 
	p_can_msg->can_data[3] =  (u8)(temp>>8);
	temp = (u16)((fcu_data_buffer.air_data_buffer.air_temperature_pile_outlet +40) /0.16);
	p_can_msg->can_data[4] =  (u8)(temp); 
	p_can_msg->can_data[5] =  (u8)(temp>>8);
	temp = (u16)((fcu_data_buffer.air_data_buffer.air_temperature_pile_inlet +40) /0.16);
	p_can_msg->can_data[6] =  (u8)(temp); 
	p_can_msg->can_data[7] =  (u8)(temp>>8);

	p_can_msg->can_priorty = 0;
	return error_code;                                       
}
//fcu����vms�Ŀ�����Ϣ//���ݴ���
enum Error_code FCU_to_VMS_air_data_msg_execute(struct FCU_to_VMS_air_data_msg *  p_fcu_to_vms_air_data_msg)
{
	return Succeed;
}






//fcu����vms�ĵ��ˮ·��Ϣ//��ʼ��
enum Error_code FCU_to_VMS_water_for_pile_data_msg_init(struct FCU_to_VMS_water_for_pile_data_msg *  p_fcu_to_vms_water_for_pile_data_msg)
{
	enum Error_code error_code = Succeed;

	if(p_fcu_to_vms_water_for_pile_data_msg == NULL )
	{return Pointer_is_null;}

	p_fcu_to_vms_water_for_pile_data_msg->updata_event_time = system_time;
	p_fcu_to_vms_water_for_pile_data_msg->send_message_time_max = CAN_SEND_MESSAGE_TIME_MAX_100;
	p_fcu_to_vms_water_for_pile_data_msg->Message_id = FCU_TO_VMS_WATER_FOR_PILE_DATA_MSG_ID;

	return error_code;
}
//fcu����vms�ĵ��ˮ·��Ϣ//���ݽ���
enum Error_code FCU_to_VMS_water_for_pile_data_msg_analysis(CAN_message * p_can_msg, struct FCU_to_VMS_water_for_pile_data_msg *  p_fcu_to_vms_water_for_pile_data_msg)
{
	return Succeed;
}
//fcu����vms�ĵ��ˮ·��Ϣ//���ݷ�װ
enum Error_code FCU_to_VMS_water_for_pile_data_msg_encapsulation(struct FCU_to_VMS_water_for_pile_data_msg *  p_fcu_to_vms_water_for_pile_data_msg, CAN_message * p_can_msg)
{
	enum Error_code error_code = Succeed;
	u16 temp;

	if(p_fcu_to_vms_water_for_pile_data_msg == NULL || p_can_msg == NULL)
	{return Pointer_is_null;}

	p_fcu_to_vms_water_for_pile_data_msg->updata_event_time = system_time;

	//�������ݷ�װ
	p_can_msg->can_message_id = p_fcu_to_vms_water_for_pile_data_msg->Message_id;
	p_can_msg->can_ide = CAN_Id_Standard;//��׼֡
	p_can_msg->can_rtr = CAN_RTR_Data;
	p_can_msg->can_len = 8;
/*
Byte1	FCECoInPrsIs(FCE ��ȴˮ����ѹ�������ֽ�
Byte2	FCECoInPrsIs(FCE ��ȴˮ����ѹ�������ֽ�
Byte3	FCECoOutTemIs(FCE ��ȴˮ�����¶�)���ֽ�
Byte4	FCECoOutTemIs(FCE ��ȴˮ�����¶�)���ֽ�
Byte5	FCECoInTemIs(FCE ��ȴˮ�����¶ȣ����ֽ�
Byte6	FCECoInTemIs(FCE ��ȴˮ�����¶ȣ����ֽ�

*/
	
	temp = (u16)(fcu_data_buffer.water_for_pile_data_buffer.water_pressure_pile_inlet1);
	p_can_msg->can_data[0] =  (u8)(temp); 
	p_can_msg->can_data[1] =  (u8)(temp>>8);
	temp = (u16)((fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_outlet1 +40) /0.16);
	p_can_msg->can_data[2] =  (u8)(temp); 
	p_can_msg->can_data[3] =  (u8)(temp>>8);
	temp = (u16)((fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_inlet1 +40) /0.16);
	p_can_msg->can_data[4] =  (u8)(temp); 
	p_can_msg->can_data[5] =  (u8)(temp>>8);
	p_can_msg->can_data[6] =  0; 
	p_can_msg->can_data[7] =  0;

	p_can_msg->can_priorty = 0;
	return error_code;                                       
}
//fcu����vms�ĵ��ˮ·��Ϣ//���ݴ���
enum Error_code FCU_to_VMS_water_for_pile_data_msg_execute(struct FCU_to_VMS_water_for_pile_data_msg *  p_fcu_to_vms_water_for_pile_data_msg)
{
	return Succeed;
}





//�Ϻ�ǿ�� canͨ��Э����� ��ʼ��
enum Error_code Can_communication_protocol_vms_shanghai_init(struct Can_Communication_Protocol_VMS_Shanghai_Total * p_can_communication_protocol_vms_shanghai_total)
{
	enum Error_code error_code = Succeed;

	if(p_can_communication_protocol_vms_shanghai_total == NULL )
	{return Pointer_is_null;}

	error_code = VMS_to_FCU_control_msg_init( &(p_can_communication_protocol_vms_shanghai_total->vms_to_fcu_control_msg) );
	if(error_code != Succeed)	{return error_code;}
	error_code = FCU_to_VMS_system_status_msg_init( &(p_can_communication_protocol_vms_shanghai_total->fcu_to_vms_system_status_msg) );
	if(error_code != Succeed)	{return error_code;}
	error_code = FCU_to_VMS_galvanic_pile_msg_init( &(p_can_communication_protocol_vms_shanghai_total->fcu_to_vms_galvanic_pile_msg) );
	if(error_code != Succeed)	{return error_code;}
	error_code = FCU_to_VMS_h2_data_msg_init( &(p_can_communication_protocol_vms_shanghai_total->fcu_to_vms_h2_data_msg) );
	if(error_code != Succeed)	{return error_code;}
	error_code = FCU_to_VMS_air_data_msg_init( &(p_can_communication_protocol_vms_shanghai_total->fcu_to_vms_air_data_msg) );
	if(error_code != Succeed)	{return error_code;}
	error_code = FCU_to_VMS_water_for_pile_data_msg_init( &(p_can_communication_protocol_vms_shanghai_total->fcu_to_vms_water_for_pile_data_msg) );
	if(error_code != Succeed)	{return error_code;}

	return error_code;
}

//�Ϻ�ǿ�� ���������ݵ�ʱ������
enum Error_code Can_communication_protocol_vms_shanghai_clear_time(struct Can_Communication_Protocol_VMS_Shanghai_Total * p_can_communication_protocol_vms_shanghai_total)
{
	enum Error_code error_code = Succeed;

	if(p_can_communication_protocol_vms_shanghai_total == NULL )
	{return Pointer_is_null;}

	p_can_communication_protocol_vms_shanghai_total->vms_to_fcu_control_msg.updata_event_time = 0;
	p_can_communication_protocol_vms_shanghai_total->fcu_to_vms_system_status_msg.updata_event_time = 0;
	p_can_communication_protocol_vms_shanghai_total->fcu_to_vms_galvanic_pile_msg.updata_event_time = 0;
	p_can_communication_protocol_vms_shanghai_total->fcu_to_vms_h2_data_msg.updata_event_time = 0;
	p_can_communication_protocol_vms_shanghai_total->fcu_to_vms_air_data_msg.updata_event_time = 0;
	p_can_communication_protocol_vms_shanghai_total->fcu_to_vms_water_for_pile_data_msg.updata_event_time = 0;


	return error_code;    
}

//�Ϻ�ǿ�� ͨ�����ܵ�CAN��Ϣ�����������ݡ�
enum Error_code Can_communication_protocol_vms_shanghai_updata_receivev_can(struct Can_Communication_Protocol_VMS_Shanghai_Total * p_can_communication_protocol_vms_shanghai_total, CAN_message * p_can_msg)
{
	enum Error_code error_code = Succeed;

	if(p_can_communication_protocol_vms_shanghai_total == NULL || p_can_msg == NULL)
	{return Pointer_is_null;}

	if(p_can_msg->can_rtr == CAN_RTR_Data)
	{	
		//��չ֡
		if(p_can_msg->can_ide == CAN_Id_Extended)
		{
			switch(p_can_msg->can_message_id)
			{

			default:
				break;
			}
		}
		//��׼֡
		else if(p_can_msg->can_ide == CAN_Id_Standard)
		{
			switch(p_can_msg->can_message_id)
			{
			case VMS_TO_FCU_CONTROL_MSG_ID:
				error_code = VMS_to_FCU_control_msg_analysis(p_can_msg, &(p_can_communication_protocol_vms_shanghai_total->vms_to_fcu_control_msg) );
				if(error_code != Succeed)	{return error_code;}
				break;

			default:
				//need 
				break;
			}
		}
	}

	return error_code;
}


//�Ϻ�ǿ�� ��ʱ��װcan����
//���û����Ҫ���͵���Ϣ�����ش���
//ע��һ��ֻ��ת��һ��������Ϣ������ж�������ѭ�����ñ�������ֱ�����������ش���
enum Error_code Can_communication_protocol_vms_shanghai_can_encapsulation_and_send(struct Can_Communication_Protocol_VMS_Shanghai_Total * p_can_communication_protocol_vms_shanghai_total, CAN_message * p_can_msg)
{
	enum Error_code error_code = Succeed;

	if(p_can_msg == NULL || p_can_communication_protocol_vms_shanghai_total == NULL)
	{return Pointer_is_null;}

	if(system_time - p_can_communication_protocol_vms_shanghai_total->fcu_to_vms_system_status_msg.updata_event_time > p_can_communication_protocol_vms_shanghai_total->fcu_to_vms_system_status_msg.send_message_time_max)
	{                         
		error_code = FCU_to_VMS_system_status_msg_encapsulation( &(p_can_communication_protocol_vms_shanghai_total->fcu_to_vms_system_status_msg),  p_can_msg);
		if(error_code == Succeed)
		{                  
//			error_code = Control_Policy_ontime_can_send_data( CAN0,  p_can_msg);
//			error_code = Control_Policy_ontime_can_send_data( CAN1,  p_can_msg);
			error_code = Control_Policy_ontime_can_send_data( CAN2,  p_can_msg);
		}
		return error_code;//���۳ɹ���񣬶�Ҫ���������������Ϊ����һ��ֻ�ܴ���һ����Ϣ��ת��
	}     
	if(system_time - p_can_communication_protocol_vms_shanghai_total->fcu_to_vms_galvanic_pile_msg.updata_event_time > p_can_communication_protocol_vms_shanghai_total->fcu_to_vms_galvanic_pile_msg.send_message_time_max)
	{                         
		error_code = FCU_to_VMS_galvanic_pile_msg_encapsulation( &(p_can_communication_protocol_vms_shanghai_total->fcu_to_vms_galvanic_pile_msg),  p_can_msg);
		if(error_code == Succeed)
		{                  
//			error_code = Control_Policy_ontime_can_send_data( CAN0,  p_can_msg);
//			error_code = Control_Policy_ontime_can_send_data( CAN1,  p_can_msg);
			error_code = Control_Policy_ontime_can_send_data( CAN2,  p_can_msg);
		}
		return error_code;//���۳ɹ���񣬶�Ҫ���������������Ϊ����һ��ֻ�ܴ���һ����Ϣ��ת��
	}      
	if(system_time - p_can_communication_protocol_vms_shanghai_total->fcu_to_vms_h2_data_msg.updata_event_time > p_can_communication_protocol_vms_shanghai_total->fcu_to_vms_h2_data_msg.send_message_time_max)
	{                         
		error_code = FCU_to_VMS_h2_data_msg_encapsulation( &(p_can_communication_protocol_vms_shanghai_total->fcu_to_vms_h2_data_msg),  p_can_msg);
		if(error_code == Succeed)
		{                  
//			error_code = Control_Policy_ontime_can_send_data( CAN0,  p_can_msg);
//			error_code = Control_Policy_ontime_can_send_data( CAN1,  p_can_msg);
			error_code = Control_Policy_ontime_can_send_data( CAN2,  p_can_msg);
		}
		return error_code;//���۳ɹ���񣬶�Ҫ���������������Ϊ����һ��ֻ�ܴ���һ����Ϣ��ת��
	}      
	if(system_time - p_can_communication_protocol_vms_shanghai_total->fcu_to_vms_air_data_msg.updata_event_time > p_can_communication_protocol_vms_shanghai_total->fcu_to_vms_air_data_msg.send_message_time_max)
	{                         
		error_code = FCU_to_VMS_air_data_msg_encapsulation( &(p_can_communication_protocol_vms_shanghai_total->fcu_to_vms_air_data_msg),  p_can_msg);
		if(error_code == Succeed)
		{                  
//			error_code = Control_Policy_ontime_can_send_data( CAN0,  p_can_msg);
//			error_code = Control_Policy_ontime_can_send_data( CAN1,  p_can_msg);
			error_code = Control_Policy_ontime_can_send_data( CAN2,  p_can_msg);
		}
		return error_code;//���۳ɹ���񣬶�Ҫ���������������Ϊ����һ��ֻ�ܴ���һ����Ϣ��ת��
	}      
	if(system_time - p_can_communication_protocol_vms_shanghai_total->fcu_to_vms_water_for_pile_data_msg.updata_event_time > p_can_communication_protocol_vms_shanghai_total->fcu_to_vms_water_for_pile_data_msg.send_message_time_max)
	{                         
		error_code = FCU_to_VMS_water_for_pile_data_msg_encapsulation( &(p_can_communication_protocol_vms_shanghai_total->fcu_to_vms_water_for_pile_data_msg),  p_can_msg);
		if(error_code == Succeed)
		{                  
//			error_code = Control_Policy_ontime_can_send_data( CAN0,  p_can_msg);
//			error_code = Control_Policy_ontime_can_send_data( CAN1,  p_can_msg);
			error_code = Control_Policy_ontime_can_send_data( CAN2,  p_can_msg);
		}
		return error_code;//���۳ɹ���񣬶�Ҫ���������������Ϊ����һ��ֻ�ܴ���һ����Ϣ��ת��
	}  


	//���û�е�������Ϣ��ʱ�䣬��ôת��ʧ�ܡ���ʾ��ǰ����Ҫ���͡�
	error_code = NoData;
	return error_code;
}










