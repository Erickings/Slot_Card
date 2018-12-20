#ifndef __USER_UART_H
#define __USER_UART_H

#include "stdio.h"	
#include "sys.h"
#include "stm32f10x.h"

/***************************************************************
*	�����ߴ���ʹ�� 
****************************************************************/
#define USER_UART1_EN	1

/***************************************************************
*	USER_UART1	UART2_TX   PA2 
*	USER_UART1	UART2_RX   PA3
****************************************************************/
#if defined (USER_UART1_EN)

#define USART3_GPIO_Cmd		       RCC_APB2PeriphClockCmd
#define USART3_GPIO_CLK          RCC_APB2Periph_GPIOB

#define USART3_AFIO_Cmd		       RCC_APB2PeriphClockCmd
#define USART3_AFIO_CLK          RCC_APB2Periph_AFIO

#define USART3_CLK_Cmd		       RCC_APB1PeriphClockCmd
#define USART3_CLK               RCC_APB1Periph_USART3 

#define USART3_GPIO_PORT         GPIOB
#define USART3_RxPin             GPIO_Pin_11
#define USART3_TxPin             GPIO_Pin_10

#endif

/***************************************************************
*	�������� 
****************************************************************/
void USER_UARTx_Init(void);	//�����ߴ��ڳ�ʼ��
void USER_UART1_Send_DATA(uint8_t data);	//�����ߴ���1����һ���ֽ�����
void USER_UART1_Send_Str(uint8_t *Data,uint8_t Num);	//�����ߴ���1�����ַ���

/***************************************************************
											*	END *
****************************************************************/
#endif
