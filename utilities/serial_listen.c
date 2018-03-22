
#include <argp.h>
#include <errno.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

#include <stdlib.h>
#include <string.h>

static speed_t tcconvspeed ( int ) ;

static tcflag_t serial_cflag =  0 ; /* serial control flags */
static tcflag_t serial_oflag =  0 ; /* serial output flags */
static tcflag_t serial_iflag =  0 ; /* serial input flags */
static tcflag_t serial_lflag =  0 ; /* serial local flags */
static speed_t  serial_baud  = B0 ;
static int      serial_port  = -1 ;

static error_t argp_callback ( int , char * , struct argp_state * ) ;

error_t      argp_err_exit_status ;
const char * argp_program_bug_address = "<11mikefree@gmail.com>" ;
const char * argp_program_version     = "serial_listen 1.0" ;

static const struct argp_option argp_option [  ] = {
  { "verbose" , 'v' , NULL     , 0 , "Produce verbose output" } ,
  { "quiet"   , 'q' , NULL     , 0 , "Don't produce any output" } ,
  { "baud"    , 'b' , "NUMBER" , 0 , "TTY baud rate"  } ,
  { "stops"   , 's' , "NUMBER" , 0 , "Number of stop bits"  } ,
  { "even-parity" , 'p' , NULL , 0 , "Enable Even parity"  } ,
  { "odd-parity"  , 'P' , NULL , 0 , "Enable Odd parity"  } ,
  { 0 } ,
} ;

static const struct argp argp = {
  . options  = argp_option ,
  . parser   = argp_callback ,
  . args_doc = "FILE" ,
  . doc      = "Tempory Documentation - Please Replace"
} ;

static error_t
argp_callback ( int key , char * arg , struct argp_state * argp )
{
  error_t ret = 0 ;

  switch ( key )
  {
    case 'b' :
      serial_baud = tcconvspeed ( atoi ( arg ) ) ;
    break ;
    case 's' :
      if ( 2 <= atoi ( arg ) ) serial_cflag |= CSTOPB ;
    break ;
    case 'p' :
      serial_cflag |= PARENB ;
      serial_iflag |= INPCK ;
    break ;
    case 'P' :
      serial_cflag |= PARENB ;
      serial_cflag |= PARODD ;
      serial_iflag |= INPCK ;
    break ;
    case ARGP_KEY_ARG :
      ret = ARGP_ERR_UNKNOWN ;

      if ( -1 == ( serial_port = open ( arg , O_RDONLY | O_NOCTTY | O_SYNC ) ) ) perror ( "open" ) ;

      ret = 0 ;
    break ;
  }

  return ret ;
}

static void
init ( void )
{
  struct termios tty ;

  memset ( & tty , 0 , sizeof tty ) ;

  if ( 0 != tcgetattr ( serial_port , & tty ) ) perror ( "tcgetattr" ) ;

  cfmakeraw ( & tty ) ;

  tty . c_cflag |= serial_cflag | CBAUD | CLOCAL | CREAD ;
  tty . c_lflag |= serial_lflag ;
  tty . c_oflag |= serial_oflag ;
  tty . c_iflag |= serial_iflag ;

  tty . c_cc [ VMIN  ] = 16 ;
  tty . c_cc [ VTIME ] = 1 ;

  if ( cfsetispeed ( & tty , serial_baud ) ) perror ( "cfsetispeed" ) ;

  if ( 0 != tcsetattr ( serial_port , TCSANOW , & tty ) ) perror ( "tcsetattr" ) ;

  fputs ( "We got here\n" , stdout ) ;
}

static void
fini ( void )
{
  if ( -1 != serial_port ) close ( serial_port ) ;
}

static void
spin ( void )
{
  unsigned char buff = 0 ;
  while ( 1 )
  {
    if ( 1 == read ( serial_port , & buff , 1 ) ) fprintf ( stdout , "%hhu\n" , buff ) ;
  }
}

int
main ( int argc , char ** argv )
{
  error_t ret = 0 ;

  if ( 0 == ( ret = argp_parse ( & argp , argc , argv , 0 , NULL , NULL ) ) )
  {
    init (  ) ;
    spin (  ) ;
    fini (  ) ;
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
