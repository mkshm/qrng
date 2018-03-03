
#include <mf_type.h>

#include <util/timer1.h>
#include <util/interrupt.h>
#include <util/debug.h>
#include <util/pins.h>

static volatile u08 over ;

ISR ( TIMER1_OVF_vect )
{
  over ++ ;
}

ISR ( TIMER1_CAPT_vect )
{
}

int
main ( void )
{
  timer1_init (  ) ;
  timer1_enable_ovf (  ) ;

  //enable_interrupts (  ) ;

/*
  while ( 1 )
  {
    pin [ 0 ] = PINB ;
    pin [ 1 ] = PINC ;
    pin [ 2 ] = PIND ;

    enable_interrupts (  ) ;

    //magic

    pin [ 3 ] = pin [ 0 ] ;
    pin [ 4 ] = pin [ 1 ] ;
    pin [ 5 ] = pin [ 2 ] ;

    disable_interrupts (  ) ;
  }
*/

  backtrace (  ) ;

  sleep_mode (  ) ;

  return 0 ;
}
