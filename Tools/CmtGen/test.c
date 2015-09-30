//---------------------------------------------------------------------------//
/// \file  test.c
/// \brief 
//---------------------------------------------------------------------------//

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


#define GBS_MAX_SIZE_ADV_DATA_FRAME   ( 123 )

typedef enum _tGBS_GAP_OOB {
  eGBS_OOB_OFF = 0,
  eGBS_OOB_ON,
  eGBS_MAX_OOB,
} tGBS_GAP_OOB;

typedef struct
{
  tPrjUInt16 FreeBlocks; // Current free blocks in memory pool
  tPrjUInt16 MaxUsed; // Maximum used blocks
  tPrjUInt32 NumAllocations; // The number of success allocations
  tPrjUInt32 NumRejections; // The number of rejected allocations
} tMemPoolDiag;

int _high;

typedef int INT8;

