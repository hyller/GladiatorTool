#ifndef D_TestGAscii_H
  #define D_TestGAscii_H

#include <cppunit/extensions/HelperMacros.h>

  class CTestGAscii:public CPPUNIT_NS::TestFixture
  {
    CPPUNIT_TEST_SUITE( CTestGAscii );
    CPPUNIT_TEST( TestGAsciiPrintAsciiByindexNormal );
    CPPUNIT_TEST( TestGAsciiPrintAsciiByindex128 );
    CPPUNIT_TEST( TestGAsciiParserParameterAll );
    CPPUNIT_TEST( TestGAsciiParserParameterHex );
    CPPUNIT_TEST( TestGAsciiParserParameterDec );
    CPPUNIT_TEST( TestGAsciiParserParameterChar );
    CPPUNIT_TEST( TestGAsciiParserParameterError );
    CPPUNIT_TEST( TestGAsciiParserParameterHelp );
    CPPUNIT_TEST( TestGAsciiParserParameterVersion );
    CPPUNIT_TEST_SUITE_END( );

  public:
    void setUp( );
    void tearDown( );
    void TestGAsciiPrintAsciiByindexNormal( );
    void TestGAsciiPrintAsciiByindex128( );
    void TestGAsciiParserParameterAll( );
    void TestGAsciiParserParameterHex( );
    void TestGAsciiParserParameterDec( );
    void TestGAsciiParserParameterChar( );
    void TestGAsciiParserParameterError( );
    void TestGAsciiParserParameterHelp( );
    void TestGAsciiParserParameterVersion( );
  };
#endif