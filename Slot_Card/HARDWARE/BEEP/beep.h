#ifndef __BEEP_H
#define __BEEP_H	 
#include "sys.h"

//蜂鸣器端口定义
#define BEEP PBout(8)	// BEEP,蜂鸣器接口		

//蜂鸣器端口定义
#define	Beep_Set()	GPIO_SetBits(GPIOB, GPIO_Pin_8)
#define	Beep_Clr()	GPIO_ResetBits(GPIOB, GPIO_Pin_8)

void BEEP_Init(void);	//初始化
		 				    
#endif

