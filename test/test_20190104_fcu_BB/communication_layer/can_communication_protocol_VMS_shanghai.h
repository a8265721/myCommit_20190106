/*
can_communication_protocol_VMS_shanghai ��ģ��������Ϻ�ǿ���������һ��canͨ��Э��
��VMS��FCU����ͨ�ţ�500kbit/s�Ĳ����ʣ�can id��11λ�ı�׼֡��
ͨ��Э�����Ϻ�ǿ��������ƶ����������ء�

�÷�������ģ��ֱ�Ӱ�����ģ�飬Ȼ����Ϊ�����ķ���ֵ��
�ϲ�ͨ���������������жϺ�����ִ�������
*/ 
//-----------------------------------------------------------------------------------------------

#ifndef __CAN_COMMUNICATION_PROTOCOL_VMS_SHANGHAI_H             
#define __CAN_COMMUNICATION_PROTOCOL_VMS_SHANGHAI_H

#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

#include "ect.h"
#include "error_system.h"
//#include "custom_math.h"
#include "pit.h"
#include "data_buff.h"
#include "can.h"

//vms��ָ������������ǿ���ʱ�����Ϻ�ǿ�������ģ��

#define VMS_TO_FCU_CONTROL_MSG_ID					    0x303//vms����fcu�Ŀ�������
#define FCU_TO_VMS_SYSTEM_STATUS_MSG_ID					0x313//fcu����vms��״̬��Ϣ
#define FCU_TO_VMS_GALVANIC_PILE_MSG_ID					0x314//fcu����vms�ĵ����Ϣ
#define FCU_TO_VMS_H2_DATA_MSG_ID						0x316//fcu����vms��������Ϣ
#define FCU_TO_VMS_AIR_DATA_MSG_ID						0x317//fcu����vms�Ŀ�����Ϣ
#define FCU_TO_VMS_WATER_FOR_PILE_DATA_MSG_ID			0x318//fcu����vms�ĵ��ˮ·��Ϣ





//һ��vms����fcu�Ŀ�������
typedef struct VMS_to_FCU_control_msg
{
	u32		updata_event_time;	//���ݸ��µ�ʱ��
	u32		overtime_max;		//��ʱ��ʱ�䣨��ǰϵͳʱ�� ��ȥ ��һ�����ݸ��µ�ʱ�� ���� ��ʱʱ�䣬��Ϊ��ʱ��ͨѶ�жϣ�
	u32		Message_id;			//CAN��Ϣid��ID:0x303��
}VMS_to_FCU_control_msg;

//vms����fcu�Ŀ�������//��ʼ��
enum Error_code VMS_to_FCU_control_msg_init(struct VMS_to_FCU_control_msg *  p_vms_to_fcu_control_msg);
//vms����fcu�Ŀ�������//���ݽ���
enum Error_code VMS_to_FCU_control_msg_analysis(CAN_message * p_can_msg, struct VMS_to_FCU_control_msg *  p_vms_to_fcu_control_msg);
//vms����fcu�Ŀ�������//���ݷ�װ
enum Error_code VMS_to_FCU_control_msg_encapsulation(struct VMS_to_FCU_control_msg *  p_vms_to_fcu_control_msg, CAN_message * p_can_msg);
//vms����fcu�Ŀ�������//���ݴ���
enum Error_code VMS_to_FCU_control_msg_execute(struct VMS_to_FCU_control_msg *  p_vms_to_fcu_control_msg);




//����fcu����vms��״̬��Ϣ
typedef struct FCU_to_VMS_system_status_msg
{
	u32		updata_event_time;	//���ݸ��µ�ʱ��
	u32		send_message_time_max;		//��ʱ��ʱ�䣨��ǰϵͳʱ�� ��ȥ ��һ�����ݸ��µ�ʱ�� ���� ��ʱʱ�䣬��Ϊ��ʱ��ͨѶ�жϣ�
	u32		Message_id;			//CAN��Ϣid��ID:0x313��

	u32		power_output_max;			//��ǰ����������ֵ����ֵ
	u32		power_output_max_updata_time;//ϵͳ���� ��ǰ����������ֵ����ֵ  �ĸ��µ�ʱ�䡣������ֹ���µ�̫�졣Ŀǰ����1s��
	int		fcu_output_electricity_level;		//fcu��������ĵȼ�

}FCU_to_VMS_system_status_msg;

