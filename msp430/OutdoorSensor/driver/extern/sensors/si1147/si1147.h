///----------------------------------------------------------------------------------------
///
/// \file si1147.h
///
/// \brief 
///
/// \date 04.01.2016
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

#ifndef SI1147_H_
#define SI1147_H_

#include <driver.h>
#include "include/si1147.h"

#define SI1147_I2C_ADDR				0x60

#define SI1147_STARTUP_TIME 	  2000000

#define SI1147_IRQ_PREN           P1REN
#define SI1147_IRQ_POUT           P1OUT
#define SI1147_IRQ_BIT            BIT0
#define SI1147_IRQ_PDIR			  P1DIR
#define SI1147_IRQ_PIES			  P1IES
#define SI1147_IRQ_NUM			  0

void si1147_init();

uint16_t si1147_ReadRawUV();
uint16_t si1147_ReadRawIR();
uint16_t si1147_ReadRawVisible();

void si1147_single_conv();

#endif /* SI1147_H_ */
