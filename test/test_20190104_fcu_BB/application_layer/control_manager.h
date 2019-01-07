
#ifndef _CONTROL_MANAGER_H                                       
#define _CONTROL_MANAGER_H

#include"data_buff.h"
#include "atd.h"
                                                               
//��ѹ��Դ24V
#define LOW_VOLTAGE_24V		 		24

//�����ѹ�޶�ֵ  ����400
#define  H2_PRESSURE_PROPORTIONAL_VALVE_FRONT_LOWER_LIMIT	400  
//�����ѹ�޶�ֵ  ����600
#define  H2_PRESSURE_PROPORTIONAL_VALVE_FRONT_UPPER_LIMIT	600 



//ϵͳ����ģʽ
typedef enum FCU_System_Running_Mode                              
{
	system_running_manual = 0,				//ȫ�ֶ�
	system_running_semi_auto = 1,			//���Զ�
	system_running_full_auto = 2,			//ȫ�Զ�
	system_running_full_test = 4,			//����
}FCU_System_Running_Mode;

//����ģʽ
typedef enum Working_Control_Mode
{
	working_control_outage = 0,			//�����ж�
	
//	working_control_wait2 = 3,			//���Ƶȴ�2���Ӵ��������е��м���̣�
//	working_control_error = 4,			//����ͣ���ĵȴ�״̬����λ��Ϣ���ɻָ���wait

	working_control_check1 = 11,			//���Ҽ��
	working_control_check2 = 12,			//���Ҽ��

	working_control_wait = 13,				//���Ƶȴ�

	working_control_check3 = 14,			//���Ҽ��

	working_control_start1  = 21,			//��������
	working_control_start2  = 22,			//��������
	working_control_start3  = 23,			//��������
	working_control_start4  = 24,			//��������
	working_control_start5  = 25,			//��������
	working_control_start6  = 26,			//��������
	working_control_start7  = 27,			//��������
	working_control_start8  = 28,			//��������
	working_control_start9  = 29,			//��������
	working_control_start10  = 30,			//��������
	working_control_start11  = 31,			//��������
	working_control_start12  = 32,			//��������
	working_control_start13  = 33,			//��������

	working_control_run = 40,				//��������

	working_control_stop1  = 41,			//����ֹͣ
	working_control_stop2  = 42,			//����ֹͣ
	working_control_stop3  = 43,			//����ֹͣ
	working_control_stop4  = 44,			//����ֹͣ
	working_control_stop5  = 45,			//����ֹͣ
	working_control_stop6  = 46,			//����ֹͣ
	working_control_stop7  = 47,			//����ֹͣ
	working_control_stop8  = 48,			//����ֹͣ
	working_control_stop9  = 49,			//����ֹͣ
	working_control_stop10  = 50,			//����ֹͣ
	working_control_stop11  = 51,			//����ֹͣ
	working_control_stop12  = 52,			//����ֹͣ

	working_control_fault0  = 60,			//����ͣ��
	working_control_fault1  = 61,			//����ͣ��
	working_control_fault2  = 62,			//����ͣ��
	working_control_fault3  = 63,			//����ͣ��
	working_control_fault4  = 64,			//����ͣ��
	working_control_fault5  = 65,			//����ͣ��
	working_control_fault6  = 66,			//����ͣ��
	working_control_fault7  = 67,			//����ͣ��
	working_control_fault8  = 68,			//����ͣ��
	working_control_fault9  = 69,			//����ͣ��
	working_control_fault10  = 70,			//����ͣ��
	working_control_fault11  = 71,			//����ͣ��
	working_control_fault12  = 72,			//����ͣ��

	working_control_fault_wait  = 80,		//����ͣ���ĵȴ�״̬����λ��Ϣ���ɻָ���wait

}Working_Control_Mode;


//����ģʽ
typedef enum Working_Status_Mode
{
	//ͨ��
	working_status_communication_outage = 0,		//ͨ���ж�
	working_status_wait = 1,						//������
	working_status_run = 2,							//����

	working_status_normal = 7,						//����

	working_status_starting  = 4,			//��������
	working_status_stoping  = 5,			//����ֹͣ

	//�쳣
	working_status_error = 101,				//���ϣ�����
}Working_Status_Mode;

