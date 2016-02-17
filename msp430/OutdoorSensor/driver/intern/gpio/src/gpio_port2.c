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

#ifdef PORT2_VECTOR
#if GPIO_PORT2_INTERRUPT == GPIO_INTERRUPT_ON

gpio_ptrfunc gpio2_isrs[8];

#pragma vector = PORT2_VECTOR
__interrupt void Port2_isr(void)
{
	uint8_t i;
	uint8_t pin;
		P2IFG &= P2IE;
		for(i = 0, pin = P2IFG; pin > 0; i++) {
			if(gpio2_isrs[i] != 0 && (pin & 0x01)) {
				gpio2_isrs[i](i);
			}
			pin >>= 1;
		}
		P2IFG = 0;
	_BIC_SR(LPM3_EXIT);
}

#endif
#endif
