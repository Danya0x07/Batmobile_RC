#include "joystic.h"

void joy_init(void)
{
    ADCSRA = _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0) | _BV(ADEN);
}

uint16_t joyX_get(void)
{
    admux_clear();
    ADMUX |= JOY_X_BITS;
    ADCSRA |= _BV(ADSC);
    while(ADCSRA & _BV(ADSC));
    // Инверсия осей для корректного определения
    // направления отклонения после разворота
    return ACCURACY - ADC * ACCURACY / 1023;
}

uint16_t joyY_get(void)
{
    admux_clear();
    ADMUX |= JOY_Y_BITS;
    ADCSRA |= _BV(ADSC);
    while(ADCSRA & _BV(ADSC));
    // Инверсия осей для корректного определения
    // направления отклонения после разворота
    return ACCURACY - ADC * ACCURACY / 1023;
}

uint8_t joy_abs_pos(uint8_t p)
{
    if(p <= S3_L_LIM || p >= S3_R_LIM)
        return 3;
    else if(p <= S2_L_LIM || p >= S2_R_LIM)
        return 2;
    else if(p <= S1_L_LIM || p >= S1_R_LIM)
        return 1;
    else return 0;
}

uint8_t joy_direction(uint8_t x, uint8_t y)
{
    if(x >= S1_L_LIM && x <= S1_R_LIM) {
        if(y > S1_R_LIM) return FORWARD;
        else if(y < S1_L_LIM) return BACKWARD;
        else return NONE;
    } else {
        if(x > S1_R_LIM) {
            if(y > S1_R_LIM) return RIGHTFRONT;
            else if(y < S1_L_LIM) return RIGHTBACK;
            else return RIGHTWARD;
        } else if(x < S1_L_LIM) {
            if(y > S1_R_LIM) return LEFTFRONT;
            else if(y < S1_L_LIM) return LEFTBACK;
            else return LEFTWARD;
        }
    }
}

uint8_t joy_inverse(uint8_t dir)
{
    switch(dir) {
        case FORWARD: return BACKWARD;
        case BACKWARD: return FORWARD;
        case LEFTFRONT: return RIGHTBACK;
        case LEFTBACK: return RIGHTFRONT;
        case RIGHTFRONT: return LEFTBACK;
        case RIGHTBACK: return LEFTFRONT;
        default: return dir;
    }
}
