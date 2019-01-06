#ifndef _LED_H
#define _LED_H


#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

#define LEDCPU PORTK_PK4
#define LEDCPU_dir DDRK_DDRK4
#define LED PORTB
#define LED_dir DDRB

#define LED_0 PORTB_PB0
#define LED_1 PORTB_PB1
#define LED_2 PORTB_PB2
#define LED_3 PORTB_PB3
#define LED_4 PORTB_PB4
#define LED_5 PORTB_PB5
#define LED_6 PORTB_PB6
#define LED_7 PORTB_PB7


#define IO_OUT_K1  PORTD_PD0
#define IO_OUT_K2  PORTD_PD1
#define IO_OUT_K3  PORTD_PD2
#define IO_OUT_K4  PORTD_PD3
#define IO_OUT_K5  PORTA_PA0
#define IO_OUT_K6  PORTA_PA1
#define IO_OUT_K7  PORTA_PA2
#define IO_OUT_K8  PORTA_PA3
#define IO_OUT_K9  PORTA_PA4
#define IO_OUT_K10 PORTA_PA5

#define IO_OUT_K1_dir DDRD_DDRD0
#define IO_OUT_K2_dir DDRD_DDRD1
#define IO_OUT_K3_dir DDRD_DDRD2
#define IO_OUT_K4_dir DDRD_DDRD3
#define IO_OUT_K5_dir DDRA_DDRA0
#define IO_OUT_K6_dir DDRA_DDRA1
#define IO_OUT_K7_dir DDRA_DDRA2
#define IO_OUT_K8_dir DDRA_DDRA3
#define IO_OUT_K9_dir DDRA_DDRA4
#define IO_OUT_K10_dir DDRA_DDRA5
// ≥ı ºªØled                
void INIT_LED(void);



#endif
