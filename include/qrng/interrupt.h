
#ifndef __QRNG_INTERRUPT_H__
#define __QRNG_INTERRUPT_H__

#include <avr/io.h>
#include <avr/interrupt.h>

static inline void
enable_interrupts ( void )
{
  sei (  ) ;
}

static inline void
disable_interrupts ( void )
{
  cli (  ) ;
}

static inline void
enable_int0 ( void )
{
  EICRA |= ISC11 ;
  EIMSK |= INT0  ;
}

#endif
