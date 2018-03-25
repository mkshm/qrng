
#include <argp.h>
#include <errno.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

#include <stdlib.h>
#include <string.h>

#include <util/string.h>

static speed_t tcconvspeed ( int ) ;

static tcflag_t serial_cflag = 0 ; /* serial control flags */
static tcflag_t serial_oflag = 0 ; /* serial output flags */
static tcflag_t serial_iflag = 0 ; /* serial input flags */
static tcflag_t serial_lflag = 0 ; /* serial local flags */

static char * serial_baud = NULL ;
static char * serial_port = NULL ;
static char * output_file = NULL ;
static char * serial_buff = NULL ;

static int verbose_output = 0 ;

int errno ;

static error_t argp_callback ( int , char * , struct argp_state * ) ;

error_t      argp_err_exit_status ;
const char * argp_program_bug_address = "<11mikefree@gmail.com>" ;
const char * argp_program_version     = "serial_listen 1.0" ;

static const struct argp_option argp_option [  ] = {
  { "verbose"     , 'v' , NULL     , 0 , "Produce verbose output" } ,
  { "quiet"       , 'q' , NULL     , 0 , "Don't produce any output" } ,
  { "output"      , 'o' , "STRING" , 0 , "Output file" } ,
  { "buffer-size" , 999 , "NUMBER" , 0 , "Buffer Size" } ,
  { "baud"        , 'b' , "NUMBER" , 0 , "TTY baud rate"  } ,
  { "extra-stop"  , 's' , NULL     , 0 , "An extra stop bit"  } ,
  { "even-parity" , 'p' , NULL     , 0 , "Enable Even parity"  } ,
  { "odd-parity"  , 'P' , NULL     , 0 , "Enable Odd parity"  } ,
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
    case 'b' :
      serial_baud = arg ;
      ret = 0 ;
    break ;
    case 's' :
      serial_cflag |= CSTOPB ;
      ret = 0 ;
    break ;
    case 'p' :
      serial_cflag |= PARENB ;
      serial_iflag |= INPCK ;
      ret = 0 ;
    break ;
    case 'P' :
      serial_cflag |= PARENB ;
      serial_cflag |= PARODD ;
      serial_iflag |= INPCK ;
      ret = 0 ;
    break ;
    case 'o' :
      output_file = arg ;
      ret = 0 ;
    break ;
    case 999 :
      serial_buff = arg ;
      ret = 0 ;
    break ;
    case ARGP_KEY_ARG :
      serial_port = arg ;
      ret = 0 ;
    break ;
    default :
      ret = 0 ;
    break ;
  }

  return ret ;
}

static int
sane ( void )
{
  int ret1 , ret2 ;

  if ( 0 != ( ret1 = str_isdigit ( serial_baud , 32 ) ) )
    argp_verbose ( "str_isdigit" , "serial_baud contains illegal characters" ) ;

  if ( 0 != ( ret2 = str_isdigit ( serial_buff , 32 ) ) )
    argp_verbose ( "str_isdigit" , "serial_buff contains illegal characters" ) ;

  return ret1 | ret2 ;
}

static void
spin ( void )
{
  struct termios tty ;
  void * buff ;
  int read_fd , write_fd ;
  unsigned char buff_size ;
  int read_speed ;

  memset ( & tty , 0 , sizeof tty ) ;

  buff_size  = atoi ( serial_buff ) ;
  read_speed = atoi ( serial_baud ) ;

  buff = malloc ( buff_size ) ;

  if ( -1 == ( write_fd = open ( output_file , O_WRONLY | O_NOCTTY | O_SYNC | O_CREAT ) ) )
    argp_verbose ( "open" , strerror ( errno ) ) ;

  if ( -1 == ( read_fd  = open ( serial_port , O_RDONLY | O_NOCTTY /*| O_NDELAY*/ ) ) )
    argp_verbose ( "open" , strerror ( errno ) ) ;

  if ( 0 != tcgetattr ( read_fd , & tty ) )
    argp_verbose ( "tcgetattr" , strerror ( errno ) ) ;

  cfmakeraw ( & tty ) ;

  tty . c_cflag |= serial_cflag | CBAUD | CLOCAL | CREAD ;
  tty . c_lflag |= serial_lflag ;
  tty . c_oflag |= serial_oflag ;
  tty . c_iflag |= serial_iflag ;

  tty . c_cc [ VMIN  ] = buff_size ;
  tty . c_cc [ VTIME ] =   0 ;

  if ( 0 != cfsetispeed ( & tty , tcconvspeed ( atoi ( serial_baud ) ) ) )
    argp_verbose ( "cfsetispeed" , strerror ( errno ) ) ;

  if ( 0 != tcsetattr ( read_fd , TCSANOW , & tty ) )
    argp_verbose ( "tcsetattr" , strerror ( errno ) ) ;

  while ( 1 )
  {
    if ( buff_size != read  ( read_fd  , buff , buff_size ) ) { argp_verbose ( "read"  , "failed to read bytes" ) ; break ; }
    if ( buff_size != write ( write_fd , buff , buff_size ) ) { argp_verbose ( "write" , "failed to write bytes" ) ; break ; }
  }

  if ( -1 !=  read_fd ) close (  read_fd ) ;
  if ( -1 != write_fd ) close ( write_fd ) ;
}

int
main ( int argc , char ** argv )
{
  error_t ret = 0 ;

  if ( 0 == ( ret = argp_parse ( & argp , argc , argv , 0 , NULL , NULL ) ) )
  {
    if ( sane (  ) ) return EXIT_FAILURE ;
    spin (  ) ;
  }

  return ret ;
}

static inline speed_t
tcconvspeed ( int speed )
{
  if ( speed >= 4000000 ) return B4000000 ;
  if ( speed >= 3500000 ) return B3500000 ;
  if ( speed >= 3000000 ) return B3000000 ;
  if ( speed >= 2500000 ) return B2500000 ;
  if ( speed >= 2000000 ) return B2000000 ;
  if ( speed >= 1500000 ) return B1500000 ;
  if ( speed >= 1152000 ) return B1152000 ;
  if ( speed >= 1000000 ) return B1000000 ;
  if ( speed >= 921600  ) return B921600  ;
  if ( speed >= 576000  ) return B576000  ;
  if ( speed >= 500000  ) return B500000  ;
  if ( speed >= 460800  ) return B460800  ;
  if ( speed >= 230400  ) return B230400  ;
  if ( speed >= 115200  ) return B115200  ;
  if ( speed >= 57600   ) return B57600   ;
  if ( speed >= 38400   ) return B38400   ;
  if ( speed >= 19200   ) return B19200   ;
  if ( speed >= 9600    ) return B9600    ;
  if ( speed >= 4800    ) return B4800    ;
  if ( speed >= 2400    ) return B2400    ;
  if ( speed >= 1800    ) return B1800    ;
  if ( speed >= 1200    ) return B1200    ;
  if ( speed >= 600     ) return B600     ;
  if ( speed >= 300     ) return B300     ;
  if ( speed >= 200     ) return B200     ;
  if ( speed >= 150     ) return B150     ;
  if ( speed >= 134     ) return B134     ;
  if ( speed >= 110     ) return B110     ;
  if ( speed >= 75      ) return B75      ;
  if ( speed >= 50      ) return B50      ;
                          return B0       ;
}
