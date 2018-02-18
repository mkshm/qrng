# 1 "qrng.c"
# 1 "/home/azsazsin/projects/qrng//"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "qrng.c"

# 1 "/usr/lib/gcc/avr/7.3.0/include/stddef.h" 1 3 4
# 149 "/usr/lib/gcc/avr/7.3.0/include/stddef.h" 3 4

# 149 "/usr/lib/gcc/avr/7.3.0/include/stddef.h" 3 4
typedef int ptrdiff_t;
# 216 "/usr/lib/gcc/avr/7.3.0/include/stddef.h" 3 4
typedef unsigned int size_t;
# 328 "/usr/lib/gcc/avr/7.3.0/include/stddef.h" 3 4
typedef int wchar_t;
# 426 "/usr/lib/gcc/avr/7.3.0/include/stddef.h" 3 4
typedef struct {
  long long __max_align_ll __attribute__((__aligned__(__alignof__(long long))));
  long double __max_align_ld __attribute__((__aligned__(__alignof__(long double))));
# 437 "/usr/lib/gcc/avr/7.3.0/include/stddef.h" 3 4
} max_align_t;
# 3 "qrng.c" 2

# 1 "/usr/avr/include/avr/io.h" 1 3
# 99 "/usr/avr/include/avr/io.h" 3
# 1 "/usr/avr/include/avr/sfr_defs.h" 1 3
# 126 "/usr/avr/include/avr/sfr_defs.h" 3
# 1 "/usr/avr/include/inttypes.h" 1 3
# 37 "/usr/avr/include/inttypes.h" 3
# 1 "/usr/lib/gcc/avr/7.3.0/include/stdint.h" 1 3 4
# 9 "/usr/lib/gcc/avr/7.3.0/include/stdint.h" 3 4
# 1 "/usr/avr/include/stdint.h" 1 3 4
# 125 "/usr/avr/include/stdint.h" 3 4
typedef signed int int8_t __attribute__((__mode__(__QI__)));
typedef unsigned int uint8_t __attribute__((__mode__(__QI__)));
typedef signed int int16_t __attribute__ ((__mode__ (__HI__)));
typedef unsigned int uint16_t __attribute__ ((__mode__ (__HI__)));
typedef signed int int32_t __attribute__ ((__mode__ (__SI__)));
typedef unsigned int uint32_t __attribute__ ((__mode__ (__SI__)));

typedef signed int int64_t __attribute__((__mode__(__DI__)));
typedef unsigned int uint64_t __attribute__((__mode__(__DI__)));
# 146 "/usr/avr/include/stdint.h" 3 4
typedef int16_t intptr_t;




typedef uint16_t uintptr_t;
# 163 "/usr/avr/include/stdint.h" 3 4
typedef int8_t int_least8_t;




typedef uint8_t uint_least8_t;




typedef int16_t int_least16_t;




typedef uint16_t uint_least16_t;




typedef int32_t int_least32_t;




typedef uint32_t uint_least32_t;







typedef int64_t int_least64_t;






typedef uint64_t uint_least64_t;
# 217 "/usr/avr/include/stdint.h" 3 4
typedef int8_t int_fast8_t;




typedef uint8_t uint_fast8_t;




typedef int16_t int_fast16_t;




typedef uint16_t uint_fast16_t;




typedef int32_t int_fast32_t;




typedef uint32_t uint_fast32_t;







typedef int64_t int_fast64_t;






typedef uint64_t uint_fast64_t;
# 277 "/usr/avr/include/stdint.h" 3 4
typedef int64_t intmax_t;




typedef uint64_t uintmax_t;
# 10 "/usr/lib/gcc/avr/7.3.0/include/stdint.h" 2 3 4
# 38 "/usr/avr/include/inttypes.h" 2 3
# 77 "/usr/avr/include/inttypes.h" 3
typedef int32_t int_farptr_t;



