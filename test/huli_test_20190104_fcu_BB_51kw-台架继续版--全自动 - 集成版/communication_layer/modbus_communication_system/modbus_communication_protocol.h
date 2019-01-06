/*
can_communication_system ��ģ����canͨ��ϵͳ
���ܣ�����can�������շ����ݡ�
�÷���
����ģ��ֱ�Ӱ�����ģ�飬Ȼ����Ϊ�����ķ���ֵ��
�ϲ�ͨ���������������жϺ�����ִ�������
*/ 
//-----------------------------------------------------------------------------------------------





#ifndef __MODBUS_COMMUNICATION_PROTOCOL_H
#define __MODBUS_COMMUNICATION_PROTOCOL_H

#include "error_system.h"
#include "modbus_communication_system.h"
#include "control_manager.h"





#define MODBUS_232_SEND_MESSAGE_TIME_MAX   1500        //modbus_232�ķ���ʱ����

#define DIRECTION_DATA_TRANSMISSION_PC_TO_FCU  0XAA

#define DIRECTION_DATA_TRANSMISSION_FCU_TO_PC  0XBB

#define FUNCTION_CODE_01  1
#define FUNCTION_CODE_02  2
#define FUNCTION_CODE_03  3
#define FUNCTION_CODE_04  4
#define FUNCTION_CODE_05  5
#define FUNCTION_CODE_06  6


extern struct FCU_modbus_tatal_manager_data  fcu_modbus_tatal_manager_data;









//1����������

//1.1����������Ϣ
struct Hydrogen_detective_data
{	

  u32   updata_event_time;    //���ݸ���ʱ��
  u32		send_message_time_max;         //�����ʱʱ��������Ϊ ������Ϣ��ʱ��Ƶ�� ����500ms����һ��
  u8    direction_data_transmission;   //���ݴ��䷽��
	u8		function_code;				//֡����
  u8		data_length;				//�����ֽڳ���
  float	h2_pressure_proportional_valve_front;	//������ǰ��ѹ��fcuϵͳ��H2�����ڣ�		����4-20mA
  float	h2_pressure_proportional_valve_rear;	//����������ѹ��                		����4-20mA
	float	h2_pressure_pile_inlet;	                //�����ѹ���ǵ�ѵ�H2���          	����4-20mA	
  float	h2_pressure_pile_outlet;	            //������ѹ���ǵ�ѵ�H2����  	����4-20mA	
  float	h2_pressure_tail_outlet;				//����β�ŵ�ѹ��,Ҳ�ǵ��H2����ѹ��		����4-20mA	


  //���
  u8		h2_inlet_valve;							//������������							���0��1
	u8		h2_outlet_valve;						//����β�ŷ���							���0��1
	float	h2_proportional_valve_pwm_dutyfactor;	//������PWMռ�ձȣ�pid�Զ����ơ�		���pwm 0~5V  Ƶ��>1000HZ
	u8		h2_circulating_pump_enble;				//����ѭ���õ�IOʹ��					���0��1
	
	//����ѭ����  canͨ��
	enum 	Working_Communication_Mode		h2_circulating_pump_working_communication_mode;	//����ѭ����  canͨ��ģʽ
	u16     h2_circulating_pump_speed_setpoint;             //����ѭ����ת���趨            ���can
	u8      h2_circulating_pump_enable_pump;                //����ѭ����CANʹ��                ���can
	float	  h2_circulating_pump_actual_mass_flow;        		//  ����ѭ������������      ����can
	
	float	h2_circulating_pump_actual_speed;        			//  ����ѭ����ʵ��ת��      ����can
	float	h2_circulating_pump_actual_current;        			//  ����ѭ���õ���          ����can
	float	h2_circulating_pump_actual_voltage;        			//  ����ѭ���õ�ѹ          ����can
	i16		h2_circulating_pump_actual_electronic_temperature;  //  ����ѭ���õ���¶�      ����can
	
