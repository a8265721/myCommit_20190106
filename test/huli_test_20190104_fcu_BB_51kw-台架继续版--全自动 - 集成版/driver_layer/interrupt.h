#ifndef _INTERRUPT_H
#define _INTERRUPT_H


#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "error_system.h"



//xs128��7���ж����ȼ���ÿһ���ж�Դ����һ���������õļ��� ��λ��������ж�Ĭ�����ȼ�Ϊ1 
//��ֵԽ�����ȼ�Խ�ߣ�������Ӧ��  
//�����ȼ����Բ�ӣ������ȼ��жϵĿ���Ƕ�׵����ȼ��ж�
//ͬһ���ȼ����ж�ͬʱ����ʱ���ߵ�ַ���жϺŽ�С�����ж�����Ӧ
//ע�⣺�ߵ�ַ�ж�ֻ��������Ӧ��������Ƕ��ͬһ���ȼ��͵�ַ���ж�


//#define Vsci0                           0xFFD6U
//���÷������£�
//MC9SX128.h�� �ҵ���Ӧ�жϵĵ�ַλ�ĺꡣ
//ǰ���FF���ܣ���ע�����һ��byte�� ����Vsci0 �����һ���ֽ�Ϊd6   6/2=3
//INT_CFADDR = 0xd;
//INT_CFDATA3=0x4;		//��Vsci0���ж����ȼ�����Ϊ4


//�ж����ȼ�����, �ж�Ĭ�����ȼ�Ϊ1, 
void init_interruput_priorty_set(void);

//ע���ˣ����Ҫ����Ƕ�ף������ȼ��жϵĿ���Ƕ�׵����ȼ��жϣ���Ҫ�ڵͼ��ж����ٿ�һ�����ж�
//����   EnableInterrupts;

#endif