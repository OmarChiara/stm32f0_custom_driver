#include "stdint.h"
#include "stm32f0xx.h"
#include "GPIO.h"
#include "TM1637.h"

void delay(void);



int main(void)
{
	
GPIO_Init();
TM1637_Init(BRIGHTNESS_MAX);
	
	
		uint8_t Led_On[]="P TO";


				while(1)
				{
					TM1637_DisplayWord(Led_On);
					Led_Board_On();
					
				}				
	
}






void delay(void)
	
{
	unsigned int i=0;
	
	for(i=0; i<100000; i++);
	
}
