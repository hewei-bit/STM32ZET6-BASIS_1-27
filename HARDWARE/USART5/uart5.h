#ifndef __UART5_H
#define __UART5_H
#include "sys.h" 

#define UART5_MAX_RECV_LEN		600					//�����ջ����ֽ���
#define UART5_MAX_SEND_LEN		600					//����ͻ����ֽ���
#define UART5_RX_EN 			1					//0,������;1,����.


extern u8   UART5_RX_BUF[ UART5_MAX_RECV_LEN]; 		//���ջ���,���USART3_MAX_RECV_LEN�ֽ�
extern u8   UART5_TX_BUF[ UART5_MAX_SEND_LEN]; 		//���ͻ���,���USART3_MAX_SEND_LEN�ֽ�
extern vu16  UART5_RX_STA;   						//��������״̬

void uart5_init(u32 bound);				//����2��ʼ�� 
void u5_printf(char* fmt,...);
#endif