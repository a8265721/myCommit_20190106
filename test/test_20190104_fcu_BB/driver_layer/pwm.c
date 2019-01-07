
#include "pwm.h"

//pwm比例阀的占空比
float dutyfactor_test = 0;

//pwm初始化  控制级联 就是2个pwm合并为一个 来提高周期频率和占空比精度
void init_pwm_cascade(void) 
{
	PWMCTL_CON01= 1;   //联结通道0,1为16位的PWM
	PWMCTL_CON23= 1;   //联结通道2,3为16位的PWM
	PWMCTL_CON45= 1;   //联结通道4,5为16位的PWM
	PWMCTL_CON67= 1;   //联结通道6,7为16位的PWM	
	//注意了，因为fcu板子设计的原因，电路控制是反向的，所以这里设置为低电平有效
	PWMPOL_PPOL1= 1;   //通道01的极性为低电平有效
	PWMPOL_PPOL3= 1;   //通道23的极性为低电平有效
	PWMPOL_PPOL5= 1;   //通道45的极性为低电平有效
	PWMPOL_PPOL7= 1;   //通道67的极性为低电平有效	
	//	PWMPRCLK = 0x55;   //A时钟和B时钟的分频系数为32,频率为1MHz
	PWMPRCLK = 0x00;   //A时钟和B时钟的分频系数为1,频率为64MHz  (总线频率64M)
	PWMSCLA  =  32;   //SA时钟频率为1000KHz（SA时钟 = A时钟 / 2 / PWMSCLA）
	PWMSCLB  =  32;   //SB时钟频率为1000KHz（SB时钟 = B时钟 / 2 / PWMSCLB）
	//	PWMCLK =0x0a;      //通道01用SA时钟作为时钟源,通道23用SB时钟作为时钟源
	PWMCLK =0xA2;      //通道01 45 67用S时钟作为时钟源,通道23用标准时钟作为时钟源
	PWMCAE   = 0x00;   //脉冲模式为左对齐模式
	PWMPER01  = 10000;  //通道01的周期为占空比例范围10000
	PWMPER23  = 10000;  //通道23的周期为占空比例范围10000
	PWMPER45  = 10000;  //通道45的周期为占空比例范围10000
	PWMPER67  = 10000;  //通道67的周期为占空比例范围10000	
	PWMDTY01  = 0;  //通道01的占空比为0%   
	PWMDTY23  = 0;  //通道23的占空比为0%  
	PWMDTY45  = 0;  //通道01的占空比为0%   
	PWMDTY67  = 0;  //通道23的占空比为0%  	
	PWME_PWME1 = 1;    //使能通道01
	PWME_PWME3 = 1;    //使能通道23
	PWME_PWME5 = 1;    //使能通道45
	PWME_PWME7 = 1;    //使能通道67	
}



