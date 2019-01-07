#ifndef _CUSTOM_MATH_H
#define _CUSTOM_MATH_H


#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */


#include "error_system.h"


//注意了，float转无符号的数时，不能为负数，所以一定要限制float范围
//限制float值的范围
void range_float(float * p_value, float min, float max);


//限制u16值的范围
void range_u16(u16 * p_value, u16 min, u16 max);

//限制i16值的范围
void range_i16(i16 * p_value, i16 min, i16 max);

//限制u32值的范围
void range_u32(u32 * p_value, u32 min, u32 max);

//限制i32值的范围
void range_i32(i32 * p_value, i32 min, i32 max);



void float_convert_four_byte(float *f,unsigned char *a,unsigned char *b,unsigned char *c,unsigned char *d);

float four_byte_convert_float(unsigned char a,unsigned char b,unsigned char c,unsigned char d);  


#endif                              