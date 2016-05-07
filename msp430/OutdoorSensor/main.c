/*
 * main.c
 */

#include "app/app.h"

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog time;

    ClockDCOInit(DCOCLK_8M00HZ);
    ClockACLKConfig(SOURCE_DCOCLK, DIVIDE_BY_8);
    ClockSMCLKConfig(SOURCE_DCOCLK, DIVIDE_BY_8);
    ClockMCLKConfig(SOURCE_DCOCLK, DIVIDE_BY_1);
    SystemTimerInit(TimerA0, 1000000ul);

    while(1) {
    	application_main();
    }
}

