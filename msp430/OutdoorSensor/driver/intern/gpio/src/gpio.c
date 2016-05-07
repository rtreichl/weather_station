///----------------------------------------------------------------------------------------
///
/// \file gpio.c
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

#include <driver.h>
#include "../include/gpio.h"

#ifdef __MSP430_HAS_PORT1_R__
#if GPIO_PORT1_INTERRUPT == GPIO_INTERRUPT_ON
	extern gpio_ptrfunc gpio1_isrs[];
#endif
#endif
#ifdef __MSP430_HAS_PORT2_R__
#if GPIO_PORT2_INTERRUPT == GPIO_INTERRUPT_ON
	extern gpio_ptrfunc gpio2_isrs[];
#endif
#endif
#ifdef __MSP430_HAS_PORT3_R__
#if GPIO_PORT3_INTERRUPT == GPIO_INTERRUPT_ON
	extern gpio_ptrfunc gpio3_isrs[];
#endif
#endif
#ifdef __MSP430_HAS_PORT4_R__
#if GPIO_PORT4_INTERRUPT == GPIO_INTERRUPT_ON
	extern gpio_ptrfunc gpio4_isrs[];
#endif
#endif
#ifdef __MSP430_HAS_PORT5_R__
#if GPIO_PORT5_INTERRUPT == GPIO_INTERRUPT_ON
	extern gpio_ptrfunc gpio5_isrs[];
#endif
#endif
#ifdef __MSP430_HAS_PORT6_R__
#if GPIO_PORT6_INTERRUPT == GPIO_INTERRUPT_ON
	extern gpio_ptrfunc gpio6_isrs[];
#endif
#endif
#ifdef __MSP430_HAS_PORT7_R__
#if GPIO_PORT7_INTERRUPT == GPIO_INTERRUPT_ON
	extern gpio_ptrfunc gpio7_isrs[];
#endif
#endif
#ifdef __MSP430_HAS_PORT8_R__
#if GPIO_PORT8_INTERRUPT == GPIO_INTERRUPT_ON
	extern gpio_ptrfunc gpio8_isrs[];
#endif
#endif
#ifdef __MSP430_HAS_PORT9_R__
#if GPIO_PORT9_INTERRUPT == GPIO_INTERRUPT_ON
	extern gpio_ptrfunc gpio9_isrs[];
#endif
#endif
#ifdef __MSP430_HAS_PORT10_R__
#if GPIO_PORT10_INTERRUPT == GPIO_INTERRUPT_ON
	extern gpio_ptrfunc gpio10_isrs[];
#endif
#endif
#ifdef __MSP430_HAS_PORT11_R__
#if GPIO_PORT11_INTERRUPT == GPIO_INTERRUPT_ON
	extern gpio_ptrfunc gpio11_isrs[];
#endif
#endif

uint16_t GpioAttachISR(GPIO8_PORT port, GPIO_PIN pin, gpio_ptrfunc isr)
{
	uint8_t tmp_pin = 0;
	uint8_t pin_cpy = pin;

	while(pin_cpy >>= 1) {
		tmp_pin++;
	}

	switch(port) {
#ifdef __MSP430_HAS_PORT1_R__
#if GPIO_PORT1_INTERRUPT == GPIO_INTERRUPT_ON
	case GPIO8_PORT1:
		gpio1_isrs[tmp_pin] = isr;
		break;
#endif
#endif
#ifdef __MSP430_HAS_PORT2_R__
#if GPIO_PORT2_INTERRUPT == GPIO_INTERRUPT_ON
	case GPIO8_PORT2:
		gpio2_isrs[tmp_pin] = isr;
		break;
#endif
#endif
#ifdef __MSP430_HAS_PORT3_R__
#if GPIO_PORT3_INTERRUPT == GPIO_INTERRUPT_ON
	case GPIO8_PORT3:
		gpio3_isrs[tmp_pin] = isr;
		break;
#endif
#endif
#ifdef __MSP430_HAS_PORT4_R__
#if GPIO_PORT4_INTERRUPT == GPIO_INTERRUPT_ON
	case GPIO8_PORT4:
		gpio4_isrs[tmp_pin] = isr;
		break;
#endif
#endif
#ifdef __MSP430_HAS_PORT5_R__
#if GPIO_PORT5_INTERRUPT == GPIO_INTERRUPT_ON
	case GPIO8_PORT5:
		gpio5_isrs[tmp_pin] = isr;
		break;
#endif
#endif
#ifdef __MSP430_HAS_PORT6_R__
#if GPIO_PORT6_INTERRUPT == GPIO_INTERRUPT_ON
	case GPIO8_PORT6:
		gpio6_isrs[tmp_pin] = isr;
		break;
#endif
#endif
#ifdef __MSP430_HAS_PORT7_R__
#if GPIO_PORT7_INTERRUPT == GPIO_INTERRUPT_ON
	case GPIO8_PORT7:
		gpio7_isrs[tmp_pin] = isr;
		break;
#endif
#endif
#ifdef __MSP430_HAS_PORT8_R__
#if GPIO_PORT8_INTERRUPT == GPIO_INTERRUPT_ON
	case GPIO8_PORT8:
		gpio8_isrs[tmp_pin] = isr;
		break;
#endif
#endif
#ifdef __MSP430_HAS_PORT9_R__
#if GPIO_PORT9_INTERRUPT == GPIO_INTERRUPT_ON
	case GPIO8_PORT9:
		gpio9_isrs[tmp_pin] = isr;
		break;
#endif
#endif
#ifdef __MSP430_HAS_PORT10_R__
#if GPIO_PORT10_INTERRUPT == GPIO_INTERRUPT_ON
	case GPIO8_PORT10:
		gpio10_isrs[tmp_pin] = isr;
		break;
#endif
#endif
#ifdef __MSP430_HAS_PORT11_R__
#if GPIO_PORT11_INTERRUPT == GPIO_INTERRUPT_ON
	case GPIO8_PORT11:
		gpio11_isrs[tmp_pin] = isr;
		break;
#endif
#endif
	default:
		break;
	}

	return 0;
}

