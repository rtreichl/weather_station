///----------------------------------------------------------------------------------------
///
/// \file adc10b.h
///
/// \brief 
///
/// \date 26.01.2016
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

#ifndef DRIVER_INTERN_ADC_ADC10B_ADC10B_H_
#define DRIVER_INTERN_ADC_ADC10B_ADC10B_H_

#include <stdint.h>

void adc_init();
void adc_internal_ref();
uint16_t adc_getResult();

#endif /* DRIVER_INTERN_ADC_ADC10B_ADC10B_H_ */