//�쳣�澯
typedef enum Working_Alarm_Mode
{
	one_level_fault = 1,			//һ���澯
	two_level_fault = 2,			//�����澯
	three_level_fault = 3,			//�����澯
	working_normal = 4,				//����״̬��û�й���
}Working_Alarm_Mode;
/*
//fcu��������ĵȼ�
typedef enum FCU_Output_Electricity_Level
{
fcu_output_power_0_30A		= 0,
fcu_output_power_30_50A		= 1,
fcu_output_power_50_100A	= 2,
fcu_output_power_100_150A	= 3,
fcu_output_power_150_200A	= 4,
fcu_output_power_200_250A	= 5,
fcu_output_power_250_300A	= 6,
fcu_output_power_300_360A	= 7,
}FCU_Output_Electricity_Level;
*/

//fcu����ʱ��������λ������   51kw�Ķ�   Ĭ��Ϊ12��������
#define FCU_OUTPUT_ELECTRICITY_TOTAL_NUMBER		 	12

//fcu����ʱ��������λ�Ĳ��������Ľṹ��
typedef struct FCU_Run_Data_Debug
{
	float	fcu_output_electricity_lower_limit;         //��������������λ����
	float	fcu_output_electricity_upper_limit;         //��������������λ����

	float	pid1_Kp;
	float	pid1_Ki;
	float	pid1_Kd;
	float	pid2_Kp;
	float	pid2_Ki;
	float	pid2_Kd;
	float   h2_pressure_target_value;               //��ѹ Ŀ��ֵ
	float   h2_pressure_advance_set_value;          //��ѹ ��ǰ��  �趨ֵ  Ĭ��Ϊ0��һ����Ϊ5
	u32		h2_outlet_valve_open_time ;				//����β�ŷ�������ʱ��
	u32		h2_outlet_valve_close_time ;			//����β�ŷ��رյ�ʱ��
	u16     h2_circulating_pump_speed_setpoint;       //����ѭ����ת���趨                            ���can

	u32		air_compressor_speed_setpoint;		    //��ѹ��ת�٣����Ʊ�Ƶ����				���can��
    float   air_rate_of_flow_target;                //����������Ŀ��ֵ
    	
	float   water_temperature_target_value;         //������ˮ�� Ŀ��ֵ

}FCU_Run_Data_Debug;





//ϵͳ״̬���ĵ������ʱ���������֮����Ҫ�ȴ������ʱ�����ܽ�����һ��״̬(Ĭ��Ϊ0.1s)
#define FCU_SYSTEM_CHANGE_MODE_DELAY_100MS		 	100
//ϵͳ״̬���ĵ������ʱ���������֮����Ҫ�ȴ������ʱ�����ܽ�����һ��״̬(Ĭ��Ϊ1s)
#define FCU_SYSTEM_CHANGE_MODE_DELAY_1S		 		1000
//ϵͳ״̬���ĵ������ʱ���������֮����Ҫ�ȴ������ʱ�����ܽ�����һ��״̬(Ĭ��Ϊ2s)
#define FCU_SYSTEM_CHANGE_MODE_DELAY_2S		 		2000
//ϵͳ״̬���ĵ������ʱ���������֮����Ҫ�ȴ������ʱ�����ܽ�����һ��״̬(Ĭ��Ϊ3s)
#define FCU_SYSTEM_CHANGE_MODE_DELAY_3S		 		3000
//ϵͳ״̬���ĵ������ʱ���������֮����Ҫ�ȴ������ʱ�����ܽ�����һ��״̬(Ĭ��Ϊ5s)
#define FCU_SYSTEM_CHANGE_MODE_DELAY_5S		 		5000
//ϵͳ״̬���ĵ������ʱ���������֮����Ҫ�ȴ������ʱ�����ܽ�����һ��״̬(Ĭ��Ϊ6s)
#define FCU_SYSTEM_CHANGE_MODE_DELAY_6S		 		6000
//ϵͳ״̬���ĵ������ʱ���������֮����Ҫ�ȴ������ʱ�����ܽ�����һ��״̬(Ĭ��Ϊ10s)
#define FCU_SYSTEM_CHANGE_MODE_DELAY_10S	 		10000
//ϵͳ״̬���ĵ������ʱ���������֮����Ҫ�ȴ������ʱ�����ܽ�����һ��״̬(Ĭ��Ϊ15s)
#define FCU_SYSTEM_CHANGE_MODE_DELAY_15S	 		15000
//ϵͳ״̬���ĵ������ʱ���������֮����Ҫ�ȴ������ʱ�����ܽ�����һ��״̬(Ĭ��Ϊ20s)
#define FCU_SYSTEM_CHANGE_MODE_DELAY_20S	 		20000
//ϵͳ״̬���ĵ������ʱ���������֮����Ҫ�ȴ������ʱ�����ܽ�����һ��״̬(Ĭ��Ϊ30s)
#define FCU_SYSTEM_CHANGE_MODE_DELAY_30S	 		30000
//ϵͳ״̬���ĵ������ʱ���������֮����Ҫ�ȴ������ʱ�����ܽ�����һ��״̬(Ĭ��Ϊ60s)
#define FCU_SYSTEM_CHANGE_MODE_DELAY_60S	 		60000
//ϵͳ״̬���ĵ������ʱ���������֮����Ҫ�ȴ������ʱ�����ܽ�����һ��״̬(Ĭ��Ϊ70s)
#define FCU_SYSTEM_CHANGE_MODE_DELAY_70S	 		70000
//ϵͳ״̬���ĵ������ʱ���������֮����Ҫ�ȴ������ʱ�����ܽ�����һ��״̬(Ĭ��Ϊ60s)
#define FCU_SYSTEM_CHANGE_MODE_DELAY_100S	 		100000

