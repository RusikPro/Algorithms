#ifndef __15_DYNAMIC_PROGRAMMING_CPP_EXERCISES_1_CUT_ROD_EXERCISES_TESTS_H__
#define __15_DYNAMIC_PROGRAMMING_CPP_EXERCISES_1_CUT_ROD_EXERCISES_TESTS_H__

/*----------------------------------------------------------------------------*/

#include "1_cut_rod_exercises.h"

#include "timer.h"

#include <functional>
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

// Exercise 15.1-5
void testFibonacciValue ()
{
    int n = 14;
    std::cout << "testFibonacciValue, n = " << n << std::endl;

    auto value = fibonacciValue( n );

    std::cout << "Value in sequence: " << value << std::endl;
}

/*----------------------------------------------------------------------------*/

void testFibonacciValueRecurrence ()
{
    int n = 14;
    std::cout << "testFibonacciValueRecurrence, n = " << n << std::endl;

    auto value = fibonacciValueRecurrence( n );

    std::cout << "Value in sequence: " << value << std::endl;
}

/*----------------------------------------------------------------------------*/

void benchmarkFib (
        std::string const & _title
    ,   std::function< int( int ) > _f
    ,   int _n
)
{
    {
        Timer< std::milli > t( _title );
        _f( _n );
    }
}

/*----------------------------------------------------------------------------*/

void compareFibPerformances ()
{
    int n = 40;
    std::cout << "comparePerformances, n = " << n << std::endl;
    benchmarkFib( "fibonacciValue", fibonacciValue, n );

    benchmarkFib( "fibonacciValueRecurrence", fibonacciValueRecurrence, n );
}

/*----------------------------------------------------------------------------*/

#endif // __15_DYNAMIC_PROGRAMMING_CPP_EXERCISES_1_CUT_ROD_EXERCISES_TESTS_H__