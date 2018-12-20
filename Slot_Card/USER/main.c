#include "usart.h"
#include "includes.h"


 int main(void)
 {	

	//		u8 num[8] = {0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38};
			u8 port_num = 1;
			u8 port_res;
			u8 temp_timer=0;
	 
		delay_init();	    	 //延时函数初始化	  
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
		uart_init(115200);	 //串口初始化为19200
//	BEEP_Init();         	//初始化蜂鸣器端口
	 GPIO_Configuration();
		EXTIX_Init();		 	//外部中断初始化
		USER_UARTx_Init(); //开发者串口初始化
	  delay_ms(5);	// 模块上电，延时5ms等待模块正常工作
			
    delay_ms(40);
    LCD_RST_Clr();
    delay_ms(40);
	  LCD_RST_Set();
   delay_ms(40);
    LCD_RST_Clr();
    delay_ms(40);
	  LCD_RST_Set();
		

  
	init_lcd();
	
	
	
//		LCD_SW_Set();
//		LCD_SW_Clr();
//	EXTIX_Init();		 	//外部中断初始化

	while(1)
 {
	

//			Rem_sum();				//显示账户余额	
//			Open_fail(insu_funds,port_num);	 
	
	 switch(step){
		 
		 case key_op:						//按键操作

				if(cou_timer >= 3)
				{
					cou_timer=0;
					key[Tra_port()]=0;
					step=def_status_logo;
					break;
				}
				port_res=Tra_port();	 
				Open_succ(port_res);
				cou_timer++;
			
				break;

		 case slot_card:				//刷卡操作
				if(cou_timer >= 3)
				{
					key[Tra_port()]=0;
					step=def_status_logo;
					break;
				}
		 
				LCD_SW_Clr();
				DELAY_CLS();
				gotoxy(1,0);
				SendStr("请刷卡！！");
				delay_ms(300);
				DELAY_CLS();
//				step=reading_card;
				break;
		
		 case reading_card:			//正在读卡

//				cou_timer=0;
				if(sem_rading == 1)
				{
						if(cou_timer >= 5)
						{
							cou_timer=0;
							key[Tra_port()]=0;
							step=def_status_logo;
							break;
						}
				 
		//				while(cou_timer <= 50)
		//				{
							LCD_SW_Clr();
							Reading_card();
							GetCard();
							key[Tra_port()]=0;
		//					delay_ms(500);
							cou_timer++;	
		//				}				
		//				cou_timer=0;
		//				step=def_status_logo;
							sem_rading=0;
				}	
				break;
		 
		 case sel_port:					//选择端口
					if(cou_timer >= 10)
					{
						step=def_status_logo;
						break;
					}
			 
					LCD_SW_Clr();
					break;
		 case slot_reslut:					//收到指令后的处理结果
			 
					while(temp_timer < 10 && USART_Data[14] != 0x00){

			 
					if(USART_Data[14] == 0x31)
					{
							Rem_sum();
							step=def_status_logo;
							break;
					}
					else if(USART_Data[14] == 0x32)
					{
						Open_fail(insu_funds,pro_open_port);
						step=def_status_logo;
						break;
					}
					else if(USART_Data[14] == 0x33)
					{
						Open_fail(card_inva,pro_open_port);
						step=def_status_logo;
						break;
					}
					else if(USART_Data[14] == 0x34)
					{
							Open_fail(port_conflic,pro_open_port);
							step=def_status_logo;
							break;
					}
					if(USART_Data[14] == 0x35)
					{
							Open_fail(comm_fail,pro_open_port);
							step=def_status_logo;
							break;
					}
					temp_timer++;
				}
//					USART_Data[14]=0x00;
					step=def_status_logo;
					break;
					

		 case ret_status:
			 
					LCD_SW_Clr();
					Open_fail(insu_funds,port_num);
					break;
		 case def_status_logo:
		
					key[Tra_port()]=0;
					sem_rading=0;
					LCD_SW_Clr();
					Def_state();			//默认显示状态
//				step=def_status_sel_port;
				break;
//		 case def_status_sel_port:
//				LCD_SW_Clr();
//				Selet_port();
//				step=def_status_logo;
//				break;
		 case parse_pro:					//选择端口
					memcpy(USART_Data, USART_RX_BUF, 26 );
					memset(USART_RX_BUF, 0x00, 26);
					Pares_Pro();
					step = slot_reslut;
					LCD_SW_Clr();
					break;
				
		 default:
				LCD_SW_Clr();
				step=def_status_logo;
				break;
	 }


		
//	 Reading_card();


//		LCD_SW_Clr();
//	 GetCard(); //获取卡号数据
//		Charging();					//充电中...


	 
}

		
		
		
		
		
		
		
		
		
		
	 

	 
	 

 }

