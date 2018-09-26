#include <net_utils.h>
#include <utils.h>
#include <string.h>

uint8_t icmpPrepareResponce(uint8_t *rcv_buffer, uint16_t rcv_size, uint8_t *tx_buffer, uint8_t tx_buff_size)
{
    memcpy(tx_buffer, rcv_buffer, rcv_size);

    tx_buffer[0] = 0;
    tx_buffer[2] = 0;
    tx_buffer[3] = 0;

    uint16_t crc = utilsCalcChecksum(tx_buffer, rcv_size);

    tx_buffer[3] = crc >> 8;
    tx_buffer[2] = crc & 0xff;

    return rcv_size;
}