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

void ipPrintHeader(IpHeader *header)
{
    utilsWriteLine(0);
    uartWriteString("Ipv4 Header : ");
    utilsPrintIndentedString("Version      : ");
    utilsPrintInt(header->version);
    utilsPrintIndentedString("Hdr Length   : ");
    utilsPrintInt(header->header_length);
    utilsPrintIndentedString("Type of Ser. : ");
    utilsPrintInt(header->type_of_service);
    utilsPrintIndentedString("Total Length : ");
    utilsPrintInt(header->total_length);
    utilsPrintIndentedString("Identific.   : ");
    utilsPrintInt(header->identification);
    utilsPrintIndentedString("Flags        : ");
    utilsPrintInt(header->flags);
    utilsPrintIndentedString("Frag Offset  : ");
    utilsPrintInt(header->fragment_offset);
    utilsPrintIndentedString("Time to Live : ");
    utilsPrintInt(header->ttl);
    utilsPrintIndentedString("Protocol     : ");
    utilsPrintInt(header->protocol);
    utilsPrintIndentedString("Hdr Checksum : ");
    utilsPrintUint16(header->header_checksum);
    utilsPrintIndentedString("Src Address  : ");
    utilsPrintIpAddress(header->src_addr);
    utilsPrintIndentedString("Dst Addr.    : ");
    utilsPrintIpAddress(header->dst_addr);
    utilsPrintIndentedString("Payload Sz   : ");
    utilsPrintInt(header->payload_size);

    utilsPrintIndentedString("Payload      : "); 

    if(header->payload_size > 0x40)
        utilsPrintHex(header->payload_ptr, 0x40);
    else
        utilsPrintHex(header->payload_ptr, header->payload_size);
}

static uint16_t ipCalcChecksum(uint8_t *buffer, uint8_t size)
{
    uint32_t checksum = 0;
    uint16_t *check_data = (uint16_t *)buffer; 

    for(uint8_t index = 0; index < size; index++)
    {
        checksum += check_data[index];
    }

    if(size % 2 == 1)
        checksum = buffer[size -1];

    checksum = (checksum >> 16) + (checksum & 0xFFFF); //here it might overflow again
    checksum = (checksum >> 16) + (checksum & 0xFFFF);

    return ~((uint16_t) checksum); 
} 

uint16_t ipHeaderToBuffer(IpHeader *header, uint8_t *buffer)
{
    buffer[0] = header->version << 4;
    buffer[0] += header->header_length / 4;

    buffer[1] = header->type_of_service;
    
    buffer[2] = header->total_length >> 8;
    buffer[3] = header->total_length & 0xff;

    buffer[4] = header->identification >> 8;
    buffer[5] = header->identification & 0xff;

    buffer[6] = header->flags << 5;
    buffer[6] += (header->fragment_offset >> 8) & 0b11111;
    buffer[7] = header->fragment_offset & 0xFF;

    buffer[8] = header->ttl;
    buffer[9] = header->protocol;

    //header checksum
    buffer[10] = 0;
    buffer[11] = 0;

    memcpy(buffer + 12, header->src_addr, 4);
    memcpy(buffer + 16, header->dst_addr, 4);

    uint16_t checksum = ipCalcChecksum(buffer, 20);

    buffer[10] = checksum >> 8;
    buffer[11] = checksum & 0xFF;

    return IP_HEADER_MIN_SIZE;
}
