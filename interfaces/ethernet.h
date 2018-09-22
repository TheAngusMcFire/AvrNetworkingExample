#include <stdint.h>

#ifndef INTERFACES_ETHERNET_H
#define INTERFACES_ETHERNET_H

#define ETH_MIN_SIZE 46

#define ETH_HEADER_OK   0
#define ETH_HEADER_FAIL 1 
 
enum ETH_TYPES
{
    ETH_TYPE_IPv4       = 0x0800,
    ETH_TYPE_IPv6       = 0x86DD,    
    ETH_TYPE_ARP        = 0x0806,
    ETH_TYPE_UNICAST    = 0x8847,
    ETH_TYPE_MULTICAST  = 0x8848,
};

typedef struct 
{
    uint8_t  dst_mac[6];
    uint8_t  src_mac[6];
    uint16_t eth_types;
    uint16_t payload_size;
    uint8_t *payload_ptr;
}EthernetHeader;

uint8_t ethernetParseHeader(EthernetHeader *eth_header, uint8_t *buffer, uint16_t rcv_size);
void    ethernetPrintHeader(EthernetHeader *eth_header);

#endif