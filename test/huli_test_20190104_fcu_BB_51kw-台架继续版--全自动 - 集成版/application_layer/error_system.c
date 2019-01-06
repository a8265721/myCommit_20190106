/*
error_system 本模块是错误码的处理
用法：其他模块直接包含本模块，然后作为函数的返回值。
上层通过分析错误码来判断函数的执行情况。
*/ 
//--------------------------------------------------------------------------------------------

#include "error_system.h"

//错误码初始化，清空Error_information里面的所有内容
void Error_init(struct Error_information * p_error_information)
{
	int length = 0;

	p_error_information->error_code = Succeed;//默认为0，表示成功，
	length = sizeof(p_error_information->Error_string);//默认256
	for(; length>0; )
	{
		length--;
		p_error_information->Error_string[length] = '\0'; 
	}
}























