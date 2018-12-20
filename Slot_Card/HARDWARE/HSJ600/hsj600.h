#ifndef __HSJ600_H
#define __HSJ600_H

#include "sys.h"
#include "user_uart.h"

#define DataLength 7	//ͨ������֡����
#define CardDateNum 2	//����������ͨ������֡�е�λ��
#define CardDataLength 4	//�������ݳ���
#define CardProLength  14
#define CardProPackLen 17

extern uint8_t NEW_DATA;	//ͨ�������������ձ�־
extern uint8_t Data[DataLength];	//ͨ������֡������
extern uint8_t CardData[CardDataLength];	//�������ݴ洢
extern uint8_t Card_pro[15];

void ClearData(uint8_t *Data,uint8_t Num); //�������
void CopyData(uint8_t  *DBfr,uint8_t  *SBfr,uint8_t Len); //��������
uint8_t GetBCC(uint8_t *Data,uint8_t Num);	//��ȡУ��λ����
void GetCard(void); //���������������
void Pro_pack(void);
u8 uitoa(u8 num);
u8 GetSum(u8 *data, u8 data_length);

#endif
