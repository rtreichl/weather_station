///----------------------------------------------------------------------------------------
///
/// \file timer.h
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

#ifndef DRIVER_INTERN_TIMER_INCLUDE_TIMER_H_
#define DRIVER_INTERN_TIMER_INCLUDE_TIMER_H_

#include <msp430.h>
#include <stdint.h>

#define TIMER_ON	1
#define TIMER_PWM	2
#define TIMER_OFF	0

typedef enum {
	TIMER_SRC_TACLK = 0,
	TIMER_SRC_ACLK = 1,
	TIMER_SRC_SMCLK = 2,
} TimerSource;

typedef enum {
	TIMER_MODE_STOP = 0,
	TIMER_MODE_UP = 1,
	TIMER_MODE_CONTINUOUS = 2,
	TIMER_MODE_UP_DOWN = 3,
} TimerMode;

typedef enum {
CCR0 = 0x00,
CCR1 = 0x02,
CCR2 = 0x04
} TimerCCR;

typedef enum {
#ifdef __MSP430_HAS_T0A3__
	TimerA0 = TIMER_A0_BASE,
#endif
#ifdef __MSP430_HAS_T1A3__
	TimerA1 = TIMER_A1_BASE,
#endif
#ifdef __MSP430_HAS_T0B3__
	TimerB0 = TIMER_B0_BASE,
#endif
#ifdef __MSP430_HAS_T1B3__
	TimerB1 = TIMER_B1_BASE,
#endif
#ifdef __MSP430_HAS_T2B3__
	TimerB2 = TIMER_B2_BASE,
#endif
} Timer;

typedef struct {
	uint16_t:1;
	uint16_t int_en:1;
	uint16_t:2;
	TimerMode mode:2;
	uint16_t divider:2;
	TimerSource source:2;
	uint16_t:6;
} TimerConfig;

typedef struct {
	uint16_t ccifg:1;
	uint16_t cov:1;
	uint16_t out:1;
	uint16_t cci:1;
	uint16_t ccie:1;
	uint16_t outmod:2;
	uint16_t cap:1;
	uint16_t :1;
	uint16_t scs:1;
	uint16_t ccis:2;
	uint16_t cm:2;
} TimerCCRConfig;

typedef uint16_t (*timerptrfunc)(TimerCCR, Timer, uint16_t);

#define TIMER_CTL(x) 	(*(uint16_t*)(x + 0x00))
#define TIMER_CCTL(x,y) (*(uint16_t*)(x + 0x02 + y))
#define TIMER_CCTL0(x) 	(*(uint16_t*)(x + 0x02))
#define TIMER_CCTL1(x) 	(*(uint16_t*)(x + 0x04))
#define TIMER_CCTL2(x) 	(*(uint16_t*)(x + 0x06))
#define TIMER_CCTL3(x) 	(*(uint16_t*)(x + 0x08))
#define TIMER_CCTL4(x) 	(*(uint16_t*)(x + 0x0A))
#define TIMER_CCTL5(x) 	(*(uint16_t*)(x + 0x0C))
#define TIMER_CCTL6(x) 	(*(uint16_t*)(x + 0x0E))
#define TIMER_R(x) 		(*(uint16_t*)(x + 0x10))
#define TIMER_CCR(x,y) 	(*(uint16_t*)(x + 0x12 + y))
#define TIMER_CCR0(x) 	(*(uint16_t*)(x + 0x12))
#define TIMER_CCR1(x) 	(*(uint16_t*)(x + 0x14))
#define TIMER_CCR2(x) 	(*(uint16_t*)(x + 0x16))
#define TIMER_CCR3(x) 	(*(uint16_t*)(x + 0x18))
#define TIMER_CCR4(x) 	(*(uint16_t*)(x + 0x1A))
#define TIMER_CCR5(x) 	(*(uint16_t*)(x + 0x1C))
#define TIMER_CCR6(x) 	(*(uint16_t*)(x + 0x1E))
#define TIMER_IV(x) 	(*(uint16_t*)(x + 0x2E))
#define TIMER_EX0(x) 	(*(uint16_t*)(x + 0x20))

typedef enum {
	TimerA0OVFLISR = 0,
	TimerA0CCR0ISR = 1,
	TimerA0CCR1ISR = 2,
	TimerA0CCR2ISR = 3,
	TimerA1OVFLISR = 0,
	TimerA1CCR0ISR = 1,
	TimerA1CCR1ISR = 2,
	TimerA1CCR2ISR = 3,
	TimerB0OVFLISR = 0,
	TimerB0CCR0ISR = 1,
	TimerB0CCR1ISR = 2,
	TimerB0CCR2ISR = 3,
	TimerB1OVFLISR = 0,
	TimerB1CCR0ISR = 1,
	TimerB1CCR1ISR = 2,
	TimerB1CCR2ISR = 3,
	TimerB2OVFLISR = 0,
	TimerB2CCR0ISR = 1,
	TimerB2CCR1ISR = 2,
	TimerB2CCR2ISR = 3,
} TimerISR;

#endif /* DRIVER_INTERN_TIMER_INCLUDE_TIMER_H_ */
