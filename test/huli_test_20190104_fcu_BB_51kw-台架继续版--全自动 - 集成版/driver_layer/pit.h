#ifndef _PIT_H
#define _PIT_H


#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "error_system.h"
#include"data_buff.h"
#include "led.h"
#include "sci.h"
//#include "can_communication_protocol.h"
#include "can_communication_protocol2.h"                  
#include "can.h"
#include "atd.h"
//#include "modbus_communication_system.h"
//#include "modbus_communication_protocol.h"
#include "control_manager.h"                                         
#include "can_communication_protocol_VMS_shanghai.h"


//pit 是周期中断定时器。  类似于ect的mdc模数递减。
//pit有8个独立的16位定时器和8个中断。互相独立。
//pit还有2个为定时器。8位的。配合普通的8个定时器使用。用来增加周期

//总计数器的范围  (1~256) * (1~65536) = 16777216

//pit定时周期 = (PITMTLD + 1) * (PITLD + 1) / 总线频率


//微秒的计时器。
extern u32 system_time_us ;

extern enum ISlock  freemaster_lock ;


//test
extern u32 test_can_begin;
extern u32 test_can_end ;
extern u32 test_can_last ;
extern u32 test_can_now ;
extern u32 test_can_receive ;
extern u32 test_can_send ;



//test
extern u32 test_pid_begin ;
extern u32 test_pid_end ;
extern u32 test_pid_last ;
extern u32 test_pid_now ;

//test

extern u32 over_pressure_alarm ;






//pit初始化
void init_PIT(void);

//pit0中断
//interrupt void PIT0_interrupt(void) 


//can通信管理函数
//主要负责把接收的can消息缓存，按某种顺序读取出来（目前按照顺序，后期优化按照优先级）
//然后按照一定的频率发送数据。
enum Error_code can_communication_control(void);

//上海强检  can通信管理函数
//主要负责把接收的can消息缓存，按某种顺序读取出来（目前按照顺序，后期优化按照优先级）
//然后按照一定的频率发送数据。
enum Error_code can_communication_control_vms_shanghai(void);

//延时函数，单位us，利用时间差
void pit_delay_us(u32 delay_time);


#endif