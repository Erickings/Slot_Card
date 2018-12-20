#include "extiout.h"
#include "key.h"
#include "delay.h"
#include "usart.h"
#include "beep.h"
#include "status.h"
#include "includes.h"

u8 key[8] = {0};

u8 sem_rading = 0;

//外部中断0服务程序
void EXTIX_Init(void)
{
 
 	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;

    KEY_Init();	 //	按键端口初始化

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//使能复用功能时钟
	
	
	  //GPIOA.0	  中断线以及中断初始化配置 下降沿触发 //KEY1
 	  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0); 
  	EXTI_InitStructure.EXTI_Line=EXTI_Line0;
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;	
  	EXTI_Init(&EXTI_InitStructure);		//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
	
	
	  //GPIOA.1	  中断线以及中断初始化配置 下降沿触发 //KEY2
 	  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource1); 
  	EXTI_InitStructure.EXTI_Line=EXTI_Line1;
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
		EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);		//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
	
	

    //GPIOA.2 中断线以及中断初始化配置   下降沿触发 //KEY3
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource2);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line2;	//KEY2
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

    //GPIOA.3	  中断线以及中断初始化配置 下降沿触发 //KEY8
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource3);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line3;
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

    //GPIOA.4	  中断线以及中断初始化配置  下降沿触发	//KEY7
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource4);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line4;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;		
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
		
		
		//GPIOA.5	  中断线以及中断初始化配置  下降沿触发	//KEY6
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource5);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line5;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;		
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
		
		//GPIOA.6	  中断线以及中断初始化配置  下降沿触发	//KEY5
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource6);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line6;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;		
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
		
		
		//GPIOA.7	  中断线以及中断初始化配置  下降沿触发	//KEY4
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource7);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line7;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;		
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
		

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//使能按键0在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//子优先级3
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure); 

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;			//使能按键WK_UP所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//子优先级3
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure); 

    NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;			//使能按键KEY2所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//子优先级2
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);


  	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;			//使能按键KEY1所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;	//抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//子优先级1 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

		NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;			//使能按键KEY0所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;	//抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//子优先级0 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
		
		
  	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//使能按键WK_UP所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//子优先级3
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);
		
 
}


//外部中断0服务程序 
void EXTI0_IRQHandler(void)
{
	delay_ms(10);//消抖
	if(EXTI_GetITStatus(EXTI_Line0)!=RESET) 
	{
			if(sem_rading == 1)
			{
					EXTI_ClearITPendingBit(EXTI_Line0); //清除LINE0上的中断标志位  
					return;
			}

			//中断处理
			if(key[0]==1)
			{
					Port_occu(0);
					EXTI_ClearITPendingBit(EXTI_Line0); //清除LINE0上的中断标志位  
					return ;
			}
			else if(key[0]==0)
			{
					Che_port(0);
					key[0] = 1;										//保护标志位					
					step=key_op;
					cou_timer=0;
					delay_ms(100);
					EXTI_ClearITPendingBit(EXTI_Line0); //清除LINE0上的中断标志位  
			}
	}
}


//外部中断1服务程序 
void EXTI1_IRQHandler(void)
{
	delay_ms(10);//消抖
		
		
	if(EXTI_GetITStatus(EXTI_Line1)!=RESET) 
	{		
		if(sem_rading == 1)
		{
				EXTI_ClearITPendingBit(EXTI_Line1); //清除LINE1上的中断标志位  
				return;
		}

		//中断处理
		if(key[1]==1)
		{
				Port_occu(1);
				EXTI_ClearITPendingBit(EXTI_Line1); //清除LINE1上的中断标志位  
				return ;
		}
		else if(key[1]==0)
		{
				Che_port(1);
				key[1] = 1;
				step=key_op;
				cou_timer=0;
				EXTI_ClearITPendingBit(EXTI_Line1); //清除LINE1上的中断标志位  
		}
	}
}
 
