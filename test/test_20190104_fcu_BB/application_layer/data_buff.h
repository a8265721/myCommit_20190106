#ifndef _DATA_BUFFER_H
#define _DATA_BUFFER_H


#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */


#include "error_system.h"                         
#include "custom_math.h"                               
#include "pid.h"
#include "can_communication_protocol2.h"          


#define H2_PRESSURE_ADVANCE_SET_VALUE           5
#define H2_PRESSURE_PID1_ADVANCE_TIME           250
#define H2_PRESSURE_PID2_ADVANCE_TIME           200

#define H2_PRESSURE_ALARM_VALUE_95          95

#define H2_PRESSURE_SET_VALUE_50            50
#define H2_PRESSURE_SET_VALUE_55            55
#define H2_PRESSURE_SET_VALUE_60            60
#define H2_PRESSURE_SET_VALUE_65            65
#define H2_PRESSURE_SET_VALUE_70            70
#define H2_PRESSURE_SET_VALUE_75            75

#define H2_CIRCULATING_PUMP_SPEED_SETPOINT_1000         1000
#define H2_CIRCULATING_PUMP_SPEED_SETPOINT_1500         1500
#define H2_CIRCULATING_PUMP_SPEED_SETPOINT_2000         2000
#define H2_CIRCULATING_PUMP_SPEED_SETPOINT_3000         3000

#define AIR_COMPRESSOR_SPEED_SETPOINT_20000            20000
#define AIR_COMPRESSOR_SPEED_SETPOINT_35000            35000
#define AIR_COMPRESSOR_SPEED_SETPOINT_45000            45000
#define AIR_COMPRESSOR_SPEED_SETPOINT_55000            55000
#define AIR_COMPRESSOR_SPEED_SETPOINT_60000            60000
#define AIR_COMPRESSOR_SPEED_SETPOINT_65000            65000
#define AIR_COMPRESSOR_SPEED_SETPOINT_70000            70000
#define AIR_COMPRESSOR_SPEED_SETPOINT_73000            73000
#define AIR_COMPRESSOR_SPEED_SETPOINT_75000            75000

#define H2_OUTLET_VALVE_OPEN_TIME_500         500
#define H2_OUTLET_VALVE_OPEN_TIME_800         800
#define H2_OUTLET_VALVE_OPEN_TIME_1000       1000
#define H2_OUTLET_VALVE_OPEN_TIME_1500       1500
#define H2_OUTLET_VALVE_OPEN_TIME_2000       2000

#define H2_OUTLET_VALVE_CLOSE_TIME_1000      1000
#define H2_OUTLET_VALVE_CLOSE_TIME_4000      4000
#define H2_OUTLET_VALVE_CLOSE_TIME_5000      5000
#define H2_OUTLET_VALVE_CLOSE_TIME_6000      6000

#define AIR_OUTLET_VALVE_OPEN_TIME_500        500
#define AIR_OUTLET_VALVE_CLOSE_TIME_8000     8000


#define  PID1_KP  0.3
#define  PID1_KI  0.00001
#define  PID1_KD  170

#define  PID2_KP  0.3
#define  PID2_KI  0.00001
#define  PID2_KD  100  

#define  PID_COMPRESSOR_KP  0.5
#define  PID_COMPRESSOR_KI  0.00001
#define  PID_COMPRESSOR_KD  5

#define  PID_WATER_KP  100
#define  PID_WATER_KI  0
#define  PID_WATER_KD  1000

//����Ũ�ȹ������ֵ
#define  H2_CONCENTRATION_OVER_MAX  1
//ͨ��״̬
typedef enum Working_Communication_Status
{
	working_communication_outage = 0,		//ͨ���ж�
	working_communication_normal = 1,						//����
}Working_Communication_Status;




                                         

