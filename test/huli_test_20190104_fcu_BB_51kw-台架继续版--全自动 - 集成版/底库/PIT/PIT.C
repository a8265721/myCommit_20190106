#include "PIT.h"
#include "KEY.h"
#include <stdio.h>

u16 time=0;
//MTLD*PITLD=计数时间(计数时间<=总线时间)
//40000000/2个总线周期=1S(详见锁相环设置)
void PIT_init(u8 Channel_enable,u8 Channel_sele,u16 Loading_value) 
{
  //PITCFLMT_PITE=0;        //定时器通道关
  PITCE = PITCE | Channel_enable;
  PITMTLD0=200-1;   //0通道8位计数器赋值 200分频 
  switch(Channel_sele)
	{
	  case 1: PITLD0 = Loading_value-1; break;
	  case 2: PITLD1 = Loading_value-1; break;
	  case 3: PITLD2 = Loading_value-1; break;
    case 4: PITLD3 = Loading_value-1; break;
    case 5: PITLD4 = Loading_value-1; break;
    case 6: PITLD5 = Loading_value-1; break;     
	  case 7:	PITLD6 = Loading_value-1; break;     		      
    case 8: PITLD7 = Loading_value-1; break;
	}
	PITINTE = PITINTE | Channel_enable;  //定时中断使能
  PITCFLMT_PITE=1;          //定时器通道开
}


#pragma CODE_SEG __NEAR_SEG NON_BANKED
void interrupt 66 PIT0(void)
{
  if(PITTF_PTF0 == 1) PITTF_PTF0 = 1;
  time++;
  if(time==100) 
  {
    LED1=~LED1;
    time=0;
  }
  PITCE_PCE0=0;
  PITCE_PCE0=1;     
}
void interrupt 67 PIT1(void)
{
  if(PITTF_PTF1 == 1) PITTF_PTF1 = 1;    
  PORTB_PB1=~PORTB_PB1;   
}
void interrupt 68 PIT2(void)
{
  if(PITTF_PTF2== 1) PITTF_PTF2 = 1;    
  PORTB_PB2=~PORTB_PB2;   
}
void interrupt 69 PIT3(void)
{
  if(PITTF_PTF3 == 1) PITTF_PTF3 = 1;  
  PORTB_PB3=~PORTB_PB3;  
}
void interrupt 80 PIT4(void)
{
  if(PITTF_PTF4 == 1) PITTF_PTF4 = 1;    
  PORTB_PB4=~PORTB_PB4;   
}
void interrupt 81 PIT5(void)
{
  if(PITTF_PTF5 == 1) PITTF_PTF5 = 1;    
  PORTB_PB5=~PORTB_PB5;   
}
void interrupt 82 PIT6(void)
{
  if(PITTF_PTF6 == 1) PITTF_PTF6 = 1;  
  PORTB_PB6=~PORTB_PB6;   
}
void interrupt 83 PIT7(void)
{
  if(PITTF_PTF7 == 1) PITTF_PTF7 = 1;   
  PORTB_PB7=~PORTB_PB7;    
}

#pragma CODE_SEG DEFAULT