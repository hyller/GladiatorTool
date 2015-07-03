#include <cppunit/ui/text/TextTestRunner.h>
#include "Scripts/TestAscii.h"

int main( )
{
  CPPUNIT_NS::TextTestRunner runner_TestGAscii;
  runner_TestGAscii.addTest( CTestGAscii::suite( ) );
  runner_TestGAscii.run( "CTestGAscii" );

  return( 0 );
}