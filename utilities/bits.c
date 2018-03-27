
#include <argp.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static char * input_file    = NULL ;
static char * printf_format = NULL ;

static int verbose_output = 0 ;

int errno ;

static error_t argp_callback ( int , char * , struct argp_state * ) ;

error_t      argp_err_exit_status ;
const char * argp_program_bug_address = "<11mikefree@gmail.com>" ;
const char * argp_program_version     = "serial_listen 1.0" ;

static const struct argp_option argp_option [  ] = {
  { "verbose" , 'v' , NULL     , 0 , "Produce verbose output" } ,
  { "quiet"   , 'q' , NULL     , 0 , "Don't produce any output" } ,
  { "format"  , 'f' , "NUMBER" , 0 , "Print format" } ,
  { 0 } ,
} ;

static const struct argp argp = {
  . options  = argp_option ,
  . parser   = argp_callback ,
  . args_doc = "FILE" ,
  . doc      = "Tempory Documentation - Please Replace"
} ;

static void
argp_verbose ( const char * str , const char * err )
{
  if ( verbose_output >= 1 ) fprintf ( stderr , "%s: %s\n" , str , err ) ;
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
doit ( void )
{
  int fd ;
  unsigned char * buff ;
  ssize_t cnt ;
  ssize_t tmp ;

  if ( NULL == ( buff = malloc ( 128 ) ) )
  {
    argp_verbose ( "malloc" , "failed to allocate buffer" ) ;
    return EXIT_FAILURE ;
  }

  if ( -1 == ( fd = open ( input_file , O_RDONLY ) ) )
  {
    argp_verbose ( "open" , strerror ( errno ) ) ;
    return EXIT_FAILURE ;
  }

  while ( 0 < ( cnt = read ( fd , buff , 128 ) ) )
  {
    for ( tmp = 0 ; tmp < cnt ; tmp += 1 )
    {
      if ( buff [ tmp ] & 0b00000001 ) fputs ( "1\n" , stdout ) ; else fputs ( "0\n" , stdout ) ;
      if ( buff [ tmp ] & 0b00000010 ) fputs ( "1\n" , stdout ) ; else fputs ( "0\n" , stdout ) ;
      if ( buff [ tmp ] & 0b00000100 ) fputs ( "1\n" , stdout ) ; else fputs ( "0\n" , stdout ) ;
      if ( buff [ tmp ] & 0b00001000 ) fputs ( "1\n" , stdout ) ; else fputs ( "0\n" , stdout ) ;
      if ( buff [ tmp ] & 0b00010000 ) fputs ( "1\n" , stdout ) ; else fputs ( "0\n" , stdout ) ;
      if ( buff [ tmp ] & 0b00100000 ) fputs ( "1\n" , stdout ) ; else fputs ( "0\n" , stdout ) ;
      if ( buff [ tmp ] & 0b01000000 ) fputs ( "1\n" , stdout ) ; else fputs ( "0\n" , stdout ) ;
      if ( buff [ tmp ] & 0b10000000 ) fputs ( "1\n" , stdout ) ; else fputs ( "0\n" , stdout ) ;
    }
  }

  if ( NULL != buff ) free ( buff ) ;
  if ( -1 != fd ) close ( fd ) ;
}

int
main ( int argc , char ** argv )
{
  error_t ret ;

  if ( 0 == ( ret = argp_parse ( & argp , argc , argv , 0 , NULL , NULL ) ) )
  {
    ret = doit (  ) ;
  }

  return ret ;
}
