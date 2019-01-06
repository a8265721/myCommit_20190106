
#include "ect.h"

u32 system_time = 0;
u32 system_time_old = 0;


u16 delaytime = 0;
u16 time1 = 0;
u16 time2 = 0;
                                                   
u16 delaytime3 = 0;
u16 time3 = 0;
u16 time4 = 0;

//注意了，一共有8个定时器，他们共用一个时钟，共用一个计数器寄存器
//但是有自己独立的中断系统 和 比较寄存器。

//输入：当检测到输入引脚的外部事件时，可以产生标志位或中断
//输出：当计数器寄存器 == 比较寄存器 时，可以产生标志位或中断， 还可以对输出引脚直接操作。

//输出比较和输入捕获 与 PT0~7 共用引脚


//输出比较初始化
void ect_init_output(void)
{
	ECT_TSCR1_TFFCA = 1;  // 定时器标志位快速清除
	ECT_TSCR1_TEN = 1;    // 定时器使能位. 1=允许定时器正常工作; 0=使主定时器不起作用(包括计数器)
	ECT_TIOS  = 0x7e;      //指定1~6为输出比较方式
	ECT_TCTL1 = 0x00;	    // 后四个通道设置为定时器与输出引脚断开
	ECT_TCTL2 = 0x00;     // 前四个通道设置为定时器与输出引脚断开
	ECT_TIE   = 0x00;     // 禁止所有通道定时中断
	ECT_TSCR2 = 0x07;	    // 预分频系数pr2-pr0:111,,时钟周期为4us, （总线时钟 / （2的7次方） = 250K HZ）
	ECT_TFLG1 = 0xff;	    // 清除各IC/OC中断标志位
	ECT_TFLG2 = 0xff;     // 清除自由定时器中断标志位

	//后续读取 标志位	ECT_TFLG1_C0F ~ ECT_TFLG1_C7F  
	//后续写入 数据位	ECT_TC0 ~ ECT_TC7
}


//输入捕获初始化
void ect_init_input(void)
{
	ECT_TSCR1_TFFCA = 1;  // 定时器标志位快速清除
	ECT_TSCR1_TEN = 1;    // 定时器使能位. 1=允许定时器正常工作; 0=使主定时器不起作用(包括计数器)
	ECT_TIOS  = 0x7e;      //指定通道7和0为输入捕捉方式
	ECT_TCTL3 = 0x40;	    // 设置通道7为捕捉上升沿方式
	ECT_TCTL4 = 0x01;	    // 设置通道0为捕捉上升沿方式
	ECT_TIE   = 0x81;     // 允许通道7和0定时中断
	ECT_TSCR2 = 0x07;	    // 预分频系数pr2-pr0:111,时钟周期为4us,（总线时钟 / （2的7次方） = 250K HZ）
	ECT_TFLG1 = 0xff;	    // 清除各IC/OC中断标志位
	ECT_TFLG2 = 0xff;     // 清除自由定时器中断标志位

	//后续读取 标志位	ECT_TFLG1_C0F ~ ECT_TFLG1_C7F  
	//后续读取 数据位	ECT_TC0 ~ ECT_TC7
}


/*************************************************************/
/*                   输入捕捉中断函数                        */
/*************************************************************/
#pragma CODE_SEG __NEAR_SEG NON_BANKED
interrupt void ect0_interrupt_capture(void) 
{
	EnableInterrupts;
	if(ECT_TFLG1_C0F == 1)
		ECT_TFLG1_C0F = 1;
	time1 = time2;
	time2 = ECT_TC0;
	delaytime = time2-time1;
	//	LEDCPU = ~LEDCPU;
}
#pragma CODE_SEG DEFAULT

#pragma CODE_SEG __NEAR_SEG NON_BANKED
interrupt void ect7_interrupt_capture(void) 
{
	EnableInterrupts;
	if(ECT_TFLG1_C7F == 1)
		ECT_TFLG1_C7F = 1;
	time3 = time4;
	time4 = ECT_TC7;
	delaytime3 = time4-time3;
	//	LEDCPU = ~LEDCPU;
}
#pragma CODE_SEG DEFAULT


