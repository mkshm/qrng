
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
timer1_stop ( void )
{
  TCCR1B &= ~ ( _BV ( CS10  ) ) ;
}

static inline void __attribute__ (( __always_inline__ ))
timer1_pwm_on ( void )
{
  DDRB   |= _BV ( DDB2 ) ;
  TCCR1B |= _BV ( WGM13 ) ;
  TCCR1A |= _BV ( WGM10 ) ;
  TCCR1A |= _BV ( COM1B1 ) ;
}

static inline void __attribute__ (( __always_inline__ ))
timer1_pwm_off ( void )
{
  TCCR1A &= ~ ( _BV ( COM1B1 ) ) ;
  TCCR1A &= ~ ( _BV ( WGM10 ) ) ;
  TCCR1B &= ~ ( _BV ( WGM13 ) ) ;
  DDRB   &= ~ ( _BV ( DDB2 ) ) ;
}

static inline void __attribute__ (( __always_inline__ ))
timer1_freq ( const unsigned long freq )
{
  OCR1A = F_CPU / ( 2UL * 1UL * freq ) ;
}

static inline unsigned short __attribute__ (( __always_inline__ ))
timer1_duty ( const unsigned short duty )
{
  unsigned short ret ;
  ret = OCR1B ;
  OCR1B = duty ;
  return ret ;
}

static inline void __attribute__ (( __always_inline__ ))
timer1_enable_overflow ( void )
{
  TIMSK1 |= _BV ( TOIE1 ) ;
}

static inline void __attribute__ (( __always_inline__ ))
timer1_disable_overflow ( void )
{
  TIMSK1 &= ~ ( _BV ( TOIE1 ) ) ;
}

#endif
