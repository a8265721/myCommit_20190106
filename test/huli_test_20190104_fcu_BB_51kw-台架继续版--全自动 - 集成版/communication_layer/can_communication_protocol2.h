#ifndef __CAN_COMMUNICATION_PROTOCOL2_H             
#define __CAN_COMMUNICATION_PROTOCOL2_H
                                                              

#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

#include "ect.h"
#include "error_system.h"
//#include "custom_math.h"
#include "pit.h"
#include "data_buff.h"
#include "can.h"
//#include "can_communication_protocol.h"




//Ѳ��嵥Ƭ��ѹ  ��Ϣ������  21
#define ITINERANT_DETECTIVE_CAN_MESSAGE_NUMBER			21

//Ѳ��嵥Ƭ��ѹ  ��Ƭ������  82
#define ITINERANT_DETECTIVE_SINGLE_VOLTAGE_NUMBER		82




#define AIR_COMPRESSOR_CONTROL_MSG_ID					    0x0CFF02A7//��ѹ��������ϢID
#define AIR_COMPRESSOR_STATS_MSG2_ID				    	0x1812A7B2//��ѹ��״̬��ϢID
#define AIR_COMPRESSOR_ALARM_MSG3                           0x1811A7B2//��ѹ��������ϢID

#define H2_PUMP_CONTROL_MSG_ID                              0x0CFFA63D //����ѭ���ÿ���ID
#define H2_CIRCULATING_PUMP_DATA_ID                         0x0CFFA7B4 //����ѭ����������ϢID
#define H2_CIRCULATING_PUMP_PARAMETER_VALUES_ID             0x0CFFA83D   
#define H2_CIRCULATING_PUMP_ACKNOWLEDGMENT                  0x18FFABB4

#define ITINERANT_DETECTIVE_SINGLE_VOLTAGE_ACTUAL_DATA      0x1880BCBA   //ʵ�ʵ�ѹֵID
#define ITINERANT_DETECTIVE_OPERATE_STATAS                  0x1801BCBA     //�������״̬
#define ITINERANT_DETECTIVE_SINGLE_CHIP_HIGHEST_VOLTAGE     0x1802BCBA  //�����ߵ�Ƭ��ѹ
#define ITINERANT_DETECTIVE_SINGLE_CHIP_MINIMUM_VOLTAGE     0x1803BCBA  //�����͵�Ƭ��ѹ
#define ITINERANT_DETECTIVE_SINGLE_VOLTAGE_SUM              0x18D4D0BA      //�ܵ�ѹID

#define ITINERANT_DETECTIVE_SINGLE_VOLTAGE_ACTUAL_DATA2     0x1820BCBA   //ʵ�ʵ�ѹֵID
#define ITINERANT_DETECTIVE_OPERATE_STATAS2                 0x1811BCBA     //�������״̬
#define ITINERANT_DETECTIVE_SINGLE_CHIP_HIGHEST_VOLTAGE2    0x1812BCBA  //�����ߵ�Ƭ��ѹ
#define ITINERANT_DETECTIVE_SINGLE_CHIP_MINIMUM_VOLTAGE2    0x1813BCBA  //�����͵�Ƭ��ѹ
#define ITINERANT_DETECTIVE_SINGLE_VOLTAGE_SUM2             0x1814D0BA      //�ܵ�ѹID

#define INSULATION_MONITOR_DATA_ID                          0x1801D0D7  //��Ե���������


//ad�ɼ� �������can��Ϣid
#define AD_AUXILIARY_BOARD_MESSAGE_ID                       0x12340001  //��һ��Ϊ0x12340001  ��������ε���

//ad�ɼ� ������    can��Ϣ������  Ĭ��Ϊ6
#define AD_AUXILIARY_BOARD_MESSAGE_NUMBER_MAX           6

/*
//ad�ɼ� ������    ת��ͨ�����������ֵ�� ��24��ad
#define AD_AUXILIARY_BOARD_CONVERSION_NUMBER_MAX		24
//ad�ɼ� ������    �ɼ���ƽ��ֵ
extern u16 ad_auxiliary_board_mean_data[AD_AUXILIARY_BOARD_CONVERSION_NUMBER_MAX];
  */



