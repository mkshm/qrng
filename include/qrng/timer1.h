
#ifndef __QRNG_TIMER1_H__
#define __QRNG_TIMER1_H__

#include <avr/io.h>

static inline void
timer1_init ( void )
{
  TCCR1B |= _BV ( CS10  ) ;
}

static inline unsigned short
timer1_read ( void )
{
  return TCNT1 ;
}

static inline unsigned short
timer1_read_capture ( void )
{
  return ICR1 ;
}

static inline void
timer1_enable_overflow ( void )
{
  TIMSK1 |= _BV ( TOIE1 ) ;
}

static inline void
timer1_enable_capture ( void )
{
  TCCR1B |= _BV ( ICNC1 ) ;
  TCCR1B |= _BV ( ICES1 ) ;
  TIMSK1 |= _BV ( ICIE1 ) ;
}

#endif
