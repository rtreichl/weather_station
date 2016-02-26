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
/// \todo
///
/// \version	1.0
///
///----------------------------------------------------------------------------------------

#ifndef DRIVER_INTERN_TIMER_TIMER_H_
#define DRIVER_INTERN_TIMER_TIMER_H_

#include <stdint.h>
#include "include/timer.h"

#define TIMER_A0	TIMER_ON
#define TIMER_A1	TIMER_OFF
#define TIMER_B0	TIMER_OFF
#define TIMER_B1	TIMER_OFF
#define TIMER_B2	TIMER_OFF

#define TIMER_EXIT_LPM	1

void TimerInit(Timer timer, TimerConfig *config);
void TimerAttachISR(Timer timer, TimerISR isr, timerptrfunc isrfnc);
void TimerDetachISR(Timer timer, TimerISR isr);
void TimerConfigCCR(Timer timer, TimerCCR ccr, TimerCCRConfig *config, uint16_t ccr_value);
uint16_t TimerGetCount(Timer timer);
uint16_t TimerSetCCR(Timer timer, TimerCCR ccr, uint16_t ccr_value);

#endif /* DRIVER_INTERN_TIMER_TIMER_H_ */
