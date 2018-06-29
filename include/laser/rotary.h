
#ifndef __UTIL_ROTARY_H__
#define __UTIL_ROTARY_H__

#include <avr/io.h>
#include <avr/sfr_defs.h>

#define rotary_port  ( PINB )
#define rotary_press ( _BV ( PB3 ) )
#define rotary_left  ( _BV ( PB4 ) )
#define rotary_right ( _BV ( PB5 ) )

static inline void __attribute__ (( __always_inline__ ))
rotary_init ( void )
{
  DDRB   &= ~ ( _BV ( DD3 ) | _BV ( DD4 ) | _BV ( DD5 ) ) ; /* Set pins 3, 4 and 5 to input */
  PORTB  |=     _BV ( PB3 ) | _BV ( PB4 ) | _BV ( PB5 ) ;   /* Enable pull-up resistor on inputs */
  PCMSK0 |=     _BV ( PCINT3 ) | _BV ( PCINT4 ) | _BV ( PCINT5 ) ;
  PCICR  |=     _BV ( PCIE0 ) ;
}

#endif
