#include "trade_processor.hpp"

#include <iostream>

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

    bool operator< ( Trade const & _other ) const
    {
        return timestamp < _other.timestamp;
    }
};

/*----------------------------------------------------------------------------*/

void simulateTrades ( TradeProcessor< Trade > & _tp )
{
    // Simulate storing trades at different intervals
    _tp.store( Trade( 100 ) ); // Trade at t = 0s
    std::this_thread::sleep_for( milliseconds( 1000 ) );
    _tp.store( Trade( 200 ) ); // Trade at t = 1s
    std::this_thread::sleep_for( milliseconds( 1000 ) );
    _tp.store( Trade( 300 ) ); // Trade at t = 2s
    std::this_thread::sleep_for( milliseconds( 2000 ) ); // Waiting for 2 seconds
    _tp.store( Trade( 400 ) ); // Trade at t = 4s
    std::this_thread::sleep_for( milliseconds( 7000 ) ); // Waiting for 7 seconds (total elapsed time = 11s)
    _tp.store( Trade( 500 ) ); // Trade at t = 11s
}

void printRecentTrades ( TradeProcessor< Trade > & _tp )
{
    auto recentTrades = _tp.getRecentTrades();
    std::cout << "Recent trades (last 10 seconds):" << std::endl;
    for ( auto const & trade : recentTrades )
    {
        auto timeElapsed = duration_cast< seconds >(
            steady_clock::now() - trade.timestamp
        ).count();

        std::cout
            << "Trade value: " << trade.value << " (elapsed time: "
            << timeElapsed << " seconds)" << std::endl
        ;
    }
}

/*----------------------------------------------------------------------------*/

int main()
{
    TradeProcessor< Trade > tp;

    simulateTrades( tp );

    printRecentTrades( tp );

    return 0;
}