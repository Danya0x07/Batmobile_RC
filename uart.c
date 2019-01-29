#include "uart.h"
#include <avr/interrupt.h>

void UART_init(uint32_t bdr)
{
    UBRR0H = (uint8_t)(bdr >> 8);
    UBRR0L = (uint8_t)bdr;
    UCSR0B = _BV(TXEN0) | _BV(RXEN0);
    UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);
}

void UART_send(uint8_t ch)
{
    while(!(UCSR0A & _BV(UDRE0)));
    UDR0 = ch;
}
