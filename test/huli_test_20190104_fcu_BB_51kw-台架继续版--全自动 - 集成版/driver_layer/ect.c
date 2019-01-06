
#include "ect.h"

u32 system_time = 0;
u32 system_time_old = 0;


u16 delaytime = 0;
u16 time1 = 0;
u16 time2 = 0;
                                                   
u16 delaytime3 = 0;
u16 time3 = 0;
u16 time4 = 0;

//ע���ˣ�һ����8����ʱ�������ǹ���һ��ʱ�ӣ�����һ���������Ĵ���
//�������Լ��������ж�ϵͳ �� �ȽϼĴ�����

//���룺����⵽�������ŵ��ⲿ�¼�ʱ�����Բ�����־λ���ж�
//��������������Ĵ��� == �ȽϼĴ��� ʱ�����Բ�����־λ���жϣ� �����Զ��������ֱ�Ӳ�����

//����ȽϺ����벶�� �� PT0~7 ��������


//����Ƚϳ�ʼ��
void ect_init_output(void)
{
	ECT_TSCR1_TFFCA = 1;  // ��ʱ����־λ�������
	ECT_TSCR1_TEN = 1;    // ��ʱ��ʹ��λ. 1=����ʱ����������; 0=ʹ����ʱ����������(����������)
	ECT_TIOS  = 0x7e;      //ָ��1~6Ϊ����ȽϷ�ʽ
	ECT_TCTL1 = 0x00;	    // ���ĸ�ͨ������Ϊ��ʱ����������ŶϿ�
	ECT_TCTL2 = 0x00;     // ǰ�ĸ�ͨ������Ϊ��ʱ����������ŶϿ�
	ECT_TIE   = 0x00;     // ��ֹ����ͨ����ʱ�ж�
	ECT_TSCR2 = 0x07;	    // Ԥ��Ƶϵ��pr2-pr0:111,,ʱ������Ϊ4us, ������ʱ�� / ��2��7�η��� = 250K HZ��
	ECT_TFLG1 = 0xff;	    // �����IC/OC�жϱ�־λ
	ECT_TFLG2 = 0xff;     // ������ɶ�ʱ���жϱ�־λ

	//������ȡ ��־λ	ECT_TFLG1_C0F ~ ECT_TFLG1_C7F  
	//����д�� ����λ	ECT_TC0 ~ ECT_TC7
}


//���벶���ʼ��
void ect_init_input(void)
{
	ECT_TSCR1_TFFCA = 1;  // ��ʱ����־λ�������
	ECT_TSCR1_TEN = 1;    // ��ʱ��ʹ��λ. 1=����ʱ����������; 0=ʹ����ʱ����������(����������)
	ECT_TIOS  = 0x7e;      //ָ��ͨ��7��0Ϊ���벶׽��ʽ
	ECT_TCTL3 = 0x40;	    // ����ͨ��7Ϊ��׽�����ط�ʽ
	ECT_TCTL4 = 0x01;	    // ����ͨ��0Ϊ��׽�����ط�ʽ
	ECT_TIE   = 0x81;     // ����ͨ��7��0��ʱ�ж�
	ECT_TSCR2 = 0x07;	    // Ԥ��Ƶϵ��pr2-pr0:111,ʱ������Ϊ4us,������ʱ�� / ��2��7�η��� = 250K HZ��
	ECT_TFLG1 = 0xff;	    // �����IC/OC�жϱ�־λ
	ECT_TFLG2 = 0xff;     // ������ɶ�ʱ���жϱ�־λ

	//������ȡ ��־λ	ECT_TFLG1_C0F ~ ECT_TFLG1_C7F  
	//������ȡ ����λ	ECT_TC0 ~ ECT_TC7
}


/*************************************************************/
/*                   ���벶׽�жϺ���                        */
/*************************************************************/
#pragma CODE_SEG __NEAR_SEG NON_BANKED
interrupt void ect0_interrupt_capture(void) 
{
	EnableInterrupts;
	if(ECT_TFLG1_C0F == 1)
		ECT_TFLG1_C0F = 1;
	time1 = time2;
	time2 = ECT_TC0;
	delaytime = time2-time1;
	//	LEDCPU = ~LEDCPU;
}
#pragma CODE_SEG DEFAULT

#pragma CODE_SEG __NEAR_SEG NON_BANKED
interrupt void ect7_interrupt_capture(void) 
{
	EnableInterrupts;
	if(ECT_TFLG1_C7F == 1)
		ECT_TFLG1_C7F = 1;
	time3 = time4;
	time4 = ECT_TC7;
	delaytime3 = time4-time3;
	//	LEDCPU = ~LEDCPU;
}
#pragma CODE_SEG DEFAULT


