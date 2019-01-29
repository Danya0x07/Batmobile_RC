#include "uart.h"
#include "joystic.h"
#include "buttons.h"
#include "leds.h"
#include "events.h"


int main(void)
{
    joy_init();
    btn_init();
    UART_init(8);
    led_init();
    while(1)
    {
        handle_btn_events();
        handle_joy_events();
    }
}
