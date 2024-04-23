#include <cmath>
#include <iostream>
#include <limits>
#include <vector>

/*----------------------------------------------------------------------------*/

using Elements = std::vector< int >;
static constexpr int MINIMUM = std::numeric_limits< int >::min();

/*----------------------------------------------------------------------------*/

int cutRod ( Elements const & _p, int _n )
{
    if ( _n == 0 )
    {
        return 0;
    }

    int q = MINIMUM;
    for ( int i = 0; i < _n; ++i )
    {
        q = std::max( q, _p[ i ] + cutRod( _p, _n - i - 1 ) );
    }
    return q;
}

/*----------------------------------------------------------------------------*/

void testCutRod ()
{
    Elements prices = { 1, 5, 8, 9, 10, 17, 17, 20, 24, 30 };
    auto maximumPrice = cutRod( prices, 10 );
    std::cout << "Maximum price: " << maximumPrice << std::endl;
}

/*----------------------------------------------------------------------------*/

int main () {
    testCutRod();
    return 0;
}