typedef uint32_t uint_farptr_t;
# 127 "/usr/avr/include/avr/sfr_defs.h" 2 3
# 100 "/usr/avr/include/avr/io.h" 2 3
# 252 "/usr/avr/include/avr/io.h" 3
# 1 "/usr/avr/include/avr/iom328p.h" 1 3
# 253 "/usr/avr/include/avr/io.h" 2 3
# 585 "/usr/avr/include/avr/io.h" 3
# 1 "/usr/avr/include/avr/portpins.h" 1 3
# 586 "/usr/avr/include/avr/io.h" 2 3

# 1 "/usr/avr/include/avr/common.h" 1 3
# 588 "/usr/avr/include/avr/io.h" 2 3

# 1 "/usr/avr/include/avr/version.h" 1 3
# 590 "/usr/avr/include/avr/io.h" 2 3






# 1 "/usr/avr/include/avr/fuse.h" 1 3
# 239 "/usr/avr/include/avr/fuse.h" 3
typedef struct
{
    unsigned char low;
    unsigned char high;
    unsigned char extended;
} __fuse_t;
# 597 "/usr/avr/include/avr/io.h" 2 3


# 1 "/usr/avr/include/avr/lock.h" 1 3
# 600 "/usr/avr/include/avr/io.h" 2 3
# 5 "qrng.c" 2
# 1 "/usr/avr/include/avr/sleep.h" 1 3
# 6 "qrng.c" 2
# 1 "/usr/avr/include/avr/interrupt.h" 1 3
# 7 "qrng.c" 2
# 1 "/usr/avr/include/avr/pgmspace.h" 1 3
# 89 "/usr/avr/include/avr/pgmspace.h" 3
# 1 "/usr/lib/gcc/avr/7.3.0/include/stddef.h" 1 3 4
# 90 "/usr/avr/include/avr/pgmspace.h" 2 3
# 1085 "/usr/avr/include/avr/pgmspace.h" 3
extern const void * memchr_P(const void *, int __val, size_t __len) __attribute__((__const__));
# 1099 "/usr/avr/include/avr/pgmspace.h" 3
extern int memcmp_P(const void *, const void *, size_t) __attribute__((__pure__));






extern void *memccpy_P(void *, const void *, int __val, size_t);
# 1115 "/usr/avr/include/avr/pgmspace.h" 3
extern void *memcpy_P(void *, const void *, size_t);






extern void *memmem_P(const void *, size_t, const void *, size_t) __attribute__((__pure__));
# 1134 "/usr/avr/include/avr/pgmspace.h" 3
extern const void * memrchr_P(const void *, int __val, size_t __len) __attribute__((__const__));
# 1144 "/usr/avr/include/avr/pgmspace.h" 3
extern char *strcat_P(char *, const char *);
# 1160 "/usr/avr/include/avr/pgmspace.h" 3
extern const char * strchr_P(const char *, int __val) __attribute__((__const__));
# 1172 "/usr/avr/include/avr/pgmspace.h" 3
extern const char * strchrnul_P(const char *, int __val) __attribute__((__const__));
# 1185 "/usr/avr/include/avr/pgmspace.h" 3
extern int strcmp_P(const char *, const char *) __attribute__((__pure__));
# 1195 "/usr/avr/include/avr/pgmspace.h" 3
extern char *strcpy_P(char *, const char *);
# 1212 "/usr/avr/include/avr/pgmspace.h" 3
extern int strcasecmp_P(const char *, const char *) __attribute__((__pure__));






