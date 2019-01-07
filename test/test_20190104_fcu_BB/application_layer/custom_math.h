#ifndef _CUSTOM_MATH_H
#define _CUSTOM_MATH_H


#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */


#include "error_system.h"


//ע���ˣ�floatת�޷��ŵ���ʱ������Ϊ����������һ��Ҫ����float��Χ
//����floatֵ�ķ�Χ
void range_float(float * p_value, float min, float max);


//����u16ֵ�ķ�Χ
void range_u16(u16 * p_value, u16 min, u16 max);

//����i16ֵ�ķ�Χ
void range_i16(i16 * p_value, i16 min, i16 max);

//����u32ֵ�ķ�Χ
void range_u32(u32 * p_value, u32 min, u32 max);

//����i32ֵ�ķ�Χ
void range_i32(i32 * p_value, i32 min, i32 max);



void float_convert_four_byte(float *f,unsigned char *a,unsigned char *b,unsigned char *c,unsigned char *d);

float four_byte_convert_float(unsigned char a,unsigned char b,unsigned char c,unsigned char d);  


#endif                              