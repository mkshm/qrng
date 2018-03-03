
#ifndef __FENCE_H__
#define __FENCE_H__

#define fence(  ) __asm__ __volatile__ ( "" ::: "memory" )

#endif
