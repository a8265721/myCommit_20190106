
#include "8BIT_LED_Segment_Displays.h"


byte led_8bit_data[4] = {0};
byte led_8bit_scan_num = 0;

byte led_8bit_show[20]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,       //0~9对应的段码
	0xbf,0x86,0xdb,0xcf,0xe6,0xed,0xfd,0x87,0xff,0xef};      //0~9后加小数点对应的段码


//初始化数码管
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


//为数码管初始化一个定时器
void ect_init_for_led_8bit(void)
{
	ECT_TSCR1_TFFCA = 1;  // 定时器标志位快速清除
	ECT_TSCR1_TEN = 1;    // 定时器使能位. 1=允许定时器正常工作; 0=使主定时器不起作用(包括计数器)
	ECT_TIOS  = 0xff;      //指定所有通道为输出比较方式
	ECT_TCTL1 = 0x00;	    // 后四个通道设置为定时器与输出引脚断开
	ECT_TCTL2 = 0x00;     // 前四个通道设置为定时器与输出引脚断开
	ECT_TIE   = 0x04;     // 允许通道2定时中断
	ECT_TSCR2 = 0x07;	    // 预分频系数pr2-pr0:111,,时钟周期为4us,
	ECT_TFLG1 = 0xff;	    // 清除各IC/OC中断标志位
	ECT_TFLG2 = 0xff;     // 清除自由定时器中断标志位
}


/*************************************************************/
/*                        延时函数                           */
/*************************************************************/
void delay(void) 
{
	unsigned int i,j;
	for(j=0;j<200;j++)
		for(i=0;i<60000;i++);
}

/*************************************************************/
/*                      中断扫描函数                         */
/*************************************************************/
#pragma CODE_SEG __NEAR_SEG NON_BANKED
interrupt void led_8bit_scan(void)
{
	if(ECT_TFLG1_C2F == 1)
	{
		ECT_TFLG1_C2F = 1;
		ECT_TC2 = ECT_TCNT + 1250;         //设置输出比较时间为5ms
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