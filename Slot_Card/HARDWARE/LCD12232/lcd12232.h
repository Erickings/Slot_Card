#ifndef __LCD12232_H
#define __LCD12232_H	 
#include "sys.h"
#include "delay.h"

#define uchar unsigned char
#define uint  unsigned int

//12232B液晶指令/数据选择引脚
#define	LCD_SID_Set()	GPIO_SetBits(GPIOB, GPIO_Pin_15)
#define	LCD_SID_Clr()	GPIO_ResetBits(GPIOB, GPIO_Pin_15)

//12232B液晶使能引脚
#define	LCD_SCLK_Set()	GPIO_SetBits(GPIOB, GPIO_Pin_13)
#define	LCD_SCLK_Clr()	GPIO_ResetBits(GPIOB, GPIO_Pin_13)

//12232B液晶读写引脚
#define	LCD_CS_Set()	GPIO_SetBits(GPIOB, GPIO_Pin_12)
#define	LCD_CS_Clr()	GPIO_ResetBits(GPIOB, GPIO_Pin_12)

#define	LCD_SW_Set()	GPIO_SetBits(GPIOB, GPIO_Pin_7)				//置高位，关闭背光
#define	LCD_SW_Clr()	GPIO_ResetBits(GPIOB, GPIO_Pin_7)			//置低位，打开背光

//12232B液晶读写引脚
#define	LCD_RST_Set()	GPIO_SetBits(GPIOB, GPIO_Pin_6)
#define	LCD_RST_Clr()	GPIO_ResetBits(GPIOB, GPIO_Pin_6)


#define  C_S  PBout(12)
#define  SID  PBout(15)
#define  SCLK PBout(13)

//12232B液晶数据端口	PD0~7
#define	DATAOUT(x)	GPIO_Write(GPIOB, x)


//12232B液晶显示屏
void GPIO_Configuration(void);
void DELAY_CLS(void);
void wr_data(uchar wdata);
void wr_cmd(uchar cmd);	
void LCD_CLS(void);
void wr_cmd_data( uchar cmd,uchar dat1,uchar dat2);
void gotoxy(uint row, uint col);
void SendStr(uchar  *ptString);
void SendStr1(uchar  *ptString);


void init_lcd(void);
void disp_Graphic(void);
void disp_fangkuang(void );
void  testshow(uchar fst, uchar snd);
void CallBuiltinChar(void);
void display_pic(uchar *pic);
void disp_kuang(void);







#endif
