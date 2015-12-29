#include "stdio.h"
#include "string.h"
#include "version.h"

int main( int argc, char* argv[] )
{
  char          str[ 3 ] = { 0 };
  unsigned char hex      = 0;
  unsigned char sum      = 0;
  unsigned int  in_len   = 0;
  unsigned int  i;

  
  printf( "\ndigitsum - sum all input words, version %s\n\n", VERSION );

  if ( argc == 1 )
  {
    printf( "Usage: digitsum hex_string\n"
            "e.g. digitsum 201035\n");
  }
  else
  {  
    printf( "Input(0x): " );
    in_len = strlen( argv[ 1 ] ) / 2;
    for ( i = 0; i < in_len; i++ )
    {
      str[ 0 ] = argv[ 1 ][ i * 2 ];
      str[ 1 ] = argv[ 1 ][ i * 2 + 1 ];
      sscanf( str, "%x", &hex );
      sum += hex;
      printf( "%02X ", hex );
    }

    printf( "\nSum  (0x): %02X\n", sum );
  }
}