//1.1��ѹ��������Ϣ
typedef struct Air_compressor_Control_Msg
{
	u32		updata_event_time;	//���ݸ��µ�ʱ��
	u32		send_message_time_max;		//��ʱ��ʱ�䣨��ǰϵͳʱ�� ��ȥ ��һ�����ݸ��µ�ʱ�� ���� ��ʱʱ�䣬��Ϊ��ʱ��ͨѶ�жϣ�
	u32		Message_id;			//CAN��Ϣid��ID:0x0CFF02A7��
	u8    CompressorStart;     //��ѹ������
	u32   SpeedSetpoint;       //��ѹ���趨ת��

	//	u8		DCDC_heartbeat_frame;		//����֡	ÿ�μ�1	
}Air_compressor_Control_Msg;

//��ѹ��������Ϣ//��ʼ��
enum Error_code Air_compressor_Control_Msg_init(struct Air_compressor_Control_Msg *  p_Air_compressor_Control_Msg);
//��ѹ��������Ϣ//���ݽ���
enum Error_code Air_compressor_Control_Msg_analysis(CAN_message * p_can_msg, struct Air_compressor_Control_Msg *  p_Air_compressor_Control_Msg);
//��ѹ��������Ϣ//���ݷ�װ
enum Error_code Air_compressor_Control_Msg_encapsulation(struct Air_compressor_Control_Msg *  p_Air_compressor_Control_Msg, CAN_message * p_can_msg);
//��ѹ��������Ϣ//���ݴ���
enum Error_code Air_compressor_Control_Msg_execute(struct Air_compressor_Control_Msg *  p_Air_compressor_Control_Msg);




//1.2��ѹ��״̬��Ϣ
typedef struct Air_compressor_stats_Msg2
{
	u32		updata_event_time;	//���ݸ��µ�ʱ��
	u32		overtime_max;		//��ʱ��ʱ�䣨��ǰϵͳʱ�� ��ȥ ��һ�����ݸ��µ�ʱ�� ���� ��ʱʱ�䣬��Ϊ��ʱ��ͨѶ�жϣ�
	u32		Message_id;			//CAN��Ϣid��ID:0x0CFF02A7��
	u8    InputCur;       //��Ƶ���������
	u16   InputVol;       // ��Ƶ�������ѹ
	u16   OutPutPower;     //�������
	i16    MotorTemp;       //����¶�
	i16    ConverterTemp;   // �������¶�
 	i16    InsideTemp;   // ��ѹ���ڲ��¶�

	//	u8		DCDC_heartbeat_frame;		//����֡	ÿ�μ�1	
}Air_compressor_stats_Msg2;

//��ѹ��״̬��Ϣ//��ʼ��
enum Error_code Air_compressor_stats_Msg2_init(struct Air_compressor_stats_Msg2 *  p_Air_compressor_stats_Msg2);
//��ѹ��״̬��Ϣ//���ݽ���
enum Error_code Air_compressor_stats_Msg2_analysis(CAN_message * p_can_msg, struct Air_compressor_stats_Msg2 *  p_Air_compressor_stats_Msg2);
//��ѹ��״̬��Ϣ//���ݷ�װ
enum Error_code Air_compressor_stats_Msg2_encapsulation(struct Air_compressor_stats_Msg2 *  p_Air_compressor_stats_Msg2, CAN_message * p_can_msg);
//��ѹ��״̬��Ϣ//���ݴ���
enum Error_code Air_compressor_stats_Msg2_execute(struct Air_compressor_stats_Msg2 *  p_Air_compressor_stats_Msg2);



//1.3��ѹ��������Ϣ
typedef struct Air_compressor_alarm_Msg3
{
	u32		updata_event_time;	//���ݸ��µ�ʱ��
	u32		overtime_max;		//��ʱ��ʱ�䣨��ǰϵͳʱ�� ��ȥ ��һ�����ݸ��µ�ʱ�� ���� ��ʱʱ�䣬��Ϊ��ʱ��ͨѶ�жϣ�
	u32		Message_id;			//CAN��Ϣid��ID:0x1811A7B2��
	u8    CompressorState;   //��ѹ��״̬
	u16   FaultCode;         //������
	u8    faultLev;          //���ϵȼ�
	u32   ActSpeed;          //��ѹ��ʵ��ת��

	//	u8		DCDC_heartbeat_frame;		//����֡	ÿ�μ�1	
}Air_compressor_alarm_Msg3;

