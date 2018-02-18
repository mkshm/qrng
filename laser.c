
#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/sfr_defs.h>

int
main ( void )
{
  u08 pin [ 6 ] ;
  u32 micros = U16 ( 65536 ) ;
  u32 cycles = ( F_CPU / 2000000 ) * micros ;

  //    [ ----+++++- ]
  DDRB &= 0b11000011 ;
  DDRB |= 0b00000010 ;
  DDRC |= 0b00000000 ;
  DDRD |= 0b00000000 ;

  PORTB |= 0b00111101 ;
  PORTC |= 0b01111111 ;
  PORTD |= 0b00111111 ;

  TCCR1B = _BV ( WGM13  ) | _BV ( CS10   ) ;
  TCCR1A = _BV ( COM1A1 ) ;
  //TIMSK1 = _BV ( TOIE1 ) ;

  ICR1  = pwmPeriod ;
  OCR1A = cycles ;

  while ( 1 )
  {
    pin [ 0 ] = PINB ;
    pin [ 1 ] = PINC ;
    pin [ 2 ] = PIND ;

    sei (  ) ;



    /* magic */

    pin [ 3 ] = pin [ 0 ] ;
    pin [ 4 ] = pin [ 1 ] ;
    pin [ 5 ] = pin [ 2 ] ;

    cli (  ) ;
  }

  return 0 ;
}
