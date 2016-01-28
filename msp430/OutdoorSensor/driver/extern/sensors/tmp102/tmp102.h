///----------------------------------------------------------------------------------------
///
/// \file tmp102.h
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

#ifndef TMP102_H_
#define TMP102_H_

#include <driver.h>
#include "include/tmp102.h"

#define TMP102_INTERRUPT_BIT		BIT1
#define TMP102_INTERRUPT_PIN		P1IN
#define TMP102_INTERRUPT_PREN		P1REN
#define TMP102_INTERRUPT_POUT		P1OUT
#define TMP102_INTERRUPT_PIES		P1IES
#define TMP102_INTERRUPT_NUM		1

#define TMP102_I2C_ADDR 0x48

int16_t TMP102_ReadRawTemperature();
int16_t TMP102_ReadTemperature();
uint16_t TMP102_init();

#endif /* TMP102_H_ */
