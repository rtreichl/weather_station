/*
 * cc110l.h
 *
 *  Created on: 15.05.2016
 *      Author: Richard Treichl
 */

#ifndef EXTERN_CC110L_INCLUDE_CC110L_H_
#define EXTERN_CC110L_INCLUDE_CC110L_H_

#define CC110L_RSSI_OFFSET 	74	//74dbm
#define CC110L_SPI_BURST 	0x40
#define CC110L_SPI_READ		0x80
#define CC110L_SPI_WRITE	0x00

/* Register addresses for CC110L */
#define CC110L_IOCFG2           0x00      /*  IOCFG2        - GDO2 output pin configuration  */
#define CC110L_IOCFG1           0x01      /*  IOCFG1        - GDO1 output pin configuration  */
#define CC110L_IOCFG0           0x02      /*  IOCFG1        - GDO0 output pin configuration  */
#define CC110L_FIFOTHR          0x03      /*  FIFOTHR       - RX FIFO and TX FIFO thresholds */
#define CC110L_SYNC1            0x04      /*  SYNC1         - Sync word, high byte */
#define CC110L_SYNC0            0x05      /*  SYNC0         - Sync word, low byte */
#define CC110L_PKTLEN           0x06      /*  PKTLEN        - Packet length */
#define CC110L_PKTCTRL1         0x07      /*  PKTCTRL1      - Packet automation control */
#define CC110L_PKTCTRL0         0x08      /*  PKTCTRL0      - Packet automation control */
#define CC110L_ADDR             0x09      /*  ADDR          - Device address */
#define CC110L_RESERVED_0X0A    0x0A      /*  RESERVED_0X0A - Reserved register */
#define CC110L_FSCTRL1          0x0B      /*  FSCTRL1       - Frequency synthesizer control */
#define CC110L_FSCTRL0          0x0C      /*  FSCTRL0       - Frequency synthesizer control */
#define CC110L_FREQ2            0x0D      /*  FREQ2         - Frequency control word, high byte */
#define CC110L_FREQ1            0x0E      /*  FREQ1         - Frequency control word, middle byte */
#define CC110L_FREQ0            0x0F      /*  FREQ0         - Frequency control word, low byte */
#define CC110L_MDMCFG4          0x10      /*  MDMCFG4       - Modem configuration */
#define CC110L_MDMCFG3          0x11      /*  MDMCFG3       - Modem configuration */
#define CC110L_MDMCFG2          0x12      /*  MDMCFG2       - Modem configuration */
#define CC110L_MDMCFG1          0x13      /*  MDMCFG1       - Modem configuration */
#define CC110L_MDMCFG0          0x14      /*  MDMCFG1       - Modem configuration */
#define CC110L_DEVIATN          0x15      /*  DEVIATN       - Modem deviation setting */
#define CC110L_MCSM2            0x16      /*  MCSM2         - Main Radio Control State Machine configuration */
#define CC110L_MCSM1            0x17      /*  MCSM1         - Main Radio Control State Machine configuration */
#define CC110L_MCSM0            0x18      /*  MCSM0         - Main Radio Control State Machine configuration */
#define CC110L_FOCCFG           0x19      /*  FOCCFG        - Frequency Offset Compensation configuration */
#define CC110L_BSCFG            0x1A      /*  BSCFG         - Bit Synchronization configuration */
#define CC110L_AGCCTRL2         0x1B      /*  AGCCTRL2      - AGC control */
#define CC110L_AGCCTRL1         0x1C      /*  AGCCTRL1      - AGC control */
#define CC110L_AGCCTRL0         0x1D      /*  AGCCTRL0      - AGC control */
#define CC110L_RESERVED_0X20    0x20      /*  RESERVED_0X20 - Reserved register */
#define CC110L_FREND1           0x21      /*  FREND1        - Front end RX configuration */
#define CC110L_FREND0           0x22      /*  FREDN0        - Front end TX configuration */
#define CC110L_FSCAL3           0x23      /*  FSCAL3        - Frequency synthesizer calibration */
#define CC110L_FSCAL2           0x24      /*  FSCAL2        - Frequency synthesizer calibration */
#define CC110L_FSCAL1           0x25      /*  FSCAL1        - Frequency synthesizer calibration */
#define CC110L_FSCAL0           0x26      /*  FSCAL0        - Frequency synthesizer calibration */
#define CC110L_RESERVED_0X29    0x29      /*  RESERVED_0X29 - Reserved register */
#define CC110L_RESERVED_0X2A    0x2A      /*  RESERVED_0X2A - Reserved register */
#define CC110L_RESERVED_0X2B    0x2B      /*  RESERVED_0X2B - Reserved register */
#define CC110L_TEST2            0x2C      /*  TEST2         - Various test settings */
#define CC110L_TEST1            0x2D      /*  TEST1         - Various test settings */
#define CC110L_TEST0            0x2E      /*  TEST0         - Various test settings */
#define CC110L_PA_TABLE0        0x3E           /*  PA_TABLE0 - PA control settings table */

