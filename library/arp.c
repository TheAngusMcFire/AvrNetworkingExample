#include <arp.h>
#include <utils.h>
#include <uart.h>
#include <string.h>

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
    utilsWriteLine(0);
    uartWriteString("Arp Header: ");
    utilsPrintIndentedString("Hardware Type  : ");
    utilsPrintInt(header->hardware_type);
    utilsPrintIndentedString("Protocol Type  : ");
    utilsPrintUint16(header->protocol_type);

    utilsPrintIndentedString("Hardw Addr Len : ");
    utilsPrintHexByte(header->hardware_addr_len);
    utilsPrintIndentedString("Proto Addr Len : ");
    utilsPrintHexByte(header->protocol_addr_len);
    utilsPrintIndentedString("Operation      : ");
    utilsPrintInt(header->operation);

    utilsPrintIndentedString("Sender Mac     : ");
    utilsPrintMacAddress(header->sender_mac);
    utilsPrintIndentedString("Sender Ip      : ");
    utilsPrintIpAddress(header->sender_ip);

    utilsPrintIndentedString("Target Mac     : ");
    utilsPrintMacAddress(header->target_mac);
    utilsPrintIndentedString("Target Ip      : ");
    utilsPrintIpAddress(header->target_ip);
    utilsWriteLine(0);
    utilsWriteLine(0);
}

void arpPrepareResponce(ArpHeader *arp_rcv, ArpHeader *arp_tx, uint8_t * mac_addr)
{
    arp_tx->hardware_type = arp_rcv->hardware_type;
    arp_tx->protocol_type = arp_rcv->protocol_type;
    arp_tx->hardware_addr_len = arp_rcv->hardware_addr_len;
    arp_tx->protocol_addr_len = arp_rcv->protocol_addr_len;
    arp_tx->operation = 2; //reply

    memcpy(arp_tx->sender_mac, mac_addr, 6);
    memcpy(arp_tx->sender_ip, arp_rcv->target_ip, 4);

    memcpy(arp_tx->target_mac, arp_rcv->sender_mac, 6);
    memcpy(arp_tx->target_ip, arp_rcv->sender_ip, 4);
}

uint16_t arpHeaderToBuffer(ArpHeader *arp_header, uint8_t * buffer)
{
    buffer[0] = arp_header->hardware_type >> 8;
    buffer[1] = arp_header->hardware_type & 0xFF;

    buffer[2] = arp_header->protocol_type >> 8;
    buffer[3] = arp_header->protocol_type & 0xFF;

    buffer[4] = arp_header->hardware_addr_len;
    buffer[5] = arp_header->protocol_addr_len;

    buffer[6] = arp_header->operation >> 8;
    buffer[7] = arp_header->operation & 0xFF;
    
    buffer += 8;

    memcpy(buffer, arp_header->sender_mac, 6);
    buffer += 6;
    memcpy(buffer, arp_header->sender_ip, 4);
    buffer += 4;

    memcpy(buffer, arp_header->target_mac, 6);
    buffer += 6;
    memcpy(buffer, arp_header->target_ip, 4);
    
    return ARP_HEADER_SIZE;
}