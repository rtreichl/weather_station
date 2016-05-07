///----------------------------------------------------------------------------------------
///
/// \file spi.c
///
/// \brief
///
/// \date 31.12.2015
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

enum SPIOperation {
	SPIRECEIVE,
	SPITRAMSMIT,
	SPITRANSFER,
	SPIIDLE
};

struct SPI_CTRL {
	uint8_t *PTxData;			///< Poiniter to be transmitting bytes.
	int8_t TxnByteCtr;			///< Number of to be transmitting bytes.
	uint8_t *PRxData;			///< Pointer to be receiving bytes.
	int8_t RxnByteCtr;			///< Number of to be receiving bytes.
	enum SPIOperation operate;
} spi = { .PTxData = 0, .PRxData = 0 };

void SPI_enable_interrupt();

int16_t SPI_init(enum SPIMode mode)
{
	P1DIR |= BIT4;
	P1OUT |= BIT4;
	P1SEL1 |= BIT5;
	P2SEL1 |= BIT0 + BIT1;
#ifdef __MSP430_HAS_EUSCI_A0__
	UCA0CTLW0 |= UCSWRST;                     	// **Put state machine in reset**
	UCA0CTLW0 |= UCMST+ UCSYNC + UCMSB;			   		// 3-pin, 8-bit SPI master
	if(mode == SPIMODE0)						// SPI mode 0
		UCA0CTLW0 |= 0;							// Clock polarity low, Clock phase low, MSB
	if(mode == SPIMODE1)						// SPI mode 1
		UCA0CTLW0 |= UCCKPH;					// Clock polarity high, Clock phase low, MSB
	if(mode == SPIMODE2)						// SPI mode 2
			UCA0CTLW0 |= UCCKPL;				// Clock polarity low, Clock phase high, MSB
	if(mode == SPIMODE3)						// SPI mode 3
			UCA0CTLW0 |= UCCKPH | UCCKPL;		// Clock polarity high, Clock phase high, MSB
	UCA0CTLW0 |= UCSSEL_2;                    	// SMCLK
	UCA0BRW = 0x01;                           	// /2
	UCA0MCTLW = 0;                            	// No modulation
	UCA0CTLW0 &= ~UCSWRST;                    	// **Initialize USCI state machine**
	UCA0IE |= UCRXIE;                			// Enable USCI_A0 RX interrupt
#elif defined (__MSP430_HAS_USCI__)
	UCA0CTL1 |= UCSWRST;						// **Put state machine in reset**
	UCA0CTL0 |= UCMSB + UCMST + UCSYNC;			// 3-pin, 8-bit SPI master
	if (mode == SPIMODE0)						// SPI mode 0
		UCA0CTL0 |= 0;							// Clock polarity low, Clock phase low, MSB
	if (mode == SPIMODE1)						// SPI mode 1
		UCA0CTL0 |= UCCKPH;						// Clock polarity high, Clock phase low, MSB
	if (mode == SPIMODE2)						// SPI mode 2
		UCA0CTL0 |= UCCKPL;						// Clock polarity low, Clock phase high, MSB
	if (mode == SPIMODE3)						// SPI mode 3
		UCA0CTL0 |= UCCKPH | UCCKPL;			// Clock polarity high, Clock phase high, MSB
	UCA0CTL1 |= UCSSEL_2;                     	// SMCLK
	UCA0BR0 |= 0x02;                          	// /2
	UCA0BR1 = 0;                              	//
	UCA0MCTL = 0;                             	// No modulation
	UCA0CTL1 &= ~UCSWRST;                  		// **Initialize USCI state machine**
#endif
	//SPI_enable_interrupt();                   	// Enable USCI0 RX interrupt
	spi.operate = SPIIDLE;
	return 0;
}

int16_t SPI_transfer(uint8_t Tx_n_bytes, void *TxBuffer, uint8_t Rx_n_bytes, void *RxBuffer)
{
	spi.PTxData = (uint8_t *)TxBuffer;
	spi.PRxData = (uint8_t *)RxBuffer;
	spi.TxnByteCtr = Tx_n_bytes;
	spi.RxnByteCtr = Rx_n_bytes;
	spi.operate = SPITRANSFER;
	SPI_enable_interrupt();
	__bis_SR_register(CPUOFF + GIE);      // CPU off, enable interrupts
	return 0;
}

