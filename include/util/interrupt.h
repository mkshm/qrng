
#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__

#include <avr/io.h>
#include <avr/interrupt.h>

static inline void __attribute__ (( __always_inline__ ))
enable_interrupts ( void )
{
  sei (  ) ;
}

static inline void __attribute__ (( __always_inline__ ))
disable_interrupts ( void )
{
  cli (  ) ;
}
/*
static inline void __attribute__ (( __always_inline__ ))
enable_int0 ( void )
{
  GICR |= ( 1 << INT0 ) ;
}

static inline void __attribute__ (( __always_inline__ ))
disable_int0 ( void )
{
  GICR &= ~ ( 1 << INT0 ) ;
}

static inline void __attribute__ (( __always_inline__ ))
enable_int1 ( void )
{
  GICR |= ( 1 << INT1 ) ;
}

static inline void __attribute__ (( __always_inline__ ))
disable_int1 ( void )
{
  GICR |= ( 1 << INT1 ) ;
}
*/
#endif
