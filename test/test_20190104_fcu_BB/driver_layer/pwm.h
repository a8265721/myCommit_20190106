#ifndef _PWM_H
#define _PWM_H


#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "error_system.h"

extern float dutyfactor_test;

//pwm通道编号
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

//pwm初始化  控制级联 就是2个pwm合并为一个 来提高频率和占空比精度
void init_pwm_cascade(void); 

//pwm初始化  单个配置。
void init_pwm_single(void);

//pwm初始化  混合控制       0和1 为8位pwm，  23 45 67 级联16位pwm
void init_pwm_hybrids(void); 


//pwm设置某个通道的周期
void pwm_set_period(enum Pwm_channel pwm_channel, Word period)  ;


//pwm设置某个通道的占空比
void pwm_set_dutyfactor(enum Pwm_channel pwm_channel, Word dutyfactor)  ;














#endif