//fcu����vms��״̬��Ϣ//��ʼ��
enum Error_code FCU_to_VMS_system_status_msg_init(struct FCU_to_VMS_system_status_msg *  p_fcu_to_vms_system_status_msg);
//fcu����vms��״̬��Ϣ//���ݽ���
enum Error_code FCU_to_VMS_system_status_msg_analysis(CAN_message * p_can_msg, struct FCU_to_VMS_system_status_msg *  p_fcu_to_vms_system_status_msg);
//fcu����vms��״̬��Ϣ//���ݷ�װ
enum Error_code FCU_to_VMS_system_status_msg_encapsulation(struct FCU_to_VMS_system_status_msg *  p_fcu_to_vms_system_status_msg, CAN_message * p_can_msg);
//fcu����vms��״̬��Ϣ//���ݴ���
enum Error_code FCU_to_VMS_system_status_msg_execute(struct FCU_to_VMS_system_status_msg *  p_fcu_to_vms_system_status_msg);




//����fcu����vms�ĵ����Ϣ
typedef struct FCU_to_VMS_galvanic_pile_msg
{
	u32		updata_event_time;	//���ݸ��µ�ʱ��
	u32		send_message_time_max;		//��ʱ��ʱ�䣨��ǰϵͳʱ�� ��ȥ ��һ�����ݸ��µ�ʱ�� ���� ��ʱʱ�䣬��Ϊ��ʱ��ͨѶ�жϣ�
	u32		Message_id;			//CAN��Ϣid��ID:0x314��

}FCU_to_VMS_galvanic_pile_msg;

//fcu����vms�ĵ����Ϣ//��ʼ��
enum Error_code FCU_to_VMS_galvanic_pile_msg_init(struct FCU_to_VMS_galvanic_pile_msg *  p_fcu_to_vms_galvanic_pile_msg);
//fcu����vms�ĵ����Ϣ//���ݽ���
enum Error_code FCU_to_VMS_galvanic_pile_msg_analysis(CAN_message * p_can_msg, struct FCU_to_VMS_galvanic_pile_msg *  p_fcu_to_vms_galvanic_pile_msg);
//fcu����vms�ĵ����Ϣ//���ݷ�װ
enum Error_code FCU_to_VMS_galvanic_pile_msg_encapsulation(struct FCU_to_VMS_galvanic_pile_msg *  p_fcu_to_vms_galvanic_pile_msg, CAN_message * p_can_msg);
//fcu����vms�ĵ����Ϣ//���ݴ���
enum Error_code FCU_to_VMS_galvanic_pile_msg_execute(struct FCU_to_VMS_galvanic_pile_msg *  p_fcu_to_vms_galvanic_pile_msg);





//�ġ�fcu����vms��������Ϣ
typedef struct FCU_to_VMS_h2_data_msg
{
	u32		updata_event_time;	//���ݸ��µ�ʱ��
	u32		send_message_time_max;		//��ʱ��ʱ�䣨��ǰϵͳʱ�� ��ȥ ��һ�����ݸ��µ�ʱ�� ���� ��ʱʱ�䣬��Ϊ��ʱ��ͨѶ�жϣ�
	u32		Message_id;			//CAN��Ϣid��ID:0x316��

}FCU_to_VMS_h2_data_msg;

//fcu����vms��������Ϣ//��ʼ��
enum Error_code FCU_to_VMS_h2_data_msg_init(struct FCU_to_VMS_h2_data_msg *  p_fcu_to_vms_h2_data_msg);
//fcu����vms��������Ϣ//���ݽ���
enum Error_code FCU_to_VMS_h2_data_msg_analysis(CAN_message * p_can_msg, struct FCU_to_VMS_h2_data_msg *  p_fcu_to_vms_h2_data_msg);
//fcu����vms��������Ϣ//���ݷ�װ
enum Error_code FCU_to_VMS_h2_data_msg_encapsulation(struct FCU_to_VMS_h2_data_msg *  p_fcu_to_vms_h2_data_msg, CAN_message * p_can_msg);
//fcu����vms��������Ϣ//���ݴ���
enum Error_code FCU_to_VMS_h2_data_msg_execute(struct FCU_to_VMS_h2_data_msg *  p_fcu_to_vms_h2_data_msg);






//�塢fcu����vms�Ŀ�����Ϣ
typedef struct FCU_to_VMS_air_data_msg
{
	u32		updata_event_time;	//���ݸ��µ�ʱ��
	u32		send_message_time_max;		//��ʱ��ʱ�䣨��ǰϵͳʱ�� ��ȥ ��һ�����ݸ��µ�ʱ�� ���� ��ʱʱ�䣬��Ϊ��ʱ��ͨѶ�жϣ�
	u32		Message_id;			//CAN��Ϣid��ID:0x317��

}FCU_to_VMS_air_data_msg;

