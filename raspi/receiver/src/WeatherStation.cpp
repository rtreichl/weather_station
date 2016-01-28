#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <iostream>
#include <endian.h>
#include <pthread.h>
#include <mysql/mysql.h>
#include <time.h>
//#include <sys/>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <string.h>
//#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <iostream>

#include "../driver/extern/cc110l/include/cc110l_config2.h"
#include "../driver/driver.h"
#include "database.h"
#include "protocol.h"

#define HDC1000_ADR  0x40
#define TMP102_ADR  0x48

#define NUM_THREADS     5

using namespace std;
using std::hex;
using std::dec;

//int getDatafromCC110L(CC110L &cc110l);
void *getDatafromCC110L(void  *userdata);

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

PROTOCOL_PORT_1_DATA_STC data;

//int main(int argc, char *argv[])
//{
//	data.hdc1000_humi = 3325;
//	data.hdc1000_temp = 2526;
//	data.tmp102_temp = 2645;
//	data.lps25h_temp = 2285;
//	data.lps25h_press = 95336;
//	data.si1147_ir = 200;
//	data.si1147_uv = 550;
//	data.si1147_vis = 300;
//	data.vbat = 330;
//	data.vsolar = 120;
//
//	Database db;
//	char address = 5;
//	char protocol = 1;
//	db.StoreData(1, 1, 1, &data);
//	//db.CreateSensor(1,1);
//	//db.CreateSensor(2,1);
//	//db.CreateSensor(3,1);
//	//db.CreateSensor(4,1);
//	return 0;
//}

#include <pthread.h>
#include <sys/poll.h>


int main(int argc, char* argv[])
{
	uint i = 1,t = 1;
	gpioInitialise();
	CC110L cc110l;
	cc110l.SendCommand(CC110L_COMMAND_SRES);
	delay(50000000);//cc110l.ReadConfig();
	cc110l.WriteConfig(CC110L_Config2);
	cc110l.ConfigDSR(getDatafromCC110L);
	cc110l.SendCommand(CC110L_COMMAND_SRX);
	cc110l.ReadStatus();
	cc110l.PrintStatusRegisters();
	cc110l.PrintStatusByte();
	//cc110l.ReadConfig();
	while(i)
	{
		if(t == 0) {
			cc110l.ReadStatus();
			cc110l.PrintStatusRegisters();
			cc110l.PrintStatusByte();
			t = 1;
		}
	}
//	HDC1000 hdc1000(I2C_DEVICE_1, HDC1000_ADR);
//	TMP102 tmp102(I2C_DEVICE_1, TMP102_ADR);
//	cout << hdc1000.ReadHumidity() << endl;
//	cout << hdc1000.ReadTemperature() << endl;
//	cout << tmp102.ReadTemperature() << endl;
//	hdc1000.~HDC1000();
//	tmp102.~TMP102();
	//cc110l.~CC110L();
	gpioTerminate();
	return 0;
}

void *getDatafromCC110L(void  *userdata)
{
	CC110L *cc110l = (CC110L *)userdata;
	//cc110l->RX();
	while(1) {
		time_t rawtime;
		//cc110l->SendCommand(CC110L_COMMAND_SRX);
		char i;
		PROTOCOL_STC package;
		char *ptr = (char *)&package;
		pthread_cond_wait(&cc110l->condition, &cc110l->mutex);
		for(i = 0; i < 33; i++)
		{
			*ptr++ = cc110l->GetData();
		}
		cc110l->PrintStatusByte();
		//pthread_mutex_unlock(&cc110l->mutex);
		time(&rawtime);
		cout << ctime(&rawtime);
		cout << "Package Len: " << dec << static_cast<int>(package.header.length) << endl;
		cout << "Dest Addr: 0x" << hex << (int)package.header.dest_addr << endl;
		cout << "Src Addr: 0x" << hex << (int)package.header.src_addr << endl;
		cout << "Port: 0x" << hex << (int)package.header.protocol << endl;
		cout << "Status: 0x" << hex << (int)package.header.status << endl;
		cout << "Solar Voltage:" << package.static_data.solar_voltage * 1.5 / 1024 << "V" << endl;
		cout << "Battery Voltage:" << package.static_data.max17048_vcell * 78.125 / 1000000 << "V" << endl;
		cout << "Battery Charge:" << package.static_data.max17048_charge / 256.0 << "%" << endl;
		cout << "Battery Charging Rate:" << package.static_data.max17048_crate * 0.208 << "%/hr" << endl;
		cout << "HDC1000 Temp: " << package.static_data.hdc1000_temp / 65535.0 * 165 - 40 << "\u2103" << endl;
		cout << "HDC1000 Humi: " << package.static_data.hdc1000_humi / 65535.0 * 100 << "%" << endl;
		cout << "TMP102 Temp: " << package.static_data.tmp102_temp * 0.0625 * 2 << "\u2103" << endl;
		switch(package.header.protocol) {
		case PROTOCOL_1:
			PROTOCOL_PORT_1_DATA_STC *ptr_data = (PROTOCOL_PORT_1_DATA_STC*)package.dyn_data;
			cout << "LPS25H Temp: " << ptr_data->lps25h_temp / 480.0 + 42.5 << "\u2103" << endl;
			cout << "LPS25H Press: " << ptr_data->lps25h_press / 4096.0 << "hPa" << endl;
			cout << "SI1147 IR: " << static_cast<int>(ptr_data->si1147_ir) << "lux" << endl;
			cout << "SI1147 VIS: " << static_cast<int>(ptr_data->si1147_vis) << "lux" << endl;
			cout << "SI1147 UV: " << ptr_data->si1147_uv / 100.0 << endl;
			cout << "Rssi: " << dec  << static_cast<int>(cc110l->RssiConvertion(ptr_data->append.rssi)) << "dBm" << endl;
			if (ptr_data->append.crc & 0x80)
				cout << "CRC: Ok!" << endl;
			else
				cout << "CRC: Failed!" << endl;
		}
	}
}
