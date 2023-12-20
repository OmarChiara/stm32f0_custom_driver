#include "GPIO_types.h"
#include "stm32f0xx.h"
#include "GPIO.h"
#include "stdlib.h"



void GPIO_Init(void)
{
RCC->AHBENR |= (1<<17);

uint8_t DevCtr;
 	
PORT_Driver_Config_t* loc_Driver_config;
PORT_Config_t* loc_port_config;

	loc_Driver_config = &PORT_Driver_Config;
	
	for(DevCtr = 0; DevCtr < loc_Driver_config->NumberOfPorts; DevCtr++)
	{
				loc_port_config = &loc_Driver_config->PortConfig_Arr[DevCtr];

	
							/****************GPIO Mode Configuration***********************/
							if((loc_port_config->mode) == INPUT_MODE)
							{
								
								GPIOA->MODER |= (0X00 << (loc_port_config->Pin * 2));
							
							}
							else if((loc_port_config->mode) == OUTPUT_MODE)
							{
								
								GPIOA->MODER |= (0X01 << (loc_port_config->Pin * 2));
								
							}
							
							else if((loc_port_config->mode) == ALTERNATE_F)
							{
								
								GPIOA->MODER |= (0X0A << (loc_port_config->Pin * 2));
								
							}
							
							else if((loc_port_config->mode) == ANALOG_MODE)
							{
								
								GPIOA->MODER |= (0X0B << (loc_port_config->Pin * 2));
								
							}
							
							/****************PULL UP-PULL DOWN configuration***************/
							
							if((loc_port_config->pdr) == NO_PUPD)
							{
								
								GPIOA->PUPDR |= (0X00 << (loc_port_config->Pin * 2));
								
							}
							
							else if((loc_port_config->pdr) == PULL_UP)
							{
								
								GPIOA->PUPDR |= (0X01 << (loc_port_config->Pin * 2));
								
							}
							
							else if((loc_port_config->pdr) == PULL_DOWN)
							{
								
								GPIOA->PUPDR |= (0X0A << (loc_port_config->Pin * 2));
								
							}
							
							else
							{
								//Error handling
							}
		}

		
}

void GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState)
{
	if (PinState != GPIO_PIN_RESET)
  {
    GPIOx->BSRR = GPIO_Pin;
  }
  else
  {
    GPIOx->BRR=GPIO_Pin;
  }
}

uint8_t GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	
		uint8_t bitstatus;

  /* Check the parameters */


  if ((GPIOx->IDR & GPIO_Pin) != (uint32_t)GPIO_PIN_RESET)
  {
    bitstatus = GPIO_PIN_SET;
  }
  else
  {
    bitstatus = GPIO_PIN_RESET;
  }
  return bitstatus;
  }



