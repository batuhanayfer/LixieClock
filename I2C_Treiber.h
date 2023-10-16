/*
 * TWI.h
 *
 * Created: 10.04.2019 08:23:39
 *  Author: scol
 */ 


#ifndef I2C_Treiber_H_
#define I2C_Treiber_H_

	#include <stdint.h>

	void twi_init(void);
	void twi_start(void);
	void twi_repStart(void);
	void twi_stop(void);
	void twi_transmittAdr(uint8_t Adr);
	void twi_receiveAdr(uint8_t Adr);
	void twi_sendDataNACK(uint8_t TWData);
	void twi_sendDataACK(uint8_t TWData);
	uint8_t twi_readDataNACK(void);
	uint8_t twi_readDataACK(void);
	void twi_send16Bit(uint8_t Adr, uint16_t Data);
	uint16_t twi_read16Bit(uint8_t Adr, uint8_t Register);
	

#endif /* TWI_H_ */