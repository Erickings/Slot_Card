#include "sys.h"
#include "usart.h"
#include "includes.h"
////////////////////////////////////////////////////////////////////////////////// 	 
//如果使用ucos,则包括下面的头文件即可.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos 使用	  
#endif
	  
 

//////////////////////////////////////////////////////////////////
//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
_sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 

/*使用microLib的方法*/
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
 
#if EN_USART1_RX   //如果使能了接收
//串口1中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误   	
u8 USART_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
u8 USART_Data[26];
u8 rem_sum[8];
u8 pro_open_port;
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART_RX_STA=0;       //接收状态标记	
u8 Uart_send_counter; //Uart_send()函数发送的字节数
vu8 *Uart_send_pointer;//发送的数组指针
u32 RxCounter1=0;
u8 RxBuffer1[200];
u8 UID_backup[4];//UID备份  用于处理 不连续写同一卡
u8 flag_nfc_status;
u8 flag_rev_finish;  //1为接收完成
u8 Tohex(u8 num);
  
void uart_init(u32 bound){
  //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟
  
	//USART1_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.9
   
  //USART1_RX	  GPIOA.10初始化
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.10  

  //Usart1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

  USART_Init(USART1, &USART_InitStructure); //初始化串口1
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(USART1, ENABLE);                    //使能串口1 
	USART_ClearFlag(USART1, USART_FLAG_TC);
}

void USART1_IRQHandler(void)                	//串口1中断服务程序
{

	uint8_t index;
#if SYSTEM_SUPPORT_OS 		//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
	OSIntEnter();    
#endif
	

	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)	//判断是否触发了接收中断
	{	
		ClearData(USART_RX_BUF,26);	//清空数据接收
		USART_ITConfig(USART1,USART_IT_RXNE,DISABLE);	//关闭接收中断		
			
//		循环接收数据
		for(index=0;index<26;index++)
		{
			while(RESET == USART_GetFlagStatus(USART1,USART_FLAG_RXNE));	//等待数据接收标志位复位
			if(SET == USART_GetFlagStatus(USART1,USART_FLAG_RXNE))	//数据接收标志位复位，表示已接收到数据
			{	
					USART_RX_BUF[index]=USART_ReceiveData(USART1);
					USART_ClearITPendingBit(USART1, USART_IT_RXNE);	//清空数据接收标志位
			}
		}
		step = parse_pro;
		USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);	//开启接收中断
	}

		 
#if SYSTEM_SUPPORT_OS 	//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
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

