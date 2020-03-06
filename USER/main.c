#include "stm32f10x.h"
#include "sys.h"
#include "usart.h"
#include "delay.h"

#include "beep.h"
#include "led.h"
#include "rtc.h"
#include "usmart.h"
#include "lcd.h"
#include "key.h"
#include "wkup.h"
#include "adc.h"
#include "dac.h"
#include "timer.h"
#include "dma.h"
#include "usart.h"
#include "usart3.h"
#include "usart2.h"

void PWM_DAC_Set(u16 vol)
{
	float temp=vol;
	temp/=100;
	temp=temp*256/3.3;
	TIM_SetCompare1(TIM1,temp);
}
void LED1SET(void)
{
	LED1=!LED1;
}

#define SEND_BUF_SIZE 8200

u8 SendBuff[SEND_BUF_SIZE];
const u8 TEXT_TO_SEND[] = {"HEWEI IS LEARNING stm32"};


 int main(void)
 {	 
	u16 i;
 	u8 t=0;	 
	u8 j,mask = 0;
	float pro = 0; 
	 
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);	 	//串口初始化为115200
	KEY_Init();				  //KEY初始化
 	LED_Init();			     //LED端口初始化
	usmart_dev.init(72);	//初始化USMART	
	LCD_Init();		 //LCD初始化
	BEEP_Init(); 
	 
	MYDMA_Config(DMA1_Channel4,(u32)&USART1->DR,(u32)SendBuff,SEND_BUF_SIZE);//DMA1通道4,外设为串口1,存储器为SendBuff,长度SEND_BUF_SIZE.
 	POINT_COLOR=RED;//设置字体为红色 
	LCD_ShowString(30,50,200,16,16,"WarShip STM32");	
	LCD_ShowString(30,70,200,16,16,"DMA TEST");	
	LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(30,110,200,16,16,"2015/1/15");	
 	LCD_ShowString(30,130,200,16,16,"KEY0:Start");
	//显示提示信息	

	j = sizeof(TEXT_TO_SEND);
	for(i = 0;i < SEND_BUF_SIZE;i++){
		if(t >= j){
			if(mask){
				SendBuff[i] = 0x0a;
				t = 0;
			}
			else{
				SendBuff[i] = 0x0d;
				mask++;
			}		
		}
		else{
			mask = 0;
			SendBuff[i] = TEXT_TO_SEND[t];
			t++;
		}
	}
 
	POINT_COLOR=BLUE;//设置字体为蓝色
	while(1)
	{
		t = KEY_Scan(0);
		if(t == KEY0_PRES){
			LCD_ShowString(30,150,200,16,16,"Starting Transimiting...");
			LCD_ShowString(30,170,200,16,16,"   %");
			printf("\r\nDMA DATA\r\n");
			USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);//使能USART1的DMA发送
			MYDMA_Enable(DMA1_Channel4);
			while(1){
				if(DMA_GetFlagStatus(DMA1_FLAG_TC4)!= RESET){
					DMA_ClearFlag(DMA1_FLAG_TC4);
					break;
				}
				pro = DMA_GetCurrDataCounter(DMA1_Channel4);
				pro = 1-pro/SEND_BUF_SIZE;
				pro*= 100;
				LCD_ShowNum(30,170,pro,3,16);
			}
			LCD_ShowNum(30,170,100,3,16);
			LCD_ShowString(30,150,200,16,16,"Transimit Finished!");
		}
		i++;
		delay_ms(10);
		if(i==20)
		{
			LED0=!LED0;//提示系统正在运行	
			i=0;
		}	
	}
 }

/******************************RTC实验*************************************/

 
/******************************RTC实验*************************************/

