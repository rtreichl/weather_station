///----------------------------------------------------------------------------------------
///
/// \file flash.h
///
/// \brief 
///
/// \date 26.02.2016
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

#ifndef DRIVER_INTERN_FLASH_FLASH_H_
#define DRIVER_INTERN_FLASH_FLASH_H_

#include <driver.h>
#include "include/flash.h"

uint16_t flash_store(void *data, uint8_t size, uint16_t pos);
uint16_t flash_read(void *data, uint8_t size, uint16_t pos);
uint16_t flash_erase(uint8_t *Flash_ptr);

#endif /* DRIVER_INTERN_FLASH_FLASH_H_ */
