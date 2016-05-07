///----------------------------------------------------------------------------------------
///
/// \file timerA.c
///
/// \brief 
///
/// \date 16.02.2016
///
/// \author Richard Treichl
///
/// \remark
///
/// \todo Implment on, pwm, off state to save resources
///
/// \version	1.0
///
///----------------------------------------------------------------------------------------

#include <driver.h>

#ifdef __MSP430_HAS_T0A3__
#if TIMER_A0 ==  TIMER_ON

timerptrfunc timer_a0_interrupts[4] = {0};

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=TIMER0_A0_VECTOR
__interrupt void TIMER_A0_CCR0(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(TIMER0_A0_VECTOR))) TIMER_A0_CCR0 (void)
#else
#error Compiler not supported!
#endif
{
	uint16_t ret = 0;

	if(timer_a0_interrupts[TimerA0CCR0ISR] != 0) {
		ret = timer_a0_interrupts[TimerA0CCR0ISR](CCR0, TimerA0, TIMER_R(TimerA0));
	}

	if(ret == TIMER_EXIT_LPM) {
		__bic_SR_register_on_exit(CPUOFF);
		return;
	}
	return;
}

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=TIMER0_A1_VECTOR
__interrupt void TIMER_A0_TAIV(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(TIMER0_A1_VECTOR))) TIMER_A0_TAIV (void)
#else
#error Compiler not supported!
#endif
{
	uint16_t ret = 0;

	switch (__even_in_range(TA0IV, 14)) {
	case 0:
		break;                          // No interrupt
	case 2: 	                        // CCR1
		if (timer_a0_interrupts[TimerA0CCR1ISR] != 0) {
			ret = timer_a0_interrupts[TimerA0CCR1ISR](CCR1, TimerA0, TIMER_R(TimerA0));
		}
		break;
	case 4:                          	// CCR2
		if (timer_a0_interrupts[TimerA0CCR2ISR] != 0) {
			ret = timer_a0_interrupts[TimerA0CCR2ISR](CCR2, TimerA0, TIMER_R(TimerA0));
		}
		break;
	case 6:
		break;                          // reserved
	case 8:
		break;                          // reserved
	case 10:
		break;                          // reserved
	case 12:
		break;                          // reserved
	case 14: 			                // overflow
		if (timer_a0_interrupts[TimerA0OVFLISR] != 0) {
			ret = timer_a0_interrupts[TimerA0OVFLISR]((TimerCCR)0xFF, TimerA0, TIMER_R(TimerA0));
		}
		break;
	default:
		break;
	}

	if(ret == TIMER_EXIT_LPM) {
		__bic_SR_register_on_exit(CPUOFF);
		return;
	}
	return;
}

#endif
#endif /* __MSP430_HAS_T0A3__ */

#ifdef __MSP430_HAS_T1A3__
#if TIMER_A1 ==  TIMER_ON
timerptrfunc timer_a1_interrupts[4] = {0};

#pragma vector = TIMER1_A0_VECTOR
__interrupt void TIMER_A1_CCR0(void)
{
	uint16_t ret = 0;

	if(timer_a1_interrupts[TimerA1CCR0ISR] != 0) {
		ret = timer_a1_interrupts[TimerA1CCR0ISR](CCR0, TimerA1, TIMER_R(TimerA1));
	}

	if(ret == TIMER_EXIT_LPM) {
		__bic_SR_register_on_exit(CPUOFF);
		return;
	}
	return;
}

#pragma vector = TIMER1_A1_VECTOR
__interrupt void TIMER_A1_TAIV(void)
{
	uint16_t ret = 0;

	switch (__even_in_range(TA1IV, 14)) {
	case 0:
		break;                          // No interrupt
	case 2: 	                        // CCR1
		if (timer_a1_interrupts[TimerA1CCR1ISR] != 0) {
			ret = timer_a1_interrupts[TimerA1CCR1ISR](CCR1, TimerA1, TIMER_R(TimerA1));
		}
		break;
	case 4:                          	// CCR2
		if (timer_a1_interrupts[TimerA1CCR2ISR] != 0) {
			ret = timer_a1_interrupts[TimerA1CCR2ISR](CCR2, TimerA1, TIMER_R(TimerA1));
		}
		break;
	case 6:
		break;                          // reserved
	case 8:
		break;                          // reserved
	case 10:
		break;                          // reserved
	case 12:
		break;                          // reserved
	case 14: 			                // overflow
		if (timer_a1_interrupts[TimerA1OVFLISR] != 0) {
			ret = timer_a1_interrupts[TimerA1OVFLISR](0xFF, TimerA1, TIMER_R(TimerA1));
		}
		break;
	default:
		break;
	}

	if(ret == TIMER_EXIT_LPM) {
		__bic_SR_register_on_exit(CPUOFF);
		return;
	}
	return;
}

#endif
#endif /* __MSP430_HAS_T1A3__ */
