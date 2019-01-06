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

//ע���ˣ�һ����8����ʱ�������ǹ���һ��ʱ�ӣ�����һ���������Ĵ���
//�������Լ��������ж�ϵͳ �� �ȽϼĴ�����

//���룺����⵽�������ŵ��ⲿ�¼�ʱ�����Բ�����־λ���ж�
//��������������Ĵ��� == �ȽϼĴ��� ʱ�����Բ�����־λ���жϣ� �����Զ��������ֱ�Ӳ�����

//����ȽϺ����벶�� �� PT0~7 ��������

//����Ƚϳ�ʼ��
void ect_init_output(void);

//���벶���ʼ��
void ect_init_input(void);



//ע���ˣ������ۼ��������벶��Ļ�������ӵĹ��ܡ�һ��Ҳʹ��ͬһ��ʱ��
//�����ۼ���4��8λͨ������PT0~3�������š�������ΪPACN0~3
//Ҳ���Լ���Ϊ2��16λ�ġ�PACA��PT7�������ţ�PACB��PT0�������š�������ΪPACA��ӦPACN32��PACB��ӦPACN10��
//ע���ˣ���ʱ���ļ������ǰ������ۼӵģ������ۼӼ������� ����⵽�ⲿ�����¼�֮��Ż�+1
//��ʱ�������ۼӳ�ʼ��
void ect_init_pai(void);



//����ֻʹ���˶�ʱ��������¼���û��ʹ�����š�
//��Ϊʱ�������ǹ̶��ģ�4us * 0xffff�������������û��ʵ�����塣
//һ�������������Ƚϣ���һ�����pwm�źš����������ں㶨��ֻ��������ռ�ձȣ�
//��ʱ�������ʼ��
void ect_init_overflow(void);



//ģ���ݼ�ֻ��һ����ӵ�ж�����ʱ�ӣ�û�ж�Ӧ������
//ģ���ݼ���Ȼ��ʱ��ʱ������Ҳ�ǹ̶��ģ����ǿ����Զ�����������ֵ�����Զ����жϴ�����ʱ�䡣
//��ʱ��ģ���ݼ���ʼ��������ϵͳ�ı�׼ʱ�䡣
void ect_init_mdc(void);


//��ʱ��������λms������ʱ���
void ect_delay_ms(u32 delay_time);

//��ӡϵͳʱ�䡣���ڲ���ֱ�Ӵ�ӡ u32�����Ը�Ϊ��ӡʱ����
void printf_system_time(void);


//�ۺϰ汾
//ect��ʼ��
void initialize_ect_ex(void);







#endif