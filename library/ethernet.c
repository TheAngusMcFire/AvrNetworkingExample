#include <ethernet.h>
#include <uart.h>
#include <utils.h>

uint8_t ethernetParseHeader(EthernetHeader *eth_header, uint8_t *buffer, uint16_t rcv_size)
{
    if(rcv_size < ETH_MIN_SIZE)
        return ETH_HEADER_FAIL;

    for(uint8_t index = 0; index < 6; index++)
        eth_header->dst_mac[index] = buffer[index];

    buffer += 6;

    for(uint8_t index = 0; index < 6; index++)
        eth_header->src_mac[index] = buffer[index];

    buffer += 6;

    eth_header->eth_types  = 0;
    eth_header->eth_types |= buffer[0] << 8;
    eth_header->eth_types |= buffer[1] << 0;

    buffer += 2;

    eth_header->payload_ptr = buffer;
    eth_header->payload_size = rcv_size - (6 + 6 + 2);

    return ETH_HEADER_OK;
}

void ethernetPrintHeader(EthernetHeader *eth_header)
{
    uartWriteString("\r\nEthernet Header: ");
    uartWriteString("\r\n    Destination MAC : ");
    utilsPrintHex(eth_header->dst_mac, 6);

    uartWriteString("    Source MAC      : ");
    utilsPrintHex(eth_header->src_mac, 6);

    uartWriteString("    Ethernet Type   : 0x");
    utilsPrintHexByte(eth_header->eth_types >> 8);
    utilsPrintHexByte(eth_header->eth_types & 0xFF);

    uartWriteString("\r\n    Payload Size    : ");
    utilsPrintInt(eth_header->payload_size);

    if(eth_header->payload_size < 50)
    {
        uartWriteString("\r\n    Payload         : \r\n    ");
        utilsPrintHex(eth_header->payload_ptr, eth_header->payload_size);
    }
    
    uartWriteString("\r\n\r\n");
}