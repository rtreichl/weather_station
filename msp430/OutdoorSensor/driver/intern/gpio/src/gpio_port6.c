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

#ifdef PORT6_VECTOR
#if GPIO_PORT6_INTERRUPT == GPIO_INTERRUPT_ON

gpio_ptrfunc gpio6_isrs[8];

#pragma vector = PORT6_VECTOR
__interrupt void Port6_isr(void)
{
	uint8_t i;
	uint8_t pin;
		P6IFG &= P6IE;
		for(i = 0, pin = P6IFG; pin > 0; i++) {
			if(gpio6_isrs[i] != 0 && (pin & 0x01)) {
				gpio6_isrs[i](i);
			}
			pin >>= 1;
		}
		P6IFG = 0;
	_BIC_SR(LPM3_EXIT);
}

#endif
#endif
