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
#include <windows.h>

#include "cii/cii-20/include/str.h"
#include "fileproxy.h"

#define FMT_STR_DEFINE "#define  VERSION  \"%s\""

int FileProxy_ReadVersion( char* filename, char* verstr, int size )
{
  HANDLE        handle;
  unsigned long iRead      = 0;
  char          buf[ 128 ] = { 0 };
  int           lpos;
  int           rpos;
  int           len;

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

  ReadFile( handle, buf, (unsigned int)size, &iRead, NULL );
  if ( iRead == 0 )
  {
    printf( "error read file\n" );
  }

  CloseHandle( handle );

  len  = (int)strlen( buf ) + 1;
  lpos = Str_chr( buf, 1, len, '"' );
  rpos = Str_rchr( buf, 1, len, '"' );

  memcpy( verstr, &buf[ lpos ], (size_t)( rpos - lpos - 1 ) );

  return( TRUE );
}

int FileProxy_WriteVersion( char* filename, char* verstr, int size )
{
  HANDLE        handle;
  unsigned long iWritten = 0;

  char buf[ 128 ] = { 0 };
  sprintf( buf, FMT_STR_DEFINE, verstr );
  size = size;

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

  WriteFile( handle, buf, (unsigned int)strlen( buf ), &iWritten, NULL );
  if ( iWritten == 0 )
  {
    printf( "error write file\n" );
  }

  CloseHandle( handle );

  return( TRUE );
}

int FileProxy_CopyFile( char* filename, char* newname )
{
  CopyFile( filename, newname, FALSE );

  return( TRUE );
}