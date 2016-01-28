///----------------------------------------------------------------------------------------
///
/// \file hdc1000.h
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

#ifndef HDC1000_H_
#define HDC1000_H_

#include <driver.h>
#include "include/hdc1000.h"

#define HDC1000_I2C_ADDR 0x40

#define HDC1000_INTERRUPT_BIT		BIT2
#define HDC1000_INTERRUPT_PIN		P1IN
#define HDC1000_INTERRUPT_PREN		P1REN
#define HDC1000_INTERRUPT_POUT		P1OUT
#define HDC1000_INTERRUPT_PDIR		P1DIR
#define HDC1000_INTERRUPT_PIES		P1IES
#define HDC1000_INTERRUPT_NUM		2

uint16_t HDC1000_init();
uint16_t HDC1000_ReadHumidity();
uint16_t HDC1000_ReadRawHumidity();
int16_t HDC1000_ReadTemperature();
int16_t HDC1000_ReadRawTemperature();

#endif /* HDC1000_H_ */
