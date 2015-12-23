#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

#include "cii/cii-20/include/str.h"
#include "fileproxy.h"
#include "version.h"

#define FMT_DEFINE_PREFIX "#define  VERSION"
#define FMT_STR_DEFINE    FMT_DEFINE_PREFIX "  \"%s\""
#define FILE_BUF_SIZE     1024

static int FileProxy_ReadFile( char* filename, char* buf, int size )
{
  FILE* ifp;

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

static char* FileProxy_GetDay( void )
{
  static char DayBuffer[80];
  size_t len;
  struct tm* tmt;
  time_t timet;
  
  timet = time(0);
  tmt = gmtime(&timet);
  len = strftime(DayBuffer, 80, "%Y-%m-%d", tmt);

  return DayBuffer;
}

int FileProxy_IsFileExist( char* filename )
{
  return( access( filename, 0 ) );
}

int FileProxy_ReadVersion( char* filename, char* verstr )
{
  char buf[ FILE_BUF_SIZE ] = { 0 };
  int  lpos;
  int  rpos;
  int  len;

  FileProxy_ReadFile( filename, buf, FILE_BUF_SIZE );

  len = (int)strlen( buf ) + 1;

  lpos = Str_find( buf, 1, len, FMT_DEFINE_PREFIX );
  lpos = Str_chr( buf, lpos + 1, len, '"' );
  rpos = Str_chr( buf, lpos + 1, len, '"' );

  memcpy( verstr, &buf[ lpos ], (size_t)( rpos - lpos - 1 ) );

  return( 0 );
}

int FileProxy_WriteVersion( char* filename, char* verstr )
{
  char buf[ FILE_BUF_SIZE ] = { 0 };
  int  len                  = 0;
  char *timestr = 0;
  
  timestr = FileProxy_GetDay();

  len += sprintf( &buf[ len ], "#ifndef _VERSION_H_\n" );
  len += sprintf( &buf[ len ], "#define _VERSION_H_\n" );
  len += sprintf( &buf[ len ], "\n" );
  len += sprintf( &buf[ len ], FMT_STR_DEFINE "\n", verstr );
  len += sprintf( &buf[ len ], "#define  MODIFY_DATE \"%s\"\n", timestr );
  len += sprintf( &buf[ len ], "\n" );
  len += sprintf( &buf[ len ], "#endif\n" );

  FileProxy_WriteFile( filename, buf, (int)strlen( buf ) );

  return( 0 );
}

int FileProxy_ReadVersionSimple( char* filename, char* verstr )
{
  char buf[ FILE_BUF_SIZE ] = { 0 };
  int  len;

  FileProxy_ReadFile( filename, buf, FILE_BUF_SIZE );

  for(len = 0; len < FILE_BUF_SIZE; len++)
  {
	if( buf[len] == ' ' || buf[len] == 0 )
	{
	  buf[len] = 0;  
	  break;
    }
  }

  strcpy( verstr, buf);

  return( 0 );
}

int FileProxy_WriteVersionSimple( char* filename, char* verstr )
{
  char buf[ FILE_BUF_SIZE ] = { 0 };  
  char *timestr = 0;
  
  timestr = FileProxy_GetDay();

  sprintf( buf, "%s    %s", verstr, timestr );

  FileProxy_WriteFile( filename, buf, (int)strlen( buf ) );

  return( 0 );
}

int FileProxy_CopyFile( char* filename, char* newname )
{
  CopyFile( filename, newname, 0 );

  return( 0 );
}