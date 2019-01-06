
#include "pwm.h"

//pwm��������ռ�ձ�
float dutyfactor_test = 0;

//pwm��ʼ��  ���Ƽ��� ����2��pwm�ϲ�Ϊһ�� ���������Ƶ�ʺ�ռ�ձȾ���
void init_pwm_cascade(void) 
{
	PWMCTL_CON01= 1;   //����ͨ��0,1Ϊ16λ��PWM
	PWMCTL_CON23= 1;   //����ͨ��2,3Ϊ16λ��PWM
	PWMCTL_CON45= 1;   //����ͨ��4,5Ϊ16λ��PWM
	PWMCTL_CON67= 1;   //����ͨ��6,7Ϊ16λ��PWM	
	//ע���ˣ���Ϊfcu������Ƶ�ԭ�򣬵�·�����Ƿ���ģ�������������Ϊ�͵�ƽ��Ч
	PWMPOL_PPOL1= 1;   //ͨ��01�ļ���Ϊ�͵�ƽ��Ч
	PWMPOL_PPOL3= 1;   //ͨ��23�ļ���Ϊ�͵�ƽ��Ч
	PWMPOL_PPOL5= 1;   //ͨ��45�ļ���Ϊ�͵�ƽ��Ч
	PWMPOL_PPOL7= 1;   //ͨ��67�ļ���Ϊ�͵�ƽ��Ч	
	//	PWMPRCLK = 0x55;   //Aʱ�Ӻ�Bʱ�ӵķ�Ƶϵ��Ϊ32,Ƶ��Ϊ1MHz
	PWMPRCLK = 0x00;   //Aʱ�Ӻ�Bʱ�ӵķ�Ƶϵ��Ϊ1,Ƶ��Ϊ64MHz  (����Ƶ��64M)
	PWMSCLA  =  32;   //SAʱ��Ƶ��Ϊ1000KHz��SAʱ�� = Aʱ�� / 2 / PWMSCLA��
	PWMSCLB  =  32;   //SBʱ��Ƶ��Ϊ1000KHz��SBʱ�� = Bʱ�� / 2 / PWMSCLB��
	//	PWMCLK =0x0a;      //ͨ��01��SAʱ����Ϊʱ��Դ,ͨ��23��SBʱ����Ϊʱ��Դ
	PWMCLK =0xA2;      //ͨ��01 45 67��Sʱ����Ϊʱ��Դ,ͨ��23�ñ�׼ʱ����Ϊʱ��Դ
	PWMCAE   = 0x00;   //����ģʽΪ�����ģʽ
	PWMPER01  = 10000;  //ͨ��01������Ϊռ�ձ�����Χ10000
	PWMPER23  = 10000;  //ͨ��23������Ϊռ�ձ�����Χ10000
	PWMPER45  = 10000;  //ͨ��45������Ϊռ�ձ�����Χ10000
	PWMPER67  = 10000;  //ͨ��67������Ϊռ�ձ�����Χ10000	
	PWMDTY01  = 0;  //ͨ��01��ռ�ձ�Ϊ0%   
	PWMDTY23  = 0;  //ͨ��23��ռ�ձ�Ϊ0%  
	PWMDTY45  = 0;  //ͨ��01��ռ�ձ�Ϊ0%   
	PWMDTY67  = 0;  //ͨ��23��ռ�ձ�Ϊ0%  	
	PWME_PWME1 = 1;    //ʹ��ͨ��01
	PWME_PWME3 = 1;    //ʹ��ͨ��23
	PWME_PWME5 = 1;    //ʹ��ͨ��45
	PWME_PWME7 = 1;    //ʹ��ͨ��67	
}



