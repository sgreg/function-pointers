# Hackaday Function Pointers Example

A generic push button handler as practical demonstration of function pointers -- see Hackaday article [*Directly Executing Chunks of Memory: Function Pointers In C*](http://hackaday.com/2018/05/02/directly-executing-chunks-of-memory-function-pointers-in-c/).

## Content

The example consists of two parts:
1. the button handler itself
    * `buttons.h` header file
    * `buttons.c` source file
2. an example implementation for AVR ATmega328P
    * `main.c` main file using the button handler
    * `Makefile` to easily build and flash

## Usage

### Button handler
The push buttons are set up as a `button_t` struct defining the GPIO port and pin, and a handler function for each press and release event. The handlers are optional and can be `NULL`, in which case nothing will happen for that specific button at the event.
```
void some_press_handler(void)
{
    ...
}
```
```
button_t buttons[] = {
    {
        .port = &INPUT_PORT_REGISTER,
        .pin = PIN_NUMBER,
        .press = some_press_handler,
        .release = NULL,
    },
    ...
};
```

The buttons are initialized with the `buttons_init()` function, passing the array with the button setup data along with the amount of entries in that array
```
buttons_init(buttons, sizeof buttons / sizeof buttons[0]);
```

To keep things easy, the button states are meant to be polled periodically
```
    while (1) {
        buttons_poll();
        ...
    }
```

That's it.

Whenever a push button is pressed or released, the defined handler functions will be called.

### AVR ATmega328P example

The example implementation is meant for an AVR ATmega328P running at 8MHz clock speed, using `avr-gcc` for compiling and `avrdude` for flashing with the USBasp programmer. Check the `Makefile` if you want to use a different AVR microcontroller or have a different programmer.

#### Other platforms?

If you want to use the handler on a different platform (PIC, MSP430, ...), you should be able to use the button handler itself as-is (well, that's kinda the whole point of it), but you will have to adjust the `main.c` file accordingly, and handle your own `Makefile` somehow (or use an IDE).
* GPIO port name in `buttons` needs to be changed to you your target controller's register names
* GPIO pin number in `buttons` accordingly
* GPIO setup in the very beginning of `main()` that defines the data direction and pull-up resistors.
