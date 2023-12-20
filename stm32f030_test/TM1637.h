/*
 * TM1637.h
 *
 *  Created and Modified on: 19-12-2023
 *     Author: Omar Chiara
 */

#ifndef TM1637_H_
#define TM1637_H_
#include "stm32f0xx.h"
#include "GPIO.h"

#define CLK_Pin	GPIO_PIN_1
#define DATA_Pin	GPIO_PIN_2

#define BRIGHTNESS_MIN 1
#define BRIGHTNESS_MED 5
#define BRIGHTNESS_MAX 8

#define DISPLAY_0 0xc3
#define DISPLAY_1 0xc2
#define DISPLAY_2 0xc1
#define DISPLAY_3 0xc0


/***************************************Static functions***********************************/

static void TM1637_ClkHigh(void);
static void TM1637_ClkLow(void);
static void TM1637_DataHigh(void);
static void TM1637_DATALow(void);
static void TM1637_SetBrightness(unsigned char brightness);
static void TM1637_Start(void);
static void TM1637_Stop(void);
static void TM1637_ReadResult(void);
static void TM1637_WriteByte(unsigned char b);
static void TM1637_DelayUsec(unsigned char i);
static uint8_t char2segments(char c);


/**************************************Extern functions***********************************/

extern void TM1637_Init(uint8_t brightness);
extern void TM1637_Turn_Off(void);
extern void TM1637_Demo(void);
extern void TM1637_DisplayDecimal(int v, int displaySeparator);
extern void display_on_x_pos(uint8_t disp_data, unsigned char x);
extern void Set_All_Zero(void);

extern void TM1637_DisplayWord(uint8_t word[]);

#endif /* TM1637_H_ */
