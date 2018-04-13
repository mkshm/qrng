/*
 * This program implements the NIST Frequency Test.
 * Michael Free 04-13-2018
 *
 */


#include <argp.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

static char * input_file    = NULL ;
static char * printf_format = NULL ;

static int verbose_output = 0 ;

int errno ;

static error_t argp_callback ( int , char * , struct argp_state * ) ;

error_t      argp_err_exit_status ;
const char * argp_program_bug_address = "<11mikefree@gmail.com>" ;
const char * argp_program_version     = "tst-freq 1.0" ;

static const struct argp_option argp_option [  ] = {
  { "verbose" , 'v' , NULL     , 0 , "Produce verbose output" } ,
  { "quiet"   , 'q' , NULL     , 0 , "Don't produce any output" } ,
  { 0 } ,
} ;

static const struct argp argp = {
  . options  = argp_option ,
  . parser   = argp_callback ,
  . args_doc = "FILE" ,
  . doc      = "Tempory Documentation - Please Replace"
} ;

static void
argp_verbose ( const char * str , const char * err , const double extra )
{
  if ( verbose_output >= 1 ) fprintf ( stderr , "%s: %s %f\n" , str , err , extra ) ;
}

static error_t
argp_callback ( int key , char * arg , struct argp_state * argp )
{
  error_t ret = ARGP_ERR_UNKNOWN ;

  switch ( key )
  {
    case 'v' :
      verbose_output += 1 ;
      ret = 0 ;
    break ;
    case 'q' :
      verbose_output = 0 ;
      ret = 0 ;
    break ;
    case 'f' :
      printf_format = arg ;
      ret = 0 ;
    break ;
    case ARGP_KEY_ARG :
      input_file = arg ;
      ret = 0 ;
    break ;
    default :
      ret = 0 ;
    break ;
  }

  return ret ;
}

static error_t
test ( void )
{
  error_t pass ;
  double  total ;
  double  nbits ;
  double  temp ;
  int fd ;
  unsigned char * buff ;
  ssize_t cnt ;
  ssize_t tmp ;

  if ( NULL == ( buff = malloc ( 128 ) ) )
  {
    argp_verbose ( "malloc" , "failed to allocate buffer" , 0.0 ) ;
    return EXIT_FAILURE ;
  }

  if ( -1 == ( fd = open ( input_file , O_RDONLY ) ) )
  {
    argp_verbose ( "open" , strerror ( errno ) , 0.0 ) ;
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
  if ( -1 != fd ) close ( fd ) ;

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

int
main ( int argc , char ** argv )
{
  error_t ret ;

  /* Collect and parse command line arguments then run the test */

  if ( 0 == ( ret = argp_parse ( & argp , argc , argv , 0 , NULL , NULL ) ) )
  {
    ret = test (  ) ;
  }

  return ret ;
}
