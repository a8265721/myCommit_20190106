#include "can_communication_protocol_VMS_shanghai.h"
#include "control_manager.h"   

//上海强检 can通信协议汇总 
struct Can_Communication_Protocol_VMS_Shanghai_Total    can_communication_protocol_vms_shanghai_total;   


//vms发给fcu的控制命令//初始化
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

//vms发给fcu的控制命令//数据解析
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
	?	1 Byte：FCEPSet（FCE功率设定）低字节
	?	2 Byte：FCEPSet（FCE功率设定）高字节
	?	3 Byte：FCECmdByte（FCE起停命令）
	?		bit5、bit4:FCECommand，待机（00）/正常关机（01）/ 启动（10）/吹扫停机（11）
	?		bit3、bit2：FCE 使能信号（FCEEnable）， 正常（10）/碰撞（01）
	?		bit1、bit0：FCE 急停控制信号（FCEShutdown），取消（10）/急停（01）
		*/

		//由于目前负载不是由fcu来控制，因此这里不能接受输出功率的设定。
		//FCE 使能信号（FCEEnable）， 正常（10）/碰撞（01）。这个系统没有，当上电之后，系统自检就会进入待机状态。然后等待启动命令。
		if( (p_can_msg->can_data[2] & 0x03) == 0x02)
		{
			fcu_data_buffer.galvanic_pile_data_buffer.fcu_stutter_stop_enable = 0;
		}
		else if( (p_can_msg->can_data[2] & 0x03) == 0x01)
		{
			fcu_data_buffer.galvanic_pile_data_buffer.fcu_stutter_stop_enable = 1;
		}
		//启动：开启启动使能。		待机、正常关机和吹扫停机 都是关闭启动使能
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
//vms发给fcu的控制命令//数据封装
enum Error_code VMS_to_FCU_control_msg_encapsulation(struct VMS_to_FCU_control_msg *  p_vms_to_fcu_control_msg, CAN_message * p_can_msg)
{
	return Succeed;
}
//vms发给fcu的控制命令//数据处理
enum Error_code VMS_to_FCU_control_msg_execute(struct VMS_to_FCU_control_msg *  p_vms_to_fcu_control_msg)
{
	return Succeed;
}






