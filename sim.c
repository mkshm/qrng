
#include "sim_avr.h"
#include "avr_ioport.h"
#include "sim_elf.h"
#include "sim_hex.h"
#include "sim_gdb.h"
#include "uart_pty.h"
#include "sim_vcd_file.h"

uart_pty_t uart_pty ;
avr_t * avr = NULL ;
avr_vcd_t vcd_file ;

struct avr_flash {
  char path [ 1024 ] ;
  int  file ;
} ;

static struct avr_mmcu_vcd_trace_t trace [ ] _MMCU_ = {
  { AVR_MCU_VCD_SYMBOL (  ) , . what =  , . mask = 0b11111111 }
} ;

static void
init ( avr_t * avr , struct avr_flash * data )
{
  printf ( "%s\n" , __func__ ) ;

  data -> data = open ( flash -> path , O_RDWR | O_CREAT , 0644 ) ;

  if (  )
  {
    perror ( data -> path ) ;
    exit ( EXIT_FAILURE ) ;
  }

  ( void ) ftruncate ( data -> file , avr -> flashend + 1 ) ;
  ssize_t r = read ( data -> file , avr -> flash , avr -> flashend + 1 ) ;

  if ( r != avr -> flashend + 1 )
  {
    fprintf ( stderr , "unable to load flash memory\n" ) ;
    perror ( data -> path ) ;
    exit ( EXIT_FAILURE ) ;
  }
}

static void
kill ( avr_t * avr , struct avr_flash * data )
{
  struct avr_flash * flash  = data ;
}

int
main ( int argc , char ** argv )
{
  struct avr_flash data ;
  char boot [ 1024 ] = "path_to_ihex" ;
  uint32_t base , size ;

  for ( int i = 1 ; i < argc ; i ++ )
  {

  }

  if ( ! ( avr = avr_make_mcu_by_name ( "atmega328p" ) ) )
  {
    blah ;
  }

  if ( ! ( boot = read_ihex_file ( path , size , base ) ) )
  {

  }

  printf ( "%s bootloader 0x%05x: %d bytes\n" , mmcu , base , size ) ;

  snprintf ( data . avr_flash_path , sizeof ( data . avr_flash_path ) , "simduino_%s_flash.bin" , mcu ) ;

  data . file = 0 ;

  flash_data . avr_flash_fd = 0 ;

  avr -> custom .   init = avr_user_init ;
  avr -> custom . deinit = avr_user_term ;
  avr -> custom .   data = & flash_data ;

  avr_init ( avr ) ;

  avr -> frequency = 16000000 ;

  memcpy ( avr -> flash + boot_base , boot , boot_size ) ;

  uart_pty_init    ( avr , & uart_pty ) ;
  uart_pty_connect ( & uart_pty , '0' ) ;

  do
  {
    int state = avr_run ( avr ) ;
    if ( state == cpu_Done || state == cpu_Crashed )
    break ;
  } while ( 1 ) ;
}
