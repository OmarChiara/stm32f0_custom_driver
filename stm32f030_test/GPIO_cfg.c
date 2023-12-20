#include "GPIO_types.h"
#include "GPIO_cfg.h"

PORT_Config_t PORT_Config[] =
{
	{
			PIN_0,
			OUTPUT_MODE,
			HIGHSPEED,
			PULL_UP,
	},
	{
			CLK,
			OUTPUT_MODE,
			HIGHSPEED,
			PULL_UP,
	},
	{
			DATA,
			OUTPUT_MODE,
			HIGHSPEED,
			PULL_UP,
	},
	{
			PIN_4,
			OUTPUT_MODE,
			HIGHSPEED,
			PULL_UP,
	},
};

PORT_Driver_Config_t PORT_Driver_Config=
{
		sizeof(PORT_Config) / sizeof(PORT_Config[0]),
		&PORT_Config[0],
	
	
};