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
	 
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
	KEY_Init();				  //KEY��ʼ��
 	LED_Init();			     //LED�˿ڳ�ʼ��
	usmart_dev.init(72);	//��ʼ��USMART	
	LCD_Init();		 //LCD��ʼ��
	BEEP_Init(); 
	 
	MYDMA_Config(DMA1_Channel4,(u32)&USART1->DR,(u32)SendBuff,SEND_BUF_SIZE);//DMA1ͨ��4,����Ϊ����1,�洢��ΪSendBuff,����SEND_BUF_SIZE.
 	POINT_COLOR=RED;//��������Ϊ��ɫ 
	LCD_ShowString(30,50,200,16,16,"WarShip STM32");	
	LCD_ShowString(30,70,200,16,16,"DMA TEST");	
	LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(30,110,200,16,16,"2015/1/15");	
 	LCD_ShowString(30,130,200,16,16,"KEY0:Start");
	//��ʾ��ʾ��Ϣ	

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
 
	POINT_COLOR=BLUE;//��������Ϊ��ɫ
	while(1)
	{
		t = KEY_Scan(0);
		if(t == KEY0_PRES){
			LCD_ShowString(30,150,200,16,16,"Starting Transimiting...");
			LCD_ShowString(30,170,200,16,16,"   %");
			printf("\r\nDMA DATA\r\n");
			USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);//ʹ��USART1��DMA����
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
			LED0=!LED0;//��ʾϵͳ��������	
			i=0;
		}	
	}
 }

/******************************RTCʵ��*************************************/

 
/******************************RTCʵ��*************************************/

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

/***********************����1ͨ��*******************/

//		if(USART_RX_STA&0x8000)
//		{					   
//			len=USART_RX_STA&0x3fff;//�õ��˴ν��յ������ݳ���
//			printf("\r\n�����͵���ϢΪ:\r\n\r\n");
//			for(t=0;t<len;t++)
//			{
//				USART_SendData(USART3, USART_RX_BUF[t]);//�򴮿�1��������
//				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
//			}
//			printf("\r\n\r\n");//���뻻��
//			USART_RX_STA=0;
//		}
//		else
//		{
//			times++;
//			if(times%5000==0)
//			{
//				printf("\r\nս��STM32������ ����ʵ��\r\n");
//				printf("����ԭ��@ALIENTEK\r\n\r\n");
//			}
//			if(times%200==0)printf("����������,�Իس�������\n");  
//			if(times%30==0)LED0=!LED0;//��˸LED,��ʾϵͳ��������.
//			delay_ms(10); 
//		}
//		

 /********************uart3ͨ��ʵ��************************/  

//		if(USART3_RX_STA&0x8000)
//		{                                           
//			len=USART3_RX_STA&0x3FFF;//�õ��˴ν������ݵĳ���
//			u3_printf("\r\n�����͵���ϢΪ:\r\n\r\n");
//			for(t=0;t<len;t++)
//			{
//				USART_SendData(USART1, USART3_RX_BUF[t]);//�򴮿�3������
//				LCD_ShowxNum(60+2*t,250,USART3_RX_BUF[t],10,20,0);

//				while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
//			}
//			u3_printf("\r\n\r\n");//���뻻��
//			USART3_RX_STA = 0;
//		}else
//		{
//			times++;
//			if(times%500 == 0)
//			{
//				u3_printf("\r\n ����3ʵ��\r\n");
//				u3_printf("��ε666\r\n\r\n");
//			}
//			if(times%200==0)u3_printf("����������,�Իس�����\r\n");  
//			if(times%300==0)LED0=!LED0;//��˸LED,��ʾϵͳ��������
//			delay_ms(10);   
//		}
		
/********************����ͨ��**************/

//		if(USART_RX_STA&0X8000)				    		//���յ�һ��������
//		{
// 			reclen=USART_RX_STA& 0X7FFF;				//�õ����ݳ���
//		  	USART_RX_BUF[reclen]=0;	 					//���������
//			for(t=0;t<reclen;t++)
//			{
//				while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);		//�ȴ����ͽ���
//				USART_SendData(USART2, USART_RX_BUF[t]);         			//�򴮿�2��������
//			}
//			u2_printf("\r\n\r\n");//����س�����
//			printf("USART_RX_BUF:%s\r\n",USART_RX_BUF);
//			printf("reclen:%d\r\n",reclen);
// 			USART_RX_STA=0;	 	
//		}
//	 	
//		if(USART2_RX_STA&0X8000)		//���յ�һ��������
//		{
// 			reclen=USART2_RX_STA&0X7FFF;//�õ����ݳ���
//		  	USART2_RX_BUF[reclen]=0;    //���������
//			for(t=0;t<reclen;t++)
//			{	
//				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
//				USART_SendData(USART1, USART2_RX_BUF[t]);//�򴮿�1��������
//			}
//			printf("\r\n\r\n");	//���뻻��
//			printf("reclen:%d\r\n",reclen); 
//			USART2_RX_STA=0;
//	    }