/* status registers CC110L */
#define CC110L_PARTNUM          0x30      /*  PARTNUM         - Chip ID */
#define CC110L_VERSION          0x31      /*  VERSION         - Chip ID */
#define CC110L_FREQEST          0x32      /*  FREQEST         – Frequency Offset Estimate from demodulator */
#define CC110L_LQI              0x33      /*  LQI             – Demodulator estimate for Link Quality */
#define CC110L_RSSI             0x34      /*  RSSI            – Received signal strength indication */
#define CC110L_MARCSTATE        0x35      /*  MARCSTATE       – Main Radio Control State Machine state */
#define CC110L_RESERVED_0X36    0x36      /*  RESERVED_0X36   – Reserved register */
#define CC110L_RESERVED_0X37    0x37      /*  RESERVED_0X37   – Reserved register */
#define CC110L_PKTSTATUS        0x38      /*  PKTSTATUS       – Current GDOx status and packet status */
#define CC110L_RESERVED_0X39    0x39      /*  RESERVED_0X39   – Reserved register */
#define CC110L_TXBYTES          0x3A      /*  TXBYTES         – Underflow and number of bytes */
#define CC110L_RXBYTES          0x3B      /*  RXBYTES         – Overflow and number of bytes */
#define CC110L_RESERVED_0X3C    0x3C      /*  RESERVED_0X3C   – Reserved register */
#define CC110L_RESERVED_0X3D    0x3D      /*  RESERVED_0X3D   – Reserved register */

/* burst write registers */
#define CC110L_PA_TABLE0   0x3E           /*  PA_TABLE0 - PA control settings table */
#define CC110L_TXFIFO      0x3F           /*  FIFO  - Transmit FIFO */
#define CC110L_RXFIFO      0xBF           /*  FIFO  - Transmit FIFO */

/* Other register bit fields */
#define CC110L_CRC_OK_BM            0x80

/* CC110L Command strobe registers */
#define CC110L_COMMAND_SRES                     0x30      /*  SRES    - Reset chip. */
#define CC110L_COMMAND_SFSTXON                  0x31      /*  SFSTXON - Enable and calibrate frequency synthesizer. */
#define CC110L_COMMAND_SXOFF                    0x32      /*  SXOFF   - Turn off crystal oscillator. */
#define CC110L_COMMAND_SCAL                     0x33      /*  SCAL    - Calibrate frequency synthesizer and turn it off. */
#define CC110L_COMMAND_SRX                      0x34      /*  SRX     - Enable RX. Perform calibration if enabled. */
#define CC110L_COMMAND_STX                      0x35      /*  STX     - Enable TX. If in RX state, only enable TX if CCA passes. */
#define CC110L_COMMAND_SIDLE                    0x36      /*  SIDLE   - Exit RX / TX, turn off frequency synthesizer. */
#define CC110L_COMMAND_SPWD                     0x39      /*  SPWD    - Enter power down mode when CSn goes high. */
#define CC110L_COMMAND_SFRX                     0x3A      /*  SFRX    - Flush the RX FIFO buffer. */
#define CC110L_COMMAND_SFTX                     0x3B      /*  SFTX    - Flush the TX FIFO buffer. */
#define CC110L_COMMAND_SNOP                     0x3D      /*  SNOP    - No operation. Returns status byte. */

/* CC110L State Machine States */
#define CC110L_MARCSTATE_SLEEP				0
#define CC110L_MARCSTATE_IDLE				1
#define CC110L_MARCSTATE_XOFF				2
#define CC110L_MARCSTATE_VCOON_MC			3
#define CC110L_MARCSTATE_REGON_MC			4
#define CC110L_MARCSTATE_MANCAL				5
#define CC110L_MARCSTATE_VCOON				6
#define CC110L_MARCSTATE_REGON				7
#define CC110L_MARCSTATE_STARTCAL			8
#define CC110L_MARCSTATE_BWBOOST			9
#define CC110L_MARCSTATE_FS_LOOK			10
#define CC110L_MARCSTATE_IFADCON			11
#define CC110L_MARCSTATE_ENDCAL				12
#define CC110L_MARCSTATE_RX					13
#define CC110L_MARCSTATE_RX_END				14
#define CC110L_MARCSTATE_RX_RST				15
#define CC110L_MARCSTATE_TXRX_SWITCH		16
#define CC110L_MARCSTATE_RXFIFO_OVERFLOW	17
#define CC110L_MARCSTATE_FSTXON				18
#define CC110L_MARCSTATE_TX					19
#define CC110L_MARCSTATE_TX_END				20
#define CC110L_MARCSTATE_RXTX_SWITCH		21
#define CC110L_MARCSTATE_TXFIFO_UNDERFLOW	22

