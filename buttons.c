/*
 * Hackday Function Pointers
 * Button Handler Example
 */
#include "buttons.h"

/* reference to the user-defined button setup */
static button_t *buttons;
/* number of entries in the array referenced by buttons */
static uint8_t button_count;

static uint8_t read_state(uint8_t);


void buttons_init(button_t *data, uint8_t count)
{
    uint8_t index;

    buttons = data;
    button_count = count;

    /* read and store each button's current state */
    for (index = 0; index < button_count; index++) {
        buttons[index].state = read_state(index);
    }
}

void buttons_poll(void)
{
    uint8_t index;
    button_t *button;

    for (index = 0; index < button_count; index++) {
        /*
         * pointer to current array element for easier handling.
         * lets us use button->foo instead of buttons[i].foo
         */
        button = &buttons[index];
        
        /* copy last state */
        button->laststate = button->state;
        /* read and store new state */
        button->state = read_state(index);

        /* check if state has changed */
        if (button->state != button->laststate) {
            /* check if new state is "button pressed" */
            if (button->state == PRESSED) {
                /* check if we have a press handler */
                if (button->press) {
                    /* yes, execute it */
                    button->press();
                }

            /* must be "button released" then */
            } else {
                /* check if we have a release handler */
                if (button->release) {
                    /* yes, execute it */
                    button->release();
                }
            }
        }
    }
}


/*
 * read the value from the GPIO port
 * see #define PRESSED in buttons.h if values seem inverted
 */
uint8_t read_state(uint8_t index)
{
    /*
     * add debounce functionality here if needed
     * or add debounce function user can set, which is then called here
     */

    return (*buttons[index].port >> buttons[index].pin) & 0x01;
}

