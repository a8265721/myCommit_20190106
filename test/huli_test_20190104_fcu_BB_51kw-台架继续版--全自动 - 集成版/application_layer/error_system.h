/*
error_system ��ģ���Ǵ�����Ĵ���
�÷�������ģ��ֱ�Ӱ�����ģ�飬Ȼ����Ϊ�����ķ���ֵ��
�ϲ�ͨ���������������жϺ�����ִ�������
*/ 
//-----------------------------------------------------------------------------------------------

#ifndef __ERROR_SYSTEM_H       
#define __ERROR_SYSTEM_H	              
//#include "sys.h"
#include "stdlib.h"                    
#include "stdio.h"          
                                                        

/* exact-width signed integer types */
typedef   signed char		int8_t;                 
typedef   signed short      int16_t;
typedef   signed long		int32_t;


/* exact-width unsigned integer types */
typedef unsigned char		uint8_t;
typedef unsigned short		uint16_t;
typedef unsigned long		uint32_t;

/* exact-width signed integer types */
typedef   signed char		int8_T;
typedef   signed short      int16_T;
typedef   signed long		int32_T;


/* exact-width unsigned integer types */
typedef unsigned char		uint8_T;
typedef unsigned short		uint16_T;
typedef unsigned long		uint32_T;

typedef int32_t		i32;
typedef int16_t		i16;
typedef int8_t		i8;

typedef uint32_t	u32;
typedef uint16_t	u16;
typedef uint8_t		u8;

typedef enum ISlock
{
	unlock = 0,
	lock = 1,
}ISlock;


#define ERROR_STRING_LENGTH		256		//��������ı�˵���ַ�������


enum IsAbled
{
	Enabled =1,
	Unabled =0,
};


//�������ö�٣������Ҫ���������룬ֱ������·��ö����׷��
enum Error_code
{
	Succeed = 0,					//�ɹ�

	//��ͨ����
	Failed = 1,						//ʧ��
	Partial_success = 2, 			//���ֳɹ�
	Warning = 3,					//����
	Error = 4,						//����

	//�����Ż�����澯ʱ����ʹ��
	NoData = 5,						//û�����ݣ�����˵��ѯ������߻��棬�������û����Ҫ��������ݣ�


	//ָ����ڴ���󣬺Ͳ��������ݲ�����
	Pointer_is_null = 100, 			//��ָ��
	Parameter_error = 101,			//��������
	Pointer_malloc_fail = 103,		//ָ���ֶ������ڴ����


	//can�ײ�ģ��
	CAN_length_error = 201,		//can���ȴ���
	CAN_out_synchronization = 202,	//can��ͬ��
	CAN_receive_flag_error = 203,	//���ܱ�־λ����


	//canͨ��ģ��
	CAN_send_overtime = 301,		//CAN������Ϣ��ʱ
	CAN_receive_overtime = 302,	//CAN������Ϣ��ʱ
	CAN_receive_nothing = 303,		//�����¼�����ɹ�������û�н��ܵ���Ϣ��//warning
	CAN_data_analysis_id_error = 310,//���ݽ�����id��ƥ��
	CAN_data_analysis_data_error = 311,//���ݽ��������ݲ�ƥ��
	CAN_data_invalid_data_error =312,  // ��Ч����


	//MODBUSͨ��ģ��
	MODBUS_send_overtime = 401,		//MODBUS������Ϣ��ʱ
	MODBUS_receive_overtime = 402,	//MODBUS������Ϣ��ʱ
	MODBUS_receive_nothing = 403,		//�����¼�����ɹ�������û�н��ܵ���Ϣ��//warning
	MODBUS_data_analysis_id_error = 410,//���ݽ�����id��ƥ��
	MODBUS_data_analysis_data_error = 411,//���ݽ��������ݲ�ƥ��
	MODBUS_data_invalid_data_error =412,  // ��Ч����
	MODBUS_receive_wait_for_reply =413,  // �ȴ���

	//adת��
	ATDX_conversion_number_error = 501,		//ad�ɼ���ͨ������







	//fcuϵͳ������
	//	Check1_overtime_error1,		//�Լ�1����ʱ��һ�����ϣ�                                            


