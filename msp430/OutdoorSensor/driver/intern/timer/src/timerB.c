///----------------------------------------------------------------------------------------
///
/// \file timerB.c
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

#ifdef __MSP430_HAS_T0B3__
#if TIMER_B0 ==  TIMER_ON

timerptrfunc timer_b0_interrupts[4] = {0};

#pragma vector = TIMER0_B0_VECTOR
__interrupt void TIMER_B0_CCR0(void)
{
	uint16_t ret = 0;

	if(timer_b0_interrupts[TimerB0CCR0ISR] != 0) {
		ret = timer_b0_interrupts[TimerB0CCR0ISR](CCR0, TimerB0, TIMER_R(TimerB0));
	}


	if(ret == TIMER_EXIT_LPM) {
		__bic_SR_register_on_exit(CPUOFF);
		return;
	}
	return;
}

#pragma vector = TIMER0_B1_VECTOR
__interrupt void TIMER_B0_TAIV(void)
{
	uint16_t ret = 0;

	switch (__even_in_range(TB0IV, 14)) {
	case 0:
		break;                          // No interrupt
	case 2: 	                        // CCR1
		if (timer_b0_interrupts[TimerB0CCR1ISR] != 0) {
			ret = timer_b0_interrupts[TimerB0CCR1ISR](CCR1, TimerB0, TIMER_R(TimerB0));
		}
		break;
	case 4:                          	// CCR2
		if (timer_b0_interrupts[TimerB0CCR2ISR] != 0) {
			ret = timer_b0_interrupts[TimerB0CCR2ISR](CCR2, TimerB0, TIMER_R(TimerB0));
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
		if (timer_b0_interrupts[TimerB0OVFLISR] != 0) {
			ret = timer_b0_interrupts[TimerB0OVFLISR](0xFF, TimerB0, TIMER_R(TimerB0));
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
#endif /* __MSP430_HAS_T0B3__ */

#ifdef __MSP430_HAS_T1B3__
#if TIMER_B1 ==  TIMER_ON

timerptrfunc timer_b1_interrupts[4] = {0};

#pragma vector = TIMER1_B0_VECTOR
__interrupt void TIMER_B1_CCR0(void)
{
	uint16_t ret = 0;

	if(timer_b1_interrupts[TimerB1CCR0ISR] != 0) {
		ret = timer_b1_interrupts[TimerB1CCR0ISR](CCR0, TimerB1, TIMER_R(TimerB1));
	}

	if(ret == TIMER_EXIT_LPM) {
		__bic_SR_register_on_exit(CPUOFF);
		return;
	}
	return;
}

#pragma vector = TIMER1_B1_VECTOR
__interrupt void TIMER_B2_TAIV(void)
{
	uint16_t ret = 0;

	switch (__even_in_range(TB1IV, 14)) {
	case 0:
		break;                          // No interrupt
	case 2: 	                        // CCR1
		if (timer_b1_interrupts[TimerB1CCR1ISR] != 0) {
			ret = timer_b1_interrupts[TimerB1CCR1ISR](CCR1, TimerB1, TIMER_R(TimerB1));
		}
		break;
	case 4:                          	// CCR2
		if (timer_b1_interrupts[TimerB1CCR2ISR] != 0) {
			ret = timer_b1_interrupts[TimerB1CCR2ISR](CCR2, TimerB1, TIMER_R(TimerB1));
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
		if (timer_b1_interrupts[TimerB1OVFLISR] != 0) {
			ret = timer_b1_interrupts[TimerB1OVFLISR](0xFF, TimerB1, TIMER_R(TimerB1));
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
#endif /* __MSP430_HAS_T1B3__ */

#ifdef __MSP430_HAS_T2B3__
#if TIMER_B2 ==  TIMER_ON

timerptrfunc timer_b2_interrupts[4] = {0};

#pragma vector = TIMER2_B0_VECTOR
__interrupt void TIMER_B2_CCR0(void)
{
	uint16_t ret = 0;

	if(timer_b2_interrupts[TimerB2CCR0ISR] != 0) {
		ret = timer_b2_interrupts[TimerB2CCR0ISR](CCR0, TimerB2, TIMER_R(TimerB2));
	}

	if(ret == TIMER_EXIT_LPM) {
		__bic_SR_register_on_exit(CPUOFF);
		return;
	}
	return;
}

#pragma vector = TIMER2_B1_VECTOR
__interrupt void TIMER_B1_TAIV(void)
{
	uint16_t ret = 0;

	switch (__even_in_range(TB2IV, 14)) {
	case 0:
		break;                          // No interrupt
	case 2: 	                        // CCR1
		if (timer_b2_interrupts[TimerB2CCR1ISR] != 0) {
			ret = timer_b2_interrupts[TimerB2CCR1ISR](CCR1, TimerB2, TIMER_R(TimerB2));
		}
		break;
	case 4:                          	// CCR2
		if (timer_b2_interrupts[TimerB2CCR2ISR] != 0) {
			ret = timer_b2_interrupts[TimerB2CCR2ISR](CCR2, TimerB2, TIMER_R(TimerB2));
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
		if (timer_b2_interrupts[TimerB2OVFLISR] != 0) {
			ret = timer_b2_interrupts[TimerB2OVFLISR](0xFF, TimerB2, TIMER_R(TimerB2));
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
#endif /* __MSP430_HAS_T2B3__ */
