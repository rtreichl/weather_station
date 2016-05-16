/*
 * cc110l_debug.cpp
 *
 *  Created on: 15.05.2016
 *      Author: Richard Treichl
 */

#include "../../../driver.h"
#include <iostream>
#include <iomanip>
#include <cstring>

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
	cout << "########################################" << endl << endl;
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

void CC110L::PrintConfigStatus(bool state, CC110L_CONFIG *config_tmp)
{
	char addr = 0;
	if(!state) {
		cout << "##########################################" << endl;
		cout << "Configuration is valid" << endl;
		cout << "##########################################" << endl << endl;
	}
	else {
		cout << "##########################################" << endl;
		cout << "Configuration check failed" << endl;
		char *config = (char *)config_tmp;
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
	}
}


