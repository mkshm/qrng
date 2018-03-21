
#ifndef __UTIL_TIMER1_H__
#define __UTIL_TIMER1_H__

#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/sfr_defs.h>
#include <avr/eeprom.h>

static volatile unsigned char over ;

ISR ( TIMER0_OVF_vect )
{
  over ++ ;
}

static inline void __attribute__ (( __always_inline__ ))
timer0_init ( void )
{
  TCNT0   = 0U ;
  TCCR0B |= _BV ( CS10  ) ;
}

static inline void __attribute__ (( __always_inline__ ))
timer0_stop ( void )
{
  TCCR0B &= ~ ( _BV ( CS10  ) ) ;
}

static inline void __attribute__ (( __always_inline__ ))
timer0_enable_overflow ( void )
{
  TIMSK0 |= _BV ( TOIE0 ) ;
}

static inline void __attribute__ (( __always_inline__ ))
timer0_disable_overflow ( void )
{
  TIMSK0 &= ~ ( _BV ( TOIE0 ) ) ;
}

#endif
