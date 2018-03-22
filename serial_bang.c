
#include <util/delay.h>

#include <qrng/interrupt.h>
#include <qrng/serial.h>

int
main ( void )
{
  disable_interrupts (  ) ; // Disable interrupts and wait for the processors voltage to rise.

  _delay_ms ( 50 ) ;

  serial_init (  ) ;            // Setup required facilities.

  while ( 1 )
  {
    serial_wait (  ) ;
    serial_send ( 0b10101010 ) ;

    _delay_ms ( 50 ) ;
  }

  return 0 ;
}
