/*
 * GPIO.cpp
 *
 *  Created on: 16.01.2016
 *      Author: Richard Treichl
 */

#include <driver.h>
#include <sys/ioctl.h>
//#include <linux/signal.h>
#include <linux/sched.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <poll.h>
#include <fcntl.h>
#include <string.h>
//#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <iostream>
#include <sstream>
#include <pthread.h>
#include <thread>
//#include <linux/i
using namespace std;

GPIO::GPIO(enum gpio_pin pin) {
	int fd;
	stringstream gpio;
	this->pin = pin;
	gpio << this->pin;

	if((fd = open("/sys/class/gpio/export", O_WRONLY)) < 0) {
		cerr << "Kann nicht auf export schreiben!" << endl;
		exit(-1);
	}
	if (write(fd, gpio.str().c_str(), gpio.str().length()) < 0) {
		cerr << "gpio_export: Can not activate Pin: " << gpio << endl;
		exit(-1);
	}
	close(fd);
}

int GPIO::GPIODirection(enum gpio_direction dir)
{
	int fd;
	stringstream direction;

	direction << "/sys/class/gpio/gpio";
	direction << this->pin;
	direction << "/direction";

	if((fd = open(direction.str().c_str(), O_WRONLY)) < 0) {
		cerr << "Kann nicht auf export schreiben!" << endl;
		return(-1);
	}

	direction.clear();

	if(dir == GPIO_IN) {
		direction << "in";
	}
	else if(dir == GPIO_OUT) {
		direction << "out";
	}

	if (write(fd, direction.str().c_str(), direction.str().length()) < 0) {
		cerr << "gpio_export: Can not activate Pin: " << this->pin << endl;
		return(-1);
	}
	close(fd);
	return 0;
}

int GPIO::GPIOEdge(enum gpio_edge edge)
{
	int fd;
	stringstream edges;

	edges << "/sys/class/gpio/gpio";
	edges << this->pin;
	edges << "/edge";

	if((fd = open(edges.str().c_str(), O_WRONLY)) < 0) {
		cerr << "Kann nicht auf export schreiben!" << endl;
		return(-1);
	}

	edges.clear();

	switch (edge) {
	case GPIO_RISING_EDGE:
		edges << "rising";
		break;
	case GPIO_FALLING_EDGE:
		edges << "falling";
		break;
	case GPIO_BOTH_EDGE:
		edges << "both";
		break;
	case GPIO_NONE_EDGE:
		edges << "none";
		break;
	default:
		return (-2);
	}

	if (write(fd, edges.str().c_str(), edges.str().length()) < 0) {
		cerr << "gpio_export: Can not activate Pin: " << this->pin << endl;
		return(-1);
	}
	close(fd);
	return 0;
}

GPIO::~GPIO() {
	int fd;
	stringstream gpio;
	gpio << this->pin;

	if((fd = open("/sys/class/gpio/unexport", O_WRONLY)) < 0) {
		cerr << "Kann nicht auf export schreiben!" << endl;
		exit(-1);
	}
	if (write(fd, gpio.str().c_str(), gpio.str().length()) < 0) {
		cerr << "gpio_export: Can not activate Pin: " << gpio << endl;
		exit(-1);
	}
	close(fd);
}

int GPIO::GPIOCreateISR(void (*function)(void *), enum gpio_edge edge) {
	this->function = function;
	GPIOEdge(edge);
	pthread_create(&this->gpio_thread, NULL, GPIO::Interrupt, (void*)this);
	return 0;
}

int GPIO::GPIODeleteISR() {
	return 0;
}

#define BCM2708_PERI_BASE	                     0x20000000
#define GPIO_BASE		(BCM2708_PERI_BASE + 0x00200000)
#define GPPUD 37
#define	PAGE_SIZE		(4*1024)
#define	BLOCK_SIZE		(4*1024)

#include <sys/mman.h>

//int GPIO::GPIOPullResistor()
//{
//	int fd;
//	  if ((fd = open ("/dev/mem", O_RDWR | O_SYNC) ) < 0)
//	  {
//	      int serr = errno ;
//		fprintf (stderr, "wiringPiSetup: Unable to open /dev/mem: %s\n", strerror (errno)) ;
//	      errno = serr ;
//	    }
//	    return -1 ;
//	  }
//
//	// GPIO:
//	  static uint8_t gpioToPUDCLK [] =
//	  {
//	    38,38,38,38,38,38,38,38,38,38,38,38,38,38,38,38,38,38,38,38,38,38,38,38,38,38,38,38,38,38,38,38,
//	    39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,
//	  } ;
//	  gpio = (uint32_t *)mmap(0, BLOCK_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, GPIO_BASE) ;
//	  if ((int32_t)gpio == -1)
//	  {
//	    if (wiringPiDebug)
//	    {
//	      int serr = errno ;
//		fprintf (stderr, "wiringPiSetup: mmap failed: %s\n", strerror (errno)) ;
//	      errno = serr ;
//	    }
//	    return -1 ;
//	  }
//
//	 *(gpio + GPPUD)              = pud ;			delayMicroseconds (5) ;
//	  *(gpio + gpioToPUDCLK [pin]) = 1 << (pin & 31) ;	delayMicroseconds (5) ;
//
//	  *(gpio + GPPUD)              = 0 ;			delayMicroseconds (5) ;
//	  *(gpio + gpioToPUDCLK [pin]) = 0 ;			delayMicroseconds (5) ;
//	return 0;
//}

void *GPIO::Interrupt(void *arg){
	GPIO *gpio = (GPIO*) arg;
	stringstream pin;
	struct pollfd polldata;
	int rc;
	pin << "sys/class/gpio/";
	pin << gpio->pin;
	pin << "/value";
	if((polldata.fd = open(pin.str().c_str(), O_RDONLY | O_NONBLOCK)) < 0) {
		cerr << "Can't open gpio for interrupt!";
		pthread_exit(&polldata.fd);
	}
	polldata.events = POLLPRI;
	polldata.revents = 0;
	lseek(polldata.fd, 0, SEEK_SET);
	//Maybe Read!!!
	while(1) {
		rc = poll(&polldata, 1, 500);
		if (rc < 0) { /* poll() failed! */
			cerr << "gpio_wait: Poll-Aufruf ging schief!" << endl;
			close(polldata.fd);
			pthread_exit(&polldata.fd);
		}
		if (rc == 0) { /* poll() timeout! */
			continue;
		}
		if (polldata.revents & POLLPRI) {
			if (rc < 0) { /* read() failed! */
				cerr << "gpio_wait: Kann von GPIO nicht lesen (read)!" << endl;
				close(polldata.fd);
				pthread_exit(&polldata.fd);
			}
			/* printf("poll() GPIO %d interrupt occurred: %s\n", pin, buf); */
			close(polldata.fd);
			gpio->function(&gpio->pin);
		}
	}
	close(polldata.fd);
	pthread_exit(&polldata.fd);
}