//外部中断2服务程序
void EXTI2_IRQHandler(void)
{
	
	delay_ms(10);//消抖
	
	if(EXTI_GetITStatus(EXTI_Line2)!=RESET) 
	{
		if(sem_rading == 1)
		{
				EXTI_ClearITPendingBit(EXTI_Line2); //清除LINE2上的中断标志位  
				return;
		}

		//中断处理
		if(key[2]==1)
		{
				Port_occu(2);
				EXTI_ClearITPendingBit(EXTI_Line2); //清除LINE2上的中断标志位  
				return ;
		}	
		else if(key[2]==0)
		{
				Che_port(2);		
				key[2] = 1;
				step=key_op;
				cou_timer=0;
				EXTI_ClearITPendingBit(EXTI_Line2); //清除LINE2上的中断标志位  
		}
	}
}
//外部中断3服务程序
void EXTI3_IRQHandler(void)
{
	delay_ms(10);//消抖
	if(EXTI_GetITStatus(EXTI_Line3)!=RESET) 
	{
		if(sem_rading == 1)
		{
				EXTI_ClearITPendingBit(EXTI_Line3); //清除LINE3上的中断标志位  
				return;
		}

		//中断处理
		if(key[3]==1)
		{
				Port_occu(3);
				EXTI_ClearITPendingBit(EXTI_Line3); //清除LINE3上的中断标志位  
				return ;
		}
		else if(key[3]==0)
		{	
				Che_port(3);		
				key[3] = 1;
				step=key_op;
				cou_timer=0;
				EXTI_ClearITPendingBit(EXTI_Line3); //清除LINE3上的中断标志位  
		}
	}
}

//外部中断4服务程序
void EXTI4_IRQHandler(void)
{
	delay_ms(10);//消抖
	if(EXTI_GetITStatus(EXTI_Line4)!=RESET) 
	{
		if(sem_rading == 1)
		{
				EXTI_ClearITPendingBit(EXTI_Line4); //清除LINE4上的中断标志位  
				return;
		}
		//中断处理
		if(key[4]==1)
		{
				Port_occu(4);
				EXTI_ClearITPendingBit(EXTI_Line4); //清除LINE4上的中断标志位  
				return ;
		}
		else if(key[4]==0)
		{
				Che_port(4);
				key[4] = 1;
				step=key_op;
				cou_timer=0;
				EXTI_ClearITPendingBit(EXTI_Line4); //清除LINE4上的中断标志位  
		}
	}
}
 
//外部中断5~9服务程序
void EXTI9_5_IRQHandler(void)
{
		delay_ms(10);//消抖
	
		if(EXTI_GetITStatus(EXTI_Line5)!=RESET)     
    {

				if(sem_rading == 1)
				{
						EXTI_ClearITPendingBit(EXTI_Line5); //清除LINE5上的中断标志位  
						return;
				}			
					
         //中断处理
				if(key[5]==1)
				{
						Port_occu(5);
						EXTI_ClearITPendingBit(EXTI_Line5); //清除LINE5上的中断标志位  
						return ;
				}
				else if(key[5]==0)
				{
						Che_port(5);				
						key[5] = 1;
						step=key_op;
						cou_timer=0;
						EXTI_ClearITPendingBit(EXTI_Line5);
				}
				
    }
	
		if(EXTI_GetITStatus(EXTI_Line6)!=RESET)     
    {

         //中断处理

				if(sem_rading == 1)
				{
						EXTI_ClearITPendingBit(EXTI_Line6); //清除LINE6上的中断标志位  
						return;
				}
					
				if(key[6]==1)
				{
						Port_occu(6);
						EXTI_ClearITPendingBit(EXTI_Line6); //清除LINE6上的中断标志位  
						return ;
				}	
				else if(key[6]==0)
				{
						Che_port(6);				
						key[6] = 1;
						step=key_op;
						cou_timer=0;				
						EXTI_ClearITPendingBit(EXTI_Line6);
				}
    }
		
		if(EXTI_GetITStatus(EXTI_Line7)!=RESET)     
    {

				if(sem_rading == 1)
				{
						EXTI_ClearITPendingBit(EXTI_Line7); //清除LINE7上的中断标志位  
						return;
				}
			
         //中断处理
				if(key[7]==1)
				{
						Port_occu(7);
						EXTI_ClearITPendingBit(EXTI_Line7); //清除LINE7上的中断标志位  
						return ;
				}
				else if(key[7]==0)
				{
						Che_port(7);				
						key[7] = 1;
						
						step=key_op;
						cou_timer=0;
						EXTI_ClearITPendingBit(EXTI_Line7);
				}
    } 	
}



//遍历端口，查看是否有按键按下
u8 Tra_port(void)					
{
	u8 i=0;
	
	for(i=0; i<8; i++)
	{
		if(key[i]==1)
		{
			return i;
		}
		
	}
	return 0;
}

