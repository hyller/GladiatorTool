#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/Test.h>
#include <cppunit/TestFailure.h>

#if defined (CPPUNIT_WITHOUT_CPP_STREAM)
#  if !defined(CPPUNIT_WITHOUT_C_OUTPUT)
#    include <stdio.h>
#  endif
#else
#include <iostream>
#endif

CPPUNIT_NS_BEGIN


BriefTestProgressListener::BriefTestProgressListener()
    : m_lastTestFailed( false )
{
}


BriefTestProgressListener::~BriefTestProgressListener()
{
}


void 
BriefTestProgressListener::startTest( Test *test )
{
#if defined (CPPUNIT_WITHOUT_CPP_STREAM)
#  if !defined (CPPUNIT_WITHOUT_C_OUTPUT)
  printf(test->getName().c_str());
#  endif
#else
  std::cerr << test->getName();
  std::cerr.flush();
#endif
  m_lastTestFailed = false;
}


void 
BriefTestProgressListener::addFailure( const TestFailure &failure )
{
#if defined (CPPUNIT_WITHOUT_CPP_STREAM)
#  if !defined (CPPUNIT_WITHOUT_C_OUTPUT)
  printf(" : ");
  printf((failure.isError() ? "error" : "assertion"));
#  endif
#else
  std::cerr << " : " << (failure.isError() ? "error" : "assertion");
#endif
  m_lastTestFailed  = true;
}


void 
BriefTestProgressListener::endTest( Test *test )
{
  if ( !m_lastTestFailed )
#if defined (CPPUNIT_WITHOUT_CPP_STREAM)
#  if !defined (CPPUNIT_WITHOUT_C_OUTPUT)
    printf(" : OK");
#  else
    { /* Do notthing */}
#  endif
#else
    std::cerr  <<  " : OK";
#endif

#if defined (CPPUNIT_WITHOUT_CPP_STREAM)
#  if !defined (CPPUNIT_WITHOUT_C_OUTPUT)
  printf("\n");
#  endif
#else
  std::cerr << std::endl;
#endif
}


CPPUNIT_NS_END

