#include <stdint.h>
#ifndef INTERFACES_ARP_H
#define INTERFACES_ARP_H

typedef struct
{
    uint16_t hardware_type;
    uint16_t protocol_type;
    uint8_t  hardware_addr_len;
    uint8_t  protocol_addr_len;
    uint16_t operation;
    uint8_t  sender_mac[6];
    uint8_t  sender_ip [4];
    uint8_t  target_mac[6];
    uint8_t  target_ip [4];
}ArpHeader;

#define ARP_HEADER_OK 0
#define ARP_HEADER_FAIL 1

//see ArpHeader struct for details
#define ARP_HEADER_SIZE (2 + 2 + 1 + 1 + 2 + 6 + 4 + 6 +4)

uint8_t arpParseHeader(ArpHeader *arp_header, uint8_t *buffer, uint16_t rcv_size);
void    arpPrintHeader(ArpHeader *eth_header);

#endif