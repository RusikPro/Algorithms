#include <iostream>
#include <vector>
#include <limits>

using Elements = std::vector< int >;

static constexpr int MINIMUM = std::numeric_limits< int >::min();
static constexpr int MAXIMUM = std::numeric_limits< int >::max();

Elements p = { 1, 5, 8, 9, 10, 17, 17, 20, 24, 30 };

int cutRod ( std::vector< int > const & _p, int _n )
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

std::pair< int, Elements >
extendedBottomUpCutRod ( Elements const & _p, int _n )
{
    Elements r( _n + 1, 0 );
    r[ 0 ] = 0;

    Elements s( _n, 0 );

    for ( int j = 1; j <= _n; ++j )
    {
        int q = MINIMUM;
        for ( int i = 1; i <= j; ++i )
        {
            if ( q < _p[ i - 1 ] + r[ j - i ] )
            {
                q = _p[ i - 1 ] + r[ j - i ];
                s[ j - 1 ] = i;
            }
        }
        r[ j ] = q;
    }
    return { r[ _n ], s };
}

/*----------------------------------------------------------------------------*/

int main ()
{
    auto result = cutRod( p, p.size() - 1 );

    std::cout << "Result: " << result << std::endl;

    int n = 4;

    auto [ price, pieces ] = extendedBottomUpCutRod( p, n );

    std::cout << "Price: " << price << std::endl;

    for ( ; n > 0; n = n - pieces[ n - 1 ] )
    {
        std::cout << pieces[ n - 1 ] << ' ';
    }
    std::cout << std::endl;
}
