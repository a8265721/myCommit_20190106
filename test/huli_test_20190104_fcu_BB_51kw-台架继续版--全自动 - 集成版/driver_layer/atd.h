#ifndef _ATD_H
#define _ATD_H


#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "error_system.h"
#include "sci.h"
#include "pwm.h"                                      
#include "pit.h"
                                           

//ad�ɼ���ת����ʱ������΢��us�� Ĭ��1000΢�룬��Լ���Բɼ�10��
#define ATDX_TIME_PERIOD		5000

//adת��ͨ�����������ֵ��mc9s12 ��16��ad
#define ATD0_CONVERSION_NUMBER_MAX		16		


//ad�ɼ��Ľ����ԭʼ�����   
//ʵ�ʽ��Ϊ    ԭʼ��� * 5v / ��2��n�η���      nΪ��������
extern u16 atd0_original_data[ATD0_CONVERSION_NUMBER_MAX] ;


//ad�ɼ���10��ƽ��ֵ
extern u16 atd0_mean_data[ATD0_CONVERSION_NUMBER_MAX];

//ad�ڵ�λʱ��ɼ��Ĵ�����
extern u32 atd0_capture_number;

//ad�ڵ�λʱ��ɼ��Ĵ������ֵ
extern u32 atd0_capture_number_max ;





//ad1ת��ͨ�����������ֵ��mc9s12 ��8��ad
#define ATD1_CONVERSION_NUMBER_MAX		8	
//ad1�ɼ��Ľ����ԭʼ�����
extern u16 atd1_original_data[ATD1_CONVERSION_NUMBER_MAX];
//ad1�ɼ���10��ƽ��ֵ
extern u16 atd1_mean_data[ATD1_CONVERSION_NUMBER_MAX];

//ad1�ڵ�λʱ��ɼ��Ĵ�����
extern u32 atd1_capture_number;

//ad�ڵ�λʱ��ɼ��Ĵ������ֵ
extern u32 atd1_capture_number_max ;




//ad�ɼ���ѹ��ʱ�䣨΢��us��
extern u32 atdx_time_count;

//ad�ɼ���ת����ʱ������΢��us��
extern u32 atdx_time_period ;


//NTC��ת���б�  �Ĵ�����Ӧ�¶�ֵ��
extern const u16 AD_Result[141];
extern const i8 Temp_Value[141];


//test
extern u32 test_atdx_begin ;
extern u32 test_atdx_end ;
extern u32 test_atdx_last;
extern u32 test_atdx_now ;





//adת������ ����ATD0CTL1_SRES�� ֱ��Ӱ�쵽�������Чλ����
enum ATDX_conversion_accuracy
{
	atdx_conversion_accuracy_8bit = 0x0,
	atdx_conversion_accuracy_10bit = 0x1,
	atdx_conversion_accuracy_12bit = 0x2,
};

//adͨ��������ģʽ
enum ATDX_input_mode
{
	atdx_input_analog ,		//����ģ������0~5V֮��ĵ�ѹ��
	atdx_input_digital ,		//������������0��5v �������źţ� ���ǵ�����ͨ��io����ڣ�
};

//adʹ�òɼ���ѹͨ��������
//��ͨ���ɼ���Ϊatd_conversion_number_1����ͨ���ɼ������Ӧ�����ġ�
enum ATDX_conversion_number
{
	atdx_conversion_number_1 = 0x1,
	atdx_conversion_number_2 = 0x2,
	atdx_conversion_number_3 = 0x3,
	atdx_conversion_number_4 = 0x4,
	atdx_conversion_number_5 = 0x5,
	atdx_conversion_number_6 = 0x6,
	atdx_conversion_number_7 = 0x7,
	atdx_conversion_number_8 = 0x8,
	atdx_conversion_number_9 = 0x9,
	atdx_conversion_number_10 = 0xa,
	atdx_conversion_number_11 = 0xb,
	atdx_conversion_number_12 = 0xc,
	atdx_conversion_number_13 = 0xd,
	atdx_conversion_number_14 = 0xe,
	atdx_conversion_number_15 = 0xf,
	atdx_conversion_number_16 = 0x10,//ע���ˣ�ת��16��ͨ����S8C, S4C, S2C, S1C�Ĵ���д0
};

//ad�ɼ���ѹ �� ��ʼͨ�������Ǵ��ĸ�ͨ���ڿ�ʼ�ɼ���
//����ɼ�����Ϊ2����ʼͨ��Ϊ3����ôʵ�ʲɼ�3��4��ͨ���ڵĵ�ѹ��
//��Ӧ�Ľ���Ĵ���ΪATD0DR0L ATD0DR1L
//ע���ˣ�����Ĵ����Ĵ��棬ÿ��ѭ����Զ���Ǵ�ATD0DR0L ��ʼ�����ܿ�ʼͨ��Ӱ��

