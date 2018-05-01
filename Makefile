#
# Hackaday Function Pointers
#
# Makefile for the button handler example in main.c
# Uses avr-gcc and avrdude
#
# Variables are set up to compile for AVR ATmega328P running at
# 8MHz clock speed and to flash with the USBasp programmer.
#
# Adjust the following variables to change the setup:
#   MCU
#       set accordingly to match for both avr-gcc and avrdude
#   F_CPU
#       the clock speed in Hertz
#   PROGRAMMER
#       programmer to flash with avrdude
#       check `avrdude -c ?` for a list
#

MCU = atmega328p
F_CPU = 8000000
PROGRAMMER = usbasp

SRC = buttons.c main.c

CC = avr-gcc
CFLAGS += -Os -std=gnu99 -I. -fpack-struct -fshort-enums -Wall -Wextra -DF_CPU=$(F_CPU) -mmcu=$(MCU)

OBJCOPY = avr-objcopy

AVRDUDE = avrdude
AVRDUDE_FLAGS += -p $(MCU) -c $(PROGRAMMER)


.PHONY: all flash clean

all: buttons.hex

buttons.elf: $(SRC)
	$(CC) $(CFLAGS) $^ -o $@

buttons.hex: buttons.elf
	@$(OBJCOPY) -O ihex -R .eeprom $< $@

flash: buttons.hex
	$(AVRDUDE) $(AVRDUDE_FLAGS) -U flash:w:$<

clean:
	rm -f buttons.hex buttons.elf

