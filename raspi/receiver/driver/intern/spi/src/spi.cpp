#include <driver.h>

#include <sys/ioctl.h>
#include <fcntl.h>
#include <iostream>
#include <linux/spi/spidev.h>
#include <unistd.h>

using namespace std;

uint8_t SPI::device_used[] = {0, 0};

string SPI::spiDev[] = {
		"/dev/spidev0.0",
		"/dev/spidev0.1"
};

SPI::SPI(uint8_t device, uint32_t spiSpeed, uint8_t spiMode, uint8_t spiBitsPerWord)
{
	this->speed = spiSpeed;
	this->mode = spiMode;
	this->bitsPerWord = spiBitsPerWord;

	if(device > 1) {
		cerr << "SPI device does not exists!" << endl;
		exit(-1);
	}

	if(device_used[device] != 0) {
		cerr << "SPI device is already in use!" << endl;
		exit(-1);
	}

	device_used[device] = 1;

	if((this->device = open(spiDev[device].c_str(), O_RDWR)) < 0) {
		cerr << "Can not open SPI device '" << spiDev[device] << "'" << endl;
		exit(-1);
	}

	if (ioctl(this->device, SPI_IOC_WR_MODE, &this->mode) < 0) {
		cerr << "Can not set SPI mode: '" << spiMode << "'" << endl;
		exit(-1);
	}

	if (ioctl(this->device, SPI_IOC_RD_MODE, &spiMode) < 0) {
		cerr << "Can not read SPI mode!" << endl;
		exit(-1);
	}

	if (this->mode != spiMode) {
		cerr << "Setting SPI mode failed!" << endl;
		exit(-1);
	}

	if (ioctl(this->device, SPI_IOC_WR_BITS_PER_WORD, &this->bitsPerWord) < 0) {
		cerr << "Can not set SPI mode: '" << spiBitsPerWord << "'" << endl;
		exit(-1);
	}

	if (ioctl(this->device, SPI_IOC_RD_BITS_PER_WORD, &bitsPerWord) < 0) {
		cerr << "Can not read SPI bits per word failed!" << endl;
		exit(-1);
	}

	if (this->bitsPerWord != spiBitsPerWord) {
		cerr << "Setting SPI bits per word failed!" << endl;
		exit(-1);
	}

	if (ioctl(this->device, SPI_IOC_WR_MAX_SPEED_HZ, &this->speed) < 0) {
		cerr << "Can not set SPI mode: '" << spiSpeed << "'" << endl;
		exit(-1);
	}

	if (ioctl(this->device, SPI_IOC_RD_MAX_SPEED_HZ, &spiSpeed) < 0) {
		cerr << "Can not read SPI bits per word failed!" << endl;
		exit(-1);
	}

	if (this->speed != spiSpeed) {
		cerr << "Setting SPI bits per word failed!" << endl;
		exit(-1);
	}
}

int SPI::SPIRead(void *RxBuffer, uint8_t n_Bytes)
{
	struct spi_ioc_transfer spi;
	spi.len =  n_Bytes;
	spi.tx_buf = 0;
	spi.rx_buf = (unsigned long)RxBuffer;
	spi.speed_hz = this->speed;
	spi.bits_per_word = this->bitsPerWord;

    return ioctl(this->device, SPI_IOC_MESSAGE(1), spi);
}

int SPI::SPIWrite(void *TxBuffer, uint8_t n_Bytes)
{
	struct spi_ioc_transfer spi;
	spi.len =  n_Bytes;
	spi.tx_buf = (unsigned long)TxBuffer;
	spi.rx_buf = 0;
	spi.speed_hz = this->speed;
	spi.bits_per_word = this->bitsPerWord;

    return ioctl(this->device, SPI_IOC_MESSAGE(1), spi);
}

int SPI::SPIXfer(void *TxBuffer, void *RxBuffer, uint8_t n_Bytes)
{
	struct spi_ioc_transfer spi;
	spi.len =  n_Bytes;
	spi.tx_buf = (unsigned long)TxBuffer;
	spi.rx_buf = (unsigned long)RxBuffer;
	spi.speed_hz = this->speed;
	spi.bits_per_word = this->bitsPerWord;

    return ioctl(this->device, SPI_IOC_MESSAGE(1), spi);
}

SPI::~SPI()
{
	close(this->device);
}
