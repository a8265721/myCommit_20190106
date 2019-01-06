#ifndef _PLL_H
#define _PLL_H

#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

//#define BUS_CLOCK		   32000000	   //总线频率
//#define BUS_CLOCK		   120000000	   //总线频率
#define BUS_CLOCK		   64000000	   //总线频率
#define OSC_CLOCK		   16000000	   //晶振频率 (固定不变，这个是都pcu决定的)


//延时函数
//bus_clock_m  为总线频率  单位是M （32000000 对应 32）
//time_ms 为延时的具体时间，单位是ms （1秒 对应 1000）
//注意u16 最大值为65535
void delay_ms(unsigned int time_ms) ;


//锁相环，cpu默认的总线频率为8M HZ
//可以用过锁相环，将cpu加快，缺点是容易导致不稳定。
//注意了，当总线时间更改，一些和时间相关的都会受到影响。（例如延时，波特率.....）
void INIT_PLL(void) ;
















#endif