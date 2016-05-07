///----------------------------------------------------------------------------------------
///
/// \file timer.c
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

#include <library.h>

volatile uint16_t system_timer = 0;

uint16_t SystemTimerISR(TimerCCR ccr, Timer timer, uint16_t count);

uint16_t SystemTimerInit(Timer timer, uint32_t aclk_freq)
{
	TimerConfig TConfig =  {0};
	TConfig.divider = 0;
	TConfig.int_en = 1;
	TConfig.mode =  TIMER_MODE_UP;
	TConfig.source = TIMER_SRC_ACLK;

	TimerCCRConfig TCCRConifg = {0};
	TCCRConifg.ccie = 1;

	TIMER_CCTL(timer, CCR0) = *((uint16_t *)&TCCRConifg);
	TIMER_CCR0(timer) = aclk_freq / 1000;
	TimerAttachISR(timer, TimerA0CCR0ISR,SystemTimerISR);
	TIMER_CTL(timer) = *(uint16_t *)&TConfig;
	__bis_SR_register(GIE);
	return 0;
}

uint16_t SystemTimeGet()
{
	return system_timer;
}

int16_t SystemTimeDiff(uint16_t timer)
{
	return timer - system_timer;
}

uint16_t SystemTimerDelay(uint16_t ms)
{
	ms += system_timer + 1;
	while(ms > system_timer)
	{
		__bis_SR_register(LPM3_bits+GIE);
	}
	return 0;
}

uint16_t SystemTimerISR(TimerCCR ccr, Timer timer, uint16_t count)
{
	system_timer++;
	return TIMER_EXIT_LPM;
}
