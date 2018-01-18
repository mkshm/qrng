
cflags=-mmcu=atmega328p -Wall -Werror -Wextra -Os
objs=$(patsubst %.c,%.o,$(wildcard *.c))

.PHONY: flash clean

all: main.hex

%.o: %.c
	avr-gcc $(cflags) -c $< -o $@

main.elf: $(objs)
	avr-gcc $(cflags) -o $@ $^

main.hex: main.elf
	avr-objcopy -j .text -j .data -O ihex $^ $@

flash: main.hex
	avrdude -p m328p -c arduino -p /dev/ttyUSB0 -b 115200 -v -U flash:w:$<

clean:
	rm -f main.hex main.elf $(objs)
