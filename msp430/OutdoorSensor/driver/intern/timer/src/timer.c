///----------------------------------------------------------------------------------------
///
/// \file timer.c
///
/// \brief 
///
/// \date 16.02.2016
///
/// \author Richard Treichl
///
/// \remark
///
/// \todo	Implment on, pwm, off state to save resources
///
/// \version	1.0
///
///----------------------------------------------------------------------------------------

#include <driver.h>

#ifdef __MSP430_HAS_T0A3__
#if TIMER_A0 ==  TIMER_ON
extern timerptrfunc timer_a0_interrupts[];
#endif
#endif

#ifdef __MSP430_HAS_T1A3__
#if TIMER_A1 ==  TIMER_ON
extern timerptrfunc timer_a1_interrupts[];
#endif
#endif

#ifdef __MSP430_HAS_T0B3__
#if TIMER_B0 ==  TIMER_ON
extern timerptrfunc timer_b0_interrupts[];
#endif
#endif

#ifdef __MSP430_HAS_T1B3__
#if TIMER_B1 ==  TIMER_ON
extern timerptrfunc timer_b1_interrupts[];
#endif
#endif

#ifdef __MSP430_HAS_T2B3__
#if TIMER_B2 ==  TIMER_ON
extern timerptrfunc timer_b2_interrupts[];
#endif
#endif

void TimerInit(Timer timer, TimerConfig *config)
{
	TIMER_CTL(timer) = *(uint16_t *)config;
	return;
}

void TimerConfigCCR(Timer timer, TimerCCR ccr, TimerCCRConfig *config, uint16_t ccr_value)
{
	TIMER_CCTL(timer, ccr) = *(uint16_t *)config;
	TIMER_CCR(timer, ccr) = ccr_value;
	return;
}

void TimerAttachISR(Timer timer, TimerISR isr, timerptrfunc isrfnc)
{
	switch(timer) {
#ifdef __MSP430_HAS_T0A3__
#if TIMER_A0 ==  TIMER_ON
	case TimerA0:
		timer_a0_interrupts[isr] = isrfnc;
		break;
#endif
#endif
#ifdef __MSP430_HAS_T1A3__
#if TIMER_A1 ==  TIMER_ON
	case TimerA1:
		timer_a1_interrupts[isr] = isrfnc;
		break;
#endif
#endif
#ifdef __MSP430_HAS_T0B3__
#if TIMER_B0 ==  TIMER_ON
	case TimerB0:
		timer_b0_interrupts[isr] = isrfnc;
		break;
#endif
#endif
#ifdef __MSP430_HAS_T1B3__
#if TIMER_B1 ==  TIMER_ON
	case TimerB1:
		timer_b1_interrupts[isr] = isrfnc;
		break;
#endif
#endif
#ifdef __MSP430_HAS_T2B3__
#if TIMER_B2 ==  TIMER_ON
	case TimerB2:
		timer_b2_interrupts[isr] = isrfnc;
		break;
#endif
#endif
	}
	return;
}

void TimerDetachISR(Timer timer, TimerISR isr)
{
	switch(timer) {
#ifdef __MSP430_HAS_T0A3__
#if TIMER_A0 ==  TIMER_ON
	case TimerA0:
		timer_a0_interrupts[isr] = 0;
		break;
#endif
#endif
#ifdef __MSP430_HAS_T1A3__
#if TIMER_A1 ==  TIMER_ON
	case TimerA1:
		timer_a1_interrupts[isr] = 0;
		break;
#endif
#endif
#ifdef __MSP430_HAS_T0B3__
#if TIMER_B0 ==  TIMER_ON
	case TimerB0:
		timer_b0_interrupts[isr] = 0;
		break;
#endif
#endif
#ifdef __MSP430_HAS_T1B3__
#if TIMER_B1 ==  TIMER_ON
	case TimerB1:
		timer_b1_interrupts[isr] = 0;
		break;
#endif
#endif
#ifdef __MSP430_HAS_T2B3__
#if TIMER_B2 ==  TIMER_ON
	case TimerB2:
		timer_b2_interrupts[isr] = 0;
		break;
#endif
#endif
	}
	return;
}

uint16_t TimerGetCount(Timer timer)
{
	return TIMER_R(timer);
}

