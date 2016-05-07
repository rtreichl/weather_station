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

#ifndef LIB_SYSTEM_H_
#define LIB_SYSTEM_H_

#include "include/delay.h"
#include "include/system.h"
#include "include/endian.h"

inline void SwapEndian(void *val);
inline uint16_t swapbytes16(uint16_t val);
inline uint32_t swapbytes32(uint32_t val);
inline uint16_t htole16(uint16_t val);
inline uint16_t htobe16(uint16_t val);
inline uint16_t letoh16(uint16_t val);
inline uint16_t betoh16(uint16_t val);
inline uint32_t htole32(uint32_t val);
inline uint32_t htobe32(uint32_t val);
inline uint32_t letoh32(uint32_t val);
inline uint32_t betoh32(uint32_t val);


#endif /* LIB_SYSTEM_SYSTEM_H_ */
