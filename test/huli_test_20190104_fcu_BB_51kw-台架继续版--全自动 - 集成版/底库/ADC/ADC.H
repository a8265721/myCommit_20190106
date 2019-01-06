#ifndef _ADC_H
#define _ADC_H
#include "derivative.h"


#define  ADC_8BIT		     0x00            //8位模数转换
#define  ADC_10BIT		   0x01            //10位模数转换
#define  ADC_12BIT		   0x02            //12位模数转换

#define  ADC_interrupt_Open   0x42       //打开AD中断
#define  ADC_interrupt_Close  0x40       //关闭AD中断

#define  Collection_channel_num16  0x80  //采集16个通道
#define  Collection_channel_num1   0x88  //采集1个通道
#define  Collection_channel_num2   0x90  //采集2个通道
#define  Collection_channel_num3   0x98  //采集3个通道
#define  Collection_channel_num4   0xA0  //采集4个通道
#define  Collection_channel_num5   0xA8  //采集5个通道
#define  Collection_channel_num6   0xB0  //采集6个通道
#define  Collection_channel_num7   0xB8  //采集7个通道
#define  Collection_channel_num8   0xC0  //采集8个通道
#define  Collection_channel_num9   0xC8  //采集9个通道
#define  Collection_channel_num10  0xD0  //采集10个通道
#define  Collection_channel_num11  0xD8  //采集11个通道
#define  Collection_channel_num12  0xE0  //采集12个通道
#define  Collection_channel_num13  0xE8  //采集13个通道
#define  Collection_channel_num14  0xF0  //采集14个通道
#define  Collection_channel_num15  0xF8  //采集15个通道



#define  ADC0_CH	 1
#define  ADC1_CH	 2

#define  ADC_Single_sampling_CH0	 0x00
#define  ADC_Single_sampling_CH1 	 0x01	
#define  ADC_Single_sampling_CH2	 0x02	
#define  ADC_Single_sampling_CH3	 0x03
#define  ADC_Single_sampling_CH4	 0x04	
#define  ADC_Single_sampling_CH5	 0x05	
#define  ADC_Single_sampling_CH6	 0x06	
#define  ADC_Single_sampling_CH7	 0x07	
#define  ADC_Single_sampling_CH8	 0x08	
#define  ADC_Single_sampling_CH9	 0x09	
#define  ADC_Single_sampling_CH10	 0x0A	
#define  ADC_Single_sampling_CH11	 0x0B	
#define  ADC_Single_sampling_CH12	 0x0C	
#define  ADC_Single_sampling_CH13	 0x0D	
#define  ADC_Single_sampling_CH14	 0x0E	
#define  ADC_Single_sampling_CH15	 0x0F
#define  ADC0_continuous_sampling	 0x10	

#define  ADC_Single_sampling_CH16	 0x00	
#define  ADC_Single_sampling_CH17  0x01	
#define  ADC_Single_sampling_CH18	 0x02	
#define  ADC_Single_sampling_CH19	 0x03	
#define  ADC_Single_sampling_CH20  0x04	
#define  ADC_Single_sampling_CH21	 0x05	
#define  ADC_Single_sampling_CH22	 0x06	
#define  ADC_Single_sampling_CH23	 0x07	
#define  ADC1_continuous_sampling	 0x10


struct ATD_DATA    
{    
    u8  ATD1_Completion_mark; 
    u8  ATD0_Completion_mark;  
    u16 continuous_sampling_data[24];
    u16 Single_sampling_data[24];   
};

void ATD_INIT(u8 Pattern,u8 Interruption_switch,u8 Collection_channel_number ); //初始化ADC   
u16 AD_Conversion(u8 AD_sele,u8 CH_sele);     //12位采样
void Channel_selection(u8 AD_selection,u8 CH_selection);
void ATD_Data_initialization(void);   
u16 ADC_Average(u8 AD_SE,u8 CH_SE,u8 times); //ADC滤波 

#endif