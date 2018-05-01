/*
 * Hackday Function Pointers
 * Button Handler Example
 */
#ifndef BUTTONS_H
#define BUTTONS_H
#include <stdint.h>

/*
 * value read from GPIO port if button is pressed
 * depending on setup and wiring, button can be either active low and
 * reading 0 means pressed, or active high, and reading 1 means pressed
 */
#define PRESSED 0


/* button handler type, pointer to function of type void foo(void) */
typedef void (*button_handler_t)(void);

/*
 * struct to define a button, typedef'd to type button_t
 *
 * - define's the GPIO port and pin the button is attached to
 * - stores the current and last button states (pressed / released)
 * - contains the handler functions for each state
 *
 */
typedef struct button {
    /* GPIO data register */
    volatile uint8_t *port;
    /* GPIO pin */
    uint8_t pin;
    /* current button state, handled internally */
    uint8_t state;
    /* previous button state, handled internally */
    uint8_t laststate;
    /* handler function called when button is pressed, can be NULL */
    button_handler_t press;
    /* handler function called when button is released, can be NULL */
    button_handler_t release;
} button_t;

/*
 * initialize buttons with given data.
 */
void buttons_init(button_t *data, uint8_t count);

/*
 * read all button states and calls their handlers if state has changed
 */
void buttons_poll(void);

#endif /* BUTTONS_H */
