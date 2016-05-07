///----------------------------------------------------------------------------------------
///
/// \file lps25h.h
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


#ifndef LPS25H_H_
#define LPS25H_H_

#include <driver.h>
#include "include/lps25h.h"

#define LPS25H_I2C_ADDR 	0x5C
#define LPS25H_IRQ_PORT 	GPIO8_PORT3
#define LPS25H_IRQ_PIN		GPIO_PIN0

uint16_t LPS25H_init();
int16_t LPS25H_ReadTemperature();
int16_t LPS25H_ReadRawTemperature();
uint32_t LPS25H_ReadPressure();
uint32_t LPS25H_ReadRawPressure();
uint16_t LPS25H_OneShot();

#endif /* LPS25H_H_ */
