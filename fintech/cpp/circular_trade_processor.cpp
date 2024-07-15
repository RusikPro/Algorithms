#include <iostream>
#include <vector>
#include <set>
#include <chrono>
#include <thread>

/*----------------------------------------------------------------------------*/

static constexpr int NUM_SECONDS = 10;

/*----------------------------------------------------------------------------*/

using namespace std::chrono;

/*----------------------------------------------------------------------------*/

struct Trade
{
    time_point< steady_clock > timestamp;
    int value; // Additional trade-related values can be added here

    Trade ( int _value )
        :   timestamp( steady_clock::now() )
        ,   value( _value )
    {
    }

    bool operator< ( Trade const & other ) const
    {
        return timestamp < other.timestamp;
    }
};

/*----------------------------------------------------------------------------*/

class TradeProcessor
{
private:
    std::vector< std::set< Trade > > buckets;
    int currentBucket;
    time_point<steady_clock> startTime;

    int getBucketIndex ( time_point< steady_clock > const & timestamp )
    {
        auto duration = duration_cast<seconds>( timestamp - startTime ).count();
        return duration % NUM_SECONDS;
    }

public:
    TradeProcessor ()
        :   buckets( NUM_SECONDS )
        ,   currentBucket( 0 )
        ,   startTime( steady_clock::now() )
    {
    }

    void store ( Trade const & trade )
    {
        auto now = steady_clock::now();
        auto bucketIndex = getBucketIndex( now );

        if ( bucketIndex != currentBucket )
        {
            // Clear buckets that are out of the NUM_SECONDS window
            auto clearTime = now - seconds( NUM_SECONDS );
            for ( int i = 0; i < NUM_SECONDS; ++i )
            {
                if (    !buckets[ i ].empty()
                    &&  buckets[ i ].begin()->timestamp < clearTime
                )
                {
                    buckets[ i ].clear();
                }
            }
            currentBucket = bucketIndex;
        }

        buckets[ bucketIndex ].insert( trade );
    }

    std::vector< Trade > getRecentTrades ()
    {
        auto now = steady_clock::now();
        std::vector< Trade > recentTrades;

        for ( int i = 0; i < NUM_SECONDS; ++i )
        {
            int index = ( currentBucket - i + NUM_SECONDS ) % NUM_SECONDS;
            for ( auto const & trade : buckets[ index ] )
            {
                auto tradeAge = duration_cast< seconds >(
                    now - trade.timestamp
                ).count();

                if ( tradeAge <= NUM_SECONDS )
                {
                    recentTrades.push_back( trade );
                }
            }
        }

        // Sort trades by timestamp in descending order
        std::sort(
                recentTrades.begin()
            ,   recentTrades.end()
            ,   [] ( Trade const & a, Trade const & b )
                {
                    return b.timestamp < a.timestamp; // Newest first
                }
        );

        return recentTrades;
    }
};

/*----------------------------------------------------------------------------*/

void simulateTrades ( TradeProcessor & tp )
{
    // Simulate storing trades at different intervals
    tp.store( Trade( 100 ) ); // Trade at t = 0s

    std::this_thread::sleep_for( milliseconds( 1000 ) );
    tp.store( Trade( 200 ) ); // Trade at t = 1s

    std::this_thread::sleep_for( milliseconds( 1000 ) );
    tp.store( Trade( 300 ) ); // Trade at t = 2s

    std::this_thread::sleep_for( milliseconds( 2000 ) ); // Waiting for 2 seconds
    tp.store( Trade( 400 ) ); // Trade at t = 4s
    tp.store( Trade( 401 ) );

    std::this_thread::sleep_for( milliseconds( 1 ) );
    tp.store( Trade( 402 ) );

    std::this_thread::sleep_for( milliseconds( 7000 ) ); // Waiting for 7 seconds (total elapsed time = 11s)
    tp.store( Trade( 500 ) ); // Trade at t = 11s

    std::this_thread::sleep_for( milliseconds( 1 ) );
    tp.store( Trade( 501 ) );
}

void printRecentTrades ( TradeProcessor & tp )
{
    std::vector< Trade > recentTrades = tp.getRecentTrades();

    std::cout << "Recent trades (last " << NUM_SECONDS << " seconds):"
        << std::endl;

    for ( auto const & trade : recentTrades )
    {
        auto timeElapsed = duration_cast< seconds >(
            steady_clock::now() - trade.timestamp
        ).count();

        std::cout << "Trade value: " << trade.value << " (elapsed time: "
            << timeElapsed << " seconds)" << std::endl;
    }
}

int main ()
{
    TradeProcessor tp;

    simulateTrades( tp );

    printRecentTrades( tp );

    return 0;
}
