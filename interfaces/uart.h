#ifndef INTERFACES_UART_H
#define INTERFACES_UART_H

#define BAUD_RATE 9600lu

void uartInit();
void uartWriteChar(char chr);
char uartGetChar();

void uartWriteString(const char* str);

#endif