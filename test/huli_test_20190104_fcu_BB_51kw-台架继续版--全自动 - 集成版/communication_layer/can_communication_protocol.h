#ifndef __CAN_COMMUNICATION_PROTOCOL_H
#define __CAN_COMMUNICATION_PROTOCOL_H


#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

#include "ect.h"
#include "error_system.h"
#include "custom_math.h"
#include "pid.h"                    
#include "data_buff.h"
#include "can.h"
/*
typedef enum Can_Channels
{
	CAN0 = 0,
	CAN1 = 1,
	CAN2 = 2,
	CAN3 = 3,
}Can_Channels;

//CAN_OVERTIME_MAX: 5000ms
#define CAN_OVERTIME_MAX 5000

//CAN_SEND_MESSAGE_TIME_MAX : 
#define CAN_SEND_MESSAGE_TIME_MAX_5         5

//CAN_SEND_MESSAGE_TIME_MAX : 
#define CAN_SEND_MESSAGE_TIME_MAX_100       100
*/
#define TEMPERATURE_DATA_ACQUISITION_MESSAGE_ID					0x1801D0CC//�¶Ȳɼ�����
#define PRESSURE_DATA1_ACQUISITION_MESSAGE_ID					0x1802D0CC//ѹ���ɼ�����1
#define PRESSURE_DATA2_ACQUISITION_MESSAGE_ID					0x1803D0CC//ѹ���ɼ�����2
#define PRESSURE_DATA3_ACQUISITION_MESSAGE_ID					0x1804D0CC//ѹ���ɼ�����3
#define DIGITAL_QUANTITY_INPUT_MESSAGE_ID						0x1805D0CC//����������

#define DIGITAL_QUANTITY_OUTPUT_MESSAGE_ID						0x1801BCD0//���������
#define PWM_OUTPUT_MESSAGE_ID									0x1802BCD0//PWM���


//�¶Ȳɼ�����
typedef struct Temperature_Data_Acquisition
{
	u32		updata_event_time;	//���ݸ��µ�ʱ��
	u32		overtime_max;		//��ʱ��ʱ�䣨��ǰϵͳʱ�� ��ȥ ��һ�����ݸ��µ�ʱ�� ���� ��ʱʱ�䣬��Ϊ��ʱ��ͨѶ�жϣ�
	u32		Message_id;			//CAN��Ϣid��ID:0x1801D0BC��

	u8		DCDC_heartbeat_frame;		//����֡	ÿ�μ�1	
}Temperature_Data_Acquisition;

//�¶Ȳɼ�����//��ʼ��
enum Error_code temperature_data_acquisition_init(struct Temperature_Data_Acquisition *  p_temperature_data_acquisition);
//�¶Ȳɼ�����//���ݽ���
enum Error_code temperature_data_acquisition_analysis(CAN_message * p_can_msg, struct Temperature_Data_Acquisition *  p_temperature_data_acquisition);
//�¶Ȳɼ�����//���ݷ�װ
enum Error_code temperature_data_acquisition_encapsulation(struct Temperature_Data_Acquisition *  p_temperature_data_acquisition, CAN_message * p_can_msg);
//�¶Ȳɼ�����//���ݴ���
enum Error_code temperature_data_acquisition_execute(struct Temperature_Data_Acquisition *  p_temperature_data_acquisition);






//ѹ���ɼ�����1
typedef struct Pressure_Data1_Acquisition
{
	u32		updata_event_time;	//���ݸ��µ�ʱ��
	u32		overtime_max;		//��ʱ��ʱ�䣨��ǰϵͳʱ�� ��ȥ ��һ�����ݸ��µ�ʱ�� ���� ��ʱʱ�䣬��Ϊ��ʱ��ͨѶ�жϣ�
	u32		Message_id;			//CAN��Ϣid��ID:0x1802D0BC��
}Pressure_Data1_Acquisition;