/* CC110L Chip states returned in status byte */
#define CC110L_STATE_IDLE               0
#define CC110L_STATE_RX                 1
#define CC110L_STATE_TX                 2
#define CC110L_STATE_FSTXON             3
#define CC110L_STATE_CALIBRATE          4
#define CC110L_STATE_SETTLING           5
#define CC110L_STATE_RXFIFO_ERROR       6
#define CC110L_STATE_TXFIFO_ERROR       7

/******************************************************************************
 * TYPEDEFS
 */

typedef struct
{
	uint8_t FIFO_BYTES_AVILABLE : 4;
	uint8_t STATE : 3;
	uint8_t CHIP_RDYn : 1;
}CC110L_STATUS_STC;

typedef struct
{
	uint8_t GDO2_CFG : 6;
	uint8_t GDO2_INV : 1;
}CC110L_IOCFG2_STC;

typedef struct
{
	uint8_t GDO1_CFG : 6;
	uint8_t GDO1_INV : 1;
	uint8_t GDO1_DS : 1;
}CC110L_IOCFG1_STC;

typedef struct
{
	uint8_t GDO0_CFG : 6;
	uint8_t GDO0_INV : 1;
}CC110L_IOCFG0_STC;

typedef struct
{
	uint8_t FIFO_THR : 4;
	uint8_t CLOSE_IN_RX : 2;
	uint8_t ADC_RETENTION : 1;
}CC110L_FIFOTHR_STC;

typedef struct
{
	uint8_t ADR_CHK : 2;
	uint8_t APPEND_STATUS : 1;
	uint8_t CRC_AUTOFLUSH : 1;
	uint8_t _res : 1;
	uint8_t SmartRF : 3;
}CC110L_PKTCTRL1_STC;

typedef struct
{
	uint8_t LENGTH_CONFIG : 2;
	uint8_t CRC_EN : 1;
	uint8_t _res1 : 1;
	uint8_t PKT_FORMAT : 2;
	uint8_t SmartRF : 1;
}CC110L_PKTCTRL0_STC;

typedef struct
{
	uint8_t LENGTH_CONFIG : 5;
	uint8_t SmartRF : 1;
}CC110L_FSCTRL1_STC;

typedef struct
{
	uint8_t FREQ : 6;
	uint8_t _FREQ : 2;
}CC110L_FREQ2_STC;

typedef struct
{
	uint8_t DRATE_E : 4;
	uint8_t CHANBW_M : 2;
	uint8_t CHANBW_E : 2;
}CC110L_MDMCFG4_STC;

typedef struct
{
	uint8_t SYNC_MODE : 3;
	uint8_t MANCHESTER_EN : 1;
	uint8_t MOD_FORMAT : 3;
	uint8_t DEM_DCFILT_OFF : 1;
}CC110L_MDMCFG2_STC;

typedef struct
{
	uint8_t CHANSPC_E : 3;
	uint8_t _res : 1;
	uint8_t NUM_PREAMBLE : 3;
	uint8_t SmartRF : 1;
}CC110L_MDMCFG1_STC;

typedef struct
{
	uint8_t DEVIATION_M : 3;
	uint8_t _res1 : 1;
	uint8_t DEVIATION_E : 2;
}CC110L_DEVIATN_STC;

typedef struct
{
	uint8_t SmartRF : 4;
	uint8_t RX_TIME_RSSI : 1;
}CC110L_MCSM2_STC;

typedef struct
{
	uint8_t TXOFF_MODE : 2;
	uint8_t RXOFF_MODE : 2;
	uint8_t CCA_MODE : 2;
}CC110L_MCSM1_STC;

typedef struct
{
	uint8_t XOSC_FORCE_ON : 1;
	uint8_t SmartRF : 1;
	uint8_t PO_TIMEOUT : 2;
	uint8_t FS_AUTOCAL : 2;
}CC110L_MCSM0_STC;

