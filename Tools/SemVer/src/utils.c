#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cii/cii-20/include/str.h"
#include "utils.h"

void ChangFileName( char* oldname, char* append, char* newname )
{
  char prefix[ 128 ] = { 0 };
  char sufix[ 128 ]  = { 0 };
  int  pos;
  int  len;

  len = (int)strlen( oldname );
  pos = Str_chr( oldname, 1, len + 1, '.' );

  if ( pos != 0 )
  {
    memcpy( prefix, oldname, (unsigned int)pos - 1 );
    memcpy( sufix, &oldname[ pos ], (unsigned int)( (int)len - pos ) );

    sprintf( newname, "%s_%s.%s", prefix, (char*)append, sufix );
  }
  else
  {
    sprintf( newname, "%s_%s", oldname, (char*)append );
  }
}