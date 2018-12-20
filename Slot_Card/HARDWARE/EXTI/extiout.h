#ifndef __EXTIOUT_H
#define __EXITOUT_H	 
#include "sys.h"
								  
extern u8 key[8];
extern u8 sem_rading;
#define USER_MUTEX	1						//用于锁定设备状态刷卡等待时，不允许操作

void EXTIX_Init(void);//外部中断初始化		
u8 Tra_port(void);
#endif

