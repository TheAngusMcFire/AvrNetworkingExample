#include <uart.h>
#include <network_controller.h>
#include <udp.h>
#include <utils.h>
#include <ethernet.h>
#include <arp.h>
#include <string.h>
#include <ip.h>
#include <net_utils.h>

uint8_t buffer[900-67];
uint8_t tx_buffer[100];
uint8_t mac_addr[] = {0x80,0xe6,0x00,0x00,0x02,0xff};
uint8_t ip_addr[] = {192,168,1,230};

EthernetHeader eth_header_rcv;
EthernetHeader eth_header_tx;

ArpHeader      arp_header_rcv;
ArpHeader      arp_header_tx;

IpHeader       ip_header_rcv;
IpHeader       ip_header_tx;

int main()
{
    uartInit();
    utilsWriteLine("Startup Net code");
    networkControllerInit(mac_addr);
    utilsWriteLine("NC init fin...");

    while(1)
    {
        uint16_t data_size = networkControllerReadByteStream(buffer, sizeof(buffer));
        
        if(data_size == 0)
            continue;


        ethernetParseHeader(&eth_header_rcv, buffer, data_size);

        if(eth_header_rcv.eth_type == ETH_TYPE_ARP)
        {
            arpParseHeader(&arp_header_rcv, eth_header_rcv.payload_ptr, eth_header_rcv.payload_size);

            if(memcmp(arp_header_rcv.target_ip, ip_addr, 4))
                continue;

            utilsPrintSeperator();
            ethernetPrintHeader(&eth_header_rcv);
            arpPrintHeader(&arp_header_rcv);            

            arpPrepareResponce(&arp_header_rcv, &arp_header_tx, mac_addr);
            arpPrintHeader(&arp_header_tx);

            ethernetBuildHeader(&eth_header_tx, eth_header_rcv.src_mac, mac_addr, ETH_TYPE_ARP);
            ethernetPrintHeader(&eth_header_tx);

            uint8_t * tmp_buffer = buffer;

            tmp_buffer += ethernetHeaderToBuffer(&eth_header_tx, tmp_buffer);
            tmp_buffer += arpHeaderToBuffer(&arp_header_tx, tmp_buffer);

            uint16_t data_size = (uint16_t)(tmp_buffer - buffer);
            uartWriteString("Data to write: ");
            utilsPrintHex(buffer, data_size);
            networkControllerWriteByteStream(buffer, data_size);
        }

        if(eth_header_rcv.eth_type == ETH_TYPE_IPv4)
        {
            ipParseHeader(&ip_header_rcv, eth_header_rcv.payload_ptr, eth_header_rcv.payload_size);
            
            //ICMP
            if(ip_header_rcv.protocol == 0x01)
            {
                //ipPrintHeader(&ip_header_rcv);
                if(ip_header_rcv.payload_ptr[0] != 8)
                    continue;

                uartWriteString("Echo(ping) recieved from: ");
                utilsPrintIpAddress(ip_header_rcv.src_addr);
                uartWriteString("\r\n");

                uint8_t icmp_size = icmpPrepareResponce(ip_header_rcv.payload_ptr,ip_header_rcv.payload_size,tx_buffer,sizeof(tx_buffer));
                ethernetBuildHeader(&eth_header_tx, eth_header_rcv.src_mac, mac_addr, ETH_TYPE_IPv4);
                ipPrepareHeader(&ip_header_tx,ip_header_rcv.src_addr,ip_addr,1, icmp_size);

                uint8_t *tmp_buffer = buffer;

                tmp_buffer += ethernetHeaderToBuffer(&eth_header_tx, tmp_buffer);
                tmp_buffer += ipHeaderToBuffer(&ip_header_tx, tmp_buffer);
                memcpy(tmp_buffer,tx_buffer,icmp_size);
                tmp_buffer+=icmp_size;
                uint16_t data_size = (uint16_t)(tmp_buffer - buffer);
                
                //uartWriteString("Data to write: ");
                //utilsPrintHex(buffer, data_size);
                
                networkControllerWriteByteStream(buffer, data_size);
            }
        }        
    }

    return 0;
}