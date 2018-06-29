
#include <util/delay.h>

#include <laser/timer1.h>
#include <laser/interrupt.h>
#include <laser/interlock.h>
#include <laser/rotary.h>

static volatile unsigned char selection_new ;
static volatile   signed char direction_new ;
static volatile unsigned char intlocked_new ;

ISR ( PCINT0_vect )
{
  if ( rotary_port & rotary_left  ) { direction_new -- ; }
  if ( rotary_port & rotary_right ) { direction_new ++ ; }
  if ( rotary_port & rotary_press ) { selection_new ++ ; }
  intlocked_new = intlck_port & intlck_pin ;
}

int
main ( void )
{
  unsigned short period ;
  unsigned short micros ;
  unsigned char  selection_cur ;
    signed char  direction_cur ;
  unsigned char  intlocked_cur ;

  disable_interrupts (  ) ;

  _delay_ms ( 50 ) ; // Allow devices voltage to rise

  intlck_init (  ) ;
  rotary_init (  ) ;
  timer1_init (  ) ;

  timer1_period ( ( period = 200u ) ) ; /* period: [50,200] us */
  timer1_micros ( ( micros =   1u ) ) ; /* micros: [1,period] us */
  timer1_toggle (  ) ;

  enable_interrupts (  ) ;

  while ( 1 )
  {
    direction_cur = direction_new ;
    selection_cur = selection_new ;
    intlocked_cur = intlocked_new ;

    direction_new = 0 ;
    selection_new = 0 ;
    intlocked_new = 0 ;

    if ( 0 == intlocked_new )
    {
      timer1_period ( 200u ) ;
      timer1_micros (   1u ) ;
    }
    else
    {
      timer1_period ( period ) ;
      timer1_micros ( micros ) ;
    }
  }

  return 0 ;
}
