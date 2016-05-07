///----------------------------------------------------------------------------------------
///
/// \file clock.h
///
/// \brief 
///
/// \date 18.02.2016
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

#ifndef DRIVER_INTERN_CLOCK_INCLUDE_CLOCK_H_
#define DRIVER_INTERN_CLOCK_INCLUDE_CLOCK_H_

#ifdef __MSP430_HAS_CS__
typedef enum {
	DCOCLK_5M33HZ = 0,
	DCOCLK_6M67HZ = (DCOFSEL0),
	DCOCLK_8M00HZ = (DCOFSEL0 + DCOFSEL1),
	DCOCLK_16M0HZ = (DCORSEL + DCOFSEL0 + DCOFSEL1),
	DCOCLK_20M0HZ = (DCORSEL + DCOFSEL0),
	DCOCLK_24M0HZ = (DCORSEL+ DCOFSEL0 + DCOFSEL1),
} ClockDCO;
#endif

typedef enum {
	SOURCE_XT1CLK = 0,
	SOURCE_VLOCLK = 1,
	SOURCE_DCOCLK = 3,
	SOURCE_XT2CLK = 5,
} ClockSource;

typedef enum {
	DIVIDE_BY_1 = 0,
	DIVIDE_BY_2 = 1,
	DIVIDE_BY_4 = 2,
	DIVIDE_BY_8 = 3,
	DIVIDE_BY_16 = 4,
	DIVIDE_BY_32 = 5,
} ClockDivider;

#endif /* DRIVER_INTERN_CLOCK_INCLUDE_CLOCK_H_ */
