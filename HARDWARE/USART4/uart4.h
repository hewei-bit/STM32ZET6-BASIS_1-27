#ifndef __UART4_H
#define __UART4_H
#include "sys.h" 

#define UART4_MAX_RECV_LEN		600					//�����ջ����ֽ���
#define UART4_MAX_SEND_LEN		600					//����ͻ����ֽ���
#define UART4_RX_EN 			1					//0,������;1,����.


extern u8   UART4_RX_BUF[ UART4_MAX_RECV_LEN]; 		//���ջ���,���USART3_MAX_RECV_LEN�ֽ�
extern u8   UART4_TX_BUF[ UART4_MAX_SEND_LEN]; 		//���ͻ���,���USART3_MAX_SEND_LEN�ֽ�
extern vu16  UART4_RX_STA;   						//��������״̬

void uart4_init(u32 bound);				//����2��ʼ�� 
void u4_printf(char* fmt,...);
#endif