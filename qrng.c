
#include <util/delay.h>

#include <qrng/timer1.h>
#include <qrng/interrupt.h>
#include <qrng/serial.h>

#include <stdint.h>

typedef uint32_t u32 ;
typedef uint16_t u16 ;
typedef uint8_t  u08 ;

static void step3 ( void ) ;
static void step0 ( void ) ;

static volatile u32 time [ 4 ] ;
static volatile u32 delt [ 4 ] ;
static volatile u16 high ;

static volatile u08 buff [ 256 ] ;
static volatile u08 head , tail ;

static void ( * volatile timer1_step ) ( void ) = step0 ;

// This function is a portable way of appending
// 2 16 bit ints into a 32 bit int.

/*
 *  |---|___|---|___| Visual of what is happening below.
 *    0   1   2   3
 */

// These defines make the functions below more readable.

static inline u32 __attribute__ (( __always_inline__ , __hot__ ))
clk ( void )
{
  typedef union { u32 lohi ; struct { u16 lo ; u16 hi ; } ; } caster ;

  const caster cast = {
    . lo = ICR1 ,
    . hi = high
  } ;

  return cast . lohi ;
}

#define stp( n  ) timer1_step = step ## n

#define upc( tm )      time [ tm ] = clk (  )
#define upd( tm , dt ) time [ tm ] = clk (  ) ; delt [ dt ] = time [ tm ] - time [ dt ]

#define btn( new , old , n ) buff [ head    ] |= ( delt [ new ] > delt [ old ] ) << n
#define bts( new , old , n ) buff [ head    ]  = ( delt [ new ] > delt [ old ] ) << n
#define bti( new , old , n ) buff [ head ++ ] |= ( delt [ new ] > delt [ old ] ) << n
/*
  - The first function, stp updates timer1_step to the next step.
  - The second function, upd, gets a new time, stores it the associated
      array given by the first argument. The second argument is for which
      delta to compute.
  - The Third function(s) compute and assign
*/
static void step10 ( void ) { stp ( 3  ) ; upd ( 2 , 1 ) ; bti ( 1 , 3 , 7 ) ; }
static void step9  ( void ) { stp ( 10 ) ; upd ( 1 , 0 ) ; btn ( 0 , 2 , 6 ) ; }
static void step8  ( void ) { stp ( 9  ) ; upd ( 0 , 3 ) ; btn ( 3 , 1 , 5 ) ; }
static void step7  ( void ) { stp ( 8  ) ; upd ( 3 , 2 ) ; btn ( 2 , 0 , 4 ) ; }
static void step6  ( void ) { stp ( 7  ) ; upd ( 2 , 1 ) ; btn ( 1 , 3 , 3 ) ; }
static void step5  ( void ) { stp ( 6  ) ; upd ( 1 , 0 ) ; btn ( 0 , 2 , 2 ) ; }
static void step4  ( void ) { stp ( 5  ) ; upd ( 0 , 3 ) ; btn ( 3 , 1 , 1 ) ; }
static void step3  ( void ) { stp ( 4  ) ; upd ( 3 , 2 ) ; bts ( 2 , 0 , 0 ) ; }

static void step2  ( void ) { stp ( 3  ) ; upd ( 2 , 1 ) ; }
static void step1  ( void ) { stp ( 2  ) ; upd ( 1 , 0 ) ; }
static void step0  ( void ) { stp ( 1  ) ; upc ( 0 ) ; }

ISR ( TIMER1_OVF_vect  ) { high ++ ;          } // The actual Timer1 Overflow Interrupt Service Routine
ISR ( TIMER1_CAPT_vect ) { timer1_step (  ) ; } // The actual Timer1 Input Capture Event Interrupt Service Routine

int
main ( void )
{
  disable_interrupts (  ) ; // Disable interrupts and wait for the processors voltage to rise.

  _delay_ms ( 50 ) ;

  serial_init (  ) ;            // Setup required facilities.
  timer1_init (  ) ;
  timer1_enable_overflow (  ) ;
  timer1_enable_capture  (  ) ;

  enable_interrupts (  ) ; // Enable interrupts, and begin sending data to serial port.

  while ( 1 )
  {
    serial_wait ( /* head , tail */ ) ;
    while ( head == tail ) ;
    serial_send ( buff [ tail ++ ] ) ;
  }

  return 0 ;
}
