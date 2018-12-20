#include "lcd12232.h"
#include "delay.h"

void GPIO_Configuration(void)
{
	GPIO_InitTypeDef	GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOD,ENABLE);//使能PB,PD端口时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//IO口速度为50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);				//初始化GPIOD0~7

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15|GPIO_Pin_12|GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//IO口速度为50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);				//初始化GPIB15,14,13
}


void wr_cmd(uchar cmd)
{
		
   uchar i;
    C_S = 1;
    SID = 1;
    for (i=0;i<5;i++)
	{
    SCLK = 0;
    SCLK = 1;
	}
    SCLK = 0;

	SID=0;
	for(i=0;i<3;i++)
	{
		SCLK=1;
		SCLK=0;
	}	
	
	for(i=0;i<4;i++)
	{
				
		if(cmd&0x80) SID=1;
		else   SID=0;
		SCLK=1;
		SCLK=0;
		cmd<<=1;
	}	
	
	SID=0;
	delay_us(150);
	for(i=0;i<4;i++)
	{
		SCLK=1;
		SCLK=0;		
	}	
					
	for(i=0;i<4;i++)
	{
		if(cmd&0x80) SID=1;
		else   SID=0;
		SCLK=1;
		SCLK=0;
		cmd<<=1;
	}	
	
	SID=0;
	for(i=0;i<4;i++)
	{
		SCLK=1;
		SCLK=0;
	}	
	
  	C_S = 0;
	delay_us(100);

}

//----------------------------------------------------------------

void wr_data(uchar dat)
{
 	
	     uchar i;
   C_S = 1;
   SID = 1;
   for (i=0;i<5;i++)
   {
   SCLK = 0;
   SCLK = 1;
   }
   SCLK = 0;
   SID  = 0;
   SCLK = 1;

   SCLK = 0;
   SID  = 1;
   SCLK = 1;

   SCLK = 0;
   SID  = 0;
   SCLK = 1;

   SCLK = 0;
   for (i=0;i<4;i++)
   {
   
		if(dat&0x80) SID=1;
		else   SID=0;
  	SCLK = 1;
	  SCLK = 0; 
		 dat<<=1;
   }


    SID  =0;
    for (i=0;i<4;i++)
	{
	 SCLK = 0;
     SCLK = 1;
	}
	 SCLK = 0;

    for (i=0;i<4;i++)
	{
     
		if(dat&0x80) SID=1;
		else   SID=0;
	  SCLK = 1;
	  SCLK = 0;
		dat<<=1;
	}

	 SID = 0;
 	for (i=0;i<4;i++)
	{
	 SCLK = 1;
	 SCLK = 0;
	}
     C_S = 0;
	delay_us(100);
	
	
}


//----------------------------------------------------------------

void DELAY_CLS()

{
   	delay_ms(100);
    LCD_CLS();
 
}

//----------------------------------------------------------------

void LCD_CLS()
{
  wr_cmd(0x30);    // 8-bit interface, Extended instruction
	wr_cmd(0x01);
	delay_ms(5);
}

//----------------------------------------------------------------

void SendStr(uchar  *ptString)
{
	while((*ptString)!='\0')
	{
		wr_data(*ptString++);
	}
}

//----------------------------------------------------------------

void SendStr1(uchar  *ptString)
{
	while((*ptString)!='\0')
	{
		wr_data( *ptString++);
    delay_ms(30);
	}
}


//----------------------------------------------------------------

void init_lcd(void)
{
  delay_ms(40);
	wr_cmd(0x30);           //设定为8位控制，基本指令起动
  delay_ms(40);
  wr_cmd(0x34);            //设定为8位控制，扩充指令起动
  delay_ms(40); 
	wr_cmd(0x0c);            // 显示打开
  delay_ms(40);
	LCD_CLS();                //清屏
  delay_ms(40);
	wr_cmd(0x06);	          // 设定AC加1           
}

//----------------------------------------------------------------

void gotoxy(uint row, uint col)
{
    switch(row)
    {
        case 1: wr_cmd(0x80+col);break;
        case 2: wr_cmd(0x90+col);break;
    }
}

//----------------------------------------------------------------

//----------------------------------------------------------------

void  testshow(uchar fst, uchar snd)
{ 
  uchar x,y,i,k;
    
      for(y=0;y<32;y++)
      {     if((y%2)==1)
               k=fst;
            else
               k=snd;
            for(x=0;x<8;x++)
            { 
               wr_cmd(0x36);     //扩充指令 绘图显示
               wr_cmd(y+0x80);    //行地址
               wr_cmd(x+0x80+i);    //列地址            
               wr_data(k);
               wr_data(k);
      wr_cmd(0x30);               //扩充指令 绘图关闭  
            }
       }   
}  
/////////////---------------显示一方框-----------------------
void disp_kuang()
{
  uchar i,j;
  wr_cmd(0x36);     //扩充指令打开
    for(i=0;i<8;i++)
   {
    wr_cmd(0x80);    //行地址
    wr_cmd(0x80+i);    //列地址            
    wr_data(0xff);
    wr_data(0xff);
   } 
      for(j=1;j<16;j++)
   {
     for(i=0;i<8;i++)
      {
       wr_cmd(0x80+j);    //行地址
       wr_cmd(0x80+i);    //列地址 
	   if(i==0) {wr_data(0x80);wr_data(0x00); }         
   	   if(i==7) {wr_data(0x00);wr_data(0x01); }
	   else  {wr_data(0x00);wr_data(0x00); }
       }
   }  

        for(j=0;j<15;j++)
   {
     for(i=0;i<8;i++)
      {
       wr_cmd(0x90+j);    //行地址
       wr_cmd(0x90+i);    //列地址 
	   if(i==0) {wr_data(0x80);wr_data(0x00); }         
   	   if(i==7) {wr_data(0x00);wr_data(0x01); }
	   else  {wr_data(0x00);wr_data(0x00); }
       }
   }   //第2排完

     
   for(i=0;i<8;i++)
   {
    wr_cmd(0x9f);    //行地址
    wr_cmd(0x90+i);    //列地址            
    wr_data(0xff);
    wr_data(0xff);
   }	 //第四排完

  wr_cmd(0x30);               //扩充指令 绘图关闭  
}

   


//-------------------------------------------------
// ^_^      功 能 说 明: 显示128*64取模图片     ^_^ 数据扫描方向：水平扫描
//-------------------------------------------------
void display_pic(uchar *pic) 
{

  uchar x,y,i;
       
      for(y=0;y<32;y++)
      {    
            for(x=0;x<8;x++)
            { 
               wr_cmd(0x36);     //扩充指令 绘图显示打开
               wr_cmd(y+0x80);    //行地址
               wr_cmd(x+0x80+i);    //列地址           
               wr_data(*pic++);
               wr_data(*pic++);
         
            }
       }  
   
}


 // Call built-in Charactors
void CallBuiltinChar(void)
{
	uint i,j;
	// 0xA140 ~ 0xA15F
	gotoxy(2,0);
	for (i = 0; i < 32; i++)
	{
		wr_data(0xA1);
		wr_data(0x40 + i);
	}
   	gotoxy(3,0);
	for (j = 0; j < 16; j++)
	{
		wr_data(0xA2);
		wr_data(0x45 + j);
	}
}