	//pid����
	float   h2_pressure_target_value;               //��ѹ �趨Ŀ��ֵ
	float   h2_pressure_real_target_value;          //��ѹ ʵ��Ŀ��ֵ
	float   h2_pressure_advance_current_value;      //��ѹ ��ǰ��  ʵ��ֵ
	float   h2_pressure_advance_set_value;          //��ѹ ��ǰ��  �趨ֵ  Ĭ��Ϊ0��һ����Ϊ5
	u32     h2_pressure_pid1_advance_time;          //pid1ʱ����ǰ��      Ĭ��250ms
	u32     h2_pressure_pid2_advance_time;          //pid2ʱ����ǰ��      Ĭ��1000ms
			
  u8      PID1_is_enble_pid;      //�Ƿ�ʹ��pid
	float   PID1_Kp;                  //����ϵ��    ��ʵ��ֵ*1000��
	float   PID1_Ki;                  //����ϵ��    ��ʵ��ֵ*1000��
	float   PID1_Kd;                  //΢��ϵ��    ��ʵ��ֵ*1000��
	
	u8      PID2_is_enble_pid;      //�Ƿ�ʹ��pid
	float   PID2_Kp;                  //����ϵ��    ��ʵ��ֵ*1000��
	float   PID2_Ki;                  //����ϵ��    ��ʵ��ֵ*1000��
	float   PID2_Kd;                  //΢��ϵ��    ��ʵ��ֵ*1000��
	
	u8		h2_pid_mode ;   						//pid�㷨����ģʽ��1��ʾʹ��pid1�����ƣ�2��ʾʹ��pid2������
	
  //����β�ſ���
	u8		h2_is_enable_outlet_valve;				//����β�ŷ����Զ����Ƶ�ʹ�ܿ���
	u32		h2_outlet_valve_open_time ;				//����β�ŷ�������ʱ��
	u32		h2_outlet_valve_close_time ;			//����β�ŷ��رյ�ʱ��
	
	float   h2_pressure_fluctuate_last_max;		    //��ѹ ����  �ϴ����ֵ
	float   h2_pressure_fluctuate_last_min;			//��ѹ ����  �ϴ���Сֵ
	
	
};


//����������Ϣ//��ʼ��
enum Error_code Hydrogen_detective_data_init(struct Hydrogen_detective_data *  p_Hydrogen_detective_data);
//����������Ϣ//���ݽ���
enum Error_code Hydrogen_detective_data_analysis(struct Modbus_Data_Buffer * p_modbus_receive_data_buffer, struct Hydrogen_detective_data *  p_Hydrogen_detective_data);
//����������Ϣ//���ݷ�װ
              
enum Error_code Hydrogen_detective_data_encapsulation( struct Hydrogen_detective_data *  p_Hydrogen_detective_data, struct Modbus_Data_Buffer * p_modbus_send_data_buffer);
//����������Ϣ//���ݴ���
enum Error_code Hydrogen_detective_data_execute(struct Hydrogen_detective_data *  p_Hydrogen_detective_data);
//����������Ϣ//�������״̬
enum Error_code Hydrogen_detective_data_clear_updata(struct Hydrogen_detective_data *  p_Hydrogen_detective_data);




//2����������

//2.1����������Ϣ
struct Air_detective_data
{	

  u32   updata_event_time;    //���ݸ���ʱ��
  u32		send_message_time_max;         //�����ʱʱ��������Ϊ ������Ϣ��ʱ��Ƶ�� ����500ms����һ��
  u8    direction_data_transmission;   //���ݴ��䷽��
	u8		function_code;				//֡����
  u8		data_length;				//�����ֽڳ���
  
  	//����
  float	air_pressure_pile_inlet;				//�����ڷ�ѹ							����4-20mA
	float	air_pressure_pile_outlet;				//��ѳ��ڷ�ѹ							����4-20mA
	float	air_pressure_pile_back;					//��ѳ��ڱ�ѹ							����4-20mA
	float	air_temperature_pile_inlet;				//�����ڷ���							�������ֵ
	float	air_temperature_pile_outlet;			//��ѳ��ڷ���							�������ֵ
	float	air_temperature_pile_back;				//��ѳ��ڱ�ѹ�¶�						�������ֵ
	float	air_temperature_humidifier;				//��ʪ����ڷ���						�������ֵ
	float	air_rate_of_flow;						//��������								����0~5V

