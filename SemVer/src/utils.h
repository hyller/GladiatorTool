int file_exists( char* filename );

int file_read( char* filename,
               char* buf,
               int   size );
void file_write( char* filename,
                 char* data );

int read_from_stdin( char* buf );

int str_is_string( char* input );

int str_is_integer( char* input );

int strings_are_equal( char* s1,
                       char* s2 );

void zero_fill( void* obj,
                int   size );