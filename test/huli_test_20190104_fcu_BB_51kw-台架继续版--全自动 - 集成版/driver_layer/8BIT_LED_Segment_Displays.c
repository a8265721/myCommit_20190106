
#include "8BIT_LED_Segment_Displays.h"


byte led_8bit_data[4] = {0};
byte led_8bit_scan_num = 0;

byte led_8bit_show[20]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,       //0~9��Ӧ�Ķ���
	0xbf,0x86,0xdb,0xcf,0xe6,0xed,0xfd,0x87,0xff,0xef};      //0~9���С�����Ӧ�Ķ���


//��ʼ�������
void led_8bit_init(void)
{
	LED_8BIT_CONT1_dir = 1;
	LED_8BIT_CONT2_dir = 1;
	LED_8BIT_CONT3_dir = 1;
	LED_8BIT_CONT4_dir = 1;
	LED_8BIT_CONT1 = 0;
	LED_8BIT_CONT2 = 0;
	LED_8BIT_CONT3 = 0;
	LED_8BIT_CONT4 = 0;
	LED_8BIT_DATA_dir = 0xff;
	LED_8BIT_DATA = 0x00;
}


//Ϊ����ܳ�ʼ��һ����ʱ��
void ect_init_for_led_8bit(void)
{
	ECT_TSCR1_TFFCA = 1;  // ��ʱ����־λ�������
	ECT_TSCR1_TEN = 1;    // ��ʱ��ʹ��λ. 1=����ʱ����������; 0=ʹ����ʱ����������(����������)
	ECT_TIOS  = 0xff;      //ָ������ͨ��Ϊ����ȽϷ�ʽ
	ECT_TCTL1 = 0x00;	    // ���ĸ�ͨ������Ϊ��ʱ����������ŶϿ�
	ECT_TCTL2 = 0x00;     // ǰ�ĸ�ͨ������Ϊ��ʱ����������ŶϿ�
	ECT_TIE   = 0x04;     // ����ͨ��2��ʱ�ж�
	ECT_TSCR2 = 0x07;	    // Ԥ��Ƶϵ��pr2-pr0:111,,ʱ������Ϊ4us,
	ECT_TFLG1 = 0xff;	    // �����IC/OC�жϱ�־λ
	ECT_TFLG2 = 0xff;     // ������ɶ�ʱ���жϱ�־λ
}


/*************************************************************/
/*                        ��ʱ����                           */
/*************************************************************/
void delay(void) 
{
	unsigned int i,j;
	for(j=0;j<200;j++)
		for(i=0;i<60000;i++);
}

/*************************************************************/
/*                      �ж�ɨ�躯��                         */
/*************************************************************/
#pragma CODE_SEG __NEAR_SEG NON_BANKED
interrupt void led_8bit_scan(void)
{
	if(ECT_TFLG1_C2F == 1)
	{
		ECT_TFLG1_C2F = 1;
		ECT_TC2 = ECT_TCNT + 1250;         //��������Ƚ�ʱ��Ϊ5ms
	}
	switch(led_8bit_scan_num)
	{
	case 0:
		LED_8BIT_CONT1 = 1;
		LED_8BIT_CONT2 = 0;
		LED_8BIT_CONT3 = 0;
		LED_8BIT_CONT4 = 0;
		LED_8BIT_DATA = led_8bit_show[led_8bit_data[0]];
		break;

	case 1:
		LED_8BIT_CONT1 = 0;
		LED_8BIT_CONT2 = 1;
		LED_8BIT_CONT3 = 0;
		LED_8BIT_CONT4 = 0;
		LED_8BIT_DATA = led_8bit_show[led_8bit_data[1]];
		break;

	case 2:
		LED_8BIT_CONT1 = 0;
		LED_8BIT_CONT2 = 0;
		LED_8BIT_CONT3 = 1;
		LED_8BIT_CONT4 = 0;
		LED_8BIT_DATA = led_8bit_show[led_8bit_data[2]];
		break;

	case 3:
		LED_8BIT_CONT1 = 0;
		LED_8BIT_CONT2 = 0;
		LED_8BIT_CONT3 = 0;
		LED_8BIT_CONT4 = 1;
		LED_8BIT_DATA = led_8bit_show[led_8bit_data[3]];
		break;

	default:
		break;
	}

	led_8bit_scan_num++;
	if(led_8bit_scan_num >= 4) 
	{
		led_8bit_scan_num = 0;
	}
}
#pragma CODE_SEG DEFAULT