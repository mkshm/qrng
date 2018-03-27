
#include <util/delay.h>

#include <qrng/timer1.h>
#include <qrng/interrupt.h>
#include <qrng/serial.h>
#include <qrng/lock.h>

#include <stdint.h>

typedef uint32_t u32 ;
typedef uint16_t u16 ;
typedef uint8_t  u08 ;

typedef union __cast
{
  u16 val ;
  struct
  {
    u08 hi ;
    u08 lo ;
  } ;
} cast ;

typedef union __cast2
{
  u32 val ;
  struct
  {
    u16 hi ;
    u16 lo ;
  } ;
} cast2 ;

static volatile cast prev = { 0 } ;
static volatile cast curr = { 0 } ;

static volatile u08 next = 0 ; /* Who is next in line? */
static volatile u08 serv = 0 ; /* What ticket are we serving? */

ISR ( TIMER1_CAPT_vect ) // The actual Timer1 Input Capture Event Interrupt Service Routine
{
  prev . val = curr .val ;
  curr . val = ICR1 ; /* ICR1 is a special register which gets set to Timer1's counter TCNT1 upon entry */
  lock_release ( & serv , & next ) ;
} 

int
main ( void )
{
  cast mix ;

  disable_interrupts (  ) ;

  _delay_ms ( 50 ) ; /* Wait for the processors voltage to rise.  */

  /* Setup required facilities.  */
  
  serial_init (  ) ;
  timer1_init (  ) ;
  timer1_enable_capture  (  ) ;

  enable_interrupts (  ) ;

  /* BEGIN */
  
  lock_acquire ( & next , & serv ) ;
  
  mix . val = prev . val ^ curr . val ;
  
  while ( 1 )
  {
    lock_acquire ( & next , & serv ) ;
    
    mix . val = prev . val ^ curr . val ;
    
    if ( serial_empty (  ) )      /* try and grab an empty buffer, then           */
      serial_send ( mix . lo ) ;  /* send the byte using the empty buffer.        */
                                  /* If this fails just move on to the next byte. */
    if ( serial_empty (  ) )      /* It shouldn't fail, unless the radioactive    */
      serial_send ( mix .hi ) ;   /* source emits too quickly to keep up with     */
  }

  return 0 ;
}
