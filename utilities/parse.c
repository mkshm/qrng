
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

static unsigned long long
cast ( const void * buff , ssize_t incr )
{
  unsigned long long temp = 0 ;
  switch ( incr )
  {
    default :
    case 1 : memcpy ( & temp , buff , 1 ) ; break ;
    case 2 : memcpy ( & temp , buff , 2 ) ; break ;
    case 4 : memcpy ( & temp , buff , 4 ) ; break ;
    case 8 : memcpy ( & temp , buff , 8 ) ; break ;
  }
  return temp ;
}

static void
init ( const char ** pfmt , ssize_t * incr )
{
  unsigned long type ;

  if ( NULL == pfmt ) return ;
  if ( NULL == incr ) return ;

#define T( a , b , c , d ) (unsigned long)(((d)<<24)|((c)<<16)|((b)<<8)|(a))

  switch ( ( type = T ( printf_format [ 0 ] ,
                        printf_format [ 1 ] ,
                        printf_format [ 2 ] ,
                        printf_format [ 3 ] ) ) )
  {
    default :
    case T('u','0','8','\0') : * pfmt = "%hhu\n" ; * incr = 1 ; break ;
    case T('s','0','8','\0') : * pfmt = "%hhd\n" ; * incr = 1 ; break ;
    case T('u','1','6','\0') : * pfmt = "%hu\n"  ; * incr = 2 ; break ;
    case T('s','1','6','\0') : * pfmt = "%hd\n"  ; * incr = 2 ; break ;
    case T('u','3','2','\0') : * pfmt = "%u\n"   ; * incr = 4 ; break ;
    case T('s','3','2','\0') : * pfmt = "%d\n"   ; * incr = 4 ; break ;
    case T('u','6','4','\0') : * pfmt = "%llu\n" ; * incr = 8 ; break ;
    case T('s','6','4','\0') : * pfmt = "%lld\n" ; * incr = 8 ; break ;
    case T('f','3','2','\0') : * pfmt = "%f\n"   ; * incr = 4 ; break ;
    case T('F','3','2','\0') : * pfmt = "%F\n"   ; * incr = 4 ; break ;
    case T('e','3','2','\0') : * pfmt = "%e\n"   ; * incr = 4 ; break ;
    case T('E','3','2','\0') : * pfmt = "%E\n"   ; * incr = 4 ; break ;
    case T('g','3','2','\0') : * pfmt = "%g\n"   ; * incr = 4 ; break ;
    case T('G','3','2','\0') : * pfmt = "%G\n"   ; * incr = 4 ; break ;
    case T('a','3','2','\0') : * pfmt = "%a\n"   ; * incr = 4 ; break ;
    case T('A','3','2','\0') : * pfmt = "%A\n"   ; * incr = 4 ; break ;
    case T('f','6','4','\0') : * pfmt = "%f\n"   ; * incr = 8 ; break ;
    case T('F','6','4','\0') : * pfmt = "%F\n"   ; * incr = 8 ; break ;
    case T('e','6','4','\0') : * pfmt = "%e\n"   ; * incr = 8 ; break ;
    case T('E','6','4','\0') : * pfmt = "%E\n"   ; * incr = 8 ; break ;
    case T('g','6','4','\0') : * pfmt = "%g\n"   ; * incr = 8 ; break ;
    case T('G','6','4','\0') : * pfmt = "%G\n"   ; * incr = 8 ; break ;
    case T('a','6','4','\0') : * pfmt = "%a\n"   ; * incr = 8 ; break ;
    case T('A','6','4','\0') : * pfmt = "%A\n"   ; * incr = 8 ; break ;
  }
#undef T
}

static error_t
doit ( void )
{
  int fd ;
  void * buff ;
  const char * pfmt ;
  ssize_t cnt ;
  ssize_t tmp ;
  ssize_t incr ;

  init ( & pfmt , & incr ) ;

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
    for ( tmp = 0 ; tmp < cnt ; tmp += incr ) fprintf ( stdout , pfmt , cast ( buff , incr ) ) ;
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
