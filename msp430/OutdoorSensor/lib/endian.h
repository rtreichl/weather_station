///----------------------------------------------------------------------------------------
///
/// \file endian.h
///
/// \brief 
///
/// \date 31.12.2015
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

#ifndef ENDIAN_H_
#define ENDIAN_H_

#define SwapConstInt16(x) ((((x) & 0xff00) >> 8) | (((x) & 0x00ff) << 8))

inline void SwapEndian(void *val)
{
	uint16_t *tmp = (uint16_t *)val;
	*tmp = ((*tmp & 0x00FF) << 8) | ((*tmp & 0xFF00) >> 8);
}

inline uint16_t swapbytes16(uint16_t val)
{
	return ((val & 0x00FF) << 8) | ((val & 0xFF00) >> 8);
}

inline uint32_t swapbytes32(uint32_t val)
{
	return (((val & 0x000000FF) << 24) | ((val & 0x0000FF00) << 8) | ((val & 0x00FF0000) >> 8) | ((val & 0xFF000000) >> 24));
}

inline uint16_t htole16(uint16_t val)
{
	return val;
}

inline uint16_t htobe16(uint16_t val)
{
	return swapbytes16(val);
}

inline uint16_t letoh16(uint16_t val)
{
	return val;
}

inline uint16_t betoh16(uint16_t val)
{
	return swapbytes16(val);
}

inline uint32_t htole32(uint32_t val)
{
	return val;
}

inline uint32_t htobe32(uint32_t val)
{
	return swapbytes32(val);
}

inline uint32_t letoh32(uint32_t val)
{
	return val;
}

inline uint32_t betoh32(uint32_t val)
{
	return swapbytes32(val);
}

#endif /* ENDIAN_H_ */
