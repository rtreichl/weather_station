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

#ifdef PORT3_VECTOR
#if GPIO_PORT3_INTERRUPT == GPIO_INTERRUPT_ON

gpio_ptrfunc gpio3_isrs[8];

#pragma vector = PORT3_VECTOR
__interrupt void Port3_isr(void)
{
	uint8_t i;
	uint8_t pin;
		P3IFG &= P3IE;
		for(i = 0, pin = P3IFG; pin > 0; i++) {
			if(gpio3_isrs[i] != 0 && (pin & 0x01)) {
				gpio3_isrs[i](i);
			}
			pin >>= 1;
		}
		P3IFG = 0;
	_BIC_SR(LPM3_EXIT);
}

#endif
#endif
