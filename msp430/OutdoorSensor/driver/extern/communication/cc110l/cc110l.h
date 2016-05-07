/******************************************************************************
    Filename: cc11xL_spi.h  
    
    Description: header file that defines a minimum set of neccessary functions
                 to communicate with CC11xL over SPI as well as the regsister 
                 mapping.    
 
*******************************************************************************/

#ifndef CC110L_SPI_H
#define CC110L_SPI_H

#include <stdint.h>
#include "include/cc110l.h"

#define CC110L_DEBUG 1

int16_t CC110L_SendData(uint8_t *Data);
int16_t CC110L_GetData();
int16_t CC110L_CheckConfig();
int16_t CC110L_WriteConfig(CC110L_CONFIG *Config);
int16_t CC110L_ReadStatus();
int16_t CC110L_SendCommand(uint8_t command);
int16_t CC110L_TX(void *data, uint8_t n_bytes);
int16_t CC110L_WritePATable(uint8_t nBytes, uint16_t PAValue);

#endif// CC11xL_SPI_H