  	//���
	u8		air_outlet_valve;						//������β�ŷ���						���0��1

	//��ѹ��  can
	enum 	Working_Communication_Mode		air_compressor_working_communication_mode;		//��ѹ��  canͨ��ģʽ
	u8      air_compressor_enable;                  //��ѹ������	                        ���can
	u32		air_compressor_speed_setpoint;		    //��ѹ��ת�٣����Ʊ�Ƶ����				���can��


	//����β�ſ���
	u8		air_is_enable_outlet_valve;				//����β�ŷ����Զ����Ƶ�ʹ�ܿ���
	u32		air_outlet_valve_open_time ;			//����β�ŷ�������ʱ��
	u32		air_outlet_valve_close_time ;			//����β�ŷ��رյ�ʱ��	
	
	
};


//����������Ϣ//��ʼ��
enum Error_code Air_detective_data_init(struct Air_detective_data *  p_Air_detective_data);
//����������Ϣ//���ݽ���
enum Error_code Air_detective_data_analysis(struct Modbus_Data_Buffer * p_modbus_receive_data_buffer, struct Air_detective_data *  p_Air_detective_data);
//����������Ϣ//���ݷ�װ
enum Error_code Air_detective_data_encapsulation( struct Air_detective_data *  p_Air_detective_data, struct Modbus_Data_Buffer * p_modbus_send_data_buffer);
//����������Ϣ//���ݴ���
enum Error_code Air_detective_data_execute(struct Air_detective_data *  p_Air_detective_data);
//����������Ϣ//�������״̬
enum Error_code Air_detective_data_clear_updata(struct Air_detective_data *  p_Air_detective_data);




//3�����ɢ��ϵͳ����
//3.1���ɢ��ϵͳ����
struct Fell_temperature_data
{	

  u32   updata_event_time;    //���ݸ���ʱ��
  u32		send_message_time_max;         //�����ʱʱ��������Ϊ ������Ϣ��ʱ��Ƶ�� ����500ms����һ��
  u8    direction_data_transmission;   //���ݴ��䷽��
	u8		function_code;				//֡����
  u8		data_length;				//�����ֽڳ���
 
 	//���� 
	float	water_pressure_pile_inlet;				//������ˮѹ							����4-20mA
	float	water_pressure_pile_outlet;				//��ѳ���ˮѹ							����4-20mA
	float	water_temperature_pile_inlet;			//������ˮ��							�������ֵ
	float	water_temperature_pile_outlet;			//��ѳ���ˮ��							�������ֵ
	
		//���
	float	water_pump_pwm_dutyfactor;				//ˮ��PWMռ�ձ�							���pwm 0~24V 
	float	water_fan1_pwm_dutyfactor;				//����1PWMռ�ձ�						���pwm 0~24V 
	float	water_fan2_pwm_dutyfactor;				//����2PWMռ�ձ�						���pwm 0~24V 
	
	
	u8      water_PID_is_enble_pid;      //�Ƿ�ʹ��pid
	float   water_PID_Kp;                  //����ϵ��    ��ʵ��ֵ*1000��
	float   water_PID_Ki;                  //����ϵ��    ��ʵ��ֵ*1000��
	float   water_PID_Kd;                  //΢��ϵ��    ��ʵ��ֵ*1000��
	
  float   water_temperature_target_value;         //������ˮ�� Ŀ��ֵ
	
};