//��ʱ��ʱ�䣨��ǰϵͳʱ�� ��ȥ ��һ�����ݸ��µ�ʱ�� ���� ��ʱʱ�䣬��ô�ͳ�ʱ�����û���ڹ涨��ʱ�������������ô����(Ĭ��Ϊ10s)
#define FCU_SYSTEM_OVERTIME_MAX_10					 		10000
//��ʱ��ʱ�䣨��ǰϵͳʱ�� ��ȥ ��һ�����ݸ��µ�ʱ�� ���� ��ʱʱ�䣬��ô�ͳ�ʱ�����û���ڹ涨��ʱ�������������ô����(Ĭ��Ϊ10s)
#define FCU_SYSTEM_OVERTIME_MAX_120					 		120000
//��ʱ��ʱ�䣨��ǰϵͳʱ�� ��ȥ ��һ�����ݸ��µ�ʱ�� ���� ��ʱʱ�䣬��ô�ͳ�ʱ�����û���ڹ涨��ʱ�������������ô����(Ĭ��Ϊ10s)
#define FCU_SYSTEM_OVERTIME_MAX_600							600000

/*
//fcu����ʱ����ѵ����ĵ�λ�л�
#define GALVANIC_PILE_ELECTRICITY_0			0
#define GALVANIC_PILE_ELECTRICITY_30		30
#define GALVANIC_PILE_ELECTRICITY_40		40
#define GALVANIC_PILE_ELECTRICITY_50		50
#define GALVANIC_PILE_ELECTRICITY_60		60
#define GALVANIC_PILE_ELECTRICITY_90		90
#define GALVANIC_PILE_ELECTRICITY_100		100
#define GALVANIC_PILE_ELECTRICITY_110		110
#define GALVANIC_PILE_ELECTRICITY_140		140
#define GALVANIC_PILE_ELECTRICITY_150		150
#define GALVANIC_PILE_ELECTRICITY_160		160
#define GALVANIC_PILE_ELECTRICITY_190		190
#define GALVANIC_PILE_ELECTRICITY_200		200
#define GALVANIC_PILE_ELECTRICITY_210		210
#define GALVANIC_PILE_ELECTRICITY_240		240
#define GALVANIC_PILE_ELECTRICITY_250		250
#define GALVANIC_PILE_ELECTRICITY_260		260
#define GALVANIC_PILE_ELECTRICITY_290		260
#define GALVANIC_PILE_ELECTRICITY_300		270
#define GALVANIC_PILE_ELECTRICITY_310		280
*/

