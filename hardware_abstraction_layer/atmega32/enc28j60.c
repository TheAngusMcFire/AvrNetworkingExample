#include <network_controller.h>
#include <spi.h>
#include <device.h>


void networkControllerInit()
{
    spiInit();
}

uint8_t networkControllerReadByteStream(uint8_t *buffer, uint16_t size)
{
    return 0;
}

uint8_t networkControllerWriteByteStream(uint8_t *buffer, uint16_t size)
{


    return 0;
}