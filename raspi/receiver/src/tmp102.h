#include <stdint.h>
#include "i2c.h"
#include <pigpio.h>

#define TMP102_TEMPERATURE_REG		0x00
#define TMP102_CONFIG_REG			0x01
#define TMP102_TEMP_LOW_REG			0x02
#define TMP102_TEMP_HIGH_REG		0x03
#define TMP102_MANF_ID_REG			0xFE
#define TMP102_DEV_ID_REG			0xFF
#define TMP102_SHUTDOWN				1
#define TMP102_NORMAL_OPERATION		0
#define TMP102_COMPERATOR_MODE		1
#define TMP102_INTERRUPT_MODE		0
#define TMP102_POLARITY_HIGH		1
#define TMP102_POLARITY_LOW			0
#define TMP102_FAULT_QUEUE_1		0
#define TMP102_FAULT_QUEUE_2		1
#define TMP102_FAULT_QUEUE_4		2
#define TMP102_FAULT_QUEUE_6		3
#define TMP102_RESOLUTION_12BIT		3
#define TMP102_ONE_SHOT				1
#define TMP102_NORMAL_MODE			0
#define TMP102_EXENDED_MODE			1
#define TMP102_ALERT_ZERO			0
#define TMP102_ALERT_ONE			1
#define TMP102_CONVER_RATE_4S		0
#define TMP102_CONVER_RATE_1S		1
#define TMP102_CONVER_RATE_250MS	2
#define TMP102_CONVER_RATE_125MS	3

#define TMP102_INTERRUPT_PIN		14

void ISR(int pin, int level, uint32_t tick);

class TMP102:I2C
{
public:
	typedef struct
	{
		uint16_t _res1 : 4;
		uint16_t EM : 1;
		uint16_t AL : 1;
		uint16_t CR : 2;
		uint16_t SD : 1;
		uint16_t TM : 1;
		uint16_t POL: 1;
		uint16_t F : 3;
		uint16_t R : 2;
		uint16_t OS : 1;
	}TMP102_Config;
	
	TMP102(uint8_t i2c_device, uint8_t address, const TMP102_Config &config = {0});
	~TMP102();
	int GetConfig(TMP102_Config *config);
	int SetConfig(const TMP102_Config &config);
	float ReadTemperature();
private:
	int device;
	TMP102_Config config = {0};
};