//��ѹ��������Ϣ//��ʼ��
enum Error_code Air_compressor_alarm_Msg3_init(struct Air_compressor_alarm_Msg3 *  p_Air_compressor_alarm_Msg3);
//��ѹ��������Ϣ//���ݽ���
enum Error_code Air_compressor_alarm_Msg3_analysis(CAN_message * p_can_msg, struct Air_compressor_alarm_Msg3 *  p_Air_compressor_alarm_Msg3);
//��ѹ��������Ϣ//���ݷ�װ
enum Error_code Air_compressor_alarm_Msg3_Msg_encapsulation(struct Air_compressor_alarm_Msg3 *  p_Air_compressor_alarm_Msg3, CAN_message * p_can_msg);
//��ѹ��������Ϣ//���ݴ���
enum Error_code Air_compressor_alarm_Msg3_execute(struct Air_compressor_alarm_Msg3 *  p_Air_compressor_alarm_Msg3);




//2.1����ѭ���ÿ�����Ϣ
typedef struct H2_PUMP_Control_Msg
{
	u32		updata_event_time;	//���ݸ��µ�ʱ��
	u32		send_message_time_max;		//��ʱ��ʱ�䣨��ǰϵͳʱ�� ��ȥ ��һ�����ݸ��µ�ʱ�� ���� ��ʱʱ�䣬��Ϊ��ʱ��ͨѶ�жϣ�
	u32		Message_id;			//CAN��Ϣid��ID:0xOCFFA63D��
	float Mass_Flow_Setpoint;     //�����趨
	float   Speed_setpoint;       //ת���趨
	u8    Enable_Pump;          //ѭ����ʹ��
	u8    Enable_Mass_Flow_Govemor;  //�������ʹ��

	//	u8		DCDC_heartbeat_frame;		//����֡	ÿ�μ�1	
}H2_PUMP_Control_Msg;

//����ѭ���ÿ�����Ϣ//��ʼ��
enum Error_code H2_PUMP_Control_Msg_init(struct H2_PUMP_Control_Msg *  p_H2_PUMP_Control_Msg);
//����ѭ���ÿ�����Ϣ//���ݽ���
enum Error_code H2_PUMP_Control_Msg_analysis(CAN_message * p_can_msg, struct H2_PUMP_Control_Msg *  p_H2_PUMP_Control_Msg);
//����ѭ���ÿ�����Ϣ//���ݷ�װ
enum Error_code H2_PUMP_Control_Msg_encapsulation(struct H2_PUMP_Control_Msg *  p_H2_PUMP_Control_Msg, CAN_message * p_can_msg);
//����ѭ���ÿ�����Ϣ//���ݴ���
enum Error_code H2_PUMP_Control_Msg_execute(struct H2_PUMP_Control_Msg *  p_H2_PUMP_Control_Msg);


//2.2����ѭ����������Ϣ
typedef struct H2_circulating_pump_data
{
	u32		updata_event_time;								 //  ���ݸ��µ�ʱ��
	u32		overtime_max;									 //  ��ʱ��ʱ�䣨��ǰϵͳʱ�� ��ȥ ��һ�����ݸ��µ�ʱ�� ���� ��ʱʱ�䣬��Ϊ��ʱ��ͨѶ�жϣ�
	u32		Message_id;										 //  CAN��Ϣid��ID:0xOCFFA7B4��

	float	    Actual_mass_flow;        					    //  ��������
	float	  Actual_speed;        					            //  ����ѭ����ת��
	float	    Actual_current;        					        //  ����ѭ���õ���
	float	    Actual_voltage;        					        //  ����ѭ���õ�ѹ
	i16	  Actual_electronic_temperature;                        //  ����ѭ���õ���¶�
	i16	  Actual_air_temperature;        		        	    //  ����ѭ���������¶�
	u8	    status_diagnose_word;        		    		    //  ����ѭ����״̬����ֽ�

}H2_circulating_pump_data;



//����ѭ����������Ϣ/��ʼ��
enum Error_code H2_circulating_pump_data_data_init(struct H2_circulating_pump_data *  p_H2_circulating_pump_data);

//����ѭ����������Ϣ/���ݽ���  
enum Error_code H2_circulating_pump_data_analysis(CAN_message * p_can_msg, struct H2_circulating_pump_data *  p_H2_circulating_pump_data);

//����ѭ����������Ϣ//���ݷ�װ
enum Error_code H2_circulating_pump_data_encapsulation(struct H2_circulating_pump_data *  p_H2_circulating_pump_data, CAN_message * p_can_msg);
//����ѭ����������Ϣ//���ݴ���
enum Error_code H2_circulating_pump_data_data_execute(struct H2_circulating_pump_data *  p_H2_circulating_pump_data);





