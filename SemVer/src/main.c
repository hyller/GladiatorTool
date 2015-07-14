#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stddef.h>
#include <ctype.h>
#include <unistd.h>

#include "utils.h"
#include "version.h"
#include "semver.h"

#define FMT_STR_DEFINE   "#define  VERSION  \"%s\""
#define  BUF_SIZE        128

typedef struct
{
  int  verbose;
  int  quiet;
  int  length;
  int  output_cdef;
  int  indexToIncrement;
  int  incrementBy;
  char filename[ BUF_SIZE ];
} tSemverSettings;

int SemVer_IncreaseVersion( tSemverSettings* as, tSemverVersion* versionData )
{
  int index  = as->indexToIncrement;
  int amount = as->incrementBy;

  switch ( index )
  {
    case 0:
      SemVer_IncreaseMajor(versionData, amount);
      return( 0 );

    case 1:
      SemVer_IncreaseMinor(versionData, amount);
      return( 0 );

    case 2:
      SemVer_IncreasePatch(versionData, amount);
      return( 0 );
    default:
      return( 1 );
      break;    
  }
}

void SemVer_Usage( int argc, char** argv )
{
  printf( "SemVer_Usage: %s v%s [version(x.y.z)] [index-to-increment] [increment-by]\n",
          argv[ 0 ], VERSION );
  printf(
    "If '-' is passed as the version number, the version will be read from stdin.\n" );

  exit( EXIT_FAILURE );
}

int SemVer_ParseStdin( int argc, char** argv, tSemverSettings* as )
{
  int c;

  memset( as, 0, sizeof( tSemverSettings ) );
  as->indexToIncrement = 2;
  as->incrementBy      = 1;
  as->output_cdef = 1;

  opterr = 0;
  while ( ( c = getopt( argc, argv, "mipdvqh" ) ) != -1 )
    switch ( c )
    {
      case 'm':
        as->indexToIncrement = 0;
        as->incrementBy      = 1;
        break;

      case 'i':
        as->indexToIncrement = 1;
        as->incrementBy      = 1;
        break;

      case 'p':
        as->indexToIncrement = 2;
        as->incrementBy      = 1;
        break;

      case 'd':
        as->output_cdef = 1;
        break;

      case 'v':
        as->verbose = 1;
        break;

      case 'q':
        as->quiet = 1;
        break;

      case 'h':
        SemVer_Usage( argc, argv );
        break;

      case '?':
        SemVer_Usage( argc, argv );

      default:
        break;
    }

  strcpy( (char*)as->filename, argv[ optind ] );

  return( 0 );
}

void SemVer_GetVersion( tSemverSettings* as, tSemverVersion* vd )
{
  char filebuf[ BUF_SIZE ];
  char verstr[ BUF_SIZE ];

  Utils_ReadFile( as->filename, (char*)filebuf, BUF_SIZE );

  if ( as->output_cdef == 1 )
  {
    sscanf( filebuf, FMT_STR_DEFINE, verstr );
  }
  else
  {
    memcpy( verstr, filebuf, BUF_SIZE );
  }

  SemVer_ConvertFromStr( vd, verstr );
}

void SemVer_OutputVersion( tSemverSettings* as, tSemverVersion* vd )
{
  char  filebuf[ BUF_SIZE ];
  char verstr[ BUF_SIZE ];

  SemVer_ConvertToStr(vd, verstr);
  
  if ( as->output_cdef == 1 )
  {
    sprintf( filebuf, FMT_STR_DEFINE, verstr );
  }
  else
  {
    memcpy( filebuf, verstr, BUF_SIZE );
  }
  
  printf( "%s", (char*)filebuf );

  Utils_WriteFile( (char*)as->filename, (char*)filebuf, strlen( filebuf ) );
}

int main( int argc, char** argv )
{
  tSemverSettings as;
  tSemverVersion  vd;

  SemVer_ParseStdin( argc, argv, &as );

  SemVer_GetVersion( &as, &vd );

  SemVer_IncreaseVersion( &as, &vd );

  SemVer_OutputVersion( &as, &vd );

  return( 0 );
}