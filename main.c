/*
* The ONE.c
*
* Created: 11.05.2020 16:18:47
* Author : Batuhan Ayfer
*
* What do I need ?
* - Led steuerung
* - RTC (sek,min,stund,wochentag,tag,monat,jahr)
* -
*
*
*/

#include <avr/io.h>
#define F_CPU	16000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include "I2C_Treiber.h"
#include "RTC.h"
#include "light_ws2812.h"
#include "Display_Config.h"
#include "Taste.h"
uint8_t helligkeit = 255;
uint8_t rot=0,gruen=0,blau=0;
uint8_t settings = 0, zifferwahl=3,alarmmodus=0;
uint8_t change_ziffer1=0, change_ziffer2=0, change_ziffer3=0, change_ziffer4=0,
change_minute,change_stunde;
uint8_t helligkeitstufe = 0, light_show=0,minute_einer,minute_zehner,
stunde_einer,stunde_zehner,datemodus,tag,monat,jahr,tag_einer,tag_zehner,monat_einer,monat_zehner;

ISR(TIMER1_COMPA_vect)
{
	light_ziffer1(stunde_zehner,rot,gruen,blau);
	light_ziffer2(stunde_einer,rot,gruen,blau);
	light_ziffer3(minute_zehner,rot,gruen,blau);
	light_ziffer4(minute_einer,rot,gruen,blau);
}

init_timer()
{
	TCCR1A = 0x00;        //CTC Modus // PORTB Toggle at Compare match
	TCCR1B = 0x0A;        //Teiler 8
	OCR1A  = 100000;	  // 10kHz (T = 0.1ms)
	TIMSK1 = 0x02;        //Compare Match A Interrupt Aktivieren
	sei();
}

void farbe_helligkeit_wechseln(void)
{
	static uint8_t farbecounter = 0;
	if (Taster5_pushed())
	{
		farbecounter++;
		if (farbecounter == 7)
		{
			farbecounter = 0;
		}
	}
	if (Taster4_pushed())
	{
		helligkeitstufe++;
		
	}
	if (helligkeitstufe > 3)
	{
		helligkeitstufe = 0;
	}
	
	switch (helligkeitstufe)
	{
		case 0 : helligkeit = 255;
		break;
		
		case 1 : helligkeit = 130;
		break;
		
		case 2 : helligkeit = 50;
		break;
		
		case 3 : helligkeit = 0;
		break;
		
	}
	switch (farbecounter)
	{
		case 0 : rot = helligkeit;
		gruen = 0 ;
		blau = 0;
		break;
		
		case 1 : rot = 0;
		gruen = helligkeit ;
		blau = 0;
		break;
		
		case 2 : rot = 0;
		gruen = 0 ;
		blau = helligkeit;
		break;
		
		case 3 : rot = helligkeit;
		gruen = helligkeit ;
		blau = 0;
		break;
		
		case 4 : rot = helligkeit;
		gruen = 0 ;
		blau = helligkeit;
		break;
		
		case 5 : rot = 0;
		gruen = helligkeit;
		blau = helligkeit;
		break;
		
		case 6 : rot = helligkeit;
		gruen = helligkeit ;
		blau = helligkeit;
		break;
		
		
	}
}

void settings_menu(void)
{
	if (Taster0_pushed())
	{
		ResetLeds();
		settings = 1 ;
		cli();
	}
	
	
	while (settings)
	{
		ResetLeds();
		if (Taster0_pushed())
		{
			
			settings = 0 ;
			change_minute = (change_ziffer2<<4)|change_ziffer1;
			change_stunde = (change_ziffer4<<4)|change_ziffer3;
			set_Time(0x00,change_minute,change_stunde);
			_delay_ms(200);
			ResetLeds();
		}
		if (Taster3_pushed())
		{
			zifferwahl--;
			if (zifferwahl == 255)
			{
				zifferwahl=3;
			}
		}
		switch (zifferwahl)
		{
			case 0: if (Taster2_pushed())
			{
				change_ziffer1++;
				if (change_ziffer1== 10)
				{
					change_ziffer1 = 0;
				}
			}
			light_ziffer4(change_ziffer1,255,255,255);
			break;
			
			case 1 : 	if (Taster2_pushed())
			{
				change_ziffer2++;
				if (change_ziffer2== 10)
				{
					change_ziffer2 = 0;
				}
			}
			light_ziffer3(change_ziffer2,255,255,255);
			break;
			case 2 : 	if (Taster2_pushed())
			{
				change_ziffer3++;
				if (change_ziffer3== 10)
				{
					change_ziffer3 = 0;
				}
			}
			light_ziffer2(change_ziffer3,255,255,255);
			break;
			
			case 3 : 	if (Taster2_pushed())
			{
				change_ziffer4++;
				if (change_ziffer4== 3)
				{
					change_ziffer4 = 0;
				}
			}
			light_ziffer1(change_ziffer4,255,255,255);
			break;
		}
		light_ziffer1(change_ziffer4,rot,gruen,blau);
		light_ziffer2(change_ziffer3,rot,gruen,blau);
		light_ziffer3(change_ziffer2,rot,gruen,blau);
		light_ziffer4(change_ziffer1,rot,gruen,blau);
		
	}

}