//���ɢ��ϵͳ����//��ʼ��
enum Error_code Fell_temperature_data_init(struct Fell_temperature_data *  p_Fell_temperature_data);
//���ɢ��ϵͳ����//���ݽ���
enum Error_code Fell_temperature_data_analysis(struct Modbus_Data_Buffer * p_modbus_receive_data_buffer, struct Fell_temperature_data *  p_Fell_temperature_data);
//���ɢ��ϵͳ����//���ݷ�װ
enum Error_code Fell_temperature_data_encapsulation( struct Fell_temperature_data *  p_Fell_temperature_data, struct Modbus_Data_Buffer * p_modbus_send_data_buffer);
//���ɢ��ϵͳ����//���ݴ���
enum Error_code Fell_temperature_data_execute(struct Fell_temperature_data *  p_Fell_temperature_data);
//���ɢ��ϵͳ����//�������״̬
enum Error_code Fell_temperature_data_updata(struct Fell_temperature_data *  p_Fell_temperature_data);




//4����ѹ��ɢ��ϵͳ����
//4.1��ѹ��ɢ��ϵͳ����
struct Air_compressor_temperature_data
{	

  u32   updata_event_time;    //���ݸ���ʱ��
  u32		send_message_time_max;         //�����ʱʱ��������Ϊ ������Ϣ��ʱ��Ƶ�� ����500ms����һ��
  u8    direction_data_transmission;   //���ݴ��䷽��
	u8		function_code;				//֡����
  u8		data_length;				//�����ֽڳ���
  
  	//����
  float	water_pressure_compressor_outlet;		//��ѹ������ˮѹ						����4-20mA
  float	water_temperature_compressor_outlet;	//��ѹ������ˮ��						�������ֵ
  float	water_temperature_pump_outlet;			//����һˮ�ó���ˮ��					�������ֵ
  float	water_temperature_compressor_shell;		//��ѹ�������¶�						�������ֵ
  
  	//���
	u8		water_pump_enable;						//ˮ�õ�ʹ��							���0��1
	float	water_fan_pwm_dutyfactor;				//����PWMռ�ձ�							���pwm 0~24V 

	
};


//��ѹ��ɢ��ϵͳ����//��ʼ��
enum Error_code Air_compressor_temperature_data_init(struct Air_compressor_temperature_data *  p_Air_compressor_temperature_data);
//��ѹ��ɢ��ϵͳ����//���ݽ���
enum Error_code Air_compressor_temperature_data_analysis(struct Modbus_Data_Buffer * p_modbus_receive_data_buffer, struct Air_compressor_temperature_data *  p_Air_compressor_temperature_data);
//��ѹ��ɢ��ϵͳ����//���ݷ�װ
enum Error_code Air_compressor_temperature_data_encapsulation( struct Air_compressor_temperature_data *  p_Air_compressor_temperature_data, struct Modbus_Data_Buffer * p_modbus_send_data_buffer);
//��ѹ��ɢ��ϵͳ����//���ݴ���
enum Error_code Air_compressor_temperature_data_execute(struct Air_compressor_temperature_data *  p_Air_compressor_temperature_data);
//��ѹ��ɢ��ϵͳ����//�������״̬
enum Error_code Air_compressor_temperature_data_updata(struct Air_compressor_temperature_data *  p_Air_compressor_temperature_data);





//5������������
//5.1����������
struct Fell_output_data
{	

  u32   updata_event_time;    //���ݸ���ʱ��
  u32		send_message_time_max;         //�����ʱʱ��������Ϊ ������Ϣ��ʱ��Ƶ�� ����500ms����һ��
  u8    direction_data_transmission;   //���ݴ��䷽��
	u8		function_code;				//֡����
  u8		data_length;				//�����ֽڳ���
  
 //����
	float	galvanic_pile_voltage;					//��ѵĵ�ѹ							����0~5V
	float	galvanic_pile_electricity;				//��ѵĵ���							����0~5V
	u8		fcu_start_enable;						//��ѵ�����ʹ��1�������ź���Ч   0�������ź���Ч	
	u8		fcu_stutter_stop_enable;				//��ѵļ�ͣʹ��1����ͣ�ź���Ч   0����ͣ�ź���Ч

	//���
	u8		galvanic_pile_is_enble_output;			//�������Ӵ���						���0��1
	u8		galvanic_pile_is_enble_load_resistance;	//��Ѹ��ص���Ӵ���					���0��1

