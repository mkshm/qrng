
#include <util/delay.h>

#include <debug/backtrace.h>

#include <laser/timer1.h>
#include <laser/interrupt.h>
#include <laser/pins.h>
#include <laser/rotary.h>

int
main ( void )
{
  unsigned char pin [ 6 ] ;
  unsigned char flag ;

  _delay_ms ( 50 ) ;

  timer1_init (  ) ;
  timer1_pwm_on (  ) ;
  timer1_freq ( 2000U ) ;
  timer1_duty (  500U ) ;

  rotary_init (  ) ;

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
  //backtrace (  ) ;

  timer1_pwm_off (  ) ;
  timer1_stop (  ) ;

  sleep_mode (  ) ;

  return 0 ;
}
