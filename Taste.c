/*
 * Taste.c
 *
 * Created: 11.11.2019 08:12:59
 *  Author: Batuhan Ayfer
 */ 


#include <avr/io.h>
#define F_CPU	16000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include <math.h>
#include <stdlib.h>
#include <avr/eeprom.h>
#include "Taste.h"
#include "Display_Config.h"

uint8_t taster0_check;
uint8_t taster1_check;
uint8_t taster2_check;
uint8_t taster3_check;
uint8_t taster4_check;
uint8_t taster5_check;

/******************************************************************************\
* <<get_Taster>>
*
* Taster einlesen
*
* Parameter:
* <<PARAMETER1>> = <<BEDEUTUNG>>
* <<PARAMETER2>> = <<BEDEUTUNG>>
*
* Rückgabewert: <<gibt 0 bis 7 oder 99 wenn nichts gedrückt ist>>
*
\******************************************************************************/

uint8_t Taster0_pushed(void)
{
		if (PINA&0x01)
		{
			taster0_check = 1;
		}	
		if (!(PINA&0x01)&&(taster0_check))
		{
			taster0_check = 0;
			ResetLeds();
			return 1;
			
		}		
	return 0;
}
uint8_t Taster1_pushed(void)
{
	if (PINA&0x02)
	{
		taster1_check = 1;
	}
	if (!(PINA&0x02)&&(taster1_check))
	{
		taster1_check = 0;
		ResetLeds();
		return 1;
		
	}	
	return 0;
}
uint8_t Taster2_pushed(void)
{
	
	if (PINA&0x04)
	{
		taster2_check = 1;
	}
	if (!(PINA&0x04)&&(taster2_check))
	{
		taster2_check = 0;
		ResetLeds();
		return 1;
		
	}	
	return 0;
}
uint8_t Taster3_pushed(void)
{
	if (PINA&0x08)
	{
		taster3_check = 1;
	}
	if (!(PINA&0x08)&&(taster3_check))
	{
		taster3_check = 0;
		ResetLeds();
		return 1;
		
	}	
	return 0;
}
uint8_t Taster4_pushed(void)
{
	if (PINA&0x10)
	{
		taster4_check = 1;
	}
	if (!(PINA&0x10)&&(taster4_check))
	{
		taster4_check = 0;
		ResetLeds();
		return 1;
		
	}
	return 0;
}
uint8_t Taster5_pushed(void)
{
	 
	if (PINA&0x20)
	{
		taster5_check = 1;
	}
	if (!(PINA&0x20)&&(taster5_check))
	{
		taster5_check = 0;
		ResetLeds();
		return 1;
	}
	return 0;
}



void init_Taster(void)
{
	DDRA = 0x00;
	PORTA = 0x00;
}