#include <iostream>
#include <vector>

class UnionFind
{
public:

    UnionFind ( int n )
        :   root( n )
        ,   rank( n )
    {
        for ( int i = 0; i < n; ++i )
        {
            root[ i ] = i;
            rank[ i ] = 1;
        }
    }

    int find ( int x )
    {
        if ( x == root[ x ] )
        {
            return x;
        }

        return root[ x ] = find( root[ x ] );
    }

    void unionSet ( int x, int y )
    {
        int rootX = find( x );
        int rootY = find( y );
        if ( rootX != rootY )
        {
            if ( rank[ rootX ] > rank[ rootY ] )
            {
                root[ rootY ] = rootX;
            }
            else if ( rank[ rootX ] < rank[ rootY ] )
            {
                root[ rootX ] = rootY;
            }
            else
            {
                root[ rootY ] = rootX;
                ++rank[ rootX ];
            }
        }
    }

    bool connected ( int x, int y )
    {
        return find( x ) == find( y );
    }

private:

    std::vector< int > root;
    std::vector< int > rank;
};


int main() {
    // for displaying booleans as literal strings, instead of 0 and 1
    std::cout << std::boolalpha;
    UnionFind uf(10);
    // 1-2-5-6-7 3-8-9 4
    uf.unionSet(1, 2);
    uf.unionSet(2, 5);
    uf.unionSet(5, 6);
    uf.unionSet(6, 7);
    uf.unionSet(3, 8);
    uf.unionSet(8, 9);
    std::cout << uf.connected(1, 5) << std::endl;  // true
    std::cout << uf.connected(5, 7) << std::endl;  // true
    std::cout << uf.connected(4, 9) << std::endl;  // false
    // 1-2-5-6-7 3-8-9-4
    uf.unionSet(9, 4);
    std::cout << uf.connected(4, 9) << std::endl;  // true

    return 0;
}