//		if(t!=calendar.sec)
//		{
//			t=calendar.sec;
//			LCD_ShowNum(60,150,calendar.w_year,4,16);									  
//			LCD_ShowNum(100,150,calendar.w_month,2,16);									  
//			LCD_ShowNum(124,150,calendar.w_date,2,16);	 
//			switch(calendar.week)
//			{
//				case 0:
//					LCD_ShowString(60,200,200,16,16,"Sunday   ");
//					break;
//				case 1:
//					LCD_ShowString(60,200,200,16,16,"Monday   ");
//					break;
//				case 2:
//					LCD_ShowString(60,200,200,16,16,"Tuesday  ");
//					break;
//				case 3:
//					LCD_ShowString(60,200,200,16,16,"Wednesday");
//					break;
//				case 4:
//					LCD_ShowString(60,200,200,16,16,"Thursday ");
//					break;
//				case 5:
//					LCD_ShowString(60,200,200,16,16,"Friday   ");
//					break;
//				case 6:
//					LCD_ShowString(60,200,200,16,16,"Saturday ");
//					break;  
//			}
//			LCD_ShowNum(60,180,calendar.hour,2,16);									  
//			LCD_ShowNum(84,180,calendar.min,2,16);									  
//			LCD_ShowNum(108,180,calendar.sec,2,16);
//			
//			
//			
//			LED0=!LED0;
//			delay_ms(250);
//		}

/***********************串口1通信*******************/

//		if(USART_RX_STA&0x8000)
//		{					   
//			len=USART_RX_STA&0x3fff;//得到此次接收到的数据长度
//			printf("\r\n您发送的消息为:\r\n\r\n");
//			for(t=0;t<len;t++)
//			{
//				USART_SendData(USART3, USART_RX_BUF[t]);//向串口1发送数据
//				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//等待发送结束
//			}
//			printf("\r\n\r\n");//插入换行
//			USART_RX_STA=0;
//		}
//		else
//		{
//			times++;
//			if(times%5000==0)
//			{
//				printf("\r\n战舰STM32开发板 串口实验\r\n");
//				printf("正点原子@ALIENTEK\r\n\r\n");
//			}
//			if(times%200==0)printf("请输入数据,以回车键结束\n");  
//			if(times%30==0)LED0=!LED0;//闪烁LED,提示系统正在运行.
//			delay_ms(10); 
//		}
//		

 /********************uart3通信实验************************/  

//		if(USART3_RX_STA&0x8000)
//		{                                           
//			len=USART3_RX_STA&0x3FFF;//得到此次接收数据的长度
//			u3_printf("\r\n您发送的消息为:\r\n\r\n");
//			for(t=0;t<len;t++)
//			{
//				USART_SendData(USART1, USART3_RX_BUF[t]);//向串口3发送数
//				LCD_ShowxNum(60+2*t,250,USART3_RX_BUF[t],10,20,0);

//				while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);//等待发送结束
//			}
//			u3_printf("\r\n\r\n");//插入换行
//			USART3_RX_STA = 0;
//		}else
//		{
//			times++;
//			if(times%500 == 0)
//			{
//				u3_printf("\r\n 串口3实验\r\n");
//				u3_printf("何蔚666\r\n\r\n");
//			}
//			if(times%200==0)u3_printf("请输入数据,以回车结束\r\n");  
//			if(times%300==0)LED0=!LED0;//闪烁LED,提示系统正在运行
//			delay_ms(10);   
//		}
		
/********************两机通信**************/

//		if(USART_RX_STA&0X8000)				    		//接收到一次数据了
//		{
// 			reclen=USART_RX_STA& 0X7FFF;				//得到数据长度
//		  	USART_RX_BUF[reclen]=0;	 					//加入结束符
//			for(t=0;t<reclen;t++)
//			{
//				while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);		//等待发送结束
//				USART_SendData(USART2, USART_RX_BUF[t]);         			//向串口2发送数据
//			}
//			u2_printf("\r\n\r\n");//插入回车换行
//			printf("USART_RX_BUF:%s\r\n",USART_RX_BUF);
//			printf("reclen:%d\r\n",reclen);
// 			USART_RX_STA=0;	 	
//		}
//	 	
//		if(USART2_RX_STA&0X8000)		//接收到一次数据了
//		{
// 			reclen=USART2_RX_STA&0X7FFF;//得到数据长度
//		  	USART2_RX_BUF[reclen]=0;    //加入结束符
//			for(t=0;t<reclen;t++)
//			{	
//				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//等待发送结束
//				USART_SendData(USART1, USART2_RX_BUF[t]);//向串口1发送数据
//			}
//			printf("\r\n\r\n");	//插入换行
//			printf("reclen:%d\r\n",reclen); 
//			USART2_RX_STA=0;
//	    }

