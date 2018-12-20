#include "extiout.h"
#include "hsj600.h"
#include "usart.h"
#include "includes.h"

uint8_t NEW_DATA=0;
uint8_t Data[DataLength];
uint8_t CardData[CardDataLength];
uint8_t CardType = 0;
uint8_t CardPro[17]={0x7e,0x7e,0x7e,0x7e,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

void GetCard(void)
{
//	while(1)
//	{
		if(NEW_DATA){
			NEW_DATA=0;
			CopyData(CardData,&Data[CardDateNum],CardDataLength);
			Pro_pack();
//			USER_UART1_Send_Str(CardPro,15);
			USART1_send_data(CardPro, CardProPackLen);
			memset(CardPro, 0x00, 17);
			//清空存放卡号的全局变量

			//USER_UART1_Send_Str(CardData,CardDataLength);
		}
//	}
}

//获取校验位数据
uint8_t GetBCC(uint8_t *Data,uint8_t Num)
{
	uint8_t BCC=0;
	for(;Num>0;Num--)
	{
		BCC^=*Data++;
	}
	
	return  BCC;
}

//清空数据
void ClearData(uint8_t *Data,uint8_t Num)
{
	uint8_t length;
	for(length=0;length<Num;length++){
		Data[length]=0x00;
	}
}

//复制数据
void CopyData(uint8_t  *DBfr,uint8_t *SBfr,uint8_t Len)
{
	uint8_t i;

	for(i=0;i<Len;i++)
	{
		DBfr[i] = SBfr[i];
	}
}

//协议打包
void Pro_pack(void)
{
	uint8_t open_port=0x11;
	u8 PORT[8] = {0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38};
	
	open_port = PORT[Tra_port()];
	CardPro[0] = 0x7E;
	CardPro[1] = 0x7E;
	CardPro[2] = 0x7E;
	CardPro[3] = 0x7E;
	CardPro[4] = 0x02; 
	CardPro[5] =open_port;
	
	CardPro[6]  = uitoa(CardData[3]>>4);
	CardPro[7]  = uitoa(CardData[3]&0x0F);
	CardPro[8]  = uitoa(CardData[2]>>4);
	CardPro[9]  = uitoa(CardData[2]&0x0F);
	CardPro[10] = uitoa(CardData[1]>>4);
	CardPro[11] = uitoa(CardData[1]&0x0F);
	CardPro[12] = uitoa(CardData[0]>>4);
	CardPro[13] = uitoa(CardData[0]&0x0F);
	
	CardPro[14]=GetSum(CardPro,14);
	CardPro[15]=0x0d;
	CardPro[16]=0x0a;

}

//转成字符
u8 uitoa(u8 num)
{
	u8 str;
	if(num >= 0 && num <= 9)
	{
		str = 0x30 + num;
	}
	if(num >= 0x0A && num <= 0x0F)
	{
		str = 0x41 + (num-0x0A);
	}

	return str;
}

//校验和
u8 GetSum(u8 *c_data, u8 data_length)
{
	u8 i=0;
	u8 sum = 0;
	for(i=0; i<data_length; ++i)
	{
		sum += *c_data++;
		sum= sum & 0xFF;
	}
	return sum;
}