	//��������
	H2_pressure_proportional_valve_front_over_error1			 = 0x1101,//4353		//������ǰ��ѹ	��ѹ��һ�����ϣ�
	H2_pressure_proportional_valve_front_over_error3			 = 0x1103,//4355		//������ǰ��ѹ	��ѹ��3�����ϣ�
	H2_pressure_proportional_valve_front_under_error1			 = 0x1104,//4356		//������ǰ��ѹ	Ƿѹ��һ�����ϣ�
	H2_pressure_proportional_valve_front_under_error3			 = 0x1106,//4358		//������ǰ��ѹ	Ƿѹ��3�����ϣ�
	H2_pressure_proportional_valve_front_atd_error1				 = 0x110a,//4362		//������ǰ��ѹ	ad�����쳣��һ�����ϣ�

	H2_pressure_proportional_valve_rear_over_error1				 = 0x1201,//4609		//����������ѹ  ��ѹ��һ�����ϣ�
	H2_pressure_proportional_valve_rear_over_error3				 = 0x1203,//4611		//����������ѹ  ��ѹ��3�����ϣ�
	H2_pressure_proportional_valve_rear_under_error1			 = 0x1204,//4612		//����������ѹ  Ƿѹ��һ�����ϣ�
	H2_pressure_proportional_valve_rear_under_error3			 = 0x1206,//4614		//����������ѹ  Ƿѹ��3�����ϣ�
	H2_pressure_proportional_valve_rear_atd_error1				 = 0x120a,//4618		//����������ѹ	ad�����쳣��һ�����ϣ�
	H2_pressure_proportional_valve_rear_unstable_error1			 = 0x120b,//4619		//����������ѹ	ѹ�����ȣ�һ�����ϣ�
	H2_pressure_no_fluctuations_error1							 = 0x120c,//4620		//����ѹ��û�в�����������β�ŷ����ϣ�һ�����ϣ�

	H2_pressure_pile_inlet_over_error1							 = 0x1301,//4865		//�����ѹ  ��ѹ��һ�����ϣ�
	H2_pressure_pile_inlet_over_error3							 = 0x1303,//4867		//�����ѹ  ��ѹ��3�����ϣ�
	H2_pressure_pile_inlet_under_error1							 = 0x1304,//4868		//�����ѹ  Ƿѹ��һ�����ϣ�
	H2_pressure_pile_inlet_under_error3							 = 0x1306,//4870		//�����ѹ  Ƿѹ��3�����ϣ�
	H2_pressure_pile_inlet_atd_error1							 = 0x130a,//4874		//�����ѹ	ad�����쳣��һ�����ϣ�
	H2_pressure_pile_inlet_unstable_error1						 = 0x130b,//4875		//�����ѹ	ѹ�����ȣ�һ�����ϣ�
	H2_pressure_pile_inlet_no_follow_error3						 = 0x130c,//4876		//�����ѹ  û�и������������ѹ��3�����ϣ�

	H2_pressure_pile_outlet_atd_error1							 = 0x140a,//5130		//������ѹ	ad�����쳣��һ�����ϣ�
	H2_pressure_pile_outlet_unstable_error1						 = 0x140b,//5131		//������ѹ	ѹ�����ȣ�һ�����ϣ�
	H2_pressure_pile_outlet_no_follow_error3					 = 0x140c,//5132		//������ѹ	û�и������������ѹ��3�����ϣ�

	H2_pressure_tail_outlet_atd_error1							 = 0x150a,//5386		//����β�ŵ�ѹ��	ad�����쳣��һ�����ϣ�
	H2_pressure_tail_outlet_unstable_error1						 = 0x150b,//5387		//β����ѹ	ѹ�����ȣ�һ�����ϣ�
	H2_pressure_tail_outlet_no_follow_error3					 = 0x150c,//5388		//β����ѹ	û�и������������ѹ��3�����ϣ�
	//	H2_pressure_tail_outlet_under_error3 ,		//β����ѹ  Ƿѹ��3�����ϣ�

	H2_proportional_valve_statas_error1							 = 0x1601,//5633		//������״̬���ϣ�һ�����ϣ�

	H2_outlet_valve_control_error1								 = 0x1701,//5889		//β�ŷ����ƹ��ϣ�һ�����ϣ�
	
