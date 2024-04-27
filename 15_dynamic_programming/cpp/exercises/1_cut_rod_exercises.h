#ifndef __15_DYNAMIC_PROGRAMMING_CPP_EXERCISES_1_CUT_ROD_EXERCISES_H__
#define __15_DYNAMIC_PROGRAMMING_CPP_EXERCISES_1_CUT_ROD_EXERCISES_H__

/*----------------------------------------------------------------------------*/

#include "constants.h"

#include <cmath>
#include <vector>

/*----------------------------------------------------------------------------*/

using Elements = std::vector< int >;

/*----------------------------------------------------------------------------*/

// Exercise 15.1-3
std::pair< int, Elements >
_extendedBottomUpCutRodWithCost ( Elements const & _p, int _n, int _c )
{
    Elements r( _n + 1, 0 );
    r[ 0 ] = 0;

    Elements s( _n, 0 );

    for ( int j = 1; j <= _n; ++j )
    {
        int q = _p[ j - 1 ];
        s[ j - 1 ] = j;

        for ( int i = 1; i <= j; ++i )
        {
            if ( q < _p[ i - 1 ] + r[ j - i ] - _c )
            {
                q = _p[ i - 1 ] + r[ j - i ] - _c;
                s[ j - 1 ] = i;
            }
        }
        r[ j ] = q;
    }
    return { r[ _n ], s };
}

/*----------------------------------------------------------------------------*/

// Exercise 15.1-3
std::pair< int, Elements >
extendedBottomUpCutRodWithCost ( Elements const & _p, int _n, int _c )
{
    auto [ price, pieces ] = _extendedBottomUpCutRodWithCost( _p, _n, _c );

    Elements finalPieces;
    for ( int n = _n ; n > 0; n = n - pieces[ n - 1 ] )
    {
        finalPieces.push_back( pieces[ n - 1 ] );
    }
    return { price, finalPieces };
}

/*----------------------------------------------------------------------------*/

// Exercise 15.1-4
int extendedMemoizedCutRodAux (
        Elements const & _p
    ,   int _n
    ,   Elements & _r
    ,   Elements & _s
)
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
            auto result = extendedMemoizedCutRodAux( _p, _n - i - 1, _r, _s );
            if ( q < _p[ i ] + result )
            {
                q = _p[ i ] + result;

                _s[ _n ] = i + 1;
            }
        }
    }
    _r[ _n ] = q;

    return q;
}

/*----------------------------------------------------------------------------*/

std::pair< int, Elements >
extendedMemoizedCutRod ( Elements const & _p, int _n )
{
    Elements r( _n + 1, MINIMUM );
    Elements s( _n + 1, 0 );

    auto price = extendedMemoizedCutRodAux( _p, _n, r, s );
    return { price, s };
}

/*----------------------------------------------------------------------------*/

#endif // __15_DYNAMIC_PROGRAMMING_CPP_EXERCISES_1_CUT_ROD_EXERCISES_H__