extern char *strcasestr_P(const char *, const char *) __attribute__((__pure__));
# 1232 "/usr/avr/include/avr/pgmspace.h" 3
extern size_t strcspn_P(const char *__s, const char * __reject) __attribute__((__pure__));
# 1248 "/usr/avr/include/avr/pgmspace.h" 3
extern size_t strlcat_P (char *, const char *, size_t );
# 1261 "/usr/avr/include/avr/pgmspace.h" 3
extern size_t strlcpy_P (char *, const char *, size_t );
# 1273 "/usr/avr/include/avr/pgmspace.h" 3
extern size_t strnlen_P(const char *, size_t) __attribute__((__const__));
# 1284 "/usr/avr/include/avr/pgmspace.h" 3
extern int strncmp_P(const char *, const char *, size_t) __attribute__((__pure__));
# 1303 "/usr/avr/include/avr/pgmspace.h" 3
extern int strncasecmp_P(const char *, const char *, size_t) __attribute__((__pure__));
# 1314 "/usr/avr/include/avr/pgmspace.h" 3
extern char *strncat_P(char *, const char *, size_t);
# 1328 "/usr/avr/include/avr/pgmspace.h" 3
extern char *strncpy_P(char *, const char *, size_t);
# 1343 "/usr/avr/include/avr/pgmspace.h" 3
extern char *strpbrk_P(const char *__s, const char * __accept) __attribute__((__pure__));
# 1354 "/usr/avr/include/avr/pgmspace.h" 3
extern const char * strrchr_P(const char *, int __val) __attribute__((__const__));
# 1374 "/usr/avr/include/avr/pgmspace.h" 3
extern char *strsep_P(char **__sp, const char * __delim);
# 1387 "/usr/avr/include/avr/pgmspace.h" 3
extern size_t strspn_P(const char *__s, const char * __accept) __attribute__((__pure__));
# 1401 "/usr/avr/include/avr/pgmspace.h" 3
extern char *strstr_P(const char *, const char *) __attribute__((__pure__));
# 1423 "/usr/avr/include/avr/pgmspace.h" 3
extern char *strtok_P(char *__s, const char * __delim);
# 1443 "/usr/avr/include/avr/pgmspace.h" 3
extern char *strtok_rP(char *__s, const char * __delim, char **__last);
# 1456 "/usr/avr/include/avr/pgmspace.h" 3
extern size_t strlen_PF(uint_farptr_t src) __attribute__((__const__));
# 1472 "/usr/avr/include/avr/pgmspace.h" 3
extern size_t strnlen_PF(uint_farptr_t src, size_t len) __attribute__((__const__));
# 1487 "/usr/avr/include/avr/pgmspace.h" 3
extern void *memcpy_PF(void *dest, uint_farptr_t src, size_t len);
# 1502 "/usr/avr/include/avr/pgmspace.h" 3
extern char *strcpy_PF(char *dest, uint_farptr_t src);
# 1522 "/usr/avr/include/avr/pgmspace.h" 3
extern char *strncpy_PF(char *dest, uint_farptr_t src, size_t len);
# 1538 "/usr/avr/include/avr/pgmspace.h" 3
extern char *strcat_PF(char *dest, uint_farptr_t src);
# 1559 "/usr/avr/include/avr/pgmspace.h" 3
extern size_t strlcat_PF(char *dst, uint_farptr_t src, size_t siz);
# 1576 "/usr/avr/include/avr/pgmspace.h" 3
extern char *strncat_PF(char *dest, uint_farptr_t src, size_t len);
# 1592 "/usr/avr/include/avr/pgmspace.h" 3
extern int strcmp_PF(const char *s1, uint_farptr_t s2) __attribute__((__pure__));
# 1609 "/usr/avr/include/avr/pgmspace.h" 3
extern int strncmp_PF(const char *s1, uint_farptr_t s2, size_t n) __attribute__((__pure__));
# 1625 "/usr/avr/include/avr/pgmspace.h" 3
extern int strcasecmp_PF(const char *s1, uint_farptr_t s2) __attribute__((__pure__));
# 1643 "/usr/avr/include/avr/pgmspace.h" 3
extern int strncasecmp_PF(const char *s1, uint_farptr_t s2, size_t n) __attribute__((__pure__));
# 1659 "/usr/avr/include/avr/pgmspace.h" 3
extern char *strstr_PF(const char *s1, uint_farptr_t s2);
# 1671 "/usr/avr/include/avr/pgmspace.h" 3
extern size_t strlcpy_PF(char *dst, uint_farptr_t src, size_t siz);
# 1687 "/usr/avr/include/avr/pgmspace.h" 3
extern int memcmp_PF(const void *, uint_farptr_t, size_t) __attribute__((__pure__));
# 1706 "/usr/avr/include/avr/pgmspace.h" 3
extern size_t __strlen_P(const char *) __attribute__((__const__));
__attribute__((__always_inline__)) static __inline__ size_t strlen_P(const char * s);
static __inline__ size_t strlen_P(const char *s) {
  return __builtin_constant_p(__builtin_strlen(s))
     ? __builtin_strlen(s) : __strlen_P(s);
}
# 8 "qrng.c" 2


