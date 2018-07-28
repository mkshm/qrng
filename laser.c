
#include <util/delay.h>

#include <laser/timer1.h>
#include <laser/interrupt.h>
#include <laser/interlock.h>
#include <laser/rotary.h>

static volatile unsigned char rotary_new = 0 ;
static volatile unsigned char intlck_new = 0 ;

static volatile unsigned char interrupted = 0 ;

ISR ( PCINT0_vect )
{
  rotary_new |= rotary_port & rotary_mask ;
  intlck_new |= intlck_port & intlck_mask ;

  interrupted = ~ ( 0 ) ;
}

int
main ( void )
{
  unsigned short period ;
  unsigned short micros ;
  unsigned char  rotary_cur ;
  unsigned char  intlck_cur ;

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
    if ( ! interrupted ) continue ;

    interrupted = 0 ;

    rotary_cur = rotary_new ;
    intlck_cur = intlck_new ;

    rotary_new = 0 ;
    intlck_new = 0 ;

    if ( intlck_cur )
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