	//����Ũ�ȼ���ad����    
	H2_concentration_over_error1						       	 = 0x1801,//6145		//����Ũ�ȼ��  Ũ�ȹ��ߣ�һ�����ϣ�
    H2_concentration_atd_error1                                  = 0x180a,//6154		//����Ũ�ȼ��	ad�����쳣��һ�����ϣ�
    
    //��������¶�
	H2_temperature_pile_inlet_over_error1						 = 0x1901,//6401		//�������  ���£�һ�����ϣ�
	H2_temperature_pile_inlet_over_error3						 = 0x1903,//6403		//�������  ���£�3�����ϣ�
	H2_temperature_pile_inlet_under_error1						 = 0x1904,//6404		//�������	Ƿ�£�һ�����ϣ�
	H2_temperature_pile_inlet_under_error3						 = 0x1906,//6406		//�������	Ƿ�£�3�����ϣ�
	H2_temperature_pile_inlet_atd_error1						 = 0x190a,//6410		//����������	ad�����쳣��һ�����ϣ�
	 
	//����ѭ����
	H2_circulating_pump_communication_error1					 = 0x1a0a,//6666		//����ѭ����  canͨ�Ź��ϣ�һ�����ϣ�
	H2_circulating_pump_low_voltage_power_error1				 = 0x1a0b,//6667		//����ѭ���õ�  24V��ѹ��Դ���ϡ���һ�����ϣ�
	H2_circulating_pump_working_statas_error1					 = 0x1a0c,//6668		//����ѭ���ù���״̬���ϣ�һ�����ϣ�
	H2_circulating_pump_actual_speed_error1						 = 0x1a0d,//6669		//����ѭ���� ʵ��ת�ٹ��ϣ�һ�����ϣ�
	H2_circulating_pump_temperature_over_error1					 = 0x1a11,//6673		//����ѭ���� �¶ȹ��ߣ�һ�����ϣ�
	H2_circulating_pump_temperature_over_error2					 = 0x1a12,//6674		//����ѭ���� �¶ȹ��ߣ�2�����ϣ�//����ѭ���� ����50%
	H2_circulating_pump_temperature_under_error1				 = 0x1a14,//6676		//����ѭ���� �¶ȹ��ͣ�һ�����ϣ�
	H2_circulating_pump_temperature_under_error3				 = 0x1a16,//6678		//����ѭ���� �¶ȹ��ͣ�3�����ϣ�






	//��������
	Air_pressure_pile_inlet_over_error1							 = 0x2101,//8449		//��ѷ�ѹ  ��ѹ��һ�����ϣ�
	Air_pressure_pile_inlet_over_error3							 = 0x2103,//8451		//��ѷ�ѹ  ��ѹ��3�����ϣ�
	Air_pressure_pile_inlet_under_error1						 = 0x2104,//8452		//��ѷ�ѹ	Ƿѹ��һ�����ϣ�
	Air_pressure_pile_inlet_under_error2						 = 0x2105,//8453		//��ѷ�ѹ	Ƿѹ��2�����ϣ�	//��ѹ�� ����10000
	Air_pressure_pile_inlet_atd_error1							 = 0x210a,//8458		//�����ڷ�ѹ	ad�����쳣��һ�����ϣ�

	Air_pressure_pile_outlet_over_error3						 = 0x2203,//8707		//���ѷ�ѹ  ��ѹ��3�����ϣ�
	Air_pressure_pile_outlet_atd_error1 						 = 0x220a,//8714		//��ѳ��ڷ�ѹ	ad�����쳣��һ�����ϣ�

	Air_pressure_pile_back_over_error3							 = 0x2303,//8963		//���ڱ�ѹ  ��ѹ��3�����ϣ�
	Air_pressure_pile_back_atd_error1							 = 0x230a,//8970		//��ѳ��ڱ�ѹ	ad�����쳣��һ�����ϣ�	

