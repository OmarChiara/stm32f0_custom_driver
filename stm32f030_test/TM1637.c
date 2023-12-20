/*
 * TM1637_.c
 *
 *  Created and Modified on: 19-12-2023
 *      Author: Omar Chiara
 */

#include "TM1637.h"
#include "GPIO.h"




const char segmentMap[] = {
    0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, // 0-7
    0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71, // 8-9, A-F
    0x00
};


/******************************************************Global functions**********************************************************/

void TM1637_Init(uint8_t brightness)
{

		TM1637_Start();
		TM1637_SetBrightness(brightness);
		TM1637_ReadResult();
		TM1637_Stop();
	/*************Sets to 0 all segments*****/
		Set_All_Zero();
	/*********Turn off the segments**********/
		TM1637_Turn_Off();
}


void TM1637_Turn_Off(void)
{
			
    TM1637_Start();               // Start signal sent to TM1637 from MCU
    TM1637_WriteByte(0x44); // Command1: Set data
		TM1637_ReadResult();
		TM1637_Stop();
	
    TM1637_Start();
		TM1637_WriteByte(DISPLAY_3); // Command2: Set data (fixed address)
		TM1637_ReadResult();
	
	
		TM1637_WriteByte(0X00);
    TM1637_ReadResult();
	
    TM1637_Stop();
	
	///////////////////////
		TM1637_Start();               // Start signal sent to TM1637 from MCU
    TM1637_WriteByte(0x44); // Command1: Set data
		TM1637_ReadResult();
		TM1637_Stop();
	
    TM1637_Start();
		TM1637_WriteByte(DISPLAY_2); // Command2: Set data (fixed address)
		TM1637_ReadResult();
	
	
		TM1637_WriteByte(0X00);
    TM1637_ReadResult();
	
    TM1637_Stop();
	///////////////////////
		TM1637_Start();               // Start signal sent to TM1637 from MCU
    TM1637_WriteByte(0x44); // Command1: Set data
		TM1637_ReadResult();
		TM1637_Stop();
	
    TM1637_Start();
		TM1637_WriteByte(DISPLAY_1); // Command2: Set data (fixed address)
		TM1637_ReadResult();
	
	
		TM1637_WriteByte(0X00);
    TM1637_ReadResult();
	
    TM1637_Stop();
		
		///////////////////////
		TM1637_Start();               // Start signal sent to TM1637 from MCU
    TM1637_WriteByte(0x44); // Command1: Set data
		TM1637_ReadResult();
		TM1637_Stop();
	
    TM1637_Start();
		TM1637_WriteByte(DISPLAY_0); // Command2: Set data (fixed address)
		TM1637_ReadResult();
	
	
		TM1637_WriteByte(0X00);
    TM1637_ReadResult();
	
    TM1637_Stop();
	
	
}

void TM1637_DisplayDecimal(int v, int displaySeparator)
{
	
    unsigned char digitArr[4];
    for (int i = 0; i < 4; ++i) {
        digitArr[i] = segmentMap[v % 10];
        if (i == 2 && displaySeparator) {
            digitArr[i] |= 1 << 7;
        }
        v /= 10;
    }

    TM1637_Start();
    TM1637_WriteByte(0x40); /*Write data to display*/
    TM1637_ReadResult();
    TM1637_Stop();

    TM1637_Start();
    TM1637_WriteByte(0xc0);   /*Selects the address */
    TM1637_ReadResult();

    for (int i = 0; i < 4; ++i) {
        TM1637_WriteByte(digitArr[3 - i]);
        TM1637_ReadResult();
    }

    TM1637_Stop();
}



void display_on_x_pos(unsigned char disp_data, unsigned char x) {

		
    TM1637_Start();               // Start signal sent to TM1637 from MCU
    TM1637_WriteByte(0x44); // Command1: Set data
		TM1637_ReadResult();
		TM1637_Stop();
	
    TM1637_Start();
		TM1637_WriteByte(x); // Command2: Set data (fixed address)
		TM1637_ReadResult();
	
	
    TM1637_WriteByte(disp_data);        // Transfer display data 8 bits
		TM1637_ReadResult();
		
    TM1637_Stop();
	

}

void Set_All_Zero(void)
{
	
		/****************Sets 4th display to 0*******************/
		TM1637_Start();               // Start signal sent to TM1637 from MCU
    TM1637_WriteByte(0x40); // Command1: Set data
		TM1637_ReadResult();
		TM1637_Stop();
	
    TM1637_Start();
		TM1637_WriteByte(0xc0); // Command2: Set data (fixed address)
		TM1637_ReadResult();
	
	
    TM1637_WriteByte(0x3f);        // Transfer display data 8 bits
		TM1637_ReadResult();
	
	
		/****************Sets 3rd display to 0*******************/
	
	
    TM1637_WriteByte(0x3f);        // Transfer display data 8 bits
		TM1637_ReadResult();
	
		
		/****************Sets 2nd display to 0*******************/

	
	
    TM1637_WriteByte(0x3f);        // Transfer display data 8 bits
		TM1637_ReadResult();
	
		
		
		
		/****************Sets 1st display to 0*******************/

	
    TM1637_WriteByte(0x3f);        // Transfer display data 8 bits
		TM1637_ReadResult();
	
    TM1637_Stop();
	
}

