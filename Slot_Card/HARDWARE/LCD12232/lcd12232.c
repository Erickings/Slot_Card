#include "lcd12232.h"
#include "delay.h"

void GPIO_Configuration(void)
{
	GPIO_InitTypeDef	GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOD,ENABLE);//ʹ��PB,PD�˿�ʱ��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);				//��ʼ��GPIOD0~7

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15|GPIO_Pin_12|GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);				//��ʼ��GPIB15,14,13
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
	wr_cmd(0x30);           //�趨Ϊ8λ���ƣ�����ָ����
  delay_ms(40);
  wr_cmd(0x34);            //�趨Ϊ8λ���ƣ�����ָ����
  delay_ms(40); 
	wr_cmd(0x0c);            // ��ʾ��
  delay_ms(40);
	LCD_CLS();                //����
  delay_ms(40);
	wr_cmd(0x06);	          // �趨AC��1           
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
               wr_cmd(0x36);     //����ָ�� ��ͼ��ʾ
               wr_cmd(y+0x80);    //�е�ַ
               wr_cmd(x+0x80+i);    //�е�ַ            
               wr_data(k);
               wr_data(k);
      wr_cmd(0x30);               //����ָ�� ��ͼ�ر�  
            }
       }   
}  
/////////////---------------��ʾһ����-----------------------
void disp_kuang()
{
  uchar i,j;
  wr_cmd(0x36);     //����ָ���
    for(i=0;i<8;i++)
   {
    wr_cmd(0x80);    //�е�ַ
    wr_cmd(0x80+i);    //�е�ַ            
    wr_data(0xff);
    wr_data(0xff);
   } 
      for(j=1;j<16;j++)
   {
     for(i=0;i<8;i++)
      {
       wr_cmd(0x80+j);    //�е�ַ
       wr_cmd(0x80+i);    //�е�ַ 
	   if(i==0) {wr_data(0x80);wr_data(0x00); }         
   	   if(i==7) {wr_data(0x00);wr_data(0x01); }
	   else  {wr_data(0x00);wr_data(0x00); }
       }
   }  

        for(j=0;j<15;j++)
   {
     for(i=0;i<8;i++)
      {
       wr_cmd(0x90+j);    //�е�ַ
       wr_cmd(0x90+i);    //�е�ַ 
	   if(i==0) {wr_data(0x80);wr_data(0x00); }         
   	   if(i==7) {wr_data(0x00);wr_data(0x01); }
	   else  {wr_data(0x00);wr_data(0x00); }
       }
   }   //��2����

     
   for(i=0;i<8;i++)
   {
    wr_cmd(0x9f);    //�е�ַ
    wr_cmd(0x90+i);    //�е�ַ            
    wr_data(0xff);
    wr_data(0xff);
   }	 //��������

  wr_cmd(0x30);               //����ָ�� ��ͼ�ر�  
}

   


//-------------------------------------------------
// ^_^      �� �� ˵ ��: ��ʾ128*64ȡģͼƬ     ^_^ ����ɨ�跽��ˮƽɨ��
//-------------------------------------------------
void display_pic(uchar *pic) 
{

  uchar x,y,i;
       
      for(y=0;y<32;y++)
      {    
            for(x=0;x<8;x++)
            { 
               wr_cmd(0x36);     //����ָ�� ��ͼ��ʾ��
               wr_cmd(y+0x80);    //�е�ַ
               wr_cmd(x+0x80+i);    //�е�ַ           
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

