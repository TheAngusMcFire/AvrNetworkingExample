#include <arp.h>
#include <utils.h>
#include <uart.h>



uint8_t arpParseHeader(ArpHeader *arp_header, uint8_t *buffer, uint16_t rcv_size)
{
    if(rcv_size < ARP_HEADER_SIZE)
        return ARP_HEADER_FAIL;

    arp_header->hardware_type = UTILS_BUFFER_TO_UINT16(buffer);
    buffer += 2;
    arp_header->protocol_type = UTILS_BUFFER_TO_UINT16(buffer);
    buffer += 2;
    arp_header->hardware_addr_len = buffer[0];
    arp_header->protocol_addr_len = buffer[1];
    buffer += 2;
    arp_header->operation = UTILS_BUFFER_TO_UINT16(buffer);
    buffer += 2;

    for(uint8_t index = 0; index < 6; index++)
        arp_header->sender_mac[index] = buffer[index];

    buffer += 6;

    for(uint8_t index = 0; index < 4; index++)
        arp_header->sender_ip[index] = buffer[index];    

    buffer += 4;

    for(uint8_t index = 0; index < 6; index++)
        arp_header->target_mac[index] = buffer[index];

    buffer += 6;

    for(uint8_t index = 0; index < 4; index++)
        arp_header->target_ip[index] = buffer[index];   

    return ARP_HEADER_OK; 
}

void arpPrintHeader(ArpHeader *header)
{
    uartWriteString("\r\nArp Header: \r\n");
    uartWriteString("    Hardware Type          : ");
    utilsPrintInt(header->hardware_type);
    uartWriteString("\n\r    Protocol Type          : 0x");
    utilsPrintHexByte(header->protocol_type >> 8);
    utilsPrintHexByte(header->protocol_type & 0xff);

    uartWriteString("\r\n    Hardware Addr Len      : ");
    utilsPrintHexByte(header->hardware_addr_len);
    uartWriteString("\r\n    Protocol Addr Len      : ");
    utilsPrintHexByte(header->protocol_addr_len);
    uartWriteString("\n\r    Operation              : ");
    utilsPrintInt(header->operation);

    uartWriteString("\r\n    Sender Mac             : ");
    utilsPrintHex(header->sender_mac, 6);
    uartWriteString("    Sender Ip              : ");
    utilsPrintInt(header->sender_ip[0]);
    uartWriteChar('.');
    utilsPrintInt(header->sender_ip[1]);
    uartWriteChar('.');
    utilsPrintInt(header->sender_ip[2]);
    uartWriteChar('.');
    utilsPrintInt(header->sender_ip[3]);

    uartWriteString("\r\n    Target Mac             : ");
    utilsPrintHex(header->target_mac, 6);
    uartWriteString("    Target Ip              : ");
   utilsPrintInt(header->target_ip[0]);
    uartWriteChar('.');
    utilsPrintInt(header->target_ip[1]);
    uartWriteChar('.');
    utilsPrintInt(header->target_ip[2]);
    uartWriteChar('.');
    utilsPrintInt(header->target_ip[3]);
    uartWriteString("\r\n\r\n");
}