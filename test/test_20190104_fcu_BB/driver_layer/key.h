#ifndef _KEY_H
#define _KEY_H


#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

#include "led.h"
#include "pwm.h"
/*                         
#define UP PTIH_PTIH0
#define DOWN PTIH_PTIH1
#define LEFT PTIH_PTIH2
#define RIGHT PTIH_PTIH3
#define UP_dir DDRH_DDRH0
#define DOWN_dir DDRH_DDRH1
#define LEFT_dir DDRH_DDRH2
#define RIGHT_dir DDRH_DDRH3
*/
                                 

#define  K1   PTIH_PTIH0
#define  K2   PTIH_PTIH1
#define  K3   PTIH_PTIH2
#define  FCU_STUTTER_STOP_ENABLE_K4   PTIH_PTIH3
#define  FCU_START_ENABLE_K5   PTIH_PTIH4
#define  K6   PTIH_PTIH5
#define  K7   PTIH_PTIH6
#define  K8   PTIH_PTIH7


#define K1_dir DDRH_DDRH0
#define K2_dir DDRH_DDRH1
#define K3_dir DDRH_DDRH2
#define K4_dir DDRH_DDRH3
#define K5_dir DDRH_DDRH4
#define K6_dir DDRH_DDRH5
#define K7_dir DDRH_DDRH6
#define K8_dir DDRH_DDRH7




// 初始化key               
void INIT_KEY(void);

//按键中断函数                           
//interrupt void PTH_inter(void) ;

#endif
