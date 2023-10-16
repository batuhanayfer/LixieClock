/*
 * I2C_Treiber.c
 *
 * Created: 10.04.2019 08:23:57
 *  Author: scol
 */ 


#include <avr/io.h>
#include <util/twi.h>

#include "I2C_Treiber.h"

#define F_CPU 16000000UL  // CPU CLK frequency
#define F_SCL 400000UL    // TWI BUS frequency

// If the TWPS value is adjusted, the TWI_Prescaler must be set accordingly.
#define TWPS 0            // TWPS:      0 | 1 |  2 |  3 | 
#define TWI_PRESCALER  1  // Prescaler: 1 | 4 | 16 | 64 |

void twi_test(uint8_t Testpattern)
{
	if ((TWSR & 0xF8) != Testpattern)
	{
		PORTA |= 0x80;	
	}
}


void twi_init(void)
{
	TWSR = (0<<TWPS0)|(0<<TWPS1);
	TWBR = 12;
}

void twi_start(void)
{
	TWCR = (1<<TWINT)|(1<<TWSTA)| (1<<TWEN);	// send START condition
	while(!(TWCR & (1<<TWINT)));				// wait until send start completed
	twi_test(TW_START);							// test the status Flag
}

void twi_repStart(void)
{
	TWCR = (1<<TWINT)|(1<<TWSTA)| (1<<TWEN);	// send START condition
	while(!(TWCR & (1<<TWINT)));				// wait until send restart completed
	twi_test(TW_REP_START);						// test the status Flag
}

void twi_stop(void)
{
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);     // Transmit STOP condition
}


void twi_transmittAdr(uint8_t Adr)
{
	TWDR = (Adr<<1) | TW_WRITE;				    // load slave Adress and write to TWDR Register RW-Bit=0 (write)
	TWCR = (1<<TWINT) | (1<<TWEN);				// send Adress to Slave
	while(!(TWCR & (1<<TWINT)));				// wait until the address has been sent
	twi_test(TW_MT_SLA_ACK);					// test the status Flag
}


void twi_receiveAdr(uint8_t Adr)
{
	TWDR = (Adr<<1) | TW_READ;				    // load slave Adress and write to TWDR Register RW-Bit=1 (read)
	TWCR = (1<<TWINT) | (1<<TWEN);				// send Adress to Slave	
	while(!(TWCR & (1<<TWINT)));				// wait until the address has been sent
	twi_test(TW_MR_SLA_ACK);					// test the status Flag
}


void twi_sendDataNACK(uint8_t TWData)
{
	TWDR = TWData;								// load DATA into TWDR Register.
	TWCR = (1<<TWINT) | (1<<TWEN);				// send Data to Slave
	while(!(TWCR & (1<<TWINT)));				// wait until writing completed
	twi_test(TW_MT_DATA_NACK);					// test the status Flag
}

void twi_sendDataACK(uint8_t TWData)
{
	TWDR = TWData;								// load DATA into TWDR Register.
	TWCR = (1<<TWINT) | (1<<TWEN);				// send Data to Slave
	while(!(TWCR & (1<<TWINT)));				// wait until writing completed
	twi_test(TW_MT_DATA_ACK);					// test the status Flag
}

uint8_t twi_readDataNACK(void)
{
	TWCR = (1<<TWINT) | (1<<TWEN);				// read Data from Slave Master send NACK
	while(!(TWCR & (1<<TWINT)));				// wait until reading completed
	twi_test(TW_MR_DATA_NACK);					// test the status Flag
	return(TWDR);
}

uint8_t twi_readDataACK(void)
{
	TWCR = (1<<TWINT) | (1<<TWEN) |(1<<TWEA); // read Data from Slave Master send ACK
	while(!(TWCR & (1<<TWINT)));			  // wait until reading completed
	twi_test(TW_MR_DATA_ACK);				  // test the status Flag
	return(TWDR);
}

void twi_send16Bit(uint8_t Adr, uint16_t Data)
{	
	twi_start();							// start i2c bus traffic
	twi_transmittAdr(Adr);					// initiate write cycle
	twi_sendDataACK(Data>>8);			    // send data
	twi_sendDataACK(Data);				    // send data
	twi_stop();								// stop i2c bus traffic
}


uint16_t twi_read16Bit(uint8_t Adr, uint8_t Register)
{	
	uint16_t data;
	twi_start();							// start i2c bus traffic
	twi_transmittAdr(Adr);					// initiate write cycle
	twi_sendDataACK(Register);				// send readpointer
	twi_repStart();							// restart
	twi_receiveAdr(Adr);					// initiate reading cycle
	data = twi_readDataACK() >> 8;			// read MSByte
	data += twi_readDataNACK();				// read LSByte
	twi_stop();								// stop i2c bus traffic
	return(data);
}