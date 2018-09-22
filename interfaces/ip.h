#include <stdint.h>

#ifndef INTERFACES_IP_H
#define INTERFACES_IP_H

typedef struct
{
    uint8_t version;
    uint8_t header_length;
    uint8_t type_of_service;
    uint16_t total_length;
    uint16_t identification;
    uint8_t flags;
    uint16_t fragment_offset;
    uint8_t ttl;
    uint8_t protocol;
    uint16_t header_checksum;
    uint8_t src_addr[4];
    uint8_t dst_addr[4];

    uint16_t payload_size;
    uint8_t *payload_ptr;
}IpHeader;

#define IP_HEADER_OK 0
#define IP_HEADER_FAIL 1

#define IP_HEADER_MIN_SIZE 20

uint8_t ipParseHeader(IpHeader *header, uint8_t *buffer, uint16_t rcv_size);

#endif