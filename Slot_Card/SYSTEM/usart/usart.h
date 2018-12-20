#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 

//1,�����˶�UCOSII��֧��
#define USART_REC_LEN  			26  	//�����������ֽ��� 200
#define EN_USART1_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����
	  	
extern u8  USART_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART_RX_STA;         		//����״̬���	
extern u8 USART_Data[26];
extern u8 rem_sum[8];
extern u8 pro_open_port;
//����봮���жϽ��գ��벻Ҫע�����º궨��
void uart_init(u32 bound);
void USART1_send_data(u8 *s, u8 len);
void Pares_Pro(void);
#endif


