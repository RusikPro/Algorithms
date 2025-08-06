#ifndef __15_DYNAMIC_PROGRAMMING_CPP_1_CUT_ROD_TESTS_H__
#define __15_DYNAMIC_PROGRAMMING_CPP_1_CUT_ROD_TESTS_H__

/*----------------------------------------------------------------------------*/

#include "1_cut_rod.h"

#include "timer.h"

#include <functional>
#include <iostream>

/*----------------------------------------------------------------------------*/

Elements p = { 1, 5, 8, 9, 10, 17, 17, 20, 24, 30 };

/*----------------------------------------------------------------------------*/

// Data from book
void validationTest ( std::function< int( Elements const &, int ) > _f )
{
    for ( int i = 0; i < 10; ++i )
    {
        std::cout << "Maximum price (" << i + 1 << "): " <<
            _f( p, i + 1 ) << std::endl
        ;
    }
}

/*----------------------------------------------------------------------------*/

void testCutRod ()
{
    std::cout << "cutRod" << std::endl;
    validationTest( cutRod );
}

/*----------------------------------------------------------------------------*/

void testMemoizationCutRod ()
{
    std::cout << "memoizedCutRod" << std::endl;
    validationTest( memoizedCutRod );
}

/*----------------------------------------------------------------------------*/

void testBottomUpCutRod ()
{
    std::cout << "bottomUpCutRod" << std::endl;
    validationTest( bottomUpCutRod );
}

/*----------------------------------------------------------------------------*/

void testExtendedBottomUpCutRod ()
{
    int n = 4;
    std::cout << "extendedBottomUpCutRod, n = " << n << std::endl;

    auto [ price, pieces ] = extendedBottomUpCutRod( p, n );

    std::cout << "Price: " << price << std::endl;
    for ( ; n > 0; n = n - pieces[ n - 1 ] )
    {
        std::cout << pieces[ n - 1 ] << ' ';
    }
    std::cout << std::endl;
}

/*----------------------------------------------------------------------------*/

void benchmarkTestMilli (
        std::string const & _title
    ,   std::function< int( Elements const &, int ) > _f
    ,   int _n
)
{
    {
        Timer< std::milli > t( _title );
        _f( p, _n );
    }
}

/*----------------------------------------------------------------------------*/

void comparePerformances ()
{
    benchmarkTestMilli( "cutRod( p, 26 )", cutRod, 26 );

    benchmarkTestMilli( "memoizedCutRod( p, 26 )", memoizedCutRod, 26 );

    benchmarkTestMilli( "bottomUpCutRod( p, 26 )", bottomUpCutRod, 26 );
}

/*----------------------------------------------------------------------------*/

#endif // __15_DYNAMIC_PROGRAMMING_CPP_1_CUT_ROD_TESTS_H__