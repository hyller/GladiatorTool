#include <cppunit/TestFailure.h>
#include <cppunit/TextTestProgressListener.h>

#if defined (CPPUNIT_WITHOUT_CPP_STREAM)
#  if !defined(CPPUNIT_WITHOUT_C_OUTPUT)
#    include <stdio.h>
#  endif
#else
#include <iostream>
#endif


CPPUNIT_NS_BEGIN


TextTestProgressListener::TextTestProgressListener()
{
}


TextTestProgressListener::~TextTestProgressListener()
{
}


void 
TextTestProgressListener::startTest( Test *test )
{
#if defined (CPPUNIT_WITHOUT_CPP_STREAM)
#  if !defined (CPPUNIT_WITHOUT_C_OUTPUT)
  printf(".");
#  endif
#else
  std::cerr << ".";
#endif
}


void 
TextTestProgressListener::addFailure( const TestFailure &failure )
{
#if defined (CPPUNIT_WITHOUT_CPP_STREAM)
#  if !defined (CPPUNIT_WITHOUT_C_OUTPUT)
  printf(( failure.isError() ? "E" : "F" ));
#  endif
#else
  std::cerr << ( failure.isError() ? "E" : "F" );
#endif
}


void 
TextTestProgressListener::endTestRun( Test *test, 
                                      TestResult *eventManager )
{
#if defined (CPPUNIT_WITHOUT_CPP_STREAM)
#  if !defined (CPPUNIT_WITHOUT_C_OUTPUT)
  printf("\n");
#  endif
#else
  std::cerr  <<  std::endl;
  std::cerr.flush();
#endif
}


CPPUNIT_NS_END

