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


//pit �������ж϶�ʱ����  ������ect��mdcģ���ݼ���
//pit��8��������16λ��ʱ����8���жϡ����������
//pit����2��Ϊ��ʱ����8λ�ġ������ͨ��8����ʱ��ʹ�á�������������

//�ܼ������ķ�Χ  (1~256) * (1~65536) = 16777216

//pit��ʱ���� = (PITMTLD + 1) * (PITLD + 1) / ����Ƶ��


//΢��ļ�ʱ����
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






//pit��ʼ��
void init_PIT(void);

//pit0�ж�
//interrupt void PIT0_interrupt(void) 


//canͨ�Ź�����
//��Ҫ����ѽ��յ�can��Ϣ���棬��ĳ��˳���ȡ������Ŀǰ����˳�򣬺����Ż��������ȼ���
//Ȼ����һ����Ƶ�ʷ������ݡ�
enum Error_code can_communication_control(void);

//�Ϻ�ǿ��  canͨ�Ź�����
//��Ҫ����ѽ��յ�can��Ϣ���棬��ĳ��˳���ȡ������Ŀǰ����˳�򣬺����Ż��������ȼ���
//Ȼ����һ����Ƶ�ʷ������ݡ�
enum Error_code can_communication_control_vms_shanghai(void);

//��ʱ��������λus������ʱ���
void pit_delay_us(u32 delay_time);


#endif