///----------------------------------------------------------------------------------------
///
/// \file clock.h
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

#ifndef DRIVER_INTERN_CLOCK_CLOCK_H_
#define DRIVER_INTERN_CLOCK_CLOCK_H_

#include "include/clock.h"

uint16_t ClockDCOInit(ClockDCO clock);
uint16_t ClockACLKConfig(ClockSource source, ClockDivider divider);
uint16_t ClockSMCLKConfig(ClockSource source, ClockDivider divider);
uint16_t ClockMCLKConfig(ClockSource source, ClockDivider divider);


#endif /* DRIVER_INTERN_CLOCK_CLOCK_H_ */
