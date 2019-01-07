#ifndef _PLL_H
#define _PLL_H

#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

//#define BUS_CLOCK		   32000000	   //����Ƶ��
//#define BUS_CLOCK		   120000000	   //����Ƶ��
#define BUS_CLOCK		   64000000	   //����Ƶ��
#define OSC_CLOCK		   16000000	   //����Ƶ�� (�̶����䣬����Ƕ�pcu������)


//��ʱ����
//bus_clock_m  Ϊ����Ƶ��  ��λ��M ��32000000 ��Ӧ 32��
//time_ms Ϊ��ʱ�ľ���ʱ�䣬��λ��ms ��1�� ��Ӧ 1000��
//ע��u16 ���ֵΪ65535
void delay_ms(unsigned int time_ms) ;


//���໷��cpuĬ�ϵ�����Ƶ��Ϊ8M HZ
//�����ù����໷����cpu�ӿ죬ȱ�������׵��²��ȶ���
//ע���ˣ�������ʱ����ģ�һЩ��ʱ����صĶ����ܵ�Ӱ�졣��������ʱ��������.....��
void INIT_PLL(void) ;
















#endif