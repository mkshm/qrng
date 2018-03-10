
#ifndef __UTIL_LCD_H__
#define __UTIL_LCD_H__

#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/sfr_defs.h>
#include <avr/eeprom.h>

static inline void __attribute__ (( __always_inline__ ))
lcd_init ( void )
{
  DDRD  |= _BV ( DD2 ) | _BV ( DD3 ) | _BV ( DD4 ) | _BV ( DD5 ) | _BV ( DD6 ) | _BV ( DD7 ) ;
  PORTD &= ~ ( _BV ( PORTD2 ) | _BV ( PORTD3 ) ) ;
}

static inline signed char __attribute__ (( __always_inline__ ))
lcd_step ( void )
{

}

#endif
