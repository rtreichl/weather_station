#include <msp430.h> 
#include <driver.h>
#include <extern/communication/cc110l/include/cc110l_config2.h>
#include "protocol.h"
#include <library.h>

/*
 * main.c
 */
int main(void) {

	P3OUT &= ~BIT7;
	P3DIR |= BIT7;
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

    ClockDCOInit(DCOCLK_8M00HZ);
    ClockACLKConfig(SOURCE_DCOCLK, DIVIDE_BY_8);
    ClockSMCLKConfig(SOURCE_DCOCLK, DIVIDE_BY_8);
    ClockMCLKConfig(SOURCE_DCOCLK, DIVIDE_BY_1);

    SystemTimerInit(TimerA0, 1000000ul);

	i2c_init(1, 200);

	SPI_init(SPIMODE1);

	adc_init();

	ds18b20_init(GPIO8_PORT1, GPIO_PIN0);
	ds18b20_StartConversion();

    SystemTimerDelay(250);

	TMP102_init();

	//HDC1000_init();

	LPS25H_init();

	//si1147_init();

	max17048_init();

	CC110L_SendCommand(CC110L_COMMAND_SRES);
	SystemTimerDelay(100);
	CC110L_WriteConfig(CC110L_Config);
	SystemTimerDelay(100);
	protocol_send();
	SystemTimerDelay(750);
	while(1) {
		P3OUT |= BIT7;
		SystemTimerDelay(50);
		P3OUT &= ~BIT7;
	}
}

