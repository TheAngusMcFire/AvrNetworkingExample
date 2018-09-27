#include <utils.h>
#include <uart.h>
#include <stdlib.h>
#include <string.h>

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
    utoa(var, text_buf, 10);
    uartWriteString(text_buf);
}

void utilsPrintMacAddress(uint8_t *mac)
{
    utilsPrintHexByte(mac[0]);

    for(uint8_t index = 1; index < 6; index++)
    {
        uartWriteChar(':');
        utilsPrintHexByte(mac[index]);
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

void utilsPrintIndentedString(const char* str)
{
    uartWriteString("\r\n");
    uartWriteString("    ");
    uartWriteString(str);
}

void utilsPrintSeperator()
{            
    for(uint8_t index = 0; index < 100; index++)
        uartWriteChar('#');

    uartWriteString("\r\n");
}

void utilsWriteLine(const char *str)
{
    if(str != 0)
        uartWriteString(str);
        
    uartWriteString("\r\n");
}



uint16_t ntohs (uint16_t value)
{
    uint16_t val = 0;

    val = value >> 8;
    val |= (value & 0xFF) << 8;

    return val; 
}

uint16_t htons (uint16_t value)
{
    return ntohs(value); 
}

//the code for crc_calc was taken from:
//http://www.microhowto.info/howto/calculate_an_internet_protocol_checksum_in_c.html

uint16_t utilsCalcChecksum(uint8_t *buffer, uint8_t size)
{
    uint32_t acc=0xffff;

    // Handle complete 16-bit blocks.
    for (size_t i=0; i+1 < size; i+=2) 
    {
        uint16_t word;
        memcpy(&word,buffer+i,2);
        acc+=ntohs(word);
        if (acc>0xffff) 
        {
            acc-=0xffff;
        }
    }

    // Handle any partial block at the end of the data.
    if (size&1) 
    {
        uint16_t word=0;
        memcpy(&word,buffer+size-1,1);
        acc+=ntohs(word);
        if (acc>0xffff)
        {
            acc-=0xffff;
        }
    }

    // Return the checksum in network byte order.
    return htons(~acc);
} 

void utilsWriteChars(const char *str, uint16_t size)
{
    for(uint16_t index = 0; index < size; index++)
        uartWriteChar(str[index]);
}