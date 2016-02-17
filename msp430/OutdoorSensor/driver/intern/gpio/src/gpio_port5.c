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

#ifdef PORT5_VECTOR
#if GPIO_PORT5_INTERRUPT == GPIO_INTERRUPT_ON

gpio_ptrfunc gpio5_isrs[8];

#pragma vector = PORT5_VECTOR
__interrupt void Port5_isr(void)
{
	uint8_t i;
	uint8_t pin;
		P5IFG &= P5IE;
		for(i = 0, pin = P5IFG; pin > 0; i++) {
			if(gpio5_isrs[i] != 0 && (pin & 0x01)) {
				gpio5_isrs[i](i);
			}
			pin >>= 1;
		}
		P5IFG = 0;
	_BIC_SR(LPM3_EXIT);
}

#endif
#endif