//注意了，脉冲累加是在输入捕获的基础上添加的功能。一般也使用同一个时钟
//脉冲累加有4个8位通道，与PT0~3共用引脚。计数器为PACN0~3
//也可以级联为2个16位的。PACA与PT7共用引脚，PACB与PT0共用引脚。计数器为PACA对应PACN32，PACB对应PACN10，
//注意了：定时器的计数器是按周期累加的，脉冲累加是 当检测到外部输入事件之后才会+1
//定时器脉冲累加初始化
void ect_init_pai(void)
{
	ECT_TSCR1_TFFCA = 1;  // 定时器标志位快速清除
	ECT_TSCR1_TEN = 1;    // 定时器使能位. 1=允许定时器正常工作; 0=使主定时器不起作用(包括计数器)
	ECT_TIOS  = 0x0f;      //IOC7必须设置为输入，否则无法捕捉
	ECT_TCTL1 = 0x00;	    // 后四个通道设置为定时器与输出引脚断开
	ECT_TCTL2 = 0x00;     // 前四个通道设置为定时器与输出引脚断开
	ECT_TIE   = 0x00;     // 禁止所有通道定时中断
	ECT_TSCR2 = 0x07;	    // 预分频系数pr2-pr0:111,,时钟周期为4us,
	ECT_TFLG1 = 0xff;	    // 清除各IC/OC中断标志位
	ECT_TFLG2 = 0xff;     // 清除自由定时器中断标志位

	ECT_PACTL = 0x50;      //始能脉冲累加器，累加上升沿，级联为PACA，捕获PT7引脚

	//后续读取 数据位	ECT_PACN3~ECT_PACN0  或者 ECT_PACN32和ECT_PACN10
}


//这里只使用了定时器的溢出事件，没有使用引脚。
//因为时间周期是固定的（4us * 0xffff），所以这个并没有实际意义。
//一般用来配合输出比较，来一起产生pwm信号。（但是周期恒定，只能灵活控制占空比）
//定时器溢出初始化
void ect_init_overflow(void)
{
	ECT_TSCR1_TFFCA = 1;  // 定时器标志位快速清除
	ECT_TSCR1_TEN = 1;    // 定时器使能位. 1=允许定时器正常工作; 0=使主定时器不起作用(包括计数器)
	ECT_TIOS  = 0xff;     // 指定所有通道为输出比较方式
	ECT_TCTL1 = 0x00;	    // 后四个通道设置为定时器与输出引脚断开
	ECT_TCTL2 = 0x08;     // 通道1，在比较事件触发时，PT1引脚变为0
	ECT_TIE   = 0x00;     // 禁止所有通道定时中断
	ECT_TSCR2 = 0x80;	    // 预分频系数为0，使用总线频率32Mhz，使能定时器溢出中断
	ECT_TFLG1 = 0xff;	    // 清除各IC/OC中断标志位
	ECT_TFLG2 = 0xff;     // 清除自由定时器中断标志位


	ECT_TTOV = 0x02;      // 通道1，在溢出事件触发时，PT1引脚翻转
	ECT_TC1 = 0xc000;     //占空比为c000/ffff=75%  pwm频率约等于32Mhz/65535=488HZ
	//由于不能调整频率，所以不建议使用ect来模拟pwm。

	//溢出中断定时触发，周期为 4us * 0xFFFF 
	//在输出比较状态时，可以配置TTOV，来切换对应的输出引脚 
}


/*************************************************************/
/*                      定时器溢出中断                       */
/*************************************************************/
#pragma CODE_SEG __NEAR_SEG NON_BANKED
interrupt void ect_interrupt_overflow(void)
{
	unsigned int temp;	
	EnableInterrupts;	
	if(ECT_TFLG2_TOF ==1)
	{
		temp=ECT_TCNT;           //清除TOF标志
		PORTB_PB4 = 1- PORTB_PB4;
		//		printf("system_time 1= %0.0f  \r\n", (float)system_time);
		//		printf("system_time 2= %0.0f  \r\n", (float)system_time);
		//		printf("\r\n"); 
	}
}
#pragma CODE_SEG DEFAULT