//�������ݲ�
typedef struct H2_Data_Buffer
{
	//����
	float	h2_pressure_proportional_valve_front;	//������ǰ��ѹ��fcuϵͳ��H2�����ڣ�		����4-20mA
	float	h2_pressure_proportional_valve_rear;	//����������ѹ��                		����4-20mA
	float	h2_pressure_pile_inlet;	                //�����ѹ���ǵ�ѵ�H2���          	����4-20mA	
	float	h2_pressure_pile_inlet1;	            //�����ѹ���ǵ�ѵ�H2���          	����4-20mA	
	float	h2_pressure_pile_inlet2;	            //�����ѹ���ǵ�ѵ�H2���          	����4-20mA	
	float	h2_pressure_pile_outlet1;	            //������ѹ���ǵ�ѵ�H2����          	����4-20mA	
	float	h2_pressure_pile_outlet2;	            //������ѹ���ǵ�ѵ�H2����          	����4-20mA	
	float	h2_pressure_tail_outlet;				//����β�ŵ�ѹ��,Ҳ�ǵ��H2����ѹ��		����4-20mA
	float	h2_concentration;						//����Ũ��								����pwm���ɼ����ں�ռ�ձ�
	float	h2_humidity;					 		//����ʪ��

	float   h2_temperature_tail_outlet;             //���β�������¶�                      ����ntc����	
	float   h2_temperature_pile_inlet;              //�����������¶�                      ����ntc����

	//���
	u8		h2_inlet_valve;							//������������							���0��1
	u8		h2_outlet_valve;						//����β�ŷ���							���0��1
	float	h2_proportional_valve_pwm_dutyfactor;	//������PWMռ�ձȣ�pid�Զ����ơ�		���pwm 0~5V  Ƶ��>1000HZ
	u8		h2_circulating_pump_enble;				//����ѭ���õ�IOʹ��					���0��1

	//����ѭ����ת���趨  �ٷֱ�	�����澯֮�󣬽���ʹ�õ�
	float	h2_circulating_pump_speed_setpoint_percent;             //����ѭ����ת���趨   �ٷֱ�
	//����ѭ����  canͨ��
	enum 	Working_Communication_Status		h2_circulating_pump_working_communication_status;	//����ѭ����  canͨ��״̬
	float   h2_circulating_pump_mass_flow_setpoint;         //����ѭ���������趨            ���can
	u16     h2_circulating_pump_speed_setpoint;             //����ѭ����ת���趨            ���can
	u8      h2_circulating_pump_enable_pump;                //����ѭ����ʹ��                ���can
	u8      h2_circulating_pump_enable_mass_flow_govemor;   //����ѭ�����������ʹ��        ���can

	float	h2_circulating_pump_actual_mass_flow;        		//  ����ѭ������������      ����can
	float	h2_circulating_pump_actual_speed;        			//  ����ѭ����ʵ��ת��      ����can
	float	h2_circulating_pump_actual_current;        			//  ����ѭ���õ���          ����can
	float	h2_circulating_pump_actual_voltage;        			//  ����ѭ���õ�ѹ          ����can
	i16		h2_circulating_pump_actual_electronic_temperature;  //  ����ѭ���õ���¶�      ����can
	i16		h2_circulating_pump_actual_air_temperature;        	//  ����ѭ���������¶�      ����can
	u8	    h2_circulating_pump_status_diagnose_word;        	//  ����ѭ����״̬����ֽ�  ����can

	//pid����
	float   h2_pressure_target_value;               //��ѹ �趨Ŀ��ֵ
	float   h2_pressure_real_target_value;          //��ѹ ʵ��Ŀ��ֵ
	float   h2_pressure_advance_current_value;      //��ѹ ��ǰ��  ʵ��ֵ
	float   h2_pressure_advance_set_value;          //��ѹ ��ǰ��  �趨ֵ  Ĭ��Ϊ0��һ����Ϊ5
	u32     h2_pressure_pid1_advance_time;          //pid1ʱ����ǰ��      Ĭ��250ms
	u32     h2_pressure_pid2_advance_time;          //pid2ʱ����ǰ��      Ĭ��1000ms		
	PID		h2_proportional_valve_pid1;				//��������pid1
	PID		h2_proportional_valve_pid2;				//��������pid2
	u8		h2_pid_mode ;   						//pid�㷨����ģʽ��1��ʾʹ��pid1�����ƣ�2��ʾʹ��pid2������
	//����β�ſ���
	u8		h2_is_enable_outlet_valve;				//����β�ŷ����Զ����Ƶ�ʹ�ܿ���
	u32		h2_outlet_valve_current_time ;	    	//����β�ŷ���ǰ��ʱ��
	u32		h2_outlet_valve_open_time ;				//����β�ŷ�������ʱ��
	u32		h2_outlet_valve_close_time ;			//����β�ŷ��رյ�ʱ��
	//��ѹ����
	u8      h2_pressure_fluctuate_reset;            //��ѹ ����  ����
	float   h2_pressure_fluctuate_current_max;      //��ѹ ����  ��ǰ���ֵ
	float   h2_pressure_fluctuate_current_min;      //��ѹ ����  ��ǰ��Сֵ
	float   h2_pressure_fluctuate_last_max;		    //��ѹ ����  �ϴ����ֵ
	float   h2_pressure_fluctuate_last_min;			//��ѹ ����  �ϴ���Сֵ
}H2_Data_Buffer;


