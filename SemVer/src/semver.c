#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "semver.h"

#define FMT_STR_SIMPLE      "%d.%d.%d"
#define INITIAL_VERSION_STR "0.1.0"

int SemVer_ConvertFromStr( tSemverVersion* ver, char* str )
{
  int nums[ 3 ];

  sscanf( str, FMT_STR_SIMPLE, &nums[ 0 ], &nums[ 1 ], &nums[ 2 ] );

  ver->major = nums[ 0 ];
  ver->minor = nums[ 1 ];
  ver->patch = nums[ 2 ];

  return( 0 );
}

int SemVer_ConvertToStr( tSemverVersion* ver, char* str )
{
  sprintf( str, (char*)FMT_STR_SIMPLE, ver->major, ver->minor, (int)ver->patch );
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