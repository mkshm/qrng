
#ifndef __UTIL_LOCK_H__
#define __UTIL_LOCK_H__

#include <stdbool.h>

#define STATIC_INLINE static inline __attribute__ (( __always_inline__ , __hot__ ))

STATIC_INLINE void
lock_acquire ( volatile bool * const next )
{
  while ( ! ( * next ) ) ;
  ( * next ) = false ;
}

STATIC_INLINE void
lock_release ( volatile bool * const next )
{
  ( * next ) = true ;
}

#undef STATIC_INLINE
#endif