//pwm初始化  单个配置。
void init_pwm_single(void)
{
	PWMPOL = 0x0f;		//通道0~3的极性为高电平有效

	PWMPRCLK = 0x55;	//A时钟和B时钟的分频系数为32,频率为1MHz（a b时钟频率=总线频率/（2的5次方） ）
	PWMSCLA  =  50;		//SA时钟频率为10KHz（SA的时钟频率=a的时钟频率/2/50）
	PWMSCLB  =  50;		//SB时钟频率为10KHz（SB的时钟频率=b的时钟频率/2/50）
	PWMCLK = 0x0f;		//通道0和1用SA时钟作为时钟源,通道2和3用SB时钟作为时钟源
	//    PWMCLK = 0x00;		//都使用默认的时钟。

	PWMCAE   = 0x00;	//脉冲模式为左对齐模式

	PWMPER0 = 100;		//通道0的周期为100Hz（通道1的周期=对应的时钟频率/100）
	PWMPER1 = 100;		//通道1的周期为100Hz（注意了，单通道只有8bit， 双通道才有16bit）  
	PWMPER2 = 100;		//通道2的周期为100Hz 
	PWMPER3 = 100;		//通道3的周期为100Hz 

	PWMDTY0 = 10;		//通道0的占空比为10%  
	PWMDTY1 = 50;		//通道0的占空比为50%  
	PWMDTY2 = 90;		//通道0的占空比为90%  
	PWMDTY3 = 100;		//通道0的占空比为100%  

	PWME = 0x0f;		//使能通道0~3
}

           /*
//pwm初始化  混合控制      
void init_pwm_hybrids(void)
{
	//	PWMCTL_CON01= 1;   //联结通道0,1为16位的PWM
	PWMCTL_CON23= 1;   //联结通道2,3为16位的PWM
	//PWMCTL_CON45= 1;   //联结通道4,5为16位的PWM
	PWMCTL_CON67= 1;   //联结通道6,7为16位的PWM	
	//注意了，因为fcu板子设计的原因，电路控制是反向的，所以这里设置为低电平有效
	PWMPOL_PPOL0= 1;   //通道0的极性为低电平有效
	PWMPOL_PPOL1= 1;   //通道1的极性为低电平有效
	PWMPOL_PPOL3= 1;   //通道23的极性为低电平有效
	PWMPOL_PPOL4= 1;   //通道4的极性为低电平有效
	PWMPOL_PPOL5= 1;   //通道5的极性为低电平有效
	PWMPOL_PPOL7= 1;   //通道67的极性为低电平有效	
	PWMPRCLK = 0x06;   //A时钟的分频系数为64,频率为1MHz, B时钟的分频系数为1,频率为64MHz  (总线频率64M)
	PWMSCLA  =  50;   //SA时钟频率为10KHz（SA时钟 = A时钟 / 2 / PWMSCLA）
//	PWMSCLB  =  32;   //SB时钟频率为1000KHz（SB时钟 = B时钟 / 2 / PWMSCLB）
	PWMSCLB  =  5;   //SB时钟频率为1000KHz（SB时钟 = B时钟 / 2 / PWMSCLB）
//	PWMCLK =0x3b;      //通道0和1用SA时钟10KHz，通道3用SB时钟1000KHz,  通道4和5用SA时钟10KHz，通道7用B时钟64MHz
	PWMCLK =0xbb;      //通道0和1用SA时钟10KHz，通道3用SB时钟1000KHz,  通道4和5用SA时钟10KHz，通道7用B时钟64MHz
	PWMCAE   = 0x00;   //脉冲模式为左对齐模式
	PWMPER0  = 100;  //通道0的周期为占空比例范围100
	PWMPER1  = 100;  //通道1的周期为占空比例范围100
	PWMPER23  = 10000;  //通道23的周期为占空比例范围10000
	PWMPER4  = 100;  //通道4的周期为占空比例范围100
	PWMPER5  = 100;  //通道5的周期为占空比例范围100
	PWMPER67  = 10000;  //通道67的周期为占空比例范围10000	
	PWMDTY0  = 0;  //通道0的占空比为0%   
	PWMDTY1  = 0;  //通道1的占空比为0%   
	PWMDTY23  = 0;  //通道23的占空比为0%  
	PWMDTY4  = 0;  //通道4的占空比为0%   
	PWMDTY5  = 0;  //通道5的占空比为0%   
	PWMDTY67  = 0;  //通道67的占空比为0%  
	PWME_PWME0 = 1;    //使能通道0
	PWME_PWME1 = 1;    //使能通道1
	PWME_PWME3 = 1;    //使能通道23
	PWME_PWME4 = 1;    //使能通道4
	PWME_PWME5 = 1;    //使能通道5
	PWME_PWME7 = 1;    //使能通道67	

}
  */
  
  //pwm初始化  混合控制      
