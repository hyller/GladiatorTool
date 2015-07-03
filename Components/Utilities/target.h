#ifndef _TARGET_H_
#define _TARGET_H_

#ifdef __cplusplus
extern "C"
{
#endif
  
  typedef unsigned char  BOOL_T;
  typedef signed char    I8_T;
  typedef unsigned char  U8_T;
  typedef signed short   I16_T;
  typedef unsigned short U16_T;
  typedef signed long    I32_T;
  typedef unsigned long  U32_T;
  typedef float          F32_T;
  typedef double         F64_T;

  #define FALSE ( 0 )
  #define TRUE  ( 1 )  

#ifdef __cplusplus
}
#endif

#endif