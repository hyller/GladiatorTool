#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stddef.h>
#include <ctype.h>
#include <unistd.h>

#include "utils.h"
#include "version.h"

#define  BUF_SIZE  128

//set to 1 to increment major version when minor reached 100. i.e.:
//1.99.0 + 0.01.0 = 1.100.0 = 2.0.0
#define ON_MINOR_100_INCREMENT_MAJOR_FIELD 0

typedef struct version_numbers_s
{
  int major;
  int minor;
  int patch;
} version_numbers;

typedef struct application_settings_s
{
  int verbose;
  int quiet;
  int length;
  int output_cdef;
  int indexToIncrement;
  int incrementBy;
  char filename[ BUF_SIZE ];
} application_settings;

int increaseVersion( version_numbers* versionData, int index, int amount )
{
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

void usage( int argc, char** argv )
{
  printf( "Usage: %s v%s [version(x.y.z)] [index-to-increment] [increment-by]\n",
          argv[ 0 ], VERSION );
  printf(
    "If '-' is passed as the version number, the version will be read from stdin.\n" );
  exit( EXIT_FAILURE );
}

int process_flags( int argc, char** argv, application_settings* as )
{
  int   aflag  = 0;
  int   bflag  = 0;
  char* cvalue = NULL;
  int   index;
  int   c;

  opterr = 0;
  while ( ( c = getopt( argc, argv, "dvq:" ) ) != -1 )
    switch ( c )
    {
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
        usage( argc, argv );

        return( 1 );

      default:
        break;
    }

  switch ( argc )
  {
    case 1:
      usage( argc, argv );
      break;

    case 2:
      as->indexToIncrement = 2;
      as->incrementBy      = 1;
      break;

    case 3:
      as->indexToIncrement = 2;
      as->incrementBy      = atoi( argv[ 3 ] );
      break;

    case 4:
      as->indexToIncrement = atoi( argv[ 2 ] );
      as->incrementBy      = atoi( argv[ 3 ] );
      break;

    default:
      break;
  }

  strcpy( (char*)as->filename, argv[ 1 ] );

  return( 0 );
}

void output_new_version( application_settings* as,
                         version_numbers*      vd,
                         char*                 filenameStr )
{
  char vbuf[ BUF_SIZE ];
  char fmtstr[ BUF_SIZE ];
  char fmtstr2[ BUF_SIZE ];
  char filenameStr2[ BUF_SIZE ];

  sprintf( (char*)fmtstr, "%s", "%d.%d.%d\n" );
  sprintf( (char*)vbuf, (char*)fmtstr, (int)vd->major, (int)vd->minor, (int)vd->patch );
  printf( "%s", (char*)vbuf );
  file_write( (char*)filenameStr, (char*)vbuf );
  
  sprintf(filenameStr2,"%s%s",filenameStr,".h");
  sprintf( (char*)fmtstr2, "#define VERSION  %s", "\"%d.%d.%d\"\n" );
  sprintf( (char*)vbuf, (char*)fmtstr2, (int)vd->major, (int)vd->minor, (int)vd->patch );
  printf( "%s", (char*)vbuf );
  file_write( (char*)filenameStr, (char*)vbuf );
}

void get_vd( char* versionBuf, version_numbers* vd )
{
  const char s[ 2 ] = ".";
  char*      token;
  char*      str1 = versionBuf;
  int versionNumbers[ 3 ] = { 0, 0, 0 };

  /* walk through other tokens */
  int index = 0;

  /* get the first token */
  token = strtok( str1, s );
  while ( token != NULL )
  {
    versionNumbers[ index ] = atoi( token );
    token                   = strtok( NULL, s );
    index++;
  }

  vd->major = versionNumbers[0];
  vd->minor = versionNumbers[1];
  vd->patch = versionNumbers[2];
}

int main( int argc, char** argv )
{
  version_numbers vd;  
  char            versionBuf[ BUF_SIZE ];
  application_settings as;
  
  memset( &as, 0, sizeof( application_settings ) );
  process_flags( argc, argv, &as );

   
  file_read( as.filename, (char*)versionBuf, BUF_SIZE );

  get_vd( versionBuf, &vd );
  
  increaseVersion( &vd, as.indexToIncrement, as.incrementBy );
  output_new_version( &as, &vd, as.filename );

  return( 0 );
}