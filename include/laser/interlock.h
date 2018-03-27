
#ifndef __UTIL_INTERLOCK_H__
#define __UTIL_INTERLOCK_H__

#include <stdbool.h>

static inline void __attribute__ (( __always_inline__ ))
interlock_init ( void )
{
  DDRB  &= ~ ( _BV ( DD2 ) ) ;
  PORTB |=     _BV ( PB2 ) ;
}

static inline bool __attribute__ (( __always_inline__ ))
interlock_open ( void )
{
  return ( PINB & _BV ( PB2 ) ) == 0 ? true : false ;
}

static inline void __attribute__ (( __always_inline__ ))
interlock_wait ( void )
{
  while ( 0 != ( PINB & _BV ( PB2 ) &&  ) ) ; /* wait for both user input and interlock close */
}

#endif
