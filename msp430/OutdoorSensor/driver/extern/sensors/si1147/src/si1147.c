///----------------------------------------------------------------------------------------
///
/// \file si1147.c
///
/// \brief 
///
/// \date 04.01.2016
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

//TODO Rework Interrupthandling

#include <driver.h>

void si1147_write_reg(uint8_t reg_addr, uint8_t data);
uint8_t si1147_read_reg(uint8_t reg_addr);

int16_t si1147_write_param(uint8_t param, uint8_t data);
uint8_t si1147_read_param(uint8_t param);

void si1147_irq_enable();
void si1147_als_irq_enable();
static uint16_t si1147_irq_handler(uint8_t pin);
void si1147_reset();
int16_t _waitUntilSleep();

volatile uint8_t SI1147_Interrupt = 0;

#define LOOP_TIMEOUT_MS 200

int16_t _waitUntilSleep()
{
  int8_t  retval = -1;
  uint8_t count = 0;
  // This loops until the Si114x is known to be in its sleep state
  // or if an i2c error occurs
  while(count < LOOP_TIMEOUT_MS)
  {
    retval = si1147_read_reg(SI1147_CHIP_STAT_REG);
    if(retval == 1) break;
    if(retval <  0) return retval;
    count++;
    SystemTimerDelay(2);
  }
  return 0;
}

// autoincrement disable if reg_addr is anded with SI1147_AUTO_INCR_DISABLE
void si1147_write_reg(uint8_t reg_addr, uint8_t data)
{

	i2c_write_smbus_byte(SI1147_I2C_ADDR, reg_addr, data);
	__delay_cycles(500);
	return;
}

// autoincrement disable if reg_addr is anded with SI1147_AUTO_INCR_DISABLE
uint8_t si1147_read_reg(uint8_t reg_addr)
{
	uint8_t rx;

	rx = i2c_read_smbus_byte(SI1147_I2C_ADDR, reg_addr);
	__delay_cycles(500);

	return rx;
}

//int16_t si1147_write_param(uint8_t address, uint8_t value)
//{
//  int16_t retval;
//  uint16_t buffer;
//  int16_t response_stored;
//  int16_t response;
//
//  if((retval = _waitUntilSleep())!=0) return retval;
//
//  response_stored = i2c_read_smbus_byte(SI1147_I2C_ADDR, SI1147_RESPONSE_REG);
//
//  buffer = value;
//  buffer = (0xA0 + (address & 0x1F)) << 8;
//
//  i2c_write_smbus_word(SI1147_I2C_ADDR, SI1147_PARAM_WR_REG, buffer);
//
//
//  // Wait for command to finish
//  response = i2c_read_smbus_byte(SI1147_I2C_ADDR, SI1147_RESPONSE_REG);
//  while(response == response_stored )
//  {
//    response = i2c_read_smbus_byte(SI1147_I2C_ADDR, SI1147_RESPONSE_REG);
//    if (response == response_stored)
//    {
//    	SystemTimerDelay(2);
//    }
//  }
//
//  if(retval < 0)
//    return retval;
//  else
//    return 0;
//}

int16_t si1147_write_param(uint8_t param, uint8_t data)
{
	si1147_write_reg(SI1147_PARAM_WR_REG, data);
	// tell to write PARAM_WR to SI1147_PARAM_I2C_ADDR
	si1147_write_reg(SI1147_COMMAND_REG, SI1147_COMMAND_PARAM_SET | param);

	return 0;
}

uint8_t si1147_read_param(uint8_t param)
{
	// tell to write parameter to PARAM_RD
	si1147_write_reg(SI1147_COMMAND_REG, SI1147_COMMAND_PARAM_QUERY | param);
	return si1147_read_reg(SI1147_PARAM_RD_REG);
}

int16_t si1147_send_command(uint8_t cmd) {
	int16_t response;
	int8_t retval;
	uint8_t count = 0;

	// Get the response register contents
	response = si1147_read_reg(SI1147_RESPONSE_REG);
	if (response < 0)
		return response;

	// Double-check the response register is consistent
	while (count < LOOP_TIMEOUT_MS) {
		if ((retval = _waitUntilSleep()) != 0)
			return retval;

		if (cmd == 0)
			break; // Skip if the command is NOP

		retval = si1147_read_reg(SI1147_RESPONSE_REG);
		if (retval == response)
			break;
		else if (retval < 0)
			return retval;
		else
			response = retval;
		count++;
	}

	// Send the Command
	si1147_write_reg(SI1147_COMMAND_REG, cmd);

	count = 0;
	// Expect a change in the response register
	while (count < LOOP_TIMEOUT_MS) {
		if (cmd == 0)
			break; // Skip if the command is NOP

		retval = si1147_read_reg(SI1147_RESPONSE_REG);
		if (retval != response)
			break;
		else if (retval < 0)
			return retval;
		count++;
		SystemTimerDelay(1);
	}
	return 0;
}

