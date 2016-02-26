///----------------------------------------------------------------------------------------
///
/// \file 1wire.h
///
/// \brief 
///
/// \date 17.02.2016
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

#ifndef DRIVER_INTERN_1WIRE_INCLUDE_1WIRE_H_
#define DRIVER_INTERN_1WIRE_INCLUDE_1WIRE_H_

typedef struct {
    volatile uint8_t *port_out;
    const volatile uint8_t *port_in;
    volatile uint8_t *port_ren;
    volatile uint8_t *port_dir;
    int pin;
  } onewire_t;

#endif /* DRIVER_INTERN_1WIRE_INCLUDE_1WIRE_H_ */
