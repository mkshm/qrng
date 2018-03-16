
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
  static unsigned char bit = 0 , hit = 0 ; // Create variables
  static unsigned long prev ;
  static unsigned long dt [ 4 ] ;

  union { unsigned long lohi ; struct { unsigned short lo , hi ; } ; } curr ; // This is a portable way to use 2 16-bit
                                                                              // integers to create a 32 bit integer.

  curr . lo = ICR1 ; // read TCNT1, which is copied to ICR1 on capture
  curr . hi = high ;

  dt [ hit & 3 ] = curr . lohi - prev ; // create the delta

  /*
   *  |---|___|---|___| Visual of the below switch statement.
   *    0   1   2   3
   */

  switch ( ( hit ++ ) & 3 )
  {
    case 0 : buff [ head ] = ( dt [ 0 ] > dt [ 2 ] ) << ( ( bit ++ ) & 7 ) ; break ; // The only confusing part here
    case 1 : buff [ head ] = ( dt [ 1 ] > dt [ 3 ] ) << ( ( bit ++ ) & 7 ) ; break ; // is the order in which deltas
    case 2 : buff [ head ] = ( dt [ 2 ] > dt [ 0 ] ) << ( ( bit ++ ) & 7 ) ; break ; // are compared, and the bitwise
    case 3 : buff [ head ] = ( dt [ 3 ] > dt [ 1 ] ) << ( ( bit ++ ) & 7 ) ; break ; // logic
  }

  head += ( bit & 8 ) >> 2 ; // increment head every byte written.
  prev = curr . lohi ;
}

int
main ( void )
{
  disable_interrupts (  ) ; // Disable interrupts and wait for the processors voltage to rise.

  _delay_ms ( 50 ) ;

  serial_init (  ) ;            // Setup required facilities.
  timer1_init (  ) ;
  timer1_enable_overflow (  ) ;
  timer1_enable_capture (  ) ;

  enable_interrupts (  ) ; //enable interrupts, and begin sending data to serial port.

  while ( 1 ) serial_loop ( buff , & head , & tail ) ;

  // We shouldn't ever get here.
  // I'm extremely pedantic, whatever you initialize you de-initialize.

  timer1_disable_capture (  ) ;
  timer1_disable_overflow (  ) ;
  timer1_stop (  ) ;

  sleep_mode (  ) ;

  return 0 ;
}
