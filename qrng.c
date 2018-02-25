
#include <stddef.h>

#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/sfr_defs.h>

#include <stdio.h>

#include <mf_type.h>

#include <avr/avr_mcu_section.h>
AVR_MCU ( F_CPU , "atmega328p" ) ;

const struct avr_mmcu_vcd_trace_t _mytrace[]  _MMCU_ = {
  { AVR_MCU_VCD_SYMBOL("UDR0"), .what = (void*)&UDR0, },
  { AVR_MCU_VCD_SYMBOL("UDRE0"), .mask = (1 << UDRE0), .what = (void*)&UCSR0A, },
};

static volatile u08 over ;

ISR ( TIMER1_OVF_vect )
{
  over ++ ;
}

ISR ( TIMER1_Comp_vect )
{
}

static int
uart_putchar ( char c , FILE * fd )
{
  if ( c == '\n' ) uart_putchar ( '\r' , fd ) ;
  loop_until_bit_is_set ( UCSR0A , UDRE0 ) ;
  UDR0 = c ;
  return 0 ;
}

static FILE mystdout = FDEV_SETUP_STREAM ( uart_putchar ,
                                           NULL ,
                                           _FDEV_SETUP_WRITE ) ;

int
main ( void )
{
  stdout = & mystdout ;

  TCCR1B = _BV ( CS10 ) ;
  TCCR1A = 0 ;
  TIMSK1 = _BV ( TOIE1 ) ;

  sei (  ) ;

  for (;;) sleep_mode (  ) ;

  return 0 ;
}