void init_pwm_hybrids(void)
{
	//	PWMCTL_CON01= 1;   //联结通道0,1为16位的PWM
	PWMCTL_CON23= 1;   //联结通道2,3为16位的PWM
	//PWMCTL_CON45= 1;   //联结通道4,5为16位的PWM
	PWMCTL_CON67= 1;   //联结通道6,7为16位的PWM	
	//注意了，因为fcu板子设计的原因，电路控制是反向的，所以这里设置为低电平有效
	PWMPOL_PPOL0= 1;   //通道0的极性为低电平有效
	PWMPOL_PPOL1= 1;   //通道1的极性为低电平有效
	PWMPOL_PPOL3= 1;   //通道23的极性为低电平有效
	PWMPOL_PPOL4= 1;   //通道4的极性为低电平有效
	PWMPOL_PPOL5= 1;   //通道5的极性为低电平有效
	PWMPOL_PPOL7= 1;   //通道67的极性为低电平有效	
	PWMPRCLK = 0x36;   //A时钟的分频系数为64,频率为1MHz, B时钟的分频系数为8,频率为8MHz  (总线频率64M)
	PWMSCLA  =  50;   //SA时钟频率为10KHz（SA时钟 = A时钟 / 2 / PWMSCLA = 1M/2/50=10k）
	PWMSCLB  =  4;   //SB时钟频率为1000KHz（SB时钟 = B时钟 / 2 / PWMSCLB = 8M/2/4=1M）
	PWMCLK =0x3b;      //通道0和1用SA时钟10KHz，通道3用SB时钟1000KHz,  通道4和5用SA时钟10KHz，通道7用B时钟8MHz
	PWMCAE   = 0x00;   //脉冲模式为左对齐模式
	PWMPER0  = 100;  //通道0的周期为占空比例范围100          频率=10k/100=100hz
	PWMPER1  = 100;  //通道1的周期为占空比例范围100          频率=10k/100=100hz
	PWMPER23  = 10000;  //通道23的周期为占空比例范围10000    频率=1M/10000=100hz
	PWMPER4  = 100;  //通道4的周期为占空比例范围100          频率=10k/100=100hz
	PWMPER5  = 100;  //通道5的周期为占空比例范围100          频率=10k/100=100hz
	PWMPER67  = 10000;  //通道67的周期为占空比例范围10000	 频率=8M/10000=800hz
	PWMDTY0  = 0;  //通道0的占空比为0%   
	PWMDTY1  = 0;  //通道1的占空比为0%   
	PWMDTY23  = 0;  //通道23的占空比为0%  
	PWMDTY4  = 0;  //通道4的占空比为0%   
	PWMDTY5  = 0;  //通道5的占空比为0%   
	PWMDTY67  = 0;  //通道67的占空比为0%  
	PWME_PWME0 = 1;    //使能通道0
	PWME_PWME1 = 1;    //使能通道1
	PWME_PWME3 = 1;    //使能通道23
	PWME_PWME4 = 1;    //使能通道4
	PWME_PWME5 = 1;    //使能通道5
	PWME_PWME7 = 1;    //使能通道67	

}
  /*
  //pwm初始化  混合控制      
void init_pwm_hybrids(void)
{
	//	PWMCTL_CON01= 1;   //联结通道0,1为16位的PWM
	PWMCTL_CON23= 1;   //联结通道2,3为16位的PWM
	//PWMCTL_CON45= 1;   //联结通道4,5为16位的PWM
	PWMCTL_CON67= 1;   //联结通道6,7为16位的PWM	
	//注意了，因为fcu板子设计的原因，电路控制是反向的，所以这里设置为低电平有效
	PWMPOL_PPOL0= 1;   //通道0的极性为低电平有效
	PWMPOL_PPOL1= 1;   //通道1的极性为低电平有效
	PWMPOL_PPOL3= 1;   //通道23的极性为低电平有效
	PWMPOL_PPOL4= 1;   //通道4的极性为低电平有效
	PWMPOL_PPOL5= 1;   //通道5的极性为低电平有效
	PWMPOL_PPOL7= 1;   //通道67的极性为低电平有效	
	PWMPRCLK = 0x36;   //A时钟的分频系数为64,频率为1MHz, B时钟的分频系数为8,频率为8MHz  (总线频率64M)
	PWMSCLA  =  50;   //SA时钟频率为10KHz（SA时钟 = A时钟 / 2 / PWMSCLA = 1M/2/50=10k）
	PWMSCLB  =  4;   //SB时钟频率为1000KHz（SB时钟 = B时钟 / 2 / PWMSCLB = 8M/2/4=1M）
	PWMCLK =0x3b;      //通道0和1用SA时钟10KHz，通道3用SB时钟1000KHz,  通道4和5用SA时钟10KHz，通道7用B时钟8MHz
	PWMCAE   = 0x00;   //脉冲模式为左对齐模式
	PWMPER0  = 100;  //通道0的周期为占空比例范围100          频率=10k/100=100hz
	PWMPER1  = 100;  //通道1的周期为占空比例范围100          频率=10k/100=100hz
	PWMPER23  = 10000;  //通道23的周期为占空比例范围10000    频率=1M/10000=100hz
	PWMPER4  = 100;  //通道4的周期为占空比例范围100          频率=10k/100=100hz
	PWMPER5  = 100;  //通道5的周期为占空比例范围100          频率=10k/100=100hz
	PWMPER67  = 8888;  //通道67的周期为占空比例范围10000	 频率=8M/8888=900hz
	PWMDTY0  = 0;  //通道0的占空比为0%   
	PWMDTY1  = 0;  //通道1的占空比为0%   
	PWMDTY23  = 0;  //通道23的占空比为0%  
	PWMDTY4  = 0;  //通道4的占空比为0%   
	PWMDTY5  = 0;  //通道5的占空比为0%   
	PWMDTY67  = 0;  //通道67的占空比为0%  
	PWME_PWME0 = 1;    //使能通道0
	PWME_PWME1 = 1;    //使能通道1
	PWME_PWME3 = 1;    //使能通道23
	PWME_PWME4 = 1;    //使能通道4
	PWME_PWME5 = 1;    //使能通道5
	PWME_PWME7 = 1;    //使能通道67	

}
 */
