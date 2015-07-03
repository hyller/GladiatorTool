#ifndef CPPUNIT_TEXTTESTRESULT_H
#define CPPUNIT_TEXTTESTRESULT_H

#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>

#if defined (CPPUNIT_WITHOUT_CPP_STREAM)
#  if !defined(CPPUNIT_WITHOUT_C_OUTPUT)
#    include <stdio.h>
#  endif
#else
#include <iostream>
#endif

CPPUNIT_NS_BEGIN


class SourceLine;
class Exception;
class Test;

/*! \brief Holds printable test result (DEPRECATED).
 * \ingroup TrackingTestExecution
 * 
 * deprecated Use class TextTestProgressListener and TextOutputter instead.
 */
class CPPUNIT_API TextTestResult : public TestResult,
                                   public TestResultCollector
{
public:
  TextTestResult();

  virtual void addFailure( const TestFailure &failure );
  virtual void startTest( Test *test );
#if defined (CPPUNIT_WITHOUT_CPP_STREAM)
#else
  virtual void print( std::ostream &stream );
#endif
};

#if defined (CPPUNIT_WITHOUT_CPP_STREAM)
#else
/** insertion operator for easy output */
CPPUNIT_API std::ostream &operator <<( std::ostream &stream, 
                                       TextTestResult &result );
#endif

CPPUNIT_NS_END

#endif // CPPUNIT_TEXTTESTRESULT_H


