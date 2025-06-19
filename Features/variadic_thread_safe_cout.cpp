#include "get_thread_id_str.h"

#include <chrono>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

/*----------------------------------------------------------------------------*/

inline std::string now_str()
{
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
    now.time_since_epoch()) % 1000;

    std::tm* local_tm = std::localtime(&time_t);

    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << local_tm->tm_hour << ":"
    << std::setfill('0') << std::setw(2) << local_tm->tm_min << ":"
    << std::setfill('0') << std::setw(2) << local_tm->tm_sec << "."
    << std::setfill('0') << std::setw(3) << ms.count();

    return oss.str();
}

/*----------------------------------------------------------------------------*/

std::recursive_mutex g_coutResource;

inline void thread_safe_cout_ ()
{
    std::cout << std::endl;
}

template < typename _FirstT, typename ..._RestT >
inline void thread_safe_cout_ ( _FirstT && _first, _RestT && ..._rest )
{
    std::cout << std::forward< _FirstT >( _first ) << " ";
    thread_safe_cout_( std::forward< _RestT >( _rest )... );
}

template < typename _FirstT, typename ..._RestT >
inline void thread_safe_cout ( _FirstT && _first, _RestT && ..._rest )
{
    std::unique_lock< std::recursive_mutex > lock( g_coutResource );

    std::cout << now_str() << " [" << get_thread_id_str() << "] ";
    thread_safe_cout_(
        std::forward< _FirstT >( _first ), std::forward< _RestT >( _rest )...
    );
}

/*----------------------------------------------------------------------------*/

inline void sleep_for ( std::size_t _milliseconds )
{
    std::this_thread::sleep_for( std::chrono::milliseconds( _milliseconds ) );
    thread_safe_cout( _milliseconds, "milliseconds passed" );
}

/*----------------------------------------------------------------------------*/

int main ()
{
    thread_safe_cout("Starting thread-safe cout demonstration");

    std::vector<std::thread> threads;

    auto worker = [] ( int thread_id )
    {
        for (int i = 0; i < 5; ++i)
        {
            thread_safe_cout( "Thread", thread_id, "- message", i + 1 );
            sleep_for( 100 + ( thread_id * 50 ) );
        }
        thread_safe_cout("Thread", thread_id, "finished");
    };

    for ( int i = 0; i < 4; ++i )
    {
        threads.emplace_back(worker, i + 1);
    }

    for ( int i = 0; i < 3; ++i )
    {
        thread_safe_cout( "Main thread message", i + 1 );
        sleep_for(100);
    }

    for ( auto & t : threads )
    {
        t.join();
    }

    thread_safe_cout("All threads completed. Demonstration finished.");

    return 0;
}

/*----------------------------------------------------------------------------*/
