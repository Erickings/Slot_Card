#include "extiout.h"
#include "key.h"
#include "delay.h"
#include "usart.h"
#include "beep.h"
#include "status.h"
#include "includes.h"

u8 key[8] = {0};

u8 sem_rading = 0;

//�ⲿ�ж�0�������
void EXTIX_Init(void)
{
 
 	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;

    KEY_Init();	 //	�����˿ڳ�ʼ��

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//ʹ�ܸ��ù���ʱ��
	
	
	  //GPIOA.0	  �ж����Լ��жϳ�ʼ������ �½��ش��� //KEY1
 	  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0); 
  	EXTI_InitStructure.EXTI_Line=EXTI_Line0;
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;	
  	EXTI_Init(&EXTI_InitStructure);		//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
	
	
	  //GPIOA.1	  �ж����Լ��жϳ�ʼ������ �½��ش��� //KEY2
 	  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource1); 
  	EXTI_InitStructure.EXTI_Line=EXTI_Line1;
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
		EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);		//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
	
	

    //GPIOA.2 �ж����Լ��жϳ�ʼ������   �½��ش��� //KEY3
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource2);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line2;	//KEY2
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

    //GPIOA.3	  �ж����Լ��жϳ�ʼ������ �½��ش��� //KEY8
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource3);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line3;
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

    //GPIOA.4	  �ж����Լ��жϳ�ʼ������  �½��ش���	//KEY7
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource4);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line4;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;		
  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
		
		
		//GPIOA.5	  �ж����Լ��жϳ�ʼ������  �½��ش���	//KEY6
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource5);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line5;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;		
  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
		
		//GPIOA.6	  �ж����Լ��жϳ�ʼ������  �½��ش���	//KEY5
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource6);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line6;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;		
  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
		
		
		//GPIOA.7	  �ж����Լ��жϳ�ʼ������  �½��ش���	//KEY4
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource7);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line7;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;		
  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
		

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//ʹ�ܰ���0�ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//�����ȼ�3
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure); 

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;			//ʹ�ܰ���WK_UP���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//�����ȼ�3
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure); 

    NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;			//ʹ�ܰ���KEY2���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//�����ȼ�2
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);


  	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;			//ʹ�ܰ���KEY1���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;	//��ռ���ȼ�2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//�����ȼ�1 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

		NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;			//ʹ�ܰ���KEY0���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;	//��ռ���ȼ�2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//�����ȼ�0 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
		
		
  	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//ʹ�ܰ���WK_UP���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//�����ȼ�3
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);
		
 
}


//�ⲿ�ж�0������� 
void EXTI0_IRQHandler(void)
{
	delay_ms(10);//����
	if(EXTI_GetITStatus(EXTI_Line0)!=RESET) 
	{
			if(sem_rading == 1)
			{
					EXTI_ClearITPendingBit(EXTI_Line0); //���LINE0�ϵ��жϱ�־λ  
					return;
			}

			//�жϴ���
			if(key[0]==1)
			{
					Port_occu(0);
					EXTI_ClearITPendingBit(EXTI_Line0); //���LINE0�ϵ��жϱ�־λ  
					return ;
			}
			else if(key[0]==0)
			{
					Che_port(0);
					key[0] = 1;										//������־λ					
					step=key_op;
					cou_timer=0;
					delay_ms(100);
					EXTI_ClearITPendingBit(EXTI_Line0); //���LINE0�ϵ��жϱ�־λ  
			}
	}
}


//�ⲿ�ж�1������� 
void EXTI1_IRQHandler(void)
{
	delay_ms(10);//����
		
		
	if(EXTI_GetITStatus(EXTI_Line1)!=RESET) 
	{		
		if(sem_rading == 1)
		{
				EXTI_ClearITPendingBit(EXTI_Line1); //���LINE1�ϵ��жϱ�־λ  
				return;
		}

		//�жϴ���
		if(key[1]==1)
		{
				Port_occu(1);
				EXTI_ClearITPendingBit(EXTI_Line1); //���LINE1�ϵ��жϱ�־λ  
				return ;
		}
		else if(key[1]==0)
		{
				Che_port(1);
				key[1] = 1;
				step=key_op;
				cou_timer=0;
				EXTI_ClearITPendingBit(EXTI_Line1); //���LINE1�ϵ��жϱ�־λ  
		}
	}
}
 
