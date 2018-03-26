
#ifndef __UTIL_SERIAL_H__
#define __UTIL_SERIAL_H__

#include <stdbool.h>

#define STATIC_INLINE static inline __attribute__ (( __always_inline__ , __hot__ ))

STATIC_INLINE unsigned char
lock_acquire ( unsigned char * const restrict next , const unsigned char * const restrict serv )
{
  unsigned char tikt = * next ++ ;
  while ( * serv != tikt ) ;
  return tikt ;
}

STATIC_INLINE void
lock_release ( unsigned char * const restrict serv )
{
  * serv ++ ;
}

#undef STATIC_INLINE
#endif
