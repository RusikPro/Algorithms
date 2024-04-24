#include "1_cut_rod.h"

#include "timer.h"

#include <iostream>

/*----------------------------------------------------------------------------*/

void testCutRod ()
{
    Elements prices = { 1, 5, 8, 9, 10, 17, 17, 20, 24, 30 };

    auto maximumPrice = cutRod( prices, 5 );
    std::cout << "Maximum price: " << maximumPrice << std::endl;

    {
        Timer<> t( "cutRod( prices, 10 )" );
        cutRod( prices, 10 );
    }

    {
        Timer<> t( "cutRod( prices, 20 )" );
        cutRod( prices, 20 );
    }

    {
        Timer< std::milli > t( "cutRod( prices, 25 )" );
        cutRod( prices, 25 );
    }

    {
        Timer< std::milli > t( "cutRod( prices, 26 )" );
        cutRod( prices, 26 );
    }
}

/*----------------------------------------------------------------------------*/

void testCutRodMemoization ()
{
    Elements prices = { 1, 5, 8, 9, 10, 17, 17, 20, 24, 30 };

    auto maximumPrice = memoizedCutRod( prices, 4 );
    std::cout << "Maximum price: " << maximumPrice << std::endl;
}

/*----------------------------------------------------------------------------*/

void comparePerformances ()
{
    Elements prices = { 1, 5, 8, 9, 10, 17, 17, 20, 24, 30 };

    {
        Timer< std::milli > t( "cutRod( prices, 26 )" );
        cutRod( prices, 26 );
    }

    {
        Timer< std::milli > t( "memoizedCutRod( prices, 26 )" );
        memoizedCutRod( prices, 26 );
    }
}

/*----------------------------------------------------------------------------*/

int main ()
{
    // testCutRod();
    testCutRodMemoization();
    // comparePerformances();
    return 0;
}
