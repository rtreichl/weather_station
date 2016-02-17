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

#ifdef PORT10_VECTOR
#if GPIO_PORT10_INTERRUPT == GPIO_INTERRUPT_ON

gpio_ptrfunc gpio10_isrs[8];

#pragma vector = PORT10_VECTOR
__interrupt void Port10_isr(void)
{
	uint10_t i;
	uint10_t pin;
		P10IFG &= P10IE;
		for(i = 0, pin = P10IFG; pin > 0; i++) {
			if(gpio10_isrs[i] != 0 && (pin & 0x01)) {
				gpio10_isrs[i](i);
			}
			pin >>= 1;
		}
		P10IFG = 0;
	_BIC_SR(LPM3_EXIT);
}

#endif
#endif
