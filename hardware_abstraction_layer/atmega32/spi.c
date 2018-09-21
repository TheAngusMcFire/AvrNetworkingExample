#include <spi.h>
#include <device.h>

void spiCsActive()
{
    PORTB &= ~_BV(4);
}

void spiCsPassive()
{
    PORTB |= _BV(4);
}

void spiWait()
{
    while(!(SPSR & _BV(SPIF)))
        __asm volatile("nop");
}

void spiWrite(uint8_t data)
{
    SPDR = data;
    spiWait();
}

uint8_t spiRead()
{
    return SPDR;
}

void spiInit()
{
    DDRB &= ~(_BV(4) | _BV(5) | _BV(6) | _BV(7)); //clear miso mosi sck cs
    DDRB |= _BV(4) | _BV(5) | _BV(7); //set mosi sck cs

    PORTB &= ~(_BV(7) | _BV(5)); //clear pullup for sck cs

    SPCR  = _BV(SPE) | _BV(MSTR);
    SPSR |= _BV(SPI2X);
}