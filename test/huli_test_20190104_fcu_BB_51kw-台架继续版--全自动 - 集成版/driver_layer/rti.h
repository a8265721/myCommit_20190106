#ifndef _RTI_H
#define _RTI_H


#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "error_system.h"
#include "led.h"

/*
实时中断就是一个定时模块，定时溢出，产生中断。 
第一步，实时中断RTI 在默认情况下是关闭的，怎样才能让 RTI 工作呢？ 
这就用到实时中断控制寄存器 RTICTL 了。 
RTICTL是一个八位寄存器，第七位没定义，只用到低七位[RTR6~RTR0]。
当RTR[6：4]=000时，实时中断被禁止，只要当RTR[6:4] 不全为0时，实时中断就开了
同时实时中断的溢出周期也是由该寄存器配置的。 
RTI 的参考时间是外部晶振的时钟OSCCLK。
故，实时中断的溢出时钟周期=（RTR[3:0]+1) x (2的（RTR[6:4] + 9）次方)/OSCCLK  
第二步，要想在实时中断溢出时产生一个中断，则用到寄存器 CRGINT 了。                 
当CRGINT_RTIE=1时，每个周期结束时，就会产生一个中断只要配置好上面说的两个寄存器，
再写上相应的中断函数，实时中断就可以用了。
顺便提一下，实时中断 RTI 的中断号是 7 CRGFLG_RTIF 是实时中断的标志位，
当 RTI 溢出时，CRGFLG_RTIF 就会由硬件置1，向CRGFLG_RTIF 写1，可以清零标志位。
这和51单片机不一样，51单片机的标志位清零是向相应的寄存器写0 与 RTI 相关的寄存器还有 CLKSEL_RTIWAI，不过一般都不会用到。
当CLKSEL_RTIWAI=1时，只要系统进入等待模式，RTI 就停止工作。
当CLKSEL_RTIWAI=0时，在等待模式下，RTI 仍然工作实时中断
*/

/*
注意了，rti的时钟周期直接和外部晶振的频率相关，不受锁相环的影响。
实时中断的溢出时钟周期=（RTR[3:0]+1) x (2的（RTR[6:4] + 9）次方)/OSCCLK  
周期为固定的几个，不能自定义为常用的值。
使用的效果和ect定时器的溢出中断类似，但是没有对应引脚。。。。
*/


//初始化实时中断
void INIT_RTI(void);


#endif