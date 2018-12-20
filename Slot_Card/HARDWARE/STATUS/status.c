#include "event_def.h"
#include "status.h"
#include "usart.h"


u8 remaining_sum[8] = {0x31,0x32,0x33,0x34,'.',0x35,0x36};

event_step step;

void Def_state(void)
{
		/**********开始提示用语		*******/
			LCD_SW_Set();
			DELAY_CLS();	

			gotoxy(1,2);
			SendStr("欢迎使用");
			gotoxy(2,2);
			SendStr("金点驿充");	
			delay_ms(300);
			DELAY_CLS();
}

void Selet_port(void)
{	
			LCD_SW_Set();

			DELAY_CLS();	
			gotoxy(1,0);
			SendStr("请选择充电端口:");	
			delay_ms(300);
//			DELAY_CLS();
	
}

void Rem_sum(void)
{
		/************显示余额 *************/
			LCD_SW_Clr();
	 		DELAY_CLS();
			gotoxy(1,0);
			SendStr(&pro_open_port);
	 	 	gotoxy(1,1);
			SendStr("端口已打开：");
			gotoxy(2,0);
			SendStr("余额");
	 		gotoxy(2,2);
			SendStr(rem_sum);
			gotoxy(2,6);
			SendStr("元");
	 		delay_ms(700);
//			DELAY_CLS();
	
}


void  Open_succ(u8 s_port)
{
	 /**********选择端口成功提示*******/
			u8 succ_port = Swit_chr(s_port);
			DELAY_CLS();
			LCD_SW_Clr();
			gotoxy(1,0);
			SendStr(&succ_port);
			gotoxy(1,1);
			SendStr("号端口可用");
			gotoxy(2,0);
			SendStr("请刷卡:");	
			delay_ms(700);
//			DELAY_CLS();
}

void Charging(void)
{
			DELAY_CLS();
			LCD_SW_Clr();
			gotoxy(1,0);
			SendStr("充电中...");
			delay_ms(500);
//			DELAY_CLS();

}	
	 

void Open_fail(fail_sort sort, u8 op_fail)
{

		if( sort==insu_funds || sort==card_inva || sort==port_conflic || sort==comm_fail )
		{
			switch(sort){
				case insu_funds:
					/**********打开端口失败提示：余额不足		*******/
					DELAY_CLS();
					LCD_SW_Clr();
					gotoxy(1,0);
					SendStr(&op_fail);
					gotoxy(1,1);
					SendStr("端口打开失败");
					gotoxy(2,2);
					SendStr("余额不足");	
					delay_ms(700);
//					DELAY_CLS();
					
					break;
				case card_inva:
				 /**********打开端口失败提示：通讯失败		*******/
					DELAY_CLS();					
					LCD_SW_Clr();
					gotoxy(1,0);
					SendStr(&op_fail);
					gotoxy(1,1);
					SendStr("端口打开失败");
					gotoxy(2,2);
					SendStr("此卡无效");	
					delay_ms(700);
//					DELAY_CLS();
				
					break;
				
				case port_conflic:
						 /**********打开端口失败提示：端口冲突*******/
						DELAY_CLS();		
						LCD_SW_Clr();
						gotoxy(1,0);
						SendStr(&op_fail);
						gotoxy(1,1);
						SendStr("端口打开失败");
						gotoxy(2,1);
						SendStr("端口已被占用");	
						delay_ms(700);

					break;
				
								
				case comm_fail:
						 /**********打开端口失败提示：端口冲突*******/
						DELAY_CLS();		
						LCD_SW_Clr();
						gotoxy(1,0);
						SendStr(&op_fail);
						gotoxy(1,1);
						SendStr("端口打开失败");
						gotoxy(2,2);
						SendStr("网络异常");	
						delay_ms(700);

					break;
					
					
			}
		}
}	
	

void Reading_card(void)
{
	 /**********正在读卡提示		*******/
			LCD_SW_Clr();
			DELAY_CLS();
			gotoxy(1,0);
			SendStr("  正在读卡");
			gotoxy(2,0);
			SendStr("  请稍后...");	
			delay_ms(500);
//		DELAY_CLS();

}

void Port_occu(u8 f_port)
{
 	 /**********选择端口失败提示		*******/
			u8 fail_port = Swit_chr(f_port);							//将十进制转换成十六进制
			DELAY_CLS();
			LCD_SW_Clr();
			gotoxy(1,0);
			SendStr(&fail_port);
			gotoxy(1,1);
			SendStr("端口开启中");
			gotoxy(2,0);
			SendStr("请稍后...");	
			delay_ms(10);
			DELAY_CLS();

}

void Che_port(u8 c_port)
{
			 /**********按键后检测该端口		*******/
			u8 check_port = Swit_chr(c_port);
			DELAY_CLS();
			LCD_SW_Clr();
			gotoxy(1,0);
			SendStr(&check_port);
			gotoxy(1,1);
			SendStr("端口:");
			gotoxy(2,0);
			SendStr("正在检测该端口");
			delay_ms(500);
//			DELAY_CLS();
}

u8 Swit_chr(u8 s_port)
{
		u8 PORT[8] = {0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38};
		u8 final_port = PORT[s_port];


		return final_port;
}	 








