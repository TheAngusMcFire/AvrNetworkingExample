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
    uint16_t cnt = 1;

    uartWriteString("\r\n");
    utilsPrintUint16(0);
    uartWriteString(":  ");

    for(uint16_t index = 0; index < size; index++)
    {
        utilsPrintHexByte(buffer[index]);

        if(cnt++ % 16 == 0)
        {
            uartWriteString("\r\n");
            utilsPrintUint16(index);
            uartWriteString(":  ");
        }
        else    
            uartWriteChar(' ');
    }
}

static char text_buf[20];
void utilsPrintInt(uint16_t var)
{
    itoa(var, text_buf, 10);
    uartWriteString(text_buf);
}

void utilsPrintMacAddress(uint8_t *mac)
{
    utilsPrintHexByte(mac[0]);

    for(uint8_t index = 1; index < 6; index++)
    {
        uartWriteChar(':');
        utilsPrintInt(mac[index]);
    }
}

void utilsPrintIpAddress(uint8_t *ip)
{
    utilsPrintInt(ip[0]);

    for(uint8_t index = 1; index < 4; index++)
    {
        uartWriteChar('.');
        utilsPrintInt(ip[index]);
    }
}

void utilsPrintUint16(uint16_t value)
{
    uartWriteString("0x");
    utilsPrintHexByte(value >> 8);
    utilsPrintHexByte(value & 0xff);    
}