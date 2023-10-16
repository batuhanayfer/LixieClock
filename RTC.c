/*
 * CFile1.c
 *
 * Created: 11.05.2020 16:21:56
 *  Author: Batuhan Ayfer
 */ 

#include <avr/io.h>
#include <util/twi.h>

#include "I2C_Treiber.h"
#include "RTC.h"



void RTC_Init()
{
	twi_init();                        // Initialize the I2c module.
	twi_start();                    // Start I2C communication
	twi_transmittAdr(Adresse);        // Connect to DS1307 by sending its ID on I2c Bus
	twi_sendDataACK(0x0E);			// Select the Ds1307 ControlRegister to configure Ds1307
	twi_sendDataACK(0x05);                        // Write 0x00 to Control register to disable SQW-Out
	twi_stop();                             // Stop I2C communication after initializing DS1307
}


void set_Time(uint8_t sekunde,uint8_t minute,uint8_t stunde)
{
	twi_start();
	twi_transmittAdr(Adresse);
	twi_sendDataACK(0x00);
	twi_sendDataACK(sekunde);
	twi_sendDataACK(minute);
	twi_sendDataACK(stunde);
	twi_stop();
}

void set_Date(uint8_t tag,uint8_t monat,uint8_t jahr)
{
	twi_start();
	twi_transmittAdr(Adresse);
	twi_sendDataACK(0x04);
	twi_sendDataACK(tag);
	twi_sendDataACK(monat);
	twi_sendDataACK(jahr);
	twi_stop();
	
}

void read_Time(uint8_t *sek,uint8_t *min,uint8_t *stund)
{
	twi_start();
	twi_transmittAdr(Adresse);
	twi_sendDataACK(0x00);
	twi_repStart();
	twi_receiveAdr(Adresse);
	*sek = twi_readDataACK();
	*min = twi_readDataACK();
	*stund = twi_readDataNACK();
	twi_stop();
}

void read_Date(uint8_t *day,uint8_t *month,uint8_t *year)
{
	twi_start();
	twi_transmittAdr(Adresse);
	twi_sendDataACK(0x04);
	twi_repStart();
	twi_receiveAdr(Adresse);
	*day = twi_readDataACK();
	*month = twi_readDataACK();
	*year = twi_readDataNACK();
	twi_stop();
}

void set_Alarm(uint8_t sek,uint8_t min,uint8_t stund)
{
	twi_start();
	twi_transmittAdr(Adresse);
	twi_sendDataACK(0x07);
	twi_sendDataACK(sek);
	twi_sendDataACK(min);
	twi_sendDataACK(stund);
	twi_sendDataACK(0x80);
	twi_stop();
}

void read_Alarm(uint8_t *alarm) //0f
{
	twi_start();
	twi_transmittAdr(Adresse);
	twi_sendDataACK(0x0F);
	twi_repStart();
	twi_receiveAdr(Adresse);
	*alarm = twi_readDataNACK();
	twi_stop();
}

void clear_Alarm()
{
	twi_start();
	twi_transmittAdr(Adresse);
	twi_sendDataACK(0x0F);
	twi_sendDataACK(0x88);
	twi_stop();
}