/******************************************************************************
    Filename: cc11xL_spi.h  
    
    Description: header file that defines a minimum set of neccessary functions
                 to communicate with CC11xL over SPI as well as the regsister 
                 mapping.    
 
*******************************************************************************/

#ifndef CC11xL_SPI_H
#define CC11xL_SPI_H

#include <stdint.h>
#include "include/cc110l.h"

#define CC110L_SPI_BUS 0
#define CC110L_SPI_BAUD 500000
#define CC110L_MISO 9
#define CC110L_SPI_CS 15
#define CC110L_GPO0 18
#define CC110L_GPO2 23

#define CC110L_DEBUG_LEVEL_1 1
#define CC110L_DEBUG_LEVEL_2 2
#define CC110L_DEBUG_LEVEL_3 3
#define CC110L_DEBUG CC110L_DEBUG_LEVEL_1

#define CC110L_BUFFER_SIZE 256


#include <pthread.h>

int delay(unsigned long nano);

class CC110L
{
public:
	CC110L(CC110L_CONFIG *Config);
	~CC110L();
	int SendData(char *Data);
	char GetData();
	bool GetData(void *data);
	bool CheckConfig();
	int WriteConfig(CC110L_CONFIG *Config);
	int ReadStatus();
	int SendCommand(char command);
	void PrintStatusByte();
	void PrintGpioState();
	void PrintStatusRegisters();
	void PrintRxAvailableBytes(CC110L_RXBYTES_STC RXBytes);
	void PrintRxAvailableBytes();
	void PrintFifoStatus();
	void PrintConfigStatus(bool state, CC110L_CONFIG *config_tmp);
	int ConfigDSR(void *(*function)(void *));
	static int16_t RssiConvertion(uint8_t rssi_dec);
	int AvailableBytes = 0;
	pthread_mutex_t mutex;
	pthread_cond_t condition;
	pthread_t DSR = 0;
private:
	static void ClearFifo(int gpio, int level, uint32_t tick, void  *userdata);
	static void RX(int gpio, int level, uint32_t tick, void  *userdata);
	int SpiWrite(uint8_t reg, void *TXBuffer, uint16_t n_bytes);
	int SpiRead(uint8_t reg, void *RXBuffer, uint16_t n_bytes);
	int TX();
	void RxAvailableNum(bool debug);
	int WritePATable(uint16_t PATable);
	int ReadPATable();
	float ConvertRssi(int8_t rssi);

	CC110L_CONFIG ConfigReg;
	CC110L_STATUS StatusReg;
	CC110L_STATUS_STC Status;
	int Device;
	bool RxBufferOverThres = 0;
	unsigned char RXBufferRead = 0;
	unsigned char RXBufferWrite = 0;
	unsigned char RXPacketPointer = 0;
	char RXBuffer[CC110L_BUFFER_SIZE];
	unsigned char RXPacketSize[CC110L_BUFFER_SIZE / 16] = {0};
	unsigned char TXBufferRead = 0;
	unsigned char TXBufferWrite = 0;
	char TXBuffer[CC110L_BUFFER_SIZE];
};

#endif// CC11xL_SPI_H