//pwm��ʼ��  �������á�
void init_pwm_single(void)
{
	PWMPOL = 0x0f;		//ͨ��0~3�ļ���Ϊ�ߵ�ƽ��Ч

	PWMPRCLK = 0x55;	//Aʱ�Ӻ�Bʱ�ӵķ�Ƶϵ��Ϊ32,Ƶ��Ϊ1MHz��a bʱ��Ƶ��=����Ƶ��/��2��5�η��� ��
	PWMSCLA  =  50;		//SAʱ��Ƶ��Ϊ10KHz��SA��ʱ��Ƶ��=a��ʱ��Ƶ��/2/50��
	PWMSCLB  =  50;		//SBʱ��Ƶ��Ϊ10KHz��SB��ʱ��Ƶ��=b��ʱ��Ƶ��/2/50��
	PWMCLK = 0x0f;		//ͨ��0��1��SAʱ����Ϊʱ��Դ,ͨ��2��3��SBʱ����Ϊʱ��Դ
	//    PWMCLK = 0x00;		//��ʹ��Ĭ�ϵ�ʱ�ӡ�

	PWMCAE   = 0x00;	//����ģʽΪ�����ģʽ

	PWMPER0 = 100;		//ͨ��0������Ϊ100Hz��ͨ��1������=��Ӧ��ʱ��Ƶ��/100��
	PWMPER1 = 100;		//ͨ��1������Ϊ100Hz��ע���ˣ���ͨ��ֻ��8bit�� ˫ͨ������16bit��  
	PWMPER2 = 100;		//ͨ��2������Ϊ100Hz 
	PWMPER3 = 100;		//ͨ��3������Ϊ100Hz 

	PWMDTY0 = 10;		//ͨ��0��ռ�ձ�Ϊ10%  
	PWMDTY1 = 50;		//ͨ��0��ռ�ձ�Ϊ50%  
	PWMDTY2 = 90;		//ͨ��0��ռ�ձ�Ϊ90%  
	PWMDTY3 = 100;		//ͨ��0��ռ�ձ�Ϊ100%  

	PWME = 0x0f;		//ʹ��ͨ��0~3
}

           /*
//pwm��ʼ��  ��Ͽ���      
void init_pwm_hybrids(void)
{
	//	PWMCTL_CON01= 1;   //����ͨ��0,1Ϊ16λ��PWM
	PWMCTL_CON23= 1;   //����ͨ��2,3Ϊ16λ��PWM
	//PWMCTL_CON45= 1;   //����ͨ��4,5Ϊ16λ��PWM
	PWMCTL_CON67= 1;   //����ͨ��6,7Ϊ16λ��PWM	
	//ע���ˣ���Ϊfcu������Ƶ�ԭ�򣬵�·�����Ƿ���ģ�������������Ϊ�͵�ƽ��Ч
	PWMPOL_PPOL0= 1;   //ͨ��0�ļ���Ϊ�͵�ƽ��Ч
	PWMPOL_PPOL1= 1;   //ͨ��1�ļ���Ϊ�͵�ƽ��Ч
	PWMPOL_PPOL3= 1;   //ͨ��23�ļ���Ϊ�͵�ƽ��Ч
	PWMPOL_PPOL4= 1;   //ͨ��4�ļ���Ϊ�͵�ƽ��Ч
	PWMPOL_PPOL5= 1;   //ͨ��5�ļ���Ϊ�͵�ƽ��Ч
	PWMPOL_PPOL7= 1;   //ͨ��67�ļ���Ϊ�͵�ƽ��Ч	
	PWMPRCLK = 0x06;   //Aʱ�ӵķ�Ƶϵ��Ϊ64,Ƶ��Ϊ1MHz, Bʱ�ӵķ�Ƶϵ��Ϊ1,Ƶ��Ϊ64MHz  (����Ƶ��64M)
	PWMSCLA  =  50;   //SAʱ��Ƶ��Ϊ10KHz��SAʱ�� = Aʱ�� / 2 / PWMSCLA��
//	PWMSCLB  =  32;   //SBʱ��Ƶ��Ϊ1000KHz��SBʱ�� = Bʱ�� / 2 / PWMSCLB��
	PWMSCLB  =  5;   //SBʱ��Ƶ��Ϊ1000KHz��SBʱ�� = Bʱ�� / 2 / PWMSCLB��
//	PWMCLK =0x3b;      //ͨ��0��1��SAʱ��10KHz��ͨ��3��SBʱ��1000KHz,  ͨ��4��5��SAʱ��10KHz��ͨ��7��Bʱ��64MHz
	PWMCLK =0xbb;      //ͨ��0��1��SAʱ��10KHz��ͨ��3��SBʱ��1000KHz,  ͨ��4��5��SAʱ��10KHz��ͨ��7��Bʱ��64MHz
	PWMCAE   = 0x00;   //����ģʽΪ�����ģʽ
	PWMPER0  = 100;  //ͨ��0������Ϊռ�ձ�����Χ100
	PWMPER1  = 100;  //ͨ��1������Ϊռ�ձ�����Χ100
	PWMPER23  = 10000;  //ͨ��23������Ϊռ�ձ�����Χ10000
	PWMPER4  = 100;  //ͨ��4������Ϊռ�ձ�����Χ100
	PWMPER5  = 100;  //ͨ��5������Ϊռ�ձ�����Χ100
	PWMPER67  = 10000;  //ͨ��67������Ϊռ�ձ�����Χ10000	
	PWMDTY0  = 0;  //ͨ��0��ռ�ձ�Ϊ0%   
	PWMDTY1  = 0;  //ͨ��1��ռ�ձ�Ϊ0%   
	PWMDTY23  = 0;  //ͨ��23��ռ�ձ�Ϊ0%  
	PWMDTY4  = 0;  //ͨ��4��ռ�ձ�Ϊ0%   
	PWMDTY5  = 0;  //ͨ��5��ռ�ձ�Ϊ0%   
	PWMDTY67  = 0;  //ͨ��67��ռ�ձ�Ϊ0%  
	PWME_PWME0 = 1;    //ʹ��ͨ��0
	PWME_PWME1 = 1;    //ʹ��ͨ��1
	PWME_PWME3 = 1;    //ʹ��ͨ��23
	PWME_PWME4 = 1;    //ʹ��ͨ��4
	PWME_PWME5 = 1;    //ʹ��ͨ��5
	PWME_PWME7 = 1;    //ʹ��ͨ��67	

}
  */
  
  //pwm��ʼ��  ��Ͽ���      