# 1 "./include/mf_type.h" 1
# 14 "./include/mf_type.h"

# 14 "./include/mf_type.h"
typedef unsigned char u08 ;
typedef signed char s08 ;
typedef unsigned short u16 ;
typedef signed short s16 ;
typedef unsigned long u32 ;
typedef signed long s32 ;
typedef unsigned long long u64 ;
typedef signed long long s64 ;
# 11 "qrng.c" 2

typedef struct rega_t
{
  u08 b1 : 1 ; u08 b2 : 1 ;
  u08 b3 : 1 ; u08 b4 : 1 ;
  u08 b5 : 1 ; u08 b6 : 1 ;
  u08 b7 : 1 ; u08 b8 : 1 ;
} B ;

enum { ON , OFF } ;

_Static_assert ( 1 == sizeof ( B ) , "B is not the same size as its corresponding register." ) ;





static volatile u08 over ;


# 30 "qrng.c" 3
void __vector_13 (void) __attribute__ ((signal,used, externally_visible)) ; void __vector_13 (void)

# 31 "qrng.c"
{
  static u16 pwm ;
  static u08 dir ;

  switch ( dir )
  {
    case ON :
      if ( ++ pwm == 1 ) dir = OFF ;
    break ;
    case OFF :
      if ( -- pwm == 0 ) dir = ON ;
    break ;
  }
  
# 44 "qrng.c" 3
 (*(volatile uint16_t *)(0x88)) 
# 44 "qrng.c"
       = pwm ;
}

int
main ( void )
{
  *( ( B * ) 
# 50 "qrng.c" 3
 ((uint16_t) &(
# 50 "qrng.c"
 ( 
# 50 "qrng.c" 3
 (*(volatile uint8_t *)((0x04) + 0x20)) 
# 50 "qrng.c"
 )
# 50 "qrng.c" 3
 )) 
# 50 "qrng.c"
 ) = ( B ) { ON } ;
  *( ( B * ) 
# 51 "qrng.c" 3
 ((uint16_t) &(
# 51 "qrng.c"
 ( 
# 51 "qrng.c" 3
 (*(volatile uint8_t *)((0x03) + 0x20)) 
# 51 "qrng.c"
 )
# 51 "qrng.c" 3
 )) 
# 51 "qrng.c"
 ) = ( B ) { ON } ;

  
# 53 "qrng.c" 3
 (*(volatile uint8_t *)(0x81)) 
# 53 "qrng.c"
        = 
# 53 "qrng.c" 3
          (1 << (4)) 
# 53 "qrng.c"
                        | 
# 53 "qrng.c" 3
                          (1 << (0)) 
# 53 "qrng.c"
                                       ;
  
# 54 "qrng.c" 3
 (*(volatile uint8_t *)(0x80)) 
# 54 "qrng.c"
        = 0 ;
  
# 55 "qrng.c" 3
 (*(volatile uint8_t *)(0x6F)) 
# 55 "qrng.c"
        = 
# 55 "qrng.c" 3
          (1 << (0)) 
# 55 "qrng.c"
                        ;

  
# 57 "qrng.c" 3
 __asm__ __volatile__ ("sei" ::: "memory") 
# 57 "qrng.c"
          ;

  for (;;) 
# 59 "qrng.c" 3
          do { do { (*(volatile uint8_t *)((0x33) + 0x20)) |= (uint8_t)(1 << (0)); } while(0); do { __asm__ __volatile__ ( "sleep" "\n\t" :: ); } while(0); do { (*(volatile uint8_t *)((0x33) + 0x20)) &= (uint8_t)(~(1 << (0))); } while(0); } while (0) 
# 59 "qrng.c"
                          ;

  return 0 ;
}
