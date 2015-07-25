#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

static const size_t buffer_size           = 1024;
static char         buffer[ buffer_size ] = { 0 };
static int          buffer_offset = 0;
static int          buffer_used   = 0;

void FormatOutputSpy_Clear( void )
{
  buffer_offset = 0;
  buffer_used   = 0;
  buffer[ 0 ]   = 0;
}

int FormatOutputSpy( const char* format, ... )
{
  int     written_size;
  va_list arguments;
  va_start( arguments, format );
  written_size
                 = vsnprintf( buffer + buffer_offset, buffer_size - buffer_used, format,
                 arguments );
  buffer_offset += written_size;
  buffer_used   += written_size;
  va_end( arguments );
  return( 1 );
}

const char* FormatOutputSpy_GetOutput( void )
{
  return( buffer );
}
