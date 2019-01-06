#include "General_module.h" 
const short AD_Result[141] = {
	0xF9D,0xF95,0xF8E,0xF85,0xF7D,0xF74,0xF6A,0xF60,0xF55,0xF49,
	0xF3D,0xF30,0xF23,0xF15,0xF06,0xEF7,0xEE6,0xED5,0xEC3,0xEB1,
	0xE9D,0xE89,0xE73,0xE5D,0xE46,0xE2E,0xE15,0xDFB,0xDE0,0xDC5,
	0xDA8,0xD8A,0xD6B,0xD4C,0xD2B,0xD0A,0xCE7,0xCC4,0xCA0,0xC7B,
	0xC55,0xC2E,0xC07,0xBDE,0xBB6,0xB8C,0xB62,0xB37,0xB0B,0xADF,
	0xAB3,0xA86,0xA58,0xA2B,0x9FD,0x9CF,0x9A0,0x972,0x943,0x915,
	0x8E6,0x8B8,0x88A,0x85C,0x82E,0x800,0x7D3,0x7A6,0x779,0x74D,
	0x721,0x6F6,0x6CB,0x6A1,0x677,0x64E,0x626,0x5FE,0x5D7,0x5B1,
	0x58B,0x566,0x542,0x51E,0x4FB,0x4D9,0x4B8,0x497,0x477,0x458,
	0x43A,0x41C,0x3FF,0x3E3,0x3C7,0x3AC,0x392,0x378,0x35F,0x347,
	0x330,0x319,0x302,0x2ED,0x2D8,0x2C3,0x2AF,0x29C,0x289,0x277,
	0x265,0x254,0x243,0x233,0x223,0x214,0x205,0x1F6,0x1E8,0x1DB,
	0x1CE,0x1C1,0x1B4,0x1A8,0x19D,0x191,0x186,0x17C,0x171,0x167,
	0x15E,0x154,0x14B,0x142,0x13A,0x131,0x129,0x121,0x11A,0x112,
	0x10B
};

const char Temp_Value[141] = {
	-40,-39,-38,-37,-36,-35,-34,-33,-32,-31,
	-30,-29,-28,-27,-26,-25,-24,-23,-22,-21,
	-20,-19,-18,-17,-16,-15,-14,-13,-12,-11,
	-10,-9,-8,-7,-6,-5,-4,-3,-2,-1,
	0,1,2,3,4,5,6,7,8,9,
	10,11,12,13,14,15,16,17,18,19,
	20,21,22,23,24,25,26,27,28,29,
	30,31,32,33,34,35,36,37,38,39,
	40,41,42,43,44,45,46,47,48,49,
	50,51,52,53,54,55,56,57,58,59,
	60,61,62,63,64,65,66,67,68,69,
	70,71,72,73,74,75,76,77,78,79,
	80,81,82,83,84,85,86,87,88,89,
	90,91,92,93,94,95,96,97,98,99,
	100
};

void Total_initialization(void) 
{
   SetBusCLK(PLL_80);    //设定总线频率
   ATD_INIT(ADC_12BIT,ADC_interrupt_Close,Collection_channel_num1);
   PWM_init(PWM_Frequency32,PWM_Center_alignment,PWM_Channel_clock2,PWM_CH2,250);
   PIT_init(PIT_enable_CH0,PIT_CH0,2000); //100/1s
   SCI_INIT(SCI_CH0,115200);
   KEY_init(); 
   // CAN0_INIT(); 
   /* PWM_Cascade_init(PWM_Frequency32,
                       PWM_Channel_clock1,
                       PWM_Cascade_switch1,
                       PWM_Center_alignment,
                       PWM_Cascade1,10000);  */   
}


void SetBusCLK(u8 PLLCLK_time)
{   
    CLKSEL &= 0x7f;       //设置OSCCLK作为系统时钟
    PLLCTL &= 0x8F;       //禁止锁相环
    SYNR = PLLCLK_time;	                     			
    REFDV = 0x81;
    PLLCTL |=0x70;  //使能锁相环
    asm NOP;
    asm NOP;
    while(!(CRGFLG&0x08)); //PLLCLK锁定 
    CLKSEL |= 0x80;        //设置PLLCLK为系统时钟		        
}

void INIT_DOG(u8 DOGS)
{
  COPCTL = DOGS;    
}

void Feed_dog(void) 
{
     ARMCOP=0X55;      //在特定时间内依次向ARMCOP写入0X55,0XAA;
     ARMCOP=0XAA;
}

void TIH_Hinit(void) //初始化按键 
{
     KEY1_dir=0;       //设置为输入
     KEY2_dir=0;
     KEY3_dir=0;
     KEY4_dir=0;
     KEY5_dir=0;      
     KEY6_dir=0;
     KEY7_dir=0;
     KEY8_dir=0;
     
     PPSH = 0x00;		      //极性选择寄存器,选择下降沿;
     PIFH = 0xFF;					//对PIFH的每一位写1来清除标志位;
     PIEH = 0xFF;		      //中断使能寄存器;
}

int NTC_Calculation(u16 data)   //温度值计算
{
  u16 TMPC_DATA;
  int TMPCun=0,TMPCun1,TMPCun2;
  TMPC_DATA = data;
  TMPCun1=0;                     
  TMPCun2=140;                    
  if(TMPC_DATA<=AD_Result[TMPCun1]) TMPCun=TMPCun1;                         
  else if(TMPC_DATA>=AD_Result[TMPCun2])  TMPCun=TMPCun2;
  else 
  {
    while(TMPCun1<TMPCun2-1)       
     {
        TMPCun = (TMPCun1+TMPCun2)>>1;    
        if(TMPC_DATA<AD_Result[TMPCun]) TMPCun2=TMPCun;               
        else  TMPCun1=TMPCun;                                         
     }
      return Temp_Value[TMPCun];
  }
  return 0;
}

#pragma CODE_SEG __NEAR_SEG NON_BANKED
 void interrupt 25 PTH_inter(void) 
{
   if(PIFH != 0)     //判断中断标志
   {
      PIFH = 0xff;     //清除中断标志
      if(KEY1 == 0) _asm(nop);       
      if(KEY2 == 0) _asm(nop);
      if(KEY3 == 0) _asm(nop);
      if(KEY4 == 0) _asm(nop);
      if(KEY5 == 0) _asm(nop);       
      if(KEY6 == 0) _asm(nop);
      if(KEY7 == 0) _asm(nop);
      if(KEY8 == 0) _asm(nop);
   
   }
}

#pragma CODE_SEG DEFAULT





