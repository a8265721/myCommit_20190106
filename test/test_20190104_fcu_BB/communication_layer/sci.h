#ifndef _SCI_H
#define _SCI_H


#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */


#include "pll.h"
#include "error_system.h"

#define BAUD_9600 9600
#define BAUD_115200 115200

#ifndef BUS_CLOCK
#define BUS_CLOCK 8000000	//�����������ʱ�ӣ���ôĬ�Ͼ���8M Hz
#endif

extern unsigned char data_receive[100];
extern int data_num ;
extern int frame_num ;
extern int is_receive_finish ;

extern u32 test_huli1 ;
extern u32 test_huli2 ;
extern u32 test_huli3 ;
extern u32 test_huli4 ;
extern u32 test_huli123;


//sci0����freemaster
//��ʼ��SCI0
void INIT_SCI0(void);

//���ڷ��ͺ��� 
void SCI0_send(unsigned char data) ;

//���ڽ��պ���                        
unsigned char SCI0_receive(void) ;

// �����жϽ��պ���
// (ע���ˣ��жϺ�����������ͷ�ļ����涨�壬
// ֻ��Ҫ�� Project.prm ������������)   
//interrupt void SCI0_receive_in_interrupt(void);


//sci1����printf   
//��ʼ��SCI1
void INIT_SCI1(void);

//���ڷ��ͺ��� 
void SCI1_send(unsigned char data) ;

//���ڷ��Ͷ��ֽں���
void SCI1_send_string(u8 *data,u8 len);
//���ڽ��պ���                        
unsigned char SCI1_receive(void) ;

// �����жϽ��պ���
// (ע���ˣ��жϺ�����������ͷ�ļ����涨�壬
// ֻ��Ҫ�� Project.prm ������������)   
//interrupt void SCI1_receive_in_interrupt(void);        

   /*
//����ض���
void TERMIO_PutChar(char C);

//�����ض���
char TERMIO_GetChar(void);
     */




#endif