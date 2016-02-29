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

#include <driver.h>

void si1147_write_reg(uint8_t reg_addr, uint8_t data);
uint8_t si1147_read_reg(uint8_t reg_addr);

void si1147_write_param(uint8_t param, uint8_t data);
uint8_t si1147_read_param(uint8_t param);

void si1147_irq_enable();
void si1147_als_irq_enable();
uint16_t si1147_irq_handler(uint8_t pin);
void si1147_reset();

volatile uint8_t SI1147_Interrupt = 0;

// autoincrement disable if reg_addr is anded with SI1147_AUTO_INCR_DISABLE
void si1147_write_reg(uint8_t reg_addr, uint8_t data)
{

	i2c_write_smbus_byte(SI1147_I2C_ADDR, reg_addr, data);
	return;
}

// autoincrement disable if reg_addr is anded with SI1147_AUTO_INCR_DISABLE
uint8_t si1147_read_reg(uint8_t reg_addr)
{
	uint8_t rx;

	rx = i2c_read_smbus_byte(SI1147_I2C_ADDR, reg_addr);

	return rx;
}

void si1147_write_param(uint8_t param, uint8_t data)
{
	si1147_write_reg(SI1147_PARAM_WR_REG, data);
	// tell to write PARAM_WR to SI1147_PARAM_I2C_ADDR
	si1147_write_reg(SI1147_COMMAND_REG, SI1147_COMMAND_PARAM_SET | param);

	return;
}

uint8_t si1147_read_param(uint8_t param)
{
	// tell to write parameter to PARAM_RD
	si1147_write_reg(SI1147_COMMAND_REG, SI1147_COMMAND_PARAM_QUERY | param);
	return si1147_read_reg(SI1147_PARAM_RD_REG);
}

// meas_rate:
//  - represents the rate at which the sensor wakes up to take measurements
//  - when non-zero, sensor is in autonomous mode
void si1147_init()
{
	SystemTimerDelay(SystemTimeDiff(25)); //Wait until system runing 25ms for startup

	si1147_reset();
	/***********************************/
	// enable UVindex measurement coefficients!

	si1147_write_reg(SI1147_UCOEF0_REG, 0x7B);
	si1147_write_reg(SI1147_UCOEF1_REG, 0x6B);
	si1147_write_reg(SI1147_UCOEF2_REG, 0x01);
	si1147_write_reg(SI1147_UCOEF3_REG, 0x00);

	// enable UV sensor
	si1147_write_param(
			SI1147_PARAM_CHLIST,
			SI1147_UV_ENABLE |
			SI1147_ALS_IR_ENABLE |
			SI1147_ALS_VIS_ENABLE);

	// enable interrupt on every sample
	si1147_write_reg(SI1147_INT_CFG_REG, 1);
	si1147_write_reg(SI1147_IRQ_ENABLE_REG, 1);

	si1147_write_param(SI1147_PARAM_ALS_IR_ADCMUX, 0);
	// fastest clocks, clock div 1
	si1147_write_param(SI1147_PARAM_ALS_IR_ADC_GAIN, 0);
	// take 511 clocks to measure
	si1147_write_param(SI1147_PARAM_ALS_IR_ADC_COUNTER, 0x70);
	// in high range mode
	si1147_write_param(SI1147_PARAM_ALS_IR_ADC_MISC, 0x20);

	// fastest clocks, clock div 1
	si1147_write_param(SI1147_PARAM_ALS_VIS_ADC_GAIN, 0);
	// take 511 clocks to measure
	si1147_write_param(SI1147_PARAM_ALS_VIS_ADC_COUNTER, 0x70);
	// in high range mode (not normal signal)
	si1147_write_param(SI1147_PARAM_ALS_VIS_ADC_MISC, 0x20);

	// measurement rate for auto
	si1147_write_reg(SI1147_MEAS_RATE0_REG, 0); // 255 * 31.25uS = 8ms
	si1147_write_reg(SI1147_MEAS_RATE0_REG, 1);

	si1147_irq_enable();

	return;
}

