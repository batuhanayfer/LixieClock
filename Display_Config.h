/*
 * Display_Config.h
 *
 * Created: 28/02/2019 15:03:01
 *  Author: Administrator
 */ 


#ifndef DISPLAY_CONFIG_H_
#define DISPLAY_CONFIG_H_
#include "light_ws2812.h"

#define Anzahl_LEDs	80
#define Einer	0
#define Zehner  1


extern struct cRGB led[Anzahl_LEDs];

void SetPixel(uint8_t LEDnummer, uint8_t Rot, uint8_t Gruen, uint8_t Blau);
void light_ziffer1(uint8_t number,uint8_t Red,uint8_t Green,uint8_t Blue);// 1,0,2,9,3,8,4,7,5,6
void light_ziffer2(uint8_t number,uint8_t Red,uint8_t Green,uint8_t Blue);// 1,0,2,9,3,8,4,7,5,6
void light_ziffer3(uint8_t number,uint8_t Red,uint8_t Green,uint8_t Blue);// 1,0,2,9,3,8,4,7,5,6
void light_ziffer4(uint8_t number,uint8_t Red,uint8_t Green,uint8_t Blue);// 1,0,2,9,3,8,4,7,5,6

void ShowDisplay(void);
void ResetLeds(void);

#endif /* DISPLAY_CONFIG_H_ */