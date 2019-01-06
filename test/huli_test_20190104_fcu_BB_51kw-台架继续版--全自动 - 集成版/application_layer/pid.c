
#include "pid.h"

//PID pid; 

//pid��ʼ��
void PID_init(PID * p_pid, float kp, float ki, float kd)
{                             
	p_pid->is_enble_pid = 0;          //�Ƿ�ʹ��pid,Ĭ�ϲ�ʹ��                           
	p_pid->CurrentPoint = 0;        //��ǰֵ
	p_pid->SetPoint = 0;            //�趨ֵ
	p_pid->output_value_float = 0;		//���ֵ��pwmռ�ձȵ�����
	p_pid->output_value_int = 0;		//���ֵ��pwmռ�ձȵ�����

	p_pid->Kp = kp;                  //����ϵ��    ��ʵ��ֵ*1000��
	p_pid->Ki = ki;                  //����ϵ��    ��ʵ��ֵ*1000��
	p_pid->Kd = kd;                  //΢��ϵ��    ��ʵ��ֵ*1000��

	p_pid->CurrentError = 0;               //��ǰ�����Er[0]
	p_pid->LastError = 0;           //���һ�������Er[-1]
	p_pid->PrevError = 0;           //���ڶ��������er[-2]
	p_pid->SumError = 0;            //������  

	p_pid->pid_updata_time = 0;		//pid��һ�ε�ˢ��ʱ�䡣
	p_pid->pid_over_time = 10;			//pidˢ�³�ʱʱ�䡣ÿ��һ��ʱ�䣬�͸���һ��pid
}

//λ����PID  
void PID_position_mode(PID * p_pid)  
{
	//	if(system_time - p_pid->pid_updata_time >= p_pid->pid_over_time)
	//	{
	p_pid->CurrentError = p_pid->SetPoint - p_pid->CurrentPoint;    //ƫ��ֵ=�趨ֵ-����ֵ����ǰֵ��
	p_pid->SumError += p_pid->CurrentError;                      //����=����+ƫ��  --ƫ����ۼ�
	//    dError = p_pid->LastError - p_pid->PrevError;     //��ǰ΢�� = ������ - ֮ǰ���

	p_pid->output_value_float =      // λ����PID  ֱ�Ӽ�������޸ĵ�ǰֵ�Ľ��
		(   p_pid->Kp * p_pid->CurrentError                      //������ = �������� * ƫ��
		+   p_pid->Ki *  p_pid->SumError                          //������ = ���ֳ��� * ������
		+   p_pid->Kd * (p_pid->CurrentError - p_pid->LastError)     //΢���� = ΢�ֳ��� * ��ǰ΢��
		) ;
	range_float(&(p_pid->output_value_float), -1000.0, 1000.0);

	p_pid->output_value_int = (i16)(p_pid->output_value_float);


	p_pid->PrevError = p_pid->LastError;              //���¡�֮ǰ��
	p_pid->LastError = p_pid->CurrentError;           //���¡������

	//		p_pid->pid_updata_time = system_time;
	//	}

}

//λ����PID  ����������
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

//������PID
void PID_increamental_mode(PID * p_pid)
{
	//	if(system_time - p_pid->pid_updata_time >= p_pid->pid_over_time)
	//	{
	p_pid->CurrentError = p_pid->SetPoint - p_pid->CurrentPoint;    //ƫ��ֵ=�趨ֵ-����ֵ����ǰֵ��

	p_pid->output_value_float  +=       //������PID     ������ǵ�ǰֵ��������
		(   p_pid->Kp * (p_pid->CurrentError - p_pid->LastError)
		+   p_pid->Ki * p_pid->CurrentError  
		+   p_pid->Kd * (p_pid->CurrentError - 2 * p_pid->LastError + p_pid->PrevError)
		)  ;

	range_float(&(p_pid->output_value_float), -100.0, 100.0);

	p_pid->output_value_int = (int)(p_pid->output_value_float);

	p_pid->PrevError = p_pid->LastError;              //���¡�֮ǰ��
	p_pid->LastError = p_pid->CurrentError;           //���¡������    

	//		p_pid->pid_updata_time = system_time;
	//	}
}

//������PID
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