//ad�ɼ���ѹ �� ��ʼͨ�������Ǵ��ĸ�ͨ���ڿ�ʼ�ɼ���
enum ATDX_start_number
{
	atdx_start_number_0 = 0x0,
	atdx_start_number_1 = 0x1,
	atdx_start_number_2 = 0x2,
	atdx_start_number_3 = 0x3,
	atdx_start_number_4 = 0x4,
	atdx_start_number_5 = 0x5,
	atdx_start_number_6 = 0x6,
	atdx_start_number_7 = 0x7,
	atdx_start_number_8 = 0x8,
	atdx_start_number_9 = 0x9,
	atdx_start_number_10 = 0xa,
	atdx_start_number_11 = 0xb,
	atdx_start_number_12 = 0xc,
	atdx_start_number_13 = 0xd,
	atdx_start_number_14 = 0xe,
	atdx_start_number_15 = 0xf,
};

//ad�ɼ��Ƿ�������
enum ATDX_conversion_is_continuous
{
	atdx_continuous = 1,		//�����ɼ���ֻ��Ҫ����һ�� ATD0CTL5	�� �����������ϵĲɼ���ѹ
	atdx_discontinuous = 0,	//�������ɼ���ÿ�ɼ�һ��ѭ�����ͻ������У���Ҫ����д��ATD0CTL5���ŻῪʼ�µĲɼ�
};


extern enum ATD_input_mode atd0_input_mode;
extern enum ATD_conversion_accuracy atd0_conversion_accuracy;
extern enum ATD_conversion_number atd0_conversion_number;
extern enum ATD_start_number atd0_start_number;
extern enum ATD_conversion_is_continuous atd0_conversion_is_continuous;


// ��ʼ��atd               
enum Error_code INIT_ATD0(void);

//ad����������,�ͳ�ʼ��һ��������һ��
enum Error_code ATD0_set_continuous(void) ;

//ad�ɼ���ѹ����Ҫѭ�����ã�ˢ������
enum Error_code ATD0_capture(void) ;

//ad�ɼ���ѹ��10��ƽ��ֵ
enum Error_code ATD0_capture_mean(void) ;


//ѹ����������ad������ѹת��Ϊѹ���ź�
//����220���裬ѹ�����������4~20mA�ĵ����ź�
//����ʵ��ĵ�ѹӦ����0.88~4.4V֮�䡣
//����ad�Ĵ���ԭʼֵ��ad�������ȣ���ѹ���������ķ�Χ��
//���ѹ����ʵ��ֵ��
float atdx_transformed_to_pressure
	(u16 ad_value, enum ATD_conversion_accuracy atdx_conversion_accuracy, 
	float pressure_max);



/*******************************************/
//������ADC1�Ĵ���  hsp
/******************************************/	

extern enum ATD_input_mode atd1_input_mode;
extern enum ATD_conversion_accuracy atd1_conversion_accuracy;
extern enum ATD_conversion_number atd1_conversion_number;
extern enum ATD_start_number atd1_start_number;
extern enum ATD_conversion_is_continuous atd1_conversion_is_continuous;	



enum Error_code INIT_ATD1(void);


enum Error_code ATD1_set_continuous(void); 


enum Error_code ATD1_capture(void);                                       

enum Error_code ATD1_capture_mean(void);



//NTC�¶ȴ����� ����
float atd_ntc_calculation(u16 da_data);

//4~20mA���������� ����
float atd_electricity_calculation(u16 da_data, u16 range_data );

//0.5~4.5V��ѹ������ ����
float atd_voltage_calculation_for_pressuer(u16 da_data, u16 range_data );

//��ѹ������ ����
//ad ת��Ϊ ��ѵ�ѹ
float atd_voltage_calculation_for_pile_voltage(u16 da_data, u16 range_data);
//ad ת��Ϊ ��ѵ���
float atd_voltage_calculation_for_pile_electricity(u16 da_data);
//ad ת��Ϊ ��������
float atd_voltage_calculation_for_air_rate_of_flow(u16 da_data);
//ad ת��Ϊ ����Ũ��	
float atd_voltage_calculation_for_h2_concentration(u16 da_data);

//ad������⣬�жϴ������Ƿ�����
enum Error_code atd_wait_check(void);

//ad������⣬�жϴ������Ƿ����� ,����������ǰ��ѹ
enum Error_code atd_wait_check_ex(void);

#endif
