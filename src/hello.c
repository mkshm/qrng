
#ifndef F_CPU
#define F_CPU 16000000
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#define LED PORT5

int
main ( void )
{
  DDRB |= ( 1 << LED ) ;
  for ( ; ; )
  {
    PORTB |= ( 1 << LED ) ;
    _delay_ms ( 100 ) ;
    PORTB &= ( 0 << LED ) ;
    _delay_ms ( 100 ) ;
  }
}
