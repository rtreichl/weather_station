///----------------------------------------------------------------------------------------
///
/// \file gpio_port1.c
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

#ifdef PORT8_VECTOR
#if GPIO_PORT8_INTERRUPT == GPIO_INTERRUPT_ON

gpio_ptrfunc gpio8_isrs[8];

#pragma vector = PORT8_VECTOR
__interrupt void Port8_isr(void)
{
	uint8_t i;
	uint8_t pin;
		P8IFG &= P8IE;
		for(i = 0, pin = P8IFG; pin > 0; i++) {
			if(gpio8_isrs[i] != 0 && (pin & 0x01)) {
				gpio8_isrs[i](i);
			}
			pin >>= 1;
		}
		P8IFG = 0;
	_BIC_SR(LPM3_EXIT);
}

#endif
#endif
