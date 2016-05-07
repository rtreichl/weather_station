///----------------------------------------------------------------------------------------
///
/// \file si1147_2.c
///
/// \brief 
///
/// \date 04.04.2016
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

#include "Si114x.h"
#include "Si114x_defs.h"

#define PS_ADC_GAIN     0x02


Si114x::Si114x(PinName sda, PinName scl) : i2c(sda,scl) {
    //Wait startup time and enable the device
    i2c.frequency(400000);
    wait_ms(30);
    write_byte(REG_MEAS_RATE0, 0x00);
    write_byte(REG_MEAS_RATE1, 0x00);

    write_cmd(CMD_RESET);
    wait_ms(10);
    write_byte(REG_HW_KEY, 0x17);

    //Set UV coefficients
    write_byte(REG_UCOEF0, 0x29);
    write_byte(REG_UCOEF1, 0x89);
    write_byte(REG_UCOEF2, 0x02);
    write_byte(REG_UCOEF3, 0x00);

    //Set LED current (max, which apparantly is not going to destroy anything)
    write_byte(REG_PS_LED21, 0xFF);

    //Set default LED channels
    setPSLEDs(1, 0x01);
    setPSLEDs(2, 0x02);

    continious = false;

}

bool Si114x::verifyConnection(void) {
    uint8_t part_id = read_byte(REG_PART_ID);
    if ((part_id == 0x45) || (part_id == 0x46) || (part_id == 0x47))
        return true;
    return false;
}

//-------------------Get light functions---------------------------

unsigned short Si114x::getVisibleLight(void) {
    if (continious == false) {
        //Enable visible light measurement, clear current interrupt, start conversion, wait until done
        write_byte(REG_IRQ_STATUS, 0x01);
        param_set(RAM_CHLIST, (1<<4));
        write_cmd(CMD_ALS_FORCE);
        while(read_byte(REG_IRQ_STATUS) & 0x01 != 0x01);
    }
    return read_word(REG_ALS_VIS_DATA0);
}

unsigned short Si114x::getIRLight(void) {
    if (continious == false) {
        //Enable IR light measurement, clear current interrupt, start conversion, wait until done
        write_byte(REG_IRQ_STATUS, 0x01);
        param_set(RAM_CHLIST, (1<<5));
        write_cmd(CMD_ALS_FORCE);
        while(read_byte(REG_IRQ_STATUS) & 0x01 != 0x01);
    }
    return read_word(REG_ALS_IR_DATA0);
}

unsigned short Si114x::getUVIndex(void) {
    if (continious == false) {
        //Enable IR light measurement, clear current interrupt, start conversion, wait until done
        write_byte(REG_IRQ_STATUS, 0x01);
        param_set(RAM_CHLIST, (1<<7));
        write_cmd(CMD_ALS_FORCE);
        while(read_byte(REG_IRQ_STATUS) & 0x01 != 0x01);
    }
    return read_word(REG_UV_INDEX0);
}

//---------------------------------- Proximity -----------------------------------------------------
unsigned short Si114x::getProximity(char pschannel) {
    if (continious == false) {
        //Enable IR light measurement, clear current interrupt, start conversion, wait until done
        write_byte(REG_IRQ_STATUS, 0x04);
        param_set(RAM_CHLIST, (1<<(pschannel-1)));
        write_cmd(CMD_PS_FORCE);
        while(read_byte(REG_IRQ_STATUS) & 0x04 != 0x04);
    }
    return read_word(REG_PS1_DATA0 + (pschannel - 1)* 2);
}

void Si114x::setPSLEDs(char pschannel, char ledmask) {
    char psled12 = param_query(RAM_PSLED12_SELECT);
    if (pschannel == 1) {
        psled12 = (psled12 & ~0x0F) | ledmask;
    }
    else {
        psled12 = (psled12 & ~0xF0) | (ledmask << 4);
    }
    param_set(RAM_PSLED12_SELECT, psled12);
}


//---------------------------------- Read/Write functions ---------------------------------------------

char Si114x::read_byte(const char reg) {
    char retval;
    i2c.write(SI114x_ADDRESS, &reg, 1, true);
    i2c.read(SI114x_ADDRESS, &retval, 1);
    return retval;
}

unsigned short Si114x::read_word(const char reg) {
    unsigned short retval;
    i2c.write(SI114x_ADDRESS, &reg, 1, true);
    i2c.read(SI114x_ADDRESS, (char*)&retval, 2);    //This actually seems to put them in correct order
    return retval;
}

void Si114x::write_byte(const char reg, const char byte) {
    char data[] = {reg, byte};
    i2c.write(SI114x_ADDRESS, data, 2);
}

void Si114x::param_set(const char param, const char value) {
    write_byte(REG_PARAM_WR, value);
    write_cmd(CMD_PARAM_SET | param);
}

char Si114x::param_query(const char param) {
    write_cmd(CMD_PARAM_QUERY | param);
    return read_byte(REG_PARAM_RD);
}

void Si114x::write_cmd(const char cmd) {
    uint8_t old_value = read_byte(REG_RESPONSE);

    write_byte(REG_COMMAND, cmd);

    if (cmd == CMD_RESET) {
        return;
    }

    char i = 0;
    while(read_byte(REG_RESPONSE) == old_value) {
        wait_ms(1);
        if (i > 25) {
            break;
        }
        i++;
    }
}
