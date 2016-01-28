///----------------------------------------------------------------------------------------
///
/// \file hdc1000.h
///
/// \brief 
///
/// \date 07.01.2016
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

#ifndef DRIVER_EXTERN_SENSORS_HDC1000_INCLUDE_HDC1000_H_
#define DRIVER_EXTERN_SENSORS_HDC1000_INCLUDE_HDC1000_H_


//HDC1000 register addresses
#define HDC1000_TEMPERATURE_REG		0x00
#define HDC1000_HUMIDITY_REG		0x01
#define HDC1000_CONFIG_REG			0x02
#define HDC1000_SERIAL_ID_1_REG		0xFB
#define HDC1000_SERIAL_ID_2_REG		0xFC
#define HDC1000_SERIAL_ID_3_REG		0xFD
#define HDC1000_MANF_ID_REG			0xFE
#define HDC1000_DEV_ID_REG			0xFF

//HDC1000 configuration
#define HDC1000_SOFTWARE_RESET		1
#define HDC1000_NORMAL_OPERATION	0
#define HDC1000_HEATER_ON			1
#define HDC1000_HEATER_OFF			0
#define HDC1000_MODE_BOTH			1
#define HDC1000_MODE_SEPARATED		0
#define HDC1000_BAT_VOLT_HIGHER_2V8	0
#define HDC1000_BAT_VOLT_LOWER_2V8	0
#define HDC1000_TEMP_RES_11_BIT		1
#define HDC1000_TEMP_RES_14_BIT		0
#define HDC1000_HUMI_RES_14_BIT		0
#define HDC1000_HUMI_RES_11_BIT		1
#define HDC1000_HUMI_RES_8_BIT		2

typedef struct
{
	uint16_t _res1 : 8;
	uint16_t HRES : 2;
	uint16_t TRES : 1;
	uint16_t BTST : 1;
	uint16_t MODE : 1;
	uint16_t HEAT : 1;
	uint16_t _res2 : 1;
	uint16_t RST : 1;
}HDC1000_Config;

#endif /* DRIVER_EXTERN_SENSORS_HDC1000_INCLUDE_HDC1000_H_ */
