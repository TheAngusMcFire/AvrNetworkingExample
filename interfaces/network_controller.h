#include <stdint.h>


#ifndef INTERFACES_NETWORK_CONTROLLER_H
#define INTERFACES_NETWORK_CONTROLLER_H

void networkControllerInit(uint8_t * mac_addr);
uint16_t networkControllerReadByteStream(uint8_t *buffer, uint16_t buffer_size);
void networkControllerWriteByteStream(uint8_t *buffer, uint16_t buffer_size);

#endif