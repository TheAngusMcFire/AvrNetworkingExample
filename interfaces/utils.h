#include <stdint.h>


#ifndef INTERFACES_UTILS_H
#define INTERFACES_UTILS_H

#define UTILS_BUFFER_TO_UINT16(ptr) (uint16_t)(((uint16_t)(ptr[0]) << 8) + ptr[1])

void utilsPrintHexByte(uint8_t byte);
void utilsPrintHex(uint8_t *buffer, uint16_t size);
void utilsPrintInt(uint16_t var);

#endif