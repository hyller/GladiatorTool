#include <cppunit/Exception.h>
#include <cppunit/SourceLine.h>
#include <cppunit/TestFailure.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/TestResultCollector.h>

#if defined (CPPUNIT_WITHOUT_CPP_STREAM)
#  if !defined(CPPUNIT_WITHOUT_C_OUTPUT)
#    include <stdio.h>
#  endif
#endif

CPPUNIT_NS_BEGIN


#if defined (CPPUNIT_WITHOUT_CPP_STREAM)
TextOutputter::TextOutputter( TestResultCollector *result )
    : m_result( result )
{
}
#else
TextOutputter::TextOutputter( TestResultCollector *result,
                              std::ostream &stream )
    : m_result( result )
    , m_stream( stream )
{
}
#endif

TextOutputter::~TextOutputter()
{
}

void 
TextOutputter::write() 
{
	write("");
}

void 
TextOutputter::write( std::string testName ) 
{
  printHeader(testName);
#if defined (CPPUNIT_WITHOUT_CPP_STREAM)
#  if !defined (CPPUNIT_WITHOUT_C_OUTPUT)
  printf("\n");
#  endif
#else
  m_stream << std::endl;
#endif
  printFailures();
#if defined (CPPUNIT_WITHOUT_CPP_STREAM)
#  if !defined (CPPUNIT_WITHOUT_C_OUTPUT)
  printf("\n");
#  endif
#else
  m_stream << std::endl;
#endif
}

void 
TextOutputter::printFailures()
{
  TestResultCollector::TestFailures::const_iterator itFailure = m_result->failures().begin();
  int failureNumber = 1;
  while ( itFailure != m_result->failures().end() ) 
  {
#if defined (CPPUNIT_WITHOUT_CPP_STREAM)
#  if !defined (CPPUNIT_WITHOUT_C_OUTPUT)
    printf("\n");
#  endif
#else
    m_stream  <<  std::endl;
#endif
    printFailure( *itFailure++, failureNumber++ );
  }
}


void 
TextOutputter::printFailure( TestFailure *failure,
                             int failureNumber )
{
  printFailureListMark( failureNumber );
#if defined (CPPUNIT_WITHOUT_CPP_STREAM)
#  if !defined (CPPUNIT_WITHOUT_C_OUTPUT)
  printf(" ");
#  endif
#else
  m_stream << ' ';
#endif
  printFailureTestName( failure );
#if defined (CPPUNIT_WITHOUT_CPP_STREAM)
#  if !defined (CPPUNIT_WITHOUT_C_OUTPUT)
  printf(" ");
#  endif
#else
  m_stream << ' ';
#endif
  printFailureType( failure );
#if defined (CPPUNIT_WITHOUT_CPP_STREAM)
#  if !defined (CPPUNIT_WITHOUT_C_OUTPUT)
  printf(" ");
#  endif
#else
  m_stream << ' ';
#endif
  printFailureLocation( failure->sourceLine() );
#if defined (CPPUNIT_WITHOUT_CPP_STREAM)
#  if !defined (CPPUNIT_WITHOUT_C_OUTPUT)
  printf("\n");
#  endif
#else
  m_stream << std::endl;
#endif
  printFailureDetail( failure->thrownException() );
#if defined (CPPUNIT_WITHOUT_CPP_STREAM)
#  if !defined (CPPUNIT_WITHOUT_C_OUTPUT)
  printf("\n");
#  endif
#else
  m_stream << std::endl;
#endif
}


void 
TextOutputter::printFailureListMark( int failureNumber )
{
#if defined (CPPUNIT_WITHOUT_CPP_STREAM)
#  if !defined (CPPUNIT_WITHOUT_C_OUTPUT)
  printf("%d)",failureNumber);
#  endif
#else
  m_stream << failureNumber << ")";
#endif
}


void 
TextOutputter::printFailureTestName( TestFailure *failure )
{
#if defined (CPPUNIT_WITHOUT_CPP_STREAM)
#  if !defined (CPPUNIT_WITHOUT_C_OUTPUT)
  printf("test: ");
  printf(failure->failedTestName().c_str());
#  endif
#else
  m_stream << "test: " << failure->failedTestName();
#endif
}


