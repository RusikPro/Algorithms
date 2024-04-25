#ifndef __15_DYNAMIC_PROGRAMMING_CPP_1_CUT_ROD_H__
#define __15_DYNAMIC_PROGRAMMING_CPP_1_CUT_ROD_H__

/*----------------------------------------------------------------------------*/

#include <cmath>
#include <limits>
#include <vector>

/*----------------------------------------------------------------------------*/

using Elements = std::vector< int >;
static constexpr int MINIMUM = std::numeric_limits< int >::min();

/*----------------------------------------------------------------------------*/

// Recursive top-down implementation
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
/*----------------------------------------------------------------------------*/

// Top-down with memoization

int memoizedCutRodAux ( Elements const & _p, int _n, Elements & _r )
{
    if ( _r[ _n ] >= 0 )
    {
        return _r[ _n ];
    }

    int q = MINIMUM;

    if ( _n == 0 )
    {
        q = 0;
    }
    else
    {
        for ( int i = 0; i < _n; ++i )
        {
            q = std::max(
                q, _p[ i ] + memoizedCutRodAux( _p, _n - i - 1, _r )
            );
        }
    }
    _r[ _n ] = q;

    return q;
}

/*----------------------------------------------------------------------------*/

int memoizedCutRod ( Elements const & _p, int _n )
{
    Elements r( _n + 1, MINIMUM );

    return memoizedCutRodAux( _p, _n, r );
}

/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

#endif // __15_DYNAMIC_PROGRAMMING_CPP_1_CUT_ROD_H__