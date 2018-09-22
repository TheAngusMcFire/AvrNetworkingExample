#include <ip.h>
#include <uart.h>
#include <utils.h>
#include <string.h>

uint8_t ipParseHeader(IpHeader *header, uint8_t *buffer, uint16_t rcv_size)
{
    if(rcv_size < IP_HEADER_MIN_SIZE)
        return IP_HEADER_FAIL;

    uint8_t *tmp_buffer = buffer;

    header->version =       (buffer[0] >> 4) & 0x0f;
    header->header_length = (buffer[0] >> 0) & 0x0f;
    header->header_length *= 4;

    header->type_of_service = buffer[1];
    header->total_length  = buffer[2] << 8;
    header->total_length += buffer[3] << 0;

    header->identification  = buffer[4] << 8;
    header->identification += buffer[5] << 0;

    header->flags = buffer[6] >> 5;

    header->fragment_offset  = (buffer[6] & 0b11111) << 8;
    header->fragment_offset += (buffer[7]) << 0;

    header->ttl = buffer[8];
    header->protocol = buffer[9];

    header->header_checksum  = buffer[10] << 8;
    header->header_checksum += buffer[11] << 0;

    buffer += 12;

    memcpy(header->src_addr, buffer, 4);
    buffer += 4;
    memcpy(header->dst_addr, buffer, 4);

    header->payload_size = header->total_length - header->header_length;
    header->payload_ptr = tmp_buffer + header->header_length;

    return IP_HEADER_OK;
}