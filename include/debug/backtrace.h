
#ifndef __DEBUG_H__
#define __DEBUG_H__

#ifndef _NDEBUG
/*
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

static void
backtrace ( void )
{
  static FILE std = FDEV_SETUP_STREAM ( uart_putchar , NULL , _FDEV_SETUP_WRITE ) ;
  disable_interrupts (  ) ;
#define BIN(b)  \
  ( (b) & 0x80 ? '1' : '0' ) , \
  ( (b) & 0x40 ? '1' : '0' ) , \
  ( (b) & 0x20 ? '1' : '0' ) , \
  ( (b) & 0x10 ? '1' : '0' ) , \
  ( (b) & 0x08 ? '1' : '0' ) , \
  ( (b) & 0x04 ? '1' : '0' ) , \
  ( (b) & 0x02 ? '1' : '0' ) , \
  ( (b) & 0x01 ? '1' : '0' )
  fprintf ( & std , "DDRB %c%c%c%c%c%c%c%c PORTB %c%c%c%c%c%c%c%c PINB %c%c%c%c%c%c%c%c\r\n" , BIN ( DDRB ) , BIN ( PORTB ) , BIN ( PINB ) ) ;
  fprintf ( & std , "DDRC %c%c%c%c%c%c%c%c PORTC %c%c%c%c%c%c%c%c PINC %c%c%c%c%c%c%c%c\r\n" , BIN ( DDRC ) , BIN ( PORTC ) , BIN ( PINC ) ) ;
  fprintf ( & std , "DDRD %c%c%c%c%c%c%c%c PORTD %c%c%c%c%c%c%c%c PIND %c%c%c%c%c%c%c%c\r\n" , BIN ( DDRD ) , BIN ( PORTD ) , BIN ( PIND ) ) ;
  fprintf ( & std , "TCCR0A %c%c%c%c%c%c%c%c TCCR0B %c%c%c%c%c%c%c%c TCNT0 %c%c%c%c%c%c%c%c\r\n" , BIN ( TCCR0A ) , BIN ( TCCR0B ) , BIN ( TCNT0 ) ) ;
  fprintf ( & std , "TCCR1A %c%c%c%c%c%c%c%c TCCR1B %c%c%c%c%c%c%c%c TCNT1 %c%c%c%c%c%c%c%c %c%c%c%c%c%c%c%c\r\n" , BIN ( TCCR1A ) , BIN ( TCCR1B ) , BIN ( TCNT1H ) , BIN ( TCNT1L ) ) ;
  fprintf ( & std , "TCCR2A %c%c%c%c%c%c%c%c TCCR2B %c%c%c%c%c%c%c%c TCNT2 %c%c%c%c%c%c%c%c\r\n" , BIN ( TCCR2A ) , BIN ( TCCR2B ) , BIN ( TCNT2 ) ) ;
  fprintf ( & std , "OCR0A %c%c%c%c%c%c%c%c OCR0B %c%c%c%c%c%c%c%c\r\n" , BIN ( OCR0A ) , BIN ( OCR0B ) ) ;
  fprintf ( & std , "OCR1A %c%c%c%c%c%c%c%c %c%c%c%c%c%c%c%c OCR1B %c%c%c%c%c%c%c%c %c%c%c%c%c%c%c%c\r\n" , BIN ( OCR1AH ) , BIN ( OCR1AL ) , BIN ( OCR1BH ) , BIN ( OCR1BL ) ) ;
  fprintf ( & std , "OCR2A %c%c%c%c%c%c%c%c OCR2B %c%c%c%c%c%c%c%c\r\n" , BIN ( OCR2A ) , BIN ( OCR2B ) ) ;
  fprintf ( & std , "Backtrace Complete\r\n" ) ;
#undef BIN
}
*/
#endif

#endif
