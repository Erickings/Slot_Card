#ifndef __BEEP_H
#define __BEEP_H	 
#include "sys.h"

//�������˿ڶ���
#define BEEP PBout(8)	// BEEP,�������ӿ�		

//�������˿ڶ���
#define	Beep_Set()	GPIO_SetBits(GPIOB, GPIO_Pin_8)
#define	Beep_Clr()	GPIO_ResetBits(GPIOB, GPIO_Pin_8)

void BEEP_Init(void);	//��ʼ��
		 				    
#endif

