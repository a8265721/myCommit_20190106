#include "PWM.h"
#include "derivative.h"

//pwm=总线频率/分频数（PWMPRCLK)/((PA|PB)*2)/PWMPER
void PWM_init(u8 Fdivision_number,u8 data_format,u8 Channel_clock,u8 Chanel,u8 data) 
{
	PWMPRCLK = Fdivision_number;   
	PWMSCLA  = 0x02;       
	PWMSCLB  = 0X02;
	PWMCAE   = data_format;
	PWMPOL   = 0X00;
	PWMCLK = PWMCLK|Channel_clock;
	PWME   = 0X00;    
	switch(Chanel)
	{
	case 1: 
		{
			PWMCNT0 = 0;             
			PWMPER0 =data;                         
		}break;
	case 2: 
		{
			PWMCNT1 = 0;     
			PWMPER1 =data;                         
		}break;
	case 3:
		{
			PWMCNT2 = 0;              
			PWMPER2 =data;                          
		}break;
	case 4: 
		{
			PWMCNT3 = 0;           
			PWMPER3 =data;                          
		}break;  
	case 5:
		{
			PWMCNT4 = 0;                 
			PWMPER4 =data;                     
		}break; 
	case 6: 
		{
			PWMCNT5 = 0;             
			PWMPER5 =data;                       
		}break; 
	case 7:
		{ 
			PWMCNT6 = 0;              
			PWMPER6 =data;                            
		}break; 
	case 8:
		{
			PWMCNT7 = 0;          
			PWMPER7 =data;                         
		}break; 
	}
}

void PWM_Cascade_init(u8 Fdivision_number,u8 Channel_clock,u8 Cascade_switch,u8 data_format,u8 Channel_number,u16 data) 
{
	PWMPRCLK = Fdivision_number;    //对总线时间预分频（A时钟|B时钟=总线时间/分频数）
	PWMCLK = PWMCLK|Channel_clock;  //PWM时钟选择
	PWMSCLA = 0x02;                 //SA时钟=A时钟/(2*PWMSCLA)
	PWMSCLB = 0x02;                 //SB时钟=B时钟/(2*PWMSCLB)
	PWMCTL = PWMCTL|Cascade_switch; //通道0/1级联 16bit 
	PWMCAE = data_format;   
	PWMPOL = 0XFF;
	switch(Channel_number)
	{
	case 1:
		{
			PWMCNT01 = 0;
			PWMPER01 = data;
			PWME_PWME1 = 1;        //使能PWM输出 
		}break;  
	case 2:
		{
			PWMCNT23 = 0;
			PWMPER23 = data;
			PWME_PWME3 = 1;        //使能PWM输出   
		}break;
	case 3: 
		{
			PWMCNT45 = 0;
			PWMPER45 = data;
			PWME_PWME5 = 1;        //使能PWM输出   
		}break;
	case 4:
		{
			PWMCNT67 = 0;
			PWMPER67 = data;
			PWME_PWME7 = 1;        //使能PWM输出   
		}break;           
	}
}


void PWM_Duty_ratio(u8 num,u16 duty) 
{
	switch(num)
	{
	case 1: PWMDTY01=duty ;break;
	case 2: PWMDTY23=duty ;break;
	case 3: PWMDTY45=duty ;break;
	case 4: PWMDTY67=duty ;break;
	}
}

void PWM_ratio(u8 num,u8 duty) 
{ 
	if(duty>=250) duty=250; 
	switch(num)
	{
	case 1: PWMDTY0=duty ;break;
	case 2: PWMDTY1=duty ;break;
	case 3: PWMDTY2=duty ;break;
	case 4: PWMDTY3=duty ;break;
	case 5: PWMDTY4=duty ;break;
	case 6: PWMDTY5=duty ;break;
	case 7: PWMDTY6=duty ;break;
	case 8: PWMDTY7=duty ;break; 
	}
}

//PD=0,关闭PWM
//PD=1,打开PWM
void PWM_KG(u8 PD,u8 Chanel) 
{
	if(PD==1) 
	{
		switch(Chanel)
		{
		case 1: PWME_PWME0=1; break;
		case 2: PWME_PWME1=1; break;
		case 3: PWME_PWME2=1; break;
		case 4: PWME_PWME3=1; break;
		case 5: PWME_PWME4=1; break;
		case 6: PWME_PWME5=1; break;
		case 7: PWME_PWME6=1; break;
		case 8: PWME_PWME7=1; break;
		}    
	}
	else if(PD==0) 
	{
		switch(Chanel)
		{
		case 1: PWME_PWME0=0; break;
		case 2: PWME_PWME1=0; break;
		case 3: PWME_PWME2=0; break;
		case 4: PWME_PWME3=0; break;
		case 5: PWME_PWME4=0; break;
		case 6: PWME_PWME5=0; break;
		case 7: PWME_PWME6=0; break;
		case 8: PWME_PWME7=0; break;
		} 
	}   
}

