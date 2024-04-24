#include "1_cut_rod.h"

#include "timer.h"

#include <iostream>

/*----------------------------------------------------------------------------*/

void testCutRod ()
{
    Elements prices = { 1, 5, 8, 9, 10, 17, 17, 20, 24, 30 };

    auto maximumPrice = cutRod( prices, 10 );
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

int main ()
{
    testCutRod();
    return 0;
}