//�������ݲ�
typedef struct Air_Data_Buffer
{
	u32		air_temperature_pile_inlet_duration_time;//����¶ȳ���75�ȵĳ���ʱ�䣨����20s����һ�����ϣ�
	//����
	float	air_pressure_pile_inlet;				//�����ڷ�ѹ							����4-20mA
	float	air_pressure_pile_outlet;				//��ѳ��ڷ�ѹ							����4-20mA
	float	air_pressure_pile_back;					//��ѳ��ڱ�ѹ							����4-20mA
	float	air_temperature_pile_inlet;				//�����ڷ���							�������ֵ
	float	air_temperature_pile_outlet;			//��ѳ��ڷ���							�������ֵ
	float	air_temperature_pile_back;				//��ѳ��ڱ�ѹ�¶�						�������ֵ
	float	air_temperature_humidifier;				//��ʪ����ڷ���						�������ֵ
	float	air_rate_of_flow;						//��������								����0~5V
	float	air_humidity;							//����ʪ��                              0-70000   
	
    float	air_temperature_humidifier_front;        //��ʪ��ǰ�����¶�                  	�������ֵ    

	//���
	u8		air_outlet_valve;						//������β�ŷ���						���0��1


	u32		air_compressor_speed_setpoint_increment;//��ѹ��ת�٣����Ʊ�Ƶ��������
	//��ѹ��  can
	enum 	Working_Communication_Status		air_compressor_working_communication_status;		//��ѹ��  canͨ��״̬
	u8      air_compressor_enable;                  //��ѹ������	                        ���can
	u32		air_compressor_speed_setpoint;		    //��ѹ��ת�٣����Ʊ�Ƶ����				���can��

	u8		air_compressor_input_electricity;		//��ѹ����Ƶ���������
	u16		air_compressor_input_voltage;			//��ѹ����Ƶ�������ѹ
	u16		air_compressor_output_power;			//��ѹ���������
	i16		air_compressor_motor_temperature;       //��ѹ������¶�
	i16		air_compressor_converter_temperature;   //��ѹ���������¶�
	i16		air_compressor_inside_temperature;		//��ѹ���ڲ��¶�
	u8		air_compressor_state;					//��ѹ��״̬
	u16		air_compressor_fault_code;				//��ѹ��������
	u8		air_compressor_fault_level;				//��ѹ�����ϵȼ�
	u32		air_compressor_act_speed;				//��ѹ��ʵ��ת��
	
	
	//20181112�����շ빤��Ҫ���ڴ����ӣ����ݿ������������ƿ�ѹ����ת�٣�Ŀǰʹ��pid���ڡ�
	PID     air_compressor_speed_pid;               //��ѹ����pid����
	float   air_rate_of_flow_target;                //����������Ŀ��ֵ

	//����β�ſ���
	u8		air_is_enable_outlet_valve;				//����β�ŷ����Զ����Ƶ�ʹ�ܿ���
	u32		air_outlet_valve_current_time ;	    	//����β�ŷ���ǰ��ʱ��
	u32		air_outlet_valve_open_time ;			//����β�ŷ�������ʱ��
	u32		air_outlet_valve_close_time ;			//����β�ŷ��رյ�ʱ��	
}Air_Data_Buffer;


