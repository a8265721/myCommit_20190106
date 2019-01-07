#ifndef _PWM_H
#define _PWM_H


#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "error_system.h"

extern float dutyfactor_test;

//pwmͨ�����
enum Pwm_channel
{
	pwm_channel_0 = 0,
	pwm_channel_1 = 1,
	pwm_channel_2 = 2,
	pwm_channel_3 = 3,
	pwm_channel_4 = 4,
	pwm_channel_5 = 5,
	pwm_channel_6 = 6,
	pwm_channel_7 = 7,
	pwm_channel_01 = 8,
	pwm_channel_23 = 9,
	pwm_channel_45 = 10,
	pwm_channel_67 = 11,
};

//pwm��ʼ��  ���Ƽ��� ����2��pwm�ϲ�Ϊһ�� �����Ƶ�ʺ�ռ�ձȾ���
void init_pwm_cascade(void); 

//pwm��ʼ��  �������á�
void init_pwm_single(void);

//pwm��ʼ��  ��Ͽ���       0��1 Ϊ8λpwm��  23 45 67 ����16λpwm
void init_pwm_hybrids(void); 


//pwm����ĳ��ͨ��������
void pwm_set_period(enum Pwm_channel pwm_channel, Word period)  ;


//pwm����ĳ��ͨ����ռ�ձ�
void pwm_set_dutyfactor(enum Pwm_channel pwm_channel, Word dutyfactor)  ;














#endif
