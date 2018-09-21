#include <avr/io.h>

#ifndef F_CPU
#define F_CPU 16000000lu
#endif

static void __attribute__((optimize("O4"))) __attribute__((unused)) delayUs(uint8_t delay)
{
    do
    {
        __asm volatile("nop\n nop\n nop\n nop\n");
        __asm volatile("nop\n nop\n nop\n nop\n");
        __asm volatile("nop\n nop\n nop\n nop\n");
        __asm volatile("nop\n nop\n");
    } while (delay--);
}