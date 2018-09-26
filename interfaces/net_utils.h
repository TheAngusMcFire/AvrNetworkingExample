#include <stdint.h>


#ifndef INTERFACES_NET_UTILS_H
#define INTERFACES_NET_UTILS_H

uint8_t icmpPrepareResponce(uint8_t *rcv_buffer, uint16_t rcv_size, uint8_t* tx_buffer, uint8_t tx_buff_size);

#endif