
#include "pid.h"

//PID pid; 

//pid初始化
void PID_init(PID * p_pid, float kp, float ki, float kd)
{                             
	p_pid->is_enble_pid = 0;          //是否使能pid,默认不使能                           
	p_pid->CurrentPoint = 0;        //当前值
	p_pid->SetPoint = 0;            //设定值
	p_pid->output_value_float = 0;		//输出值，pwm占空比的增量
	p_pid->output_value_int = 0;		//输出值，pwm占空比的增量

	p_pid->Kp = kp;                  //比例系数    （实际值*1000）
	p_pid->Ki = ki;                  //积分系数    （实际值*1000）
	p_pid->Kd = kd;                  //微分系数    （实际值*1000）

	p_pid->CurrentError = 0;               //当前误差数Er[0]
	p_pid->LastError = 0;           //最后一次误差数Er[-1]
	p_pid->PrevError = 0;           //最后第二次误差数er[-2]
	p_pid->SumError = 0;            //误差积分  

	p_pid->pid_updata_time = 0;		//pid上一次的刷新时间。
	p_pid->pid_over_time = 10;			//pid刷新超时时间。每隔一段时间，就更新一次pid
}

//位置型PID  
void PID_position_mode(PID * p_pid)  
{
	//	if(system_time - p_pid->pid_updata_time >= p_pid->pid_over_time)
	//	{
	p_pid->CurrentError = p_pid->SetPoint - p_pid->CurrentPoint;    //偏差值=设定值-输入值（当前值）
	p_pid->SumError += p_pid->CurrentError;                      //积分=积分+偏差  --偏差的累加
	//    dError = p_pid->LastError - p_pid->PrevError;     //当前微分 = 最后误差 - 之前误差

	p_pid->output_value_float =      // 位置型PID  直接计算的是修改当前值的结果
		(   p_pid->Kp * p_pid->CurrentError                      //比例项 = 比例常数 * 偏差
		+   p_pid->Ki *  p_pid->SumError                          //积分项 = 积分常数 * 误差积分
		+   p_pid->Kd * (p_pid->CurrentError - p_pid->LastError)     //微分项 = 微分常数 * 当前微分
		) ;
	range_float(&(p_pid->output_value_float), -1000.0, 1000.0);

	p_pid->output_value_int = (i16)(p_pid->output_value_float);


	p_pid->PrevError = p_pid->LastError;              //更新“之前误差”
	p_pid->LastError = p_pid->CurrentError;           //更新“最后误差”

	//		p_pid->pid_updata_time = system_time;
	//	}

}

//位置型PID  返回输出结果
float PID_position_mode_ex(PID * p_pid, float currentPoint, float setPoint)
{                                                                           
	//	if(system_time - p_pid->pid_updata_time >= p_pid->pid_over_time)
	//	{

	if(p_pid->is_enble_pid == 1)                         
	{
		p_pid->CurrentPoint = currentPoint;
		p_pid->SetPoint = setPoint;
		PID_position_mode(p_pid);
		return p_pid->output_value_float;
	}
	else
	{
		return 0.0 ;
	}

	//	}
}                                            

//增量型PID
void PID_increamental_mode(PID * p_pid)
{
	//	if(system_time - p_pid->pid_updata_time >= p_pid->pid_over_time)
	//	{
	p_pid->CurrentError = p_pid->SetPoint - p_pid->CurrentPoint;    //偏差值=设定值-输入值（当前值）

	p_pid->output_value_float  +=       //增量型PID     计算的是当前值的增加量
		(   p_pid->Kp * (p_pid->CurrentError - p_pid->LastError)
		+   p_pid->Ki * p_pid->CurrentError  
		+   p_pid->Kd * (p_pid->CurrentError - 2 * p_pid->LastError + p_pid->PrevError)
		)  ;

	range_float(&(p_pid->output_value_float), -100.0, 100.0);

	p_pid->output_value_int = (int)(p_pid->output_value_float);

	p_pid->PrevError = p_pid->LastError;              //更新“之前误差”
	p_pid->LastError = p_pid->CurrentError;           //更新“最后误差”    

	//		p_pid->pid_updata_time = system_time;
	//	}
}

//增量型PID
float PID_increamental_mode_ex(PID * p_pid, float currentPoint, float setPoint)
{
	//	if(system_time - p_pid->pid_updata_time >= p_pid->pid_over_time)
	//	{
	p_pid->CurrentPoint = currentPoint;
	p_pid->SetPoint = setPoint;
	PID_increamental_mode(p_pid);
	return p_pid->output_value_float;
	//	}
}



