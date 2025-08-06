/*
3075. Maximize Happiness of Selected Children


You are given an array happiness of length n, and a positive integer k.

There are n children standing in a queue, where the ith child has happiness
value happiness[i]. You want to select k children from these n children in k
turns.

In each turn, when you select a child, the happiness value of all the children
that have not been selected till now decreases by 1. Note that the happiness
value cannot become negative and gets decremented only if it is positive.

Return the maximum sum of the happiness values of the selected children you can
achieve by selecting k children.


https://leetcode.com/problems/maximize-happiness-of-selected-children/description/
*/

#include <gtest/gtest.h>

#include <algorithm>
#include <iostream>
#include <vector>

long long maximumHappinessSum ( std::vector< int > & _happiness, int _k )
{
    std::sort( _happiness.begin(), _happiness.end(), std::greater< int >() );

    int reduction = 0;
    long long happinessSum = 0;

    for ( auto const & child: _happiness )
    {
        if ( reduction == _k )
        {
            return happinessSum;
        }
        happinessSum += std::max( child - reduction, 0 );

        ++reduction;
    }

    return happinessSum;
}

TEST( MaximumHappinessSumTest, BasicTests )
{
    std::vector< int > happiness1 = { 5, 3, 2, 1 };
    EXPECT_EQ(maximumHappinessSum( happiness1, 2 ), 7 );

    std::vector< int > happiness2 = { 5, 3, 2, 1 };
    EXPECT_EQ(maximumHappinessSum( happiness2, 3 ), 7 );

    std::vector< int > happiness3 = { 5, 3, 2, 1 };
    EXPECT_EQ( maximumHappinessSum( happiness3, 4 ), 7 );

    std::vector< int > happiness4 = { 5, 5, 5, 5 };
    EXPECT_EQ( maximumHappinessSum( happiness4, 2 ), 9 );

    std::vector< int > happiness5 = { 1, 2, 3, 4, 5 };
    EXPECT_EQ( maximumHappinessSum( happiness5, 5 ), 9 );

    std::vector< int > happiness6 = { 1, 2, 3, 4, 5 };
    EXPECT_EQ( maximumHappinessSum( happiness6, 3 ), 9 );
}

int main ( int argc, char ** argv )
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}