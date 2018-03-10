
#include <util/delay.h>
#include <util/timer1.h>
#include <util/interrupt.h>
#include <util/debug.h>
#include <util/pins.h>
#include <util/serial.h>

#include <stdlib.h>
#include <string.h>

static volatile unsigned short high ;

static volatile unsigned char buff [ 256 ] ;
static volatile unsigned char head , tail ;

ISR ( TIMER1_OVF_vect )
{
  high ++ ;
}

ISR ( TIMER1_CAPT_vect )
{
  static unsigned char bit = 0 , hit = 0 ;
  static unsigned long ts [ 8 ] ;
  static unsigned long dt [ 4 ] ;
  union { unsigned long lohi ; struct { unsigned short lo , hi ; } ; } d ;

  d . lo = ICR1 ; // read TCNT1, which is copied to ICR1 on capture
  d . hi = high ;

  ts [ ( hit ++ ) & 7 ] = d . lohi ;

  switch ( hit << 1 ) // |--|__|--|__|
  {
    case 0 :
    case 1 :
    case 2 :
    case 3 :
  }
  switch ( bit )
  {
    case  8 : bit = 0 ; head ++ ;
    default : buff
  }
}

int
main ( void )
{
  unsigned char bit , temp ;

  disable_interrupts (  ) ;

  _delay_ms ( 50 ) ;

  serial_init (  ) ;
  timer1_init (  ) ;
  timer1_enable_overflow (  ) ;
  timer1_enable_capture (  ) ;

  enable_interrupts (  ) ;

  while ( 1 )
  {
    while ( tail == head ) ;
    serial_send ( buff [ tail ++ ] ) ;
  }

  backtrace (  ) ;

  timer1_disable_capture (  ) ;
  timer1_disable_overflow (  ) ;
  timer1_stop (  ) ;

  sleep_mode (  ) ;

  return 0 ;
}
