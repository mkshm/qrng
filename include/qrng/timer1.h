
#ifndef __UTIL_TIMER1_H__
#define __UTIL_TIMER1_H__

#include <avr/io.h>
#include <avr/sfr_defs.h>

static inline void __attribute__ (( __always_inline__ ))
timer1_init ( void )
{
  TCCR1B |= _BV ( CS10  ) ;
}

static inline void __attribute__ (( __always_inline__ ))
timer1_enable_overflow ( void )
{
  TIMSK1 |= _BV ( TOIE1 ) ;
}

static inline void __attribute__ (( __always_inline__ ))
timer1_enable_capture ( void )
{
  TCCR1B |= _BV ( ICNC1 ) ;
  TCCR1B |= _BV ( ICES1 ) ;
  TIMSK1 |= _BV ( ICIE1 ) ;
}

#endif
