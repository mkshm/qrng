
#ifndef __UTILITIES_STRING_H__
#define __UTILITIES_STRING_H__

static inline int
str_isdigit ( const char * str , size_t len )
{
  size_t tmp ;

  for ( tmp = 0 ; tmp < len ; tmp ++ )
  {
    if ( '\0' == str [ tmp ] ) break ;
    if ( ! isdigit ( str [ tmp ] ) ) return 1 ;
  }

  return 0 ;
}

#endif
