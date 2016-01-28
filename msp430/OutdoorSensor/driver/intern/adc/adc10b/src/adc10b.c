///----------------------------------------------------------------------------------------
///
/// \file adc10b.c
///
/// \brief 
///
/// \date 26.01.2016
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

#include <driver.h>

volatile uint16_t ADC_Result;

void adc_init()
{
	ADC10CTL0 |= ADC10SHT_2 + ADC10ON;     		// ADC10ON, S&H=16 ADC clks
	ADC10CTL1 |= ADC10SHP;                 		// ADCCLK = MODOSC; sampling timer
	ADC10CTL2 |= ADC10RES;                 		// 10-bit conversion results
	ADC10MCTL0 |= ADC10INCH_6 + ADC10SREF_1;	// A1 ADC input select; Vref=1.5V
	adc_internal_ref();
	ADC10IE |= ADC10IE0;                   		// Enable ADC conv complete interrupt
}

void adc_internal_ref()
{
	// By default, REFMSTR=1 => REFCTL is used to configure the internal reference
	while (REFCTL0 & REFGENBUSY); 				// If ref generator busy, WAIT
	REFCTL0 |= REFVSEL_0 + REFON;               // Select internal ref = 1.5V
}

uint16_t adc_getResult()
{
	ADC10CTL0 |= ADC10ENC + ADC10SC;        // Sampling and conversion start
	__bis_SR_register(CPUOFF + GIE);        // LPM0, ADC10_ISR will force exit
	return ADC_Result;
}

// ADC10 interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(ADC10_VECTOR))) ADC10_ISR (void)
#else
#error Compiler not supported!
#endif
{
  switch(__even_in_range(ADC10IV,12))
  {
    case  0: break;                          // No interrupt
    case  2: break;                          // conversion result overflow
    case  4: break;                          // conversion time overflow
    case  6: break;                          // ADC10HI
    case  8: break;                          // ADC10LO
    case 10: break;                          // ADC10IN
    case 12: ADC_Result = ADC10MEM0;
             __bic_SR_register_on_exit(CPUOFF);
             break;                          // Clear CPUOFF bit from 0(SR)
    default: break;
  }
}