void init_pwm_hybrids(void)
{
	//	PWMCTL_CON01= 1;   //����ͨ��0,1Ϊ16λ��PWM
	PWMCTL_CON23= 1;   //����ͨ��2,3Ϊ16λ��PWM
	//PWMCTL_CON45= 1;   //����ͨ��4,5Ϊ16λ��PWM
	PWMCTL_CON67= 1;   //����ͨ��6,7Ϊ16λ��PWM	
	//ע���ˣ���Ϊfcu������Ƶ�ԭ�򣬵�·�����Ƿ���ģ�������������Ϊ�͵�ƽ��Ч
	PWMPOL_PPOL0= 1;   //ͨ��0�ļ���Ϊ�͵�ƽ��Ч
	PWMPOL_PPOL1= 1;   //ͨ��1�ļ���Ϊ�͵�ƽ��Ч
	PWMPOL_PPOL3= 1;   //ͨ��23�ļ���Ϊ�͵�ƽ��Ч
	PWMPOL_PPOL4= 1;   //ͨ��4�ļ���Ϊ�͵�ƽ��Ч
	PWMPOL_PPOL5= 1;   //ͨ��5�ļ���Ϊ�͵�ƽ��Ч
	PWMPOL_PPOL7= 1;   //ͨ��67�ļ���Ϊ�͵�ƽ��Ч	
	PWMPRCLK = 0x36;   //Aʱ�ӵķ�Ƶϵ��Ϊ64,Ƶ��Ϊ1MHz, Bʱ�ӵķ�Ƶϵ��Ϊ8,Ƶ��Ϊ8MHz  (����Ƶ��64M)
	PWMSCLA  =  50;   //SAʱ��Ƶ��Ϊ10KHz��SAʱ�� = Aʱ�� / 2 / PWMSCLA = 1M/2/50=10k��
	PWMSCLB  =  4;   //SBʱ��Ƶ��Ϊ1000KHz��SBʱ�� = Bʱ�� / 2 / PWMSCLB = 8M/2/4=1M��
	PWMCLK =0x3b;      //ͨ��0��1��SAʱ��10KHz��ͨ��3��SBʱ��1000KHz,  ͨ��4��5��SAʱ��10KHz��ͨ��7��Bʱ��8MHz
	PWMCAE   = 0x00;   //����ģʽΪ�����ģʽ
	PWMPER0  = 100;  //ͨ��0������Ϊռ�ձ�����Χ100          Ƶ��=10k/100=100hz
	PWMPER1  = 100;  //ͨ��1������Ϊռ�ձ�����Χ100          Ƶ��=10k/100=100hz
	PWMPER23  = 10000;  //ͨ��23������Ϊռ�ձ�����Χ10000    Ƶ��=1M/10000=100hz
	PWMPER4  = 100;  //ͨ��4������Ϊռ�ձ�����Χ100          Ƶ��=10k/100=100hz
	PWMPER5  = 100;  //ͨ��5������Ϊռ�ձ�����Χ100          Ƶ��=10k/100=100hz
	PWMPER67  = 10000;  //ͨ��67������Ϊռ�ձ�����Χ10000	 Ƶ��=8M/10000=800hz
	PWMDTY0  = 0;  //ͨ��0��ռ�ձ�Ϊ0%   
	PWMDTY1  = 0;  //ͨ��1��ռ�ձ�Ϊ0%   
	PWMDTY23  = 0;  //ͨ��23��ռ�ձ�Ϊ0%  
	PWMDTY4  = 0;  //ͨ��4��ռ�ձ�Ϊ0%   
	PWMDTY5  = 0;  //ͨ��5��ռ�ձ�Ϊ0%   
	PWMDTY67  = 0;  //ͨ��67��ռ�ձ�Ϊ0%  
	PWME_PWME0 = 1;    //ʹ��ͨ��0
	PWME_PWME1 = 1;    //ʹ��ͨ��1
	PWME_PWME3 = 1;    //ʹ��ͨ��23
	PWME_PWME4 = 1;    //ʹ��ͨ��4
	PWME_PWME5 = 1;    //ʹ��ͨ��5
	PWME_PWME7 = 1;    //ʹ��ͨ��67	

}
  /*
  //pwm��ʼ��  ��Ͽ���      
void init_pwm_hybrids(void)
{
	//	PWMCTL_CON01= 1;   //����ͨ��0,1Ϊ16λ��PWM
	PWMCTL_CON23= 1;   //����ͨ��2,3Ϊ16λ��PWM
	//PWMCTL_CON45= 1;   //����ͨ��4,5Ϊ16λ��PWM
	PWMCTL_CON67= 1;   //����ͨ��6,7Ϊ16λ��PWM	
	//ע���ˣ���Ϊfcu������Ƶ�ԭ�򣬵�·�����Ƿ���ģ�������������Ϊ�͵�ƽ��Ч
	PWMPOL_PPOL0= 1;   //ͨ��0�ļ���Ϊ�͵�ƽ��Ч
	PWMPOL_PPOL1= 1;   //ͨ��1�ļ���Ϊ�͵�ƽ��Ч
	PWMPOL_PPOL3= 1;   //ͨ��23�ļ���Ϊ�͵�ƽ��Ч
	PWMPOL_PPOL4= 1;   //ͨ��4�ļ���Ϊ�͵�ƽ��Ч
	PWMPOL_PPOL5= 1;   //ͨ��5�ļ���Ϊ�͵�ƽ��Ч
	PWMPOL_PPOL7= 1;   //ͨ��67�ļ���Ϊ�͵�ƽ��Ч	
	PWMPRCLK = 0x36;   //Aʱ�ӵķ�Ƶϵ��Ϊ64,Ƶ��Ϊ1MHz, Bʱ�ӵķ�Ƶϵ��Ϊ8,Ƶ��Ϊ8MHz  (����Ƶ��64M)
	PWMSCLA  =  50;   //SAʱ��Ƶ��Ϊ10KHz��SAʱ�� = Aʱ�� / 2 / PWMSCLA = 1M/2/50=10k��
	PWMSCLB  =  4;   //SBʱ��Ƶ��Ϊ1000KHz��SBʱ�� = Bʱ�� / 2 / PWMSCLB = 8M/2/4=1M��
	PWMCLK =0x3b;      //ͨ��0��1��SAʱ��10KHz��ͨ��3��SBʱ��1000KHz,  ͨ��4��5��SAʱ��10KHz��ͨ��7��Bʱ��8MHz
	PWMCAE   = 0x00;   //����ģʽΪ�����ģʽ
	PWMPER0  = 100;  //ͨ��0������Ϊռ�ձ�����Χ100          Ƶ��=10k/100=100hz
	PWMPER1  = 100;  //ͨ��1������Ϊռ�ձ�����Χ100          Ƶ��=10k/100=100hz
	PWMPER23  = 10000;  //ͨ��23������Ϊռ�ձ�����Χ10000    Ƶ��=1M/10000=100hz
	PWMPER4  = 100;  //ͨ��4������Ϊռ�ձ�����Χ100          Ƶ��=10k/100=100hz
	PWMPER5  = 100;  //ͨ��5������Ϊռ�ձ�����Χ100          Ƶ��=10k/100=100hz
	PWMPER67  = 8888;  //ͨ��67������Ϊռ�ձ�����Χ10000	 Ƶ��=8M/8888=900hz
	PWMDTY0  = 0;  //ͨ��0��ռ�ձ�Ϊ0%   
	PWMDTY1  = 0;  //ͨ��1��ռ�ձ�Ϊ0%   
	PWMDTY23  = 0;  //ͨ��23��ռ�ձ�Ϊ0%  
	PWMDTY4  = 0;  //ͨ��4��ռ�ձ�Ϊ0%   
	PWMDTY5  = 0;  //ͨ��5��ռ�ձ�Ϊ0%   
	PWMDTY67  = 0;  //ͨ��67��ռ�ձ�Ϊ0%  
	PWME_PWME0 = 1;    //ʹ��ͨ��0
	PWME_PWME1 = 1;    //ʹ��ͨ��1
	PWME_PWME3 = 1;    //ʹ��ͨ��23
	PWME_PWME4 = 1;    //ʹ��ͨ��4
	PWME_PWME5 = 1;    //ʹ��ͨ��5
	PWME_PWME7 = 1;    //ʹ��ͨ��67	

}
 */
//pwm����ĳ��ͨ��������
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

//pwm����ĳ��ͨ����ռ�ձ�
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