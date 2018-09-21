#include <stdint.h>


#ifndef INTERFACES_SPI_H
#define INTERFACES_SPI_H

void spiInit();

void spiCsActive();
void spiCsPassive();

void spiWait();

void spiWrite(uint8_t data);
uint8_t spiRead();

#endif