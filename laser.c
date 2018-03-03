
#include <util/timer1.h>
#include <util/interrupt.h>
#include <util/debug.h>
#include <util/pins.h>

int
main ( void )
{
  u08 pin [ 6 ] ;
  u08 flag ;

  ddrb  ( 0b00000010 ) ;
  portb ( 0b00000010 ) ;

  timer1_init (  ) ;
  timer1_pwm (  ) ;
  timer1_freq ( 2000U ) ;
  timer1_duty (  500U ) ;

  disable_interrupts (  ) ;
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
  timer1_stop (  ) ;

  backtrace (  ) ;

  sleep_mode (  ) ;

  return 0 ;
}