//2.3����ѭ���ò�����Ϣ
typedef struct H2_circulating_pump_Parameter_values
{
	u32		updata_event_time;								 //  ���ݸ��µ�ʱ��
	u32		overtime_max;									 //  ��ʱ��ʱ�䣨��ǰϵͳʱ�� ��ȥ ��һ�����ݸ��µ�ʱ�� ���� ��ʱʱ�䣬��Ϊ��ʱ��ͨѶ�жϣ�
	u32		Message_id;										 //  CAN��Ϣid��ID:0x0CFFA83D��

	float	    Bm_tPt1MassFlow_c;        					
	float	      Bm_KpAirGvnr_c;        					     
	float	      Bm_kiAirGvnr_c;        					     
	float	    Bm_nSetErrorRepValue_c;        		


}H2_circulating_pump_Parameter_values;



//����ѭ���ò�����Ϣ/��ʼ��
enum Error_code H2_circulating_pump_Parameter_values_init(struct H2_circulating_pump_Parameter_values *  p_H2_circulating_pump_Parameter_values);

//����ѭ���ò�����Ϣ/���ݽ���  
enum Error_code H2_circulating_pump_Parameter_values_analysis(CAN_message * p_can_msg, struct H2_circulating_pump_Parameter_values *  p_H2_circulating_pump_Parameter_values);

//����ѭ���ò�����Ϣ//���ݷ�װ
enum Error_code H2_circulating_pump_Parameter_values_encapsulation(struct H2_circulating_pump_Parameter_values *  p_H2_circulating_pump_Parameter_values, CAN_message * p_can_msg);
//����ѭ���ò�����Ϣ//���ݴ���
enum Error_code H2_circulating_pump_Parameter_values_execute(struct H2_circulating_pump_data *  p_H2_circulating_pump_Parameter_values);


//2.4����ѭ����AcKnowledgment��Ϣ
typedef struct H2_circulating_pump_AcKnowledgment
{
	u32		updata_event_time;								 //  ���ݸ��µ�ʱ��
	u32		overtime_max;									 //  ��ʱ��ʱ�䣨��ǰϵͳʱ�� ��ȥ ��һ�����ݸ��µ�ʱ�� ���� ��ʱʱ�䣬��Ϊ��ʱ��ͨѶ�жϣ�
	u32		Message_id;										 //  CAN��Ϣid��ID:0x18FFABB4��

	u8	    AcKnowledgment;        					
	u32	    Parameter_Group_number;      //��Ҫ��ѯ�Ĳ������� 					     



}H2_circulating_pump_AcKnowledgment;



//����ѭ����AcKnowledgment��Ϣ/��ʼ��
enum Error_code H2_circulating_pump_AcKnowledgment_init(struct H2_circulating_pump_AcKnowledgment *  p_H2_circulating_pump_AcKnowledgment);

//����ѭ����AcKnowledgment��Ϣ/���ݽ���  
enum Error_code H2_circulating_pump_AcKnowledgment_analysis(CAN_message * p_can_msg, struct H2_circulating_pump_AcKnowledgment *  p_H2_circulating_pump_AcKnowledgment);

//����ѭ����AcKnowledgment��Ϣ//���ݷ�װ
enum Error_code H2_circulating_pump_AcKnowledgment_encapsulation(struct H2_circulating_pump_AcKnowledgment *  p_H2_circulating_pump_AcKnowledgment, CAN_message * p_can_msg);
//����ѭ���AcKnowledgment��Ϣ//���ݴ���
enum Error_code H2_circulating_pump_AcKnowledgment_execute(struct H2_circulating_pump_AcKnowledgment *  p_H2_circulating_pump_AcKnowledgment);




//3.1.0Ѳ����ʵ�ʵ�ѹֵ
struct Itinerant_detective_Single_voltage_actual_data
{
	u32		updata_event_time;					//���ݸ���ʱ��
	u32		overtime_max;		  //����ʱ����
	u32		Message_id;							//CAN��ϢID
	float		fell_single_voltage[4];				//Ѳ�쵥Ƭ��ѹ

};

