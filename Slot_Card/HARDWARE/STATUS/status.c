#include "event_def.h"
#include "status.h"
#include "usart.h"


u8 remaining_sum[8] = {0x31,0x32,0x33,0x34,'.',0x35,0x36};

event_step step;

void Def_state(void)
{
		/**********��ʼ��ʾ����		*******/
			LCD_SW_Set();
			DELAY_CLS();	

			gotoxy(1,2);
			SendStr("��ӭʹ��");
			gotoxy(2,2);
			SendStr("������");	
			delay_ms(300);
			DELAY_CLS();
}

void Selet_port(void)
{	
			LCD_SW_Set();

			DELAY_CLS();	
			gotoxy(1,0);
			SendStr("��ѡ����˿�:");	
			delay_ms(300);
//			DELAY_CLS();
	
}

void Rem_sum(void)
{
		/************��ʾ��� *************/
			LCD_SW_Clr();
	 		DELAY_CLS();
			gotoxy(1,0);
			SendStr(&pro_open_port);
	 	 	gotoxy(1,1);
			SendStr("�˿��Ѵ򿪣�");
			gotoxy(2,0);
			SendStr("���");
	 		gotoxy(2,2);
			SendStr(rem_sum);
			gotoxy(2,6);
			SendStr("Ԫ");
	 		delay_ms(700);
//			DELAY_CLS();
	
}


void  Open_succ(u8 s_port)
{
	 /**********ѡ��˿ڳɹ���ʾ*******/
			u8 succ_port = Swit_chr(s_port);
			DELAY_CLS();
			LCD_SW_Clr();
			gotoxy(1,0);
			SendStr(&succ_port);
			gotoxy(1,1);
			SendStr("�Ŷ˿ڿ���");
			gotoxy(2,0);
			SendStr("��ˢ��:");	
			delay_ms(700);
//			DELAY_CLS();
}

void Charging(void)
{
			DELAY_CLS();
			LCD_SW_Clr();
			gotoxy(1,0);
			SendStr("�����...");
			delay_ms(500);
//			DELAY_CLS();

}	
	 

void Open_fail(fail_sort sort, u8 op_fail)
{

		if( sort==insu_funds || sort==card_inva || sort==port_conflic || sort==comm_fail )
		{
			switch(sort){
				case insu_funds:
					/**********�򿪶˿�ʧ����ʾ������		*******/
					DELAY_CLS();
					LCD_SW_Clr();
					gotoxy(1,0);
					SendStr(&op_fail);
					gotoxy(1,1);
					SendStr("�˿ڴ�ʧ��");
					gotoxy(2,2);
					SendStr("����");	
					delay_ms(700);
//					DELAY_CLS();
					
					break;
				case card_inva:
				 /**********�򿪶˿�ʧ����ʾ��ͨѶʧ��		*******/
					DELAY_CLS();					
					LCD_SW_Clr();
					gotoxy(1,0);
					SendStr(&op_fail);
					gotoxy(1,1);
					SendStr("�˿ڴ�ʧ��");
					gotoxy(2,2);
					SendStr("�˿���Ч");	
					delay_ms(700);
//					DELAY_CLS();
				
					break;
				
				case port_conflic:
						 /**********�򿪶˿�ʧ����ʾ���˿ڳ�ͻ*******/
						DELAY_CLS();		
						LCD_SW_Clr();
						gotoxy(1,0);
						SendStr(&op_fail);
						gotoxy(1,1);
						SendStr("�˿ڴ�ʧ��");
						gotoxy(2,1);
						SendStr("�˿��ѱ�ռ��");	
						delay_ms(700);

					break;
				
								
				case comm_fail:
						 /**********�򿪶˿�ʧ����ʾ���˿ڳ�ͻ*******/
						DELAY_CLS();		
						LCD_SW_Clr();
						gotoxy(1,0);
						SendStr(&op_fail);
						gotoxy(1,1);
						SendStr("�˿ڴ�ʧ��");
						gotoxy(2,2);
						SendStr("�����쳣");	
						delay_ms(700);

					break;
					
					
			}
		}
}	
	

void Reading_card(void)
{
	 /**********���ڶ�����ʾ		*******/
			LCD_SW_Clr();
			DELAY_CLS();
			gotoxy(1,0);
			SendStr("  ���ڶ���");
			gotoxy(2,0);
			SendStr("  ���Ժ�...");	
			delay_ms(500);
//		DELAY_CLS();

}

void Port_occu(u8 f_port)
{
 	 /**********ѡ��˿�ʧ����ʾ		*******/
			u8 fail_port = Swit_chr(f_port);							//��ʮ����ת����ʮ������
			DELAY_CLS();
			LCD_SW_Clr();
			gotoxy(1,0);
			SendStr(&fail_port);
			gotoxy(1,1);
			SendStr("�˿ڿ�����");
			gotoxy(2,0);
			SendStr("���Ժ�...");	
			delay_ms(10);
			DELAY_CLS();

}

void Che_port(u8 c_port)
{
			 /**********��������ö˿�		*******/
			u8 check_port = Swit_chr(c_port);
			DELAY_CLS();
			LCD_SW_Clr();
			gotoxy(1,0);
			SendStr(&check_port);
			gotoxy(1,1);
			SendStr("�˿�:");
			gotoxy(2,0);
			SendStr("���ڼ��ö˿�");
			delay_ms(500);
//			DELAY_CLS();
}

u8 Swit_chr(u8 s_port)
{
		u8 PORT[8] = {0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38};
		u8 final_port = PORT[s_port];


		return final_port;
}	 








