
#ifndef __UTIL_ROTARY_H__
#define __UTIL_ROTARY_H__

#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/sfr_defs.h>
#include <avr/eeprom.h>

static inline void __attribute__ (( __always_inline__ ))
rotary_init ( void )
{
  DDRB  &= ~ ( _BV ( DD2 ) | _BV ( DD3 ) ) ;
  PORTB |=     _BV ( PB2 ) | _BV ( PB3 ) ;
}

static inline signed char __attribute__ (( __always_inline__ ))
rotary_step ( void )
{
  signed char ret ;
  while ( ( ret = PINB | _BV ( PB2 ) | _BV ( PB3 ) ) )
  {
  }
  return ret ;
}

#endif
