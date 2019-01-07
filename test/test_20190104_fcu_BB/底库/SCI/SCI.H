#ifndef _SCI_H
#define _SCI_H
#include "derivative.h"
#include <stdio.h>

#define  BUS_CLOCK		80000000 //œµÕ≥ ±÷”

struct SCI_receive_data    
{
    u8   Receive_Complete_tag;
    u8   Receive_Error_tag;
    u16  Receive_L;
    u16  Receive_Length;
    u8   Receive_D[10];
    
};

                                      
#define  SCI_CH0		  1
#define  SCI_CH1		  2
#define  SCI_CH2		  3
#define  SCI_CH3		  4
#define  SCI_CH4		  5
#define  SCI_CH5		  6
#define  SCI_CH6		  7
#define  SCI_CH7		  8

void SCI_INIT(u8 Serial_Channel,u32 BAUD);
u8 SCI_receive(u8 Serial_Channel);       
void SCI_send(u8 Serial_Channel,u8 Send_data); 
void send_string(u8 Channelz,u8 *putchar);
void TERMIO_PutChar(char Send_data); 
char TERMIO_GetChar(void);


void send0_string(u8 *putchar);
void SCI0_send(u8 Send_data);
u8 SCI0_receive(void);


#endif