//模数递减只有一个，拥有独立的时钟，没有对应的引脚
//模数递减虽然定时器时间周期也是固定的，但是可以自定义计数的最大值，来自定义中断触发的时间。
//定时器模数递减初始化，用作系统的标准时间。
void ect_init_mdc(void)
{
    //注意了，fcu的pll将系统频率改为了64M
	ECT_MCCTL = 0xc7;		//MCZI 使能中断，MODMC 开启循环计数。
	//MCEN 使能模数递减，MCPR1和MCPR0分频系数16，即为64Mhz/16=4MHz ，周期0.25us

	ECT_MCCNT = 4000;		//模数递减计数器的初始值，那么4000*0.25us=1ms，即为每1ms触发一次中断
	ECT_MCCTL_FLMC = 1;		//将ECT_MCCNT的初始值 加载到计数器中，此时将开始计时。
}


/*************************************************************/
/*                      定时器模数递减中断                       */
/*************************************************************/
#pragma CODE_SEG __NEAR_SEG NON_BANKED
interrupt void ect_interrupt_mdc(void)
{     
	unsigned int temp;
	EnableInterrupts;
	if(ECT_MCFLG_MCZF ==1)
	{
		ECT_MCFLG_MCZF =1;           //没有启动快速清除
		temp=ECT_MCCNT;           //清除TFLG2_MCFLG标志
		++system_time;

		if(system_time == 0xFFFFFFFF)
		{
			system_time = 0;

	//		Can_communication_protocol_clear_time(&can_communication_protocol_total);
			Can_communication_protocol2_clear_time(&can_communication_protocol2_total);
			//need pragrom
			//这里要清除所有程序中，相关的所有时间
		}
	}
}
#pragma CODE_SEG DEFAULT



//延时函数，单位ms，利用时间差
void ect_delay_ms(u32 delay_time)
{
	u32 time_temp = system_time;
	while(system_time - time_temp  <  delay_time)
	{}

}



//打印系统时间。由于不能直接打印 u32，所以改为打印时分秒
void printf_system_time(void)
{
	u32 time_temp = system_time;
	u16 day = 0;
	u16 hour = 0;
	u16 minute = 0;
	u16 second = 0;
	u16 millisecond = 0;

	millisecond = (u16)(time_temp % 1000);   
	time_temp = time_temp / 1000;

	second = (u16)(time_temp % 60);   
	time_temp = time_temp / 60;

	minute = (u16)(time_temp % 60);   
	time_temp = time_temp / 60;

	hour = (u16)(time_temp % 24); 

	day = (u16)(time_temp / 24);

	printf("system_time = %u day, %02u:%02u:%02u.%03u  \r\n", 
		day, hour, minute, second, millisecond);
}





//综合版本
//ect初始化
//t0为普通的输入捕获
//t1为输出比较。配合定时器溢出事件，模拟pwm
//t7为输入比较和脉冲累加
void initialize_ect_ex(void)
{
	ECT_TSCR1_TFFCA = 1;  // 定时器标志位快速清除
	ECT_TSCR1_TEN = 1;    // 定时器使能位. 1=允许定时器正常工作; 0=使主定时器不起作用(包括计数器)
	ECT_TIOS  = 0x7e;      //指定1~6为输出比较方式   指定通道7和0为输入捕捉方式
	ECT_TCTL1 = 0x00;	    // 后四个通道设置为定时器与输出引脚断开
	ECT_TCTL2 = 0x08;     // 通道1，在比较事件触发时，PT1引脚变为0
	ECT_TTOV = 0x02;      // 通道1，在溢出事件触发时，PT1引脚翻转
	ECT_TCTL3 = 0x40;	    // 设置通道7为捕捉上升沿方式
	ECT_TCTL4 = 0x01;	    // 设置通道0为捕捉上升沿方式
	ECT_TIE   = 0x81;     // 允许通道7和0定时中断
	ECT_TSCR2 = 0x87;	    // 预分频系数pr2-pr0:111,,时钟周期为4us, 使能定时器溢出中断
	ECT_TFLG1 = 0xff;	    // 清除各IC/OC中断标志位
	ECT_TFLG2 = 0xff;     // 清除自由定时器中断标志位

	ECT_TC1 = 0xc000;     //占空比为c000/ffff=75%  pwm频率约等于32Mhz/65535=488HZ
	ECT_PACTL = 0x50;      //始能脉冲累加器，累加上升沿，级联为PACA，捕获PT7引脚
}





