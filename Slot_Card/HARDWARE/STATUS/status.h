#ifndef __STATUS_H
#define __STATUS_H

#include "sys.h"
#include "lcd12232.h"
#include "event_def.h"


extern event_step step;


void Def_state(void);
void Rem_sum(void);
void Open_succ(u8 s_port);
void Charging(void);
void Open_fail(fail_sort sort, u8 op_fail);
void Reading_card(void);
extern void Port_occu(u8 p_num);
void Che_port(u8 c_port);
void Selet_port(void);
u8 Swit_chr(u8 s_port);


























#endif