//fcu发给vms的状态信息//初始化
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
//fcu发给vms的状态信息//数据解析
enum Error_code FCU_to_VMS_system_status_msg_analysis(CAN_message * p_can_msg, struct FCU_to_VMS_system_status_msg *  p_fcu_to_vms_system_status_msg)
{
	return Succeed;
}
//fcu发给vms的状态信息//数据封装
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

	//数据数据封装
	p_can_msg->can_message_id = p_fcu_to_vms_system_status_msg->Message_id;
	p_can_msg->can_ide = CAN_Id_Standard;//标准帧
	p_can_msg->can_rtr = CAN_RTR_Data;
	p_can_msg->can_len = 8;

	/*
?	1 Byte：FCEPstIs（燃料电池堆电功率）低字节 
?	2 Byte：FCEPstIs（燃料电池堆电功率）高字节 
?	3 Byte：FCEPLmt(当前 FCE 输出功率最大值）低字节		当前输出功率最大值允许值（低字节）
?	4 Byte：FCEPLmt(当前 FCE 输出功率最大值）高字节		当前输出功率最大值允许值（低字节）
?	5 Byte：FCEPParaIs（附属设备消耗功率）低字节
?	6 Byte：FCEPParaIs（附属设备消耗功率）高字节
?	7 Byte：FCEContStatus（FCE 继电器及水箱液位状态）
		FCE 继电器及水箱液位状态：
?		bit3、bit2: 液位正常（10）/液位过低（01）
?		bit1、bit0：断开（01）/接通（10）
?	8 Byte：FCEStatus（燃料电池当前状态码）
		bit 8~6：	100 控制电源接通（PowerUp）
					000 就绪（Ready）
					111 诊断和标定（Diag_Cali）
					101 故障（Error）
					010 使能工作状态（Enabled）
					110 急停开关启动（EmergencyOn）
		bit 5~4：	若基本状态位非101
						00 无故障运行
						01 4级（轻微故障）
						10 3级（一般故障）
					若基本状态位是101
						01 2级（次高级）
						10 1级（最高级）
		bit 3~1：	扩展状态位	保留给零部件使用（详细故障码见页尾附表）
*/
	
	//燃料电池的当前功率
	temp0 = (u32)(fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_voltage * 
		fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_electricity);
	p_can_msg->can_data[0] =  (u8)((temp0/60)); 
	p_can_msg->can_data[1] =  (u8)((temp0/60)>>8);

	//判断输出继电器，只有正常发电之后，才能设置 输出功率最大值允许值
	if(fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_is_enble_output == 1)
	{
		//每次调档之后，都要等2s，才能更新	输出功率最大值允许值 
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
			//注意了，0度以下，是不允许加负载的。
		{
			//低温情况下，缓慢加载，一次1000w。
			if(fcu_data_buffer.water_for_pile_data_buffer.water_temperature_pile_inlet1 < 30)
			{
				p_fcu_to_vms_system_status_msg->power_output_max = temp0 + 1000;
				p_fcu_to_vms_system_status_msg->power_output_max_updata_time = system_time;
			}
			else
			{
				//当前输出功率最大值允许值 = 当前电压 * 高一级档位上限电流和下限电流的平均值
				temp1 = (u32)(fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_voltage * 
					(control_policy_total_manager.fcu_run_data_debug[p_fcu_to_vms_system_status_msg->fcu_output_electricity_level + 1].fcu_output_electricity_lower_limit + 
					control_policy_total_manager.fcu_run_data_debug[p_fcu_to_vms_system_status_msg->fcu_output_electricity_level + 1].fcu_output_electricity_upper_limit) /2 );
				p_fcu_to_vms_system_status_msg->power_output_max = temp1 < 53000 ? temp1 : 53000;
			}
		}
		//否则，维持上一次的不变。

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
	//附属设备消耗功率，目前没有，默认为0
	p_can_msg->can_data[4] = 0;
	p_can_msg->can_data[5] = 0;

	//判断输出继电器，目前没有水箱液位，默认为水位正常。
	if(fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_is_enble_output == 1)
	{
		p_can_msg->can_data[6] = 0xa;
	}
	else
	{
		p_can_msg->can_data[6] = 0x9;
	}


	//判断fcu状态和故障级别
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
			//基本状态位 的 诊断和标定（Diag_Cali）目前没有
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
燃料电池轿车用燃料电池故障表	
故障码Byte8的bit 5~4		故障描述			故障等级								fcu的内部系统故障
0x10						最高级，危险故障	1 级(紧急停机故障)						没有
0x01						次高级，严重故障	2 级(请求停机故障)						1 级（自动停机）		
0x10						次低级，一般故障	3 级(降功率故障)						2 级（自动调整，vms可以辅助降载）
0x01						最低级，轻微故障 	4 级(维持FCE的正常运行，记录故障)		3 级（轻微故障，只是提示作用）	
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
//fcu发给vms的状态信息//数据处理
enum Error_code FCU_to_VMS_system_status_msg_execute(struct FCU_to_VMS_system_status_msg *  p_fcu_to_vms_system_status_msg)
{
	return Succeed;
}






//fcu发给vms的电堆信息//初始化
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
//fcu发给vms的电堆信息//数据解析
enum Error_code FCU_to_VMS_galvanic_pile_msg_analysis(CAN_message * p_can_msg, struct FCU_to_VMS_galvanic_pile_msg *  p_fcu_to_vms_galvanic_pile_msg)
{
	return Succeed;
}
//fcu发给vms的电堆信息//数据封装
enum Error_code FCU_to_VMS_galvanic_pile_msg_encapsulation(struct FCU_to_VMS_galvanic_pile_msg *  p_fcu_to_vms_galvanic_pile_msg, CAN_message * p_can_msg)
{
	enum Error_code error_code = Succeed;
	u16 temp;

	if(p_fcu_to_vms_galvanic_pile_msg == NULL || p_can_msg == NULL)
	{return Pointer_is_null;}

	p_fcu_to_vms_galvanic_pile_msg->updata_event_time = system_time;

	//数据数据封装
	p_can_msg->can_message_id = p_fcu_to_vms_galvanic_pile_msg->Message_id;
	p_can_msg->can_ide = CAN_Id_Standard;//标准帧
	p_can_msg->can_rtr = CAN_RTR_Data;
	p_can_msg->can_len = 8;
	/*
Byte1	FCE 电堆输出电流 低字节
Byte2	FCE 电堆输出电流 高字节
Byte3	FCE 电堆输出电压（低字节）
Byte4	FCE 电堆输出电压（高字节）
Byte5	FCE2CellMax单电池最大电压（低字节）
Byte6	FCE2CellMax单电池最大电压（高字节）
Byte7	FCE2CellMin单电池最小电压（低字节）
Byte8	FCE2CellMin单电池最小电压（高字节）
*/
	temp = (u16)(fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_electricity/0.4);
	p_can_msg->can_data[0] =  (u8)(temp); 
	p_can_msg->can_data[1] =  (u8)(temp>>8);
	temp = (u16)(fcu_data_buffer.galvanic_pile_data_buffer.galvanic_pile_voltage/0.55);
	p_can_msg->can_data[2] =  (u8)(temp); 
	p_can_msg->can_data[3] =  (u8)(temp>>8);
	//巡检发送单片电压的时候，我们这边是2片一检，上海强检要求一片一检。
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
//fcu发给vms的电堆信息//数据处理
enum Error_code FCU_to_VMS_galvanic_pile_msg_execute(struct FCU_to_VMS_galvanic_pile_msg *  p_fcu_to_vms_galvanic_pile_msg)
{
	return Succeed;
}






//fcu发给vms的氢气信息//初始化
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
//fcu发给vms的氢气信息//数据解析
enum Error_code FCU_to_VMS_h2_data_msg_analysis(CAN_message * p_can_msg, struct FCU_to_VMS_h2_data_msg *  p_fcu_to_vms_h2_data_msg)
{
	return Succeed;
}
//fcu发给vms的氢气信息//数据封装
enum Error_code FCU_to_VMS_h2_data_msg_encapsulation(struct FCU_to_VMS_h2_data_msg *  p_fcu_to_vms_h2_data_msg, CAN_message * p_can_msg)
{
	enum Error_code error_code = Succeed;
	u16 temp;

	if(p_fcu_to_vms_h2_data_msg == NULL || p_can_msg == NULL)
	{return Pointer_is_null;}

	p_fcu_to_vms_h2_data_msg->updata_event_time = system_time;

	//数据数据封装
	p_can_msg->can_message_id = p_fcu_to_vms_h2_data_msg->Message_id;
	p_can_msg->can_ide = CAN_Id_Standard;//标准帧
	p_can_msg->can_rtr = CAN_RTR_Data;
	p_can_msg->can_len = 8;
/*
Byte1	FCEoutH2PrsIS氢气出口压力低字节
Byte2	FCEoutH2PrsIS氢气出口压力高字节
Byte3	FCEoutH2PrsIS氢气进堆压力低字节
Byte4	FCEoutH2PrsIS氢气进堆压力高字节
Byte5	氢气出口温度低字节
Byte6	氢气出口温度高字节
Byte7	氢气进堆温度低字节
Byte8	氢气进堆温度高字节
*/
	
	temp = (u16)(fcu_data_buffer.h2_data_buffer.h2_pressure_tail_outlet);
	p_can_msg->can_data[0] =  (u8)(temp); 
	p_can_msg->can_data[1] =  (u8)(temp>>8);
	temp = (u16)(fcu_data_buffer.h2_data_buffer.h2_pressure_pile_inlet);
	p_can_msg->can_data[2] =  (u8)(temp); 
	p_can_msg->can_data[3] =  (u8)(temp>>8);
	//氢气管路没有安装温度传感器，因此没有温度数据，这里默认为0
	p_can_msg->can_data[4] = 0;
	p_can_msg->can_data[5] = 0;
	p_can_msg->can_data[6] = 0;
	p_can_msg->can_data[7] = 0;

	p_can_msg->can_priorty = 0;
	return error_code;                                       
}
//fcu发给vms的氢气信息//数据处理
enum Error_code FCU_to_VMS_h2_data_msg_execute(struct FCU_to_VMS_h2_data_msg *  p_fcu_to_vms_h2_data_msg)
{
	return Succeed;
}







//fcu发给vms的空气信息//初始化
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
//fcu发给vms的空气信息//数据解析
enum Error_code FCU_to_VMS_air_data_msg_analysis(CAN_message * p_can_msg, struct FCU_to_VMS_air_data_msg *  p_fcu_to_vms_air_data_msg)
{
	return Succeed;
}
//fcu发给vms的空气信息//数据封装
enum Error_code FCU_to_VMS_air_data_msg_encapsulation(struct FCU_to_VMS_air_data_msg *  p_fcu_to_vms_air_data_msg, CAN_message * p_can_msg)
{
	enum Error_code error_code = Succeed;
	u16 temp;

	if(p_fcu_to_vms_air_data_msg == NULL || p_can_msg == NULL)
	{return Pointer_is_null;}

	p_fcu_to_vms_air_data_msg->updata_event_time = system_time;

	//数据数据封装
	p_can_msg->can_message_id = p_fcu_to_vms_air_data_msg->Message_id;
	p_can_msg->can_ide = CAN_Id_Standard;//标准帧
	p_can_msg->can_rtr = CAN_RTR_Data;
	p_can_msg->can_len = 8;
/*
Byte1	空气出口压力低字节          
Byte2	空气出口压力高字节
Byte3	空气进堆压力低字节
Byte4	空气进堆压力高字节
Byte5	空气出口温度低字节
Byte6	空气出口温度高字节
Byte7	空气进堆温度低字节
Byte8	空气进堆温度高字节
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
//fcu发给vms的空气信息//数据处理
enum Error_code FCU_to_VMS_air_data_msg_execute(struct FCU_to_VMS_air_data_msg *  p_fcu_to_vms_air_data_msg)
{
	return Succeed;
}






//fcu发给vms的电堆水路信息//初始化
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
//fcu发给vms的电堆水路信息//数据解析
enum Error_code FCU_to_VMS_water_for_pile_data_msg_analysis(CAN_message * p_can_msg, struct FCU_to_VMS_water_for_pile_data_msg *  p_fcu_to_vms_water_for_pile_data_msg)
{
	return Succeed;
}
//fcu发给vms的电堆水路信息//数据封装
enum Error_code FCU_to_VMS_water_for_pile_data_msg_encapsulation(struct FCU_to_VMS_water_for_pile_data_msg *  p_fcu_to_vms_water_for_pile_data_msg, CAN_message * p_can_msg)
{
	enum Error_code error_code = Succeed;
	u16 temp;

	if(p_fcu_to_vms_water_for_pile_data_msg == NULL || p_can_msg == NULL)
	{return Pointer_is_null;}

	p_fcu_to_vms_water_for_pile_data_msg->updata_event_time = system_time;

	//数据数据封装
	p_can_msg->can_message_id = p_fcu_to_vms_water_for_pile_data_msg->Message_id;
	p_can_msg->can_ide = CAN_Id_Standard;//标准帧
	p_can_msg->can_rtr = CAN_RTR_Data;
	p_can_msg->can_len = 8;
/*
Byte1	FCECoInPrsIs(FCE 冷却水进口压力）低字节
Byte2	FCECoInPrsIs(FCE 冷却水进口压力）高字节
Byte3	FCECoOutTemIs(FCE 冷却水出口温度)低字节
Byte4	FCECoOutTemIs(FCE 冷却水出口温度)高字节
Byte5	FCECoInTemIs(FCE 冷却水进口温度）低字节
Byte6	FCECoInTemIs(FCE 冷却水进口温度）高字节

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
//fcu发给vms的电堆水路信息//数据处理
enum Error_code FCU_to_VMS_water_for_pile_data_msg_execute(struct FCU_to_VMS_water_for_pile_data_msg *  p_fcu_to_vms_water_for_pile_data_msg)
{
	return Succeed;
}





//上海强检 can通信协议汇总 初始化
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

//上海强检 把所有数据的时间清零
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

//上海强检 通过接受的CAN消息，来更新数据。
enum Error_code Can_communication_protocol_vms_shanghai_updata_receivev_can(struct Can_Communication_Protocol_VMS_Shanghai_Total * p_can_communication_protocol_vms_shanghai_total, CAN_message * p_can_msg)
{
	enum Error_code error_code = Succeed;

	if(p_can_communication_protocol_vms_shanghai_total == NULL || p_can_msg == NULL)
	{return Pointer_is_null;}

	if(p_can_msg->can_rtr == CAN_RTR_Data)
	{	
		//扩展帧
		if(p_can_msg->can_ide == CAN_Id_Extended)
		{
			switch(p_can_msg->can_message_id)
			{

			default:
				break;
			}
		}
		//标准帧
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


//上海强检 定时封装can数据
//如果没有需要发送的消息，返回错误
//注：一次只能转化一条发送消息。如果有多条，请循环调用本函数。直到本函数返回错误
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
		return error_code;//无论成功与否，都要结束这个函数，因为函数一次只能处理一条消息的转换
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
		return error_code;//无论成功与否，都要结束这个函数，因为函数一次只能处理一条消息的转换
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
		return error_code;//无论成功与否，都要结束这个函数，因为函数一次只能处理一条消息的转换
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
		return error_code;//无论成功与否，都要结束这个函数，因为函数一次只能处理一条消息的转换
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
		return error_code;//无论成功与否，都要结束这个函数，因为函数一次只能处理一条消息的转换
	}  


	//如果没有到发送消息的时间，那么转化失败。表示当前不需要发送。
	error_code = NoData;
	return error_code;
}










