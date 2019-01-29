#include "buttons.h"
#include <util/delay.h>

Button_t btn_cruise = {&CRUISE_BTN_pin, CRUISE_BTN_bit, 1, 0, 0};
Button_t btn_taran = {&TARAN_BTN_pin, TARAN_BTN_bit, 1, 0, 0};
Button_t btn_wpull = {&WPULL_BTN_pin, WPULL_BTN_bit, 1, 0, 0};
Button_t btn_wdrop = {&WDROP_BTN_pin, WDROP_BTN_bit, 1, 0, 0};

void btn_init(void)
{
    CRUISE_BTN_dir &= ~_BV(CRUISE_BTN_bit);
    TARAN_BTN_dir &= ~_BV(TARAN_BTN_bit);
    WPULL_BTN_dir &= ~_BV(WPULL_BTN_bit);
    WDROP_BTN_dir &= ~_BV(WDROP_BTN_bit);
}

_Bool pressed(Button_t* btn)
{
    btn->current = *btn->pin & _BV(btn->bit);
    if(btn->last != btn->current) {
        _delay_ms(5);
        btn->current = *btn->pin & _BV(btn->bit);
    } else return 0;
    
    _Bool pressed;
    if(!btn->last && btn->current) pressed = !btn->mode;
    else if(btn->last && !btn->current) pressed = btn->mode;
    else pressed = 0;
    
    btn->last = btn->current;
    return pressed;
}
