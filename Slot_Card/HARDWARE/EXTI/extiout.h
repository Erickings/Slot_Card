#ifndef __EXTIOUT_H
#define __EXITOUT_H	 
#include "sys.h"
								  
extern u8 key[8];
extern u8 sem_rading;
#define USER_MUTEX	1						//���������豸״̬ˢ���ȴ�ʱ�����������

void EXTIX_Init(void);//�ⲿ�жϳ�ʼ��		
u8 Tra_port(void);
#endif

