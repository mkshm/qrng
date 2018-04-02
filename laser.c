
#include <util/delay.h>

#include <laser/timer1.h>
#include <laser/interrupt.h>
#include <laser/serial.h>

ISR ( USART_TX_vect )
{
  
}

ISR ( USART_RX_vect )
{
  
}

int
main ( void )
{
  disable_interrupts (  ) ;
  
  _delay_ms ( 50 ) ; // Allow devices voltage to come rise

  timer1_init    (  ) ;
  interlock_init (  ) ;
  
  enable_interrupts (  ) ;

  while ( 1 )
  {
    if ( interlock_open (  ) )
    {
      prev = timer1_duty ( 5u ) ;
      
      while ( interlock_open (  ) ||  ) ;
      
      timer1_duty ( prev ) ;
    }
    
    switch ( 1 )
    {
      
    }
    
  }

  return 0 ;
}
