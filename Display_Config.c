/*
 * Display_Config.c
 *
 * Created: 28/02/2019 15:37:13
 *  Author: Administrator
 */ 
#include <avr/io.h>
#define F_CPU	16000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include <math.h>
#include <stdlib.h>
#include <avr/eeprom.h>
#include "Display_Config.h"
#include "light_ws2812.h"
struct cRGB led[Anzahl_LEDs];

/******************************************************************************\
* <<Set_Pixel>>
*
* Schaltet einzelne LED's ein oder aus
*
* Parameter:
* <<x>> = <<x Koordinate>>
* <<y>> = <<y Koordinate>>
* <<rot>> = <<Stärke der Farbe ROT >>
* <<Gruen>> = <<Stärke der Farbe GRUEN >>
* <<Blau>> = <<Stärke der Farbe BLAU >>
*
*
\******************************************************************************/
void SetPixel(uint8_t LEDnummer, uint8_t Rot, uint8_t Gruen, uint8_t Blau)
{
	led[LEDnummer].r = Rot;
	led[LEDnummer].g = Gruen;
	led[LEDnummer].b = Blau;
    
}

void light_ziffer1(uint8_t number,uint8_t Red,uint8_t Green,uint8_t Blue)// 1,0,2,9,3,8,4,7,5,6
{ 
	if (number == 6)
	{
		SetPixel(4,Red,Green,Blue);
		SetPixel(14,Red,Green,Blue);
	}
	if (number == 5)
	{
		SetPixel(3,Red,Green,Blue);
		SetPixel(13,Red,Green,Blue);
	}
	if (number == 7)
	{
		SetPixel(2,Red,Green,Blue);
		SetPixel(12,Red,Green,Blue);
	}
	if (number == 4)
	{
		SetPixel(1,Red,Green,Blue);
		SetPixel(11,Red,Green,Blue);
	}
	if (number == 8)
	{
		SetPixel(0,Red,Green,Blue);
		SetPixel(10,Red,Green,Blue);
	}
	if (number == 3)
	{
		SetPixel(9,Red,Green,Blue);
		SetPixel(19,Red,Green,Blue);
	}
	if (number == 9)
	{
		SetPixel(8,Red,Green,Blue);
		SetPixel(18,Red,Green,Blue);
	}
	if (number == 2)
	{
		SetPixel(7,Red,Green,Blue);
		SetPixel(17,Red,Green,Blue);
	}
	if (number == 0)
	{
		SetPixel(6,Red,Green,Blue);
		SetPixel(16,Red,Green,Blue);
	}
	if (number == 1)
	{
		SetPixel(5,Red,Green,Blue);
		SetPixel(15,Red,Green,Blue);
	}
	ShowDisplay();
	
}

void light_ziffer2(uint8_t number,uint8_t Red,uint8_t Green,uint8_t Blue)// 1,0,2,9,3,8,4,7,5,6
{
	if (number == 6)
	{
		SetPixel(4+20,Red,Green,Blue);
		SetPixel(14+20,Red,Green,Blue);
	}
	if (number == 5)
	{
		SetPixel(3+20,Red,Green,Blue);
		SetPixel(13+20,Red,Green,Blue);
	}
	if (number == 7)
	{
		SetPixel(2+20,Red,Green,Blue);
		SetPixel(12+20,Red,Green,Blue);
	}
	if (number == 4)
	{
		SetPixel(1+20,Red,Green,Blue);
		SetPixel(11+20,Red,Green,Blue);
	}
	if (number == 8)
	{
		SetPixel(0+20,Red,Green,Blue);
		SetPixel(10+20,Red,Green,Blue);
	}
	if (number == 3)
	{
		SetPixel(9+20,Red,Green,Blue);
		SetPixel(19+20,Red,Green,Blue);
	}
	if (number == 9)
	{
		SetPixel(8+20,Red,Green,Blue);
		SetPixel(18+20,Red,Green,Blue);
	}
	if (number == 2)
	{
		SetPixel(7+20,Red,Green,Blue);
		SetPixel(17+20,Red,Green,Blue);
	}
	if (number == 0)
	{
		SetPixel(6+20,Red,Green,Blue);
		SetPixel(16+20,Red,Green,Blue);
	}
	if (number == 1)
	{
		SetPixel(5+20,Red,Green,Blue);
		SetPixel(15+20,Red,Green,Blue);
	}
	ShowDisplay();
	
}

