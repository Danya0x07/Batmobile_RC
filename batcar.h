#pragma once

#include <avr/io.h>

void set_batcar_direction(uint8_t);
void set_batcar_speeds(uint8_t, uint8_t, uint8_t);
void refresh_batcar(uint8_t, uint8_t, uint8_t);
void refresh_cruising_batcar(uint8_t, uint8_t, uint8_t);
