/*
 * RTC.h
 *
 * Created: 12.05.2020 10:01:28
 *  Author: Administrator
 */ 


#ifndef RTC_H_
#define RTC_H_

#include <avr/io.h>
#include <util/twi.h>

#include "I2C_Treiber.h"

#define Adresse 0x68

void RTC_Init();
void set_Time(uint8_t ,uint8_t ,uint8_t );
void set_Date(uint8_t ,uint8_t ,uint8_t );
void read_Time(uint8_t *,uint8_t *,uint8_t *);
void read_Date(uint8_t *,uint8_t *,uint8_t *);
void set_Alarm(uint8_t sek,uint8_t min,uint8_t stund);
void read_Alarm(uint8_t *alarm);
void clear_Alarm();





#endif /* RTC_H_ */