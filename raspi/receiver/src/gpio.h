/*
 * GPIO.h
 *
 *  Created on: 16.01.2016
 *      Author: Richard Treichl
 */

#include <stdint.h>
#include <pthread.h>

#ifndef GPIO_H_
#define GPIO_H_

static int pinToGpioR2 [64] =
{
  17, 18, 27, 22, 23, 24, 25, 4,	// From the Original Wiki - GPIO 0 through 7:	wpi  0 -  7
   2,  3,				// I2C  - SDA0, SCL0				wpi  8 -  9
   8,  7,				// SPI  - CE1, CE0				wpi 10 - 11
  10,  9, 11, 				// SPI  - MOSI, MISO, SCLK			wpi 12 - 14
  14, 15,				// UART - Tx, Rx				wpi 15 - 16
  28, 29, 30, 31,			// New GPIOs 8 though 11			wpi 17 - 20

// Padding:

                      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,	// ... 31
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,	// ... 47
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,	// ... 63
} ;

class GPIO {
public:
	enum gpio_direction{
		GPIO_IN = 0,
		GPIO_OUT = 1
	};
	enum gpio_pin {
		GPIO0 = 17,
		GPIO1 = 18,
		GPIO2 = 27,
		GPIO3 = 22,
		GPIO4 = 23,
		GPIO5 = 24,
		GPIO6 = 25,
		GPIO7 = 4,
		GPIO8 = 2,
		GPIO9 = 3,
		GPIO10 = 8,
		GPIO11 = 7,
		GPIO12 = 10,
		GPIO13 = 9,
		GPIO14 = 11,
		GPIO15 = 14,
		GPIO16 = 15,
		GPIO17 = 28,
		GPIO18 = 29,
		GPIO19 = 30,
		GPIO20 = 31,
		GPIO21 = 5,
		GPIO22 = 6,
		GPIO23 = 13,
		GPIO24 = 19,
		GPIO25 = 26,
		GPIO26 = 12,
		GPIO27 = 16,
		GPIO28 = 20,
		GPIO29 = 21,
		GPIO30 = 1,
		GPIO31 = 0,
	};
	enum gpio_level {
		GPIO_LOW = 0,
		GPIO_HIGH = 1
	};
	enum gpio_edge {
		GPIO_FALLING_EDGE,
		GPIO_RISING_EDGE,
		GPIO_BOTH_EDGE,
		GPIO_NONE_EDGE
	};
public:
	GPIO(enum gpio_pin pin);
	int GPIODirection(enum gpio_direction dir);
	int GPIORead();
	int GPIOWrite(enum gpio_level level);
	int GPIOEdge(enum gpio_edge edge);
	int GPIOCreateISR(void (*function)(void *), enum gpio_edge edge);
	int GPIODeleteISR();
	int GPIOPullResistor();
	~GPIO();
private:
	pthread_t gpio_thread;
	void (*function)(void*);
	static void *Interrupt(void *arg);
	static bool used_pins[26];
	int pin;
	int edge;
	int direction;

};

#endif /* GPIO_H_ */