//fcu���� ���ƹ���
typedef struct Control_Policy_Total_Manager
{
	enum Working_Control_Mode		working_control_mode;	//����ģʽ
	enum Working_Status_Mode		working_status_mode;	//����ģʽ		
	enum Working_Alarm_Mode 		working_alarm_mode;		//�쳣�澯	
	enum Error_code					working_FCU_error_code;	//fcu������
	enum Working_Control_Mode		working_FCU_error_control_mode;	//����˲�䣬fcu�Ŀ���ģʽ

	enum FCU_System_Running_Mode		fcu_system_running_mode;	//ϵͳ����ģʽ

	u32						fcu_updata_event_time;								 //���ݸ��µ�ʱ��

	u8						working_error_count;			//����Ĵ���������������Σ���ȡ���������

	int						fcu_output_electricity_level;		//fcu��������ĵȼ�
	struct FCU_Run_Data_Debug		fcu_run_data_debug[FCU_OUTPUT_ELECTRICITY_TOTAL_NUMBER];			//fcu����ʱ��������λ�Ĳ��������Ľṹ��

	u8						galvanic_pile_load_resistance_switch_count;		//С���ص��л�����
	
	//��ʱ�ӵ�һ�������жϵ���ʱ  3��
	u8  one_level_fault_flag_temp; //һ���澯���λ��0������1����һ���澯
	u32 one_level_fault_time_temp; //һ���澯���ʱ�䡣���ǳ���һ���澯��ʱ�䡣

}Control_Policy_Total_Manager;

extern struct Control_Policy_Total_Manager   control_policy_total_manager;

