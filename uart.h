#pragma once
#include <avr/io.h>

enum Commands {
    SET_SPEED,
    SET_DIRECTION,
    WINCH_PULL,
    WINCH_DROP,
    WINCH_STOP,
    TARAN_ON,
    CRUISE_ON,
    NORMAL_MODE,
    SET_FADE
};

void UART_init(uint32_t);
void UART_send(uint8_t);
