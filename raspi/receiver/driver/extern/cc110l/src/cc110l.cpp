#include "../../../driver.h"
#include <iostream>
#include <iomanip>
#include <cstring>
//#include <thread>
#include <pigpio.h>

using namespace std;

#define CC110L_SPI_BUS 0
#define CC110L_SPI_BAUD 500000
#define CC110L_MISO 9
#define CC110L_SPI_CS 15
#define CC110L_GPO0 18
#define CC110L_GPO2 23

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

int CC110L::CheckConfig()
{
	CC110L_CONFIG config_tmp;
	SpiRead(CC110L_IOCFG2, &config_tmp, CC110L_TEST0 + 1);
	if(memcmp(&config_tmp, &this->ConfigReg, CC110L_TEST0 + 1) == 0) {
#if CC110L_DEBUG >= CC110L_DEBUG_LEVEL_1
		cout << "##########################################" << endl;
		cout << "Configuration is valid" << endl;
		cout << "##########################################" << endl << endl;
#endif
		return 0;
	}
	else {
#if CC110L_DEBUG >= CC110L_DEBUG_LEVEL_3
		cout << "##########################################" << endl;
		cout << "Configuration check failed" << endl;
		char *config = (char *)&config_tmp;
		char *config2 = (char *)&this->ConfigReg;
		cout << "Address: 0xREG = 0xMCU, 0xCTRL" << endl;
		for (addr =  (0x80 | CC110L_IOCFG2); addr <= (0x80 | CC110L_TEST0); addr++)
		{
			cout << "Address: 0x" << hex << (int)(addr - 0x80) << "  = 0x" << hex << (int)*config2 << " , 0x" << hex << (int)*config;
			if (*config2 == *config)
				cout << " OK" << endl;
			else
				cout << " FAILD" << endl;
			config++;
			config2++;
		}
		cout << "##########################################" << endl << endl;
#endif
		return -1;
	}
	return 0;
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

void CC110L::PrintStatusRegisters()
{
	cout << "############ Status registers ############" << endl;
	cout << "Partnumber: 0x" << hex << (int)this->StatusReg.PARTNUM << endl;
	cout << "Verstion: 0x" << hex << (int)this->StatusReg.VERSION << endl;
	cout << "Freqency offset: " << setprecision(2) << fixed << this->StatusReg.FREQEST * 1.59 << "kHz" << endl;
	if(this->StatusReg.CRC_REG == 0x80){
		cout << "Last CRC ok!" << endl;
	}
	else {
		cout << "Last CRC failed!" << endl;
	}
	cout << "RSSI: " << setprecision(2) << fixed << ConvertRssi(this->StatusReg.RSSI) << "dbm" << endl;
	cout << "Status machine state: ";
	switch(this->StatusReg.MAECSTATE){
	case CC110L_MARCSTATE_SLEEP:
		cout << "Sleep" << endl;
		break;
	case CC110L_MARCSTATE_IDLE:
		cout << "Idle" << endl;
		break;
	case CC110L_MARCSTATE_XOFF:
		cout << "Xoff" << endl;
		break;
	case CC110L_MARCSTATE_VCOON_MC:
		cout << "VCOON_MC" << endl;
		break;
	case CC110L_MARCSTATE_REGON_MC:
		cout << "REGON_MC" << endl;
		break;
	case CC110L_MARCSTATE_MANCAL:
		cout << "MANCAL" << endl;
		break;
	case CC110L_MARCSTATE_VCOON:
		cout << "VCOON" << endl;
		break;
	case CC110L_MARCSTATE_REGON:
		cout << "REGON" << endl;
		break;
	case CC110L_MARCSTATE_STARTCAL:
		cout << "Start calibration" << endl;
		break;
	case CC110L_MARCSTATE_BWBOOST:
		cout << "Bandwidth boost" << endl;
		break;
	case CC110L_MARCSTATE_IFADCON:
		cout << "IFADCON" << endl;
		break;
	case CC110L_MARCSTATE_ENDCAL:
		cout << "End calibration" << endl;
		break;
	case CC110L_MARCSTATE_RX:
		cout << "Receive" << endl;
		break;
	case CC110L_MARCSTATE_RX_END:
		cout << "Receive end" << endl;
		break;
	case CC110L_MARCSTATE_RX_RST:
		cout << "Receive reset" << endl;
		break;
	case CC110L_MARCSTATE_TXRX_SWITCH:
		cout << "Switch from TX to RX" << endl;
		break;
	case CC110L_MARCSTATE_RXFIFO_OVERFLOW:
		cout << "RX fifo overflow" << endl;
		break;
	case CC110L_MARCSTATE_FSTXON:
		cout << "FSTXON" << endl;
		break;
	case CC110L_MARCSTATE_TX:
		cout << "Transmit" << endl;
		break;
	case CC110L_MARCSTATE_TX_END:
		cout << "Transmit reset" << endl;
		break;
	case CC110L_MARCSTATE_RXTX_SWITCH:
		cout << "Switch from RX to TX" << endl;
		break;
	case CC110L_MARCSTATE_TXFIFO_UNDERFLOW:
		cout << "TX fifo underflow" << endl;
		break;
	}
	cout << "Package StatusReg: " << endl;
	if(this->StatusReg.PKTSTATUS.CRC_OK) {
		cout << "Last CRC ok" << endl;
	}
	else {
		cout << "Last CRC faild" << endl;
	}
	if(this->StatusReg.PKTSTATUS.CS) {
		cout << "Carrier sense on" << endl;
	}
	else {
		cout << "Carrier sense off" << endl;
	}
	if(this->StatusReg.PKTSTATUS.CCA) {
		cout << "Channel free" << endl;
	}
	else {
		cout << "Channel busy" << endl;
	}
	if(this->StatusReg.PKTSTATUS.SFD) {
		cout << "Sync byte received" << endl;
	}
	else {
		cout << "Package end" << endl;
	}
	if(this->StatusReg.PKTSTATUS.GDO0) {
		cout << "GDO0 is high" << endl;
	}
	else {
		cout << "GDO0 is low" << endl;
	}
	if(this->StatusReg.PKTSTATUS.GDO2) {
		cout << "GDO2 is high" << endl;
	}
	else {
		cout << "GDO2 is low" << endl;
	}
	cout << "RX buffer bytes: " << (int)this->StatusReg.RXBYTES.NUM_RXBYTES << endl;
	if(this->StatusReg.RXBYTES.RXFIFO_OVERFLOW == 1) {
		cout << "RX fifo overflow" << endl;
	}
	cout << "TX buffer bytes: " << (int)this->StatusReg.TXBYTES.NUM_TXBYTES << endl;
	if(this->StatusReg.TXBYTES.TXFIFO_UNDERFLOW == 1) {
		cout << "TX fifo underflow" << endl;
	}
	cout << "##########################################" << endl << endl;
}

void CC110L::PrintGpioState()
{
	cout << endl;
	cout << "################# GPIO #################" << endl;
	cout << "GPO0: " << static_cast<int>(CC110L_GPO0) << endl;
	cout << "GPO0 Level: " << static_cast<int>(gpioRead(CC110L_GPO0)) << endl;
	cout << "GPO0 Function:" << std::hex << static_cast<int>(this->ConfigReg.IOCFG0.GDO0_CFG) << endl;
	cout << "GPO2: " << static_cast<int>(CC110L_GPO2) << endl;
	cout << "GPO2 Level: " << static_cast<int>(gpioRead(CC110L_GPO2)) << endl;
	cout << "GPO2 Function:" << std::hex << static_cast<int>(this->ConfigReg.IOCFG2.GDO2_CFG) << endl;
	cout << "########################################" << endl;
}

void CC110L::PrintStatusByte()
{
	cout << "################# Status #################" << endl;
	if(this->Status.CHIP_RDYn == 0) {
		cout << "Device ready" << endl;
	}
	else {
		cout << "Device Busy" << endl;
	}
	cout << "Mode: ";
	switch (this->Status.STATE)
	{
	case 0:
		cout << "Idle";
		break;
	case 1:
		cout << "Receive";
		break;
	case 2:
		cout << "Transmit";
		break;
	case 3:
		cout << "FSTXON";
		break;
	case 4:
		cout << "Calibrate";
		break;
	case 5:
		cout << "Settling";
		break;
	case 6:
		cout << "RX fifo overflow";
		break;
	case 7:
		cout << "TX fifo underflow";
	}
	cout << endl;
	cout << "Bytes available: " << static_cast<int>(this->Status.FIFO_BYTES_AVILABLE) << endl;
	cout << "##########################################" << endl << endl;
}

void CC110L::ClearFifo(int gpio, int level, uint32_t tick, void  *userdata)
{
	CC110L *cc110l = (CC110L *)userdata;
	/* if timeout check for gpio level if still high return*/
	if(level == PI_TIMEOUT && gpioRead(gpio) == 0) {
		return;
	}
	cc110l->ReadStatus();
	cc110l->PrintStatusRegisters();
#if CC110L_DEBUG >= CC110L_DEBUG_LEVEL_1
	cout << endl;
	cout << "############## Interrupt ###############" << endl;
	cout << "Clear Fifo" << endl;
	cout << "Level: " << static_cast<int>(level) << endl;
	cout << "GPIO Level: " << static_cast<int>(gpioRead(gpio)) << endl;
	cout << "########################################" << endl;
#endif
	cc110l->SendCommand(CC110L_COMMAND_SFRX);
	cc110l->SendCommand(CC110L_COMMAND_SRX);
	return;
}

void CC110L::RX(int gpio, int level, uint32_t tick, void  *userdata)
{
	CC110L *cc110l = (CC110L *)userdata;
	uint8_t Num;

	/* if timeout check for gpio level if still high return*/
	if(level == PI_TIMEOUT && gpioRead(gpio) == 0) {
		return;
	}

	Num = cc110l->RxAvailableNum();

	if(Num == 0) {
		return;
	}

	cc110l->RXPacketSize[cc110l->RXPacketPointer] = Num;

	if(++cc110l->RXPacketPointer == sizeof(cc110l->RXPacketSize)){
		cc110l->RXPacketPointer = 0;
	}
#if CC110L_DEBUG >= CC110L_DEBUG_LEVEL_1
	cout << "############## Interrupt ###############" << endl;
	cout << "Level: " << static_cast<int>(level) << endl;
	cout << "GPIO Level: " << static_cast<int>(gpioRead(gpio)) << endl;
	cout << "Num Bytes: " << static_cast<int>(Num) << endl;
	cout << "Read Pointer: " << static_cast<int>(cc110l->RXBufferRead) << endl;
	cout << "Write Pointer: " << static_cast<int>(cc110l->RXBufferWrite) << endl;
	cout << "########################################" << endl;
#endif

	if(cc110l->RXBufferWrite + Num < CC110L_BUFFER_SIZE &&
		cc110l->RXBufferWrite + 1 > cc110l->RXBufferRead)
	{
		cc110l->SpiRead(CC110L_RXFIFO, &cc110l->RXBuffer[cc110l->RXBufferWrite], Num);
		cc110l->RXBufferWrite += Num;
	}
	else if(cc110l->RXBufferWrite + Num > CC110L_BUFFER_SIZE &&
			cc110l->RXBufferRead + Num - (CC110L_BUFFER_SIZE - cc110l->RXBufferWrite)> 0)
	{
		cc110l->SpiRead(CC110L_RXFIFO, &cc110l->RXBuffer[cc110l->RXBufferWrite], CC110L_BUFFER_SIZE - cc110l->RXBufferWrite);
		cc110l->SpiRead(CC110L_RXFIFO, &cc110l->RXBuffer[0], Num - (CC110L_BUFFER_SIZE - cc110l->RXBufferWrite));
		cc110l->RXBufferWrite = Num - (CC110L_BUFFER_SIZE - cc110l->RXBufferWrite);

	}
	else if(cc110l->RXBufferWrite + Num == CC110L_BUFFER_SIZE &&
			cc110l->RXBufferWrite > 0)
	{
		cc110l->SpiRead(CC110L_RXFIFO, &cc110l->RXBuffer[cc110l->RXBufferWrite], Num);
		cc110l->RXBufferWrite = 0;
	}
	else {
		return; //Buffer full
	}
	//cc110l->SendCommand(CC110L_COMMAND_SRX);
	pthread_cond_signal(&cc110l->condition);
}

int CC110L::RxAvailableNum()
{
	CC110L_RXBYTES_STC RXBytes;
	SpiRead(CC110L_RXBYTES + CC110L_SPI_BURST, &RXBytes, 1);
	gpioWrite(CC110L_SPI_CS, PI_HIGH);
#if CC110L_DEBUG >= CC110L_DEBUG_LEVEL_2
	PrintRxAvailableBytes(RXBytes);
#endif
	AvailableBytes = RXBytes.NUM_RXBYTES;
	return RXBytes.NUM_RXBYTES;

}

void CC110L::PrintRxAvailableBytes(CC110L_RXBYTES_STC RXBytes)
{
	cout << "##########################################" << endl;
	cout << "Available bytes RxFifo: "  << static_cast<int>(RXBytes.NUM_RXBYTES) << endl;
	if(RXBytes.RXFIFO_OVERFLOW == 1)
		cout << "RX fifo buffer overflow" << endl;
	cout << "##########################################" << endl << endl;
}

void CC110L::PrintRxAvailableBytes()
{
	cout << "##########################################" << endl;
	cout << "Available bytes RxFifo: "  << static_cast<int>(AvailableBytes) << endl;
	cout << "##########################################" << endl << endl;
}

void CC110L::PrintFifoStatus()
{
	cout << "##########################################" << endl;
	cout << "Read Pointer: " << static_cast<int>(RXBufferRead) << endl;
	cout << "Write Pointer: " << static_cast<int>(RXBufferWrite) << endl;
	cout << "##########################################" << endl;
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
