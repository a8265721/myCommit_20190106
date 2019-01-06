#ifndef _ECT_H
#define _ECT_H


#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "error_system.h"
#include "led.h"
#include "sci.h"
//#include "can_communication_protocol.h"
#include "can_communication_protocol2.h"


extern u32 system_time ;
extern u32 system_time_old ;

extern u16 delaytime ;
extern u16 time1 ;
extern u16 time2 ;
                                          
extern u16 delaytime3 ;
extern u16 time3 ;
extern u16 time4 ;

//注意了，一共有8个定时器，他们共用一个时钟，共用一个计数器寄存器
//但是有自己独立的中断系统 和 比较寄存器。

//输入：当检测到输入引脚的外部事件时，可以产生标志位或中断
//输出：当计数器寄存器 == 比较寄存器 时，可以产生标志位或中断， 还可以对输出引脚直接操作。

//输出比较和输入捕获 与 PT0~7 共用引脚

//输出比较初始化
void ect_init_output(void);

//输入捕获初始化
void ect_init_input(void);



//注意了，脉冲累加是在输入捕获的基础上添加的功能。一般也使用同一个时钟
//脉冲累加有4个8位通道，与PT0~3共用引脚。计数器为PACN0~3
//也可以级联为2个16位的。PACA与PT7共用引脚，PACB与PT0共用引脚。计数器为PACA对应PACN32，PACB对应PACN10，
//注意了：定时器的计数器是按周期累加的，脉冲累加计数器是 当检测到外部输入事件之后才会+1
//定时器脉冲累加初始化
void ect_init_pai(void);



//这里只使用了定时器的溢出事件，没有使用引脚。
//因为时间周期是固定的（4us * 0xffff），所以这个并没有实际意义。
//一般用来配合输出比较，来一起产生pwm信号。（但是周期恒定，只能灵活控制占空比）
//定时器溢出初始化
void ect_init_overflow(void);



//模数递减只有一个，拥有独立的时钟，没有对应的引脚
//模数递减虽然定时器时间周期也是固定的，但是可以自定义计数的最大值，来自定义中断触发的时间。
//定时器模数递减初始化，用作系统的标准时间。
void ect_init_mdc(void);


//延时函数，单位ms，利用时间差
void ect_delay_ms(u32 delay_time);

//打印系统时间。由于不能直接打印 u32，所以改为打印时分秒
void printf_system_time(void);


//综合版本
//ect初始化
void initialize_ect_ex(void);







#endif