#include "usart6.h"	
#include "delay.h"
#include "stdarg.h"	 	 
#include "stdio.h"	 	 
#include "string.h"	  

u8  USART6_RX_BUF[USART6_MAX_RECV_LEN]; 				//接收缓冲,最大USART6_MAX_RECV_LEN个字节.
u8  USART6_TX_BUF[USART6_MAX_SEND_LEN]; 			//发送缓冲,最大USART6_MAX_SEND_LEN字节

vu16 USART6_RX_STA=0; 

void usart6_init(u32 bound){
   //GPIO端口设置
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE); //使能GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6,ENABLE);//使能USART1时钟
 
	//串口1对应引脚复用映射
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_USART6); //GPIOB11复用为USART6
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_USART6); //GPIOB10复用为USART6	
	
	//USART1端口配置
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; //GPIOB11和GPIOB10初始化
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOC,&GPIO_InitStructure); //初始化GPIOB11，和GPIOB10

   //USART1 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//波特率 
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
	USART_Init(USART6, &USART_InitStructure); //初始化串口3
	
	USART_Cmd(USART6, ENABLE);  //使能串口1 
	
	//USART_ClearFlag(USART1, USART_FLAG_TC);
		
	USART_ITConfig(USART6, USART_IT_RXNE, ENABLE);//开启中断 

	//Usart1 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = USART6_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2 ;//抢占优先级2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器	
}

void USART6_IRQHandler(void)                	//串口1中断服务程序
{
	u8 Res;   

	if(USART_GetITStatus(USART6, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
	{
		Res =USART_ReceiveData(USART6);//(USART1->DR);	//读取接收到的数据
		
		if((USART6_RX_STA&0x8000)==0)//接收未完成
		{
			if(USART6_RX_STA&0x4000)//接收到了0x0d
			{
				if(Res!=0x0a)USART6_RX_STA=0;//接收错误,重新开始
				else USART6_RX_STA|=0x8000;	//接收完成了 
			}
			else //还没收到0X0D
			{	
				if(Res==0x0d)USART6_RX_STA|=0x4000;
				else
				{
					USART6_RX_BUF[USART6_RX_STA&0X3FFF]=Res ;
					USART6_RX_STA++;
					if(USART6_RX_STA>(USART6_MAX_RECV_LEN-1))USART6_RX_STA=0;//接收数据错误,重新开始接收	  
				}		 
			}
		}   		 
  } 
} 
void u6_printf(char* fmt,...)  
{  
	u16 i,j;
	va_list ap;
	va_start(ap,fmt);
	vsprintf((char*)USART6_TX_BUF,fmt,ap);
	va_end(ap);
	i=strlen((const char*)USART6_TX_BUF);//此次发送数据的长度
	for(j=0;j<i;j++)//循环发送数据
	{
	  while(USART_GetFlagStatus(USART6,USART_FLAG_TC)==RESET);  //等待上次传输完成 
		USART_SendData(USART6,(uint8_t)USART6_TX_BUF[j]); 	 //发送数据到串口3 
	}
	
}

