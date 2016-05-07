#include "../driver/driver.h"
#include "../driver/extern/cc110l/include/cc110l_config2.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <iostream>
#include <endian.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <fcntl.h>
//#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <iostream>

#include "database.h"
#include "protocol.h"

#include "../cmd/CommandParser.h"
#include "../cmd/concrete/inc.h"

#define HDC1000_ADR  0x40
#define TMP102_ADR  0x48

#define NUM_THREADS     5

using namespace std;
using std::hex;
using std::dec;

//int getDatafromCC110L(CC110L &cc110l);
void *getDatafromCC110L(void  *userdata);
void *getPiSensorData(void *arg);

//void *Sensor(void *threadid)
//{
//	gpioInitialise();
//	float temp, temp2, humi;
//	void * values[3] = {&temp, &humi, &temp2};
//	HDC1000 hdc1000(HDC1000_ADR);
//	TMP102 tmp102(TMP102_ADR);
//	OWN_MYSQL mysql;
//	mysql.SelectTabel("IndoorSensor");
//	hdc1000.GetIdentity();
//	cout.precision(2);
//	while (1)
//	{
//		temp = hdc1000.ReadTemperature();
//		humi = hdc1000.ReadHumidity();
//		temp2 = tmp102.ReadTemperature();
//		cout << "HDC1000 Temp: " << fixed <<  temp << "°" << endl;
//		cout << "HDC1000 Humi: " << fixed <<  humi << "%" << endl;
//		cout << "TMP102  Temp: " << fixed << temp2 << "°" << endl;
//		mysql.Insert("float HDC1000_TMP, float HDC1000_RH, float TMP102_TMP", values);
//		gpioSleep(PI_TIME_RELATIVE, 60, 0);
//		system("clear");
//	}
//	gpioTerminate();
//
//	pthread_exit(NULL);
//}

//int main(int argc, char *argv[])
//{
//	uint8_t tmp = 0x3D;
//	CC110L_STATUS_STC *status = (CC110L_STATUS_STC *)&tmp;
//	pthread_t threads[NUM_THREADS];
//	gpioInitialise();
//	CC110L cc110l;
//	cc110l.SendCommand(CC110L_COMMAND_SRES);
//	//cc110l.ReadConfig();
//	cc110l.WriteConfig(CC110L_Config2);
//	cc110l.SendCommand(CC110L_COMMAND_SRX);
//	//cc110l.ReadConfig();
//
//	gpioSetISRFuncEx(CC110L_GPO2, RISING_EDGE, 0, getDatafromCC110L, (void *)(&cc110l));
//
//	do
//	{
//		//cout << "Address: 0x" << hex << (int)(CC110L_IOCFG2 + i) << " = 0x" << hex << (int)tmp << endl;
//		//cout << "CHIP Ready:" << (int)status->CHIP_RDYn << endl;
//		//cout << "State:" << (int)status->STATE << endl;
//		//cout << "FIFO:" << (int)status->FIFO_BYTES_AVILABLE << endl;
//
//		/*if (int rc = pthread_create(&threads[0], NULL, Sensor, (void *)0))
//		{
//			cout << "ERROR; return code from pthread_create() is " << rc << endl;
//		}*/
//		//cout << gpioRead(CC110L_GPO2);
//
//		cc110l.ReadStatus();
//		cin >> tmp;
//	} while (tmp != 'x');
//	gpioTerminate();
//	//pthread_cancel(threads[0]);
//	pthread_exit(NULL);
//	return 0;
//}

#include <pthread.h>
#include <sys/poll.h>

