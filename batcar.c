#include "batcar.h"
#include "uart.h"
#include "joystic.h"

static const uint8_t speeds[4] = {0, 85, 170, 255};
static const int8_t fades[4] = {0, 5, 15, 25};
static uint8_t x_abs_last = 0, y_abs_last = 0;
static uint8_t dir_last = NONE;

void set_batcar_direction(uint8_t dir)
{
    UART_send(SET_DIRECTION);
    switch(dir) {
        case RIGHTFRONT: UART_send(RIGHTWARD); break;
        case LEFTFRONT:  UART_send(LEFTWARD);  break;
        case RIGHTBACK:  UART_send(LEFTWARD);  break;
        case LEFTBACK:   UART_send(RIGHTWARD); break;
        default:
            UART_send(dir);
    }
}

void set_batcar_speeds(uint8_t dir, uint8_t x_abs, uint8_t y_abs)
{
    UART_send(SET_SPEED);
    switch(dir) {
        case NONE:
            UART_send(0);
            UART_send(0);
            break;
        case RIGHTFRONT:
        case LEFTBACK:
            UART_send(speeds[y_abs]);
            UART_send(speeds[2]);
            break;
        case LEFTFRONT:
        case RIGHTBACK:
            UART_send(speeds[2]);
            UART_send(speeds[y_abs]);
            break;
        case FORWARD:
        case BACKWARD:
            UART_send(speeds[y_abs]);
            UART_send(speeds[y_abs]);
            break;
        case LEFTWARD:
        case RIGHTWARD:
            UART_send(speeds[x_abs]);
            UART_send(speeds[x_abs]);
            break;
    }
}

void refresh_batcar(uint8_t dir, uint8_t x_abs, uint8_t y_abs)
{
    if(dir != dir_last) {
        set_batcar_direction(dir);
        dir_last = dir;
    } 
    if(x_abs != x_abs_last || y_abs != y_abs_last) {
        set_batcar_speeds(dir, x_abs, y_abs);
        x_abs_last = x_abs;
        y_abs_last = y_abs;
    } 
}

void refresh_cruising_batcar(uint8_t dir, uint8_t x_abs, uint8_t y_abs)
{
    if(x_abs != x_abs_last || y_abs != y_abs_last) {
        UART_send(SET_FADE);
        switch(dir) {
            case NONE:
                UART_send(0);
                UART_send(0);
                break;
            case FORWARD:
                UART_send(fades[y_abs]);
                UART_send(fades[y_abs]);
                break;
            case BACKWARD:
                UART_send(-fades[y_abs]);
                UART_send(-fades[y_abs]);
                break;
            case LEFTWARD:
            case LEFTFRONT:
            case LEFTBACK:
                UART_send(-fades[x_abs]);
                UART_send(fades[x_abs]);
                break;
            case RIGHTWARD:
            case RIGHTFRONT:
            case RIGHTBACK:
                UART_send(fades[x_abs]);
                UART_send(-fades[x_abs]);
                break;
        }
        x_abs_last = x_abs;
        y_abs_last = y_abs;
    }
}