// caller must allocate data as 6 bytes
uint16_t si1147_ReadRawVisible()
{
	uint16_t visible;

	//si1147_single_conv();

	visible = si1147_read_reg(SI1147_ALS_VIS_DATA0_REG);
	visible += si1147_read_reg(SI1147_ALS_VIS_DATA1_REG) << 8;
	return visible;
}

uint16_t si1147_ReadRawIR()
{
	uint16_t ir;

	//si1147_single_conv();

	ir = si1147_read_reg(SI1147_ALS_IR_DATA0_REG);
	ir += si1147_read_reg(SI1147_ALS_IR_DATA1_REG) << 8;
	return ir;
}

uint16_t si1147_ReadRawUV()
{
	uint16_t uv;

	//si1147_single_conv();

	uv = si1147_read_reg(SI1147_AUX_DATA0_REG);
	uv += si1147_read_reg(SI1147_AUX_DATA1_REG) << 8;
	return uv;
}

void si1147_irq_enable()
{
//  GPIO_SOFTWARE_CONTROL(SI1147_IRQ_BASE, SI1147_IRQ_PIN_MASK);
//  GPIO_SET_INPUT(SI1147_IRQ_BASE, SI1147_IRQ_PIN_MASK);
//  GPIO_DETECT_EDGE(SI1147_IRQ_BASE, SI1147_IRQ_PIN_MASK);
//  GPIO_TRIGGER_SINGLE_EDGE(SI1147_IRQ_BASE, SI1147_IRQ_PIN_MASK);
//  GPIO_DETECT_FALLING(SI1147_IRQ_BASE, SI1147_IRQ_PIN_MASK);
//  GPIO_ENABLE_INTERRUPT(SI1147_IRQ_BASE, SI1147_IRQ_PIN_MASK);
//  ioc_set_over(SI1147_IRQ_PORT, SI1147_IRQ_PIN, IOC_OVERRIDE_DIS);
	SI1147_IRQ_PDIR &= ~SI1147_IRQ_BIT;
	SI1147_IRQ_PREN |= SI1147_IRQ_BIT;
	SI1147_IRQ_POUT |= SI1147_IRQ_BIT;
	SI1147_IRQ_PIES |= SI1147_IRQ_BIT;
	GpioAttachISR(GPIO8_PORT1, GPIO_PIN0, si1147_irq_handler);
	GpioEnableInterupt(GPIO8_PORT1, GPIO_PIN0);
	//ext_interrupt_create(SI1147_IRQ_NUM, si1147_irq_handler);
	//ext_interrupt_enable(SI1147_IRQ_NUM);
//  nvic_interrupt_enable(NVIC_INT_GPIO_PORT_C);
//  gpio_register_callback((gpio_callback_t)si1147_irq_handler, SI1147_IRQ_PORT, SI1147_IRQ_PIN);

  return;
}

void si1147_single_conv()
{
	uint8_t rx;
	SI1147_Interrupt = 0;
	rx = si1147_read_reg(SI1147_IRQ_STATUS_REG);
	si1147_write_reg(SI1147_IRQ_STATUS_REG, rx);
	si1147_write_reg(SI1147_COMMAND_REG, SI1147_COMMAND_ALS_FORCE);
	while(!SI1147_Interrupt);
	rx = si1147_read_reg(SI1147_IRQ_STATUS_REG);
	si1147_write_reg(SI1147_IRQ_STATUS_REG, rx);
	return;
}

uint16_t si1147_irq_handler(uint8_t pin) {
  SI1147_Interrupt = 1;
  return 0;
}

void si1147_reset() {
	si1147_write_reg(SI1147_MEAS_RATE0_REG, 0);
	si1147_write_reg(SI1147_MEAS_RATE1_REG, 0);
	si1147_write_reg(SI1147_IRQ_ENABLE_REG, 0);
	si1147_write_reg(SI1147_INT_CFG_REG, 0);
	si1147_write_reg(SI1147_IRQ_STATUS_REG, 0xFF);

	si1147_write_reg(SI1147_COMMAND_REG, SI1147_COMMAND_RESET);
	_delay_cycles(1000);
	si1147_write_reg(SI1147_HW_KEY_REG, 0x17);
	_delay_cycles(1000);
}