//���ɢ��ϵͳ ���ݲ�
typedef struct Water_For_Pile_Data_Buffer
{
	//����
	float	water_pressure_pile_inlet1;				//������ˮѹ							����4-20mA
	float	water_pressure_pile_outlet1;				//��ѳ���ˮѹ							����4-20mA
	float	water_temperature_pile_inlet1;			//������ˮ��							�������ֵ
	float	water_temperature_pile_outlet1;			//��ѳ���ˮ��							�������ֵ

	float	water_pressure_pile_inlet2;				//������ˮѹ							����4-20mA
	float	water_pressure_pile_outlet2;				//��ѳ���ˮѹ							����4-20mA
	float	water_temperature_pile_inlet2;			//������ˮ��							�������ֵ
	float	water_temperature_pile_outlet2;			//��ѳ���ˮ��							�������ֵ

	u8		water_pump_feedback1;					//ˮ�õķ����ź�	1������           0���쳣	
	u8		water_pump_feedback2;					//ˮ�õķ����ź�	1������           0���쳣
	u8		water_fan_feedback1;					//����1�ķ����ź�	1������           0���쳣
	u8		water_fan_feedback2;					//����2�ķ����ź�	1������           0���쳣
	u8		water_position;							//ɢ��ˮ���Һλ	1����⵽Һ��     0��û��Һ��			

	//���
	float	water_pump_pwm_dutyfactor1;				//ˮ��1PWMռ�ձ�						���pwm 0~24V 
	float	water_pump_pwm_dutyfactor2;				//ˮ��2PWMռ�ձ�						���pwm 0~24V 
	float	water_fan_pwm_dutyfactor1;				//����1PWMռ�ձ�						���pwm 0~24V 
	float	water_fan_pwm_dutyfactor2;				//����2PWMռ�ձ�						���pwm 0~24V 
	
	//���� ���ˮ�ºͷ��ȵ�pid����
	PID     water_temperature_fan_pid1;              //ˮ�ºͷ��ȵ�pid����
	PID     water_temperature_fan_pid2;              //ˮ�ºͷ��ȵ�pid����
	float   water_temperature_target_value1;         //������ˮ�� Ŀ��ֵ
	float   water_temperature_target_value2;         //������ˮ�� Ŀ��ֵ

}Water_For_Pile_Data_Buffer;


//����һɢ��ϵͳ ���ݲ㣨��ѹ������Ƶ���������������������ڿ������ǰ���ͷ���
typedef struct Water_For_Compressor_Data_Buffer
{
	//����
	float	water_pressure_compressor_outlet;		//��ѹ������ˮѹ						����4-20mA
	float	water_pressure_frequency_outlet;		//��Ƶ������ˮѹ						����4-20mA
	float	water_pressure_intercooler_outlet;		//����������ˮѹ						����4-20mA
	float	water_pressure_pump_outlet;		    	//����һˮ�ó���ˮѹ			    	����4-20mA
	float	water_temperature_compressor_outlet;	//��ѹ������ˮ��						�������ֵ
	float	water_temperature_compressor_shell;		//��ѹ�������¶�						�������ֵ
	float	water_temperature_frequency_outlet;		//��Ƶ������ˮ��						�������ֵ
	float	water_temperature_intercooler_outlet;	//����������ˮ��						�������ֵ
	float	water_temperature_pump_outlet;			//����һˮ�ó���ˮ��					�������ֵ
		
	u8		water_fan_feedback;						//���ȵķ����ź�	1������           0���쳣
	u8		water_position;							//ɢ��ˮ���Һλ	1����⵽Һ��     0��û��Һ��


	//���
	u8		water_pump_enable;						//ˮ�õ�ʹ��							���0��1
	float	water_pump_pwm_dutyfactor;				//ˮ��PWMռ�ձ�							���pwm 0~24V 
	float	water_fan_pwm_dutyfactor;				//����PWMռ�ձ�							���pwm 0~24V 
	
	//���� ���ˮ�ºͷ��ȵ�pid����
	PID     water_temperature_fan_pid;              //ˮ�ºͷ��ȵ�pid����
	float   water_temperature_target_value;         //������ˮ�� Ŀ��ֵ
	
}Water_For_Compressor_Data_Buffer;


