#ifndef _8BIT_LED_SEGMENT_DISPLAYS
#define _8BIT_LED_SEGMENT_DISPLAYS


#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "error_system.h"

#include "ect.h"

//����� 8bit LED Segment Displays
//ʹ��8����������P0~7�� �� 4����������K0~3  ��ע���ˣ�pwmʹ����P0~7�� ����pwm������ܲ���ͬʱʹ�ã�
//һ��8λ������Ҫ����4������ܣ������Ҫɨ����ơ�
//ʹ��ect����һ�������жϵĶ�ʱ���� ������ɨ���������ܡ�


#define LED_8BIT_CONT1 PORTK_PK3
#define LED_8BIT_CONT2 PORTK_PK2
#define LED_8BIT_CONT3 PORTK_PK1
#define LED_8BIT_CONT4 PORTK_PK0
#define LED_8BIT_CONT1_dir DDRK_DDRK3
#define LED_8BIT_CONT2_dir DDRK_DDRK2
#define LED_8BIT_CONT3_dir DDRK_DDRK1
#define LED_8BIT_CONT4_dir DDRK_DDRK0
#define LED_8BIT_DATA PTP
#define LED_8BIT_DATA_dir DDRP

extern byte led_8bit_data[4];

//��ʼ�������
void led_8bit_init(void);


//Ϊ����ܳ�ʼ��һ����ʱ��
void ect_init_for_led_8bit(void);

/*
//��ʾ0~9999������
void led_8bit_show_int(u16 show_num);


//��ʾС��
void led_8bit_show_float(float show_num, u8 );
*/




#endif