	//Ѳ��  can
	enum 	Working_Communication_Mode		itinerant_detective_working_communication_mode;	//Ѳ��  canͨ��ģʽ
	u8		itinerant_detective_working_statas;		//Ѳ������״̬
	u8		Single_battery_overvoltage_alarm;		//�����ع�ѹ����
	u8		Single_battery_undervoltage_alarm;		//������Ƿѹ����
	u8		Single_voltage_unbalance_alarm;			//�����ز�������
	float   electric1_mean_voltage;					//���1ƽ����ѹ
	float 	electric1_single_chip_highest_voltage;	//���1��Ƭ��ߵ�ѹ
	u16		electric1_single_chip_highest_voltage_num;	//���1��Ƭ��ߵ�ѹ���
	float 	electric1_single_chip_minimum_voltage;	//���1��͵�ѹ
	u16     electric1_single_chip_minimum_voltage_num; //���1��͵�ѹ���
	float	itinerant_detective_total_voltage;		//Ѳ���ܵ�ѹ				

	
};

//����������//��ʼ��
enum Error_code Fell_output_data_init(struct Fell_output_data *  p_Fell_output_data);
//����������//���ݽ���
enum Error_code Fell_output_data_analysis(struct Modbus_Data_Buffer * p_modbus_receive_data_buffer, struct Fell_output_data *  p_Fell_output_data);
//����������//���ݷ�װ
enum Error_code Fell_output_data_encapsulation( struct Fell_output_data *  p_Fell_output_data, struct Modbus_Data_Buffer * p_modbus_send_data_buffer);
//����������//���ݴ���
enum Error_code Fell_output_data_execute(struct Fell_output_data *  p_Fell_output_data);
//����������//�������״̬
enum Error_code Fell_output_data_updata(struct Fell_output_data *  p_Fell_output_data);




//6��FCU����״̬��Ϣ
//6.1FCU����״̬��Ϣ
struct FCU_run_stata_data
{	

    u32   updata_event_time;    //���ݸ���ʱ��
    u32		send_message_time_max;         //�����ʱʱ��������Ϊ ������Ϣ��ʱ��Ƶ�� ����500ms����һ��
    u8    direction_data_transmission;   //���ݴ��䷽��
  	u8		function_code;				//֡����
    u8		data_length;				//�����ֽڳ���

    u8 FCU_control_mode;  //FCU����ģʽ
    u8 FCU_work_mode;    //FCU����ģʽ
    u8 FCU_alarm_mode;   //FCU�쳣�澯
    u16 FCU_error_code;   //FUC������
    u8 FCU_erroring_control_mode; //����˲��,FCU�Ŀ���ģʽ
    u8 FCU_system_run_mode;     //ϵͳ����ģʽ
    	
};


//FCU����״̬��Ϣ//��ʼ��
enum Error_code FCU_run_stata_data_init(struct FCU_run_stata_data *  p_FCU_run_stata_data);
//FCU����״̬��Ϣ//���ݽ���
enum Error_code FCU_run_stata_data_analysis(struct Modbus_Data_Buffer * p_modbus_receive_data_buffer, struct FCU_run_stata_data *  p_FCU_run_stata_data);
//FCU����״̬��Ϣ//���ݷ�װ
enum Error_code FCU_run_stata_data_encapsulation( struct FCU_run_stata_data *  p_FCU_run_stata_data, struct Modbus_Data_Buffer * p_modbus_send_data_buffer);
//FCU����״̬��Ϣ//���ݴ���
enum Error_code FCU_run_stata_data_execute(struct FCU_run_stata_data *  p_FCU_run_stata_data);
//FCU����״̬��Ϣ//�������״̬
enum Error_code FCU_run_stata_data_updata(struct FCU_run_stata_data *  p_FCU_run_stata_data);








