///----------------------------------------------------------------------------------------
///
/// \file si1147.h
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

#ifndef DRIVER_EXTERN_SENSORS_SI1147_INCLUDE_SI1147_H_
#define DRIVER_EXTERN_SENSORS_SI1147_INCLUDE_SI1147_H_

// when set, enables print statements
#define SI1147_DBG 0
#define SI1147_DBG_ALS 0

// bit 6 disables auto incr when set
#define SI1147_AUTO_INCR_DISABLE 0x40
#define SI1147_PS_ENABLE 0x07
#define SI1147_ALS_ENABLE 0xF0
#define SI1147_ALS_VIS_ENABLE 0x10
#define SI1147_ALS_IR_ENABLE 0x20
#define SI1147_UV_ENABLE 0x80
#define SI1147_UVALS_ENABLE 0xB0
#define SI1147_PSALS_ENABLE 0xF7

// measurement rates
#define SI1147_FORCED_CONVERSION 0
#define SI1147_US_PER_MEAS_RATE 31.25

#define SI1147_PART_ID_REG			0x00
#define SI1147_REV_ID_REG			0x01
#define SI1147_SEQ_ID_REG			0x02
#define SI1147_INT_CFG_REG			0x03
#define SI1147_IRQ_ENABLE_REG		0x04
#define SI1147_HW_KEY_REG			0x07
#define SI1147_MEAS_RATE0_REG		0x08
#define SI1147_MEAS_RATE1_REG		0x09
#define SI1147_PS_LED21_REG			0x0F
#define SI1147_PS_LED3_REG			0x10
#define SI1147_UCOEF0_REG			0x13
#define SI1147_UCOEF1_REG			0x14
#define SI1147_UCOEF2_REG			0x15
#define SI1147_UCOEF3_REG			0x16
#define SI1147_PARAM_WR_REG			0x17
#define SI1147_COMMAND_REG			0x18
#define SI1147_RESPONSE_REG			0x20
#define SI1147_IRQ_STATUS_REG		0x21
#define SI1147_ALS_VIS_DATA0_REG	0x22
#define SI1147_ALS_VIS_DATA1_REG	0x23
#define SI1147_ALS_IR_DATA0_REG		0x24
#define SI1147_ALS_IR_DATA1_REG		0x25
#define SI1147_PS1_DATA0_REG		0x26
#define SI1147_PS1_DATA1_REG		0x27
#define SI1147_PS2_DATA0_REG		0x28
#define SI1147_PS2_DATA1_REG		0x29
#define SI1147_PS3_DATA0_REG		0x2A
#define SI1147_PS3_DATA1_REG		0x2B
#define SI1147_AUX_DATA0_REG		0x2C
#define SI1147_AUX_DATA1_REG		0x2D
#define SI1147_UVINDEX0_REG			0x2C
#define SI1147_UVINDEX1_REG			0x2D
#define SI1147_PARAM_RD_REG			0x2E
#define SI1147_CHIP_STAT_REG		0x30
#define SI1147_ANA_IN_KEY_REG		0x3B

// RESPONSE register error codes
#define SI1147_RESPONSE_NO_ERROR              0x00 // [3:0] is counter
#define SI1147_RESPONSE_INVALID_SETTING       0x80
#define SI1147_RESPONSE_PS1_ADC_OVERFLOW      0x88
#define SI1147_RESPONSE_PS2_ADC_OVERFLOW      0x89
#define SI1147_RESPONSE_PS3_ADC_OVERFLOW      0x8A
#define SI1147_RESPONSE_ALS_VIS_ADC_OVERFLOW  0x8C
#define SI1147_RESPONSE_ALS_IR_ADC_OVERFLOW   0x8D
#define SI1147_RESPONSE_AUX_ADC_OVERFLOW      0x8E

// COMMAND register commands
#define SI1147_COMMAND_PARAM_QUERY  0x80 // [4:0] are the parameter bits
#define SI1147_COMMAND_PARAM_SET    0xA0 // [4:0] are the parameter bits
#define SI1147_COMMAND_NOP          0x00
#define SI1147_COMMAND_RESET        0x01
#define SI1147_COMMAND_BUSADDR      0x02
#define SI1147_COMMAND_PS_FORCE     0x05
#define SI1147_COMMAND_GET_CAL      0x12
#define SI1147_COMMAND_ALS_FORCE    0x06
#define SI1147_COMMAND_PSALS_FORCE  0x07
#define SI1147_COMMAND_PS_PAUSE     0x09
#define SI1147_COMMAND_ALS_PAUSE    0x0A
#define SI1147_COMMAND_PSALS_PAUSE  0x0B
#define SI1147_COMMAND_PS_AUTO      0x0D
#define SI1147_COMMAND_ALS_AUTO     0x0E
#define SI1147_COMMAND_PSALS_AUTO   0x0F

// Parameter RAM addresses
#define SI1147_PARAM_I2C_ADDR             0x00
#define SI1147_PARAM_CHLIST               0x01
#define SI1147_PARAM_PSLED12_SELECT       0x02
#define SI1147_PARAM_PSLED3_SELECT        0x03
#define SI1147_PARAM_PS_ENCODING          0x05
#define SI1147_PARAM_ALS_ENCODING         0x06
#define SI1147_PARAM_PS1_ADCMUX           0x07
#define SI1147_PARAM_PS2_ADCMUX           0x08
#define SI1147_PARAM_PS3_ADCMUX           0x09
#define SI1147_PARAM_PS_ADC_COUNTER       0x0A
#define SI1147_PARAM_PS_ADC_GAIN          0x0B
#define SI1147_PARAM_PS_ADC_MISC          0x0C
#define SI1147_PARAM_ALS_IR_ADCMUX        0x0E
#define SI1147_PARAM_AUX_ADCMUX           0x0F
#define SI1147_PARAM_ALS_VIS_ADC_COUNTER  0x10
#define SI1147_PARAM_ALS_VIS_ADC_GAIN     0x11
#define SI1147_PARAM_ALS_VIS_ADC_MISC     0x12
#define SI1147_PARAM_LED_REC              0x1C
#define SI1147_PARAM_ALS_IR_ADC_COUNTER   0x1D
#define SI1147_PARAM_ALS_IR_ADC_GAIN      0x1E
#define SI1147_PARAM_ALS_IR_ADC_MISC      0x1F

#define WAIT_WHILE(cond) \
  do { \
    volatile int8_t i=0; \
    while(cond) i++; \
  } while(0)

#endif /* DRIVER_EXTERN_SENSORS_SI1147_INCLUDE_SI1147_H_ */
