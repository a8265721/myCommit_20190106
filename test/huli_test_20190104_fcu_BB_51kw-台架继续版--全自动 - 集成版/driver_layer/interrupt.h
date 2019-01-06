#ifndef _INTERRUPT_H
#define _INTERRUPT_H


#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "error_system.h"



//xs128有7个中断优先级，每一个中断源都有一个可以设置的级别， 复位后可屏蔽中断默认优先级为1 
//数值越大，优先级越高，优先响应。  
//高优先级可以插队，高优先级中断的可以嵌套低优先级中断
//同一优先级的中断同时触发时，高地址（中断号较小）的中断先响应
//注意：高地址中断只能优先响应，但不能嵌套同一优先级低地址的中断


//#define Vsci0                           0xFFD6U
//配置方法如下：
//MC9SX128.h中 找到对应中断的地址位的宏。
//前面的FF不管，关注后面的一个byte。 例如Vsci0 的最后一个字节为d6   6/2=3
//INT_CFADDR = 0xd;
//INT_CFDATA3=0x4;		//把Vsci0的中断优先级设置为4


//中断优先级设置, 中断默认优先级为1, 
void init_interruput_priorty_set(void);

//注意了，如果要进行嵌套，高优先级中断的可以嵌套低优先级中断，需要在低级中断中再开一次总中断
//增加   EnableInterrupts;

#endif