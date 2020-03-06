#ifndef __UART5_H
#define __UART5_H
#include "sys.h" 

#define UART5_MAX_RECV_LEN		600					//最大接收缓存字节数
#define UART5_MAX_SEND_LEN		600					//最大发送缓存字节数
#define UART5_RX_EN 			1					//0,不接收;1,接收.


extern u8   UART5_RX_BUF[ UART5_MAX_RECV_LEN]; 		//接收缓冲,最大USART3_MAX_RECV_LEN字节
extern u8   UART5_TX_BUF[ UART5_MAX_SEND_LEN]; 		//发送缓冲,最大USART3_MAX_SEND_LEN字节
extern vu16  UART5_RX_STA;   						//接收数据状态

void uart5_init(u32 bound);				//串口2初始化 
void u5_printf(char* fmt,...);
#endif