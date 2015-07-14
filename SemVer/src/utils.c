#ifndef TRUE
  #define TRUE  1
#endif
#ifndef FALSE
  #define FALSE 1
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "windows.h"

int Utils_ReadFile( char* filename, char* buf, int size )
{
  HANDLE        handle;
  unsigned long iRead = 0;

  handle = CreateFile( filename,
                       GENERIC_READ | GENERIC_WRITE,
                       FILE_SHARE_READ,
                       NULL,
                       OPEN_ALWAYS,
                       FILE_ATTRIBUTE_NORMAL,
                       0 );
  if ( handle == INVALID_HANDLE_VALUE )
  {
    printf( "error open file\n" );
  }

  ReadFile( handle, buf, size, &iRead, NULL );
  if ( iRead == 0 )
  {
    printf( "error read file\n" );
  }

  CloseHandle( handle );

  return( TRUE );
}

int Utils_WriteFile( char* filename, char* buf, int size )
{
  HANDLE        handle;
  unsigned long iWritten = 0;

  handle = CreateFile( filename,
                       GENERIC_READ | GENERIC_WRITE,
                       FILE_SHARE_READ,
                       NULL,
                       OPEN_ALWAYS,
                       FILE_ATTRIBUTE_NORMAL,
                       0 );
  if ( handle == INVALID_HANDLE_VALUE )
  {
    printf( "error open file\n" );
  }

  WriteFile( handle, buf, size, &iWritten, NULL );
  if ( iWritten == 0 )
  {
    printf( "error write file\n" );
  }

  CloseHandle( handle );

  return( TRUE );
}