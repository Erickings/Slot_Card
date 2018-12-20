#ifndef __HSJ600_H
#define __HSJ600_H

#include "sys.h"
#include "user_uart.h"

#define DataLength 7	//通信数据帧长度
#define CardDateNum 2	//卡号数据在通信数据帧中的位数
#define CardDataLength 4	//卡号数据长度
#define CardProLength  14
#define CardProPackLen 17

extern uint8_t NEW_DATA;	//通信数据正常接收标志
extern uint8_t Data[DataLength];	//通信数据帧缓冲区
extern uint8_t CardData[CardDataLength];	//卡号数据存储
extern uint8_t Card_pro[15];

void ClearData(uint8_t *Data,uint8_t Num); //清空数据
void CopyData(uint8_t  *DBfr,uint8_t  *SBfr,uint8_t Len); //复制数据
uint8_t GetBCC(uint8_t *Data,uint8_t Num);	//获取校验位数据
void GetCard(void); //串口输出卡号数据
void Pro_pack(void);
u8 uitoa(u8 num);
u8 GetSum(u8 *data, u8 data_length);

#endif