//pwm设置某个通道的周期
void pwm_set_period(enum Pwm_channel pwm_channel, Word period)
{
	switch(pwm_channel)
	{
	case pwm_channel_0:
		PWMPER0 = (byte)period;
		break;
	case pwm_channel_1:
		PWMPER0 = (byte)period;
		break;
	case pwm_channel_2:
		PWMPER0 = (byte)period;
		break;
	case pwm_channel_3:
		PWMPER0 = (byte)period;
		break;
	case pwm_channel_4:
		PWMPER0 = (byte)period;
		break;
	case pwm_channel_5:
		PWMPER0 = (byte)period;
		break;
	case pwm_channel_6:
		PWMPER0 = (byte)period;
		break;
	case pwm_channel_7:
		PWMPER0 = (byte)period;
		break;                               
	case pwm_channel_01:
		PWMPER01 = period;
		break;
	case pwm_channel_23:
		PWMPER23 = period;
		break;
	case pwm_channel_45:
		PWMPER45 = period;
		break;
	case pwm_channel_67:
		PWMPER67 = period;
		break;

	}
}

//pwm设置某个通道的占空比
void pwm_set_dutyfactor(enum Pwm_channel pwm_channel, Word dutyfactor)
{
	switch(pwm_channel)
	{
	case pwm_channel_0:
		PWMDTY0 = (byte)dutyfactor;
		break;                                         
	case pwm_channel_1:
		PWMDTY1 = (byte)dutyfactor;
		break;
	case pwm_channel_2:
		PWMDTY2 = (byte)dutyfactor;
		break;
	case pwm_channel_3:
		PWMDTY3 = (byte)dutyfactor;
		break;
	case pwm_channel_4:
		PWMDTY4 = (byte)dutyfactor;
		break;
	case pwm_channel_5:
		PWMDTY5 = (byte)dutyfactor;
		break;
	case pwm_channel_6:
		PWMDTY6 = (byte)dutyfactor;
		break;
	case pwm_channel_7:
		PWMDTY7 = (byte)dutyfactor;
		break;
	case pwm_channel_01:
		PWMDTY01 = dutyfactor;
		break;
	case pwm_channel_23:
		PWMDTY23 = dutyfactor;
		break;
	case pwm_channel_45:
		PWMDTY45 = dutyfactor;
		break;
	case pwm_channel_67:
		PWMDTY67 = dutyfactor;
		break;

	}
}