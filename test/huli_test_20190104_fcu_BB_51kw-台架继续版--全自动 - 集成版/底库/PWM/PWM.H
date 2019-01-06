#ifndef _PWM_H
#define _PWM_H
#include "derivative.h"

#define  PWM_CH0		   1
#define  PWM_CH1		   2
#define  PWM_CH2		   3
#define  PWM_CH3		   4
#define  PWM_CH4		   5
#define  PWM_CH5		   6
#define  PWM_CH6		   7
#define  PWM_CH7		   8

#define  PWM_Cascade1  1        //级联通道1选择
#define  PWM_Cascade2  2        //级联通道3选择
#define  PWM_Cascade3  3        //级联通道5选择
#define  PWM_Cascade4  4        //级联通道7选择

#define  PWM_Center_alignment  0x00   //中央对齐
#define  PWM_Left_aligned  0xFF       //左对齐

#define  PWM_Cascade_switch1  0x10    //级联开关01
#define  PWM_Cascade_switch3  0x20    //级联开关23
#define  PWM_Cascade_switch5  0x40    //级联开关45
#define  PWM_Cascade_switch7  0x80    //级联开关67

#define  PWM_Frequency0    0x00       //分频数 0分频
#define  PWM_Frequency2    0x11       //分频数 2分频
#define  PWM_Frequency4    0x22       //分频数 4分频
#define  PWM_Frequency8    0x33       //分频数 8分频
#define  PWM_Frequency16   0x44       //分频数 16分频
#define  PWM_Frequency32   0x55       //分频数 32分频
#define  PWM_Frequency64   0x66       //分频数 64分频
#define  PWM_Frequency128  0x77       //分频数 128分频

#define  PWM_Channel_clock0  0x01     //PWM1通道时钟选择
#define  PWM_Channel_clock1  0x02     //PWM2通道时钟选择
#define  PWM_Channel_clock2  0x04     //PWM3通道时钟选择
#define  PWM_Channel_clock3  0x08     //PWM4通道时钟选择
#define  PWM_Channel_clock4  0x10     //PWM5通道时钟选择
#define  PWM_Channel_clock5  0x20     //PWM6通道时钟选择
#define  PWM_Channel_clock6  0x40     //PWM7通道时钟选择
#define  PWM_Channel_clock7  0x80     //PWM8通道时钟选择

void PWM_init(u8 Fdivision_number,u8 data_format,u8 Channel_clock,u8 Chanel,u8 data);
void PWM_KG(u8 PD,u8 Chanel);  
void PWM_Cascade_init(u8 Fdivision_number,u8 Channel_clock,u8 Cascade_switch,u8 data_format,u8 Channel_number,u16 data); 
void PWM_Duty_ratio(u8 num,u16 duty);
void PWM_ratio(u8 num,u8 duty); 
#endif