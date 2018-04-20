/*
 * This program implements the NIST Frequency Test.
 * Michael Free 04-13-2018
 *
 */

#include <unistd.h>

#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <tst-common.h>

int
test ( int fd )
{
  error_t pass ;
  double  total ;
  double  nbits ;
  double  temp ;
  unsigned char * buff ;
  ssize_t cnt ;
  ssize_t tmp ;

  if ( NULL == ( buff = malloc ( 128 ) ) )
  {
    argp_verbose ( "malloc" , "failed to allocate buffer" , 0.0 ) ;
    return EXIT_FAILURE ;
  }

  /* The following using popcount which counts the number of 1's set
     in an integer. So, count the number of 1's set, increment the
     running total by this amount. Then, decrement by how many 0's are
     set by taking the bitwise NOT of the same value. */

  while ( 0 < ( cnt = read ( fd , buff , 128 ) ) )
  {
    for ( tmp = 0 ; tmp < cnt ; tmp += 1 )
    {
      total += ( double ) __builtin_popcount ( ( unsigned int )     buff [ tmp ] ) ;
      total -= ( double ) __builtin_popcount ( ( unsigned int ) ( ~ buff [ tmp ] ) ) ;
      nbits += 8 ;
    }
  }

  if ( NULL != buff ) free ( buff ) ;

  temp = erfc ( total / sqrt ( 2 * nbits ) ) ;

  if ( 0.01 <= temp )
  {
    argp_verbose ( "[tst-freq]" , "You passed the test p-value>=" , temp ) ;
    pass = 0 ;
  }
  else
  {
    argp_verbose ( "[tst-freq]" , "You failed the test p-value=" , temp ) ;
    pass = 1 ;
  }

  return pass ;
}