void alarm_settings(void)
{
	
	if (Taster1_pushed())
	{
		ResetLeds();
		alarmmodus = 1 ;
		_delay_ms(200);
		cli();
	}

	while (alarmmodus)
	{
		if (Taster1_pushed())
		{
			ResetLeds();
			alarmmodus = 0 ;
			change_minute = (change_ziffer2<<4)|change_ziffer1;
			change_stunde = (change_ziffer4<<4)|change_ziffer3;
			set_Alarm(0x00,change_minute,change_stunde);
			_delay_ms(200);
		}
		if (Taster3_pushed())
		{
			zifferwahl--;
			if (zifferwahl == 255)
			{
				zifferwahl=3;
			}
		}
		switch (zifferwahl)
		{
			case 0: if (Taster2_pushed())
			{
				change_ziffer1++;
				if (change_ziffer1== 10)
				{
					change_ziffer1 = 0;
				}
			}
			light_ziffer4(change_ziffer1,255,255,255);
			break;
			
			case 1 : 	if (Taster2_pushed())
			{
				change_ziffer2++;
				if (change_ziffer2== 10)
				{
					change_ziffer2 = 0;
				}
			}
			light_ziffer3(change_ziffer2,255,255,255);
			break;
			case 2 : 	if (Taster2_pushed())
			{
				change_ziffer3++;
				if (change_ziffer3== 10)
				{
					change_ziffer3 = 0;
				}
			}
			light_ziffer2(change_ziffer3,255,255,255);
			break;
			
			case 3 : 	if (Taster2_pushed())
			{
				change_ziffer4++;
				if (change_ziffer4== 3)
				{
					change_ziffer4 = 0;
				}
			}
			light_ziffer1(change_ziffer4,255,255,255);
			break;
		}
		light_ziffer1(change_ziffer4,rot,gruen,blau);
		light_ziffer2(change_ziffer3,rot,gruen,blau);
		light_ziffer3(change_ziffer2,rot,gruen,blau);
		light_ziffer4(change_ziffer1,rot,gruen,blau);
		
	}
}


void show_Date(void)
{
	if (Taster1_pushed())
	{
		datemodus = 1 ;
		_delay_ms(20);
		ResetLeds();
	}

	while (datemodus)
	{
		if (Taster1_pushed())
		{
			ResetLeds();
			datemodus = 0;
			_delay_ms(20);
		}
	read_Date(&tag,&monat,&jahr);
	tag_einer = tag&0x0F;
	tag_zehner = (tag&0xF0)>>4;
	monat_einer = monat&0x0F;
	monat_zehner = (monat&0xF0)>>4;	
	stunde_zehner = tag_zehner;
	stunde_einer = tag_einer;
	minute_zehner = monat_zehner;
	minute_einer = monat_einer;
	
	
	}
}

int main(void)
{
	uint8_t sekunde,minute,stunde,bla=0,alarmon,alarmtriggered=0,counter = 0;
	init_Taster();
	twi_init();
	init_timer();
	//set_Time(0x40,0x07,0x12);
	//set_Date(0x07,0x07,0x20);
	clear_Alarm();
	while (1)
	{
		//ResetLeds();
		read_Time(&sekunde,&minute,&stunde);
		stunde_einer = stunde&0x0F;
		stunde_zehner = (stunde&0xF0)>>4;
		minute_einer = minute&0x0F;
		minute_zehner = (minute&0xF0)>>4;
		settings_menu();
		show_Date();
		if (change_ziffer1 != minute_einer||change_ziffer2 != minute_zehner||change_ziffer3 != stunde_einer||change_ziffer4 != stunde_zehner)
		{
			change_ziffer4 = stunde_zehner;
			change_ziffer3 = stunde_einer;
			change_ziffer2 = minute_zehner;
			change_ziffer1 = minute_einer;
			ResetLeds();
		}
		
		//alarm_settings();
		farbe_helligkeit_wechseln();
		// 		read_Alarm(&alarmon);
		// 		alarmon = alarmon&0x01;
		// 		if (alarmon)
		// 		{
		// 			alarmtriggered = 1;
		// 			clear_Alarm();
		// 		}
		// 		if (Taster1_pushed())
		// 		{
		// 			alarmtriggered = 0;
		//
		// 		}
		// 		if (alarmtriggered)
		// 		{
		// 			rot = 255;
		// 			gruen=255;
		// 			blau=255;
		// 		}
		if (Taster3_pushed())
		{
			light_show++;
			if (light_show == 3)
			{
				light_show = 0;
			}
		}
		switch(light_show)
		{
			default: 
			sei();
			break;
			
			case 1 :
			cli();
			_delay_ms(200);
			light_ziffer1(stunde_zehner,rand()%255,rand()%255,rand()%255);
			_delay_ms(200);
			light_ziffer2(stunde_einer,rand()%255,rand()%255,rand()%255);
			_delay_ms(200);
			light_ziffer3(minute_zehner,rand()%255,rand()%255,rand()%255);
			_delay_ms(200);
			light_ziffer4(minute_einer,rand()%255,rand()%255,rand()%255);
			_delay_ms(200);
			
			break;
			case 2:
			cli();
			light_ziffer1(stunde_zehner,0,bla,bla);
			light_ziffer2(stunde_einer,0,bla,bla);
			light_ziffer3(minute_zehner,0,bla,bla);
			light_ziffer4(minute_einer,0,bla,bla);
			bla++;
			if (bla==255)
			{
				bla = 0;
			}
			break;
		}
	}
	
	
}

