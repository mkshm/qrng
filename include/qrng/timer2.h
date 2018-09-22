
#ifndef __QRNG_TIMER2_H__
#define __QRNG_TIMER2_H__

#include <avr/io.h>

static inline void
timer2_init ( void )
{
  TCCR2B |= _BV ( CS10  ) ;
}

static inline unsigned char
timer2_read ( void )
{
  return TCNT2 ;
}

#endif
