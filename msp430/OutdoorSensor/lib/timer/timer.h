///----------------------------------------------------------------------------------------
///
/// \file timer.h
///
/// \brief 
///
/// \date 25.02.2016
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

#ifndef LIB_TIMER_TIMER_H_
#define LIB_TIMER_TIMER_H_

#include <library.h>
#include "../../driver/intern/timer/include/timer.h"

uint16_t SystemTimerInit(Timer timer, uint32_t aclk_freq);
uint16_t SystemTimeGet();
int16_t SystemTimeDiff(uint16_t timer);
uint16_t SystemTimerDelay(uint16_t ms);

#endif /* LIB_TIMER_TIMER_H_ */
