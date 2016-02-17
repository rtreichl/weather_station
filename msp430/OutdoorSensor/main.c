#include <msp430.h> 
#include <driver.h>
#include <extern/communication/cc110l/include/cc110l_config2.h>
#include "protocol.h"

volatile uint8_t second = 0;

void delay_25ms(uint8_t multiple)
{
	second = 0;
	while(second < multiple) {
		__bis_SR_register(LPM3+GIE);
	}

}

uint16_t T1_ISR(uint16_t count);


/*
 * main.c
 */
int main(void) {

	P3OUT &= ~BIT7;
	P3DIR |= BIT7;
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

	// Init SMCLK = MCLk = ACLK = 1MHz
	CSCTL0_H = 0xA5;
	CSCTL1 |= DCOFSEL0 + DCOFSEL1;          // Set max. DCO setting = 8MHz
	CSCTL2 = SELA_3 + SELS_3 + SELM_3;      // set ACLK = MCLK = DCO
	CSCTL3 = DIVA_3 + DIVS_3 + DIVM_3;      // set all dividers to 1MHz
	
	TimerConfig T1_Config = {0};
	T1_Config.divider = 2;
	T1_Config.mode = 3;
	T1_Config.source = 2;

	TimerCCRConfig T1_CCR1_Config = {0};
	T1_CCR1_Config.ccie = 1;

	TimerInit(TimerA0, &T1_Config);
	TimerConfigCCR(TimerA0, CCR0, &T1_CCR1_Config, 3125);
	TimerAttachISR(TimerA0, TimerA0CCR0ISR, T1_ISR);
	__bis_SR_register(GIE);

	delay_25ms(10); //fixed needed for tmp102

	i2c_init(1, 200);
	SPI_init(SPIMODE1);

//	adc_init();
//
//	TMP102_init();
//
//	HDC1000_init();
//
//	LPS25H_init();
//
//	si1147_init();
//
//	max17048_init();

	CC110L_SendCommand(CC110L_COMMAND_SRES);
	delay_25ms(4); //fixed
	//CC110L_ReadStatus();
	CC110L_WriteConfig(CC110L_Config);
	//CC110L_ReadStatus();
	delay_25ms(4); //fixed
	//protocol_send();
	delay_25ms(30); //fixed
	P3OUT |= BIT7;
	delay_25ms(2);
	P3OUT &= ~BIT7;
	__bis_SR_register(LPM3+GIE);        // Enter LPM0 w/ interrupt

	return 0;
}

uint16_t T1_ISR(uint16_t count)
{
  second++;
  TA0CCR0 += 3125;                         // Add Offset to TACCR0
  return TIMER_EXIT_LPM;
}

