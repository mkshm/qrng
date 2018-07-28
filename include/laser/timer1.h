
#ifndef __UTIL_TIMER1_H__
#define __UTIL_TIMER1_H__

#include <avr/io.h>
#include <avr/sfr_defs.h>

/*
  pwm output on arduino pin 10 ( PB2 , OCR1B )
*/

static inline void
timer1_init ( void )
{
  DDRB   |= _BV ( DDB2 ) ;
  TCCR1A |= _BV ( WGM10 ) ;
  TCCR1B |= _BV ( WGM13 ) | _BV ( CS10 ) ;
}

static inline void
timer1_stop ( void )
{
  TCCR1B &= ~ ( _BV ( WGM13 ) | _BV ( CS10 ) ) ;
  TCCR1A &= ~ ( _BV ( WGM10 ) ) ;
  DDRB   &= ~ ( _BV ( DDB2 ) ) ;
}

static inline void
timer1_toggle ( void )
{
  TCCR1A ^= _BV ( COM1B1 ) ;
}

static inline void
timer1_period ( const unsigned short us )
{
  OCR1A = ( unsigned short ) ( ( unsigned long ) F_CPU / ( 2UL * 1000000UL ) ) * us ;
}

static inline void
timer1_micros ( const unsigned short us )
{
  OCR1B = ( unsigned short ) ( ( unsigned long ) F_CPU / ( 2UL * 1000000UL ) ) * us ;
}

static inline void
timer1_enable_overflow ( void )
{
  TIMSK1 |= _BV ( TOIE1 ) ;
}

static inline void
timer1_disable_overflow ( void )
{
  TIMSK1 &= ~ ( _BV ( TOIE1 ) ) ;
}

#endif