typedef struct
{
	uint8_t FOC_LIMIT : 2;
	uint8_t FOC_POST_K : 1;
	uint8_t FOC_PRE_K : 2;
	uint8_t FOC_BS_CS_GATE : 1;
}CC110L_FOCCFG_STC;

typedef struct
{
	uint8_t BS_LIMIT : 2;
	uint8_t BS_POST_KP : 1;
	uint8_t BS_POST_KI : 1;
	uint8_t BS_PRE_KP : 2;
	uint8_t BS_PRE_KI : 2;
}CC110L_BSCFG_STC;

typedef struct
{
	uint8_t MAGN_TARGET : 2;
	uint8_t MAX_LNA_GAIN : 4;
	uint8_t MAX_DVGA_GAIN : 2;
}CC110L_AGCCTRL2_STC;

typedef struct
{
	uint8_t CARRIER_SENSE_ABS_THR : 4;
	uint8_t CARRIER_SENSE_REL_THR : 2;
	uint8_t AGC_LNA_PRIORITY : 1;
}CC110L_AGCCTRL1_STC;

typedef struct
{
	uint8_t FILTER_LENGTH : 2;
	uint8_t AGC_FREEZE : 2;
	uint8_t WAIT_TIME : 2;
	uint8_t HYST_LEVEL : 2;
}CC110L_AGCCTRL0_STC;

typedef struct
{
	uint8_t MIX_CURRENT : 2;
	uint8_t LODIV_BUF_CURRENT_RX : 2;
	uint8_t LNA2MIX_CURRENT : 2;
	uint8_t LNA_CURRENT : 2;
}CC110L_FREND1_STC;

typedef struct
{
	uint8_t PA_POWER : 3;
	uint8_t _res : 1;
	uint8_t LODIV_BUF_CURRENT_TX : 2;
}CC110L_FREND0_STC;

typedef struct
{
	uint8_t FSCAL3D : 4;
	uint8_t CHP_CURR_CAL_EN : 2;
	uint8_t FSCAL3 : 2;
}CC110L_FSCAL3_STC;

typedef struct
{
	uint8_t FSCAL2 : 5;
	uint8_t VCO_CORE_H_EN : 1;
}CC110L_FSCAL2_STC;

typedef struct
{
	uint8_t TEST0L : 1;
	uint8_t VCO_SEL_CAL_EN : 1;
	uint8_t TEST0H : 6;
}CC110L_TEST0_STC;

typedef struct
{
	uint8_t GDO0 : 1;
	uint8_t _res1 : 1;
	uint8_t GDO2 : 1;
	uint8_t SFD : 1;
	uint8_t CCA : 1;
	uint8_t _res2 : 1;
	uint8_t CS : 1;
	uint8_t CRC_OK : 1;
}CC110L_PKTSTATUS_STC;

typedef struct
{
	uint8_t NUM_TXBYTES  : 7;
	uint8_t TXFIFO_UNDERFLOW : 1;
}CC110L_TXBYTES_STC;

typedef struct
{
	uint8_t NUM_RXBYTES : 7;
	uint8_t RXFIFO_OVERFLOW : 1;
}CC110L_RXBYTES_STC;

typedef uint8_t CC110L_SYNC_BYTE;
typedef uint8_t CC110L_FREQ_BYTE;
typedef uint8_t CC110L_PKTLEN_BYTE;
typedef uint8_t CC110L_ADDR_BYTE;
typedef uint8_t CC110L_SYNC_BYTE;
typedef uint8_t CC110L_MDMCFG3_BYTE;
typedef uint8_t CC110L_RESERVED_BYTE;
typedef uint8_t CC110L_FSCAL1_BYTE;
typedef uint8_t CC110L_FSCAL0_BYTE;
typedef uint8_t CC110L_VERSION_BYTE;
typedef uint8_t CC110L_FREQEST_BYTE;
typedef uint8_t CC110L_CRC_REG_BYTE;
typedef uint8_t CC110L_RSSI_BYTE;
typedef uint8_t CC110L_MARCSTATE_BYTE;
typedef uint8_t CC110L_TEST2_BYTE;
typedef uint8_t CC110L_TEST1_BYTE;
typedef uint8_t CC110L_PARTNUM_BYTE;
typedef uint8_t CC110L_CHANNR_BYTE;
typedef uint8_t CC110L_FSCTRL0_BYTE;
typedef uint8_t CC110L_MDMCFG0_BYTE;

