
#ifndef __UTIL_LOCK_H__
#define __UTIL_LOCK_H__

#include <stdbool.h>

#define STATIC_INLINE static inline __attribute__ (( __always_inline__ , __hot__ ))

STATIC_INLINE unsigned char
lock_acquire ( volatile unsigned char * const restrict next ,
         const volatile unsigned char * const restrict serv )
{
  unsigned char tikt = ( * next ) ++ ;
  while ( ( * serv ) - 1 != tikt ) ;
  return tikt ;
}

STATIC_INLINE void
lock_release ( volatile unsigned char * const restrict serv ,
         const volatile unsigned char * const restrict next )
{
  ( * serv ) = ( * next ) ;
}

#undef STATIC_INLINE
#endif
