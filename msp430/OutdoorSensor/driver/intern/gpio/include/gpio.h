///----------------------------------------------------------------------------------------
///
/// \file gpio.h
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

#ifndef DRIVER_INTERN_GPIO_INCLUDE_GPIO_H_
#define DRIVER_INTERN_GPIO_INCLUDE_GPIO_H_

#include <msp430.h>

#define GPIO_INTERRUPT_ON 1
#define GPIO_INTERRUPT_OFF 0

typedef uint16_t (*gpio_ptrfunc)(uint8_t);

typedef enum {
	GPIO_PIN0 = BIT0,
	GPIO_PIN1 = BIT1,
	GPIO_PIN2 = BIT2,
	GPIO_PIN3 = BIT3,
	GPIO_PIN4 = BIT4,
	GPIO_PIN5 = BIT5,
	GPIO_PIN6 = BIT6,
	GPIO_PIN7 = BIT7,
} GPIO_PIN;

typedef enum {
#ifdef __MSP430_HAS_PORT1_R__
	GPIO8_PORT1 = P1_BASE,
#endif
#ifdef __MSP430_HAS_PORT2_R__
	GPIO8_PORT2 = P2_BASE + 1,
#endif
#ifdef __MSP430_HAS_PORT3_R__
	GPIO8_PORT3 = P3_BASE,
#endif
#ifdef __MSP430_HAS_PORT4_R__
	GPIO8_PORT4 = P4_BASE + 1,
#endif
#ifdef __MSP430_HAS_PORT5_R__
	GPIO8_PORT5 = P5_BASE,
#endif
#ifdef __MSP430_HAS_PORT6_R__
	GPIO8_PORT6 = P6_BASE,
#endif
#ifdef __MSP430_HAS_PORT7_R__
	GPIO8_PORT7 = P7_BASE,
#endif
#ifdef __MSP430_HAS_PORT8_R__
	GPIO8_PORT8 = P8_BASE,
#endif
#ifdef __MSP430_HAS_PORT9_R__
	GPIO8_PORT9 = P9_BASE,
#endif
#ifdef __MSP430_HAS_PORT10_R__
	GPIO8_PORT10 = P10_BASE,
#endif
#ifdef __MSP430_HAS_PORT11_R__
	GPIO8_PORT11 = P11_BASE,
#endif
} GPIO8_PORT;

#define GPIO8_IN(x)		(*(uint8_t *)(x + 0x00))
#define GPIO8_OUT(x) 	(*(uint8_t *)(x + 0x02))
#define GPIO8_DIR(x) 	(*(uint8_t *)(x + 0x04))
#define GPIO8_REN(x) 	(*(uint8_t *)(x + 0x06))
#define GPIO8_SEL0(x) 	(*(uint8_t *)(x + 0x08))
#define GPIO8_SEL1(x) 	(*(uint8_t *)(x + 0x0A))
#define GPIO8_SELC(x) 	(*(uint8_t *)(x + 0x16))
#define GPIO8_IES(x) 	(*(uint8_t *)(x + 0x18))
#define GPIO8_IE(x) 	(*(uint8_t *)(x + 0x1A))
#define GPIO8_IFG(x) 	(*(uint8_t *)(x + 0x1C))

typedef enum {
#ifdef __MSP430_HAS_PORTA_R__
	GPIO16_PORTA = PA_BASE,
#endif
#ifdef __MSP430_HAS_PORTB_R__
	GPIO16_PORTB = PB_BASE,
#endif
#ifdef __MSP430_HAS_PORTC_R__
	GPIO16_PORTC = PC_BASE,
#endif
#ifdef __MSP430_HAS_PORTD_R__
	GPIO16_PORTD = PD_BASE,
#endif
#ifdef __MSP430_HAS_PORTE_R__
	GPIO16_PORTE = PE_BASE,
#endif
#ifdef __MSP430_HAS_PORTF_R__
	GPIO16_PORTF = PF_BASE,
#endif
#ifdef __MSP430_HAS_PORTJ_R__
	GPIO16_PORTJ = PJ_BASE,
#endif
} GPIO16_PORT;

#define GPIO16_IN(x)	(*(uint16_t)(x + 0x00))
#define GPIO16_OUT(x) 	(*(uint16_t)(x + 0x02))
#define GPIO16_DIR(x) 	(*(uint16_t)(x + 0x04))
#define GPIO16_REN(x) 	(*(uint16_t)(x + 0x06))
#define GPIO16_SEL0(x) 	(*(uint16_t)(x + 0x08))
#define GPIO16_SEL1(x) 	(*(uint16_t)(x + 0x0A))
#define GPIO16_SELC(x) 	(*(uint16_t)(x + 0x16))
#define GPIO16_IES(x) 	(*(uint16_t)(x + 0x18))
#define GPIO16_IE(x) 	(*(uint16_t)(x + 0x1A))
#define GPIO16_IFG(x) 	(*(uint16_t)(x + 0x1C))


#endif /* DRIVER_INTERN_GPIO_INCLUDE_GPIO_H_ */
