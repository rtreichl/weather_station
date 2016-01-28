#pragma once

#include <stdint.h>
#include <string>

//Mode for CC110L SPI_3WIRE + SPI_MODE_0

class SPI
{
public:
	SPI(uint8_t device, uint32_t spiSpeed, uint8_t spiMode, uint8_t spiBitsPerWord);
	~SPI();
	int SPIRead(void *RxBuffer, uint8_t n_Bytes);
	int SPIWrite(void *TxBuffer, uint8_t n_Bytes);
	int SPIXfer(void *TxBuffer, void *RxBuffer, uint8_t n_Bytes);
private:
	static std::string spiDev[2];
	static uint8_t device_used[2];
	int device;
	uint8_t bitsPerWord;
	uint8_t mode;
	uint32_t speed;
};
