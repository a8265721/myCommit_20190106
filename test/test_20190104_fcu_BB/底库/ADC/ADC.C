#include "ADC.h"
#include "delay.h"
#pragma MESSAGE DISABLE C5919
extern struct ATD_DATA ADT_D;


//初始化AD模块
void ATD_INIT(u8 Pattern,u8 Interruption_switch,u8 Collection_channel_number ) 
{  
 ATD0CTL1_SRES = Pattern;  //选用12位模数转换
 ATD1CTL1_SRES = Pattern;
 ATD0CTL2 = Interruption_switch;  //启动A/D模块,快速清零
 ATD1CTL2 = Interruption_switch;   
 ATD0CTL3 = Collection_channel_number;  
 ATD1CTL3 = Collection_channel_number;
 ATD0CTL4 = 0x07;   //AD模块时钟频率为2MHz ATDClock=[BusClock*0.5]/[PRS+1]
 ATD1CTL4 = 0x07;
}

//AD转换10-12位
u16 AD_Conversion(u8 AD_sele,u8 CH_sele) 
{
   u16 AD_data=0; 
   Channel_selection(AD_sele,CH_sele);
   if(AD_sele==1) 
   {
      if(CH_sele==0x10)  asm NOP;
      else
      {
        while(!ATD0STAT0_SCF);
        AD_data = ATD0DR0;
      }  
   }
   else if(AD_sele==2) 
   {
      if(CH_sele==0x10)  asm NOP;
      else
      {
        while(!ATD1STAT0_SCF);
        AD_data = ATD1DR0;
      }
    }
   return(AD_data);
}

void Channel_selection(u8 AD_selection,u8 CH_selection) 
{
   u8 AD_selection_dat = AD_selection;
   if(AD_selection_dat==1) ATD0CTL5 = CH_selection;
   else if(AD_selection_dat==2) ATD1CTL5 = CH_selection;
  
}

void ATD_Data_initialization(void)
{	
	 u8 time=0;
	 ADT_D.ATD0_Completion_mark=0;
	 ADT_D.ATD1_Completion_mark=0;
	 for(time=0;time<24;time++) 
	 { 
     ADT_D.continuous_sampling_data[time]=0;   
     ADT_D.Single_sampling_data[time]=0;
	 }
}

u16 ADC_Average(u8 AD_SE,u8 CH_SE,u8 times)
{
	float ADC_data=0.00F;
	u8 t;
	for(t=0;t<times;t++)
	{
		ADC_data+=AD_Conversion(AD_SE,CH_SE); //单次采集模式
		delay_ms(1);
	}
	ADC_data=ADC_data/times;
	ADC_data=ADC_data/0.8192F;
	return (u16)ADC_data;  //返回电压值放大1000倍
} 

#pragma CODE_SEG __NEAR_SEG NON_BANKED
interrupt 22U void ATD_ISR0(void)
{    
  ADT_D.continuous_sampling_data[0] =ATD0DR0;
  ADT_D.continuous_sampling_data[1] =ATD0DR1;
  ADT_D.continuous_sampling_data[2] =ATD0DR2;
  ADT_D.continuous_sampling_data[3] =ATD0DR3;
  ADT_D.continuous_sampling_data[4] =ATD0DR4;
  ADT_D.continuous_sampling_data[5] =ATD0DR5;
  ADT_D.continuous_sampling_data[6] =ATD0DR6;
  ADT_D.continuous_sampling_data[7] =ATD0DR7;
  ADT_D.continuous_sampling_data[8] =ATD0DR8;
  ADT_D.continuous_sampling_data[9] =ATD0DR9;
  ADT_D.continuous_sampling_data[10]=ATD0DR10;
  ADT_D.continuous_sampling_data[11]=ATD0DR11;
  ADT_D.continuous_sampling_data[12]=ATD0DR12;
  ADT_D.continuous_sampling_data[13]=ATD0DR13;
  ADT_D.continuous_sampling_data[14]=ATD0DR14;
  ADT_D.continuous_sampling_data[15]=ATD0DR15;
  ADT_D.ATD0_Completion_mark=1;  
}

interrupt 23U void ATD_ISR1(void)
{      
  ADT_D.continuous_sampling_data[16] =ATD1DR0;
  ADT_D.continuous_sampling_data[17] =ATD1DR1;
  ADT_D.continuous_sampling_data[18] =ATD1DR2;
  ADT_D.continuous_sampling_data[19] =ATD1DR3;
  ADT_D.continuous_sampling_data[20] =ATD1DR4;
  ADT_D.continuous_sampling_data[21] =ATD1DR5;
  ADT_D.continuous_sampling_data[22] =ATD1DR6;
  ADT_D.continuous_sampling_data[23] =ATD1DR7; 
  ADT_D.ATD1_Completion_mark=1;   
}
#pragma CODE_SEG DEFAULT