uint16_t GpioDetachISR(GPIO8_PORT port, GPIO_PIN pin)
{
	uint8_t tmp_pin = 0;
	uint8_t pin_cpy = pin;

	while(pin_cpy >>= 1) {
		tmp_pin++;
	}

	switch(port) {
#ifdef __MSP430_HAS_PORT1_R__
#if GPIO_PORT1_INTERRUPT == GPIO_INTERRUPT_ON
	case GPIO8_PORT1:
		gpio1_isrs[tmp_pin] = 0;
		break;
#endif
#endif
#ifdef __MSP430_HAS_PORT2_R__
#if GPIO_PORT2_INTERRUPT == GPIO_INTERRUPT_ON
	case GPIO8_PORT2:
		gpio2_isrs[tmp_pin] = 0;
		break;
#endif
#endif
#ifdef __MSP430_HAS_PORT3_R__
#if GPIO_PORT3_INTERRUPT == GPIO_INTERRUPT_ON
	case GPIO8_PORT3:
		gpio3_isrs[tmp_pin] = 0;
		break;
#endif
#endif
#ifdef __MSP430_HAS_PORT4_R__
#if GPIO_PORT4_INTERRUPT == GPIO_INTERRUPT_ON
	case GPIO8_PORT4:
		gpio4_isrs[tmp_pin] = 0;
		break;
#endif
#endif
#ifdef __MSP430_HAS_PORT5_R__
#if GPIO_PORT5_INTERRUPT == GPIO_INTERRUPT_ON
	case GPIO8_PORT5:
		gpio5_isrs[tmp_pin] = 0;
		break;
#endif
#endif
#ifdef __MSP430_HAS_PORT6_R__
#if GPIO_PORT6_INTERRUPT == GPIO_INTERRUPT_ON
	case GPIO8_PORT6:
		gpio6_isrs[tmp_pin] = 0;
		break;
#endif
#endif
#ifdef __MSP430_HAS_PORT7_R__
#if GPIO_PORT7_INTERRUPT == GPIO_INTERRUPT_ON
	case GPIO8_PORT7:
		gpio7_isrs[tmp_pin] = 0;
		break;
#endif
#endif
#ifdef __MSP430_HAS_PORT8_R__
#if GPIO_PORT8_INTERRUPT == GPIO_INTERRUPT_ON
	case GPIO8_PORT8:
		gpio8_isrs[tmp_pin] = 0;
		break;
#endif
#endif
#ifdef __MSP430_HAS_PORT9_R__
#if GPIO_PORT9_INTERRUPT == GPIO_INTERRUPT_ON
	case GPIO8_PORT9:
		gpio9_isrs[tmp_pin] = 0;
		break;
#endif
#endif
#ifdef __MSP430_HAS_PORT10_R__
#if GPIO_PORT10_INTERRUPT == GPIO_INTERRUPT_ON
	case GPIO8_PORT10:
		gpio10_isrs[tmp_pin] = 0;
		break;
#endif
#endif
#ifdef __MSP430_HAS_PORT11_R__
#if GPIO_PORT11_INTERRUPT == GPIO_INTERRUPT_ON
	case GPIO8_PORT11:
		gpio11_isrs[tmp_pin] = 0;
		break;
#endif
#endif
	default:
		break;
	}
	return 0;
}

uint16_t GpioEnableInterupt(GPIO8_PORT port, GPIO_PIN pin)
{
	GPIO8_IFG(port) &= ~pin;
	GPIO8_IE(port) |= pin;
	return 0;
}

uint16_t GpioDisableInterupt(GPIO8_PORT port, GPIO_PIN pin)
{
	GPIO8_IE(port) &= ~pin;
	return 0;
}

