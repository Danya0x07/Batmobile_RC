#pragma once

#include <avr/io.h>

#define admux_clear()   ADMUX &= ~(_BV(MUX3) | _BV(MUX2)| _BV(MUX1) | _BV(MUX0))
#define JOY_X_BITS  (_BV(MUX0))
#define JOY_Y_BITS  0

#define ACCURACY    15
#define S1_L_LIM    5
#define S1_R_LIM    10  
#define S2_L_LIM    3
#define S2_R_LIM    12
#define S3_L_LIM    1
#define S3_R_LIM    14

enum Directions {
    NONE,
    FORWARD,
    BACKWARD,
    LEFTWARD,
    RIGHTWARD,
    // только у джостика
    LEFTFRONT,
    RIGHTFRONT,
    LEFTBACK,
    RIGHTBACK
};

void joy_init(void);
uint16_t joyX_get(void);
uint16_t joyY_get(void);
uint8_t joy_abs_pos(uint8_t);
uint8_t joy_direction(uint8_t, uint8_t);
uint8_t joy_inverse(uint8_t);
