
#ifndef __DEBUG_H__
#define __DEBUG_H__

#ifndef _NDEBUG

#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/sfr_defs.h>
#include <avr/eeprom.h>

#include <stdio.h>

#include <avr/avr_mcu_section.h>

#include <util/interrupt.h>

AVR_MCU ( F_CPU , "atmega328p" ) ;

AVR_MCU_VOLTAGES ( 5 , 5 , 5 ) ;
AVR_MCU_VCD_FILE ( "laser.vcd" , 1000000 ) ;

static int
uart_putchar ( char c , FILE * fd )
{
  loop_until_bit_is_set ( UCSR0A , UDRE0 ) ;
  UDR0 = c ;
  return 0 ;
}

static FILE std = FDEV_SETUP_STREAM ( uart_putchar , NULL , _FDEV_SETUP_WRITE ) ;

#define BIN(b)  \
  ( (b) & 0x80 ? '1' : '0' ) , \
  ( (b) & 0x40 ? '1' : '0' ) , \
  ( (b) & 0x20 ? '1' : '0' ) , \
  ( (b) & 0x10 ? '1' : '0' ) , \
  ( (b) & 0x08 ? '1' : '0' ) , \
  ( (b) & 0x04 ? '1' : '0' ) , \
  ( (b) & 0x02 ? '1' : '0' ) , \
  ( (b) & 0x01 ? '1' : '0' )

static void
backtrace ( void )
{
  disable_interrupts (  ) ;
  fprintf ( & std , "DDRB %c%c%c%c%c%c%c%c PORTB %c%c%c%c%c%c%c%c PINB %c%c%c%c%c%c%c%c\r\n" , BIN ( DDRB ) , BIN ( PORTB ) , BIN ( PINB ) ) ;
  fprintf ( & std , "DDRC %c%c%c%c%c%c%c%c PORTC %c%c%c%c%c%c%c%c PINC %c%c%c%c%c%c%c%c\r\n" , BIN ( DDRC ) , BIN ( PORTC ) , BIN ( PINC ) ) ;
  fprintf ( & std , "DDRD %c%c%c%c%c%c%c%c PORTD %c%c%c%c%c%c%c%c PIND %c%c%c%c%c%c%c%c\r\n" , BIN ( DDRD ) , BIN ( PORTD ) , BIN ( PIND ) ) ;
  fprintf ( & std , "Backtrace Complete\r\n" ) ;
}

#endif

#endif
