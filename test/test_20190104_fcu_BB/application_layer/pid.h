#ifndef _PID_H
#define _PID_H


#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */


#include "error_system.h"
#include "custom_math.h"
//#include"data_buff.h"




//对变量的声明
typedef struct PID{
	u8      is_enble_pid;      //是否使能pid

	float   CurrentPoint;        //当前值
	float   SetPoint;            //设定值

	float	output_value_float;		//输出值，pwm占空比的增量
	i16		output_value_int;		//输出值，pwm占空比的增量

	float   Kp;                  //比例系数    （实际值*1000）
	float   Ki;                  //积分系数    （实际值*1000）
	float   Kd;                  //微分系数    （实际值*1000）

	float   CurrentError;               //当前误差数Er[0]
	float   LastError;           //最后一次误差数Er[-1]
	float   PrevError;           //最后第二次误差数er[-2]
	float   SumError;            //误差积分  

	u32		pid_updata_time;		//pid上一次的刷新时间。
	u32		pid_over_time;			//pid刷新超时时间。每隔一段时间，就更新一次pid
}PID;

// extern PID pid; 

//pid初始化
void PID_init(PID * p_pid, float kp, float ki, float kd);

//位置型PID  
void PID_position_mode(PID * p_pid);

//位置型PID  返回输出结果
float PID_position_mode_ex(PID * p_pid, float currentPoint, float setPoint);

//增量型PID
void PID_increamental_mode(PID * p_pid);

//增量型PID
float PID_increamental_mode_ex(PID * p_pid, float currentPoint, float setPoint);



#endif
