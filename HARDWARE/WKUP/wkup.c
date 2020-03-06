#include "wkup.h"
#include "led.h"
#include "delay.h"


void Sys_Standby()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,ENABLE);
	PWR_WakeUpPinCmd(ENABLE);//使能唤醒功能引脚
	PWR_EnterSTANDBYMode();//进入STANDBY模式
	
}
//系统进入待机模式
void Sys_Enter_Standby(void)
{
	RCC_APB2PeriphResetCmd(0x01FC,DISABLE);//复位所有IO口
	Sys_Standby();
}

u8 Check_WKUP(void)
{
	u8 t = 0;
	LED0 = 0;
	while(1)
	{
		if(WKUP_KD)
		{
			t++;
			delay_ms(30);
			if(t >= 100)
			{
				LED0 = 0;
				return 1;
			}
		}
		else
		{
			LED0 = 1;
			return 0;
		}
	}
}

void EXTI1_IRQHandler(void)
{
	EXTI_ClearITPendingBit(EXTI_Line1);//清除中断标志
	if(Check_WKUP())
	{
		Sys_Enter_Standby();
	}
}

void WKUP_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	//使用外部中断
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);
	
	EXTI_InitStruct.EXTI_Line = EXTI_Line1;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_Init(&EXTI_InitStruct);//初始化外部中断
	
	NVIC_InitStruct.NVIC_IRQChannel = EXTI1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&NVIC_InitStruct);
	
	if(Check_WKUP() == 0)Sys_Standby();
	
}
