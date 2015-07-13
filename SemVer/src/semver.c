#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stddef.h>
#include <ctype.h>
#include <unistd.h>

#include "utils.h"
#include "version.h"

#define FMT_STR_DEFINE                     "#define  VERSION  \"%s\""
#define FMT_STR_SIMPLE                     "%d.%d.%d"

#define  BUF_SIZE                          128

//set to 1 to increment major version when minor reached 100. i.e.:
//1.99.0 + 0.01.0 = 1.100.0 = 2.0.0
#define ON_MINOR_100_INCREMENT_MAJOR_FIELD 0

typedef struct
{
  int major;
  int minor;
  int patch;
} tSemverVersion;

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
      versionData->major = versionData->major + amount;
      versionData->minor = 0;
      versionData->patch = 0;
      return( 1 );

    case 1:
      versionData->minor = versionData->minor + amount;
      versionData->patch = 0;
      #ifdef ON_MINOR_100_INCREMENT_MAJOR_FIELD
        if ( versionData->minor >= 100 )
        {
          versionData->minor = 0;
          versionData->major = versionData->major + 1;
          return( 1 );
        }
      #endif
      return( 1 );

    case 2:
      versionData->patch = versionData->patch + amount;
      return( 1 );
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

void SemVer_ConvertVersionStrToDigit( char* versionBuf, tSemverVersion* vd )
{
  const char s[ 2 ] = ".";
  char*      token;
  char*      str1                = versionBuf;
  int        versionNumbers[ 3 ] = { 0, 0, 0 };

  int index = 0;

  token = strtok( str1, s );
  while ( token != NULL )
  {
    versionNumbers[ index ] = atoi( token );
    token                   = strtok( NULL, s );
    index++;
  }

  vd->major = versionNumbers[ 0 ];
  vd->minor = versionNumbers[ 1 ];
  vd->patch = versionNumbers[ 2 ];
}

void SemVer_GetVersion( tSemverSettings* as, tSemverVersion* vd )
{
  char filebuf[ BUF_SIZE ];
  char versionBuf[ BUF_SIZE ];

  Utils_ReadFile( as->filename, (char*)filebuf, BUF_SIZE );

  if ( as->output_cdef == 1 )
  {
    sscanf( filebuf, FMT_STR_DEFINE, versionBuf );
  }
  else
  {
    memcpy( versionBuf, filebuf, BUF_SIZE );
  }

  SemVer_ConvertVersionStrToDigit( versionBuf, vd );
}

void SemVer_OutputVersion( tSemverSettings* as, tSemverVersion* vd )
{
  char  vbuf[ BUF_SIZE ];
  char* fmtstr[ BUF_SIZE ];

  if ( as->output_cdef == 1 )
  {
    sprintf( fmtstr, FMT_STR_DEFINE, FMT_STR_SIMPLE );
  }
  else
  {
    sprintf( fmtstr, "%s", FMT_STR_SIMPLE );
  }

  sprintf( (char*)vbuf, (char*)fmtstr, (int)vd->major, (int)vd->minor, (int)vd->patch );

  printf( "%s", (char*)vbuf );

  Utils_WriteFile( (char*)as->filename, (char*)vbuf, strlen( vbuf ) );
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