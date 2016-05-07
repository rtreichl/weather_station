///----------------------------------------------------------------------------------------
///
/// \file system.h
///
/// \brief 
///
/// \date 25.02.2016
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

#ifndef LIB_SYSTEM_SYSTEM_H_
#define LIB_SYSTEM_SYSTEM_H_

#define SwapConstInt16(x) ((((x) & 0xff00) >> 8) | (((x) & 0x00ff) << 8))

#define CYCLES_PER_US 8L // depends on the CPU speed
#define CYCLES_PER_MS (CYCLES_PER_US * 1000L)

#define SystemDelayUS(x) __delay_cycles((x * CYCLES_PER_US))

#endif /* LIB_SYSTEM_SYSTEM_H_ */
