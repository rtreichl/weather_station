#include <driver.h>

#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

/**
 * @struct I2C_CTRL
 * @brief This struct inclued all necessaries for I2C module.
 */

struct I2C_CTRL {
	int8_t endian;			///< Stores -1 for a little endian system on slave side and a 1 for a big endian system
	uint8_t : 5;
	uint8_t rept_start : 1;		///< Stores the value, if an repated start or stop will be send after performance on I2C.
	uint8_t status : 2;			///< Stores the actual state of I2C module.
	uint8_t *PTxData;			///< Poiniter to be transmitting bytes.
	uint8_t TxByteCtr;			///< Number of to be transmitting bytes.
	uint8_t TxByteRes;			///< Number of reserved bytes on stash.
	uint8_t *PRxData;			///< Pointer to be receiving bytes.
	uint8_t RxByteCtr;			///< Number of to be recieving bytes.
} i2c = { .PTxData = 0, .status = IDLE, .TxByteRes = 0 };


/**
 * @var *PTxData Pointer to reserved data for var args.
 */

#if VARIADIC_IMPLEMENTATION

uint8_t *PTxData = 0 ;

#else

uint8_t PTxData[I2C_MAX_ARGS] = {0};

#endif

uint8_t i2c_init (uint16_t smclk_freq, uint16_t i2c_freq)
{
	/* Reset USCI_B0 */
	UCB0CTLW0 |= UCSWRST;

	/* Assign P1.6 and P1.7 to USIC_B0 */
	P1OUT |= BIT6 + BIT7;
	P1REN |= BIT6 + BIT7;
	P1SEL1 |= BIT6 + BIT7;

	/* USCI_B0 as I2C Master */
	UCB0CTLW0 = UCMST + UCMODE_3 + UCSYNC;

	/* USCI_B0 automatic stop generated */
	UCB0CTLW1 |= UCASTP_2; ///after UCB0TBCNT is reached

	/* Calculate prescaler for USCI_B0 based on SMCLK freq and I2C freq  */
	UCB0BRW = 0x0008;
	//UCB0BRW = (uint16_t)(smclk_freq * 1000) / i2c_freq;

	/* Set SMCLK as clock for USCI_B0 */
	UCB0CTL1 = UCSSEL_2 + UCSWRST;

	/* Enable NACK interrupt */
	UCB0IE |= UCNACKIE;

	/* Resume USCI_B0 to normal operation state */
	UCB0CTL1 &= ~UCSWRST;

	/* Enable gloabl interrupts */
	//__enable_interrupt();

	i2c.status = IDLE;

	return 0;
}

uint8_t i2c_write_var (uint8_t addr, enum I2C_CRTL_CMD rept_start, uint8_t n_args, ...)
{
	/* Wait until all transmitions and receptions done */
	while( i2c.status != IDLE);

#if VARIADIC_IMPLEMENTATION

	/* Reserve size of memory for transmit buffer if buffer is uninitialised*/
	if(PTxData == 0) {
		PTxData = (uint8_t *) malloc(n_args * sizeof(uint8_t));
		i2c.TxByteRes = n_args;
	}
	/* Reserve more memory if actual size not enough */
	else {
		if(i2c.TxByteRes < n_args) {
			PTxData = (uint8_t *) realloc(PTxData, n_args * sizeof(uint8_t));
			i2c.TxByteRes = n_args;
		}
	}

#endif /* VARIADIC_IMPLEMENTATION */

	uint8_t i = 0;
	va_list ap;

	/* Read n_args from function
	 * Copy args to transmit buffer
	 */
	va_start(ap, n_args);
	for(i = 0; i < n_args; i++)
		PTxData[i] = va_arg(ap, uint8_t);
	va_end(ap);

	return i2c_write_arr(addr, rept_start, n_args, PTxData);
}

uint8_t i2c_write_smbus_block(uint8_t addr, const I2C_SMBUS_PACKAGE *smbus)
{
	uint8_t i = 0;
	uint8_t *tmp_ptr = smbus->data;
	PTxData[0] = smbus->reg;
	for(i = 1; i < smbus->n_bytes + 1; i++)
			PTxData[i] = *tmp_ptr++;
	return i2c_write_arr(addr, STOP, smbus->n_bytes + 1, PTxData);
}

