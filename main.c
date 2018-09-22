#include <uart.h>
#include <network_controller.h>
#include <udp.h>
#include <utils.h>
#include <ethernet.h>
#include <arp.h>

uint8_t buffer[1000];

EthernetHeader eth_header;
ArpHeader      arp_header;

int main()
{
    uartInit();
    uartWriteString("Hello this is the Netwok code\r\n");
    networkControllerInit();
    uartWriteString("Finished init of mc\r\n");


    while(1)
    {
        uint16_t data_size = networkControllerReadByteStream(buffer, sizeof(buffer));
        
        if(data_size == 0)
            continue;

        ethernetParseHeader(&eth_header, buffer, data_size);

        if(eth_header.eth_types != ETH_TYPE_ARP)
            continue;

        ethernetPrintHeader(&eth_header);   

        arpParseHeader(&arp_header, eth_header.payload_ptr, eth_header.payload_size);     

        arpPrintHeader(&arp_header);
    }

    return 0;
}