	Air_temperature_pile_inlet_over_error1						 = 0x2401,//9217		//��ѷ���  ���£�һ�����ϣ�
	Air_temperature_pile_inlet_over_error3						 = 0x2403,//9219		//��ѷ���  ���£�3�����ϣ�
	Air_temperature_pile_inlet_under_error1						 = 0x2404,//9220		//��ѷ���	Ƿ�£�һ�����ϣ�
	Air_temperature_pile_inlet_under_error3						 = 0x2406,//9222		//��ѷ���	Ƿ�£�3�����ϣ�
	Air_temperature_pile_inlet_atd_error1						 = 0x240a,//9226		//�����ڷ���	ad�����쳣��һ�����ϣ�

	Air_temperature_pile_outlet_over_error3						 = 0x2503,//9475		//���ѷ���  ���£�3�����ϣ�
	Air_temperature_pile_outlet_atd_error1						 = 0x250a,//9482		//��ѳ��ڷ���	ad�����쳣��һ�����ϣ�

	Air_temperature_pile_back_over_error3						 = 0x2603,//9731		//���ڱ���  ���£�3�����ϣ�
	Air_temperature_pile_back_atd_error1						 = 0x260a,//9738		//��ѳ��ڱ�ѹ�¶�	ad�����쳣��һ�����ϣ�

	Air_rate_of_flow_under_error1								 = 0x2704,//9988		//�����������ͣ�һ�����ϣ�
	Air_rate_of_flow_atd_error1 								 = 0x270a,//9994		//��������	ad�����쳣��һ�����ϣ�
    
    //��ʪ��ǰ�Ŀ����¶�	
    Air_temperature_humidifier_front_over_error1				 = 0x2801,//10241		//��ʪ��ǰ�Ŀ����¶�    ���£�һ�����ϣ�
	Air_temperature_humidifier_front_over_error3				 = 0x2803,//10243		//��ʪ��ǰ�Ŀ����¶�    ���£�3�����ϣ�
	Air_temperature_humidifier_front_under_error1				 = 0x2804,//10244		//��ʪ��ǰ�Ŀ����¶�    Ƿ�£�һ�����ϣ�
	Air_temperature_humidifier_front_under_error3				 = 0x2806,//10246		//��ʪ��ǰ�Ŀ����¶�	Ƿ�£�3�����ϣ�
	Air_temperature_humidifier_front_atd_error1					 = 0x280a,//10250		//��ʪ��ǰ�Ŀ����¶�	ad�����쳣��һ�����ϣ�
	
	//��ѹ��
	Air_compressor_communication_error1							 = 0x2a0a,//10762		//��ѹ��  canͨ�Ź��ϣ�һ�����ϣ�
	Air_compressor_working_statas_error1						 = 0x2a0b,//10763		//��ѹ������״̬���ϣ�һ�����ϣ�
	Air_compressor_act_speed_error1								 = 0x2a0c,//10764		//��ѹ�� ʵ��ת�ٹ��ϣ�һ�����ϣ�
    Air_compressor_input_voltage_power_error1                    = 0x2a0d,//10765       //��ѹ�� �����ѹ���ϣ�һ�����ϣ�
	Air_compressor_temperature_over_error1						 = 0x2a11,//10769		//��ѹ�� �¶ȹ��ߣ�һ�����ϣ�
	Air_compressor_temperature_over_error2						 = 0x2a12,//10770		//��ѹ�� �¶ȹ��ߣ�2�����ϣ�
	Air_compressor_temperature_over_error3						 = 0x2a13,//10771		//��ѹ�� �¶ȹ��ߣ�3�����ϣ�
	Air_compressor_temperature_under_error1						 = 0x2a14,//10772		//��ѹ�� �¶ȹ��ͣ�һ�����ϣ�
	Air_compressor_temperature_under_error2						 = 0x2a15,//10773		//��ѹ�� �¶ȹ��ͣ�2�����ϣ�
	Air_compressor_temperature_under_error3						 = 0x2a16,//10774		//��ѹ�� �¶ȹ��ͣ�3�����ϣ�








	//���ɢ��ϵͳ 
	Water_pressure_pile_inlet_over_error1							 = 0x3101,//12545		//������ˮѹ  ��ѹ��һ�����ϣ�
	Water_pressure_pile_inlet_under_error1							 = 0x3104,//12548		//������ˮѹ  Ƿѹ��һ�����ϣ�
	Water_pressure_pile_inlet_atd_error1							 = 0x310a,//12554		//������ˮѹ	ad�����쳣��һ�����ϣ�

