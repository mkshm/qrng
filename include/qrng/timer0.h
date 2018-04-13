
#ifndef __UTIL_TIMER0_H__
#define __UTIL_TIMER0_H__

#include <avr/io.h>
#include <avr/sfr_defs.h>

static inline void __attribute__ (( __always_inline__ ))
timer1_init ( void )
{
  TCCR0B |= _BV ( CS10  ) ;
}

#endif
