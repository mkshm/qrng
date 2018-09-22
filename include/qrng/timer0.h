
#ifndef __QRNG_TIMER0_H__
#define __QRNG_TIMER0_H__

#include <avr/io.h>

static inline void
timer0_init ( void )
{
  TCCR0B |= _BV ( CS10  ) ;
}

static inline unsigned char
timer0_read ( void )
{
  return TCNT0 ;
}

#endif
