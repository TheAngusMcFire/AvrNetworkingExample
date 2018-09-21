#include <uart.h>
#include <udp.h>

int main()
{
    uartInit();

    uartWriteString("Hello this is the Netwok code");

    while(1)
    {

    }

    return 0;
}