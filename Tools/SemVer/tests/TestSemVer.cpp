#include "CppUTest/TestHarness.h"
#include "semver.h"

TEST_GROUP(TestSemVer)
{ 

void setup()
{

}
void teardown()
{

}
};

TEST(TestSemVer, TestGAsciiPrintAsciiByindexNormal) 
{
  tSemverVersion ver;
  char str[10] = "1.2.3";
  
  ver.major = 0;
  ver.minor = 0;
  ver.patch = 0; 
  
  SemVer_ConvertFromStr(&ver, str);
  
  CHECK_EQUAL( 1, ver.major );
  CHECK_EQUAL( 2, ver.minor );
  CHECK_EQUAL( 3, ver.patch );
}

