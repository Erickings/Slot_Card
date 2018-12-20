#ifndef EVENT_DEF_H
#define EVENT_DEF_H

#include <stdint.h>



//按键操作
typedef enum{
   def_status_logo,								//默认状态
	 def_status_sel_port,
	 key_op,	 							//按键操作 
	 slot_card,	            //刷卡操作
	 reading_card ,					//读卡中
	 sel_port , 						//选择端口
	 ret_status ,						//刷卡后的状态
	 slot_reslut,
	 parse_pro,
}event_step;


//刷卡后的状态结果
typedef enum{
     
	insu_funds,	 						//余额不足
	comm_fail,							//通讯失败
	card_inva,							//此卡无效
	port_conflic,						//端口冲突		
	
}fail_sort;






#endif