//Ѳ����ʵ�ʵ�ѹֵ//��ʼֵ
enum Error_code Itinerant_detective_Single_voltage_actual_data_init(struct Itinerant_detective_Single_voltage_actual_data *  p_Itinerant_detective_Single_voltage_actual_data,int ID_num);
//Ѳ����ʵ�ʵ�ѹֵ//���ݽ���
enum Error_code Itinerant_detective_Single_voltage_actual_data_analysis(CAN_message * p_can_msg, struct Itinerant_detective_Single_voltage_actual_data *  p_Itinerant_detective_Single_voltage_actual_data);
//Ѳ����ʵ�ʵ�ѹֵ//���ݷ�װ
enum Error_code Itinerant_detective_Single_voltage_actual_data_encapsulation(struct Itinerant_detective_Single_voltage_actual_data *  p_Itinerant_detective_Single_voltage_actual_data, CAN_message * p_can_msg);
//Ѳ����ʵ�ʵ�ѹֵ//���ݴ���
enum Error_code Itinerant_detective_Single_voltage_actual_data_execute(struct Itinerant_detective_Single_voltage_actual_data *  p_Itinerant_detective_Single_voltage_actual_data);


//3.2.0Ѳ������״̬
struct Itinerant_detective_operate_statas
{
	u32		updata_event_time;					//���ݸ���ʱ��
	u32		overtime_max;				      //����ʱ����
	u32		Message_id;								//CAN��ϢID (0x1801BCBA)
	u8	  itinerant_detective_working_statas;			//Ѳ������״̬
	u8 		health_of_telectric_heap;							//��ؽ���״̬
	u8		Single_battery_overvoltage_alarm;		//�����ع�ѹ����
	u8    Single_battery_undervoltage_alarm;   //������Ƿѹ����
	u8		Single_voltage_unbalance_alarm;				//�����ز�������
	float   electric1_mean_voltage;							//���1ƽ����ѹ
	float   electric2_mean_voltage;							//���2ƽ����ѹ
	u8		heartbeat_frame;						//����֡

};

//Ѳ������״̬//��ʼֵ
enum Error_code Itinerant_detective_operate_statas_init(struct Itinerant_detective_operate_statas *  p_Itinerant_detective_operate_statas, u32 can_message_id);
//Ѳ������״̬//���ݽ���
enum Error_code Itinerant_detective_operate_statas_analysis(CAN_message * p_can_msg, struct Itinerant_detective_operate_statas *  p_Itinerant_detective_operate_statas);
//Ѳ������״̬//���ݷ�װ
enum Error_code Itinerant_detective_operate_statas_encapsulation(struct Itinerant_detective_operate_statas *  p_Itinerant_detective_operate_statas, CAN_message * p_can_msg);
//Ѳ������״̬//���ݴ���
enum Error_code Itinerant_detective_operate_statas_execute(struct Itinerant_detective_operate_statas *  p_Itinerant_detective_operate_statas);



//3.2.1 Ѳ�쵥Ƭ��ߵ�ѹ
struct Itinerant_detective_single_chip_highest_voltage
{
	u32		updata_event_time;					//���ݸ���ʱ��
	u32		overtime_max;				        //����ʱ����;				
	u32		Message_id;							    //CAN��ϢID
	float 	electric1_single_chip_highest_voltage;							//���1��Ƭ��ߵ�ѹ
	u16		electric1_single_chip_highest_voltage_num;					//���1��Ƭ��ߵ�ѹ���
	float 	electric2_single_chip_highest_voltage;							//���2��Ƭ��ߵ�ѹ
	u16		electric2_single_chip_highest_voltage_num;					//���2��Ƭ��ߵ�ѹ���

};

//Ѳ�쵥Ƭ��ߵ�ѹ//��ʼֵ
enum Error_code Itinerant_detective_single_chip_highest_voltage_init(struct Itinerant_detective_single_chip_highest_voltage *  p_Itinerant_detective_single_chip_highest_voltage, u32 can_message_id);
//Ѳ�쵥Ƭ��ߵ�ѹ//���ݽ���
enum Error_code Itinerant_detective_single_chip_highest_voltage_analysis(CAN_message * p_can_msg, struct Itinerant_detective_single_chip_highest_voltage *  p_Itinerant_detective_single_chip_highest_voltage);
//Ѳ�쵥Ƭ��ߵ�ѹ//���ݷ�װ
enum Error_code Itinerant_detective_single_chip_highest_voltage_encapsulation(struct Itinerant_detective_single_chip_highest_voltage *  p_Itinerant_detective_single_chip_highest_voltage, CAN_message * p_can_msg);
//Ѳ�쵥Ƭ��ߵ�ѹ//���ݴ���
enum Error_code Itinerant_detective_single_chip_highest_voltage_execute(struct Itinerant_detective_single_chip_highest_voltage *  p_Itinerant_detective_single_chip_highest_voltage);



