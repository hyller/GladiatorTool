#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stddef.h>
#include <ctype.h>
#include <unistd.h>

#include "setting.h"

void Setting_Init( tSetting* as )
{
  memset( as, 0, sizeof( tSetting ) );
}

int Setting_Parse( tSetting* as, int argc, char** argv )
{
  int c;

  if ( argc == 1 )
  {
    as->error = 1;
    return( 1 );
  }

  opterr = 0;
  while ( ( c = getopt( argc, argv, "xyzvhsa:i:" ) ) != -1 )
  {
    switch ( c )
    {
      case 'x':
        as->index = 2;
        break;

      case 'y':
        as->index = 1;
        break;

      case 'z':
        as->index = 0;
        break;

      case 's':
        as->simple = 1;
        break;

      case 'a':
        as->append    = 1;
        as->appendarg = optarg;
        break;

      case 'i':
        as->init    = 1;
        as->initarg = optarg;
        break;

      case 'v':
        as->version = 1;
        break;

      case 'q':
        as->quiet = 1;
        break;

      case 'h':
        as->help = 1;
        break;

      case '?':
        as->help = 1;
        return( 1 );

      default:
        as->error = 1;
        return( 1 );

        break;
    }
  }

  if ( optind < argc )
  {
    strcpy( (char*)as->filename, argv[ optind ] );
  }

  return( 0 );
}