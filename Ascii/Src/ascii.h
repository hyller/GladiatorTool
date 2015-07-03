#ifndef _GASCII_H_
#define _GASCII_H_
#define  RET_SUCCESS   0
#define  RET_ERROR     1
#define  RET_PRINT_ALL 2
#define  RET_HELP      3
#define  RET_VERSION   4

extern int (* FormatOutput)( const char* format,
                             ... );

extern int parser_parameter( int   argc,
                             char* argv[],
                             int*  index );
extern void print_ascii_by_index( int index );
extern int gascii( int   argc,
                   char* argv[] );

#endif