//ѹ���ɼ�����1//��ʼ��
enum Error_code pressure_data1_acquisition_init(struct Pressure_Data1_Acquisition *  p_pressure_data1_acquisition);
//ѹ���ɼ�����1//���ݽ���
enum Error_code pressure_data1_acquisition_analysis(CAN_message * p_can_msg, struct Pressure_Data1_Acquisition *  p_pressure_data1_acquisition);
//ѹ���ɼ�����1//���ݷ�װ
enum Error_code pressure_data1_acquisition_encapsulation(struct Pressure_Data1_Acquisition *  p_pressure_data1_acquisition, CAN_message * p_can_msg);
//ѹ���ɼ�����1//���ݴ���
enum Error_code pressure_data1_acquisition_execute(struct Pressure_Data1_Acquisition *  p_pressure_data1_acquisition);







//ѹ���ɼ�����2
typedef struct Pressure_Data2_Acquisition
{
	u32		updata_event_time;	//���ݸ��µ�ʱ��
	u32		overtime_max;		//��ʱ��ʱ�䣨��ǰϵͳʱ�� ��ȥ ��һ�����ݸ��µ�ʱ�� ���� ��ʱʱ�䣬��Ϊ��ʱ��ͨѶ�жϣ�
	u32		Message_id;			//CAN��Ϣid��ID:0x1803D0BC��
}Pressure_Data2_Acquisition;

//ѹ���ɼ�����2//��ʼ��
enum Error_code pressure_data2_acquisition_init(struct Pressure_Data2_Acquisition *  p_pressure_data2_acquisition);
//ѹ���ɼ�����2//���ݽ���
enum Error_code pressure_data2_acquisition_analysis(CAN_message * p_can_msg, struct Pressure_Data2_Acquisition *  p_pressure_data2_acquisition);
//ѹ���ɼ�����2//���ݷ�װ
enum Error_code pressure_data2_acquisition_encapsulation(struct Pressure_Data2_Acquisition *  p_pressure_data2_acquisition, CAN_message * p_can_msg);
//ѹ���ɼ�����2//���ݴ���
enum Error_code pressure_data2_acquisition_execute(struct Pressure_Data2_Acquisition *  p_pressure_data2_acquisition);






//ѹ���ɼ�����3
typedef struct Pressure_Data3_Acquisition
{
	u32		updata_event_time;	//���ݸ��µ�ʱ��
	u32		overtime_max;		//��ʱ��ʱ�䣨��ǰϵͳʱ�� ��ȥ ��һ�����ݸ��µ�ʱ�� ���� ��ʱʱ�䣬��Ϊ��ʱ��ͨѶ�жϣ�
	u32		Message_id;			//CAN��Ϣid��ID:0x1804D0BC��
}Pressure_Data3_Acquisition;

//ѹ���ɼ�����3//��ʼ��
enum Error_code pressure_data3_acquisition_init(struct Pressure_Data3_Acquisition *  p_pressure_data3_acquisition);
//ѹ���ɼ�����3//���ݽ���
enum Error_code pressure_data3_acquisition_analysis(CAN_message * p_can_msg, struct Pressure_Data3_Acquisition *  p_pressure_data3_acquisition);
//ѹ���ɼ�����3//���ݷ�װ
enum Error_code pressure_data3_acquisition_encapsulation(struct Pressure_Data3_Acquisition *  p_pressure_data3_acquisition, CAN_message * p_can_msg);
//ѹ���ɼ�����3//���ݴ���
enum Error_code pressure_data3_acquisition_execute(struct Pressure_Data3_Acquisition *  p_pressure_data3_acquisition);






//����������
typedef struct Digital_Quantity_Input
{
	u32		updata_event_time;	//���ݸ��µ�ʱ��
	u32		overtime_max;		//��ʱ��ʱ�䣨��ǰϵͳʱ�� ��ȥ ��һ�����ݸ��µ�ʱ�� ���� ��ʱʱ�䣬��Ϊ��ʱ��ͨѶ�жϣ�
	u32		Message_id;			//CAN��Ϣid��ID:0x1801D0BC��
}Digital_Quantity_Input;

//����������//��ʼ��
enum Error_code digital_quantity_input_init(struct Digital_Quantity_Input *  p_digital_quantity_input);
//����������//���ݽ���
enum Error_code digital_quantity_input_analysis(CAN_message * p_can_msg, struct Digital_Quantity_Input *  p_digital_quantity_input);
//����������//���ݷ�װ
enum Error_code digital_quantity_input_encapsulation(struct Digital_Quantity_Input *  p_digital_quantity_input, CAN_message * p_can_msg);
//����������//���ݴ���
enum Error_code digital_quantity_input_execute(struct Digital_Quantity_Input *  p_digital_quantity_input);








