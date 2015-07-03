#include "stdio.h"
#include "string.h"
#include "math.h"

#define VERSION "0.02"

int main( int argc, char* argv[] )
{
  float db;
  float pr;

  printf( "\ndb2pr - converts decibel to power ration and vice versa, version %s\n\n", VERSION );

  if ( argc == 1 )
  {
    printf( "Usage: db2pr [db|pr]\n"
            "Include r as the prefix of the number to specify a power ratio value.\n"
            "e.g. To translate 5 decibel to power ratio: db2pr 20\n"
            "e.g. To translate 100 power ratio to decibel: db2pr r100\n" );
  }
  else
  if ( argv[ 1 ][ 0 ] == 'r' )
  {
    sscanf( &argv[ 1 ][ 1 ], "%f", &pr );
    db = 10 * log10( pr );
    printf( "%f pr = %f db\n", pr, db );
  }
  else
  {
    sscanf( argv[ 1 ], "%f", &db );
    pr = pow( 10, db / 10 );
    printf( "%f db = %f pr\n", db, pr );
  }
}