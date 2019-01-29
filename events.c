#include "events.h"
#include "buttons.h"
#include "uart.h"
#include "leds.h"
#include "joystic.h"
#include "batcar.h"

static uint8_t mode = NORMAL;
static uint8_t direction;
static uint8_t x_spd, y_spd;
static uint8_t x_abs, y_abs;

void handle_btn_events(void)
{
    // потянуть лебёдку
    if(pressed(&btn_wpull)) {
        if(btn_wpull.mode == 1) {
            UART_send(WINCH_PULL);
            btn_wpull.mode = 0;
        } else {
            UART_send(WINCH_STOP);
            btn_wpull.mode = 1;
        }
    }
    // отпустить лебёдку
    if(pressed(&btn_wdrop)) {
        if(btn_wdrop.mode == 1) {
            UART_send(WINCH_DROP);
            btn_wdrop.mode = 0;
        } else {
            UART_send(WINCH_STOP);
            btn_wdrop.mode = 1;
        }
    }
    // режим круиза
    if(pressed(&btn_cruise)) {
        if(mode != CRUISE) {
            mode = CRUISE;
            UART_send(CRUISE_ON);
            CML_led_on();
        } else {
            mode = NORMAL;
            UART_send(CRUISE_OFF);
            CML_led_off();
        }
    }
    // режим тарана
    if(pressed(&btn_taran)) {
        if(mode != TARAN) {
            mode = TARAN;
            UART_send(TARAN_ON);
            TML_led_on();
        } else {
            mode = NORMAL;
            UART_send(TARAN_OFF);
            TML_led_off();
        }
    }
}

void handle_joy_events(void)
{
    x_spd = joyX_get();
    y_spd = joyY_get();
    direction = joy_direction(x_spd, y_spd);
    x_abs = joy_abs_pos(x_spd);
    y_abs = joy_abs_pos(y_spd);
    update_spd_leds(x_abs, y_abs);
    if(mode == CRUISE) {
        refresh_cruising_batcar(direction, x_abs, y_abs);
    } else {
        if(mode == TARAN)
            direction = joy_inverse(direction);
        refresh_batcar(direction, x_abs, y_abs);
    }
    
}
