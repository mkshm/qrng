
#ifndef __UTIL_ROTARY_H__
#define __UTIL_ROTARY_H__

#include <avr/io.h>
#include <avr/sfr_defs.h>

static inline void __attribute__ (( __always_inline__ ))
rotary_init ( void )
{
  DDRB  &= ~ ( _BV ( DD2 ) | _BV ( DD3 ) ) ; /* Set pins 2 and 3 to INPUT */
  PORTB |=     _BV ( PB2 ) | _BV ( PB3 ) ;   /* Enable pull-up resistor */
}

static inline signed char __attribute__ (( __always_inline__ ))
rotary_step ( void )
{
  signed char ret ;
  signed char lhs , rhs ;
  
  lhs = ( PINB & _BV ( PB2 ) ) >> PB2 ; /* pin 2 is selected here to be left */
  rhs = ( PINB & _BV ( PB3 ) ) >> PB3 ; /* pin 3 is selected here to be right */
  
  return rhs - lhs ; /* going right is positive 1 , 0 is no change , -1 is left */
}

#endif
