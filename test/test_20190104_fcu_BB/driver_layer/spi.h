#ifndef _SPI_H
#define _SPI_H

/*
SCI串口通信，为mcu和其他主机的通信协议。是异步串行通信。
SPI为串行设备接口，为MCU和其他芯片以及外围设备通信的。是同步串行通信。

同步串行通信：发送1byte的时候必然会收到1byte，但是可以不做接收处理。
因为有些外围设备，不具备主动发送功能，所以需要主机来发送来触发从机的答复消息。

SPI使用4个引脚，PS4~7

PS7：从机选择信号SS。该信号总是由 主机发送给从机。
为1时，SPI不能通信，	为0时，SPI可以通信
可以让SPI自动控制，或者设置为普通io口，然后程序手动控制。

PS4和5：通信数据线
MISO为主入/从出线，  MOSI为主入/从出线，

PS6：SCK串行时钟，由主机输出时钟信号，来统一控制SPI线路的波特率
*/

#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "error_system.h"
#include "sci.h"

//FM25040A 的使能引脚。输出1，可以使能FM25040A的存储和通信功能。
#define HOLD PTJ_PTJ0
#define HOLD_dir DDRJ_DDRJ0

//ps7，SPI控制引脚，可以设为普通的io口，然后来手动控制
#define CS PTS_PTS7
#define CS_dir DDRS_DDRS7


extern unsigned char SPI_receive_data ;

//初始化SPI模块 
void INIT_SPI(void) ;


//SPI发送函数          
void SPI_send(unsigned char data) ;


//SPI接收函数                
unsigned char SPI_receive(void) ;


//初始化FM25040A        
void INIT_FM25040A(void) ;




#endif



