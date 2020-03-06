#ifndef __WKUP_H
#define __WKUP_H

#include "sys.h"
#define WKUP_KD PAin(0)

u8 Check_WKUP(void);
void WKUP_Init(void);
void Sys_Enter_Standby(void);



#endif

