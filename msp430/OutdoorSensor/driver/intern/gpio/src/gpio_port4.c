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

#ifdef PORT4_VECTOR
#if GPIO_PORT4_INTERRUPT == GPIO_INTERRUPT_ON

gpio_ptrfunc gpio4_isrs[8];

#pragma vector = PORT4_VECTOR
__interrupt void Port4_isr(void)
{
	uint8_t i;
	uint8_t pin;
		P4IFG &= P4IE;
		for(i = 0, pin = P4IFG; pin > 0; i++) {
			if(gpio4_isrs[i] != 0 && (pin & 0x01)) {
				gpio4_isrs[i](i);
			}
			pin >>= 1;
		}
		P4IFG = 0;
	_BIC_SR(LPM3_EXIT);
}

#endif
#endif
