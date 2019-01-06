#include "led.h"


// 初始化led                
void INIT_LED(void)
{
	LEDCPU_dir=1;
	LED_dir=0xff;       //设置为输出

	//	LED = 0xff;          //全灭
	LED = 0x00;          //全liang
	LEDCPU = 0;

	/*
	LED = 0xff;          //熄灭
	LEDCPU = 1;
	*/
	
   IO_OUT_K1_dir=1;
   IO_OUT_K2_dir=1;
   IO_OUT_K3_dir=1;
   IO_OUT_K4_dir=1;
   IO_OUT_K5_dir=1;
   IO_OUT_K6_dir=1;
   IO_OUT_K7_dir=1;
   IO_OUT_K8_dir=1;
   IO_OUT_K9_dir=1;
   IO_OUT_K10_dir=1;
   
   IO_OUT_K1 = 1; 
   IO_OUT_K2 = 1;
   IO_OUT_K3 = 1;
   IO_OUT_K4 = 1;
   IO_OUT_K5 = 1;                                        
   IO_OUT_K6 = 1;
   IO_OUT_K7 = 1;
   IO_OUT_K8 = 1;
   IO_OUT_K9 = 1;
   IO_OUT_K10 = 1;	
}













