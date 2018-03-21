
#ifndef __PINS_H__
#define __PINS_H__

#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/sfr_defs.h>
#include <avr/eeprom.h>

#include <laser/fence.h>

static inline void __attribute__ (( __always_inline__ ))
ddrb ( const unsigned char byte )
{
  DDRB = byte ;
  fence (  ) ;
}

static inline void __attribute__ (( __always_inline__ ))
ddrc ( const unsigned char byte )
{
  DDRC = byte ;
  fence (  ) ;
}

static inline void __attribute__ (( __always_inline__ ))
ddrd ( const unsigned char byte )
{
  DDRD = byte ;
  fence (  ) ;
}

static inline void __attribute__ (( __always_inline__ ))
portb ( const unsigned char byte )
{
  PORTB = byte ;
  fence (  ) ;
}

static inline void __attribute__ (( __always_inline__ ))
portc ( const unsigned char byte )
{
  PORTC = byte ;
  fence (  ) ;
}

static inline void __attribute__ (( __always_inline__ ))
portd ( const unsigned char byte )
{
  PORTD = byte ;
  fence (  ) ;
}

static inline unsigned char __attribute__ (( __always_inline__ ))
pinb ( void )
{
  return PINB ;
}

static inline unsigned char __attribute__ (( __always_inline__ ))
pinc ( void )
{
  return PINC ;
}

static inline unsigned char __attribute__ (( __always_inline__ ))
pind ( void )
{
  return PIND ;
}

#endif
