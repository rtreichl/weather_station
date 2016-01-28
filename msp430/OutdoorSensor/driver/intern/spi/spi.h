///----------------------------------------------------------------------------------------
///
/// \file spi.h
///
/// \brief 
///
/// \date 31.12.2015
///
/// \author Richard Treichl
///
/// \remark
///
/// \todo
///
/// \version	1.0
///
///----------------------------------------------------------------------------------------

#ifndef SPI_H_
#define SPI_H_

#include <stdint.h>

enum SPIMode {
	SPIMODE0 = 0, ///> ClkPol = 0, ClkPha = 0;
	SPIMODE1 = 1, ///> ClkPol = 0, ClkPha = 1;
	SPIMODE2 = 2, ///> ClkPol = 1, ClkPha = 0;
	SPIMODE3 = 3, ///> ClkPol = 1, ClkPha = 1;
};

int16_t SPI_init(enum SPIMode mode);
int16_t SPI_transfer(uint8_t Tx_n_bytes, void *TxBuffer, uint8_t Rx_n_bytes, void *RxBuffer);
int16_t SPI_transmit(uint8_t n_bytes, void *TxBuffer);
int16_t SPI_receive(uint8_t n_bytes, void *RxBuffer);

#endif /* SPI_H_ */