void light_ziffer3(uint8_t number,uint8_t Red,uint8_t Green,uint8_t Blue)// 1,0,2,9,3,8,4,7,5,6
{
	if (number == 6)
	{
		SetPixel(4+40,Red,Green,Blue);
		SetPixel(14+40,Red,Green,Blue);
	}
	if (number == 5)
	{
		SetPixel(3+40,Red,Green,Blue);
		SetPixel(13+40,Red,Green,Blue);
	}
	if (number == 7)
	{
		SetPixel(2+40,Red,Green,Blue);
		SetPixel(12+40,Red,Green,Blue);
	}
	if (number == 4)
	{
		SetPixel(1+40,Red,Green,Blue);
		SetPixel(11+40,Red,Green,Blue);
	}
	if (number == 8)
	{
		SetPixel(0+40,Red,Green,Blue);
		SetPixel(10+40,Red,Green,Blue);
	}
	if (number == 3)
	{
		SetPixel(9+40,Red,Green,Blue);
		SetPixel(19+40,Red,Green,Blue);
	}
	if (number == 9)
	{
		SetPixel(8+40,Red,Green,Blue);
		SetPixel(18+40,Red,Green,Blue);
	}
	if (number == 2)
	{
		SetPixel(7+40,Red,Green,Blue);
		SetPixel(17+40,Red,Green,Blue);
	}
	if (number == 0)
	{
		SetPixel(6+40,Red,Green,Blue);
		SetPixel(16+40,Red,Green,Blue);
	}
	if (number == 1)
	{
		SetPixel(5+40,Red,Green,Blue);
		SetPixel(15+40,Red,Green,Blue);
	}
	ShowDisplay();
	
}

void light_ziffer4(uint8_t number,uint8_t Red,uint8_t Green,uint8_t Blue)// 1,0,2,9,3,8,4,7,5,6
{
	if (number == 6)
	{
		SetPixel(4+60,Red,Green,Blue);
		SetPixel(14+60,Red,Green,Blue);
	}
	if (number == 5)
	{
		SetPixel(3+60,Red,Green,Blue);
		SetPixel(13+60,Red,Green,Blue);
	}
	if (number == 7)
	{
		SetPixel(2+60,Red,Green,Blue);
		SetPixel(12+60,Red,Green,Blue);
	}
	if (number == 4)
	{
		SetPixel(1+60,Red,Green,Blue);
		SetPixel(11+60,Red,Green,Blue);
	}
	if (number == 8)
	{
		SetPixel(0+60,Red,Green,Blue);
		SetPixel(10+60,Red,Green,Blue);
	}
	if (number == 3)
	{
		SetPixel(9+60,Red,Green,Blue);
		SetPixel(19+60,Red,Green,Blue);
	}
	if (number == 9)
	{
		SetPixel(8+60,Red,Green,Blue);
		SetPixel(18+60,Red,Green,Blue);
	}
	if (number == 2)
	{
		SetPixel(7+60,Red,Green,Blue);
		SetPixel(17+60,Red,Green,Blue);
	}
	if (number == 0)
	{
		SetPixel(6+60,Red,Green,Blue);
		SetPixel(16+60,Red,Green,Blue);
	}
	if (number == 1)
	{
		SetPixel(5+60,Red,Green,Blue);
		SetPixel(15+60,Red,Green,Blue);
	}
	ShowDisplay();
	
}




/******************************************************************************\
* <<ShowDisplay>>
*
* Zeigt die LED's auf dem Display an
*
*
\******************************************************************************/
void ShowDisplay(void)
{
	ws2812_setleds(led,Anzahl_LEDs);
}

/******************************************************************************\
* <<ResetLeds>>
*
* LED's löschen
*
\******************************************************************************/
void ResetLeds(void)
{
	for (uint8_t i = 0; i < 80; i++)
	{
        
		SetPixel(i,0,0,0);
	}
}
