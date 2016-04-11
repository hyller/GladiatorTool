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
    (char*)"semver",
    (char*)"-x",
    (char*)"-v",
    (char*)"-h",
    (char*)"-s",
    (char*)"-l2",
    (char*)"-ahello",
    (char*)"-i2.3.4",
    (char*)"version.h"
  };
  int   testargc = sizeof( testargv ) / sizeof( testargv[ 0 ] );

  Setting_Init( &as );
  Setting_Parse( &as, testargc, (char**)testargv );

  CHECK_EQUAL( 1, as.version );
  CHECK_EQUAL( 1, as.help );
  CHECK_EQUAL( 2, as.index );
  CHECK_EQUAL( 1, as.simple );
  CHECK_EQUAL( 1, as.append );
  CHECK_EQUAL( 1, as.init );
  CHECK_EQUAL( 2, as.length );
  STRCMP_EQUAL( "hello", as.appendarg );
  STRCMP_EQUAL( "version.h", as.filename );
  STRCMP_EQUAL( "2.3.4", as.initarg );
}