//ע���ˣ������ۼ��������벶��Ļ�������ӵĹ��ܡ�һ��Ҳʹ��ͬһ��ʱ��
//�����ۼ���4��8λͨ������PT0~3�������š�������ΪPACN0~3
//Ҳ���Լ���Ϊ2��16λ�ġ�PACA��PT7�������ţ�PACB��PT0�������š�������ΪPACA��ӦPACN32��PACB��ӦPACN10��
//ע���ˣ���ʱ���ļ������ǰ������ۼӵģ������ۼ��� ����⵽�ⲿ�����¼�֮��Ż�+1
//��ʱ�������ۼӳ�ʼ��
void ect_init_pai(void)
{
	ECT_TSCR1_TFFCA = 1;  // ��ʱ����־λ�������
	ECT_TSCR1_TEN = 1;    // ��ʱ��ʹ��λ. 1=����ʱ����������; 0=ʹ����ʱ����������(����������)
	ECT_TIOS  = 0x0f;      //IOC7��������Ϊ���룬�����޷���׽
	ECT_TCTL1 = 0x00;	    // ���ĸ�ͨ������Ϊ��ʱ����������ŶϿ�
	ECT_TCTL2 = 0x00;     // ǰ�ĸ�ͨ������Ϊ��ʱ����������ŶϿ�
	ECT_TIE   = 0x00;     // ��ֹ����ͨ����ʱ�ж�
	ECT_TSCR2 = 0x07;	    // Ԥ��Ƶϵ��pr2-pr0:111,,ʱ������Ϊ4us,
	ECT_TFLG1 = 0xff;	    // �����IC/OC�жϱ�־λ
	ECT_TFLG2 = 0xff;     // ������ɶ�ʱ���жϱ�־λ

	ECT_PACTL = 0x50;      //ʼ�������ۼ������ۼ������أ�����ΪPACA������PT7����

	//������ȡ ����λ	ECT_PACN3~ECT_PACN0  ���� ECT_PACN32��ECT_PACN10
}


//����ֻʹ���˶�ʱ��������¼���û��ʹ�����š�
//��Ϊʱ�������ǹ̶��ģ�4us * 0xffff�������������û��ʵ�����塣
//һ�������������Ƚϣ���һ�����pwm�źš����������ں㶨��ֻ��������ռ�ձȣ�
//��ʱ�������ʼ��
void ect_init_overflow(void)
{
	ECT_TSCR1_TFFCA = 1;  // ��ʱ����־λ�������
	ECT_TSCR1_TEN = 1;    // ��ʱ��ʹ��λ. 1=����ʱ����������; 0=ʹ����ʱ����������(����������)
	ECT_TIOS  = 0xff;     // ָ������ͨ��Ϊ����ȽϷ�ʽ
	ECT_TCTL1 = 0x00;	    // ���ĸ�ͨ������Ϊ��ʱ����������ŶϿ�
	ECT_TCTL2 = 0x08;     // ͨ��1���ڱȽ��¼�����ʱ��PT1���ű�Ϊ0
	ECT_TIE   = 0x00;     // ��ֹ����ͨ����ʱ�ж�
	ECT_TSCR2 = 0x80;	    // Ԥ��Ƶϵ��Ϊ0��ʹ������Ƶ��32Mhz��ʹ�ܶ�ʱ������ж�
	ECT_TFLG1 = 0xff;	    // �����IC/OC�жϱ�־λ
	ECT_TFLG2 = 0xff;     // ������ɶ�ʱ���жϱ�־λ


	ECT_TTOV = 0x02;      // ͨ��1��������¼�����ʱ��PT1���ŷ�ת
	ECT_TC1 = 0xc000;     //ռ�ձ�Ϊc000/ffff=75%  pwmƵ��Լ����32Mhz/65535=488HZ
	//���ڲ��ܵ���Ƶ�ʣ����Բ�����ʹ��ect��ģ��pwm��

	//����ж϶�ʱ����������Ϊ 4us * 0xFFFF 
	//������Ƚ�״̬ʱ����������TTOV�����л���Ӧ��������� 
}


/*************************************************************/
/*                      ��ʱ������ж�                       */
/*************************************************************/
#pragma CODE_SEG __NEAR_SEG NON_BANKED
interrupt void ect_interrupt_overflow(void)
{
	unsigned int temp;	
	EnableInterrupts;	
	if(ECT_TFLG2_TOF ==1)
	{
		temp=ECT_TCNT;           //���TOF��־
		PORTB_PB4 = 1- PORTB_PB4;
		//		printf("system_time 1= %0.0f  \r\n", (float)system_time);
		//		printf("system_time 2= %0.0f  \r\n", (float)system_time);
		//		printf("\r\n"); 
	}
}
#pragma CODE_SEG DEFAULT



