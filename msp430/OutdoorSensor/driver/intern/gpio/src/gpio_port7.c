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

#ifdef PORT7_VECTOR
#if GPIO_PORT7_INTERRUPT == GPIO_INTERRUPT_ON

gpio_ptrfunc gpio7_isrs[8];

#pragma vector = PORT7_VECTOR
__interrupt void Port7_isr(void)
{
	uint8_t i;
	uint8_t pin;
		P7IFG &= P7IE;
		for(i = 0, pin = P7IFG; pin > 0; i++) {
			if(gpio7_isrs[i] != 0 && (pin & 0x01)) {
				gpio7_isrs[i](i);
			}
			pin >>= 1;
		}
		P7IFG = 0;
	_BIC_SR(LPM3_EXIT);
}

#endif
#endif
