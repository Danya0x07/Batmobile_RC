#pragma once
#include <avr/io.h>

#define LED_dir     DDRD
#define LED_port    PORTD
#define SL1_bit PD4
#define SL2_bit PD3
#define SL3_bit PD2
#define TML_bit PD5
#define CML_bit PD6

#define TML_led_on()    LED_port |= _BV(TML_bit)
#define TML_led_off()   LED_port &= ~_BV(TML_bit)
#define CML_led_on()    LED_port |= _BV(CML_bit)
#define CML_led_off()   LED_port &= ~_BV(CML_bit)

void led_init(void);
void update_spd_leds(uint8_t, uint8_t);
