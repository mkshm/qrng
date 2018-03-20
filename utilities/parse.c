
#include <stdio.h>

int
main ( void )
{
  FILE * fd ;
  unsigned short byte [ 16 ] ;
  size_t cnt ;
  if ( ( fd = fopen ( "example_output.txt" , "rb" ) ) )
  {
    while ( ( cnt = fread ( byte , 2 , 16 , fd ) ) )
    {
      while ( cnt > 1 )
      {
        fprintf ( stdout , "%hu " , byte [ cnt ] ) ;
        cnt -= 2 ;
      }
      if ( cnt ) fprintf ( stdout , "%u " , byte [ cnt ] ) ;
      fputs ( "\n" , stdout ) ;
    }
  }
  return 0 ;
}