uint8_t i2c_read_smbus_block(uint8_t addr, const I2C_SMBUS_PACKAGE *smbus)
{
	PTxData[0] = smbus->reg;
	i2c_write_arr(addr, STOP, 1, PTxData);
	return i2c_read(addr, STOP, I2C_LITTLE_ENDIAN, smbus->n_bytes, smbus->data);
}

uint8_t i2c_write_smbus_byte(uint8_t addr, uint8_t reg, uint8_t byte)
{
	PTxData[0] = reg;
	PTxData[1] = byte;
	return i2c_write_arr(addr, STOP, 2, PTxData);
}

uint8_t i2c_read_smbus_byte(uint8_t addr, uint8_t reg)
{
	uint8_t rx;
	i2c_write_arr(addr, STOP, 1, &reg);
	i2c_read(addr, STOP, I2C_LITTLE_ENDIAN, 1, &rx);
	return rx;
}

uint8_t i2c_write_smbus_word(uint8_t addr, uint8_t reg, uint16_t word)
{
	PTxData[0] = reg;
	memcpy(&PTxData[1], &word, sizeof(uint16_t));
	return i2c_write_arr(addr, STOP, 3, PTxData);
}

uint16_t i2c_read_smbus_word(uint8_t addr, uint8_t reg)
{
	uint16_t rx;
	i2c_write_arr(addr, STOP, 1, &reg);
	i2c_read(addr, STOP, I2C_LITTLE_ENDIAN, 2, &rx);
	return rx;
}

uint8_t i2c_write_arr(uint8_t addr, enum I2C_CRTL_CMD rept_start, uint8_t n_size, const void *TxData)
{
	/* Copy pointer from TxData */
	i2c.PTxData = (uint8_t *)TxData;

	/* Set slave address */
	//UCB0I2CSA = addr;

	i2c.rept_start = rept_start;
	i2c.endian = I2C_LITTLE_ENDIAN;

	UCB0TBCNT = n_size;		    //number of bytes to be received
	UCB0I2CSA  = addr;		    //slave address

	/* Load TX byte counter */
	//i2c.TxByteCtr = n_size;

	i2c.status = TRANSMIT;

	/* Set Transmit Interrupt */
	UCB0IE &= ~UCRXIE;
	UCB0IE |= UCTXIE+UCNACKIE+UCBCNTIE;


	while (UCB0CTL1 & UCTXSTP);           // Ensure stop condition got sent

	/* Send a start condition with write flag */
	UCB0CTL1 |= UCTR + UCTXSTT;

	__bis_SR_register(CPUOFF+GIE);        // Enter LPM0 w/ interrupt

	/* Wait until Transmition is complet */
//	if(rept_start == STOP) {
//		while(UCB0STAT & UCBBUSY);
//	}
//	else {
//		_delay_ten_us(20);
//	}

	i2c.status = IDLE;

	return 0;

}