int16_t SPI_transmit(uint8_t n_bytes, void *TxBuffer)
{
	spi.PTxData = (uint8_t *)TxBuffer;
	spi.TxnByteCtr = n_bytes;
	spi.RxnByteCtr = 0;
	spi.operate = SPITRAMSMIT;
	SPI_enable_interrupt();
	__bis_SR_register(CPUOFF + GIE);      // CPU off, enable interrupts
	return 0;
}

int16_t SPI_receive(uint8_t n_bytes, void *RxBuffer)
{
	spi.PRxData = (uint8_t *)RxBuffer;
	spi.TxnByteCtr = 0;
	spi.RxnByteCtr = n_bytes;
	spi.operate = SPIRECEIVE;
	SPI_enable_interrupt();
	__bis_SR_register(CPUOFF + GIE);      // CPU off, enable interrupts
	return 0;
}

void SPI_enable_interrupt(){
#ifdef __MSP430_HAS_EUSCI_A0__
	UCA0IE |= UCTXIE;							// Enable USCI0 RX interrupt
#elif defined(__MSP430_HAS_USCI__)
	IE2 |= UCA0RXIE;                         	// Enable USCI0 RX interrupt
#endif
}

#ifdef __MSP430_HAS_USCI__

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCIA0RX_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(USCIAB0RX_VECTOR))) USCIA0RX_ISR (void)
#else
#error Compiler not supported!
#endif
{
	if ((spi.operate == RECEIVE || spi.operate == TRANSFER)
			&& spi.RxnByteCtr > 0) {
		*spi.PRxData = UCA0RXBUF;
		spi.PRxData++;
	} else {
		uint8_t tmp = 0;
		tmp = UCA0RXBUF;
	}
	if (spi.RxnByteCtr == 0 && spi.TxnByteCtr == 0) {
		__bic_SR_register_on_exit(CPUOFF); // Wake up to setup next TX
	}
	while (!(IFG2 & UCA0TXIFG));
//	if (--spi.TxnByteCtr == 0 && --spi.RxnByteCtr == 0) {
//		UCA0IE &= ~UCTXIE;
//	}
	if ((spi.operate == TRAMSMIT || spi.operate == TRANSFER)
			&& spi.TxnByteCtr > 0) {
		UCA0TXBUF = *spi.PTxData;             // Transmit characters
		spi.PTxData++;
	} else {
		UCA0TXBUF = 0;             // Transmit characters
	}
}

#endif /* __MSP430_HAS_USCI__ */

#ifdef __MSP430_HAS_EUSCI_A0__

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(USCI_A0_VECTOR))) USCI_A0_ISR (void)
#else
#error Compiler not supported!
#endif
{
  switch(__even_in_range(UCA0IV,0x04))
  {
    case 0: break;                          // Vector 0 - no interrupt
    case 2:
    	if((spi.operate == SPIRECEIVE || spi.operate == SPITRANSFER) && spi.RxnByteCtr >= 0) {
    		*spi.PRxData = UCA0RXBUF;
    		spi.PRxData++;
    	}
    	else {
    		volatile uint8_t tmp = 0;
    		tmp = UCA0RXBUF;
    		tmp++;
    	}
        if(spi.RxnByteCtr == 0 && spi.TxnByteCtr == 0) {
        	__bic_SR_register_on_exit(CPUOFF); // Wake up to setup next TX
        }
        break;
    case 4:
    	if(spi.RxnByteCtr >= 0) {
    		spi.RxnByteCtr--;
    	}
    	if(spi.TxnByteCtr >= 0) {
    		spi.TxnByteCtr--;
    	}
    	if(spi.TxnByteCtr <= 0 && spi.RxnByteCtr <= 0) {
    		UCA0IE &= ~UCTXIE;
    	}
    	if((spi.operate == SPITRAMSMIT || spi.operate == SPITRANSFER) && spi.TxnByteCtr >= 0) {
    		UCA0TXBUF = *spi.PTxData;             // Transmit characters
    		spi.PTxData++;
    	}
    	else {
    		UCA0TXBUF = 0;             // Transmit characters
    	}
    	break;
    default: break;
  }
}

#endif /* __MSP430_HAS_EUSCI_A0__ */
