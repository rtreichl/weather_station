#include "../../../driver.h"
#include <iostream>
#include <iomanip>
#include <cstring>
//#include <thread>
#include <pigpio.h>

using namespace std;

int delay(unsigned long nano)
{
	struct timespec ts;
	int err;

	ts.tv_sec = 0;
	ts.tv_nsec = nano;
	err = nanosleep(&ts, (struct timespec *)NULL);
	return (err);
}

CC110L::CC110L(CC110L_CONFIG *Config)
{
	gpioSetMode(CC110L_SPI_CS, PI_OUTPUT);
	gpioSetMode(CC110L_GPO2, PI_INPUT);
	gpioSetMode(CC110L_GPO0, PI_INPUT);
	if ((this->Device = spiOpen(CC110L_SPI_BUS, CC110L_SPI_BAUD, PI_SPI_FLAGS_RESVD(1))) < 0)
	{
		cout << "Error can't initialize SPI!";
	}
	SendCommand(CC110L_COMMAND_SRES);
	delay(50000000);
	WriteConfig(Config);
	delay(100000000);
	gpioSetISRFuncEx(CC110L_GPO0, RISING_EDGE, 30000, this->ClearFifo, (void *)(this));
	gpioSetISRFuncEx(CC110L_GPO2, RISING_EDGE, 30000, this->RX, (void *)(this));
}

CC110L::~CC110L()
{
	pthread_cancel(this->DSR);
	pthread_mutex_destroy(&this->mutex);
	pthread_cond_destroy(&this->condition);
	gpioSetISRFuncEx(CC110L_GPO0, RISING_EDGE, 30000, 0, 0);
	gpioSetISRFuncEx(CC110L_GPO2, RISING_EDGE, 30000, 0, 0);
	spiClose(this->Device);
}

int CC110L::SpiRead(uint8_t reg, void *RXBuffer, uint16_t n_bytes)
{
	if(n_bytes > 1) {
		reg |= CC110L_SPI_BURST;
	}

	reg |= CC110L_SPI_READ;

	gpioWrite(CC110L_SPI_CS, PI_LOW);

	while (gpioRead(CC110L_MISO))
	{
	}

	spiXfer(this->Device, (char *)&reg, (char *)&this->Status, 1);
	delay(200);
	if(n_bytes != 0) {
		spiRead(this->Device, (char *)RXBuffer, n_bytes);
	}
	gpioWrite(CC110L_SPI_CS, PI_HIGH);
	return 0;
}

int CC110L::SpiWrite(uint8_t reg, void *TXBuffer, uint16_t n_bytes)
{
	if(n_bytes > 1) {
		reg |= CC110L_SPI_BURST;
	}

	reg |= CC110L_SPI_WRITE;

	gpioWrite(CC110L_SPI_CS, PI_LOW);

	while (gpioRead(CC110L_MISO))
	{
	}

	spiXfer(this->Device, (char *)&reg, (char *)&this->Status, 1);
	delay(200);
	if(n_bytes != 0) {
		spiWrite(this->Device, (char *)TXBuffer, n_bytes);
	}
	gpioWrite(CC110L_SPI_CS, PI_HIGH);
	return 0;
}

int CC110L::SendCommand(char command)
{
	SpiWrite(command, 0, 0);
 	return 0;
}

bool CC110L::CheckConfig()
{
	CC110L_CONFIG config_tmp;
	SpiRead(CC110L_IOCFG2, &config_tmp, CC110L_TEST0 + 1);
	if(memcmp(&config_tmp, &this->ConfigReg, CC110L_TEST0 + 1) == 0) {
#if CC110L_DEBUG >= CC110L_DEBUG_LEVEL_1
		PrintConfigStatus(true, &config_tmp);
#endif
		return true;
	}
	else {
#if CC110L_DEBUG >= CC110L_DEBUG_LEVEL_3
		PrintConfigStatus(false, &config_tmp);
#endif
		return false;
	}
}

int CC110L::WritePATable(uint16_t PATable)
{
	uint16_t pa_table =  0x50;
	char addr = (0x40 | CC110L_PA_TABLE0);
	spiXfer(this->Device, &addr, (char *)&this->Status, 1);
	delay(200);
	spiXfer(this->Device, (char *)&pa_table, (char *)&this->Status, 2);
#if CC110L_DEBUG
	cout << "Address: 0x" << hex << (int)(addr - 0x40) << "  = 0x" << hex << (int)pa_table << endl;
#endif
	return 0;
}

