
#ifndef __UTIL_TIMER2_H__
#define __UTIL_TIMER2_H__

#include <avr/io.h>
#include <avr/sfr_defs.h>

static inline void __attribute__ (( __always_inline__ ))
timer2_init ( void )
{
  TCCR2B |= _BV ( CS10  ) ;
}

#endif