	Water_pressure_pile_outlet_over_error1							 = 0x3201,//12801		//��ѳ���ˮѹ  ��ѹ��һ�����ϣ�
	Water_pressure_pile_outlet_under_error1							 = 0x3204,//12804		//��ѳ���ˮѹ  Ƿѹ��һ�����ϣ�
	Water_pressure_pile_outlet_atd_error1							 = 0x320a,//12810		//��ѳ���ˮѹ	ad�����쳣��һ�����ϣ�

	Water_pressure_differential_pile_inlet_and_outlet_over_error1	 = 0x3301,//13057		//�����ںͳ��ڵ�ˮѹ��  ��ѹ��һ�����ϣ�
	Water_pressure_differential_pile_inlet_and_outlet_under_error1	 = 0x3304,//13060		//�����ںͳ��ڵ�ˮѹ��  Ƿѹ��һ�����ϣ�

	Water_temperature_pile_inlet_over_error1						 = 0x3401,//13313		//������ˮ��  ���£�һ�����ϣ�
	Water_temperature_pile_inlet_over_error3						 = 0x3403,//13315		//������ˮ��  ���£�3�����ϣ�
	Water_temperature_pile_inlet_under_error1						 = 0x3404,//13316		//������ˮ��  Ƿ�£�һ�����ϣ�
	Water_temperature_pile_inlet_atd_error1							 = 0x340a,//13322		//������ˮ��	ad�����쳣��һ�����ϣ�

	Water_temperature_pile_outlet_over_error1						 = 0x3501,//13569		//��ѳ���ˮ��  ���£�һ�����ϣ�
	Water_temperature_pile_outlet_over_error3						 = 0x3503,//13571		//��ѳ���ˮ��  ���£�3�����ϣ�
	Water_temperature_pile_outlet_under_error1						 = 0x3504,//13572		//��ѳ���ˮ��  Ƿ�£�һ�����ϣ�
	Water_temperature_pile_outlet_atd_error1						 = 0x350a,//13578		//��ѳ���ˮ��	ad�����쳣��һ�����ϣ�	

	Water_temperature_differential_pile_inlet_and_outlet_over_error1 = 0x3601,//13825		//�����ںͳ��ڵ�ˮ�²�  ���£�һ�����ϣ�
	Water_temperature_differential_pile_inlet_and_outlet_over_error3 = 0x3603,//13827		//�����ںͳ��ڵ�ˮ�²�  ���£�3�����ϣ�
	Water_temperature_differential_pile_inlet_and_outlet_under_error1= 0x3604,//13828		//�����ںͳ��ڵ�ˮ�²�  Ƿ�£�һ�����ϣ�








	//����һɢ��ϵͳ ����
	Water_temperature_compressor_outlet_over_error1				 = 0x4101,//16641		//��ѹ������ˮ��  ���£�һ�����ϣ�
	Water_temperature_compressor_outlet_over_error3				 = 0x4103,//16643		//��ѹ������ˮ��  ���£�3�����ϣ�
	Water_temperature_compressor_outlet_under_error1			 = 0x4104,//16644		//��ѹ������ˮ��  Ƿ�£�һ�����ϣ�
	Water_temperature_compressor_outlet_under_error3			 = 0x4106,//16646		//��ѹ������ˮ��  Ƿ�£�3�����ϣ�
	Water_temperature_compressor_outlet_atd_error1				 = 0x410a,//16650		//��ѹ������ˮ��	ad�����쳣��һ�����ϣ�

	Water_temperature_pump_outlet_over_error1					 = 0x4201,//16897		//����һˮ�ó���ˮ��  ���£�һ�����ϣ�
	Water_temperature_pump_outlet_over_error3					 = 0x4203,//16899		//����һˮ�ó���ˮ��  ���£�3�����ϣ�
	Water_temperature_pump_outlet_under_error1					 = 0x4204,//16900		//����һˮ�ó���ˮ��  Ƿ�£�һ�����ϣ�
	Water_temperature_pump_outlet_under_error3					 = 0x4206,//16902		//����һˮ�ó���ˮ��  Ƿ�£�3�����ϣ�
	Water_temperature_pump_outlet_atd_error1					 = 0x420a,//16906		//����һˮ�ó���ˮ��	ad�����쳣��һ�����ϣ�

