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

#ifdef PORT1_VECTOR
#if GPIO_PORT1_INTERRUPT == GPIO_INTERRUPT_ON

gpio_ptrfunc gpio1_isrs[8] = {0};


#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=PORT1_VECTOR
__interrupt void Port1_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(PORT1_VECTOR))) Port1_ISR (void)
#else
#error Compiler not supported!
#endif
{
	uint8_t i;
	uint8_t pin;
		P1IFG &= P1IE;
		for(i = 0, pin = P1IFG; pin > 0; i++) {
			if(gpio1_isrs[i] != 0 && (pin & 0x01)) {
				gpio1_isrs[i](i);
			}
			pin >>= 1;
		}
		P1IFG = 0;
		_bic_SR_register_on_exit(LPM3_bits);
}

#endif
#endif
