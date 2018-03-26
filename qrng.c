
#include <util/delay.h>

#include <qrng/timer1.h>
#include <qrng/interrupt.h>
#include <qrng/serial.h>
#include <qrng/lock.h>

#include <stdint.h>

typedef uint32_t u32 ;
typedef uint16_t u16 ;
typedef uint8_t  u08 ;

static void step3 ( void ) ;
static void step0 ( void ) ;

static volatile union __cast
{
  u32 time ;
  struct
  {
    u16 hi ;
    u16 lo ;
  } ;
} curr = { 0 } ;

static volatile u08 next = 0 ;
static volatile u08 serv = 0 ;

static volatile u08 bit = 0 ;

/*
 *  |---|___|---|___| Visual of what is happening below.
 *    0   1   2   3
 */

// These defines make the functions below more readable.

static volatile u32 time [ 4 ] ;
static volatile u32 delt [ 4 ] ;

static void ( * volatile timer1_step ) ( void ) = step0 ;

#define stp ( n ) timer1_step = step ## n

#define upc( tm ) ({ time [ tm ] = curr . time ; })

#define upd( tm ) \
  ({ \
    time [ tm ] = curr . time ; \
    delt [ 3 & ( tm - 1 ) ] = time [ tm ] - time [ 3 & ( tm - 1 ) ] ; \
  })

#define bts( tm ) \
  ({ \
    time [ tm ] = curr . time ; \
    delt [ 3 & ( tm - 1 ) ] = time [ tm ] - time [ 3 & ( tm - 1 ) ] ; \
    bit = ( delt [ 3 & ( tm - 1 ) ] > delt [ 3 & ( tm - 3 ) ] ) ; \
  })
/*
  - The first function, stp updates timer1_step to the next step.
  - The second function, upd, gets a new time, stores it the associated
      array given by the first argument. The second argument is for which
      delta to compute.
  - The Third function(s) compute and assign
*/
static void step10 ( void ) { stp ( 3  ) ; bts ( 2 ) ; }
static void step9  ( void ) { stp ( 10 ) ; bts ( 1 ) ; }
static void step8  ( void ) { stp ( 9  ) ; bts ( 0 ) ; }
static void step7  ( void ) { stp ( 8  ) ; bts ( 3 ) ; }
static void step6  ( void ) { stp ( 7  ) ; bts ( 2 ) ; }
static void step5  ( void ) { stp ( 6  ) ; bts ( 1 ) ; }
static void step4  ( void ) { stp ( 5  ) ; bts ( 0 ) ; }
static void step3  ( void ) { stp ( 4  ) ; bts ( 3 ) ; }
static void step2  ( void ) { stp ( 3  ) ; upd ( 2 ) ; }
static void step1  ( void ) { stp ( 2  ) ; upd ( 1 ) ; }
static void step0  ( void ) { stp ( 1  ) ; upc ( 0 ) ; }

ISR ( TIMER1_OVF_vect  ) // The actual Timer1 Overflow Interrupt Service Routine
{
  curr . hi ++ ;
}

ISR ( TIMER1_CAPT_vect ) // The actual Timer1 Input Capture Event Interrupt Service Routine
{
  curr . lo = ICR1 ; /* ICR1 is a special register which gets set to Timer1's counter TCNT1 upon entry */
  timer1_step  (  ) ;
  lock_release ( & serv ) ;
} 

int
main ( void )
{
  u08 byte , bpos ;

  disable_interrupts (  ) ;

  _delay_ms ( 50 ) ; /* Wait for the processors voltage to rise.  */

  /* Setup required facilities.  */
  
  serial_init (  ) ;
  timer1_init (  ) ;
  timer1_enable_overflow (  ) ;
  timer1_enable_capture  (  ) ;

  enable_interrupts (  ) ;

  /* BEGIN */
  
  while ( 1 )
  {
    byte = 0 ; /* Both byte and bpos have to be erased */
    bpos = 0 ; /* each time we go through the loop     */
    
    while ( ! ( 8 & bpos ) )
    {
      bpos = lock_acquire ( & next , & serv ) ;  /* lock_acquire conveniently returns bit-position */
      byte |= bit << ( 7 & bpos ) ;              /* set the bit in the byte */
    }
    
    if ( serial_empty (  ) )  /* try and grab an empty buffer      */
      serial_send ( byte ) ;  /* send data using the empty buffer  */
                              /* if this fails just move on to the next byte  */
  }

  return 0 ;
}
