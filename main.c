/*
 * Hackaday Function Pointers
 * Example implementation
 *
 * Implemented for AVR ATmega328P with three buttons:
 *      #1  PC0
 *      #2  PC1
 *      #3  PC2
 *
 */
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include "buttons.h"

/* prototypes for handler functions */
void press_something(void);
void press_something_else(void);
void press_even_more(void);
void generic_release(void);


/* our user-defined button setup data */
button_t buttons[] = {
    {
        /* first button, PC0 */
        .port = &PINC,
        .pin = 0,
        .press = press_something,
        .release = generic_release,
    },
    {
        /* second button, PC1 */
        .port = &PINC,
        .pin = 1,
        .press = press_something_else,
        .release = NULL,
    },
    {
        /* third button, PC2 */
        .port = &PINC,
        .pin = 2,
        .press = press_even_more,
        .release = generic_release,
    },
    /* need more buttons? just add another entry */
};


void press_something(void)
{
    /* called when first button is pressed */
}

void press_something_else(void)
{
    /* called when second button is pressed */
}

void press_even_more(void)
{
    /* called when third button is pressed */
}

void generic_release(void)
{
    /*
     * called when first or second button is released, but not second button
     * nothing happens when second button is released, handler is NULL
     */
}


int main(void)
{
    /* set all of port C as input */
    DDRC  = 0x00;
    /* enable pull-ups on all inputs */
    PORTC = 0xff;

    /* initialize buttons with our defined array */
    buttons_init(buttons, (sizeof buttons / sizeof buttons[0]));

    while (1) {
        /* poll forever */
        buttons_poll();
        /* and wait a bit */
        _delay_ms(10);
    }
    return 0;
}

