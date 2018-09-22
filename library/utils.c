#include <utils.h>
#include <uart.h>
#include <stdlib.h>

void utilsPrintHexByte(uint8_t byte)
{
    uint8_t lower_nibble = byte & 0x0f;
    uint8_t upper_nibble = (byte >> 4) & 0x0f;

    if(upper_nibble < 10)
        uartWriteChar(upper_nibble + '0');
    else 
        uartWriteChar((upper_nibble - 10) + 'A');

     if(lower_nibble < 10)
        uartWriteChar(lower_nibble + '0');
    else 
        uartWriteChar((lower_nibble - 10) + 'A');
}

void utilsPrintHex(uint8_t *buffer, uint16_t size)
{
    for(uint16_t index = 0; index < size; index++)
    {
        utilsPrintHexByte(buffer[index]);
        uartWriteChar(' ');
    }
    uartWriteString("\r\n");
}

static char text_buf[20];
void utilsPrintInt(uint16_t var)
{
    itoa(var, text_buf, 10);
    uartWriteString(text_buf);
}