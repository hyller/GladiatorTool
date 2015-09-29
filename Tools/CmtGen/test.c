// SelfEncapsulateData
private int _low, _high;

boolean includes( int arg )
{
  return( arg >= _low && arg <= _high );
}

void grow( int factor )
{
  _high = _high * factor;
}

IntRange( int low, int high )
{
  _low  = low;
  _high = high;
}

// ExtractMethod
void printOwing( double amount )
{
  printBanner( );

  //print details
  System.out.println( "name:" + _name );
  System.out.println( "amount" + amount );
}

//    Comments test, This service is called to reduce the transfer time when copying to LCD. The
//  purpose is to define a rectangular zone that the driver will transfer to the hardware controller
//  when the CopyToLCD function is called. The partial refresh zone is defined by 2 coordinates
//  forming a rectangle: (xMin, yMin), and (xMax, yMax).

///      Comments test, This service is called to reduce the transfer time when copying to LCD. The
///  purpose is to define a rectangular zone that the driver will transfer to the hardware controller
///  when the CopyToLCD function is called. The partial refresh zone is defined by 2 coordinates
///  forming a rectangle: (xMin, yMin), and (xMax, yMax).