//int main(int argc, char **argv) {
//	// example usage:
//
//	gpioInitialise();
//	HDC1000 hdc1000(I2C_DEVICE_1, HDC1000_ADR);
////	CC110L cc110l(CC110L_Config2);
////	cc110l.ConfigDSR(getDatafromCC110L);
////	cc110l.SendCommand(CC110L_COMMAND_SRX);
//
//	CommandParser cmdParser;
//	std::string line;
//
//	// register cmds
//	//cmdParser.registerCmd(new CommandPrintParam());
//	//cmdParser.registerCmd(new CommandSize());
//	cmdParser.registerCmd(new CommandPrint(&hdc1000));
//
//	// read command line
//	// till exit
//
//	std::cout << "cmd << ";
//	while (std::getline(std::cin, line)) {
//		if (line != "exit" && line.size() != 0) {
//			cmdParser.setCommandLine(line);
//			cmdParser.executeCmd();
//			std::cout << "cmd << ";
//		}
//		else if(line == "exit")
//			break;
//	}
//	gpioTerminate();
//	return 0;
//}

int main(int argc, char* argv[])
{
	pthread_t rapi_thread;
	gpioInitialise();

	CommandParser cmdParser;
	std::string line;

	CC110L cc110l(CC110L_Config2);
	cmdParser.registerCmd(new CommandCC110LPrint(&cc110l));
	cc110l.ConfigDSR(getDatafromCC110L);
	cc110l.SendCommand(CC110L_COMMAND_SRX);
	cc110l.ReadStatus();
	cc110l.PrintStatusRegisters();
	cc110l.PrintStatusByte();
	system("printf '\e[8;50;100t'");
	pthread_create(&rapi_thread, NULL, getPiSensorData, NULL);
	//pthread_join(rapi_thread, NULL);
	std::cout << "cmd << ";
	while (std::getline(std::cin, line)) {
		if (line != "exit" && line.size() != 0) {
			cmdParser.setCommandLine(line);
			cmdParser.executeCmd();
			std::cout << "cmd << ";
		}
		else if(line == "exit")
			break;
	}
//	HDC1000 hdc1000(I2C_DEVICE_1, HDC1000_ADR);
//	TMP102 tmp102(I2C_DEVICE_1, TMP102_ADR);
//	cout << hdc1000.ReadHumidity() << endl;
//	cout << hdc1000.ReadTemperature() << endl;
//	cout << tmp102.ReadTemperature() << endl;
//	hdc1000.~HDC1000();
//	tmp102.~TMP102();
	cc110l.~CC110L();
	gpioTerminate();
	return 0;
}

void *getDatafromCC110L(void  *userdata)
{
	CC110L *cc110l = (CC110L *)userdata;
	Database db;
	while(1) {
		PROTOCOL_DATA_STC package;
		DATABASE_DATA_STC data;
		uint8_t * ptr_package = (uint8_t *)&package;
		char i;
		pthread_cond_wait(&cc110l->condition, &cc110l->mutex);
//		if(!cc110l->GetData(&package))
//		{
//			cout << "No Data Ava." << endl;
//		}
		for(i = 0; i < cc110l->AvailableBytes; i++)
		{
			*ptr_package++ = cc110l->GetData();
		}
		protocol_decoder(&package, &data);
		db.StoreData(&data);
		protocol_print_data(&data);
		cc110l->PrintStatusByte();
	}
}

#define RAPI_ADDR 8

void *getPiSensorData(void *arg)
{
	gpioInitialise();
	sleep(20);
	HDC1000 hdc1000(I2C_DEVICE_1, HDC1000_ADR);
	TMP102 tmp102(I2C_DEVICE_1, TMP102_ADR);
	DATABASE_DATA_STC data = {0};
	Database db;
	data.header.addr  = RAPI_ADDR;
	data.hardware.hdc1000 = 1;
	data.hardware.tmp102 = 1;
	while(1) {
		data.hdc1000.humi = hdc1000.ReadHumidity();
		data.hdc1000.temp = hdc1000.ReadTemperature();
		data.tmp102.temp = tmp102.ReadTemperature();
		data.tmp102.temp = roundf(data.tmp102.temp * 100) / 100;
		data.hdc1000.temp = roundf(data.hdc1000.temp * 100) / 100;
		data.hdc1000.humi = roundf(data.hdc1000.humi * 100) / 100;
		db.StoreData(&data);
		protocol_print_data(&data);
		sleep(120);
	}
	gpioTerminate();
}

