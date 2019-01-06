#ifndef _GENERAL_MODULE_H
#define _GENERAL_MODULE_H
#include "derivative.h"
#include <math.h>
#include <stdio.h>
#include "PIT.h"
#include "PWM.h"
#include "SCI.h"
#include "ADC.h"
#include "delay.h"      
#include "KEY.h"

#define  PLL_16		  0x01
#define  PLL_24		  0x42
#define  PLL_32		  0x43
#define  PLL_40		  0x44
#define  PLL_48		  0xc5
#define  PLL_56		  0xc6
#define  PLL_64		  0xc7
#define  PLL_72		  0xc8
#define  PLL_80		  0xc9
#define  PLL_88		  0xca
#define  PLL_96		  0xcb
#define  PLL_104		0xcc
#define  PLL_120		0xcd

//晶振时钟为16M
//DOG1: 16000000/16384      976.5S
//DOG2: 16000000/65536      244.1S
//DOG3: 16000000/262144     61   S 
//DOG4: 16000000/1048576    15.2 S
//DOG5: 16000000/4194304    3.8  S
//DOG6: 16000000/8388608    1.9  S
//DOG7: 16000000/16777216   0.95 S

#define  Close_DOG  0x00
#define  DOG1		    0x01
#define  DOG2		    0x02
#define  DOG3		    0x03
#define  DOG4		    0x04
#define  DOG5		    0x05
#define  DOG6		    0x06
#define  DOG7		    0x07



#define KEY1 PTIH_PTIH0
#define KEY2 PTIH_PTIH1
#define KEY3 PTIH_PTIH2
#define KEY4 PTIH_PTIH3
#define KEY5 PTIH_PTIH4
#define KEY6 PTIH_PTIH5
#define KEY7 PTIH_PTIH6
#define KEY8 PTIH_PTIH7

#define KEY1_dir DDRH_DDRH0
#define KEY2_dir DDRH_DDRH1
#define KEY3_dir DDRH_DDRH2
#define KEY4_dir DDRH_DDRH3
#define KEY5_dir DDRH_DDRH4
#define KEY6_dir DDRH_DDRH5
#define KEY7_dir DDRH_DDRH6
#define KEY8_dir DDRH_DDRH7



void Total_initialization(void); 
void INIT_DOG(u8 DOGS);
void Feed_dog(void);
void SetBusCLK(u8 PLLCLK_time);
int NTC_Calculation(u16 data);
void TIH_Hinit(void); //初始化按键 
#endif