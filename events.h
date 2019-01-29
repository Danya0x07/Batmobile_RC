#pragma once

#include <avr/io.h>

enum Mode {
    NORMAL,
    CRUISE,
    TARAN
};

void handle_btn_events(void);
void handle_joy_events(void);
