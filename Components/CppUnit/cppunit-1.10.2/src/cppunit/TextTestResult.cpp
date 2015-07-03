#include <cppunit/Exception.h>
#include <cppunit/Test.h>
#include <cppunit/TestFailure.h>
#include <cppunit/TextTestResult.h>
#include <cppunit/TextOutputter.h>

#if defined (CPPUNIT_WITHOUT_CPP_STREAM)
#  if !defined(CPPUNIT_WITHOUT_C_OUTPUT)
#    include <stdio.h>
#  endif
#else
#include <iostream>
#endif

CPPUNIT_NS_BEGIN


TextTestResult::TextTestResult()
{
  addListener( this );
}


void 
TextTestResult::addFailure( const TestFailure &failure )
{
  TestResultCollector::addFailure( failure );
#if defined (CPPUNIT_WITHOUT_CPP_STREAM)
#  if !defined (CPPUNIT_WITHOUT_C_OUTPUT)
  printf(( failure.isError() ? "E" : "F" ));
#  endif
#else
  std::cerr << ( failure.isError() ? "E" : "F" );
#endif
}


void 
TextTestResult::startTest( Test *test )
{
  TestResultCollector::startTest (test);
#if defined (CPPUNIT_WITHOUT_CPP_STREAM)
#  if !defined (CPPUNIT_WITHOUT_C_OUTPUT)
  printf(".");
#  endif
#else
  std::cerr << ".";
#endif
}


#if defined (CPPUNIT_WITHOUT_CPP_STREAM)
#else
void 
TextTestResult::print( std::ostream& stream ) 
{
  TextOutputter outputter( this, stream );
  outputter.write();
}
#endif


#if defined (CPPUNIT_WITHOUT_CPP_STREAM)
#else
std::ostream &
operator <<( std::ostream &stream, 
             TextTestResult &result )
{ 
  result.print (stream); return stream; 
}
#endif


CPPUNIT_NS_END
