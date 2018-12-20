#include "stm32f10x_rcc.h"
#include "user_uart.h"
#include "stdio.h"	
#include "sys.h"
#include "includes.h"
#include "hsj600.h"

void USER_UARTx_Init(void);
void USER_UART1_Send_DATA(uint8_t data);
void USER_UART1_Send_Str(uint8_t *Data,uint8_t Num);

void USER_UART_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

#if defined (USER_UART1_EN)
    USART3_GPIO_Cmd(USART3_GPIO_CLK, ENABLE);
    USART3_CLK_Cmd(USART3_CLK, ENABLE);
    USART3_AFIO_Cmd(USART3_AFIO_CLK, ENABLE);

    GPIO_InitStructure.GPIO_Pin = USART3_TxPin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = USART3_RxPin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
#endif

}

void USER_UART_Config(void)
{
    USART_InitTypeDef USART_InitStructure;

#if defined (USER_UART1_EN)
    USART_InitStructure.USART_BaudRate = 9600;	//设置波特率为9600
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART3, &USART_InitStructure);

    USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);
    USART_Cmd(USART3, ENABLE);
    /* CPU的小缺陷：串口配置好，如果直接Send，则第1个字节发送不出去
    如下语句解决第1个字节无法正确发送出去的问题 */
    USART_ClearFlag(USART3, USART_FLAG_TC); /* 清发送完成标志，Transmission Complete flag */
#endif

}

void NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

#if defined (USER_UART1_EN)
    //使能串口中断，并设置优先级
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
#endif

}

void USER_UARTx_Init(void)
{
    USER_UART_GPIO_Init();
    USER_UART_Config();
    NVIC_Configuration();
}

//开发者串口1发送一个字节数据
void USER_UART1_Send_DATA(uint8_t data)	
{
    USART_SendData(USART2,data);
    while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
}
//开发者串口1发送字符串
void USER_UART1_Send_Str(uint8_t *Data,uint8_t Num)
{
	uint8_t i;
	for(i=0;i<Num;i++)
	{
		USER_UART1_Send_DATA(Data[i]);
	}
}

//开发者串口1中断服务程序
void USART3_IRQHandler(void)   
{
//	uint8_t Res;	//字节数据接收缓冲
	uint8_t index;
	uint8_t BCC_sum=0;   //校验位数据



	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)	//判断是否触发了接收中断
	{	
		ClearData(Data,DataLength);	//清空数据接收
		USART_ITConfig(USART3,USART_IT_RXNE,DISABLE);	//关闭接收中断		
			
//		循环接收数据
		for(index=0;index<DataLength;index++)
		{
			while(RESET == USART_GetFlagStatus(USART3,USART_FLAG_RXNE));	//等待数据接收标志位复位
			if(SET == USART_GetFlagStatus(USART3,USART_FLAG_RXNE))	//数据接收标志位复位，表示已接收到数据
			{	
					Data[index]=USART_ReceiveData(USART3);
					USART_ClearITPendingBit(USART3, USART_IT_RXNE);	//清空数据接收标志位
			}
		}
		
		USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);	//开启接收中断
		
		if(index==DataLength){	//判断数据接收长度
			if((Data[0]==0x55)&&(Data[1]==0xAA)){	//数据帧头正确
//			校验位判断
				BCC_sum=GetBCC(&Data[CardDateNum],CardDataLength);
				if(BCC_sum!=Data[DataLength-1]){
					return;
				}
			}
			else{	//数据帧头错误
				return;
			}
		}
		else{	//数据接收位数出错
			return;
		}
		step=reading_card;
		sem_rading = 1;
		cou_timer=0;
		NEW_DATA=1; //数据接收正常 
	}
} 
