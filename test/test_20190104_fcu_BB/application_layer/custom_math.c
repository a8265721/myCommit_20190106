
#include "custom_math.h"




//ע���ˣ�floatת�޷��ŵ���ʱ������Ϊ����������һ��Ҫ����float��Χ
//����floatֵ�ķ�Χ
void range_float(float * p_value, float min, float max)
{
	if( *p_value < min)
	{
		*p_value = min;
	}
	if( *p_value > max)
	{
		*p_value = max;
	}
}

//����u16ֵ�ķ�Χ
void range_u16(u16 * p_value, u16 min, u16 max)
{
	if( *p_value < min)
	{
		*p_value = min;
	}
	if( *p_value > max)
	{
		*p_value = max;
	}
}

//����i16ֵ�ķ�Χ
void range_i16(i16 * p_value, i16 min, i16 max)
{
	if( *p_value < min)
	{
		*p_value = min;
	}
	if( *p_value > max)
	{
		*p_value = max;
	}
}




//����u16ֵ�ķ�Χ
void range_u32(u32 * p_value, u32 min, u32 max)
{
	if( *p_value < min)
	{
		*p_value = min;
	}
	if( *p_value > max)
	{
		*p_value = max;
	}
}

//����i32ֵ�ķ�Χ
void range_i32(i32 * p_value, i32 min, i32 max)
{
	if( *p_value < min)
	{
		*p_value = min;
	}
	if( *p_value > max)
	{
		*p_value = max;
	}
}



//��һ��float��ֵ�ֽ��4���ڴ浥Ԫ ͨ��ָ�봫����
void float_convert_four_byte(float *f,unsigned char *a,unsigned char *b,unsigned char *c,unsigned char *d)
{
	unsigned char * p_f=(unsigned char *)f;
	*a= *(p_f);
	*b=*(p_f+1);
	*c=*(p_f+2);
	*d=*(p_f+3);
} 


//��float���ĸ��ڴ��ڴ浥Ԫ��ֵת����һ��float
float four_byte_convert_float(unsigned char a,unsigned char b,unsigned char c,unsigned char d) 
{
	float ff=0;
	unsigned char * p_ff=(unsigned char*)&ff;
	*p_ff=a;
	*(p_ff+1)=b;
	*(p_ff+2)=c;
	*(p_ff+3)=d;
	return ff;
}
