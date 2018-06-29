
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
  /* run in 4-bit mode, rw = 255
   _displayfunction = LCD_4BITMODE | LCD_1LINE | LCD_5x8DOTS;
   */
  DDRD  |= _BV ( DD2 ) | _BV ( DD3 )   // rs, enable
        |  _BV ( DD4 ) | _BV ( DD5 )   // d0, d1,
        |  _BV ( DD6 ) | _BV ( DD7 ) ; // d2, d3
  PORTD &= ~ ( _BV ( PORTD2 ) | _BV ( PORTD3 ) ) ;
}

static inline signed char __attribute__ (( __always_inline__ ))
lcd_step ( void )
{

}

#endif
