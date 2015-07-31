#include "CppUTest/TestHarness.h"
#include "utils.h"

TEST_GROUP( TestUtils )
{
  void setup( )
  {
  }

  void teardown( )
  {
  }
};

TEST( TestUtils, ChangeFileName )
{
  char name[ 128 ];

  ChangFileName( (char*)"mytest.hex", (char*)"0.1.0", name );

  STRCMP_EQUAL( "mytest_0.1.0.hex", name );
}

TEST( TestUtils, NoSuffix )
{
  char name[ 128 ];

  ChangFileName( (char*)"mytest", (char*)"0.1.0", name );

  STRCMP_EQUAL( "mytest_0.1.0", name );
}