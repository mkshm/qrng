
#include <avr/io.h>

/*
 * This is a stripped down example to
 * configure ATmega328p serial I/O
 * for Asynchronous I/O
 * Complete descriptions of the Registers is
 *   available in the ATmega328p datasheet
 *   pages 243 - 253
 */

int
main ( void )
{
  /*
   * This selects the greatest possible baud rate
   * for the given MCU's frequency
   * given the following:
   *   baud = f_osc / ( mult * ( UBBR0 + 1 ) )
   */
  UBRR0 = 0u ;

  /*
   * The following enables 2x speed mode
   * This implicitly changes the baud rate modifier
   *   normally it is 16, in 2x it is 8
   * baud = f_osc / ( __mult__ * ( UBBR0 + 1 ) )
   */
  UCSR0A |= _BV ( U2X0 ) ;

  /*
   * The following sets up the I/O frame
   * The comination of bits UCSZ00 and UCSZ01 selects
   *   8 bits of data
   * The combination of bits UPM01 and USBSO selects
   *   1 stop bit and even parity
   * This results in a transmission of 11 bits per write
   *   8 data bits, 1 stop bit, 1 parity bit, 1 implicit start bit
   * 73.7% of The 2Mbit/sec rate is actual data = 1.45 Mbit/sec max
   *
   */
  UCSR0C |= _BV ( UCSZ00 ) | _BV ( UCSZ01 ) ;
  UCSR0C |= _BV ( UPM01  ) | _BV ( USBS0  ) ;

  /*
   * We only enable the transmitter, no reciever
   * Switch Pin 0 on PIND  to recieve
   * Switch Pin 1 on PORTD to transmit
   * This can be changed by uncommenting the lines after
   */
  UCSR0B |= _BV ( TXEN0 ) ;
  DDRD   |= _BV ( DDD1 ) ;

  /*
  UCSR0B |=   _BV ( RXEN0 ) ;
  DDRD   &= ~ _BV ( DDD0 ) ;
   */

  /* Annoyingly transmit 0b10101010 ( 0xAA, 170 ) */
  while ( 1 )
  {
    /* Wait for UDR to empty */
    while ( ! ( UCSR0A & _BV ( UDRE0 ) ) ) ;
    /* Write to UDR */
    UDR0 = 0b10101010 ;
  }
  /*
   * You could exploit the asynchroneity even further
   * by reading up on the flags register or using interrupts
   *   UDRE0, TXC0 flag in UCSR0A pg 244
   *   Data Register Empty Interrupt USART_UDRE_vect
   *   Transmission Complete Interrupt USART_TX_vect
   */
}
