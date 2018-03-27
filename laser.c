
#include <util/delay.h>

#include <laser/timer1.h>
#include <laser/interrupt.h>
#include <laser/rotary.h>

int
main ( void )
{
  disable_interrupts (  ) ;
  
  _delay_ms ( 50 ) ; // Allow devices voltage to come rise

  selector_init (  ) ;
  interlock_init (  ) ;
  rotary_init (  ) ;
  timer1_init (  ) ;
  
  timer1_pwm_on (  ) ;
  timer1_freq ( 2000U ) ;
  timer1_duty (    5U ) ;

  while ( 1 )
  {
    if ( interlock_open (  ) )
    {
      prev = timer1_duty ( 5u ) ;
      
      while ( interlock_open (  ) ||  ) ;
      
      timer1_duty ( prev ) ;
    }
    
    select = selector_ ;
    
    switch (  )
    {
      
    }
    
    rotary_step (  ) ;
  }

  return 0 ;
}
