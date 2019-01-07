#ifndef _SPI_H
#define _SPI_H

/*
SCI����ͨ�ţ�Ϊmcu������������ͨ��Э�顣���첽����ͨ�š�
SPIΪ�����豸�ӿڣ�ΪMCU������оƬ�Լ���Χ�豸ͨ�ŵġ���ͬ������ͨ�š�

ͬ������ͨ�ţ�����1byte��ʱ���Ȼ���յ�1byte�����ǿ��Բ������մ���
��Ϊ��Щ��Χ�豸�����߱��������͹��ܣ�������Ҫ�����������������ӻ��Ĵ���Ϣ��

SPIʹ��4�����ţ�PS4~7

PS7���ӻ�ѡ���ź�SS�����ź������� �������͸��ӻ���
Ϊ1ʱ��SPI����ͨ�ţ�	Ϊ0ʱ��SPI����ͨ��
������SPI�Զ����ƣ���������Ϊ��ͨio�ڣ�Ȼ������ֶ����ơ�

PS4��5��ͨ��������
MISOΪ����/�ӳ��ߣ�  MOSIΪ����/�ӳ��ߣ�

PS6��SCK����ʱ�ӣ����������ʱ���źţ���ͳһ����SPI��·�Ĳ�����
*/

#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "error_system.h"
#include "sci.h"

//FM25040A ��ʹ�����š����1������ʹ��FM25040A�Ĵ洢��ͨ�Ź��ܡ�
#define HOLD PTJ_PTJ0
#define HOLD_dir DDRJ_DDRJ0

//ps7��SPI�������ţ�������Ϊ��ͨ��io�ڣ�Ȼ�����ֶ�����
#define CS PTS_PTS7
#define CS_dir DDRS_DDRS7


extern unsigned char SPI_receive_data ;

//��ʼ��SPIģ�� 
void INIT_SPI(void) ;


//SPI���ͺ���          
void SPI_send(unsigned char data) ;


//SPI���պ���                
unsigned char SPI_receive(void) ;


//��ʼ��FM25040A        
void INIT_FM25040A(void) ;




#endif



