#include "TestAscii.h"
#include "ascii.h"
#include "FormatOutputSpy.h"
#include "string.h"

#define CPPUNIT_ASSERT_STR_EQUAL( expect, actual ) \
  CPPUNIT_ASSERT( 0 == strcmp( ( expect ), ( actual ) ) )

const char* expectedOutput;
const char* actualOutput;

char* test_argv[ 10 ] = { 0 };
int   test_argc  = 0;
int   test_index = 0;
int   test_ret   = 0;

void CTestGAscii::setUp( )
{
  FormatOutput = FormatOutputSpy;
  actualOutput = FormatOutputSpy_GetOutput( );
  FormatOutputSpy_Clear( );
}

void CTestGAscii::tearDown( )
{
}

void CTestGAscii::TestGAsciiPrintAsciiByindexNormal( )
{
  expectedOutput = "00\t000\tNUL ^@  Null character\n"
                   "1F\t031\tUS  ^_  Unit Separator\n"
                   "7E\t126\t~\n"
                   "7F\t127\tDEL ^? Delete\n";
  print_ascii_by_index( 0 );
  print_ascii_by_index( 31 );
  print_ascii_by_index( 126 );
  print_ascii_by_index( 127 );
  CPPUNIT_ASSERT_STR_EQUAL( expectedOutput, actualOutput );
}

void CTestGAscii::TestGAsciiPrintAsciiByindex128( )
{
  expectedOutput = "80\t128\tNA\n";
  print_ascii_by_index( 128 );
  CPPUNIT_ASSERT_STR_EQUAL( expectedOutput, actualOutput );
}

void CTestGAscii::TestGAsciiParserParameterAll( )
{
  test_argc      = 1;
  test_argv[ 0 ] = (char*)"-a";
  test_ret       = parser_parameter( test_argc, test_argv, &test_index );
  CPPUNIT_ASSERT_EQUAL( RET_PRINT_ALL, test_ret );
}

void CTestGAscii::TestGAsciiParserParameterHex( )
{
  test_argc      = 2;
  test_argv[ 0 ] = (char*)"-h";

  test_argv[ 1 ] = (char*)"0";
  test_ret       = parser_parameter( test_argc, test_argv, &test_index );
  CPPUNIT_ASSERT_EQUAL( RET_SUCCESS, test_ret );
  CPPUNIT_ASSERT_EQUAL( 0, test_index );

  test_argv[ 1 ] = (char*)"05";
  test_ret       = parser_parameter( test_argc, test_argv, &test_index );
  CPPUNIT_ASSERT_EQUAL( RET_SUCCESS, test_ret );
  CPPUNIT_ASSERT_EQUAL( 5, test_index );

  test_argv[ 1 ] = (char*)"A5";
  test_ret       = parser_parameter( test_argc, test_argv, &test_index );
  CPPUNIT_ASSERT_EQUAL( RET_SUCCESS, test_ret );
  CPPUNIT_ASSERT_EQUAL( test_index, 0xA5 );

  test_argv[ 1 ] = (char*)"7F";
  test_ret       = parser_parameter( test_argc, test_argv, &test_index );
  CPPUNIT_ASSERT_EQUAL( RET_SUCCESS, test_ret );
  CPPUNIT_ASSERT_EQUAL( 127, test_index );

  test_argv[ 1 ] = (char*)"80";
  test_ret       = parser_parameter( test_argc, test_argv, &test_index );
  CPPUNIT_ASSERT_EQUAL( RET_SUCCESS, test_ret );
  CPPUNIT_ASSERT_EQUAL( 128, test_index );
}

void CTestGAscii::TestGAsciiParserParameterDec( )
{
  test_argc      = 2;
  test_argv[ 0 ] = (char*)"-d";

  test_argv[ 1 ] = (char*)"0";
  test_ret       = parser_parameter( test_argc, test_argv, &test_index );
  CPPUNIT_ASSERT_EQUAL( RET_SUCCESS, test_ret );
  CPPUNIT_ASSERT_EQUAL( 0, test_index );

  test_argv[ 1 ] = (char*)"05";
  test_ret       = parser_parameter( test_argc, test_argv, &test_index );
  CPPUNIT_ASSERT_EQUAL( RET_SUCCESS, test_ret );
  CPPUNIT_ASSERT_EQUAL( 5, test_index );

  test_argv[ 1 ] = (char*)"100";
  test_ret       = parser_parameter( test_argc, test_argv, &test_index );
  CPPUNIT_ASSERT_EQUAL( RET_SUCCESS, test_ret );
  CPPUNIT_ASSERT_EQUAL( 100, test_index );

  test_argv[ 1 ] = (char*)"127";
  test_ret       = parser_parameter( test_argc, test_argv, &test_index );
  CPPUNIT_ASSERT_EQUAL( RET_SUCCESS, test_ret );
  CPPUNIT_ASSERT_EQUAL( 127, test_index );

  test_argv[ 1 ] = (char*)"128";
  test_ret       = parser_parameter( test_argc, test_argv, &test_index );
  CPPUNIT_ASSERT_EQUAL( RET_SUCCESS, test_ret );
  CPPUNIT_ASSERT_EQUAL( 128, test_index );
}