//1.7 Ѳ�쵥Ƭ��͵�ѹ	
struct Itinerant_detective_single_chip_minimum_voltage
{
	u32		updata_event_time;					//���ݸ���ʱ��
	u32		overtime_max;				       //����ʱ����;
	u32		Message_id;							   //CAN��ϢID
	float 	electric1_single_chip_minimum_voltage;							//���1��͵�ѹ
	u16		electric1_single_chip_minimum_voltage_num;					//���1��͵�ѹ���
	float 	electric2_single_chip_minimum_voltage;							//���2��͵�ѹ
	u16		electric2_single_chip_minimum_voltage_num;					//���2��ͱ��

};

//Ѳ�쵥Ƭ��͵�ѹ	//��ʼֵ
enum Error_code Itinerant_detective_single_chip_minimum_voltage_init(struct Itinerant_detective_single_chip_minimum_voltage *  p_Itinerant_detective_single_chip_minimum_voltage, u32 can_message_id);
//Ѳ�쵥Ƭ��͵�ѹ	//���ݽ���
enum Error_code Itinerant_detective_single_chip_minimum_voltage_analysis(CAN_message * p_can_msg, struct Itinerant_detective_single_chip_minimum_voltage *  p_Itinerant_detective_single_chip_minimum_voltage);
//Ѳ�쵥Ƭ��͵�ѹ	//���ݷ�װ
enum Error_code Itinerant_detective_single_chip_minimum_voltage_encapsulation(struct Itinerant_detective_single_chip_minimum_voltage *  p_Itinerant_detective_single_chip_minimum_voltage, CAN_message * p_can_msg);
//Ѳ�쵥Ƭ��͵�ѹ	//���ݴ���
enum Error_code Itinerant_detective_single_chip_minimum_voltage_execute(struct Itinerant_detective_single_chip_minimum_voltage *  p_Itinerant_detective_single_chip_minimum_voltage);


//1.8	Ѳ���ܵ�ѹ
struct Itinerant_detective_voltage_data
{
	u32		updata_event_time;					//���ݸ���ʱ��
	u32		overtime_max;				        //����ʱ����;
	u32		Message_id;						    	 //CAN��ϢID
	float	Itinerant_detective_total_voltage;			//Ѳ���ܵ�ѹ				




};

//Ѳ���ܵ�ѹ//��ʼֵ
enum Error_code Itinerant_detective_voltage_data_init(struct Itinerant_detective_voltage_data *  p_Itinerant_detective_voltage_data, u32 can_message_id);
//Ѳ���ܵ�ѹ//���ݽ���
enum Error_code Itinerant_detective_voltage_data_analysis(CAN_message * p_can_msg, struct Itinerant_detective_voltage_data *  p_Itinerant_detective_voltage_data);
//Ѳ���ܵ�ѹ//���ݷ�װ
enum Error_code Itinerant_detective_voltage_data_encapsulation(struct Itinerant_detective_voltage_data *  p_Itinerant_detective_voltage_data, CAN_message * p_can_msg);
//Ѳ���ܵ�ѹ//���ݴ���
enum Error_code Itinerant_detective_voltage_data_execute(struct Itinerant_detective_voltage_data *  p_Itinerant_detective_voltage_data);





//	��Ե�����
struct Insulation_monitor_data
{
	u32		updata_event_time;					//���ݸ���ʱ��
	u32		overtime_max;				        //����ʱ����;
	u32		Message_id;						    	 //CAN��ϢID
	u8    fault_level;                          //���ϵȼ�
	u8    error_code	;			         //������
	u16   Insulation_resistance_value;  //��Ե����ֵ
	u16   Battery_voltage;            //��ص�ѹ
	u8    life_frame;                      //����֡
};

//��Ե�����//��ʼֵ
enum Error_code Insulation_monitor_data_init(struct Insulation_monitor_data *  p_Insulation_monitor_data);
//��Ե�����//���ݽ���
enum Error_code Insulation_monitor_data_analysis(CAN_message * p_can_msg, struct Insulation_monitor_data *  p_Insulation_monitor_data);
//��Ե�����//���ݷ�װ
enum Error_code Insulation_monitor_data_encapsulation(struct Insulation_monitor_data *  p_Insulation_monitor_data, CAN_message * p_can_msg);
//��Ե�����//���ݴ���
enum Error_code Insulation_monitor_data_execute(struct Insulation_monitor_data *  p_Insulation_monitor_data);







