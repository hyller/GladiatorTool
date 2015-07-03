#ifndef CPPUNIT_TEXTOUTPUTTER_H
#define CPPUNIT_TEXTOUTPUTTER_H

#include <cppunit/Portability.h>
#include <cppunit/Outputter.h>

#if defined (CPPUNIT_WITHOUT_CPP_STREAM)
#  if !defined(CPPUNIT_WITHOUT_C_OUTPUT)
#    include <stdio.h>
#  endif
#else
#include <iostream>
#endif

CPPUNIT_NS_BEGIN


class Exception;
class SourceLine;
class TestResultCollector;
class TestFailure;


/*! \brief Prints a TestResultCollector to a text stream.
 * \ingroup WritingTestResult
 */
class CPPUNIT_API TextOutputter : public Outputter
{
public:
#if defined (CPPUNIT_WITHOUT_CPP_STREAM)
  TextOutputter( TestResultCollector *result );
#else
  TextOutputter( TestResultCollector *result,
                 std::ostream &stream );
#endif

  /// Destructor.
  virtual ~TextOutputter();

  void write();
  void write( std::string testName );
  virtual void printFailures();
  virtual void printHeader();
  virtual void printHeader( std::string testName );

  virtual void printFailure( TestFailure *failure,
                             int failureNumber );
  virtual void printFailureListMark( int failureNumber );
  virtual void printFailureTestName( TestFailure *failure );
  virtual void printFailureType( TestFailure *failure );
  virtual void printFailureLocation( SourceLine sourceLine );
  virtual void printFailureDetail( Exception *thrownException );
  virtual void printFailureWarning();
  virtual void printStatistics();
  virtual void printStatistics( std::string testName );

protected:
  TestResultCollector *m_result;
#if defined (CPPUNIT_WITHOUT_CPP_STREAM)
#else
  std::ostream &m_stream;
#endif

private:
  /// Prevents the use of the copy constructor.
  TextOutputter( const TextOutputter &copy );

  /// Prevents the use of the copy operator.
  void operator =( const TextOutputter &copy );
};



CPPUNIT_NS_END

#endif  // CPPUNIT_TEXTOUTPUTTER_H
