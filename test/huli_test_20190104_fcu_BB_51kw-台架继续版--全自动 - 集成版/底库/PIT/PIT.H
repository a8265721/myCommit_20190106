#ifndef _PIT_H
#define _PIT_H
#include "derivative.h"

#define  PIT_CH0		  1
#define  PIT_CH1		  2
#define  PIT_CH2		  3
#define  PIT_CH3		  4
#define  PIT_CH4		  5
#define  PIT_CH5		  6
#define  PIT_CH6		  7
#define  PIT_CH7		  8

#define  PIT_enable_CH0		  0x01
#define  PIT_enable_CH1		  0x02
#define  PIT_enable_CH2		  0x04
#define  PIT_enable_CH3		  0x08
#define  PIT_enable_CH4		  0x10
#define  PIT_enable_CH5		  0x20
#define  PIT_enable_CH6		  0x40
#define  PIT_enable_CH7		  0x80




void PIT_init(u8 Channel_enable,u8 Channel_sele,u16 Loading_value) ;



#endif