//���������
typedef struct Digital_Quantity_Output
{
	u32		updata_event_time;	//���ݸ��µ�ʱ��
	u32		send_message_time_max;		//��ʱ��ʱ�䣨��ǰϵͳʱ�� ��ȥ ��һ�����ݸ��µ�ʱ�� ���� ��ʱʱ�䣬��Ϊ��ʱ��ͨѶ�жϣ�
	u32		Message_id;			//CAN��Ϣid��ID:0x1801BCD0��
}Digital_Quantity_Output;

//���������//��ʼ��
enum Error_code digital_quantity_output_init(struct Digital_Quantity_Output *  p_digital_quantity_output);
//���������//���ݽ���
enum Error_code digital_quantity_output_analysis(CAN_message * p_can_msg, struct Digital_Quantity_Output *  p_digital_quantity_output);
//���������//���ݷ�װ
enum Error_code digital_quantity_output_encapsulation(struct Digital_Quantity_Output *  p_digital_quantity_output, CAN_message * p_can_msg);
//���������//���ݴ���
enum Error_code digital_quantity_output_execute(struct Digital_Quantity_Output *  p_digital_quantity_output);





//PWM���
typedef struct Pwm_Output
{
	u32		updata_event_time;	//���ݸ��µ�ʱ��
	u32		send_message_time_max;		//��ʱ��ʱ�䣨��ǰϵͳʱ�� ��ȥ ��һ�����ݸ��µ�ʱ�� ���� ��ʱʱ�䣬��Ϊ��ʱ��ͨѶ�жϣ�
	u32		Message_id;			//CAN��Ϣid��ID:0x1802BCD0��
}Pwm_Output;

//PWM���//��ʼ��
enum Error_code pwm_output_init(struct Pwm_Output *  p_pwm_output);
//PWM���//���ݽ���
enum Error_code pwm_output_analysis(CAN_message * p_can_msg, struct Pwm_Output *  p_pwm_output);
//PWM���//���ݷ�װ
enum Error_code pwm_output_encapsulation(struct Pwm_Output *  p_pwm_output, CAN_message * p_can_msg);
//PWM���//���ݴ���
enum Error_code pwm_output_execute(struct Pwm_Output *  p_pwm_output);







//canͨ��Э�����
typedef struct Can_Communication_Protocol_Total
{
	struct Temperature_Data_Acquisition			temperature_data_acquisition;
	struct Pressure_Data1_Acquisition			pressure_data1_acquisition;
	struct Pressure_Data2_Acquisition			pressure_data2_acquisition;
	struct Pressure_Data3_Acquisition			pressure_data3_acquisition;
	struct Digital_Quantity_Input				digital_quantity_input;		

	struct Digital_Quantity_Output				digital_quantity_output;
	struct Pwm_Output							pwm_output;
}Can_Communication_Protocol_Total;

//canͨ��Э�����       
extern struct Can_Communication_Protocol_Total    can_communication_protocol_total;                                     

//canͨ��Э����� ��ʼ��
enum Error_code Can_communication_protocol_init(struct Can_Communication_Protocol_Total * p_can_communication_protocol_total);

//���������ݵ�ʱ������
enum Error_code Can_communication_protocol_clear_time(struct Can_Communication_Protocol_Total * p_can_communication_protocol_total);


//ͨ�����ܵ�CAN��Ϣ�����������ݡ�
enum Error_code Can_communication_protocol_updata_receivev_can(struct Can_Communication_Protocol_Total * p_can_communication_protocol_total, CAN_message * p_can_msg);


//��ʱ��װcan����
//���û����Ҫ���͵���Ϣ�����ش���
//ע��һ��ֻ��ת��һ��������Ϣ������ж�������ѭ�����ñ�������ֱ�����������ش���
enum Error_code Can_communication_protocol_can_encapsulation_and_send(struct Can_Communication_Protocol_Total * p_can_communication_protocol_total, CAN_message * p_can_msg);

/*
//��ʱ����can���ݣ�Ĭ��can0��
enum Error_code Control_Policy_ontime_can_send_data(enum Can_Channels CANx, CAN_message * p_can_msg);
*/













#endif