int CC110L::ReadPATable()
{
	uint16_t pa_table = 0x50;
	char addr = (0xC0 | CC110L_PA_TABLE0);
	spiXfer(this->Device, &addr, (char *)&this->Status, 1);
	delay(200);
	spiRead(this->Device, (char *)&pa_table, 2);
	cout << "Address: 0x" << hex << (int)(addr - 0xC0) << "  = 0x50" << " , 0x" << hex << (int)pa_table << endl;
	return 0;
}

int CC110L::WriteConfig(CC110L_CONFIG *Config)
{
	memcpy((wchar_t*)&this->ConfigReg, (wchar_t*)Config, CC110L_TEST0 + 1);
	SpiWrite(CC110L_IOCFG2 ,&this->ConfigReg, CC110L_TEST0 + 1);
	CheckConfig();
	return 0;
}

int CC110L::ReadStatus()
{
	for (int i = 0; i < CC110L_RESERVED_0X3D - CC110L_PARTNUM; i++)
	{
		SpiRead(CC110L_PARTNUM + CC110L_SPI_BURST + i, ((char *)&this->StatusReg) + i, 1);
	}
	return 0;
}

float CC110L::ConvertRssi(int8_t rssi)
{
	return rssi / 2.0 - CC110L_RSSI_OFFSET;
}

int CC110L::ConfigDSR(void *(*func)(void *))
{
	pthread_mutex_init(&this->mutex, NULL);
	pthread_cond_init (&this->condition, NULL);
	pthread_create(&this->DSR, NULL, func, (void *)(this));
	//pthread_join(this->DSR, NULL);
	return 0;
}

void CC110L::ClearFifo(int gpio, int level, uint32_t tick, void  *userdata)
{
	CC110L *cc110l = (CC110L *)userdata;
	/* if timeout check for gpio level if still high return*/
	if(level == PI_TIMEOUT && gpioRead(gpio) == 0) {
		return;
	}

#if CC110L_DEBUG >= CC110L_DEBUG_LEVEL_1
	cout << "############## Buffer Overflow ##############" << endl << endl;
	cc110l->ReadStatus();
	cc110l->PrintStatusRegisters();
	cc110l->PrintGpioState();
	cc110l->PrintFifoStatus();
#endif
	cc110l->SendCommand(CC110L_COMMAND_SFRX);
	delay(50000000); //Wait 500 Milliseconds
#if CC110L_DEBUG >= CC110L_DEBUG_LEVEL_1
	cout << "############## Fifo Cleared ##############" << endl << endl;
	cc110l->ReadStatus();
	cc110l->PrintStatusRegisters();
	cc110l->PrintGpioState();
#endif
	cc110l->SendCommand(CC110L_COMMAND_SRX);
	delay(50000000); //Wait 500 Milliseconds
	return;
}

