///----------------------------------------------------------------------------------------
///
/// \file 1wire.h
///
/// \brief 
///
/// \date 16.02.2016
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

#ifndef DRIVER_INTERN_1WIRE_1WIRE_H_
#define DRIVER_INTERN_1WIRE_1WIRE_H_

#include <driver.h>
#include "include/1wire.h"

uint16_t onewire_reset();
void onewire_write_bit(int bit);
uint8_t onewire_read_bit();
void onewire_write_byte(uint8_t byte);
uint8_t onewire_read_byte();
uint16_t onewire_init(GPIO8_PORT port, GPIO_PIN pin);

void onewire_line_low();
void onewire_line_high();
void onewire_line_release();


#endif /* DRIVER_INTERN_1WIRE_1WIRE_H_ */
