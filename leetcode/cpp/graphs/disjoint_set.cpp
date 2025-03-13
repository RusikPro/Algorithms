#include <iostream>
#include <vector>


class UnionFastFind
{
public:
    UnionFastFind( int n )
        :   elems( n )
    {
        for ( int i = 0; i < n; ++i )
        {
            elems[ i ] = i;
        }
    }

    int find ( int x )
    {
        // TODO: check errors
        return elems[ x ];
    }

    void unionSet ( int x, int y )
    {
        int setX = find( x );
        int setY = find( y );

        if ( setX != setY )
        {
            for ( int i = 0; i < elems.size(); ++i )
            {
                if ( elems[ i ] == setY )
                {
                    elems[ i ] = setX;
                }
            }
        }
    }

    bool connected ( int x, int y )
    {
        return find( x ) == find( y );
    }

private:
    std::vector< int > elems; // index is an element, value is a set
};

class FastUnionFind
{
public:
    FastUnionFind( int n )
        :   elems( n )
    {
        for ( int i = 0; i < n; ++i )
        {
            elems[ i ] = i;
        }
    }

    int find_non_optimized ( int x )
    {
        // TODO: check errors
        while ( x != elems[ x ] )
        {
            x = elems[ x ];
        }
        return x;
    }

    int find ( int x )
    {
        // TODO: check errors
        if ( x == elems[ x ] )
        {
            return x;
        }
        return x = find( elems[ x ] );
    }

    void unionSet ( int x, int y )
    {
        int setX = find( x );
        int setY = find( y );

        if ( setX != setY )
        {
            elems[ setY ] = setX;
        }
    }

    bool connected ( int x, int y )
    {
        return find( x ) == find( y );
    }

private:
    std::vector< int > elems; // index is an element, value is a set
};

/*

[0] - 0
[1] - 0
[2] - 2
[3] - 3
[4] - 3
[5] - 3

*/


int main ()
{
    UnionFastFind ff( 10 );

    ff.unionSet( 0, 1 );
    ff.unionSet( 1, 2 );
    ff.unionSet( 0, 3 );

    ff.unionSet( 4, 6 );
    ff.unionSet( 4, 7 );
    ff.unionSet( 7, 8 );

    ff.unionSet( 5, 9 );

    std::cout << "ff.connected( 1, 3 ): " << ff.connected( 1, 3 ) << std::endl;
    std::cout << "ff.connected( 1, 4 ): " << ff.connected( 1, 4 ) << std::endl;
    std::cout << "ff.connected( 7, 4 ): " << ff.connected( 7, 4 ) << std::endl;

    FastUnionFind fu( 10 );

    fu.unionSet( 0, 1 );
    fu.unionSet( 1, 2 );
    fu.unionSet( 0, 3 );

    fu.unionSet( 4, 6 );
    fu.unionSet( 4, 7 );
    fu.unionSet( 7, 8 );

    fu.unionSet( 5, 9 );

    std::cout << "fu.connected( 1, 3 ): " << fu.connected( 1, 3 ) << std::endl;
    std::cout << "fu.connected( 1, 4 ): " << fu.connected( 1, 4 ) << std::endl;
    std::cout << "fu.connected( 7, 4 ): " << fu.connected( 7, 4 ) << std::endl;

}
