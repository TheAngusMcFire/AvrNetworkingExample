#include <stdint.h>


#ifndef INTERFACES_NETWORK_CONTROLLER_H
#define INTERFACES_NETWORK_CONTROLLER_H

void networkControllerInit();
uint8_t networkControllerReadByteStream(uint8_t *buffer, uint16_t size);
uint8_t networkControllerWriteByteStream(uint8_t *buffer, uint16_t size);

#endif