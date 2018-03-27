
#ifndef __UTIL_LOCK_H__
#define __UTIL_LOCK_H__

#include <stdbool.h>

#define STATIC_INLINE static inline __attribute__ (( __always_inline__ , __hot__ ))

STATIC_INLINE void
lock_acquire ( volatile unsigned char * const next )
{
  ( * next ) = 1 ;
  while ( ( * next ) ) ;
}

STATIC_INLINE void
lock_release ( volatile unsigned char * const next )
{
  ( * next ) = 0 ;
}

#undef STATIC_INLINE
#endif
