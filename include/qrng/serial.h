
#ifndef __UTIL_SERIAL_H__
#define __UTIL_SERIAL_H__

#include <avr/io.h>
#include <avr/sfr_defs.h>

#include <stdbool.h>

#define STATIC_INLINE static inline __attribute__ (( __always_inline__ ))

STATIC_INLINE void
serial_init ( void )
{                                              // mult = 16 for 1x, 8 for 2x ; f_osc = clock frequency
  UBRR0   = 0u ;                               // Select baud using: baud = f_osc / ( mult * ( UBBR0 + 1 ) )
  UCSR0A |= _BV ( U2X0 ) ;                     // 2x Speed Enable ( changes multiplier above )
  UCSR0C |= _BV ( UCSZ00 ) | _BV ( UCSZ01 ) ;  // 8 bit
  UCSR0C |= _BV ( UPM01  ) | _BV ( USBS0  ) ;  // 1 stop bit + even parity
  UCSR0B |= _BV ( TXEN0 ) ;                    // Enable Transmitted Mode
  DDRD   |= _BV ( DDD1 ) ;
}

STATIC_INLINE void
serial_grab ( void )
{
  while ( ! ( UCSR0A & _BV ( UDRE0 ) ) ) ;  // Check for an empty buffer by checking the UDRE0 bit
}

STATIC_INLINE bool
serial_try_grab ( void )
{
  return 0 != ( UCSR0A & _BV ( UDRE0 ) ) ;
}

STATIC_INLINE void
serial_send ( unsigned char byte )
{
  UDR0 = byte ; // Write to the empty buffer. automatically send the data written.
}

#undef STATIC_INLINE
#endif
