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
	
	TA0CCTL0 = CCIE;                          // TACCR0 interrupt enabled
	TA0CCR0 = 3125;
	TA0CTL = TASSEL_1 + ID_3 + MC_2;                 // SMCLK, continuous mode div 8
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

// Timer A0 interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(TIMER0_A0_VECTOR))) Timer_A (void)
#else
#error Compiler not supported!
#endif
{
  second++;
  TA0CCR0 += 3125;                         // Add Offset to TACCR0
  __bic_SR_register_on_exit(CPUOFF);
}

