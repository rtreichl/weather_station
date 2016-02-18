///----------------------------------------------------------------------------------------
///
/// \file clock.c
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

#include <driver.h>

uint16_t ClockDCOInit(ClockDCO clock)
{
	// Init SMCLK = MCLk = ACLK = 1MHz
	CSCTL0_H = 0xA5;
	CSCTL1 &= ~(DCORSEL + DCOFSEL0 + DCOFSEL1);       // Set max. DCO setting = 5.33MHz
	CSCTL1 |= clock;    // set all dividers to 1MHz
	return 0;
}

uint16_t ClockACLKConfig(ClockSource source, ClockDivider divider)
{
	CSCTL2 &= ~(0x07 << 8);
	CSCTL3 &= ~(0x07 << 8);
	CSCTL2 |= (source << 8);      // set ACLK = MCLK = DCO
	CSCTL3 |= (divider << 8);
	return 0;
}

uint16_t ClockSMCLKConfig(ClockSource source, ClockDivider divider)
{
	CSCTL2 &= ~(0x07 << 4);
	CSCTL3 &= ~(0x07 << 4);
	CSCTL2 |= (source << 4);      // set ACLK = MCLK = DCO
	CSCTL3 |= (divider << 4);
	return 0;
}

uint16_t ClockMCLKConfig(ClockSource source, ClockDivider divider)
{
	CSCTL2 &= ~(0x07);
	CSCTL3 &= ~(0x07);
	CSCTL2 |= (source);      // set ACLK = MCLK = DCO
	CSCTL3 |= (divider);
	return 0;
}

