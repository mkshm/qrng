
#include <util/delay.h>
#include <util/timer1.h>
#include <util/interrupt.h>
#include <util/debug.h>
#include <util/pins.h>
#include <util/serial.h>

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define HOT_INLINE inline __attribute__ (( __always_inline__ , __hot__ ))

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

static void ( *volatile timer1_step ) ( void ) = step0 ;

static HOT_INLINE u32
tm ( void )
{
  struct lohi { u16 lo,hi; } temp = {.lo=ICR1,.hi=high} ;
  typedef union { struct lohi d ; u32 lohi ; } cast ;
  return ((cast)temp) . lohi ;
}

/*
   *  |---|___|---|___| Visual of the below switch statement.
   *    0   1   2   3
   */

static void step10 ( void ) { timer1_step = step3  ; time [ 2 ] = tm ( ) ; delt [ 1 ] = time [ 2 ] - time [ 1 ] ; buff [ head ++ ] |= ( delt [ 1 ] > delt [ 3 ] ) << 7 ; }
static void step9  ( void ) { timer1_step = step10 ; time [ 1 ] = tm ( ) ; delt [ 0 ] = time [ 1 ] - time [ 0 ] ; buff [ head    ] |= ( delt [ 0 ] > delt [ 2 ] ) << 6 ; }
static void step8  ( void ) { timer1_step = step9  ; time [ 0 ] = tm ( ) ; delt [ 3 ] = time [ 0 ] - time [ 3 ] ; buff [ head    ] |= ( delt [ 3 ] > delt [ 1 ] ) << 5 ; }
static void step7  ( void ) { timer1_step = step8  ; time [ 3 ] = tm ( ) ; delt [ 2 ] = time [ 3 ] - time [ 2 ] ; buff [ head    ] |= ( delt [ 2 ] > delt [ 0 ] ) << 4 ; }
static void step6  ( void ) { timer1_step = step7  ; time [ 2 ] = tm ( ) ; delt [ 1 ] = time [ 2 ] - time [ 1 ] ; buff [ head    ] |= ( delt [ 1 ] > delt [ 3 ] ) << 3 ; }
static void step5  ( void ) { timer1_step = step6  ; time [ 1 ] = tm ( ) ; delt [ 0 ] = time [ 1 ] - time [ 0 ] ; buff [ head    ] |= ( delt [ 0 ] > delt [ 2 ] ) << 2 ; }
static void step4  ( void ) { timer1_step = step5  ; time [ 0 ] = tm ( ) ; delt [ 3 ] = time [ 0 ] - time [ 3 ] ; buff [ head    ] |= ( delt [ 3 ] > delt [ 1 ] ) << 1 ; }
static void step3  ( void ) { timer1_step = step4  ; time [ 3 ] = tm ( ) ; delt [ 2 ] = time [ 3 ] - time [ 2 ] ; buff [ head    ]  = ( delt [ 2 ] > delt [ 0 ] ) << 0 ; }

static void step2  ( void ) { timer1_step = step3  ; time [ 2 ] = tm ( ) ; delt [ 1 ] = time [ 2 ] - time [ 1 ] ; }
static void step1  ( void ) { timer1_step = step2  ; time [ 1 ] = tm ( ) ; delt [ 0 ] = time [ 1 ] - time [ 0 ] ; }
static void step0  ( void ) { timer1_step = step1  ; time [ 0 ] = tm ( ) ; }

ISR ( TIMER1_OVF_vect )
{
  high ++ ;
}

ISR ( TIMER1_CAPT_vect )
{
  timer1_step (  ) ;
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
