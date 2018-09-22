
#ifndef __QRNG_LOCK_H__
#define __QRNG_LOCK_H__

static inline void
lock_acquire ( volatile _Bool * const next )
{
  while ( ! ( * next ) ) ;
  ( * next ) = 0 ;
}

static inline void
lock_release ( volatile _Bool * const next )
{
  ( * next ) = 1 ;
}

#endif
