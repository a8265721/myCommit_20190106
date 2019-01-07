#include "delay.h"      
 
 void delay_ms(u16 ms)
{   
   u16 i,t;
   if (ms<1) ms=1;
   for(i=0;i<ms;i++)   
     //for(jj=0;jj<1335;jj++);  //16MHz--1ms
     //for(t=0;t<3338;t++);    //40MHz--1ms 
     //for(jj=0;jj<4006;jj++);  //48MHz--1ms 
     //for(jj=0;jj<5341;jj++);    //64MHz--1ms 
     for(t=0;t<6675;t++);   //80MHz--1ms 
          
}  

