#include "sys.h"
#include "usart.h"
#include "includes.h"
////////////////////////////////////////////////////////////////////////////////// 	 
//���ʹ��ucos,����������ͷ�ļ�����.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos ʹ��	  
#endif
	  
 

//////////////////////////////////////////////////////////////////
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
_sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 

/*ʹ��microLib�ķ���*/
 /* 
int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, (uint8_t) ch);

	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {}	
   
    return ch;
}
int GetKey (void)  { 

    while (!(USART1->SR & USART_FLAG_RXNE));

    return ((int)(USART1->DR & 0x1FF));
}
*/
 
#if EN_USART1_RX   //���ʹ���˽���
//����1�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
u8 USART_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
u8 USART_Data[26];
u8 rem_sum[8];
u8 pro_open_port;
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART_RX_STA=0;       //����״̬���	
u8 Uart_send_counter; //Uart_send()�������͵��ֽ���
vu8 *Uart_send_pointer;//���͵�����ָ��
u32 RxCounter1=0;
u8 RxBuffer1[200];
u8 UID_backup[4];//UID����  ���ڴ��� ������дͬһ��
u8 flag_nfc_status;
u8 flag_rev_finish;  //1Ϊ�������
u8 Tohex(u8 num);
  
void uart_init(u32 bound){
  //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��
  
	//USART1_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.9
   
  //USART1_RX	  GPIOA.10��ʼ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.10  

  //Usart1 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
   //USART ��ʼ������

	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

  USART_Init(USART1, &USART_InitStructure); //��ʼ������1
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
  USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ���1 
	USART_ClearFlag(USART1, USART_FLAG_TC);
}

void USART1_IRQHandler(void)                	//����1�жϷ������
{

	uint8_t index;
#if SYSTEM_SUPPORT_OS 		//���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
	OSIntEnter();    
#endif
	

	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)	//�ж��Ƿ񴥷��˽����ж�
	{	
		ClearData(USART_RX_BUF,26);	//������ݽ���
		USART_ITConfig(USART1,USART_IT_RXNE,DISABLE);	//�رս����ж�		
			
//		ѭ����������
		for(index=0;index<26;index++)
		{
			while(RESET == USART_GetFlagStatus(USART1,USART_FLAG_RXNE));	//�ȴ����ݽ��ձ�־λ��λ
			if(SET == USART_GetFlagStatus(USART1,USART_FLAG_RXNE))	//���ݽ��ձ�־λ��λ����ʾ�ѽ��յ�����
			{	
					USART_RX_BUF[index]=USART_ReceiveData(USART1);
					USART_ClearITPendingBit(USART1, USART_IT_RXNE);	//������ݽ��ձ�־λ
			}
		}
		step = parse_pro;
		USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);	//���������ж�
	}

		 
#if SYSTEM_SUPPORT_OS 	//���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
	OSIntExit();  											 
#endif
} 
	

void USART1_send_data(u8 *s, u8 len)
{
	
	u8 t;
  	for(t=0;t<len;t++)		
	{		   
		while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);	  
		USART_SendData(USART1,s[t]);
	}	 
 
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);


}



void Pares_Pro(void)
{
	u8 i = 0;
	pro_open_port = USART_Data[5];
	
	for(i=0; i<8; i++)
	{
		rem_sum[i] = Tohex(USART_Data[(15+i)]); 
	}
	
}

u8 Tohex(u8 num)
{
	u8 str=0;
	switch(num)
	{
		case 48:
			str = 0x30;
			break;
		case 49:
			str = 0x31;
			break;
		case 50:
			str = 0x32;
			break;
		case 51:
			str = 0x33;
			break;
		case 52:
			str = 0x34;
			break;
		case 53:
			str = 0x35;
			break;
		case 54:
			str = 0x36;
			break;
		case 55:
			str = 0x37;
			break;
		case 56:
			str = 0x38;
			break;
		case 57:
			str = 0x39;
			break;
		case 46:
			str = 0x2E;
			break;
		default:
			break;	
	}
	return str;
}


#endif	