uint8_t i2c_read (uint8_t addr, enum I2C_CRTL_CMD rept_start, int8_t endian, uint8_t RXBytes, const void *RxData)
{

	i2c.rept_start = rept_start;
	i2c.endian = I2C_LITTLE_ENDIAN;

	UCB0TBCNT = RXBytes;		    //number of bytes to be received
	UCB0I2CSA  = addr;		    //slave address

	/* Set slave address */
	//UCB0I2CSA = addr;

	/* Change pointer to given buffer */
	i2c.PRxData = (uint8_t *)RxData;

	/* Check endian to recalculate pointer adress */
	if(endian == I2C_BIG_ENDIAN) {
		i2c.PRxData += RXBytes;
	}

	/* Load RX counter */
	//i2c.RxByteCtr = RXBytes;

	/* Load TX byte counter */
	//i2c.TxByteCtr = n_size;

	i2c.status = TRANSMIT;

	/* Set Transmit Interrupt */
	UCB0IE &= ~UCTXIE;
	UCB0IE |= UCRXIE+UCNACKIE+UCBCNTIE;

	while (UCB0CTL1 & UCTXSTP);           // Ensure stop condition got sent

	/* Send a start condition with write flag */
	UCB0CTL1 &= ~UCTR;
	UCB0CTL1 |= UCTXSTT;

	__bis_SR_register(CPUOFF+GIE);        // Enter LPM0 w/ interrupt



	i2c.endian = endian;

	i2c.status = RECEIVE;

//	/* Send a start condition with read flag */
//	if ( i2c.RxByteCtr == 1 ) {
//		i2c.RxByteCtr = 0;
//		__disable_interrupt();
//		UCB0CTL1 |= UCTXSTT;
//		while(UCB0CTL1 & UCTXSTT);
//		UCB0CTL1 |= UCTXSTP;
//		__enable_interrupt();
//	}
//	else {
//		i2c.RxByteCtr -= 2;
//		UCB0CTL1 |= UCTXSTT;
//	}
//
//	while(UCB0STAT & UCBBUSY);

	i2c.status = IDLE;

	return 0;
}

uint8_t i2c_write_arr_endian(uint8_t addr, enum I2C_CRTL_CMD rept_start, int8_t endian, uint8_t n_size, const void *TxData)
{
	/* Copy pointer from TxData */
	i2c.PTxData = (uint8_t *)TxData;

	if(endian == I2C_BIG_ENDIAN)
	{
		i2c.PTxData += n_size;
	}

	/* Set slave address */
	UCB0I2CSA = addr;

	/* Set Transmit Interrupt */
	//IE2 = UCB0TXIE;

	i2c.rept_start = rept_start;

	/* Load TX byte counter */
	i2c.TxByteCtr = n_size;

	i2c.status = TRANSMIT;
	i2c.endian = endian;

	/* Send a start condition with write flag */
	UCB0CTL1 |= UCTR + UCTXSTT;

	/* Wait until Transmition is complet */
	if(rept_start == STOP) {
		while(UCB0STAT & UCBBUSY);
	}
	else {
		//_delay_ten_us(20);
	}

	i2c.status = IDLE;

	return 0;

}

uint8_t i2c_get_status()
{
	return i2c.status;
}

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = USCI_B0_VECTOR
__interrupt void USCIB0_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(USCI_B0_VECTOR))) USCIB0_ISR (void)
#else
#error Compiler not supported!
#endif
{

  switch(__even_in_range(UCB0IV,0x1E))

  {
      case 0x00: break; // Vector 0: No interrupts break;
      case 0x02: break; // Vector 2: ALIFG break;
      case 0x04:
                 UCB0CTL1 |= UCTXSTP; // I2C start condition
                 __bic_SR_register_on_exit(CPUOFF); // Exit LPM0
      break; // Vector 4: NACKIFG break;
      case 0x06: break; // Vector 6: STTIFG break;
      case 0x08: break; // Vector 8: STPIFG break;
      case 0x0a: break; // Vector 10: RXIFG3 break;
      case 0x0c: break; // Vector 14: TXIFG3 break;
      case 0x0e: break; // Vector 16: RXIFG2 break;
      case 0x10: break; // Vector 18: TXIFG2 break;
      case 0x12: break; // Vector 20: RXIFG1 break;
      case 0x14: break; // Vector 22: TXIFG1 break;
      case 0x16:
                  *(i2c.PRxData) = UCB0RXBUF;    // Get RX data
                  i2c.PRxData++;
                  break; // Vector 24: RXIFG0 break;
      case 0x18:  UCB0TXBUF = *(i2c.PTxData);    // Get RX data
      	  	  	  i2c.PTxData++;
                  break; // Vector 26: TXIFG0 break;
      case 0x1a:
    	  	  	 __bic_SR_register_on_exit(CPUOFF); // Exit LPM0
                 break; // Vector 28: BCNTIFG break;
      case 0x1c: break; // Vector 30: clock low timeout break;
      case 0x1e: break; // Vector 32: 9th bit break;
      default: break;

  }

}
