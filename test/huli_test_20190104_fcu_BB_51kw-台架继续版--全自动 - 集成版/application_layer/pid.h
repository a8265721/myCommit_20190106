#ifndef _PID_H
#define _PID_H


#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */


#include "error_system.h"
#include "custom_math.h"
//#include"data_buff.h"




//�Ա���������
typedef struct PID{
	u8      is_enble_pid;      //�Ƿ�ʹ��pid

	float   CurrentPoint;        //��ǰֵ
	float   SetPoint;            //�趨ֵ

	float	output_value_float;		//���ֵ��pwmռ�ձȵ�����
	i16		output_value_int;		//���ֵ��pwmռ�ձȵ�����

	float   Kp;                  //����ϵ��    ��ʵ��ֵ*1000��
	float   Ki;                  //����ϵ��    ��ʵ��ֵ*1000��
	float   Kd;                  //΢��ϵ��    ��ʵ��ֵ*1000��

	float   CurrentError;               //��ǰ�����Er[0]
	float   LastError;           //���һ�������Er[-1]
	float   PrevError;           //���ڶ��������er[-2]
	float   SumError;            //������  

	u32		pid_updata_time;		//pid��һ�ε�ˢ��ʱ�䡣
	u32		pid_over_time;			//pidˢ�³�ʱʱ�䡣ÿ��һ��ʱ�䣬�͸���һ��pid
}PID;

// extern PID pid; 

//pid��ʼ��
void PID_init(PID * p_pid, float kp, float ki, float kd);

//λ����PID  
void PID_position_mode(PID * p_pid);

//λ����PID  ����������
float PID_position_mode_ex(PID * p_pid, float currentPoint, float setPoint);

//������PID
void PID_increamental_mode(PID * p_pid);

//������PID
float PID_increamental_mode_ex(PID * p_pid, float currentPoint, float setPoint);



#endif
