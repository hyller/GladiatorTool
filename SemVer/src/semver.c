#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "cii\cii-20\include\str.h"
#include "semver.h"

#define FMT_STR_DEFINE   "#define  VERSION  \"%s\""
#define FMT_STR_SIMPLE      "%d.%d.%d"
#define INITIAL_VERSION_STR "0.1.0"
#define  BUF_SIZE        128

int SemVer_ConvertFromStr( tSemverVersion* ver, char* str )
{
  const char s[ 2 ] = ".";
  char*      token;
  int        nums[ 3 ] = { 0, 1, 0 };
  int        index = 0;
  int pos, rpos;
  int len = (int)strlen(str);
  
  pos = Str_chr(str, 1, len, '.');
  rpos = Str_rchr(str, 1, len, '.');
  if(pos == rpos || pos == 0 || rpos == len )
  {
    ver->major = nums[ 0 ];
    ver->minor = nums[ 1 ];
    ver->patch = nums[ 2 ];
    return 1;
  }

  token = strtok( str, s );
  while ( token != NULL )
  {
    nums[ index ] = atoi( token );
    token = strtok( NULL, s );
    index++;
  }

  ver->major = nums[ 0 ];
  ver->minor = nums[ 1 ];
  ver->patch = nums[ 2 ];
  
  return 0;
}


int SemVer_ConvertToStr( tSemverVersion* ver, char* str )
{
  sprintf( str, (char*)FMT_STR_SIMPLE, ver->major, ver->minor, (int)ver->patch );
  return( 0 );
}


int SemVer_ConvertFromDefineStr( tSemverVersion* ver, char* defstr )
{
  char verstr[128];
  
  sscanf( defstr, FMT_STR_DEFINE, verstr);

  SemVer_ConvertFromStr( ver, verstr );
  
  return 0;
}

int SemVer_ConvertToDefineStr( tSemverVersion* ver, char* defstr )
{
  char verstr[ BUF_SIZE ];

  SemVer_ConvertToStr(ver, verstr);
  
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