void 
TextOutputter::printFailureType( TestFailure *failure )
{
#if defined (CPPUNIT_WITHOUT_CPP_STREAM)
#  if !defined (CPPUNIT_WITHOUT_C_OUTPUT)
  printf("(");
  printf((failure->isError() ? "E" : "F"));
  printf(")");
#  endif
#else
  m_stream << "("
           << (failure->isError() ? "E" : "F")
           << ")";
#endif
}


void 
TextOutputter::printFailureLocation( SourceLine sourceLine )
{
  if ( !sourceLine.isValid() )
    return;

#if defined (CPPUNIT_WITHOUT_CPP_STREAM)
#  if !defined (CPPUNIT_WITHOUT_C_OUTPUT)
  printf("line: %d", sourceLine.lineNumber());
  printf(" %s", sourceLine.fileName().c_str());
#endif
#else
  m_stream << "line: " << sourceLine.lineNumber()
           << ' ' << sourceLine.fileName();
#endif
}


void 
TextOutputter::printFailureDetail( Exception *thrownException )
{
#if defined (CPPUNIT_WITHOUT_CPP_STREAM)
#  if !defined (CPPUNIT_WITHOUT_C_OUTPUT)
  printf("%s\n", thrownException->message().shortDescription().c_str());
  printf("%s", thrownException->message().details().c_str());
#  endif
#else
  m_stream  <<  thrownException->message().shortDescription()  <<  std::endl;
  m_stream  <<  thrownException->message().details();
#endif
}

void 
TextOutputter::printHeader( )
{
	printHeader("");
}

void 
TextOutputter::printHeader( std::string testName )
{
  if ( m_result->wasSuccessful() )
#if defined (CPPUNIT_WITHOUT_CPP_STREAM)
#  if !defined (CPPUNIT_WITHOUT_C_OUTPUT)
    printf("\n%s OK (%d tests)\n", testName, m_result->runTests ());
#  else
    { /* Do nothing */}
#  endif
#else
    m_stream << std::endl << testName << " OK (" << m_result->runTests () << " tests)" 
             << std::endl;
#endif
  else
  {
#if defined (CPPUNIT_WITHOUT_CPP_STREAM)
#  if !defined (CPPUNIT_WITHOUT_C_OUTPUT)
    printf("\n");
#  endif
#else
    m_stream << std::endl;
#endif
    printFailureWarning();
    printStatistics(testName);
  }
}


void 
TextOutputter::printFailureWarning()
{
#if defined (CPPUNIT_WITHOUT_CPP_STREAM)
#  if !defined (CPPUNIT_WITHOUT_C_OUTPUT)
  printf("!!!FAILURES!!!\n");
#  endif
#else
  m_stream  << "!!!FAILURES!!!" << std::endl;
#endif
}


void 
TextOutputter::printStatistics( )
{
	printStatistics( "" );
}

void 
TextOutputter::printStatistics( std::string testName )
{
#if defined (CPPUNIT_WITHOUT_CPP_STREAM)
#  if !defined (CPPUNIT_WITHOUT_C_OUTPUT)
  printf("Test Results:\n");
#  endif
#else
  m_stream  << "Test Results:" << std::endl;
#endif

#if defined (CPPUNIT_WITHOUT_CPP_STREAM)
#  if !defined (CPPUNIT_WITHOUT_C_OUTPUT)
  printf("%s Run:  %d",testName, m_result->runTests());
  printf("   Failures: %d",m_result->testFailures());
  printf("   Errors: %d",m_result->testErrors());
  printf("\n");
#  endif
#else
  m_stream  <<  testName << " Run:  "  <<  m_result->runTests()
            <<  "   Failures: "  <<  m_result->testFailures()
            <<  "   Errors: "  <<  m_result->testErrors()
            <<  std::endl;
#endif
}


CPPUNIT_NS_END

