#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "cii/cii-20/include/str.h"
#include "semver.h"

#define FMT_STR_SIMPLE      "%d.%d.%d"
#define FMT_STR_SIMPLE2     "%02d.%02d.%02d"
#define FMT_STR_SIMPLE3     "%03d.%03d.%03d"
#define INITIAL_VERSION_STR "0.1.0"
#define BUF_SIZE            128

static BOOL SemVer_IsValidPos( int len, int lpos, int rpos )
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

int SemVer_Init( tSemverVersion* me )
{
  me->major = 0;
  me->minor = 1;
  me->patch = 0;

  return( 0 );
}

int SemVer_ConvertFromStr( tSemverVersion* me, char* str )
{
  int  lpos;
  int  rpos;
  int  len;
  char strtemp[ BUF_SIZE ] = { 0 };

  strcpy( strtemp, str );
  len = (int)strlen( strtemp );

  lpos = Str_chr( strtemp, 1, len, '.' );
  rpos = Str_rchr( strtemp, 1, len, '.' );
  if ( SemVer_IsValidPos( len, lpos, rpos ) )
  {
    strtemp[ lpos - 1 ] = 0;
    strtemp[ rpos - 1 ] = 0;
    me->major           = atoi( &strtemp[ 0 ] );
    me->minor           = atoi( &strtemp[ lpos ] );
    me->patch           = atoi( &strtemp[ rpos ] );

    return( 0 );
  }
  else
  {
    me->major = 0;
    me->minor = 1;
    me->patch = 0;
    return( 1 );
  }
}

int SemVer_ConvertToStr( tSemverVersion* me, char* str, int length )
{
  if( length == 2 )
  {
    sprintf( str, (char*)FMT_STR_SIMPLE2, me->major, me->minor, (int)me->patch );
  }
  else if( length == 3 )
  {
    sprintf( str, (char*)FMT_STR_SIMPLE3, me->major, me->minor, (int)me->patch );
  }
  else
  {  
    sprintf( str, (char*)FMT_STR_SIMPLE, me->major, me->minor, (int)me->patch );
  }
  return( 0 );
}

int SemVer_IncreaseMajor( tSemverVersion* me )
{
  me->major = me->major + 1;
  me->minor = 0;
  me->patch = 0;

  return( 0 );
}

int SemVer_IncreaseMinor( tSemverVersion* me )
{
  me->minor = me->minor + 1;
  me->patch = 0;

  return( 0 );
}

int SemVer_IncreasePatch( tSemverVersion* me )
{
  me->patch = me->patch + 1;

  return( 0 );
}