void CTestGAscii::TestGAsciiParserParameterChar( )
{
  test_argc      = 2;
  test_argv[ 0 ] = (char*)"-c";

  test_argv[ 1 ] = (char*)" ";
  test_ret       = parser_parameter( test_argc, test_argv, &test_index );
  CPPUNIT_ASSERT_EQUAL( RET_SUCCESS, test_ret );
  CPPUNIT_ASSERT_EQUAL( 32, test_index );

  test_argv[ 1 ] = (char*)"0";
  test_ret       = parser_parameter( test_argc, test_argv, &test_index );
  CPPUNIT_ASSERT_EQUAL( RET_SUCCESS, test_ret );
  CPPUNIT_ASSERT_EQUAL( 48, test_index );

  test_argv[ 1 ] = (char*)"a";
  test_ret       = parser_parameter( test_argc, test_argv, &test_index );
  CPPUNIT_ASSERT_EQUAL( RET_SUCCESS, test_ret );
  CPPUNIT_ASSERT_EQUAL( 97, test_index );

  test_argv[ 1 ] = (char*)"Z";
  test_ret       = parser_parameter( test_argc, test_argv, &test_index );
  CPPUNIT_ASSERT_EQUAL( RET_SUCCESS, test_ret );
  CPPUNIT_ASSERT_EQUAL( 90, test_index );

  test_argv[ 1 ] = (char*)"~";
  test_ret       = parser_parameter( test_argc, test_argv, &test_index );
  CPPUNIT_ASSERT_EQUAL( RET_SUCCESS, test_ret );
  CPPUNIT_ASSERT_EQUAL( 126, test_index );
}

void CTestGAscii::TestGAsciiParserParameterError( )
{
  test_argc = 0;
  test_ret  = parser_parameter( test_argc, test_argv, &test_index );
  CPPUNIT_ASSERT_EQUAL( RET_ERROR, test_ret );

  test_argc      = 1;
  test_argv[ 0 ] = (char*)"-y";
  test_ret       = parser_parameter( test_argc, test_argv, &test_index );
  CPPUNIT_ASSERT_EQUAL( RET_ERROR, test_ret );

  test_argc      = 2;
  test_argv[ 0 ] = (char*)"-h";
  test_argv[ 1 ] = (char*)"kk";
  test_ret       = parser_parameter( test_argc, test_argv, &test_index );
  CPPUNIT_ASSERT_EQUAL( RET_ERROR, test_ret );

  test_argc      = 2;
  test_argv[ 0 ] = (char*)"-d";
  test_argv[ 1 ] = (char*)"kk";
  test_ret       = parser_parameter( test_argc, test_argv, &test_index );
  CPPUNIT_ASSERT_EQUAL( RET_ERROR, test_ret );
}

void CTestGAscii::TestGAsciiParserParameterHelp( )
{
  test_argc      = 1;
  test_argv[ 0 ] = (char*)"?";
  test_ret       = parser_parameter( test_argc, test_argv, &test_index );
  CPPUNIT_ASSERT_EQUAL( test_ret, RET_HELP );

  test_argc      = 1;
  test_argv[ 0 ] = (char*)"help";
  test_ret       = parser_parameter( test_argc, test_argv, &test_index );
  CPPUNIT_ASSERT_EQUAL( test_ret, RET_HELP );
}

void CTestGAscii::TestGAsciiParserParameterVersion( )
{
  test_argc      = 1;
  test_argv[ 0 ] = (char*)"-v";
  test_ret       = parser_parameter( test_argc, test_argv, &test_index );
  CPPUNIT_ASSERT_EQUAL( test_ret, RET_VERSION );
}
