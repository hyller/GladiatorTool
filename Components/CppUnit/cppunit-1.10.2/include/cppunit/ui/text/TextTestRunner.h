#ifndef CPPUNIT_UI_TEXT_TEXTTESTRUNNER_H
#define CPPUNIT_UI_TEXT_TEXTTESTRUNNER_H


#include <cppunit/Portability.h>
#include <string>
#include <cppunit/TestRunner.h>

CPPUNIT_NS_BEGIN


#ifndef CPPUNIT_LIGHT_VERSION
class Outputter;
class Test;
class TestSuite;
class TextOutputter;
class TestResult;
class TestResultCollector;
#endif


/*!
 * \brief A text mode test runner.
 * \ingroup WritingTestResult
 * \ingroup ExecutingTest
 *
 * The test runner manage the life cycle of the added tests.
 *
 * The test runner can run only one of the added tests or all the tests. 
 *
 * TestRunner prints out a trace as the tests are executed followed by a
 * summary at the end. The trace and summary print are optional.
 *
 * Here is an example of use:
 *
 * \code
 * CppUnit::TextTestRunner runner;
 * runner.addTest( ExampleTestCase::suite() );
 * runner.run( "", true );    // Run all tests and wait
 * \endcode
 *
 * The trace is printed using a TextTestProgressListener. The summary is printed
 * using a TextOutputter. 
 *
 * You can specify an alternate Outputter at construction
 * or later with setOutputter(). 
 *
 * After construction, you can register additional TestListener to eventManager(),
 * for a custom progress trace, for example.
 *
 * \code
 * CppUnit::TextTestRunner runner;
 * runner.addTest( ExampleTestCase::suite() );
 * runner.setOutputter( CppUnit::CompilerOutputter::defaultOutputter( 
 *                          &runner.result(),
 *                          std::cerr ) );
 * MyCustomProgressTestListener progress;
 * runner.eventManager().addListener( &progress );
 * runner.run( "", true );    // Run all tests and wait
 * \endcode
 *
 * \see CompilerOutputter, XmlOutputter, TextOutputter.
 */
#ifndef CPPUNIT_LIGHT_VERSION
class CPPUNIT_API TextTestRunner : public CPPUNIT_NS::TestRunner
{
public:
  TextTestRunner( Outputter *outputter =NULL );

  virtual ~TextTestRunner();

  bool run( std::string testPath ="",
            bool doWait = false,
            bool doPrintResult = true,
            bool doPrintProgress = true );

  void setOutputter( Outputter *outputter );

  TestResultCollector &result() const;

  TestResult &eventManager() const;

protected:
  virtual void wait( bool doWait );
  virtual void printResult( std::string testName, bool doPrintResult );

  TestResultCollector *m_result;
  TestResult *m_eventManager;
  Outputter *m_outputter;
};
#else
class CPPUNIT_API TextTestRunner
{
public:
  TextTestRunner( );
  
  void addTest( std::string test );
  
  bool run( std::string testPath ="" );

};
#endif

CPPUNIT_NS_END

#endif  // CPPUNIT_UI_TEXT_TEXTTESTRUNNER_H
