#include "CppUTest/TestHarness.h"
#include "semver.h"

TEST_GROUP( TestSemVer )
{
  void setup( )
  {
  }

  void teardown( )
  {
  }
};

TEST( TestSemVer, ConvertFromStr )
{
  tSemverVersion ver;
  char           str[ 10 ] = "1.2.3";

  ver.major = 0;
  ver.minor = 0;
  ver.patch = 0;

  SemVer_ConvertFromStr( &ver, str );

  CHECK_EQUAL( 1, ver.major );
  CHECK_EQUAL( 2, ver.minor );
  CHECK_EQUAL( 3, ver.patch );
}

TEST( TestSemVer, ConvertToStr )
{
  tSemverVersion ver;
  char           str[ 10 ] = "0";

  ver.major = 1;
  ver.minor = 2;
  ver.patch = 3;

  SemVer_ConvertToStr( &ver, str, 0 );

  STRCMP_CONTAINS("1.2.3", str );
}

TEST( TestSemVer, ConvertToStr2 )
{
  tSemverVersion ver;
  char           str[ 10 ] = "0";

  ver.major = 1;
  ver.minor = 2;
  ver.patch = 3;

  SemVer_ConvertToStr( &ver, str, 2 );

  STRCMP_CONTAINS("01.02.03", str );
}

TEST( TestSemVer, ConvertToStr3 )
{
  tSemverVersion ver;
  char           str[ 10 ] = "0";

  ver.major = 1;
  ver.minor = 2;
  ver.patch = 3;

  SemVer_ConvertToStr( &ver, str, 3 );

  STRCMP_CONTAINS("001.002.003", str );
}

TEST( TestSemVer, Increase255 )
{
  tSemverVersion ver;

  ver.major = 0;
  ver.minor = 255;
  ver.patch = 255;

  SemVer_IncreasePatch( &ver );

  CHECK_EQUAL( 0, ver.major );
  CHECK_EQUAL( 255, ver.minor );
  CHECK_EQUAL( 256, ver.patch );
}