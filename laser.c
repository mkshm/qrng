
#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <mf_type.h>

#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/sfr_defs.h>
#include <avr/eeprom.h>

#include <stdio.h>

#include <avr/avr_mcu_section.h>
AVR_MCU ( F_CPU , "atmega328p" ) ;

static const struct avr_mmcu_vcd_trace_t _mytrace [  ] _MMCU_ = {
  { AVR_MCU_VCD_SYMBOL ( "PORTB" ) , . mask = 0xFF , . what = ( void * ) & PORTB } ,
} ;

static int
uart_putchar ( char c , FILE * fd )
{
  if ( c == '\n' ) uart_putchar ( '\r' , fd ) ;
  loop_until_bit_is_set ( UCSR0A , UDRE0 ) ;
  UDR0 = c ;
  return 0 ;
}

static FILE mystdout = FDEV_SETUP_STREAM ( uart_putchar ,
                                           NULL ,
                                           _FDEV_SETUP_WRITE ) ;

int
main ( void )
{
  u08 pin [ 6 ] ;
  u08 flag ;

  stdout = & mystdout ;

  DDRB |= _BV ( DDB2 ) ;

  TCCR1B = _BV ( WGM13 ) | _BV ( CS10   ) ;
  TCCR1A = _BV ( WGM10 ) | _BV ( COM1B0 ) | _BV ( COM1B1 ) ;

  // freq (TOP) = fclock / ( 2 * prescaler * fdesired )
  OCR1A = 1000000 ;

  // duty cycle = TOP * [0..1]
  OCR1B = 100000 ;

  printf ( "got here\n" ) ;

/*
  while ( 1 )
  {
    pin [ 0 ] = PINB ;
    pin [ 1 ] = PINC ;
    pin [ 2 ] = PIND ;

    sei (  ) ;

    //magic

    pin [ 3 ] = pin [ 0 ] ;
    pin [ 4 ] = pin [ 1 ] ;
    pin [ 5 ] = pin [ 2 ] ;

    cli (  ) ;
  }
*/
  // shouldn't get here

  TCCR1A &= ~ ( _BV ( COM1B0 ) | _BV ( COM1B1 ) ) ;

  sleep_cpu (  ) ;

  return 0 ;
}
