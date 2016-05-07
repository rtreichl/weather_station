///----------------------------------------------------------------------------------------
///
/// \file gpio.h
///
/// \brief 
///
/// \date 17.02.2016
///
/// \author Richard Treichl
///
/// \remark
///
/// \todo
///
/// \version	1.0
///
///----------------------------------------------------------------------------------------

#ifndef DRIVER_INTERN_GPIO_GPIO_H_
#define DRIVER_INTERN_GPIO_GPIO_H_

#include "include/gpio.h"

#define GPIO_PORT1_INTERRUPT 	GPIO_INTERRUPT_ON
#define GPIO_PORT2_INTERRUPT 	GPIO_INTERRUPT_OFF
#define GPIO_PORT3_INTERRUPT 	GPIO_INTERRUPT_ON
#define GPIO_PORT4_INTERRUPT 	GPIO_INTERRUPT_OFF
#define GPIO_PORT5_INTERRUPT 	GPIO_INTERRUPT_OFF
#define GPIO_PORT6_INTERRUPT 	GPIO_INTERRUPT_OFF
#define GPIO_PORT7_INTERRUPT 	GPIO_INTERRUPT_OFF
#define GPIO_PORT8_INTERRUPT 	GPIO_INTERRUPT_OFF
#define GPIO_PORT9_INTERRUPT 	GPIO_INTERRUPT_OFF
#define GPIO_PORT10_INTERRUPT 	GPIO_INTERRUPT_OFF
#define GPIO_PORT11_INTERRUPT	GPIO_INTERRUPT_OFF

uint16_t GpioDisableInterupt(GPIO8_PORT port, GPIO_PIN pin);
uint16_t GpioEnableInterupt(GPIO8_PORT port, GPIO_PIN pin);
uint16_t GpioDetachISR(GPIO8_PORT port, GPIO_PIN pin);
uint16_t GpioAttachISR(GPIO8_PORT port, GPIO_PIN pin, gpio_ptrfunc isr);

#endif /* DRIVER_INTERN_GPIO_GPIO_H_ */
