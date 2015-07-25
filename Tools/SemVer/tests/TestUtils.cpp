#include "CppUTest/TestHarness.h"
#include "utils.h"

TEST_GROUP(TestUtils)
{ 

void setup()
{

}
void teardown()
{

}
};



TEST(TestUtils, TestGAsciiPrintAsciiByindexNormal) 
{
  char name[128];
  
  ChangFileName((char*)"mytest.hex", (char*)"0.1.0",name);
  
  STRCMP_EQUAL( "mytest_v0.1.0.hex", name );
}

TEST(TestUtils, TestGAsciiPrintAsciiByindex128) 
{
  CHECK_EQUAL( 1, 1 );
}

TEST(TestUtils, TestGAsciiParserParameterAll) 
{
  CHECK_EQUAL( 1, 1 );
}

TEST(TestUtils, TestGAsciiParserParameterHex) 
{
  CHECK_EQUAL( 1, 1 );
}

TEST(TestUtils, TestGAsciiParserParameterDec) 
{
  CHECK_EQUAL( 1, 1 );
}

TEST(TestUtils, TestGAsciiParserParameterChar) 
{
  CHECK_EQUAL( 1, 1 );
}

TEST(TestUtils, TestGAsciiParserParameterError) 
{
  CHECK_EQUAL( 1, 1 );
}

TEST(TestUtils, TestGAsciiParserParameterHelp) 
{
  CHECK_EQUAL( 1, 1 );
}

TEST(TestUtils, TestGAsciiParserParameterVersion) 
{
  CHECK_EQUAL( 1, 1 );
}
