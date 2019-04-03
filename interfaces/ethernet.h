#include <stdint.h>

#ifndef INTERFACES_ETHERNET_H
#define INTERFACES_ETHERNET_H

#define ETH_MIN_SIZE 46
#define ETH_HEADER_SIZE (6 + 6 + 2)

#define ETH_HEADER_OK   0
#define ETH_HEADER_FAIL 1 
 
#define ETH_TYPE_IPv4      (0x0800)
#define ETH_TYPE_IPv6      (0x86DD)    
#define ETH_TYPE_ARP       (0x0806)
#define ETH_TYPE_UNICAST   (0x8847)
#define ETH_TYPE_MULTICAST (0x8848)


typedef struct 
{
    uint8_t  dst_mac[6];
    uint8_t  src_mac[6];
    uint16_t eth_type;
    uint16_t payload_size;
    uint8_t *payload_ptr;
}EthernetHeader;

uint8_t  ethernetParseHeader(EthernetHeader *eth_header, uint8_t *buffer, uint16_t rcv_size);
void     ethernetPrintHeader(EthernetHeader *eth_header);
void     ethernetBuildHeader(EthernetHeader *eth_header, uint8_t *dst_mac, uint8_t *src_mac, uint16_t eth_type);
uint16_t ethernetHeaderToBuffer(EthernetHeader *eth_header, uint8_t * buffer);


#endif