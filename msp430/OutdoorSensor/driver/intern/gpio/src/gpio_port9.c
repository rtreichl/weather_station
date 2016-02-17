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

#ifdef PORT9_VECTOR
#if GPIO_PORT9_INTERRUPT == GPIO_INTERRUPT_ON

gpio_ptrfunc gpio9_isrs[8];

#pragma vector = PORT9_VECTOR
__interrupt void Port9_isr(void)
{
	uint9_t i;
	uint9_t pin;
		P9IFG &= P9IE;
		for(i = 0, pin = P9IFG; pin > 0; i++) {
			if(gpio9_isrs[i] != 0 && (pin & 0x01)) {
				gpio9_isrs[i](i);
			}
			pin >>= 1;
		}
		P9IFG = 0;
	_BIC_SR(LPM3_EXIT);
}

#endif
#endif