//ģ���ݼ�ֻ��һ����ӵ�ж�����ʱ�ӣ�û�ж�Ӧ������
//ģ���ݼ���Ȼ��ʱ��ʱ������Ҳ�ǹ̶��ģ����ǿ����Զ�����������ֵ�����Զ����жϴ�����ʱ�䡣
//��ʱ��ģ���ݼ���ʼ��������ϵͳ�ı�׼ʱ�䡣
void ect_init_mdc(void)
{
    //ע���ˣ�fcu��pll��ϵͳƵ�ʸ�Ϊ��64M
	ECT_MCCTL = 0xc7;		//MCZI ʹ���жϣ�MODMC ����ѭ��������
	//MCEN ʹ��ģ���ݼ���MCPR1��MCPR0��Ƶϵ��16����Ϊ64Mhz/16=4MHz ������0.25us

	ECT_MCCNT = 4000;		//ģ���ݼ��������ĳ�ʼֵ����ô4000*0.25us=1ms����Ϊÿ1ms����һ���ж�
	ECT_MCCTL_FLMC = 1;		//��ECT_MCCNT�ĳ�ʼֵ ���ص��������У���ʱ����ʼ��ʱ��
}


/*************************************************************/
/*                      ��ʱ��ģ���ݼ��ж�                       */
/*************************************************************/
#pragma CODE_SEG __NEAR_SEG NON_BANKED
interrupt void ect_interrupt_mdc(void)
{     
	unsigned int temp;
	EnableInterrupts;
	if(ECT_MCFLG_MCZF ==1)
	{
		ECT_MCFLG_MCZF =1;           //û�������������
		temp=ECT_MCCNT;           //���TFLG2_MCFLG��־
		++system_time;

		if(system_time == 0xFFFFFFFF)
		{
			system_time = 0;

	//		Can_communication_protocol_clear_time(&can_communication_protocol_total);
			Can_communication_protocol2_clear_time(&can_communication_protocol2_total);
			//need pragrom
			//����Ҫ������г����У���ص�����ʱ��
		}
	}
}
#pragma CODE_SEG DEFAULT



//��ʱ��������λms������ʱ���
void ect_delay_ms(u32 delay_time)
{
	u32 time_temp = system_time;
	while(system_time - time_temp  <  delay_time)
	{}

}



//��ӡϵͳʱ�䡣���ڲ���ֱ�Ӵ�ӡ u32�����Ը�Ϊ��ӡʱ����
void printf_system_time(void)
{
	u32 time_temp = system_time;
	u16 day = 0;
	u16 hour = 0;
	u16 minute = 0;
	u16 second = 0;
	u16 millisecond = 0;

	millisecond = (u16)(time_temp % 1000);   
	time_temp = time_temp / 1000;

	second = (u16)(time_temp % 60);   
	time_temp = time_temp / 60;

	minute = (u16)(time_temp % 60);   
	time_temp = time_temp / 60;

	hour = (u16)(time_temp % 24); 

	day = (u16)(time_temp / 24);

	printf("system_time = %u day, %02u:%02u:%02u.%03u  \r\n", 
		day, hour, minute, second, millisecond);
}





//�ۺϰ汾
//ect��ʼ��
//t0Ϊ��ͨ�����벶��
//t1Ϊ����Ƚϡ���϶�ʱ������¼���ģ��pwm
//t7Ϊ����ȽϺ������ۼ�
void initialize_ect_ex(void)
{
	ECT_TSCR1_TFFCA = 1;  // ��ʱ����־λ�������
	ECT_TSCR1_TEN = 1;    // ��ʱ��ʹ��λ. 1=����ʱ����������; 0=ʹ����ʱ����������(����������)
	ECT_TIOS  = 0x7e;      //ָ��1~6Ϊ����ȽϷ�ʽ   ָ��ͨ��7��0Ϊ���벶׽��ʽ
	ECT_TCTL1 = 0x00;	    // ���ĸ�ͨ������Ϊ��ʱ����������ŶϿ�
	ECT_TCTL2 = 0x08;     // ͨ��1���ڱȽ��¼�����ʱ��PT1���ű�Ϊ0
	ECT_TTOV = 0x02;      // ͨ��1��������¼�����ʱ��PT1���ŷ�ת
	ECT_TCTL3 = 0x40;	    // ����ͨ��7Ϊ��׽�����ط�ʽ
	ECT_TCTL4 = 0x01;	    // ����ͨ��0Ϊ��׽�����ط�ʽ
	ECT_TIE   = 0x81;     // ����ͨ��7��0��ʱ�ж�
	ECT_TSCR2 = 0x87;	    // Ԥ��Ƶϵ��pr2-pr0:111,,ʱ������Ϊ4us, ʹ�ܶ�ʱ������ж�
	ECT_TFLG1 = 0xff;	    // �����IC/OC�жϱ�־λ
	ECT_TFLG2 = 0xff;     // ������ɶ�ʱ���жϱ�־λ

	ECT_TC1 = 0xc000;     //ռ�ձ�Ϊc000/ffff=75%  pwmƵ��Լ����32Mhz/65535=488HZ
	ECT_PACTL = 0x50;      //ʼ�������ۼ������ۼ������أ�����ΪPACA������PT7����
}





