
#include <avr/sleep.h>
#include <avr/interrupt.h>

#include <util/delay.h>

#include <laser/timer1.h>
#include <laser/interlock.h>
#include <laser/rotary.h>

static volatile unsigned char rotary_new = 0 ;
static volatile unsigned char intlck_new = 0 ;

static volatile unsigned char ovf_new = 0 ;

ISR ( PCINT0_vect )
{
  rotary_new |= rotary_port & rotary_mask ;
  intlck_new |= intlck_port & intlck_mask ;
}

ISR ( TIMER1_OVF_vect )
{
  ovf_new ++ ;
}

int
main ( void )
{
  unsigned short period ;
  unsigned short micros ;
  unsigned char  rotary_cur ;
  unsigned char  intlck_cur ;

  cli (  ) ;

  _delay_ms ( 50 ) ; // Allow devices voltage to rise

  intlck_init (  ) ;
  rotary_init (  ) ;
  timer1_init (  ) ;

  timer1_period ( ( period = 200u ) ) ; /* period: [50,200] us */
  timer1_micros ( ( micros =   1u ) ) ; /* micros: [1,period] us */
  timer1_toggle (  ) ;

  sei (  ) ;

  set_sleep_mode ( SLEEP_MODE_IDLE ) ;

  while ( 1 )
  {
    sleep_enable (  ) ;
    sleep_cpu (  ) ;
    cli (  ) ;
    sleep_disable (  ) ;

    rotary_cur = rotary_new ;
    intlck_cur = intlck_new ;

    sei (  ) ;

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
