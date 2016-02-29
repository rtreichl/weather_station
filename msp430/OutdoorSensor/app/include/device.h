///----------------------------------------------------------------------------------------
///
/// \file device.h
///
/// \brief 
///
/// \date 29.02.2016
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

#ifndef APP_INCLUDE_DEVICE_H_
#define APP_INCLUDE_DEVICE_H_

uint16_t DeviceGetAddress();
uint16_t DeviceGetExternalHardware();
uint16_t DeviceInitExternalHardware(PROTOCOL_HARDWARE_STC *hw);
uint16_t DeviceInitInternalHardware(PROTOCOL_HARDWARE_STC *hw);
uint16_t DeviceTurnOffinMs(uint16_t ms);

#endif /* APP_INCLUDE_DEVICE_H_ */