//�ⲿ�ж�2�������
void EXTI2_IRQHandler(void)
{
	
	delay_ms(10);//����
	
	if(EXTI_GetITStatus(EXTI_Line2)!=RESET) 
	{
		if(sem_rading == 1)
		{
				EXTI_ClearITPendingBit(EXTI_Line2); //���LINE2�ϵ��жϱ�־λ  
				return;
		}

		//�жϴ���
		if(key[2]==1)
		{
				Port_occu(2);
				EXTI_ClearITPendingBit(EXTI_Line2); //���LINE2�ϵ��жϱ�־λ  
				return ;
		}	
		else if(key[2]==0)
		{
				Che_port(2);		
				key[2] = 1;
				step=key_op;
				cou_timer=0;
				EXTI_ClearITPendingBit(EXTI_Line2); //���LINE2�ϵ��жϱ�־λ  
		}
	}
}
//�ⲿ�ж�3�������
void EXTI3_IRQHandler(void)
{
	delay_ms(10);//����
	if(EXTI_GetITStatus(EXTI_Line3)!=RESET) 
	{
		if(sem_rading == 1)
		{
				EXTI_ClearITPendingBit(EXTI_Line3); //���LINE3�ϵ��жϱ�־λ  
				return;
		}

		//�жϴ���
		if(key[3]==1)
		{
				Port_occu(3);
				EXTI_ClearITPendingBit(EXTI_Line3); //���LINE3�ϵ��жϱ�־λ  
				return ;
		}
		else if(key[3]==0)
		{	
				Che_port(3);		
				key[3] = 1;
				step=key_op;
				cou_timer=0;
				EXTI_ClearITPendingBit(EXTI_Line3); //���LINE3�ϵ��жϱ�־λ  
		}
	}
}

//�ⲿ�ж�4�������
void EXTI4_IRQHandler(void)
{
	delay_ms(10);//����
	if(EXTI_GetITStatus(EXTI_Line4)!=RESET) 
	{
		if(sem_rading == 1)
		{
				EXTI_ClearITPendingBit(EXTI_Line4); //���LINE4�ϵ��жϱ�־λ  
				return;
		}
		//�жϴ���
		if(key[4]==1)
		{
				Port_occu(4);
				EXTI_ClearITPendingBit(EXTI_Line4); //���LINE4�ϵ��жϱ�־λ  
				return ;
		}
		else if(key[4]==0)
		{
				Che_port(4);
				key[4] = 1;
				step=key_op;
				cou_timer=0;
				EXTI_ClearITPendingBit(EXTI_Line4); //���LINE4�ϵ��жϱ�־λ  
		}
	}
}
 
//�ⲿ�ж�5~9�������
void EXTI9_5_IRQHandler(void)
{
		delay_ms(10);//����
	
		if(EXTI_GetITStatus(EXTI_Line5)!=RESET)     
    {

				if(sem_rading == 1)
				{
						EXTI_ClearITPendingBit(EXTI_Line5); //���LINE5�ϵ��жϱ�־λ  
						return;
				}			
					
         //�жϴ���
				if(key[5]==1)
				{
						Port_occu(5);
						EXTI_ClearITPendingBit(EXTI_Line5); //���LINE5�ϵ��жϱ�־λ  
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

         //�жϴ���

				if(sem_rading == 1)
				{
						EXTI_ClearITPendingBit(EXTI_Line6); //���LINE6�ϵ��жϱ�־λ  
						return;
				}
					
				if(key[6]==1)
				{
						Port_occu(6);
						EXTI_ClearITPendingBit(EXTI_Line6); //���LINE6�ϵ��жϱ�־λ  
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
						EXTI_ClearITPendingBit(EXTI_Line7); //���LINE7�ϵ��жϱ�־λ  
						return;
				}
			
         //�жϴ���
				if(key[7]==1)
				{
						Port_occu(7);
						EXTI_ClearITPendingBit(EXTI_Line7); //���LINE7�ϵ��жϱ�־λ  
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



//�����˿ڣ��鿴�Ƿ��а�������
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