void CC110L::RX(int gpio, int level, uint32_t tick, void  *userdata)
{
	CC110L *cc110l = (CC110L *)userdata;

	/* if timeout check for gpio level if still high return*/
	if(level == PI_TIMEOUT && gpioRead(gpio) == 0) {
		return;
	}

#if CC110L_DEBUG >= CC110L_DEBUG_LEVEL_1
	cc110l->RxAvailableNum(true);
#else
	cc110l->RxAvailableNum(false);
#endif

	if(cc110l->AvailableBytes == 0) {
		return;
	}

	cc110l->RXPacketSize[cc110l->RXPacketPointer] = cc110l->AvailableBytes;

	if(++cc110l->RXPacketPointer == sizeof(cc110l->RXPacketSize)){
		cc110l->RXPacketPointer = 0;
	}
#if CC110L_DEBUG >= CC110L_DEBUG_LEVEL_1
	cc110l->PrintGpioState();
	cc110l->PrintFifoStatus();
#endif

	if(cc110l->RXBufferWrite + cc110l->AvailableBytes < CC110L_BUFFER_SIZE &&
		cc110l->RXBufferWrite + 1 > cc110l->RXBufferRead)
	{
		cc110l->SpiRead(CC110L_RXFIFO, &cc110l->RXBuffer[cc110l->RXBufferWrite], cc110l->AvailableBytes);
		cc110l->RXBufferWrite += cc110l->AvailableBytes;
	}
	else if(cc110l->RXBufferWrite + cc110l->AvailableBytes > CC110L_BUFFER_SIZE &&
			cc110l->RXBufferRead + cc110l->AvailableBytes - (CC110L_BUFFER_SIZE - cc110l->RXBufferWrite)> 0)
	{
		cc110l->SpiRead(CC110L_RXFIFO, &cc110l->RXBuffer[cc110l->RXBufferWrite], CC110L_BUFFER_SIZE - cc110l->RXBufferWrite);
		cc110l->SpiRead(CC110L_RXFIFO, &cc110l->RXBuffer[0], cc110l->AvailableBytes - (CC110L_BUFFER_SIZE - cc110l->RXBufferWrite));
		cc110l->RXBufferWrite = cc110l->AvailableBytes - (CC110L_BUFFER_SIZE - cc110l->RXBufferWrite);

	}
	else if(cc110l->RXBufferWrite + cc110l->AvailableBytes == CC110L_BUFFER_SIZE &&
			cc110l->RXBufferWrite > 0)
	{
		cc110l->SpiRead(CC110L_RXFIFO, &cc110l->RXBuffer[cc110l->RXBufferWrite], cc110l->AvailableBytes);
		cc110l->RXBufferWrite = 0;
	}
	else {
		return; //Buffer full
	}
	//cc110l->SendCommand(CC110L_COMMAND_SRX);
	pthread_cond_signal(&cc110l->condition);
}

void CC110L::RxAvailableNum(bool debug)
{
	CC110L_RXBYTES_STC RXBytes;
	SpiRead(CC110L_RXBYTES + CC110L_SPI_BURST, &RXBytes, 1);
	gpioWrite(CC110L_SPI_CS, PI_HIGH);
	if(debug) {
		this->PrintRxAvailableBytes(RXBytes);
	}
	AvailableBytes = RXBytes.NUM_RXBYTES;
}
	
int CC110L::TX()
{
	char addr = CC110L_RXFIFO;
	char status;
	while (gpioRead(CC110L_MISO))
	{
	}
	while (1) //Until dat Avialible
	{
		if (TXBufferWrite == TXBufferRead)
		{
			return -1; //Buffer Empty
		}
		spiXfer(this->Device, &addr, &status, 1);
		delay(200);
		spiWrite(this->Device, this->TXBuffer + TXBufferRead, 1);
		TXBufferRead++;
		if (TXBufferRead >= CC110L_BUFFER_SIZE)
		{
			TXBufferRead = 0;
		}
	}
	return 0;
}

int CC110L::SendData(char *Data)
{
	while (1) //Until dat Avialible
	{
		if ((TXBufferWrite + 1 == TXBufferRead || TXBufferRead == 0) && TXBufferWrite + 1 == CC110L_BUFFER_SIZE)
		{
			return -1; //BUFFER FULL
		}
		*Data = this->TXBuffer[TXBufferWrite];
		TXBufferWrite++;
		if (TXBufferWrite >= CC110L_BUFFER_SIZE)
		{
			TXBufferWrite = 0;
		}
	}
	return 0;
}

char CC110L::GetData()
{
	char ret = 0;
	if (RXBufferWrite == RXBufferRead)
	{
		return -1; //Buffer Empty
	}
	ret = this->RXBuffer[RXBufferRead];
	RXBufferRead++;
	if (RXBufferRead >= CC110L_BUFFER_SIZE)
	{
		RXBufferRead = 0;
	}
	return ret;
}

bool CC110L::GetData(void *data)
{
	unsigned char i = RXPacketSize[RXPacketPointer - 1];
	if(i == 0) {
		return false;
	}
	while(i-- || RXBufferWrite != RXBufferRead)
	{
		*(unsigned char *)data = this->RXBuffer[RXBufferRead];
		RXBufferRead++;
		if (RXBufferRead >= CC110L_BUFFER_SIZE)
		{
			RXBufferRead = 0;
		}
	}
	return true;
}

int16_t CC110L::RssiConvertion(uint8_t rssi_dec)
{
	uint8_t rssi_offset = 74;
	if (rssi_dec >= 128)
		return (int16_t)((int16_t)(rssi_dec - 256) / 2) - rssi_offset;
	else
		return  (rssi_dec / 2) - rssi_offset; 
}
