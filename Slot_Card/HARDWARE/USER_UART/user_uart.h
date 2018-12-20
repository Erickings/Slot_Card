#ifndef __USER_UART_H
#define __USER_UART_H

#include "stdio.h"	
#include "sys.h"
#include "stm32f10x.h"

/***************************************************************
*	开发者串口使能 
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
*	函数声明 
****************************************************************/
void USER_UARTx_Init(void);	//开发者串口初始化
void USER_UART1_Send_DATA(uint8_t data);	//开发者串口1发送一个字节数据
void USER_UART1_Send_Str(uint8_t *Data,uint8_t Num);	//开发者串口1发送字符串

/***************************************************************
											*	END *
****************************************************************/
#endif