////ad�ɼ� ������       ��Ϊ���� 6��
struct Ad_auxiliary_board_message
{
	u32		updata_event_time;					//���ݸ���ʱ��
	u32		overtime_max;				        //����ʱ����;
	u32		message_id;						    	 //CAN��ϢID
	u16     ad_auxiliary_board_message_data[4]; //can��Ϣ��adԭʼֵ  12λad    
};

//ad�ɼ� ������//��ʼֵ
enum Error_code ad_auxiliary_board_message_init(struct Ad_auxiliary_board_message *  p_ad_auxiliary_board_message, u16 num_id);
//ad�ɼ� ������//���ݽ���
enum Error_code ad_auxiliary_board_message_analysis(CAN_message * p_can_msg, struct Ad_auxiliary_board_message *  p_ad_auxiliary_board_message);
//ad�ɼ� ������//���ݷ�װ
enum Error_code ad_auxiliary_board_message_encapsulation(struct Ad_auxiliary_board_message *  p_ad_auxiliary_board_message, CAN_message * p_can_msg);
//ad�ɼ� ������//���ݴ���
enum Error_code ad_auxiliary_board_message_execute(struct Ad_auxiliary_board_message *  p_ad_auxiliary_board_message);



//fcu������λ��,canͨ��id
#define PC_CAN_COMMUNICATION_FCU_TO_LABVIEW_ID          0x1800BDBC

//��λ������fcu,canͨ��id
#define PC_CAN_COMMUNICATION_LABVIEW_TO_FCU_ID          0x1400BCBD

//fcu������λ�� ��can����
#define PC_CAN_COMMUNICATION_FCU_TO_LABVIEW_NUMBER     44

//fcu����λ��labview��canͨ�ţ�
//fcu������λ����0x1800BDBC~0x182BBDBC
typedef struct PC_can_communication_fcu_to_labview
{
	u32		updata_event_time;	//���ݸ��µ�ʱ��
	u32		send_message_time_max;		//��ʱ��ʱ�䣨��ǰϵͳʱ�� ��ȥ ��һ�����ݸ��µ�ʱ�� ���� ��ʱʱ�䣬��Ϊ��ʱ��ͨѶ�жϣ�
	u32		message_id;			//CAN��Ϣid��ID:0x1800BDBC��
	u32     can_message_index;  //can��Ϣ����0~43
	//���ݾͲ������ﱸ���ˣ�ֱ�Ӵ�data_buffer.h����ȥ�á�
}PC_can_communication_fcu_to_labview;                     

//fcu������λ��//��ʼֵ
enum Error_code pc_can_communication_fcu_to_labview_init(struct PC_can_communication_fcu_to_labview *  p_pc_can_communication_fcu_to_labview);
//fcu������λ��//���ݽ���
enum Error_code pc_can_communication_fcu_to_labview_analysis(CAN_message * p_can_msg, struct PC_can_communication_fcu_to_labview *  p_pc_can_communication_fcu_to_labview);
//fcu������λ��//���ݷ�װ
enum Error_code pc_can_communication_fcu_to_labview_encapsulation(struct PC_can_communication_fcu_to_labview *  p_pc_can_communication_fcu_to_labview, CAN_message * p_can_msg);
//fcu������λ��//���ݴ���
enum Error_code pc_can_communication_fcu_to_labview_execute(struct PC_can_communication_fcu_to_labview *  p_pc_can_communication_fcu_to_labview);        



//��λ������fcu��0x1400BCBD
typedef struct PC_can_communication_labview_to_fcu
{
	u32		updata_event_time;					//���ݸ���ʱ��
	u32		overtime_max;				        //����ʱ����;
	u32		message_id;						    //CAN��ϢID ��ID:0x1400BCBD��
	//���ݾͲ������ﱸ���ˣ�ֱ�Ӵ�data_buffer.h����ȥ�á�
}PC_can_communication_labview_to_fcu;                     