//FCU���صĹ����ʼ��
enum Error_code Control_Policy_Total_Manager_init(
struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//FCU���صĹ���������ݣ��ֶ����ƣ�ͨ��rs232���Խӿڣ�
enum Error_code Control_Policy_Total_Manager_updata_by_manual(
struct Control_Policy_Total_Manager  * p_control_policy_total_manager, float * rs232_test);
//FCU���صĹ���������ݣ��Զ����ƣ�
enum Error_code Control_Policy_Total_Manager_updata_by_Automatic (
struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//FCU���صĹ���������ݣ�ͨ��can��modbusͨ�Žӿڣ�
enum Error_code Control_Policy_Total_Manager_updata_by_communication(
struct Control_Policy_Total_Manager  * p_control_policy_total_manager, 
struct FCU_Data_Buffer * p_fcu_data_buffer);

//FCU�ȶ�����ʱ���Զ�����
enum Error_code FCU_automatic_gear_shift(void);

//����ʱ�ı������飬ͨ���ͣ�
enum Error_code FCU_run_protect_check_common(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);

//FCU���صĹ���������ݣ������㷨��
//����ĵĿ����㷨���Զ��������е����ݣ�����֤��������������С�
enum Error_code Control_Policy_Total_Manager_updata_by_system(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);

//FCU���أ����ƶϿ����㷨���տ���ʱ��״̬�������Լ�1�׶�
enum Error_code Control_Policy_Total_Manager_for_outage(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//FCU���أ��Լ�1���㷨�����ͨ�ţ�����ȴ�״̬
enum Error_code Control_Policy_Total_Manager_for_check1(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//FCU���أ��Լ�2���㷨�������Լ�1û��ͨ�������Ǿͽ��յ������������ʱ�жϣ�10s������Լ�ͨ������ô������������򱨴�
enum Error_code Control_Policy_Total_Manager_for_check2(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//FCU���أ��ȴ�������㷨���ж��Ƿ���Ҫ����fc�������Ҫ������������Լ�2״̬���������ͣ���ڵȴ�״̬��
enum Error_code Control_Policy_Total_Manager_for_wait(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//FCU���أ��Լ�3���㷨��������ģ������ݣ��ж��Ƿ�״̬����������������ͽ��������׶Σ�������ʧ�ܣ�����л��˴���Ȼ�󷵻صȴ��׶�
enum Error_code Control_Policy_Total_Manager_for_check3(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);

//fcu���أ�����1���㷨������ʱ������fc����������ɹ����ͽ������н׶Σ��������ʧ�ܣ�����л��˴���Ȼ�󷵻صȴ��׶�
enum Error_code Control_Policy_Total_Manager_for_start1(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//fcu���أ�����2���㷨������ʱ������fc����������ɹ����ͽ������н׶Σ��������ʧ�ܣ�����л��˴���Ȼ�󷵻صȴ��׶�
enum Error_code Control_Policy_Total_Manager_for_start2(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//fcu���أ�����3���㷨������ʱ������fc����������ɹ����ͽ������н׶Σ��������ʧ�ܣ�����л��˴���Ȼ�󷵻صȴ��׶�
enum Error_code Control_Policy_Total_Manager_for_start3(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//fcu���أ�����4���㷨������ʱ������fc����������ɹ����ͽ������н׶Σ��������ʧ�ܣ�����л��˴���Ȼ�󷵻صȴ��׶�
enum Error_code Control_Policy_Total_Manager_for_start4(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//fcu���أ�����5���㷨������ʱ������fc����������ɹ����ͽ������н׶Σ��������ʧ�ܣ�����л��˴���Ȼ�󷵻صȴ��׶�
enum Error_code Control_Policy_Total_Manager_for_start5(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//fcu���أ�����6���㷨������ʱ������fc����������ɹ����ͽ������н׶Σ��������ʧ�ܣ�����л��˴���Ȼ�󷵻صȴ��׶�
enum Error_code Control_Policy_Total_Manager_for_start6(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//fcu���أ�����7���㷨������ʱ������fc����������ɹ����ͽ������н׶Σ��������ʧ�ܣ�����л��˴���Ȼ�󷵻صȴ��׶�
enum Error_code Control_Policy_Total_Manager_for_start7(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//fcu���أ�����8���㷨������ʱ������fc����������ɹ����ͽ������н׶Σ��������ʧ�ܣ�����л��˴���Ȼ�󷵻صȴ��׶�
enum Error_code Control_Policy_Total_Manager_for_start8(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//fcu���أ�����9���㷨������ʱ������fc����������ɹ����ͽ������н׶Σ��������ʧ�ܣ�����л��˴���Ȼ�󷵻صȴ��׶�
enum Error_code Control_Policy_Total_Manager_for_start9(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//fcu���أ�����10���㷨������ʱ������fc����������ɹ����ͽ������н׶Σ��������ʧ�ܣ�����л��˴���Ȼ�󷵻صȴ��׶�
enum Error_code Control_Policy_Total_Manager_for_start10(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//fcu���أ�����11���㷨������ʱ������fc����������ɹ����ͽ������н׶Σ��������ʧ�ܣ�����л��˴���Ȼ�󷵻صȴ��׶�
enum Error_code Control_Policy_Total_Manager_for_start11(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//fcu���أ�����12���㷨������ʱ������fc����������ɹ����ͽ������н׶Σ��������ʧ�ܣ�����л��˴���Ȼ�󷵻صȴ��׶�
enum Error_code Control_Policy_Total_Manager_for_start12(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);


//fcu���أ����е��㷨�����ʿ��ƣ�������г����쳣������л��˴���Ȼ�󷵻صȴ��׶�
enum Error_code Control_Policy_Total_Manager_for_run(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);



//fcu���أ�ֹͣ1���㷨������ʱ��ֹͣfc�����ս���ȴ��׶�
enum Error_code Control_Policy_Total_Manager_for_stop1(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//fcu���أ�ֹͣ2���㷨������ʱ��ֹͣfc�����ս���ȴ��׶�
enum Error_code Control_Policy_Total_Manager_for_stop2(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//fcu���أ�ֹͣ3���㷨������ʱ��ֹͣfc�����ս���ȴ��׶�
enum Error_code Control_Policy_Total_Manager_for_stop3(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//fcu���أ�ֹͣ4���㷨������ʱ��ֹͣfc�����ս���ȴ��׶�
enum Error_code Control_Policy_Total_Manager_for_stop4(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//fcu���أ�ֹͣ5���㷨������ʱ��ֹͣfc�����ս���ȴ��׶�
enum Error_code Control_Policy_Total_Manager_for_stop5(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//fcu���أ�ֹͣ6���㷨������ʱ��ֹͣfc�����ս���ȴ��׶�
enum Error_code Control_Policy_Total_Manager_for_stop6(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//fcu���أ�ֹͣ7���㷨������ʱ��ֹͣfc�����ս���ȴ��׶�
enum Error_code Control_Policy_Total_Manager_for_stop7(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//fcu���أ�ֹͣ8���㷨������ʱ��ֹͣfc�����ս���ȴ��׶�
enum Error_code Control_Policy_Total_Manager_for_stop8(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//fcu���أ�ֹͣ9���㷨������ʱ��ֹͣfc�����ս���ȴ��׶�
enum Error_code Control_Policy_Total_Manager_for_stop9(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//fcu���أ�ֹͣ10���㷨������ʱ��ֹͣfc�����ս���ȴ��׶�
enum Error_code Control_Policy_Total_Manager_for_stop10(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//fcu���أ�ֹͣ11���㷨������ʱ��ֹͣfc�����ս���ȴ��׶�
enum Error_code Control_Policy_Total_Manager_for_stop11(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//fcu���أ�ֹͣ12���㷨������ʱ��ֹͣfc�����ս���ȴ��׶�
enum Error_code Control_Policy_Total_Manager_for_stop12(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);



//fcu���أ�����ͣ�����㷨��Ŀǰ��ֱ����������
enum Error_code Control_Policy_Total_Manager_for_fault0(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//fcu���أ�����ͣ��1���㷨�����մ�����ֹͣfc�����ս������ͣ���׶�
enum Error_code Control_Policy_Total_Manager_for_fault1(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//fcu���أ�����ͣ��2���㷨�����մ�����ֹͣfc�����ս������ͣ���׶�
enum Error_code Control_Policy_Total_Manager_for_fault2(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//fcu���أ�����ͣ��3���㷨�����մ�����ֹͣfc�����ս������ͣ���׶�
enum Error_code Control_Policy_Total_Manager_for_fault3(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//fcu���أ�����ͣ��4���㷨�����մ�����ֹͣfc�����ս������ͣ���׶�
enum Error_code Control_Policy_Total_Manager_for_fault4(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//fcu���أ�����ͣ��5���㷨�����մ�����ֹͣfc�����ս������ͣ���׶�
enum Error_code Control_Policy_Total_Manager_for_fault5(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//fcu���أ�����ͣ��6���㷨�����մ�����ֹͣfc�����ս������ͣ���׶�
enum Error_code Control_Policy_Total_Manager_for_fault6(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//fcu���أ�����ͣ��7���㷨�����մ�����ֹͣfc�����ս������ͣ���׶�
enum Error_code Control_Policy_Total_Manager_for_fault7(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//fcu���أ�����ͣ��8���㷨�����մ�����ֹͣfc�����ս������ͣ���׶�
enum Error_code Control_Policy_Total_Manager_for_fault8(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//fcu���أ�����ͣ��9���㷨�����մ�����ֹͣfc�����ս������ͣ���׶�
enum Error_code Control_Policy_Total_Manager_for_fault9(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//fcu���أ�����ͣ��10���㷨�����մ�����ֹͣfc�����ս������ͣ���׶�
enum Error_code Control_Policy_Total_Manager_for_fault10(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//fcu���أ�����ͣ��11���㷨�����մ�����ֹͣfc�����ս������ͣ���׶�
enum Error_code Control_Policy_Total_Manager_for_fault11(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);
//fcu���أ�����ͣ��12���㷨�����մ�����ֹͣfc�����ս������ͣ���׶�
enum Error_code Control_Policy_Total_Manager_for_fault12(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);

//fcu���أ�//����ͣ���ĵȴ�״̬����λ��Ϣ���ɻָ���wait
enum Error_code Control_Policy_Total_Manager_for_fault_wait(struct Control_Policy_Total_Manager  * p_control_policy_total_manager);





//�ж�2��ֵ�Ƿ�Լ����  ���ݴ���   20%
#define ERROR_TOLERANT_RATE 		0.2f

//�ж�2��ֵ�Ƿ�Լ���ڣ�������ݴ����ڣ��򷵻�Succeed�����򷵻�Failed
enum Error_code approximate(float value1, float value2);

//�ж�2��ֵ�Ƿ�Լ����  ���ݴ���   20%
#define ERROR_TOLERANT_RATE2 		0.05f

//�ж�2��ֵ�Ƿ�Լ���ڣ�������ݴ����ڣ��򷵻�Succeed�����򷵻�Failed
enum Error_code approximate2(float value1, float value2);


//�������ȼ����ɸ澯�ȼ�������
enum Error_code merge_alarm_mode(enum Working_Alarm_Mode * p_working_alarm_mode_source, enum Working_Alarm_Mode * p_working_alarm_mode_new);





#endif