#include <uart.h>
#include <network_controller.h>
#include <udp.h>

int main()
{
    uartInit();
    networkControllerInit();

    uartWriteString("Hello this is the Netwok code\n");

    while(1)
    {

    }

    return 0;
}