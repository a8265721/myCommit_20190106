/*
error_system ��ģ���Ǵ�����Ĵ���
�÷�������ģ��ֱ�Ӱ�����ģ�飬Ȼ����Ϊ�����ķ���ֵ��
�ϲ�ͨ���������������жϺ�����ִ�������
*/ 
//--------------------------------------------------------------------------------------------

#include "error_system.h"

//�������ʼ�������Error_information�������������
void Error_init(struct Error_information * p_error_information)
{
	int length = 0;

	p_error_information->error_code = Succeed;//Ĭ��Ϊ0����ʾ�ɹ���
	length = sizeof(p_error_information->Error_string);//Ĭ��256
	for(; length>0; )
	{
		length--;
		p_error_information->Error_string[length] = '\0'; 
	}
}























