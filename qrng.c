
#include <util/delay.h>

#include <qrng/timer1.h>
#include <qrng/interrupt.h>
#include <qrng/serial.h>
#include <qrng/lock.h>

#include <stdint.h>
#include <stdbool.h>

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

static volatile cast prev = { 0 } ;
static volatile cast curr = { 0 } ;

static volatile bool next = 0 ; /* Who is next in line? */

ISR ( TIMER1_CAPT_vect ) // The actual Timer1 Input Capture Event Interrupt Service Routine
{
  curr . val = ICR1 ; /* ICR1 is a special register which gets set to Timer1's counter TCNT1 upon entry */
  lock_release ( & next ) ;
}

ISR ( INT0_vect )
{
  curr . hi = TCNT0 ;
  curr . lo = TCNT2 ;
  lock_release ( & next ) ;
}

int
main ( void )
{
  cast mix ;
  cast temp ;

  disable_interrupts (  ) ;

  _delay_ms ( 50 ) ; /* Wait for the processors voltage to rise.  */

  /* Setup required facilities.  */
  
  serial_init (  ) ;
  timer1_init (  ) ;
  timer1_enable_capture  (  ) ;

  enable_interrupts (  ) ;

  /* BEGIN */
  
  lock_acquire ( & next ) ;
  
  mix . hi = prev . lo ^ curr . hi ;
  mix . lo = prev . hi ^ curr . lo ;
  
  while ( 1 )
  {
    lock_acquire ( & next ) ;
    
    temp . val = curr . val ;
    
    mix . hi ^= prev . lo ^ temp . hi ;
    mix . lo ^= prev . hi ^ temp . lo ;
    
    serial_wait (  ) ;         /* try and grab an empty buffer, then           */
    serial_send ( mix . lo ) ; /* send the byte using the empty buffer.        */
                               /* If this fails just move on to the next byte. */
    serial_empty (  ) ;        /* It shouldn't fail, unless the radioactive    */
    serial_send ( mix . hi ) ; /* source emits too quickly to keep up with     */
    
    prev . val = temp . val ;
  }

  return 0 ;
}
