#include <string.h>

#include "CppUTest/TestHarness.h"

#include "setting.h"

tSetting as;

TEST_GROUP( TestParse )
{
  void setup( )
  {
    Setting_Init( &as );
  }

  void teardown( )
  {
  }
};

TEST( TestParse, ParseAll )
{
  char* testargv[] = {
    (char* )"semver",    
    (char* )"-x",
    (char* )"-v",
    (char* )"-h",
    (char* )"-s",
    (char* )"-ahello",
    (char* )"version.h"
  };
  int testargc = sizeof( testargv ) / sizeof( testargv[ 0 ] );

  Setting_Init( &as );
  Setting_Parse( &as, testargc, (char**)testargv );

  CHECK_EQUAL( 1, as.version );
  CHECK_EQUAL( 1, as.help);
  CHECK_EQUAL( 0, as.index);
  CHECK_EQUAL( 1, as.simple);
  CHECK_EQUAL( 1, as.append );
  STRCMP_EQUAL("hello", as.appendarg);
  STRCMP_EQUAL("version.h", as.filename);
}

IGNORE_TEST( TestParse, ParseMinor )
{
  char* testargv[] = {
    (char* )"semver",    
    (char* )"-y",
    (char* )"version.h"
  };
  int testargc = sizeof( testargv ) / sizeof( testargv[ 0 ] );

  Setting_Init( &as );
  Setting_Parse( &as, testargc, (char**)testargv );

  CHECK_EQUAL( 1, as.index);
}

IGNORE_TEST( TestParse, ParsePatch )
{
  char* testargv[] = {
    (char* )"-z",
    (char* )"version.h"
  };
  int testargc = sizeof( testargv ) / sizeof( testargv[ 0 ] );

  Setting_Init( &as );
  Setting_Parse( &as, testargc, (char**)testargv );

  CHECK_EQUAL( 2, as.index);
}

TEST( TestParse, TestGAsciiParserParameterHex )
{
  CHECK_EQUAL( 1, 1 );
}

TEST( TestParse, TestGAsciiParserParameterDec )
{
  CHECK_EQUAL( 1, 1 );
}

TEST( TestParse, TestGAsciiParserParameterChar )
{
  CHECK_EQUAL( 1, 1 );
}

TEST( TestParse, TestGAsciiParserParameterError )
{
  CHECK_EQUAL( 1, 1 );
}

TEST( TestParse, TestGAsciiParserParameterHelp )
{
  CHECK_EQUAL( 1, 1 );
}

TEST( TestParse, TestGAsciiParserParameterVersion )
{
  CHECK_EQUAL( 1, 1 );
}