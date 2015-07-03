#include <cppunit/Exception.h>
#include <cppunit/SourceLine.h>
#include <cppunit/TestFailure.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/CompilerOutputter.h>
#include <algorithm>
#include <cppunit/tools/StringTools.h>

#if defined (CPPUNIT_WITHOUT_CPP_STREAM)
#  if !defined(CPPUNIT_WITHOUT_C_OUTPUT)
#    include <stdio.h>
#  endif
#else
#endif

CPPUNIT_NS_BEGIN


#if defined (CPPUNIT_WITHOUT_CPP_STREAM)
CompilerOutputter::CompilerOutputter( TestResultCollector *result,
                                      const std::string &locationFormat )
    : m_result( result )
    , m_locationFormat( locationFormat )
    , m_wrapColumn( CPPUNIT_WRAP_COLUMN )
{
}
#else
CompilerOutputter::CompilerOutputter( TestResultCollector *result,
                                      std::ostream &stream,
                                      const std::string &locationFormat )
    : m_result( result )
    , m_stream( stream )
    , m_locationFormat( locationFormat )
    , m_wrapColumn( CPPUNIT_WRAP_COLUMN )
{
}
#endif

CompilerOutputter::~CompilerOutputter()
{
}


void 
CompilerOutputter::setLocationFormat( const std::string &locationFormat )
{
  m_locationFormat = locationFormat;
}


#if defined (CPPUNIT_WITHOUT_CPP_STREAM)
CompilerOutputter *
CompilerOutputter::defaultOutputter( TestResultCollector *result )
{
  return new CompilerOutputter( result );
}
#else
CompilerOutputter *
CompilerOutputter::defaultOutputter( TestResultCollector *result,
                                     std::ostream &stream )
{
  return new CompilerOutputter( result, stream );
}
#endif

void 
CompilerOutputter::write()
{
  if ( m_result->wasSuccessful() )
    printSuccess();
  else
    printFailureReport();
}


void 
CompilerOutputter::printSuccess()
{
#if defined (CPPUNIT_WITHOUT_CPP_STREAM)
#  if !defined (CPPUNIT_WITHOUT_C_OUTPUT)
  printf("OK (%d)\n", m_result->runTests());
#  endif
#else
  m_stream  << "OK (" << m_result->runTests()  << ")"  
            <<  std::endl;
#endif
}


void 
CompilerOutputter::printFailureReport()
{
  printFailuresList();
  printStatistics();
}


void 
CompilerOutputter::printFailuresList()
{
  for ( int index =0; index < m_result->testFailuresTotal(); ++index)
  {
    printFailureDetail( m_result->failures()[ index ] );
  }
}


void 
CompilerOutputter::printFailureDetail( TestFailure *failure )
{
  printFailureLocation( failure->sourceLine() );
  printFailureType( failure );
  printFailedTestName( failure );
  printFailureMessage( failure );
}

 
void 
CompilerOutputter::printFailureLocation( SourceLine sourceLine )
{
  if ( !sourceLine.isValid() )
  {
#if defined (CPPUNIT_WITHOUT_CPP_STREAM)
#  if !defined (CPPUNIT_WITHOUT_C_OUTPUT)
    printf("##Failure Location unknown## : ");
#  endif
#else
    m_stream  <<  "##Failure Location unknown## : ";
#endif
    return;
  }

  std::string location;
  for ( unsigned int index = 0; index < m_locationFormat.length(); ++index )
  {
    char c = m_locationFormat[ index ];
    if ( c == '%'  &&  ( index+1 < m_locationFormat.length() ) )
    {
      char command = m_locationFormat[index+1];
      if ( processLocationFormatCommand( command, sourceLine ) )
      {
        ++index;
        continue;
      }
    }

#if defined (CPPUNIT_WITHOUT_CPP_STREAM)
#  if !defined (CPPUNIT_WITHOUT_C_OUTPUT)
    printf("%c", c);
#endif
#else
    m_stream  << c;
#endif
  }
}


