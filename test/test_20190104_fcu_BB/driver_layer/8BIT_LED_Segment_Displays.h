#ifndef _8BIT_LED_SEGMENT_DISPLAYS
#define _8BIT_LED_SEGMENT_DISPLAYS


#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "error_system.h"

#include "ect.h"

//数码管 8bit LED Segment Displays
//使用8个数据引脚P0~7， 和 4个控制引脚K0~3  （注意了，pwm使用了P0~7， 所以pwm和数码管不能同时使用）
//一个8位的数据要控制4个数码管，因此需要扫描控制。
//使用ect定义一个周期中断的定时器， 来触发扫描控制数码管。


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

//初始化数码管
void led_8bit_init(void);


//为数码管初始化一个定时器
void ect_init_for_led_8bit(void);

/*
//显示0~9999的整数
void led_8bit_show_int(u16 show_num);


//显示小数
void led_8bit_show_float(float show_num, u8 );
*/




#endif