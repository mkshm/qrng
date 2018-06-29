
#ifndef __UTIL_INTERRUPT_H__
#define __UTIL_INTERRUPT_H__

#include <avr/io.h>
#include <avr/interrupt.h>

static inline void __attribute__ (( __always_inline__ , __hot__ ))
enable_interrupts ( void )
{
  sei (  ) ;
}

static inline void __attribute__ (( __always_inline__ , __hot__ ))
disable_interrupts ( void )
{
  cli (  ) ;
}

#endif
