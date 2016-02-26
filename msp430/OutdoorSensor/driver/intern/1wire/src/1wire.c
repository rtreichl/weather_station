/*
 * 1-Wire implementation for MSP430
 *
 * @author: David Siroky <siroky@dasir.cz>
 * @license: MIT
 */

#include <driver.h>

uint8_t onewire_pin = 0;
uint16_t onewire_port = 0;

uint16_t onewire_init(GPIO8_PORT port, GPIO_PIN pin)
{
	onewire_pin = pin;
	onewire_port = port;
	return 0;
}

uint16_t onewire_reset()
{
  onewire_line_low();
  SystemDelayUS(550); // 480us minimum
  onewire_line_release();
  SystemDelayUS(70); // slave waits 15-60us
  if (GPIO8_DIR(onewire_port) & onewire_pin) return 1; // line should be pulled down by slave
  SystemDelayUS(300); // slave TX presence pulse 60-240us
  if (!(GPIO8_DIR(onewire_port) & onewire_pin)) return 2; // line should be "released" by slave
  return 0;
}

void onewire_write_bit(int bit)
{
  SystemDelayUS(2); // recovery, min 1us
  onewire_line_low();
  if (bit)
    SystemDelayUS(6); // max 15us
  else
    SystemDelayUS(64); // min 60us
  onewire_line_release();
  // rest of the write slot
  if (bit)
    SystemDelayUS(64);
  else
    SystemDelayUS(6);
}

uint8_t onewire_read_bit()
{
  int bit;
  SystemDelayUS(2); // recovery, min 1us
  onewire_line_low();
  SystemDelayUS(5); // hold min 1us
  onewire_line_release();
  SystemDelayUS(6); // 15us window
  bit = GPIO8_IN(onewire_port) & onewire_pin;
  SystemDelayUS(60); // rest of the read slot
  return bit;
}

void onewire_write_byte(uint8_t byte)
{
  int i;
  for(i = 0; i < 8; i++)
  {
    onewire_write_bit(byte & 1);
    byte >>= 1;
  }
}

uint8_t onewire_read_byte()
{
  int i;
  uint8_t byte = 0;
  for(i = 0; i < 8; i++)
  {
    byte >>= 1;
    if (onewire_read_bit()) byte |= 0x80;
  }
  return byte;
}


inline void onewire_line_low()
{
  GPIO8_DIR(onewire_port) |= onewire_pin;
  GPIO8_OUT(onewire_port) &= ~onewire_pin;
  GPIO8_REN(onewire_port) &= ~onewire_pin;
}

inline void onewire_line_high()
{
  GPIO8_DIR(onewire_port) |= onewire_pin;
  GPIO8_OUT(onewire_port) |= onewire_pin;
  GPIO8_REN(onewire_port) &= ~onewire_pin;
}

inline void onewire_line_release()
{
  GPIO8_DIR(onewire_port) &= ~onewire_pin;
  GPIO8_REN(onewire_port) |= onewire_pin;
  GPIO8_OUT(onewire_port) |= onewire_pin;
}
