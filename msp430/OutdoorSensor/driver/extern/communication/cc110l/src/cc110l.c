#include <driver.h>
#include <string.h>


#define CC110L_SPI_BUS 0
#define CC110L_SPI_BAUD 5000000
#define CC110L_MISO_BIT BIT1
#define CC110L_MISO_PIN P2IN
#define CC110L_SPI_CS 15
#define CC110L_GPO0 18
#define CC110L_GPO2 23

int16_t CC110L_RegisterWrite(uint8_t reg, uint8_t nBytes, void *TxBuffer);
int16_t CC110L_RegisterRead(uint8_t reg, uint8_t nBytes, void *RxBuffer);
void CC110L_SPI_Start();
void CC110L_SPI_End();

int16_t CC110L_SendCommand(uint8_t command)
{
	char status = 0;
	CC110L_SPI_Start();
	SPI_transfer(1, &command, 1, &status);
	CC110L_SPI_End();
 	return status;
}

int16_t CC110L_CheckConfig(CC110L_CONFIG *Config)
{
	char addr;
	CC110L_CONFIG config_tmp;
	CC110L_RegisterRead(CC110L_IOCFG2, CC110L_TEST0 + 1, &config_tmp);
	if(memcmp(&config_tmp, Config, CC110L_TEST0 + 1) == 0) {
		return 0;
	}
	else {
#if CC110L_DEBUG
		union {
			struct {
				uint8_t ok;
				uint8_t failed;
			};
			int16_t word;
		} check;
		char *config = (char *)&config_tmp;
		char *config2 = (char *)Config;
		for (addr = CC110L_IOCFG2; addr <= CC110L_TEST0; addr++) {
			if (*config2 == *config)
				check.ok++;
			else
				check.failed++;
			config++;
			config2++;
		}
#endif
		return check.word;
	}
}

int16_t CC110L_WriteConfig(CC110L_CONFIG *Config)
{
	CC110L_RegisterWrite(CC110L_IOCFG2, CC110L_TEST0 + 1, Config);
	CC110L_CheckConfig(Config);
	return 0;
}

int16_t CC110L_WritePATable(uint8_t nBytes, uint16_t PAValue)
{
	return CC110L_RegisterWrite(CC110L_PA_TABLE0, nBytes, &PAValue);
}

int16_t CC110L_ReadStatus()
{
	CC110L_STATUS status;
	uint8_t i = 0;
	for (i = 0; i < CC110L_RESERVED_0X3D - CC110L_PARTNUM; i++) {
		CC110L_RegisterRead(CC110L_PARTNUM + CC110L_SPI_BURST + i, 1, ((uint8_t *)&status) + i);
	}
	return 0;
}

//int CC110L::RX()
//{
//	int compare;
//	char addr = CC110L_RXFIFO;
//	char status;
//	while (gpioRead(CC110L_MISO))
//	{
//	}
//	while (1) //Until dat Avialible
//	{
//		if ((RXBufferWrite + 1 == RXBufferRead) || RXBufferRead == 0 && RXBufferWrite + 1 == CC110L_BUFFER_SIZE)
//		{
//			return -1; //BUFFER FULL
//		}
//		spiXfer(this->Device, &addr, &status, 1);
//		delay(200);
//		spiRead(this->Device, this->RXBuffer+RXBufferWrite, 1);
//		RXBufferWrite++;
//		if (RXBufferWrite >= CC110L_BUFFER_SIZE)
//		{
//			RXBufferWrite = 0;
//		}
//	}
//	return 0;
//}
//

int16_t CC110L_TX(void *data, uint8_t n_bytes)
{
	uint8_t status;
	status = CC110L_RegisterWrite(CC110L_TXFIFO, n_bytes, data);
	return status;
}

int16_t CC110L_RegisterWrite(uint8_t reg, uint8_t nBytes, void *TxBuffer)
{
	int16_t status;
	if(nBytes > 1) {
		reg |= CC110L_SPI_BURST;
	}

	reg |= CC110L_SPI_WRITE;

	CC110L_SPI_Start();

	SPI_transfer(1, &reg, 1, &status);
	if(nBytes != 0) {
		SPI_transmit(nBytes, TxBuffer);
	}

	CC110L_SPI_End();
	return status;
}

int16_t CC110L_RegisterRead(uint8_t reg, uint8_t nBytes, void *RxBuffer)
{
	int16_t status;
	if(nBytes > 1) {
		reg |= CC110L_SPI_BURST;
	}

	reg |= CC110L_SPI_READ;

	CC110L_SPI_Start();

	SPI_transfer(1, &reg, 1, &status);
	if(nBytes != 0) {
		SPI_receive(nBytes, RxBuffer);
	}

	CC110L_SPI_End();
	return status;
}

void CC110L_SPI_Start()
{
	P1OUT &= ~BIT4;
	while (CC110L_MISO_PIN & CC110L_MISO_BIT)
		;
}

void CC110L_SPI_End()
{
	P1OUT |= BIT4;
}

//int CC110L::SendData(char *Data)
//{
//	while (1) //Until dat Avialible
//	{
//		if ((TXBufferWrite + 1 == TXBufferRead) || TXBufferRead == 0 && TXBufferWrite + 1 == CC110L_BUFFER_SIZE)
//		{
//			return -1; //BUFFER FULL
//		}
//		*Data = this->TXBuffer[TXBufferWrite];
//		TXBufferWrite++;
//		if (TXBufferWrite >= CC110L_BUFFER_SIZE)
//		{
//			TXBufferWrite = 0;
//		}
//	}
//	return 0;
//}
//
//int CC110L::GetData()
//{
//	while (1) //Until dat Avialible
//	{
//		if (RXBufferWrite == RXBufferRead)
//		{
//			return -1; //Buffer Empty
//		}
//		return this->RXBuffer[RXBufferRead];
//		RXBufferRead++;
//		if (RXBufferRead >= CC110L_BUFFER_SIZE)
//		{
//			RXBufferRead = 0;
//		}
//	}
//	return 0;
//}
