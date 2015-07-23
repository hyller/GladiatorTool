#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "cii\cii-20\include\str.h"
#include "semver.h"

#define FMT_STR_DEFINE      "#define  VERSION  \"%s\""
#define FMT_STR_SIMPLE      "%d.%d.%d"
#define INITIAL_VERSION_STR "0.1.0"
#define BUF_SIZE            128

static BOOL SemVer_IsValid( int len, int lpos, int rpos )
{
  if ( ( lpos == 0 ) || ( rpos == 0 ) )
  {
    return( FALSE );
  }

  if ( ( lpos == 1 ) || ( rpos == len ) )
  {
    return( FALSE );
  }

  if ( ( lpos == rpos ) || ( ( lpos + 1 ) == rpos ) )
  {
    return( FALSE );
  }

  return( TRUE );
}

int SemVer_ConvertFromStr( tSemverVersion* ver, char* str )
{
  int  lpos;
  int  rpos;
  int  len;
  char strtemp[ BUF_SIZE ] = { 0 };

  strcpy( strtemp, str );
  len = (int)strlen( strtemp );

  lpos = Str_chr( strtemp, 1, len, '.' );
  rpos = Str_rchr( strtemp, 1, len, '.' );
  if ( SemVer_IsValid( len, lpos, rpos ) )
  {
    strtemp[ lpos - 1 ] = 0;
    strtemp[ rpos - 1 ] = 0;
    ver->major          = atoi( &strtemp[ 0 ] );
    ver->minor          = atoi( &strtemp[ lpos ] );
    ver->patch          = atoi( &strtemp[ rpos ] );

    return( 0 );
  }
  else
  {
    ver->major = 0;
    ver->minor = 1;
    ver->patch = 0;
    return( 1 );
  }
}

int SemVer_ConvertToStr( tSemverVersion* ver, char* str )
{
  sprintf( str, (char*)FMT_STR_SIMPLE, ver->major, ver->minor, (int)ver->patch );
  return( 0 );
}

int SemVer_ConvertFromDefineStr( tSemverVersion* ver, char* defstr )
{
  char verstr[ 128 ];

  sscanf( defstr, FMT_STR_DEFINE, verstr );

  SemVer_ConvertFromStr( ver, verstr );

  return( 0 );
}

int SemVer_ConvertToDefineStr( tSemverVersion* ver, char* defstr )
{
  char verstr[ BUF_SIZE ];

  SemVer_ConvertToStr( ver, verstr );

  sprintf( defstr, FMT_STR_DEFINE, verstr );

  return( 0 );
}

int SemVer_IncreaseMajor( tSemverVersion* ver, int amount )
{
  ver->major = ver->major + amount;
  ver->minor = 0;
  ver->patch = 0;

  return( 0 );
}

int SemVer_IncreaseMinor( tSemverVersion* ver, int amount )
{
  ver->minor = ver->minor + amount;
  ver->patch = 0;

  return( 0 );
}

int SemVer_IncreasePatch( tSemverVersion* ver, int amount )
{
  ver->patch = ver->patch + amount;

  return( 0 );
}