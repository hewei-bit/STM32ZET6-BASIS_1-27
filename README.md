# STM32ZET6-BASIS_1-27
STM32ZET6裸机实验综合1-27章
实验中对应串口说明 

* ADC:  
>>ADC1->PA.1--Channel1  
>>ADC3->  
* BEEP:  
>>BEEP->PB.8  
* DAC:  
>>DAC1->PA.4  
>>DAC2->PA.5  
* DAC-PWN:  
	PA.8(PWN_DAC)->PA.1(ADC)  
* 温湿度传感器DHT11:  
	GPIOG11(I-Wire)  
* 温度传感器DS18B20:  
	GPIOG11(I-Wire)  
* DMA:    
	  
* EXTI: 
>>	EXTI2<-KEY2:  	NVIC:P-2,S-2  
>>	EXTI3<-KEY1	    NVIC:P-2,S-1  
>>	EXTI4<-KEY0:	  NVIC:P-2,S-0
>>	EXTI0<-WK_UP:	  NVIC:P-2,S-3  
* KEY:  
>>	KEY0,1,2->PE2,3,4 
>>	WK_UP->PA.0	  
* LCD:  
>>	FSMC_BANK1_NORSRAM4   
>>	PB0 
>>	PD0,1,4,5,8,9,10,14,15  
>>	PE7,8,9,10,11,12,13,14,15  
>>	PG0,12  
* LED:  
>>	LED0,1->PB.5,E.5  
  
* 光敏传感器LSENSOR:  
>>	ADC3->PF.8--Channel6  
* OLED:  
>>两线：	I2C_SDA->PA3  
>>>>I2C_SDL->PA2  
* RTC：  
>>NVIC:P-0,S-0  	
* SRAM：  
>>	FSMC_BANK1_NORSRAM3  
>>	GPIOD?,E?,F?,G?  
* TIMER:  
>>	TIM3_CH1,TIM3_CH2,TIM3_CH3,TIM3_CH4  
>>	没有重映像的对应情况:  
>>	PA6,PA7,PB0,PB1  
>>	部分重映像:  
>>	PB4,PB5,PB0,PB1  
>>	完全重映像:  
>>	PC6,PC7,PC8,PC9  	
  
>>	TIM3_INIT  
>>	TIM3_INT:	NVIC:P-1,S-3  
>>	TIM3_PWN->PB5  
>>	TIM5_CAP<-PA0	NVIC:P-0,S-1  
	  
* 内部温度传感器TSENSOR:  
	ADC1->Channel16  
  
* UART:  
>>	UART1.TX->PA.9  
>>	UART1.RX->PA.10	NVIC:P-0,S-3  
>>	UART2.TX->PA.2  
>>	UART2.RX->PA.3	NVIC:P-3,S-3  
>>	UART3.TX->PB.10  
>>	UART3.RX->PB.11	NVIC:P-2,S-3  
* 超声波传感器WAVE:  
>>	TRIG->PE4  
>>	EHCO<-PE6  
>>	EXTI6<-PE6	NVIC:P-2,S-2  
* WDG:  
>>	IWDG:  		
>>	WWDG:		NVIC:P-2,S-3  
* WK_UP:  
>>	EXTI1<-PA0	NVIC:P-2,S-2  
