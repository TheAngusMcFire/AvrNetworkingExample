#include <stdint.h>


#ifndef INTERFACES_UTILS_H
#define INTERFACES_UTILS_H

#define UTILS_BUFFER_TO_UINT16(ptr) (uint16_t)(((uint16_t)(ptr[0]) << 8) + ptr[1])

void utilsPrintHexByte(uint8_t byte);
void utilsPrintHex(uint8_t *buffer, uint16_t size);
void utilsPrintInt(uint16_t var);
void utilsPrintMacAddress(uint8_t *mac);
void utilsPrintIpAddress(uint8_t *ip);
void utilsPrintUint16(uint16_t value);
void utilsPrintIndentedString(const char* str);
void utilsPrintSeperator();
void utilsWriteLine(const char *str);

#endif