/*

//7��FCU������������
//7.1FCU������������
struct FCU_receive_orde_data
{	

  //u32   updata_event_time;    //���ݸ���ʱ��
  //u32		overtime_max;         //�����ʱʱ��������Ϊ ������Ϣ��ʱ��Ƶ�� ����500ms����һ��
  u8    direction_data_transmission;   //���ݴ��䷽��
	u8		function_code;				//֡����
  u8		data_length;				//�����ֽڳ���
  u8    receive_orde_data[4];   //4���ֽڵ�����
  
  
  u8    h2_inlet_valve;      //����������
  u8		h2_is_enable_outlet_valve;				//����β�ŷ����Զ����Ƶ�ʹ�ܿ���
  u32		h2_outlet_valve_open_time ;				//����β�ŷ�������ʱ��
	u32		h2_outlet_valve_close_time ;			//����β�ŷ��رյ�ʱ��
  float	h2_proportional_valve_pwm_dutyfactor;	//������PWMռ�ձȣ�pid�Զ����ơ�		���pwm 0~5V  Ƶ��>1000HZ
  u8		h2_circulating_pump_enble;				//����ѭ���õ�IOʹ��					���0��1
  u8      h2_circulating_pump_enable_pump;                //����ѭ����ʹ��                ���can
  float   h2_pressure_target_value;               //��ѹ �趨Ŀ��ֵ
  float   h2_pressure_advance_set_value;          //��ѹ ��ǰ��  �趨ֵ  Ĭ��Ϊ0��һ����Ϊ5
  u8      PID1_is_enble_pid;      //�Ƿ�ʹ��pid
	float   PID1_Kp;                  //����ϵ��    ��ʵ��ֵ*1000��
	float   PID1_Ki;                  //����ϵ��    ��ʵ��ֵ*1000��
	float   PID1_Kd;                  //΢��ϵ��    ��ʵ��ֵ*1000��
	
	u8      PID2_is_enble_pid;      //�Ƿ�ʹ��pid
	float   PID2_Kp;                  //����ϵ��    ��ʵ��ֵ*1000��
	float   PID2_Ki;                  //����ϵ��    ��ʵ��ֵ*1000��
	float   PID2_Kd;                  //΢��ϵ��    ��ʵ��ֵ*1000��	
	u8		h2_pid_mode ;   						//pid�㷨����ģʽ��1��ʾʹ��pid1�����ƣ�2��ʾʹ��pid2������
	u8    air_compressor_enable;                  //��ѹ������	                        ���can
	u32		air_compressor_speed_setpoint;		    //��ѹ��ת�٣����Ʊ�Ƶ����				���can��
	u8		air_is_enable_outlet_valve;				//����β�ŷ����Զ����Ƶ�ʹ�ܿ���
	u32		air_outlet_valve_open_time ;			//����β�ŷ�������ʱ��
	u32		air_outlet_valve_close_time ;			//����β�ŷ��رյ�ʱ��
	float	water_pump_pwm_dutyfactor;				//ˮ��PWMռ�ձ�							���pwm 0~24V 
	float	water_fan1_pwm_dutyfactor;				//����1PWMռ�ձ�						���pwm 0~24V 
	float	water_fan2_pwm_dutyfactor;				//����2PWMռ�ձ�						���pwm 0~24V 
	
	u8      water_PID_is_enble_pid;      //�Ƿ�ʹ��pid
	float   water_PID_Kp;                  //����ϵ��    ��ʵ��ֵ*1000��
	float   water_PID_Ki;                  //����ϵ��    ��ʵ��ֵ*1000��
	float   water_PID_Kd;                  //΢��ϵ��    ��ʵ��ֵ*1000��
	
  float   water_temperature_target_value;         //������ˮ�� Ŀ��ֵ
  
  u8		compressor_water_pump_enable;						//ˮ�õ�ʹ��							���0��1
	float	compressor_water_fan_pwm_dutyfactor;				//����PWMռ�ձ�							���pwm 0~24V 
	
	u8		fcu_start_enable;						//��ѵ�����ʹ��1�������ź���Ч   0�������ź���Ч	
	u8		fcu_stutter_stop_enable;				//��ѵļ�ͣʹ��1����ͣ�ź���Ч   0����ͣ�ź���Ч
	u8		galvanic_pile_is_enble_output;			//�������Ӵ���						���0��1
	u8		galvanic_pile_is_enble_load_resistance;	//��Ѹ��ص���Ӵ���					���0��1
	u8    FCU_system_run_mode;     //ϵͳ����ģʽ

	
};



//FCU������������//��ʼ��
enum Error_code FCU_receive_orde_data_init(struct FCU_receive_orde_data *  p_FCU_receive_orde_data);
//FCU������������//���ݽ���
enum Error_code FCU_receive_orde_data_analysis(struct Modbus_Data_Buffer * p_modbus_receive_data_buffer, struct FCU_receive_orde_data *  p_FCU_receive_orde_data);
//FCU������������//���ݷ�װ
enum Error_code FCU_receive_orde_data_encapsulation( struct FCU_receive_orde_data *  p_FCU_receive_orde_data, struct Modbus_Data_Buffer * p_modbus_send_data_buffer);
//FCU������������//���ݴ���
enum Error_code FCU_receive_orde_data_execute(struct FCU_receive_orde_data *  p_FCU_receive_orde_data);
//FCU������������//�������״̬
enum Error_code FCU_receive_orde_data_updata(struct FCU_receive_orde_data *  p_FCU_receive_orde_data);

*/


