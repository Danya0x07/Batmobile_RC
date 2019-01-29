#include "leds.h"

void led_init(void)
{
    LED_dir |= _BV(SL1_bit) | _BV(SL2_bit) | _BV(SL3_bit)
            | _BV(TML_bit) | _BV(CML_bit);
    LED_port &= ~(_BV(SL1_bit) | _BV(SL2_bit) | _BV(SL3_bit)
                | _BV(TML_bit) | _BV(CML_bit));
}

void update_spd_leds(uint8_t x_spd, uint8_t y_spd)
{
    if(x_spd >= 1 || y_spd >= 1)
        LED_port |= _BV(SL1_bit);
    else
        LED_port &= ~_BV(SL1_bit);
    if(x_spd >= 2 || y_spd >= 2)
        LED_port |= _BV(SL2_bit);
    else
        LED_port &= ~_BV(SL2_bit);
    if(x_spd >= 3 || y_spd >= 3)
        LED_port |= _BV(SL3_bit);
    else
        LED_port &= ~_BV(SL3_bit);
}
