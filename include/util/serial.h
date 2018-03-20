
#ifndef __UTIL_SERIAL_H__
#define __UTIL_SERIAL_H__

#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/sfr_defs.h>
#include <avr/eeprom.h>

#include <stdio.h>

static int
uart_putchar ( char c , FILE * fd )
{
  loop_until_bit_is_set ( UCSR0A , UDRE0 ) ;
  UDR0 = c ;
  return 0 ;
}

static FILE std = FDEV_SETUP_STREAM ( uart_putchar , NULL , _FDEV_SETUP_WRITE ) ;

static inline void __attribute__ (( __always_inline__ ))
serial_init ( void )
{
  UBRR0   = 207u ; // baud = f_osc / ( mult * ( UBBR0 + 1 ) ) mult = 16 for 1x, 8 for 2x
  UCSR0A |= _BV ( U2X0 ) ;
  UCSR0C |= _BV ( UCSZ00 ) | _BV ( UCSZ01 ) ;
  UCSR0B |= _BV ( TXEN0 ) ;
}

static inline void __attribute__ (( __always_inline__ ))
serial_stop ( void )
{
  UCSR0B &= ~ ( _BV ( TXEN0 ) ) ;
  UCSR0C &= ~ ( _BV ( UCSZ00 ) | _BV ( UCSZ01 ) ) ;
  UCSR0A &= ~ ( _BV ( U2X0 ) ) ;
  UBRR0   = 0u ;
}

static inline void __attribute__ (( __always_inline__ ))
serial_loop ( const volatile unsigned char * const buff ,
                    volatile unsigned char * const head ,
                    volatile unsigned char * const tail )
{
  
  while ( 1 )
  {
    if ( * tail != * head && UCSR0A & _BV ( UDRE0 ) ) fprintf ( & std , "%hhu\n" , buff [ ( * tail ) ++ ] ) ;
// UDR0 = buff [ ( * tail ) ++ ] ;
  }
}

#endif