//8��FCU�ܹ���״̬
//8.1FCU�ܹ���״̬
struct FCU_modbus_tatal_manager_data
{	

   	enum ISlock     islock;      //���ݱ�����
    
    struct Hydrogen_detective_data   hydrogen_detective_data;
    struct Air_detective_data   air_detective_data;
    struct Fell_temperature_data  fell_temperature_data;
    struct Air_compressor_temperature_data  air_compressor_temperature_data;
    struct Fell_output_data   fell_output_data;
    struct FCU_run_stata_data  fcu_run_stata_data;
  //  struct FCU_receive_orde_data  fcu_receive_orde_data;
    
    
	
};


//FCU�ܹ���״̬//��ʼ��
enum Error_code FCU_modbus_tatal_manager_data_init(struct FCU_modbus_tatal_manager_data *  p_FCU_modbus_tatal_manager_data);
//FCU�ܹ���״̬//���ݽ���
enum Error_code FCU_modbus_tatal_manager_data_analysis(struct Modbus_Data_Buffer * p_modbus_receive_data_buffer,struct FCU_Data_Buffer * p_FCU_Data_Buffer,struct Control_Policy_Total_Manager * p_Control_Policy_Total_Manager);
//FCU�ܹ���״̬//���ݷ�װ
enum Error_code FCU_modbus_tatal_manager_data_encapsulation( struct FCU_modbus_tatal_manager_data *  p_FCU_modbus_tatal_manager_data, struct Modbus_Data_Buffer * p_modbus_send_data_buffer);
//FCU�ܹ���״̬//���ݴ���
enum Error_code FCU_modbus_tatal_manager_data_data_execute(struct FCU_modbus_tatal_manager_data *  p_FCU_modbus_tatal_manager_data);
//FCU�ܹ���״̬//�������״̬
enum Error_code FCU_modbus_tatal_manager_data_updata(struct FCU_modbus_tatal_manager_data *  p_FCU_modbus_tatal_manager_data);






//ͨ��ͨ��  232 modbus��ʽ���´���ͨ������  
enum Error_code  p_FCU_modbus_tatal_manager_data_updata_by_232_modbus_communication();

//�������ݸ���ͨ��Э���������
enum Error_code modbus_232_receive_to_databuff(struct Modbus_Data_Buffer * p_modbus_receive_data_buffer,struct FCU_Data_Buffer * p_FCU_Data_Buffer,struct Control_Policy_Total_Manager *p_Control_Policy_Total_Manager);










void float_convert_four_byte(float *f,unsigned char *a,unsigned char *b,unsigned char *c,unsigned char *d);

float four_byte_convert_float(unsigned char a,unsigned char b,unsigned char c,unsigned char d);  






#endif




