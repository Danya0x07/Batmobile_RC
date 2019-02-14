#pragma once

#include <avr/io.h>

void set_batcar_direction(uint8_t);
void set_batcar_speeds(uint8_t, uint8_t, uint8_t);
void refresh_movement(uint8_t, uint8_t, uint8_t);
void refresh_acceleration(uint8_t, uint8_t, uint8_t);