//��λ������fcu//��ʼֵ
enum Error_code pc_can_communication_labview_to_fcu_init(struct PC_can_communication_labview_to_fcu *  p_pc_can_communication_labview_to_fcu);
//��λ������fcu//���ݽ���
enum Error_code pc_can_communication_labview_to_fcu_analysis(CAN_message * p_can_msg, struct PC_can_communication_labview_to_fcu *  p_pc_can_communication_labview_to_fcu);
//��λ������fcu//���ݷ�װ
enum Error_code pc_can_communication_labview_to_fcu_encapsulation(struct PC_can_communication_labview_to_fcu *  p_pc_can_communication_labview_to_fcu, CAN_message * p_can_msg);
//��λ������fcu//���ݴ���
enum Error_code pc_can_communication_labview_to_fcu_execute(struct PC_can_communication_labview_to_fcu *  p_pc_can_communication_labview_to_fcu);        

                           


//canͨ��Э�����
typedef struct Can_Communication_Protocol2_Total
{
	struct Air_compressor_Control_Msg		    	air_compressor_control_msg;
	struct Air_compressor_stats_Msg2		    	air_compressor_stats_msg2;
	struct Air_compressor_alarm_Msg3		    	air_compressor_alarm_msg3;

	struct H2_PUMP_Control_Msg		            	h2_pump_control_msg;
	struct H2_circulating_pump_data			    	h2_circulating_pump_data;		
	struct H2_circulating_pump_Parameter_values		h2_circulating_pump_parameter_values;
	struct H2_circulating_pump_AcKnowledgment		h2_circulating_pump_acknowledgment;

    //  1�ŵ��   Ѳ��1
	struct Itinerant_detective_Single_voltage_actual_data   itinerant_detective_single_voltage_actual_data[ITINERANT_DETECTIVE_CAN_MESSAGE_NUMBER];
	struct Itinerant_detective_operate_statas			    itinerant_detective_operate_statas;		
	struct Itinerant_detective_single_chip_highest_voltage	itinerant_detective_single_chip_highest_voltage;
	struct Itinerant_detective_single_chip_minimum_voltage	itinerant_detective_single_chip_minimum_voltage;	
	struct Itinerant_detective_voltage_data              	itinerant_detective_voltage_data;	   
	
    //  2�ŵ��   Ѳ��2
//	struct Itinerant_detective_Single_voltage_actual_data   itinerant_detective_single_voltage_actual_data2[ITINERANT_DETECTIVE_CAN_MESSAGE_NUMBER];
	struct Itinerant_detective_operate_statas			    itinerant_detective_operate_statas2;		
	struct Itinerant_detective_single_chip_highest_voltage	itinerant_detective_single_chip_highest_voltage2;
	struct Itinerant_detective_single_chip_minimum_voltage	itinerant_detective_single_chip_minimum_voltage2;	
	struct Itinerant_detective_voltage_data              	itinerant_detective_voltage_data2;	   

	//��Ե���ģ��
	struct Insulation_monitor_data                  insulation_monitor_data;     
			             
	//����С���ad�ɼ�					 
    struct Ad_auxiliary_board_message                       ad_auxiliary_board_message_array[AD_AUXILIARY_BOARD_MESSAGE_NUMBER_MAX] ;
	
	struct PC_can_communication_fcu_to_labview       pc_can_communication_fcu_to_labview;
	struct PC_can_communication_labview_to_fcu       pc_can_communication_labview_to_fcu;
}Can_Communication_Protocol2_Total;

//canͨ��Э�����       
extern struct Can_Communication_Protocol2_Total    can_communication_protocol2_total;                                     

//canͨ��Э����� ��ʼ��
enum Error_code Can_communication_protocol2_init(struct Can_Communication_Protocol2_Total * p_can_communication_protocol2_total);

//���������ݵ�ʱ������
enum Error_code Can_communication_protocol2_clear_time(struct Can_Communication_Protocol2_Total * p_can_communication_protocol2_total);


//ͨ�����ܵ�CAN��Ϣ�����������ݡ�
enum Error_code Can_communication_protocol2_updata_receivev_can(struct Can_Communication_Protocol2_Total * p_can_communication_protocol2_total, CAN_message * p_can_msg);


//��ʱ��װcan����
//���û����Ҫ���͵���Ϣ�����ش���
//ע��һ��ֻ��ת��һ��������Ϣ������ж�������ѭ�����ñ�������ֱ�����������ش���
enum Error_code Can_communication_protocol2_can_encapsulation_and_send(struct Can_Communication_Protocol2_Total * p_can_communication_protocol2_total, CAN_message * p_can_msg);

/*
//��ʱ����can���ݣ�Ĭ��can1��
enum Error_code Control_Policy_ontime_can_send_data(enum Can_Channels CANx, CAN_message * p_can_msg);
*/



#endif