bool 
CompilerOutputter::processLocationFormatCommand( char command, 
                                                 const SourceLine &sourceLine )
{
  switch ( command )
  {
  case 'p':
#if defined (CPPUNIT_WITHOUT_CPP_STREAM)
#  if !defined (CPPUNIT_WITHOUT_C_OUTPUT)
    printf("%s", sourceLine.fileName().c_str());
#  endif
#else
    m_stream  <<  sourceLine.fileName();
#endif
    return true;
    
  case 'l':
#if defined (CPPUNIT_WITHOUT_CPP_STREAM)
#  if !defined (CPPUNIT_WITHOUT_C_OUTPUT)
    printf("%d", sourceLine.lineNumber());
#  endif
#else
    m_stream  <<  sourceLine.lineNumber();
#endif
    return true;
    
  case 'f':
#if defined (CPPUNIT_WITHOUT_CPP_STREAM)
#  if !defined (CPPUNIT_WITHOUT_C_OUTPUT)
    printf("%s", extractBaseName( sourceLine.fileName() ).c_str());
#  endif
#else
    m_stream  <<  extractBaseName( sourceLine.fileName() );
#endif
    return true;
  }
  
  return false;
}


std::string 
CompilerOutputter::extractBaseName( const std::string &fileName ) const
{
  int indexLastDirectorySeparator = fileName.find_last_of( '/' );
  
  if ( indexLastDirectorySeparator < 0 )
    indexLastDirectorySeparator = fileName.find_last_of( '\\' );
  
  if ( indexLastDirectorySeparator < 0 )
    return fileName;

  return fileName.substr( indexLastDirectorySeparator +1 );
}


void 
CompilerOutputter::printFailureType( TestFailure *failure )
{
#if defined (CPPUNIT_WITHOUT_CPP_STREAM)
#  if !defined (CPPUNIT_WITHOUT_C_OUTPUT)
  printf((failure->isError() ? "Error" : "Assertion"));
#  endif
#else
  m_stream  <<  (failure->isError() ? "Error" : "Assertion");
#endif
}


void 
CompilerOutputter::printFailedTestName( TestFailure *failure )
{
#if defined (CPPUNIT_WITHOUT_CPP_STREAM)
#  if !defined (CPPUNIT_WITHOUT_C_OUTPUT)
  printf("\nTest name: %s", failure->failedTestName().c_str());
#  endif
#else
  m_stream  <<  std::endl;
  m_stream  <<  "Test name: "  <<  failure->failedTestName();
#endif
}


void 
CompilerOutputter::printFailureMessage( TestFailure *failure )
{
#if defined (CPPUNIT_WITHOUT_CPP_STREAM)
#  if !defined (CPPUNIT_WITHOUT_C_OUTPUT)
  printf("\n");
#  endif
#else
  m_stream  <<  std::endl;
#endif
  Exception *thrownException = failure->thrownException();
#if defined (CPPUNIT_WITHOUT_CPP_STREAM)
#  if !defined (CPPUNIT_WITHOUT_C_OUTPUT)
  printf("%s\n",thrownException->message().shortDescription().c_str());
#  endif
#else
  m_stream  << thrownException->message().shortDescription()  <<  std::endl;
#endif

  std::string message = thrownException->message().details();
  if ( m_wrapColumn > 0 )
    message = StringTools::wrap( message, m_wrapColumn );

#if defined (CPPUNIT_WITHOUT_CPP_STREAM)
#  if !defined (CPPUNIT_WITHOUT_C_OUTPUT)
  printf("%s\n", message.c_str());
#  endif
#else
  m_stream  <<  message  <<  std::endl;
#endif
}


void 
CompilerOutputter::printStatistics()
{
#if defined (CPPUNIT_WITHOUT_CPP_STREAM)
#  if !defined (CPPUNIT_WITHOUT_C_OUTPUT)
  printf("Failures !!!\n");
  printf("Run: %d   ",m_result->runTests());
  printf("Failure total: %d   ", m_result->testFailuresTotal());
  printf("Failures: %d   ", m_result->testFailures());
  printf("Errors: %d", m_result->testErrors());
  printf("\n");
#  endif
#else
  m_stream  <<  "Failures !!!"  <<  std::endl;
  m_stream  <<  "Run: "  <<  m_result->runTests()  << "   "
            <<  "Failure total: "  <<  m_result->testFailuresTotal()  << "   "
            <<  "Failures: "  <<  m_result->testFailures()  << "   "
            <<  "Errors: "  <<  m_result->testErrors()
            <<  std::endl;
#endif
}


void 
CompilerOutputter::setWrapColumn( int wrapColumn )
{
  m_wrapColumn = wrapColumn;
}


void 
CompilerOutputter::setNoWrap()
{
  m_wrapColumn = 0;
}


int 
CompilerOutputter::wrapColumn() const
{
  return m_wrapColumn;
}


CPPUNIT_NS_END
