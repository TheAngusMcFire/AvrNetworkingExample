#include <uart.h>
#include <device.h>


void uartInit()
{
    uint8_t baudrate = (uint8_t)(F_CPU / (16lu * BAUD_RATE)) - 1lu;

    UBRRH = 103 >> 8;
	UBRRL = 103;    

    UCSRB = _BV(RXEN) | _BV(TXEN);
    UCSRC = _BV(URSEL) | ( 3 << UCSZ0);
}

void uartWriteChar(char chr)
{
    while (!(UCSRA & _BV(UDRE)))
        __asm volatile ("nop");
        
    UDR = chr;
}

char uartGetChar()
{
    while (!(UCSRA & _BV(RXC)))
        __asm volatile ("nop");
    
    return UDR;
}

void uartWriteString(const char* str)
{
    while(*str)
        uartWriteChar(*str++);
}