	Water_temperature_compressor_shell_over_error1				 = 0x4301,//17153		//��ѹ�������¶�  ���£�һ�����ϣ�
	Water_temperature_compressor_shell_over_error3				 = 0x4303,//17155		//��ѹ�������¶�  ���£�3�����ϣ�
	Water_temperature_compressor_shell_under_error1				 = 0x4304,//17156		//��ѹ�������¶�  Ƿ�£�һ�����ϣ�
	Water_temperature_compressor_shell_under_error3				 = 0x4306,//17158		//��ѹ�������¶�  Ƿ�£�3�����ϣ�
	Water_temperature_compressor_shell_atd_error1				 = 0x430a,//17162		//��ѹ�������¶�	ad�����쳣��һ�����ϣ�

	Water_pressure_compressor_outlet_under_error1				 = 0x4404,//17412		//��ѹ������ˮѹ	Ƿѹ��һ�����ϣ� 
	Water_pressure_compressor_outlet_atd_error1					 = 0x440a,//17418		//��ѹ������ˮѹ	ad�����쳣��һ�����ϣ�

	Water_temperature_frequency_outlet_over_error1				 = 0x4501,//17665		//��Ƶ������ˮ��  ���£�һ�����ϣ�
	Water_temperature_frequency_outlet_over_error3				 = 0x4503,//17667		//��Ƶ������ˮ��  ���£�3�����ϣ�
	Water_temperature_frequency_outlet_under_error1		    	 = 0x4504,//17668		//��Ƶ������ˮ��  Ƿ�£�һ�����ϣ�
	Water_temperature_frequency_outlet_under_error3	    		 = 0x4506,//17670		//��Ƶ������ˮ��  Ƿ�£�3�����ϣ�
	Water_temperature_frequency_outlet_atd_error1				 = 0x450a,//17674		//��Ƶ������ˮ��	ad�����쳣��һ�����ϣ�

	Water_temperature_intercooler_outlet_over_error1			 = 0x4601,//17921		//����������ˮ��  ���£�һ�����ϣ�
	Water_temperature_intercooler_outlet_over_error3			 = 0x4603,//17923		//����������ˮ��  ���£�3�����ϣ�
	Water_temperature_intercooler_outlet_under_error1			 = 0x4604,//17924		//����������ˮ��  Ƿ�£�һ�����ϣ�
	Water_temperature_intercooler_outlet_under_error3			 = 0x4606,//17926		//����������ˮ��  Ƿ�£�3�����ϣ�
	Water_temperature_intercooler_outlet_atd_error1				 = 0x460a,//17930		//����������ˮ��	ad�����쳣��һ�����ϣ�
	
	Water_pressure_pump_outlet_over_error1				         = 0x4701,//18177		//����һˮ�ó���ˮѹ  ��ѹ��һ�����ϣ�
	Water_pressure_pump_outlet_over_error3				    	 = 0x4703,//18179		//����һˮ�ó���ˮѹ  ��ѹ��3�����ϣ�
	Water_pressure_pump_outlet_under_error1			    		 = 0x4704,//18180		//����һˮ�ó���ˮѹ  Ƿѹ��һ�����ϣ�
	Water_pressure_pump_outlet_under_error3			    		 = 0x4706,//18182		//����һˮ�ó���ˮѹ  Ƿѹ��3�����ϣ�
	Water_pressure_pump_outlet_atd_error1			    		 = 0x470a,//18186		//����һˮ�ó���ˮѹ	ad�����쳣��һ�����ϣ�		
	
	
	
	
	