void TM1637_DisplayWord(uint8_t word[])
{
	
	
	
	unsigned char digitArr[sizeof(&word)];
	for(uint8_t i=0; i<sizeof(digitArr); i++)
    {
        digitArr[i] = char2segments(word[i]);
        
        
    }

    TM1637_Start();
    TM1637_WriteByte(0x40); /*Write data to display*/
    TM1637_ReadResult();
    TM1637_Stop();

    TM1637_Start();
    TM1637_WriteByte(0xc0);   /*Selects the address */
    TM1637_ReadResult();

    for (uint8_t i = 0; i < sizeof(digitArr); ++i) {
        TM1637_WriteByte(digitArr[i]);
        TM1637_ReadResult();
    }

    TM1637_Stop();
		
		//TODO implement shift for longer words
		
	
	
}

/***************************************Static functions*************************************************/



//
//      A
//     ---
//  F |   | B
//     -G-
//  E |   | C
//     ---
//      D

uint8_t char2segments(char c) {
        switch (c) {
            case '_' : return 0x08;
            case '^' : return 0x01; // ¯
            case '-' : return 0x40;
            case '*' : return 0x63; // °
            case ' ' : return 0x00; // space
            case 'A' : return 0x77; // upper case A
            case 'a' : return 0x5f; // lower case a
            case 'B' :              // lower case b
            case 'b' : return 0x7c; // lower case b
            case 'C' : return 0x39; // upper case C
            case 'c' : return 0x58; // lower case c
            case 'D' :              // lower case d
            case 'd' : return 0x5e; // lower case d
            case 'E' :              // upper case E
            case 'e' : return 0x79; // upper case E
            case 'F' :              // upper case F
            case 'f' : return 0x71; // upper case F
            case 'G' :              // upper case G
            case 'g' : return 0x7D; // upper case G
            case 'H' : return 0x76; // upper case H
            case 'h' : return 0x74; // lower case h
            case 'I' : return 0x06; // 1
            case 'i' : return 0x04; // lower case i
            case 'J' : return 0x1e; // upper case J
            case 'j' : return 0x16; // lower case j
            case 'K' :              // upper case K
            case 'k' : return 0x75; // upper case K
            case 'L' :              // upper case L
            case 'l' : return 0x38; // upper case L
            case 'M' :              // twice tall n
            case 'm' : return 0x37; // twice tall ∩
            case 'N' :              // lower case n
            case 'n' : return 0x54; // lower case n
            case 'O' :              // lower case o
            case 'o' : return 0x5c; // lower case o
            case 'P' :              // upper case P
            case 'p' : return 0x73; // upper case P
            case 'Q' : return 0x7b; // upper case Q
            case 'q' : return 0x67; // lower case q
            case 'R' :              // lower case r
            case 'r' : return 0x50; // lower case r
            case 'S' :              // 5
            case 's' : return 0x6d; // 5
            case 'T' :              // lower case t
            case 't' : return 0x78; // lower case t
            case 'U' :              // lower case u
            case 'u' : return 0x1c; // lower case u
            case 'V' :              // twice tall u
            case 'v' : return 0x3e; // twice tall u
            case 'W' : return 0x7e; // upside down A
            case 'w' : return 0x2a; // separated w
            case 'X' :              // upper case H
            case 'x' : return 0x76; // upper case H
            case 'Y' :              // lower case y
            case 'y' : return 0x6e; // lower case y
            case 'Z' :              // separated Z
            case 'z' : return 0x1b; // separated Z
        }
        return 0;
}


static void TM1637_ClkHigh(void)
{
    GPIO_WritePin(GPIOA, CLK_Pin, GPIO_PIN_SET);
}

static void TM1637_ClkLow(void)
{
    GPIO_WritePin(GPIOA, CLK_Pin, GPIO_PIN_RESET);
}

static void TM1637_DataHigh(void)
{
    GPIO_WritePin(GPIOA, DATA_Pin, GPIO_PIN_SET);
}

static void TM1637_DataLow(void)
{
    GPIO_WritePin(GPIOA, DATA_Pin, GPIO_PIN_RESET);
}

void TM1637_Demo(void)
{
	uint8_t i = 0;


	while(1){
		TM1637_DisplayDecimal(i++, 0);
	}
}


// Valid brightness values: 0 - 8.
// 0 = display off.
static void TM1637_SetBrightness(unsigned char brightness)
{
    // Brightness command:
    // 1000 0XXX = display off
    // 1000 1BBB = display on, brightness 0-8
    // X = don't care
    // B = brightness
    TM1637_Start();
    TM1637_WriteByte(0X87 + brightness);
    TM1637_ReadResult();
    TM1637_Stop();
}

static void TM1637_Start(void)
{
    TM1637_ClkHigh();
    TM1637_DataHigh();
    TM1637_DelayUsec(1);
    TM1637_DataLow();
}



static void TM1637_Stop(void)
{
    TM1637_ClkLow();
    TM1637_DelayUsec(1);
    TM1637_DataLow();
    TM1637_DelayUsec(1);
    TM1637_ClkHigh();
    TM1637_DelayUsec(1);
		TM1637_DataHigh();
}

static void TM1637_ReadResult(void)
{
	

    TM1637_DelayUsec(1);
		TM1637_ClkHigh();
    TM1637_DelayUsec(1);
		TM1637_DataLow();
    TM1637_ClkLow();		

}

static void TM1637_WriteByte(unsigned char b)
{
	for (int i = 0; i < 8; ++i) {
		TM1637_ClkLow();
		if (b & 0x01) {
			TM1637_DataHigh();
		}
		else {
			TM1637_DataLow();
		}
		TM1637_DelayUsec(1);
		b >>= 1;
		TM1637_ClkHigh();
		TM1637_DelayUsec(1);
	}
		TM1637_ClkLow();
}

static void TM1637_DelayUsec(unsigned char i)
{
    for (; i>0; i--) {
        for (int j = 0; j < 500; ++j) {
					__NOP();
        }
    }
}



