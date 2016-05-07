///----------------------------------------------------------------------------------------
///
/// \file app.h
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

#ifndef APP_APP_H_
#define APP_APP_H_

#include <driver.h>
#include <library.h>
#include "include/protocol.h"

uint16_t application_main();
uint16_t application_init(PROTOCOL_HARDWARE_STC *hw);

#endif /* APP_APP_H_ */
