
#ifndef __MF_TYPE_H__
#define __MF_TYPE_H__

#define U08(C) C 
#define S08(C) C
#define U16(C) C ## u
#define S16(C) C
#define U32(C) C ## ul
#define S32(C) C ## l
#define U64(C) C ## ull
#define S64(C) C ## ll

typedef unsigned char      u08 ;
typedef   signed char      s08 ;
typedef unsigned short     u16 ;
typedef   signed short     s16 ;
typedef unsigned long      u32 ;
typedef   signed long      s32 ;
typedef unsigned long long u64 ;
typedef   signed long long s64 ;

#endif
