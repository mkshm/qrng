
#ifndef __UTIL_INTERLOCK_H__
#define __UTIL_INTERLOCK_H__

#include <avr/io.h>
#include <avr/interrupt.h>

#define intlck_port ( PINB )
#define intlck_pin  ( _BV ( PB2 ) )

static inline void __attribute__ (( __always_inline__ ))
intlck_init ( void )
{
  DDRB   &= ~ ( _BV ( DD2 ) ) ;
  PORTB  |=     _BV ( PB2 ) ;
  PCMSK0 |=     _BV ( PCINT2 ) ;
  PCICR  |=     _BV ( PCIE0 ) ;
}

#endif
