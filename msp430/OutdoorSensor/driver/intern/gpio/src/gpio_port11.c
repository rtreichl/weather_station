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

#ifdef PORT11_VECTOR
#if GPIO_PORT11_INTERRUPT == GPIO_INTERRUPT_ON

gpio_ptrfunc gpio11_isrs[8];

#pragma vector = PORT11_VECTOR
__interrupt void Port11_isr(void)
{
	uint11_t i;
	uint11_t pin;
		P11IFG &= P11IE;
		for(i = 0, pin = P11IFG; pin > 0; i++) {
			if(gpio11_isrs[i] != 0 && (pin & 0x01)) {
				gpio11_isrs[i](i);
			}
			pin >>= 1;
		}
		P11IFG = 0;
	_BIC_SR(LPM3_EXIT);
}

#endif
#endif
