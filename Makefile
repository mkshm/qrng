
# $ @ = output
# $ < =  input
# $ ^ =  input (multiple)

CC      = avr-gcc
AR      = avr-ranlib
NM      = avr-nm
GDB     = avr-gdb
SIZE    = avr-size
STRIP   = avr-strip
OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump
AVRDUDE = avrdude
SIMAVR  = simavr

CAVR = -mmcu=atmega328p -D__AVR_ATmega328P__

CINC = -I /usr/share/arduino/hardware/archlinux-arduino/avr/cores/arduino \
       -I /usr/share/arduino/hardware/archlinux-arduino/avr/variants/standard \
			 -I ./include

CFLAGS = -flto -fno-fat-lto-objects -ffunction-sections \
         -fdata-sections -funsigned-bitfields

LFLAGS = -flto -fuse-linker-plugin -Wl,--gc-sections

CDEFS = -DF_CPU=16000000L \
        -DARDUINOO=10805 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR

CERR = -Wall -Werror -Wextra

all: main.hex

qrng.o: qrng.c
	$(CC) -c -g -Os -w -MMD -std=gnu11 $(CAVR) $(CFLAGS) $(CERR) -save-temps $(CDEFS) $(CINC) $^ -o $@

main.elf: qrng.o
	$(CC) -Os -w -g $(CAVR) $(LFLAGS) -o $@ $< -lc -lm

main.eep: main.elf
	$(OBJCOPY) -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0 $< $@

main.hex: main.elf
	$(OBJCOPY) -O ihex -j .text -j .data $^ $@

info: main.elf
	$(OBJDUMP) -p $^

size: main.elf
	$(SIZE) -C --mcu=atmega328p $^

flash: main.hex
	$(AVRDUDE) -p m328p -c arduino -P /dev/ttyUSB0 -b 115200 -v -D "-Uflash:w:$<:i"

sim:
	$(SIMAVR) -v -v -v -m atmega328p -f 16000000 -t main.hex

clean:
	rm -f *.hex *.elf *.eep *.o *.s *.d *.i