typedef struct
{
	CC110L_IOCFG2_STC IOCFG2;			//0x00
	CC110L_IOCFG1_STC IOCFG1;			//0x01
	CC110L_IOCFG0_STC IOCFG0;			//0x02
	CC110L_FIFOTHR_STC FIFOTHR;			//0x03
	CC110L_SYNC_BYTE SYNC1;				//0x04
	CC110L_SYNC_BYTE SYNC0;				//0x05
	CC110L_PKTLEN_BYTE PKTLEN;			//0x06
	CC110L_PKTCTRL1_STC PKTCTRL1;		//0x07
	CC110L_PKTCTRL0_STC PKTCTRL0;		//0x08
	CC110L_ADDR_BYTE ADDR;				//0x09
	CC110L_CHANNR_BYTE CHANNR;			//0x0A
	CC110L_FSCTRL1_STC FSCTRL1;			//0x0B
	CC110L_FSCTRL0_BYTE FSCTRL0;		//0x0C
	CC110L_FREQ2_STC FREQ2;				//0x0D
	CC110L_FREQ_BYTE FREQ1;				//0x0E
	CC110L_FREQ_BYTE FREQ0;				//0x0F
	CC110L_MDMCFG4_STC MDMCFG4;			//0x10
	CC110L_MDMCFG3_BYTE MDMCFG3;		//0x11
	CC110L_MDMCFG2_STC MDMCFG2;			//0x12
	CC110L_MDMCFG1_STC MDMCFG1;			//0x13
	CC110L_MDMCFG0_BYTE MDMCFG0;		//0x14
	CC110L_DEVIATN_STC DEVIANT;			//0x15
	CC110L_MCSM2_STC MCSM2;				//0x16
	CC110L_MCSM1_STC MCSM1;				//0x17
	CC110L_MCSM0_STC MCSM0;				//0x18
	CC110L_FOCCFG_STC FOCCFG;			//0x19
	CC110L_BSCFG_STC BSCFG;				//0x1A
	CC110L_AGCCTRL2_STC AGCCTRL2;		//0x1B
	CC110L_AGCCTRL1_STC AGCCTRL1;		//0x1C
	CC110L_AGCCTRL0_STC AGCCTRL0;		//0x1D
	CC110L_RESERVED_BYTE RESERVEDx1E;	//0x1E
	CC110L_RESERVED_BYTE RESERVEDx1F;	//0x1F
	CC110L_RESERVED_BYTE RESERVEDx20;	//0x20
	CC110L_FREND1_STC FREND1;			//0x21
	CC110L_FREND0_STC FREND0;			//0x22
	CC110L_FSCAL3_STC FSCAL3;			//0x23
	CC110L_FSCAL2_STC FSCAL2;			//0x24
	CC110L_FSCAL1_BYTE FSCAL1;			//0x25
	CC110L_FSCAL0_BYTE FSCAL0;			//0x26
	CC110L_RESERVED_BYTE RESERVEDx27;	//0x27
	CC110L_RESERVED_BYTE RESERVEDx28;	//0x28
	CC110L_RESERVED_BYTE RESERVEDx29;	//0x29
	CC110L_RESERVED_BYTE RESERVEDx2A;	//0x2A
	CC110L_RESERVED_BYTE RESERVEDx2B;	//0x2B
	CC110L_TEST2_BYTE TEST2;			//0x2C
	CC110L_TEST1_BYTE TEST1;			//0x2D
	CC110L_TEST0_STC TEST0;				//0x2E
}CC110L_CONFIG;

typedef struct
{
	CC110L_PARTNUM_BYTE PARTNUM;		//0x30
	CC110L_VERSION_BYTE VERSION;		//0x31
	CC110L_FREQEST_BYTE FREQEST;		//0x32
	CC110L_CRC_REG_BYTE CRC_REG;		//0x33
	CC110L_RSSI_BYTE RSSI;				//0x34
	CC110L_MARCSTATE_BYTE MAECSTATE;	//0x35
	CC110L_RESERVED_BYTE RESERVEDx36;	//0x36
	CC110L_RESERVED_BYTE RESERVEDx37;	//0x37
	CC110L_PKTSTATUS_STC PKTSTATUS;		//0x38
	CC110L_RESERVED_BYTE RESERVEDx39;	//0x39
	CC110L_TXBYTES_STC TXBYTES;			//0x3A
	CC110L_RXBYTES_STC RXBYTES;			//0x3B
	CC110L_RESERVED_BYTE RESERVEDx3C;	//0x3C
	CC110L_RESERVED_BYTE RESERVEDx3D;	//0x3D
} CC110L_STATUS;

#endif /* EXTERN_CC110L_INCLUDE_CC110L_H_ */
