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
#include "setting.h"


#define  BUF_SIZE        128


void PrintVersion( void )
{
  printf( "\n");
  printf( "semver increases version number in a file V%s\n", VERSION );
  printf( "\n");
}

void PrintUsage( void )
{
  printf( "\n");
  printf( "Usage: semver [option] [FILE]\n");
  printf( "\n");
  printf( "Options:\n");
  printf( "-x,  Change major version number.\n");
  printf( "-y,  Change minor version number.\n");
  printf( "-z,  Change patch version number.\n");
  printf( "-v,  Print program version.\n");
  printf( "-h,  Print this help screen.\n");
  printf( "-s,  Process simple version string.\n");
  printf( "-a,  Append version string to a file name.\n");  
  printf( "\n");
}



void GetVersion( tSetting* as, tSemverVersion* vd )
{
  char filebuf[ BUF_SIZE ] = {0};

  Utils_ReadFile( as->filename, (char*)filebuf, BUF_SIZE );

  SemVer_ConvertFromDefineStr( vd, filebuf );
  
  printf( "Read version: %s\n", (char*)filebuf );
}

int IncreaseVersion( tSetting* as, tSemverVersion* versionData )
{
  int index  = as->index;
  int amount = as->amount;

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

void OutputVersion( tSetting* as, tSemverVersion* vd )
{
  char  filebuf[ BUF_SIZE ] = {0};

  SemVer_ConvertToDefineStr(vd, filebuf);
  
  Utils_WriteFile( (char*)as->filename, (char*)filebuf, (int)strlen( filebuf ) );

  printf( "New  version: %s\n", (char*)filebuf );
}

void AppendToFile( tSetting* as, tSemverVersion* vd )
{
  char  verstr[ BUF_SIZE ] = {0};
  char  filename[ BUF_SIZE ] = {0};

  SemVer_ConvertToStr(vd, verstr);
  
  ChangFileName(as->appendarg,(char*)verstr,filename );  

  Utils_CopyFile( as->appendarg, (char*)filename );
  
  printf( "New  file   : %s\n", (char*)filename );
}

int main( int argc, char** argv )
{
  tSetting as;
  tSemverVersion  vd;

  Setting_Init(&as);  
  Setting_Parse( &as, argc, argv);

  if(as.help == 1 || as.error == 1)
  {
    PrintUsage();
  }
  else  if(as.version == 1)
  {
    PrintVersion();
  }
  else  if(as.append == 1)
  {
    GetVersion( &as, &vd );
	  AppendToFile( &as, &vd );
  }
  else
  {
    GetVersion( &as, &vd );
    IncreaseVersion( &as, &vd );
    OutputVersion( &as, &vd );
  }

  return( 1 );
}