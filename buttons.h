#pragma once
#include <avr/io.h>

#define CRUISE_BTN_dir  DDRC
#define CRUISE_BTN_pin  PINC
#define CRUISE_BTN_bit  PC2

#define TARAN_BTN_dir  DDRB
#define TARAN_BTN_pin  PINB
#define TARAN_BTN_bit  PB2

#define WPULL_BTN_dir  DDRB
#define WPULL_BTN_pin  PINB
#define WPULL_BTN_bit  PB0

#define WDROP_BTN_dir  DDRB
#define WDROP_BTN_pin  PINB
#define WDROP_BTN_bit  PB1

typedef struct {
    volatile uint8_t* pin;
    uint8_t bit;
    _Bool mode;
    _Bool last;
    _Bool current;
} Button_t;

extern Button_t btn_cruise;
extern Button_t btn_taran;
extern Button_t btn_wpull;
extern Button_t btn_wdrop;

void btn_init(void);
_Bool pressed(Button_t*);
