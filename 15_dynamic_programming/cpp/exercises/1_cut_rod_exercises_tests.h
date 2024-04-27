#ifndef __15_DYNAMIC_PROGRAMMING_CPP_EXERCISES_1_CUT_ROD_EXERCISES_TESTS_H__
#define __15_DYNAMIC_PROGRAMMING_CPP_EXERCISES_1_CUT_ROD_EXERCISES_TESTS_H__

/*----------------------------------------------------------------------------*/

#include "1_cut_rod_exercises.h"

#include <iostream>

/*----------------------------------------------------------------------------*/

Elements p = { 1, 5, 8, 9, 10, 17, 17, 20, 24, 30 };

/*----------------------------------------------------------------------------*/

// Exercise 15.1-3
void testExtendedBottomUpCutRodWithCost ()
{
    static constexpr int n = 4;
    static constexpr int c = 1;
    std::cout << "extendedBottomUpCutRodWithCost, n = " << n
        << " c = " << c << std::endl
    ;

    auto [ price, pieces ] = extendedBottomUpCutRodWithCost( p, n, c );

    std::cout << "Price: " << price << std::endl;
    for ( auto const & piece: pieces )
    {
        std::cout << piece << ' ';
    }
    std::cout << std::endl;
}

/*----------------------------------------------------------------------------*/

// Exercise 15.1-4
void testExtendedMemoizedCutRod ()
{
    int n = 7;
    std::cout << "extendedMemoizedCutRod, n = " << n << std::endl;

    auto [ price, pieces ] = extendedMemoizedCutRod( p, n );

    std::cout << "Price: " << price << std::endl;
    for ( auto & piece: pieces )
    {
        std::cout << piece << ' ';
    }
    std::cout << std::endl;
}

/*----------------------------------------------------------------------------*/

#endif // __15_DYNAMIC_PROGRAMMING_CPP_EXERCISES_1_CUT_ROD_EXERCISES_TESTS_H__