

#ifndef INC_GPIO_TYPES_H_
#define INC_GPIO_TYPES_H_

#include "stdint.h"




typedef enum
{
	PIN_0,
	CLK,
	DATA,
	PIN_3,
	PIN_4,
	PIN_5,
	PIN_6,
	PIN_7,
	PIN_8,
	PIN_9,
	PIN_10,
	PIN_11,
	PIN_12,
	PIN_13,
	PIN_14,
	
}Pin_Number_t;

typedef enum
{
	INPUT_MODE=0,
	OUTPUT_MODE,
	ALTERNATE_F,
	ANALOG_MODE,
	
}Port_mode_t;

typedef enum
{
	LOW_SPEED=0,
	MEDIUM_SPEED,
	HIGHSPEED,
	
}Port_speed_t;

typedef enum
{
	NO_PUPD=0,
	PULL_UP,
	PULL_DOWN,
	
}Port_pdr_t;

typedef struct
{
			Pin_Number_t	Pin;
			Port_mode_t		mode;
			Port_speed_t	speed;
			Port_pdr_t 		pdr;
	
}PORT_Config_t;



typedef struct
{
		uint8_t 				 NumberOfPorts;
		PORT_Config_t 	*PortConfig_Arr;
	
}PORT_Driver_Config_t;




#endif