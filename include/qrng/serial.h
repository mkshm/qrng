
#ifndef __UTIL_SERIAL_H__
#define __UTIL_SERIAL_H__

#include <avr/io.h>
#include <avr/sfr_defs.h>

#define STATIC_INLINE static inline void __attribute__ (( __always_inline__ ))

STATIC_INLINE
serial_init ( void )
{                                              // mult = 16 for 1x, 8 for 2x ; f_osc = clock frequency
  UBRR0   = 0u ;                               // Select baud using: baud = f_osc / ( mult * ( UBBR0 + 1 ) )
  UCSR0A |= _BV ( U2X0 ) ;                     // 2x Speed Enable ( changes multiplier above )
  UCSR0C |= _BV ( UCSZ00 ) | _BV ( UCSZ01 ) ;  // 8 bit Output Frame
  UCSR0B |= _BV ( TXEN0 ) ;                    // Enable Transmitted Mode
}

STATIC_INLINE
serial_loop ( const volatile unsigned char * const restrict buff ,
                    volatile unsigned char * const restrict head ,
                    volatile unsigned char * const restrict tail )
{
  while ( 1 )
  {
    while ( * tail != * head ) ;              // Spin when tail == head, the buffer is full
    while ( ! ( UCSR0A & _BV ( UDRE0 ) ) ) ;  // Check for an empty buffer by checking the UDRE0 bit
    UDR0 = buff [ ( * tail ) ++ ] ;           // Write to the empty buffer. automatically send the data written.
  }
}

#undef STATIC_INLINE
#endif
