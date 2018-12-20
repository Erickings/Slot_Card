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
    USART_InitStructure.USART_BaudRate = 9600;	//���ò�����Ϊ9600
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART3, &USART_InitStructure);

    USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);
    USART_Cmd(USART3, ENABLE);
    /* CPU��Сȱ�ݣ��������úã����ֱ��Send�����1���ֽڷ��Ͳ���ȥ
    �����������1���ֽ��޷���ȷ���ͳ�ȥ������ */
    USART_ClearFlag(USART3, USART_FLAG_TC); /* �巢����ɱ�־��Transmission Complete flag */
#endif

}

void NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

#if defined (USER_UART1_EN)
    //ʹ�ܴ����жϣ����������ȼ�
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

//�����ߴ���1����һ���ֽ�����
void USER_UART1_Send_DATA(uint8_t data)	
{
    USART_SendData(USART2,data);
    while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
}
//�����ߴ���1�����ַ���
void USER_UART1_Send_Str(uint8_t *Data,uint8_t Num)
{
	uint8_t i;
	for(i=0;i<Num;i++)
	{
		USER_UART1_Send_DATA(Data[i]);
	}
}

//�����ߴ���1�жϷ������
void USART3_IRQHandler(void)   
{
//	uint8_t Res;	//�ֽ����ݽ��ջ���
	uint8_t index;
	uint8_t BCC_sum=0;   //У��λ����



	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)	//�ж��Ƿ񴥷��˽����ж�
	{	
		ClearData(Data,DataLength);	//������ݽ���
		USART_ITConfig(USART3,USART_IT_RXNE,DISABLE);	//�رս����ж�		
			
//		ѭ����������
		for(index=0;index<DataLength;index++)
		{
			while(RESET == USART_GetFlagStatus(USART3,USART_FLAG_RXNE));	//�ȴ����ݽ��ձ�־λ��λ
			if(SET == USART_GetFlagStatus(USART3,USART_FLAG_RXNE))	//���ݽ��ձ�־λ��λ����ʾ�ѽ��յ�����
			{	
					Data[index]=USART_ReceiveData(USART3);
					USART_ClearITPendingBit(USART3, USART_IT_RXNE);	//������ݽ��ձ�־λ
			}
		}
		
		USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);	//���������ж�
		
		if(index==DataLength){	//�ж����ݽ��ճ���
			if((Data[0]==0x55)&&(Data[1]==0xAA)){	//����֡ͷ��ȷ
//			У��λ�ж�
				BCC_sum=GetBCC(&Data[CardDateNum],CardDataLength);
				if(BCC_sum!=Data[DataLength-1]){
					return;
				}
			}
			else{	//����֡ͷ����
				return;
			}
		}
		else{	//���ݽ���λ������
			return;
		}
		step=reading_card;
		sem_rading = 1;
		cou_timer=0;
		NEW_DATA=1; //���ݽ������� 
	}
} 
