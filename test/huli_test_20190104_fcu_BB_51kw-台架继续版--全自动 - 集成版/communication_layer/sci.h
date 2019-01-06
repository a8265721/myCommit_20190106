#ifndef _SCI_H
#define _SCI_H


#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */


#include "pll.h"
#include "error_system.h"

#define BAUD_9600 9600
#define BAUD_115200 115200

#ifndef BUS_CLOCK
#define BUS_CLOCK 8000000	//如果更改总线时钟，那么默认就是8M Hz
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


//sci0用作freemaster
//初始化SCI0
void INIT_SCI0(void);

//串口发送函数 
void SCI0_send(unsigned char data) ;

//串口接收函数                        
unsigned char SCI0_receive(void) ;

// 串口中断接收函数
// (注意了，中断函数，不用再头文件里面定义，
// 只需要在 Project.prm 里面声明即可)   
//interrupt void SCI0_receive_in_interrupt(void);


//sci1用作printf   
//初始化SCI1
void INIT_SCI1(void);

//串口发送函数 
void SCI1_send(unsigned char data) ;

//串口发送多字节函数
void SCI1_send_string(u8 *data,u8 len);
//串口接收函数                        
unsigned char SCI1_receive(void) ;

// 串口中断接收函数
// (注意了，中断函数，不用再头文件里面定义，
// 只需要在 Project.prm 里面声明即可)   
//interrupt void SCI1_receive_in_interrupt(void);        

   /*
//输出重定向
void TERMIO_PutChar(char C);

//输入重定向
char TERMIO_GetChar(void);
     */




#endif