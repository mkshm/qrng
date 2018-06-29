
#include <float.h>
#include <math.h>

#include <tst-common.h>

int
test ( int fd )
{
  double x , y , z ;
  double mag_sqr ;
  double i = 0.0 , n = 0.0 ;

  double * buff ;
  ssize_t cnt , tmp ;

  if ( NULL == ( buff = malloc ( 128 * (3*sizeof(double)) ) ) )
  {
    argp_verbose ( "malloc" , "failed to allocate buffer" , 0.0 ) ;
    return EXIT_FAILURE ;
  }

  while ( 0 < ( cnt = read ( fd , buff , 128 * (3*sizeof(double) ) ) ) )
  {
    for ( tmp = 0 ; tmp < ( cnt / ( 3 * sizeof ( double ) ) ) ; tmp += 1 )
    {
      if ( FP_NORMAL != fpclassify ( buff [ tmp * 3 + 0 ] ) ) continue ;
      if ( FP_NORMAL != fpclassify ( buff [ tmp * 3 + 1 ] ) ) continue ;
      if ( FP_NORMAL != fpclassify ( buff [ tmp * 3 + 2 ] ) ) continue ;

      i += 1.0 ;

      x = 2 * buff [ tmp * 3 + 0 ] / sqrt ( DBL_MAX ) ;
      y = 2 * buff [ tmp * 3 + 1 ] / sqrt ( DBL_MAX ) ;
      z = 2 * buff [ tmp * 3 + 2 ] / sqrt ( DBL_MAX ) ;

      mag_sqr  = x * x ;
      mag_sqr += y * y ;
      mag_sqr += z * z ;

      if ( 1 >= mag_sqr ) n += 1.0 ;
    }
  }

  argp_verbose ( "[tst-monte-3d]" , "The total inside  is:" , n ) ;
  argp_verbose ( "[tst-monte-3d]" , "The total         is:" , i ) ;
  argp_verbose ( "[tst-monte-3d]" , "The volume is:" , 8 * ( n / i ) ) ;

  if ( NULL != buff ) free ( buff ) ;

  return 1 ;
}
