#include "stdio.h"
#include "string.h"
#include "ascii.h"

#define VERSION "0.0.5"

int (* FormatOutput)( const char* format, ... ) = printf;

const char* ascii_table[ 32 ] = {
  "NUL ^@  Null character",
  "SOH ^A  Start of Header",
  "STX ^B  Start of Text",
  "ETX ^C  End of Text",
  "EOT ^D  End of Transmission",
  "ENQ ^E  Enquiry",
  "ACK ^F  Acknowledgment",
  "BEL ^G  Bell",
  "BS  ^H  Backspace[d][e]",
  "HT  ^I  Horizontal Tab[f]",
  "LF  ^J  Line feed",
  "VT  ^K  Vertical Tab",
  "FF  ^L  Form feed",
  "CR  ^M  Carriage return[g]",
  "SO  ^N  Shift Out",
  "SI  ^O  Shift In",
  "DLE ^P  Data Link Escape",
  "DC1 ^Q  Device Control 1 (oft. XON)",
  "DC2 ^R  Device Control 2",
  "DC3 ^S  Device Control 3 (oft. XOFF)",
  "DC4 ^T  Device Control 4",
  "NAK ^U  Negative Acknowledgment",
  "SYN ^V  Synchronous idle",
  "ETB ^W  End of Transmission Block",
  "CAN ^X  Cancel",
  "EM  ^Y  End of Medium",
  "SUB ^Z  Substitute",
  "ESC ^[  [h] Escape[i]",
  "FS  ^\\  File Separator",
  "GS  ^]  Group Separator",
  "RS  ^^[j] Record Separator",
  "US  ^_  Unit Separator"
};

const char* ascii_table_127 = "DEL ^? Delete";

void print_header( void )
{
  FormatOutput( "Hex\tDec\tCode\n" );
  FormatOutput( "-------------------------------------------------------------------------------\n" );
}

int parser_parameter( int argc, char* argv[], int* index )
{
  if( argc == 0 )
  {
    return( RET_ERROR );
  }

  if( 0 == strcmp( "-a", argv[ 0 ] ) )
  {
    return( RET_PRINT_ALL );
  }

  if( 0 == strcmp( "help", argv[ 0 ] ) )
  {
    return( RET_HELP );
  }

  if( 0 == strcmp( "?", argv[ 0 ] ) )
  {
    return( RET_HELP );
  }

  if( 0 == strcmp( "-v", argv[ 0 ] ) )
  {
    return( RET_VERSION );
  }

  if( ( 0 == strcmp( "-c", argv[ 0 ] ) ) && ( argc == 2 ) )
  {
    *index = argv[ 1 ][ 0 ];
    return( RET_SUCCESS );
  }

  if( ( 0 == strcmp( "-d", argv[ 0 ] ) ) && ( argc == 2 ) )
  {
    if( 0 != sscanf( &argv[ 1 ][ 0 ], "%d", (unsigned int*)index ) )
      return( RET_SUCCESS );
  }

  if( ( 0 == strcmp( "-h", argv[ 0 ] ) ) && ( argc == 2 ) )
  {
    if( 0 != sscanf( &argv[ 1 ][ 0 ], "%x", (unsigned int*)index ) )
      return( RET_SUCCESS );
  }

  return( RET_ERROR );
}

void print_ascii_by_index( int index )
{
  if( index < 32 )
  {
    FormatOutput( "%02X\t%03d\t%s\n", index, index, ascii_table[ index ] );
  }
  else
  if( index < 127 )
  {
    FormatOutput( "%02X\t%03d\t%c\n", index, index, index );
  }
  else
  if( index == 127 )
  {
    FormatOutput( "%02X\t%03d\t%s\n", index, index, ascii_table_127 );
  }
  else
  {
    FormatOutput( "%02X\t%03d\t%s\n", index, index, "NA" );
  }
}

void print_ascii_by_index_with_header( int index )
{
  print_header( );
  return( print_ascii_by_index( index ) );
}

void print_ascii_all_with_header( void )
{
  int index;

  print_header( );

  for( index = 0; index < 128; index++ )
  {
    print_ascii_by_index( index );
  }
}

void print_help( void )
{
  FormatOutput( "Usage: GASCII [options] [code | index] \n\n"
                "Options:\n"
                "  -?,        Show this help message\n"
                "  -v,        Show version information\n"
                "  -a,        Show whole ASCII table\n"
                "  -c,        Query an ASCII table row by code\n"
                "  -d,        Query an ASCII table row by decimal index\n"
                "  -h,        Query an ASCII table row by hexadecimal index\n" );
}

void print_version( void )
{
  FormatOutput( "\nGASCII is a utility to query ASCII table, v%s, "
                "by Haile-Hyller Jiang\n\n", VERSION );
}

int gascii( int argc, char* argv[] )
{
  int index = 0;
  int ret   = 0;

  ret = parser_parameter( argc, argv, &index );

  switch( ret )
  {
    case RET_SUCCESS:
      print_ascii_by_index_with_header( index );
      break;

    case RET_ERROR:
      print_help( );
      break;

    case RET_PRINT_ALL:
      print_ascii_all_with_header( );
      break;

    case RET_HELP:
      print_help( );
      break;

    case RET_VERSION:
      print_version( );
      break;

    default:
      print_ascii_all_with_header( );
      break;
  }

  return( ret );
}