// meas_rate:
//  - represents the rate at which the sensor wakes up to take measurements
//  - when non-zero, sensor is in autonomous mode
void si1147_init()
{
	SystemTimerDelay(SystemTimeDiff(50)); //Wait until system runing 25ms for startup

	// Turn off RTC
	si1147_write_reg(SI1147_MEAS_RATE0_REG, 0);
	si1147_write_reg(SI1147_MEAS_RATE1_REG, 0);

	si1147_reset();

	// Programm led currents!
	// Set all currents to zero
	si1147_write_reg(SI1147_PS_LED21_REG, 0);
	si1147_write_reg(SI1147_PS_LED21_REG, 0);


	/***********************************/
	// enable UVindex measurement coefficients!
	si1147_write_reg(SI1147_UCOEF0_REG, 0x7B);
	si1147_write_reg(SI1147_UCOEF1_REG, 0x6B);
	si1147_write_reg(SI1147_UCOEF2_REG, 0x01);
	si1147_write_reg(SI1147_UCOEF3_REG, 0x00);

	// enable UV, IR, VIS sensor
	si1147_write_param(
			SI1147_PARAM_CHLIST,
			SI1147_UV_ENABLE |
			SI1147_ALS_IR_ENABLE |
			SI1147_ALS_VIS_ENABLE);

	// enable interrupt on every sample of als
	si1147_write_reg(SI1147_INT_CFG_REG, 0x01);
	si1147_write_reg(SI1147_IRQ_ENABLE_REG, 0x01);

//	// Mux to large IR
//	si1147_write_param(SI1147_PARAM_ALS_IR_ADCMUX, 0x03);
//	// fastest clocks, clock div 2
//	si1147_write_param(SI1147_PARAM_ALS_IR_ADC_GAIN, 0x01);
//	// take 255 clocks to measure
//	si1147_write_param(SI1147_PARAM_ALS_IR_ADC_COUNTER, 0x60);
//	// in high range mode
//	si1147_write_param(SI1147_PARAM_ALS_IR_ADC_MISC, 0x20);
//
//	// fastest clocks, clock div 2
//	si1147_write_param(SI1147_PARAM_ALS_VIS_ADC_GAIN, 0x01);
//	// take 255 clocks to measure
//	si1147_write_param(SI1147_PARAM_ALS_VIS_ADC_COUNTER, 0x60);
//	// in high range mode (not normal signal)
//	si1147_write_param(SI1147_PARAM_ALS_VIS_ADC_MISC, 0x20);

	// measurement rate for auto
	//si1147_write_reg(SI1147_MEAS_RATE0_REG, 1); // 255 * 31.25uS = 8ms
	//si1147_write_reg(SI1147_MEAS_RATE0_REG, 1);

	si1147_irq_enable();

	return;
}

// caller must allocate data as 6 bytes
uint16_t si1147_ReadRawVisible()
{

//	uint16_t visible;
//
//	//si1147_single_conv();
//
//	//visible =
//	visible = si1147_read_reg(SI1147_ALS_VIS_DATA0_REG);
//	visible += si1147_read_reg(SI1147_ALS_VIS_DATA1_REG) << 8;

	return i2c_read_smbus_word(SI1147_I2C_ADDR, SI1147_ALS_VIS_DATA0_REG);
	//return visible;
}

uint16_t si1147_ReadRawIR()
{
	//uint16_t ir;

	//si1147_single_conv();

	//ir =
	//ir = si1147_read_reg(SI1147_ALS_IR_DATA0_REG);
	//ir += si1147_read_reg(SI1147_ALS_IR_DATA1_REG) << 8;
	return i2c_read_smbus_word(SI1147_I2C_ADDR, SI1147_ALS_IR_DATA0_REG);
}

uint16_t si1147_ReadRawUV()
{
	//uint16_t uv;

	//si1147_single_conv();

	//uv =
	//uv = si1147_read_reg(SI1147_AUX_DATA0_REG);
	//uv += si1147_read_reg(SI1147_AUX_DATA1_REG) << 8;
	return i2c_read_smbus_word(SI1147_I2C_ADDR, SI1147_AUX_DATA0_REG);
}

void si1147_irq_enable()
{
	GPIO8_DIR(SI1147_PORT) &= ~SI1147_IRQ_PIN;
	GPIO8_REN(SI1147_PORT) |= SI1147_IRQ_PIN;
	GPIO8_OUT(SI1147_PORT) |= SI1147_IRQ_PIN;
	GPIO8_IES(SI1147_PORT) |= SI1147_IRQ_PIN;
	GpioAttachISR(SI1147_PORT, SI1147_IRQ_PIN, si1147_irq_handler);
	GpioEnableInterupt(SI1147_PORT, SI1147_IRQ_PIN);
	return;
}

void si1147_single_conv()
{
	uint16_t time = 100;
	SI1147_Interrupt = 0;
	si1147_write_reg(SI1147_IRQ_STATUS_REG, 0xFF);
	__delay_cycles(500);
	si1147_write_reg(SI1147_COMMAND_REG, SI1147_COMMAND_ALS_FORCE);
	time += SystemTimeGet();
	while(!SI1147_Interrupt) {
		if(SystemTimeDiff(time) < 0)
			SI1147_Interrupt = 1;
	}
	return;
}

uint16_t si1147_irq_handler(uint8_t pin) {
  SI1147_Interrupt = 1;
  return 0;
}

// Note that the si1147_reset() actually performs the following functions:
//     1. Pauses all prior measurements
//     2. Clear  i2c registers that need to be cleared
//     3. Clears irq status to make sure INT* is negated
//     4. Delays 10 ms
//     5. Sends HW Key

void si1147_reset() {

	si1147_write_reg(SI1147_MEAS_RATE0_REG, 0);
	si1147_write_reg(SI1147_MEAS_RATE1_REG, 0);
	si1147_write_reg(SI1147_IRQ_ENABLE_REG, 0);
	si1147_write_reg(SI1147_INT_CFG_REG, 0);
	si1147_write_reg(SI1147_IRQ_STATUS_REG, 0xFF);
	si1147_write_reg(SI1147_COMMAND_REG, SI1147_COMMAND_RESET);
	SystemTimerDelay(20);
	si1147_write_reg(SI1147_HW_KEY_REG, 0x17);
}
