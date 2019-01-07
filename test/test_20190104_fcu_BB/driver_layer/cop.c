#include "cop.h"



// 初始化看门狗     
void INIT_COP(void)
{
	COPCTL = 0x07;     //设置看门狗复位间隔为1.048576s   2^24 / 16M = 1.048576
}










