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

static int     test ( int ) ;
static error_t argp_callback ( int , char * , struct argp_state * ) ;

error_t      argp_err_exit_status ;
const char * argp_program_bug_address = "<11mikefree@gmail.com>" ;
const char * argp_program_version     = "test-suite 1.0" ;

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

int
main ( int argc , char ** argv )
{
  error_t ret ;
  int fd ;

  /* Collect and parse command line arguments then run the test */

  if ( 0 == ( ret = argp_parse ( & argp , argc , argv , 0 , NULL , NULL ) ) )
  {
    if ( -1 == ( fd = open ( input_file , O_RDONLY ) ) )
    {
      argp_verbose ( "open" , strerror ( errno ) , 0.0 ) ;
      return EXIT_FAILURE ;
    }

    ret = test ( fd ) ;

    if ( -1 != fd ) close ( fd ) ;
  }

  return ret ;
}
