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
#include <unistd.h>

#include "cii/cii-20/include/str.h"
#include "fileproxy.h"

#define FMT_STR_DEFINE "#define  VERSION  \"%s\""

static int FileProxy_ReadFile( char* filename, char* buf, int size )
{
  FILE* ifp;

  size = size;

  ifp = fopen( filename, "r+" );

  if ( ifp == NULL )
  {
    printf( "Can't open file\n" );
    return( 1 );
  }

  fread( buf, (size_t)size, 1, ifp );

  fclose( ifp );

  return( 0 );
}

static int FileProxy_WriteFile( char* filename, char* buf, int size )
{
  FILE* ifp;

  if ( ( ifp = fopen( filename, "w+" ) ) == NULL )
  {
    printf( "Cannot open file.\n" );
    return( 1 );
  }

  fwrite( buf, (size_t)size, 1, ifp );
  fclose( ifp );

  return( 0 );
}

int FileProxy_IsFileExist( char* filename )
{
  return( access( filename, 0 ) );
}

int FileProxy_ReadVersion( char* filename, char* verstr, int size )
{
  char  buf[ 128 ] = { 0 };
  int   lpos;
  int   rpos;
  int   len;

  size = size;

  FileProxy_ReadFile(filename,buf,128);

  len  = (int)strlen( buf ) + 1;
  lpos = Str_chr( buf, 1, len, '"' );
  rpos = Str_rchr( buf, 1, len, '"' );

  memcpy( verstr, &buf[ lpos ], (size_t)( rpos - lpos - 1 ) );

  return( 0 );
}



int FileProxy_WriteVersion( char* filename, char* verstr, int size )
{
  char  buf[ 128 ] = { 0 };
  size = size;

  sprintf( buf, FMT_STR_DEFINE, verstr );  

  FileProxy_WriteFile(filename, buf, (int)strlen(buf));

  return( 0 );
}

int FileProxy_CopyFile( char* filename, char* newname )
{
  CopyFile( filename, newname, FALSE );

  return( 0 );
}