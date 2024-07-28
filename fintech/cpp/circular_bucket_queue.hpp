
#include <vector>
#include <set>
#include <chrono>
#include <thread>
#include <concepts>
#include <algorithm>

/*----------------------------------------------------------------------------*/

using namespace std::chrono;

/*----------------------------------------------------------------------------*/

// Concept to check if a class has a timestamp and < operator
template < typename _T >
concept TimedElement = requires ( _T _a, _T _b )
{
    { _a.timestamp } -> std::convertible_to< time_point< steady_clock > >;
    { _a < _b } -> std::convertible_to< bool >;
};

/*----------------------------------------------------------------------------*/

// Generic CircularBucketQueue class
template < TimedElement _ElementType >
class CircularBucketQueue
{

private:
    std::vector< std::set< _ElementType > > m_buckets;
    int m_currentBucket;
    time_point< steady_clock > m_startTime;
    int m_numSeconds;

    int getBucketIndex ( time_point< steady_clock > const & _timestamp )
    {
        auto duration =
            duration_cast< seconds >( _timestamp - m_startTime ).count()
        ;
        return duration % m_numSeconds;
    }

public:
    CircularBucketQueue ( int _numSeconds = 10 )
        :   m_buckets( _numSeconds )
        ,   m_currentBucket( 0 )
        ,   m_startTime( steady_clock::now() )
        ,   m_numSeconds( _numSeconds )
    {
    }

    void store ( _ElementType const & trade )
    {
        auto now = steady_clock::now();
        auto bucketIndex = getBucketIndex( now );

        if ( bucketIndex != m_currentBucket )
        {
            // Clear m_buckets that are out of the m_numSeconds window
            auto clearTime = now - seconds( m_numSeconds );
            for ( int i = 0; i < m_numSeconds; ++i )
            {
                if (    !m_buckets[ i ].empty()
                    &&  m_buckets[ i ].begin()->timestamp < clearTime
                )
                {
                    m_buckets[ i ].clear();
                }
            }
            m_currentBucket = bucketIndex;
        }

        m_buckets[ bucketIndex ].insert( trade );
    }

    std::vector< _ElementType > getRecentTrades ()
    {
        auto now = steady_clock::now();
        std::vector< _ElementType > recentTrades;

        for ( int i = 0; i < m_numSeconds; ++i )
        {
            int index = ( m_currentBucket - i + m_numSeconds ) % m_numSeconds;
            for ( auto const & trade : m_buckets[ index ] )
            {
                auto tradeAge = duration_cast< seconds >(
                    now - trade.timestamp
                ).count();

                if ( tradeAge <= m_numSeconds )
                {
                    recentTrades.push_back( trade );
                }
            }
        }

        std::sort(
                recentTrades.begin()
            ,   recentTrades.end()
            ,   [] ( _ElementType const & _a, _ElementType const & _b )
                {
                    return _b.timestamp < _a.timestamp; // Newest first
                }
        );

        return recentTrades;
    }
};

/*----------------------------------------------------------------------------*/