//fcu����vms�Ŀ�����Ϣ//��ʼ��
enum Error_code FCU_to_VMS_air_data_msg_init(struct FCU_to_VMS_air_data_msg *  p_fcu_to_vms_air_data_msg);
//fcu����vms�Ŀ�����Ϣ//���ݽ���
enum Error_code FCU_to_VMS_air_data_msg_analysis(CAN_message * p_can_msg, struct FCU_to_VMS_air_data_msg *  p_fcu_to_vms_air_data_msg);
//fcu����vms�Ŀ�����Ϣ//���ݷ�װ
enum Error_code FCU_to_VMS_air_data_msg_encapsulation(struct FCU_to_VMS_air_data_msg *  p_fcu_to_vms_air_data_msg, CAN_message * p_can_msg);
//fcu����vms�Ŀ�����Ϣ//���ݴ���
enum Error_code FCU_to_VMS_air_data_msg_execute(struct FCU_to_VMS_air_data_msg *  p_fcu_to_vms_air_data_msg);






//����fcu����vms�ĵ��ˮ·��Ϣ
typedef struct FCU_to_VMS_water_for_pile_data_msg
{
	u32		updata_event_time;	//���ݸ��µ�ʱ��
	u32		send_message_time_max;		//��ʱ��ʱ�䣨��ǰϵͳʱ�� ��ȥ ��һ�����ݸ��µ�ʱ�� ���� ��ʱʱ�䣬��Ϊ��ʱ��ͨѶ�жϣ�
	u32		Message_id;			//CAN��Ϣid��ID:0x318��

}FCU_to_VMS_water_for_pile_data_msg;

//fcu����vms�ĵ��ˮ·��Ϣ//��ʼ��
enum Error_code FCU_to_VMS_water_for_pile_data_msg_init(struct FCU_to_VMS_water_for_pile_data_msg *  p_fcu_to_vms_water_for_pile_data_msg);
//fcu����vms�ĵ��ˮ·��Ϣ//���ݽ���
enum Error_code FCU_to_VMS_water_for_pile_data_msg_analysis(CAN_message * p_can_msg, struct FCU_to_VMS_water_for_pile_data_msg *  p_fcu_to_vms_water_for_pile_data_msg);
//fcu����vms�ĵ��ˮ·��Ϣ//���ݷ�װ
enum Error_code FCU_to_VMS_water_for_pile_data_msg_encapsulation(struct FCU_to_VMS_water_for_pile_data_msg *  p_fcu_to_vms_water_for_pile_data_msg, CAN_message * p_can_msg);
//fcu����vms�ĵ��ˮ·��Ϣ//���ݴ���
enum Error_code FCU_to_VMS_water_for_pile_data_msg_execute(struct FCU_to_VMS_water_for_pile_data_msg *  p_fcu_to_vms_water_for_pile_data_msg);




//�Ϻ�ǿ�� canͨ��Э�����
typedef struct Can_Communication_Protocol_VMS_Shanghai_Total
{
	struct VMS_to_FCU_control_msg					vms_to_fcu_control_msg;
	struct FCU_to_VMS_system_status_msg				fcu_to_vms_system_status_msg;
	struct FCU_to_VMS_galvanic_pile_msg				fcu_to_vms_galvanic_pile_msg;
	struct FCU_to_VMS_h2_data_msg					fcu_to_vms_h2_data_msg;
	struct FCU_to_VMS_air_data_msg					fcu_to_vms_air_data_msg;
	struct FCU_to_VMS_water_for_pile_data_msg		fcu_to_vms_water_for_pile_data_msg;

}Can_Communication_Protocol_VMS_Shanghai_Total;

//�Ϻ�ǿ�� canͨ��Э�����       
extern struct Can_Communication_Protocol_VMS_Shanghai_Total    can_communication_protocol_vms_shanghai_total;                                     

//�Ϻ�ǿ�� canͨ��Э����� ��ʼ��
enum Error_code Can_communication_protocol_vms_shanghai_init(struct Can_Communication_Protocol_VMS_Shanghai_Total * p_can_communication_protocol_vms_shanghai_total);

//�Ϻ�ǿ�� ���������ݵ�ʱ������
enum Error_code Can_communication_protocol_vms_shanghai_clear_time(struct Can_Communication_Protocol_VMS_Shanghai_Total * p_can_communication_protocol_vms_shanghai_total);


//�Ϻ�ǿ�� ͨ�����ܵ�CAN��Ϣ�����������ݡ�
enum Error_code Can_communication_protocol_vms_shanghai_updata_receivev_can(struct Can_Communication_Protocol_VMS_Shanghai_Total * p_can_communication_protocol_vms_shanghai_total, CAN_message * p_can_msg);


//�Ϻ�ǿ�� ��ʱ��װcan����
//���û����Ҫ���͵���Ϣ�����ش���
//ע��һ��ֻ��ת��һ��������Ϣ������ж�������ѭ�����ñ�������ֱ�����������ش���
enum Error_code Can_communication_protocol_vms_shanghai_can_encapsulation_and_send(struct Can_Communication_Protocol_VMS_Shanghai_Total * p_can_communication_protocol_vms_shanghai_total, CAN_message * p_can_msg);






#endif