//��ѵ�ѹ��·�޶�ֵ  230V   ˫��130*2Ƭ��ʵ����260V���ң�
#define  GALVANIC_PILE_OPEN_CIRCUIT_VOLTAGE		230.0f  

//Ѳ�쵥Ƭ��ѹ��·�޶�ֵ  150V
#define  ITINERANT_DETECTIVE_OPEN_CIRCUIT_SINGLE_VOLTAGE		0.85f

//��ѷ�������ݲ�
typedef struct Galvanic_Pile_Data_Buffer
{
	//����
	float	galvanic_pile_voltage;					//��ѵĵ�ѹ							����0~5V
	float	galvanic_pile_electricity;				//��ѵĵ���							����0~5V
	u8		fcu_start_enable;						//��ѵ�����ʹ��1�������ź���Ч   0�������ź���Ч	
	u8		fcu_stutter_stop_enable;				//��ѵļ�ͣʹ��1����ͣ�ź���Ч   0����ͣ�ź���Ч
	u8		fcu_reset_enable;						//��ѵĸ�λʹ��1�������ź���Ч   0�������ź���Ч	

	//���
	u8		galvanic_pile_is_enble_output;			//�������Ӵ���						���0��1
	u8		galvanic_pile_is_enble_load_resistance;	//��Ѹ��ص���Ӵ���					���0��1

	//Ѳ��  can
	enum 	Working_Communication_Status		itinerant_detective_working_communication_status;	//Ѳ��  canͨ��ģʽ
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
	
	//Ѳ��  can
	enum 	Working_Communication_Status		itinerant_detective_working_communication_status2;	//Ѳ��  canͨ��ģʽ
	u8		itinerant_detective_working_statas2;		//Ѳ������״̬
	u8		Single_battery_overvoltage_alarm2;		//�����ع�ѹ����
	u8		Single_battery_undervoltage_alarm2;		//������Ƿѹ����
	u8		Single_voltage_unbalance_alarm2;			//�����ز�������
	float   electric1_mean_voltage2;					//���1ƽ����ѹ
	float 	electric1_single_chip_highest_voltage2;	//���1��Ƭ��ߵ�ѹ
	u16		electric1_single_chip_highest_voltage_num2;	//���1��Ƭ��ߵ�ѹ���
	float 	electric1_single_chip_minimum_voltage2;	//���1��͵�ѹ
	u16     electric1_single_chip_minimum_voltage_num2; //���1��͵�ѹ���
	float	itinerant_detective_total_voltage2;		//Ѳ���ܵ�ѹ					

    //��Եģ�� canͨ������
	enum 	Working_Communication_Status		insulation_monitor_working_communication_status;	//��Եģ��  canͨ��ģʽ    
	u8    insulation_monitor_fault_level;           //��Եģ����ϵȼ�
	u8    insulation_monitor_error_code	;			//��Եģ�������
	u16   insulation_resistance_value;              //��Ե����ֵ
	u16   insulation_battery_voltage;               //��Եģ���ص�ѹ

}Galvanic_Pile_Data_Buffer;



//fcu���� ���ݲ�
typedef struct FCU_Data_Buffer
{                                 
	enum ISlock                                  islock;      //���ݱ�����

	struct H2_Data_Buffer						h2_data_buffer;							//�������ݲ�
	struct Air_Data_Buffer						air_data_buffer;						//�������ݲ�
	struct Water_For_Pile_Data_Buffer			water_for_pile_data_buffer;				//���ɢ��ϵͳ ���ݲ�
	struct Water_For_Compressor_Data_Buffer		water_for_compressor_data_bufferr;		//����һɢ��ϵͳ ���ݲ�
	struct Galvanic_Pile_Data_Buffer			galvanic_pile_data_buffer;				//��ѷ�������ݲ�
}FCU_Data_Buffer;


extern struct FCU_Data_Buffer		fcu_data_buffer   ;

//fcu���ݻ������ݳ�ʼ��
void FCU_data_buffer_init(void);

//ͨ��ͨ��  ��������  ��ѹ��������ѭ����
void FCU_data_buffer_updata_by_communication(void);


#endif

