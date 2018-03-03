
#ifndef __TIMER1_H__
#define __TIMER1_H__

#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/sfr_defs.h>
#include <avr/eeprom.h>

static inline void __attribute__ (( __always_inline__ ))
timer1_init ( void )
{
  TCNT1  = 0U ;
  TCCR1A = 0 ;
  TCCR1B = _BV ( CS10 ) ;
}

static inline void __attribute__ (( __always_inline__ ))
timer1_stop ( void )
{
  TCCR1A &= ~ ( _BV ( COM1B0 ) | _BV ( COM1B1 ) ) ;
}

static inline void __attribute__ (( __always_inline__ ))
timer1_pwm ( void )
{
  TCCR1B = _BV ( WGM13 ) ;
  TCCR1A = _BV ( WGM10 ) | _BV ( COM1B0 ) | _BV ( COM1B1 ) ;
}

static inline void __attribute__ (( __always_inline__ ))
timer1_freq ( const unsigned short freq )
{
  OCR1A = F_CPU / ( 2U * 1U * freq ) ;
}

static inline void __attribute__ (( __always_inline__ ))
timer1_duty ( const unsigned short duty )
{
  OCR1B = duty ;
}

static inline void __attribute__ (( __always_inline__ ))
timer1_enable_ovf ( void )
{
  TIMSK1 = _BV ( TOIE1 ) ;
}

#endif
