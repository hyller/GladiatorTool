// ==> Implementation of cppunit/ui/text/TestRunner.h

#ifndef CPPUNIT_LIGHT_VERSION
#include <cppunit/TestSuite.h>
#include <cppunit/TextTestResult.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/TextTestProgressListener.h>
#include <cppunit/TestResult.h>
#endif
#include <cppunit/ui/text/TextTestRunner.h>

#if defined (CPPUNIT_WITHOUT_CPP_STREAM)
#  if !defined(CPPUNIT_WITHOUT_C_OUTPUT)
#    include <stdio.h>
#  endif
#else
#include <iostream>
#endif

#include <stdexcept>


CPPUNIT_NS_BEGIN


/*! Constructs a new text runner.
 * \param outputter used to print text result. Owned by the runner.
 */
#ifndef CPPUNIT_LIGHT_VERSION
TextTestRunner::TextTestRunner( Outputter *outputter ) 
    : m_outputter( outputter )
    , m_result( new TestResultCollector() )
    , m_eventManager( new TestResult() )
{
  if ( !m_outputter )
#if defined (CPPUNIT_WITHOUT_CPP_STREAM)
    m_outputter = new TextOutputter( m_result );
#else
    m_outputter = new TextOutputter( m_result, std::cout );
#endif
  m_eventManager->addListener( m_result );
}
#else
TextTestRunner::TextTestRunner(  ) 
{
}
#endif

#ifndef CPPUNIT_LIGHT_VERSION
TextTestRunner::~TextTestRunner()
{
  delete m_eventManager;
  delete m_outputter;
  delete m_result;
}
#else
TextTestRunner::~TextTestRunner()
{
}
#endif

/*! Runs the named test case.
 *
 * \param testName Name of the test case to run. If an empty is given, then
 *                 all added tests are run. The name can be the name of any
 *                 test in the hierarchy.
 * \param doWait if \c true then the user must press the RETURN key 
 *               before the run() method exit.
 * \param doPrintResult if \c true (default) then the test result are printed
 *                      on the standard output.
 * \param doPrintProgress if \c true (default) then TextTestProgressListener is
 *                        used to show the progress.
 * \return \c true is the test was successful, \c false if the test
 *         failed or was not found.
 */
#ifndef CPPUNIT_LIGHT_VERSION
bool
TextTestRunner::run( std::string testName,
                       bool doWait,
                       bool doPrintResult,
                       bool doPrintProgress )
{
  TextTestProgressListener progress;
  if ( doPrintProgress )
    m_eventManager->addListener( &progress );

  TestRunner *pThis = this;
  pThis->run( *m_eventManager, testName );

  if ( doPrintProgress )
    m_eventManager->removeListener( &progress );

  printResult( testName, doPrintResult );
  wait( doWait );

  return m_result->wasSuccessful();
}
#else
bool
TextTestRunner::run( std::string testName )
{
	printf("TextTestRunner::run\n");
	return(TRUE);
}
#endif

#ifndef CPPUNIT_LIGHT_VERSION
void 
TextTestRunner::wait( bool doWait )
{
  if ( doWait ) 
  {
#if defined (CPPUNIT_WITHOUT_CPP_STREAM)
#  if !defined (CPPUNIT_WITHOUT_C_OUTPUT)
  printf("<RETURN> to continue");
  printf(" (no pause for ARM) ");
  printf("\n");
#  endif
#else
    std::cout << "<RETURN> to continue" << std::endl;
    std::cin.get ();
#endif
  }
}
#endif

#ifndef CPPUNIT_LIGHT_VERSION
void 
TextTestRunner::printResult( std::string testName, bool doPrintResult )
{
#if defined (CPPUNIT_WITHOUT_CPP_STREAM)
#  if !defined (CPPUNIT_WITHOUT_C_OUTPUT)
  printf("\n");
#  endif
#else
  std::cout << std::endl;
#endif
  if ( doPrintResult )
    m_outputter->write(testName);
}
#endif

/*! Returns the result of the test run.
 * Use this after calling run() to access the result of the test run.
 */
#ifndef CPPUNIT_LIGHT_VERSION
TestResultCollector &
TextTestRunner::result() const
{
  return *m_result;
}
#endif

/*! Returns the event manager.
 * The instance of TestResult results returned is the one that is used to run the
 * test. Use this to register additional TestListener before running the tests.
 */
#ifndef CPPUNIT_LIGHT_VERSION
TestResult &
TextTestRunner::eventManager() const
{
  return *m_eventManager;
}
#endif

/*! Specifies an alternate outputter.
 *
 * Notes that the outputter will be use after the test run only if \a printResult was
 * \c true.
 * \param outputter New outputter to use. The previous outputter is destroyed. 
 *                  The TextTestRunner assumes ownership of the outputter.
 * \see CompilerOutputter, XmlOutputter, TextOutputter.
 */
#ifndef CPPUNIT_LIGHT_VERSION
void 
TextTestRunner::setOutputter( Outputter *outputter )
{
  delete m_outputter;
  m_outputter = outputter;
}
#endif

CPPUNIT_NS_END
