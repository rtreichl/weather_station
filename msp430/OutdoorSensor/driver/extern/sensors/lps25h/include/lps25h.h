///----------------------------------------------------------------------------------------
///
/// \file lps25h.h
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

#ifndef DRIVER_EXTERN_SENSORS_LPS25H_INCLUDE_LPS25H_H_
#define DRIVER_EXTERN_SENSORS_LPS25H_INCLUDE_LPS25H_H_

#define LPS25H_REF_P_XL_REG			0x08
#define LPS25H_REF_P_L_REG			0x09
#define LPS25H_REF_P_H_REG			0x0A
#define LPS25H_WHO_AM_I_REG			0x0F
#define LPS25H_RES_CONF_REG			0x10
#define LPS25H_CTRL1_REG			0x20
#define LPS25H_CTRL2_REG			0x21
#define LPS25H_CTRL3_REG			0x22
#define LPS25H_CTRL4_REG			0x23
#define LPS25H_INT_CFG_REG			0x24
#define LPS25H_INT_SOURCE_REG		0x25
#define LPS25H_STATUS_REG			0x27
#define LPS25H_PRESS_OUT_XL_REG		0x28
#define LPS25H_PRESS_OUT_L_REG		0x29
#define LPS25H_PRESS_OUT_H_REG		0x2A
#define LPS25H_TEMP_OUT_L_REG		0x2B
#define LPS25H_TEMP_OUT_H_REG		0x2C
#define LPS25H_FIFO_CTRL_REG		0x2E
#define LPS25H_FIFO_STATUS_REG		0x2F
#define LPS25H_THS_P_L_REG			0x30
#define LPS25H_THS_P_H_REG			0x31
#define LPS25H_RPDS_L_REG			0x39
#define LPS25H_RPDS_H_REG			0x3A

#define LPS25H_INCREMENT_REG(x)		(0x80 | x)


#endif /* DRIVER_EXTERN_SENSORS_LPS25H_INCLUDE_LPS25H_H_ */