	//��ѷ��������
	Galvanic_pile_voltage_over_error1							 = 0x5101,//20737		//��ѵ�ѹ  ���ߣ�һ�����ϣ�
	Galvanic_pile_voltage_under_error1							 = 0x5104,//20740		//��ѵ�ѹ  ���ͣ�һ�����ϣ�
	Galvanic_pile_voltage_under_error2							 = 0x5105,//20741		//��ѵ�ѹ  ���ͣ�2�����ϣ�
	Galvanic_pile_voltage_under_error3							 = 0x5106,//20742		//��ѵ�ѹ  ���ͣ�3�����ϣ�
	Galvanic_pile_voltage_atd_error1							 = 0x510a,//20746		//��ѵĵ�ѹ	ad�����쳣��һ�����ϣ�
	Galvanic_pile_voltage_statas_error1							 = 0x510b,//20747		//��ѵ�ѹ��ͣ����ʱ��û�н�Ϊ0��������С����ļ̵������ϣ�һ�����ϣ�

	Galvanic_pile_electricity_over_error1						 = 0x5201,//20993		//��ѵ���  ���ߣ�һ�����ϣ�
	Galvanic_pile_electricity_over_error2						 = 0x5202,//20994		//��ѵ���  ���ߣ�2�����ϣ�
	Galvanic_pile_electricity_over_error3						 = 0x5203,//20995		//��ѵ���  ���ߣ�3�����ϣ�
	Galvanic_pile_electricity_under_error1						 = 0x5204,//20996		//��ѵ���  ���ͣ�һ�����ϣ�
	Galvanic_pile_electricity_atd_error1						 = 0x520a,//21002		//��ѵĵ���	ad�����쳣��һ�����ϣ�
	Galvanic_pile_electricity_statas_error1						 = 0x520b,//21003		//��ѵ���������״̬���ϣ�����������̵������ϣ�һ�����ϣ�

	Galvanic_pile_pressure_differential_h2_and_air_over_error1	 = 0x5301,//21249		//������������ѹ��  ��ѹ��һ�����ϣ�
	Galvanic_pile_pressure_differential_h2_and_air_over_error2	 = 0x5302,//21250		//������������ѹ��  ��ѹ��2�����ϣ�
	Galvanic_pile_pressure_differential_h2_and_air_over_error3	 = 0x5303,//21251		//������������ѹ��  ��ѹ��3�����ϣ�

	//�յ�ͣ��ָ��ʱ����������100A����ʾ�û����ܴ���ͣ��
	Galvanic_pile_electricity_over_when_stop_error1				 = 0x5401,//21505		//�յ�ͣ��ָ��ʱ����������100A����ʾ�û����ܴ���ͣ����һ�����ϣ�
	Galvanic_pile_electricity_over_when_stop_error2				 = 0x5402,//21506		//�յ�ͣ��ָ��ʱ����������100A����ʾ�û����ܴ���ͣ����2�����ϣ�

	//Ѳ��
	Itinerant_detective_communication_error1					 = 0x5a0a,//23050		//Ѳ��  canͨ�Ź��ϣ�һ�����ϣ�
	Itinerant_detective_working_statas_error1					 = 0x5a0b,//23051		//Ѳ�칤��״̬���ϣ�һ�����ϣ�
	Itinerant_detective_working_statas_error2					 = 0x5a0c,//23052		//Ѳ�칤��״̬���ϣ�2�����ϣ�

	Glectric1_single_chip_minimum_voltage_under_error1			 = 0x5a14,//23060		//Ѳ�쵥Ƭ��ѹ���ͣ�һ�����ϣ�
	Glectric1_single_chip_minimum_voltage_under_error2			 = 0x5a15,//23061		//Ѳ�쵥Ƭ��ѹ���ͣ�2�����ϣ�
	Glectric1_single_chip_minimum_voltage_under_error3			 = 0x5a16,//23062		//Ѳ�쵥Ƭ��ѹ���ͣ�3�����ϣ�

    //��Եģ�� canͨ������
    Insulation_monitor_communication_error1                      = 0x5b0a,//23306       //��Եģ��  canͨ�Ź��ϣ�һ�����ϣ�


};


//������Ϣ�Ľṹ�壬�������������ʹ�������ı�˵���ַ���
struct Error_information
{
	enum Error_code error_code;	//������
	char Error_string[ERROR_STRING_LENGTH];		//��������ı�˵���ַ���

};	


//�������ʼ�������Error_information�������������
//p_error_information : ��Ҫ����ʼ����Error_information������ṹ���ָ�롣
void Error_init(struct Error_information * p_error_information);

#endif
