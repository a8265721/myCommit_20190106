#ifndef _KEY_H
#define _KEY_H
#include "derivative.h"

#define K1  PORTD_PD0
#define K2  PORTD_PD1
#define K3  PORTD_PD2
#define K4  PORTD_PD3
#define K5  PORTA_PA0
#define K6  PORTA_PA1
#define K7  PORTA_PA2
#define K8  PORTA_PA3
#define K9  PORTA_PA4
#define K10 PORTA_PA5

#define K1_dir DDRD_DDRD0
#define K2_dir DDRD_DDRD1
#define K3_dir DDRD_DDRD2
#define K4_dir DDRD_DDRD3
#define K5_dir DDRA_DDRA0
#define K6_dir DDRA_DDRA1
#define K7_dir DDRA_DDRA2
#define K8_dir DDRA_DDRA3
#define K9_dir DDRA_DDRA4
#define K10_dir DDRA_DDRA5


void KEY_init(void);

#endif