/*
857. Minimum Cost to Hire K Workers

There are n workers. You are given two integer arrays quality and wage where
quality[i] is the quality of the ith worker and wage[i] is the minimum wage
expectation for the ith worker.

We want to hire exactly k workers to form a paid group. To hire a group of k
workers, we must pay them according to the following rules:

Every worker in the paid group must be paid at least their minimum wage
expectation. In the group, each worker's pay must be directly proportional to
their quality. This means if a worker’s quality is double that of another worker
in the group, then they must be paid twice as much as the other worker.
Given the integer k, return the least amount of money needed to form a paid
group satisfying the above conditions. Answers within 10-5 of the actual answer
will be accepted.
*/

#include <gtest/gtest.h>

#include <iostream>
#include <queue>
#include <vector>

double mincostToHireWorkers (
        std::vector< int > _quality
    ,   std::vector< int > _wage
    ,   int _k
)
{
    size_t size = _wage.size();
    std::vector< std::pair< double, int > > ratiosQualities;
    ratiosQualities.reserve( size );

    for ( int i = 0; i < size; ++i )
    {
        ratiosQualities.emplace_back(
            static_cast< double >( _wage[ i ] ) / _quality[ i ], _quality[ i ]
        );
    }

    sort( ratiosQualities.begin(), ratiosQualities.end() );

    std::priority_queue< int > qualities;
    double qualSum = 0;
    double minCost = std::numeric_limits< double >::max();

    for ( auto const & worker: ratiosQualities )
    {
        double ratio = worker.first;
        int qual = worker.second;

        if ( qualities.size() == _k )
        {
            qualSum -= qualities.top();
            qualities.pop();
        }

        qualSum += qual;
        qualities.push( qual );

        if ( qualities.size() == _k )
        {
            minCost = std::min( minCost, qualSum * ratio );
        }
    }

    return minCost;
}

TEST( MinCostToHireWorkersTest, BasicTests )
{
    EXPECT_NEAR(
            mincostToHireWorkers( { 10, 20, 5 }, { 70, 50, 30 }, 2 )
        ,   105.0
        ,   1e-9
    );

    EXPECT_NEAR(
            mincostToHireWorkers( { 3, 1, 10, 10, 1 }, { 4, 8, 2, 2, 7 }, 3 )
        ,   30.66667
        ,   1e-4
    );
}

int main ( int argc, char ** argv )
{
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}
