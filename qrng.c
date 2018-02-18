
#include <stddef.h>

#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/sfr_defs.h>

#include <mf_type.h>

typedef struct rega_t
{
  u08 b1 : 1 ; u08 b2 : 1 ;
  u08 b3 : 1 ; u08 b4 : 1 ;
  u08 b5 : 1 ; u08 b6 : 1 ;
  u08 b7 : 1 ; u08 b8 : 1 ;
} B ;

enum { ON = 1 , OFF = 0 } ;

_Static_assert ( 1 == sizeof ( B ) , "B is not the same size as its corresponding register." ) ;

static volatile u08 over ;

ISR ( TIMER1_OVF_vect )
{
  over ++ ;
}

int
main ( void )
{
  DD ( B ) { ON } ;
  RD ( B ) { ON } ;

  TCCR1B = _BV ( WGM13 ) | _BV ( CS10 ) ;
  TCCR1A = 0 ;
  TIMSK1 = _BV ( TOIE1 ) ;

  sei (  ) ;

  for (;;) sleep_mode (  ) ;

  return 0 ;
}
