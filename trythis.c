
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
  u16 time ;
  struct
  {
    u08 hi ;
    u08 lo ;
  } ;
} cast ;

static volatile cast prev = { 0 } ;
static volatile cast curr = { 0 } ;

static volatile u08 next = 0 ; /* Who is next in line? */
static volatile u08 serv = 0 ; /* What ticket are we serving? */

ISR ( TIMER1_CAPT_vect ) // The actual Timer1 Input Capture Event Interrupt Service Routine
{
  curr . lo = ICR1 ; /* ICR1 is a special register which gets set to Timer1's counter TCNT1 upon entry */
  lock_release ( & serv , & next ) ;
} 

static inline u08 __attribute__ (( __always_inline__ ))
mix ( void )
{
  return ;
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
  timer1_enable_capture  (  ) ;

  enable_interrupts (  ) ;

  /* BEGIN */
  
  while ( 1 )
  {
    byte = 0 ; /* Both byte and bpos have to be erased */
    bpos = 0 ; /* each time we go through the loop     */
    
    for (
      bpos = lock_acquire ( & next , & serv ) ; /* lock_acquire conveniently returns bit-position */
      0 == ( 8 & bpos ) ;                       /* Every eigth bit break out of loop              */
      byte |= bit << ( 7 & bpos )               /* Set the bpos bit in byte                       */
    ) ;
    
    if ( serial_empty (  ) )  /* try and grab an empty buffer, then           */
      serial_send ( byte ) ;  /* send the byte using the empty buffer.        */
                              /* If this fails just move on to the next byte. */
                              /* It shouldn't fail, unless the radioactive    */
                              /* source emits too quickly to keep up with     */
  }

  return 0 ;
}
